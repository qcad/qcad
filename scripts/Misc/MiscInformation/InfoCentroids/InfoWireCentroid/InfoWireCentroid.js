/**0.31b
 * InfoWireCentroid Beta version 0.32 (As MiscInformation)
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

// # ToDo # Should we clear long or vast arrays? shift() out or splice(0, 1) out?

/**
 * \class InfoWireCentroid
 * \brief This action adds a wire 2D Centroid marker and text labels for a selection.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoWireCentroid(guiAction) {
    InfoCentroids.call(this, guiAction);
};

// Deriving our class from the base class:
InfoWireCentroid.prototype = new InfoCentroids();
InfoWireCentroid.includeBasePath = includeBasePath;

/**
 * This GUI action adds a 2D Centroid marker and detail labels for selected entities.
 * Calculates overall centroid position and total length assuming a uniform density wire.
 * Casts additional details as text labels and reports them on the Command History.
 * Stores full floating point data as marker custom properties.
 * 2D Centroid markers are generated with a default density of 1.00 per unit.
 * Supports single or multiple selected entities:
 *    - Line entity.
 *    - Arc entity.
 *    - Circle entity.
 *    - Ellipse entity, full or approximated as ellipse arc.
 *    - Polyline entity.
 *    - Spline entity as approximated polyline.
 * Not interpolating with line segments, the methods sum lengths and centroids by shapes.
 *
 * Included are various methods for wire 2D Centroids of RShapes.
 */
// BeginEvent handler:
InfoWireCentroid.prototype.beginEvent = function() {
    InfoCentroids.prototype.beginEvent.call(this);

    // Presets:
    this.massMode = false;
    this.wireMode = true;

    // Call the wire centroid for a selection main loop:
    this.selectionsWireCentroid(this.getDocumentInterface());

    // # Issue Fixed # Button toggles between usage, fixed with releasing
    this.getGuiAction().setChecked(false);

    // Terminate beginEvent:
    this.terminate();
    return;
};

/** Main WireCentroid
 * Main InfoWireCentroid loop.
 * A uniform wire should not be confused with a bended bar or hollow pipe for that matter.
 * Can be a good 'better than nothing' approximation with a curved nature.
 * \author CVH © 2021
 *
 * \param di         A document interface.
 *
 * \return Nothing. Casts 2D Centroid marker and text labels, reports on Command History.
 */
