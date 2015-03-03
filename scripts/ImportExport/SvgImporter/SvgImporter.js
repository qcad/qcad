/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("scripts/library.js");
include("scripts/ShapeAlgorithms.js");

/**
 * SAX style XML handler.
 */
function SvgHandler(svgImporter) {
    QXmlDefaultHandler.call(this);
    this.context = "";
    this.svgImporter = svgImporter;
    this.displayStack = [];
    this.elementStack = [];
    this.transformStack = [];
    this.styleStack = [];
}

SvgHandler.prototype = new QXmlDefaultHandler();

SvgHandler.rxStyleStroke = new RegExp(
    "stroke\\s*:\\s*([^;]*)",
    "gim"
);

SvgHandler.rxTransform = new RegExp(
    "(translate)\\s*\\(" +
        "\\s*" +
        "([+-]?\\d*\\.?\\d*)" +
        "[,\\s]+" +
        "([+-]?\\d*\\.?\\d*)" +
        "[\\s]*" +
    "\\)" +
    "|" +
    "(rotate)\\s*\\(" +
        "\\s*" +
        "([+-]?\\d*\\.?\\d*)" +
        "[\\s]*" +
    "\\)" +
    "|" +
    "(matrix)\\s*\\(" +
        "\\s*" +
        "([+-]?\\d*\\.?\\d*)" +
        "[,\\s]+" +
        "([+-]?\\d*\\.?\\d*)" +
        "[,\\s]+" +
        "([+-]?\\d*\\.?\\d*)" +
        "[,\\s]+" +
        "([+-]?\\d*\\.?\\d*)" +
        "[,\\s]+" +
        "([+-]?\\d*\\.?\\d*)" +
        "[,\\s]+" +
        "([+-]?\\d*\\.?\\d*)" +
        "[\\s]*" +
    "\\)",
    "gim"
);

/**
 * \return QTransform object from given transform attribute string.
 */
SvgHandler.prototype.getTransform = function(str) {
    var ret = new QTransform();
    var t = undefined;

    var match;
    SvgHandler.rxTransform.lastIndex = 0;
    while (match = SvgHandler.rxTransform.exec(str)) {
        if (match.length<2) {
            continue;
        }

        if (!isNull(match[1]) && match[1].toLowerCase()==="translate") {
            t = new QTransform();
            t.translate(match[2], match[3]);
        }
        else if (!isNull(match[4]) && match[4].toLowerCase()==="rotate") {
            t = new QTransform();
            t.rotate(match[5]);
        }
        else if (!isNull(match[6]) && match[6].toLowerCase()==="matrix") {
            t = new QTransform(
                        match[7], match[8], 0.0,
                        match[9], match[10], 0.0,
                        match[11], match[12], 1.0
            );
        }

        if (!isNull(t)) {
            t.operator_multiply_assign(ret);
            ret = t;
        }
    }

    return ret;
};

/**
 * Handle element (tag).
 */
