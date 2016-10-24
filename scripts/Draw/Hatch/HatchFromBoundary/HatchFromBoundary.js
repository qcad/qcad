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
 * \defgroup ecma_draw_hatch Hatch Drawing Tool
 * \ingroup ecma_draw
 *
 * \brief This module contains the ECMAScript implementation of the hatch
 * drawing tool.
 */
include("scripts/EAction.js");
include("../HatchDialog.js");

/**
 * \class Hatch
 * \brief Create hatch for selected boundary.
 * \ingroup ecma_draw_hatch
 */
function HatchFromBoundary(guiAction) {
    EAction.call(this, guiAction);
}

HatchFromBoundary.prototype = new EAction();
HatchFromBoundary.tolerance = 0.001;
HatchFromBoundary.errorPoint = undefined;

HatchFromBoundary.prototype.beginEvent = function() {
    var i, entityId, entity, shape;
    
    EAction.prototype.beginEvent.call(this);

    var doc = this.getDocument();
    var di = this.getDocumentInterface();

    // analyze selection:
    var selectedIds = doc.querySelectedEntities();

    // no selection:
    if (selectedIds.length===0) {
        EAction.handleUserWarning(qsTr("No boundary selected."));
        this.terminate();
        return;
    }

    if (!HatchFromBoundary.verifyBoundary(doc, selectedIds)) {
        this.terminate();
        return;
    }

    // collect hatch data (boundary elements ordered as loops):
    var hatchData = HatchFromBoundary.createHatchData(doc, selectedIds);

    if (isNull(hatchData)) {
        this.updatePreview();
        di.keepPreview();
        EAction.handleUserWarning(
                    qsTr("Loop not closed at point %1/%2.")
                    .arg(isNull(HatchFromBoundary.connectionPoint) ? "?" : HatchFromBoundary.connectionPoint.x)
                    .arg(isNull(HatchFromBoundary.connectionPoint) ? "?" : HatchFromBoundary.connectionPoint.y),
                    true);
        this.terminate();
        return;
    }

    // show hatch dialog for hatch pattern parameters:
    var dialog = new HatchDialog(this);
    var hatchDataDlg = dialog.show();
    if (isNull(hatchDataDlg)) {
        this.terminate();
        return;
    }

    hatchData.setSolid(hatchDataDlg.isSolid());
    hatchData.setScale(hatchDataDlg.getScale());
    hatchData.setAngle(hatchDataDlg.getAngle());
    hatchData.setPatternName(hatchDataDlg.getPatternName());

    var hatch = new RHatchEntity(doc, hatchData);
    var op = new RAddObjectOperation(hatch, this.getToolTitle());
    di.applyOperation(op);

    this.terminate();
};

HatchFromBoundary.prototype.getAuxPreview = function() {
    if (!isValidVector(HatchFromBoundary.errorPoint)) {
        return undefined;
    }

    var ret = [];

    var view = EAction.getGraphicsView();
    if (isNull(view)) {
        return undefined;
    }

    var radius = view.mapDistanceFromView(10.0);

    ret.push(new RCircle(HatchFromBoundary.errorPoint, radius));

    return ret;
};

/**
 * Verifies the entities entityIds as potential hatch boundary.
 */
HatchFromBoundary.verifyBoundary = function(doc, entityIds) {
    for (var i = 0; i < entityIds.length; i++) {
        var entityId = entityIds[i];
        var entity = doc.queryEntityDirect(entityId);
        if (!HatchFromBoundary.verifyBoundaryEntity(doc, entity)) {
            return false;
        }
    }

    return true;
};

/**
 * Verifies the given entity as potential hatch boundary.
 */
HatchFromBoundary.verifyBoundaryEntity = function(doc, entity) {
    if (isBlockReferenceEntity(entity)) {
        var blockReferenceData = entity.getData();
        var ids = doc.queryBlockEntities(blockReferenceData.getReferencedBlockId());
        var ret = true;
        for (var i=0; i<ids.length; i++) {
            var bEntity = blockReferenceData.queryEntity(ids[i]);
            if (bEntity.isNull()) {
                continue;
            }
            if (!bEntity.isVisible()) {
                continue;
            }
            ret = ret && HatchFromBoundary.verifyBoundaryEntity(doc, bEntity);
        }
        return ret;
    }

    if (isLineEntity(entity) ||
        isArcEntity(entity) ||
        isCircleEntity(entity) ||
        isEllipseEntity(entity) ||
        isPolylineEntity(entity) ||
        isFaceEntity(entity) ||
        isSplineEntity(entity)) {

        return true;
    }

    if (!isNull(entity)) {
        EAction.handleUserWarning(
                    qsTr("Each boundary entity must be a line, arc, " +
                         "circle, ellipse arc, ellipse, polyline or spline. " +
                         "Found:") + " " +
                    entityTypeToString(entity.getType(), false));
    }

    return false;
};

/**
 * \return RHatchData object created from the given boundary entities entityIds or undefined.
 */
HatchFromBoundary.createHatchData = function(doc, entityIds, ignoreOpenLoops) {
    if (isNull(ignoreOpenLoops)) {
        ignoreOpenLoops = false;
    }

    var hatchData = new RHatchData();
    hatchData.setDocument(doc);

    doc.traversed = {};
    HatchFromBoundary.errorPoint = undefined;

    for (var i=0; i<entityIds.length; i++) {
        var entityId = entityIds[i];
        if (doc.traversed[entityId]) {
            continue;
        }
        var entity = doc.queryEntityDirect(entityId);
        if (!HatchFromBoundary.traverse(hatchData, doc, entity, entityIds)) {
            if (ignoreOpenLoops) {
                continue;
            }
            else {
                return undefined;
            }
        }
    }

    return hatchData;
};

