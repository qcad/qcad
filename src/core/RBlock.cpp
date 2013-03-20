/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RBlock.h"
#include "RDocument.h"

const QString RBlock::modelSpaceName = "*Model_Space";

RPropertyTypeId RBlock::PropertyName;
RPropertyTypeId RBlock::PropertyFrozen;

RBlock::RBlock() :
    RObject(),
    frozen(false),
    origin(RVector::invalid) {
}

RBlock::RBlock(RDocument* document, const QString& name,
    const RVector& origin) :
    RObject(document),
    name(name),
    frozen(false),
    origin(origin) {
}

RBlock::~RBlock() {
}

void RBlock::init() {
    RBlock::PropertyName.generateId(typeid(RBlock), "", "Name");
    RBlock::PropertyFrozen.generateId(typeid(RBlock), "", "Frozen");
}

RBlock* RBlock::clone() const {
    return new RBlock(*this);
}

void RBlock::setName(const QString& n) {
    name = n;
}

bool RBlock::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value) {

    bool ret = false;

    ret = RObject::setMember(name, value, PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(frozen, value, PropertyFrozen == propertyTypeId);

    return ret;
}

QPair<QVariant, RPropertyAttributes> RBlock::getProperty(
        RPropertyTypeId propertyTypeId,
        bool /*humanReadable*/, bool /*noAttributes*/) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyFrozen) {
        return qMakePair(QVariant(frozen), RPropertyAttributes());
    }

    return qMakePair(QVariant(), RPropertyAttributes());
}

bool RBlock::isSelectedForPropertyEditing() {
    return false;
}

void RBlock::print(QDebug dbg) const {
    dbg.nospace() << "RBlock(";
    RObject::print(dbg);
    dbg.nospace() << ", name: " << getName()
            << ", origin: " << getOrigin()
            << ")";
}