SvgHandler.prototype.startElement = function(namespaceURI, localName, qName, atts) {
    this.elementStack.push(localName);
    this.displayStack.push(atts.value("display"));

    // handle transforms:
    var transformAttr = atts.value("transform");
    var newTransform = new QTransform();
    if (this.transformStack.length!==0) {
        newTransform = this.transformStack[this.transformStack.length-1];
    }
    if (transformAttr!=="") {
        // got transform attribute: update transform stack:
        var transform = this.getTransform(transformAttr);
//        var combinedTransform = new QTransform();
//        if (this.transformStack.length!==0) {
//            combinedTransform = this.transformStack[this.transformStack.length-1];
//        }
        transform.operator_multiply_assign(newTransform);
        newTransform = transform;

//        for (var i=0; i<this.transformStack.length; i++) {
//            qDebug("[" + i + "]: ", this.transformStack[i]);
//        }
    }
//    else {
//        // no transform attribute given: keep same transform:
//        if (this.transformStack.length!==0) {
//            newTransform = this.transformStack[this.transformStack.length-1];
//        }
//        // add identity transform to transform stack:
//        else {
//            newTransform = new QTransform();
//        }
//    }
    this.transformStack.push(newTransform);
    this.svgImporter.setTransform(newTransform);

    // handle style (color):
    var styleAttr = atts.value("style");
    var newStyle = {};
    if (this.styleStack.length>0) {
        newStyle = deepCopy(this.styleStack[this.styleStack.length-1]);
    }

    if (styleAttr!=="") {
        //qDebug("styleAttr: ", styleAttr);
        SvgHandler.rxStyleStroke.lastIndex = 0;
        var match = SvgHandler.rxStyleStroke.exec(styleAttr);
        //qDebug("match: ", match);
        if (!isNull(match) && match.length===2) {
            newStyle.stroke = match[1];
            //qDebug("color: ", match[1]);
        }
    }
    this.styleStack.push(newStyle);
    this.svgImporter.setStyle(newStyle);

    // ignore some elements and all theirs child elements:
    if (this.elementStack.contains("metadata") ||
        this.elementStack.contains("pattern")) {
        return true;
    }

    // ignore invisible groups and other elements:
    if (this.displayStack.contains("none")) {
        //qDebug("ignoring: invisible");
        return true;
    }

    var x1, y1, x2, y2;
    var cx, cy, r;
    var rx, ry;
    var x,y, width,height;

    switch (localName) {
    case "metadata":
        break;

    case "g":
        break;

    case "path":
        this.svgImporter.importPath(atts.value("d"));
        break;

    case "polygon":
        this.svgImporter.importPolygon(atts.value("points"), false);
        break;

    case "polyline":
        this.svgImporter.importPolygon(atts.value("points"), true);
        break;

    case "line":
        x1 = parseFloat(atts.value("x1"));
        y1 = parseFloat(atts.value("y1"));
        x2 = parseFloat(atts.value("x2"));
        y2 = parseFloat(atts.value("y2"));
        this.svgImporter.importLine(x1,y1, x2,y2);
        break;

    case "circle":
        cx = parseFloat(atts.value("cx"));
        cy = parseFloat(atts.value("cy"));
        r = parseFloat(atts.value("r"));
        this.svgImporter.importCircle(cx,cy, r);
        break;

    case "ellipse":
        cx = parseFloat(atts.value("cx"));
        cy = parseFloat(atts.value("cy"));
        rx = parseFloat(atts.value("rx"));
        ry = parseFloat(atts.value("ry"));
        this.svgImporter.importEllipse(cx,cy, rx,ry);
        break;

    case "rect":
        x = parseFloat(atts.value("x"));
        y = parseFloat(atts.value("y"));
        width = parseFloat(atts.value("width"));
        height = parseFloat(atts.value("height"));
        this.svgImporter.importRectangle(x,y, width,height);
        break;
    }

    this.context = localName;

    return true;
};

SvgHandler.prototype.endElement = function(namespaceURI, localName, qName) {
    this.styleStack.pop();
    if (this.styleStack.length>0) {
        this.svgImporter.setStyle(this.styleStack[this.styleStack.length-1]);
    }

    this.transformStack.pop();
    if (this.transformStack.length>0) {
        this.svgImporter.setTransform(this.transformStack[this.transformStack.length-1]);
    }

    this.displayStack.pop();
    this.elementStack.pop();

    return true;
};




/**
 * \class SvgImporter
 * \brief Very basic SVG import implementation. Only supports
 * a few SVG tags.
 *
 * \todo Use a 3rd party library to fully support SVG.
 */
function SvgImporter(document, resolution) {
    if (isNull(resolution)) {
        // default resolution, e.g. for library items:
        resolution = 90;
    }

    RFileImporterAdapter.call(this, document);
    this.setDocument(document);
    this.transform = new QTransform();
    this.style = {};

    // resolution for pixel values in PPI (pixels / inch):
    this.resolution = resolution;
    this.resolutionScale = RUnit.convert(1/this.resolution, RS.Inch, document.getUnit());
}

SvgImporter.prototype = new RFileImporterAdapter();

SvgImporter.includeBasePath = includeBasePath;

/**
 * Sets the current style to apply to all imported entities.
 * \param s object with style attributes (e.g. s.stroke="red")...
 */
SvgImporter.prototype.setStyle = function(s) {
    this.style = s;
};

/**
 * Sets the current QTransform to apply to all imported entities.
 */
SvgImporter.prototype.setTransform = function(t) {
    this.transform = t;
};

SvgImporter.prototype.importFile = function(fileName) {
    qDebug("SvgImporter.prototype.importFile");

    if (isNull(this.getDocument())) {
        this.setDocument(EAction.getDocument());
    }

    var fi = new QFileInfo(fileName);

    var file = new QFile(fi.absoluteFilePath());
    var xmlReader = new QXmlSimpleReader();
    var source = new QXmlInputSource(file);
    var handler = new SvgHandler(this);
    xmlReader.setContentHandler(handler);
    var ok = xmlReader.parse(source, false);
    file.close();
    
    this.endImport();

    return true;
};

