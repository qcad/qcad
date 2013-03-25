/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RSNAPLISTENER_H
#define RSNAPLISTENER_H

#include "core_global.h"

#include "RSnap.h"

class RDocumentInterface;
class REntity;



/**
 * \brief Abstract base class for classes that are interested in the current 
 * snap mode.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RSnapListener {
public:
    virtual ~RSnapListener() {}

    /**
     * Called by the document whenever the current snap mode changes.
     */
    virtual void updateSnap(RDocumentInterface* di) = 0;
};

Q_DECLARE_METATYPE(RSnapListener*)

#endif
