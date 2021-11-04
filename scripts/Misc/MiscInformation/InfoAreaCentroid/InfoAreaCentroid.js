/**
 * InfoAreaCentroid Beta version 0.11 (As MiscMathExamples)
 * Copyright (c) 2021 by CVH.
 * All rights reserved.
 *
 * This file is a free extension of the QCAD project.
 * Permission to evaluate, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * This script is donated to the QCAD project.
 * Copyright (c) 2011-2020 by Andrew Mustun. All rights reserved.
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

// # Oddity Fixed # Misc|Information actions are based on EAction.js
include("scripts/EAction.js");

/**
 * \class InfoAreaCentroid
 * \ingroup ecma_misc_information
 * \brief This action adds centroid markers and details to selections.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoAreaCentroid(guiAction) {
    EAction.call(this, guiAction);
};

// Deriving our class from the base class:
InfoAreaCentroid.prototype = new EAction();
InfoAreaCentroid.includeBasePath = includeBasePath;

/**
 * This GUI action adds a centroid marker and details for a selected entity.
 * Calculates centroid position and enclosed area assuming a uniform density surface.
 * Casts additional details as text labels and reports them on the Command History.
 * Supports selected enclosed area of:
 *    - Arc entity as an arc segment.
 *    - Circle entity as circle.
 *    - Ellipse entity, full or approximated & autoClosed with a line.
 *    - Polyline entity, autoClosed with a line.
 *    - Spline entity approximated & autoClosed with a line.
 * Supports Hatch entity total/differential hatched area.
 * Not interpolating with line segments, the methods sum area and centroid by shape.
 *
 * Included are various functions for area , centroid and centroid as a uniform wire.
 */

// BeginEvent handler:
InfoAreaCentroid.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.sectorMode = false;
    this.selectionAreaCentroid(this.getDocumentInterface());

    // Terminate beginEvent:
    this.terminate();
    return;
};

/**
 * Main InfoAreaCentroid loop.
 * \author CVH © 2021
 *
 * \param di         A document interface.
 *
 * \return Nothing.
 */
InfoAreaCentroid.prototype.selectionAreaCentroid = function(di) {
    var doc = di.getDocument();
    var ids, idn;
    var msg;
    var entity
    var type;
    var res;
    var area, txt;
    var op;
    var docDimSize, docDimScale;
    var shift;
    var markerSize;
    var offset;

    // Retrieve document selection, fail on none or many:
    ids = doc.querySelectedEntities();
    idn = ids.length;
    if (idn === 0) {
        EAction.handleUserWarning(qsTr("No selection."));
        EAction.handleUserInfo(qsTr("Please, make a selection first. Command terminated."));
        return undefined;
    }
    else if (idn > 1) {
        // Excluding there:
        // - open shapes can be treated as a wire or as an enclosed area
        // - uniform density areas can't be summed to uniform wire lengths
        EAction.handleUserWarning(qsTr("Multiple selection."));
        EAction.handleUserInfo(qsTr("Not implemented. Command terminated."));
        return undefined;
    }

    // Additional Command History script notification:
    EAction.handleUserMessage(qsTr("Centroid & area script by CVH"));

    // Initial values:
    this.hasApprox = false;
    this.isSingleLoop = true;
    this.isDifferential = false;
    this.markDiv = 0;
    msg = qsTr("Enclosed area:");

    // Retrieve the single selected entity:
    entity = doc.queryEntityDirect(ids[0]);    // Direct, no changes are applied to the entity

//debugger;
    // Diversify on type, if supported:
    type = this.getSupportedAreaCentroidType(entity);
    // Returns supported entity type or -1

    switch (type) {
        case 1:    // isArcEntity
            res = this.getArcAreaCentroid(entity); // Diversifies
            break;
        case 2:    // isCircleEntity
            res = this.getCircleAreaCentroid(entity);
            break;
        case 3:    // isEllipseEntity
            // # Informational # Remark that QCAD doesn't handle majorR or minorR equal to zero
            res = this.getEllipseAreaCentroid(entity); // Diversifies
            if (this.hasApprox === true) {
                msg = qsTr("Approximated enclosed area:");
            }
            // Additional ellipse arc closed format result:
            area = this.getEllipseArea(entity);
            if (!isFullEllipseEntity(entity)) {
                if (this.sectorMode) {
                    txt = qsTr("Ellipse arc sector area (closed format): %1").arg(area.toPrecision(17));
                } 
                else {
                    txt = qsTr("Ellipse arc segment area (closed format): %1").arg(area.toPrecision(17));
                }
            }
            EAction.handleUserMessage(txt);
            break;
        case 4:    // isPolylineEntity
            res = this.getPolylineAreaCentroid(entity);
            break;
        case 5:    // isSplineEntity
            res = this.getSplineAreaCentroid(entity);
            msg = qsTr("Approximated enclosed area:");
            break;
        case 6:    // isHatchEntity
            res = this.getHatchedAreaCentroid(entity);
            msg = qsTr("Hatched area:")
            if (!this.isSingleLoop) msg = qsTr("Total hatched area:");
            if (this.isDifferential) msg = qsTr("Differential hatched area:");
            break;
        default:    // isUnsupported
            EAction.handleUserWarning(qsTr("Unsupported entity type."));
            return undefined;
            break;
    } // End switch type

    // Fail without results:
    if (isNull(res)) {
        EAction.handleUserWarning(qsTr("No results."));
        return undefined;
    }

//debugger;
    // Initiate an operation:
    op = new RAddObjectOperation();
    // Set tool title used for undo/redo information:
    op.setText(qsTr("Centroid point"));

    // Retrieve preferences & document variables:
    this.infoColor = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));
    this.docDimFont = doc.getDimensionFont();     // # Issue # Returns 'TXT' when file is saved with 'standard'
    docDimSize = doc.getKnownVariable(RS.DIMTXT, 2.5);    // Default =2.5
    docDimScale = doc.getKnownVariable(RS.DIMSCALE, 1.0);    // Default =1.0
    this.fontSize = docDimSize * docDimScale;

// # Issue fixed # Font-FIX
// Revert to the standard font when is empty or 'TXT':
if (!this.docDimFont.isEmpty() && this.docDimFont.toUpperCase() === "TXT") this.docDimFont = "standard";

    // Revert to the standard font without a document font:
    if (this.docDimFont.isEmpty()) this.docDimFont = "standard";
    // Assure for a font size equal or larger than 0.03 (See marker fix):
    if (this.fontSize < 0.03) this.fontSize = 0.03;
    shift = this.fontSize / 2;

    // Include centroid marker:
    markerSize = this.getMarkerSize(entity);
    this.addCentroidMarker(doc, op, res[2], markerSize)

    // Include area value:
    msg += " " + Math.abs(res[3]).toPrecision(17);
    if (type === 6 && this.hasApprox) msg += " " + qsTr("(Incl. approximations)")
    offset = new RVector(markerSize + shift, markerSize + shift);
    this.addTextLabel(doc, op, res[2], offset, msg);
    EAction.handleUserInfo(msg);

    // Include centroid position:
    msg = (this.hasApprox) ? qsTr("Approximated centroid:") : qsTr("Centroid:");
    msg += " (" + res[0].toPrecision(17);
    msg += ", " + res[1].toPrecision(17);
    msg += ")"
    offset = new RVector(markerSize + shift, shift - markerSize);
    this.addTextLabel(doc, op, res[2], offset, msg);
    EAction.handleUserInfo(msg);

    // Apply all operations & set relative center:

    di.setRelativeZero(res[2]);
    di.applyOperation(op);
    // Return to terminate:
    return;
};

// -------------
// Area methods
// -------------
// Hatch entities
/** OK ifso by approx
 * Hatched differential area of a hatch entity (+).
 * Ifso approximated with polylines given the XP method settings.
 * \author CVH © 2021
 *
 * \param entity         A hatch REntity.
 *
 * \return The differential area (+) or 'undefined'.
 */
