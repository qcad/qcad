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

include("../ModifyCorner.js");

function Bevel(guiAction) {
    ModifyCorner.call(this, guiAction);

    this.distance1 = 1.0;
    this.distance2 = 1.0;

    this.setUiOptions("Bevel.ui");
}

Bevel.prototype = new ModifyCorner();

Bevel.prototype.beginEvent = function() {
    ModifyCorner.prototype.beginEvent.call(this);
};

Bevel.prototype.getOperation = function(preview) {
    if (!isEntity(this.entity1) || !isEntity(this.entity2)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();

    var success = Bevel.bevel(
            op,
            this.entity1.clone(), this.pos1,
            this.entity2.clone(), this.pos2,
            this.trim,
            this.distance1, this.distance2,
            preview);

    if (!success && !preview) {
        EAction.handleUserWarning(qsTr("The two entities cannot be bevelled."));
    }

    return op;
};

/**
 * Bevels or extends the given entity2 to the intersection point of the
 * entity2 and the limitingShape.
 *
 * \param entity1 First entity which will be bevelled.
 * \param pos1 Coordinate that was clicked when the user selected entity1.
 * \param entity2 Second entity which will be bevelled.
 * \param pos2 Coordinate that was clicked when the user selected entity2.
 * \param trim true: Trim both entities to bevel line.
 * \param distance1 Distance of bevel line from end point of entity1.
 * \param distance2 Distance of bevel line from end point of entity2.
 * \param preview Operation is used for preview.
 */
Bevel.bevel = function(op, entity1, pos1, entity2, pos2, trim, distance1, distance2, preview) {
    if (!isEntity(entity1) || !isValidVector(pos1) ||
            !isEntity(entity2) || !isValidVector(pos2) ||
            !isBoolean(trim)) {
        return false;
    }

    var shape1P = entity1.getClosestShape(pos1);
    var shape2P = entity2.getClosestShape(pos2);
    var shape1 = shape1P.data();
    var shape2 = shape2P.data();

    if (!isShape(shape1) || !isShape(shape2)) {
        return false;
    }

    if (isPolylineEntity(entity1) && !isPolylineEntity(entity2)) {
        return false;
    }

    if (!isPolylineEntity(entity1) && isPolylineEntity(entity2)) {
        return false;
    }

    if (isPolylineEntity(entity1) && isPolylineEntity(entity2)) {
        if (entity1.getId()!=entity2.getId()) {
            return false;
        }
    }

    // find out whether we're bevelling within a polyline:
    var polyline = undefined;
    var segments = undefined;
    var shapeIndex1 = undefined;
    var shapeIndex2 = undefined;
    if (entity1.getId()==entity2.getId() && isPolylineEntity(entity1)) {
        polyline = entity1.getData().castToShape();
        segments = polyline.getExploded();
        var minDistance1 = undefined;
        var minDistance2 = undefined;
        var segment;
        var distance;
        for (var i=0; i<segments.length; ++i) {
            segment = segments[i];

            distance = segment.getDistanceTo(pos1);
            if (isNull(minDistance1) || distance<minDistance1) {
                minDistance1 = distance;
                shapeIndex1 = i;
                shape1 = segment.clone();
            }

            distance = segment.getDistanceTo(pos2);
            if (isNull(minDistance2) || distance<minDistance2) {
                minDistance2 = distance;
                shapeIndex2 = i;
                shape2 = segment.clone();
            }
        }

        if (shapeIndex1==shapeIndex2) {
            return false;
        }

        if (shapeIndex2<shapeIndex1) {
            var tmp = shapeIndex1;
            shapeIndex1 = shapeIndex2;
            shapeIndex2 = tmp;

            tmp = shape1;
            shape1 = shape2;
            shape2 = tmp;

            tmp = distance1;
            distance1 = distance2;
            distance2 = tmp;
        }
    }

    // get intersection point(s) between two shapes:
    var sol = shape1.getIntersectionPoints(shape2, false);

    if (sol.length===0) {
        return false;
    }

    var trimmed1 = shape1.clone();
    var trimmed2 = shape2.clone();

    // trim shapes to intersection:
    var start1 = false;
    var is = pos2.getClosest(sol);
    var ending1 = trimmed1.getTrimEnd(pos1, is);
    switch (ending1) {
    case RS.EndingStart:
        trimmed1.trimStartPoint(is);
        start1 = true;
        break;
    case RS.EndingEnd:
        trimmed1.trimEndPoint(is);
        start1 = false;
        break;
    default:
        break;
    }

    var start2 = false;
    is = pos1.getClosest(sol);
    ending2 = trimmed2.getTrimEnd(pos2, is);
    switch (ending2) {
    case RS.EndingStart:
        trimmed2.trimStartPoint(is);
        start2 = true;
        break;
    case RS.EndingEnd:
        trimmed2.trimEndPoint(is);
        start2 = false;
        break;
    default:
        break;
    }

    // find definitive bevel points:
    var bp1 = trimmed1.getPointsWithDistanceToEnd(distance1, start1 ? RS.FromStart : RS.FromEnd);
    if (bp1.length!=1) {
        return false;
    }
    bp1 = bp1[0];

    var bp2 = trimmed2.getPointsWithDistanceToEnd(distance2, start2 ? RS.FromStart : RS.FromEnd);
    if (bp2.length!=1) {
        return false;
    }
    bp2 = bp2[0];

    // final trim:
    if (trim===true) {
        switch (ending1) {
        case RS.EndingStart:
            trimmed1.trimStartPoint(bp1);
            break;
        case RS.EndingEnd:
            trimmed1.trimEndPoint(bp1);
            break;
        default:
            break;
        }

        switch (ending2) {
        case RS.EndingStart:
            trimmed2.trimStartPoint(bp2);
            break;
        case RS.EndingEnd:
            trimmed2.trimEndPoint(bp2);
            break;
        default:
            break;
        }

        // trim polyline segment and add bevel segment:
        if (!isNull(polyline)) {
            var trimmedPolyline = polyline.clone();
            trimmedPolyline.clear();
            for (i=0; i<segments.length; ++i) {
                segment = segments[i];

                // add first trimmed segment and bevel segment:
                if (i==shapeIndex1) {
                    if (trimmed1.getStartPoint().equalsFuzzy(bp1)) {
                        trimmed1.reverse();
                        trimmed1.setStartPoint(shape1.getStartPoint());
                    }
                    trimmedPolyline.appendShape(trimmed1);

                    trimmedPolyline.appendVertex(bp2);

                    if (trimmed2.getEndPoint().equalsFuzzy(bp2)) {
                        trimmed2.reverse();
                        trimmed2.setEndPoint(shape2.getEndPoint());
                    }
                    trimmedPolyline.appendShape(trimmed2);
                    i = shapeIndex2;
                }

                // add unaffected segment:
                else {
                    trimmedPolyline.appendShape(segment.data());
                }
            }

            entity1.setShape(trimmedPolyline);
            op.addObject(entity1, false);
        }

        // add new trimmed entities:
        else {
            if (isFunction(entity1.setShape)) {
                entity1.setShape(trimmed1);
                op.addObject(entity1, false);
            }
            else {
                EAction.handleUserWarning(qsTr("First entity cannot be trimmed."));
            }

            if (isFunction(entity2.setShape)) {
                entity2.setShape(trimmed2);
                op.addObject(entity2, false);
            }
            else {
                EAction.handleUserWarning(qsTr("Second entity cannot be trimmed."));
            }
        }
    }

    if (isNull(polyline) || trim!==true) {
        // add bevel line:
        var bevel = new RLine(bp1, bp2);
        op.addObject(new RLineEntity(entity1.getDocument(), new RLineData(bevel)));
    }

    return true;
};

Bevel.prototype.slotLength1Changed = function(value) {
    this.distance1 = value;
}

Bevel.prototype.slotLength2Changed = function(value) {
    this.distance2 = value;
}

