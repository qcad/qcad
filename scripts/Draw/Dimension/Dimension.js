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
 * \defgroup ecma_draw_dimension Dimension Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various dimensioning tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Dimension
 * \brief Base class for all dimensioning tools.
 * \ingroup ecma_draw_dimension
 */
function Dimension(guiAction) {
    EAction.call(this, guiAction);
}

Dimension.prototype = new EAction();
Dimension.includeBasePath = includeBasePath;

Dimension.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="DimensionToolsPanelAction") {
        EAction.showCadToolBarPanel("DimensionToolsPanel");
        this.terminate();
    }
};

/**
 * Reimplemented to reset all fields, unless we are resuming.
 */
Dimension.prototype.initUiOptions = function(resume, optionsToolBar) {
    EAction.prototype.initUiOptions.call(this, resume, optionsToolBar);

    // for some dimensions (e.g. leader), no standard dimensions toolbar
    // is shown:
    if (this.uiFile.join(",").indexOf("/Dimension.ui")===-1) {
        return;
    }

    var prefixCombo = optionsToolBar.findChild("Prefix");
    prefixCombo.clear();
    prefixCombo.addItem("(" + qsTr("No prefix") + ")");
    prefixCombo.addItem("R (" + qsTr("Radius") + ")");
    prefixCombo.addItem("M (" + qsTr("Metric screw") + ")");
    prefixCombo.addItem("\u00F8 (" + qsTr("Diameter") + ")");
    prefixCombo.addItem("\u2312 (" + qsTr("Arc") + ")");
    prefixCombo.addItem("\u00B1 (" + qsTr("Plus/Minus") + ")");
    prefixCombo.addItem("\u2248 (" + qsTr("Almost equal to") + ")");
    prefixCombo.addItem("\u2243 (" + qsTr("Asymptotically equal to") + ")");
    prefixCombo.addItem("\u25FB (" + qsTr("Square") + ")");
    prefixCombo.addItem("\u0394 (" + qsTr("Delta") + ")");
    prefixCombo.currentIndex = 0;

    var textLineEdit = optionsToolBar.findChild("Text");
    textLineEdit.text = "";
    WidgetFactory.initLineEdit(textLineEdit, true);

    var upperToleranceLineEdit = optionsToolBar.findChild("UpperTolerance");
    upperToleranceLineEdit.text = "";
    WidgetFactory.initLineEdit(upperToleranceLineEdit, true);

    var lowerToleranceLineEdit = optionsToolBar.findChild("LowerTolerance");
    lowerToleranceLineEdit.text = "";
    WidgetFactory.initLineEdit(lowerToleranceLineEdit, true);

    this.initScaleCombo();

    // not a layout block: hide auto checkbox:
    var doc = this.getDocument();
    if (!isNull(doc)) {
        var block = doc.queryCurrentBlock();
        if (!isNull(block) && block.hasLayout() && block.isModelSpace()) {
            var cbAutoAction = optionsToolBar.findChild("AutoScaleAction");
            if (!isNull(cbAutoAction)) {
                cbAutoAction.visible = false;
                var cbAuto = optionsToolBar.findChild("AutoScale");
                cbAuto.checked = false;
                if (!resume) {
                    // don't (re-)initialize or save state of auto checkbox:
                    cbAuto.setProperty("Loaded", true);
                    cbAuto.setProperty("Saved", true);
                }
                var scaleCombo = optionsToolBar.findChild("Scale");
                scaleCombo.setEnabled(true);
            }
        }
    }
    
    // if we are resuming, restore previous values (automatic)
    // it not, keep them empty.
    if (!resume) {
        prefixCombo.setProperty("Loaded", true);
        textLineEdit.setProperty("Loaded", true);
        upperToleranceLineEdit.setProperty("Loaded", true);
        lowerToleranceLineEdit.setProperty("Loaded", true);
    }
};

Dimension.prototype.showUiOptions = function(resume, restoreFromSettings) {
    EAction.prototype.showUiOptions.call(this, resume, restoreFromSettings);

    if (!resume) {
        var scale = this.parseScale(this.getScaleString());
        if (!RMath.fuzzyCompare(scale, 1) && RSettings.getBoolValue("DimensionScaleDialog/DontShowDialog", false)!==true) {
            // warning if scale is not 1:
            var appWin = RMainWindowQt.getMainWindow();

            var dialog = WidgetFactory.createDialog(Dimension.includeBasePath, "DimensionScaleDialog.ui", appWin);
            dialog.exec();
            WidgetFactory.saveState(dialog);
            dialog.destroy();
            EAction.activateMainWindow();
        }
    }
};

