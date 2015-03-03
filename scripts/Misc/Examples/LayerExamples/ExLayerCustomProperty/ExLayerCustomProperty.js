/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
 * This action adds a custom property to a layer.
 */
function ExLayerCustomProperty(guiAction) {
    LayerExamples.call(this, guiAction);
}

ExLayerCustomProperty.prototype = new LayerExamples();

ExLayerCustomProperty.prototype.beginEvent = function() {
    LayerExamples.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var op = new RModifyObjectsOperation();
    var layer = document.queryLayer("0");
    layer.setCustomProperty(RSettings.getAppId(), "MyCustomProperty", "Custom Property Value");
    op.addObject(layer);
    EAction.handleUserMessage(qsTr("Added custom property 'MyCustomProperty' to layer '0'."));
    di.applyOperation(op);

//    var layer = document.queryLayerDirect(document.getLayerId("0"));
//    layer.setCustomProperty(RSettings.getAppId(), "MyCustomProperty", 7);
//    EAction.handleUserMessage(qsTr("Added custom property for application '%1' with key 'MyCustomProperty' to layer '0'.").arg(RSettings.getAppId()));

    this.terminate();
};

/**
 * Adds a menu for this action.
 */
ExLayerCustomProperty.init = function(basePath) {
    var action = new RGuiAction(qsTr("Add custom property to a layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExLayerCustomProperty.js");
    action.setGroupSortOrder(78100);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerExamplesMenu"]);
};
