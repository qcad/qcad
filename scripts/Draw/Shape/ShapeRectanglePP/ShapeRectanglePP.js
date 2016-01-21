/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

include("../Shape.js");
include("../../DrawBasedOnRectanglePP.js");

/**
 * \class ShapeRectanglePP
 * \brief Rectangle from two corner points.
 * \ingroup ecma_draw_shape
 */
function ShapeRectanglePP(guiAction) {
    DrawBasedOnRectanglePP.call(this, guiAction);

    this.createPolyline = false;
    this.setUiOptions("../Shape.ui");
}

ShapeRectanglePP.prototype = new DrawBasedOnRectanglePP();

ShapeRectanglePP.prototype.beginEvent = function() {
    DrawBasedOnRectanglePP.prototype.beginEvent.call(this);
};

ShapeRectanglePP.prototype.getOperation = function(preview) {
    var corners = this.getCorners();

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var shapes = this.getShapes(corners);
    for (var i=0; i<shapes.length; ++i) {
        var e = shapeToEntity(this.getDocument(), shapes[i]);
        if (isNull(e)) {
            continue;
        }
        op.addObject(e);
    }

    return op;
};

ShapeRectanglePP.prototype.getShapes = function(corners) {
    return Shape.prototype.getShapes.call(this, corners);
};

ShapeRectanglePP.prototype.slotCreatePolylineChanged = function(checked) {
    this.createPolyline = checked;
};