InfoAreaCentroid.prototype.getHatchedArea = function(entity) {
    var boundaries, boundary;
    var i, iMax;
    var area;
    var dArea = 0;

    // Fail without a hatch entity:
    if (!isHatchEntity(entity)) return undefined;

//debugger;
    // Pre-orient hatch boundaries for differential sign:
    boundaries = this.getOrientedHatchBoundaries(entity);
    // Returns at least one pre-oriented boundary or 'undefined'

   // Fail without boundaries:
    if (isNull(boundaries)) return undefined;
    iMax = boundaries.length;

    // Process all pre-oriented hatch boundaries:
    for (i=0; i<iMax; i++) {    // Cycle all boundaries
        boundary = boundaries[i];
        area = this.getPolylineArea(boundary); // RPolylineEntity & RPolyline
        // Returns signed area or 'undefined'

        // Sum to total, if any:
        if (!isNull(area)) {
            dArea += area;
        }
    } // Loop boundaries

    // Return differential area:
    return dArea;
};

// Spline items
/** OK by approx
 * Spline enclosed signed area (+CCW, -CW).
 * Approximated with an auto closed polyline given XP method tolerance.
 * Incorrect for self-intersecting shapes.
 * # Issue # No good test on self-intersecting bulging polylines.
 * \author CVH © 2021
 *
 * \param spline         A spline RShape or REntity.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getSplineArea = function(spline) {
    var length;
    var sTol;
    var approx;

    // Functional for RSplineEntity & RSplineData & RSpline
    // Fail without a spline entity or a spline shape:
    if (!isSplineEntity(spline) && !isSplineShape(spline)) return undefined;

    // Avoid Null-length:
    length = spline.getLength(); // RSplineEntity & RSplineData & RSpline
    if (!isNumberGreaterZero(length)) {
        return 0.0;
    }

//debugger;
    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    sTol = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);    // Default =0.01 deviation

    // Approximate the spline with a polyline and autoClose with a line segment:
    approx = spline.approximateWithArcs(sTol); // RSplineEntity & RSplineData & RSpline
    approx.autoClose(RS.PointTolerance); // RPolylineEntity & RPolylineData & RPolyline
    if (!approx.isClosed()) approx.setClosed(true);
    this.hasApprox = true;

    // Return the approximated polyline area:
    return this.getPolylineArea(approx);
};

// Polyline items
/** OK
 * Polyline enclosed signed area (+CCW, -CW).
 * Auto closed with line segment.
 * Incorrect for self-intersecting shapes.
 * # Issue # No good test on self-intersecting bulging polylines.
 * \author CVH © 2021
 *
 * \param polyline         A polyline RShape or REntity.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolylineArea = function(polyline) {
    var poly;
    var orgLength;
    var polygonArea
    var shapes;
    var i, iMax;
    var bulgeArea;
    var bulgesArea;

    // Functional for RPolylineEntity & RPolyline
    // Fail without a polyline shape, possible from an RPolylineEntity:
    if (isPolylineEntity(polyline)) {    // REntity based (Excludes RSolids and so)
        poly = polyline.castToShape().clone();
    }
    else {
        poly = polyline;
    }
    if (!isPolylineShape(poly)) return undefined;    // Failed

    // Avoid Null-length:
    orgLength = poly.getLength(); // RPolylineEntity & RPolyline
    if (!isNumberGreaterZero(orgLength)) {
        return 0.0;
    }

    // Explicit logical closed:
    poly.autoClose(RS.PointTolerance); // RPolylineEntity & RPolylineData & RPolyline
    if (!poly.isClosed()) poly.setClosed(true);

//debugger;
    // Calculate the polygon signed area:
    polygonArea = this.getPolygonArea(poly); // RPolylineEntity & RPolylineData & RPolyline
    // Returns signed area or 'undefined'

    // Fail without signed area:
    if (isNull(polygonArea)) return undefined;

    // Calculate the bulges total signed area, if any:
    bulgesArea = 0
    if (poly.hasArcSegments()) { // RPolylineEntity & RPolyline
        shapes = poly.getExploded(); // RPolylineEntity & RPolylineData & RPolyline
        iMax = shapes.length;
        for (i=0; i<iMax; i++) {    // Cycle all polyline segments
            if (isArcShape(shapes[i])) {
                bulgeArea = this.getArcSegmentArea(shapes[i]); // RArcEntity & RArcData & RArc
                // Returns signed area or 'undefined'

                // Sum to total, if any:
                if (!isNull(bulgeArea)) {
                    bulgesArea += bulgeArea;
                }
            }
        } // Loop segments

        // Return polyline total signed area:
         return polygonArea + bulgesArea;
    }
    else {
        // Return polygon signed area:
         return polygonArea;
    }
};

// Polyline items with line segments
/** OK
 * Polygon enclosed signed area (+CCW, -CW).
 * Auto closed with line segment, elides bulge factors.
 * Rejects self-intersecting polygons.
 * \author CVH © 2021
 *
 * \param polygon         A polyline RShape or REntity.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolygonArea = function(polygon) {
    var poly;
    var orgLength;
    var ips;
    var pts, npts;
    var j, i;
    var p1, p2;
    var area = 0;

    // Functional for RPolylineData & RPolyline
    // Fail without a polyline shape, possible from an RPolylineEntity:
    if (isPolylineEntity(polygon)) {    // REntity based (Excludes RSolids and so)
        poly = polygon.castToShape().clone();
    }
    else {
        poly = polygon;
    }
    if (!isPolylineShape(poly)) return undefined;    // Failed

    // Avoid Null-length:
    orgLength = poly.getLength(); // RPolylineEntity & RPolyline
    if (!isNumberGreaterZero(orgLength)) {
        return 0.0;
    }

    // Explicit logical closed:
    poly.autoClose(RS.PointTolerance); // RPolylineEntity & RPolylineData & RPolyline
    if (!poly.isClosed()) poly.setClosed(true);

//debugger;
    // Reject self-intersecting polygons:
    if (!poly.hasArcSegments()) { // RPolylineEntity & RPolyline
        ips = poly.getSelfIntersectionPoints(RS.PointTolerance);
        // Returns a single intersection point where segments are crossing,
        // 4 equal intersection points where nodes coexists
        // # Issue # Odd extra node as intersection point when node is on other segment,
        // unrelated to CW/CCW or tolerance
//        if (ips.length > 0) debugger;    // ### Catch this In the act !!! ###
        if (ips.length > 0) return undefined;    // Failed
    }

    // Process all nodes (Shoelace algorithm):
    pts = poly.getVertices(); // RPolylineData & RPolyline
    nPts = pts.length;
    j = nPts - 1;
    for (i=0; i<nPts; j=i++) {    // Cycle all nodes
        p1 = pts[j];
        p2 = pts[i];
        area += p1.x * p2.y;
        area -= p2.x * p1.y;
    } // Loop nodes

    // Return polygon signed area:
    return area / 2;
};

// Circular items excluding circles
/** Diversifies
 * Arc enclosed signed area (+CCW, -CW).
 * Diversifies between an arc segment or an arc sector.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape or REntity.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcArea = function(arc) {
    // Fail without an arc entity or an arc shape:
    if (!isArcEntity(arc) && !isArcShape(arc)) return undefined;

    // Diversify return area on the arc mode:
    if (!isNull(this.sectorMode) && this.sectorMode === true) {
        return this.getArcSectorArea(arc);
    }
    else {
        return this.getArcSegmentArea(arc);
    }
};

/** OK
 * Arc segment enclosed signed area (+CCW, -CW).
 * Not to be confused with a simple arc shape.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape or REntity.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSegmentArea = function(arc) {
    var radius, sweep;
    var area;

    // Functional for RArcEntity & RArc even for Null-length
    // Fail without an arc entity or an arc shape:
    if (!isArcEntity(arc) && !isArcShape(arc)) return undefined;

    radius = arc.getRadius(); // RArcEntity & RArcData & RArc
    sweep = arc.getSweep(); // RArcEntity & RArc

    // Define area, ifso or over revert to full arc:
    if (Math.abs(sweep) >= 2*Math.PI) {
        area = radius*radius * Math.PI;    // Unsigned area
        area *= (sweep > 0) ? 1 : -1;
    }
    else {
        area = radius*radius / 2 * (sweep - Math.sin(sweep));    // Signed area
    }

    // Return arc segment signed area:
    return area;
};

/** OK
 * Arc sector enclosed signed area (+CCW, -CW).
 * \author CVH © 2021
 *
 * \param arc         An arc RShape or REntity.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSectorArea = function(arc) {
    var radius, sweep;
    var area;

    // Functional for RArcEntity & RArc even for Null-length
    // Fail without an arc entity or an arc shape:
    if (!isArcEntity(arc) && !isArcShape(arc)) return undefined;

    radius = arc.getRadius(); // RArcEntity & RArcData & RArc
    sweep = arc.getSweep(); // RArcEntity & RArc

    // Define area, ifso or over revert to full arc:
    if (Math.abs(sweep) >= 2*Math.PI) {
        area = radius*radius * Math.PI;    // Unsigned area
        area *= (sweep > 0) ? 1 : -1;
    }
    else {
        area = radius*radius * sweep / 2;    // Signed area
    }

    // Return arc sector signed area:
    return area;
};

// Ellipse items
/** Diversifies
 * Ellipse enclosed (signed) area.
 * Diversifies between a full ellipse (+) or an ellipse arc segment or sector (+CCW, -CW).
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse RShape or REntity.
 *
 * \return Unsigned or signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArea = function(ellipse) {
    // Functional for REllipseEntity & REllipse
    // Fail without an ellipse entity or an ellipse shape:
    if (!isEllipseEntity(ellipse) && !isEllipseShape(ellipse)) return undefined;

    // Diversify return area on the closed nature:
    if (ellipse.isFullEllipse()) {
        return this.getFullEllipseArea(ellipse);
    }
    else {
        // Diversify return area on the arc mode:
        if (!isNull(this.sectorMode) && this.sectorMode) {
            return this.getEllipseArcSectorArea(ellipse);
        }
        else {
            return this.getEllipseArcSegmentArea(ellipse);
        }
    }
};

/** OK
 * Full ellipse enclosed area (+).
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         A full ellipse RShape or REntity.
 *
 * \return Unsigned area or 'undefined'.
 */
