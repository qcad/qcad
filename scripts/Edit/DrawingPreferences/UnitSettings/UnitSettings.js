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

include("scripts/Edit/DrawingPreferences/DimensionSettings/DimensionSettings.js");

function UnitSettings() {
}

UnitSettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Drawing Unit") ];
    }
    return [ qsTr("General"), qsTr("Drawing Unit") ];
};

UnitSettings.initPreferences = function(pageWidget, calledByPrefDialog, document, preferencesAction) {
    var measurementCombo = pageWidget.findChild("Measurement");
    UnitSettings.initMeasurementCombo(measurementCombo);

    var unitCombo = pageWidget.findChild("Unit");
    UnitSettings.initUnitCombo(unitCombo);

    // if the global unit / drawing unit changes in the preferences dialog,
    // other plugins are notified to update their widgets accordingly
    // if necessary:
    unitCombo["activated(int)"].connect(function(u) {
        preferencesAction.unitUpdated(u);

        // change dimension format if necessary:
        if (!isNull(document)) {
            var linearFormat = document.getLinearFormat();
            if ((u!==RS.Inch && u!==RS.Foot) &&
                (linearFormat===RS.ArchitecturalStacked || linearFormat===RS.Engineering)) {

                document.setLinearFormat(RS.Decimal);
                DimensionSettings.showLinearFormatWarning();
            }
        }
    });

    var paperUnitCombo = pageWidget.findChild("PaperUnit");
    UnitSettings.initUnitCombo(paperUnitCombo);
    paperUnitCombo["activated(int)"].connect(function(u) {
        preferencesAction.paperUnitUpdated(u);
    });

    if (!isNull(document)) {
        var i = measurementCombo.findData(document.getMeasurement());
        if (i!=-1) {
            measurementCombo.currentIndex = i;
        }
        measurementCombo.setProperty("Loaded", true);

        i = unitCombo.findData(document.getUnit());
        if (i!=-1) {
            unitCombo.currentIndex = i;
        }
        unitCombo.setProperty("Loaded", true);

        i = paperUnitCombo.findData(document.getVariable("UnitSettings/PaperUnit", RS.Millimeter));
        if (i!=-1) {
            paperUnitCombo.currentIndex = i;
        }
        paperUnitCombo.setProperty("Loaded", true);
    }
};

UnitSettings.savePreferences = function(pageWidget, calledByPrefDialog, document, transaction) {
    if (isNull(document)) {
        return;
    }

    var measurementCombo = pageWidget.findChild("Measurement");
    document.setMeasurement(measurementCombo.itemData(measurementCombo.currentIndex), transaction);
    var unitCombo = pageWidget.findChild("Unit");
    document.setUnit(unitCombo.itemData(unitCombo.currentIndex), transaction);
    unitCombo.setProperty("Saved", true);
};

UnitSettings.initUnitCombo = function(unitCombo) {
    // available units in DXF/DWG
    // int values correspond to unit codes from DXF spec
    unitCombo.clear();
    unitCombo.addItem(qsTr("None"), RS.None);
    unitCombo.addItem(qsTr("Inch"), RS.Inch);
    unitCombo.addItem(qsTr("Foot"), RS.Foot);
    unitCombo.addItem(qsTr("Mile"), RS.Mile);
    unitCombo.addItem(qsTr("Millimeter"), RS.Millimeter);
    unitCombo.addItem(qsTr("Centimeter"), RS.Centimeter);
    unitCombo.addItem(qsTr("Meter"), RS.Meter);
    unitCombo.addItem(qsTr("Kilometer"), RS.Kilometer);
    unitCombo.addItem(qsTr("Microinch"), RS.Microinch);
    unitCombo.addItem(qsTr("Mil"), RS.Mil);
    unitCombo.addItem(qsTr("Yard"), RS.Yard);
    unitCombo.addItem(qsTr("Angstrom"), RS.Angstrom);
    unitCombo.addItem(qsTr("Nanometer"), RS.Nanometer);
    unitCombo.addItem(qsTr("Micron"), RS.Micron);
    unitCombo.addItem(qsTr("Decimeter"), RS.Decimeter);
    unitCombo.addItem(qsTr("Decameter"), RS.Decameter);
    unitCombo.addItem(qsTr("Hectometer"), RS.Hectometer);
    unitCombo.addItem(qsTr("Gigameter"), RS.Gigameter);
    unitCombo.addItem(qsTr("Astro"), RS.Astro);
    unitCombo.addItem(qsTr("Lightyear"), RS.Lightyear);
    unitCombo.addItem(qsTr("Parsec"), RS.Parsec);
    //unitCombo.addItem(qsTr("Plu"), RS.Plu);
};

UnitSettings.initMeasurementCombo = function(measurementCombo) {
    measurementCombo.clear();
    measurementCombo.addItem(qsTr("Imperial"), RS.Imperial);
    measurementCombo.addItem(qsTr("Metric"), RS.Metric);
};
