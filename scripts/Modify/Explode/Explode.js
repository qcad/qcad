/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
include("scripts/Block/Block.js");
include("scripts/ShapeAlgorithms.js");

function Explode(guiAction) {
    Modify.call(this, guiAction);
}

Explode.prototype = new Modify();

Explode.getPreferencesCategory = function() {
    return [qsTr("Modify"), qsTr("Explode")];
};

Explode.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var storage = document.getStorage();
    var ids = document.querySelectedEntities();
    var i, k, e, n;
    var polyline, shapes, shape;

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    for (i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isNull(entity)) {
            debugger;
        }

        // these entity types are not explodable:
        if (isPointEntity(entity) ||
            isLineEntity(entity) ||
            isArcEntity(entity)) {
            continue;
        }

        var newShapes = [];
        var newEntities = [];

        // explode ellipse into polyline with arc segments:
        if (isEllipseEntity(entity)) {
            var ellipse = entity.getData().castToShape();
            var s = RSettings.getIntValue("Explode/EllipseSegments", 32);
            polyline = ShapeAlgorithms.approximateEllipse(ellipse, s);
            newShapes.push(polyline);
        }

        // explode polyline into line and arc segments:
        else if (isPolylineEntity(entity)) {
            polyline = entity.getData().castToShape();
            var polySegments = polyline.getExploded();
            if (polySegments.length>0) {
                for (k=0; k<polySegments.length; k++) {
                    shape = polySegments[k].data();

                    // last shape might have zero length if polyline is closed geometrically and logically:
                    if (k===polySegments.length-1) {
                        if (shape.getLength()<1.0e-5) {
                            break;
                        }
                    }

                    newShapes.push(shape.clone());
                }
            }
        }

        // explode spline into polyline with line segments:
        else if (isSplineEntity(entity)) {
            var spline = entity.getData().castToShape();
            var seg = RSettings.getIntValue("Explode/SplineSegments", 64);
            var pl = spline.toPolyline(seg);
            pl.simplify();
            newShapes.push(pl);
        }

        // explode hatch into lines / solid fill into boundary:
        else if (isHatchEntity(entity)) {
            var painterPaths = entity.getPainterPaths(false);
            for (k=0; k<painterPaths.length; k++) {
                shapes = painterPaths[k].getShapes();
                for (n=0; n<shapes.length; n++) {
                    shape = shapes[n].data();
                    if (isSplineShape(shape)) {
                        shape = ShapeAlgorithms.splineToLineOrArc(shape, 0.01);
                    }
                    newShapes.push(shape.clone());
                }
            }
        }

        // explode dimension into lines, solids (triangles) and a text entity:
        else if (isDimensionEntity(entity)) {
            shapes = entity.getShapes();
            for (k=0; k<shapes.length; k++) {
                newShapes.push(shapes[k].data());
            }
            var textData = entity.getData().getTextData();
            e = new RTextEntity(entity.getDocument(), textData);
            e.setSelected(true);
            e.copyAttributesFrom(entity.data());
            newEntities.push(e);
        }

        // explode leaders into lines and solids (triangles):
        else if (isLeaderEntity(entity)) {
            shapes = entity.getShapes();
            for (k=0; k<shapes.length; k++) {
                shape = shapes[k].data();
                newShapes.push(shape.clone());
            }
        }

        // explode solids into polylines:
        else if (isSolidEntity(entity)) {
            shapes = entity.getShapes();
            for (k=0; k<shapes.length; k++) {
                shape = shapes[k].data();
                if (shape.countVertices()===4) {
                    var v3 = shape.getVertexAt(3);
                    shape.setVertexAt(3, shape.getVertexAt(2));
                    shape.setVertexAt(2, v3);
                }
                newShapes.push(shape.clone());
            }
        }

        // explode text entities into lines, arcs and splines:
        else if (isTextEntity(entity)) {
            var painterPaths = entity.getPainterPaths();
            for (k=0; k<painterPaths.length; k++) {
                // ignore text bounding box, used only to display instead of
                // text at small zoom factors:
                if (painterPaths[k].getFeatureSize()<0) {
                    continue;
                }
                shapes = painterPaths[k].getShapes();
                for (n=0; n<shapes.length; n++) {
                    shape = shapes[n];
                    if (isSplineShape(shape)) {
                        shape = ShapeAlgorithms.splineToLineOrArc(shape, 1e-6 * painterPaths[k].getFeatureSize());
                    }

                    if (!isNull(shape)) {
                        newShapes.push(shape.clone());
                    }
                }
            }
        }

        // explode attribute entities into texts:
        else if (isAttributeEntity(entity)) {
            // create text data from attribute data:
            var d = new RTextData(entity.getData());
            // unlink from parent (block ref):
            d.setParentId(RObject.INVALID_ID);
            newEntities.push(new RTextEntity(document, d));
        }

        // explode block reference into contained entities:
        else if (isBlockReferenceEntity(entity)) {
            var data = entity.getData();
            var subIds = document.queryBlockEntities(data.getReferencedBlockId());
            for (var col=0; col<data.getColumnCount(); col++) {
                for (var row=0; row<data.getRowCount(); row++) {
                    for (k=0; k<subIds.length; k++) {
                        var subEntity = data.queryEntity(subIds[k]);
                        if (isNull(subEntity)) {
                            continue;
                        }

                        // ignore attribute definitions:
                        if (isAttributeDefinitionEntity(subEntity)) {
                            continue;
                        }

                        e = subEntity.clone();
                        data.applyColumnRowOffsetTo(e, col, row);
                        storage.setObjectId(e, RObject.INVALID_ID);
                        e.setBlockId(document.getCurrentBlockId());
                        e.setSelected(true);
                        newEntities.push(e);
                    }
                }
            }
        }


        // add explosion result and delete original:
        if (newShapes.length!==0 || newEntities.length!==0) {
            // add entities based on shapes that resulted from the explosion:
            for (k=0; k<newShapes.length; k++) {
                shape = newShapes[k];
                e = shapeToEntity(entity.getDocument(), shape);
                if (!isNull(e)) {
                    e.setSelected(true);
                    e.copyAttributesFrom(entity.data());
                    op.addObject(e, false);
                }
            }

            // add entities based on entities that resulted from the explosion:
            for (k=0; k<newEntities.length; k++) {
                op.addObject(newEntities[k], false);
            }

            // delete original entity:
            op.deleteObject(entity);
        }
    }

    di.applyOperation(op);

    this.terminate();
};

