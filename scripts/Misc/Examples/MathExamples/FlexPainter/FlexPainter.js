/**
 * Beta version 0.34
 * Copyright (c) 2019 by CVH.  # ToDo # Totally free with credit is fine
 * 
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
//# Issue Solved # Use "scripts/simple.js" istead of "simple.js"


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
 * This action paints over all selected line based entities from start to end and minimalist morphs the painter to the curvature
 * Outputs common fitpoint splines the user can edit with any tool available
 * Results may be better with radii of curvature of about the painters actual width or larger
 */

FlexPainter.prototype.beginEvent = function() {
    MathExamples.prototype.beginEvent.call(this);

debugger;

    var document = this.getDocument();    // Query document
    var di = this.getDocumentInterface();
    var ids = document.querySelectedEntities();    // Qlist with selected
    const idn = ids.length;    // Number of selected entities

    // Push command to command history
    EAction.handleUserCommand("MathExamples: Cast FlexPainter");
    // Terminate without any entity selected
    if (idn == 0) {
        // Push warning to command history
        EAction.handleUserWarning("No entities selected!");
        EAction.handleUserMessage("Nothing casted, command terminated");
        this.terminate();
        return;
    }

    // Show Dialog & terminate if cancelled
    if(!this.showDialog()) {
        EAction.handleUserMessage("Cancelled, command terminated");
        this.terminate();
        return;
    }
//    EAction.activateMainWindow();
//    disableInput();

    // Cronometration
    var crono = Date.now();

    // Initiate painter set
    this.PainterSetInit(this.painterSet);

    // Flipping is inverse scaling
    if (this.flipPainter) this.mainScaleY = -(this.mainScaleY);

    // Sum all appendices lengths
    var appendiceslength = 0;
    if (this.hasBeginApex) appendiceslength += this.beginApexData[0][2];
    if (this.hasEndApex) appendiceslength += this.endApexData[0][2];
    if (this.hasInserts) appendiceslength += this.knotData[0][2] * this.insertions;

    // Initiate pi/2, counters, trash can and intermediate message string
    this.orthoAngle = Math.PI/2;    // scope: all script functions
    this.countEntities = 0;
    this.countSplines = 0;
    this.countFitpoints = 0;
    this.trashCan = [];    // Empty trash collector
    var msg = "";

    // With grouped castings : collect all additions to one single operation
    if (this.groupCasts) startTransaction();
    // intentional +TAB
        // Process selected entities
        for (var i=0; i<idn; i++) {    // Cycle through all selected entities
            var id = ids[i];    // Pick Qlist entry
            var entity = document.queryEntity(id);    // Pick entity

            // Limit selection
            if (!isLineEntity(entity) &&
                !isArcEntity(entity) &&
                !isCircleEntity(entity) &&
                !isEllipseEntity(entity) &&
                !isPolylineEntity(entity) &&
                !isSplineEntity(entity)) {
                    // Push warning to command history
                    if (!this.beVerbose) EAction.handleUserWarning(entityTypeToString(entity.getType(),false) + " skipped!");
                    continue;    // Skip to next selected entity
                }

            var shape = entity.castToShape();

            // Set isTanCloObj flag for all geometrically and tangentially closed forms (entity based)
            this.isTanCloObj = false;
            if ((isPolylineEntity(entity) || isSplineEntity(entity))) {
                if (entity.isGeometricallyClosed()) {
                    if (isSplineEntity(entity)) {
                        this.isTanCloObj = entity.isPeriodic();
                    } else if (isPolylineEntity(entity)) {
                        this.isTanCloObj = RMath.fuzzyAngleCompare(shape.getDirection1() + Math.PI , shape.getDirection2());
                    }
                }
            } else if (isCircleEntity(entity) || isFullEllipseEntity(entity)) {
                this.isTanCloObj = true;
            }

            // Detirmine casting type
            if (isLineShape(shape) || isArcShape(shape) || isSplineShape(shape)) this.castingType = 1;
            if (isPolylineShape(shape)) this.castingType = 3;
            // # Issue Solved # No mathematical closed form. Is by serie expansion. Is very time consuming
            // Workaround: Ellipses by casting on a Polyline approximateWithArcs
            if (isEllipseEntity(entity)) {
                var shape = shape.approximateWithArcs(128);
                this.castingType = 3;
                if (this.isTanCloObj) {
                    shape.convertToClosed;
                }
            }
            if (this.isTanCloObj) this.castingType++;    // Promote 1 > 2 || 3 > 4
            if (isCircleShape(shape)) this.castingType = 5;

            // Fit a number of actual painter StepSize lengths
            this.objlength = shape.getLength();
            var painterLength = this.mainData[0][2];
            var painterStepSize = this.mainData[0][3];
            if (this.isTanCloObj) {    // Continuous closed forms > No apexes, +n.Dots > 1 more as possible
                var fitN = Math.ceil((this.objlength - ((painterLength + (this.knotData[0][2] * this.insertions)) * this.mainScaleX)) / (painterStepSize * this.mainScaleX));
            } else {    // Open forms > +Apexes, +n.Dots > 1 more as possible
                var fitN = Math.ceil((this.objlength - ((painterLength + appendiceslength) * this.mainScaleX)) / (painterStepSize * this.mainScaleX));
                if (!this.forcedDyn) fitN--;    // Not forced to scale > 1 less
            }

            // Fit a larger multiple of knotData insertions
            fitN = Math.round(Math.ceil(fitN / (this.insertions + 1))) * (this.insertions + 1);

            // Test for too many castings
            if (fitN > 9999) {
                // Push warning to command history
                if (!this.beVerbose) EAction.handleUserWarning("Too many castings. Skipped!");
                continue;    // Skip to next selected entity
            }

            // Dynamic scaler for continuous closed forms and forced to scale open forms
            this.scalerX = 1;
            this.distFromStart = 0;
            var endCasting = this.objlength;
            if (this.isTanCloObj) {    // Continuous closed forms > No apex, +n.Knots
                this.scalerX = this.objlength / ((painterLength + (this.knotData[0][2] * this.insertions) + (fitN * painterStepSize)) * this.mainScaleX);
                endCasting -= painterStepSize * this.scalerX * this.mainScaleX * 0.9999;    // To catch inaccurate multiSum
                // # ToDo # endCasting does not consider insertions yet
            } else {    // Open forms > +Apexes, +appendices
                if (this.forcedDyn) {    // Forced to scale open forms
                    this.scalerX = this.objlength / (painterLength + appendiceslength + (fitN * painterStepSize)) / this.mainScaleX;
                }    // Else: scalerX stays 1
                // All open forms
                var surPlus = this.objlength - ((painterLength + appendiceslength + (fitN * painterStepSize)) * this.scalerX * this.mainScaleX);
                this.distFromStart = surPlus * this.factorSurPlus;
                endCasting -= painterLength * this.scalerX * this.mainScaleX * 0.9999;    // To catch inaccurate multiSum
                if (this.hasEndApex) endCasting -= this.endApexData[0][2] * this.scalerX * this.mainScaleX;
                endCasting -=  surPlus * (1 - this.factorSurPlus);
                // # ToDo # endCasting does not consider insertions yet
            }

            // Set actual scaler(s)
            this.scalerY = this.mainScaleY;
            if (this.preserveLook) this.scalerY = this.scalerX * this.mainScaleY;
            msg = entityTypeToString(entity.getType(),false);
            msg += (this.scalerX == 1) ? " not dynScaled" : " dynScaled : " + this.scalerX;
            this.scalerX = this.scalerX * this.mainScaleX;

            // Test for too small entities
            if (this.objlength < ((3 * painterStepSize) + painterLength + (this.isTanCloObj * appendiceslength)) * this.scalerX) {
                // Push warning to command history
                if (!this.beVerbose) EAction.handleUserWarning(entityTypeToString(entity.getType(),false) + " Too short. Skipped!");
                continue;    // Skip to next selected entity
            }
            if (!this.beVerbose) EAction.handleUserInfo(msg);

            // Initiate global splines dot collector
            this.dotsSplineData = [];    // Empty global fitpoint collector

            // With non-grouped casting: collects additions to one single operation every entity
            if (!this.groupCasts) startTransaction();
            // intentional +TAB
                // Cast & morphs painters over Entities
                if (!this.isTanCloObj) {    // On open forms
                    if (this.hasBeginApex) {    // Cast begin apex painter
                        this.countFitpoints += this.castPainter(shape,this.beginApexData);
                        this.countSplines += this.beginApexData[0][0] - this.beginApexData[0][1];
                        this.distFromStart += this.beginApexData[0][2] * this.scalerX;
                    }
                    // Cast begin painter, Lenght=0
                    this.countFitpoints += this.castPainter(shape,this.beginData);
                    this.countSplines += this.beginData[0][0] - this.beginData[0][1];
                }

                do {    // Repeat main painter over whole the entity
                    this.countFitpoints += this.castPainter(shape,this.mainData);
                    this.countSplines += this.mainData[0][0] - this.mainData[0][1];
                    this.distFromStart += painterStepSize * this.scalerX;
                }    // Loop whole length
                while (this.distFromStart < endCasting);

                if (!this.isTanCloObj) {    // On open forms
                    // Cast end painter, Lenght=0
                    this.countFitpoints += this.castPainter(shape,this.endData);
                    this.countSplines += this.endData[0][0] - this.endData[0][1];
                    this.distFromStart += (painterLength - painterStepSize) * this.scalerX;
                    if (this.hasEndApex) {    // Cast end apex painter
                        this.countFitpoints += this.castPainter(shape,this.endApexData);
                        this.countSplines += this.endApexData[0][0] - this.endApexData[0][1];
                        this.distFromStart += this.endApexData[0][2] * this.scalerX;
                    }
                }

                // Cast Open/closed global splines on open/closed forms
                var jn = this.dotsSplineData.length;
                for (var j=0; j<jn; j++) {    // Cycle through all global splines
                    addSpline(this.dotsSplineData[j], this.isTanCloObj);
                }
                this.countSplines += jn - 1;

            // Optionally parse all additions as one single operation every entity
            if (!this.groupCasts) {
                var castResult = endTransaction();    // No error if without any
                if (castResult.isFailed()) {    // Casting failed
                    break;    // Break out loop selected entities
                }
                if (i != idn - 1) {    // # Issue Solved # Slow
                    disableInput();
                    update();    // Show progress
                    enableInput();    // # Issue # Deprecated!!??
                }
            }

            if (this.delEntity) this.trashCan.push(id);
            this.countEntities++;
        // Loop all selected entities
        }

    // Optionally parse all additions as one single operation
    if (this.groupCasts) var castResult = endTransaction();    // No error if without any

    // Optionally empty trash can
    if (this.delEntity) {
        var jn = this.trashCan.length;
        op = new RDeleteObjectsOperation();
        for (var j=0; j<jn; j++) {    // Cycle through all deletions
            // query a copy of the stored entity from the document
            // and use it to delete the entity:
            op.deleteObject(document.queryEntity(this.trashCan[j]));
        }
        di.applyOperation(op);
    }

    // Push summary to command history
    if (this.countEntities == 0 || castResult.isFailed()) {
        EAction.handleUserMessage("Nothing casted, command terminated");
    } else {
        if (!this.beVerbose) {
			EAction.handleUserInfo("- - - - -");
            msg = "Casted " + this.countSplines + " splines by " + this.countFitpoints + " fitpoints";
            EAction.handleUserInfo(msg);
            msg = "over " + this.countEntities;
            if (this.countEntities == idn) {
                msg += (this.countEntities > 1) ? " entities" : " entity";
            } else {
                msg += " of " + idn;
                msg += (idn > 1) ? " entities" : " entity";
            }
            msg += " as ";
            if (this.groupCasts || this.countEntities == 1) {
                msg += "one addition";
            } else {
                msg += this.countEntities;
                msg += (this.countEntities > 1) ? " addition" : " additions";
            }
            EAction.handleUserInfo(msg);
            if (this.delEntity && jn > 0) {
                msg = "Deleted " + jn;
                msg += (jn > 1) ? " entities" : " entity";
                msg += " as one deletion";
                EAction.handleUserInfo(msg);
            }
        }
        msg = "Casting complete (" + (Date.now() - crono) + "ms)";
        EAction.handleUserMessage(msg);
    }

//    enableInput();
    this.terminate();
    return;
};

