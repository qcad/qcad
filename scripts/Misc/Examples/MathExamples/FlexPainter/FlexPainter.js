/**  FlexPainter Beta version 0.41
 * # ToDo # Totally free with credit is fine
 *
 * Copyright (c) 2019 by CVH.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * With the unmatched assistance of Andrew Mustun.
 * This script is donated to the QCAD project.
 * Copyright (c) 2011-2019 by Andrew Mustun. All rights reserved.
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
include("scripts/simple.js");    // Added for addSpline simple API
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
    // FlexPainter.init states "Requires Document"
    // A document should be available....Retreive document, units
    var document = this.getDocument();
    this.units = document.getUnit();
    var di = this.getDocumentInterface();
    var ids = document.querySelectedEntities();    // Query Qlist with selected
    const idn = ids.length;    // Number of selected entities

    // Terminate without document units
    if (!isNumber(this.units) || isNull(this.units)){
        // Push warning to command history and terminate
        qDebug("NO Doc units");
        EAction.handleUserWarning("NO Doc units");
        qDebug("Nothing casted, command terminated");
        EAction.handleUserMessage("Nothing casted, command terminated");
        debugger;    // Can't handle no units! Halt in debugger mode
        this.terminate();    // Or terminate altogether
        return;
    }

    // Terminate without any entity selected or continue with command
    if (idn == 0) {
        // Push warning to command history and terminate
        qDebug("No selection");
        EAction.handleUserInfo("Please, make a selection!");
        this.terminate();
        return;
    }
    else {
        // Push command start to command history
        qDebug("FlexPainter Start");
        EAction.handleUserCommand("MathExamples: FlexPainter");
    }

    // Show Dialog & terminate if cancelled
    if(!this.showDialog()) {
        // Push cancelled to command history and terminate
        qDebug("Dialog cancelled");
        EAction.handleUserMessage("Cancelled, command terminated");
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

    // Sum used appendice lengths, to do is existing
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
            //  (entity based)
            this.isTanCloObj = false;
            if (isPolylineEntity(entity) || isSplineEntity(entity)) {
                if (entity.isGeometricallyClosed()) {
                    if (isSplineEntity(entity)) {
                        this.isTanCloObj = entity.isPeriodic();
                    }
                    else if (isPolylineEntity(entity)) {    // Near tangentially connected
                        this.isTanCloObj = RMath.fuzzyAngleCompare(shape.getDirection1() + Math.PI, shape.getDirection2());
                    }
                }
            }
            else if (isCircleEntity(entity) || isFullEllipseEntity(entity)) {
                this.isTanCloObj = true;
            }

            // Determine casting type
            // # Issue Solved # Its far more faster to set how to cast on the selected
            //           base entity then to test how to cast every point casted.
            if (isLineShape(shape) || isArcShape(shape) || isSplineShape(shape)) this.castingType = 1;
            if (isPolylineShape(shape)) this.castingType = 3;
            // # Issue Fixed # No mathematical Closed Form. 
            // Is by serie expansion. Is very time consuming
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
            // Reserve 1 painter Length, n.knots+1 times
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
                            (this.objlength - (knotlength * this.insertions * this.mainScaleX))
                            /    // Divided by
                            (painterStepSize * this.mainScaleS));
            }
            else {    // Open Forms: +Apexes, +n.knots, 1 more as possible
                var fitN = Math.ceil(
                            (this.objlength - ((reservedLength + appendiceslength) * this.mainScaleX))
                            /    // Divided by
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
                qDebug("Too many castings. Skipped");
                if (!this.beVerbose) EAction.handleUserWarning("Too many castings. Skipped!");
                continue;    // Skip to next selected entity
            }

//debugger;
            // Dynamic scaler for continuous Closed Forms and forced to scale Open Forms
            var dynScale = 1.00;
            if (this.isTanCloObj) {    // Continuous Closed Forms: +No apexes, +n.Knots
                dynScale =
                    this.objlength
                    /    // Divided by sum
                    ((knotlength * this.insertions * this.mainScaleX)
                    + (fitN * painterStepSize * this.mainScaleS));
            }
            else {    // Open Forms: +Apexes, +n.Konts
                if (this.forcedDyn) {    // Forced to scale Open Forms
                    dynScale =
                        this.objlength
                        /    // Divided by sum
                        (((reservedLength + appendiceslength) * this.mainScaleX)
                        + (fitN * painterStepSize * this.mainScaleS));
                }    // Else: Dynamic scaler stays f1.00
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
            // Any chain can locally only end with one such void if any
            var surPlusLabs = painterVoid;

            // Global surplus absolute:
            // Any void left globally
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
            // In any chain fits one single Null-Length painter extra
            // Except centered (There will be no place for more then 1 full painter)
            if (!this.isTanCloObj && (this.factorsurPlus != 0.50)) {
                if (painterLength == 0.00) {
                    fitN+= chainsN;
                    surPlusLabs -= painterVoid
                }
            }

            // On Open Forms: Besides Null-Length painters
            // The complete chain may expose a void globally
            // The global void may admit only one more painter
            // Except centered: There will be no place for 2 painter steps
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
            if (!this.isTanCloObj) {    // All Open Forms aligning
                this.distFromStart = surPlusGabs * this.factorsurPlus;
            }
            else {    // All Closed Forms shifting by % off stepsize
                this.distFromStart = painterStepSize * this.scalerS * this.closeShift;
            }

            // With non-grouped casting: collects additions to one single operation every entity
            if (!this.groupCasts) startTransaction();
            // Intentional +TAB Transaction Block

                // Cast & morphs painters over Entities
                // ------------------------------------
                // Optionally cast begin apex painter On Open Forms
                if (this.doBeginApex) {    // Required and existing
                    if (!this.isTanCloObj) {    // On Open Forms
                        this.countCastpoints += this.castPainter(shape, this.beginApexData);
                        this.countNewEntities += this.beginApexData[0][0] - this.beginApexData[0][1];
                        this.distFromStart += this.beginApexData[0][2] * this.scalerX;
                    }
                }

                // Repeat chain + insertion over whole the entity
                // Runs at least once, no insertion on last run
                for (var m=0; m<=this.insertions; m++) {
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
                    for (var n=1; n<=nMax; n++) {    // Zero omitted = virtual(n+1)
                        this.countCastpoints += this.castPainter(shape, this.mainData);
                        this.countNewEntities += this.mainData[0][0] - this.mainData[0][1];
                        this.distFromStart = startedAt + (n * painterStepSize * this.scalerS);
                    // Loop main painters
                    }

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
                    // Except for the last loop
                    if (m < this.insertions) {
                        if (this.doInserts) {    // Required and existing
                            this.countCastpoints += this.castPainter(shape, this.knotData);
                            this.countNewEntities += this.knotData[0][0] - this.knotData[0][1];
                            this.distFromStart += this.knotData[0][2] * this.scalerX;
                        }
                    }
                // Loop chains
                }

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

                // Cast global splines if any, open/closed on open/closed Forms
                var jsn = this.dotStringData.length;
                for (var js=0; js<jsn; js++) {    // Cycle through all global splines
                    addSpline(this.dotStringData[js], this.isTanCloObj);
                }
                this.countNewEntities += jsn;

                // Cast global polys if any, open/closed on open/closed Forms
                var jpn = this.nodStringData.length;
                for (var jp=0; jp<jpn; jp++) {    // Cycle through all global polys
                    addPolyline(this.nodStringData[jp], this.isTanCloObj, false);
                }
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
                if (i != idn - 1) {    // # Workaround # 2.Skip: only one and last
                // # Issue Fixed # 2.Fix slows down unecessary
                    this.updatePreview();    // # Workaround # 1.Best fix to show progress sequentially
                }
            }

            if (this.delEntity) this.trashCan.push(id);
            this.countEntities++;
        // Loop all selected entities
        }

    // Intentional -TAB: Transaction Block
    // Optionally parse all additions as one single operation
    if (this.groupCasts) var castResult = endTransaction();    // No error if without any

    // Optionally empty trash can
    if (this.delEntity) {
        var jn = this.trashCan.length;
        if (jn > 0) {
            op = new RDeleteObjectsOperation();
            for (var j=0; j<jn; j++) {    // Cycle through all necessary deletions
                // query the stored entity copy back from the document
                // and use this to delete the entity
                op.deleteObject(document.queryEntity(this.trashCan[j]));
            }
            di.applyOperation(op);
        // # ToDo # On groupCasts transfer selection to casted v0.42 ???
        // # Issue # Selecting too many can greatly slow down Qcad
        }
    }

    // Push summary to command history
    // With no castings
    // # Issue Fixed # Without suited in selection castResult is not set
    if (this.countEntities == 0 || castResult.isFailed()) {
        // # Workaround # countEntities isNull, 2e of OR is not processed
        // 'else' if (castResult.isFailed())
        // With none
        if (this.countEntities == 0) {
            qDebug("Nothing casted, terminated");
            EAction.handleUserMessage("Nothing casted, command terminated");
        }
        // With castResult.isFailed
        else if (castResult.isFailed()) {
            qDebug("Casting failed, terminated");
            EAction.handleUserMessage("Casting failed, command terminated");
        }
    }
    // With any castings
    else {
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
            if (this.delEntity && jn > 0) {
                msg = "Deleted " + jn;
                msg += (jn > 1) ? " base entities" : " base entity";
                msg += " as one deletion";
                qDebug(msg);
                EAction.handleUserInfo(msg);
            }
        }    // Else: not smothered
        // Push command end message to command history
        msg = "Casting complete (" + (Date.now() - crono) + "ms)";
        EAction.handleUserMessage(msg);
        qDebug("Command end");
    }

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
    // faster: local const  // faster: at top
    const objlength = this.objlength;
    const distFromStart = this.distFromStart;
    const skn = painterData[0][0];    // Number of entries in the dataset
    var countCastpoints = 0;

    // Cycle through all painter entities
    for (var sk=1; sk<=skn;sk++) {    // Zero omitted = header
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

            // Flaws with POLYLINES are getting pritty annoying
            //-------------------------------------------------
            // Catch castings nearly at entity length, copy at case4
            if (RMath.fuzzyCompare(activeDist, objlength, RS.PointTolerance)) {
                //activeDist = objlength;
                //qDebug("NearEnderCastpoint"); //non-MSWinTesting
                //EAction.handleUserWarning("NearEnderCastpoint"); //MSWinTesting
            };
            // Catch end crossers
            if (activeDist > objlength) {
                //activeDist = objlength;
                if (!this.isTanCloObj) {
                    qDebug("TooFarCaster"); //non-MSWinTesting
                    if (!this.beVerbose) EAction.handleUserWarning("TooFarCaster"); //MSWinTesting
                }
            };
            //-------------------------------------------------

            // Use different methods to determine castPoint & castAngle
            switch(this.castingType) {
                case 1:
                    // Over Lines, Arcs & open Splines simply by castPoint on shape
                    // Lines, Arcs No hard ending. Splines stiff ending, avoid crossing
                    // # Issue # IS NOT accurate on Splines, flaw larger rather near an ending?!
                    var castPoint = shape.getPointWithDistanceToStart(activeDist);
                    // # Issue Fixed # Geo closed spline: Cast on begin point has angle of ending
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
                    // isTanCloObj, simply restart from zero
                    var castPoint = shape.getPointWithDistanceToStart(activeDist % objlength);
                    var castAngle = shape.getAngleAt(activeDist, RS.FromStart);
                    break;
                case 3:
                    // Over open Polyline & EllipseArc by castPoint on ClosestSegment
                    // Hard ending, avoid crossing
                    // # Issue Fixed # Geo closed poly: Cast on end point has angle of beginning (lines!arcs?)
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
                    // isTanCloObj, simply restart from zero
                    // # Issue Fixed # Freak BUG casting non dynscaled very near endpoint eg. delta 4e-14, @453.25--7166 on 453.25--717 long
                    if (RMath.fuzzyCompare(activeDist, objlength, RS.PointTolerance)) {
                        // # Workaround # Fixed with catching ClPolyNearEnder and force at full lenght
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
                    // Circles have no ending
                    var centerAngle = activeDist / shape.getRadius();
                    var castPoint = shape.getPointAtAngle(centerAngle);
                    var castAngle = centerAngle + this.orthoAngle;
                    break;
                default:
                    // Should not occur, good practices to include
            }    // End switch(this.castingType)

            // Cast a new point
            var castVector = new RVector(castPoint.x - Math.sin(castAngle) * scaledOffsetSize,
                                         castPoint.y + Math.cos(castAngle) * scaledOffsetSize);

            // Catch casting null-vectors
            if (isNull(castVector)) {
                qDebug("Casting Null-Vector");
                EAction.handleUserWarning("Casting Null-Vector"); //MSWinTesting
                debugger;    // Faulty! Halt in debugger mode
            }

            // Push casted point to collectors
            switch(nominator) {
                case "Point":    // One point
                case "Line":    // Two points
                case "Poly":    // [Vertex,Bulge,Rel] in an array
                    // # Issue Fixed # addPoly not working with Rvectors
                    // # Workaround # split castVector in x and y
                    // https://qcad.org/rsforum/viewtopic.php?t=6618
                    newEntityData.push([castVector.x,castVector.y,partData[k][2]]);
                    break;
                case "Spline":    // Points in an array
                    newEntityData.push(castVector);
                    break;
                case "Arc":    // Center point, radius, startAngle, endAngle, reversed
                    newEntityData.push(castVector);
                    // Add radius, beginangle, endangle, reversed
                    newEntityData.push(partData[k][2] * this.scalerY);
                    // # Issue Solved # simple_create.js works with degrees and deg2rad
                    // Solved with rad2deg(val)
                    newEntityData.push(partData[k][3] + rad2deg(castAngle));
                    newEntityData.push(partData[k][4] + rad2deg(castAngle));
                    newEntityData.push(partData[k][5]);
                    break;
                case "Circle":    // Center point, radius
                    newEntityData.push(castVector);
                    // Add radius
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
                    if (this.nodStringData.length == nodStringN) {
                        // Start a new node-string collector with this first item
                        this.nodStringData[this.nodStringData.length] = [castVector];
                    }
                    else {    // Add to existing node-string collector
                        this.nodStringData[nodStringN][this.nodStringData[nodStringN].length] = castVector;
                    }
                    break;
                default:
                    // Should not occur, good practices to include
            }    // End switch(nominator)
        // Loop all painter data parts
        }

        // Cast new entity with local collector
        // # Issue Fixed # Is no error with empty newEntityData, may eventually lead to AppCrash
        // # Issue # Speed: Replace simple_create calls with function return addShape
        if(!isNull(newEntityData)) {    // # Workaround # Catch null-vectors, only cast with data
            switch(nominator) {
                case "Spline":    // Cast open spline with array of collected casted fitpoints
                    addSpline(newEntityData, false);
                    break;
                case "Line":    // Cast line with collected casted ending points
                    addLine(
                        newEntityData[0],
                        newEntityData[1]);
                    break;
                case "Point":    // Cast point with casted center point
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
                case "Poly":    // Cast poly with array of collected casted vertices and bulges
                    addPolyline(newEntityData);
                default:
                    // Dots and Nods are not handled local
            }    // End switch(nominator)
        }
    // Loop all painter entities
    }
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

    // Initiate the dialog comboboxes
    // Before any dialog change functions is active
    this.initWidgetsCombo(dialog);

    // Initiate the dialog change functions
    // # Issue Fixed # Immediately active, and not fully functional yet
    // The order of initWidgets and restoreState has pro an cons
    // # Workaround # Chosen for initWidgetsCombo--initWidgets--restoreState
    this.initWidgets(dialog);

    // Load persistent dialog entries
    // Restoring old values will trigger dialog change functions
    WidgetFactory.restoreState(dialog);

    // Detect first load: A zero-width painter never makes sense
    if (widgets["MainWidth"].getValue() == 0.00) {    // Is the first load
        // Painters, Insertions, Icons and Prefs are by default
        qDebug("First Use: " + RUnit.unitToName(this.units)); //non-MSWinTesting
        EAction.handleUserMessage("First Use: " + RUnit.unitToName(this.units)); //MSWinTesting

        // Remember using current document units
        widgets["UnitsLabel"].text = RUnit.unitToName(this.units);

        // Initiate default painter set
        //     this.PainterSetInit("Default");
        // # Workaround # Tried with success:
        //     widgets["PainterSelection"].setCurrentText("Default");
        // # Issue Solved # The Dialog starts with the non-existent set "Default"
        //          Solved with "CurtainRopeProto". Offcourse
        widgets["PainterSelection"].currentText = "CurtainRopeProto";

        // Set an appropriate default painter width
        // The idee behind this is: Metric starts with 10 units
        // 10mm with mm, 10m with m, 10km with km
        // Imperial start with an equivalent counterpart
        switch(this.units) {
            case 4:    //   and all not specified (Metric)
            default:
                widgets["MainWidth"].setValue(10.00);
        // # Issue Fixed # Not functional for first use
        // This activates the change function and fails again for the same reason the get's are created
        // And this did not occur with WidgetFactory.restoreState without any former use
        // Fixed with setCurrentText some lines higher
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
        }    // End switch(this.units)
        // 'PreserveLook' is set by default
        // The change functions are active
        // MainPainterBox will auto adapt
    }
    else {    // Not the first load
        // When former used units differs adapt dimensions appropriately
        if (widgets["UnitsLabel"].text != RUnit.unitToName(this.units)) {
            // When current or former is non metric apply correction
            if (!RUnit.isMetric(RUnit.parseUnit(widgets["UnitsLabel"].text)) || !RUnit.isMetric(this.units)) {
                qDebug("ReCalcPersistentDims"); //non-MSWinTesting
                EAction.handleUserMessage("ReCalcPersistentDims"); //MSWinTesting
                var correction = RUnit.convert(1.00, this.units, RUnit.parseUnit(widgets["UnitsLabel"].text));
                // Apply correction on all 3 preferences separately if relevant
                if (widgets["PreserveLook"].checked===false) {    // Not base9
                    // # Issue Fixed # Dialog RMathLineEdit not active.
                    // # .getValue returns no real values
                    // # .text may return a formula
                    // # Workaround # RMath.eval(text)
                    // # Issue # Not checked if its a number
                    widgets["MainWidth"].setValue(RMath.eval(widgets["MainWidth"].text) / correction);
                    // MainPainterBox is prevented to adapt proportionally
                    widgets["MainLengthX"].setValue(RMath.eval(widgets["MainLengthX"].text) / correction);
                    widgets["MainStepX"].setValue(RMath.eval(widgets["MainStepX"].text) / correction);
                } else {    // Apply correction and adapt base9
                    widgets["MainWidth"].setValue(RMath.eval(widgets["MainWidth"].text) / correction);
                    // MainPainterBox will auto adapt
                }
            }    // Else: both metric => Do nothing
            // Remember using current document units
            widgets["UnitsLabel"].text = RUnit.unitToName(this.units);
        }
        // # Issue Solved # When PainterSelection is equal former use
        // only PainterBox checked-state is included in restoreState(dialog)
        // Without change in PainterSelection, PainterBox enabled-state can not adapt
        // Solved with no current text and currentIndex = -1 in UI combo
        // restoreState(dialog) will set former painter set used
        // PainterBox enabled-state will auto adapt by change function
    }

//debugger;
    do {    // Repeat untill entries are flawless
    // # Issue # Simple & Dirty! Surely there are neater ways to do this
        var errmsg = undefined;

        // Activate FlexPainter dialog modal
        if (!dialog.exec()) {
            dialog.destroy();
            EAction.activateMainWindow();
            return false;   // Dialog rejected
        }

        // Retrieve user scaling preferences
        // Get and validate mainScaleY entry
        this.mainScaleY = Math.abs(widgets["MainWidth"].getValue()) / 9;
        // # Issue # Not checked if its a number
        if (this.mainScaleY > 111) {    // Upper limit
            this.mainScaleY = 111;
            errmsg = "! Width crossed upper limit !";
        }
        if (this.mainScaleY < 0.01) {    // Lower limit
            this.mainScaleY = 0.01;
            errmsg = "! Width crossed lower limit !";
        }
        // Push width error warning to command history
        if (!isNull(errmsg)) {
            qDebug(errmsg);
            EAction.handleUserWarning(errmsg);
            // re-parse to UI
            widgets["MainWidth"].setValue(this.mainScaleY * 9);
            errmsg = "!";
        }

        // Get and validate MainPainterBox entries
        if (widgets["PreserveLook"].checked===true) {
            this.preserveLook = true;
            // Preserve the look with uniform scaling
            this.mainScaleX = this.mainScaleY;
            this.mainScaleS = this.mainScaleY;
        }
        else {    // Not checked
            this.preserveLook = false;
            // Get and validate mainScaleX entry
            // Painter set can have main painter length zero, avoid Div0
            if (this.mainData[0][2] == 0.00){    
                this.mainScaleX = 1.00;    // Just to avoid zero or Div0 later on
                if (widgets["MainLengthX"].getValue() > 0.00) {
                // # Issue # Not checked if its a number
                    errmsg = "! Is zero-length painter !";
                }
            }
            else {
                this.mainScaleX = Math.abs(widgets["MainLengthX"].getValue()) / this.mainData[0][2];
                // # Issue # Not checked if its a number
            }
            if (this.mainScaleX > 111) {    // Upper limit
                this.mainScaleX = 111;
                errmsg = "! Length crossed upper limit !";
            }
            if (this.mainScaleX < 0.01) {    // Lower limit
                this.mainScaleX = 0.01;
                errmsg = "! Length crossed lower limit !";
            }
            // Push any length error warning to command history
            if (!isNull(errmsg)) {
                if (errmsg != "!") {
                    qDebug(errmsg);
                    EAction.handleUserWarning(errmsg);
                    // re-parse to UI
                    widgets["MainLengthX"].setValue(this.mainData[0][2] * this.mainScaleX);
                errmsg ="!"
                }
            }

            // Get and validate mainScaleS entry
            this.mainScaleS = Math.abs(widgets["MainStepX"].getValue()) / this.mainData[0][3];
            // # Issue # Not checked if its a number
            if (this.mainScaleS > 111) {    // Upper limit
                this.mainScaleS = 111;
                errmsg = "! Stepsize crossed upper limit !";
            }
            if (this.mainScaleS < 0.01) {    // Lower limit
                this.mainScaleS = 0.01;
                errmsg = "! Stepsize crossed lower limit !";
            }
            // Push stepsize error warning to command history
            if (!isNull(errmsg)) {
                if (errmsg != "!") {
                    qDebug(errmsg);
                    EAction.handleUserWarning(errmsg);
                    // re-parse to UI
                    widgets["MainStepX"].setValue(this.mainData[0][3] * this.mainScaleS);
                    errmsg ="!"
                }
            }
        }
    // Loop untill entries are flawless
    }
    while (!isNull(errmsg));

    // Retrieve user Closed Forms shifting preference (0-100)
    this.closeShift = widgets["CloseShift"].value / 100;

    // Retrieve user casting preferences
    this.flipPainter = (widgets["FlipPainter"].checked===true);
    this.groupCasts = (widgets["GroupCasts"].checked===true);
    this.SubLayerCasts = (widgets["SubLayerCasts"].checked===true);
    this.doBeginApex = (widgets["DoBeginApex"].checked===true);
        // Only do if definition exist (doubling the checked/enabled lock)
        if (this.beginApexData[0][0] == 0) this.doBeginApex = false;
    this.doEndApex = (widgets["DoEndApex"].checked===true);
        // Only do if definition exist (doubling the checked/enabled lock)
        if (this.endApexData[0][0] == 0) this.doEndApex = false;
    this.doInserts = (widgets["DoInserts"].checked===true);
        // Only do if definition exist (doubling the checked/enabled lock)
        if (this.knotData[0][0] == 0) this.doInserts = false;
    // # ToDo # Temporary fixed insertions for testing
    // Should be zero with doInserts = false
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
    else {    // Not forced to scale dynamically => Some surPlusGabs length
        if (widgets["AlignCenter"].checked===true) {
            this.factorsurPlus = 0.50;    // Start with half the surPlusGabs length
        }
        else if (widgets["AlignEnd"].checked===true) {
            this.factorsurPlus = 1.00;    // Start with the full surPlusGabs length
        }    // Else: ("AlignStart") or start with none
    }

    // Retrieve user painter set selection
    // Both text based
    this.painterSet = widgets["PainterSelection"].currentText;
    this.painterKnot = widgets["KnotSelection"].currentText;

    // Push smothered painter summary to command history
    if (!this.beVerbose) {
        EAction.handleUserInfo("Painter set: " + this.painterSet);
        EAction.handleUserInfo("Width: " + (9 * this.mainScaleY));
        EAction.handleUserInfo("Length: " + (this.mainData[0][2] * this.mainScaleX));
        EAction.handleUserInfo("Stepsize: " + (this.mainData[0][3] * this.mainScaleS));
        EAction.handleUserInfo("- - - = * = - - -");
    }

    // Save persistent dialog entries and finish
    widgets["BeVerbose"].checked = true;    // Super persistent checked
    widgets["DelEntity"].checked = false;    // Super persistent unchecked
    WidgetFactory.saveState(dialog);
    dialog.destroy();
    return true;   // Dialog accepted
};

/**
 * Initiate the FlexPainter dialog change functions.
 */
