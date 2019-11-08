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

#ifndef RMOVESELECTIONOPERATION_H
#define RMOVESELECTIONOPERATION_H

#include "operations_global.h"

#include "RDocument.h"
#include "REntity.h"
#include "RExporter.h"
#include "ROperation.h"
#include "RVector.h"


/**
 * Implementation of an operation that moves a selection
 * by a given distance.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RMoveSelectionOperation : public ROperation {
public:
    RMoveSelectionOperation(
        const RVector& referencePoint, const RVector& targetPoint
    );

    virtual ~RMoveSelectionOperation() { }
    
    virtual RTransaction apply(RDocument& document, bool preview = false);

//protected:
//    void move(RDocument& document, RTransaction& transaction, REntity::Id entityId);

private:

    RVector referencePoint;
    RVector targetPoint;
};

Q_DECLARE_METATYPE(RMoveSelectionOperation*)

#endif
