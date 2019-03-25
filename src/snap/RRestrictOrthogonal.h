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

#ifndef RRESTRICTORTHOGONAL_H
#define RRESTRICTORTHOGONAL_H

#include "snap_global.h"

#include "RSnapRestriction.h"

class RDocumentInterface;

/**
 * \brief Orthogonal snap restriction implementation.
 *
 * \scriptable
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RRestrictOrthogonal : public RSnapRestriction {
public:
    RRestrictOrthogonal(RDocumentInterface* documentInterface)
        : RSnapRestriction(documentInterface), 
          mode(RS::Orthogonal) {}
    virtual ~RRestrictOrthogonal() {}

    virtual RVector restrictSnap(const RVector& position, const RVector& relativeZero);

protected:
    RS::OrthoMode mode;
};

Q_DECLARE_METATYPE(RRestrictOrthogonal*)

#endif
