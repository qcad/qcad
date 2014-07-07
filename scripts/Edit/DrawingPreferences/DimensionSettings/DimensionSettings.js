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

function DimensionSettings() {
    // current unit (might originate from document, ini file or combo box):
    DimensionSettings.unit = undefined;
}

DimensionSettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Dimension Settings") ];
    }
    return [ qsTr("Dimension"), qsTr("Dimension Settings") ];
};

DimensionSettings.dimx = [
            // widget name, dxf variable, factor relative to dimtxt
            ["DIMTXT", RS.DIMTXT, 1.0],
            ["DIMEXE", RS.DIMEXE, 0.5],
            ["DIMEXO", RS.DIMEXO, 0.25],
            ["DIMGAP", RS.DIMGAP, 0.25],
            ["DIMASZ", RS.DIMASZ, 1.0],
            ["DIMSCALE", RS.DIMSCALE, undefined],
        ];

/**
 * Called when the user changed the drawing / global unit in another
 * preference page.
 */
DimensionSettings.updateUnit = function(unit) {
    var widgets = getWidgets(this.pageWidget);
    DimensionSettings.unit = unit;

    // (re-)init unit labels:
    var unitSymbol = "";
    unitSymbol = RUnit.unitToName(DimensionSettings.unit);
    for (var i=1; i<=5; i++) {
        widgets["DimUnit" + i].text = unitSymbol;
    }

    // update previews:
    DimensionSettings.updateLinearPreview(widgets);
    DimensionSettings.updateAngularPreview(widgets);
    DimensionSettings.updateLinearFormatFromUnit(widgets);
};

DimensionSettings.postInitPreferences = function(pageWidget, calledByPrefDialog, document) {
    if (isNull(document)) {
        var widgets = getWidgets(pageWidget);
        // update unit labels, preview:
        //var unit = RSettings.getIntValue("UnitSettings/Unit", RS.Millimeter);
//        DimensionSettings.updateUnit(unit);
//        DimensionSettings.updateLinearPrecision(widgets);
//        DimensionSettings.updateAngularPrecision(widgets);

        DimensionSettings.updateLinearPreview(widgets);
        DimensionSettings.updateAngularPreview(widgets);
        return;
    }
};

