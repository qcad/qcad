/**
 * InfoSumCentroidsWeighted Beta version 0.11 (As MiscInformation)
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
 * \ingroup ecma_misc_information
 * \brief This action sums centroid markers details weighted.
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
 * This GUI action sums selected centroid markers weighted by their individual custom density.
 * Centroid markers are generated with default density of 1.00 per unit.
 * Report on the Command History.
 */
// BeginEvent handler:
InfoSumCentroidsWeighted.prototype.beginEvent = function() {
    InfoCentroids.prototype.beginEvent.call(this);

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
    var i, ids, idn;
    var xVals, yVals, wdVals;
    var count;
    var entity;
    var density, X, Y, weight;
    var wd, dFirst;
    var isUniform;
    var centroidX, centroidY, centroidW;
    var decPnt, lstSep;
    var msg;

//debugger;
    // Retrieve document selection, fail on none:
    ids = doc.querySelectedEntities();
    idn = ids.length;
    if (idn === 0) {    // Action requires selection
        EAction.handleUserWarning(qsTr("No selection."));
        EAction.handleUserInfo(qsTr("Please, make a selection first. Command terminated."));
        return;    // Failed selection
    }

    // Additional Command History script notification:
    EAction.handleUserMessage(qsTr("Centroids weighted sum script (v0.10b) by CVH"));

    // Initial values:
    xVals = [];
    yVals = [];
    wdVals = [];
    dFirst = 0.0;
    isUniform = true;
    count = 0;

    for (i=0; i<idn; i++) {    // Cycle selected entities
        // Retrieve the selected entity:
        entity = doc.queryEntity(ids[i]);

        if (isNull(entity.getCustomProperty("QCAD", qsTr("2D Centroid"), undefined))) {
            continue;    // Not a marker entity, skip to next selected
        }

        // Verify that it is not a marker circle:
        density = entity.getCustomProperty("QCAD", qsTr("Density"), undefined);
        if (isNull(density)) {
            continue;    // A marker circle entity, skip to next selected
        }

        // Retrieve further centroid data from custom properties:
        X = entity.getCustomProperty("QCAD", qsTr("X position"), "0.0");
        Y = entity.getCustomProperty("QCAD", qsTr("Y position"), "0.0");
        weight = entity.getCustomProperty("QCAD", qsTr("Weighted"), "0.0");

        // Convert to numbers:
        density = parseFloat(density.replace(",","."));
        X = parseFloat(X.replace(",","."));
        Y = parseFloat(Y.replace(",","."));
        weight = parseFloat(weight.replace(",","."));

        // List weighted if all are numbers:
        if (isNumber(density + X + Y + weight)) {
            wd = density * weight;
            // Verify for uniform density:
            if (count === 0) dFirst = density;
            if (density !== dFirst) isUniform = false;

            // List up when it has a weighted mass:
            // # Bug Fixed # Don't mind sign
            if (wd !== 0.0) {
                // List values up:
                xVals.push(X * wd);
                yVals.push(Y * wd);
                wdVals.push(wd);
                count++;
            }
        }
        else {
            debugger;    // ### Catch this In the act !!! ###
        }
    }

    // Fail without anything to sum else sum collected data:
    if (count < 2) {
        if (count === 0) {
            msg = qsTr("No centroid markers in selection.");
        }
        else {
            msg = qsTr("One marker selected, nothing to sum. Please verify selection.");
        }
        EAction.handleUserWarning(msg);
        return; 
    }
    else {
        centroidW = this.getRunningSumKBK(wdVals);
        // Avoid dividing by zero:
        if (centroidW === 0.0) {
            EAction.handleUserWarning(qsTr("Results in Zero."));
            debugger;    // ### Catch this In the act !!! ###
            return;    // Failed, divZero
        }

        centroidX = this.getRunningSumKBK(xVals) / centroidW;
        centroidY = this.getRunningSumKBK(yVals) / centroidW;
    }

    // Use application decPnt/lstSep & precision or 17 significant:
    decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");    // Default =dot
    lstSep = RSettings.getStringValue("Input/CartesianCoordinateSeparator", ",");    // Default =comma
    // # ToDo # Use application precision
    // # Issue # Can't locate an appLinPerc

    // Report total/weighted sum (+/-):
    msg = (isUniform) ? qsTr("Total sum(%1):").arg(count) : qsTr("Weighted sum(%1):").arg(count);
    msg += " " + centroidW.toPrecision(17).replace(".", decPnt);
    EAction.handleUserInfo(msg);

    // Report overall centroid position:
    msg = qsTr("Summed centroid position:");
    msg += " (" + centroidX.toPrecision(17).replace(".", decPnt);
    msg += lstSep + " " + centroidY.toPrecision(17).replace(".", decPnt);
    msg += ")"
    EAction.handleUserInfo(msg);

    // Return to terminate:
    return;
};

