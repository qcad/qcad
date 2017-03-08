/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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
    this.setUiOptions("../Shape.ui");
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

    if (this.fill) {
        var hatchData = new RHatchData();
        hatchData.setDocument(doc);
        hatchData.setAngle(0.0);
        hatchData.setScale(1.0);
        hatchData.setSolid(true);
        hatchData.setPatternName("SOLID");
        hatchData.newLoop();
        for (var k=0; k<shapes.length; ++k) {
            hatchData.addBoundary(shapes[k]);
        }
        op.addObject(new RHatchEntity(doc, hatchData));
    }

    return op;
};

ShapeRectanglePP.prototype.getShapes = function(corners) {
    return Shape.prototype.getShapes.call(this, corners);
};

ShapeRectanglePP.prototype.slotCreatePolylineChanged = function(checked) {
    Shape.prototype.slotCreatePolylineChanged.call(this, checked);
};

ShapeRectanglePP.prototype.slotFillChanged = function(checked) {
    Shape.prototype.slotFillChanged.call(this, checked);
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
