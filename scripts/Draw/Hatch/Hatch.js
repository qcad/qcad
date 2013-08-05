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

/**
 * \defgroup ecma_draw_hatch Hatch Drawing Tool
 * \ingroup ecma_draw
 *
 * \brief This module contains the ECMAScript implementation of the hatch
 * drawing tool.
 */
include("../Draw.js");
include("HatchDialog.js");

/**
 * \class Hatch
 * \brief Create hatch for selected boundary.
 * \ingroup ecma_draw_hatch
 */
function Hatch(guiAction) {
    Draw.call(this, guiAction);

    this.errorPoint = undefined;
}

Hatch.prototype = new Draw();
Hatch.Tolerance = 0.001;

Hatch.prototype.beginEvent = function() {
    var i, entityId, entity, shape;
    
    Draw.prototype.beginEvent.call(this);

    // analyze selection:
    var document = EAction.getDocument();
    this.selectedIds = document.querySelectedEntities();

    // no selection:
    if (this.selectedIds.length===0) {
        EAction.handleUserWarning(qsTr("No boundary selected."));
        this.terminate();
        return;
    }

    // verify boundary entities:
    for (i = 0; i < this.selectedIds.length; i++) {
        entityId = this.selectedIds[i];
        entity = document.queryEntityDirect(entityId);
        if (!this.verifyBoundaryEntity(entity)) {
            this.terminate();
            return;
        }
    }

    // collect hatch data (boundary elements ordered as loops):
    this.hatchData = new RHatchData();
    document.traversed = new Object();

    for (i = 0; i < this.selectedIds.length; i++) {
        entityId = this.selectedIds[i];
        if (document.traversed[entityId]) {
            continue;
        }
        entity = document.queryEntityDirect(entityId);
        if (!this.traverse(entity, document)) {
            this.updatePreview();
            var di = EAction.getDocumentInterface();
            di.keepPreview();
            EAction.handleUserWarning(
                        qsTr("Loop not closed at point %1/%2.")
                        .arg(isNull(this.connectionPoint) ? "?" : this.connectionPoint.x)
                        .arg(isNull(this.connectionPoint) ? "?" : this.connectionPoint.y),
                        true);
            this.terminate();
            return;
        }
    }

    // show hatch dialog for hatch pattern parameters:
    var dialog = new HatchDialog(this);
    var hatchDataDlg = dialog.show();
    if (isNull(hatchDataDlg)) {
        this.terminate();
        return;
    }

    this.hatchData.setSolid(hatchDataDlg.isSolid());
    this.hatchData.setScale(hatchDataDlg.getScale());
    this.hatchData.setAngle(hatchDataDlg.getAngle());
    this.hatchData.setPatternName(hatchDataDlg.getPatternName());

    var di = this.getDocumentInterface();
    var hatch = new RHatchEntity(
        this.getDocument(),
        this.hatchData
    );
    var op = new RAddObjectOperation(hatch);
    di.applyOperation(op);

    this.terminate();
};


Hatch.prototype.verifyBoundaryEntity = function(entity) {
    if (isBlockReferenceEntity(entity)) {
        var document = EAction.getDocument();
        var blockReferenceData = entity.getData();
        var ids = document.queryBlockEntities(blockReferenceData.getReferencedBlockId());
        var ret = true;
        for (var i=0; i<ids.length; i++) {
            var bEntity = blockReferenceData.queryEntity(ids[i]);
            if (bEntity.isNull()) {
                continue;
            }
            if (!bEntity.isVisible()) {
                continue;
            }
            ret = ret && this.verifyBoundaryEntity(bEntity);
        }
        return ret;
    }

    if (isLineEntity(entity) ||
        isArcEntity(entity) ||
        isCircleEntity(entity) ||
        isEllipseEntity(entity) ||
        isPolylineEntity(entity) ||
        isSplineEntity(entity)) {

        return true;

    }

    EAction.handleUserWarning(
                qsTr("Each boundary entity must be a line, arc, " +
                     "circle, ellipse arc, ellipse, polyline or spline. " +
                     "Found:") + " " +
                entityTypeToString(entity.getType(), false));

    return false;
};

