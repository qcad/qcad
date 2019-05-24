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
 * \class InfoDistancePP
 * \ingroup ecma_information
 * \brief Measure distance from point to point.
 */
function InfoDistancePP(guiAction) {
    Information.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;

    this.setUiOptions(InfoDistancePP.includeBasePath + "/../Information.ui");
}

InfoDistancePP.prototype = new Information();
InfoDistancePP.includeBasePath = includeBasePath;

InfoDistancePP.State = {
    SettingFirstPoint : 0,
    SettingSecondPoint : 1
};

InfoDistancePP.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.setState(InfoDistancePP.State.SettingFirstPoint);
};

InfoDistancePP.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    di.setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoDistancePP.State.SettingFirstPoint:
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case InfoDistancePP.State.SettingSecondPoint:
        this.point2 = undefined;
        var trSecondPoint = qsTr("Second point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

InfoDistancePP.prototype.escapeEvent = function() {
    switch (this.state) {
    case InfoDistancePP.State.SettingFirstPoint:
        EAction.prototype.escapeEvent.call(this);
        break;
    case InfoDistancePP.State.SettingSecondPoint:
        this.setState(InfoDistancePP.State.SettingFirstPoint);
        break;
    }
};

InfoDistancePP.prototype.pickCoordinate = function(event, preview) {
    var appWin = EAction.getMainWindow();
    var di = this.getDocumentInterface();
    var op;

    switch (this.state) {
    case InfoDistancePP.State.SettingFirstPoint:
        if (!preview) {
            this.point1 = event.getModelPosition();
            this.point2 = undefined;
            di.setRelativeZero(this.point1);
            this.setState(InfoDistancePP.State.SettingSecondPoint);
        }
        break;

    case InfoDistancePP.State.SettingSecondPoint:
        this.point2 = event.getModelPosition();

        if (this.addToDrawing) {
            op = this.getOperation(preview);
            if (preview) {
                di.previewOperation(op);
            }
            else {
                di.applyOperation(op);
                di.setRelativeZero(this.point2);
            }
        }

        if (!preview) {
            var line = new RLine(this.point1, this.point2);
            var distance = line.getLength();
            var resultMessage = qsTr("Distance:") + " " + this.formatLinearResultCmd(distance);
            var dx = Math.abs(line.getEndPoint().x - line.getStartPoint().x);
            var dy = Math.abs(line.getEndPoint().y - line.getStartPoint().y);
            var angle = line.getAngle();
            resultMessage += ",\n" + qsTr("Delta X:") + " " + this.formatLinearResultCmd(dx);
            resultMessage += ",\n" + qsTr("Delta Y:") + " " + this.formatLinearResultCmd(dy);
            resultMessage += ",\n" + qsTr("Angle:") + " " + this.formatAngularResultCmd(angle);
            if (this.autoTerminate) {
                this.updateLineEdit(distance);
                this.setNoState(false);
                this.terminate();
                return;
            }
            else {
                this.setState(InfoDistancePP.State.SettingFirstPoint);
            }
            appWin.handleUserInfo(resultMessage);
        }
        break;
    }

    // keep showing preview after 2nd point has been set:
    if (!this.addToDrawing) {
        if (!isNull(this.point1) && !isNull(this.point2)) {
            op = this.getOperation(preview);
            if (preview) {
                di.previewOperation(op);
            }
            else {
                op.destroy();
            }
        }
    }
};

InfoDistancePP.prototype.getOperation = function(preview) {
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    this.addInfoLine(op, this.point1, this.point2, preview);
    return op;
};
