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

/**
 * HierarchicalLayers is provided for backwards compatibility.
 * Use the functions provided in RLayer instead.
 */
function HierarchicalLayers() {
}

HierarchicalLayers.separator = RLayer.getHierarchySeparator();

HierarchicalLayers.hasChildLayers = function(doc, layerName) {
    return RLayer.hasChildLayersStatic(doc, layerName);
};

HierarchicalLayers.getChildLayerNames = function(doc, layerName, recursive) {
    if (isNull(recursive)) {
        recursive = true;
    }

    return RLayer.getChildLayerNamesStatic(doc, layerName, recursive);
};

HierarchicalLayers.getParentLayerName = function(layerName) {
    return RLayer.getParentLayerNameStatic(layerName);
};

HierarchicalLayers.getShortLayerName = function(layerName) {
    return RLayer.getShortLayerNameStatic(layerName);
};

HierarchicalLayers.getLayerNameHierarchy = function(layerName) {
    return RLayer.getLayerNameHierarchyStatic(layerName);
};
