/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 *
 * Various changes added 2014 by Robert S.
 *
 * This file is part of the QCAD project.
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

include("scripts/Draw/Polyline/Polyline.js");
include("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");

/**
 * \class DrawFmsLanes
 * \brief Draw polyline, segment by segment.
 * This is also the base class for PolylineAppendNode.
 * \ingroup ecma_draw_polyline
 */
function DrawFmsLanes(guiAction) {
    Polyline.call(this, guiAction);

    this.polylineEntity = undefined;
    this.leftBoundaryEntity = undefined;
    this.rightBoundaryEntity = undefined;
    this.arcSegment = false;
    this.laneWidth = 20; // 20meters
    this.laneWidthCm = this.laneWidth * 100;
    this.radius = 1.0;
    this.prepend = false;
    this.segment = undefined;
    this.redoList = [];
    this.sweep = 0.0;

    this.setUiOptions(DrawFmsLanes.includeBasePath + "/DrawFmsLanes.ui");
}

DrawFmsLanes.prototype = new Polyline();
DrawFmsLanes.includeBasePath = includeBasePath;

DrawFmsLanes.State = {
    SettingFirstVertex : 0,
    SettingNextVertex : 1
};

DrawFmsLanes.prototype.beginEvent = function() {
    Polyline.prototype.beginEvent.call(this);

    this.setState(DrawFmsLanes.State.SettingFirstVertex);
    this.updateButtonStates();
};

DrawFmsLanes.prototype.initState = function(state) {
    Polyline.prototype.initState.call(this, state);

    this.setCrosshairCursor();

    switch (this.state) {
    case DrawFmsLanes.State.SettingFirstVertex:
        // do not move this outside of the case, since inheriting actions
        // might add more states:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trFirstVertex = qsTr("First vertex");
        this.setCommandPrompt(trFirstVertex);
        this.setLeftMouseTip(trFirstVertex);
        this.setRightMouseTip(EAction.trCancel);
        this.segment = undefined;
        this.leftBoundaryEntity = new RPolylineEntity(this.getDocument(), new RPolylineData());
        this.rightBoundaryEntity = new RPolylineEntity(this.getDocument(), new RPolylineData());
        EAction.showSnapTools();
        this.redoList = [];
        break;
    case DrawFmsLanes.State.SettingNextVertex:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trNextVertex = qsTr("Next vertex");
        this.setCommandPrompt(trNextVertex);
        this.setLeftMouseTip(trNextVertex);
        this.setRightMouseTip(EAction.trDone);
        EAction.showSnapTools();
        break;
    }
};

/***
 *
 * @param lineStartPoint - RVector
 * @param lineEndPoint - RVector
 */
DrawFmsLanes.prototype.drawRibsBasedOnLine = function(lineStartPoint, lineEndPoint, isLastVertex) {
    // create left rib based on directionVector to next vertex, multiplied by input laneWidth
    var ribLeft = new RLine(lineStartPoint, lineEndPoint);
    // get leftRib from directionVector rotated 90-deg
    ribLeft.rotate(Math.PI/2, ribLeft.startPoint);
    // get a normalized ribLeft so can multiply it with laneWidth,
    // couldn't see RLine.normalize function, so use RVector to normalize and then scale it
    var ribLeftVec = new RVector(
        ribLeft.endPoint.getX() - ribLeft.startPoint.getX(),
        ribLeft.endPoint.getY() - ribLeft.startPoint.getY());
    var ribLeftVecNorm = ribLeftVec.getNormalized();
    var scaled = ribLeftVecNorm.scale(this.laneWidth);
    var ribLeftFinalEndPoint = new RVector(
        ribLeft.startPoint.getX() + scaled.getX(),
        ribLeft.startPoint.getY() + scaled.getY());

    var ribRight = new RLine(lineStartPoint, lineEndPoint);
    ribRight.rotate(-Math.PI/2, ribRight.startPoint);
    var ribRightVec = new RVector(
        ribRight.endPoint.getX() - ribRight.startPoint.getX(),
        ribRight.endPoint.getY() - ribRight.startPoint.getY());
    var ribRightVecNorm = ribRightVec.getNormalized();
    var ribRightVecScaled = ribRightVecNorm.scale(this.laneWidth);
    var ribRightFinalEndPoint = new RVector(
        ribRight.startPoint.getX() + ribRightVecScaled.getX(),
        ribRight.startPoint.getY() + ribRightVecScaled.getY());

    // todo use this.applyOperation ?
    var rib = new RPolylineEntity(
        this.getDocument(),
        new RPolylineData()
    );
    rib.appendVertex(ribLeftFinalEndPoint);
    rib.appendVertex(lineStartPoint);
    rib.appendVertex(ribRightFinalEndPoint);

    rib.setCustomProperty("QCAD", "distance_left_cm", this.laneWidthCm / 2);
    rib.setCustomProperty("QCAD", "distance_right_cm", this.laneWidthCm / 2);
    var line = new RLine(lineStartPoint, lineEndPoint);
    rib.setCustomProperty("QCAD", "yaw_crad", line.getAngle() * 100);
    rib.setCustomProperty("QCAD", "type", "ribs");
    rib.setCustomProperty("QCAD", "center_point_x", lineStartPoint.getX());
    rib.setCustomProperty("QCAD", "center_point_y", lineStartPoint.getY());


    if (isLastVertex) {
        this.leftBoundaryEntity.appendVertex(ribRightFinalEndPoint);
        this.rightBoundaryEntity.appendVertex(ribLeftFinalEndPoint);

        this.leftBoundaryEntity.appendVertex(this.rightBoundaryEntity.getVertexAt(this.rightBoundaryEntity.countVertices()-1));
        this.rightBoundaryEntity.prependVertex(this.leftBoundaryEntity.getVertexAt(0));

        var line = new RLine(lineEndPoint, lineStartPoint);
        rib.setCustomProperty("QCAD", "yaw_crad", line.getAngle() * 100);
    }
    else {
        this.leftBoundaryEntity.appendVertex(ribLeftFinalEndPoint);
        this.rightBoundaryEntity.appendVertex(ribRightFinalEndPoint);
        var line = new RLine(lineStartPoint, lineEndPoint);
        rib.setCustomProperty("QCAD", "yaw_crad", line.getAngle() * 100);
    }

    var op = new RAddObjectsOperation();
    op.addObject(rib);
    this.getDocumentInterface().applyOperation(op);
    // debugger;

    // Todo:
    //     - check to not add centerPoint if ribs will intersect
    //     - associate centerLine with ribs, so no need to compute it ?
    //     - automatically add polygon based on ribs endpoint ?
}