Dimension.prototype.initScaleCombo = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleCombo = optionsToolBar.findChild("Scale");
    scaleCombo.blockSignals(true);
    var prev = scaleCombo.currentText;
    scaleCombo.clear();
    var scales = this.getScales();
    for (var i=0; i<scales.length; ++i) {
        scaleCombo.addItem(scales[i]);
    }
    scaleCombo.setEditText(prev);
    scaleCombo.blockSignals(false);
};


Dimension.getMenu = function() {
    var menu = EAction.getMenu(Dimension.getTitle(), "DimensionMenu");
    menu.setProperty("scriptFile", Dimension.includeBasePath + "/Dimension.js");
    return menu;
};

Dimension.getToolBar = function() {
    var tb = EAction.getToolBar(Dimension.getTitle(), "DimensionToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Dimension.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "DimensionToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Dimension Tools"), mtb);
        action.setScriptFile(Dimension.includeBasePath + "/Dimension.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Dimension.includeBasePath + "/Dimension.svg");
        //action.setStatusTip(qsTr("Show dimension tools"));
        action.setDefaultShortcut(new QKeySequence("w,d"));
        action.setNoState();
        action.setDefaultCommands(["dimensionmenu"]);
        action.setGroupSortOrder(30);
        action.setSortOrder(200);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Dimension.getTitle(),
        "DimensionToolsPanel",
        true
    );
    return tb;
};

Dimension.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Dimension.getTitle(), "DimensionMatrixPanel", 2100);
};

Dimension.getTitle = function() {
    return qsTr("D&imension");
};

Dimension.prototype.getTitle = function() {
    return Dimension.getTitle();
};

Dimension.init = function() {
    Dimension.getMenu();
    Dimension.getToolBar();
    Dimension.getCadToolBarPanel();
    Dimension.getToolMatrixPanel();
};


/**
 * Called when the user changes the text in the options toolbar.
 */
Dimension.prototype.slotTextChanged = function() {
    this.updateText();
};

/**
 * Called when the user changes the prefix in the options toolbar.
 */
Dimension.prototype.slotPrefixChanged = function(prefix) {
    this.updateText();
};

/**
 * \internal
 * Updates the text label of the constructed dimension entity according
 * to the prefix and text entered by the user.
 */
Dimension.prototype.updateText = function() {
    if (isNull(this.data)) {
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    var prefixCombo = optionsToolBar.findChild("Prefix");
    var textLineEdit = optionsToolBar.findChild("Text");
    var text = textLineEdit.text;
    var prefix = prefixCombo.currentText.replace(/[ ]*\(.*\)/, "");

    if (prefix.length>0 && text.length===0) {
        this.data.setText(prefix + "<>");
    }
    else {
        this.data.setText(prefix + text);
    }
};

/**
 * Called when the user changes the upper tolerance in the options toolbar.
 */
Dimension.prototype.slotUpperToleranceChanged = function(text) {
    if (!isNull(this.data)) {
        this.data.setUpperTolerance(text);
    }
};

/**
 * Called when the user changes the lower tolerance in the options toolbar.
 */
Dimension.prototype.slotLowerToleranceChanged = function(text) {
    if (!isNull(this.data)) {
        this.data.setLowerTolerance(text);
    }
};

Dimension.prototype.getScaleString = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleCombo = optionsToolBar.findChild("Scale");
    return scaleCombo.currentText;
};

/**
 * Parses the given scale string (e.g. "1:2") and returns the scale as number (e.g. 0.5).
 */
Dimension.prototype.parseScale = function(scaleString) {
    return RMath.parseScale(scaleString);
};

/**
 * Automatically adjust the dimension scale based on the context of a viewport.
 */
Dimension.prototype.autoAdjustScale = function(pos) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var cbAuto = optionsToolBar.findChild("AutoScale");
    if (isNull(cbAuto) || !cbAuto.checked) {
        return;
    }

    var doc = this.getDocument();

    // are we in a layout block:
    var block = doc.queryCurrentBlock();
    if (isNull(block) || !block.hasLayout()) {
        return;
    }

    // get scale of underlying viewport:
    var scale = undefined;
    var viewportIds = doc.queryAllEntities(false, false, RS.EntityViewport);
    for (var i=0; i<viewportIds.length; i++) {
        var viewportId = viewportIds[i];
        var viewport = doc.queryEntityDirect(viewportId);
        var box = viewport.getBoundingBox();
        if (box.containsPoint(pos)) {
            scale = viewport.getScale();
            break;
        }
    }

    // no viewport under pos:
    if (isNull(scale)) {
        scale = 1.0;
    }

    // set scale of dimension according to viewport:
    var scaleCombo = optionsToolBar.findChild("Scale");
    if (isNull(scaleCombo)) {
        return;
    }

    scaleCombo.currentText = RUnit.doubleToStringDec(scale, 3);
};
