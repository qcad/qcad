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
            ["DIMDLI", RS.DIMDLI, 2.0],
        ];

/**
 * Called when the user changed the drawing / global unit in another
 * preference page.
 */
DimensionSettings.updateUnit = function(unit) {
    var widgets = getWidgets(this.pageWidget);
    if (isNull(widgets)) {
        return;
    }

    DimensionSettings.unit = unit;

    // (re-)init unit labels:
    var unitSymbol = "";
    unitSymbol = RUnit.unitToName(DimensionSettings.unit);
    for (var i=1; i<=6; i++) {
        var w = widgets["DimUnit" + i];
        if (isNull(w)) {
            continue;
        }
        w.text = unitSymbol;
    }

    // update previews:
    DimensionSettings.updateLinearPreview(widgets);
    DimensionSettings.updateAngularPreview(widgets);
    DimensionSettings.updateLinearFormatFromUnit(widgets);
};

DimensionSettings.postInitPreferences = function(pageWidget, calledByPrefDialog, document) {
    if (isNull(document)) {
        var widgets = getWidgets(pageWidget);
        DimensionSettings.updateLinearPreview(widgets);
        DimensionSettings.updateAngularPreview(widgets);
        return;
    }
};

DimensionSettings.initPreferences = function(pageWidget, calledByPrefDialog, document, preferencesAction, unit) {
    var list;
    
    DimensionSettings.pageWidget = pageWidget;
    var settingsName = pageWidget.objectName;
    var widgets = getWidgets(pageWidget);

    var wlf = widgets["LinearFormat"];
    var wlstz = widgets["LinearShowTrailingZeros"];
    var wlp = widgets["LinearPrecision"];
    var waf = widgets["AngularFormat"];
    var wastz = widgets["AngularShowTrailingZeros"];
    var wap = widgets["AngularPrecision"];
    var wdf = widgets["DimensionFont"];
    var wdtc = widgets["DimensionTextColor"];
    var wdp = widgets["DecimalPoint"];
    var wfg = widgets["FontGroup"];
    var wkp = widgets["KeepProportions"];

    if (isNull(unit)) {
        // figure out what unit currently applies
        // (the one from the document, ini file or combo box):
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
            var u = unitCombo.itemData(unitCombo.currentIndex);
            if (!isNull(u)) {
                unit = u;
            }
        }
    }
    DimensionSettings.unit = unit;

    // connect keep proportions check box:
    if (!isNull(widgets["KeepProportions"])) {
        widgets["KeepProportions"].toggled.connect(function(onOff) {
            if (onOff) {
                DimensionSettings.keepProportions(widgets["DIMTXT"].getValue(), widgets);
            }
        });
    }
    if (!isNull(widgets["DIMTXT"])) {
        widgets["DIMTXT"].valueChanged.connect(function(value) {
            DimensionSettings.keepProportions(value, widgets);
        });
    }

    // decimal point:
    if (!isNull(wdp)) {
        wdp.addItem(". (" + qsTr("point") + ")", '.'.charCodeAt(0));
        wdp.addItem(", (" + qsTr("comma") + ")", ','.charCodeAt(0));
        wdp.addItem("  (" + qsTr("space") + ")", ' '.charCodeAt(0));
        var dimdsep = RSettings.getIntValue(settingsName + "/DecimalPoint", '.'.charCodeAt(0));
        if (dimdsep===0) {
            dimdsep = '.'.charCodeAt(0);
        }

        wdp.currentIndex = wdp.findData(dimdsep);

        wdp["activated(int)"].connect(function() {
            DimensionSettings.updateLinearPreview(widgets);
            DimensionSettings.updateAngularPreview(widgets);
        });
    }

    // init linear dimension format combo boxes:
    if (!isNull(wlf)) {
        wlf.addItem(qsTr("Scientific"), RS.Scientific);
        wlf.addItem(qsTr("Decimal"), RS.Decimal);
        wlf.addItem(qsTr("Engineering"), RS.Engineering);
        wlf.addItem(qsTr("Architectural"), RS.ArchitecturalStacked);
        wlf.addItem(qsTr("Fractional"), RS.FractionalStacked);
        var defaultFormat = RUnit.isMetric(unit) ? RS.Decimal : RS.FractionalStacked;
        wlf.currentIndex = wlf.findData(RSettings.getIntValue(settingsName + "/LinearFormat", defaultFormat));
        // unsupported:
        //wlf.addItem(qsTr("Architectural"), RS.Architectural);
        //wlf.addItem(qsTr("Fractional"), RS.Fractional);
        //wlf.addItem(qsTr("Windows Desktop"), RS.WindowsDesktop);

        wlf["activated(int)"].connect(function() {
            DimensionSettings.updateLinearFormatFromUnit(widgets);
            DimensionSettings.updateLinearPrecision(widgets);
            DimensionSettings.updateLinearPreview(widgets);
        });
    }

    if (!isNull(wlstz)) {
        wlstz.stateChanged.connect(function() {
            DimensionSettings.updateLinearPreview(widgets);
        });
    }

    DimensionSettings.updateLinearPrecision(widgets);

    if (!isNull(wlp)) {
        wlp["activated(int)"].connect(function() {
            DimensionSettings.updateLinearPreview(widgets);
        });
        wlp.currentIndex = 4;
    }

    // init angular dimension format combo boxes:
    if (!isNull(waf)) {
        waf.addItem(qsTr("Decimal Degrees"), RS.DegreesDecimal);
        waf.addItem(qsTr("Deg/min/sec"), RS.DegreesMinutesSeconds);
        waf.addItem(qsTr("Gradians"), RS.Gradians);
        waf.addItem(qsTr("Radians"), RS.Radians);
        waf.addItem(qsTr("Surveyor's units"), RS.Surveyors);
        waf.currentIndex = waf.findData(RSettings.getIntValue(settingsName + "/AngularFormat", RS.DegreesDecimal));

        waf["activated(int)"].connect(function() {
            DimensionSettings.updateAngularPrecision(widgets);
            DimensionSettings.updateAngularPreview(widgets);
        });
    }

    if (!isNull(wastz)) {
        wastz.stateChanged.connect(function() {
            DimensionSettings.updateAngularPreview(widgets);
        });
        DimensionSettings.updateAngularPrecision(widgets);
    }

    if (!isNull(wap)) {
        wap["activated(int)"].connect(function() {
            DimensionSettings.updateAngularPreview(widgets, document);
        });
        wap.currentIndex = 0;
    }

    if (isNull(document)) {
        // defaults for new drawings:
        // update unit labels, preview:
        //DimensionSettings.updateUnit(unit);
        //DimensionSettings.updateLinearPrecision(widgets);
        //DimensionSettings.updateAngularPrecision(widgets);

        if (hasPlugin("DWG")) {
            // font:
            if (!isNull(wdf)) {
                wdf.setProperty("Loaded", true);
                wdf.editable = false;
                initFontComboBox(wdf);
                var dimFont = RSettings.getStringValue(settingsName + "/DimensionFont", "Standard");
                activateFont(wdf, dimFont.isEmpty() ? "Standard" : dimFont);
            }

            // text color:
            if (!isNull(wdtc)) {
                wdtc.setProperty("Loaded", true);
                var dimTextColor = RSettings.getColorValue(settingsName + "/DimensionTextColor", new RColor(RColor.ByBlock));
                wdtc.setColor(dimTextColor);
            }
        }
        else {
            if (!isNull(wfg)) {
                wfg.visible = false;
            }
        }

        // other global preferences are initialized automatically
        return;
    }

    // init dimension settings from document:
    var keepProportions = true;
    var dimtxt = 0.0;
    var w;
    for (var i=0; i<DimensionSettings.dimx.length; i++) {
        var item = DimensionSettings.dimx[i];
        w = widgets[item[0]];
        if (isNull(w)) {
            continue;
        }

        var dimprop = document.getKnownVariable(item[1], 2.5*item[2]);
        if (item[1]===RS.DIMTXT) {
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
    if (!isNull(wkp)) {
        wkp.checked = keepProportions;
        wkp.setProperty("Loaded", true);
    }

    // init dimension arrow type:
    var dimblk = document.getKnownVariable(RS.DIMBLK, "");
    var dimtsz = document.getKnownVariable(RS.DIMTSZ, 0.0);
    if (dimblk.toUpperCase()==="ARCHTICK" || dimtsz > RS.PointTolerance) {
        if (!isNull(widgets["ArchitecturalTick"])) {
            widgets["ArchitecturalTick"].checked = true;
        }
    }
    else {
        if (!isNull(widgets["Arrow"])) {
            widgets["Arrow"].checked = true;
        }
    }
    if (!isNull(widgets["ArchitecturalTick"])) {
        widgets["ArchitecturalTick"].setProperty("Loaded", true);
    }
    if (!isNull(widgets["Arrow"])) {
        widgets["Arrow"].setProperty("Loaded", true);
    }

    // init linear dimension format:
    var dimlunit = document.getKnownVariable(RS.DIMLUNIT, RS.Decimal);
    //widgets["LinearFormat"].currentIndex = dimlunit-1;
    if (!isNull(wlf)) {
        wlf.currentIndex = wlf.findData(dimlunit);
        wlf.setProperty("Loaded", true);
        wlf["currentIndexChanged(int)"].connect(function(idx) {
            var lf = wlf.itemData(idx);
            preferencesAction.linearFormatUpdated(lf);
        });
        DimensionSettings.updateLinearPrecision(widgets);
    }

    // init linear dimension precision:
    var dimdec = document.getKnownVariable(RS.DIMDEC, 4);
    if (!isNull(wlp)) {
        wlp.currentIndex = dimdec;
        wlp.setProperty("Loaded", true);
    }

    // init angular dimension format:
    var dimaunit = document.getKnownVariable(RS.DIMAUNIT, RS.DegreesDecimal);
    if (!isNull(waf)) {
        //waf.currentIndex = dimaunit;
        waf.currentIndex = widgets["AngularFormat"].findData(dimaunit);
        waf.setProperty("Loaded", true);
        DimensionSettings.updateAngularPrecision(widgets);
    }

    // init angular dimension precision:
    var dimadec = document.getKnownVariable(RS.DIMADEC, 0);
    if (!isNull(wap)) {
        wap.currentIndex = dimadec;
        wap.setProperty("Loaded", true);
    }

    // show leading / trailing zeroes:
    var dimzin = document.getKnownVariable(RS.DIMZIN, 12);
    if (!isNull(wlstz)) {
        wlstz.checked = !((dimzin & 8) === 8);
        wlstz.setProperty("Loaded", true);
    }
    var dimazin = document.getKnownVariable(RS.DIMAZIN, 3);
    if (!isNull(wastz)) {
        wastz.checked = !((dimazin & 2) === 2);
        wastz.setProperty("Loaded", true);
    }

    // decimal separator:
    if (!isNull(wdp)) {
        var dimdsep = document.getKnownVariable(RS.DIMDSEP, '.');
        if (dimdsep===0) {
            dimdsep = '.'.charCodeAt(0);
        }

        wdp.currentIndex = wdp.findData(dimdsep);
        wdp.setProperty("Loaded", true);
    }

    // update unit labels, preview:
    DimensionSettings.updateUnit(unit);

    if (hasPlugin("DWG")) {
        // font:
        if (!isNull(wdf)) {
            wdf.setProperty("Loaded", true);
            wdf.editable = false;
            //wdf.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred);
            initFontComboBox(wdf);
            var dimFont = document.getDimensionFont();
            activateFont(wdf, dimFont.isEmpty() ? "Standard" : dimFont);
        }

        // text color:
        if (!isNull(wdtc)) {
            wdtc.setProperty("Loaded", true);
            var dimTextColor = document.getKnownVariable(RS.DIMCLRT, new RColor(RColor.ByBlock));
            if (isValidColor(dimTextColor)) {
                wdtc.setColor(dimTextColor);
            }
        }
    }
    else {
        if (!isNull(wfg)) {
            wfg.visible = false;
        }
    }
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
    if (DimensionSettings.unit!==RS.Inch &&
        (linearFormat===RS.ArchitecturalStacked || linearFormat===RS.Engineering)) {

        widgets["LinearFormat"].currentIndex = 1;
        DimensionSettings.showLinearFormatWarning();
    }
};

DimensionSettings.showLinearFormatWarning = function() {
    var appWin = EAction.getMainWindow();
    QMessageBox.warning(appWin,
                        qsTr("Unit / Format"),
                        qsTr("The drawing unit must be \"Inch\" to display dimension labels in "
                             + "formats \"Architectural\" or \"Engineering\". "
                             + "Format changed to \"Decimal\"."));
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
    var showTrailingZeros = isNull(widgets["LinearShowTrailingZeros"]) ? false : widgets["LinearShowTrailingZeros"].checked;
    var dimdsep = isNull(widgets["DecimalPoint"]) ? '.'.charCodeAt(0) : widgets["DecimalPoint"].itemData(widgets["DecimalPoint"].currentIndex);
    if (isNull(dimdsep)) {
        dimdsep = '.'.charCodeAt(0);
    }
    var value = 14.43112351;
    if (showTrailingZeros===true && RUnit.isMetric(DimensionSettings.unit)) {
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
                showTrailingZeros,
                false,
                dimdsep);
        if (prev==="") {
            prev = "N/A";
        }
    }
    widgets["LinearPreview"].text = prev;
};

