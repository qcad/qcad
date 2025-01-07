/**Beta 0.32
 * InfoAreaCentroid Beta version 0.32 (As MiscInformationCentroids)
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

include("scripts/Misc/MiscInformation/InfoCentroids/InfoCentroids.js");
//  # Issue Fixed # Included for coordinateToString(), library.js doesn't include it
include("scripts/sprintf.js");

// # ToDo # Should we clear long or vast arrays? shift() out or splice(0, 1) out?

/**
 * \class InfoAreaCentroid
 * \ingroup ecma_misc_information_centroids
 * \brief This action adds an area 2D Centroid marker and text labels for a selected entity.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoAreaCentroid(guiAction) {
    InfoCentroids.call(this, guiAction);
};

// Deriving our class from the base class:
InfoAreaCentroid.prototype = new InfoCentroids();
InfoAreaCentroid.includeBasePath = includeBasePath;

/**
 * This GUI action adds a 2D centroid marker and detail labels for a selected entity.
 * Calculates centroid position and enclosed area assuming a uniform density surface.
 * Casts additional details as text labels and reports them on the Command History.
 * Stores full floating point data as marker custom properties.
 * 2D Centroid markers are generated with a default density of 1.00 per unit.
 * Supports selected enclosed area of:
 *    - Arc entity as an arc segment.
 *    - Circle entity.
 *    - Ellipse entity, full or as arc segment, autoClosed with a line segment.
 *    - Polyline entity, autoClosed with a line segment.
 *    - Spline entity as approximated polyline & autoClosed with a line segment.
 *    - Optional as arc and ellipse arc sector by a hidden switch.
 * Supports Hatch entity total/differential hatched area.
 * Not interpolating with line segments, the methods sum areas and centroids by shapes.
 *
 * Included are various methods for area and area 2D centroids for RShapes.
 */
