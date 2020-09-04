/**  FlexPainter Beta version 0.42e
 *
 * Copyright (c) 2020 by CVH.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * With the unmatched assistance of Andrew Mustun.
 * This script and auxiliary files are donated to the QCAD project.
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

include("../MathExamples.js");
include("scripts/simple.js");    // Added for simple API
    //# Issue Solved # Use "scripts/simple.js" instead of "simple.js"
    //https://qcad.org/rsforum/viewtopic.php?t=6528


/**
 * \class FlexPainter
 * \ingroup ecma_misc_examples_mathexamples
 * \brief Cast and morphs flexible painters over selected based entities.
 *
 */
function FlexPainter(guiAction) {
    MathExamples.call(this, guiAction);
};

FlexPainter.prototype = new MathExamples();
FlexPainter.includeBasePath = includeBasePath;


/**
 * This action paints over all selected line based entities from start to end
 * and minimalistic morphs the painter set to the curvatures.
 * Casting common entities locally and/or globally the user can edit with any tool available.
 * If to much torsion is applied to a roller stamp it actually smudges. This is not considered as a flaw.
 * Results may be better with radii of curvature of about the painters actual side width or larger.
 */
FlexPainter.prototype.beginEvent = function() {
    MathExamples.prototype.beginEvent.call(this);

//debugger;
    // FlexPainter.init test for PROTOOLS to prevent loading the addon
    // These should be available at runtime
    // Prevent FlexPainter to run without PRO resources:
    if (!hasPlugin("PROTOOLS")) {
        // Push warning to command history and terminate
        qDebug("FlexPainter: NO PROTOOLS!");
        EAction.handleUserWarning("FlexPainter: NO PROTOOLS!");
        EAction.handleUserMessage("Nothing casted. Command terminated");
        this.terminate();
        return;
    } // -> Continue with PRO recources

    // FlexPainter.init states "Requires Document"
    // A document should be available....Retrieve document, units:
    var document = this.getDocument();
    this.units = document.getUnit();
    var di = this.getDocumentInterface();

//debugger;
    // Terminate without document units:
    if (isNull(this.units) || !isNumber(this.units) || this.units == 0) {
        // Push warning to command history and terminate
        qDebug("NO Doc units! ; Command terminated");
        EAction.handleUserWarning("NO Doc units! FlexPainter syncs with units.");
        EAction.handleUserMessage("Nothing casted. Command terminated");
        debugger; // ###### Catch this In the act !!!
            // CAN NOT handle no units! Halt in debugger mode
            // # ToDo # Revert to defaults
        debugger; // ######
        this.terminate();    // Or terminate altogether
        return;
    } // -> Continue with document units

    // FlexPainter.init states "Requires Selection"
    // A selection should be available....Retrieve selection:
    var ids = document.querySelectedEntities();    // Query Qlist with selected
    const idn = ids.length;    // Number of selected entities

    // Terminate without selection:
    if (idn == 0) {
        // Push warning to command history and terminate
        qDebug("No selection! Command terminated");
        EAction.handleUserWarning("No selection!");
        EAction.handleUserInfo("Please, make a selection");
        this.terminate();
        return;
    } // -> Continue with selection

    // Show Dialog & terminate if cancelled
    if (!this.showDialog()) {
        // Push 'Cancelled' to command history and terminate
        qDebug("Dialog cancelled! Command terminated");
        EAction.handleUserMessage("Cancelled!");
        EAction.handleUserMessage("Command terminated");
        this.terminate();
        return;
    }

    // Cronometration
    var crono = Date.now();

//debugger;
    // Retrieve painters specifics
    var painterLength = this.mainData[0][2];
    var painterStepSize = this.mainData[0][3];
    var knotlength = this.knotData[0][2];
    var appendiceslength = 0.00;

    // Sum used appendice lengths, do is locked with required and existing
    if (this.doBeginApex) appendiceslength += this.beginApexData[0][2];
    if (this.doEndApex) appendiceslength += this.endApexData[0][2];
    if (this.doInserts) appendiceslength += knotlength * this.insertions;

    // # Busy # SetType: Slanted, Boxed, Stepped, Periodic v0.38 posponed
    var underStepped = (painterStepSize * this.mainScaleS) < (painterLength * this.mainScaleX);
    var boxStepped = (painterStepSize * this.mainScaleS) == (painterLength * this.mainScaleX);
    var overStepped = (painterStepSize * this.mainScaleS) > (painterLength * this.mainScaleX);

    // # Busy # There is a difference between A: hasNeatEnds or B: underStepped v0.39 posponed
    this.hasNeatEnds = (this.beginData[0][0] > 0 || this.endData[0][0] > 0);

    // Initiate pi/2, counters, trash can and intermediate message string
    this.orthoAngle = Math.PI/2;
    this.countEntities = 0;
    this.countNewEntities = 0;
    this.countCastpoints = 0;
    this.trashCan = [];    // create Empty trash collector Array
    var msg = "";

    // With grouped castings: collect all additions to one single operation
    if (this.groupCasts) startTransaction();
    // Intentional +TAB: Transaction Block

        // Process all selected entities
        for (var i=0; i<idn; i++) {    // Cycle through all selected entities
            var id = ids[i];    // Pick Qlist entry
            var entity = document.queryEntity(id);    // Pick entity

            // Limit selection
            //    (entity based)
            if (
                !isLineEntity(entity) &&
                !isArcEntity(entity) &&
                !isCircleEntity(entity) &&
                !isEllipseEntity(entity) &&
                !isPolylineEntity(entity) &&
                !isSplineEntity(entity)
            ) {
                // Push smothered warning to command history
                msg = entityTypeToString(entity.getType(), false) + " skipped!";
                qDebug(msg);
                if (!this.beVerbose) EAction.handleUserWarning(msg);
                continue;    // Skip to next selected entity
            }

            var shape = entity.castToShape();

            // Set isTanCloObj flag for all geometrically and tangentially Closed Forms
            //    (entity based)
            this.isTanCloObj = false;
            if (isPolylineEntity(entity) || isSplineEntity(entity)) {
                if (entity.isGeometricallyClosed()) {
                    if (isSplineEntity(entity)) {
                        this.isTanCloObj = entity.isPeriodic();
                    }
                    else if (isPolylineEntity(entity)) {
                        // Near tangentially connected
                        this.isTanCloObj = RMath.fuzzyAngleCompare(shape.getDirection1() + Math.PI, shape.getDirection2());
                    }
                }
            }
            else if (isCircleEntity(entity) || isFullEllipseEntity(entity)) {
                this.isTanCloObj = true;
            }

            // Determine casting type
            // # Issue Solved # Its far more faster to set how to cast on the selected
            //    base entity then to test how to cast every castpoint.
            if (isLineShape(shape) || isArcShape(shape) || isSplineShape(shape)) this.castingType = 1;
            if (isPolylineShape(shape)) this.castingType = 3;
            // # Issue Fixed # No mathematical Closed Form. 
            //    Is by serie expansion. Is very time consuming
            if (isEllipseEntity(entity)) {
                // # Workaround # Ellipses by casting on a Polyline approximateWithArcs
                // # Issue # Relative acuracy, absolute acuracy sizes with the magnetude
                var shape = shape.approximateWithArcs(128);
                this.castingType = 3;
                if (this.isTanCloObj) shape.convertToClosed;
            }
            if (this.isTanCloObj) this.castingType++;    // Promote type 1 > 2 || 3 > 4
            if (isCircleShape(shape)) this.castingType = 5;

//debugger;
            // Get entity length after possible approximateWithArcs
            this.objlength = shape.getLength();

            // Understepped on Open Form:
            //    Reserve 1 painter Length, n.knots+1 times
            var chainsN = this.insertions + 1;
            var reservedLength = 0.00;
            if (!this.isTanCloObj) {
                if (underStepped) {
                    var reservedLength = chainsN * painterLength;
                }
            }

            // Fit a number of actual painter StepSize lengths
            if (this.isTanCloObj) {    // Closed Forms: +No apexes, +n.knots, 1 more as possible
                var fitN = Math.ceil(
                            (this.objlength - (knotlength * this.insertions * this.mainScaleX)) /
                                // Divided by
                            (painterStepSize * this.mainScaleS));
            }
            else {    // Open Forms: +Apexes, +n.knots, 1 more as possible
                var fitN = Math.ceil(
                            (this.objlength - ((reservedLength + appendiceslength) * this.mainScaleX)) /
                                // Divided by
                            (painterStepSize * this.mainScaleS));
                // Not forced to scale: ceil() - 1 = floor()
                if (!this.forcedDyn) fitN--;
            }

            // Fit a larger multiple of chainsN to neatly divide in subchains
            fitN = Math.trunc(Math.ceil(fitN / chainsN)) * chainsN;

            // Test for too small entities
            if (fitN <= 3) {
                // Push smothered warning to command history
                qDebug("Too short. Skipped");
                if (!this.beVerbose) EAction.handleUserWarning(entityTypeToString(entity.getType(), false) + " Too short. Skipped!");
                continue;    // Skip to next selected entity
            }

            // Test for too many castings
            if (fitN > 9999) {
                // Push smothered warning to command history
                qDebug("Too many castings (>9999). Base skipped");
                if (!this.beVerbose) EAction.handleUserWarning("Too many castings (>9999). Base skipped!");
                continue;    // Skip to next selected entity
            }

//debugger;
            // Dynamic scaler for continuous Closed Forms and forced to scale Open Forms
            var dynScale = 1.00;
            if (this.isTanCloObj) {    // Continuous Closed Forms: +No apexes, +n.Knots
                dynScale =
                    this.objlength /
                        // Divided by sum
                    ((knotlength * this.insertions * this.mainScaleX)
                    + (fitN * painterStepSize * this.mainScaleS));
            }
            else {    // Open Forms: +Apexes, +n.Konts
                if (this.forcedDyn) {    // Forced to scale Open Forms
                    dynScale =
                        this.objlength /
                            // Divided by sum
                        (((reservedLength + appendiceslength) * this.mainScaleX)
                        + (fitN * painterStepSize * this.mainScaleS));
                } // Else: Dynamic scaler stays f1.00
            }

            // Set actual scalers
            this.scalerY = this.mainScaleY;
            if (this.preserveLook) this.scalerY = this.mainScaleY * dynScale;
            this.scalerS = this.mainScaleS * dynScale;
            this.scalerX = this.mainScaleX * dynScale;

            // Push smothered dynScale info to command history
            msg = entityTypeToString(entity.getType(), false);
            msg += (dynScale == 1) ? " not dynScaled" : " dynScaled : " + dynScale;
            qDebug(msg);
            if (!this.beVerbose) EAction.handleUserInfo(msg);

            // Only overtepped painters end in voids
            if (overStepped) {
                var painterVoid = (painterStepSize * this.scalerS) - (painterLength * this.scalerX);
            }
            else {
                var painterVoid = 0.00;
            }

            // Local surplus absolute:
            //    Any chain can locally only end with one such void if any
            var surPlusLabs = painterVoid;

            // Global surplus absolute:
            //    Any void left globally
            var surPlusGabs =
                    this.objlength
                    - ((reservedLength + appendiceslength) * this.scalerX)
                    - (fitN * painterStepSize * this.scalerS);

            // # ToDo # Treat originally slanted with neat ends different
            if (!this.isTanCloObj) {
                if (!this.forcedDyn) {
                // Pro / Cons ??? v0.39 posponed
                // Aligned and exposing a void globally is automatic
                // Overstepped with Apex not
                }
            }

            // On Open Forms:
            //    In any chain fits one single Null-Length painter extra
            //    Except centered: There will be no place for more then 1 full painter
            if (!this.isTanCloObj && (this.factorsurPlus != 0.50)) {
                if (painterLength == 0.00) {
                    fitN+= chainsN;
                    surPlusLabs -= painterVoid
                }
            }

            // On Open Forms: Besides Null-Length painters:
            //    The complete chain may expose a void globally
            //    The global void may admit only one more painter
            //    Except centered: There will be no place for more then 1 full painter
            if (!this.isTanCloObj && painterLength > 0.00) {
                if (!this.doBeginApex) {    // Required and existing
                    // Aligned at end may expose a void globally
                    if (this.factorsurPlus == 1.00) {
                        if (surPlusGabs > painterLength * this.scalerX) {
                            // Add extra
                            fitN ++;
                            surPlusGabs -= painterLength * this.scalerX;
                            // The local void is then no longer exposed
                            surPlusLabs = 0.0;
                        }
                    }
                }
                if (!this.doEndApex) {    // Required and existing
                    // Aligned at start may expose a void globally
                    if (this.factorsurPlus == 0.00) {
                        if (surPlusGabs > painterLength * this.scalerX) {
                            // Add extra
                            fitN ++;
                            surPlusGabs -= painterLength * this.scalerX;
                            // The local void is then no longer exposed
                            surPlusLabs = 0.0;
                        }
                    }
                }
            }

            // Cast reserved too if any
            if (reservedLength > 0.00) fitN += chainsN;

            // Initiate global collector
            this.dotStringData = [];    // Empty global splines fitpoint collector
            this.nodStringData = [];    // Empty global polylines vertices collector

            // Aligning & Shifting
            if (this.isTanCloObj) {    // All Closed Forms shifting by % off stepsize
                this.distFromStart = painterStepSize * this.scalerS * this.closeShift;
            }
            else {    // All Open Forms aligning
                this.distFromStart = surPlusGabs * this.factorsurPlus;
            }

            // With non-grouped casting: collects additions to one single operation every entity
            if (!this.groupCasts) startTransaction();
            // Intentional +TAB Transaction Block

                // Optionally add active sublayer to the entity it's layer.
                if (this.subLayerCasts) {
                    var layerName = entity.getLayerName() + " ... Painted";
                    this.addActiveLayer(layerName, document, di)
                }

                // Cast & morphs painters over Entities
                // ------------------------------------
//debugger;
                // Optionally cast begin apex painter On Open Forms
                if (this.doBeginApex) {    // Required and existing
                    if (!this.isTanCloObj) {    // On Open Forms
                        this.countCastpoints += this.castPainter(shape, this.beginApexData);
                        this.countNewEntities += this.beginApexData[0][0] - this.beginApexData[0][1];
                        this.distFromStart += this.beginApexData[0][2] * this.scalerX;
                    }
                }

                // Repeat chain + insertion over whole the entity
                //    Runs at least once, no insertion on last run
                for (var m=0; m<=this.insertions; m++) {    // Cycle through all chains
                    // Sub-chain shifting
                    this.distFromStart += surPlusLabs * this.factorsurPlus / chainsN;

                    // Add begin painter if any on Open Forms
                    if (this.beginData[0][0] > 0) {
                        if (!this.isTanCloObj) {    // On Open Forms
                            this.countCastpoints += this.castPainter(shape, this.beginData);
                            this.countNewEntities += this.beginData[0][0] - this.beginData[0][1];
                            // Length=0=fixed!
                        }
                    }

                    // Cast main painters repetitively
                    var startedAt = this.distFromStart
                    var nMax = fitN / chainsN;
                    for (var n=1; n<=nMax; n++) {    // Cycle and repeat main painter. Zero omitted = virtual(n+1)
                        this.countCastpoints += this.castPainter(shape, this.mainData);
                        this.countNewEntities += this.mainData[0][0] - this.mainData[0][1];
                        this.distFromStart = startedAt + (n * painterStepSize * this.scalerS);
                    } // Loop main painter

                    // Add end painter if any on Open Forms
                    if (this.endData[0][0] > 0) {
                        if (!this.isTanCloObj) {    // On Open Forms
                            this.distFromStart += (painterLength * this.scalerX) - (painterStepSize * this.scalerS);
                            this.countCastpoints += this.castPainter(shape, this.endData);
                            this.countNewEntities += this.endData[0][0] - this.endData[0][1];
                            // Length=0=fixed!
                        }
                    }

                    // Sub-chain shifting
                    this.distFromStart += surPlusLabs * (1-this.factorsurPlus) / chainsN

                    // Optionally cast insertion
                    //    Except for the last loop
                    if (m < this.insertions) {
                        if (this.doInserts) {    // Required and existing
                            this.countCastpoints += this.castPainter(shape, this.knotData);
                            this.countNewEntities += this.knotData[0][0] - this.knotData[0][1];
                            this.distFromStart += this.knotData[0][2] * this.scalerX;
                        }
                    }

                } // Loop chains

                // Optionally cast end apex painter on Open Forms
                if (this.doEndApex) {    // Required and existing
                    if (!this.isTanCloObj) {    // On Open Forms
                        this.distFromStart = this.objlength
                                             - (surPlusGabs * (1-this.factorsurPlus))
                                             - (this.endApexData[0][2] * this.scalerX);
                        this.countCastpoints += this.castPainter(shape, this.endApexData);
                        this.countNewEntities += this.endApexData[0][0] - this.endApexData[0][1];
                        //this.distFromStart += this.endApexData[0][2] * this.scalerX;
                    }
                }

                // Cast global splines if any.
                //    Open/closed on open/closed Forms
                var jsn = this.dotStringData.length;
                for (var js=0; js<jsn; js++) {    // Cycle through all global splines
                    addSpline(this.dotStringData[js], this.isTanCloObj);
                } // Loop global splines
                this.countNewEntities += jsn;

                // Cast global polys if any.
                //    Open/closed on open/closed Forms
                var jpn = this.nodStringData.length;
                for (var jp=0; jp<jpn; jp++) {    // Cycle through all global polys
                    addPolyline(this.nodStringData[jp], this.isTanCloObj, false);
                } // Loop global polys
                this.countNewEntities += jpn;
                // ------------------------------------

            // Intentional -TAB Transaction Block
            // Optionally parse all additions as one single operation every entity
            if (!this.groupCasts) {
                var castResult = endTransaction();    // No error if without any
                if (castResult.isFailed()) {    // Casting failed
                    break;    // Break out selected entities loop 
                }
                // When not cast in group cast one by one
                // # Issue Fixed # 1.Not showing castings sequentially
                // # Issue Fixed # 2.Fix slows down unecessary
                if (i != idn - 1) {    // # Workaround # 2.Skip only one and last
                    this.updatePreview();    // # Workaround # 1.Best fix to show progress sequentially
                }
            }

            // Optionally mark for deletion and increase processed entities counter
            if (this.delEntity) this.trashCan.push(id);
            this.countEntities++;

        } // Loop all selected entities

    // Intentional -TAB: Transaction Block
    // Optionally parse all additions as one single operation
    if (this.groupCasts) var castResult = endTransaction();    // No error if without any

    // Optionally empty trash can
    if (this.delEntity) {
        var jn = this.trashCan.length;
        if (jn > 0) {
            // Collect deletions
            op = new RDeleteObjectsOperation();
            for (var j=0; j<jn; j++) {    // Cycle through all necessary deletions
                // Query the entity stored copy back from the document
                //    and use this to delete the entity. See ExDeleteObject.js
                op.deleteObject(document.queryEntity(this.trashCan[j]));
            } // Loop all deletions
            di.applyOperation(op);
        // # ToDo # On groupCasts transfer selection to casted v0.42 ???
        // # Issue # Selecting too many can greatly slow down Qcad
        }
    }

    // Push summary to command history
    if (this.countEntities == 0 || castResult.isFailed()) {    // With no castings
        // If none casted
        if (this.countEntities == 0) {
            qDebug("Nothing casted!? Command terminated");
            EAction.handleUserWarning("Nothing casted!? Command terminated");
        }
        // If castResult.isFailed
        // # Issue Fixed # Without suited entities in selection castResult is not set
        // # Workaround # Also countEntities isNull, 2e test of OR is not processed
        //               Added 'else' to if (castResult.isFailed())
        else if (castResult.isFailed()) {
            qDebug("Casting failed! Command terminated");
            EAction.handleUserWarning("Casting failed! Command terminated");
        }
    }
    else {    // With any castings
        if (!this.beVerbose) {    // Smothered
            qDebug("- - - = * = - - -");
            EAction.handleUserInfo("- - - = * = - - -");

            msg = "Casted " + this.countNewEntities + " entities by casting " + this.countCastpoints + " points";
            qDebug(msg);
            EAction.handleUserInfo(msg);
            msg = "over " + this.countEntities;
            if (this.countEntities == idn) {
                msg += (this.countEntities > 1) ? " entities" : " entity";
            }
            else {
                msg += " of " + idn;
                msg += (idn > 1) ? " entities" : " entity";
            }
            msg += " as ";
            if (this.countEntities == 1 || this.groupCasts ) {
                msg += "one addition";
            }
            else {
                msg += this.countEntities;
                msg += (this.countEntities > 1) ? " addition" : " additions";
            }
            qDebug(msg);
            EAction.handleUserInfo(msg);

            msg = (this.subLayerCasts) ? "on sub layers. " : "on the active layer.";
            qDebug(msg);
            EAction.handleUserInfo(msg);

            if (this.delEntity && jn > 0) {
                msg = "Deleted " + jn;
                msg += (jn > 1) ? " base entities" : " base entity";
                msg += " as one deletion";
                qDebug(msg);
                EAction.handleUserInfo(msg);
            }
        } // Else: not smothered

        // Push command end message to command history
        qDebug("Command end");
        msg = "Casting complete (" + (Date.now() - crono) + "ms)";
        EAction.handleUserMessage(msg);
    }

    // Command end
    this.terminate();
    return;
};

