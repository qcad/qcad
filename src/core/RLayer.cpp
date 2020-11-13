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
#include "RLayer.h"
#include "RDocument.h"

RLayerProxy* RLayer::layerProxy = NULL;

RPropertyTypeId RLayer::PropertyCustom;
RPropertyTypeId RLayer::PropertyType;
RPropertyTypeId RLayer::PropertyHandle;
RPropertyTypeId RLayer::PropertyProtected;
RPropertyTypeId RLayer::PropertySelected;

RPropertyTypeId RLayer::PropertyName;
RPropertyTypeId RLayer::PropertyOff;
RPropertyTypeId RLayer::PropertyFrozen;
RPropertyTypeId RLayer::PropertyLocked;
RPropertyTypeId RLayer::PropertyCollapsed;
RPropertyTypeId RLayer::PropertyPlottable;
RPropertyTypeId RLayer::PropertySnappable;
RPropertyTypeId RLayer::PropertyOffIsFreeze;
RPropertyTypeId RLayer::PropertyColor;
RPropertyTypeId RLayer::PropertyLinetype;
RPropertyTypeId RLayer::PropertyLineweight;


RLayer::RLayer() :
        RObject(),
        flags(RLayer::Plottable|RLayer::Snappable),
        linetypeId(RLinetype::INVALID_ID),
        lineweight(RLineweight::WeightInvalid) {

    RDebug::incCounter("RLayer");
}

RLayer::RLayer(RDocument* document, const QString& name,
    bool frozen, bool locked, const RColor& color,
    RLinetype::Id linetype, RLineweight::Lineweight lineweight, bool off) :

    RObject(document), name(name.trimmed()),
    color(color), linetypeId(linetype), lineweight(lineweight) {

    setOff(off);
    setFrozen(frozen);
    setLocked(locked);
    setCollapsed(false);
    setPlottable(true);
    setSnappable(true);
    setSelected(false);

    RDebug::incCounter("RLayer");
}

RLayer::RLayer(const RLayer& other) :
    RObject(other),
    name(other.name),
    flags(other.flags),
    color(other.color),
    linetypeId(other.linetypeId),
    lineweight(other.lineweight) {

    RObject::operator=(other);
    RDebug::incCounter("RLayer");
}

RLayer::~RLayer() {
    RDebug::decCounter("RLayer");
}

void RLayer::init() {
    RLayer::PropertyCustom.generateId(typeid(RLayer), RObject::PropertyCustom);
    RLayer::PropertyType.generateId(typeid(RLayer), RObject::PropertyType);
    RLayer::PropertyHandle.generateId(typeid(RLayer), RObject::PropertyHandle);
    RLayer::PropertyProtected.generateId(typeid(RLayer), RObject::PropertyProtected);
    RLayer::PropertySelected.generateId(typeid(RLayer), RObject::PropertySelected);

    RLayer::PropertyName.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Name"));
    RLayer::PropertyOff.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Off"));
    RLayer::PropertyFrozen.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Frozen"));
    RLayer::PropertyLocked.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Locked"));
    RLayer::PropertyCollapsed.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Collapsed"));
    RLayer::PropertyPlottable.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Plottable"));
    RLayer::PropertySnappable.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Snappable"));
    RLayer::PropertyOffIsFreeze.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Off is Freeze"));
    RLayer::PropertyColor.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Color"));
    RLayer::PropertyLinetype.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Linetype"));
    RLayer::PropertyLineweight.generateId(typeid(RLayer), "", QT_TRANSLATE_NOOP("REntity", "Lineweight"));
}

RLayer* RLayer::clone() const {
    return new RLayer(*this);
}

RLayer::Id RLayer::getParentLayerId() const {
    QString parentLayerName = getParentLayerName();
    if (parentLayerName.isEmpty()) {
        return RLayer::INVALID_ID;
    }

    const RDocument* doc = getDocument();
    if (doc==NULL) {
        return RLayer::INVALID_ID;
    }

    return doc->getLayerId(parentLayerName);
}

void RLayer::setName(const QString& n) {
//    if (name == "0") {
//        return;
//    }
    name = n.trimmed();
}

