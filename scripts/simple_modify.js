/**
 * Simple Modification API, mainly designed for use in the ECMAScript console.
 *
 * Entity references:
 *
 * Most functions in this module accept entity references in various forms:
 *
 * - an entity ID (number)
 * - an entity object (REntity, looked up by ID in the current document)
 * - a shape (RShape): the operation is applied to the shape only, the
 *   drawing is not changed; shapes are modified in place where possible,
 *   otherwise the resulting shapes are returned
 * - a position in the drawing (RVector or [x,y] array): the entity closest
 *   to that position is used and the position also serves as the click
 *   position where one is needed (e.g. to choose the end to trim).
 *
 * Functions that need a click position (trim, round, bevel, breakOut,
 * offset, ...) accept an optional position (RVector or [x,y]) after each
 * entity reference. If no click position is given, the middle point of the
 * entity is used.
 *
 * Operations are applied to the current document immediately or, if a
 * transaction was started with startTransaction, when endTransaction is
 * called.
 */

include("scripts/ShapeAlgorithms.js");

/**
 * Pastes the given document into the current document or into the second given document.
 * \ingroup ecma_simple
 *
 * \param docSource RDocument to paste
 * \param diDestination RDocumentInterface to paste into (or undefined for current document)
 * \param offset Offset RVector or [x,y] array
 * \param scale Scale factor
 * \param rotation Rotation angle in degrees
 * \param flipHorizontal True to flip horizontally
 * \param flipVertial True to flip vertically
 * \param toCurrentLayer Paste all entities to the current layer of the target document
 * \param overwriteLayers Overwrite existing layers in the target document with layers
 * from the source document
 * \param overwriteBlocks Overwrite existing blocks in the target document with blocks
 * from the source document
 */
function paste(docSource, diDestination, offset, scale, rotation, flipHorizontal, flipVertical, toCurrentLayer, overwriteLayers, overwriteBlocks) {
    if (isArray(offset)) {
        return paste(docSource, diDestination, new RVector(offset), scale, rotation, flipHorizontal, flipVertical, toCurrentLayer, overwriteLayers, overwriteBlocks);
    }

    var op = new RPasteOperation(docSource);
    op.setOffset(offset);
    op.setScale(scale);
    op.setRotation(deg2rad(rotation));
    op.setFlipHorizontal(flipHorizontal);
    op.setFlipVertical(flipVertical);
    op.setToCurrentLayer(toCurrentLayer);
    op.setOverwriteLayers(overwriteLayers);
    op.setOverwriteBlocks(overwriteBlocks);

    if (isNull(diDestination)) {
        diDestination = getDocumentInterface();
    }
    diDestination.applyOperation(op);
}

/**
 * \internal
 * Parses entity references with optional click positions from the given
 * argument list.
 *
 * A reference is an entity ID, an entity, a shape or a position. A reference
 * that is not a position may be followed by an optional position (the click
 * position). A position used as reference is also the click position.
 *
 * \param args Arguments object or array
 * \param count Number of references to parse
 *
 * \return Object with 'refs' (array of {ref, pos}) and 'rest'
 * (array of remaining arguments).
 */
function __simpleParseRefs(args, count) {
    var refs = [];
    var i = 0;
    while (refs.length<count && i<args.length) {
        var a = args[i++];
        var r = { ref: a, pos: undefined };
        if (isPosition(a)) {
            r.pos = toVector(a);
        }
        else if (i<args.length && isPosition(args[i])) {
            r.pos = toVector(args[i++]);
        }
        refs.push(r);
    }
    return { refs: refs, rest: Array.prototype.slice.call(args, i) };
}

/**
 * \internal
 * Returns a position on the given shape that is used as click position
 * if the user did not specify one.
 */
function __simpleDefaultPos(shape) {
    if (isNull(shape)) {
        return RVector.invalid;
    }

    var p = RVector.invalid;
    if (isPolylineShape(shape) && shape.isGeometricallyClosed()) {
        p = shape.getPointOnShape();
    }
    else if (isFunction(shape.getMiddlePoint)) {
        p = shape.getMiddlePoint();
    }
    if (!isValidVector(p)) {
        p = shape.getPointOnShape();
    }
    return p;
}

/**
 * \internal
 * Resolves a parsed reference (see __simpleParseRefs) to an object with
 * 'entity' (REntity copy or undefined for shapes), 'shape' (RShape),
 * 'pos' (click position, never invalid), 'isShape' (true if a shape was given)
 * and 'userPos' (true if the position was given by the caller).
 *
 * \return Object or undefined if the reference cannot be resolved.
 */
function __simpleResolveRef(r) {
    var ret = { entity: undefined, shape: undefined, pos: r.pos, isShape: false, userPos: isValidVector(r.pos) };

    if (isShape(r.ref)) {
        ret.shape = r.ref;
        ret.isShape = true;
    }
    else {
        ret.entity = getEntity(r.ref);
        if (isNull(ret.entity)) {
            if (!isNumber(r.ref)) {
                warning(qsTr("Not an entity reference (ID, entity, shape or position):") + " " + r.ref);
            }
            return undefined;
        }
        ret.shape = getEntityShape(ret.entity, ret.pos);
        if (isNull(ret.shape)) {
            warning(qsTr("Entity has no shape:") + " " + ret.entity.getId());
            return undefined;
        }
    }

    if (!isValidVector(ret.pos)) {
        ret.pos = __simpleDefaultPos(ret.shape);
    }
    return ret;
}

