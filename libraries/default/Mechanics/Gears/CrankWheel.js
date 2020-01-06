/**
 * Copyright (c) 2019-2020 Sandy Ganz
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 * CrankWheel -  A crankshaft wheel generator that accepts many
 *               parameters to configure a wheel for computer
 *               control of your engine. The wheel generated
 *               is used for engine position indication to the
 *               engine management system. Many different configurations,
 *               and sizes are used. This will help generate them and
 *               then finally modify in QCAD.
 *
 *
 * Make changes, fork, or open a Pull Request and I'll integrate any changes
 *
 * You can find QCAD at www.qcad.org
 *
 * Installation - Find your QCAD install directory, look for 'libraries/default' copy
 * the folder that is typically called 'CrankWheel' in the Github repository (can extract as a zip)
 * and restart QCAD it should now show up in your library browser. If on a Windows
 * machine you may need to have admin rights. You can also install in a local directory
 * and point QCAD's library path to include it as well.
 */

function CrankWheel() {
}

// Set up default values, all angle in DEGREES. Most defaults
// get loaded from the UI, these are just in case needed for
// things like drawing the preview, after that they all come
// from the UI

CrankWheel.wheelDiameter = 6.75;
CrankWheel.numberOfTeeth = 12;
CrankWheel.missingTeeth = 0;
CrankWheel.toothHeight = 0.25;
CrankWheel.toothRatio = 0.5;
CrankWheel.centerHoleDiameter = 1.0;
CrankWheel.boltHoleCount = 3;
CrankWheel.boltHoleCircleDiameter = 2.5;
CrankWheel.boltHoleDiameter = 0.375;
CrankWheel.boltPatternRotate = 0.0;
CrankWheel.boltHoleCount2 = 0;
CrankWheel.boltHoleCircleDiameter2 = 4.0;
CrankWheel.boltHoleDiameter2 = 0.375;
CrankWheel.boltPatternRotate2 = 60.0;
CrankWheel.numberOfSpokes = 0;
CrankWheel.spokeRatio = 1.0;
CrankWheel.spokeInnerDiameter = 4.0;
CrankWheel.spokeOuterDiameter = 5.0;
CrankWheel.spokeRotation = 0.0;
CrankWheel.showLegend = true;
CrankWheel.showDebug = false;
CrankWheel.drawRoundedRoots = true;
CrankWheel.toothArea = 0.0;
CrankWheel.toothWidth = 0.0;
CrankWheel.toothGapWidth = 0.0;
CrankWheel.balanceHoleDiameter = 0.0;
CrankWheel.balanceHolePositionDiameter = 0.0;
CrankWheel.centerAngle = 180.0;
CrankWheel.toothCurveRadius = 0;

// CrankWheel Class
CrankWheel.prototype.toString = function () {
    print("CrankWheel.js:", "toString(): ");
};

