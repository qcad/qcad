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
 * \class ShowActiveLayer
 * \ingroup ecma_layer
 * \brief Show only active layer.
 */
function ShowActiveLayer(guiAction) {
    Layer.call(this, guiAction);
}

ShowActiveLayer.prototype = new Layer();

ShowActiveLayer.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var layerId = this.getDocument().getCurrentLayerId();
    Layer.showHide(false, this.getDocumentInterface(), layerId);
    
    this.terminate();
};

