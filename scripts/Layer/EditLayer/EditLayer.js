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
 * \class EditLayer
 * \ingroup ecma_layer
 * \brief This action handles all user interaction to edit the current layer.
 */
function EditLayer(guiAction) {
    Layer.call(this, guiAction);
}

EditLayer.prototype = new Layer();

EditLayer.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var layer = this.getCurrentLayer();
    
    var dlg = this.createLayerDialog(this.getDocumentInterface(), layer);
    var newLayer = dlg.show();
    if (!newLayer) {
        this.terminate();
        return;
    }
    
    var operation = new RAddObjectsOperation();
    operation.setText(this.getToolTitle());
    operation.addObject(newLayer);
    this.completeOperation(operation, layer, dlg);

    var di = this.getDocumentInterface();
    di.applyOperation(operation);
    di.clearPreview();
    di.repaintViews();
    
    this.terminate();
};

/**
 * Hook for derived classes to add more objects to operation.
 */
EditLayer.prototype.completeOperation = function(operation, newLayer, dlg) {
};
