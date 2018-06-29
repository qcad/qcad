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
include("../../WidgetFactory.js");

/**
 * RSnap implementation. Extends RSnapDistance with an options toolbar which
 * allows the user to enter the snap distance.
 */
function RSnapDistanceExtension() {
    RSnapDistance.call(this);

    this.action = new EAction(
         RGuiAction.getByScriptFile("scripts/Snap/SnapDistance/SnapDistance.js")
    );
    this.action.setUiOptions(SnapDistance.includeBasePath + "/SnapDistance.ui");
    var snap = this;
    this.action.slotDistanceChanged = function(value) {
        snap.setDistance(value);
    };
}

RSnapDistanceExtension.prototype = new RSnapDistance();

RSnapDistanceExtension.prototype.showUiOptions = function() {
    this.action.showUiOptions(false);
};

RSnapDistanceExtension.prototype.hideUiOptions = function() {
    this.action.hideUiOptions();
};



/**
 * \class SnapDistance
 * \ingroup ecma_snap
 * \brief Snap to point with distance from end point.
 */
function SnapDistance(guiAction) {
    Snap.call(this, guiAction);
}

SnapDistance.prototype = new Snap();
SnapDistance.includeBasePath = includeBasePath;

SnapDistance.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    var s = new RSnapDistanceExtension();
    this.getDocumentInterface().setSnap(s);
    this.terminate();
};

