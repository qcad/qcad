/**
 * Copyright (c) 2014 by Robert S. All rights reserved.
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

function DisplayDistanceAngle(guiAction) {
    View.call(this, guiAction);
}

DisplayDistanceAngle.prototype = new View();

DisplayDistanceAngle.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();

    var base = this.getOverrideBase();
    if (isNull(base)) {
        return;
    }

    if (base.getClickMode() === RAction.PickCoordinate) {
        var display = RSettings.getIntValue("DisplaySettings/DisplayDistanceAngle", 0);
        display += 1;
        if (display > 3) {
            display = 0;
        }
        RSettings.setValue("DisplaySettings/DisplayDistanceAngle", display);
    }
    this.terminate();
};

