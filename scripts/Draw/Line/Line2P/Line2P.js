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
 * \class Line2P
 * \brief Line from two points or sequence of lines.
 * \ingroup ecma_draw_line
 */
function Line2P(guiAction) {
    Line.call(this, guiAction);

    this.pointList = new Array();
    this.point1 = undefined;
    this.point2 = undefined;

    this.setUiOptions("Line2P.ui");
}

Line2P.prototype = new Line();

Line2P.State = {
    SettingFirstPoint : 0,
    SettingNextPoint : 1
};

Line2P.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(Line2P.State.SettingFirstPoint);
    this.checkButtonStates();
};

Line2P.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        this.pointList = new Array();
        break;

    case Line2P.State.SettingNextPoint:
        var trNextPoint = qsTr("Next point");
        this.setCommandPrompt(trNextPoint);
        this.setLeftMouseTip(trNextPoint);
        this.setRightMouseTip(qsTr("Done"));
        break;
    }

    EAction.showSnapTools();
};

Line2P.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);
    this.checkButtonStates();
};

Line2P.prototype.escapeEvent = function() {
    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        EAction.prototype.escapeEvent.call(this);
        return;

    case Line2P.State.SettingNextPoint:
        this.setState(Line2P.State.SettingFirstPoint);
        this.checkButtonStates();
        break;
    }
};

Line2P.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        if (!preview) {
            this.point1 = event.getModelPosition();
            this.pointList.push(this.point1);
            di.setRelativeZero(this.point1);
            this.setState(Line2P.State.SettingNextPoint);
        }
        break;

    case Line2P.State.SettingNextPoint:
        this.point2 = event.getModelPosition();
        var op = this.getOperation(preview);
        if (preview) {
            di.previewOperation(op);
        }
        else {
            if (!isNull(op)) {
                di.applyOperation(op);
                this.pointList.push(this.point2);
                di.setRelativeZero(this.point2);
                this.point1 = this.point2;
            }
        }
        break;
    }

    if (!preview) {
        this.checkButtonStates();
    }
};

Line2P.prototype.getOperation = function(preview) {
    var line = new RLineEntity(
        this.getDocument(),
        new RLineData(this.point1, this.point2)
    );
    return new RAddObjectOperation(line);
};

Line2P.prototype.slotClose = function() {
    if (this.pointList.length >= 3) {
        this.point2 = this.pointList[0];
        this.getDocumentInterface().applyOperation(this.getOperation(false));
        this.pointList.push(this.point2);
        this.setState(Line2P.State.SettingFirstPoint);
    }
    
    this.checkButtonStates();
};

Line2P.prototype.slotUndo = function() {
    if (this.pointList.length >= 2) {
        this.pointList.pop();
        this.getDocumentInterface().undo();
        this.point1 = this.pointList[this.pointList.length - 1];
        this.getDocumentInterface().clearPreview();
        this.getDocumentInterface().previewOperation(this.getOperation(true));
    }

    this.checkButtonStates();
};

Line2P.prototype.checkButtonStates = function() {
    var w;
    
    w = objectFromPath("MainWindow::Options::Undo");
    if (this.pointList.length > 1) {
        w.enabled = true;
    } else {
        w.enabled = false;
    }
    
    w = objectFromPath("MainWindow::Options::Close");
    if (this.pointList.length < 3) {
        w.enabled = false;
    } else {
        w.enabled = true;
    }
};
