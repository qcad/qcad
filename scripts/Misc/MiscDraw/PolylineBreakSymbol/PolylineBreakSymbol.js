/*
 * Copyright (c) 2021 by Pete Vickerstaff. With a LOT of help from CVH.
 *   Based on ExLineDove.js/LineDove.js by Matthias Melcher. All rights reserved.
 *   Also based on BreakOutManual.js by Andrew Mustun. All rights reserved.
 *   Both still are or were part of the QCAD project.
 *
 * This file is a free extension of the QCAD project.
 * Permission to evaluate, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
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
UPDATES
v0 - 11/03/2021 - First upload
v1 - 15/03/2021 - Inherit checkbox added in UI, toggles inherit properties from chosen entity.
                  Spin box replaced by a drop down combo box in UI.
                  Peak Height changed to Peak Ratio. breakHeight vars now breakRatio.
                  Radio buttons replaced with Toolbar buttons in UI.
                  Added status line comments for toolbar items in UI.
v2 - 22/04/2021 - All lines 158 to 163 - .entity was .shape
 */

//  Base Class
include("scripts/EAction.js");
//  ShapeAlgorithms.autoSplitManual for removing segment
include("scripts/ShapeAlgorithms.js");


/**
 * \class PolylineBreakSymbol
 * \brief break symbol between two points.
 * \ingroup ecma_misc_draw
 */

function PolylineBreakSymbol(guiAction) {
    EAction.call(this, guiAction);


    // Default settings matching the UI:
    this.inherit = true;          // inherit properties from chosen entity
    this.removeSegment = true;    // Remove segment by Default
    this.breakRatio = 3;          // Default height
    this.inclinedSegment = true;  // Default first/last segment
    // Entity/Shape:
    this.entity = undefined;      // Selected entity
    this.shape = undefined;       // Shape derived from entity
    // Coordinates:
    this.point1 = undefined;      // First pick-point
    this.point2 = undefined;      // Second pick-point
    this.cutPoint1 = undefined;   // First cut point on shape
    this.cutPoint2 = undefined;   // Second cut point on shape
    // Toolbar widget:
    this.setUiOptions("PolylineBreakSymbol.ui");
}

PolylineBreakSymbol.prototype = new EAction();


PolylineBreakSymbol.State = {
    SettingShape : 0,
    SettingStartpt : 1,
    SettingEndpt : 2
};

PolylineBreakSymbol.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);
    this.setState(PolylineBreakSymbol.State.SettingShape);
};

PolylineBreakSymbol.prototype.escapeEvent = function() {
    switch (this.state) {
    case PolylineBreakSymbol.State.SettingShape:
        EAction.prototype.escapeEvent.call(this);
        return;    // Stop action
    case PolylineBreakSymbol.State.SettingStartpt:
        this.setState(PolylineBreakSymbol.State.SettingShape);
        break;    // Step back to SettingShape
    case PolylineBreakSymbol.State.SettingEndpt:
        this.setState(PolylineBreakSymbol.State.SettingStartpt);
        break;    // Step back to SettingStartpt
    }
};

