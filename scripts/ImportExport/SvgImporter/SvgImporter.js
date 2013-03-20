/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("scripts/ShapeAlgorithms.js");



/**
 * SAX style XML handler.
 */
function SvgHandler(svgImporter) {
    QXmlDefaultHandler.call(this);
    this.context = "";
    this.svgImporter = svgImporter;
    this.transform = new QTransform();
    this.displayStack = [];
    this.elementStack = [];
}

SvgHandler.prototype = new QXmlDefaultHandler();

/**
 * Handle element (tag).
 */
SvgHandler.prototype.startElement = function(namespaceURI, localName, qName, atts) {
    this.elementStack.push(localName);
    this.displayStack.push(atts.value("display"));

    //qDebug("localName: ", localName);
    //qDebug("id: ", atts.value("id"));

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
        this.svgImporter.importSvgPath(atts.value("d"));
        break;

    case "polygon":
    case "polyline":
        this.svgImporter.importSvgPolygon(atts.value("points"));
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
function SvgImporter(document) {
    RFileImporterAdapter.call(this, document);
    this.setDocument(document);
}

SvgImporter.prototype = new RFileImporterAdapter();

SvgImporter.includeBasePath = includeBasePath;

SvgImporter.prototype.importFile = function(fileName) {
    if (isNull(this.getDocument())) {
        this.setDocument(EAction.getDocument());
    }

    var fi = new QFileInfo(fileName);
    //this.domDoc = this.getDomDocument(fi.absoluteFilePath());

    //if (isNull(this.domDoc)) {
    //    return false;
    //}

    var file = new QFile(fi.absoluteFilePath());
    var xmlReader = new QXmlSimpleReader();
    var source = new QXmlInputSource(file);
    var handler = new SvgHandler(this);
    xmlReader.setContentHandler(handler);
    var ok = xmlReader.parse(source, false);
    file.close();

    /*
    var i;
    
    // import paths
    var paths = this.parseSvgPaths();
    for (i = 0; i < paths.length; ++i) {
        this.importSvgPath(paths[i]);
    }

    // import lines
    var lines = this.parseSvgLines();
    for (i = 0; i < lines.length; i += 4) {
        this.importSvgLine(lines.slice(i, i + 4));
    }

    // import polygons
    var polygons = this.parseSvgPolygons();
    for (i = 0; i < polygons.length; ++i) {
        this.importSvgPolygon(polygons[i]);
    }

    // import polylines
    var polylines = this.parseSvgPolylines();
    for (i = 0; i < polylines.length; ++i) {
        this.importSvgPolyline(polylines[i]);
    }

    // import circles
    var circles = this.parseSvgCircles();
    for (i = 0; i < circles.length; i += 3) {
        this.importSvgCircle(circles.slice(i, i + 3));
    }

    // import ellipses
    var ellipses = this.parseSvgEllipses();
    for (i = 0; i < ellipses.length; i += 4) {
        this.importSvgEllipse(ellipses.slice(i, i + 4));
    }

    // import rectangles
    var rectangles = this.parseSvgRectangles();
    for (i = 0; i < rectangles.length; i += 4) {
        this.importSvgRectangle(rectangles.slice(i, i + 4));
    }
    */
    
    this.endImport();

    return true;
};

/*
SvgImporter.prototype.getDomDocument = function(fileName) {
    var dlg;

    // read and parse SVG file
    var domDoc = new QDomDocument();
    var file = new QFile(fileName);
    var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
    if (!file.open(flags)) {
        dlg = new QMessageBox(QMessageBox.Warning,
                qsTr("Insufficient permissions"),
                qsTr("Insufficient permissions to read file \n'%1'")
                    .arg(file.fileName()), QMessageBox.OK);
        dlg.exec();
        return undefined;
    }
    if (!domDoc.setContent(file)) {
        file.close();
        dlg = new QMessageBox(QMessageBox.Warning,
                qsTr("Parse Error"),
                qsTr("Cannot parse SVG file\n'%1'")
                    .arg(file.fileName()), QMessageBox.OK);
        dlg.exec();
        return undefined;
    }
    return domDoc;
};
*/

/*
SvgImporter.prototype.parseSvgLines = function() {
    return this.parseSvgElement(this.domDoc, "line", "x1", "y1", "x2", "y2");
};

SvgImporter.prototype.parseSvgCircles = function() {
    return this.parseSvgElement(this.domDoc, "circle", "cx", "cy", "r");
};

SvgImporter.prototype.parseSvgEllipses = function() {
    return this.parseSvgElement(this.domDoc, "ellipse", "cx", "cy", "rx", "ry");
};

SvgImporter.prototype.parseSvgRectangles = function() {
    return this.parseSvgElement(this.domDoc, "rect", "x", "y", "width", "height");
};

SvgImporter.prototype.parseSvgPolylines = function() {
    return this.parseSvgElement(this.domDoc, "polyline", "points");
};

SvgImporter.prototype.parseSvgPolygons = function() {
    return this.parseSvgElement(this.domDoc, "polygon", "points");
};

SvgImporter.prototype.parseSvgPaths = function() {
    return this.parseSvgElement(this.domDoc, "path", "d");
};
*/

/**
 * @param domDoc The DOM document.
 * @param elementName The element name.
 * @param array attributeName1..N The attribute names to parse. 
 * @returns {Array}
 */
 /*
SvgImporter.prototype.parseSvgElement = function() {
    if (arguments.length < 3) {
        qWarning("SvgImporter.js:",
                "parseSvgElement(): not enough arguments given");
    }
    var domDoc = arguments[0];
    if (isNull(domDoc)) {
        return [];
    }

    var elementName = arguments[1];
    var ret = new Array();
    var list = domDoc.elementsByTagName(elementName);
    for ( var i = 0; i < list.count(); ++i) {
        var n = list.at(i);
        var e = n.toElement();
        if (!e.isNull()) {
            for ( var j = 2; j < arguments.length; j++) {
                ret.push(e.attribute(arguments[j]));
            }
        }
        else {
            // one argument not found:
            return [];
        }
    }
    return ret;
};
*/

SvgImporter.prototype.importCircle = function(x, y, r) {
    var circle = new RCircle(new RVector(x, -y), r);
    var entity = new RCircleEntity(this.getDocument(), new RCircleData(circle));
    this.importObject(entity);
};

SvgImporter.prototype.importEllipse = function(x, y, rx, ry) {
    var ellipse = new REllipse(new RVector(x, -y), new RVector(rx, 0), ry/rx, 0.0, 2*Math.PI, false);
    var entity = new REllipseEntity(this.getDocument(), new REllipseData(ellipse));
    this.importObject(entity);
};

SvgImporter.prototype.importRectangle = function(x, y, w, h) {
    var line = new RLine(new RVector(x, -y), new RVector(x+w, -y));
    var entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
    line = new RLine(new RVector(x+w, -y), new RVector(x+w, -y-h));
    entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
    line = new RLine(new RVector(x+w, -y-h), new RVector(x, -y-h));
    entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
    line = new RLine(new RVector(x, -y-h), new RVector(x, -y));
    entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
};

SvgImporter.prototype.importLine = function(x1, y1, x2, y2) {
    var line = new RLine(new RVector(x1, -y1), new RVector(x2, -y2));
    var entity = new RLineEntity(this.getDocument(), new RLineData(line));
    this.importObject(entity);
};

SvgImporter.prototype.importArc = function(ox, oy, x, y, rx, ry, angle, isLarge, sweep) {
    var entity;
    var center = SvgImporter.getArcCenter(ox, -oy, x, -y, rx, ry, sweep, !isLarge, angle);
    if (Math.abs(rx-ry) < RS.PointTolerance) {
        var arc = new RArc(center, rx, center.getAngleTo(new RVector(ox, -oy)), center.getAngleTo(new RVector(x, -y)), sweep);
        entity = new RArcEntity(this.getDocument(), new RArcData(arc));
        this.importObject(entity);
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
    spline.appendControlPoint(new RVector(x1, -y1));
    spline.appendControlPoint(new RVector(px1, -py1));
    spline.appendControlPoint(new RVector(px2, -py2));
    spline.appendControlPoint(new RVector(x2, -y2));

    var entity = undefined;

    var shape = ShapeAlgorithms.splineToLineOrArc(spline, 0.1);
    if (isLineShape(shape)) {
        // spline resembles a line:
        entity = new RLineEntity(this.getDocument(), new RLineData(shape));
    }
    else if (isArcShape(shape)) {
        // spline resembles an arc:
        entity = new RArcEntity(this.getDocument(), new RArcData(shape));
    }
    else {
        // spline is a normal spline:
        entity = new RSplineEntity(this.getDocument(), new RSplineData(spline));
    }

    this.importObject(entity);
};

SvgImporter.prototype.importBezier2 = function(x1, y1, px, py, x2, y2) {
    var spline = new RSpline();
    spline.setDegree(2);
    spline.appendControlPoint(new RVector(x1, -y1));
    spline.appendControlPoint(new RVector(px, -py));
    spline.appendControlPoint(new RVector(x2, -y2));
    var entity = new RSplineEntity(this.getDocument(), new RSplineData(spline));
    this.importObject(entity);
};

/**
 * Parses the given path data string and imports the lines, arcs and splines
 * from the path.
 */
SvgImporter.prototype.importSvgPath = function(dData) {
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

  var f = 1.0;
  if (sweep === false ^ isLarge === false) {
      f = -1.0;
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

/*
SvgImporter.prototype.importSvgLine = function(svgLine) {
    var x1 = parseFloat(svgLine[0]);
    var y1 = parseFloat(svgLine[1]);
    var x2 = parseFloat(svgLine[2]);
    var y2 = parseFloat(svgLine[3]);
    this.importLine(x1, y1, x2, y2);
};

SvgImporter.prototype.importSvgCircle = function(svgCircle) {
    var x = parseFloat(svgCircle[0]);
    var y = parseFloat(svgCircle[1]);
    var r = parseFloat(svgCircle[2]);
    this.importCircle(x, y, r);
};

SvgImporter.prototype.importSvgEllipse = function(svgEllipse) {
    var x = parseFloat(svgEllipse[0]);
    var y = parseFloat(svgEllipse[1]);
    var rx = parseFloat(svgEllipse[2]);
    var ry = parseFloat(svgEllipse[3]);
    this.importEllipse(x, y, rx, ry);
};

SvgImporter.prototype.importSvgRectangle = function(svgRectangle) {
    var x = parseFloat(svgRectangle[0]);
    var y = parseFloat(svgRectangle[1]);
    var width = parseFloat(svgRectangle[2]);
    var height = parseFloat(svgRectangle[3]);
    this.importRectangle(x, y, width, height);
};

SvgImporter.prototype.importSvgPolyline = function(svgPolyline) {
    this.importSvgPolygon(svgPolyline);
};
*/

SvgImporter.prototype.importSvgPolygon = function(pointsData) {
    var coordinates = pointsData.trim().split(/[\s,]+/).map(parseFloat);
    for (var i = 0; i < coordinates.length-1; i += 2) {
        var x1 = coordinates[i];
        var y1 = coordinates[i + 1];
        var x2 = coordinates[(i + 2) % coordinates.length];
        var y2 = coordinates[(i + 3) % coordinates.length];
        this.importLine(x1, y1, x2, y2);
    }
};

/**
 * Implementation from RFileImporterAdapter.
 */
SvgImporter.prototype.canImport = function(fileName, nameFilter) {
    if (new QFileInfo(fileName).suffix().toLowerCase()==="svg") {
        return true;
    }
    else {
        return false;
    }
};