Hatch.prototype.isClosedPolyline = function(entity) {
    return isPolylineEntity(entity) && entity.isLogicallyClosed();
};

Hatch.prototype.isClosedCurve = function(entity) {
    return isCircleEntity(entity) ||
            (isEllipseEntity(entity) && entity.isFullEllipse()) ||
            (isSplineEntity(entity) && entity.isClosed());
};

Hatch.prototype.traverse = function(entity, entitySource, candidateIds) {
    var i;

    if (isNull(candidateIds)) {
        candidateIds = this.selectedIds;
    }

    // handle closed polyline loops:
    if (this.isClosedPolyline(entity)) {
        this.hatchData.newLoop();
        var segments = entity.getExploded();
        for (i=0; i<segments.length; i++) {
            var segment = segments[i];
            this.hatchData.addBoundary(segment);
        }
        entitySource.traversed[entity.getId()] = true;
        return true;
    }

    // handle circle, full ellipse and closed spline loops:
    if (this.isClosedCurve(entity)) {
        this.hatchData.newLoop();
        this.hatchData.addBoundary(entity.getData().castToShape());
        entitySource.traversed[entity.getId()] = true;
        return true;
    }

    var document = EAction.getDocument();

    // handle block reference:
    if (isBlockReferenceEntity(entity)) {
        var blockReferenceData = entity.getData();
        blockReferenceData.traversed = new Object();
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
            this.traverse(bEntity, blockReferenceData, ids);
        }
        return ret;
    }

    // handle 'loose' boundary elements:

    var currentShape;
    var loopStartPoint;

    this.hatchData.newLoop();
    entitySource.traversed[entity.getId()] = true;
    var shape = entity.getData().castToShape().clone();
    this.hatchData.addBoundary(shape);
    currentShape = shape;
    loopStartPoint = shape.getStartPoint();
    // find connected entities:
    var done2 = true;
    this.connectionPoint = undefined;
    do {
        done2 = true;
        this.connectionPoint = currentShape.getEndPoint();
        for (i = 0; i < candidateIds.length; i++) {
            var entityId = candidateIds[i];
            if (entitySource.traversed[entityId]) {
                continue;
            }

            if (isFunction(entitySource.queryEntityDirect)) {
                // query entity from document:
                entity = entitySource.queryEntityDirect(entityId);
            }
            else {
                // query entity from block reference:
                entity = entitySource.queryEntity(entityId);
            }

            if (isBlockReferenceEntity(entity)) {
                continue;
            }

            if (this.isClosedCurve(entity) || this.isClosedPolyline(entity)) {
                continue;
            }

            var sp = entity.getStartPoint();
            var ep = entity.getEndPoint();

            var spConnects = this.connectionPoint.equalsFuzzy(sp, Hatch.Tolerance);
            var epConnects = this.connectionPoint.equalsFuzzy(ep, Hatch.Tolerance);

            if (spConnects || epConnects) {
                entitySource.traversed[entityId] = true;
                shape = entity.getData().castToShape().clone();
                if (epConnects) {
                    shape.reverse();
                }
                this.hatchData.addBoundary(shape);
                currentShape = shape;
                done2 = false;
                //qDebug("Hatch: next loop shape: ", shape, epConnects ? " (reversed)" : "");
                break;
            }

            //qDebug("gap sp: ", this.connectionPoint.getDistanceTo(sp));
            //qDebug("gap ep: ", this.connectionPoint.getDistanceTo(ep));
        }
    } while(!done2);

    if (!this.connectionPoint.equalsFuzzy(loopStartPoint, Hatch.Tolerance)) {
        this.errorPoint = this.connectionPoint;
        //qDebug("start does not connect to end by: ", this.connectionPoint.getDistanceTo(loopStartPoint));
        return false;
    }

    return true;
};

Hatch.prototype.getAuxPreview = function() {
    if (!isValidVector(this.errorPoint)) {
        return undefined;
    }

    var ret = [];

    var view = EAction.getGraphicsView();
    if (isNull(view)) {
        return undefined;
    }

    var radius = view.mapDistanceFromView(10.0);

    ret.push(new RCircle(this.errorPoint, radius));

    return ret;
};
