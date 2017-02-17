/**
 * Copyright (c) 2013 by Matthias Melcher. All rights reserved.
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

include("scripts/EAction.js");

/**
 * \class ExLineDove
 * \brief Dovetail joint line between two points.
 * \ingroup ecma_misc_draw
 */
function ExLineDove(guiAction) {
    EAction.call(this, guiAction);

    this.corner1 = undefined;
    this.corner2 = undefined;
}

ExLineDove.prototype = new EAction();

ExLineDove.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1
};

ExLineDove.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(ExLineDove.State.SettingCorner1);
};

ExLineDove.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ExLineDove.State.SettingCorner1:
        var trFirstCorner = qsTr("First corner");
        this.setCommandPrompt(trFirstCorner);
        this.setLeftMouseTip(trFirstCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ExLineDove.State.SettingCorner2:
        var trSecondCorner = qsTr("Second corner");
        this.setCommandPrompt(trSecondCorner);
        this.setLeftMouseTip(trSecondCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

ExLineDove.prototype.escapeEvent = function() {
    switch (this.state) {
    case ExLineDove.State.SettingCorner1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case ExLineDove.State.SettingCorner2:
        this.setState(ExLineDove.State.SettingCorner1);
        break;
    }
};

ExLineDove.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ExLineDove.State.SettingCorner1:
        this.corner1 = event.getModelPosition();
        di.setRelativeZero(this.corner1);
        this.setState(ExLineDove.State.SettingCorner2);
        break;

    case ExLineDove.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        di.setRelativeZero(this.corner2);
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
            this.setState(ExLineDove.State.SettingCorner1);
        }
        break;
    }
};

ExLineDove.prototype.coordinateEventPreview = function(event) {
    switch (this.state) {
    case ExLineDove.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        this.updatePreview();
        break;
    default:
        break;
    }
};

ExLineDove.prototype.getOperation = function(preview) {
    var len = this.corner1.getDistanceTo(this.corner2);
    var ang = this.corner1.getAngleTo(this.corner2);
    var corners = new Array(
        new RVector( 0, 0),
        new RVector( 6, 0),
        new RVector( 4, 8),
        new RVector(16, 8),
        new RVector(14, 0),
        new RVector(20, 0)
    );
    var op = new RAddObjectsOperation();
    for (var i=0; i<5; ++i) {
        var lineData = new RLineData(corners[i],corners[i+1]);
        var line = new RLineEntity(this.getDocument(), lineData);
        line.scale(len/20);
        line.move(this.corner1);
        line.rotate(ang, this.corner1);
        op.addObject(line);
    }
    return op;
};

