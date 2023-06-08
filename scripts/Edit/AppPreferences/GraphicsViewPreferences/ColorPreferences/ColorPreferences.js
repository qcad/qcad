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

function ColorPreferences() {
}

ColorPreferences.getPreferencesCategory = function() {
    return [qsTr("Graphics View"), qsTr("Colors")];
};

ColorPreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var defaults = [
                [ "BackgroundColor", "#000000" ],
                [ "CrosshairColor", "#80ffc200" ],
                [ "CrosshairColorInactive", "#806c4f00" ],
                [ "OriginColor", "#ff0000" ],
                [ "RelativeZeroColor", "#a22424" ],
                [ "GridColor", "#c0c0c0c0" ],
                [ "MetaGridColor", "#40c0c0c0" ],
                [ "SelectionColor", "#80d15a5a" ],
                [ "SecondarySelectionColor", "#ffffff" ],
                [ "ReferencePointColor", "#0000ac" ],
                [ "SecondaryReferencePointColor", "#0080ac" ],
                [ "TertiaryReferencePointColor", "#0040ac" ],
                [ "StartReferencePointColor", "#c00020" ],
                [ "EndReferencePointColor", "#0000ac" ],
                [ "SelectionBoxColor", "#800000" ],
                [ "SelectionBoxBackgroundColor", "#1e0000ff" ],
                [ "SelectionBoxBackgroundCrossColor", "#1e00ff00" ],
                [ "TextLabelColor", "#f9c61f" ],
                [ "MeasurementToolsColor", "#9bdc70" ],
                [ "AuxShapeColor", "#7976c5" ],
                [ "ZoomBoxColor", "#7f0000" ],
    ];

    for (var i=0; i<defaults.length; i++) {
        var def = defaults[i];

        var cb = pageWidget.findChild(def[0]);
        cb.setColor(new RColor(def[1]));
    }
};

/**
 * \todo maybe we can 'invalidate' RSettings to force that all values are
 * read again from the ini file instead.
 */
ColorPreferences.applyPreferences = function(doc, mdiChild) {
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
