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

include("scripts/Information/Information.js");

/**
 * \class InfoPosition
 * \ingroup ecma_information
 * \brief Query point position.
 */
function InfoPosition(guiAction) {
    Information.call(this, guiAction);
    this.pos = undefined;
    this.lastPos = undefined;
    this.setUiOptions("../Information.ui");
}

InfoPosition.prototype = new Information();

InfoPosition.State = {
    SettingPoint : 0
};

InfoPosition.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.setState(InfoPosition.State.SettingPoint);
};

InfoPosition.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    di.setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoPosition.State.SettingPoint:
        var tsPoint = qsTr("Point");
        this.setCommandPrompt(tsPoint);
        this.setLeftMouseTip(tsPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

InfoPosition.prototype.escapeEvent = function() {
    switch (this.state) {
    case InfoPosition.State.SettingPoint:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

InfoPosition.prototype.getDisplayedLabel = function(p, prec) {
    if (isNull(prec)) {
        prec = 4;
    }

    return coordinateToString(p, prec, false, false, this.getDocument());
};

InfoPosition.prototype.pickCoordinate = function(event, preview) {
    var appWin = EAction.getMainWindow();
    var di = this.getDocumentInterface();

    switch (this.state) {
    case InfoPosition.State.SettingPoint:
        this.pos = event.getModelPosition();
        if (!preview) {
            this.lastPos = this.pos;
        }

        var op = this.getOperation(preview);

        if (!preview) {
            appWin.handleUserInfo(this.getDisplayedLabel(this.pos, 8));
            if (!isNull(op)) {
                if (this.addToDrawing) {
                    di.applyOperation(op);
                }
                else {
                    op.destroy();
                }
            }
        }
        else {
            di.previewOperation(op);
        }

        break;
    }
};

InfoPosition.prototype.getOperation = function(preview) {
    if (isNull(this.pos)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var di = this.getDocumentInterface();
    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();
    view.clearTextLabels();

    this.addShape(op, new RPoint(this.pos), preview);

    var label = this.getDisplayedLabel(this.pos);
    this.addTextLabel(op, view, this.pos, label, preview);

    if (preview && !this.addToDrawing && !isNull(this.lastPos)) {
        label = this.getDisplayedLabel(this.lastPos);
        this.addTextLabel(op, view, this.lastPos, label, preview);
        this.addShape(op, new RPoint(this.lastPos), preview);
    }

    return op;
};
