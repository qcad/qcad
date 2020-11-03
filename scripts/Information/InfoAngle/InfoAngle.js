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
 * \class InfoAngle
 * \ingroup ecma_information
 * \brief Measure angle.
 */
function InfoAngle(guiAction) {
    Information.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.point1 = undefined;

    this.entity2 = undefined;
    this.shape2 = undefined;
    this.point2 = undefined;

    this.arc = undefined;
    this.position = undefined;

    this.setUiOptions(InfoAngle.includeBasePath + "/../Information.ui");
}

InfoAngle.prototype = new Information();
InfoAngle.includeBasePath = includeBasePath;

InfoAngle.State = {
    SettingFirstShape : 0,
    SettingSecondShape : 1
};

InfoAngle.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.setState(InfoAngle.State.SettingFirstShape);
}

InfoAngle.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    di.setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoAngle.State.SettingFirstShape:
        var trFirstLine = qsTr("Specify first line");
        this.setCommandPrompt(trFirstLine);
        this.setLeftMouseTip(trFirstLine);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case InfoAngle.State.SettingSecondShape:
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.point2 = undefined;
        var trSecondLine = qsTr("Specify second line");
        this.setCommandPrompt(trSecondLine);
        this.setLeftMouseTip(trSecondLine);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

InfoAngle.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var pos = event.getModelPosition();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var op;

    if (!this.isEntitySnappable(entity)) {
        // entity not on a snappable layer:
        return;
    }

    // keep showing preview after 2nd entity has been set:
    if (!this.addToDrawing) {
        op = this.getOperation(preview);
        if (!isNull(op)) {
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

    var shape;

    switch (this.state) {
    case InfoAngle.State.SettingFirstShape:
        shape = entity.getClosestSimpleShape(pos);

        if (isLineBasedShape(shape)) {
            if (!preview) {
                this.entity1 = entity;
                this.shape1 = shape;
                this.point1 = this.shape1.getClosestPointOnShape(pos);
            }
            else {
                di.highlightEntity(entity.getId());
            }
        }
        else {
            if (!preview) {
                EAction.warnNotLine();
            }
            break;
        }

        if (!preview) {
            this.setState(InfoAngle.State.SettingSecondShape);
        }
        break;

    case InfoAngle.State.SettingSecondShape:
        di.highlightEntity(this.entity1.getId());
        shape = entity.getClosestSimpleShape(pos);

        if (isLineBasedShape(shape)) {
            this.entity2 = entity;
            this.shape2 = shape;
            this.point2 = this.shape2.getClosestPointOnShape(pos);
            this.position = pos;
            di.highlightEntity(this.entity2.getId());
        }

        op = this.getOperation(preview);
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

            if (!isNull(this.arc)) {
                var value = this.arc.getAngleLength();
                var angleText = this.formatAngularResultCmd(value);
                EAction.getMainWindow().handleUserInfo(qsTr("Angle:") + " " + angleText);

                if (this.autoTerminate) {
                    this.updateLineEdit(RMath.rad2deg(value));
                    this.setNoState(false);
                    this.terminate();
                    return;
                }
                else {
                    this.setState(InfoAngle.State.SettingFirstShape);
                }
            }
            else {
                this.setState(InfoAngle.State.SettingFirstShape);
            }
        }
        break;
    }
};

InfoAngle.prototype.addMeasuringArc = function(op, center, preview) {
    var di = this.getDocumentInterface();
    var a1 = center.getAngleTo(this.point1);
    var a2 = center.getAngleTo(this.point2);
    var r = center.getDistanceTo(this.position);
    var posAngle = center.getAngleTo(this.position);
    var reversed = RMath.isAngleBetween(posAngle, a1, a2, true);

    this.arc = new RArc(center, r, a1, a2, reversed);
    this.addShape(op, this.arc, preview);

    // add label:
    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();
    var label = this.formatAngularResult(this.arc.getAngleLength());
    view.clearTextLabels();
    this.addTextLabel(op, view, this.point2, label, preview);
};

InfoAngle.prototype.getOperation = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) ||
        isNull(this.point1) || isNull(this.point2)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var sol = this.shape1.getIntersectionPoints(this.shape2.data(), false);
    if (!isNull(sol) && sol.length > 0) {
        var intersection = sol[0];
        if (intersection.isValid()) {
            var angle1 = intersection.getAngleTo(this.point1);
            var angle2 = intersection.getAngleTo(this.point2);
            var angle = RMath.getAngleDifference(angle1, angle2);
            this.addMeasuringArc(op, intersection, preview);
        }
        this.noAngle = false;
    } else {
        this.noAngle = true;
    }

    return op;
};
