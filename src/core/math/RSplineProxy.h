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
    virtual ~RSplineProxy() {}
    virtual void init() = 0;
    virtual void uninit() = 0;
    virtual RSpline updateFromFitPoints(const RSpline& spline, bool rec = false) = 0;
    virtual QList<RSpline> split(const RSpline& spline, const QList<double>& params) = 0;
    virtual QList<RSpline> splitEqual(const RSpline& spline, int pieces) = 0;
    virtual double getTAtPoint(const RSpline& spline, const RVector& point) = 0;
    virtual double getTAtDistance(const RSpline& spline, double dist) = 0;
    virtual double getDistanceAtT(const RSpline& spline, double t) = 0;
    virtual RVector getVectorTo(const RSpline& spline, const RVector& point, bool limited=true, double strictRange=RMAXDOUBLE) = 0;
    virtual RSpline simplify(const RSpline& spline, double tolerance) = 0;
    virtual RPolyline approximateWithArcs(const RSpline& spline, double tolerance=0.001) = 0;
    virtual QList<RVector> getIntersectionPoints(const RSpline& spline, const RShape& other, bool limited=true, bool same=false) = 0;
};

#endif
