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
#include "RDocumentVariables.h"
#include "RDxfServices.h"

RPropertyTypeId RDocumentVariables::PropertyCustom;
RPropertyTypeId RDocumentVariables::PropertyHandle;
RPropertyTypeId RDocumentVariables::PropertyProtected;
RPropertyTypeId RDocumentVariables::PropertyCurrentLayerId;
RPropertyTypeId RDocumentVariables::PropertyUnit;
RPropertyTypeId RDocumentVariables::PropertyLinetypeScale;
RPropertyTypeId RDocumentVariables::PropertyDimensionFont;
RPropertyTypeId RDocumentVariables::PropertyWorkingSetBlockReferenceId;

RDocumentVariables::RDocumentVariables(RDocument* document)
        : RObject(document),
        currentLayerId(RLayer::INVALID_ID),
        unit(RS::None),
        measurement(RS::UnknownMeasurement),
        linetypeScale(1.0),
        workingSetBlockReferenceId(RObject::INVALID_ID) {
}

RDocumentVariables::~RDocumentVariables() {
}

void RDocumentVariables::init() {
    RDocumentVariables::PropertyCustom.generateId(typeid(RDocumentVariables), RObject::PropertyCustom);
    RDocumentVariables::PropertyHandle.generateId(typeid(RDocumentVariables), RObject::PropertyHandle);
    RDocumentVariables::PropertyProtected.generateId(typeid(RDocumentVariables), RObject::PropertyProtected);
    RDocumentVariables::PropertyCurrentLayerId.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Current Layer ID"));
    RDocumentVariables::PropertyUnit.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Drawing Unit"));
    RDocumentVariables::PropertyLinetypeScale.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Linetype Scale"));
    RDocumentVariables::PropertyDimensionFont.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Dimension Font"));
    RDocumentVariables::PropertyWorkingSetBlockReferenceId.generateId(typeid(RDocumentVariables), "", "Working Set Block Reference Id");
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
        bool humanReadable, bool noAttributes, bool showOnRequest) {

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

    if (propertyTypeId == PropertyWorkingSetBlockReferenceId) {
        return qMakePair(QVariant(workingSetBlockReferenceId), RPropertyAttributes());
    }

    if (propertyTypeId.isCustom()) {
        QString appId = propertyTypeId.getCustomPropertyTitle();
        QString name = propertyTypeId.getCustomPropertyName();
        RS::KnownVariable v = RDxfServices::stringToVariable(name);
        if (appId=="QCAD" && v!=RS::INVALID) {
            // custom property is a known DXF variable:
            return qMakePair(getKnownVariable(v), RPropertyAttributes(RPropertyAttributes::KnownVariable));
        }
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

bool RDocumentVariables::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = false;

    ret = ret || RObject::setMember(currentLayerId, value, PropertyCurrentLayerId == propertyTypeId);
    ret = ret || RObject::setMember((int&)unit, value, PropertyUnit == propertyTypeId);
    ret = ret || RObject::setMember(linetypeScale, value, PropertyLinetypeScale == propertyTypeId);
    ret = ret || RObject::setMember(dimensionFont, value, PropertyDimensionFont == propertyTypeId);
    ret = ret || RObject::setMember(workingSetBlockReferenceId, value, PropertyWorkingSetBlockReferenceId == propertyTypeId);

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

void RDocumentVariables::setKnownVariable(RS::KnownVariable key, const RVector& value) {
    QVariant v;
    v.setValue(value);
    knownVariables.insert(key, v);
}

void RDocumentVariables::setKnownVariable(RS::KnownVariable key, const RColor& value) {
    QVariant v;
    v.setValue(value);
    knownVariables.insert(key, v);
}

void RDocumentVariables::setKnownVariable(RS::KnownVariable key, const QVariant& value) {
    switch (key) {
    case RS::INSUNITS:
        setUnit((RS::Unit)value.toInt());
        break;
    case RS::MEASUREMENT:
        setMeasurement((RS::Measurement)value.toInt());
        break;
    case RS::LTSCALE:
        setLinetypeScale(value.toDouble());
        break;
    default:
        break;
    }

    knownVariables.insert(key, value);
}

QVariant RDocumentVariables::getKnownVariable(RS::KnownVariable key) const {
    switch (key) {
    case RS::INSUNITS:
        return getUnit();

    case RS::LTSCALE:
        return getLinetypeScale();

    // if DIMADEC is -1, DIMDEC is used:
    case RS::DIMADEC:
        if (hasKnownVariable(RS::DIMDEC) &&
            knownVariables.value(RS::DIMADEC).toInt()==-1) {
            return getKnownVariable(RS::DIMDEC);
        }
        break;

    case RS::DWGCODEPAGE:
        return QVariant("ANSI_1252");

    default:
        break;
    }

    return knownVariables.value(key);
}

bool RDocumentVariables::hasKnownVariable(RS::KnownVariable key) const {
    return knownVariables.contains(key);
}

QString RDocumentVariables::addAutoVariable(double value) {
    int c = getCustomIntProperty("QCAD", "AutoVariableCounter", 0);
    c++;

    QString key = QString("d%1").arg(c);

    setCustomProperty("QCAD", key, value);
    setCustomProperty("QCAD", "AutoVariableCounter", c);

    return key;
}

QStringList RDocumentVariables::getAutoVariables() const {
    QStringList ret;
    int c = getCustomIntProperty("QCAD", "AutoVariableCounter", 0);
    QString key;
    for (int i=1; i<=c; i++) {
        key = QString("d%1").arg(i);
        if (hasCustomProperty("QCAD", key)) {
            ret.append(key);
        }
    }
    return ret;
}

void RDocumentVariables::print(QDebug dbg) const {
    dbg.nospace() << "RDocumentVariables(";
    RObject::print(dbg);
    dbg.nospace()
        << "\nunit: " << getUnit()
        << "\ncurrentLayerId: " << getCurrentLayerId()
        << "\npoint mode: " << getKnownVariable(RS::PDMODE)
        << "\ndimension font: " << getDimensionFont()
        << "\ndimension text color: " << getKnownVariable(RS::DIMCLRT)
        << ")";
}
