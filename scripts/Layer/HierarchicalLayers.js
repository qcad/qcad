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

function HierarchicalLayers() {
}

HierarchicalLayers.separator = " ... ";

HierarchicalLayers.hasChildLayers = function(doc, layerName) {
    return HierarchicalLayers.getChildLayerNames(doc, layerName).length!==0;
};

HierarchicalLayers.getChildLayerNames = function(doc, layerName, recursive) {
    if (isNull(recursive)) {
        recursive = true;
    }

    var ret = [];
    var names = doc.getLayerNames();
    for (var i=0; i<names.length; i++) {
        var name = names[i];
        var prefix = layerName + HierarchicalLayers.separator;
        if (name.startsWith(prefix)) {
            if (recursive || !name.substring(prefix.length).contains(HierarchicalLayers.separator)) {
                ret.push(name);
            }
        }
    }
    return ret;
};

HierarchicalLayers.getParentLayerName = function(layerName) {
    var a = layerName.split(HierarchicalLayers.separator);

    // top layer:
    if (a.length===1) {
        return "";
    }

    a.pop();
    return a.join(HierarchicalLayers.separator);
};

HierarchicalLayers.getShortLayerName = function(layerName) {
    var a = layerName.split(HierarchicalLayers.separator);
    return a[a.length-1];
};
