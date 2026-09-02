/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 *
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include "RLinetypePatternExporter.h"
#include "RLine.h"
#include "RSpline.h"
#include "RSplineProxy.h"


/**
 * Constructor.
 *
 * \param exporter Exporter to which the shapes are exported, e.g. a RPainterPathExporter
 * \param shapes Shapes to be exported as connected shapes with continuous line pattern.
 * \param offset Offset into the line type pattern.
 */
RLinetypePatternExporter::RLinetypePatternExporter(RExporter& exporter, const QList<QSharedPointer<RShape> >& shapes, double offset) :
    RExporter(exporter.getDocument()), exporter(exporter), shapes(shapes) {

    double length = 0.0;

    for (int i=0; i<shapes.length(); i++) {
        length += shapes[i]->getLength();
        lengthAt.push_back(length);
    }

    RLine line(RVector(0,0), RVector(length, 0));

    // export straight line with angle 0 and length of line, arc, polyline, spline, ...:
    // the pattern is mapped to the shape by this exporter:
    exportLine(line, offset);
}

/**
 * Constructor.
 *
 * \param exporter Exporter to which the shapes are exported, e.g. a RPainterPathExporter
 * \param shape Shape to be exported as connected shapes with continuous line pattern.
 * \param offset Offset into the line type pattern.
 */
RLinetypePatternExporter::RLinetypePatternExporter(RExporter& exporter, const QSharedPointer<RShape>& shape, double offset) :
    RExporter(exporter.getDocument()), exporter(exporter) {

    shapes.append(shape);

    double length = shape->getLength();
    lengthAt.push_back(length);

    RLine line(RVector(0,0), RVector(length, 0));

    // export straight line with angle 0 and length of line, arc, polyline, spline, ...:
    // the pattern is mapped to the shape by this exporter:
    exportLine(line, offset);
}

/**
 * Exports the given line segment, mapped to the shapes that are being exported.
 *
 * \param line Line segment, mapped to the straight, horizontal line starting at 0/0).
 * \param angle Always 0.0.
 */
void RLinetypePatternExporter::exportLineSegment(const RLine& line, double angle) {
    Q_UNUSED(angle)

    // indices of segments on real shape:
    int i1, i2;
    // map segment start to real shape:
    RVector p1OnShape = getPointAt(line.startPoint.x, &i1);
    // map segment start to real shape:
    RVector p2OnShape = getPointAt(line.endPoint.x, &i2);
    // get angle on real shape:
    double a = getAngleAt(line.startPoint.x);

    if (!p1OnShape.isValid() || !p2OnShape.isValid()) {
        return;
    }

    if (line.getLength()<RS::PointTolerance) {
        // zero length (point):
        exporter.exportLineSegment(RLine(p1OnShape, p2OnShape), a);
    }
    else {
        exportShapesBetween(i1, p1OnShape, i2, p2OnShape, a, line.startPoint.x, line.endPoint.x);
    }
}

void RLinetypePatternExporter::exportPainterPaths(const QList<RPainterPath>& paths, double angle, const RVector& pos) {
    Q_UNUSED(angle)

    RVector p = getPointAt(pos.x);
    double a = getAngleAt(pos.x);
    RExporter::exportPainterPaths(paths, a, p);
}

RVector RLinetypePatternExporter::getPointAt(double d, int* index) {
    int i = getShapeAt(d);
    if (i<0 || i>=(int)lengthAt.size() || i>=(int)shapes.length()) {
        return RVector::invalid;
    }

    double a;
    if (i==0) {
        a = d;
    }
    else {
        a = d - lengthAt[i-1];
    }

    RVector ret = RVector::invalid;

    // fast path for splines: distance to point through the cached arc
    // length table (a call into the spline proxy inverts the arc
    // length from scratch every time which makes dashed splines
    // unusably slow):
    const SplineDistTable* table = getSplineTable(i);
    if (table!=NULL) {
        QSharedPointer<RSpline> spline = shapes[i].dynamicCast<RSpline>();
        ret = spline->getPointAt(lookupT(*table, a));
    }
    else {
        QList<RVector> points = shapes[i]->getPointsWithDistanceToEnd(a, RS::FromStart);
        if (points.isEmpty()) {
            return RVector::invalid;
        }
        ret = points[0];
    }

    if (!ret.isValid()) {
        return RVector::invalid;
    }

    if (index) {
        *index = i;
    }
    return ret;
}

double RLinetypePatternExporter::getAngleAt(double d) {
    int i = getShapeAt(d);
    if (i<0 || i>shapes.length() || (unsigned long)i>lengthAt.size()) {
        return 0.0;
    }
    double a = d - (i==0 ? 0.0 : lengthAt[i-1]);

    // fast path for splines (see getPointAt):
    const SplineDistTable* table = getSplineTable(i);
    if (table!=NULL) {
        QSharedPointer<RSpline> spline = shapes[i].dynamicCast<RSpline>();
        return spline->getAngleAtT(lookupT(*table, a));
    }

    return shapes[i]->getAngleAt(a);
}

/**
 * \return Cached arc length table for shape at index i or NULL if the
 *      shape is not a spline. The table is built on first use.
 */
