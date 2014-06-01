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
#include "RRestrictAngleLength.h"
#include "RDocumentInterface.h"
#include "RGraphicsView.h"
#include "ROrthoGrid.h"

RVector RRestrictAngleLength::restrictSnap(const RVector& position, const RVector& relativeZero) {
    RVector ret;
    /*
    RVector retX;
    RVector retY;

    RGraphicsView* view = documentInterface.getLastKnownViewWithFocus();
    if (view==NULL) {
        return ret;
    }

    ROrthoGrid* grid = dynamic_cast<ROrthoGrid*>(view->getGrid());
    if (grid!=NULL && grid->isIsometric()) {
        double d1, d2;
        double a1, a2;

        switch (grid->getProjection()) {
        default:
        case RS::IsoTop:
            a1 = RMath::deg2rad(30);
            a2 = RMath::deg2rad(150);
            // d1 = x / cos(30):
            d1 = (position.x - relativeZero.x) / (sqrt(3.0)/2);
            d2 = -d1;
            break;
        case RS::IsoLeft:
            a1 = RMath::deg2rad(150);
            a2 = RMath::deg2rad(90);
            d1 = (position.x - relativeZero.x) / (-sqrt(3.0)/2);
            d2 = (position.y - relativeZero.y);
            break;
        case RS::IsoRight:
            a1 = RMath::deg2rad(30);
            a2 = RMath::deg2rad(90);
            d1 = (position.x - relativeZero.x) / (sqrt(3.0)/2);
            d2 = (position.y - relativeZero.y);
            break;
        }

        retX = relativeZero + RVector::createPolar(d1, a1);
        retY = relativeZero + RVector::createPolar(d2, a2);
    }
    else {
        retX = RVector(relativeZero.x, position.y);
        retY = RVector(position.x, relativeZero.y);
    }
    */

    double ang = relativeZero.getAngleTo(position);
    double len = relativeZero.getDistanceTo(position);

    double angRes = ang;
    if (fabs(angle)>RS::AngleTolerance) {
        angRes = RMath::mround((ang - baseAngle) / angle) * angle + baseAngle;
    }
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
