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

    // document is required if entitiy IDs are passed:
    var doc = undefined;
    if (isNumber(e1) || isNumber(e2)) {
        doc = getDocument();
        if (isNull(doc)) {
            return [];
        }
    }

    if (isNumber(e1)) {
        var entity1 = doc.queryEntityDirect(e1);
        e1 = entity1.data();
    }
    if (isNumber(e2)) {
        var entity2 = doc.queryEntityDirect(e2);
        e2 = entity2.data();
    }

    if (isEntity(e1) && isEntity(e2)) {
        return e1.getIntersectionPoints(e2, limited);
    }
    if (isShape(e1) && isShape(e2)) {
        return e1.getIntersectionPoints(e2, limited);
    }
    if (isEntity(e1) && isShape(e2)) {
        return e1.getIntersectionPointsWithShape(e2, limited);
    }
    if (isShape(e1) && isEntity(e2)) {
        return e2.getIntersectionPointsWithShape(e1, limited);
    }

    return [];
}
