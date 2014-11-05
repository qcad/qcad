/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#include "RLinetypePattern.h"
#include "RMath.h"
#include "RDebug.h"

QMap<QString, QString> RLinetypePattern::nameMap;


RLinetypePattern::RLinetypePattern(bool metric, const QString& name, const QString& description, int num...)
    : metric(metric), name(name), description(description), symmetrical(NULL) {

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
    : metric(metric), name(name), description(description), symmetrical(NULL) {

    set(dashes);
}

RLinetypePattern::RLinetypePattern() :
    metric(true), symmetrical(NULL) {
}

RLinetypePattern::RLinetypePattern(bool metric, const QString& name, const QString& description) :
    metric(metric), name(name), description(description), symmetrical(NULL) {
}

RLinetypePattern::RLinetypePattern(const RLinetypePattern& other) :
    symmetrical(NULL) {
    operator =(other);
}

RLinetypePattern::~RLinetypePattern() {
    if (symmetrical != NULL) {
        delete[] symmetrical;
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

    pattern = dashes;

    int num = pattern.length();
    symmetrical = new bool[num];
    for (int i = 0; i < num; ++i) {
        symmetrical[i] = true;
        for (int a = 1; a < num; ++a) {
            if (fabs(pattern[ RMath::absmod((i-a), num) ]
                            - pattern[ RMath::absmod((i+a), num) ] ) > 0.1) {
                symmetrical[i] = false;
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

    if (!other.pattern.isEmpty()) {
        pattern = other.pattern;
        int num = pattern.length();
        symmetrical = new bool[num];
        for (int i = 0; i < num; ++i) {
            symmetrical[i] = other.symmetrical[i];
        }
    } else {
        pattern.clear();
        symmetrical = NULL;
    }
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
        if (symmetrical[i] != other.symmetrical[i]) {
            return false;
        }
    }

    return true;
}

void RLinetypePattern::scale(double factor) {
    for (int i = 0; i < pattern.length(); ++i) {
        pattern[i] *= factor;
    }
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
            //if (dash<RS::PointTolerance) {
            if (dash<2.0) {
                dash = 2.0;
            }
            ret << ceil(dash);
        }
    }

    return ret;
}

double RLinetypePattern::getDelta(double pos) const {
    if (pos < 0) {
        pos += (RMath::trunc(pos / getPatternLength()) + 1) * getPatternLength();
    } else if (pos > getPatternLength()) {
        pos -= RMath::trunc(pos / getPatternLength()) * getPatternLength();
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
    RLinetypePattern* ltpattern = NULL;;

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
            ltpattern = new RLinetypePattern(metric, name, description);

            // some patterns in the imperial pattern file are actually metric:
            if (!metric && name.toUpper().startsWith("ACAD_ISO")) {
                ltpattern->metric = true;
            }

            ret.append(qMakePair(name, ltpattern));
            continue;
        }

        // linetype pattern definition:
        if (ltpattern!=NULL) {
            QStringList parts = line.split(',', QString::SkipEmptyParts);
            if (parts.at(0).startsWith("A", Qt::CaseInsensitive)) {
                parts.removeFirst();
            }

            QList<double> dashes;
            for (int i = 0; i < parts.length(); i++) {
                if (parts.at(i).startsWith("[", Qt::CaseInsensitive)) {
                    dashes.clear();
                    delete ltpattern;
                    ret.removeLast();
                    break;
                } else {
                    dashes.append(parts.at(i).toDouble());
                }
            }

            if (dashes.count() > 0) {
                ltpattern->set(dashes);
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

    nameMap.insert("ACADISO02W100", tr("ISO dash"));
    nameMap.insert("ACADISO03W100", tr("ISO dash space"));
    nameMap.insert("ACADISO04W100", tr("ISO long-dash dot"));
    nameMap.insert("ACADISO05W100", tr("ISO long-dash double-dot"));
    nameMap.insert("ACADISO06W100", tr("ISO long-dash triple-dot"));
    nameMap.insert("ACADISO07W100", tr("ISO dot"));
    nameMap.insert("ACADISO08W100", tr("ISO long-dash short-dash"));
    nameMap.insert("ACADISO09W100", tr("ISO long-dash double-short-dash"));
    nameMap.insert("ACADISO10W100", tr("ISO dash dot"));
    nameMap.insert("ACADISO11W100", tr("ISO double-dash dot"));
    nameMap.insert("ACADISO12W100", tr("ISO dash double-dot"));
    nameMap.insert("ACADISO13W100", tr("ISO double-dash double-dot"));
    nameMap.insert("ACADISO14W100", tr("ISO dash triple-dot"));
    nameMap.insert("ACADISO15W100", tr("ISO double-dash triple-dot"));
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
    for (int i=0;i<p.getNumDashes();++i) {
        if (i!=0) {
            dbg.nospace() << ",";
        }
        dbg.nospace() << p.getDashLengthAt(i);
    }
    dbg.nospace() << ")";
    return dbg.space();
}
