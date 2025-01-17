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
#include "RDimAngularData.h"

RDimAngularData::RDimAngularData() {
}

RDimAngularData::RDimAngularData(RDocument* document, const RDimAngularData& data)
    : RDimensionData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

/**
 * \param definitionPoint Definition point is extensionLine2End.
 */
RDimAngularData::RDimAngularData(const RDimensionData& dimData)
    : RDimensionData(dimData) {

}

bool RDimAngularData::isValid() const {
    return RDimensionData::isValid() &&
            getExtensionLine1End().isValid() &&
            getExtensionLine2End().isValid() &&
            getDimArcPosition().isValid();
}

bool RDimAngularData::isSane() const {
    return RDimensionData::isSane() &&
            getExtensionLine1End().isSane() &&
            getExtensionLine2End().isSane() &&
            getDimArcPosition().isSane();
}

QList<RRefPoint> RDimAngularData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret = RDimensionData::getReferencePoints(hint);

    ret.append(getTextPosition());
    ret.append(getExtensionLine1End());
    ret.append(getExtensionLine2End());
    ret.append(getDimArcPosition());

    return ret;
}

bool RDimAngularData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    if (referencePoint.equalsFuzzy(getExtensionLine1End())) {
        setExtensionLine1End(targetPoint);
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(getExtensionLine2End())) {
        setExtensionLine2End(targetPoint);
        autoTextPos = true;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(getDimArcPosition())) {
        setDimArcPosition(targetPoint);
        autoTextPos = true;
        ret = true;
    }

    if (!ret) {
        ret = RDimensionData::moveReferencePoint(referencePoint, targetPoint, modifiers);
    }

    if (ret) {
        update();
    }

    return ret;
}

/**
 * \return Angle of the measured dimension.
 */
double RDimAngularData::getAngle() const {
    double ang1 = 0.0;
    double ang2 = 0.0;
    bool reversed = false;
    RVector p1;
    RVector p2;

    getAngles(ang1, ang2, reversed, p1, p2);

    //bool dimArcLength = (getType()==RS::EntityDimArcLength);

    double ret;
    if (!reversed) {
        if (ang2<ang1) {
            ang2+=2*M_PI;
        }
        ret = ang2-ang1;
    } else {
        if (ang1<ang2) {
            ang1+=2*M_PI;
        }
        ret = ang1-ang2;
    }
    return ret;
}

double RDimAngularData::getMeasuredValue() const {
    return getAngle();
}

QString RDimAngularData::getAutoLabel() const {
    return formatAngleLabel(getMeasuredValue());
}

RArc RDimAngularData::getDimensionArc() const {
    RVector center = getCenter();
    double radius = center.getDistanceTo(getDimArcPosition());
    double ang1, ang2;
    bool reversed;
    RVector p1, p2;
    getAngles(ang1, ang2, reversed, p1, p2);
    return RArc(center, radius, ang1, ang2, reversed);
}
