/**
 * Copyright (c) 2015 by Norbert Kolb. All rights reserved.
 */

include("scripts/Modify/Modify.js");

/**
 * \class BreakOutGap
 * \brief Divide entities (lines, arcs or circles) into two parts with specified distance.
 * \ingroup ecma_modify
 */
function BreakOutGap(guiAction) {
    Modify.call(this, guiAction);

    this.setUiOptions("BreakOutGap.ui");

    this.entity = undefined;
    this.shape = undefined;
    // user click position:
    this.pos = undefined;
    // actual cutting point:
    this.cutPos = undefined;
    // offset between cutting points
    this.offset = 4;
}

BreakOutGap.prototype = new Modify();

BreakOutGap.State = {
    ChoosingEntity : 0,
    SettingPos : 1
};

BreakOutGap.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(BreakOutGap.State.ChoosingEntity);
};

BreakOutGap.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
        case BreakOutGap.State.ChoosingEntity:
            this.entity = undefined;
            this.shape = undefined;
            this.pos = undefined;
            this.cutPos = undefined;
            this.getDocumentInterface().setClickMode(RAction.PickEntity);
            tr = qsTr("Choose line, arc or circle");
            this.setLeftMouseTip(tr);
            this.setCommandPrompt(tr);
            this.setRightMouseTip(EAction.trCancel);
            EAction.showModificationTools();
            break;
        case BreakOutGap.State.SettingPos:
            this.pos = undefined;
            this.cutPos = undefined;
            this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
            tr = qsTr("Specify point");
            this.setLeftMouseTip(tr);
            this.setCommandPrompt(tr);
            this.setRightMouseTip(EAction.trBack);
            EAction.showSnapTools();
            break;
    }
};

BreakOutGap.prototype.escapeEvent = function() {
    switch (this.state) {
        case BreakOutGap.State.ChoosingEntity:
            EAction.prototype.escapeEvent.call(this);
            break;
        case BreakOutGap.State.SettingPos:
            this.setState(BreakOutGap.State.ChoosingEntity);
            break;
    }
};

BreakOutGap.prototype.pickEntity = function(event, preview) {
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
        case BreakOutGap.State.ChoosingEntity:
            if (isLineEntity(entity) ||
                isArcEntity(entity) ||
                isCircleEntity(entity)) {

                this.entity = entity;
                this.shape = entity.getClosestShape(pos);

                if (preview) {
                    this.updatePreview();
                } else {
                    this.setState(BreakOutGap.State.SettingPos);
                }
            } else {
                if (!preview) {
                    EAction.warnNotLineArcCircle();
                }
            }
            break;
    }
};

BreakOutGap.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var op;

    switch (this.state) {
        case BreakOutGap.State.SettingPos:
            this.pos = event.getModelPosition();

            if (preview) {
                this.updatePreview();
            } else {
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
                this.setState(BreakOutGap.State.ChoosingEntity);
            }
            break;
    }
};

BreakOutGap.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.entity) || !isShape(this.shape)) {
        return undefined;
    }

    var e;

    var op = new RMixedOperation();
    if (isCircleShape(this.shape)) {
        var center;
        var angle = undefined;
        var angle2 = undefined;

        op.deleteObject(this.entity);

        center = this.shape.getCenter();
        var radius = this.shape.getRadius();
        angle = center.getAngleTo(this.pos)+((this.offset/2)/radius);
        angle2 = center.getAngleTo(this.pos)-((this.offset/2)/radius);

        this.cutPos = center.operator_add(RVector.createPolar(radius, angle-((this.offset/2)/radius)));

        var arc = new RArc(
                this.shape.getCenter(),
                this.shape.getRadius(),
                angle,
                angle2,
                false);
        e = new RArcEntity(this.entity.getDocument(), new RArcData(arc));
        op.addObject(e, false);
    } else if (isLineShape(this.shape)) {
        var shape1 = this.shape.clone();
        var shape2 = this.shape.clone();

        shape1 = trimEndPoint(shape1, this.pos, this.pos);
        this.cutPos = shape1.getEndPoint();
        var points = shape1.getPointsWithDistanceToEnd(this.offset/2);
        var line = new RLine(shape1.getStartPoint(), points[1]);

        // modify chosen entity into first part:
        modifyEntity(op, this.entity, line);
        
        shape2 = trimStartPoint(shape2, this.pos, this.pos);
        points = shape2.getPointsWithDistanceToEnd(this.offset/2);
        var line2 = new RLine(points[0], shape2.getEndPoint());
        e = shapeToEntity(this.entity.getDocument(), line2);
        if (!isNull(e)) {
            e.copyAttributesFrom(this.entity.data());
            op.addObject(e, false);
        }
    } else if (isArcShape(this.shape)) {
        var center;
        var angle = undefined;
        var angle2 = undefined;

        op.deleteObject(this.entity);

        center = this.shape.getCenter();
        var radius = this.shape.getRadius();
        angle = center.getAngleTo(this.shape.getStartPoint());
        angle2 = center.getAngleTo(this.pos)-((this.offset/2)/radius);

        this.cutPos = center.operator_add(RVector.createPolar(radius, angle2+((this.offset/2)/radius)));

        var arc = new RArc(
                this.shape.getCenter(),
                this.shape.getRadius(),
                angle,
                angle2,
                false);
        e = new RArcEntity(this.entity.getDocument(), new RArcData(arc));
        op.addObject(e, false);

        angle = center.getAngleTo(this.pos)+((this.offset/2)/radius);
        angle2 = center.getAngleTo(this.shape.getEndPoint());
        arc = new RArc(
                this.shape.getCenter(),
                this.shape.getRadius(),
                angle,
                angle2,
                false);
        e = new RArcEntity(this.entity.getDocument(), new RArcData(arc));
        op.addObject(e, false);
    }
    return op;
};

BreakOutGap.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

BreakOutGap.prototype.getAuxPreview = function() {
    if (!isValidVector(this.cutPos)) {
        return undefined;
    }

    var ret = [];

    var view = EAction.getGraphicsView();
    var overlap = view.mapDistanceFromView(25);

    var line = new RLine(this.cutPos, this.pos);
    var points = line.getPointsWithDistanceToEnd(-overlap);
    line = new RLine(points[0], points[1]);
    ret.push(line);

    var circle = new RCircle( this.cutPos, this.offset/2);
    ret.push(circle);

    return ret;
};

BreakOutGap.prototype.applyCommand = function(event, preview) {
    var di = this.getDocumentInterface();
    var cmd = event.getCommand();

    var pos = RMath.parseCoordinate(cmd);
    if (pos.isValid()) {
        return;
    }

    var value = RMath.eval(cmd);
    if (isNaN(value)) {
        return;
    }

    switch (this.state) {
        case BreakOutGap.State.SettingPos:
            event.accept();
            if (preview) {
                var r = this.offset;
                this.offset = value;
                this.updatePreview(true);
                this.offset = r;
            } else {
                this.setRadius(event.getCommand());
            }
            break;
    }
};

BreakOutGap.prototype.setRadius = function(expr) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("Offset");
    if (isQWidget(w)) {
        w.text = expr;
    }
};

BreakOutGap.prototype.slotOffsetChanged = function(value) {
    this.offset = value;
    this.updatePreview(true);
};
