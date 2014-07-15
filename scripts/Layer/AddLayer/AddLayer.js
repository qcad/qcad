/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
include("../LayerDialog.js");

/**
 * \class AddLayer
 * \ingroup ecma_layer
 * \brief This action handles all user interaction to add a new layer to the current drawing.
 */
function AddLayer(guiAction) {
    Layer.call(this, guiAction);
}

AddLayer.prototype = new Layer();

AddLayer.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var dlg = this.createLayerDialog(this.getDocument());
    this.layer = dlg.show();
    if (isNull(this.layer)) {
        this.terminate();
        return;
    }

    this.layer.setCustomProperty("QCAD", "Blah", new Array(10000).join("Q"));
    
    var operation = new RAddObjectOperation(this.layer);
    var di = this.getDocumentInterface();
    di.applyOperation(operation);

    di.setCurrentLayer(this.layer);

    this.terminate();
};

AddLayer.prototype.getAddedLayer = function() {
    return this.layer;
};

