/**
 * Simple Modification API, mainly designed for use in the ECMAScript console.
 */

/**
 * Moves the given entity or shape by the given offset.
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * move(entity, x,y)
 * move(entity, new RVector(x,y))
 * move(entityId, x,y)
 * move(entityId, new RVector(x,y))
 * move(shape, x,y)
 * move(shape, new RVector(x,y))
 * \endcode
 */
function move(e, p1, p2) {
    if (isNumber(p1)) {
        return move(e, new RVector(p1, p2));
    }
    if (isNumber(e)) {
        var doc = getDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        return move(entity, p1);
    }

    e.move(p1);
    return addEntity(e);
}

/**
 * Rotates the given entity or shape by the given angle around the given center.
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * rotate(entity, angle, cx,cy)
 * rotate(entity, angle, new RVector(cx,cy))
 * rotate(entityId, angle, cx,cy)
 * rotate(entityId, angle, new RVector(cx,cy))
 * rotate(shape, angle, cx,cy)
 * rotate(shape, angle, new RVector(x,y))
 * \endcode
 */
function rotate(e, angle, p1, p2) {
    if (isNumber(p1)) {
        return rotate(e, angle, new RVector(p1, p2));
    }
    if (isNumber(e)) {
        var doc = getDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        return rotate(entity, angle, p1);
    }

    if (isNull(p1)) {
        e.rotate(deg2rad(angle));
    }
    else {
        e.rotate(deg2rad(angle), p1);
    }
    return addEntity(e);
}
