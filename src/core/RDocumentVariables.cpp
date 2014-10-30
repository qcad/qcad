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

RPropertyTypeId RDocumentVariables::PropertyCustom;
RPropertyTypeId RDocumentVariables::PropertyHandle;
RPropertyTypeId RDocumentVariables::PropertyCurrentLayerId;
RPropertyTypeId RDocumentVariables::PropertyUnit;


RDocumentVariables::~RDocumentVariables() {
}

void RDocumentVariables::init() {
    RDocumentVariables::PropertyCustom.generateId(typeid(RDocumentVariables), RObject::PropertyCustom);
    RDocumentVariables::PropertyHandle.generateId(typeid(RDocumentVariables), RObject::PropertyHandle);
    RDocumentVariables::PropertyCurrentLayerId.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Current Layer ID"));
    RDocumentVariables::PropertyUnit.generateId(typeid(RDocumentVariables), "", QT_TRANSLATE_NOOP("RDocumentVariables", "Drawing unit"));
}

QPair<QVariant, RPropertyAttributes> RDocumentVariables::getProperty(RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyCurrentLayerId) {
        return qMakePair(QVariant(currentLayerId), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyUnit) {
        return qMakePair(QVariant(unit), RPropertyAttributes());
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes);
}

bool RDocumentVariables::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = RObject::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(currentLayerId, value, PropertyCurrentLayerId == propertyTypeId);
    ret = ret || RObject::setMember((int&)unit, value, PropertyUnit == propertyTypeId);

    return ret;
}

void RDocumentVariables::print(QDebug dbg) const {
    dbg.nospace() << "RDocumentVariables(";
    RObject::print(dbg);
    dbg.nospace()
        << "\nunit: " << getUnit()
        << "\ncurrentLayerId: " << getCurrentLayerId()
        << ")";
}
