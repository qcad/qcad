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
 * \class Trim
 * \brief Trims an entity to another entity or trims both entities
 * if \c this.trimBoth is true.
 * \ingroup ecma_modify
 */
function Trim(guiAction) {
    Modify.call(this, guiAction);

    this.limitingEntity = undefined;
    this.limitingShape = undefined;
    this.limitingPos = undefined;

    this.trimEntity = undefined;
    this.trimPos = undefined;

    this.trimBoth = false;
}

Trim.prototype = new Modify();

Trim.includeBasePath = includeBasePath;

Trim.State = {
    ChoosingLimitingEntity : 0,
    ChoosingTrimEntity : 1
};

Trim.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(Trim.State.ChoosingLimitingEntity);
};

Trim.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Trim.State.ChoosingLimitingEntity:
        this.limitingEntity = undefined;
        this.limitingShape = undefined;
        this.limitingPos = undefined;
        this.trimEntity = undefined;
        this.trimPos = undefined;
        var trLimitingEntity = qsTr("Choose limiting entity");
        this.setCommandPrompt(trLimitingEntity);
        this.setLeftMouseTip(trLimitingEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Trim.State.ChoosingTrimEntity:
        this.trimEntity = undefined;
        this.trimPos = undefined;
        var trTrimEntity = qsTr("Choose entity to trim");
        this.setCommandPrompt(trTrimEntity);
        this.setLeftMouseTip(trTrimEntity);
        this.setRightMouseTip(EAction.trBack);
        break;
    }
};

Trim.prototype.escapeEvent = function() {
    switch (this.state) {
    case Trim.State.ChoosingLimitingEntity:
        Modify.prototype.escapeEvent.call(this);
        break;

    case Trim.State.ChoosingTrimEntity:
        this.setState(Trim.State.ChoosingLimitingEntity);
        break;
    }
};

Trim.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    switch (this.state) {
    case Trim.State.ChoosingLimitingEntity:
        if (isNull(entity) || (this.trimBoth && !EAction.assertEditable(entity, preview))) {
            this.limitingEntity = undefined;
            this.limitingShape = undefined;
            if (preview) {
                this.updatePreview();
            }
            break;
        }

        var shape = entity.getClosestShape(pos);

        if (!isLineShape(shape) &&
            !isArcShape(shape) &&
            !isCircleShape(shape) &&
            !isEllipseShape(shape) &&
            !isSplineShape(shape)) {

            if (!preview) {
                EAction.warnNotLineArcCircleEllipse();
            }
            break;
        }

        this.limitingEntity = entity;
        this.limitingShape = shape;
        this.limitingPos = pos;
        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Trim.State.ChoosingTrimEntity);
        }
        break;

    case Trim.State.ChoosingTrimEntity:
        if (isNull(entity) || !EAction.assertEditable(entity, preview)) {
            this.trimEntity = undefined;
            if (preview) {
                this.updatePreview();
            }
            return;
        }

        if (!isLineEntity(entity) &&
            !isArcEntity(entity) &&
            !isCircleEntity(entity) &&
            !isEllipseEntity(entity)) {

            this.trimEntity = undefined;
            if (preview) {
                this.updatePreview();
            }
            else {
                EAction.warnNotLineArcCircleEllipse();
            }
            break;
        }

        this.trimEntity = entity;
        this.trimPos = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            di.applyOperation(this.getOperation(false));

            if (this.trimBoth) {
                this.setState(Trim.State.ChoosingLimitingEntity);
            }
        }
        break;
    }
};

Trim.prototype.getOperation = function(preview) {
    if (!isEntity(this.trimEntity)) {
        return undefined;
    }

    var op = new RMixedOperation();

    var success = Trim.trim(op, this.limitingEntity, this.limitingShape, this.limitingPos, this.trimEntity, this.trimPos, this.trimBoth, preview);

    if (!success && !preview) {
        EAction.handleUserWarning(qsTr("The two entities don't intersect, or are currently not supported for trimming."));
    }

    return op;
};

Trim.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.limitingEntity)) {
        ret.push(this.limitingEntity.getId());
    }
    if (isEntity(this.trimEntity)) {
        ret.push(this.trimEntity.getId());
    }
    return ret;
};

/**
 * Trims or extends the given trimEntity to the intersection point of the
 * trimEntity and the limitingShape.
 *
 * \param trimPos Coordinate which defines which endpoint of the
 *   trim entity to trim.
 * \param trimEntity Entity which will be trimmed.
 * \param limitingPos Coordinate which defines the intersection to which the
 *    trim entity will be trimmed.
 * \param limitingShape Entity to which the trim entity will be trimmed.
 * \param trimBoth true: Trim both entities. false: trim trimEntity only.
 */
