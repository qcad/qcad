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

include("scripts/library.js");
include("scripts/Layer/Layer.js");

/**
 * \class SelectLayer
 * \ingroup ecma_layer
 * \brief Select entities based on layer.
 */
function SelectLayer(guiAction) {
    Layer.call(this, guiAction);
    this.select = true;
}

SelectLayer.prototype = new Layer();

SelectLayer.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var doc = this.getDocument();
    var layer = doc.queryCurrentLayer();
    this.selectLayer(layer);
    this.terminate();
};

SelectLayer.prototype.selectLayer = function(layer) {
    return this.selectLayers([layer]);
};

SelectLayer.prototype.selectLayers = function(layers) {
    var ret = true;
    var doc = this.getDocument();
    var di = this.getDocumentInterface();

    var num;
    var ids = [];
    for (var i=0; i<layers.length; i++) {
        var layer = layers[i];
        if (layer.isOffOrFrozen()) {
            ret = false;
        }
        else {
            ids = ids.concat(doc.queryLayerEntities(layer.getId()));
        }
    }

    if (ids.length>0) {
        if (this.select) {
            num = di.selectEntities(ids, true);
            EAction.handleUserMessage(qsTr("%1 entities added to selection.").arg(num));
        }
        else {
            num = di.deselectEntities(ids);
            EAction.handleUserMessage(qsTr("%1 entities removed from selection.").arg(num));
        }
    }

    return ret;
};
