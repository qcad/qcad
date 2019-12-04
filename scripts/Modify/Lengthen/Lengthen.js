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

include("scripts/Modify/Modify.js");

/**
 * \class Lengthen
 * \brief Lengthens (or shortens) an entity by a given amount. If the amount is
 * positive, the entity is lengthened (extended), if the amount is negative
 * it is shortened.
 * \ingroup ecma_modify
 */
function Lengthen(guiAction) {
    Modify.call(this, guiAction);

    this.amount = undefined;
    this.entity = undefined;
    this.pos = undefined;

    this.setUiOptions("Lengthen.ui");
}

Lengthen.prototype = new Modify();

Lengthen.State = {
    ChoosingEntity : 0
};

Lengthen.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(Lengthen.State.ChoosingEntity);
};

Lengthen.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Lengthen.State.ChoosingEntity:
        var tr = qsTr("Choose line or arc");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

Lengthen.prototype.escapeEvent = function() {
    switch (this.state) {
    case Lengthen.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

Lengthen.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.entity = undefined;
        return;
    }

    switch (this.state) {
    case Lengthen.State.ChoosingEntity:
        if (!this.isSupportedEntity(entity)) {
            if (!preview) {
                this.warnUnsupportedEntity();
            }
            break;
        }

        if (!EAction.assertEditable(entity, preview)) {
            break;
        }

        this.entity = entity;
        this.pos = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                if (this.error.length!==0) {
                    EAction.handleUserWarning(this.error);
                }
            }
        }
        break;
    }
};

Lengthen.prototype.isSupportedEntity = function(entity) {
    return isLineEntity(entity) ||
           isArcEntity(entity) ||
//           (RSpline.hasProxy() && isSplineEntity(entity)) ||
           (RPolyline.hasProxy() && isPolylineEntity(entity));
};

Lengthen.prototype.warnUnsupportedEntity = function() {
    if (/*RSpline.hasProxy() && */RPolyline.hasProxy()) {
        EAction.warnNotLineArcPolyline();
    }
    else {
        EAction.warnNotLineArc();
    }
};

Lengthen.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.entity) || !isNumber(this.amount)) {
        return undefined;
    }

    var ret = Lengthen.lengthen(this.entity, this.pos, undefined, this.amount);
    if (!ret) {
        return undefined;
    }

    return new RAddObjectOperation(this.entity, this.getToolTitle(), false);
};

Lengthen.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

Lengthen.prototype.slotAmountChanged = function(amount) {
    this.amount = amount;
};

/**
 * Lengthens the given entity by the given amount at its start or end point.
 *
 * \param entity Entity to lengthen
 * \param position Position clicked by the user or undefined if trimStartPoint is given
 * \param trimStartPoint True to trim start point, false to trim end point
 * \param amount Amount to lengthen or negative to shorten
 */
Lengthen.lengthen = function(entity, position, trimStartPoint, amount) {
    if (isNull(trimStartPoint)) {
        if (isPolylineEntity(entity)) {
            trimStartPoint = entity.getLengthTo(position) < entity.getLength()/2;
        }
        else {
            trimStartPoint = position.getDistanceTo(entity.getStartPoint()) < position.getDistanceTo(entity.getEndPoint());
        }
    }

    var from;
    if (trimStartPoint) {
        from = RS.FromStart;
    }
    else {
        from = RS.FromEnd;
    }

    var iss;
    if (isPolylineEntity(entity)) {
        var pl = entity.castToShape();
        iss = pl.getPointsWithDistanceToEnd(-amount, from|RS.AlongPolyline);
    }
    else {
        iss = entity.getPointsWithDistanceToEnd(-amount, from|RS.AlongPolyline);
    }

    var is = position.getClosest(iss);

    if (!isValidVector(is)) {
        return false;
    }

    if (trimStartPoint) {
        if (!isFunction(entity.trimStartPoint)) {
            return false;
        }

        entity.trimStartPoint(is, is, amount>0);
    } else {
        if (!isFunction(entity.trimEndPoint)) {
            return false;
        }

        entity.trimEndPoint(is, is, amount>0);
    }

    return true;
}
