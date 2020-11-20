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
#include "RRayEntity.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RRayEntity::PropertyCustom;
RPropertyTypeId RRayEntity::PropertyHandle;
RPropertyTypeId RRayEntity::PropertyProtected;
RPropertyTypeId RRayEntity::PropertyWorkingSet;
RPropertyTypeId RRayEntity::PropertyType;
RPropertyTypeId RRayEntity::PropertyBlock;
RPropertyTypeId RRayEntity::PropertyLayer;
RPropertyTypeId RRayEntity::PropertyLinetype;
RPropertyTypeId RRayEntity::PropertyLinetypeScale;
RPropertyTypeId RRayEntity::PropertyLineweight;
RPropertyTypeId RRayEntity::PropertyColor;
RPropertyTypeId RRayEntity::PropertyDisplayedColor;
RPropertyTypeId RRayEntity::PropertyDrawOrder;

RPropertyTypeId RRayEntity::PropertyBasePointX;
RPropertyTypeId RRayEntity::PropertyBasePointY;
RPropertyTypeId RRayEntity::PropertyBasePointZ;
RPropertyTypeId RRayEntity::PropertySecondPointX;
RPropertyTypeId RRayEntity::PropertySecondPointY;
RPropertyTypeId RRayEntity::PropertySecondPointZ;

RPropertyTypeId RRayEntity::PropertyDirectionX;
RPropertyTypeId RRayEntity::PropertyDirectionY;
RPropertyTypeId RRayEntity::PropertyDirectionZ;

RPropertyTypeId RRayEntity::PropertyAngle;
RPropertyTypeId RRayEntity::PropertyFixedAngle;


RRayEntity::RRayEntity(RDocument* document, const RRayData& data) :
    REntity(document), data(document, data) {
}

RRayEntity::~RRayEntity() {
}

void RRayEntity::setShape(const RRay& r) {
    data.setBasePoint(r.getBasePoint());
    data.setSecondPoint(r.getSecondPoint());
}

void RRayEntity::init() {
    RRayEntity::PropertyCustom.generateId(typeid(RRayEntity), RObject::PropertyCustom);
    RRayEntity::PropertyHandle.generateId(typeid(RRayEntity), RObject::PropertyHandle);
    RRayEntity::PropertyProtected.generateId(typeid(RRayEntity), RObject::PropertyProtected);
    RRayEntity::PropertyWorkingSet.generateId(typeid(RRayEntity), RObject::PropertyWorkingSet);
    RRayEntity::PropertyType.generateId(typeid(RRayEntity), REntity::PropertyType);
    RRayEntity::PropertyBlock.generateId(typeid(RRayEntity), REntity::PropertyBlock);
    RRayEntity::PropertyLayer.generateId(typeid(RRayEntity), REntity::PropertyLayer);
    RRayEntity::PropertyLinetype.generateId(typeid(RRayEntity), REntity::PropertyLinetype);
    RRayEntity::PropertyLinetypeScale.generateId(typeid(RRayEntity), REntity::PropertyLinetypeScale);
    RRayEntity::PropertyLineweight.generateId(typeid(RRayEntity), REntity::PropertyLineweight);
    RRayEntity::PropertyColor.generateId(typeid(RRayEntity), REntity::PropertyColor);
    RRayEntity::PropertyDisplayedColor.generateId(typeid(RRayEntity), REntity::PropertyDisplayedColor);
    RRayEntity::PropertyDrawOrder.generateId(typeid(RRayEntity), REntity::PropertyDrawOrder);

    RRayEntity::PropertyBasePointX.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Base Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RRayEntity::PropertyBasePointY.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Base Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RRayEntity::PropertyBasePointZ.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Base Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RRayEntity::PropertySecondPointX.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Second Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RRayEntity::PropertySecondPointY.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Second Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RRayEntity::PropertySecondPointZ.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Second Point"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RRayEntity::PropertyDirectionX.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Direction Vector"), QT_TRANSLATE_NOOP("REntity", "X"));
    RRayEntity::PropertyDirectionY.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Direction Vector"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RRayEntity::PropertyDirectionZ.generateId(typeid(RRayEntity), QT_TRANSLATE_NOOP("REntity", "Direction Vector"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RRayEntity::PropertyAngle.generateId(typeid(RRayEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
    RRayEntity::PropertyFixedAngle.generateId(typeid(RRayEntity), "", QT_TRANSLATE_NOOP("REntity", "Fixed Angle"));
}

