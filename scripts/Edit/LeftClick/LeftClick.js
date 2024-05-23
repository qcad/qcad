/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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

function LeftClick(guiAction) {
    Edit.call(this, guiAction);
}

LeftClick.prototype = new Edit();

/**
 * Triggers left-click in graphics view by shortcut.
 */
LeftClick.prototype.beginEvent = function() {
    Edit.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    if (isNull(di)) {
        this.terminate();
        return;
    }

    var gv = di.getLastKnownViewWithFocus();
    if (isNull(gv)) {
        this.terminate();
        return;
    }

    var gvWidget = gv.getWidget();
    if (isNull(gvWidget)) {
        this.terminate();
        return;
    }

    var gs = gv.getScene();
    if (isNull(gs)) {
        this.terminate();
        return;
    }

    var globalCursorPos = QCursor.pos();
    var cursorPos = gvWidget.mapFromGlobal(globalCursorPos);

    var nevt = new QMouseEvent(QEvent.MouseButtonPress, cursorPos, Qt.LeftButton, Qt.LeftButton, Qt.NoModifier);
    QCoreApplication.postEvent(gvWidget, nevt);

    var nevt2 = new QMouseEvent(QEvent.MouseButtonRelease, cursorPos, Qt.LeftButton, Qt.LeftButton, Qt.NoModifier);
    QCoreApplication.postEvent(gvWidget, nevt2);

    this.terminate();
};

