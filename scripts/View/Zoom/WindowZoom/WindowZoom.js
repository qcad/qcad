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

include("scripts/View/View.js");


function WindowZoom(guiAction) {
    View.call(this, guiAction);

    this.v1 = RVector.invalid;
    this.v2 = RVector.invalid;
    this.s1 = RVector.invalid;
    this.s2 = RVector.invalid;

    var bitmap, mask
    if (RSettings.getDevicePixelRatio()===2 && RS.getSystemId()!=="osx") {
        bitmap = new QBitmap(WindowZoom.includeBasePath + "/WindowZoomCursor@2x.png", "PNG");
        mask = new QBitmap(WindowZoom.includeBasePath + "/WindowZoomCursorMask@2x.png", "PNG");
        this.cursor = new QCursor(bitmap, mask, 24, 24);
    }
    else {
        bitmap = new QBitmap(WindowZoom.includeBasePath + "/WindowZoomCursor.png", "PNG");
        mask = new QBitmap(WindowZoom.includeBasePath + "/WindowZoomCursorMask.png", "PNG");
        this.cursor = new QCursor(bitmap, mask, 12, 12);
    }
}

WindowZoom.prototype = new View();
WindowZoom.includeBasePath = includeBasePath;

WindowZoom.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1
};

WindowZoom.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);
    this.setState(WindowZoom.State.SettingCorner1);
};

WindowZoom.prototype.setState = function(state) {
    View.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickingDisabled);
    this.setCursor(this.cursor, "WindowZoomCursor");
};

WindowZoom.prototype.mousePressEvent = function(event) {
    this.view = event.getGraphicsView();

    if (event.button() == Qt.LeftButton) {
        if (this.state == WindowZoom.State.SettingCorner1) {
            this.v1 = event.getModelPosition();
            this.s1 = event.getScreenPosition();
            this.state = WindowZoom.State.SettingCorner2;
        }
    }
};

WindowZoom.prototype.mouseReleaseEvent = function(event) {
    if (this.view != event.getGraphicsView()) {
        return;
    }
    if (event.button() == Qt.LeftButton) {
        if (this.state == WindowZoom.State.SettingCorner2) {
            this.v2 = event.getModelPosition();
            this.s2 = event.getScreenPosition();
            if (this.s1.getDistanceTo(this.s2) > 5) {
                var di = this.getDocumentInterface();
                di.clearPreview();
                di.zoomTo(new RBox(this.v1, this.v2));
                di.repaintViews();
                this.state = WindowZoom.State.SettingCorner1;
            }
        }
    }
    else {
        View.prototype.mouseReleaseEvent.call(this, event);
    }
};

WindowZoom.prototype.mouseMoveEvent = function(event) {
    if (this.state == WindowZoom.State.SettingCorner2 && this.v1.isValid()) {
        if (this.view == event.getGraphicsView()) {
            this.v2 = event.getModelPosition();
        }
        this.getDocumentInterface().addZoomBoxToPreview(
                new RBox(this.v1, this.v2));
    }
};

WindowZoom.prototype.finishEvent = function(event) {
    View.prototype.finishEvent.call(this);
    this.setCursor(new QCursor(Qt.ArrowCursor));
};

