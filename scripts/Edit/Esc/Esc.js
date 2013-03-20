/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("../Edit.js");

function Esc(guiAction) {
    Edit.call(this, guiAction);
}

Esc.prototype = new Edit();

Esc.prototype.beginEvent = function() {
    Edit.prototype.beginEvent.call(this);

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
                var appWin = EAction.getMainWindow();
                appWin.setFocus(Qt.OtherFocusReason);
            }
        }
    }

    // send escape event to current action:
    var base = this.getOverrideBase();
    if (!isNull(base)) {
        base.escapeEvent();
    }
    this.terminate();
};

