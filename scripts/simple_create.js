/**
 * Simple Creation API, mainly designed for use in the ECMAScript console.
 */

/**
 * Adds a point to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addPoint(x,y)
 * addPoint(new RVector(x,y))
 * \endcode
 */
function addPoint(p1, p2) {
    if (isNumber(p1)) {
        return addPoint(new RVector(p1, p2));
    }

    return addShape(new RPoint(p1));
}

/**
 * Adds a line to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addLine(x1,y1, x2,y2)
 * addLine(new RVector(x1,y1), new RVector(x2,y2))
 * \endcode
 */
function addLine(p1, p2, p3, p4) {
    if (isNumber(p1)) {
        return addLine(new RVector(p1, p2), new RVector(p3, p4));
    }

    return addShape(new RLine(p1, p2));
}

/**
 * Adds an arc to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addArc(cx,cy, radius, startAngle, endAngle, reversed)
 * addArc(new RVector(cx,cy), radius, startAngle, endAngle, reversed)
 * \endcode
 */
function addArc(p1, p2, p3, p4, p5, p6) {
    if (isNumber(p1)) {
        return addArc(new RVector(p1, p2), p3, p4,p5, p6);
    }
    return addShape(new RArc(p1, p2, deg2rad(p3),deg2rad(p4), p5));
}

/**
 * Adds a circle to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addCircle(cx,cy, radius)
 * addCircle(new RVector(cx,cy), radius)
 * \endcode
 */
function addCircle(p1, p2, p3) {
    if (isNumber(p1)) {
        return addCircle(new RVector(p1, p2), p3);
    }
    return addShape(new RCircle(p1, p2));
}

/**
 * Adds a polyline to the drawing.
 * \ingroup ecma_simple
 *
 * \param points Array of RVector or [x,y] tuples.
 * \param closed True for an implicitely closed polyline.
 *
 * \code
 * addPolyline([[x1,y1],[x2,y2],[x3,y3]], false)
 * addPolyline([new RVector(x1,y1)],new RVector(x2,y2),new RVector(x3,y3)], false)
 * \endcode
 */
function addPolyline(points, closed) {
    if (isNull(closed)) {
        closed = false;
    }
    var pl = new RPolyline();
    pl.setClosed(closed);
    for (var i=0; i<points.length; i++) {
        if (isVector(points[i])) {
            pl.appendVertex(points[i]);
        }
        else {
            pl.appendVertex(new RVector(points[i][0], points[i][1]));
        }
    }
    return addShape(pl);
}

/**
 * Adds a spline to the drawing.
 * \ingroup ecma_simple
 *
 * \param fitPoints Array of RVector or [x,y] tuples.
 * \param closed True for a closed, periodic spline.
 *
 * \code
 * addSpline([[x1,y1],[x2,y2],[x3,y3]], false)
 * addSpline([new RVector(x1,y1)],new RVector(x2,y2),new RVector(x3,y3)], false)
 * \endcode
 */
function addSpline(points, closed) {
    if (isNull(closed)) {
        closed = false;
    }
    var sp = new RSpline();
    sp.setPeriodic(closed);
    for (var i=0; i<points.length; i++) {
        if (isVector(points[i])) {
            sp.appendFitPoint(points[i]);
        }
        else {
            sp.appendFitPoint(new RVector(points[i][0], points[i][1]));
        }
    }
    return addShape(sp);
}

/**
 * Adds a simple text to the drawing.
 * \ingroup ecma_simple
 *
 * \param text Text string.
 * \param x X position
 * \param y Y position
 * \param height Text height (defaults to 1)
 * \param angle Text angle (defaults to 0)
 * \param font Font (defaults to "standard")
 * \param vAlign Vertical alignment (defaults to RS.VAlignTop)
 * \param hAlign Horizontal alignment (defaults to RS.HAlignLeft)
 * \param bold True for bold text (TTF fonts only)
 * \param italic True for italic text (TTF fonts only)
 *
 * \code
 * addSimpleText(text, x, y, height, angle, font, vAlign, hAlign, bold, italic)
 * \endcode
 */
function addSimpleText(text, x, y, height, angle, font, vAlign, hAlign, bold, italic) {
    if (isNull(height)) height = 1.0;
    if (isNull(angle)) angle = 0.0;
    if (isNull(font)) font = "Standard";
    if (isNull(vAlign)) vAlign = RS.VAlignTop;
    if (isNull(hAlign)) hAlign = RS.HAlignLeft;
    if (isNull(bold)) bold = false;
    if (isNull(italic)) italic = false;

    var entity = new RTextEntity(
        getDocument(),
        new RTextData(
              new RVector(x, y),
              new RVector(x, y),
              height,
              100.0,
              vAlign,
              hAlign,
              RS.LeftToRight,
              RS.Exact,
              1.0,
              text,
              font,
              bold,
              italic,
              deg2rad(angle),
              true
        )
    );
    return addEntity(entity);
}

/**
 * Adds the given RShape to the drawing using current layer and attributes.
 * \ingroup ecma_simple
 */
function addShape(shape) {
    var di = getDocumentInterface();
    var entity = shapeToEntity(getDocument(), shape);
    return addEntity(entity);
}

/**
 * Adds the given REntity to the drawing using layer and attributes as set by the entity.
 * \ingroup ecma_simple
 *
 * \return ID of added entity or undefined if a transaction is in progress
 * and the entity ID is not yet known.
 */
function addEntity(entity) {
    if (isFunction(entity.data)) {
        addEntity(entity.data().clone());
    }

    if (__simpleUseOp===true) {
        if (isNull(__simpleOp)) {
            __simpleOp = new RAddObjectsOperation();
        }
        __simpleOp.addObject(entity, false);
        return undefined;
    }
    else {
        var di = getDocumentInterface();
        di.applyOperation(new RAddObjectOperation(entity, false));
        return entity.getId();
    }
}