/**
 * Casts Painter local / global spline fitpoints.
 *
 * \return Number of casted fitpoints.
 */
// Sub-script of FlexPainter.beginEvent
FlexPainter.prototype.castPainter = function (shape,splineData) {
    // faster: local const  // faster: at top
    const objlength = this.objlength;
    const distFromStart = this.distFromStart;
    const skn = splineData[0][0];    // Number of entries in the dataset
    var countFitpoints = 0;

    // Cycle through all painter splines
    for (var sk=1; sk<=skn;sk++) {    // Zero omitted
        var newSplineData = [];    // Empty local fitpoint collector
        var partData = splineData[sk];   // Pick painter spline
        var nominator = partData[0];
        var dotStringN = (nominator == "spline") ? 0 : 1 * nominator.slice(4);    // Isolate dot string number
        var kn = partData.length - 1;    // Number of painter spline fitpoints
        countFitpoints += kn;

        // Cycle through all painter spline fitpoints
        for (var k=1; k<=kn;k++) {    // Zero omitted
            var offsetAtDist = partData[k][0];
            var scaledOffsetSize = partData[k][1] * this.scalerY;
            var activeDist = distFromStart + (offsetAtDist * this.scalerX);

            // Use different methods to determine castPoint & castAngle
            switch(this.castingType) {
                case 1:
                    // Lines, Arcs & open Splines simply by castPoint on shape, hard end
                    var castPoint = shape.getPointWithDistanceToStart(activeDist);
                    var castAngle = shape.getAngleAt(activeDist,RS.FromStart);
                    break;
                case 2:
                    // Continuous closed Splines simply by castPoint on shape, no hard end
                    var castPoint = shape.getPointWithDistanceToStart(activeDist % objlength);
                    var castAngle = shape.getAngleAt(activeDist,RS.FromStart);
                    break;
                case 3:
                    // Open Polyline & EllipseArc by castPoint on ClosestSegment, hard end
                    var castPoint = shape.getPointWithDistanceToStart(activeDist);
                    var segmentShape = shape.getSegmentAt(shape.getClosestSegment(castPoint));
                    var castAngle = segmentShape.getAngleAtPoint(castPoint);
                    break;
                case 4:
                    // Continuous closed Polyline by castPoint on ClosestSegment, no hard end
                    var castPoint = shape.getPointWithDistanceToStart(activeDist % objlength);
                    var segmentShape = shape.getSegmentAt(shape.getClosestSegment(castPoint));
                    var castAngle = segmentShape.getAngleAtPoint(castPoint);
                    break;
                case 5:
                    // Circles by equation for castPoint & castAngle, circles have no ending
                    var centerAngle = activeDist / shape.getRadius();
                    var castPoint = shape.getPointAtAngle(centerAngle);
                    var castAngle = centerAngle + this.orthoAngle;
                    break;
                default:
                    // Should not occur, good practices
            } 

            // Push casted fitpoint to collectors
            var castVector = new RVector(castPoint.x - Math.sin(castAngle) * scaledOffsetSize,
                    castPoint.y + Math.cos(castAngle) * scaledOffsetSize);
            if (nominator == "spline") {    // Push to local splines
                newSplineData.push(castVector);
            } else {    // Push to global splines
                if (this.dotsSplineData.length == dotStringN) {    // Start a new dotString
                    this.dotsSplineData[this.dotsSplineData.length] = [castVector];
                } else {    // Add to existing dotString # Issue # Again, Why not push?
                this.dotsSplineData[dotStringN][this.dotsSplineData[dotStringN].length] = castVector;
                }
            }
        // Loop all painter spline fitpoints
        }

        // Cast open spline with collected casted fitpoints
        // # Issue Solved # Is no error with empty newSplineData, will lead to AppCrash
        if (nominator == "spline") addSpline(newSplineData, false);
    // Loop all painter splines
    }

    return countFitpoints;
};

