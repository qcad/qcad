/**
 * Standalone performance benchmark for RHatchData::getPainterPaths().
 *
 * Build:  src/entity/bench/build_bench.sh
 * Run:    release/hatchbench [options]
 *
 * Options:
 *   -n <count>       number of timed repetitions per case (default 5)
 *   -w <count>       number of warm up repetitions per case (default 1)
 *   -f <substring>   only run cases whose name contains <substring>
 *   -l               list cases and exit
 *   -b <file>        write results as baseline to <file>
 *   -c <file>        compare results against baseline in <file>
 *   -v               verbose (print per-repetition timings)
 *
 * The benchmark prints, for every case, the median / minimum wall clock time
 * of a full (uncached) RHatchData::getPainterPaths() call plus a checksum of
 * the generated geometry. The checksum must not change when the
 * implementation is optimized: it is the regression guard for all changes.
 */
#include <QCoreApplication>
#include <QtGlobal>
#include <QString>
#include <QStringList>
#include <QList>
#include <QPainterPath>
#include <QDir>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "RArc.h"
#include "RCircle.h"
#include "REllipse.h"
#include "RHatchData.h"
#include "RLine.h"
#include "RMath.h"
#include "RPainterPath.h"
#include "RPattern.h"
#include "RPatternListMetric.h"
#include "RSettings.h"
#include "RSpline.h"
#include "RBox.h"
#include "RVector.h"

// ----------------------------------------------------------------------------
// output helpers
// ----------------------------------------------------------------------------

static bool verbose = false;

static void quietMessageHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg) {
    Q_UNUSED(ctx)
    // hatch generation is chatty (missing document, dense pattern warnings):
    // only let real warnings through when running verbose.
    if (!verbose && (type == QtDebugMsg || type == QtWarningMsg)) {
        return;
    }
    fprintf(stderr, "%s\n", qPrintable(msg));
}

// ----------------------------------------------------------------------------
// boundary construction helpers
// ----------------------------------------------------------------------------

/**
 * Appends a closed loop of line segments through the given points.
 */
static void addPolygonLoop(RHatchData& h, const QList<RVector>& pts) {
    h.newLoop();
    for (int i = 0; i < pts.length(); i++) {
        const RVector& a = pts[i];
        const RVector& b = pts[(i + 1) % pts.length()];
        h.addBoundary(QSharedPointer<RShape>(new RLine(a, b)));
    }
}

static void addRectLoop(RHatchData& h, double x1, double y1, double x2, double y2) {
    QList<RVector> pts;
    pts << RVector(x1, y1) << RVector(x2, y1) << RVector(x2, y2) << RVector(x1, y2);
    addPolygonLoop(h, pts);
}

/**
 * Star / cog shaped polygon with 2*teeth vertices: a boundary with many
 * line segments, which stresses the per-segment intersection search.
 */
static void addStarLoop(RHatchData& h, const RVector& c, double rOuter, double rInner, int teeth) {
    QList<RVector> pts;
    for (int i = 0; i < teeth * 2; i++) {
        double a = 2.0 * M_PI * i / (teeth * 2);
        double r = (i % 2 == 0) ? rOuter : rInner;
        pts << c + RVector::createPolar(r, a);
    }
    addPolygonLoop(h, pts);
}

/**
 * Scalloped circle: alternating arcs and lines, closed loop.
 */
static void addScallopLoop(RHatchData& h, const RVector& c, double r, double bump, int count) {
    h.newLoop();
    for (int i = 0; i < count; i++) {
        double a1 = 2.0 * M_PI * i / count;
        double a2 = 2.0 * M_PI * (i + 1) / count;
        RVector p1 = c + RVector::createPolar(r, a1);
        RVector p2 = c + RVector::createPolar(r, a2);
        RVector m = c + RVector::createPolar(r + bump, (a1 + a2) / 2.0);
        RArc arc = RArc::createFrom3Points(p1, m, p2);
        h.addBoundary(QSharedPointer<RShape>(new RArc(arc)));
    }
}

