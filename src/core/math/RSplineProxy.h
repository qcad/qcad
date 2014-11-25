/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#ifndef RSPLINEPROXY_H
#define RSPLINEPROXY_H

#include "../core_global.h"

#include "RSpline.h"


/**
 * Proxy for advanced spline functionality. May be implemented
 * by a plugin.
 *
 * \ingroup math
 */
class QCADCORE_EXPORT RSplineProxy {
public:
    virtual void init() = 0;
    virtual void uninit() = 0;
    virtual RSpline updateFromFitPoints(const RSpline& spline, bool useTangents) = 0;
    virtual QList<RSpline> split(const RSpline& spline, const QList<RVector>& points) = 0;
    virtual double getTAtPoint(const RSpline& spline, const RVector& point) = 0;
    virtual double getTAtDistance(const RSpline& spline, double dist) = 0;
    virtual RVector getClosestPointOnShape(const RSpline& spline, const RVector& point, bool limited = true) = 0;
    //virtual QList<RVector> getIntersectionPoints(const RSpline& spline, const RShape& other, bool limited=true, bool same=false) = 0;
};

#endif
