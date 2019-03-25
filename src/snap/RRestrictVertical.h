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

#ifndef RRESTRICTVERTICAL_H
#define RRESTRICTVERTICAL_H

#include "snap_global.h"

#include "RRestrictOrthogonal.h"

class RDocumentInterface;

/**
 * \brief Vertical snap restriction implementation.
 *
 * \scriptable
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RRestrictVertical : public RRestrictOrthogonal {
public:
    RRestrictVertical(RDocumentInterface* documentInterface)
        : RRestrictOrthogonal(documentInterface) {
        mode = RS::OrthoVertical;
    }
    virtual ~RRestrictVertical() {}

    //virtual RVector restrictSnap(const RVector& position, const RVector& relativeZero);
};

Q_DECLARE_METATYPE(RRestrictVertical*)

#endif