DimensionSettings.updateAngularPreview = function(widgets) {
    var wFormat = widgets["AngularFormat"];
    var showTrailingZeros = widgets["AngularShowTrailingZeros"].checked;
    var dimdsep = isNull(widgets["DecimalPoint"]) ? '.'.charCodeAt(0) : widgets["DecimalPoint"].itemData(widgets["DecimalPoint"].currentIndex);
    if (isNull(dimdsep)) {
        dimdsep = '.'.charCodeAt(0);
    }
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
                true, showTrailingZeros,
                dimdsep);
        if (prev==="") {
            prev = "N/A";
        }
    }
    widgets["AngularPreview"].text = prev;
};

DimensionSettings.savePreferences = function(pageWidget, calledByPrefDialog, document, transaction) {
    var widgets = getWidgets(pageWidget);

    if (isNull(document)) {
        RSettings.setValue("DimensionSettings/DimensionFont", widgets["DimensionFont"].currentText);
        return;
    }

    for (var i=0; i<DimensionSettings.dimx.length; i++) {
        var item = DimensionSettings.dimx[i];
        document.setKnownVariable(item[1], widgets[item[0]].getValue(), transaction);
        widgets[item[0]].setProperty("Saved", true);
    }

    // dimension arrow type:
    if (widgets["ArchitecturalTick"].checked) {
        document.setKnownVariable(RS.DIMTSZ, document.getKnownVariable(RS.DIMASZ), transaction);
        //document.setKnownVariable(RS.DIMBLK, "ArchTick", transaction);
    }
    else {
        document.setKnownVariable(RS.DIMTSZ, 0.0, transaction);
        //document.setKnownVariable(RS.DIMBLK, "", transaction);
    }
    widgets["ArchitecturalTick"].setProperty("Saved", true);
    widgets["Arrow"].setProperty("Saved", true);

    // decimal point:
    document.setKnownVariable(RS.DIMDSEP, widgets["DecimalPoint"].itemData(widgets["DecimalPoint"].currentIndex), transaction);

    // dimension format / precision:
    document.setKnownVariable(RS.DIMLUNIT, widgets["LinearFormat"].currentIndex+1, transaction);
    document.setKnownVariable(RS.DIMDEC, widgets["LinearPrecision"].currentIndex, transaction);
    document.setKnownVariable(RS.DIMAUNIT, widgets["AngularFormat"].currentIndex, transaction);
    document.setKnownVariable(RS.DIMADEC, widgets["AngularPrecision"].currentIndex, transaction);
    document.setKnownVariable(RS.DIMCLRT, widgets["DimensionTextColor"].getColor(), transaction);
    document.setDimensionFont(widgets["DimensionFont"].currentText, transaction);

    // show leading / trailing zeroes:
    if (widgets["LinearShowTrailingZeros"].checked) {
        document.setKnownVariable(RS.DIMZIN, 0, transaction);
    }
    else {
        document.setKnownVariable(RS.DIMZIN, 8, transaction);
    }
    widgets["LinearShowTrailingZeros"].setProperty("Saved", true);

    if (widgets["AngularShowTrailingZeros"].checked) {
        document.setKnownVariable(RS.DIMAZIN, 0, transaction);
    }
    else {
        document.setKnownVariable(RS.DIMAZIN, 2, transaction);
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
