/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("scripts/Draw/DrawBasedOnThreeCircles.js");
include("scripts/Apollonius.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class PointPowerCenter
 * \brief Point at the power center of three chosen circles.
 * \ingroup ecma_draw_circle
 */
function PointPowerCenter(guiAction) {
    DrawBasedOnThreeCircles.call(this, guiAction);
}

PointPowerCenter.prototype = new DrawBasedOnThreeCircles();

PointPowerCenter.prototype.getShapes = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) || isNull(this.shape3)) {
        return undefined;
    }

    var c = Apollonius.getPowerCenter(this.shape1.data(), this.shape2.data(), this.shape3.data());

    if (isNull(c)) {
        return undefined;
    }

    return [ new RPoint(c) ];
};
