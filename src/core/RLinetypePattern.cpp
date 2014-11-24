/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
#include <QMap>

#include "RFontList.h"
#include "RLinetypePattern.h"
#include "RMath.h"
#include "RTextData.h"
#include "RTextRenderer.h"
#include "RDebug.h"

QMap<QString, QString> RLinetypePattern::nameMap;


RLinetypePattern::RLinetypePattern(bool metric, const QString& name, const QString& description, int num...)
    : metric(metric), name(name), description(description), symmetrical(NULL), symmetricalEnd(NULL) {

    QList<double> dashes;

    va_list vl;
    va_start(vl, num);
    for (int i=0; i<num; ++i) {
        dashes.append(va_arg(vl, double));
    }
    va_end(vl);

    set(dashes);
}

RLinetypePattern::RLinetypePattern(bool metric, const QString& name, const QString& description, const QList<double>& dashes)
    : metric(metric), name(name), description(description), symmetrical(NULL), symmetricalEnd(NULL) {

    set(dashes);
}

RLinetypePattern::RLinetypePattern() :
    metric(true), symmetrical(NULL), symmetricalEnd(NULL) {
}

RLinetypePattern::RLinetypePattern(bool metric, const QString& name, const QString& description) :
    metric(metric), name(name), description(description), symmetrical(NULL), symmetricalEnd(NULL) {
}

RLinetypePattern::RLinetypePattern(const RLinetypePattern& other) :
    symmetrical(NULL), symmetricalEnd(NULL) {
    operator =(other);
}

RLinetypePattern::~RLinetypePattern() {
    if (symmetrical != NULL) {
        delete[] symmetrical;
    }
    if (symmetricalEnd != NULL) {
        delete[] symmetricalEnd;
    }
}

//RLinetypePattern::RLinetypePattern(const QString& name, int num, double* pattern)
//    : name(name), num(0), pattern(), symmetrical(NULL) {

//    QList<double> dashes;

//    for (int i = 0; i < num; ++i) {
//        dashes.append(pattern[i]);
//    }

//    set(dashes);
//}


void RLinetypePattern::set(const QList<double>& dashes) {
    if (symmetrical != NULL) {
        delete[] symmetrical;
    }
    if (symmetricalEnd != NULL) {
        delete[] symmetricalEnd;
    }

    pattern = dashes;

    int num = pattern.length();
    symmetrical = new bool[num];
    for (int i = 0; i < num; ++i) {
        symmetrical[i] = true;
        for (int a = 1; a < num; ++a) {
            if (fabs(pattern[ RMath::absmod((i-a), num) ] - pattern[ RMath::absmod((i+a), num) ] ) > 0.1) {
                symmetrical[i] = false;
                break;
            }
        }
    }

    symmetricalEnd = new bool[num];
    for (int i = 0; i < num; ++i) {
        symmetricalEnd[i] = true;
        for (int a = 0; a < num; ++a) {
            if (fabs(pattern[ RMath::absmod((i-a), num) ] - pattern[ RMath::absmod((i+a+1), num) ] ) > 0.1) {
                symmetricalEnd[i] = false;
                break;
            }
        }
    }
}

RLinetypePattern& RLinetypePattern::operator=(const RLinetypePattern& other) {
    if (this == &other) {
        return *this;
    }

    if (symmetrical != NULL) {
        delete symmetrical;
    }
    if (symmetricalEnd != NULL) {
        delete symmetricalEnd;
    }

    if (!other.pattern.isEmpty()) {
        pattern = other.pattern;
        int num = pattern.length();
        symmetrical = new bool[num];
        for (int i = 0; i < num; ++i) {
            symmetrical[i] = other.symmetrical[i];
        }
        symmetricalEnd = new bool[num];
        for (int i = 0; i < num; ++i) {
            symmetricalEnd[i] = other.symmetricalEnd[i];
        }
    } else {
        pattern.clear();
        symmetrical = NULL;
        symmetricalEnd = NULL;
    }
    shapes = other.shapes;
    shapeTexts = other.shapeTexts;
    shapeTextStyles = other.shapeTextStyles;
    shapeNumbers = other.shapeNumbers;
    shapeScales = other.shapeScales;
    shapeRotations = other.shapeRotations;
    shapeOffsets = other.shapeOffsets;
    metric = other.metric;
    name = other.name;
    description = other.description;
    return *this;
}

