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

    var statusBar = appWin.statusBar();
    var splitter = new QSplitter(statusBar);
    splitter.setSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Fixed);
    splitter.setFixedHeight(40);
    splitter.childrenCollapsible = false;
    splitter.objectName = "StatusBar";
    statusBar.addWidget(splitter, 1000);
};

StatusBar.postInit = function() {
    var statusBarSplitter = StatusBar.getStatusBarSplitter();
    if (isNull(statusBarSplitter)) {
        return;
    }
    var sl = RSettings.getStringListValue("StatusBar/Sizes", []);
    var l = [];
    for (var i=0; i<sl.length; i++) {
        l.push(parseInt(sl[i]));
    }
    statusBarSplitter.setSizes(l);
};

StatusBar.uninit = function(basePath) {
    var statusBarSplitter = StatusBar.getStatusBarSplitter();
    if (isNull(statusBarSplitter)) {
        return;
    }
    var sizes = statusBarSplitter.sizes();
    var sl = [];
    for (var i=0; i<sizes.length; i++) {
        sl.push("%1".arg(sizes[i]));
    }
    RSettings.setValue("StatusBar/Sizes", sl);
};

StatusBar.clearMessage = function() {
    var appWin = EAction.getMainWindow();
    var statusBar = appWin.statusBar();
    statusBar.clearMessage();
};

StatusBar.getStatusBarSplitter = function() {
    var appWin = EAction.getMainWindow();
    return appWin.findChild("StatusBar");
};

StatusBar.addWidget = function(widget, sortOrder, visible) {
    widget.setProperty("SortOrder", sortOrder);

    var i;
    var appWin = EAction.getMainWindow();
    var statusBarSplitter = appWin.findChild("StatusBar");
    var list = [];
    for (i=0; i<statusBarSplitter.count(); i++) {
        list.push(statusBarSplitter.widget(i));
    }

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

    widget.setParent(statusBarSplitter);
    if (index >= list.length) {
        statusBarSplitter.addWidget(widget);
    } else {
        statusBarSplitter.insertWidget(index, widget);
    }

    widget.visible = visible;
};

StatusBar.applyPreferences = function(doc, mdiChild) {
    var appWin = RMainWindowQt.getMainWindow();

    var statusBarSplitter = StatusBar.getStatusBarSplitter();
    StatusBar.applyFont(statusBarSplitter);

    var widgetNames = ["CoordinateDisplay", "MouseDisplay", "SelectionDisplay", "ProgressDisplay"];
    for (var i=0; i<widgetNames.length; i++) {
        var widgetName = widgetNames[i];

        var w = statusBarSplitter.findChild(widgetName);
        if (!isNull(w)) {
            w.visible = RSettings.getBoolValue("StatusBar/" + widgetName, true);
        }
        w = statusBarSplitter.findChild(widgetName + "Separator");
        if (!isNull(w)) {
            w.visible = RSettings.getBoolValue("StatusBar/" + widgetName, true);
        }
    }
};

StatusBar.applyFont = function(widget) {
    var children = widget.children();
    for (var i = 0; i < children.length; ++i) {
        var c = children[i];
        if (isOfType(c, QLabel) || isOfType(c, QComboBox)) {
            c.font = RSettings.getStatusBarFont();
        }
        else {
            StatusBar.applyFont(c);
        }
    }
};

StatusBar.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (QCoreApplication.arguments().contains("-no-show")) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    var widget = appWin.statusBar();
    widget.visible = !widget.visible;
};
