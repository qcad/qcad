/**
 * Simple Creation API, mainly designed for use in the ECMAScript console.
 */

/**
 * Adds a point to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addPoint(x,y)
 * addPoint([x,y])
 * addPoint(new RVector(x,y))
 * \endcode
 */
function addPoint(position) {
    if (arguments.length===2) {
        return addPoint(new RVector(arguments[0], arguments[1]));
    }

    if (isArray(position)) {
        return addPoint(new RVector(position));
    }

    return addShape(new RPoint(position));
}

/**
 * Adds a line to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addLine(x1,y1, x2,y2)
 * addLine([x1,y1], [x2,y2])
 * addLine(new RVector(x1,y1), new RVector(x2,y2))
 * \endcode
 */
function addLine(startPoint, endPoint) {
    if (arguments.length===4) {
        return addLine(new RVector(arguments[0], arguments[1]), new RVector(arguments[2], arguments[3]));
    }

    if (isArray(startPoint)) {
        startPoint = new RVector(startPoint);
    }
    if (isArray(endPoint)) {
        endPoint = new RVector(endPoint);
    }

    return addShape(new RLine(startPoint, endPoint));
}

/**
 * Adds an arc to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addArc(cx,cy, radius, startAngle, endAngle, reversed)
 * addArc([cx,cy], radius, startAngle, endAngle, reversed)
 * addArc(new RVector(cx,cy), radius, startAngle, endAngle, reversed)
 * \endcode
 */
function addArc(center, radius, startAngle, endAngle, reversed) {
    if (arguments.length===6) {
        return addShape(new RVector(arguments[0], arguments[1]), arguments[2], arguments[3], arguments[4], arguments[5]);
    }

    if (isArray(center)) {
        center = new RVector(center);
    }
    return addShape(new RArc(center, radius, deg2rad(startAngle), deg2rad(endAngle), reversed));
}

/**
 * Adds a circle to the drawing.
 * \ingroup ecma_simple
 *
 * \code
 * addCircle(cx,cy, radius)
 * addCircle([cx,cy], radius)
 * addCircle(new RVector(cx,cy), radius)
 * \endcode
 */
function addCircle(center, radius) {
    if (arguments.length===3) {
        return addShape(new RVector(arguments[0], arguments[1]), arguments[2]);
    }

    if (isArray(center)) {
        center = new RVector(center);
    }
    return addShape(new RCircle(center));
}

/**
 * Adds a polyline to the drawing.
 * \ingroup ecma_simple
 * \author Andrew Mustun
 * \author tukuyomi
 *
 * \param p Array of type [ [ x, y, bulge, relative ], ..., [ ... ] ]
 * or [ [ vector, bulge, relative ], ..., [ ... ] ]
 * Where:
 * x: X coordinate
 * y: Y coordinate
 * vector: RVector with position of vertex
 * bulge: Bulge for next segment after vertex, defaults to 0.0.
 * relative: True if this vector's coordinates are relative to the previous coordinates,
 * defaults to false.
 *
 * \param closed True for an implicitely closed polyline. Default is false.
 * \param relative True to treat all coordinates as relative.
 * The first coordinate is always absolute. Default is false.
 *
 * \code
 * addPolyline([[x1,y1],[x2,y2],[x3,y3]], false)
 * addPolyline([ [ 100 , 0 ], [ 20 , -10 , 1 ], [ 0 , 40 , 0 , true ], [ -20 , -10 , 1 , true ] ])
 * addPolyline([new RVector(x1,y1)],new RVector(x2,y2),new RVector(x3,y3)], closed, relative)
 * addPolyline([new RVector(x1,y1),bulge1,rel1],[new RVector(x2,y2),bulge2,rel2],[new RVector(x3,y3),bulge3,rel3]], closed, relative)
 * \endcode
 */
function addPolyline(points, closed, relative) {
    if (isNull(closed)) {
        closed = false;
    }
    if (isNull(relative)) {
        relative = false;
    }

    var pl = new RPolyline();
    pl.setClosed(closed);

    var v = new RVector(0,0);
    for (var i=0; i<points.length; i++) {
        var v0, b, rel;

        // first item in vertex tuple is RVector or x,y pair:
        if (isVector(points[i][0])) {
            v0 = points[i][0];
            b = points[i][1];
            rel = points[i][2];
        }
        else {
            v0 = new RVector(points[i][0], points[i][1]);
            b = points[i][2];
            rel = points[i][3];
        }

        // defaults for vertices:
        if (isNull(b)) {
            b = 0.0;
        }
        if (isNull(rel)) {
            rel = relative;
        }

        // relative or absolute vertex position:
        if (relative) {
            v = v.operator_add(v0);
        }
        else {
            v = v0;
        }

        pl.appendVertex(v, b);
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
 * \param position position
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
 * addSimpleText(text, [x, y], height, angle, font, vAlign, hAlign, bold, italic)
 * addSimpleText(text, new RVector(x, y), height, angle, font, vAlign, hAlign, bold, italic)
 * \endcode
 */
function addSimpleText(text, position, height, angle, font, vAlign, hAlign, bold, italic) {
    if (arguments.length===10) {
        return addShape(arguments[0], new RVector(arguments[1], arguments[2]), arguments[3], arguments[4], arguments[5], arguments[6], arguments[7], arguments[8], arguments[9]);
    }

    var doc = getTransactionDocument();
    if (isNull(doc)) {
        return undefined;
    }

    if (isNull(height)) height = 1.0;
    if (isNull(angle)) angle = 0.0;
    if (isNull(font)) font = "Standard";
    if (isNull(vAlign)) vAlign = RS.VAlignTop;
    if (isNull(hAlign)) hAlign = RS.HAlignLeft;
    if (isNull(bold)) bold = false;
    if (isNull(italic)) italic = false;

    if (isArray(position)) {
        position = new RVector(position);
    }

    var entity = new RTextEntity(
        doc,
        new RTextData(
              position,
              position,
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
 * Adds the given RShape to the drawing as a new entity using current layer and attributes.
 * \ingroup ecma_simple
 *
 * \return The added entity. The entity does not yet have a valid ID if it was added within a
 * transaction.
 */
function addShape(shape) {
    var doc = getTransactionDocument();
    if (isNull(doc)) {
        return undefined;
    }

    var entity = shapeToEntity(doc, shape);
    return addEntity(entity);
}

/**
 * Adds the given REntity to the drawing using layer and attributes as set by the entity.
 * \ingroup ecma_simple
 *
 * \return The added entity. The entity does not yet have a valid ID if it was added within a
 * transaction.
 */
function addEntity(entity) {
    if (isFunction(entity.data)) {
        addEntity(entity.data().clone());
    }

    if (__simpleUseOp===true) {
        if (isNull(__simpleOp)) {
            __simpleOp = new RAddObjectsOperation();
            qDebug("create op");
        }
        __simpleOp.addObject(entity, false);
        return entity
    }
    else {
        var di = getDocumentInterface();
        di.applyOperation(new RAddObjectOperation(entity, false));
        qDebug("apply local op");
        return entity;
    }
}
