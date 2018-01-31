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

#ifndef RSNAPRESTRICTION_H
#define RSNAPRESTRICTION_H

#include "core_global.h"

#include "RVector.h"

class RDocumentInterface;

/**
 * \brief Abstract base class for all snap restriction implementations.
 *
 * \scriptable
 * \generateScriptShell
 *
 * \ingroup core
 */
class QCADCORE_EXPORT RSnapRestriction {
public:
    RSnapRestriction(RDocumentInterface* documentInterface = NULL) :
        documentInterface(documentInterface),
        lastSnap(RVector::invalid) {}
    virtual ~RSnapRestriction() {}

    /**
     * \return The snapped position (closest relevant position)
     * for the given mouse position.
     */
    virtual RVector restrictSnap(const RVector& position, const RVector& relativeZero) = 0;

    virtual void showUiOptions() {}
    virtual void hideUiOptions() {}

    RVector getLastSnap() const {
        return lastSnap;
    }

    void reset() {
        lastSnap = RVector::invalid;
    }

protected:
    RDocumentInterface* documentInterface;
    RVector lastSnap;
};

Q_DECLARE_METATYPE(RSnapRestriction*)

#endif