bool RLinetypePattern::operator==(const RLinetypePattern& other) const {
    if (pattern.length()!=other.pattern.length()) {
        return false;
    }
    if (name.toLower()!=other.name.toLower()) {
        return false;
    }
    if (metric!=other.metric) {
        return false;
    }

    for (int i = 0; i < other.pattern.length(); ++i) {
        if (pattern[i] != other.pattern[i]) {
            return false;
        }
//        if (symmetrical[i] != other.symmetrical[i]) {
//            return false;
//        }
    }

    return true;
}

void RLinetypePattern::scale(double factor) {
    for (int i = 0; i < pattern.length(); ++i) {
        pattern[i] *= factor;
        if (shapeScales.contains(i)) {
            shapeScales[i] *= factor;
        }
        else {
            shapeScales.insert(i, factor);
        }
        if (shapeOffsets.contains(i)) {
            shapeOffsets[i] *= factor;
        }
    }
    updateShapes();
}

/**
 * \return Line pattern that can be used for a QPen to render screen
 * optimized patterns. Empty vector for continuous.
 */
QVector<qreal> RLinetypePattern::getScreenBasedLinetype() {
    QVector<qreal> ret;

    if (pattern.length()>1) {
        for (int i = 0; i < pattern.length(); ++i) {
//            if (RMath::isNaN(pattern[i])) {
//                continue;
//            }
            double dash = fabs(pattern[i]);
            if (!metric) {
                dash*=25.4;
            }
            //if (dash<RS::PointTolerance) {
            if (dash<2.0) {
                dash = 2.0;
            }
            ret << ceil(dash);
        }
    }

    return ret;
}

/**
 * \return Offset to use to apply the given pattern to an entity of the
 *      given length that the pattern is symmetrical.
 */
double RLinetypePattern::getPatternOffset(double length) {
    double optOffset = 0.0;
    double gap = 0.0;
    double maxGap = RMINDOUBLE;
    for (int i = 0; i < pattern.length(); ++i) {
        if (symmetrical[i]) {
            double offset = getPatternOffsetAt(length, i, &gap, false);
            //qDebug() << "gap at middle of " << i << ": " << gap;
            if (gap > maxGap) {
                maxGap = gap;
                optOffset = offset;
            }
        }
        if (symmetricalEnd[i]) {
            double offset = getPatternOffsetAt(length, i, &gap, true);
            //qDebug() << "gap at end of " << i << ": " << gap;
            if (gap > maxGap) {
                maxGap = gap;
                optOffset = offset;
            }
        }
    }

//    qDebug() << "length: " << length;
//    qDebug() << "gap: " << maxGap;
//    qDebug() << "optOffset: " << optOffset;

    return optOffset;
}

/**
 * \return Offset to use for an entity with the given length, so that
 * the given dash (index) is in the middle of the entity.
 */
double RLinetypePattern::getPatternOffsetAt(double length, int index, double* gap, bool end) {
    double patternLength = getPatternLength();
    if (patternLength<RS::PointTolerance) {
        return 0.0;
    }

    // distance from pattern start to middle of this dash:
    double po = fabs(getDashLengthAt(index)) / (end ? 1 : 2);
    for (int i = index - 1; i >= 0; --i) {
        po += fabs(getDashLengthAt(i));
    }

    double offset = length / 2 - po;
    int m = (int) RMath::trunc(offset / patternLength);
    offset -= (m + 1) * patternLength;
    if (gap != NULL) {
        *gap = getDelta(-offset);
    }
    return offset;
}

/**
 * \return Distance from start of pattern to
 */
double RLinetypePattern::getDelta(double pos) const {
    double l = getPatternLength();
    if (pos < 0) {
        pos += (RMath::trunc(pos / l) + 1) * l;
    } else if (pos > l) {
        pos -= RMath::trunc(pos / l) * l;
    }
    double total = 0.0;
    for (int i = 0; i < pattern.length(); ++i) {
        total += fabs(pattern[i]);
        if (total >= pos) {
            if (pattern[i] < 0) {
                return -(total - pos);
            }
            return total - pos;
        }
    }
    qWarning("RLinetypePattern::getDelta: invalid pos argument");
    return 0.0;
}

