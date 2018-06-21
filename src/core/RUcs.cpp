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
#include "RUcs.h"
#include "RLine.h"
#include "RTriangle.h"

RPropertyTypeId RUcs::PropertyName;

RPropertyTypeId RUcs::PropertyOriginX;
RPropertyTypeId RUcs::PropertyOriginY;
RPropertyTypeId RUcs::PropertyOriginZ;

RPropertyTypeId RUcs::PropertyXAxisDirectionX;
RPropertyTypeId RUcs::PropertyXAxisDirectionY;
RPropertyTypeId RUcs::PropertyXAxisDirectionZ;

RPropertyTypeId RUcs::PropertyYAxisDirectionX;
RPropertyTypeId RUcs::PropertyYAxisDirectionY;
RPropertyTypeId RUcs::PropertyYAxisDirectionZ;

void RUcs::init() {
    RUcs::PropertyName.generateId(typeid(RUcs), "", "Name");

    RUcs::PropertyOriginX.generateId(typeid(RUcs), "Origin", "X");
    RUcs::PropertyOriginY.generateId(typeid(RUcs), "Origin", "Y");
    RUcs::PropertyOriginZ.generateId(typeid(RUcs), "Origin", "Z");

    RUcs::PropertyXAxisDirectionX.generateId(typeid(RUcs), "X Axis", "X");
    RUcs::PropertyXAxisDirectionY.generateId(typeid(RUcs), "X Axis", "Y");
    RUcs::PropertyXAxisDirectionZ.generateId(typeid(RUcs), "X Axis", "Z");

    RUcs::PropertyYAxisDirectionX.generateId(typeid(RUcs), "Y Axis", "X");
    RUcs::PropertyYAxisDirectionY.generateId(typeid(RUcs), "Y Axis", "Y");
    RUcs::PropertyYAxisDirectionZ.generateId(typeid(RUcs), "Y Axis", "Z");
}

bool RUcs::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {
    Q_UNUSED(transaction);

    bool ret = false;
    ret = RObject::setMember(name, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(origin.x, value, PropertyOriginX  == propertyTypeId);
    ret = ret || RObject::setMember(origin.y, value, PropertyOriginY  == propertyTypeId);
    ret = ret || RObject::setMember(origin.z, value, PropertyOriginZ  == propertyTypeId);
    ret = ret || RObject::setMember(xAxisDirection.x, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(xAxisDirection.y, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(xAxisDirection.z, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(yAxisDirection.x, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(yAxisDirection.y, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(yAxisDirection.z, value, PropertyName == propertyTypeId);
    return ret;
}

QPair<QVariant, RPropertyAttributes> RUcs::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyOriginX) {
        return qMakePair(QVariant(origin.x), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyOriginY) {
        return qMakePair(QVariant(origin.y), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyOriginZ) {
        return qMakePair(QVariant(origin.z), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyXAxisDirectionX) {
        return qMakePair(QVariant(xAxisDirection.x), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyXAxisDirectionY) {
        return qMakePair(QVariant(xAxisDirection.y), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyXAxisDirectionZ) {
        return qMakePair(QVariant(xAxisDirection.z), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyYAxisDirectionX) {
        return qMakePair(QVariant(yAxisDirection.x), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyYAxisDirectionY) {
        return qMakePair(QVariant(yAxisDirection.y), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyYAxisDirectionZ) {
        return qMakePair(QVariant(yAxisDirection.z), RPropertyAttributes());
    }

    //return qMakePair(QVariant(), RPropertyAttributes());
    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


/**
 * \return Vector that indicates the direction of the Z-Axis
 * (orthogonal to the XY plane).
 */
RVector RUcs::getZAxisDirection() {
    return RVector::getCrossProduct(xAxisDirection, yAxisDirection);
}



/**
 * Maps the given UCS (user coordinate system) position to an
 * absolute WCS (world coordinate system) position.
 */
RVector RUcs::mapFromUcs(const RVector& positionUcs) {
    return origin
         + xAxisDirection.getUnitVector() * positionUcs.x
         + yAxisDirection.getUnitVector() * positionUcs.y
         + getZAxisDirection().getUnitVector() * positionUcs.z;
}



/**
 * Maps the given WCS position to a UCS position.
 */
RVector RUcs::mapToUcs(const RVector& positionWcs) {
    // normal of UCS XY plane in WCS:
    RVector normal = getZAxisDirection();

    // a ray from the WCS position in the direction of the UCS plane normal:
    RLine ray(positionWcs, positionWcs + normal);

    // the UCS XY plane as a WCS triangle:
    RTriangle plane(origin, origin + xAxisDirection, origin + yAxisDirection);

    // the Z coordinate of the result is the distance of the given position to the
    // XY plane:
    double z = plane.getDistanceTo(positionWcs, false);

    // find intersection point of ray with XY plane:
//    QList<RVector> res = plane.getIntersectionPoints(ray, false);
    QList<RVector> res = RShape::getIntersectionPoints(plane, ray, false);
    if (res.size()==0) {
        qDebug("RUcs::mapToUcs: no intersection between plane and normal");
        return RVector();
    }

    // intersection point of ray with XY plane:
    RVector onPlane = res.front();

    // find absolute value of X as distance of given position to Y axis of this UCS:
    RLine yAxisUcs(origin, origin + yAxisDirection);
    double x = yAxisUcs.getDistanceTo(onPlane, false);

    // find absolute value of Y as distance of given position to X axis of this UCS:
    RLine xAxisUcs(origin, origin + xAxisDirection);
    double y = xAxisUcs.getDistanceTo(onPlane, false);

    // determine sign of X/Y coordinates:
    if (RTriangle(origin, origin-xAxisDirection, origin+yAxisDirection).isPointInQuadrant(onPlane)) {
        return RVector(-x, y, z);
    }
    else if (RTriangle(origin, origin-xAxisDirection, origin-yAxisDirection).isPointInQuadrant(onPlane)) {
        return RVector(-x, -y, z);
    }
    else if (RTriangle(origin, origin+xAxisDirection, origin-yAxisDirection).isPointInQuadrant(onPlane)) {
        return RVector(x, -y, z);
    }
    else {
        return RVector(x, y, z);
    }
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RUcs& u) {
    dbg.nospace() << "RUcs(" << u.name << ", " << u.origin << ", " << u.xAxisDirection << ", " << u.yAxisDirection << ")";
    return dbg.space();
}
