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

include("scripts/EAction.js");
include("scripts/sprintf.js");
include("scripts/File/Print/Print.js");

function PageSettings() {
}

PageSettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Printing - Page") ];
    }
    return [ qsTr("Printing"), qsTr("Page") ];
};

/**
 * Available paper sizes. Some are defined by Qt, the rest are custom
 * paper sizes.
 */
PageSettings.paperSizes = new Array(
        [ qsTr("Custom"), new QSizeF(), QPrinter.Custom ],
        
        [ "ISO A0",  new QSizeF(841, 1189), QPrinter.A0 ],
        [ "ISO A1",  new QSizeF(594,  841), QPrinter.A1 ],
        [ "ISO A2",  new QSizeF(420,  594), QPrinter.A2 ],
        [ "ISO A3",  new QSizeF(297,  420), QPrinter.A3 ],
        [ "ISO A4",  new QSizeF(210,  297), QPrinter.A4 ],
        [ "ISO A5",  new QSizeF(148,  210), QPrinter.A5 ],
        [ "ISO A6",  new QSizeF(105,  148), QPrinter.A6 ],
        [ "ISO A7",  new QSizeF( 74,  105), QPrinter.A7 ],
        [ "ISO A8",  new QSizeF( 52,   74), QPrinter.A8 ],
        [ "ISO A9",  new QSizeF( 37,   52), QPrinter.A9 ],
        [ "ISO A10", new QSizeF( 26,   37), QPrinter.Custom ],
        
        [ "ISO B0",  new QSizeF(1000, 1414), QPrinter.B0 ],
        [ "ISO B1",  new QSizeF( 707, 1000), QPrinter.B1 ],
        [ "ISO B2",  new QSizeF( 500,  707), QPrinter.B2 ],
        [ "ISO B3",  new QSizeF( 353,  500), QPrinter.B3 ],
        [ "ISO B4",  new QSizeF( 250,  353), QPrinter.B4 ],
        [ "ISO B5",  new QSizeF( 176,  250), QPrinter.B5 ],
        [ "ISO B6",  new QSizeF( 125,  176), QPrinter.B6 ],
        [ "ISO B7",  new QSizeF(  88,  125), QPrinter.B7 ],
        [ "ISO B8",  new QSizeF(  62,   88), QPrinter.B8 ],
        [ "ISO B9",  new QSizeF(  44,   62), QPrinter.B9 ],
        [ "ISO B10", new QSizeF(  31,   44), QPrinter.B10 ],
          
        [ "ISO C0",  new QSizeF( 917, 1297), QPrinter.Custom ],
        [ "ISO C1",  new QSizeF( 648,  917), QPrinter.Custom ],
        [ "ISO C2",  new QSizeF( 458,  648), QPrinter.Custom ],
        [ "ISO C3",  new QSizeF( 324,  458), QPrinter.Custom ],
        [ "ISO C4",  new QSizeF( 229,  324), QPrinter.Custom ],
        [ "ISO C5",  new QSizeF( 162,  229), QPrinter.Custom ],
        [ "ISO C6",  new QSizeF( 114,  162), QPrinter.Custom ],
        [ "ISO C7",  new QSizeF(  81,  114), QPrinter.Custom ],
        [ "ISO C8",  new QSizeF(  57,   81), QPrinter.Custom ],
        [ "ISO C9",  new QSizeF(  40,   57), QPrinter.Custom ],
        [ "ISO C10", new QSizeF(  28,   40), QPrinter.Custom ],

        [ "DIN 476 4A0", new QSizeF(1682, 2378), QPrinter.Custom ],
        [ "DIN 476 2A0", new QSizeF(1189, 1682), QPrinter.Custom ],

        // JIS:
        [ "JIS B0",  new QSizeF(1030, 1456), QPrinter.Custom ],
        [ "JIS B1",  new QSizeF( 728, 1030), QPrinter.Custom ],
        [ "JIS B2",  new QSizeF( 515,  728), QPrinter.Custom ],
        [ "JIS B3",  new QSizeF( 364,  515), QPrinter.Custom ],
        [ "JIS B4",  new QSizeF( 257,  364), QPrinter.Custom ],
        [ "JIS B5",  new QSizeF( 182,  257), QPrinter.Custom ],
        [ "JIS B6",  new QSizeF( 128,  182), QPrinter.Custom ],
        [ "JIS B7",  new QSizeF(  91,  128), QPrinter.Custom ],
        [ "JIS B8",  new QSizeF(  64,   91), QPrinter.Custom ],
        [ "JIS B9",  new QSizeF(  45,   64), QPrinter.Custom ],
        [ "JIS B10", new QSizeF(  32,   45), QPrinter.Custom ],
        [ "JIS B11", new QSizeF(  22,   32), QPrinter.Custom ],
        [ "JIS B12", new QSizeF(  16,   22), QPrinter.Custom ],

        // 7.5" x 10"
        [ "Executive",  new QSizeF(190.5, 254), QPrinter.Executive ],
        // 8.5" x 14"
        [ "Legal",      new QSizeF(215.9, 355.6), QPrinter.Legal ],
        // 8.5" x 11"
        [ "ANSI A (Letter)", new QSizeF(215.9, 279.4), QPrinter.Letter ],
        // 11" x 17"
        [ "ANSI B (Ledger, Tabloid)", new QSizeF(279.4, 431.8), QPrinter.Tabloid ],
        // 13" x 19"
        [ "Super B",    new QSizeF(330.2, 482.6), QPrinter.Custom ],
        // 17" x 22"
        [ "ANSI C",     new QSizeF(431.8, 558.8), QPrinter.Custom ],
        // 22" x 34"
        [ "ANSI D",     new QSizeF(558.8, 863.6), QPrinter.Custom ],
        // 34" x 44"
        [ "ANSI E",     new QSizeF(863.6, 1117.6), QPrinter.Custom ],

        // US Architectural:
        // 9" x 12"
        [ "Arch A",     new QSizeF(228.6, 304.8), QPrinter.Custom ],
        // 12" x 18"
        [ "Arch B",     new QSizeF(304.8, 457.2), QPrinter.Custom ],
        // 18" x 24"
        [ "Arch C",     new QSizeF(457.2, 609.6), QPrinter.Custom ],
        // 24" x 36"
        [ "Arch D",     new QSizeF(609.6, 914.4), QPrinter.Custom ],
        // 36" x 48"
        [ "Arch E",     new QSizeF(914.4, 1219.2), QPrinter.Custom ],
        // 30" x 42"
        [ "Arch E1",    new QSizeF(762, 1066.8), QPrinter.Custom ],
        // 26" x 38"
        [ "Arch E2",    new QSizeF(660.4, 965.2), QPrinter.Custom ],
        // 27" x 39"
        [ "Arch E3",    new QSizeF(685.8, 990.6), QPrinter.Custom ],

        // Others:
        // Folio / Foolscap:
        [ "F4 (Folio, Foolscap)", new QSizeF( 210,   330), QPrinter.Folio ],
        // U.S. Common 10 Envelope:
        [ "Common 10 Envelope", new QSizeF(105, 241), QPrinter.Comm10E ],
        // DLE Envelope:
        [ "DLE Envelope", new QSizeF( 110,   220), QPrinter.DLE ]
);

