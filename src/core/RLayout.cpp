/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include "RLayout.h"
#include "RDocument.h"

RPropertyTypeId RLayout::PropertyCustom;
RPropertyTypeId RLayout::PropertyName;
RPropertyTypeId RLayout::PropertyTabOrder;
RPropertyTypeId RLayout::PropertyMinLimitsX;
RPropertyTypeId RLayout::PropertyMinLimitsY;
RPropertyTypeId RLayout::PropertyMinLimitsZ;
RPropertyTypeId RLayout::PropertyMaxLimitsX;
RPropertyTypeId RLayout::PropertyMaxLimitsY;
RPropertyTypeId RLayout::PropertyMaxLimitsZ;
RPropertyTypeId RLayout::PropertyInsertionBaseX;
RPropertyTypeId RLayout::PropertyInsertionBaseY;
RPropertyTypeId RLayout::PropertyInsertionBaseZ;
RPropertyTypeId RLayout::PropertyMinExtentsX;
RPropertyTypeId RLayout::PropertyMinExtentsY;
RPropertyTypeId RLayout::PropertyMinExtentsZ;
RPropertyTypeId RLayout::PropertyMaxExtentsX;
RPropertyTypeId RLayout::PropertyMaxExtentsY;
RPropertyTypeId RLayout::PropertyMaxExtentsZ;

RLayout::RLayout() :
    RObject(),
    tabOrder(0) {
}

RLayout::RLayout(RDocument* document, const QString& name) :
    RObject(document),
    name(name.trimmed()),
    tabOrder(0) {
}

RLayout::~RLayout() {
}

void RLayout::init() {
    RLayout::PropertyCustom.generateId(typeid(RLayout), RObject::PropertyCustom);
    RLayout::PropertyName.generateId(typeid(RLayout), "", QT_TRANSLATE_NOOP("REntity", "Name"));
    RLayout::PropertyTabOrder.generateId(typeid(RLayout), "", QT_TRANSLATE_NOOP("REntity", "Tab Order"));
    RLayout::PropertyMinLimitsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Limits"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMinLimitsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Limits"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMinLimitsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Limits"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyMaxLimitsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Limits"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMaxLimitsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Limits"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMaxLimitsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Limits"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyInsertionBaseX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Insertion Base"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyInsertionBaseY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Insertion Base"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyInsertionBaseZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Insertion Base"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyMinExtentsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Extents"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMinExtentsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Extents"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMinExtentsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Min Extents"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RLayout::PropertyMaxExtentsX.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Extents"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLayout::PropertyMaxExtentsY.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Extents"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLayout::PropertyMaxExtentsZ.generateId(typeid(RLayout), QT_TRANSLATE_NOOP("REntity", "Max Extents"), QT_TRANSLATE_NOOP("REntity", "Z"));
}

RLayout* RLayout::clone() const {
    return new RLayout(*this);
}

void RLayout::setName(const QString& n) {
    name = n.trimmed();
}

bool RLayout::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = RObject::setProperty(propertyTypeId, value, transaction);

    if (PropertyName == propertyTypeId) {
        // never change name of layouts starting with * (model space, paper space, ...):
        if (name.startsWith("*")) {
            return false;
        }
        // never change layout name to empty string:
        if (value.toString().isEmpty()) {
            return false;
        }
    }

    ret = ret || RObject::setMember(name, value.toString().trimmed(), PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(tabOrder, value, PropertyTabOrder == propertyTypeId);

    ret = ret || RObject::setMember(minLimits.x, value, PropertyMinLimitsX == propertyTypeId);
    ret = ret || RObject::setMember(minLimits.y, value, PropertyMinLimitsY == propertyTypeId);
    ret = ret || RObject::setMember(minLimits.z, value, PropertyMinLimitsZ == propertyTypeId);
    ret = ret || RObject::setMember(maxLimits.x, value, PropertyMaxLimitsX == propertyTypeId);
    ret = ret || RObject::setMember(maxLimits.y, value, PropertyMaxLimitsY == propertyTypeId);
    ret = ret || RObject::setMember(maxLimits.z, value, PropertyMaxLimitsZ == propertyTypeId);
    ret = ret || RObject::setMember(insertionBase.x, value, PropertyInsertionBaseX == propertyTypeId);
    ret = ret || RObject::setMember(insertionBase.y, value, PropertyInsertionBaseY == propertyTypeId);
    ret = ret || RObject::setMember(insertionBase.z, value, PropertyInsertionBaseZ == propertyTypeId);
    ret = ret || RObject::setMember(minExtents.x, value, PropertyMinExtentsX == propertyTypeId);
    ret = ret || RObject::setMember(minExtents.y, value, PropertyMinExtentsY == propertyTypeId);
    ret = ret || RObject::setMember(minExtents.z, value, PropertyMinExtentsZ == propertyTypeId);
    ret = ret || RObject::setMember(maxExtents.x, value, PropertyMaxExtentsX == propertyTypeId);
    ret = ret || RObject::setMember(maxExtents.y, value, PropertyMaxExtentsY == propertyTypeId);
    ret = ret || RObject::setMember(maxExtents.z, value, PropertyMaxExtentsZ == propertyTypeId);

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLayout::getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyTabOrder) {
        return qMakePair(QVariant(tabOrder), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinLimitsX) {
        return qMakePair(QVariant(minLimits.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinLimitsY) {
        return qMakePair(QVariant(minLimits.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinLimitsZ) {
        return qMakePair(QVariant(minLimits.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxLimitsX) {
        return qMakePair(QVariant(maxLimits.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxLimitsY) {
        return qMakePair(QVariant(maxLimits.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxLimitsZ) {
        return qMakePair(QVariant(maxLimits.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyInsertionBaseX) {
        return qMakePair(QVariant(insertionBase.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyInsertionBaseY) {
        return qMakePair(QVariant(insertionBase.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyInsertionBaseZ) {
        return qMakePair(QVariant(insertionBase.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinExtentsX) {
        return qMakePair(QVariant(minExtents.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinExtentsY) {
        return qMakePair(QVariant(minExtents.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinExtentsZ) {
        return qMakePair(QVariant(minExtents.z), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxExtentsX) {
        return qMakePair(QVariant(maxExtents.x), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxExtentsY) {
        return qMakePair(QVariant(maxExtents.y), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMaxExtentsZ) {
        return qMakePair(QVariant(maxExtents.z), RPropertyAttributes());
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes);
}

bool RLayout::isSelectedForPropertyEditing() {
    return false;
}

void RLayout::print(QDebug dbg) const {
    dbg.nospace() << "RLayout(";
    RObject::print(dbg);
    dbg.nospace() << ", name: " << getName()
            << ", insertionBase: " << getInsertionBase()
            << ")";
}