SvgImporter.prototype.importShape = function(shape) {
    var shapeP;

    if (isArcShape(shape) || isEllipseShape(shape) || isCircleShape(shape)) {
        var t = this.transform;
        shape = ShapeAlgorithms.transformArc(shape,
            function(v) {
                v.transform2d(t);
            }
        );
    }
    else {
        shapeP = shape.getTransformed(this.transform);
        shape = shapeP.data();
    }

    shape.scale(new RVector(1.0, -1.0));
    shape.scale(new RVector(this.resolutionScale, this.resolutionScale));

    var entity = shapeToEntity(this.getDocument(), shape);

    if (isNull(entity)) {
        return;
    }

    if (!isNull(this.style.stroke)) {
        entity.setColor(new RColor(this.style.stroke));
    }
    this.importObject(entity);
};

SvgImporter.prototype.importCircle = function(x, y, r) {
    this.importShape(new RCircle(new RVector(x, y), r));
};

SvgImporter.prototype.importEllipse = function(x, y, rx, ry) {
    this.importShape(new REllipse(new RVector(x, y), new RVector(rx, 0), ry/rx, 0.0, 2*Math.PI, false));
};

SvgImporter.prototype.importRectangle = function(x, y, w, h) {
    this.importShape(new RLine(new RVector(x, y), new RVector(x+w, y)));
    this.importShape(new RLine(new RVector(x+w, y), new RVector(x+w, y+h)));
    this.importShape(new RLine(new RVector(x+w, y+h), new RVector(x, y+h)));
    this.importShape(new RLine(new RVector(x, y+h), new RVector(x, y)));
};

SvgImporter.prototype.importLine = function(x1, y1, x2, y2) {
    this.importShape(new RLine(new RVector(x1, y1), new RVector(x2, y2)));
};

SvgImporter.prototype.importArc = function(ox, oy, x, y, rx, ry, angle, isLarge, sweep) {
    var entity;
    var center = SvgImporter.getArcCenter(ox, oy, x, y, rx, ry, sweep, !isLarge, angle);
    if (Math.abs(rx-ry) < RS.PointTolerance) {
        this.importShape(new RArc(center, rx, center.getAngleTo(new RVector(ox, oy)), center.getAngleTo(new RVector(x, y)), !sweep));
    }
    else {
        // TODO
        //var ellipse = new REllipseArc();
        //entity = new REllipseEntity(this.getDocument(), new REllipseData(ellipse));
    }
};

/**
 * Imports a cubic spline with the given start point, control points and ent point.
 * If the spline is almost exactly resembling an arc, an arc is imported instead.
 */
SvgImporter.prototype.importBezier = function(x1, y1, px1, py1, px2, py2, x2, y2) {
    var spline = new RSpline();
    spline.setDegree(3);
    spline.appendControlPoint(new RVector(x1, y1));
    spline.appendControlPoint(new RVector(px1, py1));
    spline.appendControlPoint(new RVector(px2, py2));
    spline.appendControlPoint(new RVector(x2, y2));

    var shape = ShapeAlgorithms.splineToLineOrArc(spline, 0.1);

    this.importShape(shape);
};

SvgImporter.prototype.importBezier2 = function(x1, y1, px, py, x2, y2) {
    var spline = new RSpline();
    spline.setDegree(2);
    spline.appendControlPoint(new RVector(x1, y1));
    spline.appendControlPoint(new RVector(px, py));
    spline.appendControlPoint(new RVector(x2, y2));
    this.importShape(spline);
};

/**
 * Parses the given path data string and imports the lines, arcs and splines
 * from the path.
 */
