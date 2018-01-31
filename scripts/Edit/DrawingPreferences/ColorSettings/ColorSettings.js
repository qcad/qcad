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

function ColorSettings() {
}

ColorSettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Printing - Colors") ];
    }
    return [ qsTr("Printing"), qsTr("Colors") ];
};

ColorSettings.getPreferencesScope = function() {
    return "block";
};

ColorSettings.applyPreferences = function(doc, mdiChild) {
    if (isNull(doc) || isNull(mdiChild)) {
        return;
    }

    var di = mdiChild.getDocumentInterface();
    var scenes = di.getGraphicsScenes();

    for (var si = 0; si<scenes.length; ++si) {
        var scene = scenes[si];
        var views = scene.getGraphicsViews();
        for (var vi = 0; vi<views.length; ++vi) {
            var view = views[vi];
            if (!view.isPrintPreview()) {
                // setting bg color to invalid will automatically update it:
                view.setBackgroundColor(new QColor());
            }
            view.regenerate(false);
        }
    }
};
