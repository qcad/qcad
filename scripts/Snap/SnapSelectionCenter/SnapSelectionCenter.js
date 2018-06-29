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

include("scripts/Snap/Snap.js");

/**
 * \class SnapSelectionCenter
 * \ingroup ecma_snap
 * \brief Snap to center of current selection.
 */
function SnapSelectionCenter(guiAction) {
    Snap.call(this, guiAction);
}

SnapSelectionCenter.prototype = new Snap();

SnapSelectionCenter.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);

    var di = EAction.getDocumentInterface();
    var doc = di.getDocument();

    var view = di.getGraphicsViewWithFocus();
    if (isNull(view)) {
        this.terminate();
        return;
    }
    var scene = view.getScene();
    if (isNull(scene)) {
        this.terminate();
        return;
    }

    var selectionBox = doc.getSelectionBox();
    var pos = selectionBox.getCenter();

    var ce = new RCoordinateEvent(pos, scene, view.getRGraphicsView());
    var base = this.getOverrideBase();
    if (!isNull(base)) {
        base.coordinateEvent(ce);
    }
    //di.coordinateEvent(ce);

    this.terminate();
};

