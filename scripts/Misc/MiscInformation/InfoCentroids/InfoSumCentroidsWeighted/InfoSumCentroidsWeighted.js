/**Beta 0.24
 * InfoSumCentroidsWeighted Beta version 0.24 (As MiscInformationCentroids)
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

// # Optional # Casting a marker and text labels. Can't also be summed!

/**
 * \class InfoSumCentroidsWeighted
 * \ingroup ecma_misc_information_centroids
 * \brief This action makes the weighted sum of selected 2D Centroid markers.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoSumCentroidsWeighted(guiAction) {
    InfoCentroids.call(this, guiAction);
};

// Deriving our class from the base class:
InfoSumCentroidsWeighted.prototype = new InfoCentroids();
InfoSumCentroidsWeighted.includeBasePath = includeBasePath;

/**
 * This GUI action sums selected 2D Centroid markers weighted by their individual point mass.
 * For area and wire centroids the mass is related to a given custom density.
 * Version 0.24 report on the Command History.
 */
// BeginEvent handler:
InfoSumCentroidsWeighted.prototype.beginEvent = function() {
    InfoCentroids.prototype.beginEvent.call(this);

    // Presets:
    this.massMode = true;
    this.wireMode = false;

    // Call main loop:
    this.sumSelectedCentroids(this.getDocumentInterface());

    // # Issue Fixed # Button toggles between usage, fixed with releasing
    this.getGuiAction().setChecked(false);

    // Terminate beginEvent:
    this.terminate();
    return;
};

/**
 * Main InfoSumCentroidsWeighted loop.
 * \author CVH © 2021
 *
 * \param di         A document interface.
 *
 * \return Nothing. Reports on Command History.
 */