/**
 * Casts painter points local / global.
 *
 * \return Number of casted points
 */
// Sub-script of FlexPainter.beginEvent
FlexPainter.prototype.castPainter = function (shape, painterData) {
    // Faster: local const  // Faster: at top
    const objlength = this.objlength;
    const distFromStart = this.distFromStart;
    const skn = painterData[0][0];    // Number of entries in the dataset
    var countCastpoints = 0;

    // Cycle through all painter definitions
    for (var sk=1; sk<=skn;sk++) {    // Zero omitted = Header
        var newEntityData = [];    // Empty local collector
        var partData = painterData[sk];   // Pick painter data part
        var nominator = partData[0];
        if (nominator.startsWith("Dots")) {
            var dotStringN = 1*nominator.slice(4);    // Isolate dot-string number
            nominator = nominator.substring(0,4);
        }
        if (nominator.startsWith("Nods")) {
            var nodStringN = 1*nominator.slice(4);    // Isolate node-string number
            nominator = nominator.substring(0,4);
        }
        var kn = partData.length - 1;    // Number of painter coordinates
        countCastpoints += kn;

        // Cycle through all painter data parts
        for (var k=1; k<=kn;k++) {    // Zero omitted = header
            var offsetAtDist = partData[k][0];
            var scaledOffsetSize = partData[k][1] * this.scalerY;
            var activeDist = distFromStart + (offsetAtDist * this.scalerX);

            // Catch end crossers
            if (activeDist > objlength) {
//                activeDist = objlength;
                if (!this.isTanCloObj) {
                    qDebug("TooFarCaster"); //non-MSWinTesting
                    if (!this.beVerbose) EAction.handleUserWarning("TooFarCaster"); //MSWinTesting
                    debugger; // ###### Catch this In the act !!!
                      // Faulty! Halt in debugger mode
                    debugger; // ######
                }
            }

            // Use different methods to determine castPoint & castAngle
            switch(this.castingType) {
                case 1:
                    // Over Lines, Arcs & open Splines simply by castPoint on shape
                    //    Lines, Arcs NO hard ending. Splines stiff ending, is no error, avoid crossing
                    // # Issue # IS NOT accurate on Splines, flaw larger rather near an ending?!
                    var castPoint = shape.getPointWithDistanceToStart(activeDist);
                    // # Issue Fixed # Geo closed spline: Cast on begin has angle of ending
                    if (RMath.fuzzyCompare(activeDist, 0.00, RS.PointTolerance)) {
                        // # Workaround # Fixed with offset a tiny bit from start
                        // # Issue # Fixing solution slows center loop
                        // # Issue # Fixing solution counts for all type 1
                        var castAngle = shape.getAngleAt(2*RS.PointTolerance, RS.FromStart);
                        qDebug("Type1BeginCastFix"); //non-MSWinTesting
                        if (!this.beVerbose) EAction.handleUserWarning("Type1BeginCastFix"); //MSWinTesting
                    }
                    else { 
                        var castAngle = shape.getAngleAt(activeDist, RS.FromStart);
                    }
                    break;
                case 2:
                    // Over continuous closed Splines simply by castPoint on shape.
                    //    isTanCloObj, simply restart from zero
                    var castPoint = shape.getPointWithDistanceToStart(activeDist % objlength);
                    var castAngle = shape.getAngleAt(activeDist, RS.FromStart);
                    break;
                case 3:
                    // Over open Polyline & EllipseArc by castPoint on ClosestSegment
                    //    Hard ending, avoid crossing
                    // # Issue Fixed # Geo closed poly: Cast on end has angle of beginning
                    //           As does casting on all vertices = angle at next segment
                    if (RMath.fuzzyCompare(activeDist, objlength, RS.PointTolerance)) {
                        // # Workaround # Fixed with offset a tiny bit from end
                        // # Issue # This IS NOT a tiny bit. SEE also case 4
                        // # Issue # Fixing solution slows center loop
                        qDebug("Type3HugeEndCastFix"); //non-MSWinTesting
                        if (!this.beVerbose) EAction.handleUserWarning("Type3HugeEndCastFix"); //MSWinTesting
                        var castPoint = shape.getPointWithDistanceToStart(objlength - (2000*RS.PointTolerance));
                    }
                    else {
                        var castPoint = shape.getPointWithDistanceToStart(activeDist);
                    }
                    var segmentShape = shape.getSegmentAt(shape.getClosestSegment(castPoint));
                    var castAngle = segmentShape.getAngleAtPoint(castPoint);
                    break;
                case 4:
                    // Over continuous closed Polyline by castPoint on ClosestSegment.
                    //    isTanCloObj, simply restart from zero
                    // # Issue Fixed # Freak BUG casting non dynscaled very near endpoint eg. delta 4e-14, @453.25--7166 on 453.25--717 long
                    if (RMath.fuzzyCompare(activeDist, objlength, RS.PointTolerance)) {
                        // # Workaround # Fixed with catching ClPolyNearEnder and force at full length
                        // # Issue # Fixing solution slows center loop
                        activeDist = objlength;
                        qDebug("ClPolyNearEnderFix"); //non-MSWinTesting
                        if (!this.beVerbose) EAction.handleUserWarning("ClPolyNearEnderFix"); //MSWinTesting
                    };
                    var castPoint = shape.getPointWithDistanceToStart(activeDist % objlength);
                    var segmentShape = shape.getSegmentAt(shape.getClosestSegment(castPoint));
                    var castAngle = segmentShape.getAngleAtPoint(castPoint);
                    break;
                case 5:
                    // Over Circles by equation for castPoint & castAngle.
                    //    Circles have no ending
                    var centerAngle = activeDist / shape.getRadius();
                    var castPoint = shape.getPointAtAngle(centerAngle);
                    var castAngle = centerAngle + this.orthoAngle;
                    break;
                default:
                    // Should not occur, good practices to include
            } // End switch(this.castingType)

            // Cast a new vector
            var castVector = new RVector(castPoint.x - Math.sin(castAngle) * scaledOffsetSize,
                                         castPoint.y + Math.cos(castAngle) * scaledOffsetSize);

            // Catch casting null-vectors
            if (isNull(castVector)) {
                qDebug("Casting a Null-Vector!");
                EAction.handleUserWarning("Casting a Null-Vector!"); //MSWinTesting
                debugger; // ###### Catch this In the act !!!
                    // Faulty! Halt in debugger mode
                debugger; // ######
            }

            // Push casted point to collectors
            switch(nominator) {
                case "Point":    // One point
                case "Line":    // Two points
                case "Poly":    // [Vertex, Bulge, Relative] in an array
                    // # Issue Fixed # addPoly not working with Rvectors
                    // # Workaround # Split castVector back in x and y
                    // https://qcad.org/rsforum/viewtopic.php?t=6618
                    var bulging = partData[k][2];
                    newEntityData.push([castVector.x,castVector.y,bulging]);
                    break;
                case "Spline":    // Points in an array
                    newEntityData.push(castVector);
                    break;
                case "Arc":    // Center point, radius, startAngle, endAngle, reversed
                    newEntityData.push(castVector);
                    // Add radius[2], beginangle[3], endangle[4], reversed[5]
                    newEntityData.push(partData[k][2] * this.scalerY);
                    // # Issue Solved # simple_create.js works with degrees and deg2rad
                    //    Solved with rad2deg(val)
                    newEntityData.push(partData[k][3] + rad2deg(castAngle));
                    newEntityData.push(partData[k][4] + rad2deg(castAngle));
                    newEntityData.push(partData[k][5]);
                    break;
                case "Circle":    // Center point, radius
                    newEntityData.push(castVector);
                    // Add radius[2]
                    newEntityData.push(partData[k][2] * this.scalerY);
                    break;
                case "Dots":    // Push to global splines
                    // Solution not push but add past end
                    if (this.dotStringData.length == dotStringN) {
                        // Start a new dot-string collector with this first item
                        this.dotStringData[this.dotStringData.length] = [castVector];
                    }
                    else {    // Add to existing dot-string collector
                        this.dotStringData[dotStringN][this.dotStringData[dotStringN].length] = castVector;
                    }
                    break;
                case "Nods":    // Push to global polys
                    // Solution not push but add past end
                    var bulging = partData[k][2];
                    // # Issue Solved # Global bulges don't flip
                    //    Solved with flip sign
                    if (bulging != 0.00) {    // When bulging isNOT zero
                        if (this.flipPainter) bulging = -bulging;
                    } // -> Continue with conditioned bulge

                    if (this.nodStringData.length == nodStringN) {
                        // Start a new node-string collector with this first item (double squared brackets)
                        this.nodStringData[this.nodStringData.length] = [[castVector.x,castVector.y,bulging]];
                    }
                    else {    // Add to existing node-string collector
                        this.nodStringData[nodStringN][this.nodStringData[nodStringN].length] = [castVector.x,castVector.y,bulging];
                    }
                    break;
                default:
                    // Should not occur, good practices to include
            } // End switch(nominator)

        } // Loop all painter data parts

        // Cast new entity with local collector
        // # Issue Fixed # Is no error with empty newEntityData, may eventually lead to AppCrash
        // # Issue # Speed: Replace simple_create calls with function return addShape
        if (!isNull(newEntityData)) {    // # Workaround # Catch null-vectors, only cast with data
            switch(nominator) {
                case "Spline":    // Cast open spline with array of collected casted fitpoints
                    addSpline(newEntityData, false);
                    break;
                case "Line":    // Cast line with collected casted ending points
                    addLine(
                        newEntityData[0],
                        newEntityData[1]);
                    break;
                case "Point":    // Cast point at casted point
                    addPoint(newEntityData[0]);
                    break;
                case "Arc":    // Cast arc at casted center point
                    addArc(
                        newEntityData[0],
                        newEntityData[1],
                        newEntityData[2],
                        newEntityData[3],
                        newEntityData[4]);
                    break;
                case "Circle":    // Cast circle at casted center point
                    addCircle(
                        newEntityData[0],
                        newEntityData[1]);
                    break;
                case "Poly":    // Cast open poly non-relative with array of collected: casted vertices & bulges
                    addPolyline(newEntityData, false, false);
                default:
                    // Dots and Nods are not handled local
            } // End switch(nominator)
        } // Else: cast nothing

    } // Loop all painter definitions
    return countCastpoints;
};

/**
 * Shows the painter dialog.
 *
 * \return True if the dialog was accepted, false if it was cancelled.
 */
// Based on the scaling dialog Widget
FlexPainter.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(FlexPainter.includeBasePath, "FlexPainterDialog.ui");
    var widgets = getWidgets(dialog);

    // Initiate the dialog comboboxes:
    //    Before any dialog change functions is active
    this.initWidgetsCombo(dialog);

    // Initiate the dialog change functions:
    // # Issue Fixed # Immediately active, and not fully functional yet
    //    The order of initWidgets and restoreState has pro an cons
    // # Workaround # Chosen for initWidgetsCombo--initWidgets--restoreState
    this.initWidgets(dialog);

    // Load persistent dialog entries:
    //    Restoring old values will trigger dialog change functions
    WidgetFactory.restoreState(dialog);

    // Detect first load: 
    //    A zero-width painter never makes sense
    if (widgets["MainWidth"].getValue() == 0.00) {    // Is the first load
        // Painters, Insertions, Icons and Prefs are by default in UI
        qDebug("Initial Use: " + RUnit.unitToName(this.units)); //non-MSWinTesting
        EAction.handleUserMessage("Initial Use: " + RUnit.unitToName(this.units)); //MSWinTesting

        // Remember using current document units:
        widgets["UnitsLabel"].text = RUnit.unitToName(this.units);

        // Initiate default painter set:
        //    Normally done with:
        //    this.PainterSetInit("Default");
        // # Workaround # 1: Tried with success:
        //    widgets["PainterSelection"].setCurrentText("Default");
        // # Issue Solved # 2: The Dialog starts with the non-existent set "Default"
        //    Solved with "CurtainRopeProto". Offcourse
        widgets["PainterSelection"].setCurrentText("CurtainRopeProto");

        // Set an appropriate default painter width:
        //    The idee behind this is: Metric starts with 10 units
        //    10mm with mm, 10m with m, 10km with km
        //    Imperial start with an equivalent counterpart
        switch(this.units) {
            case 4:
            default:    //   and all not specified (Metric)
                widgets["MainWidth"].setValue(10.00);
        // # Issue Fixed # 1: Not functional for first use
        //    This activates the change function and fails again for the same reason the get's are created
        //    And this did not occur with WidgetFactory.restoreState without any former use
        //    Fixed with setCurrentText some lines higher
                break;
            case 1:    // 1 Inch 25.4mm => 10mm
            case 8:    // 1 Microinch 25.4nm => 10nm
            case 9:    // 1 Mil 25.4micron => 10micron
                widgets["MainWidth"].setValue(0.3937);
                break;
            case 2:    // 1 Foot 0.3048m => 10m
                widgets["MainWidth"].setValue(32.8084);
                break;
            case 3:    // 1 Mile 1.609km => 10km
                widgets["MainWidth"].setValue(6.215);
                break;
            case 10:    // 1 Yard 0.9144m => 10m
                widgets["MainWidth"].setValue(10.9361);
                break;
        } // End switch(this.units)
        // 'PreserveLook' is set by default
        //    The change functions are active
        //    Values in MainPainterBox will auto adapt
    }
    else {    // Not the first load
        // When former used units differs adapt dimensions appropriately:
        if (widgets["UnitsLabel"].text != RUnit.unitToName(this.units)) {
            // When current or former is non metric apply correction:
            if (!RUnit.isMetric(RUnit.parseUnit(widgets["UnitsLabel"].text)) || !RUnit.isMetric(this.units)) {
                qDebug("ReCalcPersistentDims"); //non-MSWinTesting
                EAction.handleUserMessage("ReCalcPersistentDims"); //MSWinTesting
                var correction = RUnit.convert(1.00, this.units, RUnit.parseUnit(widgets["UnitsLabel"].text));
                // Apply correction on all 3 preferences separately if relevant:
                if (widgets["PreserveLook"].checked===false) {    // Not base9
                    // # Issue Fixed # Dialog RMathLineEdit not active yet.
                    // #    .getValue returns no real values
                    // #    .text may return a formula
                    // # Workaround # RMath.eval(text)
                    // # Issue # Not checked if its a number
                    widgets["MainWidth"].setValue(RMath.eval(widgets["MainWidth"].text) / correction);

                    // Values in MainPainterBox are prevented to adapt proportionally:
                    widgets["MainLengthX"].setValue(RMath.eval(widgets["MainLengthX"].text) / correction);
                    widgets["MainStepX"].setValue(RMath.eval(widgets["MainStepX"].text) / correction);
                } 
                else {    // is base9, apply correction and adapt base9:
                    widgets["MainWidth"].setValue(RMath.eval(widgets["MainWidth"].text) / correction);
                    // Values in MainPainterBox will auto adapt
                }
            } // Else: Both metric: Do nothing

            // Remember using current document units:
            widgets["UnitsLabel"].text = RUnit.unitToName(this.units);
        } // Else: No change: Do nothing

        // # Issue Solved # When PainterSelection is equal former use
        //    only PainterBox checked-state is included in restoreState(dialog)
        //    Later found Q&A @ https://www.qcad.org/bugtracker/index.php?do=details&task_id=1863
        //    Without change in PainterSelection, PainterBox enabled-state can not adapt
        //    Solved with no current text and currentIndex = -1 in UI combo
        //    restoreState(dialog) will set former painter set used
        //    PainterBox enabled-state will auto adapt by change function
    }  // End first load detection
