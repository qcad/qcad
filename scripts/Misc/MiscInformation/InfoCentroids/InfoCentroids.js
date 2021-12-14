/**Beta 0.32
 * InfoCentroids Beta version 0.32 (As MiscInformation)
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

/**
 * \defgroup ecma_misc_information_centroids 2D Centroids Scripts
 * \ingroup ecma_misc_information
 *
 * \brief This module contains 2D Centroids related ECMAScript.
 */

include("scripts/Misc/MiscInformation/MiscInformation.js");

/**
 * \class InfoCentroids
 * \ingroup ecma_misc_information
 * \brief Base class for all 2D Centroid tools.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoCentroids(guiAction) {
    MiscInformation.call(this, guiAction);
};

// Common translations:
InfoCentroids.Terms = {
    Title : qsTr("2D Centroid"),
    PointMass : qsTr("Point mass"),
    Area : qsTr("Area"),
    Wire : qsTr("Wire"),
    Density : qsTr("Density"),
    Weighted : qsTr("Weighted"),
    PositionX : qsTr("X position"),
    PositionY : qsTr("Y position"),
    Undefined : qsTr("Undefined")
}

// Deriving our class from the base class:
InfoCentroids.prototype = new MiscInformation();
InfoCentroids.includeBasePath = includeBasePath;

// BeginEvent handler:
InfoCentroids.prototype.beginEvent = function() {
    MiscInformation.prototype.beginEvent.call(this);
};

/**
 * Sums values in an array by 'A generalized Kahan–Babuška-Summation-Algorithm' proposed by Klein.
 * Running sums may have a poor accuracy due to loss of significance.
 * Somewhat slower than the naive approach and it requires arrays of many (tiny) values.
 * Advantages here are: Single loop trough and second-order compensation.
 * Usable for long (unsorted) lists of arbitrary values.
 * \author CVH © 2021
 *
 * \param list         A list of values.
 *
 * \return The sum of the values or NaN when not an array of all numbers.
 */
InfoCentroids.prototype.getRunningSumKBK = function (list) {
    var i, iMax;
    var tulple;
    var t;
    var sum = 0.0;
    var cs  = 0.0;
    var ccs = 0.0;
    var c   = 0.0;
    var cc  = 0.0;

    // Fail without a list:
    if (isNull(list) || list.length === 0) return Number.NaN;    // Failed as list

//debugger;
    // Naively for 1 or 2 values:
    iMax = list.length;

    if (iMax === 1) return list[0];
    if (iMax === 2) return list[0] + list[1];

    // Second-order 'iterative Kahan–Babuška algorithm':
    // See: https://en.wikipedia.org/wiki/Kahan_summation_algorithm
    for (i=0; i<iMax; i++) {    // Cycle all values
        tulple = list[i];

        t = sum + tulple;

        if (Math.abs(sum) >= Math.abs(tulple)) {
            c = (sum - t) + tulple;
        }
        else {
            c = (tulple - t) + sum;
        }

        sum = t;
        t = cs + c;

        if (Math.abs(cs) >= Math.abs(c)) {
            cc = (cs - t) + c;
        }
        else {
            cc = (c - t) + cs;
        }

        cs = t;
        ccs = ccs + cc;
    } // Loop values

    // Return the final sum:
    return cs + ccs + sum;    // General advice: 'Sum smaller first'
};

/**
 * Accumulate a given item to an overall box size.
 * \author CVH © 2021
 *
 * \param item         An RBox or an RVector to include.
 *
 * \return Nothing. Overall box in this.boxSize is adapted.
 */
InfoCentroids.prototype.mergeBoxWith = function(item) {

//debugger;
    if (isNull(this.boxSize)) {
        // The first item to be added should be an RBox
        if (isOfType(item, RBox)) {
            // Use box as first:
            this.boxSize = item;
        }
    }
    else {
        if (isOfType(item, RBox)) {
            // Include box:
            this.boxSize.growToIncludeBox(item);
        }
        else if (isValidVector(item)) {
            // Include point:
            this.boxSize.growToIncludePoint(item);
        }
    }
    return;
};