FlexPainter.prototype.PainterSetInit = function(painterSet) {
// ** HARDCODED in Arrays, works similar as splineEntity.objects **
// ** ADJUSTABLE SPLINE DATA SETS **    Painters splines fitpoint vectors
    this.beginApexData = [[29,0,3.92]];    // *beginApexData.count, *Dots.count, *painterLength, ....... (*: fixed for all)
        this.beginApexData.push(["spline",[0.3000,-1.3100],[0.6200,-1.1300],[1.0200,-0.9900],[1.4200,-0.9200]]);
        this.beginApexData.push(["spline",[0.3200,-0.9800],[0.6400,-0.8500],[0.8800,-0.7900]]);
        this.beginApexData.push(["spline",[0.3200,-1.6500],[0.7200,-1.3900],[1.3200,-1.1300],[1.8200,-1.0500]]);
        this.beginApexData.push(["spline",[2.1200,-1.2000],[2.1200,1.2000]]);
        this.beginApexData.push(["spline",[2.1200,1.2000],[2.0200,1.2000],[0.9200,1.6000],[0.2200,2.0000],[0.0266,1.0706],[0.0010,0.0000],[0.0266,-1.0706],[0.2200,-2.0000],[0.9200,-1.6000],[2.0200,-1.2000],[2.1200,-1.2000]]);
        this.beginApexData.push(["spline",[2.3210,-1.3000],[2.3210,1.3000]]);
        this.beginApexData.push(["spline",[2.5210,1.3000],[2.3520,-0.8900]]);
        this.beginApexData.push(["spline",[2.5210,1.3000],[2.5076,1.3500],[2.4710,1.3866],[2.4210,1.4000],[2.3710,1.3866],[2.3344,1.3500],[2.3210,1.3000]]);
        this.beginApexData.push(["spline",[3.1210,1.3000],[3.1076,1.3500],[3.0710,1.3866],[3.0210,1.4000],[2.9710,1.3866],[2.9344,1.3500],[2.9210,1.3000]]);
        this.beginApexData.push(["spline",[3.1210,-1.3000],[3.1076,-1.3500],[3.0710,-1.3866],[3.0210,-1.4000],[2.9710,-1.3866],[2.9344,-1.3500],[2.9210,-1.3000]]);
        this.beginApexData.push(["spline",[3.5210,-1.3000],[3.5076,-1.3500],[3.4710,-1.3866],[3.4210,-1.4000],[3.3710,-1.3866],[3.3344,-1.3500],[3.3210,-1.3000]]);
        this.beginApexData.push(["spline",[2.7210,1.3000],[2.5210,-1.3000]]);
        this.beginApexData.push(["spline",[2.7210,1.3000],[2.7076,1.3500],[2.6710,1.3866],[2.6210,1.4000],[2.5710,1.3866],[2.5344,1.3500],[2.5210,1.3000]]);
        this.beginApexData.push(["spline",[2.7210,-1.3000],[2.7076,-1.3500],[2.6710,-1.3866],[2.6210,-1.4000],[2.5710,-1.3866],[2.5344,-1.3500],[2.5210,-1.3000]]);
        this.beginApexData.push(["spline",[2.9210,1.3000],[2.7210,-1.3000]]);
        this.beginApexData.push(["spline",[2.9210,1.3000],[2.9076,1.3500],[2.8710,1.3866],[2.8210,1.4000],[2.7710,1.3866],[2.7344,1.3500],[2.7210,1.3000]]);
        this.beginApexData.push(["spline",[2.9210,-1.3000],[2.9076,-1.3500],[2.8710,-1.3866],[2.8210,-1.4000],[2.7710,-1.3866],[2.7344,-1.3500],[2.7210,-1.3000]]);
        this.beginApexData.push(["spline",[3.1210,1.3000],[2.9210,-1.3000]]);
        this.beginApexData.push(["spline",[3.3210,1.3000],[3.1210,-1.3000]]);
        this.beginApexData.push(["spline",[3.3210,1.3000],[3.3076,1.3500],[3.2710,1.3866],[3.2210,1.4000],[3.1710,1.3866],[3.1344,1.3500],[3.1210,1.3000]]);
        this.beginApexData.push(["spline",[3.3210,-1.3000],[3.3076,-1.3500],[3.2710,-1.3866],[3.2210,-1.4000],[3.1710,-1.3866],[3.1344,-1.3500],[3.1210,-1.3000]]);
        this.beginApexData.push(["spline",[3.5210,1.3000],[3.3210,-1.3000]]);
        this.beginApexData.push(["spline",[3.5210,1.3000],[3.5076,1.3500],[3.4710,1.3866],[3.4210,1.4000],[3.3710,1.3866],[3.3344,1.3500],[3.3210,1.3000]]);
        this.beginApexData.push(["spline",[3.5210,-1.3000],[3.5344,-1.3500],[3.5710,-1.3866],[3.6210,-1.4000],[3.6710,-1.3866],[3.7076,-1.3500],[3.9400,-1.0976]]);
        this.beginApexData.push(["spline",[2.5210,-1.3000],[2.5076,-1.3500],[2.4710,-1.3866],[2.4210,-1.4000],[2.3710,-1.3866],[2.3344,-1.3500],[2.3210,-1.3000]]);
        this.beginApexData.push(["spline",[3.6900,0.8900],[3.5210,-1.3000]]);
        this.beginApexData.push(["spline",[3.7210,1.3000],[3.7210,-0.9229]]);
        this.beginApexData.push(["spline",[3.7210,1.3000],[3.7076,1.3500],[3.6710,1.3866],[3.6210,1.4000],[3.5710,1.3866],[3.5344,1.3500],[3.5210,1.3000]]);
        this.beginApexData.push(["spline",[3.9400,-1.0976],[3.7210,-0.9229]]);
    this.beginData = [[5,1,0.00]];    // *beginData.count, *Dots.count, *painterLength, .......
        this.beginData.push(["spline",[0.0010,0.6672],[0.0010,-0.6689]]);
        this.beginData.push(["spline",[0.0010,-0.6689],[0.4370,-1.0527],[0.5875,-1.1856],[1.0510,-1.4160],[1.5677,-1.3838],[1.9990,-1.0976]]);
        this.beginData.push(["spline",[1.9990,-1.0976],[1.4995,-0.6567],[1.0000,-0.2158],[0.5005,0.2251],[0.0010,0.6672]]);
        this.beginData.push(["spline",[0.8500,-0.8000],[1.2106,-1.0897],[1.5677,-1.3838]]);
        this.beginData.push(["Dots00",[0.1000,1.3000]]);
    this.mainData = [[4,1,4.00,2.00]];    // *mainData.count, *Dots.count, *painterLength, painterStepSize, .......
        this.mainData.push(["spline",[0.0010,1.0976],[0.6476,0.5268],[1.2943,-0.0440],[1.9409,-0.6148],[2.4370,-1.0527],[2.5875,-1.1856],[3.0510,-1.4160],[3.5677,-1.3838],[3.9990,-1.0976]]);
        this.mainData.push(["spline",[3.9990,-1.0976],[3.3534,-0.5257],[2.7057,0.0440],[2.1244,0.5587],[1.5624,1.0532],[1.4125,1.1856],[0.9490,1.4160],[0.4323,1.3838],[0.0010,1.0976]]);
        this.mainData.push(["spline",[2.8500,-0.8000],[3.2106,-1.0897],[3.5677,-1.3838]]);
        this.mainData.push(["Dots00",[0.4500,1.4500],[1.0500,1.4500],[1.8000,1.2000],[2.1000,1.3000]]);
    this.endData = [[4,1,0.00]];    // *endData.count, *Dots.count, *painterLength, .......
        this.endData.push(["spline",[0.0000,1.0976],[0.4998,0.6565],[0.9995,0.2153],[1.4993,-0.2258],[1.9990,-0.6669]]);
        this.endData.push(["spline",[1.9990,-0.6669],[1.9990,0.6669]]);
        this.endData.push(["spline",[1.9990,0.6669],[1.5614,1.0532],[1.4115,1.1856],[0.9480,1.4160],[0.4313,1.3838],[0.0000,1.0976]]);
        this.endData.push(["Dots00",[0.4500,1.4500],[1.0500,1.4500],[1.8000,1.2000]]);
    this.endApexData = [[25,1,4.00]];    // *endApexData.count, *Dots.count, *painterLength, .......
        this.endApexData.push(["spline",[-0.0200,1.0976],[0.1990,0.9229]]);
        this.endApexData.push(["spline",[0.3990,1.3000],[0.3990,-1.3000]]);
        this.endApexData.push(["spline",[0.3990,1.3000],[0.3856,1.3500],[0.3490,1.3866],[0.2990,1.4000],[0.2490,1.3866],[0.2124,1.3500],[-0.0200,1.0976]]);
        this.endApexData.push(["spline",[0.5990,1.3000],[0.5990,-1.3000]]);
        this.endApexData.push(["spline",[0.5990,1.3000],[0.6124,1.3500],[0.6490,1.3866],[0.6990,1.4000],[0.7490,1.3866],[0.7856,1.3500],[0.7990,1.3000]]);
        this.endApexData.push(["spline",[0.5990,-1.3000],[0.6124,-1.3500],[0.6490,-1.3866],[0.6990,-1.4000],[0.7490,-1.3866],[0.7856,-1.3500],[0.7990,-1.3000]]);
        this.endApexData.push(["spline",[0.7990,1.3000],[0.7990,-1.3000]]);
        this.endApexData.push(["spline",[0.9990,1.3000],[0.9990,-1.3000]]);
        this.endApexData.push(["spline",[0.9990,1.3000],[1.0124,1.3500],[1.0490,1.3866],[1.0990,1.4000],[1.1490,1.3866],[1.1856,1.3500],[1.1990,1.3000]]);
        this.endApexData.push(["spline",[0.9990,-1.3000],[1.0124,-1.3500],[1.0490,-1.3866],[1.0990,-1.4000],[1.1490,-1.3866],[1.1856,-1.3500],[1.1990,-1.3000]]);
        this.endApexData.push(["spline",[1.1990,1.3000],[1.1990,-1.3000]]);
        this.endApexData.push(["spline",[0.1990,-1.3000],[0.2124,-1.3500],[0.2490,-1.3866],[0.2990,-1.4000],[0.3490,-1.3866],[0.3856,-1.3500],[0.39900,-1.3000]]);
        this.endApexData.push(["spline",[1.3990,1.3000],[1.3990,-1.3000]]);
        this.endApexData.push(["spline",[1.3990,1.3000],[1.4124,1.3500],[1.4490,1.3866],[1.4990,1.4000],[1.5490,1.3866],[1.5856,1.3500],[1.5990,1.3000]]);
        this.endApexData.push(["spline",[1.3990,-1.3000],[1.4124,-1.3500],[1.4490,-1.3866],[1.4990,-1.4000],[1.5490,-1.3866],[1.5856,-1.3500],[1.5990,-1.3000]]);
        this.endApexData.push(["spline",[1.5990,1.3000],[1.5990,-1.3000]]);
        this.endApexData.push(["spline",[1.8000,1.2000],[1.8000,-1.2000]]);
        this.endApexData.push(["spline",[1.8000,1.2000],[1.9000,1.2000],[3.0000,1.6000],[3.7000,2.0000]]);
        this.endApexData.push(["spline",[1.8000,-1.2000],[1.9000,-1.2000],[3.0000,-1.6000],[3.7000,-2.0000]]);
        this.endApexData.push(["spline",[0.1990,-1.3000],[0.1990,0.9229]]);
        this.endApexData.push(["spline",[3.7000,2.0000],[3.9990,0.0000],[3.7000,-2.0000]]);
        this.endApexData.push(["spline",[3.7674,-1.6970],[3.2000,-1.4000],[2.6000,-1.1400],[2.2000,-1.0600]]);
        this.endApexData.push(["spline",[3.8336,-1.3848],[3.4000,-1.1800],[3.0000,-1.0200],[2.5000,-0.9200]]);
        this.endApexData.push(["spline",[3.8934,-1.0706],[3.4900,-0.9100],[3.0500,-0.8000]]);
        this.endApexData.push(["Dots01",[1.9500,-1.4000],[1.5500,-1.7500],[1.2000,-1.8000],[0.6000,-1.7000],[0.6000,-1.6000],[1.2000,-1.6500],[1.9500,-1.3000]]);
    this.knotData = [[0,0,5.00,1,50]];    // *knotData.count, *Dots.count, *painterLength, insertions, insertPoints.......
    //    this.knotData.push([[0.0,0.0],[0.0,0.0],....]);
// ** USER-ADJUSTABLE PARAMETERS ABOVE **
};

