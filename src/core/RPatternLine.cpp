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
#include "RPatternLine.h"


RPainterPath RPatternLine::getPainterPath() const {
    RPainterPath p;

    RVector cursor(0,0);
    p.moveTo(cursor);

    // continuous:
    if (dashes.length()==0) {
        cursor += RVector::createPolar(10.0, angle);
        p.lineTo(cursor);
    }
    else {
        for (int i=0; i<dashes.length(); i++) {
            double dash = dashes[i];
            cursor += RVector::createPolar(qAbs(dash), angle);
            if (dash<0) {
                p.moveTo(cursor);
            }
            else {
                p.lineTo(cursor);
            }
        }
    }

    return p;
}

bool RPatternLine::hasDots() const {
    for (int i=0; i<dashes.length(); i++) {
        if (RMath::fuzzyCompare(dashes[i], 0.0)) {
            return true;
        }
    }
    return false;
}

/**
 * \returen Line shapes for this pattern line. No offset applied.
 */
QList<RLine> RPatternLine::getLines(bool includeDashes) const {
    QList<RLine> ret;

    RVector cursor(0,0);

    // continuous:
    if (dashes.length()==0) {
        RVector newCursor = cursor + RVector::createPolar(10.0, angle);
        ret.append(RLine(cursor, newCursor));
        cursor = newCursor;
    }
    else {
        for (int i=0; i<dashes.length(); i++) {
            double dash = dashes[i];
            RVector newCursor = cursor + RVector::createPolar(qAbs(dash), angle);
            if (dash>0) {
                ret.append(RLine(cursor, newCursor));
            }
            else {
                if (includeDashes) {
                    // dashes as invalid lines:
                    RVector sp = cursor;
                    RVector ep = newCursor;
                    sp.valid = false;
                    ep.valid = false;
                    ret.append(RLine(sp, ep));
                }
            }
            cursor = newCursor;
        }
    }

    return ret;
}

double RPatternLine::getLength() const {
    if (dashes.length()==0) {
        return 10.0;
    }
    else {
        double ret = 0.0;
        for (int i=0; i<dashes.length(); i++) {
            ret += qAbs(dashes[i]);
        }
        return ret;
    }
}

void RPatternLine::scale(double f) {
    offset *= f;
    basePoint *= f;
    for (int i=0; i<dashes.length(); i++) {
        dashes[i] *= f;
    }
}

void RPatternLine::rotate(double a) {
    //offset.rotate(a);
    basePoint.rotate(a);
    angle = RMath::getNormalizedAngle(angle+a);
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RPatternLine& p) {
    dbg.nospace() << "RPatternLine(";
    dbg.nospace() << "\tangle:" << RMath::rad2deg(p.angle);
    dbg.nospace() << "\tbase:" << p.basePoint;
    dbg.nospace() << "\toffset:" << p.offset;
    for (int i=0; i<p.dashes.length(); ++i) {
        dbg.nospace() << "\t" << p.dashes[i];
    }
    dbg.nospace() << ")";

    return dbg.space();
}
