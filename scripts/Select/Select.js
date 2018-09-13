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
 * \defgroup ecma_select Selection Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of advanced
 * selection tools.
 */
include("scripts/EAction.js");

/**
 * \class Select
 * \brief Base class for all advanced selection tools.
 * \ingroup ecma_select
 */
function Select(guiAction) {
    EAction.call(this, guiAction);

    this.selectionMode = Select.Mode.Replace;
    this.crossSelection = false;
}

Select.prototype = new EAction();
Select.includeBasePath = includeBasePath;

Select.Mode = {
    Replace: 0,
    Add: 1,
    Remove: 2,
    Intersect: 3
};

Select.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="SelectToolsPanelAction") {
        EAction.showCadToolBarPanel("SelectToolsPanel");
        this.terminate();
    }
};

/**
 * Adds the given box as a selection box to the preview.
 * \param di RDocumentInterface
 * \param box RBox
 * \param crossSelection boolean true for cross selection
 */
Select.previewSelectionBox = function(di, box, crossSelection) {
    var points = new Array(
        box.c1,
        new RVector(box.c1.x, box.c2.y),
        box.c2,
        new RVector(box.c2.x, box.c1.y),
        box.c1
    );
    Select.previewSelectionPolygon(di, points, crossSelection);
};

/**
 * Adds a selection polygon with the given points to the preview.
 * \param points Array of RVector objects
 */
Select.previewSelectionPolygon = function(di, points, crossSelection) {
    var polygon = new RPolyline(points, true);
    var color = RSettings.getColor("GraphicsViewColors/SelectionBoxColor", new RColor(128,0,0,255));
    var lw = RLineweight.Weight000;
    var c;
    if (crossSelection) {
        c = RSettings.getColor("GraphicsViewColors/SelectionBoxBackgroundCrossColor", new RColor(0,0,255,30));
    } else {
        c = RSettings.getColor("GraphicsViewColors/SelectionBoxBackgroundColor", new RColor(0,255,0,30));
    }
    // TODO c.getQColor() doesn't work
    var bgColor = new QColor(c.red(), c.green(), c.blue(), c.alpha());
    var brush = new QBrush(bgColor, Qt.SolidPattern);
    if (crossSelection) {
        var dashes = new Array(10, 5);
        di.addShapeToPreview(polygon, color, brush,
                lw, Qt.CustomDashLine.valueOf(), dashes);
    } else {
        // TODO "Qt.SolidLine" doesn't convert to number
        di.addShapeToPreview(polygon, color, brush,
                lw, Qt.SolidLine.valueOf());
    }
};

/**
 * Called when the user toggles the cross selection option available in
 * some selection options toolbars.
 */
Select.prototype.slotCrossSelectionChanged = function(checked) {
    this.crossSelection = checked;
    this.getDocumentInterface().clearPreview();
    this.getDocumentInterface().repaintViews();
    this.preview();
};

/**
 * Called when the current selection mode changed to 'replace'.
 */
Select.prototype.slotModeReplaceChanged = function(checked) {
    if (checked) {
        this.selectionMode = Select.Mode.Replace;
    }
};

/**
 * Called when the current selection mode changed to 'add'.
 */
Select.prototype.slotModeAddChanged = function(checked) {
    if (checked) {
        this.selectionMode = Select.Mode.Add;
    }
};

/**
 * Called when the current selection mode changed to 'remove'.
 */
Select.prototype.slotModeRemoveChanged = function(checked) {
    if (checked) {
        this.selectionMode = Select.Mode.Remove;
    }
};

/**
 * Called when the current selection mode changed to 'intersect'.
 */
Select.prototype.slotModeIntersectChanged = function(checked) {
    if (checked) {
        this.selectionMode = Select.Mode.Intersect;
    }
};

/**
 * Change selection based on given matching entities and current
 * selection mode.
 */
Select.prototype.selectWithMode = function(entityIds) {
    var di = this.getDocumentInterface();
    Select.selectWithMode(entityIds, di, this.selectionMode);
};

Select.selectWithMode = function(entityIds, di, selectionMode) {
    switch (selectionMode) {
    case Select.Mode.Replace:
        di.selectEntities(entityIds, false);
        break;
    case Select.Mode.Add:
        di.selectEntities(entityIds, true);
        break;
    case Select.Mode.Remove:
        di.deselectEntities(entityIds);
        break;
    case Select.Mode.Intersect:
        var doc = di.getDocument();
        var allEntityIds = doc.queryAllEntities();
        var entityIdsToSelect = [];
        var entityIdsToDeselect = [];
        for (var e = 0; e < allEntityIds.length; ++e) {
            var entityId = allEntityIds[e];
            var entity = EAction.getDocument().queryEntity(entityId);
            var match = entityIds.contains(entityId);
            var previouslySelected = entity.isSelected();
            var select = match && previouslySelected;
            if (select && !previouslySelected) {
                entityIdsToSelect.push(entityId);
            }
            if (!select && previouslySelected) {
                entityIdsToDeselect.push(entityId);
            }
        }
        if (entityIdsToSelect.length!==0) {
            di.selectEntities(entityIdsToSelect);
        }
        if (entityIdsToDeselect.length!==0) {
            di.deselectEntities(entityIdsToDeselect);
        }
        break;
    }
};

Select.getMenu = function() {
    var menu = EAction.getMenu(Select.getTitle(), "SelectMenu");
    menu.setProperty("scriptFile", Select.includeBasePath + "/Select.js");
    return menu;
};

Select.getToolBar = function() {
    var tb = EAction.getToolBar(Select.getTitle(), "SelectToolBar");
    tb.visible = false;
    return tb;
};

Select.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "SelectToolsPanelAction";
    if (!isNull(mtb) && isNull(mtb.findChild(actionName))) {
        var action = new RGuiAction(qsTr("Selection Tools"), mtb);
        action.setScriptFile(Select.includeBasePath + "/Select.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Select.includeBasePath + "/Select.svg");
        //action.setStatusTip(qsTr("Show selection tools"));
        action.setDefaultShortcut(new QKeySequence("w,s"));
        action.setNoState();
        action.setDefaultCommands(["selectionmenu"]);
        action.setGroupSortOrder(40);
        action.setSortOrder(400);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(qsTr("Selection Tools Panel"), "SelectToolsPanel", true);
    return tb;
};

Select.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Select.getTitle(), "SelectMatrixPanel", 4000);
};

Select.getTitle = function() {
    return qsTr("&Select");
};

Select.prototype.getTitle = function() {
    return Select.getTitle();
};

Select.init = function() {
    Select.getMenu();
    Select.getToolBar();
    Select.getCadToolBarPanel();
    Select.getToolMatrixPanel();
};
