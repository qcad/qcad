/**
 * InfoCentroids Beta version 0.31 (As MiscInformation)
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

// # Oddity Fixed # Misc .. Information actions are based on EAction.js
// Misc .. Examples usually chain down to Misc (and to EAction)
include("scripts/EAction.js");

/**
 * \class InfoCentroids
 * \ingroup ecma_misc_information
 * \brief Base class for all centroid tools.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoCentroids(guiAction) {
    EAction.call(this, guiAction);
};

// Deriving our class from the base class:
InfoCentroids.prototype = new EAction();
InfoCentroids.includeBasePath = includeBasePath;

// BeginEvent handler:
InfoCentroids.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);
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
 * \return The sum of the values or zero when not an array of numbers.
 */
InfoCentroids.prototype.getRunningSumKBK = function (list) {
    var i, iMax;
    var t;
    var sum = 0.0;
    var cs  = 0.0;
    var ccs = 0.0;
    var c   = 0.0;
    var cc  = 0.0;
    var fool;

    // Fail without a list of numbers:
    if (isNull(list) || list.length === 0 || !isNumber(list[0])) return 0.0;    // Failed list of numbers

//debugger;
    // Naively for 1 or 2 values:
    iMax = list.length;
    if (iMax === 1) return list[0];
    if (iMax === 2) return list[0] + list[1];

    // Second-order 'iterative Kahan–Babuška algorithm':
    // See: https://en.wikipedia.org/wiki/Kahan_summation_algorithm
    for (i=0; i<iMax; i++) {    // Cycle all values
        t = sum + list[i];

        if (Math.abs(sum) >= Math.abs(list[i])) {
            c = (sum - t) + list[i];
        }
        else {
            c = (list[i] - t) + sum;
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
 * Accumulate box size.
 * \author CVH © 2021
 *
 * \param item         An RBox or an RVector to include.
 *
 * \return Nothing. Overall box is adapted.
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
 */
InfoCentroids.prototype.addTextLabel = function(doc, op, pos, offset, text) {
    var textData;
    var infoColor;
    var newEntity;

//debugger;
    // Create new text data object:
    textData = new RTextData();
    textData.setAlignmentPoint(new RVector(pos.x + offset.x, pos.y + offset.y));
    textData.setVAlign(RS.VAlignTop);
    textData.setHAlign(RS.HAlignLeft);
    textData.setFontName(this.docDimFont);
    textData.setTextHeight(this.fontSize);
    textData.setText(text);

    // Retrieve info color:
    infoColor = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));    // Default =pale green

    // Create new document entity:
    newEntity = new RTextEntity(doc, textData);
    newEntity.setColor(infoColor);

    // Add to operation:
    op.addObject(newEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
};

/**
 * Adding centroid marker to a given operation.
 * \author CVH © 2021
 */
InfoCentroids.prototype.addCentroidMarker = function(doc, op, dataC, radius) {
    var quaterC = 0.4142135623730950488;    // bulge = (sqrt(2) - 1)
    var type;
    var bulges, widths;
    var shift;
    var pts;
    var poly;
    var circleData, polyData;
    var infoColor;
    var circleEntity, polyEntity;
    var decPnt;


    // Revert to defaults when missing:
    if (isNull(this.wireMode)) this.wireMode = false;
    type = (this.wireMode === false) ? "Area" : "Wire";

//debugger;
    bulges = [quaterC, 0.0, -quaterC, 0.0];
    // # Issue Fixed # Circle sector is not rendered correct by QCAD with Width = 2R
    // Fixed with adding 1%, functional for 2R>=0.03 units
    // See: https://qcad.org/rsforum/viewtopic.php?t=7889&p=30877#p30803
    // See: https://www.ribbonsoft.com/bugtracker/index.php?do=details&task_id=2155
    var radiusFix = radius * 1.01;
    widths = [radiusFix, 0.0, radiusFix, 0.0];
    shift = radius / 2;
    pts = [new RVector(dataC[0] + shift, dataC[1]),
            new RVector(dataC[0], dataC[1] + shift),
            new RVector(dataC[0], dataC[1] - shift),
            new RVector(dataC[0] - shift, dataC[1])];

    // Create new centroid marker polyline:
    poly = new RPolyline(pts, false);    // notClosed
    poly.setBulges(bulges);
    poly.setStartWidths(widths);
    poly.setEndWidths(widths);

    // Create new shape data objects:
    circleData = new RCircleData(dataC[2], radius);
    polyData = new RPolylineData(poly);

    // Retrieve info color:
    infoColor = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));    // Default =pale green

    // Create new entities:
    circleEntity = new RCircleEntity(doc, circleData);
    circleEntity.setColor(infoColor);
    polyEntity = new RPolylineEntity(doc, polyData);
    polyEntity.setColor(infoColor);

    // Set custom Properties, use application decPnt:
    // # Bug Fixed # Export absolute centroid value
    decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");    // Default =dot
    circleEntity.setCustomProperty("QCAD", qsTr("2D Centroid"), type);
    polyEntity.setCustomProperty("QCAD", qsTr("2D Centroid"), type);
    polyEntity.setCustomProperty("QCAD", qsTr("X position"), dataC[0].toPrecision(17).replace(".", decPnt));
    polyEntity.setCustomProperty("QCAD", qsTr("Y position"), dataC[1].toPrecision(17).replace(".", decPnt));
    polyEntity.setCustomProperty("QCAD", qsTr("Weighted"), Math.abs(dataC[3]).toPrecision(17).replace(".", decPnt));
    polyEntity.setCustomProperty("QCAD", qsTr("Density"), "1");

    // Add to operation:
    op.addObject(polyEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
    op.addObject(circleEntity, false, false);    // NOTuseCurrentAttributes NOTforceNew
};

/**
 * Define centroid marker size based on overall box and drawing font size.
 * \author CVH © 2021
 *
 * \return Radius for marker.
 */
InfoCentroids.prototype.getMarkerSize = function() {
    var markerSize;

//debugger;
    if (isOfType(this.boxSize, RBox)) {
        // Proportional to shape(s):
        // Equals to: half the size of sqrt(25x25 per squared area):
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

// Pete proposed: ["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]
// Endorsed by Husky