InfoAreaCentroid.prototype.getFullEllipseArea = function(ellipse) {
    var major, minor;
    var area;

    // Functional for REllipseEntity & REllipse even for Null-length
    // Fail without a full ellipse entity or a full ellipse shape:
    if (!isFullEllipseEntity(ellipse) && !isFullEllipseShape(ellipse)) return undefined;

    major = ellipse.getMajorRadius(); // REllipseEntity & REllipseData & REllipse
    minor = ellipse.getMinorRadius(); // REllipseEntity & REllipse
    area = major * minor * Math.PI;    // Unsigned area

    // Return full ellipse area:
    return area;
};

/** OK
 * Ellipse arc segment enclosed signed area (+CCW, -CW).
 * Not to be confused with a simple ellipse arc shape.
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape or REntity.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSegmentArea = function(ellipse) {
    var major, minor;
    var sweep;
    var area;

    // Functional for REllipseEntity & REllipse even for Null-length
    // Fail without an ellipse arc entity or an ellipse arc shape:
    if (!(isEllipseEntity(ellipse) && !ellipse.isFullEllipse()) && !isEllipseArcShape(ellipse)) return undefined;

    major = ellipse.getMajorRadius(); // REllipseEntity & REllipseData & REllipse
    minor = ellipse.getMinorRadius(); // REllipseEntity & REllipse
    sweep = ellipse.getSweep(); // REllipseEntity & REllipseData & REllipse

    // Define area, ifso or over revert to full arc:
    if (Math.abs(sweep) >= 2*Math.PI) {
        area = major * minor * Math.PI;    // Unsigned area
        area *= (sweep > 0) ? 1 : -1;
    }
    else {
        area = major * minor / 2 * (sweep - Math.sin(sweep));    // signed area
    }

    // Return ellipse arc segment signed area:
    return area;
};

/** OK
 * Ellipse arc sector enclosed signed area (+CCW, -CW).
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape or REntity.
 *
 * \return Area or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSectorArea = function(ellipse) {
    var major, minor;
    var halfSweep;
    var area;

    // Functional for REllipseEntity & REllipse even for Null-length
    // Fail without an ellipse arc entity or an ellipse arc shape:
    if (!(isEllipseEntity(ellipse) && !ellipse.isFullEllipse()) && !isEllipseArcShape(ellipse)) return undefined;

    major = ellipse.getMajorRadius(); // REllipseEntity & REllipseData & REllipse
    minor = ellipse.getMinorRadius(); // REllipseEntity & REllipse
    halfSweep = ellipse.getSweep() / 2; // REllipseEntity & REllipseData & REllipse

    // Define area, ifso or over revert to full arc:
    if (Math.abs(halfSweep) >= Math.PI) {
        area = major * minor * Math.PI;    // Unsigned area
        area *= (sweep > 0) ? 1 : -1;
    }
    else {
        area = major * minor * halfSweep;    // signed area
    }

    // Return ellipse arc sector signed area:
    return area;
};

// --------------------------------------------------
// Area centroid methods for a uniform density in 2D
// --------------------------------------------------
// Hatch entities
/** OK ifso by approx
 * Hatched centroid data of a hatch entity, including the differential hatched area (+).
 * Considering a uniform density in 2D.
 * Ifso approximated with polylines given the XP method settings.
 * \author CVH © 2021
 *
 * \param entity         A hatch REntity.
 *
 * \return [centroid.x, centroid.y, centroid, differential area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getHatchedAreaCentroid = function(entity) {
    var boundaries;
    var i, iMax;
    var boundary;
    var length;
    var polyC;
    var dX = 0;
    var dY = 0;
    var dArea = 0;
    var count = 0;
    var centroid;

    // Fail without a hatch entity:
    if (!isHatchEntity(entity)) return undefined;

//debugger;
    // Pre-orient hatch boundaries for differential sign:
    boundaries = this.getOrientedHatchBoundaries(entity);
    // Returns at least one pre-oriented boundary or 'undefined'

    // Fail without boundaries:
    if (isNull(boundaries)) return undefined;
    iMax = boundaries.length;

    // Process all pre-oriented hatch boundary loops:
    for (i=0; i<iMax; i++) {    // Cycle all boundary loops
        boundary = boundaries[i];

        polyC = this.getPolylineAreaCentroid(boundary); // RPolylineEntity & RPolyline
        // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

        // Sum to total, if any:
        if (!isNull(polyC)) {
            dX += polyC[0] * polyC[3];
            dY += polyC[1] * polyC[3];
            dArea += polyC[3];
            count++;
        }
    } // Loop boundaries

    // Avoid and fail when dividing by a zero area:
    if (dArea === 0.0) return undefined;

    // Hatch statistics:
    if (count > 1) this.isSingleLoop = false;

    // Create differential centroid vector:
    centroid = new RVector(dX / dArea, dY / dArea);

    // Return hatch centroid data:
    return [centroid.x, centroid.y, centroid, dArea];
};

// Contour items
/** NOK
 * Contours of connected items centroid data, including the total enclosed area (+).
 * Considering a uniform density in 2D.
 * As merged polylines, ifso approximated with polylines given the XP method settings.
 * Incorrect for nested or self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param loops         Collections of multiple RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, total area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getContoursAreaCentroid = function(loops) {
    // # ToDo # Contours of connected shapes or entities, ifso by approx
    // Verify isNotIntersecting isNotNested
    // Loops InfoAreaCentroid.prototype.getContourAreaCentroid()
    return undefined;
};

/** NOK
 * A single contour of connected items centroid data, including the total enclosed area (+).
 * Considering a uniform density in 2D.
 * As merged polyline, ifso approximated with polylines given the XP method settings.
 * Incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param items         A collection of multiple RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, total area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getContourAreaCentroid = function(items) {
    // # ToDo # Contour of connected items, ifso by approx
    // Verify isConnected
    // Merge chain of connected RShapes to polyline
    // .getPolylineAreaCentroid(poly)
    return undefined;
}

// Spline items
/** OK by approx
 * Spline centroid data, including enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Approximated with an auto closed polyline given XP method tolerance.
 * Incorrect for self-intersecting shapes.
 * # Issue # No good test on self-intersecting bulging polylines.
 * \author CVH © 2021
 *
 * \param spline         A polyline RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getSplineAreaCentroid = function(spline) {
    var length, start;
    var sTol;
    var approx;

    // Functional for RSplineEntity & RSplineData & RSpline
    // Fail without a spline entity or a spline shape:
    if (!isSplineEntity(spline) && !isSplineShape(spline)) return undefined;

    // Avoid Null-length:
    length = spline.getLength(); // RSplineEntity & RSplineData & RSpline
    if (!isNumberGreaterZero(length)) {
        start = spline.getStartPoint(); // RSplineEntity & RSplineData & RSpline
        return [start.x, start.y, start, 0.0];
    }

//debugger;
    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    sTol = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);    // Default =0.01 deviation

    // Approximate the spline with a polyline and autoClose with a line segment:
    approx = spline.approximateWithArcs(sTol); // RSplineEntity & RSplineData & RSpline
    approx.autoClose(RS.PointTolerance); // RPolylineEntity & RPolylineData & RPolyline
    if (!approx.isClosed()) approx.setClosed(true);
    this.hasApprox = true;

    // Return the approximated polyline centroid data:
    return this.getPolylineAreaCentroid(approx);
};

// Polyline items
/** OK
 * Polyline centroid data, including enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Auto closed with line segment.
 * Incorrect for self-intersecting shapes.
 * # Issue # No good test on self-intersecting bulging polylines.
 * \author CVH © 2021
 *
 * \param polyline         A polyline RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolylineAreaCentroid = function(polyline) {
// Also see empty InfoArcCircleArea.prototype.getCenter()
// Was: InfoPolylineArea.prototype.getCenter() but needed correction
// Was: InfoArea.prototype.getCenter() but needed correction
// https://qcad.org/rsforum/viewtopic.php?f=32&p=35084#p35080
    var poly;
    var orgLength, start;
    var polyC;
    var x, y, area;
    var shapes;
    var i, iMax;
    var bulgeC;
    var centroid;

    // Functional for RPolylineEntity & RPolyline
    // Fail without a polyline shape, possible from an RPolylineEntity:
    if (isPolylineEntity(polyline)) {    // REntity based (Excludes RSolids and so)
        poly = polyline.castToShape().clone();
    }
    else {
        poly = polyline;
    }
    if (!isPolylineShape(poly)) return undefined;    // Failed

    // Avoid Null-length:
    orgLength = poly.getLength(); // RPolylineEntity & RPolyline
    if (!isNumberGreaterZero(orgLength)) {
        start = poly.getStartPoint(); // RPolylineEntity & RPolylineData & RPolyline
        return [start.x, start.y, start, 0.0];
    }

    // Explicit logical closed:
    poly.autoClose(RS.PointTolerance); // RPolylineEntity & RPolylineData & RPolyline
    if (!poly.isClosed()) poly.setClosed(true);

//debugger;
    // Get polygon centroid & signed area:
    polyC = this.getPolygonAreaCentroid(poly); // RPolylineEntity & RPolylineData & RPolyline
    // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

    // Fail without polygon data:
    if (isNull(polyC)) return undefined;

    // Initiate with polygon centroid:
    x = polyC[0] * polyC[3];
    y = polyC[1] * polyC[3];
    area = polyC[3];

    // Add bulging centroids & signed areas, if any:
    if (poly.hasArcSegments()) { // RPolylineEntity & RPolyline
        shapes = poly.getExploded(); // RPolylineEntity & RPolylineData & RPolyline
        iMax = shapes.length;
        for (i=0; i<iMax; i++) {    // Cycle all polyline segments
            if (isArcShape(shapes[i])) {
                bulgeC = this.getArcSegmentAreaCentroid(shapes[i]); // RArcEntity & RArcData & RArc
                // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

                // Sum to total, if any:
                if (!isNull(bulgeC)) {
                    x += bulgeC[0] * bulgeC[3];
                    y += bulgeC[1] * bulgeC[3];
                    area += bulgeC[3];
                }
            }
        } // Loop segments

        // Avoid and fail when dividing by a zero area:
        if (area === 0.0) return undefined;

        // Create overall centroid vector:
        centroid = new RVector(x / area, y / area);
    }
    else {
        // Use polygon centroid vector:
        centroid = polyC[2];
    }

    // Return polyline centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

// Polylines items with line segments
/** OK
 * Polygon centroid data, including enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Auto closed with line segment, elides bulge factors.
 * Rejects self-intersecting polygons.
 * \author CVH © 2021
 *
 * \param polygon         A polyline RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolygonAreaCentroid = function(polygon) {
    var poly;
    var orgLength, start;
    var ips;
    var pts, npts;
    var j, i;
    var p1, p2;
    var f;
    var x = 0;
    var y = 0;
    var area = 0;
    var centroid;

    // Functional for RPolylineEntity & RPolyline
    // Fail without a polyline shape, possible from an RPolylineEntity:
    if (isPolylineEntity(polygon)) {    // REntity based (Excludes RSolids and so)
        poly = polygon.castToShape().clone();
    }
    else {
        poly = polygon;
    }
    if (!isPolylineShape(poly)) return undefined;    // Failed

    // Avoid Null-length:
    orgLength = poly.getLength(); // RPolylineEntity & RPolyline
    if (!isNumberGreaterZero(orgLength)) {
        start = poly.getStartPoint(); // RPolylineEntity & RPolylineData & RPolyline
        return [start.x, start.y, start, 0.0];
    }

    // Explicit logical closed:
    poly.autoClose(RS.PointTolerance); // RPolylineEntity & RPolylineData & RPolyline
    if (!poly.isClosed()) poly.setClosed(true);

//debugger;
    // Reject self-intersecting polygons:
    if (!poly.hasArcSegments()) { // RPolylineEntity & RPolyline
        ips = poly.getSelfIntersectionPoints(RS.PointTolerance);
        // Returns a single intersection point where segments are crossing,
        // 4 equal intersection points where nodes coexists
        // # Issue # Odd extra node as intersection point when node is on other segment,
        // unrelated to CW/CCW or tolerance
//        if (ips.length > 0) debugger;    // ### Catch this In the act !!! ###
        if (ips.length > 0) return undefined;    // Failed
    }

    // Process all nodes (Shoelace algorithm):
    pts = poly.getVertices(); // RPolylineData & RPolyline
    nPts = pts.length;
    j = nPts - 1;
    for (i=0; i<nPts; j=i++) {    // Cycle all nodes
        p1 = pts[j];
        p2 = pts[i];
        f = p1.x * p2.y - p2.x * p1.y;
        area += f;    // Summing signed areas
        x += (p1.x + p2.x) * f;
        y += (p1.y + p2.y) * f;
    } // Loop nodes
    f = area * 3;

    // Avoid dividing by a zero area factor:
    if (f === 0.0) {
        // Diversify specific vector on number of points:
        switch (nPts) {
            case 0:
                centroid = RVector.nullVector;
                break;
            case 1:
                centroid = pts[0];
                break;
            case 2:
                centroid = RVector.getAverage(pts[0], pts[1]);
                break;
            default:
                centroid = RVector.getAverage(pts);
                break;
        }
    }
    else {
        // Create overall centroid vector:
        centroid = new RVector(x / f, y / f);
    }

    // Return polygon centroid data:
    return [centroid.x, centroid.y, centroid, area / 2];
};

// Circular items
/** Diversifies
 * Arc centroid data, including signed area (+CCW, -CW).
 * Diversifies between an arc segment or an arc sector.
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcAreaCentroid = function(arc) {
    // Functional for RArcEntity & RArc even for Null-length
    // Fail without an arc entity or an arc shape:
    if (!isArcEntity(arc) && !isArcShape(arc)) return undefined;

    // Diversify return area on the arc mode:
    if (!isNull(this.sectorMode) && this.sectorMode) {
        return this.getArcSectorAreaCentroid(arc);
    }
    else {
        return this.getArcSegmentAreaCentroid(arc);
    }
};

/** OK
 * Arc segment centroid data, including signed area (+CCW, -CW).
 * Not to be confused with a simple arc shape.
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSegmentAreaCentroid = function(arc) {
    var radius, sweep;
    var factor;
    var area;
    var magnitude;
    var centerPoint, midPoint;
    var centroidVector, centroid;

    // Functional for RArcEntity & RArc
    // Fail without an arc entity or an arc shape:
    if (!isArcEntity(arc) && !isArcShape(arc)) return undefined;

    radius = arc.getRadius(); // RArcEntity & RArcData & RArc
    sweep = arc.getSweep(); // RArcEntity & RArc
    centerPoint = arc.getCenter(); // RArcEntity & RArcData & RArc

    // Ifso or over revert to full arc:
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return circle centroid data:
        return [centroid.x, centroid.y, centroid, radius*radius * Math.PI];
    }

    // Avoid division by zero factor:
    if (sweep === 0.0) {
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // Define factor & signed area:
    factor = sweep - Math.sin(sweep);
    area = radius*radius * factor / 2;

    // Define centroid magnitude:
    magnitude = 4 * radius * Math.pow(Math.sin(Math.abs(sweep) / 2), 3) / 3 / Math.abs(factor);

    // Create centroid vector:
    midPoint = arc.getMiddlePoint(); // RArcEntity & RArcData & RArc
    centroidVector = midPoint.operator_subtract(centerPoint);
    centroidVector.setMagnitude2D(magnitude);
    centroid = centerPoint.operator_add(centroidVector);

    // Return arc segment centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

/** OK
 * Arc sector centroid data, including signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSectorAreaCentroid = function(arc) {
    var radius, halfSweep;
    var area;
    var centroid;
    var magnitude;
    var centerPoint, midPoint;
    var centroidVector, centroid;

    // Functional for RArcEntity & RArc
    // Fail without an arc entity or an arc shape:
    if (!isArcEntity(arc) && !isArcShape(arc)) return undefined;

    radius = arc.getRadius(); // RArcEntity & RArcData & RArc
    halfSweep = arc.getSweep() / 2; // RArcEntity & RArc
    centerPoint = arc.getCenter(); // RArcEntity & RArcData & RArc

    // Avoid division by zero sweep:
    if (halfSweep === 0.0) {
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // Ifso or over revert to full arc:
    if (Math.abs(halfSweep) >= Math.PI) {
        // Return circle centroid data:
        return [centroid.x, centroid.y, centroid, radius*radius * Math.PI];
    }

    // Define signed area:
    area = radius*radius * halfSweep;

    // Define centroid magnitude:
    magnitude = 2 * radius * Math.sin(Math.abs(halfSweep)) / 3 / Math.abs(halfSweep);

    // Create centroid vector:
    midPoint = arc.getMiddlePoint(); // RArcEntity & RArcData & RArc
    centroidVector = midPoint.operator_subtract(centerPoint);
    centroidVector.setMagnitude2D(magnitude);
    centroid = centerPoint.operator_add(centroidVector);

    // Return arc sector centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

/** OK
 * Circle centroid data, including enclosed area (+).
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param circle         An circle RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getCircleAreaCentroid = function(circle) {
    var centroid;
    var radius;
    var area;

    // Functional for RCircleEntity & RCircleData & RCircle even for Null-length
    // Fail without a circle entity or a circle shape:
    if (!isCircleEntity(circle) && !isCircleShape(circle)) return undefined;

    centroid = circle.getCenter(); // RCircleEntity & RCircleData & RCircle
    radius = circle.getRadius(); // RCircleEntity & RCircleData & RCircle
    area = radius*radius * Math.PI; // getArea() only for RCircle

    // Return circle centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

// Ellipse items
/** Diversifies
 * Ellipse centroid data, including enclosed (signed) area.
 * Diversifies between a full ellipse (+) or an ellipse arc segment or sector (+CCW, -CW).
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseAreaCentroid = function(ellipse) {
    // Functional for REllipseEntity & REllipse
    // Fail without an ellipse entity or an ellipse shape:
    if (!isEllipseEntity(ellipse) && !isEllipseShape(ellipse)) return undefined;

    // Diversify return centroid data on the closed nature:
    if (ellipse.isFullEllipse()) {
        return this.getFullEllipseAreaCentroid(ellipse);
    }
    else {
        // Diversify return area on the arc mode:
        if (!isNull(this.sectorMode) && this.sectorMode) {
            return this.getEllipseArcSectorAreaCentroid(ellipse);
        }
        else {
            return this.getEllipseArcSegmentAreaCentroid(ellipse);
        }
    }
};

/** OK
 * Full ellipse centroid data, including enclosed area (+).
 * Considering a uniform density in 2D.
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         A full ellipse RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getFullEllipseAreaCentroid = function(ellipse) {
    var centroid;
    var major, minor;
    var area;

    // Functional for REllipseEntity & REllipse even for Null-length
    // Fail without a full ellipse entity or a full ellipse shape:
    if (!isFullEllipseEntity(ellipse) && !isFullEllipseShape(ellipse)) return undefined;

    centroid = ellipse.getCenter(); // REllipseEntity & REllipseData & REllipse
    major = ellipse.getMajorRadius(); // REllipseEntity & REllipseData & REllipse
    minor = ellipse.getMinorRadius(); // REllipseEntity & REllipse
    area = major * minor * Math.PI;    // Unsigned area

    // Return full ellipse centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

/** OK by approx
 * Ellipse arc segment centroid data, including enclosed signed area (+CCW, -CW).
 * Not to be confused with a simple ellipse arc shape.
 * Considering a uniform density in 2D.
 * Approximated with an auto closed polyline given the XP method number of arc segments.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSegmentAreaCentroid = function(ellipse) {
    var sweep;
    var length, center;
    var eSegs;
    var approx;

    // Functional for REllipseEntity & REllipse
    // Fail without an ellipse arc entity or an ellipse arc shape:
    if (!(isEllipseEntity(ellipse) && !ellipse.isFullEllipse()) && !isEllipseArcShape(ellipse)) return undefined;

    // Ifso or over revert to full arc:
    sweep = ellipse.getSweep(); // REllipseEntity & REllipseData & REllipse
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return the full ellipse centroid data:
        return this.getFullEllipseAreaCentroid(ellipse);
    }

    // Avoid Null-length:
    length = ellipse.getLength(); // REllipseEntity & REllipseData & REllipse
    if (!isNumberGreaterZero(length)) {
        center = ellipse.getCenter(); // REllipseEntity & REllipseData & REllipse
        return [center.x, center.y, center, 0.0];
    }

//debugger;
    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    // # Issue # ->fullEllipseArcs<- Is a size relative accuracy
    eSegs = RSettings.getIntValue("Explode/EllipseSegments", 32);    // Default =32 arc segments/full ellipse

    // Approximate the ellipse with a polyline and autoClose with a line segment:
    approx = ellipse.approximateWithArcs(eSegs); // REllipseEntity & REllipse
    approx.autoClose(RS.PointTolerance); // RPolylineEntity & RPolylineData & RPolyline
    if (!approx.isClosed()) approx.setClosed(true);
    this.hasApprox = true;

    // Return the approximated polyline centroid data:
    return this.getPolylineAreaCentroid(approx);
};

/** OK by approx =Verified
 * Ellipse arc sector centroid data including, enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSectorAreaCentroid = function(ellipse) {
    var sweep;
    var length, center;
    var arcC
    var pts, triagle;
    var triagleC
    var sign
    var x, y;
    var area;
    var centroid;

    // Functional for REllipseEntity & REllipse
    // Fail without an ellipse arc entity or an ellipse arc shape:
    if (!(isEllipseEntity(ellipse) && !ellipse.isFullEllipse()) && !isEllipseArcShape(ellipse)) return undefined;

    // Ifso or over revert to full ellipse:
    sweep = ellipse.getSweep(); // REllipseEntity & REllipseData & REllipse
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return the full ellipse centroid data:
        return this.getFullEllipseAreaCentroid(ellipse);
    }

    // Avoid Null-length:
    length = ellipse.getLength(); // REllipseEntity & REllipseData & REllipse
    center = ellipse.getCenter(); // REllipseEntity & REllipseData & REllipse
    if (!isNumberGreaterZero(length)) {
        // Return center zero centroid data:
        return [center.x, center.y, center, 0.0];
    }

    // Define ellipse arc centroid by closed equation:
    arcC = this.getEllipseArcSegmentAreaCentroid(ellipse);
    // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

    // Define arc center sector centroid:
    pts = [ellipse.getStartPoint(),
            center,
            ellipse.getEndPoint()];
    triagle = new RPolyline(pts, true);    // isClosed

    triagleC = this.getPolygonAreaCentroid(triagle);
    // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

    // Summing or subtracting:
    sign = (Math.abs(sweep) < Math.PI) ? 1 : -1;

    // Create overall centroid vector:
    var x = arcC[0] * Math.abs(arcC[3]) + sign * triagleC[0] * Math.abs(triagleC[3]);
    var y = arcC[1] * Math.abs(arcC[3]) + sign * triagleC[1] * Math.abs(triagleC[3]);
    var area = Math.abs(arcC[3]) + sign * Math.abs(triagleC[3]);
    var centroid = new RVector(x / area, y / area);    // area isNOT zero

    // CW or CCW:
    var sign = (sweep > 0.0) ? 1 : -1;

    // Return the arc sector centroid data:
    return [centroid.x, centroid.y, centroid, sign * area];
};

// --------------------------------------------------
// Centroid methods for a wire of uniform density     # ToDo # Move to wire centroids Addon # ToDo # Verify
// --------------------------------------------------

/** NOK
 * Contours of connected items centroid data, including total length (+).
 * Considering a wire of uniform density.
 * As merged polylines, ifso approximated with polylines given the XP method settings.
 * Incorrect for nested or self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param loops         Collections of multiple RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, total length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getContoursWireCentroid = function(loops) {
    // # ToDo # Contours of connected items ifso by approx
    // Verify isNotIntersecting isNotNested
    // Loops InfoAreaCentroid.prototype.getContourWireCentroid()
    return undefined;
};

/** NOK
 * A single contour of connected items centroid data, including total length (+).
 * Considering a wire of uniform density.
 * As merged polyline, ifso approximated with polylines given the XP method settings.
 * Incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param items         A collection of multiple RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, total length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getContourWireCentroid = function(items) {
    // # ToDo # Contour of connected items ifso by approx
    // Verify isConnected
    // Merge chain of connected RShapes to polyline
    // .getPolylineArea(poly)
    return undefined;
}

/** OK by approx
 * Spline centroid data, including length (+).
 * Considering a wire of uniform density.
 * Approximated with a polyline given the XP method tolerance.
 * Incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param spline         A spline RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getSplineWireCentroid = function(spline) {
    var length, start;
    var sTol;
    var approx;

    // Functional for RSplineEntity & RSplineData & RSpline
    // Fail without a spline entity or a spline shape:
    if (!isSplineEntity(spline) && !isSplineShape(spline)) return undefined;

    // Avoid Null-length:
    length = spline.getLength(); // RSplineEntity & RSplineData & RSpline
    if (!isNumberGreaterZero(length)) {
        start = spline.getStartPoint(); // RSplineEntity & RSplineData & RSpline
        return [start.x, start.y, start, 0.0];
    }

    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    sTol = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);    // Default =0.01 deviation

    // Construct polyline of RShapes from ellipse approximation:
    approx = spline.approximateWithArcs(sTol); // RSplineEntity & RSplineData & RSpline
    this.hasApprox = true;

    // Return the approximated polyline centroid data:
    return this.getPolylineWireCentroid(approx);
};

// Polyline items
/** OK
 * Polyline centroid data, including length (+).
 * Considering a wire of uniform density.
 * Incorrect for self-intersecting shapes.
 * # Issue # No good test on self-intersecting bulging polylines.
 * \author CVH © 2021
 *
 * \param polyline         A polyline RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolylineWireCentroid = function(polyline) {
    // Sums PolygonWireCentroid & multiple ArcWireCentroid
    var poly;
    var orgLength, start;
    var ips;
    var shapes, shape;
    var i, iMax;
    var shapeC;
    var x = 0;
    var y = 0;
    var length = 0;
    var centroid;

    // Functional for RPolylineEntity & RPolyline
    // Fail without a polyline shape, possible from an RPolylineEntity:
    if (isPolylineEntity(polyline)) {    // REntity based (Excludes RSolids and so)
        poly = polyline.castToShape().clone();
    }
    else {
        poly = polyline;
    }
    if (!isPolylineShape(poly)) return undefined;    // Failed

    // Avoid Null-length:
    orgLength = poly.getLength(); // RPolylineEntity & RPolyline
    if (!isNumberGreaterZero(orgLength)) {
        start = poly.getStartPoint(); // RPolylineEntity & RPolylineData & RPolyline
        return [start.x, start.y, start, 0.0];
    }

//debugger;
    // Reject self-intersecting polylines with line segments:
    if (!polyline.hasArcSegments()) { // RPolylineEntity & RPolyline
        ips = poly.getSelfIntersectionPoints(RS.PointTolerance);
        // Returns a single intersection point where segments are crossing,
        // 4 equal intersection points where nodes coexists
        // # Issue # Odd extra node as intersection point when node is on other segment,
        // unrelated to CW/CCW or tolerance
        if (ips.length > 0) debugger;    // ### Catch this In the act !!! ###
        if (ips.length > 0) return undefined;    // Failed
    }

    // Process all exploded shapes:
    shapes = poly.getExploded(); // RPolylineEntity & RPolylineData & RPolyline
    iMax = shapes.length;
    for (i=0; i<iMax; i++) {    // Cycle all polyline segments
        shape = shapes[i];
        if (isLineShape(shape)) {
            shapeC = this.getLineWireCentroid(shape);
            // Returns [centroid.x, centroid.y, centroid, length] or 'undefined'
        }
        else if (isArcShape(shape)){
            shapeC = this.getArcWireCentroid(shape);
            // Returns [centroid.x, centroid.y, centroid, length] or 'undefined'
        }
        else {
            shapeC = undefined;
        }

        // Sum to total, if any:
        if (!isNull(shapeC)) {
            x += shapeC[0] * shapeC[3];
            y += shapeC[1] * shapeC[3];
            length += shapeC[3];
        }
    } // Loop segments

if (length !== orgLength) debugger;

    // Avoid and fail when dividing by a zero length:
    if (length === 0.0) return undefined;

    // Create overall centroid vector:
    centroid = new RVector(x / length, y / length);

    // Return arc segment centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

// Polyline items with line segments
/** OK
 * Polyline entity with line segments centroid data, including length (+).
 * Considering a wire of uniform density.
 * Elides bulge factors.
 * Rejects self-intersecting polyline with line segments.
 * \author CVH © 2021
 *
 * \param polygon         A polyline RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolygonWireCentroid = function(polygon) {
    var poly;
    var orgLength, start;
    var ips;
    var shapes, shape;
    var i, iMax;
    var lineC;
    var x = 0;
    var y = 0;
    var length = 0;
    var centroid;

    // Functional for RPolylineEntity & RPolyline
    // Fail without a polyline shape, possible from an RPolylineEntity:
    if (isPolylineEntity(polygon)) {    // REntity based (Excludes RSolids and so)
        poly = polygon.castToShape().clone();
    }
    else {
        poly = polygon;
    }
    if (!isPolylineShape(poly)) return undefined;    // Failed

    // Avoid Null-length:
    orgLength = poly.getLength(); // RPolylineEntity & RPolyline
    if (!isNumberGreaterZero(orgLength)) {
        start = poly.getStartPoint(); // RPolylineEntity & RPolylineData & RPolyline
        return [start.x, start.y, start, 0.0];
    }

//debugger;
    // Reject self-intersecting polylines with line segments:
    if (!poly.hasArcSegments()) { // RPolylineEntity & RPolyline
        ips = poly.getSelfIntersectionPoints(RS.PointTolerance);
        // Returns a single intersection point where segments are crossing,
        // 4 equal intersection points where nodes coexists
        // # Issue # Odd extra node as intersection point when node is on other segment,
        // unrelated to CW/CCW or tolerance
        if (ips.length > 0) debugger;    // ### Catch this In the act !!! ###
        if (ips.length > 0) return undefined;    // Failed
    }

    // Process all line shapes from exploded shapes:
    shapes = poly.getExploded(); // RPolylineEntity & RPolylineData & RPolyline
    iMax = shapes.length;
    for (i=0; i<iMax; i++) {    // Cycle all polyline segments
        shape = shapes[i];
        if (isLineShape(shape)) {
            lineC = this.getLineWireCentroid(shape);
            // Returns [centroid.x, centroid.y, centroid, length] or 'undefined'

            // Sum to total, if any:
            if (!isNull(lineC)) {
                x += lineC[0] * lineC[3];
                y += lineC[1] * lineC[3];
                length += lineC[3];
            }
        }
    } // Loop segments

if (length !== orgLength) debugger;

    // Avoid and fail when dividing by a zero length:
    if (length === 0.0) return undefined;

    // Create overall centroid vector:
    centroid = new RVector(x / length, y / length);

    // Return arc segment centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

// Line items
/** OK
 * Line segment centroid data, including length (+).
 * Considering a wire of uniform density.
 * Excluding rays and Xlines
 * \author CVH © 2021
 *
 * \param line         A line RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getLineWireCentroid = function(line) {
    var length;
    var midPoint;

    // Functional for RArcEntity & RArc even for Null-length
    // Fail without a line entity or a line shape:
    if (!isLineEntity(line) && !isLineShape(line)) return undefined;

    length = line.getLength();
    midPoint = line.getMiddlePoint();

    // Return line segment centroid data:
    return [midPoint.x, midPoint.y, midPoint, length];
};

// Circular items
/** OK
 * Arc centroid data, including length (+).
 * Considering a wire of uniform density.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcWireCentroid = function(arc) {
    var radius, halfSweep;
    var length;
    var magnitude;
    var centerPoint, midPoint;
    var centroidVector, centroid;

    // Functional for RArcEntity & RArc even for Null-length
    // Fail without an arc entity or an arc shape:
    if (!isArcEntity(arc) && !isArcShape(arc)) return undefined;

    radius = arc.getRadius(); // RArcEntity & RArcData & RArc
    halfSweep = arc.getSweep() / 2; // RArcEntity & RArc
    length = arc.getLength(); // RArcEntity & RArcData & RArc
    centerPoint = arc.getCenter(); // RArcEntity & RArcData & RArc


    // Ifso or over revert to full arc:
    if (Math.abs(halfSweep) >= Math.PI) {
        // Return circle centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 2 * radius * Math.PI];
    }

    // Avoid division by zero sweep:
    if (halfSweep === 0.0) {
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // Define centroid magnitude:
    magnitude = radius * Math.sin(halfSweep) / halfSweep;

    // Create centroid vector:
    midPoint = arc.getMiddlePoint(); // RArcEntity & RArcData & RArc
    centroidVector = midPoint.operator_subtract(centerPoint);
    centroidVector.setMagnitude2D(magnitude);
    centroid = centerPoint.operator_add(centroidVector);

    // Return arc segment centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

/** OK
 * Circle centroid data, including length (+).
 * Considering a wire of uniform density.
 * \author CVH © 2021
 *
 * \param circle         An circle RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getCircleWireCentroid = function(circle) {
    var centroid;
    var length;

    // Functional for RCircleEntity & RCircle even for Null-length
    // Fail without a circle entity or a circle shape:
    if (!isCircleEntity(circle) && !isCircleShape(circle)) return undefined;

    centroid = circle.getCenter(); // RCircleEntity & RCircleData & RCircle
    length = circle.getLength(); // RCircleEntity & RCircle

    // Return circle centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

// Ellipse items
/** Diversifies
 * Ellipse centroid data, including length (+).
 * Diversifies between a full ellipse or an ellipse arc.
 * Considering a wire of uniform density.
 * Ifso, approximated with a polyline given the XP method number of arc segments.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseWireCentroid = function(ellipse) {
    // Functional for REllipseEntity & REllipse
    // Fail without an ellipse entity or an ellipse shape:
    if (!isEllipseEntity(ellipse) && !isEllipseShape(ellipse)) return undefined;

    // Diversify return centroid data on the closed nature:
    if (ellipse.isFullEllipse()) {
        return this.getFullEllipseWireCentroid(ellipse);
    }
    else {
        return this.getEllipseArcWireCentroid(ellipse);
    }
};

/** OK
 * Full ellipse centroid data, including length (+).
 * Considering a wire of uniform density.
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         A full ellipse RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getFullEllipseWireCentroid = function(ellipse) {
    var centroid;
    var length;

    // Functional for REllipseEntity & REllipseData & REllipse even for Null-length
    // Fail without a full ellipse entity or a full ellipse shape:
    if (!isFullEllipseEntity(ellipse) && !isFullEllipseShape(ellipse)) return undefined;

    centroid = ellipse.getCenter(); // REllipseEntity & REllipseData & REllipse
    length = ellipse.getLength(); // REllipseEntity & REllipseData & REllipse

    // Return full ellipse centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

/** OK by approx
 * Ellipse arc centroid data, including length (+).
 * Considering a wire of uniform density.
 * Approximated with a polyline given the XP method number of arc segments.
 * \author CVH © 2021
 *
 * \param ellipse         A spline RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcWireCentroid = function(ellipse) {
    var sweep;
    var length, center;
    var eSegs;
    var approx;

    // Functional for REllipseEntity & REllipse
    // Fail without an ellipse arc entity or an ellipse arc shape:
    if (!(isEllipseEntity(ellipse) && !ellipse.isFullEllipse()) && !isEllipseArcShape(ellipse)) return undefined;

    // Ifso or over revert to full arc:
    sweep = ellipse.getSweep(); // REllipseEntity & REllipseData & REllipse
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return the full ellipse centroid data:
        return this.getFullEllipseWireCentroid(ellipse);
    }

    // Avoid Null-length:
    length = ellipse.getLength(); // REllipseEntity & REllipseData & REllipse
    if (!isNumberGreaterZero(length)) {
        center = ellipse.getCenter(); // REllipseEntity & REllipseData & REllipse
        return [center.x, center.y, center, 0.0];
    }

    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    // # Issue # ->fullEllipseArcs<- Is a size relative accuracy
    eSegs = RSettings.getIntValue("Explode/EllipseSegments", 32);    // Default =32 arc segments/full ellipse
    // Get polyline of RShapes from ellipse approximation:
    approx = ellipse.approximateWithArcs(eSegs); // REllipseEntity & REllipse
    this.hasApprox = true;

    // Return the approximated polyline centroid data:
    return this.getPolylineWireCentroid(approx);
};

// ==================================================

/**
 * Pre-oriented hatch boundary loops as polylines with line and arc segments.
 * Is hatched = CCW = positive area
 * Is voided = CW = negative area
 * # Issue # Can't guarantee how correct RShapes from boundaries are merged.
 * \author CVH © 2021
 *
 * \param hatch         A hatch REntity.
 *
 * \return A list of pre-oriented boundary loops as polylines or 'undefined'.
 */
