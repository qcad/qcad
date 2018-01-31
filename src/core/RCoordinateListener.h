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

#ifndef RCOORDINATELISTENER_H
#define RCOORDINATELISTENER_H

#include "core_global.h"

#include <QMetaType>

class RDocumentInterface;


/**
 * \brief Abstract base class for classes that are interested in 
 * the current coordinate of the mouse cursor. This can for example
 * be a widget that displays the cursor coordinate.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RCoordinateListener {
public:
    virtual ~RCoordinateListener() {}
    virtual void updateCoordinate(RDocumentInterface* documentInterface) = 0;
};

Q_DECLARE_METATYPE(QList<RCoordinateListener*>)
Q_DECLARE_METATYPE(RCoordinateListener*)

#endif
