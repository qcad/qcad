/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
 * 
 * Various changes added 2013 by Robert S.
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

include("scripts/Draw/Line/Line.js");

/**
 * \class Line2PEx
 * \brief Line from two points or sequence of lines.
 * \ingroup ecma_draw_line
 */
function Line2PEx(guiAction) {
    Line.call(this, guiAction);

    this.pointList = new Array();
    this.redoList = new Array();
    this.undoList = new Array();

    this.point1 = undefined;
    this.point2 = undefined;

    this.cmd = "";
    this.restrict = undefined;
    this.display = undefined;
    this.rzpos = undefined;

    this.setUiOptions("Line2PEx.ui");
};

Line2PEx.prototype = new Line();

Line2PEx.State = {
    SettingFirstPoint : 0,
    SettingNextPoint : 1
};

Line2PEx.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    var ob = objectFromPath("MainWindow::Options::Restrict");
    this.restrict = ob.checked;
    ob = objectFromPath("MainWindow::Options::Display");
    this.display = ob.checked;

    this.setState(Line2PEx.State.SettingFirstPoint);
    this.checkButtonStates();
};

Line2PEx.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();
    switch (this.state) {
    case Line2PEx.State.SettingFirstPoint:
        this.pointList = [];
        this.redoList = [];
        this.undoList = [];
        break;
    }
    this.setPrompt();
    EAction.showSnapTools();
};

/**
 * This changes the command line prompt each time the user chooses a point or
 * uses close, undo or redo.
 * The prompt indicates which options are available each time.
 */
Line2PEx.prototype.setPrompt = function() {
    var promptStr, cStr, uStr, rStr;

    switch (this.state) {
    case Line2PEx.State.SettingFirstPoint:
        promptStr = qsTr("First point");
        this.setCommandPrompt(promptStr);
        this.setLeftMouseTip(promptStr);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Line2PEx.State.SettingNextPoint:
        promptStr = qsTr("Next point");
        cStr = (this.pointList.length >= 3) ? qsTr("Close") + "/" : "";
        uStr = (this.pointList.length >= 2) ? qsTr("Undo") : "";
        rStr = (this.redoList.length >= 1) ? "/" + qsTr("Redo") : "";
        if (uStr === "" && rStr !== "") {
            rStr = qsTr("Redo");
        }
        if ((cStr !== "") || (uStr !== "") || (rStr !== "")) {
            promptStr = qsTr("Next point or ") + "[" + cStr + uStr + rStr + "]";
        } else {
            promptStr = qsTr("Next point");
        }
        this.setCommandPrompt(promptStr);
        this.setLeftMouseTip(qsTr("Next point"));
        this.setRightMouseTip(qsTr("Done"));
        break;
    }
};


Line2PEx.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);

    var ob = objectFromPath("MainWindow::Options");
    ob.enabled = true;

    // restore relative zero position when returning from another command
    var di = this.getDocumentInterface();
    if (!isNull(this.rzpos) && this.rzpos.isValid()) {
        di.setRelativeZero(this.rzpos);
    }
    this.checkButtonStates();
};

Line2PEx.prototype.hideUiOptions = function(saveSettings) {
    // store relative zero position
    var di = this.getDocumentInterface();
    this.rzpos = di.getRelativeZero();

    var ob = objectFromPath("MainWindow::Options");
    ob.enabled = true;

    Draw.prototype.hideUiOptions.call(this, saveSettings);
};

Line2PEx.prototype.escapeEvent = function() {
    switch (this.state) {
    case Line2PEx.State.SettingFirstPoint:
        EAction.prototype.escapeEvent.call(this);
        return;

    case Line2PEx.State.SettingNextPoint:
        this.setState(Line2PEx.State.SettingFirstPoint);
        this.checkButtonStates();
        break;
    }
};

Line2PEx.prototype.keyPressEvent = function(event) {
    var di = this.getDocumentInterface();

    if ((event.key() === Qt.Key_Enter.valueOf()) || (event.key() === Qt.Key_Return.valueOf())) {
        if (this.state === Line2PEx.State.SettingFirstPoint) {
            this.point1 = di.getLastPosition();
            di.setRelativeZero(this.point1);
            this.setState(Line2PEx.State.SettingNextPoint);
            di.clearPreview();
            di.previewOperation(this.getOperation(true));
        }
    } else {
        EAction.prototype.keyPressEvent(event);
    }
};

Line2PEx.prototype.keyReleaseEvent = function(event) {
    var di = this.getDocumentInterface();

    if ((event.key() === Qt.Key_Z.valueOf()) && (event.modifiers().valueOf() === Qt.AltModifier.valueOf())) {
        var ob = objectFromPath("MainWindow::Options");
        ob.enabled = !ob.enabled;

        // need to save relative zero position
        // so it can be restored when returning from another command
        if (ob.enabled === false) {
            this.rzpos = di.getRelativeZero();
        } else {
            di.setRelativeZero(this.rzpos);
        }
    } else {
        EAction.prototype.keyReleaseEvent(event);
    }
};