InfoWireCentroid.prototype.selectionsWireCentroid = function(di) {
    var doc = di.getDocument();
    var i, ids, idn;
    var msg, txt;
    var entity, entityShape;
    var type;
    var res;
    var shapesX = [];
    var shapesY = [];
    var shapesL = [];
    var x, y, length;
    var centroid, dataC;
    var op;
    var dimStyle;
    var shift;
    var markerSize;
    var decPnt, lstSep;
    var dimLinPrec, dimTrZeros;
    var offset;
    var transaction;

    // Retrieve document selection, fail on none:
    // # ToDo # Add states for none & pointing inside a closed contour
    ids = doc.querySelectedEntities();
    idn = ids.length;
    if (idn === 0) {    // Double lock, action requires selection
        // Abort here:
        EAction.handleUserWarning(qsTr("No selection."));
        EAction.handleUserInfo(qsTr("Please, make a selection first. Command terminated."));
        return undefined;    // Failed selection
    }

    // Additional Command History script notification:
    EAction.handleUserMessage(qsTr("Wire 2D Centroid script (v0.32) by CVH"));

    // Initial values:
    this.hasApprox = false;
    this.isSingular = (idn === 1);
    this.boxSize = undefined;
    this.errMsg = undefined;
    msg = qsTr("Length:");

//debugger;
    // Process all selected entities:
    for (i=0; i<idn; i++) {    // Cycle selected entities
        // Retrieve the selected entity:
        entity = doc.queryEntity(ids[i]);

        // Get the supported type:
        type = this.getSupportedWireCentroidType(entity);    // REntity based (Excludes RSolids and so)
        // Returns supported entity type or -1

        // As 2D RShape when supported:
        if (type > 0) {
            entityShape = entity.castToShape().clone();
            entityShape.to2D();
        }

//debugger;
        // Diversify on type:
        switch (type) {
            case 1:    // isArcEntity
                res = this.getArcWireCentroid(entityShape); // Diversifies
                break;
            case 2:    // isCircleEntity
                // Reject old style marker circles:
                if (!isNull(entity.getCustomProperty("QCAD", InfoCentroids.Terms.Title, undefined))) {
                    // Abort critical:
                    EAction.handleUserWarning(qsTr("2D Centroid markers circle in selection. No results."));
                    return undefined;    // Failed, isMarker
                }
                res = this.getCircleWireCentroid(entityShape);
                break;
            case 3:    // isEllipseEntity
                res = this.getEllipseWireCentroid(entityShape); // Diversifies
                if (this.hasApprox) msg = qsTr("Approximated length:");
                break;
            case 4:    // isPolylineEntity
                res = this.getPolylineWireCentroid(entityShape);
                break;
            case 5:    // isSplineEntity
                res = this.getSplineWireCentroid(entityShape);
                msg = qsTr("Approximated length:");
                break;
            case 6:    // isLineEntity
                res = this.getLineWireCentroid(entityShape);
                break;
            default:    // isUnsupported
                // Abort critical:
                EAction.handleUserWarning(qsTr("Unsupported entity type. No results."));
                return undefined;    // Failed type
                break;
        } // End switch type

        // Add to lists, if any:
        if (!isNull(res)) {
            shapesX.push(res[0] * res[3]);
            shapesY.push(res[1] * res[3]);
            shapesL.push(res[3]);
            // Merge box with the overall box:
            this.mergeBoxWith(entityShape.getBoundingBox());
        }
        else {
            // Abort critical:
            if (isNull(this.errMsg)) this.errMsg = qsTr("No results.");
            EAction.handleUserWarning(this.errMsg);
            return undefined;    // Failed, resNull
        }

    } // Loop selected

    // Calculate running sums:
    x = this.getRunningSumKBK(shapesX);
    y = this.getRunningSumKBK(shapesY);
    length = this.getRunningSumKBK(shapesL);

    // Avoid NaN values:
    if (!isNumber(x) || !isNumber(y) || !isNumber(length)) {
        return undefined;    // Failed, NaN
    }

    // Avoid division by a zero length, abort critical:
    if (length === 0.0) {
        EAction.handleUserWarning(qsTr("Results in a division by zero."));
        debugger;    // ### Catch this In the act !!! ###
        return undefined;    // Failed, divZero
    }

    // Create overall centroid vector and data:
    centroid = new RVector(x / length, y / length);
    dataC = [centroid.x, centroid.y, centroid, length];

//debugger;
    // Initiate an operation:
    op = new RAddObjectOperation();
    // Set tool title used for undo/redo information:
    op.setText(qsTr("2D wire Centroid"));

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
    this.addCentroidMarker(doc, op, dataC, markerSize);

    // Use drawing decPnt/lstSep/precision:
    // # Known Issue # Will not work prior QCAD 3.26.4
    decPnt = String.fromCharCode(dimStyle.getInt(RS.DIMDSEP));    // charCode 32/44/46
    dimLinPrec = dimStyle.getInt(RS.DIMDEC);          // Integer value
    dimTrZeros = dimStyle.getInt(RS.DIMZIN) === 0;    // Show decimal trailing zeros: 0=Yes 8=No
    // # Issue Fixed # Undefined drawing list separator, use common sense
    lstSep = (decPnt === ",") ? ";" : ",";    // Default =comma

    // Adapt to not singular nature:
    if (!this.isSingular) msg = qsTr("Total length:")

    // Include absolute length label:
    txt = msg + " " + this.formatLabelValue(Math.abs(length), decPnt, dimLinPrec, dimTrZeros);
    if (!this.isSingular && this.hasApprox) txt += " " + qsTr("(Incl. approximations)");
    offset = new RVector(markerSize + shift, markerSize + shift);
    this.addTextLabel(doc, op, centroid, offset, txt);

    // Report absolute length:
    txt = msg + this.formatCmdValue(Math.abs(length));
    if (!this.isSingular && this.hasApprox) txt += " " + qsTr("(Incl. approximations)");
    EAction.handleUserInfo(txt);

    // Diversify on approximated nature:
    msg = (this.hasApprox) ? qsTr("Approximated centroid:") : qsTr("Centroid:");

    // Include centroid position label:
    txt = msg + " (" + this.formatLabelValue(centroid.x, decPnt, dimLinPrec, dimTrZeros);
    txt += lstSep + " " + this.formatLabelValue(centroid.y, decPnt, dimLinPrec, dimTrZeros) + ")";
    offset = new RVector(markerSize + shift, shift - markerSize);
    this.addTextLabel(doc, op, centroid, offset, txt);

    // Report centroid position:
    msg += this.formatCoordinate(centroid.x, centroid.y);
    EAction.handleUserInfo(msg);

    // Set relative zero and apply all operations:
    di.setRelativeZero(res[2]);
    transaction = di.applyOperation(op);

    // Advance selection to marker:
    this.advanceSelection(di, transaction);

    // Return to terminate:
    return true;
};

