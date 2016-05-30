/**
 * Simple Information API, mainly designed for use in the ECMAScript console.
 */

/**
 * Auto zoom.
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
 *
 * \code
 * zoomTo(entity)
 * zoomTo(entity, margin)
 * zoomTo(entityId)
 * zoomTo(entityId, margin)
 * zoomTo(shape)
 * zoomTo(shape, margin)
 * zoomTo(x1,y1, x2,y2)
 * zoomTo(x1,y1, x2,y2, margin)
 * zoomTo(new RBox(x1,y1,x2,y2))
 * zoomTo(new RBox(x1,y1, x2,y2), margin)
 * \endcode
 */
function zoomTo(p1,p2,p3,p4,p5) {
    var margin = 10;

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

    if (isNumber(p1) && isNumber(p2)) {
        return zoomTo(new RBox(p1,p2, p3,p4), p5);
    }

    var view = getGraphicsView();
    if (isNull(view)) {
        return undefined;
    }
    view.zoomTo(p1, margin);
    return p1;
}
