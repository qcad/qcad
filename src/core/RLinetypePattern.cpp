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
#include <QIcon>

#include "RLinetypePattern.h"
#include "RMath.h"
#include "RDebug.h"

RLinetypePattern::RLinetypePattern(const QString& name, const QString& description, int num...)
    : name(name), description(description), symmetrical(NULL) {

    QList<double> dashes;

    va_list vl;
    va_start(vl, num);
    for (int i=0; i<num; ++i) {
        dashes.append(va_arg(vl, double));
    }
    va_end(vl);

    set(dashes);
}

RLinetypePattern::RLinetypePattern(const QString& name, const QString& description, const QList<double>& dashes)
    : name(name), description(description), symmetrical(NULL) {

    set(dashes);
}

RLinetypePattern::RLinetypePattern() :
    symmetrical(NULL) {
}

RLinetypePattern::RLinetypePattern(const QString& name, const QString& description) :
    name(name), description(description), symmetrical(NULL) {
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
            ret << ceil(fabs(pattern[i]));
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

QIcon RLinetypePattern::getIcon() const {
    // TODO:
    return QIcon();
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
QList<QPair<QString, RLinetypePattern*> > RLinetypePattern::loadAllFrom(const QString& fileName) {
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
            qDebug() << "loading: " << name;
            ltpattern = new RLinetypePattern(name, description);
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
                for (int i = 0; i < dashes.count(); i++) {
                    if (dashes.at(i) == 0) {
                        // subtract half of 0.1 (0.05) from previous space
                        // and following space (if any)
                        // The spaces are negative numbers so we add 0.05
                        if (i == 0) {
                            dashes.replace(i, 0.1);
                            dashes.replace(i + 1, dashes.at(i + 1) + 0.1);
                        } else if (i > 0 && i < dashes.count() - 1) {
                            dashes.replace(i - 1, dashes.at(i - 1) + 0.05);
                            dashes.replace(i, 0.1);
                            dashes.replace(i + 1, dashes.at(i + 1) + 0.05);
                        } else if (i == dashes.count() - 1) {
                            dashes.replace(i - 1, dashes.at(i - 1) + 0.1);
                            dashes.replace(i, 0.1);
                        }

                    }
                }
                ltpattern->set(dashes);
            }
        }
    }

    return ret;
}


/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLinetypePattern& p) {
    dbg.nospace() << "RLinetypePattern(" << p.getName() << ", " << p.getDescription() << ", ";
    for (int i=0;i<p.getNumDashes();++i) {
        if (i!=0) {
            dbg.nospace() << ",";
        }
        dbg.nospace() << p.getDashLengthAt(i);
    }
    dbg.nospace() << ")";
    return dbg.space();
}