/**
 * Adding text labels to a given operation.
 * \author CVH © 2021
 *
 * \param doc           Reference to the current document.
 * \param op            Given operation to add the text label entity.
 * \param pos           Marker position.
 * \param offset        Offset vector to the marker position.
 * \param text          Label text.
 *
 * \return Nothing, text label is added to the operation.
 */
InfoCentroids.prototype.addTextLabel = function(doc, op, pos, offset, text) {
    var infoColor;
    var textData;
    var textEntity;

    // Retrieve info color:    Default =pale green
    infoColor = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));

//debugger;
    // Create new text data object:
    textData = new RTextData();
    textData.setAlignmentPoint(new RVector(pos.x + offset.x, pos.y + offset.y));
    textData.setVAlign(RS.VAlignTop);
    textData.setHAlign(RS.HAlignLeft);
    textData.setFontName(this.docDimFont);
    textData.setTextHeight(this.fontSize);
    textData.setText(text);

    // Create new document entity:
    textEntity = new RTextEntity(doc, textData);
    textEntity.setColor(infoColor);

    // Add to given operation:
    op.addObject(textEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
};

/**
 * Adding 2D Centroid marker to a given operation.
 * Supports: 2D point mass, 2D area Centroid and 2D wire Centroid
 * Type depends on booleans this.massMode & this.wireMode
 * \author CVH © 2021
 *
 * \param doc              Reference to the current document.
 * \param op               Given operation to add the marker entity.
 * \param dataC            Centroid data [x, y, position, weight]
 *    (A value to weigh with, not to be mistaken by its mass for area/wire types)
 * \param radius           Marker size.
 * \param (preview)        Optional: Preview mode, true/=false.
 *
 * \return Nothing, marker is added to the operation.
 */
InfoCentroids.prototype.addCentroidMarker = function(doc, op, dataC, radius, preview) {
    var infoColor;
    var quaterC, bulges, widths;
    var step;
    var pts;
    var poly, polyData, polyEntity;
    var terms;
    var type;
    var mass;

    // Retrieve info color::    Default =pale green
    infoColor = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));

//debugger;
    quaterC = 0.4142135623730950488;    // bulge = sqrt(2)-1
    bulges = [1.0, 0.0, quaterC, 0.0, -quaterC,  0.0, -1.0];
    // # Known Issue # Circle sector is not rendered correct by QCAD with Width = 2R
    // Fixed with adding 1%, functional for 2R>=0.03 units
    // See: https://qcad.org/rsforum/viewtopic.php?t=7889&p=30877#p30803
    // See: https://www.ribbonsoft.com/bugtracker/index.php?do=details&task_id=2155
    var radiusFix = radius * 1.01;
    widths = [0.0, 0.0, radiusFix, 0.0, radiusFix, 0.0, 0.0];
    step = radius / 2;
    pts = [new RVector(dataC[0] - radius, dataC[1]),
            new RVector(dataC[0] + radius, dataC[1]),
            new RVector(dataC[0] + step, dataC[1]),
            new RVector(dataC[0], dataC[1] + step),
            new RVector(dataC[0], dataC[1] - step),
            new RVector(dataC[0] - step, dataC[1]),
            new RVector(dataC[0] - radius, dataC[1]),
            new RVector(dataC[0] + radius, dataC[1])];

    // Create new centroid marker polyline shape:
    poly = new RPolyline(pts, false);    // notClosed
    poly.setBulges(bulges);
    poly.setStartWidths(widths);
    poly.setEndWidths(widths);
    polyData = new RPolylineData(poly);

    // Create new polyline entity:
    polyEntity = new RPolylineEntity(doc, polyData);
    polyEntity.setColor(infoColor);

    // Add custom properties except in preview mode (InfoAddCustomCentroid):
    if (isNull(preview) || preview === false) {
        terms = InfoCentroids.Terms;

        // Ifso, use mass mode:
        if (this.massMode === true) {
            type = terms.PointMass;
        }
        // Otherwise use area/wire mode:
        else {
            // Revert to defaults when missing:
            if (isNull(this.wireMode)) this.wireMode = false;
            type = (this.wireMode === false) ? terms.Area : terms.Wire;
        }

        // Set marker common custom properties, use application decPnt & full precision:
        polyEntity.setCustomProperty("QCAD", terms.Title, type);
        polyEntity.setCustomProperty("QCAD", terms.PositionX, this.formatPropValue(dataC[0]));
        polyEntity.setCustomProperty("QCAD", terms.PositionY, this.formatPropValue(dataC[1]));

        // Set marker point mass custom property:
        mass = terms.Undefined;
        if (this.massMode) {    // From a mass mode >
            // Store value or valid equation:
            if (isNumber(dataC[3])) {    // When a number >
                mass = this.formatPropValue(dataC[3]);
            } // End with number
            else if (!isNull(dataC[3])) {    // When not a number nor undefined >
                // Use an equation when valid:
                if (isNumber(RMath.eval(dataC[3].replace(/\,/g, ".")))) {
                    // Store equation literal:
                    mass = dataC[3];
                }
            } // End with NaN
        } // End mass mode
        else {    // From Area/wire mode >
            // Density is 'Undefined' and considered as 1.0 ... 1xWeighted = Weighted
            mass = this.formatPropValue(dataC[3]);
        } // End modes
        polyEntity.setCustomProperty("QCAD", terms.PointMass, mass);

        // Set additional properties for area/wire Centroids:
        if (!this.massMode) {
            polyEntity.setCustomProperty("QCAD", terms.Weighted, this.formatPropValue(Math.abs(dataC[3])));
            polyEntity.setCustomProperty("QCAD", terms.Density, terms.Undefined);
        }
    } // End isNotPreview

    // Add marker to the given operation:
    op.addObject(polyEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
};