SvgImporter.prototype.importPath = function(dData) {
    var segs = dData.split(/(?=[mlhvcsqtaz])/i);
    var x = 0;
    var y = 0;
    var x0, y0;  // start point of sub path for z command
    var ox, oy;  // last x/y coordinate
    var px, py;
    var pc;
    var k = 0;

    var rx, ry;
    var angle;
    var isLarge;
    var sweep;

    for (var i=0; i<segs.length; i++) {
        var seg = segs[i];
        //qDebug("seg[" + i + "]: ", seg);
        var cmd = seg.match(/[mlhvcsqtaz]/i);
        if (!cmd) {
            //qDebug("abort...");
            return;
        }
        cmd = cmd[0];
        var coords = 
            seg.match(/(([+-]?[0-9][0-9]*\.?[0-9]*)|[+-]?(\.[0-9]+))([Ee][+-]?[0-9]+)?/gi);
        if (coords) {
            coords = coords.map(parseFloat);
        }

        ox = x;
        oy = y;

        switch(cmd) {
        case 'M':
            for (k=0; k<coords.length; k+=2) {
                x = coords[k+0];
                y = coords[k+1];
                px = py = null;
                // coordinates after the first: implicit line to:
                if (k!==0) {
                    this.importLine(ox, oy, x, y);
                }
                else {
                    x0 = x;
                    y0 = y;
                }

                ox = x;
                oy = y;
            }
            break;

        case 'm':
            for (k=0; k<coords.length; k+=2) {
                x += coords[k+0];
                y += coords[k+1];
                px = py = null;
                // coordinates after the first: implicit line to:
                if (k!==0) {
                    this.importLine(ox, oy, x, y);
                }
                else {
                    x0 = x;
                    y0 = y;
                }

                ox = x;
                oy = y;
            }
            break;

        case 'L':
            for (k=0; k<coords.length; k+=2) {
                x = coords[k+0];
                y = coords[k+1];
                px = py = null;
                this.importLine(ox, oy, x, y);
                ox = x;
                oy = y;
            }
            break;

        case 'l':
            for (k=0; k<coords.length; k+=2) {
                x += coords[k+0];
                y += coords[k+1];
                px = py = null;
                this.importLine(ox, oy, x, y);
                ox = x;
                oy = y;
            }
            break;

        case 'H':
            for (k=0; k<coords.length; k+=1) {
                x = coords[k+0];
                px = py = null;
                this.importLine(ox, oy, x, y);
                ox = x;
            }
            break;

        case 'h':
            for (k=0; k<coords.length; k+=1) {
                x += coords[k+0];
                px = py = null;
                this.importLine(ox, oy, x, y);
                ox = x;
            }
            break;

        case 'V':
            for (k=0; k<coords.length; k+=1) {
                y = coords[k+0];
                px = py = null;
                this.importLine(ox, oy, x, y);
                oy = y;
            }
            break;

        case 'v':
            for (k=0; k<coords.length; k+=1) {
                y += coords[k+0];
                px = py = null;
                this.importLine(ox, oy, x, y);
                oy = y;
            }
            break;

        case 'C':
            for (k=0; k<coords.length; k+=6) {
                x = coords[k+4];
                y = coords[k+5];
                px = coords[k+2];
                py = coords[k+3];
                this.importBezier(ox, oy,
                                  coords[k+0], coords[k+1],
                                  coords[k+2], coords[k+3],
                                  coords[k+4], coords[k+5]);
                ox = x;
                oy = y;
            }
            break;

        case 'c':
            for (k=0; k<coords.length; k+=6) {
                this.importBezier(ox, oy,
                                  coords[k+0] + x, coords[k+1] + y,
                                  coords[k+2] + x, coords[k+3] + y,
                                  coords[k+4] + x, coords[k+5] + y);
                px = x + coords[k+2];
                py = y + coords[k+3];
                x += coords[k+4];
                y += coords[k+5];
                ox = x;
                oy = y;
            }
            break;

        case 'S':
            if (isNull(px) || !pc.match(/[sc]/i)) {
                px = x;
                py = y;
            }
            this.importBezier(ox, oy,
                              x-(px-x), y-(py-y),
                              coords[0], coords[1],
                              coords[2], coords[3]);
            px = coords[0];
            py = coords[1];
            x = coords[2];
            y = coords[3];
            break;

        case 's':
            if (isNull(px) || !pc.match(/[sc]/i)) {
                px = x;
                py = y;
            }
            this.importBezier(ox, oy,
                              x-(px-x), y-(py-y),
                              x + coords[0], y + coords[1],
                              x + coords[2], y + coords[3]);
            px = x + coords[0];
            py = y + coords[1];
            x += coords[2];
            y += coords[3];
            break;

        case 'Q':
            px = coords[0];
            py = coords[1];
            x = coords[2];
            y = coords[3];
            this.importBezier2(ox, oy,
                              coords[0], coords[1],
                              coords[2], coords[3]);
            break;

        case 'q':
            this.importBezier2(ox, oy,
                              coords[0] + x, coords[1] + y,
                              coords[2] + x, coords[3] + y);
            px = x + coords[0];
            py = y + coords[1];
            x += coords[2];
            y += coords[3];
            break;

        case 'T':
            if (isNull(px) || !pc.match(/[qt]/i)) {
                px = x;
                py = y;
            } else {
                px = x-(px-x);
                py = y-(py-y);
            }
            this.importBezier2(ox, oy,
                              px, py,
                              coords[0], coords[1]);
            px = x-(px-x);
            py = y-(py-y);
            x = coords[0];
            y = coords[1];
            break;

        case 't':
            if (px == null || !pc.match(/[qt]/i)) {
                px = x;
                py = y;
            } else {
                px = x-(px-x);
                py = y-(py-y);
            }
            this.importBezier2(ox, oy,
                              px, py,
                              coords[0] + x, coords[1] + y);
            x += coords[0];
            y += coords[1];
            break;

        case 'A':
            for (k=0; k<coords.length; k+=7) {
                rx = coords[k+0];
                ry = coords[k+1];
                angle = coords[k+2];
                isLarge = coords[k+3];
                sweep = coords[k+4];
                x = coords[k+5];
                y = coords[k+6];
                px = py = null;
                this.importArc(ox, oy, x, y, rx, ry, angle, isLarge===1, sweep===1);
                ox = x;
                oy = y;
            }
            break;

        case 'a':
            for (k=0; k<coords.length; k+=7) {
                rx = coords[k+0];
                ry = coords[k+1];
                angle = coords[k+2];
                isLarge = coords[k+3];
                sweep = coords[k+4];
                x += coords[k+5];
                y += coords[k+6];
                px = py = null;
                this.importArc(ox, oy, x, y, rx, ry, angle, isLarge===1, sweep===1);
                ox = x;
                oy = y;
            }
            break;

        case 'Z':
        case 'z':
            x = x0;
            y = y0;
            this.importLine(ox,oy, x,y);
            ox = x;
            oy = y;
            break;
        }
        pc = cmd;
    }
};

