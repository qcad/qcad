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
 * \defgroup ecma_misc_point PointMark Marker Tools
 * \ingroup ecma_misc
 *
 * \brief This module contains ECMAScript implementations of 
 * point marker drawing, export and visualization tools.
 */
include("../Misc.js");

/**
 * \class PointMark
 * \brief Base class for all point marker tools.
 * \ingroup ecma_misc_point
 */
function PointMark(guiAction) {
    Misc.call(this, guiAction);
}

PointMark.prototype = new Misc();
PointMark.includeBasePath = includeBasePath;

PointMark.prototype.beginEvent = function() {
    Misc.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName=="PointMarkMenu") {
        EAction.showCadToolBarPanel("PointMarkToolsPanel");
        this.terminate();
    }
};

PointMark.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        20000,
        PointMark.getTitle(),
        "pointmark",
        PointMark.includeBasePath + "/PointMark.svg"
    );
    menu.setProperty("scriptFile", PointMark.includeBasePath + "/PointMark.js");
    return menu;
};

PointMark.getToolBar = function() {
    var tb = EAction.getToolBar(PointMark.getTitle(), "PointMark");
    tb.visible = false;
    return tb;
};

PointMark.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "PointMarkMenu";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("PointMark Tools"), mtb);
        action.setScriptFile(PointMark.includeBasePath + "/PointMark.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(PointMark.includeBasePath + "/PointMark.svg");
        action.setStatusTip(qsTr("Show point marker tools"));
        action.setDefaultShortcut(new QKeySequence("w,t"));
        action.setNoState();
        action.setProperty("SortOrder", 20000);
        action.setDefaultCommands(["pointmarkmenu"]);
        CadToolBarPanel.prototype.addAction.call(mtb, action);
    }

    var tb = EAction.getCadToolBarPanel(
        PointMark.getTitle(),
        "PointMarkToolsPanel",
        true
    );
    return tb;
};

PointMark.getTitle = function() {
    return qsTr("&Point Marker");
};

PointMark.prototype.getTitle = function() {
    return PointMark.getTitle();
};

PointMark.queryAllMarks = function(doc) {
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

PointMark.getMarkerLabel = function(doc, blockRefId) {
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

PointMark.getBenchmarkHandle = function(blockRef) {
    var handle = blockRef.getCustomProperty("QCAD", "benchmark", undefined);
    if (isNull(handle)) {
        return RObject.INVALID_HANDLE;
    }
    return parseInt(handle, 16);
};
