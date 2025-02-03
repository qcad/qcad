/**
 * Copyright (c) 2011-2025 by Andrew Mustun. All rights reserved.
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
#include "RCustomEntity.h"
#include "RCustomEntityHandler.h"
#include "RCustomEntityRegistry.h"
#include "RDebug.h"
#include "RDocument.h"
#include "RExporter.h"
#include "RS.h"
#include "RSettings.h"
#include "RStorage.h"
#include "RTransform.h"

RPropertyTypeId RCustomEntity::PropertyCustom;
RPropertyTypeId RCustomEntity::PropertyHandle;
RPropertyTypeId RCustomEntity::PropertyProtected;
RPropertyTypeId RCustomEntity::PropertyWorkingSet;
RPropertyTypeId RCustomEntity::PropertyType;
RPropertyTypeId RCustomEntity::PropertyBlock;
RPropertyTypeId RCustomEntity::PropertyLayer;
RPropertyTypeId RCustomEntity::PropertyLinetype;
RPropertyTypeId RCustomEntity::PropertyLinetypeScale;
RPropertyTypeId RCustomEntity::PropertyLineweight;
RPropertyTypeId RCustomEntity::PropertyColor;
RPropertyTypeId RCustomEntity::PropertyDisplayedColor;
RPropertyTypeId RCustomEntity::PropertyDrawOrder;

RPropertyTypeId RCustomEntity::PropertyReferencedBlock;
RPropertyTypeId RCustomEntity::PropertyPositionX;
RPropertyTypeId RCustomEntity::PropertyPositionY;
RPropertyTypeId RCustomEntity::PropertyPositionZ;
RPropertyTypeId RCustomEntity::PropertyScaleX;
RPropertyTypeId RCustomEntity::PropertyScaleY;
RPropertyTypeId RCustomEntity::PropertyScaleZ;
RPropertyTypeId RCustomEntity::PropertyRotation;


RCustomEntity::RCustomEntity(RDocument* document, RS::EntityType customEntityType,
    const RBlockReferenceData& data) :
    RBlockReferenceEntity(document, data), customEntityType(customEntityType), lastBlockUpdate(0), lastPropertyUpdate(0) {
    RDebug::incCounter("RCustomEntity");
}

RCustomEntity::RCustomEntity(const RCustomEntity& other) : RBlockReferenceEntity(other) {
    RDebug::incCounter("RCustomEntity");

    customEntityType = other.customEntityType;
    lastBlockUpdate = other.lastBlockUpdate;
    lastPropertyUpdate = other.lastPropertyUpdate;
}

RCustomEntity::~RCustomEntity() {
    RDebug::decCounter("RCustomEntity");
}

void RCustomEntity::init() {
    RCustomEntity::PropertyCustom.generateId(RCustomEntity::getRtti(), RObject::PropertyCustom);
    RCustomEntity::PropertyHandle.generateId(RCustomEntity::getRtti(), RObject::PropertyHandle);
    RCustomEntity::PropertyProtected.generateId(RCustomEntity::getRtti(), RObject::PropertyProtected);
    RCustomEntity::PropertyWorkingSet.generateId(RCustomEntity::getRtti(), REntity::PropertyWorkingSet);
    RCustomEntity::PropertyType.generateId(RCustomEntity::getRtti(), REntity::PropertyType);
    RCustomEntity::PropertyBlock.generateId(RCustomEntity::getRtti(), REntity::PropertyBlock);
    RCustomEntity::PropertyLayer.generateId(RCustomEntity::getRtti(), REntity::PropertyLayer);
    RCustomEntity::PropertyLinetype.generateId(RCustomEntity::getRtti(), REntity::PropertyLinetype);
    RCustomEntity::PropertyLinetypeScale.generateId(RCustomEntity::getRtti(), REntity::PropertyLinetypeScale);
    RCustomEntity::PropertyLineweight.generateId(RCustomEntity::getRtti(), REntity::PropertyLineweight);
    RCustomEntity::PropertyColor.generateId(RCustomEntity::getRtti(), REntity::PropertyColor);
    RCustomEntity::PropertyDisplayedColor.generateId(RCustomEntity::getRtti(), REntity::PropertyDisplayedColor);
    RCustomEntity::PropertyDrawOrder.generateId(RCustomEntity::getRtti(), REntity::PropertyDrawOrder);

    RCustomEntity::PropertyReferencedBlock.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyReferencedBlock);
    RCustomEntity::PropertyPositionX.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyPositionX);
    RCustomEntity::PropertyPositionY.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyPositionY);
    RCustomEntity::PropertyPositionZ.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyPositionZ);
    RCustomEntity::PropertyScaleX.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyScaleX);
    RCustomEntity::PropertyScaleY.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyScaleY);
    RCustomEntity::PropertyScaleZ.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyScaleZ);
    RCustomEntity::PropertyRotation.generateId(RCustomEntity::getRtti(), RBlockReferenceEntity::PropertyRotation);
}

QPair<QVariant, RPropertyAttributes> RCustomEntity::getProperty(
    RPropertyTypeId& propertyTypeId,
    bool humanReadable, bool noAttributes, bool showOnRequest) {

    return RBlockReferenceEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

bool RCustomEntity::setProperty(RPropertyTypeId propertyTypeId,
                                        const QVariant& value, RTransaction* transaction) {

    lastPropertyUpdate = QDateTime::currentMSecsSinceEpoch();

    return RBlockReferenceEntity::setProperty(propertyTypeId, value, transaction);
}

void RCustomEntity::update() const {
    qDebug() << "RCustomEntity::update";
    RBlockReferenceEntity::update();
}

void RCustomEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    qDebug() << "RCustomEntity::exportEntity";

    // check if block is up to date:
    bool updateRequired = lastPropertyUpdate > lastBlockUpdate || lastBlockUpdate==0;

    // update block if necessary:
    if (updateRequired) {

        RCustomEntityHandler* handler = RCustomEntityRegistry::getHandler(customEntityType);
        if (handler==NULL) {
            qDebug() << "RCustomEntity::exportEntity: no handler for entity type: " << customEntityType;
        }
        else {
            handler->render(this);
        }

        //->render(const_cast<RCustomEntity*>(this));

        lastBlockUpdate = QDateTime::currentMSecsSinceEpoch();
    }

    // render block:
    RBlockReferenceEntity::exportEntity(e, preview, forceSelected);
}

void RCustomEntity::print(QDebug dbg) const {
    dbg.nospace() << "RCustomEntity(";
    RBlockReferenceEntity::print(dbg);
    dbg.nospace() << ")";
}
