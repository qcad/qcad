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

include("scripts/EAction.js");

/**
 * The status bar is created and initialized here.
 */
function StatusBar(guiAction) {
    EAction.call(this, guiAction);
}

StatusBar.prototype = new EAction();

StatusBar.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("Status Bar")];
};

StatusBar.init = function(basePath) {
    var appWin = EAction.getMainWindow();

    var action = new RGuiAction(qsTr("&Status Bar"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/StatusBar.js");
    //action.setIcon(basePath + "/StatusBar.svg");
    action.setDefaultShortcut(new QKeySequence("g,s"));
    action.setDefaultCommands(["gs"]);
    action.setGroupSortOrder(3800);
    action.setSortOrder(200);
    action.setWidgetNames(["ViewMenu", "!WidgetsToolBar", "!ViewToolsPanel"]);

//    if (RSettings.getBoolValue("StatusBar/UseDockWidget", false)===true) {
//        var dock = new RDockWidget(qsTr("Status Bar"), appWin);
//        dock.objectName = "StatusBarDock";
//        dock.setFixedHeight(32);
//        dock.minimumWidth = 400;
//        dock.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred);
        var statusBar = appWin.statusBar();
        //var splitter = new QSplitter(dock);
        var splitter = new QSplitter(statusBar);
        splitter.setSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Fixed);
        splitter.setFixedHeight(40);
        splitter.childrenCollapsible = false;
        splitter.objectName = "StatusBar";
//        dock.setWidget(splitter);
        statusBar.addWidget(splitter, 1000);
        //var commandLineDock = appWin.findChild("CommandLineDock");
        //appWin.splitDockWidget(commandLineDock, dock, Qt.Vertical);
//        dock.shown.connect(function() { action.setChecked(true); });
//        dock.hidden.connect(function() { action.setChecked(false); });

//        dock.setTitleBarWidget(new QWidget(dock));
//    }
//    else {
//        var statusBar = appWin.statusBar();
//        statusBar.objectName = "StatusBar";
//    }
};

StatusBar.clearMessage = function() {
    var appWin = EAction.getMainWindow();
    var statusBar;
//    if (RSettings.getBoolValue("StatusBar/UseDockWidget", false)===true) {
//        statusBar = appWin.findChild("StatusBar");
//    }
//    else {
        statusBar = appWin.statusBar();
        statusBar.clearMessage();
//    }
};

StatusBar.getStatusBar = function() {
    var appWin = EAction.getMainWindow();
    return appWin.findChild("StatusBar");
};

StatusBar.addWidget = function(widget, sortOrder, visible) {
    widget.setProperty("SortOrder", sortOrder);

    var i;
    var appWin = EAction.getMainWindow();
    var statusBar = appWin.findChild("StatusBar");
    var list = [];
//    if (RSettings.getBoolValue("StatusBar/UseDockWidget", false)===true) {
//        for (i=0; i<statusBar.count(); i++) {
//            list.push(statusBar.widget(i));
//        }
//    }
//    else {
        list = statusBar.children().filter(function(w) { return !isNull(w.property("SortOrder")); } );
//    }

    var maxSortOrder = 0;
    var index = 0;

    for (i = 0; i < list.length; ++i) {
        var w = list[i];
        var wSortOrder = w.property("SortOrder");
        if (wSortOrder > maxSortOrder && wSortOrder < widget.property("SortOrder")) {
            maxSortOrder = wSortOrder;
            index = i+1;
        }
    }

//    var separator = undefined;
//    if (RS.getSystemId() === "osx" && RSettings.getBoolValue("StatusBar/UseDockWidget", false)===false) {
//        separator = new QFrame();
//        separator.frameShape = QFrame.VLine;
//        separator.frameShadow = QFrame.Sunken;
//        separator.setProperty("SortOrder", sortOrder + 1);
//        separator.objectName = widget.objectName + "Separator";
//    }

    if (index >= list.length) {
        statusBar.addWidget(widget);
//        if (separator) {
//            statusBar.addWidget(separator);
//        }
    } else {
        statusBar.insertWidget(index, widget);
//        if (separator) {
//            statusBar.insertWidget(index + 1, separator);
//        }
    }

    widget.visible = visible;
//    if (separator) {
//        separator.visible = visible;
//    }
};

StatusBar.applyPreferences = function(doc, mdiChild) {
    var appWin = RMainWindowQt.getMainWindow();

    var statusBar = StatusBar.getStatusBar();
    var w, i;

    var widgetNames = ["Abs", "Rel", "AbsPol", "RelPol", "Right", "Left", "SelectionText"];
    for (i=0; i<widgetNames.length; i++) {
        w = statusBar.findChild(widgetNames[i]);
        w.font = RSettings.getStatusBarFont();
    }

    widgetNames = ["CoordinateDisplay", "MouseDisplay", "SelectionDisplay", "ProgressDisplay"];
    for (i=0; i<widgetNames.length; i++) {
        var widgetName = widgetNames[i];

        w = statusBar.findChild(widgetName);
        if (!isNull(w)) {
            w.visible = RSettings.getBoolValue("StatusBar/" + widgetName, true);
        }
        w = statusBar.findChild(widgetName + "Separator");
        if (!isNull(w)) {
            w.visible = RSettings.getBoolValue("StatusBar/" + widgetName, true);
        }
    }
};

StatusBar.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (QCoreApplication.arguments().contains("-no-show")) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    var widget;
//    if (RSettings.getBoolValue("StatusBar/UseDockWidget", false)===true) {
//        widget = appWin.findChild("StatusBarDock");
//    }
//    else {
        widget = appWin.statusBar();
//    }

    widget.visible = !widget.visible;
};
