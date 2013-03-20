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
 * \defgroup ecma_draw_line Line Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various line drawing tools.
 */
include("../Draw.js");

/**
 * \class Line
 * \brief Base class for all line drawing tools.
 * \ingroup ecma_draw_line
 */
function Line(guiAction) {
    Draw.call(this, guiAction);
}

Line.prototype = new Draw();
Line.includeBasePath = includeBasePath;

Line.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="LineMenu") {
        EAction.showCadToolBarPanel("LineToolsPanel");
        this.terminate();
    }
};

Line.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        200,
        Line.getTitle(),
        "line",
        Line.includeBasePath + "/Line.svg"
    );
    menu.setProperty("scriptFile", Line.includeBasePath + "/Line.js");
    return menu;
};

Line.getToolBar = function() {
    var tb = EAction.getToolBar(Line.getTitle(), "Line");
    tb.visible = false;
    return tb;
};

Line.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "LineMenu";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Line Tools"), mtb);
        action.setScriptFile(Line.includeBasePath + "/Line.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Line.includeBasePath + "/Line.svg");
        action.setStatusTip(qsTr("Show line tools"));
        action.setDefaultShortcut(new QKeySequence("w,l"));
        action.setNoState();
        action.setProperty("SortOrder", 200);
        action.setDefaultCommands(["linemenu"]);
        CadToolBarPanel.prototype.addAction.call(mtb, action);
    }

    var tb = EAction.getCadToolBarPanel(
        Line.getTitle(),
        "LineToolsPanel",
        true
    );
    return tb;
};

Line.getTitle = function() {
    return qsTr("&Line");
};

Line.prototype.getTitle = function() {
    return Line.getTitle();
};
