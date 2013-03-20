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

include("../Information.js");

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
}

InfoAngle.prototype = new Information();

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
        this.setRightMouseTip(qsTr("Done"));
        break;
    }

    EAction.showSnapTools();
};

InfoAngle.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var pos = event.getModelPosition();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);

//    if (isNull(entity)) {
//        switch (this.state) {
//        case InfoAngle.State.SettingFirstShape:
//            this.entity1 = undefined;
//            break;
//        case InfoAngle.State.SettingSecondShape:
//            di.highlightEntity(this.entity1.getId());
//            this.entity2 = undefined;
//            break;
//        }
//        return;
//    }

    //if (preview) {
        this.updatePreview();
    //}

    if (isNull(entity)) {
        return;
    }

    var shape;

    switch (this.state) {
    case InfoAngle.State.SettingFirstShape:
        shape = entity.getClosestShape(pos);

        if (isLineShape(shape)) {
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
        shape = entity.getClosestShape(pos);

        if (isLineShape(shape)) {
            this.entity2 = entity;
            this.shape2 = shape;
            this.point2 = this.shape2.getClosestPointOnShape(pos);
            this.position = pos;
            di.highlightEntity(this.entity2.getId());
        }

        if (!preview) {
            this.setState(InfoAngle.State.SettingFirstShape);
            if (!isNull(this.arc)) {
                //var angleText = RMath.angleToString(this.arc.getAngleLength());
                var angleText = this.formatAngularResultCmd(this.arc.getAngleLength());
                EAction.getMainWindow().handleUserInfo(qsTr("Angle:") + " " + angleText);
            }
        }
        break;
    }
    
    //this.updatePreview();
};

InfoAngle.prototype.addMeasuringArc = function(center) {
    var di = this.getDocumentInterface();
    var a1 = center.getAngleTo(this.point1);
    var a2 = center.getAngleTo(this.point2);
    var r = center.getDistanceTo(this.position);
    var posAngle = center.getAngleTo(this.position);
    var reversed = RMath.isAngleBetween(posAngle, a1, a2, true);

    this.arc = new RArc(center, r, a1, a2, reversed);
    this.addShape(this.arc);

    // add label:
    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();
    var dx = view.mapDistanceFromView(10);
    var dy = view.mapDistanceFromView(30);
    //var label = sprintf("%0.3f°", RMath.angleToString(this.arc.getAngleLength()));
    var label = this.formatAngularResult(this.arc.getAngleLength());
    view.clearTextLabels();
    view.addTextLabel(new RTextLabel(new RVector(this.point2.x + dx, this.point2.y + dy), label));
};

InfoAngle.prototype.updatePreview = function() {
    if (isNull(this.shape1) || isNull(this.shape2) ||
        isNull(this.point1) || isNull(this.point2)) {
        return;
    }

    var sol = this.shape1.getIntersectionPoints(this.shape2.data(), false);
    if (!isNull(sol) && sol.length > 0) {
        var intersection = sol[0];
        if (intersection.isValid()) {
            var angle1 = intersection.getAngleTo(this.point1);
            var angle2 = intersection.getAngleTo(this.point2);
            var angle = RMath.getAngleDifference(angle1, angle2);
            this.addMeasuringArc(intersection);
        }
        this.noAngle = false;
    } else {
        this.noAngle = true;
    }
};

