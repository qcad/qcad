/**
 * Copyright (c) 2013 by Robert S. All rights reserved.
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

include("scripts/EAction.js");

/**
 * \class SnapYManual
 * \ingroup ecma_snap
 * \brief Lock Y coordinate.
 */
function SnapYManual(guiAction) {
    EAction.call(this, guiAction);

    this.State = {
        PickingPoint1 : 0,
        PickingPoint2 : 1
    };

    this.state = this.State.PickingPoint1;
    this.setCommandPrompt("Specify point for Y coordinate");
    this.point1 = undefined;
    this.point2 = undefined;
};

SnapYManual.prototype = new EAction();

SnapYManual.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.di = this.getDocumentInterface();
    this.di.setClickMode(RAction.PickCoordinate);
    this.base = this.getOverrideBase();
    if (isNull(this.base)) {
        qWarning("No base action to override");
        this.terminate();
        return;
    }
    if (this.base.getClickMode() !== RAction.PickCoordinate) {
        qWarning("No coordinate requested at this point");
        this.terminate();
    }
};

SnapYManual.prototype.coordinateEvent = function(event) {
    if (this.state === this.State.PickingPoint1) {
        this.point1 = event.getModelPosition();
        this.state = this.State.PickingPoint2;
    	this.setCommandPrompt("Specify point for X coordinate");
    }
    else {
        this.point2 = event.getModelPosition();
        var p = new RVector(this.point2.x, this.point1.y);
        if (!isNull(this.base)) {
            this.base.coordinateEvent(
                new RCoordinateEvent(
                    p,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
        }
        this.terminate();
    }
};


SnapYManual.prototype.coordinateEventPreview = function(event) {
    if (this.state === this.State.PickingPoint2) {
        this.point2 = event.getModelPosition();
        var p = new RVector(this.point2.x, this.point1.y);
        if (!isNull(this.base)) {
            this.base.coordinateEventPreview(
                new RCoordinateEvent(
                    p,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
            var point = new RVector(this.point2.x, this.point1.y);
            var line = new RLine(this.point1, point);
            this.di.addAuxShapeToPreview(line);
            this.di.setCursorPosition(p);
        }
    }
};


