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

#include "RS.h"

class RShape;
class RVector;


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

    /**
     * Traces the inner most (smallest) closed contour around the given position
     * from the arrangement formed by the given shapes.
     *
     * \param position Point inside the region to trace (e.g. a click point).
     * \param shapes Boundary shapes (lines, arcs, circles, ellipses, splines,
     *      polylines) that may form contours. Polylines are exploded internally.
     * \return The ordered shapes forming the traced contour (counter-clockwise),
     *      or an empty list if no closed contour was found.
     */
    virtual QList<QSharedPointer<RShape> > getInnerMostContour(const RVector& position, const QList<QSharedPointer<RShape> >& shapes) = 0;
};

#endif