// Based on the scaling dialog Widget
//    HatchDialog.js is maybe a beter base ???
FlexPainter.prototype.initWidgets = function(widget, postfix) {

    if (isNull(postfix)) {    // Unknown purpose, left as was
        postfix = "";
    }

    // HERE IN SCOPE
        // widget
        // postfix
        var widgets = getWidgets(widget);
        // FlexPainter.includeBasePath

    // HERE NOT IN SCOPE
        // this.PainterSetInit("whatever")
        // this.mainData[0][(0,1)]
        // this.beginApexData[0][0]
        // this.endApexData[0][0]
        // this.knotData[0][0]

    var self = this;

    // On PainterSelection change:
    // Continuously: Adapt Preview icons
    //               Re-initiate painter set & Prefs
    //               Force base9 and parse MainWidth to MainPainterBox
    widgets["PainterSelection"].editTextChanged.connect(
                function(currentText) {
                    // # ToDo # Check set data named 'currentText' and report if none
                    // Adapt icons
                    widgets["PreviewPainters"].icon = new QIcon(FlexPainter.includeBasePath + "/Icons/" + currentText + ".svg");
                    // # ToDo # Only one icon set yet. Hardcoded here as "CurtainRopeProto" vs currentText
                    widgets["PreviewKnot"].icon = new QIcon(FlexPainter.includeBasePath + "/Icons/" + "CurtainRopeProto" + "Knot" +".svg");
                    // Re-initiate painter set
                    // # Issue Fixed # FlexPainter.PainterSetInit() out of scope
                    // # Workaround # getPainterSet functions (calls PainterSetInit)
                    self.getPainterSet(currentText);
                    // Adapt for Apexes and Insertions
                    // # Issue Fixed # Painter data out of scope
                    // # Workaround # getDoBeginApex, getDoEndApex and getDoInserts functions (return boolean)
                    widgets["DoBeginApex"].setEnabled(self.getDoBeginApex());
                    widgets["DoEndApex"].setEnabled(self.getDoEndApex());
                    widgets["DoInserts"].setEnabled(self.getDoInserts());
                    // Width remains: Force MainPainterBox to base9 by PreserveLook
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
                    // Don't allow entry to start with 'minus'
                    widgets["MainWidth"].text = text.replace(/^-/, "");
                    // With PreserveLook parse MainWidth to MainPainterBox base9
                    if (widgets["PreserveLook"].checked===true) {
                        var scaleW = widgets["MainWidth"].getValue() / 9;    // can be NaN
                        // # Issue Fixed # Painter data out of scope
                        // # Workaround # getBase9Length and getBase9Stepsize functions (return dimension)
                        widgets["MainLengthX"].setValue(self.getBase9Length() * scaleW);
                        widgets["MainStepX"].setValue(self.getBase9Stepsize() * scaleW);
                    }
                });

    // On PreserveLook toggled: (can be on or off)
    // Continuously: Adapt PreserveLook icon
    //               When checked parse MainWidth to MainPainterBox base9
    //               Adapt for Null-Length painter if applicable
    widgets["PreserveLook"].toggled.connect(
                function(checked) {
                    if (checked) {    // Checked: Adapt icon
                        widgets["PreserveLook"].icon = new QIcon(FlexPainter.includeBasePath + "/PreserveLookOn" + postfix + ".svg");
                    }
                    else {    // Uncheked: Adapt icon
                        widgets["PreserveLook"].icon = new QIcon(FlexPainter.includeBasePath + "/PreserveLookOff" + postfix + ".svg");
                    }
                    if (checked) {    // Checked: Parse MainWidth to MainPainterBox base9
                        var scaleW = widgets["MainWidth"].getValue() / 9;    // can be NaN
                        // # Issue Fixed # Painter data out of scope
                        // # Workaround # getBase9Length and getBase9Stepsize functions (return dimension)
                        widgets["MainLengthX"].setValue(self.getBase9Length() * scaleW);
                        widgets["MainStepX"].setValue(self.getBase9Stepsize() * scaleW);
                    }
                    // Adapt for Null-Length painter
                    if (!checked && self.getBase9Length() == 0.00) {
                        widgets["LabelLength"].setEnabled(false);
                        widgets["MainLengthX"].setEnabled(false);
                    }
                });

    // On MainLength change:
    // Continuously: Dismiss negative entries
    //               Adapt for Null-Length painter if applicable
    widgets["MainLengthX"].textChanged.connect(
                function(text) {
                    // Don't allow entry to start with 'minus'
                    widgets["MainLengthX"].text = text.replace(/^-/, "");
                    // Adapt for Null-Length painter
                    // # Issue Fixed # Painter data out of scope
                    // # Workaround # getBase9Length function (return dimension)
                    if (self.getBase9Length() == 0.00) {
                        widgets["MainLengthX"].text = "0";
                        widgets["LabelLength"].setEnabled(false);
                        widgets["MainLengthX"].setEnabled(false);
                    }
                });

    // On MainStepX change:
    // Continuously dismiss negative entries
    widgets["MainStepX"].textChanged.connect(
                function(text) {
                    // Don't allow entry to start with 'minus'
                    widgets["MainStepX"].text = text.replace(/^-/, "");
                });
};

