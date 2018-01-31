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

#ifndef RCOPYOPERATION_H
#define RCOPYOPERATION_H

#include "operations_global.h"

#include "RDocument.h"
#include "REntity.h"
#include "RExporter.h"
#include "RClipboardOperation.h"
#include "RVector.h"


/**
 * Implementation of an operation that copies the selection of the
 * given document to the clipboard
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RCopyOperation : public RClipboardOperation {
public:
    RCopyOperation(const RVector& offset, RDocument& src);
    virtual ~RCopyOperation() {}
    
    virtual RTransaction apply(RDocument& document, bool preview = false);

    void setClear(bool on) {
        clear = on;
    }

private:
    bool clear;
    RVector offset;
    RDocument& src;
};

Q_DECLARE_METATYPE(RCopyOperation*)

#endif
