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

/**
 * \defgroup ecma_layer Layer Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * layer related tools.
 */
include("scripts/EAction.js");

/**
 * \class Layer
 * \brief Base class for all layer tools.
 * \ingroup ecma_layer
 */
function Layer(guiAction) {
    EAction.call(this, guiAction);

    this.documentInterface = undefined;

//    if (!isNull(guiAction) && !isNull(guiAction.getDocumentInterface())) {
//        this.setDocumentInterface(guiAction.getDocumentInterface());
//    }
}

Layer.prototype = new EAction();
Layer.includeBasePath = includeBasePath;

Layer.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="LayerToolsPanelAction") {
        EAction.showCadToolBarPanel("LayerToolsPanel");
        this.terminate();
    }
};

Layer.prototype.setDocumentInterface = function(di) {
    this.documentInterface = di;
};

Layer.prototype.getDocumentInterface = function() {
    if (!isNull(this.documentInterface)) {
        return this.documentInterface;
    }
    return EAction.prototype.getDocumentInterface.call(this);
};

Layer.prototype.getDocument = function() {
    if (!isNull(this.documentInterface)) {
        return this.documentInterface.getDocument();
    }
    return EAction.prototype.getDocument.call(this);
};

Layer.prototype.getCurrentLayer = function() {
    // get current or override document:
    var doc = this.getDocument();
    return doc.queryCurrentLayer();
};


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

Layer.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "LayerToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Layer Tools"), mtb);
        action.setScriptFile(Layer.includeBasePath + "/Layer.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Layer.includeBasePath + "/Layer.svg");
        //action.setStatusTip(qsTr("Show layer tools"));
        action.setDefaultShortcut(new QKeySequence("w,y"));
        action.setNoState();
        action.setDefaultCommands(["layermenu"]);
        action.setGroupSortOrder(60);
        action.setSortOrder(200);
        action.setWidgetNames(["!MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Layer.getTitle(),
        "LayerToolsPanel",
        true
    );
    return tb;
};

Layer.getToolMatrixPanel = function() {
    RSettings.setValue("Layer/VisibleInMatrixPanel", false, false);
    return EAction.getToolMatrixPanel(Layer.getTitle(), "LayerMatrixPanel", 7000);
};

Layer.getTitle = function() {
    return qsTr("&Layer");
};

Layer.prototype.getTitle = function() {
    return Layer.getTitle();
};

Layer.init = function() {
    Layer.getMenu();
    Layer.getToolBar();
    Layer.getCadToolBarPanel();
    Layer.getToolMatrixPanel();
};

Layer.getShowFrozen = function() {
    if (hasPlugin("PROTOOLS")) {
        return RSettings.getBoolValue("LayerListPro/ShowFrozen", false);
    }
    else {
        return false;
    }
};

Layer.getFreezeLayer = function() {
    if (hasPlugin("PROTOOLS")) {
        return RSettings.getBoolValue("LayerListPro/FreezeLayer", true);
    }
    else {
        return true;
    }
};

/**
 * Show / hide all layers.
 *
 * \param show True to show, false to hide all
 * \param di RDocumentInterface
 * \param layerId ID of layer to exempt from the action
 * \param showProgress True to show progress information to progress listeners
 */
Layer.showHide = function(show, di, layerId, showProgress) {
    if (showProgress===true) {
        if (show) {
            EAction.setProgressText(qsTr("Showing all layers"));
        }
        else {
            EAction.setProgressText(qsTr("Hiding all layers"));
        }
    }

    var showFrozen = Layer.getShowFrozen();
    var freezeLayer = Layer.getFreezeLayer();

    var operation = new RModifyObjectsOperation();
    var layers = di.getDocument().queryAllLayers();
    for (var l = 0; l < layers.length; ++l) {
        if (showProgress===true) {
            EAction.setProgress(100/layers.length*l);
        }

        var layer = di.getDocument().queryLayer(layers[l]);
        if (layers[l] !== layerId) {
            if (showFrozen) {
                layer.setOff(!show);
            }
            else {
                layer.setFrozen(!show);
                layer.setOff(!show);
            }
        } else {
            if (showFrozen) {
                layer.setOff(false);
            }
            else {
                layer.setOff(false);
                layer.setFrozen(false);
            }
        }
        operation.addObject(layer);
    }
    di.applyOperation(operation);
    di.clearPreview();
    di.repaintViews();

    if (showProgress===true) {
        EAction.setProgressEnd();
    }
};

Layer.thawFreeze = function(freeze, di, layerId, showProgress) {
    if (showProgress===true) {
        if (freeze) {
            EAction.setProgressText(qsTr("Thawing all layers"));
        }
        else {
            EAction.setProgressText(qsTr("Freezing all layers"));
        }
    }

    var operation = new RModifyObjectsOperation();
    var layers = di.getDocument().queryAllLayers();
    for (var l = 0; l < layers.length; ++l) {
        if (showProgress===true) {
            EAction.setProgress(100/layers.length*l);
        }

        var layer = di.getDocument().queryLayer(layers[l]);
        if (layers[l] !== layerId) {
            layer.setFrozen(!freeze);
        } else {
            layer.setFrozen(false);
        }
        operation.addObject(layer);
    }
    di.applyOperation(operation);
    di.clearPreview();
    di.repaintViews();

    if (showProgress===true) {
        EAction.setProgressEnd();
    }
};

Layer.lockUnlock = function(lock, di, showProgress) {
    if (showProgress===true) {
        if (lock) {
            EAction.setProgressText(qsTr("Locking all layers"));
        }
        else {
            EAction.setProgressText(qsTr("Unlocking all layers"));
        }
    }

    var operation = new RModifyObjectsOperation();
    operation.setTransactionType(RTransaction.LayerLockStatusChange);
    var layers = di.getDocument().queryAllLayers();
    for (var l = 0; l < layers.length; ++l) {
        if (showProgress===true) {
            EAction.setProgress(50/layers.length*l);
        }

        var layer = di.getDocument().queryLayer(layers[l]);
        layer.setLocked(lock);
        operation.addObject(layer);
    }
    di.applyOperation(operation);
    di.clearPreview();
    if (showProgress===true) {
        EAction.setProgress(90);
    }
    di.repaintViews();
    if (showProgress===true) {
        EAction.setProgress(100);
    }

    if (showProgress===true) {
        EAction.setProgressEnd();
    }
};

/**
 * Can be reimplemented in derived classes to provide an advanced dialog.
 */
Layer.prototype.createLayerDialog = function(di, layer) {
    return new LayerDialog(di, layer);
};
