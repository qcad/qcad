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

include("scripts/Edit/Edit.js");

function Esc(guiAction) {
    Edit.call(this, guiAction);
}

Esc.prototype = new Edit();

Esc.prototype.beginEvent = function() {
    Edit.prototype.beginEvent.call(this);

    var returnFocus = false;

    var appWin = EAction.getMainWindow();
    var w = QApplication.focusWidget();

    // focus in RMathLineEdit (e.g. in options toolbar)
    // return focus to graphics view:
    if (isOfType(w, RMathLineEdit) || isOfType(w, QSpinBox)) {
        if (w.ignoreEscape===true) {
            // ignore escape and use standard action for escape
            // this is for some actions to make sure esc triggers step back
            // and not move focus to graphics view
            // the ignoreEscape property can be set in the UI file
        }
        else {
            returnFocus = true;
        }
    }

    // special case: erase command line text:
    var commandLineEdit = objectFromPath("MainWindow::CommandLine::CommandEdit");
    if (!isNull(commandLineEdit)) {
        if (commandLineEdit.focus) {
            if (commandLineEdit.text!=="") {
                commandLineEdit.text = "";
                this.terminate();
                return;
            }
            else {
                returnFocus = true;
            }
        }
    }

    // special case: erase script shell text:
    var ecmaScriptShellEdit = objectFromPath("MainWindow::EcmaScriptShell::CommandEdit");
    if (!isNull(ecmaScriptShellEdit)) {
        if (ecmaScriptShellEdit.focus) {
            if (ecmaScriptShellEdit.text!=="") {
                ecmaScriptShellEdit.text = "";
                this.terminate();
                return;
            }
            else {
                // give script shell a chance to cancel open brackets
                ecmaScriptShellEdit.escape();
                if (ecmaScriptShellEdit.property("OpenBrackets")>0) {
                    ecmaScriptShellEdit.setProperty("OpenBrackets", 0);
                }
                else {
                    returnFocus = true;
                }
            }
        }
    }

    // special case: erase tool matrix filter text:
    var filterEdit = objectFromPath("MainWindow::ToolMatrixDock::FilterEdit");
    if (!isNull(filterEdit)) {
        if (filterEdit.focus) {
            if (filterEdit.text!=="") {
                filterEdit.text = "";
                this.terminate();
                return;
            }
            else {
                returnFocus = true;
            }
        }
    }

    // return focus to graphics view or application window:
    if (returnFocus) {
        var view = this.getGraphicsView();
        if (!isNull(view) && isFunction(view.getQWidget)) {
            var viewQt = view.getQWidget();
            if (!isNull(viewQt)) {
                viewQt.setFocus(Qt.OtherFocusReason);
                this.terminate();
                return;
            }
        }
        else {
            appWin.setFocus(Qt.OtherFocusReason);
            this.terminate();
            return;
        }
    }

    // send escape event to current action:
    var base = this.getOverrideBase();
    if (!isNull(base)) {
        base.escapeEvent();
    }

    // clear key log of recorded keystrokes:
    appWin.clearKeyLog();

    this.terminate();
};