/**
 * Called when the user changed the drawing / global paper unit in another
 * preference page.
 */
PageSettings.updatePaperUnit = function(unit) {
    PageSettings.paperUnit = unit;
    var unitSymbol = "";
    if (isString(unit)) {
        unit = parseInt(unit, 10);
    }

    unitSymbol = RUnit.unitToSymbol(unit);

    PageSettings.widgets["HeightUnit"].text = unitSymbol;
    PageSettings.widgets["WidthUnit"].text = unitSymbol;
    PageSettings.widgets["OffsetXUnit"].text = unitSymbol;
    PageSettings.widgets["OffsetYUnit"].text = unitSymbol;

    PageSettings.updatePaperSize(PageSettings.widgets["PaperSizeName"].currentIndex);

    //PageSettings.widgets["PaperWidth"].setValue();
};


PageSettings.getPreferencesScope = function() {
    return "block";
};

PageSettings.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = PageSettings.widgets = getWidgets(pageWidget);

    var unit;

    // fill scale combo with default drawing scales:
    if (!isNull(document)) {
        unit = document.getUnit();
    }
    else {
        // no document: use default unit:
        unit = RSettings.getIntValue("UnitSettings/Unit", RS.Millimeter);
    }

    widgets["Scale"].clear();
    var scales = EAction.getScales(unit);
    for (i = 0; i < scales.length; ++i) {
        widgets["Scale"].addItem(scales[i]);
    }

    // do not automatically restore paper size name
    //widgets["PaperSizeName"].setProperty("Loaded", true);

    // update unit symbols beside paper size and offset inputs:
    var paperUnit;
    if (!isNull(document)) {
        paperUnit = Print.getPaperUnit(document);
    }
    else {
        // no document: use default paper unit:
        paperUnit = Print.getDefaultPaperUnit();
    }

    // paper unit might have been changed by user:
    var unitCombo = objectFromPath("MainWindow::PaperUnit");
    if (isComboBox(unitCombo)) {
        paperUnit = unitCombo.itemData(unitCombo.currentIndex);
    }

    PageSettings.updatePaperUnit(paperUnit);
};