DrawFmsLanes.prototype.escapeEvent = function() {
    switch (this.state) {
    case DrawFmsLanes.State.SettingFirstVertex:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DrawFmsLanes.State.SettingNextVertex:
        if (!isNull(this.polylineEntity)) {
            // remove polyline with one or zero vertices:
            if (this.polylineEntity.countVertices() <= 1) {
                var op = new RDeleteObjectOperation(this.polylineEntity, false);
                this.applyOperation(op);
            }
            else {
                // add rib to last vertex
                this.drawRibsBasedOnLine(this.segment.endPoint, this.segment.startPoint, true);

                var op = new RAddObjectsOperation();
                var allBoundary = new RPolylineEntity(this.getDocument(), this.leftBoundaryEntity.getData());

                for (var i = this.rightBoundaryEntity.countVertices()-1; i >= 0 ; i--) {
                    allBoundary.appendVertex(this.rightBoundaryEntity.getVertexAt(i));
                }
                allBoundary.normalize(0.001);

                op.addObject(allBoundary);
                // op.addObject(this.rightBoundaryEntity);
                this.getDocumentInterface().applyOperation(op);
            }
        }

        this.setState(DrawFmsLanes.State.SettingFirstVertex);
        this.polylineEntity = undefined;
        this.leftBoundaryEntity = undefined;
        this.rightBoundaryEntity = undefined;
        this.updateButtonStates();
        break;
    }

};

DrawFmsLanes.prototype.keyPressEvent = function(event) {
    var di = this.getDocumentInterface();

    if ((event.key() === Qt.Key_Enter.valueOf()) || (event.key() === Qt.Key_Return.valueOf())) {
        if (this.state === DrawFmsLanes.State.SettingFirstVertex) {
            var view = di.getLastKnownViewWithFocus();
            var pos = di.getLastPosition();
            var e = new RCoordinateEvent(pos, view.getScene(), getRGraphicsView(view));
            this.pickCoordinate(e, false);
        }
    } else {
        EAction.prototype.keyPressEvent(event);
    }
};

DrawFmsLanes.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);

    var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("Restrict");
    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");
    w.setDefaultAction(guiAction);

    this.updateButtonStates();
};

