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
 * \class SnapMiddleManual
 * \ingroup ecma_snap
 * \brief Snap to middle points between two points.
 */
function SnapMiddleManual(guiAction) {
    Snap.call(this, guiAction);

    this.State = {
        PickingPoint1 : 0,
        PickingPoint2 : 1
    };

    this.state = this.State.PickingPoint1;
    this.point1 = undefined;
    this.point2 = undefined;
}

SnapMiddleManual.prototype = new Snap();

SnapMiddleManual.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    this.di = this.getDocumentInterface();
    this.di.setSnap(new RSnapAuto());
    this.di.setClickMode(RAction.PickCoordinate);
    this.base = this.getOverrideBase();
    if (isNull(this.base)) {
        qWarning("No base action to override");
        this.terminate();
        return;
    }
    if (this.base.getClickMode()!=RAction.PickCoordinate) {
        qWarning("No coordinate requested at this point");
        this.terminate();
    }
};

SnapMiddleManual.prototype.coordinateEvent = function(event) {
    if (this.state===this.State.PickingPoint1) {
        this.point1 = event.getModelPosition();
        this.state = this.State.PickingPoint2;
        this.di.setRelativeZero(this.point1);
    }
    else {
        this.point2 = event.getModelPosition();
        var mp = this.point1.operator_add(this.point2).operator_divide(2.0);
        mp = this.restrict(mp);
        if (!isNull(this.base)) {
            this.base.coordinateEvent(
                new RCoordinateEvent(
                    mp,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
        }
        this.terminate();
    }
};

SnapMiddleManual.prototype.coordinateEventPreview = function(event) {
    if (this.state===this.State.PickingPoint2) {
        this.point2 = event.getModelPosition();
        var mp = this.point1.operator_add(this.point2).operator_divide(2.0);
        mp = this.restrict(mp);
        if (!isNull(this.base)) {
            this.base.coordinateEventPreview(
                new RCoordinateEvent(
                    mp,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
            var line = new RLine(this.point1, this.point2);
            this.di.addAuxShapeToPreview(line);
            this.di.setCursorPosition(mp);
        }
    }
};

