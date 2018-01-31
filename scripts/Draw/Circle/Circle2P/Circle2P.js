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

include("../Circle.js");

/**
 * \class Circle2P
 * \brief Circle from two diagonally opposite points.
 * \ingroup ecma_draw_circle
 */
function Circle2P(guiAction) {
    Circle.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;
}

Circle2P.prototype = new Circle();

Circle2P.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1
};

Circle2P.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(Circle2P.State.SettingPoint1);
};

Circle2P.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Circle2P.State.SettingPoint1:
        this.point1 = undefined;
        this.point2 = undefined;
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle2P.State.SettingPoint2:
        var trSecondPoint = qsTr("Second point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Circle2P.prototype.escapeEvent = function() {
    switch (this.state) {
    case Circle2P.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Circle2P.State.SettingPoint2:
        this.setState(Circle2P.State.SettingPoint1);
        break;
    }
};

Circle2P.prototype.pickCoordinate = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Circle2P.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.point1);
            this.setState(Circle2P.State.SettingPoint2);
        }
        break;

    case Circle2P.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.point2);
                this.setState(Circle2P.State.SettingPoint1);
            }
        }
        break;

    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle2P.prototype.getOperation = function(preview) {
    var shape = this.getCircle2P(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    var entity = new RCircleEntity(doc, new RCircleData(shape));

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

Circle2P.prototype.getCircle2P = function(preview) {
    if (isNull(this.point1) || isNull(this.point2)) {
        return undefined;
    }

    var distance = this.point1.getDistanceTo(this.point2);
    if (distance<RS.PointTolerance) {
        if (!preview) {
            this.error = qsTr("The two points are identical");
        }
        return undefined;
    }

    return RCircle.createFrom2Points(this.point1, this.point2);
};