/**
 * \internal
 * Applies the given operation unless we are inside a transaction.
 *
 * \return RTransaction or undefined.
 */
function __simpleApplyOperation(op) {
    if (__simpleUseOp===true) {
        // applied by endTransaction:
        return undefined;
    }

    var di = getDocumentInterface();
    if (isNull(di)) {
        return undefined;
    }
    return di.applyOperation(op);
}

/**
 * \internal
 * Applies the given transformation function to the given entity reference
 * or shape.
 */
function __simpleTransform(e, fn) {
    if (isShape(e)) {
        fn(e);
        return undefined;
    }

    var entity = getEntity(e);
    if (isNull(entity)) {
        return undefined;
    }

    fn(entity);
    return addObject(entity);
}

/**
 * Moves the given entity or shape by the given offset.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID, shape or position in the drawing.
 * \param offset Offset vector (RVector or [x,y]).
 *
 * \return The modified entity or undefined for shapes (which are modified in place).
 *
 * \code
 * move(entity, x,y)
 * move(entity, [x,y])
 * move(entity, new RVector(x,y))
 * move([px,py], [x,y])
 * \endcode
 */
function move(e, offset) {
    if (arguments.length===3) {
        return move(arguments[0], new RVector(arguments[1], arguments[2]));
    }

    if (isArray(offset)) {
        return move(e, new RVector(offset));
    }

    return __simpleTransform(e, function(obj) {
        obj.move(offset);
    });
}

/**
 * Rotates the given entity or shape by the given angle around the given center.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID, shape or position in the drawing.
 * \param angle Rotation angle in degrees.
 * \param center Rotation center (RVector or [x,y]), defaults to the origin.
 *
 * \return The modified entity or undefined for shapes (which are modified in place).
 *
 * \code
 * rotate(entity, angle)
 * rotate(entity, angle, cx,cy)
 * rotate(entity, angle, [cx,cy])
 * rotate(entity, angle, new RVector(cx,cy))
 * \endcode
 */
function rotate(e, angle, center) {
    if (arguments.length===4) {
        return rotate(arguments[0], arguments[1], new RVector(arguments[2], arguments[3]));
    }

    if (isArray(center)) {
        return rotate(e, angle, new RVector(center));
    }

    return __simpleTransform(e, function(obj) {
        if (isNull(center)) {
            obj.rotate(deg2rad(angle));
        }
        else {
            obj.rotate(deg2rad(angle), center);
        }
    });
}

/**
 * Scales the given entity or shape by the given factor with the given focus point.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID, shape or position in the drawing.
 * \param factor Scale factor (number) or factors (RVector or [sx,sy]).
 * \param focusPoint Focus point (RVector or [x,y]), defaults to the origin.
 *
 * \return The modified entity or undefined for shapes (which are modified in place).
 *
 * \code
 * scale(entity, factor)
 * scale(entity, factor, cx,cy)
 * scale(entity, factor, [cx,cy])
 * scale(entity, factor, new RVector(cx,cy))
 * scale(entity, [sx,sy], [cx,cy])
 * \endcode
 */
function scale(e, factor, focusPoint) {
    if (arguments.length===4) {
        return scale(arguments[0], arguments[1], new RVector(arguments[2], arguments[3]));
    }

    if (isArray(factor)) {
        return scale(e, new RVector(factor), focusPoint);
    }
    if (isArray(focusPoint)) {
        return scale(e, factor, new RVector(focusPoint));
    }

    return __simpleTransform(e, function(obj) {
        if (isNull(focusPoint)) {
            obj.scale(factor);
        }
        else {
            obj.scale(factor, focusPoint);
        }
    });
}

/**
 * Mirrors the given entity or shape at the given axis.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID, shape or position in the drawing.
 * \param axis Mirror axis (RLine, two points or array of two points).
 *
 * \return The modified entity or undefined for shapes (which are modified in place).
 *
 * \code
 * mirror(entity, x1,y1, x2,y2)
 * mirror(entity, [x1,y1], [x2,y2])
 * mirror(entity, new RVector(x1,y1), new RVector(x2,y2))
 * mirror(entity, new RLine(x1,y1, x2, y2))
 * mirror(entity, [new RVector(x1,y1), new RVector(x2,y2)])
 * mirror(entity, [[x1,y1], [x2,y2]])
 * \endcode
 */
function mirror(e, axis) {
    if (arguments.length===5) {
        return mirror(arguments[0], new RLine(arguments[1], arguments[2], arguments[3], arguments[4]));
    }
    if (arguments.length===3) {
        return mirror(arguments[0], new RLine(toVector(arguments[1]), toVector(arguments[2])));
    }

    if (isArray(axis)) {
        return mirror(e, new RLine(toVector(axis[0]), toVector(axis[1])));
    }

    return __simpleTransform(e, function(obj) {
        obj.mirror(axis);
    });
}

/**
 * Deletes the given entity from the drawing.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or position in the drawing.
 *
 * \return True on success.
 *
 * \code
 * deleteEntity(id)
 * deleteEntity(entity)
 * deleteEntity(x,y)
 * deleteEntity([x,y])
 * \endcode
 */
function deleteEntity(e) {
    if (arguments.length===2) {
        return deleteEntity(new RVector(arguments[0], arguments[1]));
    }

    var entity = getEntity(e);
    if (isNull(entity)) {
        return false;
    }

    deleteObject(entity);
    return true;
}

