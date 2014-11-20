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

include("../View.js");

function ToggleStatusBar(guiAction) {
    View.call(this, guiAction);
}

ToggleStatusBar.prototype = new View();

ToggleStatusBar.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var appWin = EAction.getMainWindow();
    var statusBar = appWin.statusBar();
    if (statusBar.visible) {
        statusBar.hide();
    }
    else {
        if (!QCoreApplication.arguments().contains("-no-show")) {
            statusBar.show();
        }
    }

    this.terminate();
};

ToggleStatusBar.prototype.finishEvent = function() {
    View.prototype.finishEvent.call(this);

    var appWin = EAction.getMainWindow();
    var statusBar = appWin.statusBar();

    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(statusBar.visible);
    }
};

