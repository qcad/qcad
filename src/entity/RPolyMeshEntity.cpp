/**
 * Copyright (c) 2011-2026 by Andrew Mustun. All rights reserved.
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
#include "RPolyMeshEntity.h"
#include "RExporter.h"

RPropertyTypeId RPolyMeshEntity::PropertyCustom;
RPropertyTypeId RPolyMeshEntity::PropertyHandle;
RPropertyTypeId RPolyMeshEntity::PropertyProtected;
RPropertyTypeId RPolyMeshEntity::PropertyWorkingSet;
RPropertyTypeId RPolyMeshEntity::PropertyType;
RPropertyTypeId RPolyMeshEntity::PropertyBlock;
RPropertyTypeId RPolyMeshEntity::PropertyLayer;
RPropertyTypeId RPolyMeshEntity::PropertyLinetype;
RPropertyTypeId RPolyMeshEntity::PropertyLinetypeScale;
RPropertyTypeId RPolyMeshEntity::PropertyLineweight;
RPropertyTypeId RPolyMeshEntity::PropertyColor;
RPropertyTypeId RPolyMeshEntity::PropertyDisplayedColor;
RPropertyTypeId RPolyMeshEntity::PropertyDrawOrder;

RPropertyTypeId RPolyMeshEntity::PropertyVertexCount;
RPropertyTypeId RPolyMeshEntity::PropertyFaceCount;

RPolyMeshEntityProxy* RPolyMeshEntity::polyMeshEntityProxy = NULL;


RPolyMeshEntity::RPolyMeshEntity(RDocument* document, const RPolyMeshData& data) :
    REntity(document), data(document, data) {
}

RPolyMeshEntity::~RPolyMeshEntity() {
}

void RPolyMeshEntity::init() {
    RPolyMeshEntity::PropertyCustom.generateId(RPolyMeshEntity::getRtti(), RObject::PropertyCustom);
    RPolyMeshEntity::PropertyHandle.generateId(RPolyMeshEntity::getRtti(), RObject::PropertyHandle);
    RPolyMeshEntity::PropertyProtected.generateId(RPolyMeshEntity::getRtti(), RObject::PropertyProtected);
    RPolyMeshEntity::PropertyWorkingSet.generateId(RPolyMeshEntity::getRtti(), RObject::PropertyWorkingSet);
    RPolyMeshEntity::PropertyType.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyType);
    RPolyMeshEntity::PropertyBlock.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyBlock);
    RPolyMeshEntity::PropertyLayer.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyLayer);
    RPolyMeshEntity::PropertyLinetype.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyLinetype);
    RPolyMeshEntity::PropertyLinetypeScale.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyLinetypeScale);
    RPolyMeshEntity::PropertyLineweight.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyLineweight);
    RPolyMeshEntity::PropertyColor.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyColor);
    RPolyMeshEntity::PropertyDisplayedColor.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyDisplayedColor);
    RPolyMeshEntity::PropertyDrawOrder.generateId(RPolyMeshEntity::getRtti(), REntity::PropertyDrawOrder);

    RPolyMeshEntity::PropertyVertexCount.generateId(RPolyMeshEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Vertices"));
    RPolyMeshEntity::PropertyFaceCount.generateId(RPolyMeshEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Faces"));
}

bool RPolyMeshEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    return REntity::setProperty(propertyTypeId, value, transaction);
}

QPair<QVariant, RPropertyAttributes> RPolyMeshEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {
    if (propertyTypeId==PropertyVertexCount) {
        return qMakePair(QVariant(data.countVertices()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    else if (propertyTypeId==PropertyFaceCount) {
        return qMakePair(QVariant(data.countFaces()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RPolyMeshEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    if (!hasProxy()) {
        return;
    }
    polyMeshEntityProxy->exportEntity(*this, e, preview, forceSelected);
}

void RPolyMeshEntity::print(QDebug dbg) const {
    dbg.nospace() << "RPolyMeshEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", vertices: " << data.countVertices()
                  << ", faces: " << data.countFaces();
    dbg.nospace() << ")";
}