Trim.trim = function(op, limitingEntity, limitingShape, limitingPos, trimEntity, trimPos, trimBoth, preview) {
    if (!isEntity(limitingEntity) || !isShape(limitingShape) || !isValidVector(limitingPos) ||
            !isEntity(trimEntity) || !isValidVector(trimPos) ||
            !isBoolean(trimBoth)) {
        return false;
    }

    var trimShape = trimEntity.getData().castToShape();

    if (isNull(trimShape)) {
        return false;
    }

    // possible trim points:
    var sol = trimShape.getIntersectionPoints(limitingShape.data(), false);

    if (sol.length===0) {
        return false;
    }

    var trimmed1;
    var trimmed2;
    var c, r, am, a1, a2;
    var mp;

    if (isCircleEntity(trimEntity)) {
        // convert circle to trimmable arc:
        c = trimEntity.getCenter();
        r = trimEntity.getRadius();
        am = c.getAngleTo(trimPos);
        a1 = RMath.getNormalizedAngle(am-Math.PI/2);
        a2 = RMath.getNormalizedAngle(am+Math.PI/2);
        trimmed1 = new RArcEntity(
                    trimEntity.getDocument(),
                    new RArcData(c,r,a1,a2,false));
        trimmed1.copyAttributesFrom(trimEntity.data());
    }
    else if (isFullEllipseEntity(trimEntity)) {
        c = trimEntity.getCenter();
        mp = trimEntity.getMajorPoint();
        r = trimEntity.getRatio();
        am = trimEntity.getParamTo(trimPos);
        a1 = RMath.getNormalizedAngle(am-Math.PI/2);
        a2 = RMath.getNormalizedAngle(am+Math.PI/2);
        trimmed1 = new REllipseEntity(
                    trimEntity.getDocument(),
                    new REllipseData(c,mp,r,a1,a2,false));
        trimmed1.copyAttributesFrom(trimEntity.data());
    }
    else {
        trimmed1 = trimEntity.clone();
    }

    if (trimBoth) {
        if (isCircleEntity(limitingEntity)) {
            // convert circle to trimmable arc:
            c = limitingEntity.getCenter();
            r = limitingEntity.getRadius();
            am = c.getAngleTo(trimPos);
            a1 = RMath.getNormalizedAngle(am-Math.PI/2);
            a2 = RMath.getNormalizedAngle(am+Math.PI/2);
            trimmed2 = new RArcEntity(
                        limitingEntity.getDocument(),
                        new RArcData(c,r,a1,a2,false));
        }
//        else if (isFullEllipseEntity(limitingEntity)) {
//            // convert circle to trimmable arc:
//            c = limitingEntity.getCenter();
//            r = limitingEntity.getRadius();
//            am = c.getAngleTo(trimPos);
//            a1 = RMath.getNormalizedAngle(am-Math.PI/2);
//            a2 = RMath.getNormalizedAngle(am+Math.PI/2);
//            trimmed2 = new RArcEntity(
//                        limitingEntity.getDocument(),
//                        new RArcData(c,r,a1,a2,false));
//        }
        else {
            trimmed2 = limitingEntity.clone();
        }
    }

    // find trim (intersection) point:
    var isIdx;
    if (trimBoth || isEllipseEntity(trimEntity)) {
        isIdx = trimPos.getClosestIndex(sol);
    }
    else {
        isIdx = limitingPos.getClosestIndex(sol);
    }
    var is = sol[isIdx];
    var is2;

    if (sol.length===1 || isIdx!==0) {
        is2 = sol[0];
    }
    else {
        is2 = sol[1];
    }

    // trim trim entity:
    var ending = trimmed1.getTrimEnd(trimPos, is);

    switch (ending) {
    case RS.EndingStart:
        trimmed1.trimStartPoint(is);
        if (isCircleEntity(trimEntity) || isFullEllipseEntity(trimEntity)) {
            trimmed1.trimEndPoint(is2);
        }
        break;
    case RS.EndingEnd:
        trimmed1.trimEndPoint(is);
        if (isCircleEntity(trimEntity) || isFullEllipseEntity(trimEntity)) {
            trimmed1.trimStartPoint(is2);
        }
        break;
    default:
        break;
    }

    // trim limiting entity if possible (not possible for splines):
    if (trimBoth && isFunction(trimmed2.getTrimEnd)) {
        ending = trimmed2.getTrimEnd(limitingPos, is);

        switch (ending) {
        case RS.EndingStart:
            trimmed2.trimStartPoint(is);
            if (isCircleEntity(limitingEntity) || isFullEllipseEntity(limitingEntity)) {
                trimmed2.trimEndPoint(is2);
            }
            break;
        case RS.EndingEnd:
            trimmed2.trimEndPoint(is);
            if (isCircleEntity(limitingEntity) || isFullEllipseEntity(limitingEntity)) {
                trimmed2.trimStartPoint(is2);
            }
            break;
        default:
            break;
        }
    }

    op.addObject(trimmed1, false);
    if (isCircleEntity(trimEntity) || isFullEllipseEntity(trimEntity)) {
        op.deleteObject(trimEntity);
    }

    if (trimBoth) {
        op.addObject(trimmed2, false);
        if (isCircleEntity(limitingEntity)) {
            op.deleteObject(limitingEntity);
        }
    }

    return true;
};

