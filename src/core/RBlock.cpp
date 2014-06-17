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
    anonymous(false),
    origin(RVector::invalid) {
}

RBlock::RBlock(RDocument* document, const QString& name,
    const RVector& origin) :
    RObject(document),
    name(name.trimmed()),
    frozen(false),
    anonymous(false),
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
    name = n.trimmed();
}

//void RBlock::setAttributeDefinition(const RAttributeDefinition& attDef) {
//    for (int i=0; i<attributeDefinitions.size(); i++) {
//        RAttributeDefinition ad = attributeDefinitions[i];
//        if (ad.)
//    }
//    attributeDefinitions.append();
//}

bool RBlock::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    Q_UNUSED(transaction)

    bool ret = false;

//    // set attribute definition, internally a custom property:
//    if (propertyTypeId.isBlockAttribute()) {
//        if (value.isValid()) {
//            setAttributeDefinition(
//                RAttributeDefinition(
//                    propertyTypeId.getBlockAttributeTag(),
//                    propertyTypeId.getBlockAttributePrompt(),
//                    value.toString()
//                )
//            );
//        }
//        else {
//            removeCustomProperty(propertyTypeId.getCustomPropertyName());
//        }
//        return true;
//    }

    ret = RObject::setMember(name, value.toString().trimmed(), PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(frozen, value, PropertyFrozen == propertyTypeId);

    return ret;
}

QPair<QVariant, RPropertyAttributes> RBlock::getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyFrozen) {
        return qMakePair(QVariant(frozen), RPropertyAttributes());
    }

    //return qMakePair(QVariant(), RPropertyAttributes());
    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes);
}

bool RBlock::isSelectedForPropertyEditing() {
    return false;
}

void RBlock::print(QDebug dbg) const {
    dbg.nospace() << "RBlock(";
    RObject::print(dbg);
    dbg.nospace() << ", name: " << getName()
            << ", origin: " << getOrigin()
            << ", frozen: " << isFrozen()
            << ", anonymous: " << isAnonymous()
            << ")";
}