PageSettings.postInitPreferences = function(pageWidget, calledByPrefDialog, document) {
    var i;
    
    PageSettings.document = document;
    var widgets = PageSettings.widgets = getWidgets(pageWidget);
    var paperUnit = Print.getPaperUnit(document);

    // fill paper combo with paper sizes
    var paperSizeNameCombo = widgets["PaperSizeName"];
    //var paperUnitCombo = widgets["PaperUnit"];
    PageSettings.initPaperSizeNameCombo(paperSizeNameCombo);

    var paperWidth = RUnit.convert(widgets["PaperWidth"].getValue(), paperUnit, RS.Millimeter);
    var paperHeight = RUnit.convert(widgets["PaperHeight"].getValue(), paperUnit, RS.Millimeter);
    var paperSizeName = Print.getPaperSizeNameFromSize(new QSizeF(paperWidth, paperHeight));
    var idx = widgets["PaperSizeName"].findText(paperSizeName);
    if (idx===-1) {
        widgets["PaperSizeName"].currentIndex = 0;
    }
    else {
        widgets["PaperSizeName"].currentIndex = idx;
    }

    paperSizeNameCombo["currentIndexChanged(int)"].connect(PageSettings, "updatePaperSize");

    PageSettings.updatePaperSize(widgets["PaperSizeName"].currentIndex);

    // fill unit combo with available units
    // (label is unit name and user data is RS.Unit enum):
//    paperUnitCombo.clear();
//    for (i = 0; i < PageSettings.paperUnits.length; ++i) {
//        var unit = PageSettings.paperUnits[i];
//        paperUnitCombo.addItem(undefined, unit[0], unit[1]);
//    }
//    paperUnitCombo["currentIndexChanged(int)"].connect(PageSettings, function(index) {
//        PageSettings.update(index, widgets);
//    });

//    var unitEnum;
//    if (!isNull(document)) {
//        unitEnum = document.getUnit();
//    }
//    else {
//        unitEnum = RSettings.getIntValue("PageSettings/PaperUnit", RS.Millimeter);
//    }

//    var unitIndex = paperUnitCombo.findData(unitEnum);
//    if (unitIndex==-1) {
//        unitIndex = 0;
//    }

    //paperUnitCombo.currentIndex = unitIndex;

//    // fill scale combo with default drawing scales:
//    if (!isNull(document)) {
//        // TODO: no document? use default unit!
//        widgets["Scale"].clear();
//        var scales = EAction.getScales(document.getUnit());
//        for (i = 0; i < scales.length; ++i) {
//            widgets["Scale"].addItem(scales[i]);
//        }
//    }
    
    widgets["ZeroPoint"].clicked.connect(PageSettings, function() {
        widgets["OffsetX"].setValue(0.0);
        widgets["OffsetY"].setValue(0.0);
    });

    //paperUnitCombo.currentIndex = paperUnitIndex;
    
    var paperName;
    var paperUnitIndex;

    // set default paper size:
    if (!isNull(document)) {
        paperName = Print.getPaperSizeName(document);
    }
    else {
        //debugger;
        //paperName = RSettings.getStringValue("PageSettings/PaperSizeName", "ISO A4");
        paperName = Print.getDefaultPaperSizeName(document);
    }

    var index = paperSizeNameCombo.findText(paperName);
    if (index!=-1) {
        paperSizeNameCombo.blockSignals(true);
        paperSizeNameCombo.currentIndex = index;
        paperSizeNameCombo.blockSignals(false);
    }
};

