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

include("../LayerExamples.js");

/**
 * This action adds a custom property to layer '0'.
 */
function ExLayerAdd(guiAction) {
    LayerExamples.call(this, guiAction);
}

ExLayerAdd.prototype = new LayerExamples();

ExLayerAdd.prototype.beginEvent = function() {
    LayerExamples.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    // add layer:
    var op = new RModifyObjectsOperation();
    var linetypeId = document.getLinetypeId("CONTINUOUS");
    var layer = new RLayer(document, "MyLayer", false, false, new RColor("red"), linetypeId, RLineweight.Weight000);
    op.addObject(layer);
    EAction.handleUserMessage(qsTr("Added layer 'MyLayer'"));
    di.applyOperation(op);

    // make the new layer the current layer:
    di.setCurrentLayer("MyLayer");

    this.terminate();
};

/**
 * Adds a menu for this action.
 */
ExLayerAdd.init = function(basePath) {
    var action = new RGuiAction(qsTr("Add layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExLayerAdd.js");
    action.setGroupSortOrder(78100);
    action.setSortOrder(50);
    action.setWidgetNames(["LayerExamplesMenu"]);
};