// Seems OK
InfoAreaCentroid.prototype.getOrientedHatchBoundaries = function(hatch) {
    var hatchData;
    var boundaries;
    var i, j, iMax;
    var boundary;
    var nesting, isOddNested;
    var trial;
    var pointInside;
    var pointOnEntity;
    var orientation;

    // Fail without a hatch entity:
    if (!isHatchEntity(hatch)) return undefined;
    hatchData = hatch.getData();

//debugger;
    // Retrieve boundary loops:
    // boundaries = hatchData.getBoundaryAsPolylines(0);    // Line segment length
    // # Issue Solved # .getBoundaryAsPolylines(val) interpolates curved shapes with line segments
    // Crashes QCAD with 0 or -1 for no interpolation. Solved with a custom script
    boundaries = this.getHacthPolyLoops(hatchData);
    // Returns a list of boundary loops as polylines with line and arc segments

    iMax = boundaries.length;
    // Fail without at least one boundary:
    if (iMax < 1) return undefined;

    // # Informational # Hatch boundaries should/will not intersect, self-intersect, can touch, ...
    // # Informational # Common is the use of counting crossings of a ray from a point inside the closed contour.

//debugger;
    // Process all hatch boundaries for their nested nature:
    for (i=0; i<iMax; i++) {    // A) Cycle all boundaries
        boundary = boundaries[i];

        // Define odd or even nested vs all other boundaries except itself:
        nesting = 0;
        var point = boundary.getStartPoint();
        for (j=0; j<iMax; j++) {    // Cycle all boundaries except itself
            if (i === j) continue;    // Skip itself
            trial = boundaries[j];

            // Verify if the boundary is nested inside the one on trial:
            // A) Excludes box based not even close:
            if (!trial.getBoundingBox().contains(boundary.getBoundingBox())) {
                continue;    // Is not nested
            }
            // B) Verify if a random vertex is inside the trial boundary.
            if (trial.contains(point, true, RS.PointTolerance)) {
                nesting++;    // Is nested
            }
        } // Loop boundaries except itself

        // Force outer contour and even 'islands' as positive area =CCW, odd voids as negative area =CW:
        isOddNested = nesting % 2 === 1;
        orientation = boundary.getOrientation();
        if (isOddNested) {    // When odd >
            // Must be CW:
            if (orientation === RS.CCW) {
                boundary.reverse();
            }
        }
        else {    // When even >
            // Must be CCW:
            if (orientation === RS.CW) {
                boundary.reverse();
            }
        }

        // Hatch statistics:
        // A) Sum outer boundary loops length for marker size:
        if (nesting === 0) {
            this.markDiv += boundary.getLength();
        }
        // B) Is summed or differential area:
        if (nesting > 0) {
            this.isDifferential = true;
        }
        // C) Is one or multiple loops:
        if (iMax > 1) {
            this.isSingleLoop = false;
        }

    } // Loop boundaries

    // Return the pre-oriented boundaries:
    return boundaries;
};

