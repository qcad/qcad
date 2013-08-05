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

include("../Modify.js");

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
        this.setLeftMouseTip(qsTr("Choose line or arc"));
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
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.entity = undefined;
        return;
    }

    switch (this.state) {
    case Lengthen.State.ChoosingEntity:
        if (!isLineEntity(entity) &&
            !isArcEntity(entity)) {

            if (!preview) {
                EAction.warnNotLineArc();
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

Lengthen.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.entity) || !isNumber(this.amount)) {
        return undefined;
    }

    var iss = this.entity.getPointsWithDistanceToEnd(-this.amount);
    if (iss.length!==2) {
        return undefined;
    }

    var is = this.pos.getClosest(iss);

    if (!isValidVector(is)) {
        return undefined;
    }

    if (this.pos.getDistanceTo(this.entity.getStartPoint()) <
        this.pos.getDistanceTo(this.entity.getEndPoint())) {
        if (!isFunction(this.entity.trimStartPoint)) {
            return undefined;
        }

        this.entity.trimStartPoint(is);
    } else {
        if (!isFunction(this.entity.trimEndPoint)) {
            return undefined;
        }

        this.entity.trimEndPoint(is);
    }

    return new RAddObjectOperation(this.entity, false);
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

