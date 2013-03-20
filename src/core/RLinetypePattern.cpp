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
#include "RLinetypePattern.h"

#include "RMath.h"
#include "RDebug.h"

RLinetypePattern::RLinetypePattern(int num...)
    :num(0), pattern(NULL), symmetrical(NULL) {

    QList<double> dashes;

    va_list vl;
    va_start(vl, num);
    for (int i=0; i<num; ++i) {
        dashes.append(va_arg(vl, double));
    }
    va_end(vl);

    set(dashes);
}

void RLinetypePattern::set(const QList<double> dashes) {
    if (pattern!=NULL) {
        delete[] pattern;
    }
    if (symmetrical != NULL) {
        delete[] symmetrical;
    }

    num = dashes.count();
    pattern = new double[num];
    for (int i=0; i<num; ++i) {
        pattern[i] = dashes[i];
    }

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

RLinetypePattern::RLinetypePattern() :
    num(-1), pattern(NULL), symmetrical(NULL) {
}

RLinetypePattern::RLinetypePattern(const RLinetypePattern& other) :
    num(-1), pattern(NULL), symmetrical(NULL) {
    operator =(other);
}

RLinetypePattern::~RLinetypePattern() {
    if (pattern != NULL) {
        delete[] pattern;
    }
    if (symmetrical != NULL) {
        delete[] symmetrical;
    }
}

RLinetypePattern& RLinetypePattern::operator=(const RLinetypePattern& other) {
    if (this == &other) {
        return *this;
    }

    if (pattern != NULL) {
        delete pattern;
    }
    if (symmetrical != NULL) {
        delete symmetrical;
    }

    num = other.num;
    if (num > 0) {
        pattern = new double[num];
        symmetrical = new bool[num];
        for (int i = 0; i < num; ++i) {
            pattern[i] = other.pattern[i];
            symmetrical[i] = other.symmetrical[i];
        }
    } else {
        pattern = NULL;
        symmetrical = NULL;
    }
    return *this;
}

void RLinetypePattern::scale(double factor) {
    for (int i = 0; i < num; ++i) {
        pattern[i] *= factor;
    }
}

double RLinetypePattern::getDelta(double pos) const {
    if (pos < 0) {
        pos += (RMath::trunc(pos / getPatternLength()) + 1) * getPatternLength();
    } else if (pos > getPatternLength()) {
        pos -= RMath::trunc(pos / getPatternLength()) * getPatternLength();
    }
    double total = 0.0;
    for (int i = 0; i < num; ++i) {
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
    for (int i = 0; i < num; ++i) {
        total += fabs(pattern[i]);
        if (total > pos) {
            return pattern[i] > 0;
        }
    }
    qWarning("RLinetypePattern::hasDashAt: invalid pos argument");
    return false;
}

bool RLinetypePattern::isSymmetrical(int i) const {
    if (i >= num) {
        return false;
    }
    return symmetrical[i];
    //  if (num == 2) {
    //      return true;
    //  }
    //  if (num == 4) {
    //      return (i % 2) == 0;
    //  }
    //  return true;
}

bool RLinetypePattern::isValid() const {
    return num>0;
}

int RLinetypePattern::getNumDashes() const {
    return num;
}

double RLinetypePattern::getPatternLength() const {
    double ret=0;
    for(int i=0;i<num;++i) {
        ret += fabs(pattern[i]);
    }
    return ret;
}

double RLinetypePattern::getDashLengthAt(int i) const {
    if (i>=0 && i<num) {
        return pattern[i];
    }
    return 0.0;
}

double RLinetypePattern::getLargestGap() const {
    double ret = 0.0;
    for(int i=0;i<num;++i) {
        if (pattern[i]<0.0 && fabs(pattern[i])>ret) {
            ret = fabs(pattern[i]);
        }
    }
    return ret;
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLinetypePattern& p) {
    dbg.nospace() << "RLinetypePattern(";
    for(int i=0;i<p.getNumDashes();++i) {
        if (i!=0) {
            dbg.nospace() << ",";
        }
        dbg.nospace() << p.getDashLengthAt(i);
    }
    dbg.nospace() << ")";
    return dbg.space();
}