static void addCircleLoop(RHatchData& h, const RVector& c, double r) {
    h.newLoop();
    h.addBoundary(QSharedPointer<RShape>(new RCircle(c, r)));
}

static void addEllipseLoop(RHatchData& h, const RVector& c, double major, double ratio, double angle) {
    h.newLoop();
    h.addBoundary(QSharedPointer<RShape>(
        new REllipse(c, RVector::createPolar(major, angle), ratio, 0.0, 2 * M_PI, false)));
}

/**
 * Rounded rectangle: alternating lines and corner arcs, the typical mixed
 * line / arc boundary found in real drawings.
 */
static void addRoundedRectLoop(RHatchData& h, double x1, double y1, double x2, double y2, double r) {
    h.newLoop();
    h.addBoundary(QSharedPointer<RShape>(new RLine(RVector(x1 + r, y1), RVector(x2 - r, y1))));
    h.addBoundary(QSharedPointer<RShape>(new RArc(RVector(x2 - r, y1 + r), r, -M_PI / 2, 0.0, false)));
    h.addBoundary(QSharedPointer<RShape>(new RLine(RVector(x2, y1 + r), RVector(x2, y2 - r))));
    h.addBoundary(QSharedPointer<RShape>(new RArc(RVector(x2 - r, y2 - r), r, 0.0, M_PI / 2, false)));
    h.addBoundary(QSharedPointer<RShape>(new RLine(RVector(x2 - r, y2), RVector(x1 + r, y2))));
    h.addBoundary(QSharedPointer<RShape>(new RArc(RVector(x1 + r, y2 - r), r, M_PI / 2, M_PI, false)));
    h.addBoundary(QSharedPointer<RShape>(new RLine(RVector(x1, y2 - r), RVector(x1, y1 + r))));
    h.addBoundary(QSharedPointer<RShape>(new RArc(RVector(x1 + r, y1 + r), r, M_PI, M_PI * 1.5, false)));
}

// ----------------------------------------------------------------------------
// cases
// ----------------------------------------------------------------------------

struct Case {
    QString name;
    QString description;
    RHatchData hatch;
    bool draft;
    double pixelSizeHint;
};

static RHatchData makeHatch(const QString& pattern, double scale, double angleDeg) {
    RHatchData h(false, scale, RMath::deg2rad(angleDeg), pattern);
    return h;
}