// -----------------------------------------------------
// Centroid methods for a wire of uniform density in 2D
// -----------------------------------------------------

// Spline RShapes ... Length differs a lot with QCAD getLength()
/**
 * Spline RShape centroid data, including length (+).
 * Considering a wire of uniform density.
 * Approximated with a polyline given the XP method tolerance.
 * \author CVH © 2021
 *
 * \param spline         A spline RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getSplineWireCentroid = function(spline) {
    var orgLength, start;
    var box, boxCenter;
    var clone;
    var sTol;
    var approx;
    var res;
    var centroid;

    // Fail without a spline entity or a spline shape:
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

    // Get the approximated polyline centroid data:
    res = this.getPolylineWireCentroid(approx);
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
 * Polyline RShape centroid data, including length (+).
 * Considering a wire of uniform density.
 * \author CVH © 2021
 *
 * \param polyline         A polyline RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getPolylineWireCentroid = function(polyline) {
    var orgLength, start;
    var box, boxCenter;
    var clone;
    var shapes, shape;
    var i, iMax;
    var shapeC;
    var shapesX = [];
    var shapesY = [];
    var shapesL = [];
    var x, y, length;
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
    // Translate clone to encircle the origin:
    box = polyline.getBoundingBox();
    boxCenter = box.getCenter();
    clone = polyline.clone();
    clone.move(boxCenter.getNegated());

    // Process all exploded shapes:
    shapes = clone.getExploded();
    iMax = shapes.length;
    for (i=0; i<iMax; i++) {    // Cycle all polyline segments
        shape = shapes[i];
        // Diversify on RShape:
        if (isLineShape(shape)) {
            // Get line segment centroid data:
            shapeC = this.getLineWireCentroid(shape);
            // Returns [centroid.x, centroid.y, centroid, length] or 'undefined'
        }
        else if (isArcShape(shape)){
            // Get arc segment centroid data:
            shapeC = this.getArcWireCentroid(shape);
            // Returns [centroid.x, centroid.y, centroid, length] or 'undefined'
        }
        else {    // Should not occur >
            shapeC = undefined;
            debugger;    // ### Catch this In the act !!! ###
        }

        // Add to lists, if any:
        if (!isNull(shapeC)) {
            shapesX.push(shapeC[0] * shapeC[3]);
            shapesY.push(shapeC[1] * shapeC[3]);
            shapesL.push(shapeC[3]);
        }
        else {    // Should not occur >
            debugger;    // ### Catch this In the act !!! ###
        }
    } // Loop segments

    // Calculate running sums:
    x = this.getRunningSumKBK(shapesX);
    y = this.getRunningSumKBK(shapesY);
    length = this.getRunningSumKBK(shapesL);

if (!RMath.fuzzyCompare(length, orgLength)) debugger; // ### Catch this In the act !!! ###

    // Avoid NaN values:
    if (!isNumber(x) || !isNumber(y) || !isNumber(length)) {
        return undefined;    // Failed, NaN
    }

    // Avoid and fail when dividing by a zero length:
    if (length === 0.0) return undefined;    // Failed, divZero

    // Create overall centroid vector:
    centroid = new RVector(x / length, y / length);

    // Translate result back to the original position:
    centroid.operator_add_assign(boxCenter);

    // Return the polyline centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

// Polyline RShapes with line segments
/**
 * Closed or open polyline RShape with line segments centroid data, including length (+).
 * Considering a wire of uniform density.
 * \author CVH © 2021
 *
 * \param polygon         A polyline RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getPolygonWireCentroid = function(polygon) {
    var orgLength, start;
    var box, boxCenter;
    var clone;
    var shapes, shape;
    var i, iMax;
    var lineC;
    var linesX = [];
    var linesY = [];
    var linesL = [];
    var midPoint;
    var x, y, length;
    var centroid;

    // Fail without a polyline shape:    RShape based (includes RSolids and so)
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
    // Translate clone to encircle the origin:
    box = polygon.getBoundingBox();
    boxCenter = box.getCenter();
    clone = polygon.clone();
    clone.move(boxCenter.getNegated());

    // Process all line shapes from exploded shapes:
    shapes = clone.getExploded();
    iMax = shapes.length;
    for (i=0; i<iMax; i++) {    // Cycle all polyline segments
        shape = shapes[i];
        // Diversify on RShape:
        if (isLineShape(shape)) {
            // Get line segment centroid data:
            lineC = this.getLineWireCentroid(shape);
            // Returns [centroid.x, centroid.y, centroid, length] or 'undefined'

            // Add to lists, if any:
            if (!isNull(lineC)) {
                linesX.push(lineC[0] * lineC[3]);
                linesY.push(lineC[1] * lineC[3]);
                linesL.push(lineC[3]);
            }
            else {    // Should not occur >
                debugger;    // ### Catch this In the act !!! ###
            }
        }
        else if (isArcShape(shape)) {
            midPoint = getAverage(clone.getVertexAt(i), clone.getVertexAt(i+1));
            length = clone.getVertexAt(i).getDistanceTo2D(clone.getVertexAt(i+1));

            // Add to lists, if any:
            if (isNumberGreaterZero(length) && isValidVector(midPoint)) {
                linesX.push(midPoint.x * length);
                linesY.push(midPoint.y * length);
                linesL.push(length);
            }
            else {    // Should not occur >
                debugger;    // ### Catch this In the act !!! ###
            }
        }
        else {    // Should not occur >
            debugger;    // ### Catch this In the act !!! ###
        }
    } // Loop segments

    // Calculate running sums:
    x = this.getRunningSumKBK(linesX);
    y = this.getRunningSumKBK(linesY);
    length = this.getRunningSumKBK(linesL);

if (!RMath.fuzzyCompare(length, orgLength)) debugger;    // ### Catch this In the act !!! ###

    // Avoid NaN values:
    if (!isNumber(x) || !isNumber(y) || !isNumber(length)) {
        return undefined;    // Failed, NaN
    }

    // Avoid and fail when dividing by a zero length:
    if (length === 0.0) return undefined;    // Failed, divZero

    // Create overall centroid vector:
    centroid = new RVector(x / length, y / length);

    // Translate result back to the original position:
    centroid.operator_add_assign(boxCenter);

    // Return the polygon centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

// Line RShapes
/**
 * Line segment RShape centroid data, including length (+).
 * Considering a wire of uniform density.
 * Excluding Rays and Xlines
 * \author CVH © 2021
 *
 * \param line         A line RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getLineWireCentroid = function(line) {
    var length;
    var midPoint;

    // Functional even for Null-length
    // Fail without a line shape:
    if (!isLineShape(line)) return undefined;    // Failed RShape

//debugger;
    length = line.getLength();
    midPoint = line.getMiddlePoint();

    // Return the line segment centroid data:
    return [midPoint.x, midPoint.y, midPoint, length];
};

// Circular RShapes
/** OK closed format  Called by Main
 * Circle RShape centroid data, including length (+).
 * Considering a wire of uniform density.
 * \author CVH © 2021
 *
 * \param circle         An circle RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getCircleWireCentroid = function(circle) {
    var centroid;
    var length;

    // Functional even for Null-length
    // Fail without a circle shape:
    if (!isCircleShape(circle)) return undefined;    // Failed RShape

//debugger;
    centroid = circle.getCenter();
    length = circle.getLength();

    // Return the circle centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

/**
 * Arc RShape centroid data, including length (+).
 * Considering a wire of uniform density.
 * \author CVH © 2021
 *
 * \param arc         An arc RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getArcWireCentroid = function(arc) {
    var orgLength, centerPoint;
    var halfSweep, radius;
    var length;
    var magnitude;
    var midPoint;
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
        length = radius * Math.PI * 2;
        // Return circle centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, length];
    }

    // Avoid division by zero sweep:
    if (halfSweep === 0.0) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

//debugger;
    // Define centroid magnitude:
    magnitude = radius * Math.sin(halfSweep) / halfSweep;

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
    return [centroid.x, centroid.y, centroid, orgLength];
};

// Ellipse RShapes
// # Informational # Remark that QCAD doesn't handle minorR equal to zero, a degenerate ellipse
/**
 * Ellipse RShape centroid data, including length (+).
 * Diversifies between a full ellipse or an ellipse arc.
 * Considering a wire of uniform density.
 * Ifso, approximated with a polyline given the XP method number of arc segments.
 * \author CVH © 2021
 *
 * \param ellipse         An ellipse RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getEllipseWireCentroid = function(ellipse) {
    // Fail without an ellipse shape:
    if (!isEllipseShape(ellipse)) return undefined;    // Failed RShape

//debugger;
    // Diversify return centroid data on the closed nature:
    if (ellipse.isFullEllipse()) {
        return this.getFullEllipseWireCentroid(ellipse);
    }
    else {
        return this.getEllipseArcWireCentroid(ellipse);
    }
};

/**
 * Full ellipse RShape centroid data, including circumference (+).
 * Considering a wire of uniform density.
 * Centroid closed format equation, nearly exact circumference by infinite series expansion.
 * \author CVH © 2021
 *
 * \param ellipse         A full ellipse RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getFullEllipseWireCentroid = function(ellipse) {
    var orgLength, centroid;
    var major, minor;
    var ratio;
    var length;

    // Functional even for degenerated
    // Fail without a full ellipse shape:
    if (!isFullEllipseShape(ellipse)) return undefined;    // Failed RShape

    // Avoid Null-length & degenerated:
    orgLength = ellipse.getLength();
    centroid = ellipse.getCenter();
    if (!isNumberGreaterZero(orgLength)) {
        // Return center zero centroid data:
        return [centroid.x, centroid.y, centroid, 0.0];
    }

//debugger;
    major = ellipse.getMajorRadius();
    minor = ellipse.getMinorRadius();
    ratio = ellipse.getRatio();

// The Simpson approximation used by QCAD is rather good for common ellipses
// but found incorrect for elongated or flat shapes.
// Approximations tend to have an error related with the eccentricity.
// --------------------------------------------
 var circum_QCAD_S = orgLength;
// --------------------------------------------
// var circum___Flat= 4 * major;
// var circum__Round = 2 * major * Math.PI;

// Srinivasa Ramanujan second close approximations up to h^5
// See: https://en.wikipedia.org/wiki/Ellipse
// Evaluated to be within -0.04%
// --------------------------------------------
var h = Math.pow(major - minor, 2) / Math.pow(major + minor, 2);
var circumRaman_2 = Math.PI * (major + minor) * (1 + 3 * h / (10 + Math.sqrt(4 - 3 * h)));
// --------------------------------------------

// Cantrell-Ramanujan approximation adds pi(a+b)(4/pi-14/11)h^12
// Evaluated to be within 14.5ppm
// Fine alternative for QCAD ellipse.getLength() with a full ellipse
// Here circumRamanC is the result and ..CP & ..CM are the maximum 14.5ppm limits
// --------------------------------------------
var corr = Math.PI * (major + minor) * (4 / Math.PI - 14 / 11) * Math.pow(h, 12);
var circumRaman_C = circumRaman_2 + corr;
var circumRamanCM = circumRaman_C * 0.9999855;
var circumRamanCP = circumRaman_C * 1.0000145;
// --------------------------------------------

// A well used approximation method in many programs mentioned by Chris Rackauckas:
// pi(a+b)(135168-85760h-5568h²+3687h³)/(135168-119552h-22208h²+345h³)
// http://www.chrisrackauckas.com/assets/Papers/ChrisRackauckas-The_Circumference_of_an_Ellipse.pdf

// For equations approximating to within 151.6ppb refer to:
// http://www.ebyte.it/library/docs/math07/EllipsePerimeterApprox07.html

// Implemented two distinct infinite series expansions that converge within 20 terms.
// Each specialized for a ratio towards zero or upwards to a ratio of 1.

// --------------------------------------------
// var circumISC__20 = this.getFullEllipseCircumISC(major, minor, 20);
// var circumISGK_20 = this.getFullEllipseCircumISGK(major, minor, 20);
// --------------------------------------------
//debugger;


    // Diversify on ratio:
    // Threshold 0.35 (TR Chandrupatla, TJ Osler) what differs from the advised 28% or 25%
    if (ratio <= 0.35) {    // When rather elongated >
        length = this.getFullEllipseCircumISC(major, minor, 20);
    }
    else {    // When rather round >
        length = this.getFullEllipseCircumISGK(major, minor, 20);
    }

    // Fail without a number:
    if (!isNumber(length)) return undefined;    // Failed, noNumber

    // ### Catch these In the act !!! ###
    // Simpson length fails 14.5ppm:
    if (circum_QCAD_S < circumRamanCM || circum_QCAD_S > circumRamanCP) debugger;
    // Both series expansion fail 14.5ppm:
    if (length < circumRamanCM || length > circumRamanCP) debugger;
    // ### Catch these In the act !!! ###

    // Return the full ellipse centroid data:
    return [centroid.x, centroid.y, centroid, length];
};

/**
 * Ellipse arc RShape centroid data, including length (+).
 * Considering a wire of uniform density.
 * Approximated with a polyline given the XP method number of arc segments, at least 4096.
 * \author CVH © 2021
 *
 * \param ellipse         A spline RShape.
 *
 * \return [centroid.x, centroid.y, centroid, length] or 'undefined'.
 */