DrawFmsLanes.prototype.pickCoordinate = function(event, preview) {
    var point, op;
    var pointLeft;

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    switch (this.state) {
    // set first vertex, create polyline entity:
    case DrawFmsLanes.State.SettingFirstVertex:
        if (!preview) {
            point = event.getModelPosition();

            var pl = new RPolylineEntity(document, new RPolylineData());

            pl.appendVertex(point);
            op = new RAddObjectOperation(pl, this.getToolTitle());
            this.applyOperation(op);

            di.setRelativeZero(point);
            if (!isNull(this.polylineEntity)) {
                this.setState(DrawFmsLanes.State.SettingNextVertex);
            }
        }
        break;

    // set next vertex:
    case DrawFmsLanes.State.SettingNextVertex:
        point = event.getModelPosition();
        // debugger;

        // number of existing vertices:
        var numberOfVertices;
        if (isNull(this.polylineEntity)) {
            numberOfVertices = 0;
        }
        else {
            numberOfVertices = this.polylineEntity.countVertices();
        }

        if (numberOfVertices>0) {
            var bulge;
            var vertex;
            var ribLeft;
            var ribRight;
            var appendPoint;
            if (this.prepend) {
                appendPoint = this.polylineEntity.getStartPoint();
            }
            else {
                appendPoint = this.polylineEntity.getEndPoint();
            }

            if (this.arcSegment===true) {
                var dir = 0.0;
                if (numberOfVertices>1) {
                    if (this.prepend) {
                        dir = this.polylineEntity.getDirection1() + Math.PI;
                    }
                    else {
                        dir = this.polylineEntity.getDirection2() + Math.PI;
                    }
                }

                this.segment = RArc.createTangential(
                        appendPoint,
                        point,
                        dir,
                        this.radius);

                // handle sweep here
                // change end angle
                // if sweep equals zero then do nothing
                if (this.sweep < 0.0 || this.sweep > 360.0) {
                    // print error message
                    this.sweep = 0.0;
                }
                if (this.sweep !== 0.0) {
                    var curSweep = this.segment.getSweep();
                    if (curSweep !== this.sweep) {
                        var startAngle = RMath.rad2deg(this.segment.getStartAngle());
                        var reversed = this.segment.isReversed();
                        if (reversed) {
                            var endAngle = startAngle - this.sweep;
                            if (endAngle < 0.0) {
                                endAngle = endAngle + 360.0;
                            }
                        } else {
                            endAngle = startAngle + this.sweep;
                            if (endAngle > 360.0) {
                                endAngle = endAngle - 360.0;
                            }
                        }
                        this.segment.setEndAngle(RMath.deg2rad(endAngle));
                    }
                }
                vertex = this.segment.getEndPoint();

                if (this.prepend) {
                    this.segment.reverse();
                }

                bulge = this.segment.getBulge();
                this.center = this.segment.getCenter();
                this.angle = this.segment.getEndAngle();
            }
            else {
                this.segment = new RLine(appendPoint, point);
                var angle = this.segment.getAngle();

                bulge = 0.0;
                vertex = point;

                this.center = undefined;
                this.angle = undefined;
            }

            // append or prepend vertex:
            if (!preview) {
                if (this.prepend) {
                    this.polylineEntity.prependVertex(vertex, bulge);
                }
                else {
                    this.polylineEntity.setBulgeAt(numberOfVertices-1, bulge);
                    this.polylineEntity.appendVertex(vertex, 0.0);

                    this.drawRibsBasedOnLine(this.segment.startPoint, vertex, false);

                }
            }
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                this.applyOperation(op);
                di.setRelativeZero(vertex);
                this.uncheckArcSegment();
            }
        }
        break;
    }

    if (!preview) {
        this.updateButtonStates();
    }
};

DrawFmsLanes.prototype.getOperation = function(preview) {
    if (isNull(this.polylineEntity)) {
        return undefined;
    }

    // for preview, only add current segment:
    if (preview) {
        var entity;
        if (isLineShape(this.segment)) {
            entity = new RLineEntity(
                    this.getDocument(),
                    new RLineData(this.segment)
            );
        }
        else if (isArcShape(this.segment)) {
            entity = new RArcEntity(
                    this.getDocument(),
                    new RArcData(this.segment)
            );
        }
        if (!isEntity(entity)) {
            return undefined;
        }
        entity.copyAttributesFrom(getPtr(this.polylineEntity));
        return new RAddObjectOperation(entity, false);
    }
    else {
        return new RAddObjectOperation(this.polylineEntity, this.getToolTitle(), true, false);
    }
};

/**
 * Updates the polyline in storage and makes sure that this.polylineEntity
 * points to new new clone of the original entity.
 */
DrawFmsLanes.prototype.applyOperation = function(op) {
    this.polylineEntity = undefined;
    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var transaction = di.applyOperation(op);

    // find out ID of polyline, that was added to the document:
    var ids = transaction.getAffectedObjects();
    for (var i=0; i<ids.length; ++i) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isPolylineEntity(entity)) {
            this.polylineEntity = entity;
            break;
        }
    }
};

/**
 * Called when user clicks the 'Close' button to close the polyline.
 */
DrawFmsLanes.prototype.slotClose = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    if (this.polylineEntity.countVertices() >= 3) {
        var di = this.getDocumentInterface();
        di.setRelativeZero(this.polylineEntity.getVertexAt(0));
        this.polylineEntity.setClosed(true);
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
        }
        this.setState(DrawFmsLanes.State.SettingFirstVertex);
        this.polylineEntity = undefined;
    }

    this.updateButtonStates();
};

