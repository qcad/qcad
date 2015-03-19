/**
 * Simple API, mainly designed for use in the ECMAScript console.
 */

include("scripts/library.js");

PI = Math.PI;
LN2 = Math.LN2;
LN10 = Math.LN10;
LOG2E = Math.LOG2E;
LOG10E = Math.LOG10E;
SQRT1_2 = Math.SQRT1_2;
SQRT2 = Math.SQRT2;
abs = Math.abs;
ceil = Math.ceil;
floor = Math.floor;
exp = Math.exp;
log = Math.log;
max = Math.max;
min = Math.min;
pow = Math.pow;
sqrt = Math.sqrt;
random = Math.random;
round = Math.round;

function rad2deg(a) { 
    return a / (2.0 * Math.PI) * 360.0; 
}

function deg2rad(a) { 
    return (a / 360.0) * (2.0 * Math.PI); 
}

function sin(v) { 
    return Math.sin(deg2rad(v)); 
}

function cos(v) { 
    return Math.cos(deg2rad(v)); 
}

function tan(v) { 
    return Math.tan(deg2rad(v)); 
}

function asin(v) { 
    return rad2deg(Math.asin(v)); 
}

function acos(v) {
    return rad2deg(Math.acos(v)); 
}

function atan(v) { 
    return rad2deg(Math.atan(v)); 
}

function getMainWindow() {
    return RMainWindowQt.getMainWindow();
}

function getDocumentInterface() {
    var appWin = getMainWindow();
    return appWin.getDocumentInterface();
}

function getDocument() {
    var di = getDocumentInterface();
    return di.getDocument();
}

function addPoint(p1, p2) {
    if (isNumber(p1)) {
        addPoint(new RVector(p1, p2));
        return;
    }

    addShape(new RPoint(p1));
}

function addLine(p1, p2, p3, p4) {
    if (isNumber(p1)) {
        addLine(new RVector(p1, p2), new RVector(p3, p4));
        return;
    }

    addShape(new RLine(p1, p2));
}

function addArc(p1, p2, p3, p4, p5, p6) {
    if (isNumber(p1)) {
        addArc(new RVector(p1, p2), p3, p4, p5, p6);
        return;
    }
    addShape(new RArc(p1, p2, p3, p4, p5));
}

function addCircle(p1, p2, p3) {
    if (isNumber(p1)) {
        addCircle(new RVector(p1, p2), p3);
        return;
    }
    addShape(new RCircle(p1, p2));
}

/**
 * \param points Array of RVector or [x,y] tuples.
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
    addShape(pl);
}

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
              angle,
              true
        )
    );
    addEntity(entity);
}

function addShape(shape) {
    var di = getDocumentInterface();
    var entity = shapeToEntity(getDocument(), shape);
    addEntity(entity);
}

function addEntity(entity) {
    var di = getDocumentInterface();
    var op = new RAddObjectOperation(entity);
    di.applyOperation(op);
}