InfoWireCentroid.prototype.getEllipseArcWireCentroid = function(ellipse) {
    var orgLength, centerPoint;
    var sweep;
    var clone;
    var eSegs;
    var approx;
    var res;
    var centroid;

    // # Informational # Requires elliptic integrals or series expansion
    // Nor can an arcWireCentroid be transformed to an ellipseArc,
    // Nor is the QCAD Simpson getLength perfect

    // We could look at this as the nearly exact circumference of a full ellipse by series expansion
    // minus an integrated form 0° to the begin angle
    // minus an integrated value from 360° down to the end angle
    // Even add full 1/4 ellipse fractions

    // Fail without an ellipse arc shape:
    if (!isEllipseArcShape(ellipse)) return undefined;    // Failed RShape

    // Requires REllipseProxy, fail without:
    if (!REllipse.hasProxy()) return undefined;    // Failed, noProxy

    // Avoid Null-length & degenerated:
    orgLength = ellipse.getLength();
    centerPoint = ellipse.getCenter();
    if (!isNumberGreaterZero(orgLength)) {
        // Return center zero centroid data:
        return [centerPoint.x, centerPoint.y, centerPoint, 0.0];
    }

    // When 2pi or over revert to full ellipse centroid data:
    sweep = ellipse.getSweep();
    if (Math.abs(sweep) >= 2*Math.PI) {
        // Return the full ellipse centroid data by infinite series:
        return this.getFullEllipseWireCentroid(ellipse);
    }

//debugger;
    // Translate clone to encircle the origin:
    clone = ellipse.clone();
    clone.move(centerPoint.getNegated());

    // Retrieve approximation tolerances of the Explode method (XP), if any, or use defaults:
    // # Issue Unsolved # ->fullEllipseArcs<- Is a size relative accuracy
    eSegs = RSettings.getIntValue("Explode/EllipseSegments", 32);    // Default =32 arc segments/full ellipse
    //  # Issue Fixed # Here 4,096 ... 65,536 would be advised, not less and too high may degenerate the result
    if (eSegs < 4096) eSegs = 4096;
    // Approximate the ellipse with a polyline with arc segments:
    approx = clone.approximateWithArcs(eSegs);
    this.hasApprox = true;

    // Get the approximated polyline centroid data:
    res = this.getPolylineWireCentroid(approx);
    // Returns [centroid.x, centroid.y, centroid, signed area] or 'undefined'

    // Fail without results:
    if (isNull(res)) return undefined;    // Failed, resNull

    // Translate result back to the original position:
    centroid = res[2].operator_add(centerPoint);

    // Return the translated polyline centroid data:
    return [centroid.x, centroid.y, centroid, res[3]];
};

