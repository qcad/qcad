/**
 * Copyright (c) 2011-2021 by Andrew Mustun. All rights reserved.
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

#ifndef RDIMSTYLEPROXY_H
#define RDIMSTYLEPROXY_H

#include "../core_global.h"

class RDimStyle;
class REntityData;
//class RExporter;

/**
 * Proxy for advanced dimension style functionality and rendering. May be implemented
 * by a plugin.
 *
 * \ingroup entity
 */
class QCADCORE_EXPORT RDimStyleProxy {
public:
    virtual ~RDimStyleProxy() {}

    virtual void render(const RDimStyle& dimStyle, const REntityData& entityData, bool preview, bool forceSelected) = 0;
};

#endif
