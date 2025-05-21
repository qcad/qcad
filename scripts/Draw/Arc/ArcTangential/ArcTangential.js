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

/**
 * \class ArcTangential
 * \brief Arc tangentially connected to a line or arc.
 * \ingroup ecma_draw_arc
 */
function ArcTangential(guiAction) {
    Arc.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    this.appendToStartPoint = undefined;
    this.pos = undefined;
    this.radius = undefined;

    this.setUiOptions("ArcTangential.ui");
}

ArcTangential.prototype = new Arc();

ArcTangential.State = {
    ChoosingBaseEntity : 0,
    SettingEndPoint : 1
};

ArcTangential.prototype.beginEvent = function() {
    Arc.prototype.beginEvent.call(this);

    this.setState(ArcTangential.State.ChoosingBaseEntity);
};

ArcTangential.prototype.setState = function(state) {
    Arc.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ArcTangential.State.ChoosingBaseEntity:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity = undefined;
        this.shape = undefined;
        this.pos = undefined;
        this.appendToStartPoint = undefined;
        tr = qsTr("Choose base line or base arc");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case ArcTangential.State.SettingEndPoint:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        tr = qsTr("Choose end point of arc");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        EAction.showSnapTools();
        break;
    }

};

ArcTangential.prototype.escapeEvent = function() {
    switch (this.state) {
    case ArcTangential.State.ChoosingBaseEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    case ArcTangential.State.SettingEndPoint:
        this.setState(ArcTangential.State.ChoosingBaseEntity);
        break;
    }
};

ArcTangential.prototype.pickEntity = function(event, preview) {
    var appWin;
    
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (!isEntity(entity)) {
        return;
    }

    this.shape = this.getShape(entity, pos);

    switch (this.state) {
    case ArcTangential.State.ChoosingBaseEntity:
        if (this.isSupportedShape(this.shape)) {
            this.entity = entity;

            var startPoint;
            if (this.shape.getStartPoint().getDistanceTo(pos) <
                this.shape.getEndPoint().getDistanceTo(pos)) {

                this.appendToStartPoint = true;
                startPoint = this.shape.getStartPoint();
            } else {
                this.appendToStartPoint = false;
                startPoint = this.shape.getEndPoint();
            }
            if (preview) {
                this.updatePreview();
            }
            else {
                di.setRelativeZero(startPoint);
                this.setState(ArcTangential.State.SettingEndPoint);
            }
        }
        else {
            if (!preview) {
                EAction.warnNotLineArc();
            }
            this.entity = undefined;
            this.shape = undefined;
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

ArcTangential.prototype.getShape = function(entity, pos) {
    return entity.castToShape();
};

ArcTangential.prototype.isSupportedShape = function(shape) {
    return isLineShape(shape) || isArcShape(shape);
};

ArcTangential.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ArcTangential.State.SettingEndPoint:
        this.pos = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.pos);
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                if (this.error.length===0) {
                    this.setState(ArcTangential.State.ChoosingBaseEntity);
                }
            }
            this.setState(ArcTangential.State.ChoosingBaseEntity);
        }
        break;
    }
};

ArcTangential.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || !isBoolean(this.appendToStartPoint) ||
        !isEntity(this.entity) || !isShape(this.shape) || !isNumber(this.radius)) {
        return undefined;
    }

    var doc = this.getDocument();

    var arc = this.getArc();

    if (!isArcShape(arc) || !arc.isValid()) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    op.addObject(new RArcEntity(doc, new RArcData(arc)));
    return op;
};

ArcTangential.prototype.getArc = function() {
    var doc = this.getDocument();

    var direction;
    var startPoint;
    if (this.appendToStartPoint==true) {
        direction = this.shape.getDirection1() + Math.PI;
        startPoint = this.shape.getStartPoint();
    }
    else {
        direction = this.shape.getDirection2() + Math.PI;
        startPoint = this.shape.getEndPoint();
    }

    return this.createTangential(startPoint, direction);
};

ArcTangential.prototype.createTangential = function(startPoint, direction) {
    return RArc.createTangential(startPoint, this.pos, direction, this.radius);
};

ArcTangential.getTangentialArc = function(startPoint, pos, direction, radius) {
    // orthogonal to base entity:
    var ortho = new RVector();
    ortho.setPolar(radius, direction + Math.PI/2.0);

    // two possible center points for arc:
    var center1 = startPoint.operator_add(ortho);
    var center2 = startPoint.operator_subtract(ortho);
    var center;
    if (center1.getDistanceTo(pos) < center2.getDistanceTo(pos)) {
        center = center1;
    } else {
        center = center2;
    }

    // angles:
    var angle1 = center.getAngleTo(startPoint);
    var angle2 = center.getAngleTo(pos);

    // handle arc direction:
    var reversed = false;
    var arc = new RArc(center, radius, angle1, angle2, reversed);
    var diff = RMath.getNormalizedAngle(arc.getDirection1() - direction);
    if (Math.abs(diff-Math.PI) < 1.0e-1) {
        reversed = true;
    }

    arc.setReversed(reversed);

    return arc;
};

ArcTangential.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

ArcTangential.prototype.getAuxPreview = function() {
    if (isNull(this.pos) || !isBoolean(this.appendToStartPoint) ||
            !isEntity(this.entity) || !isShape(this.shape) || !isNumber(this.radius)) {
        return undefined;
    }

    var ret = [];

    if (this.state==ArcTangential.State.SettingEndPoint) {
        var arc = this.getArc();
        ret.push(new RLine(arc.getCenter(), arc.getStartPoint()));
        ret.push(new RLine(arc.getCenter(), this.pos));
    }

    return ret;
};

ArcTangential.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
    this.updatePreview(true);
};