/**
 * Shows the painter dialog.
 *
 * \return True if the dialog was accepted, false if it was canceled.
 */
// Based on the scaling dialog Widget
FlexPainter.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(FlexPainter.includeBasePath, "FlexPainterDialog.ui");
    var widgets = getWidgets(dialog);
    // Initiate the FlexPainter dialog
    this.initWidgets(dialog);
    // Load persistent dialog entries
    WidgetFactory.restoreState(dialog);

    // Activate FlexPainter dialog modal
    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
        return false;   // Dialog rejected
    }

    // Retrieve user preferences
    this.flipPainter = (widgets["FlipPainter"].checked===true);
    this.groupCasts = (widgets["GroupCasts"].checked===true);
    this.hasBeginApex = (widgets["HasBeginApex"].checked===true);
    this.hasEndApex = (widgets["HasEndApex"].checked===true);
    this.hasInserts = (widgets["HasInserts"].checked===true);
    this.insertions = 0;// Fixed for testing
    this.delEntity = (widgets["DelEntity"].checked===true);
    this.beVerbose = (widgets["BeVerbose"].checked===true);

    // Retrieve painter scaling preferences
    this.mainScaleX = Math.abs(widgets["MainScaleX"].getValue());
    if (this.mainScaleX > 99.99) this.mainScaleX = 99.99;    // Upper limit
    if (this.mainScaleX < 0.01) this.mainScaleX = 0.01;    // Lower limit
    widgets["MainScaleX"].setValue(this.mainScaleX);    // re-parse to UI
    if (widgets["PreserveLook"].checked===true) {
        this.preserveLook = true;
        this.mainScaleY = this.mainScaleX;
    }
    else {
        this.preserveLook = false;
        this.mainScaleY = Math.abs(widgets["MainScaleY"].getValue());
        if (this.mainScaleY > 99.99) this.mainScaleY = 99.99;    // Upper limit
        if (this.mainScaleY < 0.01) this.mainScaleY = 0.01;    // Lower limit
        widgets["MainScaleY"].setValue(this.mainScaleY);    // re-parse to UI
    }

    // Retrieve open forms scaling preferences
    this.factorSurPlus = 0.00;    // factor of the surplus length
    if (widgets["ForcedDyn"].checked===true) {
        this.forcedDyn = true;
    } else {    // Not forced to scale dynamically
        if (widgets["AlignCenter"].checked===true) {
            this.factorSurPlus = 0.50;
        }else if (widgets["AlignEnd"].checked===true) {
            this.factorSurPlus = 1.00;
        }
    }

    // Retrieve painterset
    this.painterSet = widgets["PainterSet"].currentText;
    if (!this.beVerbose) {
		EAction.handleUserInfo("Painter set: " + this.painterSet);
		msg = "Main scale in X: " + this.mainScaleX +
				" , in Y: " + this.mainScaleX;
		EAction.handleUserInfo(msg);
		EAction.handleUserInfo("- - - - -");
	}

    // Save persistent dialog entries and finish
    widgets["BeVerbose"].checked = true;    // Persistent checked
	widgets["DelEntity"].checked = false;    // Persistent unchecked
    WidgetFactory.saveState(dialog);
    dialog.destroy();
    return true;   // Dialog accepted
};