/**
 * Hatch boundary loops as polylines with line and arc segments.
 * Replacement for .getBoundaryAsPolylines(val) that interpolates with line segments.
 * # Issue # Can't guarantee how correct RShapes from boundaries are merged.
 * \author CVH © 2021
 *
 * \param hatchData         A hatch RHatchData.
 *
 * \return A list of boundary loops as polylines. (Can be empty # Issue # Can it?)
 */
// Seems OK
InfoAreaCentroid.prototype.getHacthPolyLoops = function(hatchData) {
    var i, iMax, n, nMax;
    var shapes, shape;
    var polyShapes;
    var sTol, eSegs;
    var approx;
    var loop;
    var loops = [];

//debugger;
    iMax = hatchData.getLoopCount();
    for (i=0; i<iMax; i++) {    // Cycle all boundary loops
        shapes = hatchData.getLoopBoundary(i);
        nMax = shapes.length
        polyShapes = [];
        for (n=0; n<nMax; n++) {    // Cycle all boundary loop shapes
            shape = shapes[n];
            // Diversify on RShape from boundary loop:
            if (isCircleShape(shape)) {
                // Append circles as arc shapes:
                // # Bug Fixed # Circles are initially stored as circles
                // https://www.qcad.org/rsforum/viewtopic.php?t=8846#p35173
                polyShapes.push(new RArc(shape.getCenter(), shape.getRadius(), 0.0, Math.PI, false));
                polyShapes.push(new RArc(shape.getCenter(), shape.getRadius(), Math.PI, 2*Math.PI, false));
            }
            else if (isArcShape(shape)) {
                // Append arc shape:
                // # Issue Fixed # Circles are saved as full arcs ... bulge = 1.66312e+16 instead of infinite
                if (shape.getSweep() > 2*Math.PI - RS.AngleTolerance) {
                    polyShapes.push(new RArc(shape.getCenter(), shape.getRadius(), 0.0, Math.PI, false));
                    polyShapes.push(new RArc(shape.getCenter(), shape.getRadius(), Math.PI, 2*Math.PI, false));
                }
                else {
                    polyShapes.push(shape.clone());
                }
            }
            else if (isLineShape(shape)) {
                // Append line shape:
                polyShapes.push(shape.clone());
            }
            else if (isSplineShape(shape)) {
                // Append RShapes from spline approximation:
                // # Issue # What about lines or arcs as spline?
                // See: ShapeAlgorithms.splineToLineOrArc()
                sTol = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);    // Default =0.01 deviation
                approx = shape.approximateWithArcs(sTol);
                this.hasApprox = true;
                polyShapes = polyShapes.concat(approx.getExploded());
            }
            else if (isEllipseShape(shape)) {
                // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
                // # Issue # ->fullEllipseArcs<- Is a size relative accuracy
                eSegs = RSettings.getIntValue("Explode/EllipseSegments", 32);    // Default =32 arc segments/full ellipse
                // Append RShapes from ellipse approximation:
                approx = shape.approximateWithArcs(eSegs);
                this.hasApprox = true;
                polyShapes = polyShapes.concat(approx.getExploded());
            }
            else {
                // # ToDo # Possible incomplete
                EAction.handleUserWarning(qsTr("Unhandled shape from hatch loop."));
                debugger;    // ### Catch this In the act !!! ###
            }
        } // Loop boundary loop shapes

        loop = new RPolyline(polyShapes);    // Typical logically closed ifso
        loops.push(loop);
    } // Loop boundary loops

    return loops;
};

