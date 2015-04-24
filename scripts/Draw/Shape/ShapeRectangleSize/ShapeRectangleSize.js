/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
include("../../DrawBasedOnRectangleSize.js");

/**
 * \class ShapeRectangleSize
 * \brief Rectangle from point and size.
 * \ingroup ecma_draw_shape
 */
function ShapeRectangleSize(guiAction) {
    DrawBasedOnRectangleSize.call(this, guiAction);

    this.createPolyline = false;
    this.includeBasePath = ShapeRectangleSize.includeBasePath;
    this.dialogUiFile = "ShapeRectangleSizeDialog.ui";

    this.setUiOptions(["../Shape.ui", "ShapeRectangleSize.ui"]);
}

ShapeRectangleSize.prototype = new DrawBasedOnRectangleSize();
ShapeRectangleSize.includeBasePath = includeBasePath;

ShapeRectangleSize.prototype.getShapes = function(corners) {
    return Shape.prototype.getShapes.call(this, corners);
};

ShapeRectangleSize.prototype.slotCreatePolylineChanged = function(checked) {
    this.createPolyline = checked;
};

