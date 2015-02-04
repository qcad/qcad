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
include("scripts/simple.js");

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
    action.setWidgetNames(["MiscDevelopmentMenu", "MiscDevelopmentToolBar", "MiscDevelopmentToolsPanel"]);

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

        //qDebug(teHistory.html);

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

    // user pressed enter, eval command:
    leCommand.commandConfirmed.connect(function(command) {
        leCommand.clear();

        var historySize = RSettings.getIntValue("EcmaScriptShell/HistorySize", 1000);
        var buf = teHistory.plainText.split("\n");
        if (buf.length > historySize) {
            teHistory.setPlainText(buf.slice(-historySize).join("\n"));
        }

        appendAndScroll("<span style='color:#000000;'>" + Qt.escape("ecma> ") + Qt.escape(command) + "</span>");

        var res;
        try {
            res = RMainWindow.getMainWindow().eval("js", command);
            appendAndScroll("<span style='color:#000000;'>" + Qt.escape(res) + "</span>");
        }
        catch(e) {
            appendAndScroll("<span style='color:#cc0000;'>" + Qt.escape(e) + "</span>");
            //qDebug("error: ", e);
            //qDebug("error: res:", res);
        }

        leCommand.setFocus();
    });

    // user pressed tab:
    leCommand.completeCommand.connect(function(command) {
        // look from cursor pos backwards:
        //var toComplete = command.substring(0, leCommand.cursorPosition);

        var i2 = leCommand.cursorPosition;
        var i1 = command.regexLastIndexOf(/[^a-zA-Z0-9_]/, i2) + 1;
        var i0 = 0;
        if (i1>2) {
            i0 = command.regexLastIndexOf(/[^a-zA-Z0-9_]/, i1-2) + 1;
        }

        var objName = command.substring(i0, i1-1);
        var toComplete = command.substring(i1, i2);

        var obj = global;
        if (objName.length>0) {
            obj = eval(objName);
        }

        var choices = [];

        //choices = Object.keys(obj);
        for (var k in obj) {
            choices.push(k);
        }

        choices = choices.filter(function(e) { return e.startsWith(toComplete); });
        if (choices.length === 0) {
            // nothing to match
        } else if (choices.length === 1) {
            // only one match. complete it:
            //qDebug("inserting:",choices[0].substring(i2-i1));
            leCommand.insert(choices[0].substring(i2-i1));
        } else {
            // suggest multiple choices that match so far:
            appendAndScroll(choices.join(", "));

            // complete as much as possible:
            var done = false;
            var i = toComplete.length;
            do {
                for (var k=0; k<choices.length; ++k) {
                    if (choices[k].length <= i) {
                        done = true;
                        break;
                    }

                    if (choices[k][i] != choices[0][i]) {
                        done = true;
                        break;
                    }
                }
                if (!done) {
                    leCommand.insert(choices[0][i++]);
                    //command = command.concat(choices[0][i++]);
                }
            } while(!done);

            //leCommand.text = command;
        }
    });

    leCommand.clearHistory.connect(teHistory, "clear");
};
