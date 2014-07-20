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

/**
 * \defgroup ecma_layer Layer Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * layer related tools.
 */
include("../EAction.js");

/**
 * \class Layer
 * \brief Base class for all layer tools.
 * \ingroup ecma_layer
 */
function Layer(guiAction) {
    EAction.call(this, guiAction);
}

Layer.prototype = new EAction();
Layer.includeBasePath = includeBasePath;

Layer.getMenu = function() {
    var menu = EAction.getMenu(Layer.getTitle(), "LayerMenu");
    menu.setProperty("scriptFile", Layer.includeBasePath + "/Layer.js");
    return menu;
};

Layer.getToolBar = function() {
    var tb = EAction.getToolBar(Layer.getTitle(), "LayerToolBar");
    tb.visible = false;
    return tb;
};

Layer.getTitle = function() {
    return qsTr("&Layer");
};

Layer.prototype.getTitle = function() {
    return Layer.getTitle();
};

Layer.showHide = function(show, obj, layerId) {
    var operation = new RModifyObjectsOperation();
    var layers = obj.getDocument().queryAllLayers();
    for (var l = 0; l < layers.length; ++l) {
        var layer = obj.getDocument().queryLayer(layers[l]);
        if (layers[l] !== layerId) {
            layer.setFrozen(!show);
        } else {
            layer.setFrozen(false);
        }
        operation.addObject(layer);
    }
    var di = obj.getDocumentInterface();
    di.applyOperation(operation);
    di.clearPreview();
    di.repaintViews();
};

/**
 * Can be reimplemented in derived classes to provide an advanced dialog.
 */
Layer.prototype.createLayerDialog = function(doc, layer) {
    return new LayerDialog(doc, layer);
};