DimensionSettings.initPreferences = function(pageWidget, calledByPrefDialog, document, preferencesAction) {
    var w, list;
    
    DimensionSettings.pageWidget = pageWidget;
    var widgets = getWidgets(pageWidget);

    // figure out what unit currently applies
    // (the one from the document, ini file or combo box):
    var unit;
    if (!isNull(document)) {
        // drawing unit:
        unit = document.getUnit();
    }
    else {
        // global unit:
        unit = RSettings.getIntValue("UnitSettings/Unit", RS.Millimeter);
    }

    // unit might have been changed by user:
    var unitCombo = objectFromPath("MainWindow::Unit");
    if (isComboBox(unitCombo)) {
        unit = unitCombo.itemData(unitCombo.currentIndex);
    }
    DimensionSettings.unit = unit;

    // connect keep proportions check box:
    widgets["KeepProportions"].toggled.connect(function(onOff) {
        if (onOff) {
            DimensionSettings.keepProportions(widgets["DIMTXT"].getValue(), widgets);
        }
    });
    widgets["DIMTXT"].valueChanged.connect(function(value) {
        DimensionSettings.keepProportions(value, widgets);
    });

    // init linear dimension format combo boxes:
    w = widgets["LinearFormat"];
    w.addItem(qsTr("Scientific"), RS.Scientific);
    w.addItem(qsTr("Decimal"), RS.Decimal);
    w.addItem(qsTr("Engineering"), RS.Engineering);
    w.addItem(qsTr("Architectural"), RS.ArchitecturalStacked);
    w.addItem(qsTr("Fractional"), RS.FractionalStacked);
    w.currentIndex = w.findData(RSettings.getIntValue("DimensionSettings/LinearFormat", RS.Decimal));
    // unsupported:
    //w.addItem(qsTr("Architectural"), RS.Architectural);
    //w.addItem(qsTr("Fractional"), RS.Fractional);
    //w.addItem(qsTr("Windows Desktop"), RS.WindowsDesktop);

    w["activated(int)"].connect(function() {
        DimensionSettings.updateLinearFormatFromUnit(widgets);
        DimensionSettings.updateLinearPrecision(widgets);
        DimensionSettings.updateLinearPreview(widgets);
    });

    w = widgets["LinearShowTrailingZeros"];
    w.stateChanged.connect(function() {
        DimensionSettings.updateLinearPreview(widgets);
    });

    DimensionSettings.updateLinearPrecision(widgets);

    w = widgets["LinearPrecision"];
    w["activated(int)"].connect(function() {
        DimensionSettings.updateLinearPreview(widgets);
    });
    w.currentIndex = 4;

    // init angular dimension format combo boxes:
    w = widgets["AngularFormat"];
    w.addItem(qsTr("Decimal Degrees"), RS.DegreesDecimal);
    w.addItem(qsTr("Deg/min/sec"), RS.DegreesMinutesSeconds);
    w.addItem(qsTr("Gradians"), RS.Gradians);
    w.addItem(qsTr("Radians"), RS.Radians);
    w.addItem(qsTr("Surveyor's units"), RS.Surveyors);
    w.currentIndex = w.findData(RSettings.getIntValue("DimensionSettings/AngularFormat", RS.DegreesDecimal));

    w["activated(int)"].connect(function() {
        DimensionSettings.updateAngularPrecision(widgets);
        DimensionSettings.updateAngularPreview(widgets);
    });

    w = widgets["AngularShowTrailingZeros"];
    w.stateChanged.connect(function() {
        DimensionSettings.updateAngularPreview(widgets);
    });

    DimensionSettings.updateAngularPrecision(widgets);

    w = widgets["AngularPrecision"];
    w["activated(int)"].connect(function() {
        DimensionSettings.updateAngularPreview(widgets, document);
    });
    w.currentIndex = 0;

    if (isNull(document)) {
        // update unit labels, preview:
        //DimensionSettings.updateUnit(unit);
        //DimensionSettings.updateLinearPrecision(widgets);
        //DimensionSettings.updateAngularPrecision(widgets);
        // global preferences are initialized automatically
        return;
    }

    // init dimension settings from document:
    var keepProportions = true;
    var dimtxt = 0.0;
    for (var i=0; i<DimensionSettings.dimx.length; i++) {
        var item = DimensionSettings.dimx[i];
        w = widgets[item[0]];
        var dimprop = document.getKnownVariable(item[1], 2.5*item[2]);
        if (item[1]==RS.DIMTXT) {
            dimtxt = dimprop;
        }
        else {
            if (Math.abs(dimprop-dimtxt*item[2]) > RS.PointTolerance) {
                keepProportions = false;
            }
        }
        //w.defaultValue = [w.text, w.getDefaultUnit()];
        w.defaultValue = w.text;
        w.setValue(dimprop);
        w.setProperty("Loaded", true);
    }

    // init keep proportions check box:
    widgets["KeepProportions"].checked = keepProportions;
    widgets["KeepProportions"].setProperty("Loaded", true);

    // init dimension arrow type:
    var dimblk = document.getKnownVariable(RS.DIMBLK, "");
    var dimtsz = document.getKnownVariable(RS.DIMTSZ, 0.0);
    if (dimblk.toUpperCase()=="ARCHTICK" || dimtsz > RS.PointTolerance) {
        widgets["ArchitecturalTick"].checked = true;
    }
    else {
        widgets["Arrow"].checked = true;
    }
    widgets["ArchitecturalTick"].setProperty("Loaded", true);
    widgets["Arrow"].setProperty("Loaded", true);

    // init linear dimension format:
    var dimlunit = document.getKnownVariable(RS.DIMLUNIT, RS.Decimal);
    //widgets["LinearFormat"].currentIndex = dimlunit-1;
    widgets["LinearFormat"].currentIndex = widgets["LinearFormat"].findData(dimlunit);
    widgets["LinearFormat"].setProperty("Loaded", true);
    widgets["LinearFormat"]["currentIndexChanged(int)"].connect(function(idx) {
        var lf = widgets["LinearFormat"].itemData(idx);
        preferencesAction.linearFormatUpdated(lf);
    });
    DimensionSettings.updateLinearPrecision(widgets);

    // init linear dimension precision:
    var dimdec = document.getKnownVariable(RS.DIMDEC, 4);
    widgets["LinearPrecision"].currentIndex = dimdec;
    widgets["LinearPrecision"].setProperty("Loaded", true);

    // init angular dimension format:
    var dimaunit = document.getKnownVariable(RS.DIMAUNIT, RS.DegreesDecimal);
    //widgets["AngularFormat"].currentIndex = dimaunit;
    widgets["AngularFormat"].currentIndex = widgets["AngularFormat"].findData(dimaunit);
    widgets["AngularFormat"].setProperty("Loaded", true);
    DimensionSettings.updateAngularPrecision(widgets);

    // init angular dimension precision:
    var dimadec = document.getKnownVariable(RS.DIMADEC, 0);
    widgets["AngularPrecision"].currentIndex = dimadec;
    widgets["AngularPrecision"].setProperty("Loaded", true);

    // show leading / trailing zeroes:
    var dimzin = document.getKnownVariable(RS.DIMZIN, 12);
    widgets["LinearShowTrailingZeros"].checked = !((dimzin & 8) === 8);
    widgets["LinearShowTrailingZeros"].setProperty("Loaded", true);
    var dimazin = document.getKnownVariable(RS.DIMAZIN, 3);
    widgets["AngularShowTrailingZeros"].checked = !((dimazin & 2) === 2);
    widgets["AngularShowTrailingZeros"].setProperty("Loaded", true);

    // update unit labels, preview:
    DimensionSettings.updateUnit(unit);

    if (hasPlugin("DWG")) {
        widgets["DimensionFont"].setProperty("Loaded", true);
        widgets["DimensionFont"].editable = false;
        //widgets["DimensionFont"].setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred);
        initFontComboBox(widgets["DimensionFont"]);
        var dimFont = document.getDimensionFont();
        activateFont(widgets["DimensionFont"], dimFont.isEmpty() ? "Standard" : dimFont);
    }
    else {
        widgets["FontGroup"].visible = false;
    }

    // update previews:
    //DimensionSettings.updateLinearPreview(widgets);
    //DimensionSettings.updateAngularPreview(widgets);
};