/**
 * Get functions for dialog change functions.
 */
// Based on OrthogonalProjections.js Line 194 & 261
// # Issue # Can't explain this but while in debugger mode:
// Found FlexPainter under this but no painter data
// Found painter data under this.FlexPainter.prototype.xyz
// I was astonished that it worked...
FlexPainter.prototype.getPainterSet = function(painterSet) {
    this.PainterSetInit(painterSet);
};

FlexPainter.prototype.getBase9Length = function() {
    if (isNull(this.mainData)) {
        return 0.0;
    }
    return this.mainData[0][2];
};

FlexPainter.prototype.getBase9Stepsize = function() {
    if (isNull(this.mainData)) {
        return 0.0;
    }
    return this.mainData[0][3];
};

FlexPainter.prototype.getDoBeginApex = function() {
    if (isNull(this.mainData)) {
        return false;
    }
    return (this.beginApexData[0][0] > 0);
};

FlexPainter.prototype.getDoEndApex = function() {
    if (isNull(this.mainData)) {
        return false;
    }
    return (this.endApexData[0][0] > 0);
};

FlexPainter.prototype.getDoInserts = function() {
    if (isNull(this.mainData)) {
        return false;
    }
    return (this.knotData[0][0] > 0);
};

/**
 * Initiate painter set data.
 *
 * \return painterSet + "done" for now, never fails to get a set. # ToDo # Sources
 */