InfoSumCentroidsWeighted.prototype.sumSelectedCentroids = function(di) {
    var doc = di.getDocument();
    var terms = InfoCentroids.Terms;
    var i, ids, idn;
    var entity;
    var type, tFirst, isMixed;
    var anyError;
    var density, mass, weight, X, Y;
    var hasUndefVal;
    var count;
    var dFirst, isUniform;
    var xVals, yVals, mVals, wVals, rVals;
    var msg;
    var centroidX, centroidY, centroidM;
    var op;
    var dataC;
    var markerSize;
    var transaction;

//debugger;
    // Retrieve document selection, fail on none:
    ids = doc.querySelectedEntities();
    idn = ids.length;
    if (idn === 0) {    // Double lock, action requires selection
        EAction.handleUserWarning(qsTr("No selection."));
        EAction.handleUserInfo(qsTr("Please, make a selection first. Command terminated."));
        return;    // Failed selection
    }

    // Additional Command History script notification:
    EAction.handleUserMessage(qsTr("2D Centroids weighted sum script (v0.24) by CVH."));

    // Initial values:
    hasUndefVal = false;
    count = 0;
    isUniform = true;
    isMixed = false;
    xVals = [];
    yVals = [];
    wVals = [];
    mVals = [];
    rVals = [];

    // Process all selected entities:
    for (i=0; i<idn; i++) {    // Cycle selected entities
        // Retrieve the selected entity:
        entity = doc.queryEntity(ids[i]);

        // Exclude anything except polylines:
        if (!isPolylineEntity(entity)) {
            continue;    // Never a centroid marker entity, skip to next selected
        }

        // Exclude anything except 2D Centroid markers:
        type = entity.getCustomProperty("QCAD", terms.Title, undefined)
        if (isNull(type)) {
            continue;    // Not a centroid marker polyline, skip to next selected
        }

        // Retrieve centroid other custom properties:
        density = entity.getCustomProperty("QCAD", terms.Density, undefined);
        mass = entity.getCustomProperty("QCAD", terms.PointMass, undefined);
        weight = entity.getCustomProperty("QCAD", terms.Weighted, undefined);
        X = entity.getCustomProperty("QCAD", terms.PositionX, undefined);
        Y = entity.getCustomProperty("QCAD", terms.PositionY, undefined);

        // Validate coordinates:
        if (isNull(X) || isNull(Y)) {
            anyError = qsTr("Encountered a missing coordinate value.");
            break;    // Failed, stop cycling
        }
        X = parseFloat(X.replace(/\,/g, "."));
        Y = parseFloat(Y.replace(/\,/g, "."));
        if (!isNumber(X) || !isNumber(Y)) {
            anyError = qsTr("Encountered an invalid coordinate value.");
            break;    // Failed, stop cycling
        }
        // -> Continue with valid coordinates

        // Validate point mass or density/weighted pair:
        if (type === terms.PointMass) {    // With a point mass >
            if (isNull(mass)) {
                anyError = qsTr("Encountered a missing \'%1\' value.").arg(terms.PointMass);
                break;    // Failed, stop cycling
            }
            mass = RMath.eval(mass.replace(/\,/g, "."));
            if (!isNumber(mass)) {
                anyError = qsTr("Encountered an invalid \'%1\' value.").arg(terms.PointMass);
                break;    // Failed, stop cycling
            }
        } // End point mass related
        else if (type === terms.Area || type === terms.Wire) {   // When area/wire related >
            if (isNull(weight)) {
                anyError = qsTr("Encountered a missing \'%1\' value.").arg(terms.Weighted);
                break;    // Failed, stop cycling
            }
            weight = parseFloat(weight.replace(/\,/g, "."));
            if (!isNumber(weight)) {
                anyError = qsTr("Encountered an invalid \'%1\' value.").arg(terms.Weighted);
                break;    // Failed, stop cycling
            }

            if (isNull(density)) {
                anyError = qsTr("Encountered a missing \'%1\' value.").arg(terms.Density);
                break;    // Failed, stop cycling
            }

            // Revert to unity value when density is literal 'Undefined':
            if (density === terms.Undefined) {
                density = "1.0";
                hasUndefVal= true;
            }

            density = RMath.eval(density.replace(/\,/g, "."));
            if (!isNumber(density)) {
                anyError = qsTr("Encountered an invalid \'%1\' value.").arg(terms.Density);
                break;    // Failed, stop cycling
            }

            // Define point mass:
            mass = weight * density;
        } // End area/wire related
        else {   // With unknown type >
            anyError = qsTr("Encountered an unknown marker type.");
            break;    // Failed, stop cycling
        }
        // -> Continue with valid coordinates & valid mass

        // Collect radii, account for old style markers:
        rVals.push(entity.getBoundingBox().getWidth() / 2);

        // Verify for uniform density & equal type:
        if (count === 0) {    // With the first component
            // Preserve first values:
            dFirst = density;
            tFirst = type;
        } // End with first
        else {    // With successive components
            // Compare with first values:
            if (density !== dFirst) isUniform = false;
            if (type !== tFirst) isMixed = true;
        } // End with successive

        // If any, list up all weighted values of the first type:
        if (!isMixed && !isNull(weight)) wVals.push(weight);

        // List up properties weighted:
        xVals.push(X * mass);
        yVals.push(Y * mass);
        mVals.push(mass);
        count++;
    } // Loop selected

//debugger;
    // If any, fail on returned error:
    if (!isNull(anyError)) {
        EAction.handleUserWarning(anyError + " " + qsTr("No result."));
        return;    // Failed
    }

    // Fail without anything to sum:
    if (count === 0) {
        msg = qsTr("No 2D Centroid markers found in the selection.");
        EAction.handleUserWarning(msg);
        return;    // Failed
    }
    // -> Continue with at least one data point

    // Report the mass of a single data point:
    if (count === 1) {    // With 1 data point >
        msg = qsTr("Single marker selected, point mass = %1").arg(this.formatCmdValue(mVals[0]));
        // If any, specify undefined densities:
        if (hasUndefVal) msg += " - " + qsTr("Density is undefined") + " (=1.0)";
        EAction.handleUserInfo(msg);
        return;    // Done, return to terminate
    } // End 1 data point
    // Try to sum multiple components weighted:
    else {    // With more data points >
        centroidM = this.getRunningSumKBK(mVals);

        // Avoid division by zero, abort critical:
        if (centroidM === 0.0) {
            EAction.handleUserWarning(qsTr("Results in a division by zero."));
            debugger;    // ### Catch this In the act !!! ###
            return;    // Failed, divZero
        }

        centroidX = this.getRunningSumKBK(xVals) / centroidM;
        centroidY = this.getRunningSumKBK(yVals) / centroidM;
    } // End more data points

    // Avoid NaN values, abort critical:
    if (!isNumber(centroidM) || !isNumber(centroidX) || !isNumber(centroidY)) {
        EAction.handleUserWarning(qsTr("Results in a NaN value."));
        debugger;    // ### Catch this In the act !!! ###
        return;    // Failed, NaN
    }

    // Initiate an operation:
    op = new RAddObjectOperation();
    // Set tool title used for undo/redo information:
    op.setText(qsTr("Combined 2D Centroid"));

//debugger;
    // Create a centroid data set:
    dataC = [centroidX, centroidY, new RVector(centroidX, centroidY), centroidM];

    // Include centroid marker proportional to the combined components:
    // Equals the largest size summed with 1/3 of the average size of the others components
    rVals.sort(function(a, b) {return b - a});
    markerSize = rVals.shift() + this.getRunningSumKBK(rVals) / rVals.length / 3;
    this.addCentroidMarker(doc, op, dataC, markerSize);

    // Report total/combined sum (+/-):
    msg = (isUniform) ?
                qsTr("Combined uniform point mass (%1):").arg(count) :
                qsTr("Combined point mass (%1):").arg(count);

    msg += this.formatCmdValue(centroidM);
    // If any, specify undefined densities:
    if (hasUndefVal) {
        if (isUniform) {
            msg += " - " + qsTr("All densities are undefined") + " (=1.0)";
        }
        else {
            msg += " - " + qsTr("Some densities are undefined") + " (=1.0)";
        }
    }
    EAction.handleUserInfo(msg);

    // When not mixed report overall weighted property human readable:
    if (!isMixed && wVals.length > 0) {
        msg = "Combined" + " ";
        if (type === terms.Area) msg += qsTr("area (Informational):");
        if (type === terms.Wire) msg += qsTr("wire length (Informational):");
        msg += this.formatCmdValue(this.getRunningSumKBK(wVals));
        EAction.handleUserInfo(msg);
    }

    // Report overall centroid position:
    msg = qsTr("Combined centroid:");
    msg += this.formatCoordinate(centroidX, centroidY);
    EAction.handleUserInfo(msg);

    // Set relative zero and apply all operations:
    di.setRelativeZero(dataC[2]);
    transaction = di.applyOperation(op);

    // Advance selection to marker:
    this.advanceSelection(di, transaction);

    // Return to terminate:
    return;
};