/**
 * Updates dimension sizes proportional to dimtxt.
 */
DimensionSettings.keepProportions = function(value, widgets) {
    if (widgets["KeepProportions"].checked) {
        for (var i=1; i<DimensionSettings.dimx.length; i++) {
            var item = DimensionSettings.dimx[i];
            if (!isNull(item[2])) {
                widgets[item[0]].setValue(value*item[2]);
            }
        }
    }
};

/**
 * Makes sure that linear format and drawing unit match.
 */
DimensionSettings.updateLinearFormatFromUnit = function(widgets) {
    var linearFormat = widgets["LinearFormat"].currentIndex+1;
    //var drawingUnit = document.getUnit();
    if (DimensionSettings.unit!=RS.Inch &&
        (linearFormat==RS.ArchitecturalStacked || linearFormat==RS.Engineering)) {

        var appWin = EAction.getMainWindow();
        widgets["LinearFormat"].currentIndex = 1;
        QMessageBox.warning(appWin,
                            qsTr("Unit / Format"),
                            qsTr("The drawing unit must be 'Inch' to display dimension labels in "
                                 + "formats 'Architectural' or 'Engineering'. "
                                 + "Format changed to 'Decimal'."));
    }
};


/**
 * Updates the linear precision combobox depending on the current
 * chosen format.
 */
DimensionSettings.updateLinearPrecision = function(widgets) {
    var wFormat = widgets["LinearFormat"];
    var wPrecision = widgets["LinearPrecision"];
    var index = wPrecision.currentIndex;
    wPrecision.clear();

    switch (wFormat.currentIndex+1) {
    case RS.Scientific:
        // scientific
        wPrecision.addItem("0E+00", 0);
        wPrecision.addItem("0.0E+00", 1);
        wPrecision.addItem("0.00E+00", 2);
        wPrecision.addItem("0.000E+00", 3);
        wPrecision.addItem("0.0000E+00", 4);
        wPrecision.addItem("0.00000E+00", 5);
        wPrecision.addItem("0.000000E+00", 6);
        wPrecision.addItem("0.0000000E+00", 7);
        wPrecision.addItem("0.00000000E+00", 8);
        break;

    case RS.Decimal:
        // decimal
        wPrecision.addItem("0", 0);
        wPrecision.addItem("0.0", 1);
        wPrecision.addItem("0.00", 2);
        wPrecision.addItem("0.000", 3);
        wPrecision.addItem("0.0000", 4);
        wPrecision.addItem("0.00000", 5);
        wPrecision.addItem("0.000000", 6);
        wPrecision.addItem("0.0000000", 7);
        wPrecision.addItem("0.00000000", 8);
        break;

    case RS.Engineering:
        // engineering:
        wPrecision.addItem("0'-0\"", 0);
        wPrecision.addItem("0'-0.0\"", 1);
        wPrecision.addItem("0'-0.00\"", 2);
        wPrecision.addItem("0'-0.000\"", 3);
        wPrecision.addItem("0'-0.0000\"", 4);
        wPrecision.addItem("0'-0.00000\"", 5);
        wPrecision.addItem("0'-0.000000\"", 6);
        wPrecision.addItem("0'-0.0000000\"", 7);
        wPrecision.addItem("0'-0.00000000\"", 8);
        break;

    case RS.ArchitecturalStacked:
        // architectural:
        wPrecision.addItem("0'-0\"", 0);
        wPrecision.addItem("0'-0 1/2\"", 1);
        wPrecision.addItem("0'-0 1/4\"", 2);
        wPrecision.addItem("0'-0 1/8\"", 3);
        wPrecision.addItem("0'-0 1/16\"", 4);
        wPrecision.addItem("0'-0 1/32\"", 5);
        wPrecision.addItem("0'-0 1/64\"", 6);
        wPrecision.addItem("0'-0 1/128\"", 7);
        wPrecision.addItem("0'-0 1/256\"", 8);
        break;

    case RS.FractionalStacked:
        // fractional
        wPrecision.addItem("0", 0);
        wPrecision.addItem("0 1/2", 1);
        wPrecision.addItem("0 1/4", 2);
        wPrecision.addItem("0 1/8", 3);
        wPrecision.addItem("0 1/16", 4);
        wPrecision.addItem("0 1/32", 5);
        wPrecision.addItem("0 1/64", 6);
        wPrecision.addItem("0 1/128", 7);
        wPrecision.addItem("0 1/256", 8);
        break;

    default:
        break;
    }

    if (index>=0) {
        wPrecision.currentIndex = index;
    }
};