// Sub-script of FlexPainter.beginEvent
FlexPainter.prototype.PainterSetInit = function(painterSet) {
    // ** HARDCODED in Arrays (Works similar as objects) **
    qDebug("Asked for: " + painterSet);  //non-MSWinTesting
    EAction.handleUserMessage("Asked for: " + painterSet); //MSWinTesting
    // ** ADJUSTABLE DATA SETS **
    //    Local casting:
    //        Spline [x1,y1],[x2,y2],[x3...  Spline fitpoints, open
    //        Poly [x1,y1,B1],[x2,y2,B2],[x3...  Poly vertices & bulge, open
    //        Line [x1,y1],[x2,y2]
    //        Point [x,y]
    //        Circle [x,y,r]
    //        Arc [x1,y1,r,a0,a1,Rev] (Angles in degrees)
    //    Global casting:
    //        Dots00 [x1,y1],[x2,y2],[x3...  Spline fitpoints, open
    //        Nods00 [x1,y1],[x2,y2],[x3...  Poly vertices, open, no bulging
    //        # ToDo # Add global bulging for completeness
    //    Note on Poly: Morphing is in se non-uniform scaling
    //        Bulging does not adapt, added for completeness, may act weird
    //        If of any use, tangent scaling travers functions can be found in scale.js by CVH

    switch(painterSet) {    // * = fixed for all
        case "CurtainRopeProto":
        // # ToDo # Change apex chains to Poly if applicable
        // # ToDo # Split kinds
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
    case "GreekMeander15":
        this.beginApexData = [[4,2,1.5000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
            this.beginApexData.push(["Nods00",[0.0,4.5],[1.5,4.5]]);
            this.beginApexData.push(["Poly",[1.5,-3.5],[1.0,-3.5],[1.0,3.5],[1.5,3.5]]);
            this.beginApexData.push(["Line",[0.0,4.5],[0.0,-4.5]]);
            this.beginApexData.push(["Nods01",[0.0,-4.5],[1.5,-4.5]]);
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,2,8.0000,8.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[8.0,4.5]]);
            this.mainData.push(["Poly",[0.0,3.5],[6.5,3.5],[6.5,-1.5],[3.5,-1.5],[3.5,0.5],[2.5,0.5],[2.5,-2.5],[7.5,-2.5],[7.5,3.5],[8.0,3.5]]);
            this.mainData.push(["Poly",[8.0,-3.5],[1.5,-3.5],[1.5,1.5],[4.5,1.5],[4.5,-0.5],[5.5,-0.5],[5.5,2.5],[0.5,2.5],[0.5,-3.5],[0.0,-3.5]]);
            this.mainData.push(["Nods01",[8.0,-4.5]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[4,2,1.5000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
            this.endApexData.push(["Nods00",[0.0,4.5],[1.5,4.5]]);
            this.endApexData.push(["Poly",[0.0,3.5],[0.5,3.5],[0.5,-3.5],[0.0,-3.5]]);
            this.endApexData.push(["Line",[1.5,-4.5],[1.5,4.5]]);
            this.endApexData.push(["Nods01",[0.0,-4.5],[1.5,-4.5]]);
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
    case "TelephoneCoilMedio":3.513000
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
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,9.000],[0.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "OrthogonalBar":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,4.5000],[0.0000,-4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "1OrthoPointGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,9.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "2OrthoPointsGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,2,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,4.5000]]);
            this.mainData.push(["Nods01",[0.0000,-4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "1OrthoPointGlobalFlex":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,1,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,9.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "2OrthoPointsGlobalFlex":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,2,0.0000,9.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,4.5000]]);
            this.mainData.push(["Dots01",[0.0000,-4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RulerMetric":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
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
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "RulerInch":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
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
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SinusoidWave":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Spline",[0.0000,0.0000],[0.5000,1.5391],[1.0000,2.8925],[1.5000,3.8971],[1.7500,4.2286],[2.0000,4.4316],[2.2500,4.5000],[2.5000,4.4316],[2.7500,4.2286],[3.0000,3.8971],[3.5000,2.8925],[4.0000,1.5391],[4.5000,0.0000]]);
            this.mainData.push(["Spline",[4.5000,0.0000],[5.0000,-1.5391],[5.5000,-2.8925],[6.0000,-3.8971],[6.2500,-4.2286],[6.5000,-4.4316],[6.7500,-4.5000],[7.0000,-4.4316],[7.2500,-4.2286],[7.5000,-3.8971],[8.0000,-2.8925],[8.5000,-1.5391],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SinusoidWaveGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,2,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Dots00",[0.0000,0.0000],[0.5000,1.5391],[1.0000,2.8925],[1.5000,3.8971],[1.7500,4.2286],[2.0000,4.4316],[2.2500,4.5000],[2.5000,4.4316],[2.7500,4.2286],[3.0000,3.8971],[3.5000,2.8925],[4.0000,1.5391]]);
            this.mainData.push(["Dots00",[4.5000,0.0000],[5.0000,-1.5391],[5.5000,-2.8925],[6.0000,-3.8971],[6.2500,-4.2286],[6.5000,-4.4316],[6.7500,-4.5000],[7.0000,-4.4316],[7.2500,-4.2286],[7.5000,-3.8971],[8.0000,-2.8925],[8.5000,-1.5391]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Dots00",[0.0000,0.0000]]);
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "3PhaseWaveGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
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
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "TriangleWave":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[2.2500,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[6.7500,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "TriangleWaveGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[1,1,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
            this.beginData.push(["Nods00",[0.0000,0.0000]]);
        this.mainData = [[1,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[2.2500,4.5000],[6.7500,-4.5000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000]]);
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SawtoothWave":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[4.5000,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[4.5000,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SawtoothWaveGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[1,1,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
            this.beginData.push(["Nods00",[0.0000,0.0000]]);
        this.mainData = [[1,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[4.5000,4.5000],[4.5000,-4.5000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000]]);
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SqaureWave":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[0.0000,4.5000],[4.5000,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[4.5000,-4.5000],[9.0000,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SqaureWaveFlexing":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[6,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,0.0000],[0.0000,4.5000]]);
            this.mainData.push(["Spline",[0.0000,4.5000],[1.5000,4.5000],[3.0000,4.5000],[4.5000,4.5000]]);
            this.mainData.push(["Line",[4.5000,4.5000],[4.5000,0.0000]]);
            this.mainData.push(["Line",[4.5000,0.0000],[4.5000,-4.5000]]);
            this.mainData.push(["Spline",[4.5000,-4.5000],[6.0000,-4.5000],[7.5000,-4.5000],[9.0000,-4.5000]]);
            this.mainData.push(["Line",[9.0000,-4.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SqaureWaveGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,0.0000],[0.0000,4.5000],[4.5000,4.5000],[4.5000,0.0000],[4.5000,-4.5000],[9.0000,-4.5000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000]]);
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SteppedWave":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,0.0000],[0.0000,1.5000],[0.9000,1.5000],[0.9000,3.0000],[1.8000,3.0000],[1.8000,4.5000],[2.7000,4.5000],[2.7000,3.0000],[3.6000,3.0000],[3.6000,1.5000],[4.5000,1.5000],[4.5000,0.0000]]);
            this.mainData.push(["Poly",[4.5000,0.0000],[4.5000,-1.5000],[5.4000,-1.5000],[5.4000,-3.0000],[6.3000,-3.0000],[6.3000,-4.5000],[7.2000,-4.5000],[7.2000,-3.0000],[8.1000,-3.0000],[8.1000,-1.5000],[9.0000,-1.5000],[9.0000,0.0000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SteppedWaveGlobal":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[2,0,9.0000,9.0000,"Boxed"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Nods00",[0.0000,0.0000],[0.0000,1.5000],[0.9000,1.5000],[0.9000,3.0000],[1.8000,3.0000],[1.8000,4.5000],[2.7000,4.5000],[2.7000,3.0000],[3.6000,3.0000],[3.6000,1.5000],[4.5000,1.5000],[4.5000,0.0000]]);
            this.mainData.push(["Nods00",[4.5000,-1.5000],[5.4000,-1.5000],[5.4000,-3.0000],[6.3000,-3.0000],[6.3000,-4.5000],[7.2000,-4.5000],[7.2000,-3.0000],[8.1000,-3.0000],[8.1000,-1.5000],[9.0000,-1.5000]]);
        this.endData = [[1,1,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
            this.endData.push(["Nods00",[0.0000,0.0000]]);
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SqauredShape":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[1,0,9.0000,18.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Poly",[0.0000,4.5000],[0.0000,-4.5000],[9.0000,-4.5000],[9.0000,4.5000],[0.0000,4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    case "SqauredShapeFlexing":
        this.beginApexData = [[0,0,0.0000]];    // *beginApexData.count, *Dots/Nods.count, *painterLength, .......
        this.beginData = [[0,0,0.0000]];    // *beginData.count, *Dots/Nods.count, *painterLength, .......
        this.mainData = [[4,0,9.0000,18.0000,"Stepped"]];    // *mainData.count, *Dots/Nods.count, *painterLength, painterStepSize, .......
            this.mainData.push(["Line",[0.0000,4.5000],[0.0000,-4.5000]]);
            this.mainData.push(["Spline",[0.0000,-4.5000],[1.0000,-4.5000],[2.0000,-4.5000],[3.0000,-4.5000],[4.0000,-4.5000],[5.0000,-4.5000],[6.0000,-4.5000],[7.0000,-4.5000],[8.0000,-4.5000],[9.0000,-4.5000]]);
            this.mainData.push(["Line",[9.0000,-4.5000],[9.0000,4.5000]]);
            this.mainData.push(["Spline",[9.0000,4.5000],[8.0000,4.5000],[7.0000,4.5000],[6.0000,4.5000],[5.0000,4.5000],[4.0000,4.5000],[3.0000,4.5000],[2.0000,4.5000],[1.0000,4.5000],[0.0000,4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
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
            this.mainData.push(["Nods00",[0.0000,2.2000],[1.0000,-2.2000],[2.0000,2.2000]]);
            this.mainData.push(["Dots00",[0.0000,4.000],[1.0000,3.500],[2.0000,4.000]]);
            this.mainData.push(["Dots01",[0.0000,-4.5000],[1.5000,-4.5000],[3.0000,-4.5000],[4.5000,-4.5000],[6.0000,-4.5000],[7.5000,-4.5000]]);
        this.endData = [[0,0,0.0000]];    // *endData.count, *Dots/Nods.count, *painterLength, .......
        this.endApexData = [[0,0,0.0000]];    // *endApexData.count, *Dots/Nods.count, *painterLength, .......
        this.knotData = [[0,0,0.0000,0,0.00]];    // *knotData.count, *Dots/Nods.count, *painterLength, insertions, insertPoints.......
        break;
    }    // End switch(painterSet)
    // ** USER-ADJUSTABLE PARAMETERS ABOVE **
    return painterSet + " done";
};

/**
 * Initiate the FlexPainter dialog Comboboxes. # ToDo # Sources
 */
// Based on Dimension.js initUiOptions
FlexPainter.prototype.initWidgetsCombo = function(widget) {
    // ** HARDCODED **
    var widgets = getWidgets(widget);
    var painterSetCombo = widgets["PainterSelection"];
    painterSetCombo.clear();
        painterSetCombo.addItem("CurtainRopeProto"); // Slanted: Passed: Over, Boxed, Under
            //On open forms & step > length: Apex detached. Is in se correct
        painterSetCombo.addItem("GreekMeander15"); // Similar Boxed
        painterSetCombo.addItem("GreekMeander15Flexing"); // Similar Boxed
        painterSetCombo.addItem("TelephoneCoilMedio"); // Similar Boxed
        painterSetCombo.addItem("RailwayTrackLineArt"); // Similar Boxed
        painterSetCombo.addItem("RailwayTrackConcrete"); // Similar Boxed
        painterSetCombo.addItem("OrthogonalMark"); // Similar Stepped Null-length
        painterSetCombo.addItem("OrthogonalBar"); // Stepped Null-length: Passed: Over
        painterSetCombo.addItem("1OrthoPointGlobal"); // Similar Stepped Null-length
        painterSetCombo.addItem("2OrthoPointsGlobal"); // Similar Stepped Null-length
        painterSetCombo.addItem("1OrthoPointGlobalFlex"); // Similar Stepped Null-length
        painterSetCombo.addItem("2OrthoPointsGlobalFlex"); // Similar Stepped Null-length
        painterSetCombo.addItem("RulerMetric"); // Similar Boxed
        painterSetCombo.addItem("RulerInch"); // Similar Boxed
        painterSetCombo.addItem("SinusoidWave"); // Similar Boxed
        painterSetCombo.addItem("SinusoidWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("3PhaseWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("TriangleWave"); // Similar Boxed
        painterSetCombo.addItem("TriangleWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("SawtoothWave"); // Similar Boxed
        painterSetCombo.addItem("SawtoothWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("SqaureWave"); // Similar Boxed
        painterSetCombo.addItem("SqaureWaveFlexing"); // Similar Boxed
        painterSetCombo.addItem("SqaureWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("SteppedWave"); // Boxed: Passed: Over, Boxed, Under
        painterSetCombo.addItem("SteppedWaveGlobal"); // Similar Boxed
        painterSetCombo.addItem("SqauredShape"); // Similar Stepped
        painterSetCombo.addItem("SqauredShapeFlexing"); // Similar Stepped
        painterSetCombo.addItem("AllPainterDataTypes"); // Stepped: Passed: Over, Boxed, Under
    // Same solution for PainterBox enabled-state
    painterSetCombo.currentText = "";
    painterSetCombo.currentIndex = -1;
    return;
};

/**
 * Adds a menu for this action to Examples/Math Examples/FlexPainter.
 */
// Based on both Math Examples
FlexPainter.init = function(basePath) {
    var action = new RGuiAction(qsTr("&FlexPainter"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/FlexPainter.js");
    action.setIcon(basePath + "/FlexPainter.svg");
    action.setDefaultShortcut(new QKeySequence("f,p"));
    action.setDefaultCommands(["flexpainter"]);
    action.setGroupSortOrder(79700);
    action.setSortOrder(300);
    action.setWidgetNames(["MathExamplesMenu"]);
};

/**
 * Major remark block as dummy function. Collapsable in NPP as such.
 */
FlexPainter.Remarks = function(only4DummysLikeMe) {
    //    # Error 0 # MAJOR ISSUE 0/2 # Fixed 2 # Workaround 2 #
    //    # Issue 18/54 # Unsolvable 1 # Solved 12 # Fixed 23 # Workaround 23 #
    //    # ToDo 21 # Done 8 # Busy 4 # Reminder 2 #
    // *************************************************************************************************
    //    # ToDo # Solution for Painter data sets.(Partially prepared UI & code)
    //              # ToDo # Investigate entities in Blocks or Files, icons are in files

    //    # ToDo # Casting on newly added sublayer 'Painted'
    //              # Done # Asked if sub-layers are Pro, if so only on Pro, how to know it is Pro

    //    # Busy # Insertable painters (eg. Knots) @(aaa%,bbb%,ccc%,...)(Partially prepared UI & code)

    //    # Busy # Check user numerical entries ... mainScaleX/Y != -n; 0; huge v.37
    //              # ToDo # Investigate '.setValidator' for QLineEdit (Occurs in eg. InvoluteSpur.js)
    //              # ToDo # Check that values are numbers
    //              Done: Can't start entries with '-', can enter expression that gives negative result v.37
    //              Done: Made absolute and factor limited to 0.01 & 111 and written back to Widget v.38
    //              Done: limited casting main painter to 9999 / entity  v.38
    //                  (# ToDo # Revise: On short line in test f0.01 14s 21139 splines /3 is about 7000 painters)
    //              Done: Dirty loop untill flawless v.39

    // *************************************************************************************************
    //    # MAJOR ISSUE Fixed # Dialog painter set selection coding and how to have scope...
    //                    - FlexPainter.PainterSetInit() out of scope
    //                    - Painter data out of scope
    //                    JAVAscript/Qt related  Asked for help
    //              # Workaround # Get functions analogue OrthogonalProjections.js
    //                    - getPainterSet functions (calling PainterSetInit)
    //                    - getDoBeginApex, getDoEndApex and getDoInserts functions (return boolean)
    //                    - getBase9Length and getBase9Stepsize functions (return dimension)
    //              # Issue Fixed # Not functional for first use
    //              # Workaround # Instead of: this.PainterSetInit("Default") wich returns "CurtainRopeProto"
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
    //              # ToDo # Debate not catching NULL entry
    //    # Issue Unsolvable # Can't find where qDebug("...") is sending to
    //              Windows can not: https://qcad.org/rsforum/viewtopic.php?t=6202
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
    //                         factor +/-x2: const orthoAngle (not Global)
    //                         factor +/-x4: var orthoAngle && const orthoAngle (Global) && this.orthoAngle
    //                         factor +/-x8...12: Math.PI/2
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
    //                                        https://qcad.org/rsforum/viewtopic.php?t=6601
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
    //    # Issue Fixed # Pushing messages to command history is slow (80ms/entry vs casting fitpoints: 10/ms)
    //              Optionally suppress if not critical or essential
    //              # Workaround # with beVerbose flag. Super persistently set
    //    # Done # Optionally delete base entity(-ies) in one operation at end. Super persistently cleared
    //    # Done # Beside dynamically scale Open Forms optionally Align @start @end @center
    //    # Done # With fitN rather fit N or N+1 instead of cast until end
    //              Kind of a hybrid in last version
    //    # Done # Closed forms align too. 
    //              Use shift closed forms placement 0-100% actual painter stepsize
    //    # Done # Beside splines add painter entities types: Line, Point, Arc, Circle, Poly, Poly global


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
    //    Math.round rounds correct towards nearest integer
    //    Math.trunc simply cuts of the point and the digits. Is not done by Math!
    //    Progress see Ucs.js ??? ISNOT part of EAction Class. See RProgressHandler Class
    //        EAction.setProgressText("Applying operation...");
    //        EAction.setProgress((100 / ids.length) *  i);
    //        EAction.setProgress(100);
    //        EAction.setProgressEnd();
    //    this.updatePreview();
};
