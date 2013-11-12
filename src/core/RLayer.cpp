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
#include "RLayer.h"
#include "RDocument.h"

RPropertyTypeId RLayer::PropertyName;
RPropertyTypeId RLayer::PropertyFrozen;
RPropertyTypeId RLayer::PropertyLocked;
RPropertyTypeId RLayer::PropertyColor;
RPropertyTypeId RLayer::PropertyLinetype;
RPropertyTypeId RLayer::PropertyLineweight;

RLayer::RLayer() :
        RObject(),
        frozen(false),
        locked(false),
        linetype(RLinetype::INVALID_ID),
        lineweight(RLineweight::WeightInvalid) {
}

RLayer::RLayer(RDocument* document, const QString& name,
    bool frozen, bool locked, const RColor& color,
    RLinetype::Id linetype, RLineweight::Lineweight lineweight) :
    RObject(document), name(name.trimmed()), frozen(frozen), locked(locked),
    color(color), linetype(linetype), lineweight(lineweight) {
}

RLayer::~RLayer() {
}

void RLayer::init() {
    RLayer::PropertyName.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("RLayer", "Name"));
    RLayer::PropertyFrozen.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("RLayer", "Frozen"));
    RLayer::PropertyLocked.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("RLayer", "Locked"));
    RLayer::PropertyColor.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("RLayer", "Color"));
    RLayer::PropertyLinetype.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("RLayer", "Linetype"));
    RLayer::PropertyLineweight.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("RLayer", "Lineweight"));
}

RLayer* RLayer::clone() const {
    return new RLayer(*this);
}

void RLayer::setName(const QString& n) {
    if (name == "0") {
        return;
    }
    name = n.trimmed();
}

bool RLayer::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = false;

    if (PropertyName == propertyTypeId && name == "0") {
        return false;
    }

    ret = RObject::setMember(name, value.toString().trimmed(), PropertyName == propertyTypeId);
    ret = ret || RObject::setMember(frozen, value, PropertyFrozen == propertyTypeId);
    ret = ret || RObject::setMember(locked, value, PropertyLocked == propertyTypeId);
    ret = ret || RObject::setMember(color, value, PropertyColor == propertyTypeId);

    if (propertyTypeId == PropertyLinetype) {
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            ret = ret || RObject::setMember(linetype, value.toInt(), true);
        } else if (value.type() == QVariant::String) {
            if (getDocument() != NULL) {
                ret = ret || RObject::setMember(linetype,
                        getDocument()->getLinetypeId(value.toString()), true);
            }
        }
    }

    if (PropertyLineweight == propertyTypeId) {
        lineweight = value.value<RLineweight::Lineweight>();
        ret = true;
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLayer::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyFrozen) {
        return qMakePair(QVariant(frozen), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyLocked) {
        return qMakePair(QVariant(locked), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyColor) {
        QVariant v;
        v.setValue(color);
        return qMakePair(v, RPropertyAttributes());
    }

    if (propertyTypeId == PropertyLinetype) {
        if (humanReadable) {
            if (getDocument() != NULL) {
                RPropertyAttributes attr;
                if (!noAttributes) {
                    attr.setChoices(getDocument()->getLinetypeNames());
                }
                QVariant v;
                QSharedPointer<RLinetype> lt = getDocument()->queryLinetype(
                        linetype);
                v.setValue<RLinetype> (*lt.data());
                return qMakePair(v, attr);
//                return qMakePair(QVariant(getDocument()->getLinetypeName(
//                        linetype)), attr);
            }
        } else {
            return qMakePair(QVariant(linetype), RPropertyAttributes());
        }
    }

    if (propertyTypeId == PropertyLineweight) {
        QVariant v;
        v.setValue(lineweight);
        return qMakePair(v, RPropertyAttributes());
    }

    //return qMakePair(QVariant(), RPropertyAttributes());
    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes);
}

bool RLayer::isSelectedForPropertyEditing() {
    return false;
}


/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLayer& l) {
    dbg.nospace()
       << "RLayer("
       << (RObject&) l
       << ", name: " << l.getName()
       << ", color: " << l.getColor()
       << ", lineweight: " << l.getLineweight()
       << ", linetype: " << l.getLinetypeId()
       << ")";
    return dbg.space();
}