static QList<Case> buildCases() {
    QList<Case> cases;

    {   // small rectangle, single direction pattern: the most common case
        Case c;
        c.name = "rect-ansi31";
        c.description = "300x200 rectangle, ANSI31, scale 1";
        c.hatch = makeHatch("ANSI31", 1.0, 0.0);
        addRectLoop(c.hatch, 0, 0, 300, 200);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // dense variant: many more pattern lines over the same boundary
        Case c;
        c.name = "rect-ansi31-dense";
        c.description = "300x200 rectangle, ANSI31, scale 0.2 (dense)";
        c.hatch = makeHatch("ANSI31", 0.2, 0.0);
        addRectLoop(c.hatch, 0, 0, 300, 200);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // two pattern line definitions (cross hatch)
        Case c;
        c.name = "rect-net";
        c.description = "300x200 rectangle, NET (2 pattern lines), scale 0.5";
        c.hatch = makeHatch("NET", 0.5, 0.0);
        addRectLoop(c.hatch, 0, 0, 300, 200);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // dashed pattern with 6 pattern line definitions
        Case c;
        c.name = "rect-earth";
        c.description = "300x200 rectangle, EARTH (6 dashed pattern lines), scale 0.5";
        c.hatch = makeHatch("EARTH", 0.5, 0.0);
        addRectLoop(c.hatch, 0, 0, 300, 200);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // dot pattern (hasDots path)
        Case c;
        c.name = "rect-dots";
        c.description = "300x200 rectangle, DOTS, scale 1";
        c.hatch = makeHatch("DOTS", 1.0, 0.0);
        addRectLoop(c.hatch, 0, 0, 300, 200);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // circular boundary with a hole: curved boundary intersections
        Case c;
        c.name = "ring-ansi31";
        c.description = "circle r100 with r40 hole, ANSI31, scale 0.5";
        c.hatch = makeHatch("ANSI31", 0.5, 0.0);
        addCircleLoop(c.hatch, RVector(0, 0), 100);
        addCircleLoop(c.hatch, RVector(0, 0), 40);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // many boundary elements: the intersection search dominates
        Case c;
        c.name = "star-240-ansi31";
        c.description = "240 segment star polygon, ANSI31, scale 0.5";
        c.hatch = makeHatch("ANSI31", 0.5, 0.0);
        addStarLoop(c.hatch, RVector(0, 0), 150, 100, 120);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // many arc boundary elements
        Case c;
        c.name = "scallop-120-ansi31";
        c.description = "120 arc scalloped circle, ANSI31, scale 0.5";
        c.hatch = makeHatch("ANSI31", 0.5, 0.0);
        addScallopLoop(c.hatch, RVector(0, 0), 120, 8, 120);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // ellipse boundary
        Case c;
        c.name = "ellipse-ansi31";
        c.description = "rotated ellipse, ANSI31, scale 0.5";
        c.hatch = makeHatch("ANSI31", 0.5, 0.0);
        addEllipseLoop(c.hatch, RVector(0, 0), 160, 0.4, RMath::deg2rad(30));
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // mixed line / arc boundary with an elliptical hole
        Case c;
        c.name = "mixed-ansi31";
        c.description = "rounded rectangle with elliptical hole, ANSI31, scale 0.5";
        c.hatch = makeHatch("ANSI31", 0.5, 0.0);
        addRoundedRectLoop(c.hatch, 0, 0, 300, 200, 40);
        addEllipseLoop(c.hatch, RVector(150, 100), 80, 0.5, RMath::deg2rad(20));
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // many loops (islands)
        Case c;
        c.name = "islands-64-ansi31";
        c.description = "300x200 rectangle with 64 circular holes, ANSI31, scale 0.5";
        c.hatch = makeHatch("ANSI31", 0.5, 0.0);
        addRectLoop(c.hatch, 0, 0, 300, 200);
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                addCircleLoop(c.hatch, RVector(20 + x * 36, 15 + y * 24), 8);
            }
        }
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // solid fill: exercises the early return / boundary path only
        Case c;
        c.name = "solid-star-240";
        c.description = "solid fill of 240 segment star polygon";
        c.hatch = RHatchData(true, 1.0, 0.0, "SOLID");
        addStarLoop(c.hatch, RVector(0, 0), 150, 100, 120);
        c.draft = false;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    {   // draft mode of a pattern hatch
        Case c;
        c.name = "draft-star-240";
        c.description = "draft mode of 240 segment star polygon hatch";
        c.hatch = makeHatch("ANSI31", 0.5, 0.0);
        addStarLoop(c.hatch, RVector(0, 0), 150, 100, 120);
        c.draft = true;
        c.pixelSizeHint = -1.0;
        cases << c;
    }

    return cases;
}

// ----------------------------------------------------------------------------
// checksum: geometry fingerprint of the generated painter paths
// ----------------------------------------------------------------------------

static inline void hashCombine(quint64& h, quint64 v) {
    h ^= v + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
}

static inline void hashDouble(quint64& h, double d) {
    // quantize to 1e-6 so that harmless floating point noise (e.g. different
    // order of the same additions) does not trip the regression guard:
    double q = std::floor(d * 1.0e6 + 0.5);
    if (q == 0.0) {
        q = 0.0;    // normalize -0
    }
    quint64 v;
    memcpy(&v, &q, sizeof(v));
    hashCombine(h, v);
}

struct Result {
    int pathCount;
    int elementCount;
    quint64 checksum;
    double medianMs;
    double minMs;
};