bool RLinetypePattern::hasDashAt(double pos) const {
    if (pos < 0) {
        pos += (RMath::trunc(pos / getPatternLength()) + 1) * getPatternLength();
    } else if (pos > getPatternLength()) {
        pos -= RMath::trunc(pos / getPatternLength()) * getPatternLength();
    }
    double total = 0.0;
    for (int i = 0; i < pattern.length(); ++i) {
//        if (RMath::isNaN(pattern[i])) {
//            continue;
//        }
        total += fabs(pattern[i]);
        if (total > pos) {
            return pattern[i] > 0;
        }
    }
    qWarning("RLinetypePattern::hasDashAt: invalid pos argument");
    return false;
}

bool RLinetypePattern::isSymmetrical(int i) const {
    if (i >= pattern.length()) {
        return false;
    }
    return symmetrical[i];
}

bool RLinetypePattern::isValid() const {
    return pattern.length()>0;
}

int RLinetypePattern::getNumDashes() const {
    return pattern.length();
}

QString RLinetypePattern::getName() const {
    return name;
}

void RLinetypePattern::setName(const QString& n) {
    name = n;
}

QString RLinetypePattern::getDescription() const {
    return description;
}

void RLinetypePattern::setDescription(const QString& d) {
    description = d;
}

QString RLinetypePattern::getLabel() const {
//    if (description.isEmpty()) {
//        return name;
//    }

//    else {
//        return name + " - " + description;
//    }

    //QString desc; //= p.getDescription();
//    QRegExp onlyPattern("[_\\. ]*");
//    if (onlyPattern.indexIn(desc)==0) {
//        if (p.getDescription().isEmpty()) {
//            desc = p.getName();
//        }
//        else {
//            desc = p.getName() + " - " + p.getDescription();
//        }
//    }
    QString desc = description;
    QString preview;
    if (!description.isEmpty()) {
        int k = description.lastIndexOf(QRegExp("[^_\\. ]"));
        if (k!=-1) {
            desc = description.mid(0, k+1);
            preview = description.mid(k+1);
            //prev.replace('.', QChar(0x00B7));
            //prev.replace('_', QChar(0x2014));
        }
        else {
            preview = desc;
            desc = "";
        }
    }

    //qDebug() << "desc: " << desc;
    //qDebug() << "preview: " << preview;

//    if (desc.isEmpty()) {
//        return fixName(name);
//    }

//    return fixName(desc);

    if (nameMap.isEmpty()) {
        initNameMap();
    }

    QString nameUpper = name.toUpper();
    if (nameMap.contains(nameUpper)) {
        return nameMap.value(nameUpper);
    }

//    if (nameUpper.endsWith(" (2x)")) {
//        QString nx2 = nameUpper+"X2";
//        nx2.replace(" ", "");
//        if (nameMap.contains(nx2)) {
//            return nameMap.value(nx2);
//        }
//    }

//    if (nameUpper.endsWith(" (.5x)")) {
//        QString n2 = nameUpper+"2";
//        n2.replace(" ", "");
//        if (nameMap.contains(n2)) {
//            return nameMap.value(n2);
//        }
//    }

    return name;
}

QList<double> RLinetypePattern::getPattern() const {
    return pattern;
}

double RLinetypePattern::getPatternLength() const {
    double ret=0;
    for (int i=0; i<pattern.length(); ++i) {
//        if (RMath::isNaN(pattern[i])) {
//            continue;
//        }
        ret += fabs(pattern[i]);
    }
    return ret;
}

double RLinetypePattern::getDashLengthAt(int i) const {
    if (i>=0 && i<pattern.length()) {
        return pattern[i];
    }
    return 0.0;
}

bool RLinetypePattern::hasShapes() const {
    return !shapes.isEmpty();
}

bool RLinetypePattern::hasShapeAt(int i) const {
    return shapes.contains(i);
}

QList<int> RLinetypePattern::getShapeIndices() const {
    return shapes.keys();
}

QList<RPainterPath> RLinetypePattern::getShapeAt(int i) const {
    QList<RPainterPath> ret;

    if (shapes.contains(i)) {
        for (int k=0; k<shapes[i].length(); k++) {
            if (shapes[i][k].getFeatureSize()<0.0) {
                continue;
            }
            RPainterPath pp = shapes[i][k];
            ret.append(pp);
        }

        return ret;
    }
    else {
        qWarning() << "RLinetypePattern::getShapeAt: invalid pattern definition: " << getName();
        qWarning() << "RLinetypePattern::getShapeAt: no shape at: " << i;
        return ret;
    }
}

