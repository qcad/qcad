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

include("../Line.js");

/**
 * \class LineTangent2
 * \brief Line tangential to two arcs or circles.
 * \ingroup ecma_draw_line
 */
function LineTangent2(guiAction) {
    Line.call(this, guiAction);

    // first entity (circle, arc, polyline, ...):
    this.entity1 = undefined;
    // shape within chosen polyline or shape of entity self:
    this.shape1 = undefined;
    // click position when choosing first entity:
    this.pos1 = undefined;

    // second entity (circle, arc, polyline, ...):
    this.entity2 = undefined;
    // shape within chosen polyline or shape of entity self:
    this.shape2 = undefined;
    // click position when choosing second entity:
    this.pos2 = undefined;
}

LineTangent2.prototype = new Line();

LineTangent2.State = {
    ChoosingEntity1 : 0,
    ChoosingEntity2 : 1
};

LineTangent2.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineTangent2.State.ChoosingEntity1);
};

LineTangent2.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineTangent2.State.ChoosingEntity1:
        this.setLeftMouseTip(qsTr("Choose first circle or arc"));
        this.setRightMouseTip(EAction.trCancel);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.pos1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.pos2 = undefined;
        break;
    case LineTangent2.State.ChoosingEntity2:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.setLeftMouseTip(qsTr("Choose second circle or arc"));
        this.setRightMouseTip(EAction.trBack);
        break;
    }

};

LineTangent2.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineTangent2.State.ChoosingEntity1:
        EAction.prototype.escapeEvent.call(this);
        break;
    case LineTangent2.State.ChoosingEntity2:
        this.setState(LineTangent2.State.ChoosingEntity1);
        break;
    }
};

LineTangent2.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    var shape = entity.getClosestShape(pos);

    if (isArcShape(shape) ||
        isCircleShape(shape)) {

        if (this.state===LineTangent2.State.ChoosingEntity1) {
            this.entity1 = entity;
            this.shape1 = shape;
            this.pos1 = pos;
            if (!preview) {
                this.setState(LineTangent2.State.ChoosingEntity2);
                return;
            }
        }
        else {
            this.entity2 = entity;
            this.shape2 = shape;
            this.pos2 = pos;
        }
    }
    else {
        // handle error:
        if (!preview) {
            EAction.warnNotArcCircle();
        }
        if (this.state===LineTangent2.State.ChoosingEntity1) {
            this.entity1 = undefined;
            this.shape1 = undefined;
            this.pos1 = undefined;
        }
        else {
            this.entity2 = undefined;
            this.shape2 = undefined;
            this.pos2 = undefined;
        }
    }

    if (preview) {
        this.updatePreview();
    }
    else {
        if (this.state===LineTangent2.State.ChoosingEntity2) {
            var op = this.getOperation(preview);
            if (!isNull(op)) {
                di.applyOperation(op);
                if (this.error.length===0) {
                    this.setState(LineTangent2.State.ChoosingEntity1);
                }
            }
        }
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

LineTangent2.prototype.getHighlightedEntities = function() {
    var ret = new Array();
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};

LineTangent2.prototype.getAuxPreview = function() {
    var ellipse;
    
    var ret = new Array();

    if (isArcShape(this.shape1)) {
        ret.push(new RCircle(this.shape1.getCenter(), this.shape1.getRadius()));
    }
    else if (isEllipseShape(this.shape1)) {
        ellipse = this.shape1.clone();
        ellipse.setStartParam(0.0);
        ellipse.setEndParam(2*Math.PI);
        ret.push(ellipse);
    }

    if (isArcShape(this.shape2)) {
        ret.push(new RCircle(this.shape2.getCenter(), this.shape2.getRadius()));
    }
    else if (isEllipseShape(this.shape2)) {
        ellipse = this.shape2.clone();
        ellipse.setStartParam(0.0);
        ellipse.setEndParam(2*Math.PI);
        ret.push(ellipse);
    }

    return ret;
};

LineTangent2.prototype.getOperation = function(preview) {
    if (isNull(this.pos1) || isNull(this.pos2) ||
        isNull(this.entity1) || isNull(this.entity2) ||
        isNull(this.shape1) || isNull(this.shape2)) {

        return undefined;
    }

    var doc = this.getDocument();

    var tangent = this.getTangent();

    if (isNull(tangent)) {
        if (!preview) {
            this.error = qsTr("No tangent possible");
        }
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.addObject(new RLineEntity(doc, new RLineData(tangent)));
    return op;
};

LineTangent2.prototype.getTangent = function() {
    var ret, offs1, offs2;
    
    var doc = this.getDocument();

    var circleCenter1 = this.shape1.getCenter();
    var circleRadius1 = this.shape1.getRadius();
    var circleCenter2 = this.shape2.getCenter();
    var circleRadius2 = this.shape2.getRadius();

    // create all four possible tangents:
    var tangents = new Array();

    var angle1 = circleCenter1.getAngleTo(circleCenter2);
    var dist1 = circleCenter1.getDistanceTo(circleCenter2);

    if (dist1<1.0e-6) {
        return undefined;
    }

    // outer tangents:
    var dist2 = circleRadius2 - circleRadius1;
    if (dist1>dist2) {
        var angle2 = Math.asin(dist2/dist1);
        var angt1 = angle1 + angle2 + Math.PI/2.0;
        var angt2 = angle1 - angle2 - Math.PI/2.0;
        offs1 = new RVector();
        offs2 = new RVector();

        offs1.setPolar(circleRadius1, angt1);
        offs2.setPolar(circleRadius2, angt1);

        tangents.push(new RLine(circleCenter1.operator_add(offs1),
                                circleCenter2.operator_add(offs2)));

        offs1.setPolar(circleRadius1, angt2);
        offs2.setPolar(circleRadius2, angt2);

        tangents.push(new RLine(circleCenter1.operator_add(offs1),
                                circleCenter2.operator_add(offs2)));
    }

    // inner tangents:
    var dist3 = circleRadius2 + circleRadius1;
    if (dist1>dist3) {
        var angle3 = Math.asin(dist3/dist1);
        var angt3 = angle1 + angle3 + Math.PI/2.0;
        var angt4 = angle1 - angle3 - Math.PI/2.0;
        offs1 = new RVector();
        offs2 = new RVector();

        offs1.setPolar(circleRadius1, angt3);
        offs2.setPolar(circleRadius2, angt3);

        tangents.push(new RLine(circleCenter1.operator_subtract(offs1),
                                circleCenter2.operator_add(offs2)));

        offs1.setPolar(circleRadius1, angt4);
        offs2.setPolar(circleRadius2, angt4);

        tangents.push(new RLine(circleCenter1.operator_subtract(offs1),
                                circleCenter2.operator_add(offs2)));
    }

    // find closest tangent:
    var minDist;
    var dist;
    var idx = -1;
    for (var i=0; i<tangents.length; ++i) {
        dist = tangents[i].getDistanceTo(this.pos2, false);
        if (isNull(minDist) || dist<minDist) {
            minDist = dist;
            ret = tangents[i];
        }
    }

    return ret;
};

