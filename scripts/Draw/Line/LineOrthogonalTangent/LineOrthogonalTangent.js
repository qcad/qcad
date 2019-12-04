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
include("scripts/ShapeAlgorithms.js");

/**
 * \class LineOrthogonalTangent
 * \brief Line orthogonal to line and tangential to arc, circle or ellipse.
 * \ingroup ecma_draw_line
 */
function LineOrthogonalTangent(guiAction) {
    Line.call(this, guiAction);

    // first entity (line):
    this.entity1 = undefined;
    // first shape:
    this.shape1 = undefined;
    // click position when choosing first entity:
    this.pos1 = undefined;

    // second entity (circle, arc, ellipse):
    this.entity2 = undefined;
    // second shape:
    this.shape2 = undefined;
    // click position when choosing second entity:
    this.pos2 = undefined;

    this.setUiOptions("../Line.ui");
}

LineOrthogonalTangent.prototype = new Line();

LineOrthogonalTangent.State = {
    ChoosingEntity1 : 0,
    ChoosingEntity2 : 1
};

LineOrthogonalTangent.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineOrthogonalTangent.State.ChoosingEntity1);
};

LineOrthogonalTangent.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineOrthogonalTangent.State.ChoosingEntity1:
        tr = qsTr("Choose line");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.pos1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.pos2 = undefined;
        break;
    case LineOrthogonalTangent.State.ChoosingEntity2:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        tr = qsTr("Choose circle, arc or ellipse");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

};

LineOrthogonalTangent.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineOrthogonalTangent.State.ChoosingEntity1:
        EAction.prototype.escapeEvent.call(this);
        break;
    case LineOrthogonalTangent.State.ChoosingEntity2:
        this.setState(LineOrthogonalTangent.State.ChoosingEntity1);
        break;
    }
};

LineOrthogonalTangent.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.updatePreview();
        return;
    }

    var shape = entity.getClosestSimpleShape(pos);

    switch (this.state) {
    case LineOrthogonalTangent.State.ChoosingEntity1:
        if (isLineBasedShape(shape)) {
            this.entity1 = entity;
            this.shape1 = shape;
            this.pos1 = pos;

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(LineOrthogonalTangent.State.ChoosingEntity2);
            }
        }
        else {
            this.entity1 = undefined;
            this.shape1 = undefined;
            this.pos1 = undefined;
            if (!preview) {
                EAction.warnNotLine();
            }
        }
        break;

    case LineOrthogonalTangent.State.ChoosingEntity2:
        if (isArcShape(shape) ||
            isCircleShape(shape) ||
            isEllipseShape(shape)) {

            this.entity2 = entity;
            this.shape2 = shape;
            this.pos2 = pos;

            if (preview) {
                this.updatePreview();
            }
            else {
                var op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                    if (this.error.length===0) {
                        this.setState(LineOrthogonalTangent.State.ChoosingEntity1);
                    }
                }
            }
        }
        else {
            this.entity2 = undefined;
            this.shape2 = undefined;
            this.pos2 = undefined;
            if (preview) {
                this.updatePreview();
            }
            else {
                EAction.warnNotArcCircleEllipse();
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

LineOrthogonalTangent.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};

LineOrthogonalTangent.prototype.getAuxPreview = function() {
    var ret = [];

    if (isArcShape(this.shape2)) {
        ret.push(new RCircle(this.shape2.getCenter(), this.shape2.getRadius()));
    }
    else if (isEllipseShape(this.shape2) && !isFullEllipseShape(this.shape2)) {
        var ellipse = this.shape2.clone();
        ellipse.setStartParam(0.0);
        ellipse.setEndParam(2*Math.PI);
        ret.push(ellipse);
    }

    return ret;
};

LineOrthogonalTangent.prototype.getOperation = function(preview) {
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

    var e = this.createLineEntity(doc, tangent.getEndPoint(), tangent.getStartPoint());
    if (isNull(e)) {
        return undefined;
    }

    return new RAddObjectOperation(e, this.getToolTitle());
};

LineOrthogonalTangent.prototype.getTangent = function() {
    var ret;
    var tangents = ShapeAlgorithms.getOrthogonalTangents(this.shape1, this.shape2);

    // find closest tangent:
    var minDist;
    var dist;
    var idx = -1;
    for (var i=0; i<tangents.length; ++i) {
        if (isNull(tangents[i])) {
            continue;
        }

        dist = tangents[i].getDistanceTo(this.pos2, false);
        if (isNull(minDist) || dist<minDist) {
            minDist = dist;
            ret = tangents[i];
        }
    }

    return ret;
};
