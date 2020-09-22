/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
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

/**
 * \class EcmaScriptShell
 * \brief Dockable script shell with history.
 * \ingroup ecma_misc_development
 */
function EcmaScriptShell(guiAction) {
    EAction.call(this, guiAction);
}

/*
EcmaScriptShell.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("ECMA Script Shell") ];
};
*/

EcmaScriptShell.prototype = new EAction();
EcmaScriptShell.includeBasePath = includeBasePath;

/**
 * Shows / hides the script shell widget.
 */
EcmaScriptShell.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("EcmaScriptShellDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {

        if (dock.visible===false) {
            // show warning:
            if (RSettings.getBoolValue("EcmaScriptShell/DontShowDialog", false)!==true) {
                var dialog = WidgetFactory.createDialog(EcmaScriptShell.includeBasePath, "EcmaScriptShellDialog.ui", appWin);
                var bb = dialog.findChild("ButtonBox");
                var b = bb.addButton(qsTr("Show ECMAScript Shell"), QDialogButtonBox.AcceptRole);
                b["default"] = false;
                bb.button(QDialogButtonBox.Cancel)["default"] = true;
                var l = dialog.findChild("Message");
                l.openExternalLinks = true;
                var ret = dialog.exec();
                if (ret!==QDialog.Accepted.valueOf()) {
                    dialog.destroy();
                    EAction.activateMainWindow();
                    return;
                }
                WidgetFactory.saveState(dialog);
                dialog.destroy();
                EAction.activateMainWindow();
            }
        }

        dock.visible = !dock.visible;
        if (dock.visible) dock.raise();
    }
};

EcmaScriptShell.prototype.finishEvent = function() {
    EAction.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("EcmaScriptShellDock");
    this.getGuiAction().setChecked(dock.visible);
};

//EcmaScriptShell.prototype.openUrl = function(url) {
//    QDesktopServices.openUrl(url);
//};

EcmaScriptShell.col = "#000";
EcmaScriptShell.colWarning = "#cc0000";
EcmaScriptShell.colPrompt = "#0000cc";


EcmaScriptShell.initStyle = function() {
    if (RSettings.hasDarkGuiBackground()) {
        EcmaScriptShell.col = "#fff";
        EcmaScriptShell.colWarning = "#cc0000";
        EcmaScriptShell.colPrompt = "#2E9AFE";
    }
    else {
        EcmaScriptShell.col = "#000";
        EcmaScriptShell.colWarning = "#cc0000";
        EcmaScriptShell.colPrompt = "#0000cc";
    }
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
    action.setSortOrder(100);
    action.setWidgetNames(["MiscDevelopmentMenu", "MiscDevelopmentToolBar", "MiscDevelopmentToolsPanel"]);

    EcmaScriptShell.initStyle();

    var pl = new RPaletteListenerAdapter();
    appWin.addPaletteListener(pl);
    pl.paletteChanged.connect(EcmaScriptShell.initStyle);

    var formWidget = WidgetFactory.createWidget(basePath, "EcmaScriptShell.ui");

    var frame = formWidget.findChild("Frame");
//    var p = frame.palette;
//    if (!RSettings.hasDarkGuiBackground()) {
//        // white background of command line label:
//        p.setColor(QPalette.Active, QPalette.Window, new QColor(Qt.white));
//    }
//    else {
//        p.setColor(QPalette.Active, QPalette.Window, new QColor("#1e1e1e"));
//    }
//    frame.palette = p;
//    frame.autoFillBackground = true;

    var teHistory = formWidget.findChild("History");
    var leCommand = formWidget.findChild("CommandEdit");
    leCommand.setHistory(RSettings.getStringListValue("EcmaScriptShell/History", []));
    var lCommand = formWidget.findChild("CommandLabel");
    var bToggleTitleBar = formWidget.findChild("ToggleTitleBar");
    var dock = new RDockWidget(qsTr("Script Shell"), appWin);
    dock.objectName = "EcmaScriptShellDock";
    dock.setWidget(formWidget);
    
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });

    dock.visible = false;

    if (!isNull(warning)) {
        // initialize simple API warning handler:
        warning.handler = function(msg) {
            appendAndScroll("<span style='color:"+EcmaScriptShell.colWarning+"'>WARNING: " +  Qt.escape(msg) + "</span>");
        };
    }

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

    var expression = "";
    var bracketsCountR = 0;
    var bracketsCountC = 0;
    var bracketsCountS = 0;
    lCommand.text = ">";

    // user pressed enter, eval command:
    function countBraces(str) {
        for (var i=0, len=str.length; i<len; ++i) {
            switch(str[i]) {
                case '(': ++bracketsCountR; break;
                case ')': --bracketsCountR; break;
                case '{': ++bracketsCountC; break;
                case '}': --bracketsCountC; break;
                case '[': ++bracketsCountS; break;
                case ']': --bracketsCountS; break;
            }
            if (bracketsCountR < 0 || bracketsCountC < 0 || bracketsCountS < 0) {
                // error:
                return false;
            }
        }
        return true;
    }

    leCommand.escape.connect(function() {
        leCommand.setProperty("OpenBrackets", bracketsCountR+bracketsCountC+bracketsCountS);
        bracketsCountR = 0;
        bracketsCountC = 0;
        bracketsCountS = 0;
        lCommand.text = ">";
        expression = "";
    });

    leCommand.commandConfirmed.connect(function(command) {
        // save history:
        var h = leCommand.getHistory();
        if (h.length>100) {
            h = h.slice(-100);
        }

        RSettings.setValue("EcmaScriptShell/History", h);

        leCommand.clear();

        var historySize = RSettings.getIntValue("EcmaScriptShell/HistorySize", 1000);
        var buf = teHistory.plainText.split("\n");
        if (buf.length > historySize) {
            teHistory.setPlainText(buf.slice(-historySize).join("\n"));
        }

        appendAndScroll("<span style='font-style:italic;color:"+EcmaScriptShell.colPrompt+";'>" + Qt.escape("ecma> ") + "</span>"
                        + "<span style='color:"+EcmaScriptShell.col+"'>" + Qt.escape(command) + "</span>");
        leCommand.appendCommand(command);

        // if we have open brackets: continue entering:
        countBraces(command);
        expression+=command + "\n";
        if (bracketsCountR>0 || bracketsCountC>0 || bracketsCountS>0) {
            lCommand.text = "...";
        }
        else {
            var res;
            try {
                //startTransaction();
                //res = RMainWindow.getMainWindow().eval("js", expression);
                res = EcmaScriptShell.eval(expression);
                //endTransaction();

                // make sure input is enabled again:
                if (!isInputEnabled()) {
                    enableInput();
                }

                appendAndScroll("<span style='color:"+EcmaScriptShell.col+";'>" + Qt.escape(res) + "</span>");
            }
            catch(e) {
                appendAndScroll("<span style='color:"+EcmaScriptShell.colWarning+";'>" + Qt.escape(e) + "</span>");
                //qDebug("error: ", e);
                //qDebug("error: res:", res);
            }

            expression = "";
            bracketsCountR = 0;
            bracketsCountC = 0;
            bracketsCountS = 0;
            lCommand.text = ">";
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

EcmaScriptShell.eval = function(expression) {
    return RMainWindow.getMainWindow().eval("js", expression);
}