/**
 * Called when user clicks the 'Undo' button to remove the last added vertex.
 */
DrawFmsLanes.prototype.slotUndo = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    if (this.polylineEntity.countVertices() >= 2) {
        var di = this.getDocumentInterface();
        var bulge = this.polylineEntity.getBulgeAt(this.polylineEntity.countVertices() - 1);
        var vertex = this.polylineEntity.getVertexAt(this.polylineEntity.countVertices() - 1);
        this.polylineEntity.removeLastVertex();
        di.setRelativeZero(this.polylineEntity.getVertexAt(this.polylineEntity.countVertices() - 1));
        di.clearPreview();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
            // add last vertex and bulge to redoList
            this.redoList.push(bulge);
            this.redoList.push(vertex);
        }
        this.simulateMouseMoveEvent();
    }

    this.updateButtonStates();
};

/**
 * Called when user clicks the 'Redo' button to redo the last vertex.
 */
DrawFmsLanes.prototype.slotRedo = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    if (this.redoList.length >= 2) {
        var di = this.getDocumentInterface();
        // redo last vertex and bulge
        var vertex = this.redoList.pop();
        var bulge = this.redoList.pop();
        this.polylineEntity.appendVertex(vertex, bulge);
        di.clearPreview();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
        }
        di.setRelativeZero(vertex);
        this.simulateMouseMoveEvent();
    }

    this.updateButtonStates();
};


/**
 * Called when user toggles 'Arc segment' check box to indicate if the next
 * segment is a line or an arc segment.
 */
DrawFmsLanes.prototype.slotArcSegmentChanged = function(value) {
    this.arcSegment = value;
};

/**
 * Called when user enters a radius for the next arc segment.
 */
DrawFmsLanes.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
};

/**
 * Called when user enters a sweep for the next arc segment.
 */
DrawFmsLanes.prototype.slotSweepChanged = function(value) {
    this.sweep = value;
};

/**
 * Called internally to automatically uncheck the 'Arc segment' check box.
 */
DrawFmsLanes.prototype.uncheckArcSegment = function() {
    var w = objectFromPath("MainWindow::Options::ArcSegment");
    w.checked = false;
};


/**
 * Updates the state (enabled / disabled) of the undo and the close buttons
 * depending on the current progress.
 */
DrawFmsLanes.prototype.updateButtonStates = function() {
    var w;

    if (this.state === DrawFmsLanes.State.SettingFirstVertex) {
        this.uncheckArcSegment();
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    w = optionsToolBar.findChild("Close");
    if (!isNull(this.polylineEntity)) {
        w.enabled = (this.polylineEntity.countVertices() >= 3) ? true : false;
    }
    else {
        w.enabled = false;
    }

    w = optionsToolBar.findChild("Undo");
    if (!isNull(this.polylineEntity)) {
        w.enabled = (this.polylineEntity.countVertices() >= 2) ? true : false;
    }
    else {
        w.enabled = false;
    }

    w = optionsToolBar.findChild("Redo");
    w.enabled = (this.redoList.length >= 2) ? true : false;
};

DrawFmsLanes.prototype.getAuxPreview = function() {
    var ret = [];

    if (this.state === DrawFmsLanes.State.SettingNextVertex) {
        if (!isNull(this.center) && !isNull(this.angle)) {
            var v = RVector.createPolar(this.radius, this.angle);
            ret.push(new RLine(this.center, this.center.operator_add(v)));
        }
    }

    return ret;
};

/**
 * Allows commands to be entered in command line
 * Using the 'startsWith' function allows the user to enter only as many characters
 * as needed to distinguish between commands
 * In this case only the first character is needed. (But entering 'c', 'cl', 'clo', 'clos'
 * or 'close' would all invoke the close command. Similarly with undo and redo)
 */
DrawFmsLanes.prototype.commandEvent = function(event) {
    var str;

    var cmd = event.getCommand();
    cmd = cmd.toLowerCase();

    str = qsTr("close");
    if (str.startsWith(cmd)) {
        this.slotClose();
        event.accept();
        return;
    }
    str = qsTr("undo");
    if (str.startsWith(cmd)) {
        this.slotUndo();
        event.accept();
        return;
    }
    str = qsTr("redo");
    if (str.startsWith(cmd)) {
        this.slotRedo();
        event.accept();
        return;
    }
    str = qsTr("arc");
    if (str.startsWith(cmd)) {
        var ob = objectFromPath("MainWindow::Options::ArcSegment");
        ob.checked = !ob.checked
        this.slotArcSegmentChanged(ob.checked);
        event.accept();
        return;
    }
};
