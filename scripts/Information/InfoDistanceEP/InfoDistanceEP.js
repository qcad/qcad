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
 * \class InfoDistanceEP
 * \ingroup ecma_information
 * \brief Measure distance from entity to point.
 */
function InfoDistanceEP(guiAction) {
    Information.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    this.point1 = undefined;
    this.point2 = undefined;

    this.setUiOptions(InfoDistanceEP.includeBasePath + "/../Information.ui");
}

InfoDistanceEP.prototype = new Information();
InfoDistanceEP.includeBasePath = includeBasePath;

InfoDistanceEP.State = {
    SettingShape : 0,
    SettingPoint : 1
};

InfoDistanceEP.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.setState(InfoDistanceEP.State.SettingShape);
};

InfoDistanceEP.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoDistanceEP.State.SettingShape:
        di.setClickMode(RAction.PickEntity);
        var trFirstPoint = qsTr("Specify entity");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case InfoDistanceEP.State.SettingPoint:
        this.point2 = undefined;
        di.setClickMode(RAction.PickCoordinate);
        var trSecondPoint = qsTr("Specify point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    this.setCrosshairCursor();
    EAction.showSnapTools();
};

InfoDistanceEP.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    // keep showing preview after 2nd point has been set:
    if (!this.addToDrawing) {
        if (!isNull(this.point1) && !isNull(this.point2)) {
            var op = this.getOperation(preview);
            if (preview) {
                di.previewOperation(op);
            }
            else {
                op.destroy();
            }
        }
    }

    if (isNull(entity)) {
        return;
    }

    this.entity = entity;
    di.highlightEntity(this.entity.getId());

    if (!preview) {
        this.shape = entity.getClosestSimpleShape(pos);
        this.setState(InfoDistanceEP.State.SettingPoint);
    }
};

InfoDistanceEP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    if (isNull(this.shape)) {
        return;
    }

    this.point2 = event.getModelPosition();

    if (!isValidVector(this.point2)) {
        return;
    }

    this.point1 = this.shape.getClosestPointOnShape(this.point2, false);

    if (!isValidVector(this.point1)) {
        return;
    }

    di.highlightEntity(this.entity.getId());

    var op = this.getOperation(preview);
    if (preview) {
        di.previewOperation(op);
    }
    else {
        if (this.addToDrawing) {
            di.applyOperation(op);
            di.setRelativeZero(this.point2);
        }
        else {
            op.destroy();
        }
    }

    if (!preview) {
        var distance = this.point1.getDistanceTo(this.point2);
        EAction.getMainWindow().handleUserInfo(qsTr("Distance:") + " " + this.formatLinearResultCmd(distance));

        if (this.autoTerminate) {
            this.updateLineEdit(distance);
            this.setNoState(false);
            this.terminate();
            return;
        }
        else {
            this.setState(InfoDistanceEP.State.SettingShape);
        }
    }
};

InfoDistanceEP.prototype.getOperation = function(preview) {
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    this.addInfoLine(op, this.point1, this.point2, preview);
    return op;
};
