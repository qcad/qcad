/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
 * \defgroup ecma_misc_point PointMarker Marker Tools
 * \ingroup ecma_misc
 *
 * \brief This module contains ECMAScript implementations of 
 * point marker drawing, export and visualization tools.
 */
include("../Misc.js");

/**
 * \class PointMarker
 * \brief Base class for all point marker tools.
 * \ingroup ecma_misc_point
 */
function PointMarker(guiAction) {
    Misc.call(this, guiAction);
}

PointMarker.prototype = new Misc();
PointMarker.includeBasePath = includeBasePath;

PointMarker.prototype.beginEvent = function() {
    Misc.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName=="PointMarkerMenu") {
        EAction.showCadToolBarPanel("PointMarkerToolsPanel");
        this.terminate();
    }
};

PointMarker.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        20000,
        PointMarker.getTitle(),
        "pointmarker",
        PointMarker.includeBasePath + "/PointMarker.svg"
    );
    menu.setProperty("scriptFile", PointMarker.includeBasePath + "/PointMarker.js");
    return menu;
};

PointMarker.getToolBar = function() {
    var tb = EAction.getToolBar(PointMarker.getTitle(), "PointMarker");
    tb.visible = false;
    return tb;
};

PointMarker.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "PointMarkerMenu";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("PointMarker Tools"), mtb);
        action.setScriptFile(PointMarker.includeBasePath + "/PointMarker.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(PointMarker.includeBasePath + "/PointMarker.svg");
        action.setStatusTip(qsTr("Show point marker tools"));
        action.setDefaultShortcut(new QKeySequence("w,t"));
        action.setNoState();
        action.setProperty("SortOrder", 20000);
        action.setDefaultCommands(["pointmarkermenu"]);
        CadToolBarPanel.prototype.addAction.call(mtb, action);
    }

    var tb = EAction.getCadToolBarPanel(
        PointMarker.getTitle(),
        "PointMarkerToolsPanel",
        true
    );
    return tb;
};

PointMarker.getTitle = function() {
    return qsTr("&Point Marker");
};

PointMarker.prototype.getTitle = function() {
    return PointMarker.getTitle();
};

PointMarker.queryAllMarks = function(doc) {
    var ret = [];

    var ids = doc.queryAllBlockReferences();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var blockRef = doc.queryEntityDirect(id);
        if (isNull(blockRef)) {
            continue;
        }

        var handle = blockRef.getCustomProperty("QCAD", "benchmark", undefined);
        if (isNull(handle)) {
            continue;
        }

        ret.push(id);
    }

    return ret;
};

PointMarker.getMarkerLabel = function(doc, blockRefId) {
    var blockAttribIds = doc.queryChildEntities(blockRefId);
    if (blockAttribIds.length!==1) {
        return "";
    }
    var attrib = doc.queryEntityDirect(blockAttribIds[0]);
    if (isNull(attrib)) {
        return "";
    }

    return attrib.getPlainText();
};
