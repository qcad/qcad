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
#include <QMap>

#include "RFontList.h"
#include "RLinetypePattern.h"
#include "RMath.h"
#include "RTextData.h"
#include "RTextRenderer.h"
#include "RDebug.h"
#include "RPluginLoader.h"

QMap<QString, QString> RLinetypePattern::nameMap;


RLinetypePattern::RLinetypePattern(bool metric, const QString& name, const QString& description, int num...)
    : metric(metric), name(name), description(description), screenScale(1.0), noOffset(false) {

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
    : metric(metric), name(name), description(description), screenScale(1.0), noOffset(false) {

    set(dashes);
}

RLinetypePattern::RLinetypePattern() :
    metric(true), screenScale(1.0), noOffset(false) {
}

RLinetypePattern::RLinetypePattern(bool metric, const QString& name, const QString& description) :
    metric(metric), name(name), description(description), screenScale(1.0), noOffset(false) {
}

RLinetypePattern::RLinetypePattern(const RLinetypePattern& other) {
    operator =(other);
}

RLinetypePattern::~RLinetypePattern() {
}

void RLinetypePattern::set(const QList<double>& dashes) {
    pattern = dashes;

    // find symmetries:
    QList<double> normalizedPattern;
    for (int i=0; i<pattern.length(); i++) {
        if (i==0) {
            normalizedPattern.append(pattern[i]);
            continue;
        }

        if ((pattern[i]>=0.0 && pattern[i-1]>=0.0) ||
            (pattern[i]<0.0 && pattern[i-1]<0.0)) {

            normalizedPattern.last() += pattern[i];
            continue;
        }

        normalizedPattern.append(pattern[i]);
    }

    double normalizedPatternOffset = 0.0;
    if (normalizedPattern.length()>2) {
        if (normalizedPattern.last()>=0.0 && normalizedPattern.first()>=0) {
            normalizedPattern.first() += normalizedPattern.last();
            normalizedPatternOffset = normalizedPattern.last();
            normalizedPattern.removeLast();
        }
    }

    symmetries.clear();
    double len = getPatternLength();
    int num = normalizedPattern.length();
    for (int i=0; i<num; i++) {
        bool sym = true;
        for (int a = 1; a<num; ++a) {
            if (fabs(normalizedPattern[ RMath::absmod((i-a), num) ] - normalizedPattern[ RMath::absmod((i+a), num) ] ) > 0.1) {
                sym = false;
                break;
            }
        }

        if (sym) {
            // add middle of dash to symmetries:
            double s = getDashOffsetAt(normalizedPattern, i);
            s = s + fabs(normalizedPattern[i])/2.0;
            s = s - normalizedPatternOffset;
            if (s<0.0) {
                s = len+s;
            }
            if (s>len) {
                s = len-s;
            }
            symmetries.append(s);
        }
    }
    patternString = "";
}

RLinetypePattern& RLinetypePattern::operator=(const RLinetypePattern& other) {
    if (this == &other) {
        return *this;
    }

    metric = other.metric;
    name = other.name;
    description = other.description;
    screenScale = other.screenScale;
    noOffset = other.noOffset;
    patternString = other.patternString;
    pattern = other.pattern;
    shapes = other.shapes;
    shapeTexts = other.shapeTexts;
    shapeTextStyles = other.shapeTextStyles;
    shapeNumbers = other.shapeNumbers;
    shapeScales = other.shapeScales;
    shapeRotations = other.shapeRotations;
    shapeOffsets = other.shapeOffsets;
    symmetries = other.symmetries;
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
    }

    return true;
}

bool RLinetypePattern::operator<(const RLinetypePattern& other) const {
    QString n1 = name.toLower();
    QString n2 = other.name.toLower();
    if (n1=="bylayer") {
        return true;
    }
    if (n2=="bylayer") {
        return false;
    }

    if (n1=="byblock") {
        return true;
    }
    if (n2=="byblock") {
        return false;
    }

    if (n1=="continuous") {
        return true;
    }
    if (n2=="continuous") {
        return false;
    }

    return n1<n2;
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
    for (int i = 0; i < symmetries.length(); ++i) {
        symmetries[i] *= factor;
    }
    updateShapes();
    patternString = "";
}

/**
 * \return Line pattern that can be used for a QPen to render screen
 * optimized patterns. Empty vector for continuous.
 */
