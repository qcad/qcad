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

function PanZoom(guiAction) {
    View.call(this, guiAction);
    this.panning = false;
    this.panOrigin = new RVector();
}

PanZoom.prototype = new View();

PanZoom.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);
    this.getDocumentInterface().setClickMode(RAction.PickingDisabled);
    this.getDocumentInterface().setCursor(new QCursor(Qt.OpenHandCursor));
};

PanZoom.prototype.mousePressEvent = function(event) {
    if (event.button() == Qt.LeftButton) {
        this.panOrigin = event.getScreenPosition();
        this.panning = true;
        this.getDocumentInterface().setCursor(new QCursor(Qt.ClosedHandCursor));
    }
    else {
        View.prototype.mousePressEvent.call(this, event);
    }
};

PanZoom.prototype.mouseReleaseEvent = function(event) {
    if (event.button() == Qt.LeftButton) {
        this.panning = false;
        this.getDocumentInterface().setCursor(new QCursor(Qt.OpenHandCursor));
    }
    else {
        View.prototype.mouseReleaseEvent.call(this, event);
    }
};

PanZoom.prototype.mouseMoveEvent = function(event) {
    if (event.buttons().valueOf() & Qt.LeftButton.valueOf()) {
        if (this.panning == true) {
            var view = event.getGraphicsView();
            var panTarget = event.getScreenPosition();
            var panDelta = panTarget.operator_subtract(this.panOrigin);
            if (panDelta.x != 0 || panDelta.y != 0) {
                view.pan(panDelta);
            }
            this.panOrigin = panTarget;
        }
    }
};

PanZoom.prototype.finishEvent = function(event) {
    View.prototype.finishEvent.call(this);
    this.getDocumentInterface().setCursor(new QCursor(Qt.ArrowCursor));
};

