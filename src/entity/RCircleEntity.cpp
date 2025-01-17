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
#include "RArcEntity.h"
#include "RCircleEntity.h"
#include "RExporter.h"

RPropertyTypeId RCircleEntity::PropertyCustom;
RPropertyTypeId RCircleEntity::PropertyHandle;
RPropertyTypeId RCircleEntity::PropertyProtected;
RPropertyTypeId RCircleEntity::PropertyWorkingSet;
RPropertyTypeId RCircleEntity::PropertyType;
RPropertyTypeId RCircleEntity::PropertyBlock;
RPropertyTypeId RCircleEntity::PropertyLayer;
RPropertyTypeId RCircleEntity::PropertyLinetype;
RPropertyTypeId RCircleEntity::PropertyLinetypeScale;
RPropertyTypeId RCircleEntity::PropertyLineweight;
RPropertyTypeId RCircleEntity::PropertyColor;
RPropertyTypeId RCircleEntity::PropertyDisplayedColor;
RPropertyTypeId RCircleEntity::PropertyDrawOrder;

RPropertyTypeId RCircleEntity::PropertyCenterX;
RPropertyTypeId RCircleEntity::PropertyCenterY;
RPropertyTypeId RCircleEntity::PropertyCenterZ;
RPropertyTypeId RCircleEntity::PropertyRadius;

RPropertyTypeId RCircleEntity::PropertyDiameter;
RPropertyTypeId RCircleEntity::PropertyCircumference;
RPropertyTypeId RCircleEntity::PropertyArea;
RPropertyTypeId RCircleEntity::PropertyTotalArea;


RCircleEntity::RCircleEntity(RDocument* document, const RCircleData& data) :
    REntity(document), data(document, data) {

    RDebug::incCounter("RCircleEntity");
}

RCircleEntity::RCircleEntity(const RCircleEntity& other) : REntity(other) {
    RDebug::incCounter("RCircleEntity");
    data = other.data;
}

RCircleEntity::~RCircleEntity() {
    RDebug::decCounter("RCircleEntity");
}

