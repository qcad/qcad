/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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
#include "RWipeoutEntity.h"
#include "RMetaTypes.h"
#include "RExporter.h"
#include "RLine.h"
#include "RPluginLoader.h"

RPropertyTypeId RWipeoutEntity::PropertyCustom;
RPropertyTypeId RWipeoutEntity::PropertyHandle;
RPropertyTypeId RWipeoutEntity::PropertyProtected;
RPropertyTypeId RWipeoutEntity::PropertyWorkingSet;
RPropertyTypeId RWipeoutEntity::PropertyType;
RPropertyTypeId RWipeoutEntity::PropertyBlock;
RPropertyTypeId RWipeoutEntity::PropertyLayer;
RPropertyTypeId RWipeoutEntity::PropertyLinetype;
RPropertyTypeId RWipeoutEntity::PropertyLinetypeScale;
RPropertyTypeId RWipeoutEntity::PropertyLineweight;
RPropertyTypeId RWipeoutEntity::PropertyColor;
RPropertyTypeId RWipeoutEntity::PropertyDisplayedColor;
RPropertyTypeId RWipeoutEntity::PropertyDrawOrder;

RPropertyTypeId RWipeoutEntity::PropertyVertexNX;
RPropertyTypeId RWipeoutEntity::PropertyVertexNY;
RPropertyTypeId RWipeoutEntity::PropertyVertexNZ;
RPropertyTypeId RWipeoutEntity::PropertyBulgeN;

RPropertyTypeId RWipeoutEntity::PropertyBaseAngle;
RPropertyTypeId RWipeoutEntity::PropertySize1;
RPropertyTypeId RWipeoutEntity::PropertySize2;

RPropertyTypeId RWipeoutEntity::PropertyFrame;

RWipeoutEntity::RWipeoutEntity(RDocument* document, const RWipeoutData& data) :
    REntity(document), data(document, data) {
    RDebug::incCounter("RWipeoutEntity");
}

RWipeoutEntity::RWipeoutEntity(const RWipeoutEntity& other) : REntity(other) {
    RDebug::incCounter("RWipeoutEntity");
    data = other.data;
}

RWipeoutEntity::~RWipeoutEntity() {
    RDebug::decCounter("RWipeoutEntity");
}

void RWipeoutEntity::setShape(const RPolyline& l) {
    data.setVertices(l.getVertices());
    data.setBulges(l.getBulges());
}

void RWipeoutEntity::init() {
    RWipeoutEntity::PropertyCustom.generateId(RWipeoutEntity::getRtti(), RObject::PropertyCustom);
    RWipeoutEntity::PropertyHandle.generateId(RWipeoutEntity::getRtti(), RObject::PropertyHandle);
    RWipeoutEntity::PropertyProtected.generateId(RWipeoutEntity::getRtti(), RObject::PropertyProtected);
    RWipeoutEntity::PropertyWorkingSet.generateId(RWipeoutEntity::getRtti(), RObject::PropertyWorkingSet);
    RWipeoutEntity::PropertyType.generateId(RWipeoutEntity::getRtti(), REntity::PropertyType);
    RWipeoutEntity::PropertyBlock.generateId(RWipeoutEntity::getRtti(), REntity::PropertyBlock);
    RWipeoutEntity::PropertyLayer.generateId(RWipeoutEntity::getRtti(), REntity::PropertyLayer);
    RWipeoutEntity::PropertyLinetype.generateId(RWipeoutEntity::getRtti(), REntity::PropertyLinetype);
    RWipeoutEntity::PropertyLinetypeScale.generateId(RWipeoutEntity::getRtti(), REntity::PropertyLinetypeScale);
    RWipeoutEntity::PropertyLineweight.generateId(RWipeoutEntity::getRtti(), REntity::PropertyLineweight);
    RWipeoutEntity::PropertyColor.generateId(RWipeoutEntity::getRtti(), REntity::PropertyColor);
    RWipeoutEntity::PropertyDisplayedColor.generateId(RWipeoutEntity::getRtti(), REntity::PropertyDisplayedColor);
    RWipeoutEntity::PropertyDrawOrder.generateId(RWipeoutEntity::getRtti(), REntity::PropertyDrawOrder);

    RWipeoutEntity::PropertyVertexNX.generateId(RWipeoutEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RWipeoutEntity::PropertyVertexNY.generateId(RWipeoutEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RWipeoutEntity::PropertyVertexNZ.generateId(RWipeoutEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RWipeoutEntity::PropertyBulgeN.generateId(RWipeoutEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Bulge"), false, RPropertyAttributes::Geometry);

    RWipeoutEntity::PropertyBaseAngle.generateId(RWipeoutEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Size"), QT_TRANSLATE_NOOP("REntity", "Base Angle"));
    RWipeoutEntity::PropertySize1.generateId(RWipeoutEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Size"), QT_TRANSLATE_NOOP("REntity", "Size 1"));
    RWipeoutEntity::PropertySize2.generateId(RWipeoutEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Size"), QT_TRANSLATE_NOOP("REntity", "Size 2"));

    RWipeoutEntity::PropertyFrame.generateId(RWipeoutEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Frame"));
}

bool RWipeoutEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value, transaction);
    ret = ret || RObject::setMemberX(data.vertices, value, PropertyVertexNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.vertices, value, PropertyVertexNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.vertices, value, PropertyVertexNZ == propertyTypeId);
    ret = ret || RObject::setMember(data.bulges, value, PropertyBulgeN == propertyTypeId);

    ret = ret || RObject::setMember(data.showFrame, value, PropertyFrame == propertyTypeId);

    return ret;
}

QPair<QVariant, RPropertyAttributes> RWipeoutEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyVertexNX) {
        QVariant v;
        v.setValue(RVector::getXList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyVertexNY) {
        QVariant v;
        v.setValue(RVector::getYList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyVertexNZ) {
        QVariant v;
        v.setValue(RVector::getZList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyBulgeN) {
        QVariant v;
        v.setValue(data.bulges);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List|RPropertyAttributes::UnitLess));
    } else if (propertyTypeId == PropertyFrame) {
        QVariant v;
        v.setValue(data.showFrame);
        return qMakePair(v, RPropertyAttributes());
    }

    if (RPolyline::hasProxy()) {
        double baseAngle = data.getBaseAngle();
        if (!RMath::isNaN(baseAngle)) {
            if (propertyTypeId == PropertyBaseAngle) {
                QVariant v;
                v.setValue(baseAngle);
                return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Angle|RPropertyAttributes::Redundant|RPropertyAttributes::ReadOnly));
            }
            else if (propertyTypeId == PropertySize1) {
                QVariant v;
                v.setValue(data.getWidth());
                return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Redundant));
            }
            else if (propertyTypeId == PropertySize2) {
                QVariant v;
                v.setValue(data.getHeight());
                return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Redundant));
            }
        }
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RWipeoutEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    RPolyline pl = data.getBoundary();

    e.setBrush(Qt::SolidPattern);

    if (!getShowFrame()) {
        QPen pen = e.getPen();
        pen.setStyle(Qt::NoPen);
        e.setPen(pen);
    }
    e.setWipeout(true);
    e.exportPolyline(pl);
    e.setWipeout(false);
}