/**
 * Initiate the FlexPainter dialog change functions
 */
FlexPainter.prototype.initWidgets = function(widget, postfix) {
// Based on the scaling dialog Widget
    if (isNull(postfix)) {    // Unknown purpose
        postfix = "";
    }

    // With PreserveLook continuously parse entries in MainScaleX to MainScaleY
    var widgets = getWidgets(widget);
    widgets["MainScaleX"].textChanged.connect(
                function(text) {
                    // don't allow to start with minus
                    widgets["MainScaleX"].text = text.replace(/^-/, "");
                    if (widgets["PreserveLook"].checked===true) {
                        widgets["MainScaleY"].text = text;
                    }
                });

    // On PreserveLook toggle: adapt icon & when checked parse MainScaleX to MainScaleY
    widgets["PreserveLook"].toggled.connect(
                function(checked) {
                    if (checked) {    // Parse MainScaleX > MainScaleY
                        widgets["MainScaleY"].text = widgets["MainScaleX"].text;
                    }
                    // # Issue # Double test on 'Checked'
                    if (checked) {    // Adapt icon
                        widgets["PreserveLook"].icon = new QIcon(FlexPainter.includeBasePath + "/PreserveLookOn" + postfix + ".svg");
                    } else {
                        widgets["PreserveLook"].icon = new QIcon(FlexPainter.includeBasePath + "/PreserveLookOff" + postfix + ".svg");
                    }
                });

//    widgets["PainterSet"].textChanged.connect(
//                function(text) {
//                    // insert code to check for file named 'text' and report error  //
//                    widgets["PreviewPainters"].icon = new QIcon(FlexPainter.includeBasePath + text + ".svg");
//                });    // This should be all needed
};

