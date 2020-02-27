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

AddLayer.getPreferencesCategory = function() {
    return [ qsTr("Layer"), qsTr("Add Layer") ];
};

AddLayer.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var dlg = this.createLayerDialog(this.getDocumentInterface());
    this.layer = dlg.show();
    if (isNull(this.layer)) {
        this.terminate();
        return;
    }

    this.applyOperation();

    var di = this.getDocumentInterface();
    di.setCurrentLayer(this.layer);

    this.terminate();
};

AddLayer.prototype.getOperation = function() {
    return new RAddObjectOperation(this.layer, this.getToolTitle());
};

AddLayer.prototype.getAddedLayer = function() {
    return this.layer;
};

