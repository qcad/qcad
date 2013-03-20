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

include("../LayerExamples.js");

/**
 * This action changes the color of all white layers to black.
 */
function ExLayerWhiteToBlack(guiAction) {
    LayerExamples.call(this, guiAction);
}

ExLayerWhiteToBlack.prototype = new LayerExamples();

ExLayerWhiteToBlack.prototype.beginEvent = function() {
    LayerExamples.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var op = new RModifyObjectsOperation();

    var layerIds = document.queryAllLayers();
    for (var i=0; i<layerIds.length; i++) {
        var layerId = layerIds[i];
        var layer = document.queryLayer(layerId);

        if (layer.getName()==="ref") {
            layer.setColor(new RColor("blue"));
            op.addObject(layer);
        }
        else if (layer.getName()==="sel") {
            layer.setColor(new RColor("#880000"));
            op.addObject(layer);
        }
        else if (layer.getName()==="cursor" || layer.getName()==="center") {
            layer.setColor(new RColor("#ff0000"));
            op.addObject(layer);
        }
        else if (layer.getName()==="limiting") {
            layer.setColor(new RColor("#0000ff"));
            op.addObject(layer);
        }
        else  if (layer.getColor().name().toLowerCase()==="#ffffff") {
            layer.setColor(new RColor("#000000"));
            op.addObject(layer);
            EAction.handleUserMessage(
                qsTr("Changed color of layer '%1' from white to black.")
                    .arg(layer.getName())
            );
        }
    }

    di.applyOperation(op);

    var op = new RModifyObjectsOperation();

    var ids = document.queryAllEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);

        if (isTextEntity(entity)) {
            entity.setFontName("Arial");
            entity.update();
            op.addObject(entity);
        }
    }

    di.applyOperation(op);

    this.terminate();
};

/**
 * Adds a menu for this action.
 */
ExLayerWhiteToBlack.init = function(basePath) {
    var action = new RGuiAction("Make all White Layers Black", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExLayerWhiteToBlack.js");
    action.setDefaultShortcut(new QKeySequence("x,x"));
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, LayerExamples, true, false, false);
};