void RLinetypePattern::updateShapes() {
    for (int i=0; i<pattern.length(); i++) {
        QString textStyle;
        QString text;
        RVector offset;
        double scale = 1.0;
        double rotation = 0.0;

        if (shapeTextStyles.contains(i) && shapeTexts.contains(i)) {
            textStyle = shapeTextStyles[i];
            text = shapeTexts[i];
        }
        if (shapeOffsets.contains(i)) {
            offset = shapeOffsets[i];
        }
        if (shapeScales.contains(i)) {
            scale = shapeScales[i];
        }
        if (shapeRotations.contains(i)) {
            rotation = shapeRotations[i];
        }

        if (!text.isNull()) {
            if (textStyle.endsWith(".shx") || textStyle.endsWith(".shp")) {
                // shape:
                textStyle = textStyle.left(textStyle.length()-4);
                //qDebug() << "textStyle: " << textStyle;
                RFont* font = RFontList::get(textStyle);
                if (font) {
                    RPainterPath pp(font->getShape(text));
                    pp.setInheritPen(true);
                    //qDebug() << "scale: " << scale;
                    pp.scale(scale, scale);
                    //qDebug() << "rotate: " << rotation;
                    pp.rotate(rotation);
                    //qDebug() << "offset: " << offset;
                    pp.translate(offset.x, offset.y);
                    //qDebug() << "pp: " << pp;
                    shapes.insert(i, QList<RPainterPath>() << pp);
                }
            }
            else {
                // text:
                RTextBasedData td(
                    offset, offset,
                    scale, 0.0,
                    RS::VAlignBase, RS::HAlignLeft, RS::LeftToRight, RS::Exact,
                    1.0,
                    text,
                    textStyle,
                    false, false, rotation, true
                );
                RTextRenderer r(td, false, RTextRenderer::PainterPaths);
                r.render();
                QList<RPainterPath> pp = r.getPainterPaths();
                for (int k=0; k<pp.length(); k++) {
                    pp[k].setInheritPen(true);
                }
                shapes.insert(i, pp);
            }
        }
    }
}

double RLinetypePattern::getLargestGap() const {
    double ret = 0.0;
    for(int i=0;i<pattern.length();++i) {
//        if (RMath::isNaN(pattern[i])) {
//            continue;
//        }
        if (pattern[i]<0.0 && fabs(pattern[i])>ret) {
            ret = fabs(pattern[i]);
        }
    }
    return ret;
}

/**
 * Loads all linetype patterns in the given file into memory.
 */
