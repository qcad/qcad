/**
 * Copyright (c) 2011-2025 by Andrew Mustun. All rights reserved.
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

#ifndef RARCPROXY_H
#define RARCPROXY_H

#include "../core_global.h"

#include "RS.h"
#include "RVector.h"

class RArc;


/**
 * Proxy for advanced arc functionality. May be implemented
 * by a plugin.
 *
 * \ingroup math
 */
class QCADCORE_EXPORT RArcProxy {
public:
    virtual ~RArcProxy() {}

    virtual RArc createTangential(const RVector& startPoint, const RVector& pos, double direction, double radius, double sweep) = 0;
};

#endif
