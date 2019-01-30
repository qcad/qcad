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
    this.fill = false;
    this.roundCorners = false;
    this.radius = 1.0;

    this.includeBasePath = ShapeRectangleSize.includeBasePath;
    this.dialogUiFile = "ShapeRectangleSizeDialog.ui";

    this.setUiOptions(["../Shape.ui", "ShapeRectangleSize.ui"]);
}

ShapeRectangleSize.prototype = new DrawBasedOnRectangleSize();
ShapeRectangleSize.includeBasePath = includeBasePath;

ShapeRectangleSize.prototype.getShapes = function(corners) {
    return Shape.getShapes(this, corners);
};

ShapeRectangleSize.prototype.slotCreatePolylineChanged = function(checked) {
    Shape.slotCreatePolylineChanged(this, checked);
};

ShapeRectangleSize.prototype.slotFillChanged = function(checked) {
    Shape.slotFillChanged(this, checked);
};

ShapeRectangleSize.prototype.slotRoundCornersChanged = function(checked) {
    Shape.slotRoundCornersChanged(this, checked);
};

ShapeRectangleSize.prototype.slotRadiusChanged = function(v) {
    Shape.slotRadiusChanged(this, v);
};

ShapeRectangleSize.prototype.initUiOptions = function(resume, optionsToolBar) {
    DrawBasedOnRectangleSize.prototype.initUiOptions.call(this, resume, optionsToolBar);

    this.createPolyline = RSettings.getBoolValue(this.settingsGroup + "/CreatePolyline", false);

    //var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("CreatePolyline");
    if (!isNull(w)) {
        w.checked = this.createPolyline;
    }
};

ShapeRectangleSize.prototype.hideUiOptions = function(saveToSettings) {
    DrawBasedOnRectangleSize.prototype.hideUiOptions.call(this, saveToSettings);

    RSettings.setValue(this.settingsGroup + "/CreatePolyline", this.createPolyline);
};

ShapeRectangleSize.prototype.getOperation = function(preview) {
    var op = DrawBasedOnRectangleSize.prototype.getOperation.call(this, preview);
    if (!isNull(op)) {
        var shapes = this.getShapes(this.corners);
        Shape.complementOperation(this, this.getDocument(), op, shapes);
    }
    return op;
};