/**
 * Updates the angular precision combobox depending on the current
 * chosen format.
 */
DimensionSettings.updateAngularPrecision = function(widgets) {
    var wFormat = widgets["AngularFormat"];
    var wPrecision = widgets["AngularPrecision"];
    var index = wPrecision.currentIndex;
    wPrecision.clear();

    switch (wFormat.currentIndex) {
    case 0:
        // decimal
        wPrecision.addItem("0", 0);
        wPrecision.addItem("0.0", 1);
        wPrecision.addItem("0.00", 2);
        wPrecision.addItem("0.000", 3);
        wPrecision.addItem("0.0000", 4);
        wPrecision.addItem("0.00000", 5);
        wPrecision.addItem("0.000000", 6);
        wPrecision.addItem("0.0000000", 7);
        wPrecision.addItem("0.00000000", 8);
        break;

    case 1:
        // deg/min/sec:
        wPrecision.addItem("0d", 0);
        wPrecision.addItem("0d00'", 1);
        wPrecision.addItem("0d00'00\"", 2);
        wPrecision.addItem("0d00'00.0\"", 3);
        wPrecision.addItem("0d00'00.00\"", 4);
        wPrecision.addItem("0d00'00.000\"", 5);
        wPrecision.addItem("0d00'00.0000\"", 6);
        break;

    case 2:
        // gradians:
        wPrecision.addItem("0g", 0);
        wPrecision.addItem("0.0g", 1);
        wPrecision.addItem("0.00g", 2);
        wPrecision.addItem("0.000g", 3);
        wPrecision.addItem("0.0000g", 4);
        wPrecision.addItem("0.00000g", 5);
        wPrecision.addItem("0.000000g", 6);
        wPrecision.addItem("0.0000000g", 7);
        wPrecision.addItem("0.00000000g", 8);
        break;

    case 3:
        // radians:
        wPrecision.addItem("0r", 0);
        wPrecision.addItem("0.0r", 1);
        wPrecision.addItem("0.00r", 2);
        wPrecision.addItem("0.000r", 3);
        wPrecision.addItem("0.0000r", 4);
        wPrecision.addItem("0.00000r", 5);
        wPrecision.addItem("0.000000r", 6);
        wPrecision.addItem("0.0000000r", 7);
        wPrecision.addItem("0.00000000r", 8);
        break;

    case 4:
        // surveyor's units:
        wPrecision.addItem("N 0d E", 0);
        wPrecision.addItem("N 0d00' E", 1);
        wPrecision.addItem("N 0d00'00\" E", 2);
        wPrecision.addItem("N 0d00'00.0\" E", 3);
        wPrecision.addItem("N 0d00'00.00\" E", 4);
        wPrecision.addItem("N 0d00'00.000\" E", 5);
        wPrecision.addItem("N 0d00'00.0000\" E", 6);
        break;

    default:
        break;
    }

    if (index>=0) {
        wPrecision.currentIndex = index;
    }
};

