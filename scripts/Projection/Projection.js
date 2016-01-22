/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

/**
 * \defgroup ecma_projection Projection Tools
 * \ingroup ecma_modify
 *
 * \brief This module contains ECMAScript implementations of various projection (isometric, orthographic) tools.
 */

include("../Modify/Transform.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Projection
 * \brief Base class for all projection tools.
 * \ingroup ecma_projection
 */
function Projection(guiAction) {
    Transform.call(this, guiAction);

    this.rotation = 0.0;
    this.copies = 1;
    this.referencePoint = undefined;
    this.targetPoint = undefined;

    // inheriting classes set this to true if projected entities have to be
    // segmented into line segments:
    this.segmentation = false;
    this.segmentLength = 1.0;

    // force flat projection (for aux constructions):
    this.flat = false;
}

Projection.prototype = new Transform();
Projection.includeBasePath = includeBasePath;

Projection.State = {
    SettingReferencePoint : 0,
    SettingTargetPoint : 1
};

Projection.getToolBar = function() {
    var tb = EAction.getToolBar(Projection.getTitle(), "ProjectionToolBar");
    tb.visible = false;
    return tb;
};

Projection.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "ProjectionToolsPanelAction";
    if (!isNull(mtb) && isNull(mtb.findChild(actionName))) {
        var action = new RGuiAction(qsTr("Projection Tools"), mtb);
        action.setScriptFile(Projection.includeBasePath + "/Projection.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Projection.includeBasePath + "/Projection.svg");
        action.setStatusTip(qsTr("Show projection tools"));
        action.setDefaultShortcut(new QKeySequence("w,j"));
        action.setNoState();
        action.setDefaultCommands(["projectmenu"]);
        action.setGroupSortOrder(50);
        action.setSortOrder(100);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(Projection.getTitle(), "ProjectionToolsPanel", true);
    return tb;
};

Projection.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Projection.getTitle(), "ProjectionMatrixPanel", 6000);
};

Projection.getTitle = function() {
    return qsTr("&Projection");
};

Projection.prototype.getTitle = function() {
    return Projection.getTitle();
};

Projection.init = function() {
    Projection.getToolBar();
    Projection.getCadToolBarPanel();
    Projection.getToolMatrixPanel();
};

Projection.prototype.beginEvent = function() {
    Transform.prototype.beginEvent.call(this);

    // show projection tools panel:
    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="ProjectionToolsPanelAction") {
        EAction.showCadToolBarPanel("ProjectionToolsPanel");
        this.terminate();
        return;
    }

    // start tool:
    if (!this.verifySelection()) {
        this.terminate();
        return;
    }

    this.setState(Projection.State.SettingReferencePoint);
};

Projection.prototype.setState = function(state) {
    Transform.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Projection.State.SettingReferencePoint:
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        var trReferencePoint = qsTr("Reference point");
        this.setCommandPrompt(trReferencePoint);
        this.setLeftMouseTip(trReferencePoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Projection.State.SettingTargetPoint:
        this.targetPoint = undefined;
        var trTargetPoint = qsTr("Target point");
        this.setCommandPrompt(trTargetPoint);
        this.setLeftMouseTip(trTargetPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Projection.prototype.escapeEvent = function() {
    switch (this.state) {
    case Projection.State.SettingReferencePoint:
        Transform.prototype.escapeEvent.call(this);
        break;

    case Projection.State.SettingTargetPoint:
        this.setState(Projection.State.SettingReferencePoint);
        break;
    }
};

Projection.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Projection.State.SettingReferencePoint:
        this.referencePoint = event.getModelPosition();
        this.clearCache();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.referencePoint);
            this.setState(Projection.State.SettingTargetPoint);
        }
        break;

    case Projection.State.SettingTargetPoint:
        this.targetPoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
            di.setRelativeZero(this.targetPoint);
        }
        break;
    }
};

Projection.prototype.getOperation = function(preview) {
    if (this.state===Projection.State.SettingReferencePoint) {
        return undefined;
    }

    if (isNull(this.referencePoint) || isNull(this.targetPoint)) {
        return undefined;
    }

    return Transform.prototype.getOperation.call(this, preview, false, true);
};

Projection.prototype.preTransform = function(entity) {
    // move original entity to neutral position:
    entity.move(this.referencePoint.getNegated());

    // rotate entity:
    entity.rotate(RMath.deg2rad(this.rotation));
};

Projection.prototype.postTransform = function(entity) {
};

