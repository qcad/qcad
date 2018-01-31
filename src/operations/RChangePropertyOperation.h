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

#ifndef RCHANGEPROPERTYOPERATION_H
#define RCHANGEPROPERTYOPERATION_H

#include "operations_global.h"

#include <QVariant>

#include "RDocument.h"
#include "RExporter.h"
#include "ROperation.h"
#include "RPropertyEvent.h"
#include "RPropertyTypeId.h"
#include "RTransaction.h"

/**
 * Implementation of an operation that changes a given property to
 * a given value for the selection in a document.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RChangePropertyOperation : public ROperation {
public:
    RChangePropertyOperation(
        const RPropertyTypeId& propertyTypeId,
        const QVariant& value,
        RS::EntityType entityTypeFilter = RS::EntityAll,
        bool undoable = true
    );

    RChangePropertyOperation(
        const RPropertyEvent& event,
        bool undoable = true);

    virtual ~RChangePropertyOperation() {}
    
    virtual RTransaction apply(RDocument& document, bool preview = false);

private:
    RPropertyTypeId propertyTypeId;
    QVariant value;
};

Q_DECLARE_METATYPE(RChangePropertyOperation*)

#endif
