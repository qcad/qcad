/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
 * 
 * DirectDistanceEntry handling added 2013 by Robert S.
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

function EcmaScriptShell(guiAction) {
    Widgets.call(this, guiAction);
}

/*
EcmaScriptShell.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("ECMA Script Shell") ];
};
*/

EcmaScriptShell.prototype = new Widgets();

/**
 * Shows / hides the script shell widget.
 */
EcmaScriptShell.prototype.beginEvent = function() {
    Widgets.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("EcmaScriptShellDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
    }
};

EcmaScriptShell.prototype.finishEvent = function() {
    Widgets.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("EcmaScriptShellDock");
    this.getGuiAction().setChecked(dock.visible);
};

EcmaScriptShell.init = function(basePath) {
    var appWin = EAction.getMainWindow();

    var action = new RGuiAction(qsTr("&Script Shell"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/EcmaScriptShell.js");
    action.setIcon(basePath + "/EcmaScriptShell.svg");
    action.setDefaultShortcut(new QKeySequence("g,e"));
    action.setDefaultCommands(["ge"]);
    action.setGroupSortOrder(3800);
    action.setSortOrder(10000);
    action.setWidgetNames(["MiscDeveloperMenu", "MiscDeveloperToolBar", "MiscDeveloperToolsPanel"]);

    var e;
    var formWidget = WidgetFactory.createWidget(basePath, "EcmaScriptShell.ui");
    var teHistory = formWidget.findChild("History");
    var leCommand = formWidget.findChild("CommandEdit");
    var lCommand = formWidget.findChild("CommandLabel");
    var bToggleTitleBar = formWidget.findChild("ToggleTitleBar");
    var dock = new RDockWidget(qsTr("Script Shell"), appWin);
    dock.objectName = "EcmaScriptShellDock";
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });

    function appendAndScroll(msg) {
        teHistory.append(msg);
        var c = teHistory.textCursor();
        c.movePosition(QTextCursor.End);
        teHistory.setTextCursor(c);
        teHistory.ensureCursorVisible();

        var appWin = EAction.getMainWindow();
        var dlg = appWin.findChild("ProgressDialog");
        if (!appWin.enabled || (!isNull(dlg) && dlg.visible)) {
            QCoreApplication.processEvents();
        }
    }

    var showTitleBar = RSettings.getBoolValue("EcmaScriptShell/ShowTitleBar", false);
    if (!showTitleBar) {
        dock.setTitleBarWidget(new QWidget(dock));
        bToggleTitleBar.checked = false;
    }
    else {
        bToggleTitleBar.checked = true;
    }

    // hide title bar of command line dock widget:
    bToggleTitleBar.toggled.connect(
        function(show) {
            if (show) {
                dock.setTitleBarWidget(null);
                RSettings.setValue("EcmaScriptShell/ShowTitleBar", true);
            }
            else {
                dock.setTitleBarWidget(new QWidget(dock));
                RSettings.setValue("EcmaScriptShell/ShowTitleBar", false);
            }
        }
    );

    //var context = this;
    //var evalFunction = context.eval;

    // user pressed enter, eval command:
    leCommand.commandConfirmed.connect(function(command) {
        leCommand.clear();

        var historySize = RSettings.getIntValue("EcmaScriptShell/HistorySize", 1000);
        var buf = teHistory.plainText.split("\n");
        if (buf.length > historySize) {
            teHistory.setPlainText(buf.slice(-historySize).join("\n"));
        }

        appendAndScroll("ecma> " + command);

        //var res = eval.call(global, command);
        //var res = EcmaScriptShell.eval(command);
        var res = RMainWindow.getMainWindow().eval("js", command);

        appendAndScroll(res);

        leCommand.setFocus();
    });
};
