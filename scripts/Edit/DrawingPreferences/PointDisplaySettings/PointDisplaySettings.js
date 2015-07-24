/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

function PointDisplaySettings() {
}

PointDisplaySettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Point Display") ];
    }
    return [ qsTr("General"), qsTr("Point Display") ];
};

PointDisplaySettings.initPreferences = function(pageWidget, calledByPrefDialog, document, preferencesAction) {
    var widgets = getWidgets(pageWidget);

    var modeEdit = pageWidget.findChild("Mode");
    if (!isNull(document)) {
        modeEdit.setValue(document.getKnownVariable(RS.PDMODE, 0));
        var w = pageWidget.findChild("Button" + modeEdit.text);
        w.checked = true;
    }

    var sizeEdit = pageWidget.findChild("Size");
    if (!isNull(document)) {
        sizeEdit.setValue(document.getKnownVariable(RS.PDSIZE, 0));
    }

    widgets["Button0"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(0);
    });
    widgets["Button1"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(1);
    });
    widgets["Button2"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(2);
    });
    widgets["Button3"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(3);
    });
    widgets["Button4"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(4);
    });
    widgets["Button32"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(32);
    });
    widgets["Button33"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(33);
    });
    widgets["Button34"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(34);
    });
    widgets["Button35"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(35);
    });
    widgets["Button36"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(36);
    });
    widgets["Button64"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(64);
    });
    widgets["Button65"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(65);
    });
    widgets["Button66"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(66);
    });
    widgets["Button67"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(67);
    });
    widgets["Button68"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(68);
    });
    widgets["Button96"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(96);
    });
    widgets["Button97"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(97);
    });
    widgets["Button98"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(98);
    });
    widgets["Button99"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(99);
    });
    widgets["Button100"]["clicked"].connect(function() {
        var modeEdit = pageWidget.findChild("Mode");
        modeEdit.setValue(100);
    });

};

PointDisplaySettings.savePreferences = function(pageWidget, calledByPrefDialog, document, transaction) {
    if (isNull(document)) {
        return;
    }

    var modeEdit = pageWidget.findChild("Mode");
    document.setKnownVariable(RS.PDMODE, modeEdit.getValue(), transaction);

    var sizeEdit = pageWidget.findChild("Size");
    document.setKnownVariable(RS.PDSIZE, sizeEdit.getValue(), transaction);
};
