/**
 * Simple Modification API, mainly designed for use in the ECMAScript console.
 */

/**
 * Moves the given entity or shape by the given offset.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * move(entity, x,y)
 * move(entity, new RVector(x,y))
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
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * rotate(entity, angle, cx,cy)
 * rotate(entity, angle, new RVector(cx,cy))
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

/**
 * Scales the given entity or shape by the given factor with the given focus point.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * scale(entity, factor, cx,cy)
 * scale(entity, factor, new RVector(cx,cy))
 * \endcode
 */
function scale(e, factor, p1, p2) {
    if (isNumber(p1)) {
        return scale(e, factor, new RVector(p1, p2));
    }
    if (isNumber(e)) {
        var doc = getDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        return scale(entity, factor, p1);
    }

    if (isNull(p1)) {
        e.scale(factor);
    }
    else {
        e.scale(factor, p1);
    }
    return addEntity(e);
}

/**
 * Mirrors the given entity or shape at the given axis.
 * \ingroup ecma_simple
 *
 * \param e Entity, entity ID or shape.
 *
 * \code
 * mirror(entity, axis)
 * mirror(entity, p1, p2)
 * mirror(entity, x1,y1, x2,y2)
 * \endcode
 */
function mirror(e, p1, p2, p3, p4) {
    if (isNumber(p1)) {
        return mirror(e, new RLine(new RVector(p1, p2), new RVector(p3, p4)));
    }
    if (isVector(p1)) {
        return mirror(e, new RLine(p1, p2));
    }
    if (isNumber(e)) {
        var doc = getDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntity(e);
        return mirror(entity, p1);
    }

    e.mirror(p1);
    return addEntity(e);
}