DimensionSettings.updateLinearPreview = function(widgets) {
    var wFormat = widgets["LinearFormat"];
    var showTrailingZeros = widgets["LinearShowTrailingZeros"].checked;
    var value = 14.43112351;
    if (showTrailingZeros===true) {
        value = 10.0;
    }

    var prev;
    if (wFormat.currentIndex < 0 || widgets["LinearPrecision"].currentIndex < 0) {
        prev = "N/A";
    } else {
        prev = RUnit.formatLinear(value,
                DimensionSettings.unit,
                wFormat.itemData(wFormat.currentIndex),
                widgets["LinearPrecision"].currentIndex,
                false, false,
                showTrailingZeros);
        if (prev==="") {
            prev = "N/A";
        }
    }
    widgets["LinearPreview"].text = prev;
};

DimensionSettings.updateAngularPreview = function(widgets) {
    var wFormat = widgets["AngularFormat"];
    var showTrailingZeros = widgets["AngularShowTrailingZeros"].checked;
    var value = RMath.deg2rad(37.15357578);
    if (showTrailingZeros===true) {
        value = RMath.deg2rad(60.0);
    }

    var prev;
    if (wFormat.currentIndex < 0
            || widgets["AngularPrecision"].currentIndex < 0) {
        prev = "N/A";
    } else {        
        prev = RUnit.formatAngle(value,
                wFormat.itemData(wFormat.currentIndex),
                widgets["AngularPrecision"].currentIndex,
                showTrailingZeros);
        if (prev==="") {
            prev = "N/A";
        }
    }
    widgets["AngularPreview"].text = prev;
};

DimensionSettings.savePreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);

    if (isNull(document)) {
        return;
    }

    for (var i=0; i<DimensionSettings.dimx.length; i++) {
        var item = DimensionSettings.dimx[i];
        document.setKnownVariable(item[1], widgets[item[0]].getValue());
        widgets[item[0]].setProperty("Saved", true);
    }

    // dimension arrow type:
    if (widgets["ArchitecturalTick"].checked) {
        document.setKnownVariable(RS.DIMTSZ, document.getKnownVariable(RS.DIMASZ));
        //document.setKnownVariable(RS.DIMBLK, "ArchTick");
    }
    else {
        document.setKnownVariable(RS.DIMTSZ, 0.0);
        //document.setKnownVariable(RS.DIMBLK, "");
    }
    widgets["ArchitecturalTick"].setProperty("Saved", true);
    widgets["Arrow"].setProperty("Saved", true);

    //qDebug("linear format: ", );
    //qDebug("unit: ", document.getUnit());

//    var linearFormat = widgets["LinearFormat"].currentIndex+1;
//    var drawingUnit = document.getUnit();
//    if (linearFormat==RS.ArchitecturalStacked && drawingUnit!=RS.Inch) {
//        var appWin = EAction.getMainWindow();
//        document.setUnit(RS.Inch);
//        QMessageBox.warning(appWin,
//                            qsTr("Unit / Format"),
//                            qsTr("The drawing unit must be 'Inch' to display dimension labels in "
//                                 + "format 'architectural'."
//                                 + "The drawing unit was changed to Inch automatically."));
//    }

    // dimension format / precision:
    document.setKnownVariable(RS.DIMLUNIT, widgets["LinearFormat"].currentIndex+1);
    document.setKnownVariable(RS.DIMDEC, widgets["LinearPrecision"].currentIndex);
    document.setKnownVariable(RS.DIMAUNIT, widgets["AngularFormat"].currentIndex);
    document.setKnownVariable(RS.DIMADEC, widgets["AngularPrecision"].currentIndex);
    document.setDimensionFont(widgets["DimensionFont"].currentText);
    qDebug("dim font: ", widgets["DimensionFont"].currentText);

    // show leading / trailing zeroes:
    if (widgets["LinearShowTrailingZeros"].checked) {
        document.setKnownVariable(RS.DIMZIN, 0);
    }
    else {
        document.setKnownVariable(RS.DIMZIN, 8);
    }
    widgets["LinearShowTrailingZeros"].setProperty("Saved", true);

    if (widgets["AngularShowTrailingZeros"].checked) {
        document.setKnownVariable(RS.DIMAZIN, 0);
    }
    else {
        document.setKnownVariable(RS.DIMAZIN, 2);
    }
    widgets["AngularShowTrailingZeros"].setProperty("Saved", true);


    // force update of bounding box of dimension entities:
    var ids = document.queryAllEntities();
    for (i=0; i<ids.length; i++) {
        var entityId = ids[i];
        var entity = document.queryEntity(entityId);
        if (!isDimensionEntity(entity)) {
            // ignore non dimension entities:
            continue;
        }

        document.removeFromSpatialIndex(entity);
        entity.update();
        document.addToSpatialIndex(entity);
    }
};
