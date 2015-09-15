/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

class RArc;
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
    virtual void trimStartPoint(RPolyline& polyline, const RVector& p) = 0;
    virtual void trimEndPoint(RPolyline& polyline, const RVector& p) = 0;

    virtual void exportThickLine(RPainterPath& path, const RLine& line, double w1, double w2) = 0;
    virtual void exportThickArc(RPainterPath& path, const RArc& arc, double w1, double w2) = 0;
};

#endif