QVector<qreal> RLinetypePattern::getScreenBasedLinetype() {
    QVector<qreal> ret;

    if (pattern.length()>1) {
        for (int i = 0; i < pattern.length(); ++i) {
            double dash = fabs(pattern[i]);
            if (!metric) {
                dash*=25.4;
            }
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
    if (noOffset) {
        return 0.0;
    }

    double optOffset = 0.0;
    double gap = 0.0;
    double maxGap = RMINDOUBLE;
    for (int i = 0; i < symmetries.length(); ++i) {
        double offset = getPatternOffsetAt(length, symmetries[i], &gap, false);
        if (gap > maxGap) {
            maxGap = gap;
            optOffset = offset;
        }
    }

    return optOffset;
}

/**
 * \return Offset to use for an entity with the given length, so that
 * the given dash (index) is in the middle of the entity.
 */
double RLinetypePattern::getPatternOffsetAt(double length, double symmetryPos, double* gap, bool end) {
    Q_UNUSED(end)

    double patternLength = getPatternLength();
    if (patternLength<RS::PointTolerance) {
        return 0.0;
    }

    double offset = length / 2 - symmetryPos;
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
        total += fabs(pattern[i]);
        if (total > pos) {
            return pattern[i] > 0;
        }
    }
    qWarning("RLinetypePattern::hasDashAt: invalid pos argument");
    return false;
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

double RLinetypePattern::getScreenScale() const {
    return screenScale;
}

void RLinetypePattern::setScreenScale(double s) {
    screenScale = s;
}

bool RLinetypePattern::getNoOffset() const {
    return noOffset;
}

void RLinetypePattern::setNoOffset(bool n) {
    noOffset = n;
}

QString RLinetypePattern::getLabel() const {
    QString desc = description;
    QString preview;
    if (!description.isEmpty()) {
        int k = description.lastIndexOf(QRegExp("[^_\\. ]"));
        if (k!=-1) {
            desc = description.mid(0, k+1);
            preview = description.mid(k+1);
        }
        else {
            preview = desc;
            desc = "";
        }
    }

    if (nameMap.isEmpty()) {
        initNameMap();
    }

    QString nameUpper = name.toUpper();
    if (nameMap.contains(nameUpper)) {
        return nameMap.value(nameUpper);
    }

    return name;
}

/**
 * Set pattern based on .lin formatted string.
 * e.g. "A,3.81,[TRACK1,ltypeshp.shx,S=6.35],3.81"
 */
bool RLinetypePattern::setPatternString(const QString& patternString) {
    this->patternString = "";

    shapeNumbers.clear();
    shapeOffsets.clear();
    shapeRotations.clear();
    shapeScales.clear();
    shapeTexts.clear();
    shapeTextStyles.clear();
    shapes.clear();
    screenScale = 1.0;

    QStringList parts;
    QRegExp rx("\\[[^\\]]*\\]|A|([+-]?\\d+\\.?\\d*)|([+-]?\\d*\\.?\\d+)");

    int pos = 0;
    while ((pos = rx.indexIn(patternString, pos))!=-1) {
        parts.append(rx.cap(0));
        int l = rx.matchedLength();
        if (l==0) {
            break;
        }
        pos += l;
    }

    if (parts.isEmpty()) {
        return false;
    }

    if (parts.at(0).startsWith("A", Qt::CaseInsensitive)) {
        parts.removeFirst();
    }

    QList<double> dashes;
    for (int i = 0; i < parts.length(); i++) {
        QString part = parts[i];
        if (part.startsWith("[", Qt::CaseInsensitive)) {
            if (!RPluginLoader::hasPlugin("DWG")) {
                return false;
            }

            QRegExp rx(
                "\\["
                "([^, ]*)"   // text
                "[, ]*"
                "([^, ]*)"   // style
                "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|[+-]?\\d*\\.\\d+)))?"
                "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|[+-]?\\d*\\.\\d+)))?"
                "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|[+-]?\\d*\\.\\d+)))?"
                "(?:[, ]*([SRXYA])[^=]*=(?:([+-]?\\d+\\.?\\d*|[+-]?\\d*\\.\\d+)))?"
                "\\]"
            );
            rx.setCaseSensitivity(Qt::CaseInsensitive);

            rx.indexIn(part);

            int idx = dashes.length()-1;
            QString text = rx.cap(1);
            if (text.startsWith("\"") && text.endsWith("\"")) {
                text = text.mid(1, text.length()-2);
            }
            shapeTexts.insert(idx, text);
            shapeTextStyles.insert(idx, rx.cap(2));
            for (int k=3; k+1<=rx.captureCount(); k+=2) {
                QString c = rx.cap(k).toUpper();
                double val = rx.cap(k+1).toDouble();

                if (c=="S") {
                    shapeScales.insert(idx, val);
                }
                if (c=="R") {
                    shapeRotations.insert(idx, RMath::deg2rad(val));
                }
                if (c=="X") {
                    if (shapeOffsets.contains(idx)) {
                        shapeOffsets[idx].x = val;
                    }
                    else {
                        shapeOffsets.insert(idx, RVector(val, 0));
                    }
                }
                if (c=="Y") {
                    if (shapeOffsets.contains(idx)) {
                        shapeOffsets[idx].y = val;
                    }
                    else {
                        shapeOffsets.insert(idx, RVector(0, val));
                    }
                }
            }
        } else {
            dashes.append(part.toDouble());
        }
    }

    if (dashes.count() > 0) {
        set(dashes);
        updateShapes();
    }

    this->patternString = patternString;

    return true;
}

QString RLinetypePattern::getPatternString() const {
    if (patternString.isEmpty()) {
        QString buffer = "A"; //(isScaledToFit() ? "S" : "A");
        for (int i=0; i < getNumDashes(); i++) {
            buffer += "," + QString("%1").arg(getDashLengthAt(i));

            int shapeNumber  = getShapeNumberAt(i);
            QString text = getShapeTextAt(i);
            QString textStyle = getShapeTextStyleAt(i);

            if (shapeNumber==0 && text.isEmpty()) {
                continue;
            }

            if (shapeNumber!=0) {
                buffer += ",[";
                buffer +=  QString("%1").arg(shapeNumber);
                buffer += ",";
                if (!textStyle.isEmpty()) {
                    buffer += textStyle;
                }
                else {
                    buffer += "NULL style";
                }
            }
            else {
                buffer += ",[\"";
                buffer += text;
                buffer += "\",";
                if (!textStyle.isEmpty()) {
                    buffer += textStyle;
                }
                else {
                    buffer += "NULL style";
                }
            }
            if (fabs(getShapeScaleAt(i))>RS::PointTolerance) {
                buffer += ",S=";
                buffer += QString("%1").arg(getShapeScaleAt(i));
            }
            if (fabs(getShapeRotationAt(i))) {
                buffer += ",R=";
                buffer += QString("%1").arg(RMath::rad2deg(getShapeRotationAt(i)));
            }
            if (fabs(getShapeOffsetAt(i).x)>RS::PointTolerance) {
                buffer += ",X=";
                buffer += QString("%1").arg(getShapeOffsetAt(i).x);
            }
            if (fabs(getShapeOffsetAt(i).y)>RS::PointTolerance) {
                buffer += ",Y=";
                buffer += QString("%1").arg(getShapeOffsetAt(i).y);
            }
            buffer += "]";
        }
        patternString = buffer;
    }

    return patternString;
}

QList<double> RLinetypePattern::getPattern() const {
    return pattern;
}

double RLinetypePattern::getPatternLength() const {
    double ret=0.0;
    for (int i=0; i<pattern.length(); ++i) {
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

double RLinetypePattern::getDashOffsetAt(const QList<double>& dashes, int i) const {
    double ret = 0.0;

    if (i<0 || i>=dashes.length()) {
        return ret;
    }

    for (int k=0; k<i; k++) {
        ret += fabs(dashes[k]);
    }
    return ret;
}

bool RLinetypePattern::hasShapeNumberAt(int i) const {
    return shapeNumbers.contains(i);
}

int RLinetypePattern::getShapeNumberAt(int i) const {
    if (!shapeNumbers.contains(i)) {
        return 0;
    }
    return shapeNumbers[i];
}

void RLinetypePattern::setShapeNumberAt(int i, int num) {
    shapeNumbers.insert(i, num);
    patternString = "";
}

bool RLinetypePattern::hasShapeScaleAt(int i) const {
    return shapeScales.contains(i);
}

double RLinetypePattern::getShapeScaleAt(int i) const {
    if (!shapeScales.contains(i)) {
        return 0.0;
    }
    return shapeScales[i];
}

void RLinetypePattern::setShapeScaleAt(int i, double s) {
    shapeScales.insert(i, s);
    patternString = "";
}

bool RLinetypePattern::hasShapeRotationAt(int i) const {
    return shapeRotations.contains(i);
}

double RLinetypePattern::getShapeRotationAt(int i) const {
    if (!shapeRotations.contains(i)) {
        return 0.0;
    }
    return shapeRotations[i];
}

void RLinetypePattern::setShapeRotationAt(int i, double r) {
    shapeRotations.insert(i, r);
    patternString = "";
}

bool RLinetypePattern::hasShapeOffsetAt(int i) const {
    return shapeOffsets.contains(i);
}

RVector RLinetypePattern::getShapeOffsetAt(int i) const {
    if (!shapeOffsets.contains(i)) {
        return RVector(0,0);
    }
    return shapeOffsets[i];
}

void RLinetypePattern::setShapeOffsetAt(int i, const RVector& offset) {
    shapeOffsets.insert(i, offset);
    patternString = "";
}

bool RLinetypePattern::hasShapeTextAt(int i) const {
    return shapeTexts.contains(i);
}

QString RLinetypePattern::getShapeTextAt(int i) const {
    if (!shapeTexts.contains(i)) {
        return QString();
    }
    return shapeTexts[i];
}

void RLinetypePattern::setShapeTextAt(int i, const QString& t) {
    shapeTexts.insert(i, t);
    patternString = "";
}

bool RLinetypePattern::hasShapeTextStyleAt(int i) const {
    return shapeTextStyles.contains(i);
}

QString RLinetypePattern::getShapeTextStyleAt(int i) const {
    if (!shapeTextStyles.contains(i)) {
        return QString();
    }
    return shapeTextStyles[i];
}

void RLinetypePattern::setShapeTextStyleAt(int i, const QString& t) {
    shapeTextStyles.insert(i, t);
    patternString = "";
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

/**
 * Updates the painter paths for the shapes in this pattern.
 */
void RLinetypePattern::updateShapes() {
    shapes.clear();

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

        // linetype pattern definition ("A,3.81,[TRACK1,ltypeshp.shx,S=6.35],3.81"):
        else if (ltPattern!=NULL) {
            if (!ltPattern->setPatternString(line)) {
                ret.removeLast();
                delete ltPattern;
                ltPattern = NULL;
            }
        }
    }

    return ret;
}

void RLinetypePattern::initNameMap() {
    nameMap.insert("BYLAYER", tr("By Layer"));
    nameMap.insert("BYBLOCK", tr("By Block"));
    nameMap.insert("CONTINUOUS", tr("Continuous"));

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
    nameMap.insert("HOT_WATER", tr("Hot Water"));
    nameMap.insert("GAS_LINE", tr("Gas Line"));
    nameMap.insert("BATTING", tr("Batting"));
    nameMap.insert("ZIGZAG", tr("Zig Zag"));
    nameMap.insert("TRACKS", tr("Tracks"));
    nameMap.insert("FENCELINE1", tr("Fenceline 1"));
    nameMap.insert("FENCELINE2", tr("Fenceline 2"));

    nameMap.insert("DRAINAGE", tr("Drainage"));
    nameMap.insert("DRAINAGE2", tr("Drainage Reversed"));
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLinetypePattern& p) {
    dbg.nospace() << "RLinetypePattern("
    << (p.isMetric() ? "metric" : "imperial")
    << ", " << p.getName()
    << ", " << p.getDescription()
    << ", string: " << p.getPatternString() << ", "
    << ", length: " << p.getPatternLength() << ", "
    << ", dashes: " << p.getNumDashes() << ", ";
    for (int i=0; i<p.getNumDashes(); ++i) {
        if (i!=0) {
            dbg.nospace() << ",";
        }
        dbg.nospace() << p.getDashLengthAt(i);

        bool gotShape = false;
        if (p.hasShapeNumberAt(i) || p.hasShapeTextAt(i)) {
            gotShape = true;
        }

        if (gotShape) {
            dbg.nospace() << "[";
        }
        if (p.hasShapeTextAt(i)) {
            dbg.nospace() << "text: " << p.getShapeTextAt(i);
        }
        if (p.hasShapeNumberAt(i)) {
            dbg.nospace() << ", num: " << p.getShapeNumberAt(i);
        }
        if (p.hasShapeTextStyleAt(i)) {
            dbg.nospace() << ", style: " << p.getShapeTextStyleAt(i);
        }
        if (p.hasShapeScaleAt(i)) {
            dbg.nospace() << ", scale: " << p.getShapeScaleAt(i);
        }
        if (p.hasShapeRotationAt(i)) {
            dbg.nospace() << ", rotation: " << p.getShapeRotationAt(i);
        }
        if (p.hasShapeOffsetAt(i)) {
            dbg.nospace() << ", offset: " << p.getShapeOffsetAt(i);
        }
        if (gotShape) {
            dbg.nospace() << "]";
        }
    }
    dbg.nospace() << "\nsymmetries: " << p.getSymmetries();
    dbg.nospace() << ")";
    return dbg.space();
}