/**
 * Defines a 2D Centroid marker size based on overall box and drawing font size.
 * Depends on this.boxSize & this.fontSize
 * \author CVH © 2021
 *
 * \return Radius for marker entity.
 */
InfoCentroids.prototype.getMarkerSize = function() {
    var markerSize;

//debugger;
    // If any, by box size or default:
    if (isOfType(this.boxSize, RBox)) {
        // Proportional to shape(s):
        // Equals to: half the size of sqrt(25x25 per squared out area):
        markerSize = Math.sqrt(this.boxSize.getArea() / 625) / 2;
    }
    else {
        markerSize = 2.5;    // Default
    }

    // Not smaller than 1.20 times the dimension font size:
    if (isNumber(this.fontSize) && this.fontSize > 0.0) {
        if (markerSize < this.fontSize * 1.20) markerSize = this.fontSize * 1.20;
    }

    // Return centroid marker size:
    return markerSize;
};

/**
 * Format a value textual for a 2D Centroid label.
 * Without a leading space.
 * \author CVH © 2021
 *
 * \param value            Value to format textual.
 * \param decPnt           Decimal separator.
 * \param digits           Number of digits.
 * \param trailingZ        Trailing zeros, true/false.
 *
 * \return Textual representation governed by given preferences
 */
InfoCentroids.prototype.formatLabelValue = function(value, decPnt, digits, trailingZ) {
    var numTxt;

    // Fail without a number:
    if (!isNumber(value)) return " NaN";    // Failed as number

    // In fixed notation:
    numTxt = value.toFixed(digits);
    // Suppress trailing zeros if required:
    if (!trailingZ) numTxt = numTxt.replace(/(?:(\.\d*?[1-9]+)|\.)0*$/, "\$1");

    return numTxt.replace(".", decPnt);
};

/**
 * Format a value textual for reporting on the command History.
 * Without trailing zeros, defaults to 8 when digits is invalid.
 * With a leading space, without trailing zeros.
 * \author CVH © 2021
 *
 * \param value           Value to format textual.
 * \param (digits)        Optional: Number of digits. (=Appl.Prec.)
 *
 * \return Textual representation with application decimal point in
 *           given or in application precision.
 */
