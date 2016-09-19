/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

#ifndef RLAYERPROXY_H
#define RLAYERPROXY_H

#include "../core_global.h"

#include "RLayer.h"


/**
 * Proxy for advanced layer functionality. May be implemented
 * by a plugin.
 *
 * \ingroup core
 */
class QCADCORE_EXPORT RLayerProxy {
public:
    virtual ~RLayerProxy() {}

    virtual QString getHierarchySeparator() = 0;
    virtual bool hasChildLayers(const RDocument* doc, const QString& layerName) = 0;
    virtual QList<QString> getChildLayerNames(const RDocument* doc, const QString& layerName, bool recursive = true) = 0;
    virtual QString getParentLayerName(const QString& layerName) = 0;
    virtual QString getShortLayerName(const QString& layerName) = 0;
    virtual QList<QString> getLayerNameHierarchy(const QString& layerName) = 0;
    virtual bool isChildLayerOf(const QString& layerName, const QString& parentLayerName) = 0;
};

#endif
