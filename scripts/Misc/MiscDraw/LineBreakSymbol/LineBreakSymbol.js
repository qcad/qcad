/**
* Copyright (c) 2021 by Pete Vickerstaff. This is a modified script of the ExLineDove.js
*   script created by Matthias Melcher. All rights reserved.
*
* This file is an extension of the QCAD project.
*
* LineBreakSymbol is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, LineBreakSymbolion 3 of the License, or
* (at your option) any later version.
*
* LineDove2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("scripts/EAction.js");

/**
 * \class LineBreakSymbol
 * \brief break symbol between two points.
 * \ingroup ecma_misc_draw
 */
function LineBreakSymbol(guiAction) {
    EAction.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;
}

LineBreakSymbol.prototype = new EAction();

LineBreakSymbol.State = {
    Settingpoint1 : 0,
    Settingpoint2 : 1
};

LineBreakSymbol.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(LineBreakSymbol.State.Settingpoint1);
};

LineBreakSymbol.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineBreakSymbol.State.Settingpoint1:
        var trFirstPoint = qsTr("Pick the first point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case LineBreakSymbol.State.Settingpoint2:
        var trSecondPoint = qsTr("Pick the second point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

LineBreakSymbol.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineBreakSymbol.State.Settingpoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case LineBreakSymbol.State.Settingpoint2:
        this.setState(LineBreakSymbol.State.Settingpoint1);
        break;
    }
};

LineBreakSymbol.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case LineBreakSymbol.State.Settingpoint1:
        this.point1 = event.getModelPosition();
        di.setRelativeZero(this.point1);
        this.setState(LineBreakSymbol.State.Settingpoint2);
        break;

    case LineBreakSymbol.State.Settingpoint2:
        this.point2 = event.getModelPosition();
        di.setRelativeZero(this.point2);
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
            this.setState(LineBreakSymbol.State.Settingpoint1);
        }
        break;
    }
};

LineBreakSymbol.prototype.coordinateEventPreview = function(event) {
    switch (this.state) {
    case LineBreakSymbol.State.Settingpoint2:
        this.point2 = event.getModelPosition();
        this.updatePreview();
        break;
    default:
        break;
    }
};

LineBreakSymbol.prototype.getOperation = function(preview) {
    var len = this.point1.getDistanceTo(this.point2);
    var ang = this.point1.getAngleTo(this.point2);
    var corners = new Array(
        new RVector( 0, 0),
        new RVector( 1, 3),
        new RVector( 2, -3),
        new RVector(3, 0)
    );
    var op = new RAddObjectsOperation();
    for (var i=0; i<3; ++i) {
        var lineData = new RLineData(corners[i],corners[i+1]);
        var line = new RLineEntity(this.getDocument(), lineData);
        line.scale(len/3);
        line.move(this.point1);
        line.rotate(ang, this.point1);
        op.addObject(line);
    }
    return op;
};
