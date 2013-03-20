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

include("../IsometricProjection.js");


function IsoProject(guiAction) {
    Projection.call(this, guiAction);

    this.projection = RS.IsoTop;
    this.trueScale = false;

    this.setUiOptions("IsoProject.ui");
}

IsoProject.prototype = new Projection();

IsoProject.includeBasePath = includeBasePath;

//IsoProject.prototype.beginEvent = function() {
//    Projection.prototype.beginEvent.call(this);

//    if (!this.verifySelection()) {
//        return;
//    }

//    this.setState(Projection.State.SettingReferencePoint);
//};

/**
 * Isometric projection of a single coordinate.
 */
IsoProject.prototype.project = function(p) {
    p.isoProject(this.projection, this.trueScale);
};

IsoProject.prototype.slotTopChanged = function() {
    this.projection = RS.IsoTop;
    this.updatePreview(true);
};

IsoProject.prototype.slotBottomChanged = function() {
    this.projection = RS.IsoBottom;
    this.updatePreview(true);
};

IsoProject.prototype.slotLeftChanged = function() {
    this.projection = RS.IsoLeft;
    this.updatePreview(true);
};

IsoProject.prototype.slotLeftBackChanged = function() {
    this.projection = RS.IsoLeftBack;
    this.updatePreview(true);
};

IsoProject.prototype.slotRightChanged = function() {
    this.projection = RS.IsoRight;
    this.updatePreview(true);
};

IsoProject.prototype.slotRightBackChanged = function() {
    this.projection = RS.IsoRightBack;
    this.updatePreview(true);
};

IsoProject.prototype.slotTrueScaleChanged = function(v) {
    this.trueScale = v;
    this.updatePreview(true);
};