bool RRayEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.basePoint.x, value, PropertyBasePointX == propertyTypeId);
    ret = ret || RObject::setMember(data.basePoint.y, value, PropertyBasePointY == propertyTypeId);
    ret = ret || RObject::setMember(data.basePoint.z, value, PropertyBasePointZ == propertyTypeId);
    ret = ret || RObject::setMember(data.directionVector.x, value, PropertyDirectionX == propertyTypeId);
    ret = ret || RObject::setMember(data.directionVector.y, value, PropertyDirectionY == propertyTypeId);
    ret = ret || RObject::setMember(data.directionVector.z, value, PropertyDirectionZ == propertyTypeId);

    if (propertyTypeId == PropertySecondPointX) {
        RVector v = data.getSecondPoint();
        v.x = value.toDouble();
        data.setSecondPoint(v);
        ret = true;
    } else if (propertyTypeId == PropertySecondPointY) {
        RVector v = data.getSecondPoint();
        v.y = value.toDouble();
        data.setSecondPoint(v);
        ret = true;
    } else if (propertyTypeId == PropertySecondPointZ) {
        RVector v = data.getSecondPoint();
        v.z = value.toDouble();
        data.setSecondPoint(v);
        ret = true;
    }

    else if (propertyTypeId==PropertyAngle) {
        data.setAngle(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyFixedAngle) {
        data.setFixedAngle(value.toBool());
        ret = true;
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RRayEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {

    RPropertyAttributes attFixedAngle;
    attFixedAngle.setReadOnly(data.fixedAngle);

    if (propertyTypeId == PropertyBasePointX) {
        return qMakePair(QVariant(data.basePoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyBasePointY) {
        return qMakePair(QVariant(data.basePoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyBasePointZ) {
        return qMakePair(QVariant(data.basePoint.z), RPropertyAttributes());
    }

    else if (propertyTypeId == PropertyDirectionX) {
        return qMakePair(QVariant(data.directionVector.x), attFixedAngle);
    } else if (propertyTypeId == PropertyDirectionY) {
        return qMakePair(QVariant(data.directionVector.y), attFixedAngle);
    } else if (propertyTypeId == PropertyDirectionZ) {
        return qMakePair(QVariant(data.directionVector.z), attFixedAngle);
    }

    else if (propertyTypeId == PropertySecondPointX) {
        attFixedAngle.setRedundant(true);
        return qMakePair(QVariant(data.getSecondPoint().x), attFixedAngle);
    } else if (propertyTypeId == PropertySecondPointY) {
        attFixedAngle.setRedundant(true);
        return qMakePair(QVariant(data.getSecondPoint().y), attFixedAngle);
    } else if (propertyTypeId == PropertySecondPointZ) {
        attFixedAngle.setRedundant(true);
        return qMakePair(QVariant(data.getSecondPoint().z), attFixedAngle);
    }

    else if (propertyTypeId==PropertyAngle) {
        return qMakePair(QVariant(data.getAngle()), RPropertyAttributes(RPropertyAttributes::Angle|RPropertyAttributes::Redundant));
    }
    else if (propertyTypeId==PropertyFixedAngle) {
        return qMakePair(QVariant(data.fixedAngle), RPropertyAttributes());
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RRayEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.setBrush(Qt::NoBrush);
    e.exportRay(data);
}

void RRayEntity::print(QDebug dbg) const {
    dbg.nospace() << "RRayEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", startPoint: " << getBasePoint() << ", endPoint: "
            << getSecondPoint() << ")";
}
