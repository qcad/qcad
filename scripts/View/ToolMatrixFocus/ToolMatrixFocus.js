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

include("scripts/View/View.js");

function ToolMatrixFocus(guiAction) {
    View.call(this, guiAction);
}

ToolMatrixFocus.prototype = new View();

ToolMatrixFocus.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var appWin = EAction.getMainWindow();
    var filterEdit = objectFromPath("MainWindow::ToolMatrixWidget::FilterEdit");
    if (filterEdit.visible) {
        filterEdit.setFocus(Qt.OtherFocusReason);
        filterEdit.selectAll();
    }
    var w = appWin.findChild("ToolMatrixWidget");
    if (w.visible) {
        w.activateWindow();
    }

    this.terminate();
};