// BeginEvent handler:
InfoAreaCentroid.prototype.beginEvent = function() {
    InfoCentroids.prototype.beginEvent.call(this);

    // Presets:
    this.massMode = false;
    this.wireMode = false;

    // Retrieve hidden switch as preset:
    this.sectorMode = RSettings.getBoolValue("InfoAreaCentroid/sectorMode", false);    // Default =False

    // Call the area centroid of a selected entity main loop
    this.selectionAreaCentroid(this.getDocumentInterface());

    // Initiate or store switch back:
    RSettings.setValue("InfoAreaCentroid/sectorMode", this.sectorMode, true);    // doOverwrite

    // # Issue Fixed # Button toggles between usage, fixed with releasing
    this.getGuiAction().setChecked(false);

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
 * \return Nothing. Casts 2D Centroid marker and text labels, reports on Command History.
 */
InfoAreaCentroid.prototype.selectionAreaCentroid = function(di) {
    var doc = di.getDocument();
    var ids, idn;
    var msg, txt;
    var entity, entityShape;
    var type;
    var res;
    var op;
    var dimStyle
    var shift;
    var markerSize;
    var decPnt, lstSep;
    var dimLinPrec, dimTrZeros;
    var offset;
    var transaction;

    // Retrieve document selection, fail on none or many:
    // # ToDo # Add states for none & pointing inside a closed contour
    ids = doc.querySelectedEntities();
    idn = ids.length;
    if (idn === 0) {    // Double lock, action requires selection
        EAction.handleUserWarning(qsTr("No selection."));
        EAction.handleUserInfo(qsTr("Please, make a selection first. Command terminated."));
        return undefined;    // Failed selection
    }
    else if (idn > 1) {
        // Excluding there:
        // - Open shapes can be treated as a wire or as an enclosed area
        // - Arcs and ellipse arcs can be treated as segments or sectors or wires
        // - Uniform density areas can't be summed directly to uniform wire lengths
        EAction.handleUserWarning(qsTr("Multiple entities in selection."));
        EAction.handleUserInfo(qsTr("Not implemented. Command terminated."));
        return undefined;    // Failed selection
    }

    // Additional Command History script notification:
    msg = qsTr("Area 2D Centroid script (v0.32) by CVH");
    if (this.sectorMode) msg += " - " + qsTr("Arc sector mode");
    EAction.handleUserMessage(qsTr("Area 2D Centroid script (v0.32) by CVH"));

    // Initial values:
    this.hasApprox = false;
    this.isSingleLoop = true;
    this.isDifferential = false;
    this.boxSize = undefined;
    this.errMsg = undefined;
    msg = qsTr("Enclosed area:");

    // Retrieve the single selected entity:
    entity = doc.queryEntity(ids[0]);

//debugger;
    // Retrieve supported type:
    type = this.getSupportedAreaCentroidType(entity);    // REntity based (Excludes RSolids and so)
    // Returns supported entity type or -1

    // As 2D RShape when supported except for hatch entities:
    if (type > 0 && type < 6) {
        entityShape = entity.castToShape().clone();
        entityShape.to2D();
        // Merge box with the overall box:
        this.mergeBoxWith(entityShape.getBoundingBox());
    }

    // Diversify on type:
    switch (type) {
        case 1:    // isArcEntity
            res = this.getArcAreaCentroid(entityShape); // Diversifies
            break;
        case 2:    // isCircleEntity
            // Reject old style marker circles:
            if (!isNull(entity.getCustomProperty("QCAD", InfoCentroids.Terms.Title, undefined))) {
                // Abort critical:
                EAction.handleUserWarning(qsTr("Centroid markers circle in selection. No results."));
                return undefined;    // Failed, isMarker
            }
            res = this.getCircleAreaCentroid(entityShape);
            break;
        case 3:    // isEllipseEntity
            res = this.getEllipseAreaCentroid(entityShape); // Diversifies
            break;
        case 4:    // isPolylineEntity
            // Reject any self-intersecting shape (incl. centroid markers):
            if (this.isSelfIntersectingPoly(entityShape)) {
                res = undefined;
            }
            else {
                res = this.getPolylineAreaCentroid(entityShape);
            }
            break;
        case 5:    // isSplineEntity
            res = this.getSplineAreaCentroid(entityShape);
            msg = qsTr("Approximated enclosed area:");
            break;
        case 6:    // isHatchEntity
            res = this.getHatchedAreaCentroid(entity);    // REntity based
            msg = qsTr("Hatched area:")
            if (!this.isSingleLoop) msg = qsTr("Total hatched area:");
            if (this.isDifferential) msg = qsTr("Differential hatched area:");
            break;
        default:    // isUnsupported
            // Abort critical:
            EAction.handleUserWarning(qsTr("Unsupported entity type. No results."));
            return undefined;    // Failed type
            break;
    } // End switch type
            // Abort here:

    // Abort critical without results:
    if (isNull(res)) {
        if (isNull(this.errMsg)) this.errMsg = qsTr("No results.");
        EAction.handleUserWarning(this.errMsg);
        return undefined;    // Failed, resNull
    }

//debugger;
    // Initiate an operation:
    op = new RAddObjectOperation();
    // Set tool title used for undo/redo information:
    op.setText(qsTr("2D area Centroid"));

    // Retrieve document dimension font:
    this.docDimFont = doc.getDimensionFont();

    // Revert to the standard font without a document font:
    if (isNull(this.docDimFont) || this.docDimFont.isEmpty()) {
        this.docDimFont = "Standard";
    }

    // # Issue Fixed # Drawings saved with 'Standard' revert to 'TXT' when reloaded
    // Revert to the standard font when it is 'TXT':
    if (this.docDimFont.toUpperCase() === "TXT") {
        this.docDimFont = "Standard";
    }

    // Retrieve drawing dimensions font size:
    // # Known Issue # Will not work prior QCAD 3.26.4
    dimStyle = doc.queryDimStyle();
    this.fontSize = dimStyle.getDouble(RS.DIMTXT) * dimStyle.getDouble(RS.DIMSCALE);

    // Assure for a font size equal or larger than 0.03 (See addCentroidMarker() fix):
    if (isNull(this.fontSize) || !isNumber(this.fontSize)) this.fontSize = 2.5;    // Default
    if (this.fontSize < 0.03) this.fontSize = 0.03;
    shift = this.fontSize / 2;

    // Include centroid marker:
    markerSize = this.getMarkerSize();
    this.addCentroidMarker(doc, op, res, markerSize);

    // Use drawing decPnt/lstSep/precision:
    // # Known Issue # Will not work prior QCAD 3.26.4
    decPnt = String.fromCharCode(dimStyle.getInt(RS.DIMDSEP));    // charCode 32/44/46
    dimLinPrec = dimStyle.getInt(RS.DIMDEC);          // Integer value
    dimTrZeros = dimStyle.getInt(RS.DIMZIN) === 0;    // Show decimal trailing zeros: 0=Yes 8=No
    // # Issue Fixed # Undefined drawing list separator, use common sense
    lstSep = (decPnt === ",") ? ";" : ",";    // Default =comma

    // Include absolute area label:
    txt = msg + " " +this.formatLabelValue(Math.abs(res[3]), decPnt, dimLinPrec, dimTrZeros);
    if (type === 6 && this.hasApprox) txt += " " + qsTr("(Incl. approximations)");
    offset = new RVector(markerSize + shift, markerSize + shift);
    this.addTextLabel(doc, op, res[2], offset, txt);

    // Report absolute area:
    txt = msg + this.formatCmdValue(Math.abs(res[3]));
    if (type === 6 && this.hasApprox) txt += " " + qsTr("(Incl. approximations)");
    EAction.handleUserInfo(txt);

    // Diversify on approximated nature:
    msg = (this.hasApprox) ? qsTr("Approximated centroid:") : qsTr("Centroid:");

    // Include centroid position label:
    txt = msg + " (" + this.formatLabelValue(res[0], decPnt, dimLinPrec, dimTrZeros);
    txt += lstSep + " " + this.formatLabelValue(res[1], decPnt, dimLinPrec, dimTrZeros) + ")";
    offset = new RVector(markerSize + shift, shift - markerSize);
    this.addTextLabel(doc, op, res[2], offset, txt);

    // Report centroid position:
    msg += this.formatCoordinate(res[0], res[1]);
    EAction.handleUserInfo(msg);

    // Set relative zero and apply all operations:
    di.setRelativeZero(res[2]);
    transaction = di.applyOperation(op);

    // Advance selection to marker:
    this.advanceSelection(di, transaction);

    // Return to terminate:
    return true;
};

// -------------
// Area methods
// -------------
// Hatch items
/**
 * Hatched differential area of a hatch entity (+).
 * Ifso approximated with polylines given the XP method settings, handled in situ.
 * \author CVH © 2021
 *
 * \param entity         A hatch REntity.
 *
 * \return The differential area (+) or 'undefined'.
 */
InfoAreaCentroid.prototype.getHatchedArea = function(entity) {
    var boundaries;
    var i, iMax;
    var boundA;
    var boundsA = [];
    var dArea;

    // Fail without a hatch entity:
    if (!isHatchEntity(entity)) return undefined;    // Failed REntity

//debugger;
    // Pre-orient hatch boundaries for differential sign:
    boundaries = this.getOrientedHatchBoundaries(entity);
    // Returns at least one pre-oriented boundary or 'undefined'

    // Fail without boundaries:
    if (isNull(boundaries)) return undefined;    // Failed, noBoundaries

    // Process all pre-oriented hatch boundary loops:
    iMax = boundaries.length;
    for (i=0; i<iMax; i++) {    // Cycle all boundary loops
        // Get boundary area:
        boundA = this.getPolylineArea(boundaries[i]);
        // Returns signed area or 'undefined'

        // Add to list, if any:
        if (!isNull(boundA)) {
            boundsA.push(boundA);
        }
        else {    // Should not occur >
            debugger;    // ### Catch this In the act !!! ###
        }
    } // Loop boundaries

    // Calculate running sum:
    dArea = this.getRunningSumKBK(boundsA);

        // Avoid NaN values:
        if (!isNumber(dArea)) {
            return undefined;    // Failed, NaN
        }

    // Hatch statistics:
    if (boundsA.length > 1) this.isSingleLoop = false;

    // Return the differential area:
    return dArea;
};

// Contour items
/**
 * Placeholder: Contours of connected items enclosed area (+).
 * As merged polygons + shapes, ifso approximated with polylines given the XP method settings.
 * Incorrect for nested, intersecting or self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param loops         Collections of multiple RShape or REntity.
 *
 * \return Total area or 'undefined'.
 */
InfoAreaCentroid.prototype.getContoursArea = function(loops) {
    // # ToDo # Contours of connected shapes or entities, ifso by approx
    // Verify isNotIntersecting isNotNested
    // Loops InfoAreaCentroid.prototype.getContourAreaCentroid()
    return undefined;
};

/**
 * Placeholder: A single contour of connected items enclosed area (+).
 * As merged polygon + shapes, ifso approximated with polylines given the XP method settings.
 * Incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param items         A collection of multiple RShape.
 *
 * \return Total area or 'undefined'.
 */
InfoAreaCentroid.prototype.getContourArea = function(items) {
    // # ToDo # Contour of connected items, ifso by approx
    // Verify  isNotNull-Length isNotNull isConnected
    // Merge endpoints to a polyline with line segments to an inner polygon hull
    // Set off situ by box ...?
    // Cycle Area methods
    return undefined;
}

// Spline RShapes
/**
 * Spline RShape enclosed signed area (+CCW, -CW).
 * Approximated with an auto closed polyline given XP method tolerance.
 * Unverified and incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param spline         A spline RShape.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getSplineArea = function(spline) {
    var orgLength;
    var box, boxCenter;
    var clone;
    var sTol;
    var approx;

    // Fail without a spline shape:
    if (!isSplineShape(spline)) return undefined;    // Failed RShape

    // Requires RSplineProxy, fail without:
    if (!RSpline.hasProxy()) return undefined;    // Failed, noProxy

    // Avoid Null-length:
    orgLength = spline.getLength();
    if (!isNumberGreaterZero(orgLength)) {
        // Return zero area:
        return 0.0;
    }

//debugger;
    // Translate clone to encircle the origin:
    box = spline.getBoundingBox();
    boxCenter = box.getCenter();
    clone = spline.clone();
    clone.move(boxCenter.getNegated());

    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    sTol = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);    // Default =0.01 deviation

    // Approximate the spline with a polyline with arc segments:
    approx = clone.approximateWithArcs(sTol);
    this.hasApprox = true;

    // Auto-close with a line segment, explicit logical closed:
    approx.autoClose(RS.PointTolerance);
    if (!approx.isClosed()) approx.setClosed(true);

    // Return the approximated polyline area:
    return this.getPolylineArea(approx);
};

// Polyline RShapes
/**
 * Polyline RShape enclosed signed area (+CCW, -CW).
 * Auto closed with line segment.
 * Unverified and incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param polyline         A polyline RShape.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolylineArea = function(polyline) {
    var orgLength;
    var polygonA
    var shapes;
    var i, iMax;
    var bulgeA;
    var bulgesA = [];
    var area;

    // Fail without a polyline shape:    RShape based (Includes RSolids and so)
    if (!isPolylineShape(polyline)) return undefined;    // Failed RShape

    // Avoid Null-length:
    orgLength = polyline.getLength();
    if (!isNumberGreaterZero(orgLength)) {
        // Return zero area:
        return 0.0;
    }

    // Reject polylines with widths:
    if (polyline.hasWidths()) {
        this.errMsg = qsTr("Encountered an unsupported polyline with custom widths");
        return undefined;    // Failed, hasWidths
    }

//debugger;
    // Explicit logical closed:
    polyline.autoClose(RS.PointTolerance);
    if (!polyline.isClosed()) polyline.setClosed(true);

    // Get the polygon signed area:
    polygonA = this.getPolygonArea(polyline);
    // Returns signed area or 'undefined'

    // Fail without results:
    if (isNull(polygonA)) return undefined;    // Failed, resNull

    // Sum the bulges total signed area, if any:
    bulgesA = 0
    if (polyline.hasArcSegments()) {
        shapes = polyline.getExploded();
        iMax = shapes.length;
        for (i=0; i<iMax; i++) {    // Cycle all polyline segments
            if (isArcShape(shapes[i])) {
                // Get arc segment area:
                bulgeA = this.getArcSegmentArea(shapes[i]);
                // Returns signed area or 'undefined'

                // Add to list, if any:
                if (!isNull(bulgeA)) {
                    bulgesA.push(bulgeA);
                }
                else {    // Should not occur >
                    debugger;    // ### Catch this In the act !!! ###
                }
            }
        } // Loop segments

        // Add polygon result:    General advice: 'Sum smaller first'
        bulgesA.push(polygonA);

        // Calculate running sums:
        area = this.getRunningSumKBK(bulgesA);

        // Avoid NaN values:
        if (!isNumber(area)) {
            return undefined;    // Failed, NaN
        }

        // Return the polyline total signed area:
         return area;
    }
    else {
        // Return the polygon signed area:
         return polygonA;
    }
};

// Polyline RShapes with line segments
/**
 * Closed or open polyline RShape with line segments enclosed signed area (+CCW, -CW).
 * Auto closed with line segment, elides bulge factors.
 * Unverified and incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param polygon         A polyline RShape.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolygonArea = function(polygon) {
    var orgLength;
    var box, boxCenter;
    var clone;
    var pts, num;
    var j, i;
    var p1, p2;
    var areas = [];
    var area;

    // Fail without a polyline shape:    RShape based (Includes RSolids and so)
    if (!isPolylineShape(polygon)) return undefined;    // Failed RShape

    // Avoid Null-length:
    orgLength = polygon.getLength();
    if (!isNumberGreaterZero(orgLength)) {
        // Return zero area:
        return 0.0;
    }

    // Reject polylines with widths:
    if (polygon.hasWidths()) {
        this.errMsg = qsTr("Encountered an unsupported polygon with custom widths");
        return undefined;    // Failed, hasWidths
    }

//debugger;
    // Explicit logical closed:
    polygon.autoClose(RS.PointTolerance);
    if (!polygon.isClosed()) polygon.setClosed(true);

    // Translate clone to encircle the origin:
    box = polygon.getBoundingBox();
    boxCenter = box.getCenter();
    clone = polygon.clone();
    clone.move(boxCenter.getNegated());

    // Process all nodes (Shoelace algorithm):
    pts = clone.getVertices();
    num = pts.length;
    j = num - 1;    // Refers to last
    for (i=0; i<num; j=i++) {    // Cycle all nodes
        p1 = pts[j];
        p2 = pts[i];
        areas.push(p1.x * p2.y);
        areas.push(-p2.x * p1.y);
    } // Loop nodes

    // Calculate half the running sum:
    area = this.getRunningSumKBK(areas) / 2;

    // Avoid a NaN value:
    if (!isNumber(area)) {
        return undefined;    // Failed, NaN
    }

    // Return the polygon signed area:
    return area;
};

// Circular RShapes excluding circles
/**
 * Arc RShape enclosed signed area (+CCW, -CW).
 * Diversifies between an arc segment or an arc sector.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcArea = function(arc) {
    // Fail without an arc shape:
    if (!isArcShape(arc)) return undefined;    // Failed RShape

//debugger;
    // Diversify return area on the arc mode:
    if (!isNull(this.sectorMode) && this.sectorMode === true) {
        return this.getArcSectorArea(arc);
    }
    else {
        return this.getArcSegmentArea(arc);
    }
};

/**
 * Arc RShape segment enclosed signed area (+CCW, -CW).
 * Not to be confused with an arc shape itself.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSegmentArea = function(arc) {
    var radius, sweep;
    var area;

    // Functional even for Null-length
    // Fail without an arc shape:
    if (!isArcShape(arc)) return undefined;    // Failed RShape

//debugger;
    radius = arc.getRadius();
    sweep = arc.getSweep();

    // Define area, when 2pi or over revert to circle area:
    if (Math.abs(sweep) >= 2*Math.PI) {
        area = radius*radius * Math.PI;    // Unsigned area
        area *= (isNumberGreaterEqualZero(sweep)) ? 1 : -1;
    }
    else {
        // # Issue # Robert S. diversifies in RArc.getChordArea(), getAngleLength is if clause
        area = radius*radius * (sweep - Math.sin(sweep)) / 2;    // Signed area
    }

    // Return the arc segment signed area:
    return area;
};

/**
 * Arc RShape sector enclosed signed area (+CCW, -CW).
 * \author CVH © 2021
 *
 * \param arc         An arc RShape.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSectorArea = function(arc) {
    var radius, sweep;
    var area;

    // Functional even for Null-length
    // Fail without an arc shape:
    if (!isArcShape(arc)) return undefined;    // Failed RShape

//debugger;
    radius = arc.getRadius();
    sweep = arc.getSweep();

    // Define area, when 2pi or over revert to circle area:
    if (Math.abs(sweep) >= 2*Math.PI) {
        area = radius*radius * Math.PI;    // Unsigned area
        area *= (isNumberGreaterEqualZero(sweep)) ? 1 : -1;
    }
    else {
        area = radius*radius * sweep / 2;    // Signed area
    }

    // Return arc sector signed area:
    return area;
};

// Ellipse RShapes
// # Informational # Remark that QCAD doesn't handle minorR equal to zero, a degenerate ellipse
/**
 * Ellipse RShape enclosed (signed) area.
 * Diversifies between a full ellipse (+) or an ellipse arc segment or sector (+CCW, -CW).
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse RShape.
 *
 * \return Unsigned or signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArea = function(ellipse) {
    // Fail without an ellipse shape:
    if (!isEllipseShape(ellipse)) return undefined;    // Failed RShape

//debugger;
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

/**
 * Full ellipse RShape enclosed area (+).
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         A full ellipse RShape.
 *
 * \return Unsigned area or 'undefined'.
 */
InfoAreaCentroid.prototype.getFullEllipseArea = function(ellipse) {
    var major, minor;
    var area;

    // Functional even for Null-length & degenerated
    // Fail without a full ellipse shape:
    if (!isFullEllipseShape(ellipse)) return undefined;    // Failed RShape

//debugger;
    major = ellipse.getMajorRadius();
    minor = ellipse.getMinorRadius();
    area = major * minor * Math.PI;    // Unsigned area

    // Return the full ellipse unsigned area:
    return area;
};

/**
 * Ellipse arc RShape segment enclosed signed area (+CCW, -CW).
 * Not to be confused with an ellipse arc shape itself.
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape.
 *
 * \return Signed area or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSegmentArea = function(ellipse) {
    var major, minor;
    var sweep;
    var area;

    // Functional even for Null-length & degenerated
    // Fail without an ellipse arc shape:
    if (!isEllipseArcShape(ellipse)) return undefined;    // Failed RShape

//debugger;
    major = ellipse.getMajorRadius();
    minor = ellipse.getMinorRadius();
    sweep = ellipse.getSweep();

    // Define area, when 2pi or over revert to full ellipse arc area:
    if (Math.abs(sweep) >= 2*Math.PI) {
        area = major * minor * Math.PI;    // Unsigned area
        area *= (isNumberGreaterEqualZero(sweep)) ? 1 : -1;
    }
    else {
        area = major * minor * (sweep - Math.sin(sweep)) / 2;    // signed area
    }

    // Return the ellipse arc segment signed area:
    return area;
};

/**
 * Ellipse arc RShape sector enclosed signed area (+CCW, -CW).
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape.
 *
 * \return Area or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSectorArea = function(ellipse) {
    var major, minor;
    var sweep;
    var area;

    // Functional even for Null-length & degenerated
    // Fail without an ellipse arc shape:
    if (!isEllipseArcShape(ellipse)) return undefined;    // Failed RShape

//debugger;
    major = ellipse.getMajorRadius();
    minor = ellipse.getMinorRadius();
    sweep = ellipse.getSweep();

    // Define area, when 2pi or over revert to full ellipse arc area:
    if (Math.abs(sweep) >= 2*Math.PI) {
        area = major * minor * Math.PI;    // Unsigned area
        area *= (isNumberGreaterEqualZero(sweep)) ? 1 : -1;
    }
    else {
        area = major * minor * sweep / 2;    // signed area
    }

    // Return the ellipse arc sector signed area:
    return area;
};

// --------------------------------------------------
// Area centroid methods for a uniform density in 2D
// --------------------------------------------------
// Hatch entities
/**
 * Hatched centroid data of a hatch entity, including the differential hatched area (+).
 * Considering a uniform density in 2D.
 * Ifso approximated with polylines given the XP method settings, handled in situ.
 * \author CVH © 2021
 *
 * \param entity         A hatch REntity.
 *
 * \return [centroid.x, centroid.y, centroid, differential area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getHatchedAreaCentroid = function(entity) {
    var boundaries;
    var i, iMax;
    var length;
    var polyC;
    var boundsX = [];
    var boundsY = [];
    var boundsA = [];
    var dX, dY, dArea;
    var centroid;

    // Fail without a hatch entity:
    if (!isHatchEntity(entity)) return undefined;    // Failed REntity

//debugger;
    // Pre-orient hatch boundaries for differential sign:
    boundaries = this.getOrientedHatchBoundaries(entity);
    // Returns at least one pre-oriented boundary or 'undefined'

    // Fail without boundaries:
    if (isNull(boundaries)) return undefined;    // Failed, noBoundaries

    // Process all pre-oriented hatch boundary loops:
    iMax = boundaries.length;
    for (i=0; i<iMax; i++) {    // Cycle all boundary loops
        // Get boundary centroid data:
        polyC = this.getPolylineAreaCentroid(boundaries[i]);
        // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

        // Add to lists, if any:
        if (!isNull(polyC)) {
            boundsX.push(polyC[0] * polyC[3]);
            boundsY.push(polyC[1] * polyC[3]);
            boundsA.push(polyC[3]);
        }
        else {    // Should not occur >
            debugger;    // ### Catch this In the act !!! ###
        }
    } // Loop boundaries

    // Hatch statistics:
    if (boundsA.length > 1) this.isSingleLoop = false;

    // Calculate running sums:
    dX = this.getRunningSumKBK(boundsX);
    dY = this.getRunningSumKBK(boundsY);
    dArea = this.getRunningSumKBK(boundsA);

    // Avoid NaN values:
    if (!isNumber(dX) || !isNumber(dY) || !isNumber(dArea)) {
        return undefined;    // Failed, NaN
    }

    // Avoid and fail when dividing by a zero area:
    if (dArea === 0.0) return undefined;    // Failed, divZero

    // Create differential centroid vector:
    centroid = new RVector(dX / dArea, dY / dArea);

    // Return hatch centroid data:
    return [centroid.x, centroid.y, centroid, dArea];
};

// Contour items
/**
 * Placeholder: Contours of connected items centroid data, including the total enclosed area (+).
 * Considering a uniform density in 2D.
 * As merged polygons + shapes, ifso approximated with polylines given the XP method settings.
 * Incorrect for nested, intersecting or self-intersecting shapes.
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

/**
 * Placeholder: A single contour of connected items centroid data, including the total enclosed area (+).
 * Considering a uniform density in 2D.
 * As merged polygon + shapes, ifso approximated with polylines given the XP method settings.
 * Incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param items         A collection of multiple RShape or REntity.
 *
 * \return [centroid.x, centroid.y, centroid, total area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getContourAreaCentroid = function(items) {
    // # ToDo # Contour of connected items, ifso by approx
    // Verify  isNotNull-Length isNotNull isConnected
    // Merge endpoints to a polyline with line segments to an inner polygon hull
    // Set off situ by box ...?
    // Cycle AreaCentroid methods
    return undefined;
}

// Spline RShapes
/**
 * Spline RShape centroid data, including enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Approximated with an auto closed polyline given XP method tolerance.
 * Unverified and incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param spline         A spline RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getSplineAreaCentroid = function(spline) {
    var orgLength, start;
    var box, boxCenter;
    var clone;
    var sTol;
    var approx;
    var res;
    var centroid;

    // Fail without a spline shape:
    if (!isSplineShape(spline)) return undefined;    // Failed RShape

    // Requires RSplineProxy, fail without:
    if (!RSpline.hasProxy()) return undefined;    // Failed, noProxy

    // Avoid Null-length:
    orgLength = spline.getLength();
    if (!isNumberGreaterZero(orgLength)) {
        start = spline.getStartPoint();
        // Return dummy zero centroid data:
        return [start.x, start.y, start, 0.0];
    }

//debugger;
    // Translate clone to encircle the origin:
    box = spline.getBoundingBox();
    boxCenter = box.getCenter();
    clone = spline.clone();
    clone.move(boxCenter.getNegated());

    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    sTol = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);    // Default =0.01 deviation

    // Approximate the spline with a polyline with arc segments:
    approx = clone.approximateWithArcs(sTol);
    this.hasApprox = true;

    // Reject any self-intersecting shape:
    if (this.isSelfIntersectingPoly(approx)) return undefined;    // Failed, self-intersecting

    // Auto-close with a line segment, explicit logical closed:
    approx.autoClose(RS.PointTolerance);
    if (!approx.isClosed()) approx.setClosed(true);

    // Get the approximated polyline centroid data:
    res = this.getPolylineAreaCentroid(approx);
    // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

    // Fail without results:
    if (isNull(res)) return undefined;    // Failed, resNull

    // Translate result back to the original position:
    centroid = res[2].operator_add(boxCenter);

    // Return the translated polyline centroid data:
    return [centroid.x, centroid.y, centroid, res[3]];
};

// Polyline RShapes
/**
 * Polyline RShape centroid data, including enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Auto closed with line segment.
 * Unverified and incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param polyline         A polyline RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolylineAreaCentroid = function(polyline) {
// Was: InfoPolylineArea.prototype.getCenter() but needed correction
// Was: InfoArea.prototype.getCenter() but needed correction
// https://qcad.org/rsforum/viewtopic.php?p=35084#p35080
// Also see empty InfoArcCircleArea.prototype.getCenter()
    var orgLength, start;
    var polygonC;
    var shapes;
    var i, iMax;
    var bulgeC;
    var bulgesX = [];
    var bulgesY = [];
    var bulgesA = [];
    var x, y, area;
    var centroid;

    // Fail without a polyline shape:    RShape based (Includes RSolids and so)
    if (!isPolylineShape(polyline)) return undefined;    // Failed RShape

    // Avoid Null-length:
    orgLength = polyline.getLength();
    if (!isNumberGreaterZero(orgLength)) {
        start = polyline.getStartPoint();
        // Return dummy zero centroid data:
        return [start.x, start.y, start, 0.0];
    }

    // Reject polylines with widths:
    if (polyline.hasWidths()) {
        this.errMsg = qsTr("Encountered an unsupported polyline with custom widths");
        return undefined;    // Failed, hasWidths
    }

//debugger;
    // Explicit logical closed:
    polyline.autoClose(RS.PointTolerance);
    if (!polyline.isClosed()) polyline.setClosed(true);

    // Get polygon centroid & signed area:
    polygonC = this.getPolygonAreaCentroid(polyline);
    // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

    // Fail without polygon data:
    if (isNull(polygonC)) return undefined;    // Failed, resNull

    // List up bulging centroids & signed areas, if any:
    if (polyline.hasArcSegments()) {
        shapes = polyline.getExploded();
        iMax = shapes.length;
        for (i=0; i<iMax; i++) {    // Cycle all polyline segments
            if (isArcShape(shapes[i])) {
                // Get arc segment centroid data:
                bulgeC = this.getArcSegmentAreaCentroid(shapes[i]);
                // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

                // Add to lists, if any:
                if (!isNull(bulgeC)) {
                    bulgesX.push(bulgeC[0] * bulgeC[3]);
                    bulgesY.push(bulgeC[1] * bulgeC[3]);
                    bulgesA.push(bulgeC[3]);
                }
                else {    // Should not occur >
                    debugger;    // ### Catch this In the act !!! ###
                }
            }
        } // Loop segments    General advice: 'Sum smaller first'

        // Add polygon result:    General advice: 'Sum smaller first'
        bulgesX.push(polygonC[0] * polygonC[3]);
        bulgesY.push(polygonC[1] * polygonC[3]);
        bulgesA.push(polygonC[3]);

        // Calculate running sums:
        x = this.getRunningSumKBK(bulgesX);
        y = this.getRunningSumKBK(bulgesY);
        area = this.getRunningSumKBK(bulgesA);

        // Avoid NaN values:
        if (!isNumber(x) || !isNumber(y) || !isNumber(area)) {
            return undefined;    // Failed, NaN
        }

        // Avoid and fail when dividing by a zero area:
        if (area === 0.0) return undefined;    // Failed, divZero

        // Create overall centroid vector:
        centroid = new RVector(x / area, y / area);
    } // End with arc segments
    else {    // Without arc segments
        // Use polygon centroid vector and area:
        centroid = polygonC[2];
        area  = polygonC[3];
    } // End without arc segments

    // Return the polyline centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

// Polylines RShapes with line segments
/**
 * Closed or open polyline RShape with line segments centroid data, including enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Auto closed with line segment, elides bulge factors.
 * Unverified and incorrect for self-intersecting shapes.
 * \author CVH © 2021
 *
 * \param polygon         A polyline RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getPolygonAreaCentroid = function(polygon) {
    var orgLength, start;
    var box, boxCenter;
    var clone;
    var pts;
    var i, j, iMax;
    var p1, p2;
    var factor;
    var xVals = [];
    var yVals = [];
    var areas = [];
    var x, y, area;
    var centroid;

    // Fail without a polyline shape:    RShape based (Includes RSolids and so)
    if (!isPolylineShape(polygon)) return undefined;    // Failed RShape

    // Avoid Null-length:
    orgLength = polygon.getLength();
    if (!isNumberGreaterZero(orgLength)) {
        start = polygon.getStartPoint();
        // Return dummy zero centroid data:
        return [start.x, start.y, start, 0.0];
    }

    // Reject polylines with widths:
    if (polygon.hasWidths()) {
        this.errMsg = qsTr("Encountered an unsupported polygon with custom widths");
        return undefined;    // Failed, hasWidths
    }

//debugger;
    // Explicit logical closed:
    polygon.autoClose(RS.PointTolerance);
    if (!polygon.isClosed()) polygon.setClosed(true);

    // Translate clone to encircle the origin:
    box = polygon.getBoundingBox();
    boxCenter = box.getCenter();
    clone = polygon.clone();
    clone.move(boxCenter.getNegated());

    // Process all nodes (Shoelace algorithm):
    pts = clone.getVertices();
    iMax = pts.length;
    j = iMax - 1;    // Refers to last
    for (i=0; i<iMax; j=i++) {    // Cycle all nodes
        p1 = pts[j];
        p2 = pts[i];
        factor = p1.x * p2.y - p2.x * p1.y;    // Signed area
        xVals.push((p1.x + p2.x) * factor);
        yVals.push((p1.y + p2.y) * factor);
        areas.push(factor);
    } // Loop nodes

    // Calculate running sums:
    x = this.getRunningSumKBK(xVals);
    y = this.getRunningSumKBK(yVals);
    area = this.getRunningSumKBK(areas);

    // Avoid NaN values:
    if (!isNumber(x) || !isNumber(y) || !isNumber(area)) {
        return undefined;    // Failed, NaN
    }

    // Avoid dividing by a zero area:
    if (area === 0.0) {
        // Diversify specific vector on number of points:
        switch (iMax) {
            case 0:
                centroid = new RVector(0.0 ,0.0);
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
        centroid = new RVector(x / 3 / area, y / 3 / area);
    }

    // Translate result back to the original position:
    centroid.operator_add_assign(boxCenter);

    // Return the polygon centroid data:
    return [centroid.x, centroid.y, centroid, area / 2];
};

// Circular RShapes
/**
 * Arc RShape centroid data, including signed area (+CCW, -CW).
 * Diversifies between an arc segment or an arc sector.
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcAreaCentroid = function(arc) {
    // Functional even for Null-length
    // Fail without an arc shape:
    if (!isArcShape(arc)) return undefined;    // Failed RShape

//debugger;
    // Diversify return area on the arc mode:
    if (!isNull(this.sectorMode) && this.sectorMode) {
        return this.getArcSectorAreaCentroid(arc);
    }
    else {
        return this.getArcSegmentAreaCentroid(arc);
    }
};

/**
 * Circle RShape centroid data, including enclosed area (+).
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param circle         An circle RShape.
 *
 * \return [centroid.x, centroid.y, centroid, unsigned area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getCircleAreaCentroid = function(circle) {
    var centroid;
    var radius;
    var area;

    // Functional even for Null-length
    // Fail without a circle shape:
    if (!isCircleShape(circle)) return undefined;    // Failed RShape

//debugger;
    centroid = circle.getCenter();
    radius = circle.getRadius();
    area = radius*radius * Math.PI;

    // Return the circle centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

/**
 * Arc RShape segment centroid data, including signed area (+CCW, -CW).
 * Not to be confused with an arc shape itself.
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSegmentAreaCentroid = function(arc) {
    var orgLength, centerPoint;
    var sweep, radius;
    var area, factor;
    var magnitude;
    var clone;
    var centroidVector, centroid;

    // Fail without an arc shape:
    if (!isArcShape(arc)) return undefined;    // Failed RShape

    // Avoid Null-length:
    orgLength = arc.getLength();
    centerPoint = arc.getCenter();
    if (!isNumberGreaterZero(orgLength)) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // When 2pi or over revert to circle centroid data:
    sweep = arc.getSweep();
    radius = arc.getRadius();
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return circle centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, radius*radius * Math.PI];
    }

    // Avoid division by zero factor:
    if (sweep === 0.0) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

//debugger;
    // Define factor & signed area:
    factor = sweep - Math.sin(sweep);
    area = radius*radius * factor / 2;

    // Define centroid magnitude:
    magnitude = radius * Math.pow(Math.sin(Math.abs(sweep) / 2), 3) / 3 / Math.abs(factor) * 4;

    // Translate clone to encircle the origin:
    clone = new RArc(new RVector(0.0, 0.0), radius,
                        arc.getStartAngle(),
                        arc.getEndAngle(),
                        arc.isReversed());

    // Create centroid vector:
    centroidVector = clone.getMiddlePoint();
    centroidVector.setMagnitude2D(magnitude);

    // Translate result back to the original position:
    centroid = centroidVector.operator_add(centerPoint);

    // Return the arc segment centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

/**
 * Arc RShape sector centroid data, including signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getArcSectorAreaCentroid = function(arc) {
    var orgLength, centerPoint;
    var halfSweep, radius;
    var area;
    var centroid;
    var magnitude;
    var clone;
    var centroidVector, centroid;

    // Fail without an arc shape:
    if (!isArcShape(arc)) return undefined;    // Failed RShape

    // Avoid Null-length:
    orgLength = arc.getLength();
    centerPoint = arc.getCenter();
    if (!isNumberGreaterZero(orgLength)) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // When 2pi or over revert to circle centroid data:
    halfSweep = arc.getSweep() / 2;
    radius = arc.getRadius();
    if (Math.abs(halfSweep) >= Math.PI) {
        // Return circle centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, radius*radius * Math.PI];
    }

    // Avoid division by zero sweep:
    if (halfSweep === 0.0) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

//debugger;
    // Define signed area:
    area = radius*radius * halfSweep;

    // Define centroid magnitude:
    magnitude = radius * Math.sin(Math.abs(halfSweep)) / 3 / Math.abs(halfSweep) * 2;

    // Translate clone to encircle the origin:
    clone = new RArc(new RVector(0.0, 0.0), radius,
                        arc.getStartAngle(),
                        arc.getEndAngle(),
                        arc.isReversed());

    // Create centroid vector:
    centroidVector = clone.getMiddlePoint();
    centroidVector.setMagnitude2D(magnitude);

    // Translate result back to the original position:
    centroid = centroidVector.operator_add(centerPoint);

    // Merge center with the overall box:
    this.mergeBoxWith(centerPoint);

    // Return the arc sector centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

// Ellipse RShapes
// # Informational # Remark that QCAD doesn't handle minorR equal to zero, a degenerate ellipse
/**
 * Ellipse RShape centroid data, including enclosed (signed) area.
 * Diversifies between a full ellipse (+) or an ellipse arc segment or sector (+CCW, -CW).
 * Considering a uniform density in 2D.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse RShape.
 *
 * \return [centroid.x, centroid.y, centroid, (un)signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseAreaCentroid = function(ellipse) {
    // Fail without an ellipse shape:
    if (!isEllipseShape(ellipse)) return undefined;    // Failed RShape

//debugger;
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

/**
 * Full ellipse RShape centroid data, including enclosed area (+).
 * Considering a uniform density in 2D.
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         A full ellipse RShape.
 *
 * \return [centroid.x, centroid.y, centroid, unsigned area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getFullEllipseAreaCentroid = function(ellipse) {
    var centroid;
    var major, minor;
    var area;

    // Functional even for Null-length & degenerated
    // Fail without a full ellipse shape:
    if (!isFullEllipseShape(ellipse)) return undefined;    // Failed RShape

//debugger;
    centroid = ellipse.getCenter();
    major = ellipse.getMajorRadius();
    minor = ellipse.getMinorRadius();
    area = major * minor * Math.PI;    // Unsigned area

    // Return the full ellipse centroid data:
    return [centroid.x, centroid.y, centroid, area];
};

/**
 * Ellipse arc RShape segment centroid data, including enclosed signed area (+CCW, -CW).
 * Not to be confused with an ellipse arc shape itself.
 * Considering a uniform density in 2D.
 * Approximated with an auto closed polyline given the XP method number of arc segments.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSegmentAreaCentroid = function(ellipse) {
    var orgLength, centerPoint;
    var sweep, major, ratio;
    var area;
    var startParam, endParam;
    var reversed, eAngle;
    var arcShape;
    var res;
    var scaleV;
    var arcCentroidVector;
    var centroid;

    // Fail without an ellipse arc shape:
    if (!isEllipseArcShape(ellipse)) return undefined;    // Failed RShape

    // Avoid Null-length & degenerated:
    orgLength = ellipse.getLength();
    centerPoint = ellipse.getCenter();
    if (!isNumberGreaterZero(orgLength)) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // When 2pi or over revert to full ellipse centroid data:
    sweep = ellipse.getSweep();
    major = ellipse.getMajorRadius();
    ratio = ellipse.getRatio();
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return the full ellipse centroid data:
        area = major * major * ratio * Math.PI;
        return [centerPoint.x, centerPoint.y, centerPoint, area];
    }

//debugger;
    // Retrieve ellipse arc properties:
    startParam = ellipse.getStartParam();
    endParam = ellipse.getEndParam();
    reversed  = ellipse.isReversed();
    eAngle = ellipse.getAngle();

    // Handle it transformed to an arc shape as segment:
    // Start and end parameter are arcs resulting from transforming the ellipse into a circle
    arcShape = new RArc(centerPoint, major, startParam, endParam, reversed);
    res = this.getArcSegmentAreaCentroid(arcShape);
    // Returns [centroid.x, centroid.y, centroid, area] or 'undefined'

    // Fail without result:
    if (isNull(res)) return undefined;    // Failed, resNull

    // Transform the result back:
    scaleV = new RVector(1, ratio);
    arcCentroidVector = res[2].operator_subtract(centerPoint);
    arcCentroidVector.scale(scaleV);
    arcCentroidVector.rotate(eAngle);
    centroid = arcCentroidVector.operator_add(centerPoint);

    // Retrieve closed format area value:
    area = this.getEllipseArcSegmentArea(ellipse);
    // Returns signed area or 'undefined'

    // Fail without result:
    if (isNull(area)) return undefined;    // Failed, resNull

    // Return the ellipse arc segment centroid data:
    return [centroid.x, centroid.y, centroid, area]
};

/**
 * Ellipse arc RShape sector centroid data including, enclosed signed area (+CCW, -CW).
 * Considering a uniform density in 2D.
 * Closed format equation.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse arc RShape.
 *
 * \return [centroid.x, centroid.y, centroid, signed area] or 'undefined'.
 */
InfoAreaCentroid.prototype.getEllipseArcSectorAreaCentroid = function(ellipse) {
    var orgLength, centerPoint;
    var sweep, major, ratio;
    var area;
    var startParam, endParam;
    var reversed, eAngle;
    var arcShape;
    var res;
    var scaleV;
    var arcCentroidVector;
    var centroid;

    // Fail without an ellipse arc shape:
    if (!isEllipseArcShape(ellipse)) return undefined;    // Failed RShape

    // Avoid Null-length & degenerated:
    orgLength = ellipse.getLength();
    centerPoint = ellipse.getCenter();
    if (!isNumberGreaterZero(orgLength)) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // When 2pi or over revert to full ellipse centroid data:
    sweep = ellipse.getSweep();
    major = ellipse.getMajorRadius();
    ratio = ellipse.getRatio();
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return the full ellipse centroid data:
        area = major * major * ratio * Math.PI;
        return [centerPoint.x, centerPoint.y, centerPoint, area];
    }

//debugger;
    // Retrieve ellipse arc properties:
    startParam = ellipse.getStartParam();
    endParam = ellipse.getEndParam();
    reversed  = ellipse.isReversed();
    eAngle = ellipse.getAngle();

    // Handle it transformed to an arc shape as sector:
    // Start and end parameter are arcs resulting from transforming the ellipse into a circle
    arcShape = new RArc(centerPoint, major, startParam, endParam, reversed);
    res = this.getArcSectorAreaCentroid(arcShape);
    // Returns [centroid.x, centroid.y, centroid, area] or 'undefined'

    // Fail without result:
    if (isNull(res)) return undefined;    // Failed, resNull

    // Transform the result back:
    scaleV = new RVector(1, ratio);
    arcCentroidVector = res[2].operator_subtract(centerPoint);
    arcCentroidVector.scale(scaleV);
    arcCentroidVector.rotate(eAngle);
    centroid = arcCentroidVector.operator_add(centerPoint);

    // Retrieve closed format area value:
    area = this.getEllipseArcSectorArea(ellipse);
    // Returns signed area or 'undefined'

    // Fail without result:
    if (isNull(area)) return undefined;    // Failed, resNull

    // Merge center with the overall box:
    this.mergeBoxWith(centerPoint);

    // Return the ellipse arc centroid data:
    return [centroid.x, centroid.y, centroid, area]
};