/**
 * Adding text labels.
 */
InfoAreaCentroid.prototype.addTextLabel = function(doc, op, pos, offset, text) {
    var textData;
    var newEntity;

    // Create new text data object:
    textData = new RTextData();
    textData.setAlignmentPoint(new RVector(pos.x + offset.x, pos.y + offset.y));
    textData.setVAlign(RS.VAlignTop);
    textData.setHAlign(RS.HAlignLeft);
    textData.setFontName(this.docDimFont);
    textData.setTextHeight(this.fontSize);
    textData.setText(text);

    // Create new document entity:
    newEntity = new RTextEntity(doc, textData);
    newEntity.setColor(this.infoColor);

    // Add to operation:
    op.addObject(newEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
};

/**
 * Adding centroid marker.
 * \author CVH © 2021
 */
InfoAreaCentroid.prototype.addCentroidMarker = function(doc, op, pos, radius) {
    var quaterC = 0.4142135623730950488;    // bulge = (sqrt(2) - 1)
    var bulges, widths;
    var shift;
    var pts;
    var poly;
    var circleData, polyData;
    var circleEntity, polyEntity;

    bulges = [quaterC, 0.0, -quaterC, 0.0];
    // # Issue Fixed # Circle sector is not rendered correct with Width = 2R
    // Fixed with adding 1%, functional for 2R>=0.03 units
    // See: https://qcad.org/rsforum/viewtopic.php?f=33&t=7889&p=30877
    // See: https://www.ribbonsoft.com/bugtracker/index.php?do=details&task_id=2155
    var radiusFix = radius * 1.01;
    widths = [radiusFix, 0.0, radiusFix, 0.0];
    shift = radius / 2;
    pts = [new RVector(pos.x + shift, pos.y),
            new RVector(pos.x, pos.y + shift),
            new RVector(pos.x, pos.y - shift),
            new RVector(pos.x - shift, pos.y)];

    // Create new centroid marker polyline:
    poly = new RPolyline(pts, false);    // notClosed
    poly.setBulges(bulges);
    poly.setStartWidths(widths);
    poly.setEndWidths(widths);

    // Create new shape data objects:
    circleData = new RCircleData(pos, radius);
    polyData = new RPolylineData(poly);

    // Create new entities:
    circleEntity = new RCircleEntity(doc, circleData);
    circleEntity.setColor(this.infoColor);
    polyEntity = new RPolylineEntity(doc, polyData);
    polyEntity.setColor(this.infoColor);

    // Add to operation:
    op.addObject(circleEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
    op.addObject(polyEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
};

/**
 * Area centroids supported entity type or -1 when not supported.
 */
InfoAreaCentroid.prototype.getSupportedAreaCentroidType = function(entity) {
    var ret = -1;    // Default, not supported

    // Diversify on entity type:
    if (isArcEntity(entity)) {
        ret = 1;    // As arc segment
    }
    else if (isCircleEntity(entity)) {
        ret = 2;    // As circle
    }
    else if (isEllipseEntity(entity)) {
        ret = 3;    // Full or approximated, autoClosed with a line
    }
    else if (isPolylineEntity(entity)) {
        ret = 4;    // autoClosed with a line
    }
    else if (isSplineEntity(entity)) {
        ret = 5;     // Approximated, autoClosed with a line
    }
    else if (isHatchEntity(entity)) {
        ret = 6;     // Total/differential hatched area
    }

    // Return type:
    return ret;
};

/**
 * Define centroid marker size.
 * \author CVH © 2021
 */
InfoAreaCentroid.prototype.getMarkerSize = function(entity) {
    var box;
    var markerSize;

    // Functional for REntity, REntityData, RShape
    box = entity.getBoundingBox(); // REntity, REntityData, RShape

    // Use given length or entity length, except zero or less:
    if (this.markDiv <= 0.0) this.markDiv = entity.getLength();
    if (this.markDiv <= 0.0) this.markDiv = 1;

    // Proportional to shape:
    // Equals to: sqrt(25x25 per area) times the half box circumference divided by the entity length:
    markerSize = Math.sqrt(box.getArea() / 625) * (box.getWidth() + box.getHeight()) / this.markDiv;

    // Not smaller than the dimension font size:
    if (markerSize < this.fontSize) markerSize = this.fontSize;

    // Return centroid marker size:
    return markerSize;
};