/**
 * Adds a menu for this action to Examples/Math Examples/Painter.
 */
FlexPainter.init = function(basePath) {
    var action = new RGuiAction(qsTr("&FlexPainter"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/FlexPainter.js");
    action.setIcon(basePath + "/FlexPainter.svg");
//    action.setDefaultShortcut(new QKeySequence("xyz,xyz"));
//    action.setDefaultCommands(["xyzxyz", "xyzxyz"]);
    action.setGroupSortOrder(79700);
    action.setSortOrder(300);
    action.setWidgetNames(["MathExamplesMenu"]);
};

//    # Issue # metric vs imperial (mm stay mm or units stay units? eg. fonts base 9)
//    # Issue # castAngle failing @startPoint or @distance zero or @endpoint or @distance objlength
//              Some such castings return null vectors for castpoint and subsequently an error for castAngle
//              # ToDo # Isolate cases and file bugreport ?=== offset to poly @startPoint || @endpoint
//        Temporary Workaround: AVOID the use of fitpoints on the reference margins
//    # MAJOR ISSUE Solved# AppCrash on casting Null-splines followed by:
//                    - Select All
//                    - Select Layer Entities: cast layer
//                    - Invert Selection (with base entity(-ies) still selected)
//                    - Selection filter: entities on cast layer
//                    - Selection filter: splines
//                    - draw select including origin
//                    NOT draw select excluding origin
//              Solved with difference in target
//              # ToDo # Debate not catching NULL entry
//    # Issue Solved # Pi/2 was used 3 times in each painter spline fitpoint casting loop
//              Solved with: appropriate math, script global this.var, locals as var and some as const (faster)
//              Exec time: factor x1: literal (1.570796...)
//                         factor x2: const orthoAngle (not Global)
//                         factor x4: var orthoAngle && const orthoAngle (Global) && this.orthoAngle
//                         factor x8-12: Math.PI/2
//    # Issue Solved # For(){...} loops work faster with less calculations in the conditions
//              # Done # Check For() {...} loop conditions
//    # Issue Solved # In debugger mode non-grouped castings are still displayed successively
//               No longer in normal mode
//               Solved with 'update()' Is slow: Solved for last or one
//    # Issue Solved # Pushing messages to command history is slow (80ms/entry, casting fitpoints: 10/ms)
//               Solved with beVerbose flag. Persistent set on dialog load
//    # ToDo # Solution for Painter splines data sets.(Partially prepared UI & code)
//             Investigate splines in Blocks:
//                 "Splines" -> sequentially local fitpoints
//                 "Dotsplines" -> sequentially global fitpoints
//                     Dots sorted in X -> global fitpoints
//    # ToDo # Insertable painters (eg. Knots) @(aaa%,bbb%,ccc%,...)(Partially prepared UI & code)
//    # ToDo # Optionally delete base entity(-ies) (UI prepared)
//    # Todo # Check user numerical entries ... mainScaleX/Y != -n; 0; huge
//             Done: Can't start entries with "-" but can enter expression that gives negative result
//             Done: Made absolute and limited to 0.01 & 99.99 and written back to Widget
//             Done: limited casting main painter to 10000 / entity 
//                   (On line in test f0.01 14s 21139 splines /3= about 7000 painters
//    # Todo # With fitN rather fit N or N+1 instead of cast until end ???
//    # ToDo Done # Beside dynamically scale open forms optional Align @start @end @center
