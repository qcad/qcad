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

include("scripts/sprintf.js");

function GridSettings() {
}

GridSettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Grid") ];
    }
    return [ qsTr("General"), qsTr("Grid") ];
};

/**
 * Called when the user changed the drawing / global paper unit in another
 * preference page.
 */
GridSettings.updateUnit = function(unit) {
    var unitSymbol = "";
    if (isString(unit)) {
        unit = parseInt(unit, 10);
    }

    unitSymbol = RUnit.unitToSymbol(unit);

    if (isNull(GridSettings.widgets)) {
        return;
    }

    for (var i=0; i<4; i++) {
        if (isNull(GridSettings.widgets["GridSpacingXUnit0%1".arg(i)])) {
            continue;
        }
        GridSettings.widgets["GridSpacingXUnit0%1".arg(i)].text = unitSymbol;
        GridSettings.widgets["GridSpacingYUnit0%1".arg(i)].text = unitSymbol;
        GridSettings.widgets["MetaGridSpacingXUnit0%1".arg(i)].text = unitSymbol;
        GridSettings.widgets["MetaGridSpacingYUnit0%1".arg(i)].text = unitSymbol;
    }

//    var i;
//    var cb = [];
//    cb.push(GridSettings.widgets["GridSpacingX"]);
//    cb.push(GridSettings.widgets["GridSpacingY"]);
//    cb.push(GridSettings.widgets["MetaGridSpacingX"]);
//    cb.push(GridSettings.widgets["MetaGridSpacingY"]);
//    for (i=0; i<cb.length; i++) {
//        cb[i].clear();
//        cb[i].addItem(qsTr("auto"));
//    }

//    var v, sv;

//    if (RUnit.isMetric(unit)) {
//        for (v=0.001; v<=1000; v*=10) {
//            sv = sprintf("%.4f", v);
//            for (i=0; i<cb.length; i++) {
//                cb[i].addItem(sv);
//            }
//        }
//    }
//    else {
//        for (v=1/128; v<=128; v*=2) {
//            sv = RMath.toFractionString(v, 128);
//            for (i=0; i<cb.length; i++) {
//                cb[i].addItem(sv);
//            }
//        }
//    }

//    for (i=0; i<cb.length; i++) {
//        cb[i].currentIndex = 0;
//    }
};

/**
 * Called when the user changed the linear format in another
 * preference page.
 */
GridSettings.updateLinearFormat = function(linearFormat) {
    var unitSymbol = "";
    if (isString(linearFormat)) {
        linearFormat = parseInt(linearFormat, 10);
    }

    var i;
    var cb = [];
    for (i=0; i<4; i++) {
        cb.push(GridSettings.widgets["GridSpacingX0%1".arg(i)]);
        cb.push(GridSettings.widgets["GridSpacingY0%1".arg(i)]);
        cb.push(GridSettings.widgets["MetaGridSpacingX0%1".arg(i)]);
        cb.push(GridSettings.widgets["MetaGridSpacingY0%1".arg(i)]);
    }
    for (i=0; i<cb.length; i++) {
        cb[i].clear();
        cb[i].addItem(qsTr("auto"));
    }

    var v, sv;

    if (linearFormat===RS.ArchitecturalStacked ||
        linearFormat===RS.FractionalStacked ||
        linearFormat===RS.Architectural ||
        linearFormat===RS.Fractional) {

        for (v=1/128; v<=128; v*=2) {
            sv = RMath.toFractionString(v, 128);
            for (i=0; i<cb.length; i++) {
                cb[i].addItem(sv);
            }
        }
    }
    else {
        for (v=0.001; v<=1000; v*=10) {
            sv = sprintf("%.4f", v);
            for (i=0; i<cb.length; i++) {
                cb[i].addItem(sv);
            }
        }
    }

    for (i=0; i<cb.length; i++) {
        cb[i].currentIndex = 0;
    }
};

