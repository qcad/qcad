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
include("scripts/ShapeAlgorithms.js");


/**
 * \class Circle3P
 * \brief Circle from start point, point on circle line and end point.
 * \ingroup ecma_draw_circle
 */
function Circle3P(guiAction) {
    Circle.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;
    this.point3 = undefined;
}

Circle3P.prototype = new Circle();

Circle3P.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1,
    SettingPoint3 : 2
};

Circle3P.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(Circle3P.State.SettingPoint1);
};

Circle3P.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Circle3P.State.SettingPoint1:
        this.point1 = undefined;
        this.point2 = undefined;
        this.point3 = undefined;
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle3P.State.SettingPoint2:
        this.point2 = undefined;
        this.point3 = undefined;
        var trSecondPoint = qsTr("Second point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trBack);
        break;

   case Circle3P.State.SettingPoint3:
        this.point3 = undefined;
        var trThirdPoint = qsTr("Third point");
        this.setCommandPrompt(trThirdPoint);
        this.setLeftMouseTip(trThirdPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Circle3P.prototype.escapeEvent = function() {
    switch (this.state) {
    case Circle3P.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Circle3P.State.SettingPoint2:
        this.setState(Circle3P.State.SettingPoint1);
        break;

    case Circle3P.State.SettingPoint3:
        this.setState(Circle3P.State.SettingPoint2);
        break;
    }
};

Circle3P.prototype.pickCoordinate = function(event, preview) {
    this.error = undefined;
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Circle3P.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.point1);
            this.setState(Circle3P.State.SettingPoint2);
        }
        break;

    case Circle3P.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.point2);
            this.setState(Circle3P.State.SettingPoint3);
            this.error = undefined;
        }
        break;

    case Circle3P.State.SettingPoint3:
        this.point3 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.point3);
                this.setState(Circle3P.State.SettingPoint1);
            }
        }
        break;

    }

    if (!preview && !isNull(this.error)) {
        EAction.handleUserWarning(this.error);
    }
};

Circle3P.prototype.getOperation = function(preview) {
    var shape = ShapeAlgorithms.createCircleFrom3Points(this.point1, this.point2, this.point3);
    if (!preview) {
        this.error = ShapeAlgorithms.error;
    }

    if (isNull(shape)) {
        return undefined;
    }

    var entity;
    var doc = this.getDocument();

    if (isCircleShape(shape)) {
        entity = new RCircleEntity(doc, new RCircleData(shape));
    }
    else if (isLineShape(shape)) {
        entity = new RLineEntity(doc, new RLineData(shape));
    }

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

