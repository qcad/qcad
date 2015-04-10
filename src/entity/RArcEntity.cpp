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
#include "RArcEntity.h"
#include "RExporter.h"
#include "RPoint.h"

RPropertyTypeId RArcEntity::PropertyCustom;
RPropertyTypeId RArcEntity::PropertyHandle;
RPropertyTypeId RArcEntity::PropertyType;
RPropertyTypeId RArcEntity::PropertyBlock;
RPropertyTypeId RArcEntity::PropertyLayer;
RPropertyTypeId RArcEntity::PropertyLinetype;
RPropertyTypeId RArcEntity::PropertyLinetypeScale;
RPropertyTypeId RArcEntity::PropertyLineweight;
RPropertyTypeId RArcEntity::PropertyColor;
RPropertyTypeId RArcEntity::PropertyDrawOrder;

RPropertyTypeId RArcEntity::PropertyCenterX;
RPropertyTypeId RArcEntity::PropertyCenterY;
RPropertyTypeId RArcEntity::PropertyCenterZ;
RPropertyTypeId RArcEntity::PropertyRadius;
RPropertyTypeId RArcEntity::PropertyStartAngle;
RPropertyTypeId RArcEntity::PropertyEndAngle;
RPropertyTypeId RArcEntity::PropertyReversed;

RPropertyTypeId RArcEntity::PropertyDiameter;
RPropertyTypeId RArcEntity::PropertyLength;
RPropertyTypeId RArcEntity::PropertySweepAngle;
RPropertyTypeId RArcEntity::PropertyArea;

RArcEntity::RArcEntity(RDocument* document, const RArcData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
    RDebug::incCounter("RArcEntity");
}

RArcEntity::RArcEntity(const RArcEntity& other) : REntity(other) {
    RDebug::incCounter("RArcEntity");
    data = other.data;
}

RArcEntity::~RArcEntity() {
    RDebug::decCounter("RArcEntity");
}

void RArcEntity::setShape(const RArc& a) {
    data.setCenter(a.getCenter());
    data.setRadius(a.getRadius());
    data.setStartAngle(a.getStartAngle());
    data.setEndAngle(a.getEndAngle());
    data.setReversed(a.isReversed());
}

void RArcEntity::init() {
    RArcEntity::PropertyCustom.generateId(typeid(RArcEntity), RObject::PropertyCustom);
    RArcEntity::PropertyHandle.generateId(typeid(RArcEntity), RObject::PropertyHandle);
    RArcEntity::PropertyType.generateId(typeid(RArcEntity), REntity::PropertyType);
    RArcEntity::PropertyBlock.generateId(typeid(RArcEntity), REntity::PropertyBlock);
    RArcEntity::PropertyLayer.generateId(typeid(RArcEntity), REntity::PropertyLayer);
    RArcEntity::PropertyLinetype.generateId(typeid(RArcEntity), REntity::PropertyLinetype);
    RArcEntity::PropertyLinetypeScale.generateId(typeid(RArcEntity), REntity::PropertyLinetypeScale);
    RArcEntity::PropertyLineweight.generateId(typeid(RArcEntity), REntity::PropertyLineweight);
    RArcEntity::PropertyColor.generateId(typeid(RArcEntity), REntity::PropertyColor);
    RArcEntity::PropertyDrawOrder.generateId(typeid(RArcEntity), REntity::PropertyDrawOrder);
    RArcEntity::PropertyCenterX.generateId(typeid(RArcEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"));
    RArcEntity::PropertyCenterY.generateId(typeid(RArcEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RArcEntity::PropertyCenterZ.generateId(typeid(RArcEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RArcEntity::PropertyRadius.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Radius"));
    RArcEntity::PropertyStartAngle.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Start Angle"));
    RArcEntity::PropertyEndAngle.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "End Angle"));
    RArcEntity::PropertyReversed.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Reversed"));

    RArcEntity::PropertyDiameter.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Diameter"));
    RArcEntity::PropertyLength.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RArcEntity::PropertySweepAngle.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Sweep Angle"));
    RArcEntity::PropertyArea.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Area"));
}

bool RArcEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value);
    ret = ret || RObject::setMember(data.center.x, value, PropertyCenterX
            == propertyTypeId);
    ret = ret || RObject::setMember(data.center.y, value, PropertyCenterY
            == propertyTypeId);
    ret = ret || RObject::setMember(data.center.z, value, PropertyCenterZ
            == propertyTypeId);
    ret = ret || RObject::setMember(data.radius, value, PropertyRadius
            == propertyTypeId);
    ret = ret || RObject::setMember(data.startAngle,
            RMath::getNormalizedAngle(value.toDouble()), PropertyStartAngle == propertyTypeId);
    ret = ret || RObject::setMember(data.endAngle,
            RMath::getNormalizedAngle(value.toDouble()), PropertyEndAngle == propertyTypeId);
    ret = ret || RObject::setMember(data.reversed, value, PropertyReversed
            == propertyTypeId);

    if (propertyTypeId==PropertyDiameter) {
        data.setDiameter(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyLength) {
        data.setLength(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertySweepAngle) {
        data.setSweep(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyArea) {
        data.setArea(value.toDouble());
        ret = true;
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RArcEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyCenterX) {
        return qMakePair(QVariant(data.center.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterY) {
        return qMakePair(QVariant(data.center.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterZ) {
        return qMakePair(QVariant(data.center.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRadius) {
        return qMakePair(QVariant(data.radius), RPropertyAttributes());
    } else if (propertyTypeId == PropertyStartAngle) {
        return qMakePair(QVariant(data.startAngle), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyEndAngle) {
        return qMakePair(QVariant(data.endAngle), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyReversed) {
        return qMakePair(QVariant(data.reversed), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDiameter) {
        return qMakePair(QVariant(data.getDiameter()), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertyLength) {
        return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertySweepAngle) {
        return qMakePair(QVariant(data.getSweep()), RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyArea) {
        return qMakePair(QVariant(data.getArea()), RPropertyAttributes(RPropertyAttributes::Redundant));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RArcEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.setBrush(Qt::NoBrush);
    e.exportArc(data);
}

void RArcEntity::print(QDebug dbg) const {
    dbg.nospace() << "RArcEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", center: " << getCenter();
    dbg.nospace() << ", radius: " << getRadius();
    dbg.nospace() << ", startAngle: " << getStartAngle();
    dbg.nospace() << ", endAngle: " << getEndAngle();
    dbg.nospace() << ", reversed: " << isReversed() << ")";
}
