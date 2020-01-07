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
#include "RLinetype.h"
#include "RSettings.h"
#include "RMetaTypes.h"


RPropertyTypeId RLinetype::PropertyName;
RPropertyTypeId RLinetype::PropertyDescription;
RPropertyTypeId RLinetype::PropertyMetric;
RPropertyTypeId RLinetype::PropertyPatternString;

RLinetype::RLinetype(RDocument* document) : RObject(document) {
}

RLinetype::RLinetype(RDocument* document, const RLinetypePattern& pattern)
    : RObject(document), pattern(pattern) {
}

RLinetype::RLinetype(const RLinetype& other) : RObject(other) {
    pattern = other.pattern;
}

RLinetype::~RLinetype() {
}

bool RLinetype::operator==(const RLinetype & linetype) const {
    return getName().compare(linetype.getName(), Qt::CaseInsensitive) == 0;
}

bool RLinetype::operator!=(const RLinetype & linetype) const{
    return !operator ==(linetype);
}

void RLinetype::init() {
    RLinetype::PropertyName.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Name"));
    RLinetype::PropertyDescription.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Description"));
    RLinetype::PropertyMetric.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Metric"));
    RLinetype::PropertyPatternString.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Pattern"));
}

bool RLinetype::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    Q_UNUSED(transaction)

    bool ret = false;
    ret = RObject::setMember(pattern.name, value, PropertyName == propertyTypeId);
    ret = RObject::setMember(pattern.description, value, PropertyDescription == propertyTypeId);
    ret = RObject::setMember(pattern.metric, value, PropertyMetric == propertyTypeId);

    if (propertyTypeId==PropertyPatternString) {
        if (pattern.getPatternString()!=value.toString()) {
            pattern.setPatternString(value.toString());
            ret = true;
        }
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RLinetype::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(pattern.name), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyDescription) {
        return qMakePair(QVariant(pattern.description), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyMetric) {
        return qMakePair(QVariant(pattern.metric), RPropertyAttributes());
    }
    if (propertyTypeId == PropertyPatternString) {
        QVariant v;
        v.setValue(pattern.getPatternString());
        return qMakePair(v, RPropertyAttributes());
    }

    //return qMakePair(QVariant(), RPropertyAttributes());
    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

bool RLinetype::isValid() const {
    return !pattern.name.isNull();
}

RLinetypePattern RLinetype::getPattern() const {
    return pattern;
}

void RLinetype::setPattern(const RLinetypePattern& p) {
    pattern = p;
}

bool RLinetype::operator<(const RLinetype & linetype) const {
    return getName().toLower() < linetype.getName().toLower();
}

void RLinetype::print(QDebug dbg) const {
    dbg.nospace() << "RLinetype(";
    RObject::print(dbg);
    dbg.nospace()
        << ", pattern: " << getPattern()
        << ")";
}
