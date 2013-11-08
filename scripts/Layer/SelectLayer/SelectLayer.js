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
 

function SelectLayer(guiAction) {
    Layer.call(this, guiAction);
}

SelectLayer.prototype = new Layer();

SelectLayer.prototype.beginEvent = function() {
    Layer.prototype.beginEvent.call(this);

    var doc = this.getDocument();
    var di = this.getDocumentInterface();

    var layerId = doc.getCurrentLayerId();
    var layer = doc.queryLayer(layerId);
    if (layer.isFrozen()) {
        this.terminate();
        return;
    }

    var ids = doc.queryLayerEntities(layerId);
    di.selectEntities(ids, true);

    this.terminate();
};