/**
 * Trims the given entity or shape to a limiting entity or shape.
 * \ingroup ecma_simple
 *
 * \param trimEntity Entity, entity ID, shape or position of the entity to trim.
 * \param trimClickPos Position that indicates which part of the entity to keep (optional).
 * \param limitingEntity Entity, entity ID, shape or position of the entity that limits the trimming.
 * \param limitingClickPos Position that indicates which part of the limiting entity to keep
 * if both entities are trimmed (optional).
 * \param trimBoth True to trim both entities.
 *
 * \return RTransaction created by the operation, undefined inside a transaction or
 * if the entities cannot be trimmed. If only shapes are given, the trimmed shape
 * (or both trimmed shapes if trimBoth is true) are returned as an array and the
 * original shapes are not changed.
 *
 * \code
 * trim(trimEntity, limitingEntity)
 * trim(trimEntity, limitingEntity, trimBoth)
 * trim(trimEntity, [x1,y1], limitingEntity, [x2,y2], trimBoth)
 * trim([x1,y1], [x2,y2], trimBoth)
 * trim(trimEntity, x1,y1, limitingEntity, x2,y2, trimBoth)
 * trim(trimEntity, new RVector(x1,y1), limitingEntity, new RVector(x2,y2), trimBoth)
 * \endcode
 */
function trim(trimEntity, trimClickPos, limitingEntity, limitingClickPos, trimBoth) {
    if (arguments.length===7) {
        return trim(arguments[0], new RVector(arguments[1], arguments[2]), arguments[3], new RVector(arguments[4], arguments[5]), arguments[6]);
    }

    var p = __simpleParseRefs(arguments, 2);
    if (p.refs.length<2) {
        warning(qsTr("Two entities are required."));
        return undefined;
    }
    trimBoth = (p.rest[0]===true);

    var r1 = __simpleResolveRef(p.refs[0]);
    var r2 = __simpleResolveRef(p.refs[1]);
    if (isNull(r1) || isNull(r2)) {
        return undefined;
    }

    var samePolyline = false;
    if (!r1.isShape && !r2.isShape) {
        samePolyline = (r1.entity.getId()===r2.entity.getId() && isPolylineEntity(r1.entity));
    }
    if (samePolyline && !trimBoth) {
        // TODO: fix trimming one segment within same polyline:
        warning(qsTr("Trimming within the same polyline requires trimming of both segments."));
        return undefined;
    }

    var newShapes = RShape.trim(r1.shape, r1.pos, r2.shape, r2.pos, trimBoth, samePolyline);
    if (newShapes.length===0) {
        warning(qsTr("Entity cannot be trimmed."));
        return undefined;
    }
    for (var i=0; i<newShapes.length; i++) {
        newShapes[i] = getPtr(newShapes[i]);
    }

    if (r1.isShape && r2.isShape) {
        if (trimBoth) {
            return newShapes;
        }
        return [ newShapes[0] ];
    }

    var op = getOperation();

    if (!r1.isShape) {
        if (!modifyEntity(op, r1.entity, newShapes[0])) {
            if (trimBoth) {
                warning(qsTr("First entity cannot be trimmed."));
            }
            else {
                warning(qsTr("Entity cannot be trimmed."));
            }
        }
    }

    if (newShapes.length>1 && trimBoth && !r2.isShape) {
        if (!modifyEntity(op, r2.entity, newShapes[1])) {
            warning(qsTr("Second entity cannot be trimmed."));
        }
    }

    return __simpleApplyOperation(op);
}

/**
 * Trims both given entities or shapes to each other.
 * \ingroup ecma_simple
 *
 * \see trim
 *
 * \code
 * trimBoth(entity1, entity2)
 * trimBoth(entity1, [x1,y1], entity2, [x2,y2])
 * trimBoth([x1,y1], [x2,y2])
 * trimBoth(entity1, x1,y1, entity2, x2,y2)
 * \endcode
 */
function trimBoth() {
    var args = Array.prototype.slice.call(arguments);
    args.push(true);
    return trim.apply(this, args);
}

/**
 * Lengthens or shortens the given entity or shape.
 * \ingroup ecma_simple
 *
 * \param entity Entity, entity ID, shape or position of the entity to lengthen.
 * \param start True to lengthen at the start point, false for the end point
 * or a position close to the end to lengthen. Defaults to the end point.
 * \param amount Amount to lengthen or negative value to shorten.
 *
 * \return The modified entity or undefined for shapes (which are modified in place).
 *
 * \code
 * lengthen(entity, true, amount)
 * lengthen(entity, [x,y], amount)
 * lengthen([x,y], amount)
 * lengthen(entity, amount)
 * \endcode
 */