/**
 * Full ellipse circumference (+) by series expansion, best suited for elongated ellipses.
 * Fast converging exact infinite series expansion for a given number of terms.
 * Also known as the 'Cayley's series expansion'.
 * The first term is 4 times the major radius for a degenerated ellipse.
 * Optimal used for ratio <= 0.35 within 20 terms, halts on converging numerical.
 * \author CVH © 2021
 *
 * \param a            Full ellipse major radius.
 * \param b            Full ellipse minor radius.
 * \param terms        Limit expansion to n terms. (4<=n<=20)
 *
 * \return Unsigned circumference or 'NaN'.
 */
InfoWireCentroid.prototype.getFullEllipseCircumISC = function (a, b, terms) {
    var ratio, sqrRatio;
    var t1, t2;
    var factor, oldFactor;
    var a1, a2;
    var s1, s2;
    var i;

    // Infinite series expansion:
    // C = 4a times a factor from which the ratio can not easily be isolated
    // See: http://numericana.com/answer/ellipse.htm#cayley

    // Fail without numbers:
    if (!isNumber(a) || !isNumber(b) || !isNumber(terms)) return Number.NaN;

//debugger;
    // Fail on radii not greater than zero:
    if (a < 0 || b < 0) return Number.NaN;

    // Swap radii when required:
    if (b > a) return this.getFullEllipseCircumISC(b, a, terms);

    // Degenerated ellipse:
    if (a > 0.0 && b === 0.0) return 4 * a;    // A line back and forth

    // Null-length:
    if (a === 0.0 && b === 0.0) return 0.0;

    // Circular ellipse:
    if (a === b) return a * b * Math.PI;    // A circle

    // Limit to at least 4 terms:
    if (terms < 4) terms = 4;
    // Limit to at most 20 terms:
    if (terms > 20) terms = 20;

    // First + second term:
    ratio = b / a;
    sqrRatio = ratio * ratio;
    t1 = sqrRatio / 2;
    t2 = Math.log(4 / ratio) - 0.5;    // log based e =ln()
    factor = 1 + t1 * t2;

//var reply = 4 * a;
//EAction.handleUserMessage(reply.toPrecision(21).replace(".", ","));
//var reply = 4 * a * factor;
//EAction.handleUserMessage(reply.toPrecision(21).replace(".", ","));

    a1 = 1;
    a2 = 2;
    s1 = a1 / a2;
    s2 = 1 / a1 / a2;

    // Further terms until best precision attained:
    // See note on running sum in reference
    for (i=2; i<terms; i++) {    // Cycle further terms
        t1 *= s1;
        t2 -= s2;
        a1 += 2;
        a2 += 2;
        s1 = a1 / a2;
        s2 = 1 / a1 / a2;
        t1 *= sqrRatio * s1;
        t2 -= s2;

        oldFactor = factor;
        factor += t1 * t2;

//var reply = 4 * a * factor;
//EAction.handleUserMessage(reply.toPrecision(21).replace(".", ","));

        if (factor === oldFactor) break;    // Maximum precision attained
    } // Loop terms

    // Return factor times 4a:
    return 4 * a * factor
};