GridSettings.initPreferences = function(pageWidget, calledByPrefDialog, document, preferencesAction) {
    GridSettings.widgets = getWidgets(pageWidget);

    // update unit symbols beside grid spacing inputs:
    // update available choices for minimum grid spacing:
    var unit;
    var linearFormat;
    if (!isNull(document)) {
        unit = document.getUnit();
        linearFormat = document.getLinearFormat();
    }
    else {
        // no document: use default unit / format:
        unit = RSettings.getIntValue("UnitSettings/Unit", RS.Millimeter);
        linearFormat = RSettings.getIntValue("DimensionSettings/LinearFormat", RS.Decimal);
    }

    // unit might have been changed by user:
    var unitCombo = objectFromPath("MainWindow::Unit");
    if (isComboBox(unitCombo)) {
        unit = unitCombo.itemData(unitCombo.currentIndex);
    }

    var lfCombo = objectFromPath("MainWindow::LinearFormat");
    if (isComboBox(lfCombo)) {
        linearFormat = lfCombo.itemData(lfCombo.currentIndex);
    }

    for (var i=0; i<4; i++) {
        eval("function f(checked) { GridSettings.isometricGridToggled(" + i +", checked); }")
        GridSettings.widgets["IsometricGrid0%1".arg(i)].toggled.connect(GridSettings, f);
        eval("function f() { GridSettings.updateIsometricGrid(" + i + "); }")
        GridSettings.widgets["GridSpacingY0%1".arg(i)].editTextChanged.connect(GridSettings, f);
        eval("function f() { GridSettings.updateIsometricMetaGrid(" + i + "); }")
        GridSettings.widgets["MetaGridSpacingY0%1".arg(i)].editTextChanged.connect(GridSettings, f);
    }

    GridSettings.updateUnit(unit);
    GridSettings.updateLinearFormat(linearFormat);
};

GridSettings.savePreferences = function(pageWidget, calledByPrefDialog, document) {
};

GridSettings.isometricGridToggled = function(i, checked) {
    GridSettings.updateIsometricGrid(i);
    GridSettings.updateIsometricMetaGrid(i);

    if (!checked) {
        var cbXCombo = GridSettings.widgets["GridSpacingX0%1".arg(i)];
        var cbYCombo = GridSettings.widgets["GridSpacingY0%1".arg(i)];
        cbXCombo.setEditText(cbYCombo.currentText);

        cbXCombo = GridSettings.widgets["MetaGridSpacingX0%1".arg(i)];
        cbYCombo = GridSettings.widgets["MetaGridSpacingY0%1".arg(i)];
        cbXCombo.setEditText(cbYCombo.currentText);
    }
};

GridSettings.updateIsometricGrid = function(i) {
    if (!GridSettings.widgets["IsometricGrid0%1".arg(i)].checked) {
        //qDebug("grid not isometric");
        return;
    }

    var sx, sy;

    // update isometric grid: compute x spacing for given y spacing:
    var cbXCombo = GridSettings.widgets["GridSpacingX0%1".arg(i)];
    var cbYCombo = GridSettings.widgets["GridSpacingY0%1".arg(i)];

    var str = cbYCombo.currentText;
    if (str===qsTr("auto")) {
        cbXCombo.setEditText(qsTr("auto"));
    }
    else {
        sy = parseFloat(cbYCombo.currentText);
        sx = sy * 2.0 * Math.sin(RMath.deg2rad(60));
        cbXCombo.setEditText(sx.toString());
    }
};

GridSettings.updateIsometricMetaGrid = function(i) {
    if (!GridSettings.widgets["IsometricGrid0%1".arg(i)].checked) {
        //qDebug("grid not isometric");
        return;
    }

    var sx, sy;

    // update isometric meta grid: compute x spacing for given y spacing:
    var cbXCombo = GridSettings.widgets["MetaGridSpacingX0%1".arg(i)];
    var cbYCombo = GridSettings.widgets["MetaGridSpacingY0%1".arg(i)];

    var str = cbYCombo.currentText;
    if (str===qsTr("auto")) {
        cbXCombo.setEditText(qsTr("auto"));
    }
    else {
        sy = parseFloat(cbYCombo.currentText);
        sx = sy * 2.0 * Math.sin(Math.PI/3.0);
        cbXCombo.setEditText(sx.toString());
    }
};

GridSettings.applyPreferences = function(doc, mdiChild) {
    if (isNull(doc) || isNull(mdiChild)) {
        return;
    }

    var di = mdiChild.getDocumentInterface();
    var scenes = di.getGraphicsScenes();

    for (var si = 0; si<scenes.length; ++si) {
        var scene = scenes[si];
        var views = scene.getGraphicsViews();
        for (var vi = 0; vi<views.length; ++vi) {
            var view = views[vi];
            view.regenerate(false);
        }
    }
};
