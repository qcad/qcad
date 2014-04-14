/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

include("../../../WidgetFactory.js");

function PointMarkerList(guiAction) {
    Widgets.call(this, guiAction);
}

PointMarkerList.prototype = new Widgets();

/**
 * Shows / hides the layer list.
 */
PointMarkerList.prototype.beginEvent = function() {
    Widgets.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PointMarkerDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
    }
};

PointMarkerList.prototype.finishEvent = function() {
    Widgets.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PointMarkerDock");
    this.getGuiAction().setChecked(dock.visible);
};

PointMarkerList.init = function(basePath) {
    var appWin = RMainWindowQt.getMainWindow();

    var action = new RGuiAction(qsTr("&Point Marker List"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/PointMarkerList.js");
    action.setIcon(basePath + "/PointMarkerList.svg");
    action.setDefaultShortcut(new QKeySequence("g,t"));
    action.setDefaultCommands(["gt"]);
    action.setSortOrder(10000);
    //var separator = new RGuiAction("", appWin);
    //separator.setSeparator(true);
    //separator.setSortOrder(action.getSortOrder()-1);
    //separator.addToMenu(View.getMenu());
    EAction.addGuiActionTo(action, Widgets, true, true, false);

    var formWidget = WidgetFactory.createWidget(basePath, "PointMarkerList.ui");
    var layout = formWidget.findChild("verticalLayout");
    //var layerList = new RPointMarkerListQt(layout);
    //layerList.objectName = "PointMarkerList";
    //layout.addWidget(layerList, 1, 0);

    var dock = new RDockWidget(qsTr("Point Marker List"), appWin);
    dock.objectName = "PointMarkerDock";
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);

    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });
};