void RCircleEntity::init() {
    RCircleEntity::PropertyCustom.generateId(RCircleEntity::getRtti(), RObject::PropertyCustom);
    RCircleEntity::PropertyHandle.generateId(RCircleEntity::getRtti(), RObject::PropertyHandle);
    RCircleEntity::PropertyProtected.generateId(RCircleEntity::getRtti(), RObject::PropertyProtected);
    RCircleEntity::PropertyWorkingSet.generateId(RCircleEntity::getRtti(), RObject::PropertyWorkingSet);
    RCircleEntity::PropertyType.generateId(RCircleEntity::getRtti(), REntity::PropertyType);
    RCircleEntity::PropertyBlock.generateId(RCircleEntity::getRtti(), REntity::PropertyBlock);
    RCircleEntity::PropertyLayer.generateId(RCircleEntity::getRtti(), REntity::PropertyLayer);
    RCircleEntity::PropertyLinetype.generateId(RCircleEntity::getRtti(), REntity::PropertyLinetype);
    RCircleEntity::PropertyLinetypeScale.generateId(RCircleEntity::getRtti(), REntity::PropertyLinetypeScale);
    RCircleEntity::PropertyLineweight.generateId(RCircleEntity::getRtti(), REntity::PropertyLineweight);
    RCircleEntity::PropertyColor.generateId(RCircleEntity::getRtti(), REntity::PropertyColor);
    RCircleEntity::PropertyDisplayedColor.generateId(RCircleEntity::getRtti(), REntity::PropertyDisplayedColor);
    RCircleEntity::PropertyDrawOrder.generateId(RCircleEntity::getRtti(), REntity::PropertyDrawOrder);

    RCircleEntity::PropertyCenterX.generateId(RCircleEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RCircleEntity::PropertyCenterY.generateId(RCircleEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RCircleEntity::PropertyCenterZ.generateId(RCircleEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RCircleEntity::PropertyRadius.generateId(RCircleEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Radius"), false, RPropertyAttributes::Geometry);

    RCircleEntity::PropertyDiameter.generateId(RCircleEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Diameter"));
    RCircleEntity::PropertyCircumference.generateId(RCircleEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Circumference"));
    RCircleEntity::PropertyArea.generateId(RCircleEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Area"));
    RCircleEntity::PropertyTotalArea.generateId(RCircleEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Total Area"));
}


bool RCircleEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.center.x, value, PropertyCenterX == propertyTypeId);
    ret = ret || RObject::setMember(data.center.y, value, PropertyCenterY == propertyTypeId);
    ret = ret || RObject::setMember(data.center.z, value, PropertyCenterZ == propertyTypeId);
    ret = ret || RObject::setMember(data.radius, value, PropertyRadius == propertyTypeId);

    if (propertyTypeId==PropertyDiameter) {
        data.setDiameter(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyCircumference) {
        data.setCircumference(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyArea) {
        data.setArea(value.toDouble());
        ret = true;
    }

    return ret;
}

//QList<RProperty> RCircleEntity::getAllProperties(bool showOnRequest) const {
//    QList<RProperty> ret = REntity::getAllProperties();

//    ret << RProperty(RCircleEntity::PropertyCenterX, data.center.x);
//    ret << RProperty(RCircleEntity::PropertyCenterY, data.center.y);
//    ret << RProperty(RCircleEntity::PropertyCenterZ, data.center.z);
//    ret << RProperty(RCircleEntity::PropertyRadius, data.radius);
//    ret << RProperty(RCircleEntity::PropertyDiameter, data.getDiameter(), RPropertyAttributes(RPropertyAttributes::Redundant));
//    ret << RProperty(RCircleEntity::PropertyCircumference, data.getCircumference(), RPropertyAttributes(RPropertyAttributes::Redundant));
//    ret << RProperty(RCircleEntity::PropertyArea, data.getArea(), RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::Area));
//    //ret << RProperty(RCircleEntity::PropertyTotalArea, data.getArea(), RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::Area));

//    if (showOnRequest) {
//        ret << RProperty(RCircleEntity::PropertyTotalArea, data.getArea(), RPropertyAttributes(RPropertyAttributes::Sum|RPropertyAttributes::Area));
//    }
//    else {
//        ret << RProperty(RCircleEntity::PropertyTotalArea, 0.0, RPropertyAttributes(RPropertyAttributes::OnRequest|RPropertyAttributes::Area));
//    }

//    return ret;
//}

QPair<QVariant, RPropertyAttributes> RCircleEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyCenterX) {
        return qMakePair(QVariant(data.center.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterY) {
        return qMakePair(QVariant(data.center.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterZ) {
        return qMakePair(QVariant(data.center.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRadius) {
        return qMakePair(QVariant(data.radius), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDiameter) {
        return qMakePair(QVariant(data.getDiameter()), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertyCircumference) {
        return qMakePair(QVariant(data.getCircumference()), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertyArea) {
        return qMakePair(QVariant(data.getArea()), RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::Area));
    } else if (propertyTypeId == PropertyTotalArea) {
        if (showOnRequest) {
            QVariant v;
            v.setValue(data.getArea());
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Sum|RPropertyAttributes::Area));
        }
        else {
            QVariant v;
            v.setValue(0.0);
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::OnRequest|RPropertyAttributes::Area));
        }
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RCircleEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)
    Q_UNUSED(forceSelected)

    e.setBrush(Qt::NoBrush);
    e.exportCircle(data);
}

QSharedPointer<REntity> RCircleEntity::scaleNonUniform(const RVector& scaleFactors, const RVector& center) {
    return RArcEntity::scaleNonUniform(*this, scaleFactors, center);
}

void RCircleEntity::print(QDebug dbg) const {
    dbg.nospace() << "RCircleEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", center: " << getCenter();
    dbg.nospace() << ", radius: " << getRadius() << ")";
}