//debugger;

    // Repeat Dialog untill entries are flawless
    do {
    // # Issue # Simple & Dirty! Surely there are neater ways to do this
        var errmsg = undefined;    // Reset former error

        // Activate FlexPainter dialog modal
        if (!dialog.exec()) {
            dialog.destroy();
            EAction.activateMainWindow();
            return false;   // Dialog rejected
        }

        // Retrieve user numerical preferences
        // -----------------------------------
        // A) Get and validate mainScaleY entry:
        this.mainScaleY = Math.abs(widgets["MainWidth"].getValue()) / 9;
        // # Issue # Not checked if its a number or positif

        // Limit mainScaleY:
        if (this.mainScaleY > 111) {    // Upper limit
            this.mainScaleY = 111;
            errmsg = "! Width crossed upper limit !";
        }
        if (this.mainScaleY < 0.01) {    // Lower limit
            this.mainScaleY = 0.01;
            errmsg = "! Width crossed lower limit !";
        }

        // Push any 'width error' warning to command history:
        if (!isNull(errmsg)) {    // when a width error
            qDebug(errmsg);
            EAction.handleUserWarning(errmsg);
            errmsg = "!";    // Remember there was an error
        } // End is length error

        // Text entries stay text, re-parse value to UI as text:
        widgets["MainWidth"].setText(this.mainScaleY * 9);

        // B) Get and validate MainPainterBox entries:
        if (widgets["PreserveLook"].checked===true) {
            this.preserveLook = true;
            // Preserve the look with uniform scaling:
            this.mainScaleX = this.mainScaleY;
            this.mainScaleS = this.mainScaleY;
        }
        else {    // 'PreserveLook' NOT checked
            this.preserveLook = false;
            // Get and validate mainScaleX entry:
            // Painter set can have main painter length zero, avoid Div0
            if (this.mainData[0][2] == 0.00){
                this.mainScaleX = 1.00;    // Just to avoid zero or Div0 later on
                if (widgets["MainLengthX"].getValue() > 0.00) {
                // # Issue # Not checked if its a number
                    errmsg = "! Is zero-length painter !";
                }
            }
            else {    // Not a null-length painter 
                this.mainScaleX = Math.abs(widgets["MainLengthX"].getValue()) / this.mainData[0][2];
        // # Issue # Not checked if its a number or positif
            }

            // Limit mainScaleY:
            if (this.mainScaleX > 111) {    // Upper limit
                this.mainScaleX = 111;
                errmsg = "! Length crossed upper limit !";
            }
            if (this.mainScaleX < 0.01) {    // Lower limit
                this.mainScaleX = 0.01;
                errmsg = "! Length crossed lower limit !";
            }

            // Push any 'length error' warning to command history
            if (!isNull(errmsg)) {
                if (errmsg != "!") {    // when a length error
                    qDebug(errmsg);
                    EAction.handleUserWarning(errmsg);
                    errmsg ="!"    // Remember there was an error
                } // End is length error
            } // End push error

            // Text entries stay text, re-parse value to UI as text:
            widgets["MainLengthX"].setText(this.mainData[0][2] * this.mainScaleX);

            // Get and validate mainScaleS entry
            this.mainScaleS = Math.abs(widgets["MainStepX"].getValue()) / this.mainData[0][3];
            // # Issue # Not checked if its a number or positif
            if (this.mainScaleS > 111) {    // Upper limit
                this.mainScaleS = 111;
                errmsg = "! Stepsize crossed upper limit !";
            }
            if (this.mainScaleS < 0.01) {    // Lower limit
                this.mainScaleS = 0.01;
                errmsg = "! Stepsize crossed lower limit !";
            }

            // Push stepsize error warning to command history:
            if (!isNull(errmsg)) {
                if (errmsg != "!") {    // when a stepsize error
                    qDebug(errmsg);
                    EAction.handleUserWarning(errmsg);
                    errmsg ="!"    // Remember there was an error
                } // End is stepsize error
            } // End push error

            // Text entries stay text, re-parse value to UI as text:
            widgets["MainStepX"].setValue(this.mainData[0][3] * this.mainScaleS);
        } // End validate MainPainterBox
    } // Loop untill entries are flawless
    while (!isNull(errmsg));

    // Retrieve user Closed Forms shifting preference (0-100)
    this.closeShift = widgets["CloseShift"].value / 100;

    // Retrieve user casting preferences
    this.flipPainter = (widgets["FlipPainter"].checked===true);
    this.groupCasts = (widgets["GroupCasts"].checked===true);
    this.subLayerCasts = (widgets["SubLayerCasts"].checked===true);
    this.doBeginApex = (widgets["DoBeginApex"].checked===true);
        // Only do if definition has length (doubling the checked/enabled lock)
        if (this.beginApexData[0][2] === 0) this.doBeginApex = false;
    this.doEndApex = (widgets["DoEndApex"].checked===true);
        // Only do if definition has length (doubling the checked/enabled lock)
        if (this.endApexData[0][2] === 0) this.doEndApex = false;
    this.doInserts = (widgets["DoInserts"].checked===true);
        // Only do if definition has length (doubling the checked/enabled lock)
        if (this.knotData[0][2] === 0) this.doInserts = false;
    // # ToDo # Temporary fixed insertions for testing
    //    Should be zero with doInserts = false
    this.insertions = 0;
    this.beVerbose = (widgets["BeVerbose"].checked===true);
    this.delEntity = (widgets["DelEntity"].checked===true);

    // Flipping is inverse scaling in Y
    if (this.flipPainter) this.mainScaleY = -(this.mainScaleY);

    // Retrieve user Open Forms scaling preferences
    this.factorsurPlus = 0.00;
    if (widgets["ForcedDyn"].checked===true) {
        this.forcedDyn = true;    // Start with no surPlusGabs length
    }
    else {    // Not forced to scale dynamically: May have some surPlusGabs length
        if (widgets["AlignCenter"].checked===true) {
            this.factorsurPlus = 0.50;    // Start with half the surPlusGabs length
        }
        else if (widgets["AlignEnd"].checked===true) {
            this.factorsurPlus = 1.00;    // Start with the full surPlusGabs length
        } // Else: ("AlignStart") or start with none
    }

    // Retrieve user painter set selection
    //    Both text based
    this.painterSet = widgets["PainterSelection"].currentText;
    this.painterKnot = widgets["KnotSelection"].currentText;

    // Push smothered painter summary to command history
    if (!this.beVerbose) {
        EAction.handleUserInfo("Version Beta 0.42e");
        EAction.handleUserInfo("Painter set: " + this.painterSet);
        EAction.handleUserInfo("Width: " + (9 * this.mainScaleY));
        EAction.handleUserInfo("Length: " + (this.mainData[0][2] * this.mainScaleX));
        EAction.handleUserInfo("Stepsize: " + (this.mainData[0][3] * this.mainScaleS));
        EAction.handleUserInfo("- - - = * = - - -");
    }

    // Force persistent dialog entries, save them and finish
    widgets["BeVerbose"].checked = true;    // Super persistent =checked
    widgets["DelEntity"].checked = false;    // Super persistent =unchecked
    WidgetFactory.saveState(dialog);
    dialog.destroy();
    return true;   // Dialog accepted
};

/**
 * Add an Active Layer.
 */
// Based on ExAddLayer.js
FlexPainter.prototype.addActiveLayer = function(layerName, document, di) {
    if (!document.hasLayer(layerName)) {
        var op = new RModifyObjectsOperation();
        // Set tool title used for undo/redo information:
        op.setText(qsTr("Add Active SubLayer"));
        var linetypeId = document.getLinetypeId("CONTINUOUS");
        // new RLayer (document, name, frozen & locked = false, color, linetypeId, lineweight, off)
        var layer = new RLayer(document, layerName, false, false, new RColor("green"), linetypeId, RLineweight.Weight013, false);
        op.addObject(layer);
        di.applyOperation(op);
        EAction.handleUserInfo(qsTr("FP added layer:"));
        EAction.handleUserInfo(">  " + layerName);
    }
    di.setCurrentLayer(layerName);
};

/**
 * Initiate the FlexPainter dialog change functions.
 */
// Based on the scaling dialog Widget
FlexPainter.prototype.initWidgets = function(widget, postfix) {

    if (isNull(postfix)) {    // Unknown purpose, left as was
        postfix = "";
    }
//debugger;
    // HERE IN SCOPE (but static)
        // widget (parsed)
        // postfix (parsed)
        var widgets = getWidgets(widget);
        // this.beVerbose
        // FlexPainter.includeBasePath

    // HERE NOT IN SCOPE
        // this.PainterSetInit("whatever")
        // this.mainData[0][(0,1)]
        // this.beginApexData[0][0]
        // this.endApexData[0][0]
        // this.knotData[0][0]



    // On PainterSelection change:
    // Continuously: Adapt Preview icons
    //               Re-initiate painter set & Prefs
    //               Force base9 and parse MainWidth to MainPainterBox
    widgets["PainterSelection"].currentTextChanged.connect(
                function(currentText) {
                    // # ToDo # Check set data named 'currentText' and report if none
                    // Adapt icons:
                    widgets["PreviewPainters"].icon = new QIcon(FlexPainter.includeBasePath + "/Icons/" + currentText + ".svg");
                    // # ToDo # Only one icon set yet. currentText Hardcoded here as "CurtainRopeProto"
                    widgets["PreviewKnot"].icon = new QIcon(FlexPainter.includeBasePath + "/Icons/" + "CurtainRopeProto" + "Knot" +".svg");
//debugger;
                    // Re-initiate painter set:
                    // # Issue Fixed # FlexPainter.PainterSetInit() out of scope
                    // # Workaround # getPainterSet functions (calls PainterSetInit)
                    getPainterSet(currentText, widgets["BeVerbose"].checked===true);

                    // Adapt for Apexes and Insertions:
                    // # Issue Fixed # Painter data out of scope
                    // # Workaround # getDoBeginApex, getDoEndApex and getDoInserts functions (return boolean)
                    widgets["DoBeginApex"].setEnabled(getDoBeginApex());
                    widgets["DoEndApex"].setEnabled(getDoEndApex());
                    widgets["DoInserts"].setEnabled(getDoInserts());

                    // Width remains: Force MainPainterBox to base9 by PreserveLook:
                    // # Issue # Simple & Dirty! Toggle twice to get the correct state and actions
                    widgets["PreserveLook"].checked = false
                    widgets["PreserveLook"].checked = true
                        // OR The same actions as in widgets["PreserveLook"].toggled.connect when ischecked
                });

    // On MainWidth change:
    // Continuously: Dismiss negative entries
    //               With PreserveLook parse entries in MainWidth to MainPainterBox
    widgets["MainWidth"].textChanged.connect(
                function(text) {
                    // Don't allow entry to start with 'minus' and some kind of digit:
                    widgets["MainWidth"].text = text.replace(/^-(\d||[\.\,]\d)/, "\$1");

                    // With PreserveLook parse MainWidth to MainPainterBox base9:
                    if (widgets["PreserveLook"].checked===true) {
                        var scaleW = widgets["MainWidth"].getValue() / 9;    // can be NaN
                        // # Issue Fixed # Painter data out of scope
                        // # Workaround # getBase9Length and getBase9Stepsize functions (return dimension)
                        widgets["MainLengthX"].setValue(getBase9Length() * scaleW);
                        widgets["MainStepX"].setValue(getBase9Stepsize() * scaleW);
                    }
                });

    // On PreserveLook toggled: (can be on or off)
    // Continuously: Adapt PreserveLook icon
    //               When checked parse MainWidth to MainPainterBox base9
    //               Adapt for Null-Length painter if applicable
    widgets["PreserveLook"].toggled.connect(
                function(checked) {
                    // Adapt Icon:
                    if (checked) {    // Toggled to Checked
                        widgets["PreserveLook"].icon = new QIcon(FlexPainter.includeBasePath + "/PreserveLookOn" + postfix + ".svg");
                    }
                    else {    // Toggled to Un-checked
                        widgets["PreserveLook"].icon = new QIcon(FlexPainter.includeBasePath + "/PreserveLookOff" + postfix + ".svg");
                    }

                    // When checked parse MainWidth to MainPainterBox base9:
                    if (checked) {
                        var scaleW = widgets["MainWidth"].getValue() / 9;    // can be NaN
                        // # Issue Fixed # Painter data out of scope
                        // # Workaround # getBase9Length and getBase9Stepsize functions (return dimension)
                        widgets["MainLengthX"].setValue(getBase9Length() * scaleW);
                        widgets["MainStepX"].setValue(getBase9Stepsize() * scaleW);
                    }

                    // Adapt for Null-Length painter:
                    // # Issue Fixed # Painter data out of scope
                    // # Workaround # getBase9Length function (return dimension)
                    if (!checked && getBase9Length() == 0.00) {
                        widgets["LabelLength"].setEnabled(false);
                        widgets["MainLengthX"].setEnabled(false);
                    }
                });

    // On MainLength change:
    // Continuously: Dismiss negative entries
    //               Adapt for Null-Length painter if applicable
    widgets["MainLengthX"].textChanged.connect(
                function(text) {
                    // Don't allow entry to start with 'minus' and some kind of digit:
                    widgets["MainLengthX"].text = text.replace(/^-(\d||[\.\,]\d)/, "\$1");

                    // Adapt for Null-Length painter:
                    // # Issue Fixed # Painter data out of scope
                    // # Workaround # getBase9Length function (return dimension)
                    if (getBase9Length() == 0.00) {
                        widgets["MainLengthX"].text = "0";
                        widgets["LabelLength"].setEnabled(false);
                        widgets["MainLengthX"].setEnabled(false);
                    }
                });

    // On MainStepX change:
    // Continuously dismiss negative entries
    widgets["MainStepX"].textChanged.connect(
                function(text) {
                    // Don't allow entry to start with 'minus' and some kind of digit:
                    widgets["MainStepX"].text = text.replace(/^-(\d||[\.\,]\d)/, "\$1");
                });
};

/**
 * Get functions for dialog change functions.
 */
// Based on OrthogonalProjections.js Line 194 & 261
// https://qcad.org/rsforum/viewtopic.php?t=6626
// # Issue # Can't explain this but while in debugger mode:
// Found FlexPainter under 'this' but no painter data
// Found painter data under 'this.FlexPainter.prototype.xyz'
// I was astonished that it worked...
// # Issue # As I am not mistaken this are Global Functions !!!
getPainterSet = function(painterSet, beVerbose) {
    this.FlexPainter.prototype.PainterSetInit(painterSet, beVerbose);
    // # Issue # Painter Data has different scope but is functional
};
getBase9Length = function() {
    return this.FlexPainter.prototype.mainData[0][2];
};
getBase9Stepsize = function() {
    return this.FlexPainter.prototype.mainData[0][3];
};
getDoBeginApex = function() {
    return (this.FlexPainter.prototype.beginApexData[0][2] > 0);
};
getDoEndApex = function() {
    return (this.FlexPainter.prototype.endApexData[0][2] > 0);
};
getDoInserts = function() {
    return (this.FlexPainter.prototype.knotData[0][2] > 0);
};

/**
 * Initiate painter set data.
 *
 * \return painterSet + "done" for now, never fails to get a set. # ToDo # Sources
 */
