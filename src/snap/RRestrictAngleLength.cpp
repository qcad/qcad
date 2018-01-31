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
#include "RRestrictAngleLength.h"
#include "RDocumentInterface.h"
#include "RGraphicsView.h"
#include "ROrthoGrid.h"

RVector RRestrictAngleLength::restrictSnap(const RVector& position, const RVector& relativeZero) {
    RVector ret;

    double ang = relativeZero.getAngleTo(position);
    double angRes = ang;
    if (fabs(angle)>RS::AngleTolerance) {
        angRes = RMath::mround((ang - baseAngle) / angle) * angle + baseAngle;
    }

    RVector rPos = position;
    if (mode==RRestrictAngleLength::AngleLength || mode==RRestrictAngleLength::Angle) {
        RLine line(relativeZero, relativeZero + RVector::createPolar(100.0, angRes));
        rPos = line.getClosestPointOnShape(position, false);
    }

    double len = relativeZero.getDistanceTo(rPos);
    double lenRes = len;
    if (fabs(length)>RS::PointTolerance) {
        lenRes = RMath::mround((len - baseLength) / length) * length + baseLength;
    }

    switch (mode) {
    case RRestrictAngleLength::None:
        ret = position;
        break;
    case RRestrictAngleLength::AngleLength:
        ret = relativeZero + RVector::createPolar(lenRes, angRes);
        break;
    case RRestrictAngleLength::Angle:
        ret = relativeZero + RVector::createPolar(len, angRes);
        break;
    case RRestrictAngleLength::Length:
        ret = relativeZero + RVector::createPolar(lenRes, ang);
        break;
    }

    lastSnap = ret;

    return ret;
}
