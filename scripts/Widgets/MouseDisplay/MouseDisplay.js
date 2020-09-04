/**
 * Copyright (c) 2011-2020 by Andrew Mustun. All rights reserved.
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
include("scripts/Widgets/StatusBar/StatusBar.js");

function MouseDisplay() {
}

MouseDisplay.postInit = function(basePath) {
    var widget = WidgetFactory.createWidget(basePath, "MouseDisplay.ui");
    StatusBar.addWidget(widget, 200, RSettings.getBoolValue("StatusBar/MouseDisplay", true));

    var right = widget.findChild("Right");
    right.font = RSettings.getStatusBarFont();
    var left = widget.findChild("Left");
    left.font = RSettings.getStatusBarFont();

    var appWin = EAction.getMainWindow();
    appWin.rightMouseTip.connect(function(message) {
        right.text = message;
    });
    appWin.leftMouseTip.connect(function(message) {
        left.text = message;
    });
};
