/**
 * Simple API, mainly designed for use in the ECMAScript console.
 */

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

function addPoint(x, y) {
    addShape(new RPoint(x, y));
}

function addLine(x1, y1, x2, y2) {
    addShape(new RLine(x1, y1, x2, y2));
}

function addArc(cx, cy, radius, a1, a2, rev) {
    addShape(new RArc(cx, cy, radius, a1, a2, rev));
}

function addCircle(cx, cy, radius) {
    addShape(new RCircle(cx, cy, radius));
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
