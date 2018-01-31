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

include("../Circle.js");
include("../../DrawBasedOnRectangleSize.js");

/**
 * \class CircleCD
 * \brief Circle from center and radius.
 * \ingroup ecma_draw_circle
 */
function CircleCD(guiAction) {
    DrawBasedOnRectangleSize.call(this, guiAction);

    this.dialogUiFile = "CircleCDDialog.ui";
    this.setUiOptions("CircleCD.ui");
}

CircleCD.prototype = new DrawBasedOnRectangleSize();

CircleCD.prototype.getShapes = function(corners) {
    var circle = new RCircle(RVector.getAverage(corners[0], corners[2]), corners[0].getDistanceTo(corners[1])/2);
    return [ circle ];
};

CircleCD.prototype.getAuxPreview = function() {
    if (isNull(this.corners) || this.corners.length===0) {
        return undefined;
    }

    var ret = [];

    for (var i=0; i<this.corners.length; ++i) {
        ret.push(new RLine(this.corners[i], this.corners[(i+1)%this.corners.length]));
    }

    return ret;
};

CircleCD.prototype.slotDiameterChanged = function(value) {
    this.width = value;
    this.height = value;
    this.updateOkButton();
    this.updatePreview(true);
};
