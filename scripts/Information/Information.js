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
 * \defgroup ecma_information Measuring / Information Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * measuring and information tools.
 */
include("../EAction.js");

/**
 * \class Information
 * \brief Base class for all measuring and information tools.
 */
function Information(guiAction) {
    EAction.call(this, guiAction);
}

Information.prototype = new EAction();
Information.includeBasePath = includeBasePath;

Information.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName=="InformationMenu") {
        EAction.showCadToolBarPanel("InformationToolsPanel");
        this.terminate();
    }
};

Information.prototype.formatLinearResult = function(distance) {
    var document = this.getDocument();
    if (isNull(document)) {
        return "";
    }

    return RUnit.getLabel(distance, document, true);
};

Information.prototype.formatAngularResult = function(angle) {
    var document = this.getDocument();
    if (isNull(document)) {
        return "";
    }

    return RUnit.formatAngle(angle,
                              document.getAngleFormat(), document.getAnglePrecision(),
                              document.showLeadingZeroesAngle(), document.showTrailingZeroesAngle());
};

/**
 * \return Result formatted in dimension label format and with 6 decimal points.
 * e.g.: "3 1/3 [3.333333]"
 */
Information.prototype.formatLinearResultCmd = function(distance) {
    var ret = this.formatLinearResult(distance);
    var exact = sprintf("%0.6f", distance)
    if (ret!=exact) {
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
    if (ret!=exact) {
        ret += " [" + exact + "]";
    }
    return ret;
};

Information.prototype.addInfoLine = function(point1, point2) {
    if (isNull(point1) || isNull(point2)) {
        return;
    }

    var di = this.getDocumentInterface();
    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();

    // line
    var line = new RLine(point1, point2);
    var angle = line.getAngle();
    this.addShape(line);
    // tickers
    this.addMajorTicker(view, point1, angle);
    this.addMajorTicker(view, point2, angle);
    this.addGridTickers(view, point1, point2);
    
    // label
    var dx = view.mapDistanceFromView(10);
    var dy = view.mapDistanceFromView(30);
    var lengthText = this.formatLinearResult(line.getLength());
    //var lengthText = sprintf("%0.3f", line.getLength());
    view.clearTextLabels();
    view.addTextLabel(new RTextLabel(new RVector(point2.x + dx,
            point2.y + dy), lengthText));
};

Information.prototype.addGridTickers = function(view, point1, point2) {
    var spacings = ROrthoGrid.getIdealGridSpacing(view, 10, new RVector(0.001, 0.001), new RVector(0.001, 0.001));
    var gridSpacing = spacings[0];
    var metaGridSpacing = spacings[1];
    
    // minor tickers
    var dv = point2.operator_subtract(point1);
    var a = point1.getAngleTo(point2);
    var b = new RVector(gridSpacing.x, 0); // assuming equal spacing for x / y
    b = b.rotate(a);
    var c = b;
    var num = Math.ceil(dv.getMagnitude() / gridSpacing.x);
    for (var i = 1; i < num; ++i) {
        c = b.operator_multiply(i);
        this.addMinorTicker(view, point1.operator_add(c), a);
    }

    // major tickers
    b = new RVector(metaGridSpacing.x, 0); // assuming equal spacing for x / y
    b = b.rotate(a);
    c = b;
    num = Math.ceil(dv.getMagnitude() / metaGridSpacing.x);
    for (i = 1; i < num; ++i) {
        c = b.operator_multiply(i);
        this.addMajorTicker(view, point1.operator_add(c), a);
    }
};

Information.prototype.addMinorTicker = function(view, p, angle) {
    this.addTicker(view, p, 2, angle);
};

Information.prototype.addMajorTicker = function(view, p, angle) {
    this.addTicker(view, p, 5, angle);
};

Information.prototype.addTicker = function(view, p, length, angle) {
    var s = view.mapDistanceFromView(length);
    var v = new RVector(0, s);
    v1 = v.rotate(angle + RMath.deg2rad(180));
    var st1 = p.operator_add(v1);
    var st2 = p.operator_subtract(v1);
    var ticker = new RLine(st2, st1);
    this.addShape(ticker);
};

Information.prototype.addShape = function(shape) {
    var di = this.getDocumentInterface();
    var clr = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));
    var brush = new QBrush();
    var lw = RLineweight.Weight000;
    var dashes = new Array();
    di.addShapeToPreview(shape, clr, brush, lw, Qt.SolidLine.valueOf(), dashes);
};

/**
 * Refreshes the preview.
 */
Information.prototype.resumeEvent = function() {
    EAction.prototype.resumeEvent.call(this);
    this.simulateMouseMoveEvent();
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
    var actionName = "InformationMenu";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var separator = new RGuiAction("", RMainWindowQt.getMainWindow());
        separator.setSeparator(true);
        separator.setSortOrder(1900);
        CadToolBarPanel.prototype.addAction.call(mtb, separator);

        var action = new RGuiAction(qsTr("Information Tools"), mtb);
        action.setScriptFile(Information.includeBasePath + "/Information.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Information.includeBasePath + "/Information.svg");
        action.setStatusTip(qsTr("Show information tools"));
        action.setDefaultShortcut(new QKeySequence("w,i"));
        action.setNoState();
        action.setProperty("SortOrder", 2000);
        action.setDefaultCommands(["infomenu", "informationmenu", "measuringmenu"]);
        CadToolBarPanel.prototype.addAction.call(mtb, action);
    }

    var tb = EAction.getCadToolBarPanel(
        Information.getTitle(),
        "InformationToolsPanel",
        true
    );
    return tb;
};

Information.getTitle = function() {
    return qsTr("&Info");
};

Information.prototype.getTitle = function() {
    return Information.getTitle();
};