// Build a string for the legend. This uses the class vars
CrankWheel.getLegendStr = function () {
    var t = "";
    t += "Wheel Diameter       : " + CrankWheel.wheelDiameter + "\n";
    t += "Tooth Count          : " + CrankWheel.numberOfTeeth + "\n";
    t += "Missing Teeth        : " + CrankWheel.missingTeeth + "\n";
    t += "Tooth Height         : " + CrankWheel.toothHeight + "\n";
    t += "Tooth Ratio          : " + CrankWheel.toothRatio + "\n";
    t += "Center Hole Diameter : " + CrankWheel.centerHoleDiameter + "\n";
    t += "Number of Spokes     : " + CrankWheel.numberOfSpokes + "\n";
    t += "Spoke Ratio          : " + CrankWheel.spokeRatio + "\n";
    t += "Inner Spoke Diameter : " + CrankWheel.spokeInnerDiameter + "\n";
    t += "Outer Spoke Diameter : " + CrankWheel.spokeOuterDiameter + "\n";
    t += "Spoke Rotation       : " + CrankWheel.spokeRotation + "\n";
    t += "Bolt Hole Pattern 1" + "\n";
    t += "  Bolt Hole Count           : " + CrankWheel.boltHoleCount + "\n";
    t += "  Bolt Hole Circle Diameter : " + CrankWheel.boltHoleCircleDiameter + "\n";
    t += "  Bolt Hole Diameter        : " + CrankWheel.boltHoleDiameter + "\n";
    t += "  Bolt Pattern Rotate       : " + CrankWheel.boltPatternRotate + "\n";
    t += "Bolt Hole Pattern 2" + "\n";
    t += "  Bolt Hole Count           : " + CrankWheel.boltHoleCount2 + "\n";
    t += "  Bolt Hole Circle Diameter : " + CrankWheel.boltHoleCircleDiameter2 + "\n";
    t += "  Bolt Hole Diameter        : " + CrankWheel.boltHoleDiameter2 + "\n";
    t += "  Bolt Pattern Rotate       : " + CrankWheel.boltPatternRotate2 + "\n";
    t += "Tooth Area :                : " + CrankWheel.toothArea.toFixed(5) + "\n";
    t += "Balance Hole Diameter       : " + CrankWheel.balanceHoleDiameter.toFixed(5) + "\n";
    t += "Balance Position Diameter   : " + CrankWheel.balanceHolePositionDiameter + "\n";
    t += "Computed Tooth Width        : " + CrankWheel.toothWidth.toFixed(5) + "\n";
    t += "Computed Gap Width          : " + CrankWheel.toothGapWidth.toFixed(5) + "\n";
    t += "Center Angle                : " + CrankWheel.centerAngle + "\n";
    t += "Tooth Rounding Radius       : " + CrankWheel.toothCurveRadius.toFixed(5) + "\n";

    return t;
};

// Set up any needed start up 'stuff'. Right
// now grabs the match CrankWheel.ui and loads
// the XML for the data entry form
CrankWheel.init = function (formWidget) {
    if (!isNull(formWidget)) {
        CrankWheel.widgets = getWidgets(formWidget);
    }
};

