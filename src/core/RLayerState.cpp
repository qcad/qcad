/**
 * Copyright (c) 2019 by Andrew Mustun. All rights reserved.
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
#include "RLayerState.h"
#include "RDocument.h"

RPropertyTypeId RLayerState::PropertyCustom;
RPropertyTypeId RLayerState::PropertyType;
RPropertyTypeId RLayerState::PropertyHandle;
RPropertyTypeId RLayerState::PropertyProtected;

RPropertyTypeId RLayerState::PropertyName;


RLayerState::RLayerState() : RObject() {
}

RLayerState::RLayerState(RDocument* document, const QString& name)
    : RObject(document), name(name.trimmed()) {
}

RLayerState::~RLayerState() {
}

void RLayerState::init() {
    RLayerState::PropertyCustom.generateId(typeid(RLayerState), RObject::PropertyCustom);
    RLayerState::PropertyType.generateId(typeid(RLayerState), RObject::PropertyType);
    RLayerState::PropertyHandle.generateId(typeid(RLayerState), RObject::PropertyHandle);
    RLayerState::PropertyProtected.generateId(typeid(RLayerState), RObject::PropertyProtected);

    RLayerState::PropertyName.generateId(typeid(RLayerState), "", QT_TRANSLATE_NOOP("REntity", "Name"));
}

RLayerState* RLayerState::clone() const {
    return new RLayerState(*this);
}

void RLayerState::setName(const QString& n) {
    name = n.trimmed();
}

void RLayerState::addLayer(const QString& layerName, RLayer::LayerFlags layerFlags) {
    layerStates.insert(layerName, layerFlags);
}

bool RLayerState::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {
    bool ret = RObject::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(name, value.toString().trimmed(), PropertyName == propertyTypeId);

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLayerState::getProperty(RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

bool RLayerState::isSelectedForPropertyEditing() {
    return false;
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLayerState& l) {
    dbg.nospace()
       << "RLayerState("
       << (RObject&) l
       << ", name: " << l.getName()
       << ")";
    return dbg.space();
}
