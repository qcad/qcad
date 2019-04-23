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

include("scripts/Layer/Layer.js");
 
/**
 * \class ToggleLayerLock
 * \ingroup ecma_layer
 * \brief Toggle layer lock status.
 */
function ToggleLayerLock(guiAction) {
    Layer.call(this, guiAction);
}

ToggleLayerLock.prototype = new Layer();

ToggleLayerLock.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var layers = this.getSelectedLayers();

    var op = new RModifyObjectsOperation();
    for (var i=0; i<layers.length; i++) {
        var layer = layers[i];
        layer.setLocked(!layer.isLocked());
        op.addObject(layer);
    }

    if (!op.isEmpty()) {
        var di = this.getDocumentInterface();
        di.applyOperation(op);
    }
    else {
        op.destroy();
    }

    this.terminate();
};

ToggleLayerLock.prototype.getSelectedLayers = function() {
    return [ this.getCurrentLayer() ];
};
