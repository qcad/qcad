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
 * \defgroup ecma_draw_line Line Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various line drawing tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Line
 * \brief Base class for all line drawing tools.
 * \ingroup ecma_draw_line
 */
function Line(guiAction) {
    Draw.call(this, guiAction);

    this.showAutoLineType = false;
    this.lineType = Line.LineType.Line;
}

Line.prototype = new Draw();
Line.includeBasePath = includeBasePath;

Line.LineType = {
    Auto : -1,
    Line : 0,
    XLine : 1,
    Ray : 2
};

Line.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="LineToolsPanelAction") {
        EAction.showCadToolBarPanel("LineToolsPanel");
        this.terminate();
    }
};

Line.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 200,
        Line.getTitle(),
        "DrawLineMenu",
        Line.includeBasePath + "/Line.svg"
    );
    menu.setProperty("scriptFile", Line.includeBasePath + "/Line.js");
    return menu;
};

Line.getToolBar = function() {
    var tb = EAction.getToolBar(Line.getTitle(), "LineToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Line.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "LineToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Line Tools"), mtb);
        action.setScriptFile(Line.includeBasePath + "/Line.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Line.includeBasePath + "/Line.svg");
        //action.setStatusTip(qsTr("Show line tools"));
        action.setDefaultShortcut(new QKeySequence("w,l"));
        action.setNoState();
        action.setDefaultCommands(["linemenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(200);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(Line.getTitle(), "LineToolsPanel", true);
    return tb;
};

Line.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Line.getTitle(), "LineMatrixPanel", 200);
};

Line.getTitle = function() {
    return qsTr("&Line");
};

Line.prototype.getTitle = function() {
    return Line.getTitle();
};

Line.getLineType = function(shape) {
    if (isLineShape(shape)) {
        return Line.LineType.Line;
    }
    if (isRayShape(shape)) {
        return Line.LineType.Ray;
    }
    if (isXLineShape(shape)) {
        return Line.LineType.XLine;
    }
    return undefined;
};

Line.createLineEntity = function(doc, p1, p2, lineType) {
    switch (lineType) {
    default:
    case Line.LineType.Line:
        return new RLineEntity(doc, new RLineData(p1, p2));
    case Line.LineType.XLine:
        return new RXLineEntity(doc, new RXLineData(p1, p2.operator_subtract(p1)));
    case Line.LineType.Ray:
        return new RRayEntity(doc, new RRayData(p1, p2.operator_subtract(p1)));
    }
};

Line.prototype.createLineEntity = function(doc, p1, p2) {
    return Line.createLineEntity(doc, p1, p2, this.lineType);
};

Line.prototype.initUiOptions = function(resume, optionsToolBar) {
    Draw.prototype.initUiOptions.call(this, resume, optionsToolBar);

    this.lineType = RSettings.getIntValue(this.settingsGroup + "/Type",
        this.showAutoLineType ? Line.LineType.Auto : Line.LineType.Line);

    var wn = "";
    switch (this.lineType) {
    case Line.LineType.Auto:
        wn = "TypeAuto";
        break;
    case Line.LineType.Line:
        wn = "TypeSegment";
        break;
    case Line.LineType.XLine:
        wn = "TypeXLine";
        break;
    case Line.LineType.Ray:
        wn = "TypeRay";
        break;
    }

    var w = optionsToolBar.findChild("TypeAutoAction");
    if (!isNull(w) && !this.showAutoLineType) {
        w.visible = false;
        if (wn==="TypeAuto") {
            wn = "TypeSegment";
        }
    }

    w = optionsToolBar.findChild(wn);
    if (!isNull(w)) {
        w.checked = true;
    }
};

Line.prototype.hideUiOptions = function(saveToSettings) {
    Draw.prototype.hideUiOptions.call(this, saveToSettings);

    RSettings.setValue(this.settingsGroup + "/Type", this.lineType);
};

/**
 * Implemented by line tool classes to be notified when type changed.
 */
Line.prototype.typeChanged = function() {
};

Line.prototype.slotTypeAutoChanged = function(checked) {
    Line.slotTypeAutoChanged(this, checked);
};

Line.slotTypeAutoChanged = function(obj, checked) {
    if (checked) {
        obj.lineType = Line.LineType.Auto;
        obj.updatePreview(true);
        if (isFunction(obj.typeChanged)) {
            obj.typeChanged();
        }
    }
};

Line.prototype.slotTypeSegmentChanged = function(checked) {
    Line.slotTypeSegmentChanged(this, checked);
};

Line.slotTypeSegmentChanged = function(obj, checked) {
    if (checked) {
        obj.lineType = Line.LineType.Line;
        obj.updatePreview(true);
        if (isFunction(obj.typeChanged)) {
            obj.typeChanged();
        }
    }
};


Line.prototype.slotTypeRayChanged = function(checked) {
    Line.slotTypeRayChanged(this, checked);
};

Line.slotTypeRayChanged = function(obj, checked) {
    if (checked) {
        obj.lineType = Line.LineType.Ray;
        obj.updatePreview(true);
        if (isFunction(obj.typeChanged)) {
            obj.typeChanged();
        }
    }
};

Line.prototype.slotTypeXLineChanged = function(checked) {
    Line.slotTypeXLineChanged(this, checked);
};

Line.slotTypeXLineChanged = function(obj, checked) {
    if (checked) {
        obj.lineType = Line.LineType.XLine;
        obj.updatePreview(true);
        if (isFunction(obj.typeChanged)) {
            obj.typeChanged();
        }
    }
};

Line.prototype.isRayOrXLine = function() {
    return this.lineType===Line.LineType.Ray || this.lineType===Line.LineType.XLine;
};

Line.init = function() {
    Line.getMenu();
    Line.getToolBar();
    Line.getCadToolBarPanel();
    Line.getToolMatrixPanel();
};
