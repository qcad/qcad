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
#include "RLineEntity.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RLineEntity::PropertyCustom;
RPropertyTypeId RLineEntity::PropertyHandle;
RPropertyTypeId RLineEntity::PropertyProtected;
RPropertyTypeId RLineEntity::PropertyWorkingSet;
RPropertyTypeId RLineEntity::PropertyType;
RPropertyTypeId RLineEntity::PropertyBlock;
RPropertyTypeId RLineEntity::PropertyLayer;
RPropertyTypeId RLineEntity::PropertyLinetype;
RPropertyTypeId RLineEntity::PropertyLinetypeScale;
RPropertyTypeId RLineEntity::PropertyLineweight;
RPropertyTypeId RLineEntity::PropertyColor;
RPropertyTypeId RLineEntity::PropertyDisplayedColor;
RPropertyTypeId RLineEntity::PropertyDrawOrder;

RPropertyTypeId RLineEntity::PropertyStartPointX;
RPropertyTypeId RLineEntity::PropertyStartPointY;
RPropertyTypeId RLineEntity::PropertyStartPointZ;
RPropertyTypeId RLineEntity::PropertyEndPointX;
RPropertyTypeId RLineEntity::PropertyEndPointY;
RPropertyTypeId RLineEntity::PropertyEndPointZ;

RPropertyTypeId RLineEntity::PropertyAngle;
RPropertyTypeId RLineEntity::PropertyLength;
RPropertyTypeId RLineEntity::PropertyTotalLength;


RLineEntity::RLineEntity(RDocument* document, const RLineData& data) :
    REntity(document), data(document, data) {

    RDebug::incCounter("RLineEntity");
}

RLineEntity::RLineEntity(const RLineEntity& other) : REntity(other) {
    RDebug::incCounter("RLineEntity");
    data = other.data;
}

RLineEntity::~RLineEntity() {
    RDebug::decCounter("RLineEntity");
}

void RLineEntity::setShape(const RLine& l) {
    data.setStartPoint(l.getStartPoint());
    data.setEndPoint(l.getEndPoint());
}

void RLineEntity::init() {
    RLineEntity::PropertyCustom.generateId(typeid(RLineEntity), RObject::PropertyCustom);
    RLineEntity::PropertyHandle.generateId(typeid(RLineEntity), RObject::PropertyHandle);
    RLineEntity::PropertyProtected.generateId(typeid(RLineEntity), RObject::PropertyProtected);
    RLineEntity::PropertyWorkingSet.generateId(typeid(RLineEntity), RObject::PropertyWorkingSet);
    RLineEntity::PropertyType.generateId(typeid(RLineEntity), REntity::PropertyType);
    RLineEntity::PropertyBlock.generateId(typeid(RLineEntity), REntity::PropertyBlock);
    RLineEntity::PropertyLayer.generateId(typeid(RLineEntity), REntity::PropertyLayer);
    RLineEntity::PropertyLinetype.generateId(typeid(RLineEntity), REntity::PropertyLinetype);
    RLineEntity::PropertyLinetypeScale.generateId(typeid(RLineEntity), REntity::PropertyLinetypeScale);
    RLineEntity::PropertyLineweight.generateId(typeid(RLineEntity), REntity::PropertyLineweight);
    RLineEntity::PropertyColor.generateId(typeid(RLineEntity), REntity::PropertyColor);
    RLineEntity::PropertyDisplayedColor.generateId(typeid(RLineEntity), REntity::PropertyDisplayedColor);
    RLineEntity::PropertyDrawOrder.generateId(typeid(RLineEntity), REntity::PropertyDrawOrder);

    RLineEntity::PropertyStartPointX.generateId(typeid(RLineEntity), QT_TRANSLATE_NOOP("REntity", "Start Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RLineEntity::PropertyStartPointY.generateId(typeid(RLineEntity), QT_TRANSLATE_NOOP("REntity", "Start Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RLineEntity::PropertyStartPointZ.generateId(typeid(RLineEntity), QT_TRANSLATE_NOOP("REntity", "Start Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RLineEntity::PropertyEndPointX.generateId(typeid(RLineEntity), QT_TRANSLATE_NOOP("REntity", "End Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RLineEntity::PropertyEndPointY.generateId(typeid(RLineEntity), QT_TRANSLATE_NOOP("REntity", "End Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RLineEntity::PropertyEndPointZ.generateId(typeid(RLineEntity), QT_TRANSLATE_NOOP("REntity", "End Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RLineEntity::PropertyAngle.generateId(typeid(RLineEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
    RLineEntity::PropertyLength.generateId(typeid(RLineEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RLineEntity::PropertyTotalLength.generateId(typeid(RLineEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));
}

bool RLineEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.startPoint.x, value, PropertyStartPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.startPoint.y, value, PropertyStartPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.startPoint.z, value, PropertyStartPointZ == propertyTypeId);
    ret = ret || RObject::setMember(data.endPoint.x, value, PropertyEndPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.endPoint.y, value, PropertyEndPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.endPoint.z, value, PropertyEndPointZ == propertyTypeId);

    if (propertyTypeId==PropertyAngle) {
        data.setAngle(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyLength) {
        data.setLength(value.toDouble());
        ret = true;
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLineEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyStartPointX) {
        return qMakePair(QVariant(data.startPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyStartPointY) {
        return qMakePair(QVariant(data.startPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyStartPointZ) {
        return qMakePair(QVariant(data.startPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyEndPointX) {
        return qMakePair(QVariant(data.endPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyEndPointY) {
        return qMakePair(QVariant(data.endPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyEndPointZ) {
        return qMakePair(QVariant(data.endPoint.z), RPropertyAttributes());
    } else if (propertyTypeId==PropertyAngle) {
        return qMakePair(QVariant(data.getAngle()), RPropertyAttributes(RPropertyAttributes::Angle|RPropertyAttributes::Redundant));
    } else if (propertyTypeId==PropertyLength) {
        return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId==PropertyTotalLength) {
        return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Sum));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RLineEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.setBrush(Qt::NoBrush);
    e.exportLine(data);
}

void RLineEntity::print(QDebug dbg) const {
    dbg.nospace() << "RLineEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", startPoint: " << getStartPoint() << ", endPoint: "
            << getEndPoint() << ")";
}
