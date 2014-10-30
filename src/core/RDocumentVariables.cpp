/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
#include "RDocumentVariables.h"
#include "RDxfServices.h"

RPropertyTypeId RDocumentVariables::PropertyCustom;
RPropertyTypeId RDocumentVariables::PropertyHandle;
RPropertyTypeId RDocumentVariables::PropertyCurrentLayerId;
RPropertyTypeId RDocumentVariables::PropertyUnit;
RPropertyTypeId RDocumentVariables::PropertyLinetypeScale;
RPropertyTypeId RDocumentVariables::PropertyDimensionFont;

RDocumentVariables::RDocumentVariables(RDocument* document, RObject::Id objectId)
        : RObject(document, objectId),
        currentLayerId(RLayer::INVALID_ID),
        unit(RS::None),
        linetypeScale(1.0) {
}

RDocumentVariables::~RDocumentVariables() {
}

void RDocumentVariables::init() {
    RDocumentVariables::PropertyCustom.generateId(typeid(RDocumentVariables), RObject::PropertyCustom);
    RDocumentVariables::PropertyHandle.generateId(typeid(RDocumentVariables), RObject::PropertyHandle);
    RDocumentVariables::PropertyCurrentLayerId.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Current Layer ID"));
    RDocumentVariables::PropertyUnit.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Drawing Unit"));
    RDocumentVariables::PropertyLinetypeScale.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Linetype Scale"));
    RDocumentVariables::PropertyDimensionFont.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Dimension Font"));
}

QSet<RPropertyTypeId> RDocumentVariables::getCustomPropertyTypeIds() const {
    QSet<RPropertyTypeId> ret;

    for (int i=RS::ANGBASE; i<=RS::MaxKnownVariable; i++) {
        RS::KnownVariable v = (RS::KnownVariable)i;

        //qDebug() << "var property: " << RDxfServices::variableToString(v);
        ret.insert(RPropertyTypeId("QCAD", RDxfServices::variableToString(v)));
    }

    ret.unite(RObject::getCustomPropertyTypeIds());

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDocumentVariables::getProperty(RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyCurrentLayerId) {
        return qMakePair(QVariant(currentLayerId), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyUnit) {
        return qMakePair(QVariant(unit), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyLinetypeScale) {
        return qMakePair(QVariant(linetypeScale), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyDimensionFont) {
        return qMakePair(QVariant(dimensionFont), RPropertyAttributes());
    }

    if (propertyTypeId.isCustom()) {
        QString appId = propertyTypeId.getCustomPropertyTitle();
        QString name = propertyTypeId.getCustomPropertyName();
        RS::KnownVariable v = RDxfServices::stringToVariable(name);
        if (appId=="QCAD" && v!=RS::INVALID) {
            return qMakePair(getKnownVariable(v), RPropertyAttributes(RPropertyAttributes::KnownVariable));
        }
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes);
}

bool RDocumentVariables::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = false;

    ret = ret || RObject::setMember(currentLayerId, value, PropertyCurrentLayerId == propertyTypeId);
    ret = ret || RObject::setMember((int&)unit, value, PropertyUnit == propertyTypeId);
    ret = ret || RObject::setMember(linetypeScale, value, PropertyLinetypeScale == propertyTypeId);
    ret = ret || RObject::setMember(dimensionFont, value, PropertyDimensionFont == propertyTypeId);

    // custom property that is a known variable:
    if (propertyTypeId.isCustom()) {
        QString appId = propertyTypeId.getCustomPropertyTitle();
        QString name = propertyTypeId.getCustomPropertyName();
        RS::KnownVariable v = RDxfServices::stringToVariable(name);
        if (appId=="QCAD" && v!=RS::INVALID) {
            setKnownVariable(v, value);
            ret = true;
        }
    }

    ret = ret || RObject::setProperty(propertyTypeId, value, transaction);

    return ret;
}

void RDocumentVariables::clear() {
    knownVariables.clear();
}

void RDocumentVariables::setKnownVariable(RS::KnownVariable key, QVariant value) {
    if (key==RS::INSUNITS) {
        setUnit((RS::Unit)value.toInt());
    }
    // TODO:
//    else if (key==RS::LTSCALE) {
//        setLinetypeScale(value.toDouble());
//    }

    knownVariables.insert(key, value);
}

QVariant RDocumentVariables::getKnownVariable(RS::KnownVariable key) const {
    if (key==RS::INSUNITS) {
        return getUnit();
    }

//    if (key==RS::LTSCALE) {
//        // TODO
//        return getLinetypeScale();
//    }

    // if DIMADEC is -1, DIMDEC is used:
    if (key==RS::DIMADEC &&
        hasKnownVariable(RS::DIMDEC) &&
        getKnownVariable(RS::DIMDEC).toInt()==-1) {

        return getKnownVariable(RS::DIMDEC);
    }

    if (key==RS::DWGCODEPAGE) {
        return QVariant("ANSI_1252");
    }

    return knownVariables.value(key);
}

bool RDocumentVariables::hasKnownVariable(RS::KnownVariable key) const {
    return knownVariables.contains(key);
}

void RDocumentVariables::print(QDebug dbg) const {
    dbg.nospace() << "RDocumentVariables(";
    RObject::print(dbg);
    dbg.nospace()
        << "\nunit: " << getUnit()
        << "\ncurrentLayerId: " << getCurrentLayerId()
        << "\npoint mode: " << getKnownVariable(RS::PDMODE)
        << "\ndimension font: " << getDimensionFont()
        << ")";
}