function lengthen(entity, start, amount) {
    var p = __simpleParseRefs(arguments, 1);
    if (p.refs.length<1) {
        return undefined;
    }

    var r = __simpleResolveRef(p.refs[0]);
    if (isNull(r)) {
        return undefined;
    }

    var trimStart = undefined;
    if (isBoolean(p.rest[0])) {
        trimStart = p.rest[0];
        amount = p.rest[1];
    }
    else {
        amount = p.rest[0];
    }

    if (!isNumber(amount)) {
        warning(qsTr("Amount is required."));
        return undefined;
    }

    var shape = r.shape;

    if (isNull(trimStart)) {
        if (!r.userPos) {
            trimStart = false;
        }
        else if (isPolylineShape(shape)) {
            trimStart = shape.getLengthTo(r.pos) < shape.getLength()/2;
        }
        else {
            trimStart = r.pos.getDistanceTo(shape.getStartPoint()) < r.pos.getDistanceTo(shape.getEndPoint());
        }
    }

    var from = trimStart ? RS.FromStart : RS.FromEnd;
    var iss = shape.getPointsWithDistanceToEnd(-amount, from|RS.AlongPolyline);
    var is = r.pos.getClosest(iss);
    if (!isValidVector(is)) {
        warning(qsTr("Entity cannot be lengthened."));
        return undefined;
    }

    var target = r.isShape ? shape : r.entity;
    if (trimStart) {
        if (!isFunction(target.trimStartPoint)) {
            warning(qsTr("Entity cannot be lengthened."));
            return undefined;
        }
        target.trimStartPoint(is, is, amount>0);
    }
    else {
        if (!isFunction(target.trimEndPoint)) {
            warning(qsTr("Entity cannot be lengthened."));
            return undefined;
        }
        target.trimEndPoint(is, is, amount>0);
    }

    if (r.isShape) {
        return undefined;
    }
    return addObject(r.entity);
}

/**
 * \internal
 * Implementation of breakOut and autoTrim.
 */
function __simpleBreakOut(args, extend) {
    var p = __simpleParseRefs(args, 1);
    if (p.refs.length<1) {
        return undefined;
    }

    var removeSegment = true;
    if (isBoolean(p.rest[0])) {
        removeSegment = p.rest[0];
    }

    var r = __simpleResolveRef(p.refs[0]);
    if (isNull(r)) {
        return undefined;
    }

    var doc = getTransactionDocument();

    if (r.isShape) {
        var shape = r.shape.clone();
        var otherShapes = [];
        if (!isNull(doc)) {
            otherShapes = ShapeAlgorithms.getIntersectingShapes(doc, RObject.INVALID_ID, shape, extend);
        }
        var segs = ShapeAlgorithms.autoSplit(shape, otherShapes, r.pos, extend);
        if (isNull(segs)) {
            return [];
        }
        var ret = [];
        if (extend || !removeSegment) {
            if (!isNull(segs[2])) {
                ret.push(segs[2]);
            }
        }
        if (!extend) {
            if (!isNull(segs[0])) {
                ret.push(segs[0]);
            }
            if (!isNull(segs[1])) {
                ret.push(segs[1]);
            }
        }
        return ret;
    }

    include("scripts/Modify/BreakOut/BreakOut.js");

    var op = getOperation();
    if (!BreakOut.breakOut(op, r.entity, r.pos, extend, removeSegment)) {
        if (extend) {
            warning(qsTr("Entity cannot be trimmed."));
        }
        else {
            warning(qsTr("Entity cannot be broken out."));
        }
        return undefined;
    }

    return __simpleApplyOperation(op);
}

/**
 * Breaks out the segment of the given entity between the closest intersection
 * points with other entities on either side of the given position. If there
 * are no intersections, the segment extends to the end of the entity.
 * \ingroup ecma_simple
 *
 * \param entity Entity, entity ID, shape or position of the entity.
 * \param pos Position on the segment to break out (optional for positions
 * given as entity reference, otherwise defaults to the middle of the entity).
 * \param removeSegment True (default) to delete the segment, false to keep it
 * as a separate entity.
 *
 * \return RTransaction created by the operation, undefined inside a transaction or
 * if the entity cannot be broken out. If a shape is given, the remaining shapes
 * (and the segment if removeSegment is false) are returned as array.
 *
 * \code
 * breakOut(entity, x,y)
 * breakOut(entity, [x,y])
 * breakOut([x,y])
 * breakOut(entity, [x,y], false)
 * \endcode
 */
function breakOut(entity, pos, removeSegment) {
    if (arguments.length>=3 && isNumber(arguments[1]) && isNumber(arguments[2])) {
        return breakOut(arguments[0], new RVector(arguments[1], arguments[2]), arguments[3]);
    }
    return __simpleBreakOut(arguments, false);
}

/**
 * Trims the given entity to the closest intersection points with other
 * entities on either side of the given position, keeping only the segment
 * at the given position (auto trim).
 * \ingroup ecma_simple
 *
 * \param entity Entity, entity ID, shape or position of the entity.
 * \param pos Position on the segment to keep (optional for positions
 * given as entity reference, otherwise defaults to the middle of the entity).
 *
 * \return RTransaction created by the operation, undefined inside a transaction or
 * if the entity cannot be trimmed. If a shape is given, the remaining segment
 * is returned in an array.
 *
 * \code
 * autoTrim(entity, x,y)
 * autoTrim(entity, [x,y])
 * autoTrim([x,y])
 * \endcode
 */
function autoTrim(entity, pos) {
    if (arguments.length>=3 && isNumber(arguments[1]) && isNumber(arguments[2])) {
        return autoTrim(arguments[0], new RVector(arguments[1], arguments[2]));
    }
    return __simpleBreakOut(arguments, true);
}

