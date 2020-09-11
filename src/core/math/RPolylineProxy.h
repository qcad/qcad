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

#ifndef RPOLYLINEPROXY_H
#define RPOLYLINEPROXY_H

#include "../core_global.h"

#include <RS.h>
#include <RMath.h>

class RArc;
class RExporter;
class RLine;
class RPainterPath;
class RPolyline;
class RVector;


/**
 * Proxy for advanced polyline functionality. May be implemented
 * by a plugin.
 *
 * \ingroup math
 */
class QCADCORE_EXPORT RPolylineProxy {
public:
    virtual ~RPolylineProxy() {}
    virtual RS::Ending getTrimEnd(RPolyline& polyline, const RVector& trimPoint, const RVector& clickPoint) = 0;
    virtual bool trimStartPoint(RPolyline& polyline, const RVector& trimPoint, const RVector& clickPoint, bool extend = false) = 0;
    virtual bool trimEndPoint(RPolyline& polyline, const RVector& trimPoint, const RVector& clickPoint, bool extend = false) = 0;
    virtual bool trimStartPoint(RPolyline& polyline, double trimDist) = 0;
    virtual bool trimEndPoint(RPolyline& polyline, double trimDist) = 0;
    virtual bool relocateStartPoint(RPolyline& polyline, const RVector& p) = 0;
    virtual bool relocateStartPoint(RPolyline& polyline, double dist) = 0;
    virtual int getSegmentAtDist(const RPolyline& polyline, double dist) = 0;

    virtual QList<RPolyline> renderThickPolyline(const RPolyline& polyline) = 0;
    virtual QList<QPair<RPolyline, RPolyline> > getLeftRightOutline(const RPolyline& polyline) = 0;
    virtual QList<RVector> verifyTangency(const RPolyline& polyline, double toleranceMin = RS::AngleTolerance, double toleranceMax = M_PI_4) = 0;
    virtual double getArea(const RPolyline& polyline, double segmentLength) = 0;
    virtual RVector getPointInside(const RPolyline& polyline) = 0;

    virtual QList<RPolyline> splitAtDiscontinuities(const RPolyline& polyline, double tolerance) = 0;

    virtual double getBaseAngle(const RPolyline& polyline) = 0;
    virtual double getWidth(const RPolyline& polyline) = 0;
    virtual bool setWidth(RPolyline& polyline, double v) = 0;
    virtual double getHeight(const RPolyline& polyline) = 0;
    virtual bool setHeight(RPolyline& polyline, double v) = 0;

    virtual QList<RPolyline> morph(const RPolyline& polyline, const RPolyline& target, int steps, RS::Easing easing = RS::Linear, bool zLinear = true, double customFactor = RNANDOUBLE) = 0;
    virtual RPolyline roundAllCorners(const RPolyline& polyline, double radius) = 0;
    virtual RPolyline getPolygonHull(const RPolyline& polyline, double angle, double tolerance, bool inner = false) = 0;
    virtual RVector insertVertexAtDistance(RPolyline& polyline, double dist) = 0;

    virtual bool simplify(RPolyline& polyline, double tolerance) = 0;
    virtual QList<RPolyline> splitAtSegmentTypeChange(const RPolyline& polyline) = 0;
};

#endif