QList<QPair<QString, RLinetypePattern*> > RLinetypePattern::loadAllFrom(bool metric, const QString& fileName) {
    qDebug() << "loading patterns from file: " << fileName;
    QList<QPair<QString, RLinetypePattern*> > ret;

    // Open lin file:
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() <<  "RLinetypePattern::loadAllFrom: Cannot open lin file: " <<  fileName;
        return ret;
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    QString line;
    RLinetypePattern* ltPattern = NULL;;

    // Read line by line:
    while (!ts.atEnd()) {
        line = ts.readLine();

        // handle comments (;):
        int semi = line.indexOf(';');
        if (semi==0) {
            continue;
        }

        if (semi!=-1) {
            line = line.left(semi);
        }

        // skip empty lines:
        if (line.isEmpty()) {
            continue;
        }

        // name / description:
        if (line.at(0)=='*') {
            QRegExp rx("\\*([^,]*)(?:,\\s*(.*))?", Qt::CaseSensitive, QRegExp::RegExp2);
            rx.indexIn(line);
            QString name = rx.cap(1);
            QString description = rx.cap(2);
            ltPattern = new RLinetypePattern(metric, name, description);

            // some patterns in the imperial pattern file are actually metric:
            if (!metric && name.toUpper().startsWith("ACAD_ISO")) {
                ltPattern->metric = true;
            }

            ret.append(qMakePair(name, ltPattern));
            continue;
        }

        // linetype pattern definition:
        else if (ltPattern!=NULL) {
            QStringList parts;
            QRegExp rx("\\[[^\\]]*\\]|A|([+-]?\\d+\\.?\\d*)|([+-]?\\d*\\.?\\d+)");

            int pos = 0;
            while ((pos = rx.indexIn(line, pos))!=-1) {
                parts.append(rx.cap(0));
                int l = rx.matchedLength();
                if (l==0) {
                    break;
                }
                pos += l;
            }

            qDebug() << "name: " << ltPattern->name;
            qDebug() << "parts: " << parts;

            if (parts.isEmpty()) {
                continue;
            }

            if (parts.at(0).startsWith("A", Qt::CaseInsensitive)) {
                parts.removeFirst();
            }

            QList<double> dashes;
            for (int i = 0; i < parts.length(); i++) {
                QString part = parts[i];
                if (part.startsWith("[", Qt::CaseInsensitive)) {
                    QRegExp rx(
                        "\\["
                        "([^, ]*)"   // text
                        "[, ]*"
                        "([^, ]*)"   // style
                        "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|\\d*\\.\\d+)))?"
                        "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|\\d*\\.\\d+)))?"
                        "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|\\d*\\.\\d+)))?"
                        "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|\\d*\\.\\d+)))?"
                        "\\]");
                    rx.setCaseSensitivity(Qt::CaseInsensitive);

                    rx.indexIn(part);
                    //qDebug() << "all: " << rx.capturedTexts();
                    //qDebug() << "count: " << rx.captureCount();

                    int idx = dashes.length()-1;
                    QString text = rx.cap(1);
                    if (text.startsWith("\"") && text.endsWith("\"")) {
                        text = text.mid(1, text.length()-2);
                    }
                    //qDebug() << "text: " << text;
                    ltPattern->shapeTexts.insert(idx, text);
                    ltPattern->shapeTextStyles.insert(idx, rx.cap(2));
                    for (int k=3; k+1<=rx.captureCount(); k+=2) {
                        QString c = rx.cap(k).toUpper();
                        double val = rx.cap(k+1).toDouble();

                        //qDebug() << "cap 1: " << rx.cap(k);
                        //qDebug() << "cap 2: " << rx.cap(k+1);

                        if (c=="S") {
                            ltPattern->shapeScales.insert(idx, val);
                        }
                        if (c=="R") {
                            ltPattern->shapeRotations.insert(idx, RMath::deg2rad(val));
                        }
                        if (c=="X") {
                            if (ltPattern->shapeOffsets.contains(idx)) {
                                ltPattern->shapeOffsets[idx].x = val;
                            }
                            else {
                                ltPattern->shapeOffsets.insert(idx, RVector(val, 0));
                            }
                        }
                        if (c=="Y") {
                            if (ltPattern->shapeOffsets.contains(idx)) {
                                ltPattern->shapeOffsets[idx].y = val;
                            }
                            else {
                                ltPattern->shapeOffsets.insert(idx, RVector(0, val));
                            }
                        }
                    }
                } else {
                    dashes.append(part.toDouble());
                }
            }

            if (dashes.count() > 0) {
                ltPattern->set(dashes);
                ltPattern->updateShapes();
            }
        }
    }

    return ret;
}

//QString RLinetypePattern::fixName(const QString& name) {
//    if (nameMap.isEmpty()) {
//        initNameMap();
//    }

//    QString n = name.toUpper();
//    if (nameMap.contains(n)) {
//        return nameMap.value(n);
//    }

//    if (n.endsWith(" (2x)")) {
//        QString nx2 = n+"X2";
//        nx2.replace(" ", "");
//        if (nameMap.contains(nx2)) {
//            return nameMap.value(nx2);
//        }
//    }

//    if (n.endsWith(" (.5x)")) {
//        QString n2 = n+"2";
//        n2.replace(" ", "");
//        if (nameMap.contains(n2)) {
//            return nameMap.value(n2);
//        }
//    }

//    return name;
//}

