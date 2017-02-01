/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

include("scripts/Pro/Layer/AddLayerPro/AddLayerPro.js");

/**
 * \class ExLayerFromHatches
 * \ingroup ecma_misc_examples_layerexamples
 * This action moves all hatches to a new layer.
 */
function ExLayerFromHatches(guiAction) {
    AddLayer.call(this, guiAction);
}

ExLayerFromHatches.prototype = new AddLayer();

ExLayerFromHatches.prototype.beginEvent = function() {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();

    var oriLayer = doc.queryCurrentLayer();

    // this shows the layer dialog and creates a new layer:
    AddLayerPro.prototype.beginEvent.call(this);

    var layer = doc.queryCurrentLayer();

    if (layer.getId()===oriLayer.getId()) {
        // no new layer has been created: cancel:
        return;
    }

    var op = new RAddObjectsOperation();

    // query all hatches:
    var entityIds = doc.queryAllEntities(false, false, RS.EntityHatch);
    for (var i = 0; i < entityIds.length; i++) {
        var entityId = entityIds[i];
        var entity = doc.queryEntity(entityId);
        if (!isHatchEntity(entity)) {
            continue;
        }

        // move hatch to current layer:
        entity.setLayerId(layer.getId());
        op.addObject(entity);
    }

    di.applyOperation(op);
};