/**
 * Divides the given entity or shape at one or two positions.
 * \ingroup ecma_simple
 *
 * \param entity Entity, entity ID, shape or position of the entity to divide.
 * \param pos1 First cutting position (optional if a position is given as entity reference).
 * \param pos2 Second cutting position (optional). Closed shapes (circles, full ellipses,
 * closed polylines) are divided into two parts at the two positions, open shapes are
 * cut at both positions (three parts).
 *
 * \return RTransaction created by the operation or undefined inside a transaction or
 * if the entity cannot be divided. If a shape is given, the resulting shapes are
 * returned as array.
 *
 * \code
 * divide(entity, x,y)
 * divide(entity, [x,y])
 * divide([x,y])
 * divide(entity, [x1,y1], [x2,y2])
 * divide(entity, x1,y1, x2,y2)
 * \endcode
 */
function divide(entity, pos1, pos2) {
    if (arguments.length>=3 && isNumber(arguments[1]) && isNumber(arguments[2])) {
        if (arguments.length>=5 && isNumber(arguments[3]) && isNumber(arguments[4])) {
            return divide(arguments[0], new RVector(arguments[1], arguments[2]), new RVector(arguments[3], arguments[4]));
        }
        return divide(arguments[0], new RVector(arguments[1], arguments[2]));
    }

    var p = __simpleParseRefs(arguments, 1);
    if (p.refs.length<1) {
        return undefined;
    }

    var r = __simpleResolveRef(p.refs[0]);
    if (isNull(r)) {
        return undefined;
    }

    if (!r.userPos) {
        warning(qsTr("Position is required."));
        return undefined;
    }
    pos1 = r.pos;
    pos2 = undefined;
    if (isPosition(p.rest[0])) {
        pos2 = toVector(p.rest[0]);
    }

    include("scripts/Modify/Divide/Divide.js");

    var shapes = __simpleDivideShape(r.shape, pos1, pos2);
    if (shapes.length===0) {
        if (r.isShape) {
            return [];
        }
        warning(qsTr("Entity cannot be divided."));
        return undefined;
    }

    if (r.isShape) {
        return shapes;
    }

    var doc = getTransactionDocument();
    var op = getOperation();
    op.deleteObject(r.entity);
    for (var k=0; k<shapes.length; k++) {
        var e = shapeToEntity(doc, shapes[k]);
        if (isNull(e)) {
            continue;
        }
        e.copyAttributesFrom(getPtr(r.entity));
        op.addObject(e, false);
    }

    return __simpleApplyOperation(op);
}

/**
 * \internal
 * Divides the given shape at one or two positions.
 * Closed shapes (circles, full ellipses, closed polylines) are divided into
 * two parts by two positions, open shapes are cut at each given position.
 *
 * \return Array of resulting shapes (empty on failure).
 */
function __simpleDivideShape(shape, pos1, pos2) {
    var closed = isCircleShape(shape) ||
        (isEllipseShape(shape) && shape.isFullEllipse()) ||
        (isPolylineShape(shape) && shape.isClosed());

    var i;
    var ret = [];

    // divideShape modifies closed polylines in place:
    var res = ShapeAlgorithms.divideShape(shape.clone(), pos1, closed ? pos2 : undefined);
    if (isNull(res)) {
        return [];
    }
    for (i=0; i<res[0].length; i++) {
        if (!isNull(res[0][i])) {
            ret.push(getPtr(res[0][i]));
        }
    }

    if (!closed && isValidVector(pos2) && ret.length>0) {
        // second cut on open shape: divide the part closest to pos2 again:
        var minDist = undefined;
        var idx = -1;
        for (i=0; i<ret.length; i++) {
            var d = ret[i].getClosestPointOnShape(pos2, true).getDistanceTo(pos2);
            if (isNull(minDist) || d<minDist) {
                minDist = d;
                idx = i;
            }
        }
        if (idx!==-1) {
            var res2 = ShapeAlgorithms.divideShape(ret[idx].clone(), pos2, undefined);
            if (!isNull(res2)) {
                var parts = [];
                for (i=0; i<res2[0].length; i++) {
                    if (!isNull(res2[0][i])) {
                        parts.push(getPtr(res2[0][i]));
                    }
                }
                if (parts.length>0) {
                    ret.splice.apply(ret, [idx, 1].concat(parts));
                }
            }
        }
    }

    return ret;
}

/**
 * \internal
 * Applies the result of a corner operation (round, bevel) to the drawing.
 *
 * \param newShapes Array of shapes: [trimmed shape 1, corner shape, trimmed shape 2]
 * or [modified polyline] for corners within the same polyline.
 * \param cornerToEntity Function (doc, shape) that creates the entity for the corner.
 */
function __simpleCornerResult(r1, r2, newShapes, trim, cornerToEntity, errorMessage) {
    if (isNull(newShapes) || newShapes.length===0) {
        warning(errorMessage);
        return undefined;
    }

    var i;
    for (i=0; i<newShapes.length; i++) {
        newShapes[i] = getPtr(newShapes[i]);
    }

    if (r1.isShape && r2.isShape) {
        return newShapes;
    }

    var doc = getTransactionDocument();
    var op = getOperation();

    if (trim && !r1.isShape) {
        if (!modifyEntity(op, r1.entity, newShapes[0])) {
            warning(qsTr("First entity cannot be trimmed."));
        }
    }

    if (newShapes.length<3) {
        // corner was within same polyline:
        return __simpleApplyOperation(op);
    }

    if (trim && !r2.isShape) {
        if (!modifyEntity(op, r2.entity, newShapes[2])) {
            warning(qsTr("Second entity cannot be trimmed."));
        }
    }

    var ce = cornerToEntity(doc, newShapes[1]);
    if (!isNull(ce)) {
        op.addObject(ce);
    }

    return __simpleApplyOperation(op);
}

