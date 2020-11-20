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

function GraphicsViewPreferences() {
}

GraphicsViewPreferences.getPreferencesCategory = function() {
    return [qsTr("Graphics View"), qsTr("Appearance")];
};

GraphicsViewPreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);
    // remove item "Default":
    widgets["ZeroWeightWeight"].removeItem(0);
    // remove item "0.00":
    widgets["ZeroWeightWeight"].removeItem(0);

    var cbCapStyle = widgets["PenCapStyle"];
    cbCapStyle.visible = false;
    var lCapStyle = widgets["PenCapStyle_Label"];
    lCapStyle.visible = false;
//    cbCapStyle.addItem(qsTr("Round Cap"), Qt.RoundCap.valueOf());
//    cbCapStyle.addItem(qsTr("Flat Cap"), Qt.FlatCap.valueOf());
//    cbCapStyle.addItem(qsTr("Square Cap"), Qt.SquareCap.valueOf());

    widgets["Threads"].setItemText(0, widgets["Threads"].itemText(0) + " (" + Math.min(RS.getIdealThreadCount(), 6) + ")");

    widgets["DefaultLineweight"].setLineweight(RLineweight.Weight000);
};

GraphicsViewPreferences.applyPreferences = function(doc, mdiChild) {
    if (isNull(doc) || isNull(mdiChild)) {
        return;
    }

    var numThreads = RSettings.getIntValue("GraphicsView/Threads", Math.min(RS.getIdealThreadCount(), 6));
    //EAction.handleUserMessage(qsTr("Threads:") + " " + numThreads);

    var di = mdiChild.getDocumentInterface();
    var scenes = di.getGraphicsScenes();

    for (var si = 0; si<scenes.length; ++si) {
        var scene = scenes[si];
        var views = scene.getGraphicsViews();
        for (var vi = 0; vi<views.length; ++vi) {
            var view = views[vi];
            // setting bg color to invalid will automatically update it:
            if (!view.isPrintPreview()) {
                view.setBackgroundColor(new QColor());
            }

            view.setNumThreads(numThreads);

            view.regenerate(false);
        }
    }
};

