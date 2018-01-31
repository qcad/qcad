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

#ifndef RMOUSECOORDINATELISTENER_H
#define RMOUSECOORDINATELISTENER_H

#include "core_global.h"

class RVector;

/**
 * Abstract base class for classes that are interested in
 * the current coordinate of the mouse cursor. This can for example
 * be a widget that displays the cursor coordinate.
 *
 * \ingroup core
 */
class QCADCORE_EXPORT RMouseCoordinateListener {
public:
    virtual ~RMouseCoordinateListener() {}
    /**
     * Notifies this listener if the current mouse position has changed.
     *
     * \param wcsPosition world coordinate position
     * \param ucsPosition user coordinate position
     */
    virtual void setCoordinate(const RVector& wcsPosition, const RVector& ucsPosition) = 0;
};

#endif
