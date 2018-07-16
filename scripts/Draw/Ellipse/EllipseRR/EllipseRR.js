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

include("scripts/Draw/Ellipse/Ellipse.js");
include("../../DrawBasedOnRectangleSize.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class EllipseRR
 * \brief Ellipse from position and radii.
 * \ingroup ecma_draw_ellipse
 */
function EllipseRR(guiAction) {
    DrawBasedOnRectangleSize.call(this, guiAction);

    this.dialogUiFile = "EllipseRRDialog.ui";
    this.setUiOptions("EllipseRR.ui");
}

EllipseRR.prototype = new DrawBasedOnRectangleSize();

EllipseRR.prototype.getShapes = function(corners) {
    var lines = [];
    for (var i=0; i<corners.length; ++i) {
        lines.push(new RLine(corners[i], corners[(i+1)%corners.length]));
    }
    var ellipse = ShapeAlgorithms.createEllipseInscribedFromLines(lines[0], lines[1], lines[2], lines[3]);

    ellipse = Ellipse.postProcess(ellipse);

    return [ ellipse ];
};

EllipseRR.prototype.getAuxPreview = function() {
    if (isNull(this.corners) || this.corners.length===0) {
        return undefined;
    }

    var ret = [];

    for (var i=0; i<this.corners.length; ++i) {
        ret.push(new RLine(this.corners[i], this.corners[(i+1)%this.corners.length]));
    }

    return ret;
};

EllipseRR.prototype.slotXRadiusChanged = function(value) {
    this.width = value * 2;
    this.updateOkButton();
    this.updatePreview(true);
};

EllipseRR.prototype.slotYRadiusChanged = function(value) {
    this.height = value * 2;
    this.updateOkButton();
    this.updatePreview(true);
};
