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

include("../Misc.js");

/**
 * \class MiscLayer
 * \brief Base class for misc layer tools.
 */
function MiscLayer(guiAction) {
    EAction.call(this, guiAction);
}

MiscLayer.prototype = new EAction();
MiscLayer.includeBasePath = includeBasePath;

MiscLayer.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51100, 400,
        MiscLayer.getTitle(),
        "MiscLayerMenu"
    );
    return menu;
};

MiscLayer.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscLayer.getTitle(), "MiscLayerToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

MiscLayer.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscLayerToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Layer Tools"), mtb);
        action.setScriptFile(MiscLayer.includeBasePath + "/MiscLayer.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscLayer.includeBasePath + "/MiscLayer.svg");
        action.setStatusTip(qsTr("Show misc layer tools"));
        action.setNoState();
        action.setDefaultCommands(["misclayermenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(450);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscLayer.getTitle(),
        "MiscLayerToolsPanel",
        true
    );
    return tb;
};


MiscLayer.getTitle = function() {
    return qsTr("&Layer");
};

MiscLayer.prototype.getTitle = function() {
    return MiscLayer.getTitle();
};

MiscLayer.init = function() {
    MiscLayer.getMenu();
    MiscLayer.getToolBar();
    MiscLayer.getCadToolBarPanel();
};
