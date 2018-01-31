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

include("../../EAction.js");
include("../../WidgetFactory.js");

// TODO: use QLocale::decimalPoint

function InputPreferences(guiAction) {
    EAction.call(this, guiAction);
}

InputPreferences.prototype = new EAction();

InputPreferences.getPreferencesCategory = function() {
    return [qsTr("General"), qsTr("Coordinate Format")];
};

InputPreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var combo;
    
    InputPreferences.pageWidget = pageWidget;

    combo = pageWidget.findChild("DecimalPoint");
    var decimalPointCombo = combo;
    InputPreferences.updateDecimalPointCombo(combo);
    combo['currentIndexChanged(int)'].connect(InputPreferences, "correctBasedOnDecimalPoint");
    combo['currentIndexChanged(int)'].connect(InputPreferences, "updatePreview");

    combo = pageWidget.findChild("CartesianCoordinateSeparator");
    combo.addItem(qsTr("Comma") + " ',' " + qsTr("(Default)"), ",");
    combo.addItem(qsTr("Semicolon") + " ';'", ";");
    combo['currentIndexChanged(int)'].connect(InputPreferences, "correctBasedOnSeparator");
    combo['currentIndexChanged(int)'].connect(InputPreferences, "updatePreview");

    combo = pageWidget.findChild("PolarCoordinateSeparator");
    combo.addItem(qsTr("Less Than") + " '<' " + qsTr("(Default)"), "<");
    combo['currentIndexChanged(int)'].connect(InputPreferences, "updatePreview");

    combo = pageWidget.findChild("RelativeCoordinatePrefix");
    var at = String.fromCharCode(64);  // @ (doxygen can't cope with an @ here)
    combo.addItem(qsTr("At") + " '" + at + "' " + qsTr("(Default)"), at);
    combo.addItem(qsTr("Percentage") + " '%'", "%");
    combo.addItem(qsTr("Dollar") + " '$'", "$");
    combo.addItem(qsTr("Hash") + " '#'", "#");
    combo['currentIndexChanged(int)'].connect(InputPreferences, "updatePreview");

    var locale = QLocale.system();
    var dot = String.fromCharCode(locale.decimalPoint());
    decimalPointCombo.currentIndex = decimalPointCombo.findData(dot);

    InputPreferences.updatePreview();
};

InputPreferences.updateDecimalPointCombo = function(combo) {
    combo.clear();
    combo.addItem(qsTr("Dot") + " '.' " +  qsTr("(Default)"), ".");
    combo.addItem(qsTr("Comma") + " ','", ",");
};

InputPreferences.correctBasedOnDecimalPoint = function() {
    var combo;
    
    combo = InputPreferences.pageWidget.findChild("DecimalPoint");
    var dot = combo.itemData(combo.currentIndex);

    combo = InputPreferences.pageWidget.findChild("CartesianCoordinateSeparator");
    var cartSep = combo.itemData(combo.currentIndex);

    if (cartSep==dot) {
        for (var i=0; i<combo.count; ++i) {
            if (i!=combo.currentIndex) {
                combo.currentIndex = i;
                break;
            }
        }
    }
};

InputPreferences.correctBasedOnSeparator = function() {
    var combo;
    
    combo = InputPreferences.pageWidget.findChild("CartesianCoordinateSeparator");
    var cartSep = combo.itemData(combo.currentIndex);

    combo = InputPreferences.pageWidget.findChild("DecimalPoint");
    var dot = combo.itemData(combo.currentIndex);

    if (cartSep==dot) {
        for (var i=0; i<combo.count; ++i) {
            if (i!=combo.currentIndex) {
                combo.currentIndex = i;
                break;
            }
        }
    }
};

InputPreferences.updatePreview = function() {
    var combo, label;
    
    combo = InputPreferences.pageWidget.findChild("DecimalPoint");
    var dot = combo.itemData(combo.currentIndex);

    combo = InputPreferences.pageWidget.findChild("CartesianCoordinateSeparator");
    var cartSep = combo.itemData(combo.currentIndex);

    combo = InputPreferences.pageWidget.findChild("PolarCoordinateSeparator");
    var polarSep = combo.itemData(combo.currentIndex);

    combo = InputPreferences.pageWidget.findChild("RelativeCoordinatePrefix");
    var relPre = combo.itemData(combo.currentIndex);

    label = InputPreferences.pageWidget.findChild("AbsCart");
    label.text = "10" + dot + "5" + cartSep + "7" + dot + "25";

    label = InputPreferences.pageWidget.findChild("AbsPolar");
    label.text = "12" + dot + "125" + polarSep + "30" + dot + "0";

    label = InputPreferences.pageWidget.findChild("RelCart");
    label.text = relPre + "10" + dot + "5" + cartSep + "7" + dot + "25";

    label = InputPreferences.pageWidget.findChild("RelPolar");
    label.text = relPre + "12" + dot + "125" + polarSep + "30" + dot + "0";
};

InputPreferences.applyPreferences = function(doc) {
};
