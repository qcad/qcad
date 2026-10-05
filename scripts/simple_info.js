/**
 * Simple Information API, mainly designed for use in the ECMAScript console.
 */

/**
 * Returns intersection points between the two given entities or shapes.
 * \ingroup ecma_simple
 *
 * \param e1 First entity, entity ID or shape.
 * \param e2 Second entity, entity ID or shape.
 * \param limited True to only return intersection points that lay
 * on the given entities or shapes (visible intersections).
 */
function getIntersectionPoints(e1, e2, limited) {
    if (isNull(limited)) {
        limited = true;
    }

    // document is required if entity IDs are passed:
    var doc = undefined;
    if (isNumber(e1) || isNumber(e2)) {
        doc = getDocument();
        if (isNull(doc)) {
            return [];
        }
    }

    if (isNumber(e1)) {
        var entity1 = doc.queryEntityDirect(e1);
        e1 = entity1;
    }
    if (isNumber(e2)) {
        var entity2 = doc.queryEntityDirect(e2);
        e2 = entity2;
    }

    if (isEntity(e1) && isEntity(e2)) {
        return e1.getIntersectionPoints(getPtr(e2), limited);
    }
    if (isShape(e1) && isShape(e2)) {
        return e1.getIntersectionPoints(getPtr(e2), limited);
    }
    if (isEntity(e1) && isShape(e2)) {
        return e1.getIntersectionPointsWithShape(getPtr(e2), limited);
    }
    if (isShape(e1) && isEntity(e2)) {
        return e2.getIntersectionPointsWithShape(getPtr(e1), limited);
    }

    return [];
}

/**
 * Returns true if the given value is a position (RVector or array of two or
 * three numbers).
 * \ingroup ecma_simple
 */
function isPosition(p) {
    if (isVector(p)) {
        return true;
    }
    return isArray(p) && (p.length===2 || p.length===3) && isNumber(p[0]) && isNumber(p[1]);
}

/**
 * Converts the given position (RVector or [x,y] array) to an RVector.
 * \ingroup ecma_simple
 */
function toVector(p) {
    if (isVector(p)) {
        return p;
    }
    if (isArray(p)) {
        return new RVector(p);
    }
    return RVector.invalid;
}

/**
 * Returns the entity closest to the given position in the drawing.
 * \ingroup ecma_simple
 *
 * \param pos Position (RVector or [x,y]).
 * \param range Maximum distance from the position (optional, defaults to
 * a range that covers the whole drawing).
 *
 * \return A copy of the closest entity (REntity) or undefined.
 *
 * \code
 * getClosestEntity(x,y)
 * getClosestEntity([x,y])
 * getClosestEntity(new RVector(x,y), 0.5)
 * \endcode
 */
function getClosestEntity(pos, range) {
    if (arguments.length===2 && isNumber(arguments[0]) && isNumber(arguments[1])) {
        return getClosestEntity(new RVector(arguments[0], arguments[1]));
    }

    pos = toVector(pos);
    if (!isValidVector(pos)) {
        return undefined;
    }

    var doc = getTransactionDocument();
    if (isNull(doc)) {
        return undefined;
    }

    if (!isNumber(range)) {
        // range that covers the whole drawing:
        range = 1.0;
        var bb = doc.getBoundingBox(true, false);
        if (bb.isValid()) {
            range = Math.max(range, bb.getSize().getMagnitude() + bb.getCenter().getDistanceTo(pos));
        }
    }

    var id = doc.queryClosestXY(pos, range, false);
    if (id===RObject.INVALID_ID) {
        return undefined;
    }

    return doc.queryEntity(id);
}

/**
 * Returns the entity for the given entity reference.
 * \ingroup ecma_simple
 *
 * \param e Entity ID, entity object or position in the drawing (RVector or [x,y]).
 * For a position, the closest entity is returned.
 *
 * \return A copy of the entity (REntity) which can be modified and passed
 * to addEntity or addObject, or undefined.
 *
 * \code
 * getEntity(id)
 * getEntity(entity)
 * getEntity(x,y)
 * getEntity([x,y])
 * \endcode
 */
function getEntity(e) {
    if (arguments.length===2 && isNumber(arguments[0]) && isNumber(arguments[1])) {
        return getEntity(new RVector(arguments[0], arguments[1]));
    }

    var doc;
    if (isNumber(e)) {
        doc = getTransactionDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        if (isNull(entity)) {
            warning(qsTr("ID does not refer to an entity:") + e);
            return undefined;
        }
        return entity;
    }

    if (isEntity(e)) {
        var id = e.getId();
        if (id!==RObject.INVALID_ID) {
            doc = getTransactionDocument();
            if (!isNull(doc)) {
                var stored = doc.queryEntity(id);
                if (!isNull(stored)) {
                    return stored;
                }
            }
        }
        return e.clone();
    }

    if (isPosition(e)) {
        return getClosestEntity(e);
    }

    return undefined;
}

/**
 * Returns the shape for the given reference.
 * \ingroup ecma_simple
 *
 * \param e Entity ID, entity object, shape or position in the drawing (RVector or [x,y]).
 * \param pos Position used to choose the closest sub shape of complex entities
 * (hatches, dimensions, block references). Optional.
 *
 * \return RShape or undefined. Shapes are returned as they are. For entities,
 * the shape of the entity is returned (RLine for a line entity, RPolyline for
 * a polyline entity, etc.)
 *
 * \code
 * getShape(id)
 * getShape(entity)
 * getShape(shape)
 * getShape(x,y)
 * getShape([x,y])
 * \endcode
 */
function getShape(e, pos) {
    if (arguments.length===2 && isNumber(arguments[0]) && isNumber(arguments[1])) {
        return getShape(new RVector(arguments[0], arguments[1]));
    }

    if (isShape(e)) {
        return e;
    }

    var entity = getEntity(e);
    if (isNull(entity)) {
        return undefined;
    }

    if (isNull(pos) && isPosition(e)) {
        pos = e;
    }

    return getEntityShape(entity, toVector(pos));
}

/**
 * Returns the shape of the given entity. For complex entities (hatches,
 * dimensions, block references), the sub shape closest to the given
 * position is returned.
 * \ingroup ecma_simple
 *
 * \param entity REntity
 * \param pos RVector (optional)
 *
 * \return RShape or undefined
 */
function getEntityShape(entity, pos) {
    if (isNull(entity)) {
        return undefined;
    }

    var shape = entity.castToShape();
    if (!isNull(shape)) {
        return shape;
    }

    if (!isValidVector(pos)) {
        pos = entity.getPointOnEntity();
    }

    var sp = entity.getClosestShape(pos);
    if (isNull(sp)) {
        return undefined;
    }
    return getPtr(sp);
}
