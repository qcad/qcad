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

include("../Line.js");

/**
 * \class LineRectangle
 * \brief Rectangle from two corner points.
 * \ingroup ecma_draw_line
 */
function LineRectangle(guiAction) {
    Line.call(this, guiAction);

    this.corner1 = undefined;
    this.corner2 = undefined;
}

LineRectangle.prototype = new Line();

LineRectangle.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1
};

LineRectangle.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineRectangle.State.SettingCorner1);
};

LineRectangle.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineRectangle.State.SettingCorner1:
        var trFirstCorner = qsTr("First corner");
        this.setCommandPrompt(trFirstCorner);
        this.setLeftMouseTip(trFirstCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case LineRectangle.State.SettingCorner2:
        var trSecondCorner = qsTr("Second corner");
        this.setCommandPrompt(trSecondCorner);
        this.setLeftMouseTip(trSecondCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

LineRectangle.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineRectangle.State.SettingCorner1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case LineRectangle.State.SettingCorner2:
        this.setState(LineRectangle.State.SettingCorner1);
        break;
    }
};

LineRectangle.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case LineRectangle.State.SettingCorner1:
        this.corner1 = event.getModelPosition();
        di.setRelativeZero(this.corner1);
        this.setState(LineRectangle.State.SettingCorner2);
        break;

    case LineRectangle.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        di.setRelativeZero(this.corner2);
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
            this.setState(LineRectangle.State.SettingCorner1);
        }
        break;
    }
};

LineRectangle.prototype.coordinateEventPreview = function(event) {
    switch (this.state) {
    case LineRectangle.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        this.updatePreview();
        break;
    default:
        break;
    }
};

LineRectangle.prototype.getOperation = function(preview) {
    var corners = new Array(
        new RVector(this.corner1.x, this.corner1.y),
        new RVector(this.corner2.x, this.corner1.y),
        new RVector(this.corner2.x, this.corner2.y),
        new RVector(this.corner1.x, this.corner2.y)
    );
    var op = new RAddObjectsOperation();
    for (var i=0; i<4; ++i) {
        var line = new RLineEntity(
            this.getDocument(),
            new RLineData(
                corners[i],
                corners[(i+1)%4]
            )
        );
        op.addObject(line);
    }
    return op;
};