/**
 * Rounds the corner between the two given entities or shapes (fillet).
 * \ingroup ecma_simple
 *
 * \param entity1 First entity, entity ID, shape or position.
 * \param clickPos1 Position that indicates which end of the first entity to round (optional).
 * \param entity2 Second entity, entity ID, shape or position.
 * \param clickPos2 Position that indicates which end of the second entity to round (optional).
 * \param radius Rounding radius.
 * \param trim True (default) to trim both entities to the rounding arc.
 * \param solutionPos Position that indicates which solution to use (optional, defaults to clickPos2).
 * \param inverted True to invert the arc (inside rounding), default is false.
 *
 * \return RTransaction created by the operation, undefined inside a transaction or
 * if the entities cannot be rounded. If only shapes are given, an array with the
 * trimmed shapes and the rounding arc is returned and the given shapes are not changed:
 * [shape1 trimmed, arc, shape2 trimmed].
 *
 * \code
 * round(entity1, entity2, radius)
 * round(entity1, [x1,y1], entity2, [x2,y2], radius)
 * round([x1,y1], [x2,y2], radius)
 * round(entity1, x1,y1, entity2, x2,y2, radius)
 * round(entity1, [x1,y1], entity2, [x2,y2], radius, false)
 * \endcode
 */
function round(entity1, clickPos1, entity2, clickPos2, radius, trim, solutionPos, inverted) {
    if (arguments.length>=7 && isNumber(arguments[1]) && isNumber(arguments[2]) && isNumber(arguments[4]) && isNumber(arguments[5])) {
        var args = [arguments[0], new RVector(arguments[1], arguments[2]), arguments[3], new RVector(arguments[4], arguments[5])];
        return round.apply(this, args.concat(Array.prototype.slice.call(arguments, 6)));
    }

    var p = __simpleParseRefs(arguments, 2);
    if (p.refs.length<2) {
        warning(qsTr("Two entities are required."));
        return undefined;
    }

    radius = p.rest[0];
    if (!isNumber(radius)) {
        warning(qsTr("Radius is required."));
        return undefined;
    }
    trim = isBoolean(p.rest[1]) ? p.rest[1] : true;
    solutionPos = isPosition(p.rest[2]) ? toVector(p.rest[2]) : undefined;
    inverted = (p.rest[3]===true);

    var r1 = __simpleResolveRef(p.refs[0]);
    var r2 = __simpleResolveRef(p.refs[1]);
    if (isNull(r1) || isNull(r2)) {
        return undefined;
    }

    var samePolyline = false;
    if (!r1.isShape && !r2.isShape) {
        samePolyline = (r1.entity.getId()===r2.entity.getId() && isPolylineEntity(r1.entity));
    }

    if (isNull(solutionPos)) {
        solutionPos = r2.pos;
    }

    var newShapes = RShape.roundShapes(r1.shape, r1.pos, r2.shape, r2.pos, trim, samePolyline, radius, solutionPos);

    return __simpleCornerResult(r1, r2, newShapes, trim, function(doc, arc) {
        if (inverted) {
            arc.mirror(new RLine(arc.getStartPoint(), arc.getEndPoint()));
        }
        return new RArcEntity(doc, new RArcData(arc));
    }, qsTr("The two entities cannot be rounded."));
}

/**
 * Bevels the corner between the two given entities or shapes (chamfer).
 * \ingroup ecma_simple
 *
 * \param entity1 First entity, entity ID, shape or position.
 * \param clickPos1 Position that indicates which end of the first entity to bevel (optional).
 * \param entity2 Second entity, entity ID, shape or position.
 * \param clickPos2 Position that indicates which end of the second entity to bevel (optional).
 * \param distance1 Distance of the bevel line from the corner along the first entity.
 * \param distance2 Distance of the bevel line from the corner along the second entity
 * (optional, defaults to distance1).
 * \param trim True (default) to trim both entities to the bevel line.
 *
 * \return RTransaction created by the operation, undefined inside a transaction or
 * if the entities cannot be bevelled. If only shapes are given, an array with the
 * trimmed shapes and the bevel line is returned and the given shapes are not changed:
 * [shape1 trimmed, line, shape2 trimmed].
 *
 * \code
 * bevel(entity1, entity2, distance)
 * bevel(entity1, entity2, distance1, distance2)
 * bevel(entity1, [x1,y1], entity2, [x2,y2], distance1, distance2)
 * bevel([x1,y1], [x2,y2], distance)
 * bevel(entity1, x1,y1, entity2, x2,y2, distance1, distance2)
 * bevel(entity1, entity2, distance1, distance2, false)
 * \endcode
 */
