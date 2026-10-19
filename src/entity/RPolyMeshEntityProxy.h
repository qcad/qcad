/**
 * Copyright (c) 2011-2026 by Andrew Mustun. All rights reserved.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RPOLYMESHENTITYPROXY_H
#define RPOLYMESHENTITYPROXY_H

#include "entity_global.h"

class RExporter;
class RPolyMeshEntity;

/**
 * Proxy for polygon mesh entity functionality (rendering). May be
 * implemented by a plugin.
 *
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPolyMeshEntityProxy {
public:
    virtual ~RPolyMeshEntityProxy() {}

    /**
     * Exports the given mesh entity to the given exporter (edges for 2D
     * exports, triangles for 3D views).
     */
    virtual void exportEntity(const RPolyMeshEntity& entity, RExporter& e, bool preview, bool forceSelected) const = 0;
};

#endif