// ==================================================

/** 
 * Diversifies uniform density area centroids supported entity type or -1 when not supported.
 * REntity based (Excludes RSolids and so).
 */
InfoAreaCentroid.prototype.getSupportedAreaCentroidType = function(entity) {
    var ret = -1;    // Default, not supported

//debugger;
    // Diversify on entity type:
    if (isArcEntity(entity)) {
        ret = 1;    // As arc segment or sector, autoClosed with a line
    }
    else if (isCircleEntity(entity)) {
        ret = 2;    // As circle
    }
    else if (isEllipseEntity(entity)) {
        ret = 3;    // Full or as arc segment or sector, autoClosed with a line
    }
    else if (isPolylineEntity(entity)) {
        ret = 4;    // With or without arc segments, autoClosed with a line
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
 * Pre-oriented hatch boundary loops as polylines with line and arc segments.
 * Is hatched = CCW = positive area
 * Is voided = CW = negative area
 * # Issue Unsolved # Can't guarantee how correct RShapes from boundaries are merged.
 * \author CVH © 2021
 *
 * \param hatch         A hatch REntity.
 *
 * \return A list (>=1) of pre-oriented boundary loops as polylines or 'undefined'.
 */
InfoAreaCentroid.prototype.getOrientedHatchBoundaries = function(hatch) {
    var hatchData;
    var boundaries;
    var i, j, iMax;
    var boundary;
    var nesting, isOddNested;
    var trialPoint, trial;
    var orientation;

    // Fail without a hatch entity:
    if (!isHatchEntity(hatch)) return undefined;    // Failed REntity
    hatchData = hatch.getData();

//debugger;
    // Retrieve boundary loops:
    // boundaries = hatchData.getBoundaryAsPolylines(0);    // Line segment length
    // # Issue Solved # .getBoundaryAsPolylines(val) interpolates curved shapes with line segments
    // Crashes QCAD with 0 or -1 for 'no interpolation'. Solved with a custom script
    boundaries = this.getHatchPolyLoops(hatchData);
    // Returns a list of boundary loops as polylines with line and arc segments, can be empty.

    iMax = boundaries.length;
    // Fail without at least one boundary:
    if (iMax < 1) return undefined;    // Failed, noBoundaries

    // # Informational # Hatch boundaries should/will not intersect, self-intersect, can touch, ...
    // # Informational # Common is the use of counting crossings of a ray from a point inside the closed contour.

//debugger;
    // Process all hatch boundaries for their nested nature:
    for (i=0; i<iMax; i++) {    // A) Cycle all boundaries
        boundary = boundaries[i];

        // Define odd or even nested vs all other boundaries except itself:
        nesting = 0;
        trialPoint = boundary.getStartPoint();
        for (j=0; j<iMax; j++) {    // Cycle all boundaries except itself
            if (i === j) continue;    // Skip itself
            trial = boundaries[j];

            // Verify if the boundary is nested inside the one on trial:
            // A) Excludes box based not even close:
            if (!trial.getBoundingBox().contains(boundary.getBoundingBox())) {
                continue;    // Is not nested
            }
            // B) Verify if a random vertex is inside the trial boundary.
            if (trial.contains(trialPoint, true, RS.PointTolerance)) {
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
        // A) Merge outer boundary loops their box with the overall box:
        if (nesting === 0) {
            this.mergeBoxWith(boundary.getBoundingBox());
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
 * # Unsolvable # Can't guarantee how correct RShapes from boundaries are merged.
 * \author CVH © 2021
 *
 * \param hatchData         A hatch RHatchData.
 *
 * \return A list of boundary loops as polylines, can be empty.
 */
InfoAreaCentroid.prototype.getHatchPolyLoops = function(hatchData) {
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
                // # Bug Fixed # Circles are initially stored as circles until saved/reloaded
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
                // Requires RSplineProxy, fail without:
                if (!RSpline.hasProxy()) return [];    // Failed, noProxy

                // Append RShapes from spline approximation:
                sTol = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);    // Default =0.01 deviation
                approx = shape.approximateWithArcs(sTol);
                this.hasApprox = true;
                polyShapes = polyShapes.concat(approx.getExploded());
            }
            else if (isEllipseShape(shape)) {
                // Requires REllipseProxy, fail without:
                if (!REllipse.hasProxy()) return [];    // Failed, noProxy

                // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
                // # Issue Unsolved # ->fullEllipseArcs<- Is a size relative accuracy
                eSegs = RSettings.getIntValue("Explode/EllipseSegments", 32);    // Default =32 arc segments/full ellipse
                //  # Issue Fixed # Here not less than 1,024 would be advised
                if (eSegs < 1024) eSegs = 1024;
                // Append RShapes from ellipse approximation:
                approx = shape.approximateWithArcs(eSegs);
                this.hasApprox = true;
                polyShapes = polyShapes.concat(approx.getExploded());
            }
            else {
                // # ToDo # Possible incomplete, warn immediately
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
 * Verifies if the given open/closed polyline shape is self-intersecting.
 * Specific for area methods including an autoClose line segment.
 * \author CVH © 2021
 *
 * \param shape         A polyline RShape.
 *
 * \return True or false, assumed false when not a polyline RShape.
 */
InfoAreaCentroid.prototype.isSelfIntersectingPoly = function(shape) {
    var ips = [];
    var line;
    var ipsLine;

    // Fail without a polyline shape, assume not intersecting:    RShape based (Includes RSolids and so)
    if (!isPolylineShape(shape)) return false;    // Failed RShape

    // # Issue Solved # Polyline tolerance patch issued on Jun 17, 2021
    //    Prior version 3.26.4.5, without tolerance
    // # Issue Solved # Spline tolerance patch issued on Nov 15, 2021
    //    Not intended for all self-intersections
    // # Solutions # Beta version 0.32 requires Framework 3.27, splines as approximated polylines

//debugger;
    // Get self-intersection points, diversify on arc segments:
    if (shape.hasArcSegments()) {   // With line/arc segments >
        // # Issue Fixed # No good test on self-intersecting bulging polylines
        // See: https://qcad.org/rsforum/viewtopic.php?t=8526
        // Setting something less strict than the connect tolerance 1.0e-3 (RPolyline.appendShape)
        ips = shape.getSelfIntersectionPoints(1.1e-3);
    }
    else {   // With line segments >
        // # Issue Fixed # Test on polylines with line segment:
        // - Returns a single intersection point where segments are crossing and
        //    4 equal intersection points where nodes coexists
        // - # Issue # Odd extra ending as intersection point when a node is on an other segment,
        //    unrelated to CW/CCW or tolerance ... position in the plane ...
        //    See: https://qcad.org/bugtracker/index.php?do=details&task_id=2302
        // - # Issue # May still return self-intersections points that are nearly nodes
        //    e.g. Open spline example approximated with arcs, tolerance 0.001,
        //    transformed into an open polygon by forcing bulging factors to zero:
        //    - 1e-9 >>> 112 (near?) nodes (=Default RS.PointTolerance)
        //    - 1e-8 >>> 1 near node "RVector(2167.413312, 2742.600518, 0.000000, 1)"
        //      Or better: Reported intersection of 2 consecutive line segments is off by 3.9015270069336183e-7 from the node itself
        //    - 1e-7 >>> no intersection reported
        ips = shape.getSelfIntersectionPoints(1e-6);
    }

    // Additional intersections with closing line shape:
    if (!shape.isGeometricallyClosed(RS.PointTolerance)) {
        line = new RLine(shape.getEndPoint(), shape.getStartPoint());
        ipsLine = line.getIntersectionPoints(getPtr(shape));
        // With more intersections than endpoints add the second point found, one will do:
        if (ipsLine.length > 2) ips.push(ipsLine[1]);
    }

    // Warn user about self-intersection:
    if (isNumberGreaterZero(ips.length)) {
        this.errMsg = qsTr("Self-intersecting shape near (%1). No Results.").arg(coordinateToString(ips[0]));
    }

    // Return the self-intersecting nature:
    return (ips.length > 0);
};

