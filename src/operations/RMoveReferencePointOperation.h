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

#ifndef RMOVEREFERENCEPOINTOPERATION_H
#define RMOVEREFERENCEPOINTOPERATION_H

#include "operations_global.h"

#include "RDocument.h"
#include "RExporter.h"
#include "RGraphicsScene.h"
#include "ROperation.h"
#include "RVector.h"

class REntity;

/**
 * Implementation of an operation that moves a reference point
 * by a given distance.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RMoveReferencePointOperation : public ROperation {
public:
    RMoveReferencePointOperation(
        const RVector& referencePoint, const RVector& targetPoint,
        Qt::KeyboardModifiers modifiers
    );
    virtual ~RMoveReferencePointOperation() {}
    
    virtual RTransaction apply(RDocument& document, bool preview = false);

    void setGraphicsScene(RGraphicsScene* s) {
        scene = s;
    }

private:
    RVector referencePoint;
    RVector targetPoint;
    Qt::KeyboardModifiers modifiers;
    RGraphicsScene* scene;
};

Q_DECLARE_METATYPE(RMoveReferencePointOperation*)

#endif