/**
 * Callback function for Transform.getOperation. Generic for all projections.
 * \param k Ignored
 */
Projection.prototype.transform = function(entity, k, op, preview, forceNew) {
    var i;

    this.preTransform(entity);

    // shapes that represent this entity:
    var shapes = entity.getShapes();
    this.addTransformedShapes(entity, shapes, op, preview, forceNew);

    // text data that is part of this entity (dimension label):
    if (isDimensionEntity(entity) && isFunction(entity.getTextData)) {
        var textData = entity.getTextData();
        var painterPaths = textData.getPainterPaths(false);
        for (i=0; i<painterPaths.length; i++) {
            if (painterPaths[i].getFeatureSize()<0.0) {
                continue;
            }
            shapes = painterPaths[i].getShapes();
            this.addTransformedShapes(entity, shapes, op, preview, forceNew);
        }
    }
};

/**
 * Adds the projected shapes of the given entity to the given operation.
 *
 * \param entity REntity Original (unprojected) entity (used to copy attributes
 *      to new shapes).
 * \param shapes Array The transformed shapes
 * \param op RAddObjectsOperation Operation
 */
Projection.prototype.addTransformedShapes = function(entity, shapes, op, preview, forceNew) {
    for (var i=0; i<shapes.length; i++) {
        var s = this.projectShape(shapes[i].data(), preview);
        for (var n=0; n<s.length; n++) {
            if (isNull(s[n])) {
                debugger;
            }

            var e = shapeToEntity(entity.getDocument(), s[n]);
            if (isNull(e)) {
                continue;
            }

            e.copyAttributesFrom(entity);
            //e.move(this.targetPoint);
            op.addObject(e, false, forceNew);
        }
    }
};

/**
 * Reimplemented by inheriting classes to trim the given unprojected shape
 * to the projectable area.
 *
 * Default implementation returns the original shape (no trimming).
 *
 * \param shape RShape Shape to trim (normalized).
 */
Projection.prototype.trimShape = function(shape) {
    return [shape];
};

/**
 * Reimplemented by inheriting classes.
 *
 * Default implementation does nothing (no projection).
 *
 * \param p Vector to transform in normalized coordinates, relative to the
 * chosen reference point.
 */
Projection.prototype.project = function(p) {
    return p;
}

/**
 * Can be reimplemented to return true if the transformation flips
 * entities (mirroring). This means that arcs have to be reversed.
 */
Projection.prototype.isFlip = function() {
    return false;
}

/**
 * Projection of the given shape. The shape uses coordinates relative to
 * the chosen reference point.
 *
 * \return Array of new projected shapes.
 */
