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

include("scripts/WidgetFactory.js");

function PenToolBar() {
}

PenToolBar.init = function(basePath) {
    var penToolBar = EAction.getToolBar(qsTr("Pen"), "Pen");
    var w = WidgetFactory.createWidget(includeBasePath, "PenToolBar.ui", RMainWindowQt.getMainWindow());
    WidgetFactory.moveChildren(w, penToolBar, w.objectName);
    w.destroy();
    //penToolBar.addWidget(w);
    penToolBar.visible = false;

    var appWin = EAction.getMainWindow();
    var adapter = new RPenListenerAdapter();
    appWin.addPenListener(adapter);
    adapter.penUpdated.connect(
        function(di) {
            if (isNull(di)) {
                return;
            }
            var colorCombo = penToolBar.findChild("Color");
            colorCombo.blockSignals(true);
            colorCombo.setColor(di.getCurrentColor());
            colorCombo.blockSignals(false);

            var linetypeCombo = penToolBar.findChild("Linetype");
            linetypeCombo.blockSignals(true);
            linetypeCombo.init(di.getDocument());
            linetypeCombo.setLinetypePattern(di.getCurrentLinetypePattern());
            linetypeCombo.blockSignals(false);

            var lineweightCombo = penToolBar.findChild("Lineweight");
            lineweightCombo.blockSignals(true);
            lineweightCombo.setLineweight(di.getCurrentLineweight());
            lineweightCombo.blockSignals(false);
        }
    );

    adapter.penCleared.connect(
        function(documentInterface) {
            // TODO
            qDebug("clearPen");
        }
    );

    var colorCombo = penToolBar.findChild("Color");
    colorCombo.valueChanged.connect(
        function(color) {
            EAction.getDocumentInterface().setCurrentColor(color);
        }
    );

    var linetypeCombo = penToolBar.findChild("Linetype");
    linetypeCombo.minimumWidth = 250;
    linetypeCombo.valueChanged.connect(
        function(p) {
            EAction.getDocumentInterface().setCurrentLinetypePattern(p);
        }
    );

    var lineweightCombo = penToolBar.findChild("Lineweight");
    lineweightCombo.valueChanged.connect(
        function(lw) {
            EAction.getDocumentInterface().setCurrentLineweight(lw);
        }
    );

    var resetButton = penToolBar.findChild("Reset");
    if (!isNull(resetButton)) {
        resetButton.toolTip = qsTr("Reset to Defaults");
        resetButton.clicked.connect(
            function() {
                colorCombo.setColor(new RColor(RColor.ByLayer));
                linetypeCombo.setLinetypePattern("BYLAYER");
                lineweightCombo.setLineweight(RLineweight.WeightByLayer);
            }
        );
    }
};
