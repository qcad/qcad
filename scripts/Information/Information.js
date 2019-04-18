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
 * \defgroup ecma_information Measuring / Information Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * measuring and information tools.
 */
include("scripts/EAction.js");
include("scripts/sprintf.js");

/**
 * \class Information
 * \brief Base class for all measuring and information tools.
 * \ingroup ecma_information
 */
function Information(guiAction) {
    EAction.call(this, guiAction);

    this.addToDrawing = false;
    this.textHeight = 1.0;
    this.mathLineEdit = undefined;
    this.autoTerminate = false;
}

Information.prototype = new EAction();
Information.includeBasePath = includeBasePath;

Information.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="InformationToolsPanelAction") {
        EAction.showCadToolBarPanel("InformationToolsPanel");
        this.terminate();
    }
};

Information.prototype.formatLinearResult = function(distance) {
    var document = this.getDocument();
    if (isNull(document)) {
        return "";
    }

    // use preference for label precision:
    return RUnit.getLabel(distance, document, RSettings.getIntValue("Info/Precision", -1));
};

Information.prototype.formatAngularResult = function(angle) {
    var document = this.getDocument();
    if (isNull(document)) {
        return "";
    }

    return document.formatAngle(angle);
};

Information.prototype.formatAreaResult = function(area, rounded) {
    var document = this.getDocument();
    if (isNull(document)) {
        return "";
    }

    var prec = 12;
    if (rounded) {
        prec = 3;
    }

    var areaText;
    if (document.getUnit()===RS.Inch) {
        var sqft = Math.floor(area/144);
        var sqin = area-sqft*144;
        return "%1 (= %2ft² %3in²)".arg(area).arg(sqft, 0, 'f', prec).arg(sqin, 0, 'f', prec);
    }
    else {
        return "%1".arg(area, 0, 'f', prec);
    }
};

/**
 * \return Result formatted in dimension label format and with 6 decimal points.
 * e.g.: "3 1/3 [3.333333]"
 */
Information.prototype.formatLinearResultCmd = function(distance) {
    var ret = this.formatLinearResult(distance);
    var exact = sprintf("%0.6f", distance)
    if (ret!==exact) {
        ret += " [" + exact + "]";
    }
    return ret;
};

/**
 * \return Result formatted in dimension label format for angles and with
 * 6 decimal points.
 *
 * \param angle Angle in rad.
 */
Information.prototype.formatAngularResultCmd = function(angle) {
    var ret = this.formatAngularResult(angle);
    var exact = sprintf("%0.6f\u00B0", RMath.rad2deg(angle))
    if (ret!==exact) {
        ret += " [" + exact + "]";
    }
    return ret;
};

Information.prototype.addInfoLine = function(op, point1, point2, preview) {
    if (isNull(point1) || isNull(point2)) {
        return;
    }

    var di = this.getDocumentInterface();
    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();

    // line
    var line = new RLine(point1, point2);
    var angle = line.getAngle();
    this.addShape(op, line, preview);
    // ticks:
    this.addMajorTick(op, view, point1, angle, preview);
    this.addMajorTick(op, view, point2, angle, preview);
    this.addGridTicks(op, view, point1, point2, preview);
    
    // label
    var lengthText = this.formatLinearResult(line.getLength());
    //var lengthText = sprintf("%0.3f", line.getLength());
    view.clearTextLabels();
    this.addTextLabel(op, view, point2, lengthText, preview);
};

Information.prototype.addTextLabel = function(op, view, pos, text, preview) {
    var dx, dy;

    if (preview) {
        dx = view.mapDistanceFromView(10);
        dy = view.mapDistanceFromView(30);
        view.addTextLabel(new RTextLabel(new RVector(pos.x + dx, pos.y + dy), text));
    }
    else {
        dx = this.textHeight*0.5;
        dy = this.textHeight*1.2;
        var td = new RTextData();
        td.setAlignmentPoint(new RVector(pos.x + dx, pos.y + dy));
        td.setVAlign(RS.VAlignTop);
        td.setHAlign(RS.HAlignLeft);
        td.setText(text);
        td.setTextHeight(this.textHeight);
        td.setFontName("standard");
        op.addObject(new RTextEntity(this.getDocument(), td));
    }
};

Information.prototype.addGridTicks = function(op, view, point1, point2, preview) {
    var doc = this.getDocument();
    var minV = new RVector(0.001, 0.001);
    if (!isNull(doc)) {
        var linearFormat = doc.getLinearFormat();
        if (linearFormat==RS.ArchitecturalStacked ||
            linearFormat==RS.FractionalStacked ||
            linearFormat==RS.Architectural ||
            linearFormat==RS.Fractional) {

            minV = new RVector(1.0/128, 1.0/128);
        }
    }
    var spacings = ROrthoGrid.getIdealGridSpacing(view, 10, minV, new RVector(Number.NaN, Number.NaN));
    var gridSpacing = spacings[0];
    var metaGridSpacing = spacings[1];
    
    var c;

    // minor ticks
    var dv = point2.operator_subtract(point1);
    var a = point1.getAngleTo(point2);
    var b = new RVector(gridSpacing.x, 0); // assuming equal spacing for x / y
    b = b.rotate(a);
    var num = Math.ceil(dv.getMagnitude2D() / gridSpacing.x);
    for (var i = 1; i < num; ++i) {
        c = b.operator_multiply(i);
        this.addMinorTick(op, view, point1.operator_add(c), a, preview);
    }

    // major ticks
    b = new RVector(metaGridSpacing.x, 0); // assuming equal spacing for x / y
    b = b.rotate(a);
    num = Math.ceil(dv.getMagnitude2D() / metaGridSpacing.x);
    for (i = 1; i < num; ++i) {
        c = b.operator_multiply(i);
        this.addMajorTick(op, view, point1.operator_add(c), a, preview);
    }
};

