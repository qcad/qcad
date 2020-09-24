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
include("../../DrawBasedOnRectanglePP.js");
include("scripts/Draw/Hatch/Hatch.js");

/**
 * \class ShapeRectanglePP
 * \brief Rectangle from two corner points.
 * \ingroup ecma_draw_shape
 */
function ShapeRectanglePP(guiAction) {
    DrawBasedOnRectanglePP.call(this, guiAction);

    this.createPolyline = false;
    this.fill = false;
    this.roundCorners = false;
    this.radius = 1.0;

    this.setUiOptions(["../Shape.ui", "ShapeRectanglePP.ui"]);
}

ShapeRectanglePP.prototype = new DrawBasedOnRectanglePP();

ShapeRectanglePP.prototype.beginEvent = function() {
    DrawBasedOnRectanglePP.prototype.beginEvent.call(this);
};

ShapeRectanglePP.prototype.getOperation = function(preview) {
    var doc = this.getDocument();
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

    Shape.complementOperation(this, doc, op, shapes);

    return op;
};

ShapeRectanglePP.prototype.getShapes = function(corners) {
    return Shape.getShapes(this, corners);
};

ShapeRectanglePP.prototype.slotCreatePolylineChanged = function(checked) {
    Shape.slotCreatePolylineChanged(this, checked);
};

ShapeRectanglePP.prototype.slotFillChanged = function(checked) {
    Shape.slotFillChanged(this, checked);
};

ShapeRectanglePP.prototype.slotRoundCornersChanged = function(checked) {
    Shape.slotRoundCornersChanged(this, checked);
};

ShapeRectanglePP.prototype.slotRadiusChanged = function(v) {
    Shape.slotRadiusChanged(this, v);
};

ShapeRectanglePP.prototype.slotRotateChanged = function(v) {
    this.rotate = v;
    this.updatePreview(true);
};

ShapeRectanglePP.prototype.slotRotationChanged = function(value) {
    if (isNumber(value)) {
        this.rotation = value;
    }
    else {
        this.rotation = 0.0;
    }
    this.updatePreview(true);
};

ShapeRectanglePP.prototype.initUiOptions = function(resume, optionsToolBar) {
    DrawBasedOnRectanglePP.prototype.initUiOptions.call(this, resume, optionsToolBar);

    this.createPolyline = RSettings.getBoolValue(this.settingsGroup + "/CreatePolyline", false);

    //var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("CreatePolyline");
    if (!isNull(w)) {
        w.checked = this.createPolyline;
    }
};

ShapeRectanglePP.prototype.hideUiOptions = function(saveToSettings) {
    DrawBasedOnRectanglePP.prototype.hideUiOptions.call(this, saveToSettings);

    RSettings.setValue(this.settingsGroup + "/CreatePolyline", this.createPolyline);
};