InfoCentroids.prototype.formatCmdValue = function(value, digits) {
    var decPnt;
    var numTxt;

    // Fail without a number:
    if (!isNumber(value)) return " NaN";    // Failed as number

    // Retrieve application decimal point preferences:
    decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");    // Default =dot

    // Revert to application precision or default when omitted or invalid:
    if (isNull(digits)) {
        // # Known Issue # Will not work prior QCAD 3.26.4.13
        digits = RSettings.getIntValue("PropertyEditor/Decimals", 8);    // Default =8
    }
    if (!isNumber(digits) || digits < 0 || digits > 8) {
        digits = 8;
    }

    // In fixed notation, suppress trailing zeros:
    numTxt = value.toFixed(digits).replace(/(?:(\.\d*?[1-9]+)|\.)0*$/, "\$1");

    return " " + numTxt.replace(".", decPnt);
};

/**
 * Format a value textual for storing properties.
 * Without a leading space.
 * \author CVH © 2021
 *
 * \param value        Value to format textual.
 *
 * \return Textual representation in full precision with application decimal point.
 */
InfoCentroids.prototype.formatPropValue = function(value) {
    // Fail without a number:
    if (!isNumber(value)) return " NaN";    // Failed as number

    // Retrieve application decimal point preferences:
    var decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");    // Default =dot

    return value.toPrecision(17).replace(".", decPnt);
};

/**
 * Format a pair of values textual as coordinate.
 * In full precision with application decimal point.
 * With a leading space.
 * \author CVH © 2021
 *
 * \param valueX        X value of coordinate.
 * \param valueY        X value of coordinate.
 *
 * \return Textual representation coordinate pair.
 */
InfoCentroids.prototype.formatCoordinate = function(valueX, valueY) {
    // Retrieve application decimal point preferences:
    var lstSep = RSettings.getStringValue("Input/CartesianCoordinateSeparator", ",");    // Default =comma

    return " " + this.formatPropValue(valueX) + lstSep + " " + this.formatPropValue(valueY);
};

/**
 * Advance the selection to the added marker (polyline).
 * \author CVH © 2021
 *
 * \param di                 A reference to the document interface.
 * \param transaction        The transaction that added entities.
 *
 * \return Nothing. Selection is adapted
 */
InfoCentroids.prototype.advanceSelection = function(di, transaction) {
    var doc = di.getDocument();
    var affectedIds;
    var i, idn;
    var entity;

    // Retrieve affected entity Id's:
    affectedIds = transaction.getAffectedObjects();
    idn = affectedIds.length;

    // Process all Id's:
    for (i=idn-1; i>=0; i--) {    // Cycle all Id's backwards
        entity = doc.queryEntity(affectedIds[i]);
        // Properly remove Id from list when not a polyline:
        if (!isPolylineEntity(entity)) affectedIds.splice(i, 1);
    } // Loop Id's

    // Advance selection:
    di.selectEntities(affectedIds, false);    // NOTaddToCurrent
};

// Initialization:
// ----------------
InfoCentroids.getMenu = function() {
    var menu = EAction.getSubMenu(
        MiscInformation.getMenu(),
        71050, 100,    // 71050 initially confirmed by Andrew, PM Thu Nov 11, 2021 11:25 am but now set lower than the positions tools
        InfoCentroids.getTitle(),
        "MiscInformationCentroidsMenu"
    );
    return menu;
};

InfoCentroids.getTitle = function() {
    return qsTr("2D &Centroids");
};

InfoCentroids.prototype.getTitle = function() {
    return InfoCentroids.getTitle();
};

InfoCentroids.init = function() {
    // Prevent InfoAddCustomCentroid to be loaded without PRO resources
    if (!hasPlugin("PROTOOLS")) {
        return;    // Don't initiate the Addon
    }
    // -> Continue with PRO recourses

    // Prevent InfoAddCustomCentroid to be loaded with inadequate framework lower than QCAD 3.27
    var frameworkV = getVersionNumber(RSettings.getMajorVersion(), RSettings.getMinorVersion(), RSettings.getRevisionVersion(), RSettings.getBuildVersion());
    var minV = getVersionNumber(3, 27, 0, 0);
    if (frameworkV < minV) {
        return;    // Don't initiate the Addon
    }
    // -> Continue when framework is up to date

    InfoCentroids.getMenu();
};