bool RLayer::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {
    bool ret = RObject::setProperty(propertyTypeId, value, transaction);

    if (PropertyName == propertyTypeId) {
        // never change name of layer 0:
        if (name == "0") {
            return false;
        }
        // never change layer name to empty string:
        if (value.toString().isEmpty()) {
            return false;
        }
    }

    ret = ret || RObject::setMember(name, value.toString().trimmed(), PropertyName == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RLayer::Off, value, PropertyOff == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RLayer::Frozen, value, PropertyFrozen == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RLayer::Locked, value, PropertyLocked == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RLayer::Collapsed, value, PropertyCollapsed == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RLayer::Plottable, value, PropertyPlottable == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RLayer::Snappable, value, PropertySnappable == propertyTypeId);
    ret = ret || RObject::setMemberFlag(RLayer::OffIsFreeze, value, PropertyOffIsFreeze == propertyTypeId);
    ret = ret || RObject::setMember(color, value, PropertyColor == propertyTypeId);

    if (propertyTypeId == PropertyLinetype) {
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            ret = ret || RObject::setMember(linetypeId, value.toInt(), true);
        } else {
            RDocument* document = getDocument();
            if (document != NULL) {
                RLinetypePattern t = value.value<RLinetypePattern> ();
                int id = document->getLinetypeId(t.getName());
                ret = ret || RObject::setMember(linetypeId, id, true);
            }
        }
    }
    else if (propertyTypeId == PropertyLineweight) {
        if (value.type()==QVariant::Int || value.type()==QVariant::Double) {
            ret = ret || RObject::setMember((int&)lineweight,
                value.value<int>(), true);
        }
        else {
            ret = ret || RObject::setMember((int&)lineweight,
                (int)value.value<RLineweight::Lineweight>(), true);
        }
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLayer::getProperty(RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyOff) {
        return qMakePair(QVariant(isOff()), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyFrozen) {
        return qMakePair(QVariant(isFrozen()), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyLocked) {
        return qMakePair(QVariant(isLocked()), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyCollapsed) {
        return qMakePair(QVariant(isCollapsed()), RPropertyAttributes(RPropertyAttributes::Invisible));
    }
    if (propertyTypeId == PropertyPlottable) {
        return qMakePair(QVariant(isPlottable()), RPropertyAttributes());
    }
    if (propertyTypeId == PropertySnappable) {
        return qMakePair(QVariant(isSnappable()), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyOffIsFreeze) {
        return qMakePair(QVariant(isOffIsFreeze()), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyColor) {
        QVariant v;
        v.setValue(color);
        return qMakePair(v, RPropertyAttributes());
    }

    if (propertyTypeId == PropertyLinetype) {
        if (humanReadable) {
            RDocument* document = getDocument();
            if (document != NULL) {
                RPropertyAttributes attr;
                //if (!noAttributes) {
                //    attr.setChoices(getDocument()->getLinetypeNames());
                //}
                //QVariant v;
                //QSharedPointer<RLinetype> lt = getDocument()->queryLinetype(linetype);
                //v.setValue<RLinetype> (*lt.data());
                //return qMakePair(v, attr);
//                return qMakePair(QVariant(getDocument()->getLinetypeName(
//                        linetype)), attr);
                QString desc = document->getLinetypeLabel(linetypeId);
                return qMakePair(QVariant(desc), attr);
            }
        } else {
            return qMakePair(QVariant(linetypeId), RPropertyAttributes());
        }
    }

    if (propertyTypeId == PropertyLineweight) {
        QVariant v;
        v.setValue(lineweight);
        return qMakePair(v, RPropertyAttributes());
    }

    //return qMakePair(QVariant(), RPropertyAttributes());
    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLayer& l) {
    dbg.nospace()
       << "\nRLayer("
       << (RObject&) l
       << ", name: " << l.getName()
       << ", color: " << l.getColor()
       << ", lineweight: " << l.getLineweight()
       << ", linetype: " << l.getLinetypeId()
       << ")";
    return dbg.space();
}
