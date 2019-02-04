/**
 * Copyright (c) 2011-2019 by Andrew Mustun. All rights reserved.
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

#ifndef RSHAPEPROXY_H
#define RSHAPEPROXY_H

#include "../core_global.h"

#include <RS.h>
#include <RMath.h>

class RShape;


/**
 * Proxy for advanced shape functionality. May be implemented
 * by a plugin.
 *
 * \ingroup math
 */
class QCADCORE_EXPORT RShapeProxy {
public:
    virtual ~RShapeProxy() {}

    virtual QList<QSharedPointer<RShape> > roundAllCorners(const QList<QSharedPointer<RShape> >& shapes, double radius) = 0;
};

#endif
