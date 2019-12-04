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
 * \class LineTangent1
 * \brief Line tangential to arc, circle or ellipse.
 * \ingroup ecma_draw_line
 */
function LineTangent1(guiAction) {
    Line.call(this, guiAction);

    // chosen arc, circle, ellipse, polyline, ... entity to draw the tangent to:
    this.entity = undefined;
    // shape within chosen polyline or shape of entity self:
    this.shape = undefined;
    // start point of line:
    this.pos1 = undefined;
    // click point when choosing arc, circle or ellipse:
    this.pos2 = undefined;

    this.setUiOptions("../Line.ui");
}

LineTangent1.prototype = new Line();

LineTangent1.State = {
    SettingPos : 0,
    ChoosingEntity : 1
};

LineTangent1.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineTangent1.State.SettingPos);
};

LineTangent1.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineTangent1.State.SettingPos:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        tr = qsTr("Choose start point of tangent");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        this.entity = undefined;
        this.shape = undefined;
        this.pos1 = undefined;
        this.pos2 = undefined;
        EAction.showSnapTools();
        break;
    case LineTangent1.State.ChoosingEntity:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        tr = qsTr("Choose circle, arc or ellipse");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trBack);
        //EAction.showMainTools();
        break;
    }

};

LineTangent1.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineTangent1.State.SettingPos:
        EAction.prototype.escapeEvent.call(this);
        break;
    case LineTangent1.State.ChoosingEntity:
        this.setState(LineTangent1.State.SettingPos);
        break;
    }
};

LineTangent1.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case LineTangent1.State.SettingPos:
        this.pos1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.pos1);
            //di.repaintViews();
            this.setState(LineTangent1.State.ChoosingEntity);
        }
        break;
    }
};

LineTangent1.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.entity = undefined;
        this.shape = undefined;
        return;
    }

    switch (this.state) {
    case LineTangent1.State.ChoosingEntity:
        var shape = entity.getClosestSimpleShape(pos);

        if (isArcShape(shape) ||
            isCircleShape(shape) ||
            isEllipseShape(shape)) {

            this.entity = entity;
            this.shape = shape;
            this.pos2 = pos;
        }
        else {
            this.entity = undefined;
            this.shape = undefined;
            this.pos2 = undefined;
            if (!preview) {
                EAction.warnNotArcCircleEllipse();
            }
            break;
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                if (this.error.length==0) {
                    this.setState(LineTangent1.State.SettingPos);
                }
            }
            else {
                EAction.handleUserWarning(
                    qsTr("No tangent possible.")
                );
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

LineTangent1.prototype.getOperation = function(preview) {
    if (isNull(this.pos1) || isNull(this.pos2) ||
        isNull(this.entity) || isNull(this.shape)) {

        return undefined;
    }

    var doc = this.getDocument();

    var tangent;
    var tangents = this.shape.getTangents(this.pos1);
    if (tangents.length===0) {
        if (!preview) {
            this.error = qsTr("Cannot draw tangent from point inside circle to circle")
        }
    }
    else {
        if (tangents.length!==2 ||
                tangents[0].getDistanceTo(this.pos2) < tangents[1].getDistanceTo(this.pos2)) {

            tangent = tangents[0];
        }
        else {
            tangent = tangents[1];
        }
    }

    if (isNull(tangent)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    op.addObject(this.createLineEntity(doc, tangent.getStartPoint(), tangent.getEndPoint()));
    return op;
};

LineTangent1.prototype.getTangentArcOrCircle = function(arcOrCircle, preview) {
    var doc = this.getDocument();

    // create temporary thales circle:
    var thalesCenter = this.pos1.operator_add(arcOrCircle.getCenter()).operator_divide(2.0);
    var thalesRadius = this.pos1.getDistanceTo(thalesCenter);

    if (thalesRadius<arcOrCircle.getRadius()/2.0) {
        if (!preview) {
            this.error = qsTr("Cannot draw tangent from point inside circle to circle");
        }
        return undefined;
    }

    var thalesCircle = new RCircle(thalesCenter, thalesRadius);

    // get the two intersection points which are the tangent points:
    var ips = thalesCircle.getIntersectionPoints(
            arcOrCircle.data(),
            false
    );

    if (ips.length>0) {
        var tangent1 = new RLine(this.pos1, ips[0]);
        if (ips.length>1) {
            var tangent2 = new RLine(this.pos1, ips[1]);
            if (tangent1.getDistanceTo(this.pos2) <
                    tangent2.getDistanceTo(this.pos2)) {
                return tangent1;
            }
            else {
                return tangent2;
            }
        }
        else {
            return tangent1;
        }
    }
    else {
        return undefined;
    }
};

LineTangent1.prototype.getAuxPreview = function() {
    var ret = [];

    if (isArcShape(this.shape)) {
        ret.push(new RCircle(this.shape.getCenter(), this.shape.getRadius()));
    }
    else if (isEllipseShape(this.shape)) {
        var ellipse = this.shape.clone();
        ellipse.setStartParam(0.0);
        ellipse.setEndParam(2*Math.PI);
        ret.push(ellipse);
    }

    return ret;
};

LineTangent1.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

