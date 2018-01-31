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
    var pdmode = undefined;
    if (!isNull(document)) {
        pdmode = document.getKnownVariable(RS.PDMODE, 0)
    }
    else {
        pdmode = RSettings.getIntValue("PointDisplaySettings/Mode", 0);
    }

    if (!isNull(pdmode)) {
        modeEdit.text = pdmode.toString();
        var w = pageWidget.findChild("Button" + pdmode);
        if (!isNull(w)) {
            w.checked = true;
        }
    }

    var sizeEdit = pageWidget.findChild("Size");
    var pdsize = undefined;
    if (!isNull(pdsize)) {
        if (!isNull(document)) {
            pdsize = document.getKnownVariable(RS.PDSIZE, 0);
        }
        else {
            pdsize = RSettings.getIntValue("PointDisplaySettings/Size", 0);
        }
        sizeEdit.text = pdsize.toString();
    }

    var values = [ 0, 1, 2, 3, 4,
                  32,33,34,35,36,
                  64,65,66,67,68,
                  96,97,98,99,100];
    for (var i=0; i<values.length; i++) {
        var f = function() { modeEdit.text = values[arguments.callee.i].toString(); };
        f.i = i;
        widgets["Button" + values[i]]["clicked"].connect(f);
    }
};

PointDisplaySettings.savePreferences = function(pageWidget, calledByPrefDialog, document, transaction) {
    var modeEdit = pageWidget.findChild("Mode");
    var sizeEdit = pageWidget.findChild("Size");

    if (!isNull(document)) {
        document.setKnownVariable(RS.PDMODE, parseInt(modeEdit.text), transaction);
        document.setKnownVariable(RS.PDSIZE, parseInt(sizeEdit.text), transaction);
    }
};