/**
 * Full ellipse circumference (+) by series expansion, best suited for round ellipses.
 * Exact infinite series expansion for a given number of terms.
 * Also known as the 'Gauss-Kummer series expansion'.
 * The first term is 2piR for a circular ellipse.
 * Optimized with a list of factors, one for each expansion term.
 * Optimal used for ratio > 0.35 within 20 terms.
 * \author CVH © 2021
 *
 * \param a            Full ellipse major radius.
 * \param b            Full ellipse minor radius.
 * \param terms        Limit expansion to n terms. (4<=n<=20)
 *
 * \return Unsigned circumference or 'NaN'.
 */
InfoWireCentroid.prototype.getFullEllipseCircumISGK = function (a, b, terms) {
    var base;
    var h;
    var i;
    var term;
    var sum = 0;

    // Infinite series expansion:
    // C = pi*(a+b)(1 + h/4 + h²/64 + h³/256 + ...)
    // Where: h = ((a-b)/(a+b))², terms in power n (0-infinite), 1/denominator = f(n)=((2n-3)!!/(2^n*n!))²
    // See: https://en.wikipedia.org/wiki/Ellipse#Circumference
    // See: http://numericana.com/answer/ellipse.htm#gausskummer
    // What can be simplified with a list of term factors (21) for 1/denominator.
    var termFactors =
        [1, 0.25, 0.015625, 0.00390625, 0.00152587890625, 0.0007476806640625,
        4.2057037353515625e-4, 2.5963783264160156e-4, 1.7140153795480728e-4,
        1.190288458019495e-4, 8.599834109190851e-5, 6.414339077309704e-5,
        4.910978356065243e-5, 3.8430585064475045e-5, 3.06366271241032e-5,
        2.481566797052359e-5, 2.0380836682822596e-5, 1.6942892778713254e-5,
        1.423673629322433e-5, 1.2077563683656365e-5, 1.0333865426828481e-5];

    // Fail without numbers:
    if (!isNumber(a) || !isNumber(b) || !isNumber(terms)) return Number.NaN;

//debugger;
    // Fail on radii not equal or greater than zero:
    if (a < 0 || b < 0) return Number.NaN;

    // Swap radii when required:
    if (b > a) return this.getFullEllipseCircumISGK(b, a, terms);

    // Degenerated ellipse:
    if (a > 0.0 && b === 0.0) return 4 * a;    // A line back and forth

    // Null-length:
    if (a === 0.0 && b === 0.0) return 0.0;

    // Circular ellipse:
    if (a === b) return a * b * Math.PI;    // A circle

    // Limit to at least 4 terms:
    if (terms < 4) terms = 4;
    // Limit to at most 20 terms:
    if (terms > 20) terms = 20;

    base = Math.PI * (a + b);
    h = Math.pow((a - b) / (a + b), 2);

    // Sum terms of the infinite series expansion:
    // General advice: 'Sum smaller first', both h^n & denominator(n) decrease with n
    for (i=terms; i>0; i--) {    // Cycle terms in reversed order
    //  Made factorials obsolete with a list of factors per term
    //  term = base * Math.pow(h, i) * Math.pow(getDoubleFactorial(2 * i - 3) / Math.pow(2, i) / getFactorial(i) , 2);
        term = base * Math.pow(h, i) * termFactors[i];
        sum += term;
    } // Loop terms

//var reply = base + sum;
//EAction.handleUserMessage(reply.toPrecision(21).replace(".", ","));

    // Return pi(a+b) and the sum of the terms:
    return base + sum;
};