PolylineBreakSymbol.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    switch (this.state) {
    case PolylineBreakSymbol.State.SettingShape:
        this.cutPoint1 = undefined;        // Reset first cut point on shape
        this.cutPoint2 = undefined;        // Reset second cut point on shape
        di.setClickMode(RAction.PickEntity);
        // Set prompt and button tips textual:
        var trFirstPoint;
        if (RSpline.hasProxy() && RPolyline.hasProxy()) {    // With PRO resources
            trFirstPoint = qsTr("Choose line, arc, circle, ellipse, spline or polyline to break up");
        }
        else {    // Without PRO resources
            trFirstPoint = qsTr("Choose line, arc, circle or ellipse to break up");
        }
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case PolylineBreakSymbol.State.SettingStartpt:
        this.cutPoint2 = undefined;        // Reset second cut point on shape
        di.setClickMode(RAction.PickCoordinate);    // Missing, but functional coordinateEvent & +Preview
        // Set prompt and button tips textual:
        var trFirstPoint = qsTr("Pick the first point");
        if (this.removeSegment) trFirstPoint = qsTr("Pick the first break point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case PolylineBreakSymbol.State.SettingEndpt:
        di.setClickMode(RAction.PickCoordinate);    // Missing but functional coordinateEvent & +Preview
        // Set prompt and button tips textual:
        var trSecondPoint = qsTr("Pick the second point");
        if (this.removeSegment) trSecondPoint = qsTr("Pick the second break point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    this.setCrosshairCursor();
    EAction.showSnapTools();
};

PolylineBreakSymbol.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);

    // Return nothing when not an entity:
    if (isNull(entity)) {
        return;
    }

    // Store entity & shape:
    this.entity = entity;
    this.shape = this.entity.castToShape();

    // Validation of entity:  All lines 158 to 163 - .entity was .shape
    var cond = isLineBasedEntity(this.entity) ||
                isArcEntity(this.entity) ||
                isCircleEntity(this.entity) ||
                isEllipseEntity(this.entity) ||
                (RSpline.hasProxy() && isSplineEntity(this.entity)) ||
                (RPolyline.hasProxy() && isPolylineEntity(this.entity));

    if (!cond) {   // When validation failed
        // Warn about when unsupported entity if not a preview:
        if (!preview) {
            if (RSpline.hasProxy() && RPolyline.hasProxy()) {    // With PRO resources
                // Standard warning PRO
                EAction.warnNotLineArcCircleEllipseSplinePolyline();
            }
            else {    // Without PRO resources
                // Standard warning non PRO
                EAction.warnNotLineArcCircleEllipse();
            }
        }
        // Return nothing when unsupported entity:
        return;
    }
    else {   // When validation didn't fail
        di.highlightEntity(entity.getId());
    }

    if (!EAction.assertEditable(entity, preview)) {
        return;
    }

    if (!preview) {   // When NOT previewing
        this.setState(PolylineBreakSymbol.State.SettingStartpt);
    }
};

PolylineBreakSymbol.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case PolylineBreakSymbol.State.SettingStartpt:
        this.point1 = event.getModelPosition();
        this.cutPoint1 = this.shape.getClosestPointOnShape(this.point1, true);    // Limited =true
        if (!isValidVector(this.cutPoint1)) this.cutPoint1 = this.point1;
        di.setRelativeZero(this.cutPoint1);
        this.setState(PolylineBreakSymbol.State.SettingEndpt);
        break;
    case PolylineBreakSymbol.State.SettingEndpt:
        this.point2 = event.getModelPosition();
        this.cutPoint2 = this.shape.getClosestPointOnShape(this.point2, true);    // Limited =true
        if (!isValidVector(this.cutPoint2)) this.cutPoint2 = this.point2;
        di.setRelativeZero(this.cutPoint2);

        // Get the Break symbol, apply if any:
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
        }

        // Optionally get the Breakout operation, apply if any:
        if (this.removeSegment) {
            var op = this.getBreakOutOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
        }

        // Return to SettingShape state when done:
        this.setState(PolylineBreakSymbol.State.SettingShape)
        break;
    }
};

PolylineBreakSymbol.prototype.coordinateEventPreview = function(event) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case PolylineBreakSymbol.State.SettingStartpt:
        this.point1 = event.getModelPosition();
        this.cutPoint1 = this.shape.getClosestPointOnShape(this.point1, true);    // Limited =true
        line = new RLine(this.point1, this.cutPoint1);
        di.addAuxShapeToPreview(line);
        this.updatePreview();
        break;
    case PolylineBreakSymbol.State.SettingEndpt:
        this.point2 = event.getModelPosition();
        this.cutPoint2 = this.shape.getClosestPointOnShape(this.point2, true);    // Limited =true
        line = new RLine(this.point2, this.cutPoint2);
        di.addAuxShapeToPreview(line);
        this.updatePreview();
        break;
    }
};

PolylineBreakSymbol.prototype.getOperation = function(preview) {    // Unused var preview =?OBSOLETE
    // Return none when no endpoints:
    if (!isValidVector(this.cutPoint1) || !isValidVector(this.cutPoint2)) {
        return undefined;
    }

    var factor = this.cutPoint1.getDistanceTo(this.cutPoint2) / 3;
    var scaleV = new RVector(factor, factor);
    var segvi = (this.inclinedSegment === true) ? 1 : 0;

    // Define SEED:
    var points = new Array(
        new RVector( 0, 0),
        new RVector( segvi, this.breakRatio),
        new RVector( 3-segvi, this.breakRatio * -1),
        new RVector( 3, 0)
    );

    // Initiate an operation:
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    // Make an oriented and scaled polyline and add to operation:
    var poly = new RPolyline();
    for (var i=0; i<3; ++i) {
        var line = new RLine(points[i],points[i+1]);
        line.scale(scaleV);
        line.move(this.cutPoint1);
        line.rotate(this.cutPoint1.getAngleTo(this.cutPoint2), this.cutPoint1);
        poly.appendShape(line);
    }
    var polylineEntity = new RPolylineEntity(this.getDocument(), new RPolylineData(poly))
    polylineEntity.copyAttributesFrom(getPtr(this.entity));
    var pinherit = (this.inherit === true) ? false : true;  //reverse true/false
    op.addObject(polylineEntity, pinherit);

    // Return the operation:
    return op;
};