Information.prototype.addMinorTick = function(op, view, p, angle, preview) {
    this.addTick(op, view, p, 2, angle, preview);
};

Information.prototype.addMajorTick = function(op, view, p, angle, preview) {
    this.addTick(op, view, p, 5, angle, preview);
};

Information.prototype.addTick = function(op, view, p, length, angle, preview) {
    var s = view.mapDistanceFromView(length);
    var v = new RVector(0, s);
    var v1 = v.rotate(angle + RMath.deg2rad(180));
    var st1 = p.operator_add(v1);
    var st2 = p.operator_subtract(v1);
    var tick = new RLine(st2, st1);
    this.addShape(op, tick, preview);
};

Information.prototype.addShape = function(op, shape, preview) {
    var di = this.getDocumentInterface();

    if (preview) {
        var clr = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));
        var brush = new QBrush();
        var lw = RLineweight.Weight000;
        var dashes = [];
        di.addShapeToPreview(shape, clr, brush, lw, Qt.SolidLine.valueOf(), dashes);
    }
    else {
        if (!isNull(op)) {
            var e = shapeToEntity(this.getDocument(), shape);
            if (!isNull(e)) {
                op.addObject(e);
            }
        }
    }
};

Information.prototype.slotAddToDrawingChanged = function(value) {
    this.addToDrawing = value;
    var optionsToolBar = EAction.getOptionsToolBar();
    var textHeightEdit = optionsToolBar.findChild("TextHeight");
    textHeightEdit.enabled = value;
    var textHeightLabel = optionsToolBar.findChild("TextHeightLabel");
    textHeightLabel.enabled = value;
};

Information.prototype.slotTextHeightChanged = function(value) {
    this.textHeight = value;
};

/**
 * Refreshes the preview.
 */
Information.prototype.resumeEvent = function() {
    EAction.prototype.resumeEvent.call(this);
    this.simulateMouseMoveEvent();
};

/**
 * Set a math line edit as receiver of the result.
 */
Information.prototype.setLineEdit = function(lineEditName) {
    this.lineEditName = lineEditName;
    this.autoTerminate = true;
    this.addToDrawing = false;
    this.setUiOptions(undefined);

    // make sure action can run even though a script is already running:
    this.setNoState();
};

Information.prototype.updateLineEdit = function(value) {
    if (isNull(this.lineEditName)) {
        return;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }

    var lineEdit = appWin.findChild(this.lineEditName);
    if (isNull(lineEdit)) {
        return;
    }

    if (!isOfType(lineEdit, QLineEdit) &&
        !isOfType(lineEdit, RMathComboBox) &&
        !isOfType(lineEdit, RMathLineEdit) &&
        !isOfType(lineEdit, RCommandLine)) {
        return;
    }

    var di = this.getDocumentInterface();
    var doc = di.getDocument();
    var varName = doc.addAutoVariable(value);

    if (isOfType(lineEdit, RMathComboBox)) {
        lineEdit.lineEdit().insert(varName);
    }
    else {
        lineEdit.insert(varName);
    }
};

Information.getMenu = function() {
    var menu = EAction.getMenu(Information.getTitle(), "InformationMenu");
    menu.setProperty("scriptFile", Information.includeBasePath + "/Information.js");
    return menu;
};

Information.getToolBar = function() {
    var tb = EAction.getToolBar(Information.getTitle(), "InformationToolBar");
    tb.visible = false;
    return tb;
};

Information.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "InformationToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Information Tools"), mtb);
        action.setScriptFile(Information.includeBasePath + "/Information.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Information.includeBasePath + "/Information.svg");
        //action.setStatusTip(qsTr("Show information tools"));
        action.setDefaultShortcut(new QKeySequence("w,i"));
        action.setNoState();
        action.setDefaultCommands(["infomenu", "informationmenu", "measuringmenu"]);
        action.setGroupSortOrder(40);
        action.setSortOrder(200);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Information.getTitle(),
        "InformationToolsPanel",
        true
    );
    return tb;
};

Information.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Information.getTitle(), "InformationMatrixPanel", 4000);
};

Information.getTitle = function() {
    return qsTr("&Info");
};

Information.prototype.getTitle = function() {
    return Information.getTitle();
};

Information.init = function() {
    Information.getMenu();
    Information.getToolBar();
    Information.getCadToolBarPanel();
    Information.getToolMatrixPanel();
};
