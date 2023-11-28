/*
 * Copyright (c) 2017 by RibbonSoft, GmbH. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * Licensees holding valid QCAD Professional Edition licenses 
 * may use this file in accordance with the QCAD License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, 
 * INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE.
 * 
 * See http://www.ribbonsoft.com for further details.
 */

include("scripts/Misc/Misc.js");

/**
 * \class MiscInformation
 * \brief Base class for misc info tools.
 */
function MiscInformation(guiAction) {
    EAction.call(this, guiAction);
}

MiscInformation.prototype = new EAction();
MiscInformation.includeBasePath = includeBasePath;

MiscInformation.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51100, 600,
        MiscInformation.getTitle(),
        "MiscInformationMenu"
    );
    return menu;
};

MiscInformation.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscInformation.getTitle(), "MiscInformationToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

MiscInformation.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscInformationToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Information Tools"), mtb);
        action.setScriptFile(MiscInformation.includeBasePath + "/MiscInformation.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setStatusTip(qsTr("Show misc information tools"));
        action.setNoState();
        action.setDefaultCommands(["miscinfomenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(450);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscInformation.getTitle(),
        "MiscInformationToolsPanel",
        true
    );
    return tb;
};


MiscInformation.getTitle = function() {
    return qsTr("&Information");
};

MiscInformation.prototype.getTitle = function() {
    return MiscInformation.getTitle();
};

MiscInformation.init = function() {
    MiscInformation.getMenu();
    MiscInformation.getToolBar();
    MiscInformation.getCadToolBarPanel();
};