// ==================================================

/**
 * Diversifies uniform density wire centroids supported entity type or -1 when not supported.
 * REntity based (Excludes RSolids and so).
 */
InfoWireCentroid.prototype.getSupportedWireCentroidType = function(entity) {
    var ret = -1;    // Default, not supported

//debugger;
    // Diversify on entity type:
    if (isArcEntity(entity)) {
        ret = 1;    // As arc segment or sector
    }
    else if (isCircleEntity(entity)) {
        ret = 2;    // As circle
    }
    else if (isEllipseEntity(entity)) {
        ret = 3;    // Full or as arc segment or sector
    }
    else if (isPolylineEntity(entity)) {
        ret = 4;    // With or without arc segments
    }
    else if (isSplineEntity(entity)) {
        ret = 5;     // Approximated
    }
    else if (isLineEntity(entity)) {
        ret = 6;    // As line, excluding Rays and XLines
    }

    // Return type:
    return ret;
};

/**
 * Returning the factorial of an integer value.
 * See: https://en.wikipedia.org/wiki/Factorial
 */
// Made obsolete here
/* List of the first 23 values for n
[1,1,2,6,24,120,720,5040,40320,362880,3628800,
  39916800,479001600,6227020800,87178291200,
  1307674368000,20922789888000,355687428096000,
  6402373705728000,121645100408832000,
  2432902008176640000,51090942171709440000,
  1124000727777607680000]
*/
/*getFactorial = function (n) {
    var product = 1;

    // Fail without numbers:
    if (!isNumber(n)) return Number.NaN;

    // limit return:
    if (n < 1) return 1;

    // As integer:
    n = Math.floor(n)

    for (var i=n; i>1; i--) {    // Cycle integers
        product *= i;
    } // Loop integers

    return product;
};
*/

/**
 * Returning the double factorial of an integer value.
 * See: https://en.wikipedia.org/wiki/Double_factorial
 */
// Made obsolete here
/* List of the first 20 values for even n including 0
[1,2,8,48,384,3840,46080,645120,10321920,
  185794560,3715891200,81749606400,1961990553600,
  51011754393600,1428329123020800,42849873690624000,
  1371195958099968000,46620662575398912000,
  1678343852714360832000,63777066403145711616000]
*/
/* List of the first 20 values for uneven n
[1, 1, 3, 15, 105, 945, 10395, 135135, 2027025,
  34459425, 654729075, 13749310575, 316234143225,
  7905853580625, 213458046676875, 6190283353629375,
  191898783962510625, 6332659870762850625,
  221643095476699771875, 8200794532637891559375]
 */
/*getDoubleFactorial = function (n) {
    var product = 1

    // Fail without numbers:
    if (!isNumber(n)) return Number.NaN;

    // limit return:
    if (n < 1) return 1;

    // As integer:
    n = Math.floor(n)

    for (n; n>1; n-=2) {    // Cycle integers
        product *= n;
    } // Loop integers

    return product;
};
*/

