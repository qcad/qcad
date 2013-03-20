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

include("../../WidgetFactory.js");

function MouseDisplay() {
    this.formWidget = undefined;
}

MouseDisplay.init = function(basePath) {
    var md = new MouseDisplay();
    md.formWidget = WidgetFactory.createWidget(basePath, "MouseDisplay.ui");
    var right = md.formWidget.findChild("Right");
    right.font = RSettings.getStatusBarFont();
    var left = md.formWidget.findChild("Left");
    left.font = RSettings.getStatusBarFont();

    var appWin = EAction.getMainWindow();
    appWin.rightMouseTip.connect(md, "setRightMouseTip");
    appWin.leftMouseTip.connect(md, "setLeftMouseTip");
    EAction.addToStatusBar(md.formWidget, 200);
};

MouseDisplay.prototype.setRightMouseTip = function(message) {
    var right = this.formWidget.findChild("Right");
    right.text = message;
};

MouseDisplay.prototype.setLeftMouseTip = function(message) {
    var left = this.formWidget.findChild("Left");
    left.text = message;
};
