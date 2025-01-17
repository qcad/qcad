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
#include "RPointEntity.h"
#include "RExporter.h"

RPropertyTypeId RPointEntity::PropertyCustom;
RPropertyTypeId RPointEntity::PropertyHandle;
RPropertyTypeId RPointEntity::PropertyProtected;
RPropertyTypeId RPointEntity::PropertyWorkingSet;
RPropertyTypeId RPointEntity::PropertyType;
RPropertyTypeId RPointEntity::PropertyBlock;
RPropertyTypeId RPointEntity::PropertyLayer;
RPropertyTypeId RPointEntity::PropertyLinetype;
RPropertyTypeId RPointEntity::PropertyLinetypeScale;
RPropertyTypeId RPointEntity::PropertyLineweight;
RPropertyTypeId RPointEntity::PropertyColor;
RPropertyTypeId RPointEntity::PropertyDisplayedColor;
RPropertyTypeId RPointEntity::PropertyDrawOrder;

RPropertyTypeId RPointEntity::PropertyPositionX;
RPropertyTypeId RPointEntity::PropertyPositionY;
RPropertyTypeId RPointEntity::PropertyPositionZ;


RPointEntity::RPointEntity(RDocument* document, const RPointData& data) :
    REntity(document), data(document, data) {

    RDebug::incCounter("RPointEntity");
}

RPointEntity::RPointEntity(const RPointEntity& other) : REntity(other) {
    RDebug::incCounter("RPointEntity");
    data = other.data;
}

RPointEntity::~RPointEntity() {
    RDebug::decCounter("RPointEntity");
}

void RPointEntity::init() {
    RPointEntity::PropertyCustom.generateId(RPointEntity::getRtti(), RObject::PropertyCustom);
    RPointEntity::PropertyHandle.generateId(RPointEntity::getRtti(), RObject::PropertyHandle);
    RPointEntity::PropertyProtected.generateId(RPointEntity::getRtti(), RObject::PropertyProtected);
    RPointEntity::PropertyWorkingSet.generateId(RPointEntity::getRtti(), RObject::PropertyWorkingSet);
    RPointEntity::PropertyType.generateId(RPointEntity::getRtti(), REntity::PropertyType);
    RPointEntity::PropertyBlock.generateId(RPointEntity::getRtti(), REntity::PropertyBlock);
    RPointEntity::PropertyLayer.generateId(RPointEntity::getRtti(), REntity::PropertyLayer);
    RPointEntity::PropertyLinetype.generateId(RPointEntity::getRtti(), REntity::PropertyLinetype);
    RPointEntity::PropertyLinetypeScale.generateId(RPointEntity::getRtti(), REntity::PropertyLinetypeScale);
    RPointEntity::PropertyLineweight.generateId(RPointEntity::getRtti(), REntity::PropertyLineweight);
    RPointEntity::PropertyColor.generateId(RPointEntity::getRtti(), REntity::PropertyColor);
    RPointEntity::PropertyDisplayedColor.generateId(RPointEntity::getRtti(), REntity::PropertyDisplayedColor);
    RPointEntity::PropertyDrawOrder.generateId(RPointEntity::getRtti(), REntity::PropertyDrawOrder);

    RPointEntity::PropertyPositionX.generateId(RPointEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RPointEntity::PropertyPositionY.generateId(RPointEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RPointEntity::PropertyPositionZ.generateId(RPointEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RPointEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);
    ret = ret || RObject::setMember(data.position.x, value, PropertyPositionX == propertyTypeId);
    ret = ret || RObject::setMember(data.position.y, value, PropertyPositionY == propertyTypeId);
    ret = ret || RObject::setMember(data.position.z, value, PropertyPositionZ == propertyTypeId);
    return ret;
}

QPair<QVariant, RPropertyAttributes> RPointEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyPositionX) {
        return qMakePair(QVariant(data.position.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionY) {
        return qMakePair(QVariant(data.position.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionZ) {
        return qMakePair(QVariant(data.position.z), RPropertyAttributes());
    }
    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RPointEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.setBrush(Qt::NoBrush);
    e.exportPoint(data);
}

void RPointEntity::print(QDebug dbg) const {
    dbg.nospace() << "RPointEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", position: " << getPosition() << ")";
}
