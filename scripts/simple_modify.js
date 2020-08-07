/**
 * Simple Modification API, mainly designed for use in the ECMAScript console.
 */

/**
 * Pastes the given document into the current document or into the second given document.
 * \ingroup ecma_simple
 *
 * \param docSource RDocument to paste
 * \param docDestination RDocument to paste into (or undefined for current document)
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
 * Moves the given entity or shape by the given offset.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * move(entity, x,y)
 * move(entity, [x,y])
 * move(entity, new RVector(x,y))
 * \endcode
 */
function move(e, offset) {
    if (arguments.length===3) {
        return move(arguments[0], new RVector(arguments[1], arguments[2]));
    }

    if (isArray(offset)) {
        return move(e, new RVector(offset));
    }
    if (isEntity(e)) {
        return move(e.getId(), offset);
    }
    if (isShape(e)) {
        e.move(offset);
        return undefined;
    }
    if (isNumber(e)) {
        var doc = getTransactionDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        entity.move(offset);
        return addEntity(entity);
    }
    return undefined;
}

/**
 * Rotates the given entity or shape by the given angle around the given center.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
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
    if (isEntity(e)) {
        return rotate(e.getId(), angle, center);
    }
    if (isShape(e)) {
        e.rotate(angle, center);
        return undefined;
    }
    if (isNumber(e)) {
        var doc = getTransactionDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);

        if (isNull(center)) {
            entity.rotate(deg2rad(angle));
        }
        else {
            entity.rotate(deg2rad(angle), center);
        }
        return addEntity(entity);
    }
    return undefined;
}

/**
 * Scales the given entity or shape by the given factor with the given focus point.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * scale(entity, factor, cx,cy)
 * scale(entity, factor, [cx,cy])
 * scale(entity, factor, new RVector(cx,cy))
 * \endcode
 */
function scale(e, factor, focusPoint) {
    if (arguments.length===4) {
        return scale(arguments[0], arguments[1], new RVector(arguments[2], arguments[3]));
    }

    if (isNumber(focusPoint)) {
        return scale(e, factor, new RVector(focusPoint));
    }
    if (isEntity(e)) {
        return scale(e.getId(), factor, focusPoint);
    }
    if (isShape(e)) {
        e.scale(factor, focusPoint);
        return undefined;
    }
    if (isNumber(e)) {
        var doc = getTransactionDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        if (isNull(focusPoint)) {
            entity.scale(factor);
        }
        else {
            entity.scale(factor, focusPoint);
        }
        return addEntity(entity);
    }

    return undefined;
}

/**
 * Mirrors the given entity or shape at the given axis.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
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
        var p1 = arguments[1];
        if (isArray(p1)) {
            p1 = new RVector(p1);
        }
        var p2 = arguments[1];
        if (isArray(p2)) {
            p2 = new RVector(p2);
        }
        return mirror(arguments[0], new RLine(p1, p2));
    }

    if (isArray(axis)) {
        if (isVector(axis[0])) {
            return mirror(e, new RLine(axis[0], axis[1]));
        }
        return mirror(e, new RLine(new RVector(axis[0]), new RVector(axis[1])));
    }
    if (isEntity(e)) {
        return mirror(e.getId(), axis);
    }
    if (isShape(e)) {
        e.mirror(axis);
        return undefined;
    }
    if (isNumber(e)) {
        var doc = getTransactionDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        entity.mirror(axis);
        return addEntity(entity);
    }
    return undefined;
}

/**
 * Trims the given entity / entities or shape(s).
 * \ingroup ecma_simple
 *
 * \param trimEntity Entity, entity ID or shape to trim
 * \param trimClickPos Position clicked when choosing trim entity.
 * \param limitingEntity Entity, entity ID or shape that limits the trimming.
 * \param limitingClickPos Position clicked when choosing limiting entity.
 * \param trimBoth True to trim both entities.
 *
 * \return RTransaction created by operation if no operation is given. If op is given, undefined is returned.
 *
 * \code
 * trim(trimEntity, x1,y1, limitingEntity, x2,y2, trimBoth)
 * trim(trimEntity, [x1,y1], limitingEntity, [x2,y2], trimBoth)
 * trim(trimEntity, new RVector(x1,y1), limitingEntity, new RVector(x2,y2), trimBoth)
 * \endcode
 */
function trim(trimEntity, trimClickPos, limitingEntity, limitingClickPos, trimBoth) {
    if (arguments.length===7) {
        return trim(arguments[0], new RVector(arguments[1], arguments[2]), arguments[3], new RVector(arguments[4], arguments[5]), arguments[6]);
    }

    var trimShape, limitingShape;

    var doc = getTransactionDocument();
    if (isNull(doc)) {
        return undefined;
    }

    if (isNumber(trimEntity)) {
        trimEntity = doc.queryEntity(trimEntity);
    }
    if (isNumber(limitingEntity)) {
        limitingEntity = doc.queryEntity(limitingEntity);
    }

    if (isShape(trimEntity) && isShape(limitingShape)) {
        trimShape = trimEntity;
        limitingShape = limitingEntity;
    }
    else {
        trimShape = trimEntity.castToShape();
        limitingShape = limitingEntity.castToShape();
        if (isNull(limitingShape)) {
            limitingShape = limitingEntity.getClosestSimpleShape(limitingClickPos);
            if (!isNull(limitingShape)) {
                limitingShape = limitingShape.data();
            }
        }
    }

    if (isNull(trimShape) || isNull(limitingShape)) {
        return undefined;
    }

    var samePolyline = (limitingEntity.getId()===trimEntity.getId() && isPolylineEntity(limitingEntity));
    if (samePolyline) {
        if (!trimBoth) {
            // TODO: fix trimming one segment within same polyline:
            return undefined;
        }
    }

    var newShapes = RShape.trim(trimShape, trimClickPos, limitingShape, limitingClickPos, trimBoth, samePolyline);
    if (newShapes.length===0) {
        return undefined;
    }

    var op = getOperation();

    if (!modifyEntity(op, trimEntity.clone(), newShapes[0].data())) {
        if (trimBoth) {
            warning(qsTr("First entity cannot be trimmed."));
        }
        else {
            warning(qsTr("Entity cannot be trimmed."));
        }
    }

    if (newShapes.length===1) {
        // trimming was within same polyline
    }
    else {
        if (trimBoth) {
            if (!modifyEntity(op, limitingEntity.clone(), newShapes[1].data())) {
                warning(qsTr("Second entity cannot be trimmed."));
            }
        }
    }

    if (!__simpleUseOp) {
        var di = getDocumentInterface();
        return di.applyOperation(op);
    }
}

/**
 * Lengthens of shortens the given entity or shape.
 * \ingroup ecma_simple
 *
 * \param entity Entity, entity ID or shape to lengthen
 * \param start True to extend at start point, false for end point
 * \param amount Amount to lengthen or negative value to shorten
 */
function lengthen(entity, start, amount) {
    var doc = getTransactionDocument();
    if (isNull(doc)) {
        return undefined;
    }

    if (isNumber(entity)) {
        entity = doc.queryEntity(entity);
    }
    else {
        entity = entity.clone();
    }

    var from = RS.FromStart;
    if (!start) {
        from = RS.FromEnd;
    }

    var pts = entity.getPointsWithDistanceToEnd(-amount, from);
    if (pts.length===1) {
        if (start) {
            entity.trimStartPoint(pts[0], pts[0], true);
        }
        else {
            entity.trimEndPoint(pts[0], pts[0], true);
        }
    }

    return addEntity(entity);
}