function bevel(entity1, clickPos1, entity2, clickPos2, distance1, distance2, trim) {
    if (arguments.length>=7 && isNumber(arguments[1]) && isNumber(arguments[2]) && isNumber(arguments[4]) && isNumber(arguments[5])) {
        var args = [arguments[0], new RVector(arguments[1], arguments[2]), arguments[3], new RVector(arguments[4], arguments[5])];
        return bevel.apply(this, args.concat(Array.prototype.slice.call(arguments, 6)));
    }

    var p = __simpleParseRefs(arguments, 2);
    if (p.refs.length<2) {
        warning(qsTr("Two entities are required."));
        return undefined;
    }

    distance1 = p.rest[0];
    if (!isNumber(distance1)) {
        warning(qsTr("Distance is required."));
        return undefined;
    }
    distance2 = isNumber(p.rest[1]) ? p.rest[1] : distance1;
    trim = true;
    if (isBoolean(p.rest[1])) {
        trim = p.rest[1];
    }
    else if (isBoolean(p.rest[2])) {
        trim = p.rest[2];
    }

    var r1 = __simpleResolveRef(p.refs[0]);
    var r2 = __simpleResolveRef(p.refs[1]);
    if (isNull(r1) || isNull(r2)) {
        return undefined;
    }

    var samePolyline = false;
    if (!r1.isShape && !r2.isShape) {
        samePolyline = (r1.entity.getId()===r2.entity.getId() && isPolylineEntity(r1.entity));
    }

    include("scripts/Modify/Bevel/Bevel.js");

    var newShapes = Bevel.bevelShapes(r1.shape, r1.pos, r2.shape, r2.pos, trim, samePolyline, distance1, distance2);

    return __simpleCornerResult(r1, r2, newShapes, trim, function(doc, line) {
        if (line.getLength()<=RS.PointTolerance) {
            return undefined;
        }
        return new RLineEntity(doc, new RLineData(line));
    }, qsTr("The two entities cannot be bevelled."));
}

/**
 * Alias for bevel.
 * \ingroup ecma_simple
 * \see bevel
 */
function chamfer() {
    return bevel.apply(this, arguments);
}

/**
 * Creates parallel (offset) copies of the given entity or shape.
 * \ingroup ecma_simple
 *
 * \param entity Entity, entity ID, shape or position of the entity.
 * \param sidePos Position that indicates on which side of the entity to create
 * the parallels (optional). A position on the entity itself means both sides.
 * \param distance Distance between the parallels.
 * \param number Number of parallels to create (default is 1).
 * \param side RS.LeftHand, RS.RightHand or RS.BothSides (default) or a position.
 * Only used if no side position is given.
 *
 * \return RTransaction created by the operation or undefined inside a transaction.
 * If a shape is given, the parallel shapes are returned as array.
 *
 * \code
 * offset(entity, distance)
 * offset(entity, distance, number)
 * offset(entity, distance, number, RS.LeftHand)
 * offset(entity, [x,y], distance)
 * offset(entity, [x,y], distance, number)
 * offset([x,y], distance)
 * \endcode
 */
function offset(entity, sidePos, distance, number, side) {
    var p = __simpleParseRefs(arguments, 1);
    if (p.refs.length<1) {
        return undefined;
    }

    distance = p.rest[0];
    if (!isNumber(distance)) {
        warning(qsTr("Distance is required."));
        return undefined;
    }
    number = isNumber(p.rest[1]) ? p.rest[1] : 1;

    var r = __simpleResolveRef(p.refs[0]);
    if (isNull(r)) {
        return undefined;
    }

    if (r.userPos && r.shape.getClosestPointOnShape(r.pos, true).getDistanceTo(r.pos)>RS.PointTolerance) {
        // position next to the entity indicates the side:
        side = r.pos;
    }
    else if (isPosition(p.rest[2])) {
        side = toVector(p.rest[2]);
    }
    else if (isNumber(p.rest[2])) {
        side = p.rest[2];
    }
    else {
        side = RS.BothSides;
    }

    var shapes = ShapeAlgorithms.getOffsetShapes(r.shape, distance, number, side);
    var c = RShape.getErrorCode();
    if (c!==0) {
        if (isCircleShape(r.shape)) {
            warning(qsTr("Radius dropped below 0.0 after %n concentric circle(s).", "", c-1));
        }
        else if (isArcShape(r.shape)) {
            warning(qsTr("Radius dropped below 0.0 after %n concentric arc(s).", "", c-1));
        }
    }
    if (isNull(shapes)) {
        return undefined;
    }

    var i;
    var ret = [];
    for (i=0; i<shapes.length; i++) {
        if (isNull(shapes[i])) {
            continue;
        }
        ret.push(getPtr(shapes[i]));
    }

    if (r.isShape) {
        return ret;
    }

    if (ret.length===0) {
        warning(qsTr("Entity cannot be offset."));
        return undefined;
    }

    var doc = getTransactionDocument();
    var op = getOperation();
    for (i=0; i<ret.length; i++) {
        var e = shapeToEntity(doc, ret[i]);
        if (!isNull(e)) {
            op.addObject(e);
        }
    }

    return __simpleApplyOperation(op);
}

/**
 * Reverses the direction of the given entity or shape.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID, shape or position in the drawing.
 *
 * \return The modified entity or undefined for shapes (which are modified in place).
 *
 * \code
 * reverse(entity)
 * reverse(x,y)
 * reverse([x,y])
 * \endcode
 */
function reverse(e) {
    if (arguments.length===2) {
        return reverse(new RVector(arguments[0], arguments[1]));
    }

    if (isShape(e)) {
        if (isFunction(e.reverse)) {
            e.reverse();
        }
        return undefined;
    }

    var entity = getEntity(e);
    if (isNull(entity)) {
        return undefined;
    }

    if (!isFunction(entity.reverse)) {
        warning(qsTr("Entity cannot be reversed."));
        return undefined;
    }

    entity.reverse();
    return addObject(entity);
}

