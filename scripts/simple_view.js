/**
 * Simple Information API, mainly designed for use in the ECMAScript console.
 */

/**
 * Auto zoom.
 * \ingroup ecma_simple
 */
function autoZoom() {
    var view = getGraphicsView();
    if (isNull(view)) {
        return false;
    }
    view.autoZoom();
    return true;
}

/**
 * Zooms to the given entity.
 * Returns the bounding box of the given entity or undefined.
 * \ingroup ecma_simple
 *
 * \code
 * zoomTo(entity)
 * zoomTo(entity, margin)
 * zoomTo(entityId)
 * zoomTo(entityId, margin)
 * zoomTo(shape)
 * zoomTo(shape, margin)
 * zoomTo([x1,y1], [x2,y2])
 * zoomTo([x1,y1], [x2,y2], margin)
 * zoomTo(new RBox(x1,y1, x2,y2))
 * zoomTo(new RBox(x1,y1, x2,y2), margin)
 * \endcode
 */
function zoomTo(p1,p2,p3,p4,p5) {
    if (isEntity(p1) || isShape(p1)) {
        return zoomTo(p1.getBoundingBox(), p2);
    }

    if (isNumber(p1) && isNull(p3)) {
        var doc = getDocument();
        if (isNull(doc)) {
            return undefined;
        }
        var entity = doc.queryEntityDirect(e);
        var e = entity.data();
        return zoomTo(e.getBoundingBox(), p2);
    }

    if (isArray(p1) && isArray(p2)) {
        return zoomTo(new RBox(new RVector(p1), new RVector(p2)), p3);
    }

    var view = getGraphicsView();
    if (isNull(view)) {
        return undefined;
    }
    if (isNull(p2)) {
        p2 = 10;
    }
    view.zoomTo(p1, p2);
    return p1;
}
