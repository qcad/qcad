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

function LinetypeSettings() {
}

LinetypeSettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Linetype") ];
    }
    return [ qsTr("General"), qsTr("Linetype") ];
};

LinetypeSettings.initPreferences = function(pageWidget, calledByPrefDialog, document, preferencesAction) {
    if (isNull(document)) {
        return;
    }

    var linetypeScaleEdit = pageWidget.findChild("Scale");
    linetypeScaleEdit.setValue(document.getLinetypeScale());
    linetypeScaleEdit.setProperty("Loaded", true);

    if (hasPlugin("DWG")) {
        var psltscale = pageWidget.findChild("PSLTSCALE");
        psltscale.checked = !document.getKnownVariable(RS.PSLTSCALE, false);
        psltscale.setProperty("Loaded", true);
    }
};

LinetypeSettings.savePreferences = function(pageWidget, calledByPrefDialog, document, transaction) {
    if (isNull(document)) {
        return;
    }

    var linetypeScaleEdit = pageWidget.findChild("Scale");
    document.setLinetypeScale(linetypeScaleEdit.getValue(), transaction);
    linetypeScaleEdit.setProperty("Saved", true);

    if (hasPlugin("DWG")) {
        var psltscale = pageWidget.findChild("PSLTSCALE");
        document.setKnownVariable(RS.PSLTSCALE, !psltscale.checked);
        psltscale.setProperty("Saved", true);
    }
};