/**
 * Explodes the given entity (polyline, block reference, text, dimension,
 * hatch, spline, ellipse, ...) into its components.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID, shape or position in the drawing.
 * \param options Object with optional settings (defaults come from the
 * application preferences): splineTolerance, splineSegments, ellipseSegments,
 * splinesToLineSegments, textToPolylines, textSplineToLineOrArc,
 * multilineTextToSimpleText, circlesToPolylines.
 *
 * \return RTransaction created by the operation, undefined inside a transaction or
 * if the entity cannot be exploded. If a polyline shape is given, its segments are
 * returned as array.
 *
 * \code
 * explode(entity)
 * explode(x,y)
 * explode([x,y])
 * explode(entity, { splineSegments: 128 })
 * \endcode
 */
function explode(e, options) {
    if (arguments.length>=2 && isNumber(arguments[0]) && isNumber(arguments[1])) {
        return explode(new RVector(arguments[0], arguments[1]), arguments[2]);
    }

    if (isShape(e)) {
        if (isFunction(e.getExploded)) {
            var exploded = e.getExploded();
            var shapes = [];
            for (var n=0; n<exploded.length; n++) {
                shapes.push(getPtr(exploded[n]));
            }
            return shapes;
        }
        return undefined;
    }

    var entity = getEntity(e);
    if (isNull(entity)) {
        return undefined;
    }

    include("scripts/Modify/Explode/Explode.js");

    var news = Explode.explodeEntity(entity, options);
    if (isNull(news)) {
        warning(qsTr("Entity cannot be exploded."));
        return undefined;
    }

    var doc = getTransactionDocument();
    var op = getOperation();
    var blockReferences = [];
    var attributeEntities = [];

    for (var k=0; k<news.length; k++) {
        var ne;
        if (isEntity(news[k])) {
            ne = news[k];
            op.addObject(ne, false, true);

            if (isBlockReferenceEntity(ne)) {
                blockReferences.push(ne);
            }
            else if (isAttributeEntity(ne)) {
                attributeEntities.push(ne);
            }
        }
        else {
            var newShape = news[k];
            ne = shapeToEntity(doc, newShape);
            if (!isNull(ne)) {
                ne.copyAttributesFrom(getPtr(entity));
                if (!isNull(newShape.color)) {
                    ne.setColor(new RColor(newShape.color));
                }
                op.addObject(ne, false);
            }
        }
    }

    // delete original entity:
    op.deleteObject(entity);

    var t = __simpleApplyOperation(op);

    // fix attribute links to exploded block references
    // (only possible outside of a transaction when the new IDs are known):
    if (!isNull(t) && attributeEntities.length>0) {
        var storage = doc.getStorage();
        var opAtt = new RAddObjectsOperation();
        var gotAttributes = false;
        for (var i=0; i<attributeEntities.length; i++) {
            var attributeEntity = attributeEntities[i].clone();
            for (var b=0; b<blockReferences.length; b++) {
                if (blockReferences[b].getId()===attributeEntity.getParentId()) {
                    storage.setEntityParentId(getPtr(attributeEntity), blockReferences[b].getId());
                    opAtt.addObject(attributeEntity, false);
                    gotAttributes = true;
                    break;
                }
            }
        }
        if (gotAttributes) {
            __simpleApplyOperation(opAtt);
        }
    }

    return t;
}

/**
 * Stretches all entities that intersect with the given area by the given
 * offset. Entities completely inside the area are moved. If the drawing has
 * a selection, only selected entities are stretched.
 * \ingroup ecma_simple
 *
 * \param area RBox, RPolyline or array of two corner positions.
 * \param offset Offset (RVector or [dx,dy]).
 *
 * \return RTransaction created by the operation or undefined inside a transaction.
 *
 * \code
 * stretch(x1,y1, x2,y2, dx,dy)
 * stretch([x1,y1], [x2,y2], [dx,dy])
 * stretch([[x1,y1], [x2,y2]], [dx,dy])
 * stretch(new RBox(c1, c2), new RVector(dx,dy))
 * stretch(polyline, new RVector(dx,dy))
 * \endcode
 */
function stretch(area, offset) {
    if (arguments.length===6) {
        return stretch(new RBox(new RVector(arguments[0], arguments[1]), new RVector(arguments[2], arguments[3])), new RVector(arguments[4], arguments[5]));
    }
    if (arguments.length===3) {
        return stretch(new RBox(toVector(arguments[0]), toVector(arguments[1])), toVector(arguments[2]));
    }

    if (isArray(area) && area.length===2 && isPosition(area[0]) && isPosition(area[1])) {
        area = new RBox(toVector(area[0]), toVector(area[1]));
    }
    if (isArray(offset)) {
        offset = new RVector(offset);
    }

    var polygon;
    if (isOfType(area, RBox)) {
        polygon = area.getPolyline2d();
    }
    else if (isPolylineShape(area)) {
        polygon = area;
    }
    else {
        warning(qsTr("Area must be a box, a polyline or two corner positions."));
        return undefined;
    }

    if (!isValidVector(offset)) {
        warning(qsTr("Offset is required."));
        return undefined;
    }

    var doc = getTransactionDocument();
    if (isNull(doc)) {
        return undefined;
    }

    include("scripts/Modify/Stretch/Stretch.js");

    var op = getOperation();
    Stretch.getStrechOperation(doc, polygon, false, offset, undefined, op);

    return __simpleApplyOperation(op);
}
