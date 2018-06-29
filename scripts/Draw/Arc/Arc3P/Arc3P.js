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

include("scripts/Draw/Arc/Arc.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Arc3P
 * \brief Arc from three points.
 * \ingroup ecma_draw_arc
 */
function Arc3P(guiAction) {
    Arc.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;
    this.point3 = undefined;
}

Arc3P.prototype = new Arc();

Arc3P.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1,
    SettingPoint3 : 2
};

Arc3P.prototype.beginEvent = function() {
    Arc.prototype.beginEvent.call(this);

    this.setState(Arc3P.State.SettingPoint1);
};

Arc3P.prototype.setState = function(state) {
    Arc.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Arc3P.State.SettingPoint1:
        this.point1 = undefined;
        this.point2 = undefined;
        this.point3 = undefined;
        var trStartPoint = qsTr("Start point");
        this.setCommandPrompt(trStartPoint);
        this.setLeftMouseTip(trStartPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Arc3P.State.SettingPoint2:
        this.point3 = undefined;
        var trPoint = qsTr("Point on arc");
        this.setCommandPrompt(trPoint);
        this.setLeftMouseTip(trPoint);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Arc3P.State.SettingPoint3:
        var trEndPoint = qsTr("End point");
        this.setCommandPrompt(trEndPoint);
        this.setLeftMouseTip(trEndPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Arc3P.prototype.escapeEvent = function() {
    switch (this.state) {
    case Arc3P.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Arc3P.State.SettingPoint2:
        this.setState(Arc3P.State.SettingPoint1);
        break;

    case Arc3P.State.SettingPoint3:
        this.setState(Arc3P.State.SettingPoint2);
        break;
    }
};

Arc3P.prototype.pickCoordinate = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Arc3P.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.point1);
            this.setState(Arc3P.State.SettingPoint2);
        }
        break;

    case Arc3P.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.point2);
            this.setState(Arc3P.State.SettingPoint3);
        }
        break;

    case Arc3P.State.SettingPoint3:
        this.point3 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.point3);
                this.setState(Arc3P.State.SettingPoint1);
            }
        }
        if (!preview && this.error.length!==0) {
            EAction.handleUserWarning(this.error);
        }
        break;
    }
};

Arc3P.prototype.getOperation = function(preview) {
    var shape = ShapeAlgorithms.createArcFrom3Points(this.point1, this.point2, this.point3);
    if (!preview) {
        this.error = ShapeAlgorithms.error;
    }

    if (isNull(shape)) {
        return undefined;
    }

    var entity;
    var doc = this.getDocument();

    if (isArcShape(shape)) {
        entity = new RArcEntity(doc, new RArcData(shape));
    }
    else if (isLineShape(shape)) {
        entity = new RLineEntity(doc, new RLineData(shape));
    }

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};