/**
 * If restrict is on then change the co-ordinate to lie on the nearest multiple
 * of the specified angle.
 * If the user has entered an absolute or relative co-ordinate, then that
 * overrides restrict.
 * Calls pickCoordinate(event, false)
 */
Line2PEx.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();
    var pos;

    switch (this.state) {
    case Line2PEx.State.SettingNextPoint:
        if (this.restrict === true) {
            var value = RMath.eval(this.cmd);
            var de = objectFromPath("MainWindow::Options::Degrees");

            // need this to avoid Bug FS#954
            var cartCoordSep = RSettings.getStringValue("Input/CartesianCoordinateSeparator", ',');
            var polCoordSep = RSettings.getStringValue("Input/PolarCoordinateSeparator", '<');

            // coordinates override restrict
            if (this.cmd.contains(cartCoordSep) || this.cmd.contains(polCoordSep)) {
                break;
            } else if (isNumber(value)) {       // if distance entered, use it
                pos = this.restrictToAngle(di.getRelativeZero(), event.getModelPosition(), RMath.eval(de.text), true);
            } else {
                pos = this.restrictToAngle(di.getRelativeZero(), event.getModelPosition(), RMath.eval(de.text), false);
            }
            if (!isNull(pos) && pos.isValid()) {
                event.setModelPosition(pos);
            }
        }
        break;
    }

    this.pickCoordinate(event, false);
};

/**
 * If restrict is on then change the co-ordinate to lie on the nearest multiple
 * of the specified angle.
 * Calls pickCoordinate(event, true)
 */
Line2PEx.prototype.coordinateEventPreview = function(event) {
    switch (this.state) {
    case Line2PEx.State.SettingNextPoint:
        if (this.restrict === true) {
            var di = this.getDocumentInterface();
            var de = objectFromPath("MainWindow::Options::Degrees");

            // set 'isDistance' to false for preview
            var pos = this.restrictToAngle(di.getRelativeZero(), event.getModelPosition(), RMath.eval(de.text), false);
            if (!isNull(pos) && pos.isValid()) {
                event.setModelPosition(pos);
            }

            // display angle
            if (this.display === true) {
                this.displayAngle(di.getRelativeZero(), pos, di.getLastKnownViewWithFocus());
            }
        }
        break;
    }

    this.pickCoordinate(event, true);
};

/**
 * Display the angle between relativeZero and pos.
 */
Line2PEx.prototype.displayAngle = function(relativeZero, pos, view) {
    var graphicsview = view.getRGraphicsView();

    var ang = relativeZero.getAngleTo(pos);
    ang = RMath.rad2deg(ang);
    ang = sprintf("%.3f", ang);
    graphicsview.clearTextLabels();
    var dx = graphicsview.mapDistanceFromView(10);
    var dy = graphicsview.mapDistanceFromView(30);
    graphicsview.addTextLabel(new RTextLabel(new RVector(pos.x + dx, pos.y + dy), ang));
};

/**
 * restrictToAngle calculates the co-ordinate which lies on the nearest multiple
 * of the specified angle.
 *
 * Params
 *  relativeZero
 *  pos             - the co-ordinate to change
 *  snapang         - the angle multiplier in degrees
 *  isDistance      - boolean indicating if user entered a distance
 *                    if true then use that distance (dist)
 *                    if false then adjust the distance to the long side of a right-
 *                    angled triangle between pos, relativeZero and nearest angle (pdist)
 */
Line2PEx.prototype.restrictToAngle = function(relativeZero, pos, snapang, isDistance) {
    if (!isValidVector(relativeZero)) {           // if this is the first action
        relativeZero = new RVector(0.0, 0.0);     // of a new drawing relativezero
    }                                             // is not valid
    if (relativeZero.equalsFuzzy(pos)) {
        // cursor at same position as relative zero:
        return RVector.invalid;
    }
    var ang = relativeZero.getAngleTo(pos);
    var dist = relativeZero.getDistanceTo(pos);
    var pdist = dist;
    if (snapang < 0.0) {
        snapang = Math.abs(snapang);
    }

    if (snapang > 0.0) {
        ang = RMath.rad2deg(ang);
        var mang = Math.round(ang / snapang) * snapang;
        pdist = dist * Math.cos(RMath.deg2rad(Math.abs(ang - mang)));
        ang = mang;
        if (ang >= 360.0) ang = 0.0;
        ang = RMath.deg2rad(ang);
    }
    var v = new RVector();
    if (isDistance) {
        v.setPolar(dist, ang);
    } else {
        v.setPolar(pdist, ang);
    }
    pos = relativeZero.operator_add(v);
    return pos;
};

