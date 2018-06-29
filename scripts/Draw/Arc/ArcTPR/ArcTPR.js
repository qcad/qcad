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
 * \class ArcTPR
 * \brief Arc tangential to entity, through point with given radius.
 * \ingroup ecma_draw_arc
 */
function ArcTPR(guiAction) {
    Arc.call(this, guiAction);

    this.radius = undefined;

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;

    this.pos = undefined;
    this.posSolution = undefined;

    this.candidates = undefined;

    this.fullCircle = false;

    this.setUiOptions(ArcTPR.includeBasePath + "/ArcTPR.ui");
}

ArcTPR.prototype = new Arc();
ArcTPR.includeBasePath = includeBasePath;

ArcTPR.State = {
    ChoosingShape : 0,
    SettingPoint : 1,
    ChoosingSolution : 2
};

ArcTPR.prototype.beginEvent = function() {
    Arc.prototype.beginEvent.call(this);

    this.setState(ArcTPR.State.ChoosingShape);
};

ArcTPR.prototype.setState = function(state) {
    Arc.prototype.setState.call(this, state);

    var di = this.getDocumentInterface();

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ArcTPR.State.ChoosingShape:
        di.setClickMode(RAction.PickEntity);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.pos = undefined;
        this.posSolution = undefined;
        this.candidates = undefined;
        var trEntity = qsTr("Choose line, arc, circle or ellipse");
        this.setCommandPrompt(trEntity);
        this.setLeftMouseTip(trEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ArcTPR.State.SettingPoint:
        di.setClickMode(RAction.PickCoordinate);
        this.pos = undefined;
        this.posSolution = undefined;
        this.candidates = undefined;
        var trPoint = qsTr("Point on arc");
        this.setCommandPrompt(trPoint);
        this.setLeftMouseTip(trPoint);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;

    case ArcTPR.State.ChoosingSolution:
        di.setClickMode(RAction.PickEntity);
        this.posSolution = undefined;
        var trSolution = qsTr("Choose solution");
        this.setCommandPrompt(trSolution);
        this.setLeftMouseTip(trSolution);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    this.simulateMouseMoveEvent();
};

ArcTPR.prototype.escapeEvent = function() {
    switch (this.state) {
    case ArcTPR.State.ChoosingShape:
        EAction.prototype.escapeEvent.call(this);
        break;

    case ArcTPR.State.SettingPoint:
        this.setState(ArcTPR.State.ChoosingShape);
        break;

    case ArcTPR.State.ChoosingSolution:
        this.setState(ArcTPR.State.SettingPoint);
        break;
    }
};

ArcTPR.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();
    var shape = undefined;

    if (this.state!==ArcTPR.State.ChoosingSolution) {
        if (isNull(entity)) {
            return;
        }
        else {
            shape = entity.getClosestSimpleShape(pos);

            if (!isLineBasedShape(shape) &&
                !isArcShape(shape) &&
                !isCircleShape(shape) &&
                !isEllipseShape(shape)) {

                if (!preview) {
                    EAction.warnNotLineArcCircleEllipse();
                    return;
                }

                shape = undefined;
            }
        }
    }

    switch (this.state) {
    case ArcTPR.State.ChoosingShape:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(ArcTPR.State.SettingPoint);
        }
        break;

    case ArcTPR.State.ChoosingSolution:
        this.posSolution = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(ArcTPR.State.ChoosingShape);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

ArcTPR.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var pos = event.getModelPosition();

    switch (this.state) {
    case ArcTPR.State.SettingPoint:
        if (isNull(this.pos) || !pos.equalsFuzzy(this.pos)) {
            this.candidates = undefined;
        }

        this.pos = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                // only one solution:
                if (this.candidates.length===1) {
                    di.applyOperation(op);
                    this.setState(ArcTPR.State.ChoosingShape);
                }
                // multiple solutions:
                else {
                    op.destroy();
                    this.setState(ArcTPR.State.ChoosingSolution);
                }
            }
            // no solution:
            else {
                this.setState(ArcTPR.State.ChoosingShape);
                this.error = qsTr("No solution");
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

ArcTPR.prototype.getOperation = function(preview) {
    var shape = this.getShapes(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    for (var i=0; i<shape.length; i++) {
        var entity = shapeToEntity(doc, shape[i]);
        op.addObject(entity);
    }

    return op;
};

ArcTPR.prototype.getShapes = function(preview) {
    if (isNull(this.shape1) || isNull(this.pos) || isNull(this.radius)) {
        return undefined;
    }

    if (isNull(this.candidates)) {
        this.candidates = [];

        // parallel to shape:
        var parallels = ShapeAlgorithms.getOffsetShapes(this.shape1, this.radius, 1, this.pos);
        if (parallels.length===1) {
            // circle around pos:
            var circle = new RCircle(this.pos, this.radius);

            // find potential centers for arc:
            var ips = parallels[0].getIntersectionPoints(circle, false);
            for (var i=0; i<ips.length; i++) {
                var ip = ips[i];

                if (this.fullCircle) {
                    this.candidates.push(new RCircle(ip, this.radius));
                }
                else {
                    var p = this.shape1.getClosestPointOnShape(ip, false);
                    var a1 = ip.getAngleTo(p);
                    var a2 = ip.getAngleTo(this.pos);
                    this.candidates.push(new RArc(ip, this.radius, a1, a2, false));
                    this.candidates.push(new RArc(ip, this.radius, a2, a1, false));
                }
            }
        }
    }

    if (this.candidates.length===0) {
        if (!preview) {
            this.error = qsTr("No solution");
        }
        return undefined;
    }

    // no position of solution yet: return all candidates for preview:
    if (isNull(this.posSolution)) {
        return this.candidates;
    }

    return [ ShapeAlgorithms.getClosestShape(this.candidates, this.posSolution) ];
};

ArcTPR.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    return ret;
};

ArcTPR.prototype.getAuxPreview = function() {
    if (isNull(this.shape1) || isNull(this.pos)) {
        return [];
    }

    if (!isNull(this.posSolution)) {
        return this.candidates;
    }

    return [];
};

ArcTPR.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
    this.updatePreview(true);
};
