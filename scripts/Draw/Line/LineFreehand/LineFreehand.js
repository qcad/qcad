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

include("scripts/Draw/Line/Line.js");

/**
 * \class LineFreehand
 * \brief Freehand line.
 * \ingroup ecma_draw_line
 */
function LineFreehand(guiAction) {
    Line.call(this, guiAction);

    this.pointList = [];
}

LineFreehand.prototype = new Line();

LineFreehand.State = {
    Idle : 0,
    Drawing : 1
};

LineFreehand.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineFreehand.State.Idle);
};

LineFreehand.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineFreehand.State.Idle:
        var trStart = qsTr("Press to start drawing");
        this.setCommandPrompt(trStart);
        this.setLeftMouseTip(trStart);
        this.setRightMouseTip(EAction.trCancel);
        this.pointList = [];
        break;

    case LineFreehand.State.Drawing:
        var trStop = qsTr("Release to stop drawing");
        this.setCommandPrompt(trStop);
        this.setLeftMouseTip(trStop);
        this.setRightMouseTip("");
        break;
    }
};

LineFreehand.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineFreehand.State.Idle:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

LineFreehand.prototype.mousePressEvent = function(event) {
    if (event.button() == Qt.LeftButton
            && event.modifiers().valueOf() != Qt.ControlModifier.valueOf()) {
        if (this.state == LineFreehand.State.Idle) {
            this.setState(LineFreehand.State.Drawing);
        }
    }
};

LineFreehand.prototype.mouseMoveEvent = function(event) {
    if (event.buttons().valueOf() & Qt.LeftButton.valueOf() &&
          event.modifiers().valueOf() != Qt.ControlModifier.valueOf()) {

        if (this.state == LineFreehand.State.Drawing) {
            this.pointList.push(event.getModelPosition());
            this.updatePreview();
        }
    }
};

LineFreehand.prototype.mouseReleaseEvent = function(event) {
    if (event.button() == Qt.LeftButton) {
        if (this.state == LineFreehand.State.Drawing) {
            var di = this.getDocumentInterface();
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
            this.setState(LineFreehand.State.Idle);
        }
    }

    Line.prototype.mouseReleaseEvent.call(this, event);
};

LineFreehand.prototype.getOperation = function(preview) {
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    op.setLimitPreview(false);

    for (var i=0; i<this.pointList.length-1; ++i) {
        var line = new RLineEntity(
            this.getDocument(),
            new RLineData(
                this.pointList[i],
                this.pointList[i+1]
            )
        );
        op.addObject(line);
    }

    return op;
};