/**
 * Computes the center of (elliptical) arc from x1/y1 to x2/y2.
 * \param rx Ellipse radius in X
 * \param ry Ellipse radius in Y
 * \param sweep Sweep flag (boolean).
 * \param isLarge Large arc flag (boolean).
 * \param angle Rotation of the allipse in rad.
 * \return Center of arc as RVector
 */
SvgImporter.getArcCenter = function(x1, y1, x2, y2, rx, ry, sweep, isLarge, angle) {
    if (Math.abs(rx)<RS.PointTolerance || Math.abs(ry)<RS.PointTolerance) {
        return RVector.invalid;
    }

    var f = -1.0;
    if (sweep === false ^ isLarge === false) {
        f = 1.0;
    }

    var dx = f * (x1 - x2);
    var dy = f * (y1 - y2);

    var sinAngle = Math.sin(angle);
    var cosAngle = Math.cos(angle);

    var dx2 = dx*cosAngle + dy*sinAngle;
    var dy2 = -dx*sinAngle + dy*cosAngle;
    dx2 = 0.5 * dx2 / rx;
    dy2 = 0.5 * dy2 / ry;

    var lambda = Math.sqrt(dx2*dx2 + dy2*dy2);
    if (lambda > 1.0) {
        return new RVector(0.5*(x1+x2), 0.5*(y1+y2));
    }

    var psi1 = -Math.atan2(dx2, dy2);
    var psi2 = Math.asin(Math.sqrt(dx2*dx2 + dy2*dy2));
    var phi1 = psi1 + f * psi2;

    dx2 = Math.cos(phi1) * rx;
    dy2 = Math.sin(phi1) * ry;

    var dx3 = dx2 * cosAngle - dy2 * sinAngle;
    var dy3 = dx2 * sinAngle + dy2 * cosAngle;

    return new RVector(x1 - dx3, y1 - dy3);
};

SvgImporter.prototype.importPolygon = function(pointsData, open) {
    var coordinates = pointsData.trim().split(/[\s,]+/).map(parseFloat);
    for (var i = 0; i < coordinates.length-1; i += 2) {
        var x1 = coordinates[i];
        var y1 = coordinates[i + 1];
        var x2 = coordinates[(i + 2) % coordinates.length];
        var y2 = coordinates[(i + 3) % coordinates.length];
        if (!open || i!==coordinates.length-2) {
            this.importLine(x1, y1, x2, y2);
        }
    }
};

/**
 * Implementation from RFileImporterAdapter.
 */
SvgImporter.prototype.canImport = function(fileName, nameFilter) {
    if (new QFileInfo(fileName).suffix().toLowerCase()==="svg") {
        return 100;
    }
    else {
        return -1;
    }
};
