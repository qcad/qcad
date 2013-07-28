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

include("../Circle.js");
include("scripts/Apollonius.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class CircleT2P
 * \brief Circle tangential to entity, through 2 points.
 * \ingroup ecma_draw_circle
 */
function CircleT2P(guiAction) {
    Circle.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;
    this.pos2 = undefined;
    this.pos3 = undefined;

    this.center = undefined;
}

CircleT2P.prototype = new Circle();

CircleT2P.State = {
    ChoosingShape : 0,
    SettingPoint1 : 1,
    SettingPoint2 : 2
};

CircleT2P.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(CircleT2P.State.ChoosingShape);
};

CircleT2P.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case CircleT2P.State.ChoosingShape:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.center = undefined;
        var trFirstEntity = qsTr("Line, arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case CircleT2P.State.SettingPoint1:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.pos2 = undefined;
        this.center = undefined;
        var trFirstPoint = qsTr("First point on circle line");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;

    case CircleT2P.State.SettingPoint2:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.pos3 = undefined;
        this.center = undefined;
        var trSecondPoint = qsTr("Second point on circle line");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    }
};

CircleT2P.prototype.escapeEvent = function() {
    switch (this.state) {
    case CircleT2P.State.ChoosingShape:
        EAction.prototype.escapeEvent.call(this);
        break;

    case CircleT2P.State.SettingPoint1:
        this.setState(CircleT2P.State.ChoosingShape);
        break;

    case CircleT2P.State.SettingPoint2:
        this.setState(CircleT2P.State.SettingPoint1);
        break;
    }
};

CircleT2P.prototype.pickEntity = function(event, preview) {
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

    if (!preview) {
        if (!isLineShape(shape) &&
            !isArcShape(shape) &&
            !isCircleShape(shape)) {

            EAction.warnNotLineArcCircle();
            return;
        }
    }

    switch (this.state) {
    case CircleT2P.State.ChoosingShape:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(CircleT2P.State.SettingPoint1);
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

CircleT2P.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case CircleT2P.State.SettingPoint1:
        this.pos2 = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(CircleT2P.State.SettingPoint2);
        }
        break;

    case CircleT2P.State.SettingPoint2:
        this.pos3 = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(CircleT2P.State.ChoosingShape);
            }
        }
        break;
    }
};

CircleT2P.prototype.getOperation = function(preview) {
    // temporary disabled:
    if (preview) return undefined;

    var shape = this.getCircleT2P(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    //var entity = new RCircleEntity(doc, new RCircleData(shape));

    var op = new RAddObjectsOperation();
    for (var i=0; i<shape.length; i++) {
        // ignore lines:
        if (!isCircleShape(shape[i])) {
            continue;
        }

        var entity = new RCircleEntity(doc, new RCircleData(shape[i]));
        op.addObject(entity);
    }

    for (var k=0; k<Apollonius.constructionShapes.length; k++) {
        var s = Apollonius.constructionShapes[k];
        var e = shapeToEntity(doc, s);
        e.setColor(new RColor("blue"));
        op.addObject(e, false);
    }

    return op;
};

CircleT2P.prototype.getCircleT2P = function(preview) {
    if (isNull(this.shape1) || isNull(this.pos2) || isNull(this.pos3)) {
        return undefined;
    }

    var i,k,ips;

    var shape2 = new RPoint(this.pos2);
    var shape3 = new RPoint(this.pos3);

    Apollonius.constructionShapes = [];
    var candidates = Apollonius.getSolutions(this.shape1.data(), shape2, shape3);

    if (!preview) {
        qDebug("candidates: ", candidates);
    }

    if (candidates.length===0) {
        if (!preview) {
            this.error = qsTr("No solution");
        }
        return undefined;
    }

    var minDist = -1;
    var circle = undefined;
    for (i=0; i<candidates.length; i++) {
        var c = candidates[i];
        var dist = c.getDistanceTo(this.pos3);
        if (minDist<0 || dist<minDist) {
            minDist = dist;
            circle = c;
            this.center = c.center;
        }
    }

    //return circle;
    return candidates;
};

CircleT2P.prototype.getHighlightedEntities = function() {
    var ret = new Array();
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    return ret;
};


CircleT2P.prototype.getAuxPreview = function() {
    var ret = new Array();
    /*
    var a;

    if (isVector(this.center)) {
        if (isArcShape(this.shape1)) {
            a = this.shape1.getCenter().getAngleTo(this.center);
            if (!this.shape1.isAngleWithinArc(a)) {
                ret.push(new RCircle(this.shape1.getCenter(), this.shape1.getRadius()));
            }
        }
        if (isArcShape(this.shape2)) {
            a = this.shape2.getCenter().getAngleTo(this.center);
            if (!this.shape2.isAngleWithinArc(a)) {
                ret.push(new RCircle(this.shape2.getCenter(), this.shape2.getRadius()));
            }
        }
    }
    */

    return ret;
};