void RLinetypePattern::initNameMap() {
    nameMap.insert("BYLAYER", tr("By Layer"));
    nameMap.insert("BYBLOCK", tr("By Block"));

    nameMap.insert("BORDER", tr("Border"));
    nameMap.insert("BORDER2", tr("Border") + " (.5x)");
    nameMap.insert("BORDERX2", tr("Border") + " (2x)");

    nameMap.insert("CENTER", tr("Center"));
    nameMap.insert("CENTER2", tr("Center") + " (.5x)");
    nameMap.insert("CENTERX2", tr("Center") + " (2x)");

    nameMap.insert("DASHDOT", tr("Dash dot"));
    nameMap.insert("DASHDOT2", tr("Dash dot") + " (.5x)");
    nameMap.insert("DASHDOTX2", tr("Dash dot") + " (2x)");

    nameMap.insert("DASHED", tr("Dashed"));
    nameMap.insert("DASHED2", tr("Dashed") + " (.5x)");
    nameMap.insert("DASHEDX2", tr("Dashed") + " (2x)");

    nameMap.insert("DIVIDE", tr("Divide"));
    nameMap.insert("DIVIDE2", tr("Divide") + " (.5x)");
    nameMap.insert("DIVIDEX2", tr("Divide") + " (2x)");

    nameMap.insert("DOT", tr("Dot"));
    nameMap.insert("DOT2", tr("Dot") + " (.5x)");
    nameMap.insert("DOTX2", tr("Dot") + " (2x)");

    nameMap.insert("HIDDEN", tr("Hidden"));
    nameMap.insert("HIDDEN2", tr("Hidden") + " (.5x)");
    nameMap.insert("HIDDENX2", tr("Hidden") + " (2x)");

    nameMap.insert("PHANTOM", tr("Phantom"));
    nameMap.insert("PHANTOM2", tr("Phantom") + " (.5x)");
    nameMap.insert("PHANTOMX2", tr("Phantom") + " (2x)");

    nameMap.insert("ACAD_ISO02W100", tr("ISO dash"));
    nameMap.insert("ACAD_ISO03W100", tr("ISO dash space"));
    nameMap.insert("ACAD_ISO04W100", tr("ISO long-dash dot"));
    nameMap.insert("ACAD_ISO05W100", tr("ISO long-dash double-dot"));
    nameMap.insert("ACAD_ISO06W100", tr("ISO long-dash triple-dot"));
    nameMap.insert("ACAD_ISO07W100", tr("ISO dot"));
    nameMap.insert("ACAD_ISO08W100", tr("ISO long-dash short-dash"));
    nameMap.insert("ACAD_ISO09W100", tr("ISO long-dash double-short-dash"));
    nameMap.insert("ACAD_ISO10W100", tr("ISO dash dot"));
    nameMap.insert("ACAD_ISO11W100", tr("ISO double-dash dot"));
    nameMap.insert("ACAD_ISO12W100", tr("ISO dash double-dot"));
    nameMap.insert("ACAD_ISO13W100", tr("ISO double-dash double-dot"));
    nameMap.insert("ACAD_ISO14W100", tr("ISO dash triple-dot"));
    nameMap.insert("ACAD_ISO15W100", tr("ISO double-dash triple-dot"));

    nameMap.insert("HOT_WATER_SUPPLY", tr("Hot Water Supply"));
    nameMap.insert("HOT_WATER", tr("Hot Water Supply"));
    nameMap.insert("GAS_LINE", tr("Gas Line"));
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLinetypePattern& p) {
    dbg.nospace() << "RLinetypePattern("
    << (p.isMetric() ? "metric" : "imperial")
    << ", " << p.getName()
    << ", " << p.getDescription()
    << ", " << p.getPatternLength() << ", ";
    for (int i=0; i<p.getNumDashes(); ++i) {
        if (i!=0) {
            dbg.nospace() << ",";
        }
        dbg.nospace() << p.getDashLengthAt(i);

        bool gotShape = false;
        if (p.shapeNumbers.contains(i) || p.shapeTexts.contains(i)) {
            gotShape = true;
        }

        if (gotShape) {
            dbg.nospace() << "[";
        }
        if (p.shapeTexts.contains(i)) {
            dbg.nospace() << "text: " << p.shapeTexts.value(i);
        }
        if (p.shapeNumbers.contains(i)) {
            dbg.nospace() << ", num: " << p.shapeNumbers.value(i);
        }
        if (p.shapeTextStyles.contains(i)) {
            dbg.nospace() << ", style: " << p.shapeTextStyles.value(i);
        }
        if (p.shapeScales.contains(i)) {
            dbg.nospace() << ", scale: " << p.shapeScales.value(i);
        }
        if (p.shapeRotations.contains(i)) {
            dbg.nospace() << ", rotation: " << p.shapeRotations.value(i);
        }
        if (p.shapeOffsets.contains(i)) {
            dbg.nospace() << ", offset: " << p.shapeOffsets.value(i);
        }
        if (gotShape) {
            dbg.nospace() << "]";
        }
    }
    //dbg.nospace() << ", " << "shapes: " << p.shapes << ", ";
    dbg.nospace() << ")";
    return dbg.space();
}
