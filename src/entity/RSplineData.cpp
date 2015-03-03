/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
#include "RSplineData.h"
#include "RSplineEntity.h"

RSplineData::RSplineData() {
}

RSplineData::RSplineData(RDocument* document, const RSplineData& data)
    : REntityData(document) {

    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RSplineData::RSplineData(const RSpline& spline) :
    RSpline(spline) {
}

RBox RSplineData::getBoundingBox(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    return RSpline::getBoundingBox();
}

QList<RVector> RSplineData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    if (countFitPoints()!=0) {
        return getFitPoints();
    }
    else {
        return getControlPoints();
    }
}

bool RSplineData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {

    bool ret = false;
    //bool periodic = isPeriodic();

    QList<RVector>::iterator it;
    for (it=controlPoints.begin(); it!=controlPoints.end(); ++it) {
        if (referencePoint.equalsFuzzy(*it)) {
            (*it) = targetPoint;
            ret = true;
        }
    }

    for (it=fitPoints.begin(); it!=fitPoints.end(); ++it) {
        if (referencePoint.equalsFuzzy(*it)) {
            (*it) = targetPoint;
            ret = true;
        }
    }

    if (ret) {
        //if (periodic) {
            //RSpline::updateTangentsPeriodic();
        //}
        RSpline::update();
    }

    return ret;
}
