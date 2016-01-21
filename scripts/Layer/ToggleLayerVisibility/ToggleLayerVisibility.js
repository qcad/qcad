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

include("../Layer.js");
 
/**
 * \class ToggleLayerVisibility
 * \ingroup ecma_layer
 * \brief Toggle layer visibility.
 */
function ToggleLayerVisibility(guiAction) {
    Layer.call(this, guiAction);
}

ToggleLayerVisibility.prototype = new Layer();

ToggleLayerVisibility.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var layer = this.getDocument().queryCurrentLayer();

    layer.setFrozen(!layer.isFrozen());

    var operation = new RModifyObjectOperation(layer);
    var di = this.getDocumentInterface();
    di.applyOperation(operation);

    this.terminate();
};