/**
 * Called when paper name changed. Enables width/height edits if
 * paper name is 'Custom'.
 */
PageSettings.updatePaperSize = function(index) {
    if (index==-1) {
        return;
    }

    var document = PageSettings.document;
    var widgets = PageSettings.widgets;
    //var paperUnit = Print.getPaperUnit(document);

    // get paper size in mm:
    var w, h;
    if (index === 0) {  // paper size is custom
        // custom size, enable line edits:
        widgets["PaperWidth"].enabled = true;
        widgets["PaperHeight"].enabled = true;

        if (!isNull(document)) {
            w = Print.getPaperWidth(document);
            h = Print.getPaperHeight(document);
        }
        else {
            w = RSettings.getDoubleValue("PageSettings/PaperWidth", 210);
            h = RSettings.getDoubleValue("PageSettings/PaperHeight", 297);
        }
    } else {
        widgets["PaperWidth"].enabled = false;
        widgets["PaperHeight"].enabled = false;
        var size = PageSettings.paperSizes[index][1];
        w = RUnit.convert(size.width(), RS.Millimeter, PageSettings.paperUnit);
        h = RUnit.convert(size.height(), RS.Millimeter, PageSettings.paperUnit);
    }

    // convert paper size from mm to paper unit:
    widgets["PaperWidth"].text = sprintf("%.3f", w);
    widgets["PaperHeight"].text = sprintf("%.3f", h);

    // enum is not stored automatically:
    //document.setVariable("PageSettings/PaperSizeEnum", paperSizeNameCombo.itemData(index, Qt.UserRole));

    //PageSettings.update(paperUnitCombo.currentIndex, widgets);
};

/**
 * Initializes the combo box with paper size choices.
 */
PageSettings.initPaperSizeNameCombo = function(paperSizeNameCombo) {
    paperSizeNameCombo.clear();
    for (var i = 0; i < PageSettings.paperSizes.length; ++i) {
        // paper[0]: name
        // paper[1]: QSizeF
        // paper[2]: QPrinter::PaperSize
        var paper = PageSettings.paperSizes[i];
        paperSizeNameCombo.addItem(paper[0], paper[2]);
        paperSizeNameCombo.setItemData(i, paper[1], Qt.UserRole + 1);
    }
};

/*
PageSettings.update = function(paperUnitIndex, widgets) {
    widgets["HeightUnit"].text = PageSettings.paperUnits[paperUnitIndex][0];
    var unit = PageSettings.paperUnits[paperUnitIndex][1];
    var psIndex = widgets["PaperSizeName"].currentIndex;
    
    widgets["PaperWidth"].setDefaultUnit(unit);
    widgets["PaperHeight"].setDefaultUnit(unit);
    
    if (psIndex === 0) {
        // custom paper size, don't convert
        return;
    } else {
        size = PageSettings.paperSizes[psIndex][1];
    }
    var pw = RUnit.convert(size.width(), RS.Millimeter, unit);
    widgets["PaperWidth"].text = pw.toFixed(2);
    var ph = RUnit.convert(size.height(), RS.Millimeter, unit);
    widgets["PaperHeight"].text = ph.toFixed(2);
};
*/

//PageSettings.savePreferences = function(pageWidget, calledByPrefDialog, document) {
    // page size enum is not stored automatically:
    //var paperSizeNameCombo = pageWidget.findChild("PaperSizeName");

    //var paperSizeEnum = paperSizeNameCombo.itemData(paperSizeNameCombo.currentIndex, Qt.UserRole);
    //debugger;

//    if (isNull(document)) {
//        RSettings.setValue("PageSettings/PaperSizeEnum", paperSizeEnum);
//    }
//    else {
//        document.setVariable("PageSettings/PaperSizeEnum", paperSizeEnum);
//    }
//}
