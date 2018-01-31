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

include("../SnapCoordinate/SnapCoordinate.js");
include("../../WidgetFactory.js");

/**
 * RSnap implementation for polar coordinate snap.
 */
function RSnapCoordinatePolar(guiAction) {
    RSnapCoordinate.call(this, guiAction);
    this.r = 0.0;
    this.a = 0.0;
}

RSnapCoordinatePolar.prototype = new RSnapCoordinate();

RSnapCoordinatePolar.prototype.initAction = function(guiAction) {
    this.action = new EAction(guiAction);
    if (!isNull(this.action.setUiOptions)) {
        this.action.setUiOptions(SnapCoordinatePolar.includeBasePath + "/SnapCoordinatePolar.ui");
    }
    var snap = this;

    this.action.slotRChanged = function(value) {
        snap.r = value;
        snap.update();
    };
    this.action.slotAChanged = function(value) {
        snap.a = value;
        snap.update();
    };
    this.action.slotRelativeChanged = function(on) {
        snap.relative = on;
        snap.update();
    };
    this.action.slotSet = function() {
        var ce = snap.getCoordinateEvent();
        if (!isNull(ce)) {
            var di = EAction.getDocumentInterface();
            di.coordinateEvent(ce);
        }
    };
};

RSnapCoordinatePolar.prototype.getCoordinate = function() {
    var di = EAction.getDocumentInterface();
    var coordinate = RVector.createPolar(this.r, this.a);
    if (this.relative) {
        coordinate = coordinate.operator_add(di.getRelativeZero());
    }
    return coordinate;
};



/**
 * \class SnapCoordinatePolar
 * \ingroup ecma_snap
 * \brief Enter polar coordinate.
 */
function SnapCoordinatePolar(guiAction) {
    Snap.call(this, guiAction);
}

SnapCoordinatePolar.prototype = new Snap();
SnapCoordinatePolar.includeBasePath = includeBasePath;

SnapCoordinatePolar.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    
    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/SnapCoordinatePolar/SnapCoordinatePolar.js");
    var s = new RSnapCoordinatePolar(guiAction);
    this.getDocumentInterface().setSnap(s);
    this.terminate();
};