PolylineBreakSymbol.prototype.getBreakOutOperation = function(preview) {    // Unused var preview =?OBSOLETE
    var segment;

    // Return the operations:
    if (!isValidVector(this.cutPoint1) || !isValidVector(this.cutPoint2)) {
        return undefined;
    }

    // Initiate an operation:
    var op = new RMixedOperation();
    op.setText(qsTr("Break Out Segment"));

    // ODDITY in BreakOutManual for Arcs | Open Polylines
    // Order cut-points on distance from start:
    if (isArcEntity(this.entity) ||
            (isPolylineEntity(this.entity) && !this.entity.isClosed())) {
        var cutDist1 = this.shape.getDistanceFromStart(this.cutPoint1);
        var cutDist2 = this.shape.getDistanceFromStart(this.cutPoint2);
        if (cutDist1 > cutDist2) {
            // Swap points:
            this.point2 = this.cutPoint1;
            this.cutPoint1 = this.cutPoint2;
            this.cutPoint2 = this.point2;
        }
    }

    // DIFFERECE with BreakOutManual for Circles
    // Order cut-points CW:  (.getDistanceFromStart returns 1e+300)
    if (isCircleEntity(this.entity)) {
        var cutAngle1 = this.entity.getCenter().getAngleTo(this.cutPoint1);
        var cutAngle2 = this.entity.getCenter().getAngleTo(this.cutPoint2);
        if (cutAngle2 > cutAngle1) {
            // Swap points:
            this.point2 = this.cutPoint1;
            this.cutPoint1 = this.cutPoint2;
            this.cutPoint2 = this.point2;
        }
    }

    // Get 3 segments resulting from:
    // ShapeAlgorithms.autoSplitManual(shape, cutDist1, cutDist2, cutPos1, cutPos2, position, extend);
    // Returns an array with rest from entity start, rest from entity end and the segment in between.
    // Returns undefined when the segment length would be zero.
    var newSegments = ShapeAlgorithms.autoSplitManual(this.shape,
                                                        undefined,     // Is calculate from cut point
                                                        undefined,     // Is calculate from cut point
                                                        this.cutPoint1,
                                                        this.cutPoint2,
                                                        RVector.getAverage(this.cutPoint1, this.cutPoint2),
                                                        false);        // NOT extending Arcs

    // Add the first segment with the same attributes as entity, if any:
    if (!isNull(newSegments[0])) {
        segment = shapeToEntity(this.entity.getDocument(), newSegments[0]);
        if (!isNull(segment)) {
            segment.copyAttributesFrom(getPtr(this.entity));
            op.addObject(segment, false);    // NOTuseCurrentAttributes
        }
    }

    // Add the last segment with the same attributes as entity, if any:
    if (!isNull(newSegments[1])) {
        segment = shapeToEntity(this.entity.getDocument(), newSegments[1])
        if (!isNull(segment)) {
            segment.copyAttributesFrom(getPtr(this.entity));
            op.addObject(segment, false);    // NOTuseCurrentAttributes
        }
    }

    // Delete the original entity:
    op.deleteObject(this.entity);

    // Return the operation:
    return op;
};

PolylineBreakSymbol.prototype.slotRemoveSegmentChanged = function(bool) {
    this.removeSegment = bool;
    this.updatePreview(true);
};

PolylineBreakSymbol.prototype.slotBreakRatioChanged = function(index) {
    this.breakRatio = index + 1;
    this.updatePreview(true);
};

PolylineBreakSymbol.prototype.slotIncSegChanged = function(bool) {
    this.inclinedSegment = bool;
    this.updatePreview(true);
};

PolylineBreakSymbol.prototype.slotInheritChanged = function(bool) {
    this.inherit = bool;
    this.updatePreview(true);
};
