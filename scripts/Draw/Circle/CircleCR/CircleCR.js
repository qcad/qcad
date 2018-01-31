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
 * \class CircleCR
 * \brief Circle from center and radius.
 * \ingroup ecma_draw_circle
 */
function CircleCR(guiAction) {
    DrawBasedOnRectangleSize.call(this, guiAction);

    this.dialogUiFile = "CircleCRDialog.ui";
    this.setUiOptions("CircleCR.ui");
}

CircleCR.prototype = new DrawBasedOnRectangleSize();

CircleCR.prototype.getShapes = function(corners) {
    var circle = new RCircle(RVector.getAverage(corners[0], corners[2]), corners[0].getDistanceTo(corners[1])/2);
    return [ circle ];
};

CircleCR.prototype.getAuxPreview = function() {
    if (isNull(this.corners) || this.corners.length===0) {
        return undefined;
    }

    var ret = [];

    for (var i=0; i<this.corners.length; ++i) {
        ret.push(new RLine(this.corners[i], this.corners[(i+1)%this.corners.length]));
    }

    return ret;
};

CircleCR.prototype.slotRadiusChanged = function(value) {
    this.width = value * 2;
    this.height = value * 2;
    this.updateOkButton();
    this.updatePreview(true);
};
