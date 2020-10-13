/**
 * Copyright (c) 2011-2013 by Robert S. All rights reserved.
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
 * \class SnapDistanceManual
 * \ingroup ecma_snap
 * \brief Snap to point with distance to specified point.
 */
function SnapDistanceManual(guiAction) {
    Snap.call(this, guiAction);

    this.State = {
        PickingPoint1 : 0,
        PickingPoint2 : 1
    };

    this.state = this.State.PickingPoint1;
    this.setCommandPrompt(qsTr("Specify first point to measure distance from"));
    this.point1 = undefined;
    this.point2 = undefined;

    this.setUiOptions("SnapDistanceManual.ui");
}

SnapDistanceManual.prototype = new Snap();

SnapDistanceManual.prototype.beginEvent = function() {
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

    if (this.base.getClickMode() !== RAction.PickCoordinate) {
        qWarning("No coordinate requested at this point");
        this.terminate();
    }
};

SnapDistanceManual.prototype.coordinateEvent = function(event) {
    if (this.state===this.State.PickingPoint1) {
        this.point1 = event.getModelPosition();
        this.state = this.State.PickingPoint2;
        this.di.setRelativeZero(this.point1);
        this.setCommandPrompt(qsTr("Second point"));
    }
    else {
        this.point2 = event.getModelPosition();
        this.generateEvent(event, false);
        this.terminate();
    }
};

SnapDistanceManual.prototype.coordinateEventPreview = function(event) {
    if (this.state===this.State.PickingPoint2) {
        this.point2 = event.getModelPosition();
        this.generateEvent(event, true);
    }
};

SnapDistanceManual.prototype.generateEvent = function(event, preview) {
    var dist2p = this.point1.getDistanceTo(this.point2);
    var ang = this.point1.getAngleTo(this.point2);
    var dist = objectFromPath("MainWindow::Options::Distance");
    var value = RMath.eval(dist.text);
    var tc = objectFromPath("MainWindow::Options::TypeCombo");
    if (tc.currentIndex === 1) {        // Percent
        dist = dist2p * value / 100;
    } else if (tc.currentIndex === 2) { // Fraction
        dist = dist2p * value;
    } else {                            // Distance
        dist = value;
    }
    var v = new RVector();
    v.setPolar(dist, ang);
    var pos = this.point1.operator_add(v);
    pos = this.restrict(pos);
    if (!isNull(this.base)) {
        if (!preview) {
            this.base.coordinateEvent(
                new RCoordinateEvent(
                    pos,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
        } else {
            this.base.coordinateEventPreview(
                new RCoordinateEvent(
                    pos,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
            var line = new RLine(this.point1, this.point2);
            this.di.addAuxShapeToPreview(line);
            this.di.setCursorPosition(pos);
        }
    }
};
