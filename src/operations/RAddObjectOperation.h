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

#ifndef RADDOBJECTOPERATION_H
#define RADDOBJECTOPERATION_H

#include "operations_global.h"

#include <QSharedPointer>

#include "RAddObjectsOperation.h"
#include "ROperation.h"
#include "RVector.h"

class RObject;

/**
 * Implementation of an operation that adds entities.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RAddObjectOperation: public RAddObjectsOperation {
public:
    RAddObjectOperation() {}
    RAddObjectOperation(QSharedPointer<RObject> object, const QString& text,
                        bool useCurrentAttributes = true, bool undoable = true);
    RAddObjectOperation(QSharedPointer<RObject> object,
       bool useCurrentAttributes = true, bool undoable = true);
    virtual ~RAddObjectOperation() {
    }
};

Q_DECLARE_METATYPE(RAddObjectOperation*)

#endif
