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

PageSettings.prototype = new Object();

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
var pageNames = [ 
    qsTr("Custom"), 
    "ISO A0",
    "ISO A1",
    "ISO A2",
    "ISO A3",
    "ISO A4",
    "ISO A5",
    "ISO A6",
    "ISO A7",
    "ISO A8",
    "ISO A9",
    "ISO A10",
    
    "ISO B0",
    "ISO B1",
    "ISO B2",
    "ISO B3",
    "ISO B4",
    "ISO B5",
    "ISO B6",
    "ISO B7",
    "ISO B8",
    "ISO B9",
    "ISO B10",
      
    "ISO C0",
    "ISO C1",
    "ISO C2",
    "ISO C3",
    "ISO C4",
    "ISO C5",
    "ISO C6",
    "ISO C7",
    "ISO C8",
    "ISO C9",
    "ISO C10",

    "DIN 476 4A0",
    "DIN 476 2A0",

    // JIS:
    "JIS B0",
    "JIS B1",
    "JIS B2",
    "JIS B3",
    "JIS B4",
    "JIS B5",
    "JIS B6",
    "JIS B7",
    "JIS B8",
    "JIS B9",
    "JIS B10",
    "JIS B11",
    "JIS B12",

    // 7.5" x 10"
    "Executive",
    // 8.5" x 14"
    "Legal",
    // 8.5" x 11"
    "ANSI A (Letter)",
    // 11" x 17"
    "ANSI B (Ledger, Tabloid)",
    // 13" x 19"
    "Super B",
    // 17" x 22"
    "ANSI C",
    // 22" x 34"
    "ANSI D",
    // 34" x 44"
    "ANSI E",

    // US Architectural:
    // 9" x 12"
    "Arch A",
    // 12" x 18"
    "Arch B",
    // 18" x 24"
    "Arch C",
    // 24" x 36"
    "Arch D",
    // 36" x 48"
    "Arch E",
    // 30" x 42"
    "Arch E1",
    // 26" x 38"
    "Arch E2",
    // 27" x 39"
    "Arch E3",

    // Others:
    // Folio / Foolscap:
    "F4 (Folio, Foolscap)",
    // U.S. Common 10 Envelope:
    "Common 10 Envelope",
    // DLE Envelope:
    "DLE Envelope"
];

PageSettings.paperSizes = new Array();

for (var i=0; i<pageNames.length; i++) {
    PageSettings.paperSizes.push([pageNames[i], RS.getPageSize(pageNames[i]), RS.getPageSizeId(pageNames[i])]);
}

PageSettings.getPreferencesScope = function() {
    // page settings apply to the current layout block:
    return "block";
};

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

    PageSettings.widgets["LeftMarginUnit"].text = unitSymbol;
    PageSettings.widgets["RightMarginUnit"].text = unitSymbol;
    PageSettings.widgets["TopMarginUnit"].text = unitSymbol;
    PageSettings.widgets["BottomMarginUnit"].text = unitSymbol;

    PageSettings.updatePaperSize(PageSettings.widgets["PaperSizeName"].currentIndex);

    //PageSettings.widgets["PaperWidth"].setValue();
};

PageSettings.getPaperUnit = function(document) {
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

    return paperUnit;
};

PageSettings.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = PageSettings.widgets = getWidgets(pageWidget);
    var paperUnit = PageSettings.getPaperUnit(document);
    PageSettings.updatePaperUnit(paperUnit);

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

    // set glue margins to printer margins
    widgets["btSetToPrinterMargins"].clicked.connect(this, function() {
        var paperUnit = PageSettings.getPaperUnit(document);
        widgets["MarginLeft"].text = Print.getDefaultPrintMarginLeft(document, paperUnit).toFixed(2).replace(/\.?0+$/, "");;
        widgets["MarginRight"].text = Print.getDefaultPrintMarginRight(document, paperUnit).toFixed(2).replace(/\.?0+$/, "");;
        widgets["MarginTop"].text = Print.getDefaultPrintMarginTop(document, paperUnit).toFixed(2).replace(/\.?0+$/, "");;
        widgets["MarginBottom"].text = Print.getDefaultPrintMarginBottom(document, paperUnit).toFixed(2).replace(/\.?0+$/, "");;
    });

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

    paperSizeNameCombo["currentIndexChanged(int)"].connect(PageSettings, PageSettings.updatePaperSize);

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

    // backwards compatibility:
    // margins used to be stored in multi page settings tab:
    if (!isNull(document)) {
        widgets["MarginLeft"].text = PageSettings.getValueAsString(document.getVariable("MultiPageSettings/GlueMarginsLeft", "0", true));
        widgets["MarginRight"].text = PageSettings.getValueAsString(document.getVariable("MultiPageSettings/GlueMarginsRight", "0", true));
        widgets["MarginTop"].text = PageSettings.getValueAsString(document.getVariable("MultiPageSettings/GlueMarginsTop", "0", true));
        widgets["MarginBottom"].text = PageSettings.getValueAsString(document.getVariable("MultiPageSettings/GlueMarginsBottom", "0", true));
    }
    else {
        widgets["MarginLeft"].text = PageSettings.getValueAsString(RSettings.getDoubleValue("MultiPageSettings/GlueMarginsLeft", 0));
        widgets["MarginRight"].text = PageSettings.getValueAsString(RSettings.getDoubleValue("MultiPageSettings/GlueMarginsRight", 0));
        widgets["MarginTop"].text = PageSettings.getValueAsString(RSettings.getDoubleValue("MultiPageSettings/GlueMarginsTop", 0));
        widgets["MarginBottom"].text = PageSettings.getValueAsString(RSettings.getDoubleValue("MultiPageSettings/GlueMarginsBottom", 0));
    }
};

PageSettings.getValueAsString = function(val) {
    if (isString(val)) {
        return val;
    }
    else {
        return val.toFixed(2).replace(/\.?0+$/, "");
    }
};

PageSettings.savePreferences = function(pageWidget, calledByPrefDialog, document) {
    var leMarginLeft = pageWidget.findChild("MarginLeft");
    var leMarginRight = pageWidget.findChild("MarginRight");
    var leMarginTop = pageWidget.findChild("MarginTop");
    var leMarginBottom = pageWidget.findChild("MarginBottom");

    if (!isNull(document)) {
        document.setVariable("MultiPageSettings/GlueMarginsLeft", leMarginLeft.text);
        document.setVariable("MultiPageSettings/GlueMarginsRight", leMarginRight.text);
        document.setVariable("MultiPageSettings/GlueMarginsTop", leMarginTop.text);
        document.setVariable("MultiPageSettings/GlueMarginsBottom", leMarginBottom.text);
    }
    else {
        RSettings.setValue("MultiPageSettings/GlueMarginsLeft", leMarginLeft.text);
        RSettings.setValue("MultiPageSettings/GlueMarginsRight", leMarginRight.text);
        RSettings.setValue("MultiPageSettings/GlueMarginsTop", leMarginTop.text);
        RSettings.setValue("MultiPageSettings/GlueMarginsBottom", leMarginBottom.text);
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
