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
 * \class Circle2TP
 * \brief Circle tangential to three entities.
 * \ingroup ecma_draw_circle
 */
function Circle2TP(guiAction) {
    Circle.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;
    this.pos3 = undefined;

    this.center = undefined;
}

Circle2TP.prototype = new Circle();

Circle2TP.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1,
    SettingPoint : 2
};

Circle2TP.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(Circle2TP.State.ChoosingShape1);
};

Circle2TP.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Circle2TP.State.ChoosingShape1:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.center = undefined;
        var trFirstEntity = qsTr("First line, arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle2TP.State.ChoosingShape2:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.center = undefined;
        var trSecondEntity = qsTr("Second line, arc or circle");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Circle2TP.State.SettingPoint:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.pos3 = undefined;
        this.center = undefined;
        var trPoint = qsTr("Point on circle line");
        this.setCommandPrompt(trPoint);
        this.setLeftMouseTip(trPoint);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    }
};

Circle2TP.prototype.escapeEvent = function() {
    switch (this.state) {
    case Circle2TP.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Circle2TP.State.ChoosingShape2:
        this.setState(Circle2TP.State.ChoosingShape1);
        break;

    case Circle2TP.State.SettingPoint:
        this.setState(Circle2TP.State.ChoosingShape2);
        break;
    }
};

Circle2TP.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        if (preview) {
            this.updatePreview();
        }
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
    case Circle2TP.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle2TP.State.ChoosingShape2);
        }
        break;

    case Circle2TP.State.ChoosingShape2:
        this.entity2 = entity;
        this.shape2 = shape;
        this.pos2 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle2TP.State.SettingPoint);
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle2TP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Circle2TP.State.SettingPoint:
        this.pos3 = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(Circle2TP.State.ChoosingShape1);
            }
        }
        break;
    }
};

Circle2TP.prototype.getOperation = function(preview) {
    // temporary disabled:
    if (preview) return undefined;

    var shape = this.getCircle2TP(preview);

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
        qDebug("construction shape: ", s);
        var e = shapeToEntity(doc, s);
        if (!isNull(e)) {
            e.setColor(new RColor("blue"));
            op.addObject(e, false);
        }
    }

    return op;


//    if (!isEntity(entity)) {
//        return undefined;
//    }

//    return new RAddObjectOperation(entity);
};

Circle2TP.prototype.getCircle2TP = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) || isNull(this.pos3)) {
        return undefined;
    }

    var i,k,ips;

    var shape3 = new RPoint(this.pos3);

    Apollonius.constructionShapes = [];
    var candidates = Apollonius.getSolutions(this.shape1.data(), this.shape2.data(), shape3);

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

Circle2TP.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};


Circle2TP.prototype.getAuxPreview = function() {
    var ret = [];
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