const RLinetypePatternExporter::SplineDistTable* RLinetypePatternExporter::getSplineTable(int i) {
    if (i<0 || i>=shapes.length() || i>=(int)lengthAt.size()) {
        return NULL;
    }

    QMap<int, SplineDistTable>::const_iterator it = splineTables.find(i);
    if (it!=splineTables.constEnd()) {
        return it->dists.isEmpty() ? NULL : &it.value();
    }

    SplineDistTable& table = splineTables[i];

    QSharedPointer<RSpline> spline = shapes[i].dynamicCast<RSpline>();
    if (spline.isNull() || !spline->isValid()) {
        // marked as not applicable (empty table):
        return NULL;
    }

    double tMin = spline->getTMin();
    double tMax = spline->getTMax();
    if (!RMath::isNormal(tMin) || !RMath::isNormal(tMax) || tMax-tMin<RS::PointTolerance) {
        return NULL;
    }

    // sample density: 32 intervals per knot span, each interval length
    // corrected with its mid point (chord error negligible for the
    // purpose of placing pattern dashes):
    int spans = qMax(1, spline->countControlPoints() - spline->getDegree());
    int n = qBound(64, spans*32, 4096);

    table.dists.reserve(n+1);
    table.ts.reserve(n+1);

    double dist = 0.0;
    RVector prev = spline->getPointAt(tMin);
    table.dists.append(0.0);
    table.ts.append(tMin);
    for (int k=1; k<=n; k++) {
        double t = tMin + (tMax-tMin)*k/n;
        double tm = tMin + (tMax-tMin)*(k-0.5)/n;
        RVector pm = spline->getPointAt(tm);
        RVector p = spline->getPointAt(t);
        if (!pm.isValid() || !p.isValid()) {
            table.dists.clear();
            table.ts.clear();
            return NULL;
        }
        dist += prev.getDistanceTo(pm) + pm.getDistanceTo(p);
        table.dists.append(dist);
        table.ts.append(t);
        prev = p;
    }

    if (dist<RS::PointTolerance) {
        table.dists.clear();
        table.ts.clear();
        return NULL;
    }

    // normalize to the shape length used by the pattern walk
    // (lengthAt), so table distances and pattern distances line up
    // exactly at both ends:
    double shapeLength = lengthAt[i] - (i==0 ? 0.0 : lengthAt[i-1]);
    if (shapeLength>RS::PointTolerance) {
        double f = shapeLength / dist;
        for (int k=0; k<table.dists.length(); k++) {
            table.dists[k] *= f;
        }
    }

    return &table;
}

/**
 * \return Spline parameter for the given distance from the start of
 *      the spline, interpolated from the given arc length table.
 */
double RLinetypePatternExporter::lookupT(const SplineDistTable& table, double dist) {
    if (dist<=table.dists.first()) {
        return table.ts.first();
    }
    if (dist>=table.dists.last()) {
        return table.ts.last();
    }

    // binary search for the interval containing dist:
    int lo = 0;
    int hi = table.dists.length()-1;
    while (hi-lo>1) {
        int mid = (lo+hi)/2;
        if (table.dists[mid]<=dist) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }

    double d1 = table.dists[lo];
    double d2 = table.dists[hi];
    if (d2-d1<RS::PointTolerance) {
        return table.ts[lo];
    }
    double r = (dist-d1) / (d2-d1);
    return table.ts[lo] + (table.ts[hi]-table.ts[lo])*r;
}

int RLinetypePatternExporter::getShapeAt(double d) {
    for (int i=0; (unsigned long)i<lengthAt.size(); i++) {
        double d1;
        if (i==0) {
            d1 = 0.0;
        }
        else {
            d1 = lengthAt[i-1];
        }
        double d2 = lengthAt[i];
        if (d>=d1 && d<=d2) {
            return i;
        }
    }
    return -1;
}

void RLinetypePatternExporter::exportShapesBetween(int i1, const RVector& p1, int i2, const RVector& p2, double angle,
                                                   double d1, double d2) {
    for (int i=i1; i<=i2; i++) {
        if (i!=i1 && i!=i2) {
            // whole shape is between points:
            exporter.exportShapeSegment(shapes[i], angle);
            continue;
        }

        // fast path for splines: extract the dash as a sub spline by
        // parameter through the cached arc length table instead of
        // trimming a clone (trimming a spline inverts a point to a
        // parameter through the spline proxy for every single dash):
        const SplineDistTable* table = getSplineTable(i);
        if (table!=NULL && !RMath::isNaN(d1) && !RMath::isNaN(d2)) {
            QSharedPointer<RSpline> spline = shapes[i].dynamicCast<RSpline>();
            double shapeStart = (i==0 ? 0.0 : lengthAt[i-1]);
            double t1 = (i==i1) ? lookupT(*table, d1-shapeStart) : spline->getTMin();
            double t2 = (i==i2) ? lookupT(*table, d2-shapeStart) : spline->getTMax();
            if (t2-t1>RS::PointTolerance) {
                RSpline sub = spline->getSubSpline(t1, t2);
                if (sub.isValid()) {
                    exporter.exportShapeSegment(QSharedPointer<RShape>(new RSpline(sub)), angle);
                    continue;
                }
            }
            // fall through to the generic trim path on failure:
        }

        QSharedPointer<RShape> shape = shapes[i]->clone();
        if (!shape->isDirected()) {
            continue;
        }

        if (i==i1) {
            // trim start point:
            shape->trimStartPoint(p1);
        }
        if (i==i2) {
            // trim end point:
            shape->trimEndPoint(p2);
        }

        // invalid spline can cause artefacts when rendering splines with dashes:
        if (!shape->isValid()) {
            continue;
        }

        exporter.exportShapeSegment(shape, angle);
    }
}