Projection.prototype.projectShape = function(shape, preview, trim) {
    var p, p2, i, k, s, ret;

    if (isNull(trim)) {
        trim = true;
    }

    // trim shape and project resulting segments:
    if (trim===true && (isPointShape(shape) || isLineShape(shape) || isArcShape(shape))) {
        var trimmedShapes = this.trimShape(shape);

        ret = [];
        for (k=0; k<trimmedShapes.length; k++) {
            shape = trimmedShapes[k];
            s = this.projectShape(shape, preview, false);
            ret = ret.concat(s);
        }
        return ret;
    }

    if (this.segmentation && !this.flat) {
        // If segmentation is on, split up lines and arcs into polylines
        // with the given segment length. All other shapes are split up into
        // lines and arcs.
        if (isLineShape(shape) || isArcShape(shape)) {
            ret = [];

            // switch off segmentation for polyline segments:
            this.segmentation = false;

            var l = shape.getLength();
            var numSegments = 16;
            if (!preview && this.segmentLength>RS.PointTolerance) {
                numSegments = Math.ceil(l/this.segmentLength);
            }

            var polyline = ShapeAlgorithms.lineOrArcToPolyline(shape, numSegments);
            var projectedPl = this.projectShape(polyline, preview, trim)[0];
            if (!isNull(projectedPl)) {
                projectedPl.simplify();
                ret.push(projectedPl);
            }
            this.segmentation = true;

            return ret;
        }
        if (isXLineShape(shape) || isRayShape(shape)) {
            return [];
        }
    }

    if (isPointShape(shape)) {
        p = shape.getPosition();
        this.project(p);
        shape.setPosition(p);
        return [ shape ];
    }

    if (isLineShape(shape)) {
        p = shape.getStartPoint();
        this.project(p);
        shape.setStartPoint(p);

        p = shape.getEndPoint();
        this.project(p);
        shape.setEndPoint(p);
        return [ shape ];
    }

    if (isXLineShape(shape) || isRayShape(shape)) {
        p = shape.getBasePoint();
        this.project(p);

        p2 = shape.getSecondPoint();
        this.project(p2);

        shape.setBasePoint(p);
        shape.setSecondPoint(p2);
        return [ shape ];
    }

    if (isArcShape(shape)) {
        var self=this;
        var ellipse = ShapeAlgorithms.transformArc(shape,
            function(p) {
                self.project(p);
            }
        );
        return [ ellipse ];
    }

    if (isCircleShape(shape)) {
        var arc = new RArc(shape.getCenter(), shape.getRadius(), 0.0, Math.PI*2);
        return this.projectShape(arc, preview, trim);
    }

    if (isEllipseShape(shape)) {
        if (shape.isCircular()) {
            // ellipse is a full circle:
            if (shape.isFullEllipse()) {
                var circle = new RCircle(shape.getCenter(), shape.getMajorRadius());
                return this.projectShape(circle, preview, trim);
            }
            // ellipse is a circular arc:
            else {
                var arc = new RArc(shape.getCenter(),
                                     shape.getMajorRadius(),
                                     shape.getStartAngle(),
                                     shape.getEndAngle(),
                                     shape.isReversed());
                return this.projectShape(arc, preview, trim);
            }
        }

        var ple = ShapeAlgorithms.approximateEllipse(shape, 16);
        return this.projectShape(ple, preview, trim);
    }

    if (isTriangleShape(shape)) {
        for (i=0; i<3; ++i) {
            p = shape.getCorner(i);
            this.project(p);
            shape.setCorner(i, p);
        }

        return [ shape ];
    }

    if (isSplineShape(shape)) {
        shape = ShapeAlgorithms.splineToLineOrArc(shape, 0.01);
        if (!isSplineShape(shape)) {
            return this.projectShape(shape, preview, trim);
        }

        var segmentation = this.segmentation;
        this.segmentation = false;
        var segments = preview ? 4 : -1;
        var pls = shape.toPolyline(segments);
//        var shapes = shape.getExploded(segments);
//        var pls = new RPolyline();
//        for (i=0; i<shapes.length; i++) {
//            s = shapes[i].data();
//            pls.appendShape(s);
//        }
        ret = this.projectShape(pls, preview, trim);
        this.segmentation = segmentation;
        return ret;
    }

    if (isPolylineShape(shape)) {
        // add polyline, split up at arcs that are projected into ellipses and
        // at gaps caused by trimming:
        ret = [];
        var pl = new RPolyline();
        var segmentCount = shape.countSegments();
        var addPl = false;

        // project each segment individually:
        for (i=0; i<segmentCount; i++) {
            s = shape.getSegmentAt(i).data();
            s = this.projectShape(s, preview, trim);

            // iterate through projected shapes (trimming might lead to gaps):
            for (k=0; k<s.length; k++) {
                var seg = s[k];

                var gotGap = pl.countVertices()>0 &&
                    !pl.getEndPoint().equalsFuzzy(seg.getStartPoint());

                // s is a line or polyline that connets to the polyline we have:
                if (!gotGap && (isLineShape(seg) || isPolylineShape(seg))) {
                    if (seg.getLength()>RS.PointTolerance) {
                        pl.appendShape(seg);
                    }
                }

                // s is an ellipse:
                var gotEllipse = isEllipseShape(seg);

                if (i===segmentCount-1 || gotEllipse || gotGap) {
                    if (pl.countVertices()===1) {
                        // don't add polyline for one single shape:
                        ret.push(pl.getSegmentAt(0));
                    }
                    else if (pl.countVertices()>0) {
                        ret.push(pl);
                        addPl = false;
                    }

                    if (gotEllipse) {
                        ret.push(seg);
                        pl = new RPolyline();
                    }
                    else if (gotGap){
                        pl = new RPolyline();
                        pl.appendShape(seg);
                        addPl = true;
                    }
                }
            }
        }

        if (addPl && pl.countVertices()>0) {
            ret.push(pl);
        }

        return ret;
    }

    return [];
}

Projection.prototype.slotRotateCCW = function() {
    this.rotation += 90;
    this.clearCache();
    this.updatePreview(true);
};

Projection.prototype.slotRotateCW = function() {
    this.rotation -= 90;
    this.clearCache();
    this.updatePreview(true);
};

Projection.prototype.slotSegmentLengthChanged = function(l) {
    this.segmentLength = l;
    this.clearCache();
    this.updatePreview(true);
};