static void fingerprint(const QList<RPainterPath>& paths, Result& r) {
    quint64 h = 1469598103934665603ULL;
    int elements = 0;
    for (int i = 0; i < paths.length(); i++) {
        const QPainterPath& p = paths[i];
        int n = p.elementCount();
        elements += n;
        hashCombine(h, (quint64)n);
        for (int k = 0; k < n; k++) {
            QPainterPath::Element e = p.elementAt(k);
            hashCombine(h, (quint64)e.type);
            hashDouble(h, e.x);
            hashDouble(h, e.y);
        }
        // dot patterns are exported as points, not as path elements:
        QList<RVector> pts = paths[i].getPoints();
        elements += pts.length();
        hashCombine(h, (quint64)pts.length());
        for (int k = 0; k < pts.length(); k++) {
            hashDouble(h, pts[k].x);
            hashDouble(h, pts[k].y);
        }
    }
    r.pathCount = paths.length();
    r.elementCount = elements;
    r.checksum = h;
}

// ----------------------------------------------------------------------------
// running
// ----------------------------------------------------------------------------

static double runOnce(Case& c, Result& r) {
    // force a full regeneration:
    c.hatch.update();

    auto t0 = std::chrono::steady_clock::now();
    QList<RPainterPath> paths = c.hatch.getPainterPaths(c.draft, c.pixelSizeHint);
    auto t1 = std::chrono::steady_clock::now();

    fingerprint(paths, r);
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

int main(int argc, char** argv) {
    int reps = 5;
    int warmup = 1;
    QString filter;
    QString baselineOut;
    QString baselineIn;
    bool listOnly = false;

    for (int i = 1; i < argc; i++) {
        QString a = QString::fromLocal8Bit(argv[i]);
        if (a == "-n" && i + 1 < argc) { reps = atoi(argv[++i]); }
        else if (a == "-w" && i + 1 < argc) { warmup = atoi(argv[++i]); }
        else if (a == "-f" && i + 1 < argc) { filter = QString::fromLocal8Bit(argv[++i]); }
        else if (a == "-b" && i + 1 < argc) { baselineOut = QString::fromLocal8Bit(argv[++i]); }
        else if (a == "-c" && i + 1 < argc) { baselineIn = QString::fromLocal8Bit(argv[++i]); }
        else if (a == "-l") { listOnly = true; }
        else if (a == "-v") { verbose = true; }
        else {
            fprintf(stderr, "unknown argument: %s\n", qPrintable(a));
            return 2;
        }
    }

    qInstallMessageHandler(quietMessageHandler);

    QCoreApplication app(argc, argv);
    // use a dedicated settings file so the benchmark never touches the
    // settings of an installed QCAD:
    QCoreApplication::setOrganizationName("QCAD");
    QCoreApplication::setApplicationName("QCADHatchBenchmark");

    // RS::getDirectoryList() looks for resources relative to the current
    // directory: the binary lives in release/, the patterns one level up.
    {
        QDir appDir(QCoreApplication::applicationDirPath());
        if (appDir.dirName() == "release" || appDir.dirName() == "debug") {
            appDir.cdUp();
        }
        QDir::setCurrent(appDir.absolutePath());
    }

    // do not let the hatch generator bail out on dense cases:
    RSettings::setValue("GraphicsView/MaxHatchTime", 600000);
    RSettings::resetCache();

    RPatternListMetric::init();
    if (RPatternListMetric::getNames().isEmpty()) {
        fprintf(stderr,
                "error: no hatch patterns found.\n"
                "       expected patterns/metric in the parent directory of the binary.\n");
        return 1;
    }

    QList<Case> cases = buildCases();

    if (listOnly) {
        for (int i = 0; i < cases.length(); i++) {
            RBox bb = cases[i].hatch.getBoundingBox();
            printf("%-22s loops=%-3d complexity=%-5d bpElements=%-6d bbox=%.1f/%.1f..%.1f/%.1f  %s\n",
                   qPrintable(cases[i].name),
                   cases[i].hatch.getLoopCount(),
                   cases[i].hatch.getComplexity(),
                   cases[i].hatch.getBoundaryPath().elementCount(),
                   bb.getMinimum().x, bb.getMinimum().y,
                   bb.getMaximum().x, bb.getMaximum().y,
                   qPrintable(cases[i].description));
        }
        return 0;
    }

    // read baseline:
    QMap<QString, QPair<double, quint64> > baseline;
    if (!baselineIn.isEmpty()) {
        FILE* f = fopen(qPrintable(baselineIn), "r");
        if (f == NULL) {
            fprintf(stderr, "error: cannot read baseline: %s\n", qPrintable(baselineIn));
            return 1;
        }
        char name[256];
        double ms;
        unsigned long long sum;
        while (fscanf(f, "%255s %lf %llu\n", name, &ms, &sum) == 3) {
            baseline.insert(QString::fromLatin1(name), qMakePair(ms, (quint64)sum));
        }
        fclose(f);
    }

    printf("%-22s %10s %10s %8s %9s %20s",
           "case", "median/ms", "min/ms", "paths", "elements", "checksum");
    if (!baseline.isEmpty()) {
        printf(" %10s %s", "vs base", "geometry");
    }
    printf("\n");
    printf("%s\n", QString(baseline.isEmpty() ? 84 : 108, '-').toLatin1().constData());

    QList<QPair<QString, Result> > results;
    double totalMedian = 0.0;
    double totalBaseline = 0.0;
    bool anyMismatch = false;

    for (int i = 0; i < cases.length(); i++) {
        Case& c = cases[i];
        if (!filter.isEmpty() && !c.name.contains(filter)) {
            continue;
        }

        Result r;
        r.pathCount = 0;
        r.elementCount = 0;
        r.checksum = 0;

        for (int w = 0; w < warmup; w++) {
            runOnce(c, r);
        }

        QList<double> times;
        for (int k = 0; k < reps; k++) {
            double ms = runOnce(c, r);
            times << ms;
            if (verbose) {
                printf("    %s rep %d: %.3f ms\n", qPrintable(c.name), k, ms);
            }
        }
        std::sort(times.begin(), times.end());
        r.minMs = times.first();
        r.medianMs = times[times.length() / 2];

        printf("%-22s %10.3f %10.3f %8d %9d %20llu",
               qPrintable(c.name), r.medianMs, r.minMs,
               r.pathCount, r.elementCount, (unsigned long long)r.checksum);

        if (!baseline.isEmpty()) {
            if (baseline.contains(c.name)) {
                QPair<double, quint64> b = baseline.value(c.name);
                double speedup = b.first / r.medianMs;
                bool same = (b.second == r.checksum);
                if (!same) {
                    anyMismatch = true;
                }
                printf(" %9.2fx %s", speedup, same ? "OK" : "*** CHANGED ***");
                totalBaseline += b.first;
            }
            else {
                printf(" %10s %s", "-", "(new)");
            }
        }
        printf("\n");
        fflush(stdout);

        totalMedian += r.medianMs;
        results << qMakePair(c.name, r);
    }

    printf("%s\n", QString(baseline.isEmpty() ? 84 : 108, '-').toLatin1().constData());
    printf("%-22s %10.3f\n", "total", totalMedian);
    if (totalBaseline > 0.0) {
        printf("%-22s %10.3f  (%.2fx overall)\n", "total baseline", totalBaseline,
               totalBaseline / totalMedian);
    }

    if (!baselineOut.isEmpty()) {
        FILE* f = fopen(qPrintable(baselineOut), "w");
        if (f == NULL) {
            fprintf(stderr, "error: cannot write baseline: %s\n", qPrintable(baselineOut));
            return 1;
        }
        for (int i = 0; i < results.length(); i++) {
            fprintf(f, "%s %.6f %llu\n",
                    qPrintable(results[i].first),
                    results[i].second.medianMs,
                    (unsigned long long)results[i].second.checksum);
        }
        fclose(f);
        printf("baseline written to %s\n", qPrintable(baselineOut));
    }

    if (anyMismatch) {
        fprintf(stderr, "\nERROR: generated geometry differs from the baseline.\n");
        return 1;
    }

    return 0;
}