/**
 * Traverses the given candidates recursively for connected entities.
 * Resulting loops are appened to the given hatch data.
 */
HatchFromBoundary.traverse = function(hatchData, docOrBlockRef, entity, candidateIds) {
    var i;

    // handle closed polyline loops:
    if (HatchFromBoundary.isClosedPolyline(entity)) {
        if (entity.getLength()<RS.PointTolerance) {
            // zero length closed polyline: safe to ignore:
            return true;
        }

        hatchData.newLoop();
        var segments = entity.getExploded();
        for (i=0; i<segments.length; i++) {
            var segment = segments[i];
            hatchData.addBoundary(segment);
        }
        // TODO: add polyline as boundary:
//        hatchData.addBoundary(entity.getData().castToShape());
        docOrBlockRef.traversed[entity.getId()] = true;
        return true;
    }

    // handle circle, full ellipse and closed spline loops:
    if (HatchFromBoundary.isClosedCurve(entity)) {
        hatchData.newLoop();
        hatchData.addBoundary(entity.getData().castToShape());
        docOrBlockRef.traversed[entity.getId()] = true;
        return true;
    }

    var document = EAction.getDocument();

    // handle block reference:
    if (isBlockReferenceEntity(entity)) {
        var blockReferenceData = entity.getData();
        blockReferenceData.traversed = {};
        var ids = document.queryBlockEntities(blockReferenceData.getReferencedBlockId());
        var ret = true;
        for (i=0; i<ids.length; i++) {
            if (blockReferenceData.traversed[ids[i]]) {
                continue;
            }

            var bEntity = blockReferenceData.queryEntity(ids[i]);
            if (bEntity.isNull()) {
                continue;
            }
            if (!bEntity.isVisible()) {
                continue;
            }
            if (!HatchFromBoundary.traverse(hatchData, blockReferenceData, bEntity, ids)) {
                ret = false;
                break;
            }
        }
        return ret;
    }

    var shape = entity.getData().castToShape().clone();
    if (isFunction(shape.getLength)) {
        if (shape.getLength()<RS.PointTolerance) {
            // ignore zero length entity:
            return false;
        }
    }

    // connect 'loose' boundary elements into loops:
    hatchData.newLoop();
    docOrBlockRef.traversed[entity.getId()] = true;
    hatchData.addBoundary(shape);
    var currentShape = shape;
    var loopStartPoint = shape.getStartPoint();

    // find connected entities:
    var done2 = true;
    HatchFromBoundary.connectionPoint = undefined;
    do {
        done2 = true;
        HatchFromBoundary.connectionPoint = currentShape.getEndPoint();
        for (i = 0; i < candidateIds.length; i++) {
            var entityId = candidateIds[i];
            if (docOrBlockRef.traversed[entityId]) {
                continue;
            }

            if (isFunction(docOrBlockRef.queryEntityDirect)) {
                // query entity from document:
                entity = docOrBlockRef.queryEntityDirect(entityId);
            }
            else {
                // query entity from block reference:
                entity = docOrBlockRef.queryEntity(entityId);
            }

            if (isBlockReferenceEntity(entity)) {
                continue;
            }

            if (HatchFromBoundary.isClosedCurve(entity) || HatchFromBoundary.isClosedPolyline(entity)) {
                continue;
            }

            if (isFunction(entity.getLength)) {
                // ignore zero length entities:
                if (entity.getLength()<RS.PointTolerance) {
                    docOrBlockRef.traversed[entityId] = true;
                    continue;
                }
            }

            var sp = entity.getStartPoint();
            var ep = entity.getEndPoint();

            var spConnects = HatchFromBoundary.connectionPoint.equalsFuzzy(sp, HatchFromBoundary.tolerance);
            var epConnects = HatchFromBoundary.connectionPoint.equalsFuzzy(ep, HatchFromBoundary.tolerance);

            if (spConnects || epConnects) {
                docOrBlockRef.traversed[entityId] = true;
                shape = entity.getData().castToShape().clone();
                if (epConnects) {
                    shape.reverse();
                }
                hatchData.addBoundary(shape);
                currentShape = shape;
                done2 = false;
                //qDebug("Hatch: next loop shape: ", shape, epConnects ? " (reversed)" : "");
                break;
            }

            //qDebug("gap sp: ", HatchFromBoundary.connectionPoint.getDistanceTo(sp));
            //qDebug("gap ep: ", HatchFromBoundary.connectionPoint.getDistanceTo(ep));
        }
    } while (!done2);

    if (!HatchFromBoundary.connectionPoint.equalsFuzzy(loopStartPoint, HatchFromBoundary.tolerance)) {
        HatchFromBoundary.errorPoint = HatchFromBoundary.connectionPoint;
        hatchData.cancelLoop();
        //qDebug("start does not connect to end by: ", HatchFromBoundary.connectionPoint.getDistanceTo(loopStartPoint));
        return false;
    }

    return true;
};

HatchFromBoundary.isClosedPolyline = function(entity) {
    return (isPolylineEntity(entity) && entity.isGeometricallyClosed()) || isFaceEntity(entity);
};

HatchFromBoundary.isClosedCurve = function(entity) {
    return isCircleEntity(entity) ||
            (isEllipseEntity(entity) && entity.isFullEllipse()) ||
            (isSplineEntity(entity) && entity.isClosed());
};