Line2PEx.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Line2PEx.State.SettingFirstPoint:
        if (!preview) {
            this.point1 = event.getModelPosition();
            this.pointList.push(this.point1);
            di.setRelativeZero(this.point1);
            this.setState(Line2PEx.State.SettingNextPoint);
        }
        break;

    case Line2PEx.State.SettingNextPoint:
        this.point2 = event.getModelPosition();
        if (this.point1.equalsFuzzy(this.point2)) {
            if (!preview) {
                this.checkButtonStates();
            }
            return;
        }
        var op = this.getOperation(preview);
        if (preview) {
            di.previewOperation(op);
            //this.updatePreview();
        }
        else {
            if (!isNull(op)) {
                var trans = di.applyOperation(op);
                this.undoList.push(trans);
                this.pointList.push(this.point2);
                di.setRelativeZero(this.point2);
                this.point1 = this.point2;
            }
        }        
        break;
    }

    if (!preview) {
        this.checkButtonStates();
    }
};

Line2PEx.prototype.getOperation = function(preview) {
    var line = new RLineEntity(
        this.getDocument(),
        new RLineData(this.point1, this.point2)
    );
    return new RAddObjectOperation(line);
};

Line2PEx.prototype.slotClose = function() {
    if (this.pointList.length >= 3) {
        this.point2 = this.pointList[0];
        this.getDocumentInterface().setRelativeZero(this.point2);
        this.getDocumentInterface().applyOperation(this.getOperation(false));
        this.pointList.push(this.point2);
        this.setState(Line2PEx.State.SettingFirstPoint);
    }
    
    this.checkButtonStates();
};

Line2PEx.prototype.slotUndo = function() {
    if (this.pointList.length >= 2) {
        var di = this.getDocumentInterface();
        var doc = di.getDocument();

        this.redoList.push(this.pointList.pop());
        // if, for example, a circle is drawn while drawing lines, on return, system undo
        // deletes the circle, not last line segment
        //di.undo();
        var trans = this.undoList.pop();
        trans.undo(doc);
        di.regenerateViews(true);
        this.point1 = this.pointList[this.pointList.length - 1];
        di.setRelativeZero(this.point1);
        di.clearPreview();
        di.previewOperation(this.getOperation(true));
    }

    this.checkButtonStates();
};

/**
 * pops values from redoList until redoList is empty
 * this is different from system redo as redoList is not reset when user
 * enters a co-ordinate
 */
Line2PEx.prototype.slotRedo = function() {
    if (this.redoList.length >= 1) {
        var di = this.getDocumentInterface();
        var doc = di.getDocument();

        this.pointList.push(this.redoList.pop());
        this.point2 = this.pointList[this.pointList.length - 1];
        var trans = di.applyOperation(this.getOperation(false));
        this.undoList.push(trans);
        di.setRelativeZero(this.point2);
        this.point1 = this.point2;
        this.simulateMouseMoveEvent();
        di.clearPreview();
        di.previewOperation(this.getOperation(true));
    }

    this.checkButtonStates();
};

Line2PEx.prototype.slotRestrictChanged = function(value) {
    var de, dl, di;

    this.restrict = value;
    de = objectFromPath("MainWindow::Options::Degrees");
    dl = objectFromPath("MainWindow::Options::dlabel");
    di = objectFromPath("MainWindow::Options::Display");

    if (this.restrict === true) {
        de.enabled = true;
        dl.enabled = true;
        di.enabled = true;
    } else {
        de.enabled = false;
        dl.enabled = false;
        di.enabled = false;
    }
};

Line2PEx.prototype.slotDisplayChanged = function(value) {
    this.display = value;
};

Line2PEx.prototype.checkButtonStates = function() {
    var w;

    w = objectFromPath("MainWindow::Options::Close");
    w.enabled = (this.pointList.length >= 3) ? true : false;

    w = objectFromPath("MainWindow::Options::Undo");
    w.enabled = (this.pointList.length >= 2) ? true : false;

    w = objectFromPath("MainWindow::Options::Redo");
    w.enabled = (this.redoList.length >= 1) ? true : false;


    this.setPrompt();
};

/**
 * Allows commands to be entered in command line
 * Using the 'startsWith' function allows the user to enter only as many characters
 * as needed to distinguish between commands
 * In this case only the first character is needed. (But entering 'c', 'cl', 'clo', 'clos'
 * or 'close' would all invoke the close command. Similarly with undo and redo)
 */
Line2PEx.prototype.commandEvent = function(event) {
    var str;

    var cmd = event.getCommand();
    cmd = cmd.toLowerCase();
    this.cmd = cmd;

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
    if (cmd === qsTr("t")) {
        var ob = objectFromPath("MainWindow::Options::Restrict");
        ob.checked = !ob.checked
        this.restrict = ob.checked;
        this.slotRestrictChanged(ob.checked);
        event.accept();
        return;
    }
    if (cmd === qsTr("d")) {
        ob = objectFromPath("MainWindow::Options::Display");
        if (ob.enabled === true) {
            ob.checked = !ob.checked;
            this.display = ob.checked;
            this.slotDisplayChanged(ob.checked);
        }
        event.accept();
        return;
    }
};