// Generate the CrankWheel for QCAD, this takes
// the document interface (di) and uses that for setting up
// all drawing. Not using the file.
CrankWheel.generate = function (di, file) {

    // if not specified all numeric inputs are of RMathLineEdit class
    // which can't be edited in the Qt Designer as a side note.
    // Also any missing widgets will fail and cause no drawing!

    var v = CrankWheel.widgets["WheelDiameter"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.wheelDiameter = v.getValue();

    // QSpinBox
    CrankWheel.numberOfTeeth = CrankWheel.widgets["NumberOfTeeth"].value;

    // QSpinBox
    CrankWheel.missingTeeth = CrankWheel.widgets["MissingTeeth"].value;

    v = CrankWheel.widgets["ToothHeight"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.toothHeight = v.getValue();

    v = CrankWheel.widgets["ToothRatio"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.toothRatio = v.getValue();

    v = CrankWheel.widgets["CenterHoleDiameter"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.centerHoleDiameter = v.getValue();

    // QCheckBox
    CrankWheel.drawRoundedRoots = CrankWheel.widgets["DrawRoundedRoot"].checked;

    // QSpinBox
    CrankWheel.numberOfSpokes = CrankWheel.widgets["NumberOfSpokes"].value;

    v = CrankWheel.widgets["SpokeRatio"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.spokeRatio = v.getValue();

    v = CrankWheel.widgets["SpokeInnerDiameter"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.spokeInnerDiameter = v.getValue();

    v = CrankWheel.widgets["SpokeOuterDiameter"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.spokeOuterDiameter = v.getValue();

    v = CrankWheel.widgets["SpokeRotation"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.spokeRotation = v.getValue();

    // QSpinBox
    CrankWheel.boltHoleCount = CrankWheel.widgets["BoltHoleCount"].value;

    v = CrankWheel.widgets["BoltHoleCircleDiameter"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.boltHoleCircleDiameter = v.getValue();

    v = CrankWheel.widgets["BoltHoleDiameter"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.boltHoleDiameter = v.getValue();

    v = CrankWheel.widgets["BoltPatternRotate"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.boltPatternRotate = v.getValue();

    // QSpinBox
    CrankWheel.boltHoleCount2 = CrankWheel.widgets["BoltHoleCount2"].value;

    v = CrankWheel.widgets["BoltHoleCircleDiameter2"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.boltHoleCircleDiameter2 = v.getValue();

    v = CrankWheel.widgets["BoltHoleDiameter2"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.boltHoleDiameter2 = v.getValue();

    v = CrankWheel.widgets["BoltPatternRotate2"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.boltPatternRotate2 = v.getValue();

    v = CrankWheel.widgets["BalanceHolePositionDiameter"];
    if (!v.isValid()) {
        return undefined;
    }
    CrankWheel.balanceHolePositionDiameter = v.getValue();

    // QCheckBox
    CrankWheel.showLegend = CrankWheel.widgets["ShowLegend"].checked;

    // QCheckBox
    CrankWheel.showDebug = CrankWheel.widgets["ShowDebug"].checked;

    // At this point generate the wheel. Prior to this some validation
    // could be done to prevent invalid wheels due to params.

    return CrankWheel.getOperation(di);
};

// Called to display the small icon of the wheel. Default
// params are just used, may be better to reset them here,
// always but may not matter (user changes var in the class etc.)
CrankWheel.generatePreview = function (di, iconSize) {

    // Save the legend state so we can disable it for the preview
    var saveLegendState = CrankWheel.showLegend;
    CrankWheel.showLegend = false;
    var ret = CrankWheel.getOperation(di);
    CrankWheel.showLegend = saveLegendState;

    return ret;
};

// Helper Funcs

// create array of bolt holes formed in a circle about a point 0,0
// Returns an array of RCircleEntity's or empty if nothing to do
function generateBoltPattern(boltCount, angleOffset, circleDiameter, boltDiameter) {
    var boltPattern = [];

    // Reject some things if needed
    if (boltCount < 0.0 || circleDiameter < 0.0 || boltDiameter < 0.0) {
        return boltPattern;
    }

    const circleSector = 2 * Math.PI / boltCount;
    const offsetRads = RMath.deg2rad(angleOffset); // FUDGE_FACTOR is a HACK to rotate to 0 degrees. BUG???
    const circleRadius = circleDiameter / 2.0;
    const boltRadius = boltDiameter / 2.0;

    // Now build the array of bolt holes
    for (var cnt = 0; cnt < boltCount; cnt++) {
        boltPattern.push(new RCircleData(new RVector.createPolar(circleRadius, circleSector * cnt + offsetRads), boltRadius));
    }

    return boltPattern;
}

// Calculate the area of the simple tooth. This is basically an annular sector
// and found some 'math' on the internets that does the trick
// innerRadius is the innermost
// outerRadius is the outermost
// sectorAngle is the angle of the sector in DEGREES
// A = ( R² - r² ) * π * angle / 360 Area of a sector Degs
// A = ( R² - r² ) * π * angle / 2 * π Area of a sector Degs
function simpleToothArea(innerRadius, outerRadius, sectorAngle) {
    return (outerRadius * outerRadius - innerRadius * innerRadius) * Math.PI * sectorAngle / (2 * Math.PI);
}

// Calculate the area of the fancy bottom curved tooth. This is the tooth
// that is composed of a simple tooth with a radius on each
// side of the tooth. The radius on the tooth is 1/4 of a circle
// since the bulge is -1 which draws a semi-circle to the next point
// Now to calculate all that... No idea. So my attack will be an
// approximation. The way I did it was use the simpleToothArea
// and add that with the 1/4 circle area on each side.
// To get these little arcs ar the you can approximate this by drawing
// a square with the diameter of 2 * Radius of the circle. Then
// subtract the circle from the square and divide by 2 to get the area
// of the base curves. This ONLY works because a Bulge of -1 is a semi-circle!
function roundedRootToothArea(innerRadius, outerRadius, sectorAngle, rootRadius) {
    const squareArea = rootRadius * rootRadius * 4;
    const circleArea = Math.PI * rootRadius * rootRadius;
    const curveyRoots = (squareArea - circleArea) / 2; // area under both curvey parts

    // now add the curvy part with the regular tooth part. Gets a close
    // approximation, not exact but good enough. Draw the picture to see why
    // and remember the tooth is an annular (arcs top and bottom)
    return simpleToothArea(innerRadius, outerRadius, sectorAngle) + curveyRoots;
}

// Given the area of a circle calculate the Radius that would
// generate this area.
// r = sqrt( A / π ) Radius of circle with given Area
function circleAreaToRadius(circleArea) {
    return Math.sqrt(circleArea / Math.PI);
}

// compute the equivalent area (missing) at a different radius. This
// is a basic lever equation at play
function balanceHoleAreaAtRadius(area, currentRadius, newRadius) {
    return (area * currentRadius) / (newRadius);
}

// calculates the chord length given the radius and angle
// angle in radians of course
function chordLength(radius, angle) {
    return 2.0 * radius * Math.sin(angle / 2.0);
}

// Does all the drawing work. Remember most things here just add points (vertices)
// to an array for drawing. Drawing is closed so should alway be a closed surface for
// the wheel.
CrankWheel.getOperation = function (di) {
    var addOperation = new RAddObjectsOperation(false);

    const center = new RVector();
    const wheelRadius = CrankWheel.wheelDiameter / 2.0;
    const pitchCircleDiameter = CrankWheel.wheelDiameter - (2.0 * CrankWheel.toothHeight);
    const pitchCircleRadius = pitchCircleDiameter / 2.0;
    const centerHoleRadius = CrankWheel.centerHoleDiameter / 2.0;

    // di is the interface not the doc, so get the doc as we need that
    var document = di.getDocument();

    // Draw the center of the wheel if not 0
    if (centerHoleRadius) {
        var centerHoleData = new RCircleData(center, centerHoleRadius);
        addOperation.addObject(new RCircleEntity(document, centerHoleData));
    }

    // now the first bolt pattern
    generateBoltPattern(
        CrankWheel.boltHoleCount,
        CrankWheel.boltPatternRotate,
        CrankWheel.boltHoleCircleDiameter,
        CrankWheel.boltHoleDiameter).forEach(
            function (hole) {
                addOperation.addObject(new RCircleEntity(document, hole));
            }
        );

    // now the second
    generateBoltPattern(
        CrankWheel.boltHoleCount2,
        CrankWheel.boltPatternRotate2,
        CrankWheel.boltHoleCircleDiameter2,
        CrankWheel.boltHoleDiameter2).forEach(
            function (hole) {
                addOperation.addObject(new RCircleEntity(document, hole));
            }
        );

    // storage for the points to draw tooths and the missing-toothed parts

    var td = [];    // tooth data user selected bulge
    var mtd = [];   // missing tooth data all nice lower arc
    var ltd = [];   // last tooth IF bulge root is selected needs to be different
    var std = [];   // starting tooth (first)

    // This draws the top of the tooth's arch and the inner missing
    // arch which is later used IF missing teeth are specified

    const sectorAngle = 2.0 * Math.PI / CrankWheel.numberOfTeeth;
    const percentTooth = CrankWheel.toothRatio;
    const toothAngle = sectorAngle * percentTooth;
    const rootAngle = sectorAngle - toothAngle;
    const outsideBulge = Math.tan(toothAngle / 4.0);
    const insideBulge = Math.tan(rootAngle / 4.0);

    // Draws the tooth start points, same for both on the inner (pitchCircle)
    // and the outer.
    // Tooth Legend :
    //  std - start tooth
    //  td  - middle teeth
    //  ltd - last tooth
    //  mtd - outer missing tooth part
    // pitch circle - the (chord length / 2) is the radius of the bulge since
    // the bulge is a semi-circle we can take advantage of this fact later on for tooth calculation

    CrankWheel.toothWidth = chordLength(wheelRadius, toothAngle);
    CrankWheel.toothGapWidth = chordLength(pitchCircleRadius, rootAngle);

    const curvePitchRadius = pitchCircleRadius - CrankWheel.toothGapWidth / 2.0;
    var curveOrFlatPitchRadius;
    var noMissingBulge;

    // screwy logic to set up drawing curved teeth, curved teeth with missing,
    // non curved teeth and non curved with missing. a bulge of -1 is a semi-circle for
    // the fancy looking teeth. I'm sure their is a cleaner way to do this...

    const userBulge = CrankWheel.drawRoundedRoots ? -1.0 : insideBulge;

    if (CrankWheel.missingTeeth > 0) {
        curveOrFlatPitchRadius = CrankWheel.drawRoundedRoots ? curvePitchRadius : pitchCircleRadius;
        noMissingBulge = insideBulge;
    }
    else {
        curveOrFlatPitchRadius = pitchCircleRadius;
        noMissingBulge = userBulge;
    }

    // Point 1, start of tooth, bottom
    std.push([curveOrFlatPitchRadius, 0, 0]);
    td.push([pitchCircleRadius, 0, 0]);
    ltd.push([pitchCircleRadius, 0, 0]);
    mtd.push([curveOrFlatPitchRadius, 0, 0]);

    // draw point 2, which is the inner to outer line, continue draw with bulge
    std.push([wheelRadius, 0, outsideBulge]);
    td.push([wheelRadius, 0, outsideBulge]);
    ltd.push([wheelRadius, 0, outsideBulge]);
    mtd.push([curveOrFlatPitchRadius, 0, outsideBulge]);  // save the pattern for the bottom (root) not a top

    // draw point 3, which is the arch
    std.push([wheelRadius, toothAngle, 0]);
    td.push([wheelRadius, toothAngle, 0]); // draw end point of outer tooth, next line is a line down to pitchCircle
    ltd.push([wheelRadius, toothAngle, 0]);

    // Set the bulge type based on style of tooth and where it is,
    // First, Middle, Missing, and Last
    std.push([pitchCircleRadius, toothAngle, userBulge]);
    td.push([pitchCircleRadius, toothAngle, userBulge]);
    ltd.push([curveOrFlatPitchRadius, toothAngle, noMissingBulge]);
    mtd.push([curveOrFlatPitchRadius, toothAngle, insideBulge]);

    // compute the center of the missing tooth area 180 deg away
    // so we can place the balance hole on the user specified radius
    CrankWheel.centerAngle = RMath.rad2deg(Math.PI - (rootAngle + (rootAngle + toothAngle) * CrankWheel.missingTeeth) / 2);

    // need to pick based on tooth type and not do it if 0 missing teeth, need to calc a bit different
    if (CrankWheel.drawRoundedRoots) {
        // for rounded roots we need to know the radius of the root curve. We have that!
        CrankWheel.toothCurveRadius = CrankWheel.toothGapWidth / 2.0;
        CrankWheel.toothArea = roundedRootToothArea(pitchCircleRadius, wheelRadius, toothAngle, CrankWheel.toothCurveRadius);
    }
    else {
        CrankWheel.toothArea = simpleToothArea(pitchCircleRadius, wheelRadius, toothAngle);
    }

    // If we do have any missing teeth and want a balance hole do it now
    if (CrankWheel.missingTeeth > 0 && CrankWheel.balanceHolePositionDiameter > 0.0) {
        const leverArea = balanceHoleAreaAtRadius(CrankWheel.toothArea * CrankWheel.missingTeeth, pitchCircleRadius, CrankWheel.balanceHolePositionDiameter / 2.0);
        CrankWheel.balanceHoleDiameter = circleAreaToRadius(leverArea) * 2.0;

        // draw the balance hole, use the pattern generator to rotate a single hole around
        // this places the balance hole at the midpoint on the balance hole diameter.
        // Not sure if this is technically correct because of the calculation but seems better.
        if (CrankWheel.balanceHoleDiameter > 0.0) {
            generateBoltPattern(
                1,
                CrankWheel.centerAngle,
                CrankWheel.balanceHolePositionDiameter,
                CrankWheel.balanceHoleDiameter).forEach(
                    function (hole) {
                        addOperation.addObject(new RCircleEntity(document, hole));
                    }
                );
        }
    }

    // Construct the wheel here with teeth as previously created.
    //
    // Roll through the list of teeth and when at the point where we need missing
    // teeth draw that area. We have special case for the next to last tooth, and any
    // missing teeth.

    wheel = new RPolyline();
    wheel.setClosed(true);

    // Draw start tooth which may be different, similar to the last tooth
    for (var n = 0; n < td.length; n++) {
        wheel.appendVertex(RVector.createPolar(std[n][0], std[n][1]), std[n][2]);
    }

    for (var i = 1; i < CrankWheel.numberOfTeeth; i++) {

        // logic here might be if a missing tooth cnt > 0 always the last tooth is drawn with
        // a regular arc (bulge), then the mtd will always connect. Might go with td, mtd, ltd (last tooth)
        // when assembling the array, and pick which is needed based on settings and missing tooth.
        // Also last tooth may always be OK to have with regular arcs

        // if numberOfTeeth - missingTeeth - 1 draw as normal
        // else if numberOfTeeth - missingTeeth draw as final tooth with normal arc (not bulge)
        // else draw the mtd to wrap it all up.
        var n;

        // Draw each complete tooth here, or missing tooth depending on count
        if (i < CrankWheel.numberOfTeeth - CrankWheel.missingTeeth - 1) {
            for (n = 0; n < td.length; n++) {
                wheel.appendVertex(RVector.createPolar(td[n][0], (i * sectorAngle) + td[n][1]), td[n][2]);
            }
        }
        else if (i < CrankWheel.numberOfTeeth - CrankWheel.missingTeeth) {
            // last tooth before missing teeth if any, won't be here otherwise
            for (n = 0; n < ltd.length; n++) {
                wheel.appendVertex(RVector.createPolar(ltd[n][0], (i * sectorAngle) + ltd[n][1]), ltd[n][2]);
            }
        } else {
            // only will be here if Missing any teeth
            // draw missing parts typically 3 for each missing tooth
            for (var n = 0; n < mtd.length; n++) {
                wheel.appendVertex(RVector.createPolar(mtd[n][0], (i * sectorAngle) + mtd[n][1]), mtd[n][2]);
            }
        }
    }

    // Draw the wheel teeth
    addOperation.addObject(new RPolylineEntity(document, new RPolylineData(wheel)));

    if (CrankWheel.numberOfSpokes > 0 && CrankWheel.spokeInnerDiameter > 0.0
        && CrankWheel.spokeOuterDiameter > CrankWheel.spokeInnerDiameter) {

        const spokeAngle = 2 * Math.PI / CrankWheel.numberOfSpokes;

        // inner spoke hole line
        const r0 = CrankWheel.spokeInnerDiameter / 2.0;
        const a0 = Math.asin(CrankWheel.spokeRatio / (r0 * 4.0));

        // outer spoke hole line
        const r1 = CrankWheel.spokeOuterDiameter / 2.0;
        const a1 = Math.asin(CrankWheel.spokeRatio / (r1 * 4.0));

        const innerSpokeBulge = Math.tan((2.0 * a0 - spokeAngle) / 4.0);
        const outerSpokeBulge = Math.tan((spokeAngle - 2.0 * a1) / 4.0);

        // gets the starting angle and offset
        var spokeAngleOffset = spokeAngle + RMath.deg2rad(CrankWheel.spokeRotation);

        // draw spokes one at a time like the tooths
        for (var i = 0; i < CrankWheel.numberOfSpokes; i++) {

            // create each new spoke hole
            hole = new RPolyline();
            hole.setClosed(true);

            // draw each slot as a closed object
            hole.appendVertex(RVector.createPolar(r0, (spokeAngle - a0) + spokeAngleOffset), innerSpokeBulge);
            hole.appendVertex(RVector.createPolar(r0, a0 + spokeAngleOffset), 0);
            hole.appendVertex(RVector.createPolar(r1, a1 + spokeAngleOffset), outerSpokeBulge);
            hole.appendVertex(RVector.createPolar(r1, (spokeAngle - a1) + spokeAngleOffset), 0);

            // once all created add and draw
            addOperation.addObject(new RPolylineEntity(document, new RPolylineData(hole)));

            // nudge the angle along to rotate things around
            spokeAngleOffset += spokeAngle;
        }
    }

    // Draw the info block, offset to right of wheel

    if (CrankWheel.showLegend) {
        var wheelLegend = CrankWheel.getLegendStr();

        // calculate the position to the right of the wheel
        textPos = new RVector([wheelRadius + wheelRadius * 0.1, wheelRadius]);

        var text = new RTextEntity(
            document,
            new RTextData(
                textPos,            // position
                textPos,            // alignment point
                0.15,               // height
                1.0,                // text width (ignored for now)
                RS.VAlignTop,       // alignments
                RS.HAlignLeft,
                RS.LeftToRight,
                RS.Exact,
                1.0,                // line spacing factor
                wheelLegend,        // the text
                "Courier",          // font fixed spacing is nicer here
                false,              // bold
                false,              // italic
                0.0,                // angle
                false               // simple text without formatting
            )
        );
        addOperation.addObject(text);
    }

    // draw anything needed in debug mode

    if (CrankWheel.showDebug) {
        // Wheels outer diameter
        var wheelCircleData = new RCircleData(center, wheelRadius);
        addOperation.addObject(new RCircleEntity(document, wheelCircleData));

        // tooth inner root circle
        var wheelPitchData = new RCircleData(center, pitchCircleRadius);
        addOperation.addObject(new RCircleEntity(document, wheelPitchData));

        // User defined circle for the balance hole
        var balanceHoleData = new RCircleData(center, CrankWheel.balanceHolePositionDiameter / 2.0);
        addOperation.addObject(new RCircleEntity(document, balanceHoleData));

        // if we are drawing bolt holes draw that circle
        if (CrankWheel.boltHoleCount) {
            var boltPitchData = new RCircleData(center, CrankWheel.boltHoleCircleDiameter / 2.0);
            addOperation.addObject(new RCircleEntity(document, boltPitchData));
        }

        // same for second set of bolt holes
        if (CrankWheel.boltHoleCount2) {
            var boltPitchData2 = new RCircleData(center, CrankWheel.boltHoleCircleDiameter2 / 2.0);
            addOperation.addObject(new RCircleEntity(document, boltPitchData2));
        }

        // now spoke boundaries (inner and outer) if being drawn

        // draw inner circle for the spokes
        if (CrankWheel.numberOfSpokes) {
            var spokeInnerData = new RCircleData(center, r0);
            addOperation.addObject(new RCircleEntity(document, spokeInnerData));
        }

        // same for the outers
        if (CrankWheel.numberOfSpokes) {
            var spokeInnerData2 = new RCircleData(center, r1);
            addOperation.addObject(new RCircleEntity(document, spokeInnerData2));
        }
    }

    // Add it all to the drawing
    return addOperation;
};
