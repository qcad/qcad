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

function TextPreferences(guiAction) {
    EAction.call(this, guiAction);
}

TextPreferences.prototype = new EAction();

TextPreferences.getPreferencesCategory = function() {
    return [qsTr("Draw"), qsTr("Text")];
};

TextPreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var cbUseReducedList = pageWidget.findChild("UseReducedFontList");
    var lReducedList = pageWidget.findChild("ReducedFontList");
    var bCheckAll = pageWidget.findChild("CheckAll");
    var bUncheckAll = pageWidget.findChild("UncheckAll");

    lReducedList.enabled = cbUseReducedList.checked;

    // add CAD fonts to list:
    var cadList = RFontList.getNames();
    lReducedList.addItems(cadList);

    // add system fonts to list:
    var fontDb = new RFontDatabase();
    var families = fontDb.families();
    lReducedList.addItems(families);

    var list = RSettings.getValue("Text/ReducedFontList", []);
    if (isNull(list)) {
        list = [];
    }

    for (var row = 0; row<lReducedList.count; row++) {
        var item = lReducedList.item(row);
        var flags = new Qt.ItemFlags(item.flags() | Qt.ItemIsUserCheckable);

        // always check 'standard' and make it immutable:
        if (item.text().toLowerCase()==="standard") {
            item.setCheckState(Qt.Checked);
            flags = new Qt.ItemFlags(item.flags() & ~(Qt.ItemIsUserCheckable | Qt.ItemIsEnabled));
        }
        else if (list.contains(item.text())) {
            item.setCheckState(Qt.Checked);
        }
        else {
            item.setCheckState(Qt.Unchecked);
        }
        item.setFlags(flags);
    }

    bCheckAll.clicked.connect(function() {
        for (var row = 0; row<lReducedList.count; row++) {
            var item = lReducedList.item(row);
            item.setCheckState(Qt.Checked);
        }
    });
    bUncheckAll.clicked.connect(function() {
        for (var row = 0; row<lReducedList.count; row++) {
            var item = lReducedList.item(row);
            if (item.text().toLowerCase()==="standard") {
                continue;
            }
            item.setCheckState(Qt.Unchecked);
        }
    });

    lReducedList.setProperty("Loaded", true);
};

TextPreferences.savePreferences = function(pageWidget, calledByPrefDialog, document) {
    var cbUseReducedList = pageWidget.findChild("UseReducedFontList");
    var lReducedList = pageWidget.findChild("ReducedFontList");

    var list = [];

    if (cbUseReducedList.checked) {
        for (var row = 0; row<lReducedList.count; row++) {
            var item = lReducedList.item(row);
            if (item.checkState()===Qt.Checked) {
                list.push(item.text());
            }
        }
    }

    RSettings.setValue("Text/ReducedFontList", list);
    lReducedList.setProperty("Saved", true);
};