// Sub-script of FlexPainter.beginEvent
FlexPainter.prototype.PainterSetInit = function(painterSet, beVerbose) {
    // ** HARDCODED in Arrays (Works similar as objects) **
    qDebug("Asked for: " + painterSet);  //non-MSWinTesting
    // Smothered
    if (!beVerbose) EAction.handleUserMessage("Asked for: " + painterSet); //MSWinTesting
    // # Issue # this.verbose out of scope
    // # Issue # Painter Data has different scope but is functional

    // ** ADJUSTABLE DATA SETS **
    //    Local casting:
    //        Spline [x1,y1],[x2,y2],[x3...  Spline fitpoints, open type
    //        Poly [x1,y1,B1],[x2,y2,B2],[x3...  Poly vertices & bulging, open type
    //        Line [x1,y1],[x2,y2]
    //        Point [x,y]
    //        Circle [x,y,r]
    //        Arc [x1,y1,r,a0,a1,Rev] (Angles in degrees)
    //    Global casting: 00-99 individual Splines and/or Polys
    //        Dots## [x1,y1],[x2,y2],[x3...  Spline fitpoints, open/closed type as base entity
    //        Nods## [x1,y1,B1],[x2,y2,B2],[x3...  Poly vertices & bulging, open/closed type as base entity
    //
    //    Note on Polys: Morphing is in se non-uniform scaling
    //        Bulging does not adapt, it is added for completeness and may act weird
    //        The real distance between casted points affects how wide the bulge actually is
    //        The painter stepsize also affects the last bulging of every set
    //        If of any use, tangent scaling travers functions can be found in scale.js by CVH
    //        # ToDo # Fix poly bulging !!!

    switch(painterSet) {    // * = fixed for all
    case "CurtainRopeProto":
        // # ToDo # Change apex chains to Poly if applicable
        // # ToDo # Split proto kinds
    default:
        this.beginApexData = [[29,0,12.6000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Spline",[11.3175,4.1786],[11.2744,4.3393],[11.1568,4.4569],[10.9961,4.5000],[10.8354,4.4569],[10.7177,4.3393],[10.6746,4.1786]]);
            this.beginApexData.push(["Spline",[8.1032,4.1786],[7.5600,-2.8607]]);
            this.beginApexData.push(["Spline",[10.0318,4.1786],[9.9887,4.3393],[9.8711,4.4569],[9.7104,4.5000],[9.5496,4.4569],[9.4320,4.3393],[9.3889,4.1786]]);
            this.beginApexData.push(["Spline",[8.7461,4.1786],[8.7030,4.3393],[8.5854,4.4569],[8.4246,4.5000],[8.2639,4.4569],[8.1463,4.3393],[8.1032,4.1786]]);
            this.beginApexData.push(["Spline",[8.7461,4.1786],[8.1032,-4.1786]]);
            this.beginApexData.push(["Line",[11.9604,4.1786],[11.9604,-2.9663]]);
            this.beginApexData.push(["Spline",[11.3175,-4.1786],[11.3606,-4.3393],[11.4782,-4.4569],[11.6389,-4.5000],[11.7996,-4.4569],[11.9173,-4.3393],[12.6643,-3.5281]]);
            this.beginApexData.push(["Spline",[12.6643,-3.5281],[11.9604,-2.9663]]);
            this.beginApexData.push(["Spline",[1.0286,-5.3036],[2.3143,-4.4679],[4.2429,-3.6321],[5.8500,-3.3750]]);
            this.beginApexData.push(["Spline",[6.8143,3.8571],[6.4929,3.8571],[2.9571,5.1429],[0.7071,6.4286],[0.0855,3.4413],[0.0032,0.0000],[0.0855,-3.4413],[0.7071,-6.4286],[2.9571,-5.1429],[6.4929,-3.8571],[6.8143,-3.8571]]);
            this.beginApexData.push(["Spline",[0.9643,-4.2107],[1.9929,-3.6321],[3.2786,-3.1821],[4.5643,-2.9571]]);
            this.beginApexData.push(["Spline",[1.0286,-3.1500],[2.0571,-2.7321],[2.8286,-2.5393]]);
            this.beginApexData.push(["Line",[6.8143,-3.8571],[6.8143,3.8571]]);
            this.beginApexData.push(["Line",[7.4604,-4.1786],[7.4604,4.1786]]);
            this.beginApexData.push(["Spline",[11.3175,4.1786],[10.6746,-4.1786]]);
            this.beginApexData.push(["Spline",[10.0318,4.1786],[9.3889,-4.1786]]);
            this.beginApexData.push(["Spline",[11.8607,2.8607],[11.3175,-4.1786]]);
            this.beginApexData.push(["Spline",[8.1032,-4.1786],[8.0602,-4.3393],[7.9425,-4.4569],[7.7818,-4.5000],[7.6211,-4.4569],[7.5034,-4.3393],[7.4604,-4.1786]]);
            this.beginApexData.push(["Spline",[10.6746,4.1786],[10.0318,-4.1786]]);
            this.beginApexData.push(["Spline",[10.6746,-4.1786],[10.6316,-4.3393],[10.5139,-4.4569],[10.3532,-4.5000],[10.1925,-4.4569],[10.0748,-4.3393],[10.0318,-4.1786]]);
            this.beginApexData.push(["Spline",[9.3889,-4.1786],[9.3459,-4.3393],[9.2282,-4.4569],[9.0675,-4.5000],[8.9068,-4.4569],[8.7891,-4.3393],[8.7461,-4.1786]]);
            this.beginApexData.push(["Spline",[9.3889,4.1786],[8.7461,-4.1786]]);
            this.beginApexData.push(["Spline",[11.9604,4.1786],[11.9173,4.3393],[11.7996,4.4569],[11.6389,4.5000],[11.4782,4.4569],[11.3606,4.3393],[11.3175,4.1786]]);
            this.beginApexData.push(["Spline",[10.6746,4.1786],[10.6316,4.3393],[10.5139,4.4569],[10.3532,4.5000],[10.1925,4.4569],[10.0748,4.3393],[10.0318,4.1786]]);
            this.beginApexData.push(["Spline",[9.3889,4.1786],[9.3459,4.3393],[9.2282,4.4569],[9.0675,4.5000],[8.9068,4.4569],[8.7891,4.3393],[8.7461,4.1786]]);
            this.beginApexData.push(["Spline",[8.1032,4.1786],[8.0602,4.3393],[7.9425,4.4569],[7.7818,4.5000],[7.6211,4.4569],[7.5034,4.3393],[7.4604,4.1786]]);
            this.beginApexData.push(["Spline",[8.7461,-4.1786],[8.7030,-4.3393],[8.5854,-4.4569],[8.4246,-4.5000],[8.2639,-4.4569],[8.1463,-4.3393],[8.1032,-4.1786]]);
            this.beginApexData.push(["Spline",[11.3175,-4.1786],[11.2744,-4.3393],[11.1568,-4.4569],[10.9961,-4.5000],[10.8354,-4.4569],[10.7177,-4.3393],[10.6746,-4.1786]]);
            this.beginApexData.push(["Spline",[10.0318,-4.1786],[9.9887,-4.3393],[9.8711,-4.4569],[9.7104,-4.5000],[9.5496,-4.4569],[9.4320,-4.3393],[9.3889,-4.1786]]);
        this.beginData = [[4,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
            this.beginData.push(["Line",[0.0000,2.1437],[0.0032,-2.1437]]);
            this.beginData.push(["Spline",[0.0032,-2.1437],[1.4047,-3.3837],[1.8885,-3.8107],[3.3783,-4.5514],[5.0389,-4.4480],[6.4286,-3.5309]]);
            this.beginData.push(["Spline",[6.4286,-3.5309],[4.8198,-2.1109],[3.2143,-0.6936],[1.6088,0.7236],[0.0000,2.1437]]);
            this.beginData.push(["Spline",[2.7321,-2.5714],[3.8912,-3.5028],[5.0389,-4.4480]]);
        this.mainData = [[4,1,12.8571,6.4286,"Slanted"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, painterType, .......
            this.mainData.push(["Spline",[0.0032,3.5281],[2.0817,1.6934],[4.1601,-0.1413],[6.2386,-1.9760],[7.8333,-3.3837],[8.3170,-3.8107],[9.8069,-4.5514],[11.4675,-4.4480],[12.8539,-3.5281]]);
            this.mainData.push(["Spline",[12.8539,-3.5281],[10.7787,-1.6898],[8.6970,0.1413],[6.8286,1.7957],[5.0221,3.3853],[4.5401,3.8107],[3.0503,4.5514],[1.3896,4.4480],[0.0032,3.5281]]);
            this.mainData.push(["Spline",[9.1607,-2.5714],[10.3198,-3.5028],[11.4675,-4.4480]]);
            this.mainData.push(["Dots00",[0.0000,4.2337],[1.4464,4.8607],[3.375,4.8607],[5.7857,4.0571]]);
        this.endData = [[12,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Spline",[-6.4286,3.5281],[-4.8222,2.1102],[-3.2159,0.6922],[-1.6096,-0.7258],[0.0000,-2.1466]]);
            this.endData.push(["Line",[0.0000,-2.1466],[0.0000,2.1380]]);
            this.endData.push(["Spline",[0.0000,2.1380],[-1.4097,3.3853],[-1.8917,3.8107],[-3.3815,4.5514],[-5.0422,4.4480],[-6.4286,3.5281]]);
            // - - - - CVH mark - - - - 
            this.endData.push(["Spline",[-0.1284,0.0475],[-0.1284,0.0550],[-0.1246,0.0775],[-0.1146,0.0875],[-0.0896,0.0875],[-0.0796,0.0775],[-0.0759,0.0550],[-0.0759,0.0475]]);
            this.endData.push(["Spline",[-0.0759,0.0475],[-0.1271,0.0300]]);
            this.endData.push(["Spline",[-0.1271,0.0300],[-0.0771,0.0050]]);
            this.endData.push(["Spline",[-0.0771,0.0050],[-0.0771,-0.0700]]);
            this.endData.push(["Spline",[-0.0771,-0.0700],[-0.0896,-0.0700]]);
            this.endData.push(["Spline",[-0.0896,-0.0200],[-0.1271,-0.0200]]);
            this.endData.push(["Spline",[-0.1084,-0.0200],[-0.1084,-0.0450]]);
            this.endData.push(["Spline",[-0.0896,-0.0450],[-0.1271,-0.0450]]);
            // - - - - CVH mark - - - - -
            this.endData.push(["Dots00",[-6.4286,4.2337],[-4.9821,4.8607],[-3.0536,4.8607],[-0.6429,4.0571],[0.0000,4.2337]]);
        this.endApexData = [[25,1,12.8571]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Line",[1.2825,-4.1786],[1.2825,4.1786]]);
            this.endApexData.push(["Line",[0.6396,-4.1786],[0.6396,2.9663]]);
            this.endApexData.push(["Spline",[1.2825,4.1786],[1.2394,4.3393],[1.1218,4.4569],[0.9611,4.5000],[0.8004,4.4569],[0.6827,4.3393],[-0.0643,3.5281]]);
            this.endApexData.push(["Spline",[-0.0643,3.5281],[0.6396,2.9663]]);
            this.endApexData.push(["Spline",[5.7857,-3.8571],[6.1071,-3.8571],[9.6429,-5.1429],[11.8929,-6.4286]]);
            this.endApexData.push(["Spline",[5.7857,3.8571],[6.1071,3.8571],[9.6429,5.1429],[11.8929,6.4286]]);
            this.endApexData.push(["Spline",[12.5145,-3.4413],[11.2179,-2.9250],[9.8036,-2.5714]]);
            this.endApexData.push(["Spline",[11.8929,6.4286],[12.8539,0.0000],[11.8929,-6.4286]]);
            this.endApexData.push(["Spline",[12.3223,-4.4512],[10.9286,-3.7929],[9.6429,-3.2786],[8.0357,-2.9571]]);
            this.endApexData.push(["Spline",[12.1096,-5.4547],[10.2857,-4.5000],[8.3571,-3.6643],[7.0714,-3.4071]]);
            this.endApexData.push(["Line",[5.1396,4.1786],[5.1396,-4.1786]]);
            this.endApexData.push(["Line",[3.8539,4.1786],[3.8539,-4.1786]]);
            this.endApexData.push(["Spline",[4.4968,-4.1786],[4.5398,-4.3393],[4.6575,-4.4569],[4.8182,-4.5000],[4.9789,-4.4569],[5.0966,-4.3393],[5.1396,-4.1786]]);
            this.endApexData.push(["Spline",[3.2111,-4.1786],[3.2541,-4.3393],[3.3718,-4.4569],[3.5325,-4.5000],[3.6932,-4.4569],[3.8109,-4.3393],[3.8539,-4.1786]]);
            this.endApexData.push(["Line",[2.5682,4.1786],[2.5682,-4.1786]]);
            this.endApexData.push(["Spline",[1.9254,-4.1786],[1.9684,-4.3393],[2.0861,-4.4569],[2.2468,-4.5000],[2.4075,-4.4569],[2.5252,-4.3393],[2.5682,-4.1786]]);
            this.endApexData.push(["Spline",[0.6396,-4.1786],[0.6827,-4.3393],[0.8004,-4.4569],[0.9611,-4.5000],[1.1218,-4.4569],[1.2394,-4.3393],[1.2825,-4.1786]]);
            this.endApexData.push(["Line",[4.4968,4.1786],[4.4968,-4.1786]]);
            this.endApexData.push(["Spline",[1.9254,4.1786],[1.9684,4.3393],[2.0861,4.4569],[2.2468,4.5000],[2.4075,4.4569],[2.5252,4.3393],[2.5682,4.1786]]);
            this.endApexData.push(["Spline",[3.2111,4.1786],[3.2541,4.3393],[3.3718,4.4569],[3.5325,4.5000],[3.6932,4.4569],[3.8109,4.3393],[3.8539,4.1786]]);
            this.endApexData.push(["Spline",[4.4968,4.1786],[4.5398,4.3393],[4.6575,4.4569],[4.8182,4.5000],[4.9789,4.4569],[5.0966,4.3393],[5.1396,4.1786]]);
            this.endApexData.push(["Line",[3.2111,4.1786],[3.2111,-4.1786]]);
            this.endApexData.push(["Line",[1.9254,4.1786],[1.9254,-4.1786]]);
            this.endApexData.push(["Line",[5.7857,-3.8571],[5.7857,3.8571]]);
            this.endApexData.push(["Dots01",[-0.2327,-4.4996],[-1.5183,-5.6245],[-2.6432,-5.7852],[-4.5716,-5.4638],[-4.5716,-5.1424],[-2.6432,-5.3031],[-0.2327,-4.1782]]);
        this.knotData = [[0,0,0.0000,1,50.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        // # ToDo # 1 insertions, insertPoint 50% with length zero to work without knots
        //    this.knotData.push([[0.0,0.0],[0.0,0.0],....]);
        break;
    case "GreekMeander14":  // Not implemented
        this.beginApexData = [[4,2,1.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0,4.5,0.0],[5.7857,4.5,0.0]]);
            this.beginApexData.push(["Poly",[5.7857,1.9286],[2.5714,1.9286],[2.5714,-3.2143],[1.2857,-3.2143],[1.2857,3.2143],[5.7857,3.2143]]);
            this.beginApexData.push(["Line",[0.0,4.5],[0.0,-4.5]]);
            this.beginApexData.push(["Nods01",[0.0,-4.5,0.0],[5.7857,-4.5,0.0]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,2,8.0000,8.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[8.0,4.5,0.0]]);
            this.mainData.push(["Poly",[0.0,3.5],[6.5,3.5],[6.5,-1.5],[3.5,-1.5],[3.5,0.5],[2.5,0.5],[2.5,-2.5],[7.5,-2.5],[7.5,3.5],[8.0,3.5]]);
            this.mainData.push(["Poly",[8.0,-3.5],[1.5,-3.5],[1.5,1.5],[4.5,1.5],[4.5,-0.5],[5.5,-0.5],[5.5,2.5],[0.5,2.5],[0.5,-3.5],[0.0,-3.5]]);
            this.mainData.push(["Nods01",[8.0,-4.5,0.0]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[4,2,1.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[0.0,4.5,0.0],[1.5,4.5,0.0]]);
            this.endApexData.push(["Poly",[0.0,3.5],[0.5,3.5],[0.5,-3.5],[0.0,-3.5]]);
            this.endApexData.push(["Line",[1.5,-4.5],[1.5,4.5]]);
            this.endApexData.push(["Nods01",[0.0,-4.5,0.0],[1.5,-4.5,0.0]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "GreekMeander15":
        this.beginApexData = [[4,2,1.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0,4.5,0.0],[1.5,4.5,0.0]]);
            this.beginApexData.push(["Poly",[1.5,-3.5],[1.0,-3.5],[1.0,3.5],[1.5,3.5]]);
            this.beginApexData.push(["Line",[0.0,4.5],[0.0,-4.5]]);
            this.beginApexData.push(["Nods01",[0.0,-4.5,0.0],[1.5,-4.5,0.0]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,2,8.0000,8.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[8.0,4.5,0.0]]);
            this.mainData.push(["Poly",[0.0,3.5],[6.5,3.5],[6.5,-1.5],[3.5,-1.5],[3.5,0.5],[2.5,0.5],[2.5,-2.5],[7.5,-2.5],[7.5,3.5],[8.0,3.5]]);
            this.mainData.push(["Poly",[8.0,-3.5],[1.5,-3.5],[1.5,1.5],[4.5,1.5],[4.5,-0.5],[5.5,-0.5],[5.5,2.5],[0.5,2.5],[0.5,-3.5],[0.0,-3.5]]);
            this.mainData.push(["Nods01",[8.0,-4.5,0.0]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[4,2,1.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[0.0,4.5,0.0],[1.5,4.5,0.0]]);
            this.endApexData.push(["Poly",[0.0,3.5],[0.5,3.5],[0.5,-3.5],[0.0,-3.5]]);
            this.endApexData.push(["Line",[1.5,-4.5],[1.5,4.5]]);
            this.endApexData.push(["Nods01",[0.0,-4.5,0.0],[1.5,-4.5,0.0]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "GreekMeander15Flexing":
        this.beginApexData = [[6,2,1.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Dots00",[0.0,4.5],[0.5,4.5],[1.0,4.5]]);
            this.beginApexData.push(["Spline",[1.5,-3.5],[1.25,-3.5],[1.0,-3.5]]);
            this.beginApexData.push(["Line",[1.0,-3.5],[1.0,3.5]]);
            this.beginApexData.push(["Spline",[1.0,3.5],[1.25,3.5],[1.5,3.5]]);
            this.beginApexData.push(["Line",[0.0,4.5],[0.0,-4.5]]);
            this.beginApexData.push(["Dots01",[0.0,-4.5],[0.5,-4.5],[1.0,-4.5]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[20,2,8.0000,8.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0,4.5],[1.0,4.5],[2.0,4.5],[3.0,4.5],[4.0,4.5],[5.0,4.5],[6.0,4.5],[7.0,4.5]]);
            this.mainData.push(["Spline",[0.0,3.5],[0.5,3.5],[1.5,3.5],[2.5,3.5],[3.5,3.5],[4.5,3.5],[5.5,3.5],[6.5,3.5]]);
            this.mainData.push(["Line",[6.5,3.5],[6.5,-1.5]]);
            this.mainData.push(["Spline",[6.5,-1.5],[5.5,-1.5],[4.5,-1.5],[3.5,-1.5]]);
            this.mainData.push(["Line",[3.5,-1.5],[3.5,0.5]]);
            this.mainData.push(["Spline",[3.5,0.5],[3.0,0.5],[2.5,0.5]]);
            this.mainData.push(["Line",[2.5,0.5],[2.5,-2.5]]);
            this.mainData.push(["Spline",[2.5,-2.5],[3.5,-2.5],[4.5,-2.5],[5.5,-2.5],[6.5,-2.5],[7.5,-2.5]]);
            this.mainData.push(["Line",[7.5,-2.5],[7.5,3.5]]);
            this.mainData.push(["Spline",[7.5,3.5],[7.75,3.5],[8.0,3.5]]);
            this.mainData.push(["Spline",[8.0,-3.5],[7.5,-3.5],[6.5,-3.5],[5.5,-3.5],[4.5,-3.5],[3.5,-3.5],[2.5,-3.5],[1.5,-3.5]]);
            this.mainData.push(["Line",[1.5,-3.5],[1.5,1.5]]);
            this.mainData.push(["Spline",[1.5,1.5],[2.5,1.5],[3.5,1.5],[4.5,1.5]]);
            this.mainData.push(["Line",[4.5,1.5],[4.5,-0.5]]);
            this.mainData.push(["Spline",[4.5,-0.5],[5.0,-0.5],[5.5,-0.5]]);
            this.mainData.push(["Line",[5.5,-0.5],[5.5,2.5]]);
            this.mainData.push(["Spline",[5.5,2.5],[4.5,2.5],[3.5,2.5],[2.5,2.5],[1.5,2.5],[0.5,2.5]]);
            this.mainData.push(["Line",[0.5,2.5],[0.5,-3.5]]);
            this.mainData.push(["Spline",[0.5,-3.5],[0.25,-3.5],[0.0,-3.5]]);
            this.mainData.push(["Dots01",[0.0,-4.5],[1.0,-4.5],[2.0,-4.5],[3.0,-4.5],[4.0,-4.5],[5.0,-4.5],[6.0,-4.5],[7.0,-4.5]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[6,2,1.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Dots00",[0.0,4.5],[0.5,4.5],[1.0,4.5],[1.5,4.5]]);
            this.endApexData.push(["Spline",[0.0,3.5],[0.25,3.5],[0.5,3.5]]);
            this.endApexData.push(["Line",[0.5,3.5],[0.5,-3.5]]);
            this.endApexData.push(["Spline",[0.5,-3.5],[0.25,-3.5],[0.0,-3.5]]);
            this.endApexData.push(["Line",[1.5,-4.5],[1.5,4.5]]);
            this.endApexData.push(["Dots01",[0.0,-4.5],[0.5,-4.5],[1.0,-4.5],[1.5,-4.5]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "CelticMeanderRounded":
        this.beginApexData = [[4,0,5.1213]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Spline",[5.1213,-1.9092],[4.9743,-1.6771],[4.5759,-0.5824],[4.5249,0.0000],[4.5759,0.5824],[4.9743,1.6771],[5.1213,1.9092]]);
            this.beginApexData.push(["Spline",[4.2728,-2.6917],[3.9791,-2.2516],[3.4337,-0.7838],[3.3594,0.0000],[3.4224,0.7858],[3.9505,2.2681],[4.2728,2.7577],[4.6971,3.1820],[5.1213,3.5560]]);
            this.beginApexData.push(["Spline",[5.1213,-1.9092],[4.6971,-2.3335],[4.2728,-2.6917],[4.0790,-2.8827],[3.5539,-3.1876],[2.9558,-3.2948],[2.3564,-3.1909],[1.8284,-2.8878],[1.4358,-2.4218],[1.2268,-1.8491],[1.2000,-1.5442],[1.2000,-1.2382],[1.2000,0.0000],[1.2000,1.2381],[1.2000,1.5442],[1.2264,1.8491],[1.4329,2.4234],[1.8226,2.8947],[2.3508,3.2065],[2.9558,3.3201],[3.5656,3.2195],[4.1057,2.9146],[4.2728,2.7577]]);
            this.beginApexData.push(["Spline",[5.1213,-3.5560],[4.8557,-3.8085],[3.9667,-4.3217],[2.9558,-4.5000],[1.9449,-4.3217],[1.0558,-3.8085],[0.3960,-3.0221],[0.0449,-2.0575],[0.0000,-1.5442],[0.0000,-1.0290],[0.0000,0.0000],[0.0000,1.0290],[0.0000,1.5442],[0.0449,2.0575],[0.3960,3.0221],[1.0558,3.8085],[1.9449,4.3217],[2.9558,4.5000],[3.9667,4.3217],[4.8557,3.8085],[5.1213,3.5560]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[10,0,5.5154,5.5154,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.0000,1.9092],[0.4243,2.3335],[0.8874,2.7188],[1.8226,3.1647],[2.7577,3.3000],[3.6929,3.1647],[4.1843,2.9757],[4.6280,2.7188]]);
            this.mainData.push(["Spline",[2.7577,0.8485],[3.6929,1.7837],[4.6280,2.7188],[5.0912,3.1820],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.1625],[0.8874,-2.7188],[1.8226,-1.7837],[2.7577,-0.8485]]);
            this.mainData.push(["Spline",[0.0000,-1.9092],[0.8874,-1.0218],[1.9092,0.0000]]);
            this.mainData.push(["Spline",[0.0000,1.9092],[0.8874,1.0218],[1.9092,0.0000],[2.3335,-0.4243],[2.7577,-0.8485],[3.6929,-1.7837],[4.6280,-2.7188]]);
            this.mainData.push(["Spline",[0.0000,3.5560],[0.4437,3.8595],[0.8874,4.0929],[1.8226,4.4018],[2.7577,4.5000],[3.6929,4.4018],[4.6280,4.0929],[5.0717,3.8595],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.8874,2.7188],[1.8226,1.7837],[2.7577,0.8485],[3.6062,0.0000],[4.6280,-1.0218],[5.5154,-1.9092]]);
            this.mainData.push(["Spline",[3.6062,0.0000],[4.6280,1.0218],[5.5154,1.9092]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.8595],[0.8874,-4.0929],[1.8226,-4.4018],[2.7577,-4.5000],[3.6929,-4.4018],[4.6280,-4.0929],[5.0717,-3.8595],[5.5154,-3.5560]]);
            this.mainData.push(["Spline",[0.8874,-2.7188],[1.3311,-2.9757],[1.8226,-3.1647],[2.7577,-3.3000],[3.6929,-3.1647],[4.6280,-2.7188],[5.0912,-2.3335],[5.5154,-1.9092]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[4,0,5.1213]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.1470,1.6771],[0.5454,0.5824],[0.5964,0.0000],[0.5454,-0.5824],[0.1470,-1.6771],[0.0000,-1.9092]]);
            this.endApexData.push(["Spline",[0.8485,2.6917],[1.1422,2.2516],[1.6877,0.7838],[1.7620,0.0000],[1.6989,-0.7858],[1.1708,-2.2681],[0.8485,-2.7577],[0.4243,-3.1820],[0.0000,-3.5560]]);
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.4243,2.3335],[0.8485,2.6917],[1.0424,2.8827],[1.5674,3.1876],[2.1655,3.2948],[2.7649,3.1909],[3.2929,2.8878],[3.6855,2.4218],[3.8946,1.8491],[3.9213,1.5442],[3.9213,1.2382],[3.9213,0.0000],[3.9213,-1.2381],[3.9213,-1.5442],[3.8949,-1.8491],[3.6884,-2.4234],[3.2987,-2.8947],[2.7706,-3.2065],[2.1655,-3.3201],[1.5558,-3.2195],[1.0156,-2.9146],[0.8485,-2.7577]]);
            this.endApexData.push(["Spline",[0.0000,3.5560],[0.2656,3.8085],[1.1546,4.3217],[2.1655,4.5000],[3.1765,4.3217],[4.0655,3.8085],[4.7253,3.0221],[5.0764,2.0575],[5.1213,1.5442],[5.1213,1.0290],[5.1213,0.0000],[5.1213,-1.0290],[5.1213,-1.5442],[5.0764,-2.0575],[4.7253,-3.0221],[4.0655,-3.8085],[3.1765,-4.3217],[2.1655,-4.5000],[1.1546,-4.3217],[0.2656,-3.8085],[0.0000,-3.5560]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "CelticMeanderHardBend":
        this.beginApexData = [[8,0,4.5577]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Line",[1.2000,-3.3000],[1.2000,3.3000]]);
            this.beginApexData.push(["Line",[0.0000,-4.5000],[0.0000,4.5000]]);
            this.beginApexData.push(["Spline",[4.5577,-1.9092],[4.4107,-1.6771],[4.0123,-0.5824],[3.9613,0.0000],[4.0123,0.5824],[4.4107,1.6771],[4.5577,1.9092]]);
            this.beginApexData.push(["Spline",[3.7092,-2.6917],[3.4183,-2.2500],[2.8838,-0.7814],[2.8154,0.0000],[2.8838,0.7814],[3.4183,2.2500],[3.7092,2.6917],[4.1335,3.1820],[4.5577,3.5560]]);
            this.beginApexData.push(["Spline",[4.5577,-3.5560],[4.1140,-3.8595],[3.6703,-4.0929],[3.2266,-4.2679],[2.7351,-4.4018],[1.8000,-4.5000],[1.5577,-4.5000],[0.0000,-4.5000]]);
            this.beginApexData.push(["Spline",[1.2000,3.3000],[1.8000,3.3000],[2.7351,3.1647],[3.2266,2.9757],[3.7092,2.6917]]);
            this.beginApexData.push(["Spline",[0.0000,4.5000],[1.5577,4.5000],[1.8000,4.5000],[2.7351,4.4018],[3.2266,4.2679],[3.6703,4.0929],[4.1140,3.8595],[4.5577,3.5560]]);
            this.beginApexData.push(["Spline",[4.5577,-1.9092],[4.1140,-2.3527],[3.7092,-2.6917],[3.2266,-2.9757],[2.7351,-3.1647],[1.8000,-3.3000],[1.2000,-3.3000]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[10,0,5.5154,5.5154,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.0000,1.9092],[0.4243,2.3335],[0.8874,2.7188],[1.8226,3.1647],[2.7577,3.3000],[3.6929,3.1647],[4.1843,2.9757],[4.6280,2.7188]]);
            this.mainData.push(["Spline",[2.7577,0.8485],[3.6929,1.7837],[4.6280,2.7188],[5.0912,3.1820],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.1625],[0.8874,-2.7188],[1.8226,-1.7837],[2.7577,-0.8485]]);
            this.mainData.push(["Spline",[0.0000,-1.9092],[0.8874,-1.0218],[1.9092,0.0000]]);
            this.mainData.push(["Spline",[0.0000,1.9092],[0.8874,1.0218],[1.9092,0.0000],[2.3335,-0.4243],[2.7577,-0.8485],[3.6929,-1.7837],[4.6280,-2.7188]]);
            this.mainData.push(["Spline",[0.0000,3.5560],[0.4437,3.8595],[0.8874,4.0929],[1.8226,4.4018],[2.7577,4.5000],[3.6929,4.4018],[4.6280,4.0929],[5.0717,3.8595],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.8874,2.7188],[1.8226,1.7837],[2.7577,0.8485],[3.6062,0.0000],[4.6280,-1.0218],[5.5154,-1.9092]]);
            this.mainData.push(["Spline",[3.6062,0.0000],[4.6280,1.0218],[5.5154,1.9092]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.8595],[0.8874,-4.0929],[1.8226,-4.4018],[2.7577,-4.5000],[3.6929,-4.4018],[4.6280,-4.0929],[5.0717,-3.8595],[5.5154,-3.5560]]);
            this.mainData.push(["Spline",[0.8874,-2.7188],[1.3311,-2.9757],[1.8226,-3.1647],[2.7577,-3.3000],[3.6929,-3.1647],[4.6280,-2.7188],[5.0912,-2.3335],[5.5154,-1.9092]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[8,0,4.5577]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Line",[3.3577,3.3000],[3.3577,-3.3000]]);
            this.endApexData.push(["Line",[4.5577,4.5000],[4.5577,-4.5000]]);
            this.endApexData.push(["Spline",[0.8485,2.6917],[1.1394,2.2500],[1.6739,0.7814],[1.7423,0.0000],[1.6739,-0.7814],[1.1394,-2.2500],[0.8485,-2.6917],[0.4243,-3.1820],[0.0000,-3.5560]]);
            this.endApexData.push(["Spline",[0.0000,3.5560],[0.4437,3.8595],[0.8874,4.0929],[1.3311,4.2679],[1.8226,4.4018],[2.7577,4.5000],[3.0000,4.5000],[4.5577,4.5000]]);
            this.endApexData.push(["Spline",[3.3577,-3.3000],[2.7577,-3.3000],[1.8226,-3.1647],[1.3311,-2.9757],[0.8485,-2.6917]]);
            this.endApexData.push(["Spline",[4.5577,-4.5000],[3.0000,-4.5000],[2.7577,-4.5000],[1.8226,-4.4018],[1.3311,-4.2679],[0.8874,-4.0929],[0.4437,-3.8595],[0.0000,-3.5560]]);
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.4437,2.3527],[0.8485,2.6917],[1.3311,2.9757],[1.8226,3.1647],[2.7577,3.3000],[3.3577,3.3000]]);
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.1470,1.6771],[0.5454,0.5824],[0.5964,0.0000],[0.5454,-0.5824],[0.1470,-1.6771],[0.0000,-1.9092]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "CelticMeanderRound":
        this.beginApexData = [[6,0,7.2577]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Spline",[5.3485,0.0000],[6.3031,0.9546],[7.2577,1.9092]]);
            this.beginApexData.push(["Spline",[7.2577,-1.9092],[6.3031,-0.9546],[5.3485,0.0000]]);
            this.beginApexData.push(["Spline",[7.2577,-3.5560],[6.7500,-3.8971],[5.2814,-4.4316],[3.7186,-4.4316],[2.2500,-3.8971],[1.3180,-3.1820],[0.6029,-2.2500],[0.0684,-0.7814],[0.0000,0.0000],[0.0684,0.7814],[0.6029,2.2500],[1.3180,3.1820],[2.2500,3.8971],[3.7186,4.4316],[5.2814,4.4316],[6.7500,3.8971],[7.2577,3.5560]]);
            this.beginApexData.push(["Spline",[7.2577,-1.9092],[6.8335,-2.3335],[6.3703,-2.7188],[5.0730,-3.2499],[3.9270,-3.2499],[2.8500,-2.8579],[2.1665,-2.3335],[1.6421,-1.6500],[1.2501,-0.5730],[1.2000,0.0000],[1.2501,0.5730],[1.6421,1.6500],[2.1665,2.3335],[2.8500,2.8579],[3.9270,3.2499],[5.0730,3.2499],[6.1500,2.8579],[6.3703,2.7188]]);
            this.beginApexData.push(["Spline",[6.3703,-2.7188],[5.6591,-2.0076],[4.6816,-1.0302],[3.6515,0.0000]]);
            this.beginApexData.push(["Spline",[3.6515,0.0000],[4.6816,1.0302],[5.6591,2.0076],[6.3703,2.7188],[6.8335,3.1820],[7.2577,3.5560]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[10,0,5.5154,5.5154,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.0000,1.9092],[0.4243,2.3335],[0.8874,2.7188],[1.8226,3.1647],[2.7577,3.3000],[3.6929,3.1647],[4.1843,2.9757],[4.6280,2.7188]]);
            this.mainData.push(["Spline",[2.7577,0.8485],[3.6929,1.7837],[4.6280,2.7188],[5.0912,3.1820],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.1625],[0.8874,-2.7188],[1.8226,-1.7837],[2.7577,-0.8485]]);
            this.mainData.push(["Spline",[0.0000,-1.9092],[0.8874,-1.0218],[1.9092,0.0000]]);
            this.mainData.push(["Spline",[0.0000,1.9092],[0.8874,1.0218],[1.9092,0.0000],[2.3335,-0.4243],[2.7577,-0.8485],[3.6929,-1.7837],[4.6280,-2.7188]]);
            this.mainData.push(["Spline",[0.0000,3.5560],[0.4437,3.8595],[0.8874,4.0929],[1.8226,4.4018],[2.7577,4.5000],[3.6929,4.4018],[4.6280,4.0929],[5.0717,3.8595],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.8874,2.7188],[1.8226,1.7837],[2.7577,0.8485],[3.6062,0.0000],[4.6280,-1.0218],[5.5154,-1.9092]]);
            this.mainData.push(["Spline",[3.6062,0.0000],[4.6280,1.0218],[5.5154,1.9092]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.8595],[0.8874,-4.0929],[1.8226,-4.4018],[2.7577,-4.5000],[3.6929,-4.4018],[4.6280,-4.0929],[5.0717,-3.8595],[5.5154,-3.5560]]);
            this.mainData.push(["Spline",[0.8874,-2.7188],[1.3311,-2.9757],[1.8226,-3.1647],[2.7577,-3.3000],[3.6929,-3.1647],[4.6280,-2.7188],[5.0912,-2.3335],[5.5154,-1.9092]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[6,0,7.2577]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Spline",[0.8874,2.7188],[1.5986,2.0076],[2.5761,1.0302],[3.6062,0.0000]]);
            this.endApexData.push(["Spline",[3.6062,0.0000],[2.5761,-1.0302],[1.5986,-2.0076],[0.8874,-2.7188],[0.4243,-3.1820],[0.0000,-3.5560]]);
            this.endApexData.push(["Spline",[1.9092,0.0000],[0.9546,-0.9546],[0.0000,-1.9092]]);
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.9546,0.9546],[1.9092,0.0000]]);
            this.endApexData.push(["Spline",[0.0000,3.5560],[0.5077,3.8971],[1.9763,4.4316],[3.5391,4.4316],[5.0077,3.8971],[5.9397,3.1820],[6.6548,2.2500],[7.1894,0.7814],[7.2577,0.0000],[7.1894,-0.7814],[6.6548,-2.2500],[5.9397,-3.1820],[5.0077,-3.8971],[3.5391,-4.4316],[1.9763,-4.4316],[0.5077,-3.8971],[0.0000,-3.5560]]);
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.4243,2.3335],[0.8874,2.7188],[2.1847,3.2499],[3.3308,3.2499],[4.4077,2.8579],[5.0912,2.3335],[5.6156,1.6500],[6.0076,0.5730],[6.0577,0.0000],[6.0076,-0.5730],[5.6156,-1.6500],[5.0912,-2.3335],[4.4077,-2.8579],[3.3308,-3.2499],[2.1847,-3.2499],[1.1077,-2.8579],[0.8874,-2.7188]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "CelticMeanderEndless":
        this.beginApexData = [[8,0,4.4316]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Spline",[4.4316,-1.9092],[3.4770,-0.9546],[2.5224,0.0000],[2.0981,0.4243],[1.7128,0.8874],[1.4290,1.3885],[1.1817,2.1847],[1.1418,3.0174],[1.1703,3.2613]]);
            this.beginApexData.push(["Spline",[1.1703,-3.2613],[1.1418,-3.0174],[1.1817,-2.1847],[1.4290,-1.3885],[1.7128,-0.8874]]);
            this.beginApexData.push(["Spline",[4.4316,-1.9092],[4.0073,-2.3335],[3.5442,-2.7188],[3.0431,-3.0026],[2.2469,-3.2499],[1.4142,-3.2898],[1.1703,-3.2613]]);
            this.beginApexData.push(["Spline",[3.5442,-2.7188],[2.6285,-1.8031],[1.7128,-0.8874],[1.2496,-0.4243],[0.8756,0.0000],[0.5345,0.5077],[0.0000,1.9763],[0.0000,3.5391],[0.0590,3.8210],[0.2575,4.1741],[0.6106,4.3726],[0.8925,4.4316],[2.4553,4.4316],[3.9239,3.8971],[4.4316,3.5560]]);
            this.beginApexData.push(["Spline",[2.5224,0.0000],[3.4770,0.9546],[4.4316,1.9092]]);
            this.beginApexData.push(["Spline",[4.4316,-3.5560],[3.9239,-3.8971],[2.4553,-4.4316],[0.8925,-4.4316],[0.6106,-4.3726],[0.2575,-4.1741],[0.0590,-3.8210],[0.0000,-3.5391],[0.0000,-1.9763],[0.5345,-0.5077],[0.8756,0.0000]]);
            this.beginApexData.push(["Spline",[1.1703,3.2613],[1.4142,3.2898],[2.2469,3.2499],[3.0431,3.0026],[3.5442,2.7188]]);
            this.beginApexData.push(["Spline",[1.7128,0.8874],[2.6285,1.8031],[3.5442,2.7188],[4.0073,3.1820],[4.4316,3.5560]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[10,0,5.5154,5.5154,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.0000,1.9092],[0.4243,2.3335],[0.8874,2.7188],[1.8226,3.1647],[2.7577,3.3000],[3.6929,3.1647],[4.1843,2.9757],[4.6280,2.7188]]);
            this.mainData.push(["Spline",[2.7577,0.8485],[3.6929,1.7837],[4.6280,2.7188],[5.0912,3.1820],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.1625],[0.8874,-2.7188],[1.8226,-1.7837],[2.7577,-0.8485]]);
            this.mainData.push(["Spline",[0.0000,-1.9092],[0.8874,-1.0218],[1.9092,0.0000]]);
            this.mainData.push(["Spline",[0.0000,1.9092],[0.8874,1.0218],[1.9092,0.0000],[2.3335,-0.4243],[2.7577,-0.8485],[3.6929,-1.7837],[4.6280,-2.7188]]);
            this.mainData.push(["Spline",[0.0000,3.5560],[0.4437,3.8595],[0.8874,4.0929],[1.8226,4.4018],[2.7577,4.5000],[3.6929,4.4018],[4.6280,4.0929],[5.0717,3.8595],[5.5154,3.5560]]);
            this.mainData.push(["Spline",[0.8874,2.7188],[1.8226,1.7837],[2.7577,0.8485],[3.6062,0.0000],[4.6280,-1.0218],[5.5154,-1.9092]]);
            this.mainData.push(["Spline",[3.6062,0.0000],[4.6280,1.0218],[5.5154,1.9092]]);
            this.mainData.push(["Spline",[0.0000,-3.5560],[0.4437,-3.8595],[0.8874,-4.0929],[1.8226,-4.4018],[2.7577,-4.5000],[3.6929,-4.4018],[4.6280,-4.0929],[5.0717,-3.8595],[5.5154,-3.5560]]);
            this.mainData.push(["Spline",[0.8874,-2.7188],[1.3311,-2.9757],[1.8226,-3.1647],[2.7577,-3.3000],[3.6929,-3.1647],[4.6280,-2.7188],[5.0912,-2.3335],[5.5154,-1.9092]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[8,0,4.4316]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Spline",[1.9092,0.0000],[0.9546,-0.9546],[0.0000,-1.9092]]);
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.4243,2.3335],[0.8874,2.7188],[1.3885,3.0026],[2.1847,3.2499],[3.0174,3.2898],[3.2613,3.2613]]);
            this.endApexData.push(["Spline",[0.8874,2.7188],[1.5986,2.0076],[2.7188,0.8874],[3.1820,0.4243],[3.5560,0.0000],[3.8971,-0.5077],[4.4316,-1.9763],[4.4316,-3.5391],[4.3726,-3.8210],[4.1741,-4.1741],[3.8210,-4.3726],[3.5391,-4.4316],[1.9763,-4.4316],[0.5077,-3.8971],[0.0000,-3.5560]]);
            this.endApexData.push(["Spline",[0.0000,3.5560],[0.5077,3.8971],[1.9763,4.4316],[3.5391,4.4316],[3.8210,4.3726],[4.1741,4.1741],[4.3726,3.8210],[4.4316,3.5391],[4.4316,1.9763],[3.8971,0.5077],[3.5560,0.0000]]);
            this.endApexData.push(["Spline",[3.2613,-3.2613],[3.0174,-3.2898],[2.1847,-3.2499],[1.3885,-3.0026],[0.8874,-2.7188]]);
            this.endApexData.push(["Spline",[0.0000,1.9092],[0.9546,0.9546],[1.9092,0.0000],[2.3335,-0.4243],[2.7188,-0.8874],[3.0026,-1.3885],[3.2499,-2.1847],[3.2898,-3.0174],[3.2613,-3.2613]]);
            this.endApexData.push(["Spline",[3.2613,3.2613],[3.2898,3.0174],[3.2499,2.1847],[3.0026,1.3885],[2.7188,0.8874]]);
            this.endApexData.push(["Spline",[2.7188,-0.8874],[1.8031,-1.8031],[0.8874,-2.7188],[0.4243,-3.1820],[0.0000,-3.5560]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "CelticMeanderEndless_L":
        this.beginApexData = [[12,0,2.7901]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Spline",[1.6064,1.7099],[2.1983,2.3017],[2.7901,2.8936]]);
            this.beginApexData.push(["Spline",[2.2399,-3.3956],[1.6721,-2.8279],[1.1044,-2.2601],[0.8172,-1.9729],[0.5853,-1.7099],[0.3972,-1.4348],[0.2524,-1.1596],[0.0609,-0.5798],[0.0000,0.0000],[0.0609,0.5798],[0.2524,1.1596],[0.3972,1.4348],[0.5853,1.7099]]);
            this.beginApexData.push(["Spline",[2.7901,-2.8936],[2.5271,-3.1567],[2.2399,-3.3956],[1.9292,-3.5715],[1.4356,-3.7249],[0.9193,-3.7496],[0.7680,-3.7320]]);
            this.beginApexData.push(["Spline",[1.1044,2.2601],[1.6721,2.8279],[2.2399,3.3956],[2.5271,3.6828],[2.7901,3.9147]]);
            this.beginApexData.push(["Spline",[0.7680,-3.7320],[0.7504,-3.5807],[0.7751,-3.0644],[0.9285,-2.5708],[1.1044,-2.2601]]);
            this.beginApexData.push(["Spline",[2.7901,-2.8936],[2.1983,-2.3017],[1.6064,-1.7099],[1.3433,-1.4468],[1.1044,-1.1596],[0.8279,-0.5798],[0.7440,0.0000],[0.8279,0.5798],[0.9451,0.8845],[1.1044,1.1596]]);
            this.beginApexData.push(["Spline",[2.7901,-3.9147],[2.4753,-4.1262],[1.5648,-4.4576],[0.5958,-4.4576],[0.4210,-4.4210],[0.2020,-4.2980],[0.0790,-4.0790],[0.0424,-3.9042],[0.0424,-2.9352],[0.3738,-2.0247],[0.5853,-1.7099]]);
            this.beginApexData.push(["Spline",[2.7901,0.5261],[2.1983,1.1180],[1.6064,1.7099],[1.3433,1.9729],[1.1044,2.2601],[0.9285,2.5708],[0.7751,3.0644],[0.7504,3.5807],[0.7680,3.7320]]);
            this.beginApexData.push(["Spline",[1.6064,-1.7099],[2.1983,-1.1180],[2.7901,-0.5261]]);
            this.beginApexData.push(["Spline",[2.2640,0.0000],[1.6721,0.5919],[1.1044,1.1596],[0.8172,1.4468],[0.5853,1.7099],[0.3738,2.0247],[0.0424,2.9352],[0.0424,3.9042],[0.0790,4.0790],[0.2020,4.2980],[0.4210,4.4210],[0.5958,4.4576],[1.5648,4.4576],[2.4753,4.1262],[2.7901,3.9147]]);
            this.beginApexData.push(["Spline",[1.1044,-1.1596],[1.6721,-0.5919],[2.2640,0.0000],[2.7901,0.5261]]);
            this.beginApexData.push(["Spline",[0.7680,3.7320],[0.9193,3.7496],[1.4356,3.7249],[1.9292,3.5715],[2.2399,3.3956]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[16,0,3.4197,3.4197,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.5502,3.3956],[1.1180,2.8279],[1.7099,2.2360],[2.2360,1.7099],[2.8279,1.1180],[3.4197,0.5261]]);
            this.mainData.push(["Spline",[3.4197,-2.8936],[2.8279,-2.3017],[2.2360,-1.7099],[1.7099,-1.1838],[1.1180,-0.5919],[0.5261,0.0000]]);
            this.mainData.push(["Spline",[3.4197,-3.9147],[3.1446,-4.1028],[2.8695,-4.2476],[2.2897,-4.4391],[1.7099,-4.5000],[1.1300,-4.4391],[0.5502,-4.2476],[0.2751,-4.1028],[0.0000,-3.9147]]);
            this.mainData.push(["Spline",[1.7340,2.2601],[2.3017,2.8279],[2.8695,3.3956],[3.1567,3.6828],[3.4197,3.9147]]);
            this.mainData.push(["Spline",[3.4197,-2.8936],[3.1567,-3.1567],[2.8695,-3.3956],[2.2897,-3.6721],[1.7099,-3.7560],[1.1300,-3.6721],[0.8253,-3.5549],[0.5502,-3.3956]]);
            this.mainData.push(["Spline",[2.8695,-3.3956],[2.3017,-2.8279],[1.7099,-2.2360],[1.1838,-1.7099],[0.5919,-1.1180],[0.0000,-0.5261]]);
            this.mainData.push(["Spline",[3.4197,0.5261],[2.8936,0.0000],[2.3017,-0.5919],[1.7099,-1.1838]]);
            this.mainData.push(["Spline",[0.0000,2.8936],[0.2631,3.1567],[0.5502,3.3956],[1.1300,3.6721],[1.7099,3.7560],[2.2897,3.6721],[2.5944,3.5549],[2.8695,3.3956]]);
            this.mainData.push(["Spline",[0.0000,2.8936],[0.5919,2.3017],[1.1838,1.7099],[1.7099,1.1838],[2.3017,0.5919],[2.8936,0.0000]]);
            this.mainData.push(["Spline",[0.0000,-2.8936],[0.5919,-2.3017],[1.1838,-1.7099]]);
            this.mainData.push(["Spline",[3.4197,-0.5261],[2.8279,-1.1180],[2.2360,-1.7099]]);
            this.mainData.push(["Spline",[0.0000,-0.5261],[0.5261,0.0000],[1.1180,0.5919],[1.7099,1.1838]]);
            this.mainData.push(["Spline",[0.0000,0.5261],[0.5919,1.1180],[1.1838,1.7099]]);
            this.mainData.push(["Spline",[0.0000,3.9147],[0.2751,4.1028],[0.5502,4.2476],[1.1300,4.4391],[1.7099,4.5000],[2.2897,4.4391],[2.8695,4.2476],[3.1446,4.1028],[3.4197,3.9147]]);
            this.mainData.push(["Spline",[1.7099,-2.2360],[0.5502,-3.3956],[0.2631,-3.6828],[0.0000,-3.9147]]);
            this.mainData.push(["Spline",[2.2360,1.7099],[2.8279,2.3017],[3.4197,2.8936]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[12,0,2.7901]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Spline",[1.1838,1.7099],[0.5919,1.1180],[0.0000,0.5261]]);
            this.endApexData.push(["Spline",[2.0221,3.7320],[2.0398,3.5807],[2.0150,3.0644],[1.8617,2.5708],[1.6858,2.2601]]);
            this.endApexData.push(["Spline",[0.0000,2.8936],[0.5919,2.3017],[1.1838,1.7099],[1.4468,1.4468],[1.6858,1.1596],[1.9622,0.5798],[2.0461,0.0000],[1.9622,-0.5798],[1.8450,-0.8845],[1.6858,-1.1596]]);
            this.endApexData.push(["Spline",[0.0000,3.9147],[0.3148,4.1262],[1.2254,4.4576],[2.1944,4.4576],[2.3692,4.4210],[2.5881,4.2980],[2.7111,4.0790],[2.7477,3.9042],[2.7477,2.9352],[2.4163,2.0247],[2.2048,1.7099]]);
            this.endApexData.push(["Spline",[0.0000,-0.5261],[0.5919,-1.1180],[1.1838,-1.7099],[1.4468,-1.9729],[1.6858,-2.2601],[1.8617,-2.5708],[2.0150,-3.0644],[2.0398,-3.5807],[2.0221,-3.7320]]);
            this.endApexData.push(["Spline",[1.6858,-2.2601],[1.1180,-2.8279],[0.5502,-3.3956],[0.2631,-3.6828],[0.0000,-3.9147]]);
            this.endApexData.push(["Spline",[0.5261,0.0000],[1.1180,-0.5919],[1.6858,-1.1596],[1.9729,-1.4468],[2.2048,-1.7099],[2.4163,-2.0247],[2.7477,-2.9352],[2.7477,-3.9042],[2.7111,-4.0790],[2.5881,-4.2980],[2.3692,-4.4210],[2.1944,-4.4576],[1.2254,-4.4576],[0.3148,-4.1262],[0.0000,-3.9147]]);
            this.endApexData.push(["Spline",[1.6858,1.1596],[1.1180,0.5919],[0.5261,0.0000],[0.0000,-0.5261]]);
            this.endApexData.push(["Spline",[2.0221,-3.7320],[1.8709,-3.7496],[1.3546,-3.7249],[0.8609,-3.5715],[0.5502,-3.3956]]);
            this.endApexData.push(["Spline",[0.0000,2.8936],[0.2631,3.1567],[0.5502,3.3956],[0.8609,3.5715],[1.3546,3.7249],[1.8709,3.7496],[2.0221,3.7320]]);
            this.endApexData.push(["Spline",[1.1838,-1.7099],[0.5919,-2.3017],[0.0000,-2.8936]]);
            this.endApexData.push(["Spline",[0.5502,3.3956],[1.1180,2.8279],[1.6858,2.2601],[1.9729,1.9729],[2.2048,1.7099],[2.3930,1.4348],[2.5377,1.1596],[2.7292,0.5798],[2.7901,0.0000],[2.7292,-0.5798],[2.5377,-1.1596],[2.3930,-1.4348],[2.2048,-1.7099]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "TelephoneCoilMedio": //3.513000 lost what this value stands for
        this.beginApexData = [[9,0,4.4870]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Spline",[0.0000,-1.3756],[0.4881,-0.4313],[1.0995,0.9276],[1.7086,2.3363],[2.4397,3.5918],[3.2335,4.3045],[4.1065,4.5001],[4.4870,4.4889]]);
            this.beginApexData.push(["Spline",[2.7591,-2.3569],[3.1885,-1.5145],[3.5936,-0.6075],[3.9656,0.4000]]);
            this.beginApexData.push(["Spline",[0.0611,-1.3901],[0.7869,-0.1409],[1.3999,1.0000],[1.9270,2.0109],[2.5464,2.6949],[3.0114,2.3214],[3.3331,1.8477],[3.6502,1.2324],[3.9656,0.4000],[4.1032,0.0000],[4.4870,-1.0314]]);
            this.beginApexData.push(["Spline",[2.1751,3.2097],[2.5904,3.6145],[3.0070,3.6281],[3.4558,3.1890],[3.6420,2.7315],[3.7013,2.3000],[3.7013,2.0000],[3.7594,1.7348],[3.9991,1.0394],[4.1068,0.4266],[4.4870,-1.0314]]);
            this.beginApexData.push(["Spline",[2.7591,-1.4284],[3.0240,-1.0208],[3.6916,0.1369],[3.9227,0.5243]]);
            this.beginApexData.push(["Spline",[0.0000,-1.3756],[1.4093,-1.6041],[2.7591,-1.4284]]);
            this.beginApexData.push(["Spline",[0.0000,-2.3041],[0.4043,-2.8469],[1.3448,-3.2106],[2.3345,-2.8841],[2.7591,-2.3569]]);
            this.beginApexData.push(["Line",[2.7591,-1.4284],[2.7591,-2.3569]]);
            this.beginApexData.push(["Line",[0.0000,-1.3756],[0.0000,-2.3041]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[6,0,8.0000,8.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.0000,4.4889],[0.4910,4.3664],[1.1525,3.8522],[1.5235,3.2665],[1.8966,2.3007],[2.5146,0.5675],[3.1783,-0.8466],[3.8636,-1.8200],[4.5371,-2.3453],[5.2195,-2.3961],[5.8310,-1.9725],[6.5370,-1.0208],[7.2046,0.1369],[7.4358,0.5243]]);
            this.mainData.push(["Spline",[0.0000,-1.0314],[0.2677,-1.6785],[0.6442,-2.4108],[1.5457,-3.6638],[2.4762,-4.2638],[3.5530,-4.5000],[4.4983,-4.3223],[5.1804,-3.8614],[5.8609,-3.0369],[6.7015,-1.5145],[7.1066,-0.6075],[7.4786,0.4000]]);
            this.mainData.push(["Spline",[3.5130,-1.3756],[4.0011,-0.4313],[4.6125,0.9276],[5.2216,2.3363],[5.9527,3.5918],[6.7465,4.3045],[7.6195,4.5001],[8.0000,4.4889]]);
            this.mainData.push(["Spline",[3.5510,-1.4288],[4.2999,-0.1409],[4.9129,1.0000],[5.4400,2.0109],[6.0594,2.6949],[6.5244,2.3214],[6.8461,1.8477],[7.1632,1.2324],[7.4786,0.4000],[7.6162,0.0000],[8.0000,-1.0314]]);
            this.mainData.push(["Spline",[2.2963,1.1446],[2.8107,-0.6372],[3.3810,-1.9055],[3.8615,-2.7353],[4.3637,-3.3283],[4.8364,-3.5330],[5.2606,-3.4788],[5.8609,-3.0369]]);
            this.mainData.push(["Spline",[5.6881,3.2097],[6.1034,3.6145],[6.5200,3.6281],[6.9688,3.1890],[7.1550,2.7315],[7.2143,2.3000],[7.2143,2.0000],[7.2724,1.7348],[7.5121,1.0394],[7.6198,0.4266],[8.0000,-1.0314]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[5,0,6.2721]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Spline",[0.0000,4.4889],[0.4910,4.3664],[1.1525,3.8522],[1.5235,3.2665],[1.8966,2.3007],[2.5146,0.5675],[3.1783,-0.8466],[3.8636,-1.8200],[4.5371,-2.3453],[5.2195,-2.3961],[5.8310,-1.9725],[6.2721,-1.4284]]);
            this.endApexData.push(["Spline",[0.0000,-1.0314],[0.2677,-1.6785],[0.6442,-2.4108],[1.5457,-3.6638],[2.4762,-4.2638],[3.5530,-4.5000],[4.4983,-4.3223],[5.1804,-3.8614],[5.8609,-3.0369],[6.2721,-2.3569]]);
            this.endApexData.push(["Spline",[2.2963,1.1446],[2.8107,-0.6372],[3.3810,-1.9055],[3.8615,-2.7353],[4.3637,-3.3283],[4.8364,-3.5330],[5.2606,-3.4788],[5.8609,-3.0369]]);
            this.endApexData.push(["Spline",[3.5130,-1.3756],[4.9223,-1.6041],[6.2721,-1.4284]]);
            this.endApexData.push(["Line",[6.2721,-1.4284],[6.2721,-2.3569]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RailwayTrackLineArt":
        this.beginApexData = [[2,2,1.4000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Dots00",[0.00,4.50],[0.70,4.50]]);
            this.beginApexData.push(["Dots01",[0.00,-4.50],[0.70,-4.50]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[3,2,4.4000,4.4000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.00,7.10],[1.60,7.10],[1.60,-7.10],[0.00,-7.10],[0.00,7.10]]);
            this.mainData.push(["Dots00",[0.00,4.50],[0.88,4.50],[1.76,4.50],[2.64,4.50],[3.52,4.50]]);
            this.mainData.push(["Dots01",[0.00,-4.50],[0.88,-4.50],[1.76,-4.50],[2.64,-4.50],[3.52,-4.50]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[3,2,3.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Poly",[0.00,7.10],[1.60,7.10],[1.60,-7.10],[0.00,-7.10],[0.00,7.10]]);
            this.endApexData.push(["Dots00",[0.00,4.50],[1.00,4.50],[2.00,4.50],[3.00,4.50]]);
            this.endApexData.push(["Dots01",[0.00,-4.50],[1.00,-4.50],[2.00,-4.50],[3.00,-4.50]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RailwayTrackConcrete":
        this.beginApexData = [[6,4,1.4000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Line",[0.00,4.95],[0.00,4.50]]);
            this.beginApexData.push(["Line",[0.00,-4.50],[0.00,-4.95]]);
            this.beginApexData.push(["Dots00",[0.00,4.95],[0.70,4.95]]);
            this.beginApexData.push(["Dots01",[0.00,4.50],[0.70,4.50]]);
            this.beginApexData.push(["Dots02",[0.00,-4.50],[0.70,-4.50]]);
            this.beginApexData.push(["Dots03",[0.00,-4.95],[0.70,-4.95]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[18,4,4.4000,4.4000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.00,4.50],[0.00,-4.50]]);
            this.mainData.push(["Line",[1.60,4.50],[1.60,-4.50]]);
            this.mainData.push(["Poly",[0.00,4.95],[0.00,7.55],[1.60,7.55],[1.60,4.95]]);
            this.mainData.push(["Poly",[0.23,4.95],[0.23,5.75],[1.37,5.75],[1.37,4.95]]);
            this.mainData.push(["Poly",[0.23,4.50],[0.23,3.70],[1.37,3.70],[1.37,4.50]]);
            this.mainData.push(["Poly",[0.23,-4.50],[0.23,-3.70],[1.37,-3.70],[1.37,-4.50]]);
            this.mainData.push(["Poly",[0.23,-4.95],[0.23,-5.75],[1.37,-5.75],[1.37,-4.95]]);
            this.mainData.push(["Poly",[0.00,-4.95],[0.00,-7.55],[1.60,-7.55],[1.60,-4.95]]);
            this.mainData.push(["Line",[0.00,6.70],[1.60,6.70]]);
            this.mainData.push(["Line",[0.00,2.75],[1.60,2.75]]);
            this.mainData.push(["Line",[0.00,1.20],[1.60,1.20]]);
            this.mainData.push(["Line",[0.00,-1.20],[1.60,-1.20]]);
            this.mainData.push(["Line",[0.00,-2.75],[1.60,-2.75]]);
            this.mainData.push(["Line",[0.00,-6.70],[1.60,-6.70]]);
            this.mainData.push(["Dots00",[0.00,4.95],[0.88,4.95],[1.76,4.95],[2.64,4.95],[3.52,4.95]]);
            this.mainData.push(["Dots01",[0.00,4.50],[0.88,4.50],[1.76,4.50],[2.64,4.50],[3.52,4.50]]);
            this.mainData.push(["Dots02",[0.00,-4.50],[0.88,-4.50],[1.76,-4.50],[2.64,-4.50],[3.52,-4.50]]);
            this.mainData.push(["Dots03",[0.00,-4.95],[0.88,-4.95],[1.76,-4.95],[2.64,-4.95],[3.52,-4.95]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[20,4,3.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Line",[0.00,4.50],[0.00,-4.50]]);
            this.endApexData.push(["Line",[1.60,4.50],[1.60,-4.50]]);
            this.endApexData.push(["Poly",[0.00,4.95],[0.00,7.55],[1.60,7.55],[1.60,4.95]]);
            this.endApexData.push(["Poly",[0.23,4.95],[0.23,5.75],[1.37,5.75],[1.37,4.95]]);
            this.endApexData.push(["Poly",[0.23,4.50],[0.23,3.70],[1.37,3.70],[1.37,4.50]]);
            this.endApexData.push(["Poly",[0.23,-4.50],[0.23,-3.70],[1.37,-3.70],[1.37,-4.50]]);
            this.endApexData.push(["Poly",[0.23,-4.95],[0.23,-5.75],[1.37,-5.75],[1.37,-4.95]]);
            this.endApexData.push(["Poly",[0.00,-4.95],[0.00,-7.55],[1.60,-7.55],[1.60,-4.95]]);
            this.endApexData.push(["Line",[0.00,6.70],[1.60,6.70]]);
            this.endApexData.push(["Line",[0.00,2.75],[1.60,2.75]]);
            this.endApexData.push(["Line",[0.00,1.20],[1.60,1.20]]);
            this.endApexData.push(["Line",[0.00,-1.20],[1.60,-1.20]]);
            this.endApexData.push(["Line",[0.00,-2.75],[1.60,-2.75]]);
            this.endApexData.push(["Line",[0.00,-6.70],[1.60,-6.70]]);
            this.endApexData.push(["Dots00",[0.00,4.95],[1.00,4.95],[2.00,4.95],[3.00,4.95]]);
            this.endApexData.push(["Dots01",[0.00,4.50],[1.00,4.50],[2.00,4.50],[3.00,4.50]]);
            this.endApexData.push(["Dots02",[0.00,-4.50],[1.00,-4.50],[2.00,-4.50],[3.00,-4.50]]);
            this.endApexData.push(["Dots03",[0.00,-4.95],[1.00,-4.95],[2.00,-4.95],[3.00,-4.95]]);
            this.endApexData.push(["Line",[3.00,4.95],[3.00,4.50]]);
            this.endApexData.push(["Line",[3.00,-4.50],[3.00,-4.95]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "OrthogonalMark":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,9.000],[0.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "OrthogonalBar":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,4.5000],[0.0000,-4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "1_OrthoPointGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "1_OrthoPointGlobalFlex":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,9.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "2_OrthoPointsGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,2,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,4.5000,0.0000]]);
            this.mainData.push(["Nods01",[0.0000,-4.5000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "2_OrthoPointsGlobalFlex":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,2,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,4.5000]]);
            this.mainData.push(["Dots01",[0.0000,-4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "ApproxSegments":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,0.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "ApproxSpline":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RulerMetric":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[10,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,9.0000],[0.0000,0.0000]]);
            this.mainData.push(["Line",[0.9000,4.5000],[0.9000,0.0000]]);
            this.mainData.push(["Line",[1.8000,4.5000],[1.8000,0.0000]]);
            this.mainData.push(["Line",[2.7000,4.5000],[2.7000,0.0000]]);
            this.mainData.push(["Line",[3.6000,4.5000],[3.6000,0.0000]]);
            this.mainData.push(["Line",[4.5000,6.7500],[4.5000,0.0000]]);
            this.mainData.push(["Line",[5.4000,4.5000],[5.4000,0.0000]]);
            this.mainData.push(["Line",[6.3000,4.5000],[6.3000,0.0000]]);
            this.mainData.push(["Line",[7.2000,4.5000],[7.2000,0.0000]]);
            this.mainData.push(["Line",[8.1000,4.5000],[8.1000,0.0000]]);
        this.endData = [[1,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,9.000],[0.0000,0.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RulerInch":
        this.beginApexData = [[0,0,11.4300]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[8,0,22.8600,22.8600,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,8.5725],[0.0000,0.0000]]);
            this.mainData.push(["Line",[2.8575,4.28625],[2.8575,0.0000]]);
            this.mainData.push(["Line",[5.7150,5.7150],[5.7150,0.0000]]);
            this.mainData.push(["Line",[8.5725,4.28625],[8.5725,0.0000]]);
            this.mainData.push(["Line",[11.4300,6.7500],[11.4300,0.0000]]);
            this.mainData.push(["Line",[14.2875,4.28625],[14.2875,0.0000]]);
            this.mainData.push(["Line",[17.1450,5.7150],[17.1450,0.0000]]);
            this.mainData.push(["Line",[20.0025,4.28625],[20.0025,0.0000]]);
        this.endData = [[1,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,8.5725],[0.0000,0.0000]]);
        this.endApexData = [[0,0,11.4300]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "Riverbanks_In_1-1":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.mainData.push(["Line",[4.5000,0.0000],[4.5000,4,5000]]);
        this.endData = [[1,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "Riverbanks+L_In_1-1":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,2,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.mainData.push(["Line",[4.5000,0.0000],[4.5000,4,5000]]);
            this.mainData.push(["Dots00",[0.0000,9.0000]]);
            this.mainData.push(["Dots00",[4.5000,9.0000]]);
        this.endData = [[2,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.endData.push(["Dots00",[0.0000,9.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "Riverbanks+L_Out_1-1":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,2,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.mainData.push(["Line",[4.5000,4.5000],[4.5000,9.0000]]);
            this.mainData.push(["Dots00",[0.0000,9.0000]]);
            this.mainData.push(["Dots00",[4.5000,9.0000]]);
        this.endData = [[2,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.endData.push(["Dots00",[0.0000,9.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "Riverbanks_In_2-3":
        this.beginApexData = [[0,0,3.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,6.0000,6.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.mainData.push(["Line",[3.0000,0.0000],[3.0000,4.5000]]);
        this.endData = [[1,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
        this.endApexData = [[0,0,3.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "Riverbanks+L_In_2-3":
        this.beginApexData = [[0,0,3.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,2,6.0000,6.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.mainData.push(["Line",[3.0000,0.0000],[3.0000,4.5000]]);
            this.mainData.push(["Dots00",[0.0000,9.0000]]);
            this.mainData.push(["Dots00",[3.0000,9.0000]]);
        this.endData = [[2,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.endData.push(["Dots00",[0.0000,9.0000]]);
        this.endApexData = [[0,0,3.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "Riverbanks+L_Out_2-3":
        this.beginApexData = [[0,0,3.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,2,6.0000,6.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.mainData.push(["Line",[3.0000,4.5000],[3.0000,9.0000]]);
            this.mainData.push(["Dots00",[0.0000,9.0000]]);
            this.mainData.push(["Dots00",[3.0000,9.0000]]);
        this.endData = [[2,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Line",[0.0000,0.0000],[0.0000,9.0000]]);
            this.endData.push(["Dots00",[0.0000,9.0000]]);
        this.endApexData = [[0,0,3.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RevisionCloud_L":
        this.beginApexData = [[1,1,15.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0000,0.0000,0.0000],[2.5000,15.0000,0.0000],[5.0000,0.0000,-0.6337]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,20.0000,20.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0,-4.5,-0.9]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0,-4.5,-0.6337]]);
        this.endApexData = [[1,1,7.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[7.5000,0.0000,0.0000]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RevisionCloud_SL":
        this.beginApexData = [[1,1,15.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0000,0.0000,0.0000],[2.5000,15.0000,0.0000],[5.0000,0.0000,-0.6337]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,25.0000,25.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0,-4.5,-0.9],[5.0,-4.5,-0.9]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0,-4.5,-0.6337]]);
        this.endApexData = [[1,1,7.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[7.5000,0.0000,0.0000]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RevisionCloud_ML":
        this.beginApexData = [[1,1,15.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0000,0.0000,0.0000],[2.5000,15.0000,0.0000],[5.0000,0.0000,-0.6337]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,32.0000,32.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0,-4.5,-0.9],[12.0,-4.5,-0.9]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0,-4.5,-0.6337]]);
        this.endApexData = [[1,1,7.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[7.5000,0.0000,0.0000]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RevisionCloud_SML":
        this.beginApexData = [[1,1,15.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0000,0.0000,0.0000],[2.5000,15.0000,0.0000],[5.0000,0.0000,-0.6337]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,37.0000,37.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0,-4.5,-0.9],[5.0,-4.5,-0.9],[17.0,-4.5,-0.9]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0,-4.5,-0.6337]]);
        this.endApexData = [[1,1,7.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[7.5000,0.0000,0.0000]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RevisionCloud_MSML":
        this.beginApexData = [[1,1,15.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0000,0.0000,0.0000],[2.5000,15.0000,0.0000],[5.0000,0.0000,-0.6337]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,49.0000,49.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0,-4.5,-0.9],[12.0,-4.5,-0.9],[17.0,-4.5,-0.9],[29.0,-4.5,-0.9]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0,-4.5,-0.6337]]);
        this.endApexData = [[1,1,7.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[7.5000,0.0000,0.0000]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RevisionCloud_Multi":
        this.beginApexData = [[1,1,15.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0000,0.0000,0.0000],[2.5000,15.0000,0.0000],[5.0000,0.0000,-0.6337]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,37.0000,37.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,-4.5000,-0.8315],[4.8604,-3.5980,-0.6337],[15.7420,-2.7896,-1.5189],[17.3856,-2.6098,-0.8166]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0,-4.5,-0.6337]]);
        this.endApexData = [[1,1,7.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[7.5000,0.0000,0.0000]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RevisionCloud_Complex":
        this.beginApexData = [[1,1,15.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0000,0.0000,0.0000],[2.5000,15.0000,0.0000],[5.0000,0.0000,-0.6337]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[3,1,37.0000,37.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,-4.5000,-0.8315],[4.8604,-3.5980,-0.6337],[15.7420,-2.7896,-0.1155],[17.3856,-2.6098,-0.8166]]);
            this.mainData.push(["Poly",[15.7420,-2.7896,0.0985],[14.5249,-3.5113,0.0000]]);
            this.mainData.push(["Poly",[17.3856,-2.6098,-0.0985],[18.7300,-3.0513,0.5000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0,-4.5,-0.6337]]);
        this.endApexData = [[1,1,7.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[7.5000,0.0000,0.0000]]);
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SinusoidWave":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.0000,0.0000],[0.5000,1.5391],[1.0000,2.8925],[1.5000,3.8971],[1.7500,4.2286],[2.0000,4.4316],[2.2500,4.5000],[2.5000,4.4316],[2.7500,4.2286],[3.0000,3.8971],[3.5000,2.8925],[4.0000,1.5391],[4.5000,0.0000]]);
            this.mainData.push(["Spline",[4.5000,0.0000],[5.0000,-1.5391],[5.5000,-2.8925],[6.0000,-3.8971],[6.2500,-4.2286],[6.5000,-4.4316],[6.7500,-4.5000],[7.0000,-4.4316],[7.2500,-4.2286],[7.5000,-3.8971],[8.0000,-2.8925],[8.5000,-1.5391],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SinusoidWaveGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,2,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,0.0000],[0.5000,1.5391],[1.0000,2.8925],[1.5000,3.8971],[1.7500,4.2286],[2.0000,4.4316],[2.2500,4.5000],[2.5000,4.4316],[2.7500,4.2286],[3.0000,3.8971],[3.5000,2.8925],[4.0000,1.5391]]);
            this.mainData.push(["Dots00",[4.5000,0.0000],[5.0000,-1.5391],[5.5000,-2.8925],[6.0000,-3.8971],[6.2500,-4.2286],[6.5000,-4.4316],[6.7500,-4.5000],[7.0000,-4.4316],[7.2500,-4.2286],[7.5000,-3.8971],[8.0000,-2.8925],[8.5000,-1.5391]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Dots00",[0.0000,0.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "3PhaseWaveGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[8,8,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,0.0000],[0.5000,1.5391],[1.0000,2.8925],[1.5000,3.8971],[1.7500,4.2286],[2.0000,4.4316],[2.2500,4.5000],[2.5000,4.4316],[2.7500,4.2286],[3.0000,3.8971],[3.5000,2.8925],[4.0000,1.5391],[4.5000,0.0000]]);
            this.mainData.push(["Dots00",[5.0000,-1.5391],[5.5000,-2.8925],[6.0000,-3.8971],[6.2500,-4.2286],[6.5000,-4.4316],[6.7500,-4.5000],[7.0000,-4.4316],[7.2500,-4.2286],[7.5000,-3.8971],[8.0000,-2.8925],[8.5000,-1.5391]]);
            this.mainData.push(["Dots01",[0.0000,3.8971],[0.5000,2.8925],[1.0000,1.5391],[1.5000,0.0000]]);
            this.mainData.push(["Dots01",[2.0000,-1.5391],[2.5000,-2.8925],[3.0000,-3.8971],[3.2500,-4.2286],[3.5000,-4.4316],[3.7500,-4.5000],[4.0000,-4.4316],[4.2500,-4.2286],[4.5000,-3.8971],[5.0000,-2.8925],[5.5000,-1.5391]]);
            this.mainData.push(["Dots01",[6.0000,0.0000],[6.5000,1.5391],[7.0000,2.8925],[7.5000,3.8971],[7.7500,4.2286],[8.0000,4.4316],[8.2500,4.5000],[8.5000,4.4316],[8.7500,4.2286]]);
            this.mainData.push(["Dots02",[0.0000,-3.8971],[0.2500,-4.2286],[0.5000,-4.4316],[0.7500,-4.5000],[1.0000,-4.4316],[1.2500,-4.2286],[1.5000,-3.8971],[2.0000,-2.8925],[2.5000,-1.5391],[3.0000,0.0000]]);
            this.mainData.push(["Dots02",[3.5000,1.5391],[4.0000,2.8925],[4.5000,3.8971],[4.7500,4.2286],[5.0000,4.4316],[5.2500,4.5000],[5.5000,4.4316],[5.7500,4.2286],[6.0000,3.8971],[6.5000,2.8925],[7.0000,1.5391]]);
            this.mainData.push(["Dots02",[7.5000,0.0000],[8.0000,-1.5391],[8.5000,-2.8925]]);
        this.endData = [[3,3,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Dots00",[0.0000,0.0000]]);
            this.endData.push(["Dots01",[0.0000,3.8971]]);
            this.endData.push(["Dots02",[0.0000,-3.8971]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "TriangleWave":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[2.2500,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[6.7500,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "TriangleWaveGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[1,1,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
            this.beginData.push(["Nods00",[0.0000,0.0000,0.0000]]);
        this.mainData = [[1,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[2.2500,4.5000,0.0000],[6.7500,-4.5000,0.0000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000,0.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SawtoothWave":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[4.5000,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[4.5000,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SawtoothWaveGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[1,1,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
            this.beginData.push(["Nods00",[0.0000,0.0000,0.0000]]);
        this.mainData = [[1,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[4.5000,4.5000,0.0000],[4.5000,-4.5000,0.0000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000,0.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SquareWave":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[0.0000,4.5000],[4.5000,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[4.5000,-4.5000],[9.0000,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SquareWaveFlexing":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[6,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,4.5000]]);
            this.mainData.push(["Spline",[0.0000,4.5000],[1.5000,4.5000],[3.0000,4.5000],[4.5000,4.5000]]);
            this.mainData.push(["Line",[4.5000,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Line",[4.5000,0.0000],[4.5000,-4.5000]]);
            this.mainData.push(["Spline",[4.5000,-4.5000],[6.0000,-4.5000],[7.5000,-4.5000],[9.0000,-4.5000]]);
            this.mainData.push(["Line",[9.0000,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SquareWaveGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,0.0000,0.0000],[0.0000,4.5000,0.0000],[4.5000,4.5000,0.0000],[4.5000,0.0000,0.0000],[4.5000,-4.5000,0.0000],[9.0000,-4.5000,0.0000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000,0.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SteppedWave":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[0.0000,1.5000],[0.9000,1.5000],[0.9000,3.0000],[1.8000,3.0000],[1.8000,4.5000],[2.7000,4.5000],[2.7000,3.0000],[3.6000,3.0000],[3.6000,1.5000],[4.5000,1.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[4.5000,-1.5000],[5.4000,-1.5000],[5.4000,-3.0000],[6.3000,-3.0000],[6.3000,-4.5000],[7.2000,-4.5000],[7.2000,-3.0000],[8.1000,-3.0000],[8.1000,-1.5000],[9.0000,-1.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SteppedWaveGlobal":
        this.beginApexData = [[0,0,4.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,0.0000,0.0000],[0.0000,1.5000,0.0000],[0.9000,1.5000,0.0000],[0.9000,3.0000,0.0000],[1.8000,3.0000,0.0000],[1.8000,4.5000,0.0000],[2.7000,4.5000,0.0000],[2.7000,3.0000,0.0000],[3.6000,3.0000,0.0000],[3.6000,1.5000,0.0000],[4.5000,1.5000,0.0000],[4.5000,0.0000,0.0000]]);
            this.mainData.push(["Nods00",[4.5000,-1.5000,0.0000],[5.4000,-1.5000,0.0000],[5.4000,-3.0000,0.0000],[6.3000,-3.0000,0.0000],[6.3000,-4.5000,0.0000],[7.2000,-4.5000,0.0000],[7.2000,-3.0000,0.0000],[8.1000,-3.0000,0.0000],[8.1000,-1.5000,0.0000],[9.0000,-1.5000,0.0000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000,0.0000]]);
        this.endApexData = [[0,0,4.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "Quadrilar":
        this.beginApexData = [[0,0,9.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,9.0000,18.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,4.5000],[0.0000,-4.5000],[9.0000,-4.5000],[9.0000,4.5000],[0.0000,4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,9.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "QuadrilarFlexing":
        this.beginApexData = [[0,0,9.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,0,9.0000,18.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,4.5000],[0.0000,-4.5000]]);
            this.mainData.push(["Spline",[0.0000,-4.5000],[1.0000,-4.5000],[2.0000,-4.5000],[3.0000,-4.5000],[4.0000,-4.5000],[5.0000,-4.5000],[6.0000,-4.5000],[7.0000,-4.5000],[8.0000,-4.5000],[9.0000,-4.5000]]);
            this.mainData.push(["Line",[9.0000,-4.5000],[9.0000,4.5000]]);
            this.mainData.push(["Spline",[9.0000,4.5000],[8.0000,4.5000],[7.0000,4.5000],[6.0000,4.5000],[5.0000,4.5000],[4.0000,4.5000],[3.0000,4.5000],[2.0000,4.5000],[1.0000,4.5000],[0.0000,4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,9.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SideQuadrilar":
        this.beginApexData = [[0,0,9.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,9.0000,18.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,9.0000],[0.0000,0.0000],[9.0000,0.0000],[9.0000,9.0000],[0.0000,9.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,9.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SideQuadrilarFlexing":
        this.beginApexData = [[0,0,9.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,0,9.0000,18.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,9.000],[0.0000,0.000]]);
            this.mainData.push(["Spline",[0.0000,0.0000],[1.0000,0.0000],[2.0000,0.0000],[3.0000,0.0000],[4.0000,0.0000],[5.0000,0.0000],[6.0000,0.0000],[7.0000,0.0000],[8.0000,0.0000],[9.0000,0.0000]]);
            this.mainData.push(["Line",[9.0000,0.0000],[9.0000,9.0000]]);
            this.mainData.push(["Spline",[9.0000,9.0000],[8.0000,9.0000],[7.0000,9.0000],[6.0000,9.0000],[5.0000,9.0000],[4.0000,9.0000],[3.0000,9.0000],[2.0000,9.0000],[1.0000,9.0000],[0.0000,9.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,9.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "AllPainterDataTypes":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[9,3,2.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Point",[1.0000,4.0000]]);
            this.mainData.push(["Line",[0.0000,4.5000],[2.0000,-4.5000]]);
            this.mainData.push(["Poly",[0.0000,4.900,0.0000],[0.5000,4.8000,0.5000],[2.0000,5.2000,0.0000],[0.0000,5.3000,0.0000]]);
            this.mainData.push(["Spline",[1.5145,-3.4413],[1.2179,-2.9250],[0.8036,-2.5714],[0.0000,0.0000]]);
            this.mainData.push(["Arc",[0.0000,4.5000,2.1000,90.0000,270.0000,false]]);
            this.mainData.push(["Circle",[2.0000,-4.5000,1.2000]]);
            this.mainData.push(["Nods00",[0.0000,2.2000,0.0000],[1.0000,-2.2000,0.0000],[2.0000,2.2000,0.0000]]);
            this.mainData.push(["Dots00",[0.0000,4.000],[1.0000,3.500],[2.0000,4.000]]);
            this.mainData.push(["Dots01",[0.0000,-4.5000],[1.5000,-4.5000],[3.0000,-4.5000],[4.5000,-4.5000],[6.0000,-4.5000],[7.5000,-4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    } // End switch(painterSet)
    // ** USER-ADJUSTABLE PARAMETERS ABOVE **
    return painterSet + " done";
};

/**
 * Initiate the FlexPainter dialog Comboboxes. # ToDo # Sources
 */
// Based on Dimension.js initUiOptions
FlexPainter.prototype.initWidgetsCombo = function(widget) {
    // ** HARDCODED 51 ** 51 cases, 51 icons, 1 knot icon
    var widgets = getWidgets(widget);
    var painterSetCombo = widgets["PainterSelection"];
    painterSetCombo.clear();
        painterSetCombo.addItem("CurtainRopeProto"); // =Flexing Slanted: Passed: Over, Boxed, Under
            // On open forms & step > length: Apex detached, is in se correct
//        painterSetCombo.addItem("GreekMeander14"); // Similar Boxed
        painterSetCombo.addItem("GreekMeander15"); // Similar Boxed
        painterSetCombo.addItem("GreekMeander15Flexing"); // Similar Boxed
        painterSetCombo.addItem("CelticMeanderRounded"); // =Flexing Similar Boxed
        painterSetCombo.addItem("CelticMeanderHardBend"); // =Flexing Similar Boxed
        painterSetCombo.addItem("CelticMeanderRound"); // =Flexing Similar Boxed
        painterSetCombo.addItem("CelticMeanderEndless"); // =Flexing Similar Boxed
        painterSetCombo.addItem("CelticMeanderEndless_L"); // =Flexing Similar Boxed
        painterSetCombo.addItem("TelephoneCoilMedio"); // =Flexing Similar Boxed
            // Railways are not so ideal to morph, the sleepers get transformed to trapezoids
        painterSetCombo.addItem("RailwayTrackLineArt"); // =Mixed Flexing Similar Boxed
        painterSetCombo.addItem("RailwayTrackConcrete"); // =Mixed Flexing Similar Boxed
        painterSetCombo.addItem("OrthogonalMark"); // Similar Stepped Null-length
        painterSetCombo.addItem("OrthogonalBar"); // Stepped Null-length: Passed: Over
        painterSetCombo.addItem("1_OrthoPointGlobal"); // Similar Stepped Null-length
        painterSetCombo.addItem("1_OrthoPointGlobalFlex"); // Similar Stepped Null-length
        painterSetCombo.addItem("2_OrthoPointsGlobal"); // Similar Stepped Null-length
        painterSetCombo.addItem("2_OrthoPointsGlobalFlex"); // Similar Stepped Null-length
        painterSetCombo.addItem("ApproxSegments"); // Similar Stepped Null-length
        painterSetCombo.addItem("ApproxSpline"); // Similar Stepped Null-length
        painterSetCombo.addItem("Quadrilar"); // Similar Stepped
        painterSetCombo.addItem("QuadrilarFlexing"); // Similar Stepped
        painterSetCombo.addItem("SideQuadrilar"); // Similar Stepped
        painterSetCombo.addItem("SideQuadrilarFlexing"); // Similar Stepped
            // Rulers are only accurate if no dynamic scaling is involved
        painterSetCombo.addItem("RulerMetric"); // Similar Boxed
        painterSetCombo.addItem("RulerInch"); // Similar Boxed
        painterSetCombo.addItem("Riverbanks_In_1-1"); // Similar Boxed
        painterSetCombo.addItem("Riverbanks+L_In_1-1"); // Similar Boxed
        painterSetCombo.addItem("Riverbanks+L_Out_1-1"); // Similar Boxed
        painterSetCombo.addItem("Riverbanks_In_2-3"); // Similar Boxed
        painterSetCombo.addItem("Riverbanks+L_In_2-3"); // Similar Boxed
        painterSetCombo.addItem("Riverbanks+L_Out_2-3"); // Similar Boxed
            // RevisionClouds mostly rely on the bulging of a global polyline
        painterSetCombo.addItem("RevisionCloud_L"); // Similar Boxed
        painterSetCombo.addItem("RevisionCloud_SL"); // Similar Boxed
        painterSetCombo.addItem("RevisionCloud_ML"); // Similar Boxed
        painterSetCombo.addItem("RevisionCloud_SML"); // Similar Boxed
        painterSetCombo.addItem("RevisionCloud_MSML"); // Similar Boxed
        painterSetCombo.addItem("RevisionCloud_Multi"); // Similar Boxed
        painterSetCombo.addItem("RevisionCloud_Complex"); // Similar Boxed
        painterSetCombo.addItem("SinusoidWave"); // Similar Boxed
        painterSetCombo.addItem("SinusoidWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("3PhaseWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("TriangleWave"); // Similar Boxed
        painterSetCombo.addItem("TriangleWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("SawtoothWave"); // Similar Boxed
        painterSetCombo.addItem("SawtoothWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("SquareWave"); // Similar Boxed
        painterSetCombo.addItem("SquareWaveFlexing"); // Similar Boxed
        painterSetCombo.addItem("SquareWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("SteppedWave"); // Boxed: Passed: Over, Boxed, Under
        painterSetCombo.addItem("SteppedWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("AllPainterDataTypes"); // Stepped: Passed: Over, Boxed, Under
    // Same solution for PainterBox enabled-state
    painterSetCombo.currentText = "";
    painterSetCombo.currentIndex = -1;
    return;
};

/**
 * Adds a menu for this action to Examples/Math Examples/FlexPainter.
 */
// Based on both Math Examples and other snips
FlexPainter.init = function(basePath) {
    // Prevent FlexPainter to be loaded without PRO resources
    if (!hasPlugin("PROTOOLS")) { return; };
    // -> Continue with PRO recources

    var action = new RGuiAction(qsTr("&FlexPainter"), RMainWindowQt.getMainWindow());
    var tip = qsTranslate("FlexPainter", "Paints over selection mimicking a roller stamp");
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/FlexPainter.js");
    action.setIcon(basePath + "/FlexPainter.svg");
    action.setDefaultShortcut(new QKeySequence("f,p")); 
    action.setDefaultCommands(["flexpainter", "fp"]);    // A list array separated by comma + space
    action.setStatusTip(tip);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tip);    // Displays aside near Toolbars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(79700);
    action.setSortOrder(300);
    action.setWidgetNames(["MathExamplesMenu"]);
};

/**
 * Major remark block as dummy function. Collapsable in NPP as such.
 */
FlexPainter.Remarks = function(only4DummysLikeMe) {
    //    Recheck last status!!!
    //    # Error 0 # MAJOR ISSUE 0/2 # Fixed 2 # Workaround 2 #
    //    # Issue 18/54 # Unsolvable 1 # Solved 12 # Fixed 23 # Workaround 23 #
    //    # ToDo 21 # Done 8 # Busy 4 # Reminder 2 #
    // *************************************************************************************************
    //    # ToDo # Solution for Painter data sets.(Partially prepared UI & code)
    //              # ToDo # Investigate entities in Blocks or Files, icons are in files

    //    # Busy # Casting on newly added sublayer 'Painted'
    //              # Issue # Interferes with group castings.

    //    # Busy # Insertable painters (eg. Knots) @(aaa%,bbb%,ccc%,...)(Partially prepared UI & code)

    //    # Busy # Check user numerical entries ... mainScaleX/Y != -n; 0; huge v.37
    //              # ToDo # Investigate '.setValidator' for QLineEdit (Occurs in eg. InvoluteSpur.js)
    //              # ToDo # Check that values are numbers
    //              Done: Can't start entries with '-', can enter expression that gives negative result v.37
    //              Done: Made absolute and factor limited to 0.01 & 111 and written back to Widget v.38
    //              Done: limited casting main painter to 9999 / entity  v.38
    //                  (# ToDo # Revise: On short line in test f0.01 14s 21139 splines /3 is about 7000 painters)
    //              Done: Dirty loop Dialog untill flawless v.39

    // *************************************************************************************************
    //    # MAJOR ISSUE Fixed # Fails in CE
    //              # Workaround # hasPlugin("PROTOOLS")
    //                    Initiate conditional in FlexPainter.init
    //                    Run conditional from beginEvent
    //              # ToDo # Can it be CE lean ???
    //    # MAJOR ISSUE Fixed # Dialog painter set selection coding and how to have scope...
    //                    - FlexPainter.PainterSetInit() out of scope
    //                    - Painter data out of scope
    //                    JAVAscript/Qt related  Asked for help
    //              # Workaround # Get functions analogue OrthogonalProjections.js Line 194 & 261
    //                    https://qcad.org/rsforum/viewtopic.php?t=6626
    //                    - getPainterSet functions (calling PainterSetInit)
    //                    - getDoBeginApex, getDoEndApex and getDoInserts functions (return boolean)
    //                    - getBase9Length and getBase9Stepsize functions (return dimension)
    //              # Issue Fixed # Not functional for first use
    //              # Workaround # Instead of: this.PainterSetInit("Default") what returns "CurtainRopeProto"
    //                    Tried with success: widgets["PainterSelection"].setCurrentText("Default");
    //                    And let change function take over
    //              # Issue Solved # The Dialog starts with the non-existent set "Default"
    //                    Solved with "CurtainRopeProto". Offcourse
    //    # MAJOR ISSUE Fixed # AppCrash on casting Null-splines followed by:
    //                    - Select All
    //                    - Select Layer Entities: cast layer
    //                    - Invert Selection (with base entity(-ies) still selected)
    //                    - Selection filter: entities on cast layer
    //                    - Selection filter: splines
    //                    - draw select including origin
    //                    NOT with draw select excluding the origin
    //              # Workaround # Difference in target & catching null-vectors
    //                    For usability only reports and halts in debugger mode
    //              # ToDo # Debate the casting of a NULL entry
    //    # Issue Unsolvable # Can't find where qDebug("...") is sending to
    //              Windows can not!: https://qcad.org/rsforum/viewtopic.php?t=6202
    //    # Issue Solved # Not functional spinbox
    //              Solved by setting 'singleStep' to 1 in UI spinbox, added 'accelerated'
    //    # Issue Solved # Two options
    //              Solved by knowing the difference
    //              widgets["MainLengthX"].text = xyz;
    //              widgets["MainLengthX"].setValue(xyz);
    //              ... = widgets["FactorY"].text;
    //              ... = widgets["FactorY"].getValue();
    //              See: https://qcad.org/rsforum/viewtopic.php?t=6583
    //    # Issue Solved # metric vs imperial
    //              Solved with base 9 & Units
    //              See: https://qcad.org/rsforum/viewtopic.php?t=6547#p24624
    //    # Issue Solved # Division Pi/2 was used 3 times in each painter spline fitpoint casting loop
    //              Solved with: appropriate math, script global this.var, locals as var and some as const (faster)
    //              Still interesting for overal speed
    //              Exec time: factor x1: literal (1.570796...)
    //                         factor ~x2: const orthoAngle (not Global)
    //                         factor ~x4: var orthoAngle && Global const orthoAngle && this.orthoAngle
    //                         factor ~x8...12: Math.PI/2
    //    # Issue Solved # 'if () {...}' with multiple AND conditions take longer to evaluate.
    //              Solved for AND in frequent looping with: Multistage testing, test larger variations first
    //              Solved for OR with: Test more likely to be true first
    //              Kept multistage testing for uniflow main script loop
    //              # Reminder # Check 'if() {...}' block conditions
    //    # Issue Solved # 'For(){...}' loops work faster with less calculations in the conditions
    //              # Reminder # Check 'For() {...}' loop conditions
    //    # Issue Fixed # Pushing to an object defined as array doesn't work out well
    //              # Workaround # Append beyond end: xyz.object.length = item to append
    //    # Issue Fixed # castAngle failing @startPoint or @distance zero or @endpoint or @distance objlength
    //              Some such castings return null vectors for castpoint and subsequently an error for castAngle
    //              # Done # Isolate cases see FlexPainter.prototype.castPainter...switch(this.castingType){}
    //              # Done # File topic/bugreport =related to= offset to poly @startPoint || @endpoint
    //              https://www.ribbonsoft.com/rsforum/viewtopic.php?t=6590
    //                    https://qcad.org/rsforum/viewtopic.php?t=6601
    //        Prior v0.39: AVOID the use of fitpoints on the reference margins
    //        Final # Workaround # Offset tiny bit from start- or endpoint
    //              # Issue # On geo closed have to offset >999 times RS.PointTolerance (1e-6) to stay away from first segment
    //              Tested RS.PointTolerance times { 2,10,100,1000(ok),500,750,999,1000(ok) => 2000 times}
    //    # Issue Fixed # Angle at polyline
    //              shape.getAngleAtPoint(RVector) == NaN
    //              shape.getAngleAt(distance,RS.FromStart) == NaN
    //              # Workaround # Angle at segment
    //    # Issue Fixed # Dialog pops up with lots of decimals without initWidgets(dialog)
    //              With the dialog change functions active less are displayed
    //              RMathLineEdit is with precision 6 and displaying is java related
    //              # Workaround # Reordered sequence
    //                   And get stuck with precision 6, allways better then an endless number of digits.
    //    # Issue Solved # Pushing messages to command history is slow (80ms/entry vs casting fitpoints: 10/ms)
    //              Solved with optionally suppress if not critical or essential
    //              With beVerbose flag in Dialog. Super persistently set
    //    # Done # Optionally delete base entity(-ies) in one operation at end. Super persistently cleared
    //    # Done # Beside dynamically scale Open Forms optionally Align @start @end @center
    //    # Done # With fitN rather fit N or N+1 instead of cast until end
    //              Kind of a hybrid starting from version 0.40
    //    # Done # Closed forms align too. 
    //              Use shift closed forms placement 0-100% actual painter stepsize
    //    # Done # Beside splines add painter entities types: Line, Point, Arc, Circle, Poly, Poly global
    //    # Done # Include poly and global poly bulging


    // ***Reminders*************************************************************************************
    //    !! Use '==' not '=' !! apart from the fact '==' is allways conditional
    //    Don't use '>>' by mistake nor '<<' '=<' '=>'
    //    Code on lines must end with ';' or '}' and nothing else unless the code is properly multilined
    //    Simple test: even counts of '[', ']', '(', ')', '{', '}'   forget 1 ')' will lead to crash
    //    'this.variable' in FlexPainter.prototype.xyz functions    Scope: all FlexPainter.prototype.xyz functions
    //    const only have function scope
    //    bool true = multipler 1, bool false = multipler 0 BUT TAKE CARE
    //    Return more variables: var ret = []; ret.push(...); ret.push(...); return ret;
    //    RMath.fuzzyCompare(value, value, tolerance);  RS.PointTolerance
    //    Math.round ECMAScript rounds to nearest integer tie breaking half towards positive infinity
    //    meaning: m.500 rounds up = m+1 , -m.500 rounds up = -m+1
    //    Common is rounding to nearest integer tie breaking half away from zero (towards infinity)
    //    meaning: m.500 up = m+1 , -m.500 down = -m-1
    //    https://upload.wikimedia.org/wikipedia/commons/8/8a/Comparison_rounding_graphs_SMIL.svg
    //    Math.trunc simply cuts of the point and the digits. Is not done by Math!
    //    Progress see Ucs.js ??? ISNOT part of EAction Class. See RProgressHandler Class
    //        EAction.setProgressText("Applying operation...");
    //        EAction.setProgress((100 / ids.length) *  i);
    //        EAction.setProgress(100);
    //        EAction.setProgressEnd();
    //    this.updatePreview();
};

