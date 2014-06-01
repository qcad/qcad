/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("../Line.js");
include("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");

/**
 * \class Line2P
 * \brief Line from two points or sequence of lines.
 * \ingroup ecma_draw_line
 */
function Line2P(guiAction) {
    Line.call(this, guiAction);

    // list of points drawn:
    this.pointList = [];
    // index of point that was drawn last, used for tool undo / redo:
    this.pointListIndex = -1;
    // list of entities drawn:
    this.entityIdList = [];

    this.point1 = undefined;
    this.point2 = undefined;

    this.restrictLength = undefined;
    this.length = undefined;
    this.restrictAngle = undefined;
    this.angle = undefined;

    this.cmd = "";

    this.setUiOptions(["../Line.ui", "Line2P.ui"]);
}

Line2P.prototype = new Line();

Line2P.State = {
    SettingFirstPoint : 0,
    SettingNextPoint : 1
};

Line2P.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(Line2P.State.SettingFirstPoint);
    this.checkButtonStates();
};

Line2P.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        this.pointList = [];
        this.pointListIndex = -1;
        this.entityIdList = [];
        break;

    case Line2P.State.SettingNextPoint:
        var trNextPoint = qsTr("Next point");
        this.setCommandPrompt(trNextPoint);
        this.setLeftMouseTip(trNextPoint);
        this.setRightMouseTip(qsTr("Done"));
        break;
    }

    EAction.showSnapTools();
};

Line2P.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);

    var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("Restrict");
    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");
    w.setDefaultAction(guiAction);

    this.checkButtonStates();
};

Line2P.prototype.escapeEvent = function() {
    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        EAction.prototype.escapeEvent.call(this);
        return;

    case Line2P.State.SettingNextPoint:
        this.setState(Line2P.State.SettingFirstPoint);
        this.checkButtonStates();
        break;
    }
};

Line2P.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        if (!preview) {
            this.point1 = event.getModelPosition();
            this.pointList.splice(0, 0, this.point1);
            this.pointListIndex = 0;
            di.setRelativeZero(this.point1);
            this.setState(Line2P.State.SettingNextPoint);
        }
        break;

    case Line2P.State.SettingNextPoint:
        this.point2 = event.getModelPosition();
        var op = this.getOperation(preview);
        if (preview) {
            di.previewOperation(op);
        }
        else {
            if (!isNull(op)) {
                this.pointListIndex++;

                var doc = this.getDocument();
                var trans = di.applyOperation(op);
                var id = this.getLineEntityId(trans);
                this.pointList.splice(this.pointListIndex, 0, this.point2);
                this.entityIdList.splice(this.pointListIndex-1, 0, id);

                di.setRelativeZero(this.point2);
                this.point1 = this.point2;

                qDebug("this.pointList: ", this.pointList);
                qDebug("this.entityIdList: ", this.entityIdList);
                qDebug("this.pointListIndex: ", this.pointListIndex);
            }
        }
        break;
    }

    if (!preview) {
        this.checkButtonStates();
    }
};

/**
 * If restrict is on then change the co-ordinate to lie on the nearest multiple
 * of the specified angle.
 * If the user has entered an absolute or relative co-ordinate, then that
 * overrides restrict.
 * Calls pickCoordinate(event, false)
 */
 /*
Line2P.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();
    var pos = undefined;

    switch (this.state) {
    case Line2PEx.State.SettingNextPoint:
        if (this.restrictAngle || this.restrictLength) {
            var value = RMath.eval(this.cmd);
            var de = objectFromPath("MainWindow::Options::Degrees");

            // need this to avoid Bug FS#954
            var cartCoordSep = RSettings.getStringValue("Input/CartesianCoordinateSeparator", ',');
            var polCoordSep = RSettings.getStringValue("Input/PolarCoordinateSeparator", '<');

            // coordinates override restrict
            if (this.cmd.contains(cartCoordSep) || this.cmd.contains(polCoordSep)) {
                break;
            } else if (isNumber(value)) {       // if distance entered, use it
                pos = this.restrict(di.getRelativeZero(), event.getModelPosition(), RMath.eval(de.text), true);
            } else {
                pos = this.restrict(di.getRelativeZero(), event.getModelPosition(), RMath.eval(de.text), false);
            }
            if (!isNull(pos) && pos.isValid()) {
                event.setModelPosition(pos);
            }
        }
        break;
    }

    this.pickCoordinate(event, false);
};
*/

Line2P.prototype.getOperation = function(preview) {
    if (!isVector(this.point1) || !isVector(this.point2)) {
        return undefined;
    }

    var e = this.createLineEntity(this.getDocument(), this.point1, this.point2);
    return new RAddObjectOperation(e);
};

Line2P.prototype.slotClose = function() {
    if (this.pointList.length >= 3) {
        this.point2 = this.pointList[0];
        this.getDocumentInterface().applyOperation(this.getOperation(false));
        this.pointList.push(this.point2);
        this.setState(Line2P.State.SettingFirstPoint);
    }
    
    this.checkButtonStates();
};

Line2P.prototype.slotUndo = function() {
    if (this.pointListIndex > 0) {
        var di = this.getDocumentInterface();
        var doc = this.getDocument();

        this.pointListIndex--;
        this.point1 = this.pointList[this.pointListIndex];
        qDebug("undone: back to point: ", this.point1);

        var id = this.entityIdList[this.pointListIndex];
        var entity = doc.queryEntity(id);
        di.applyOperation(new RDeleteObjectOperation(entity));

        di.clearPreview();
        di.previewOperation(this.getOperation(true));

        qDebug("undone: this.pointListIndex: ", this.pointListIndex);
        qDebug("undone: this.pointList: ", this.pointList);
        qDebug("undone: this.entityIdList: ", this.entityIdList);
    }

    this.checkButtonStates();
};

Line2P.prototype.slotRedo = function() {
    if (this.pointListIndex < this.pointList.length-1) {
        var di = this.getDocumentInterface();
        var doc = this.getDocument();

        this.pointListIndex++;
        this.point1 = this.pointList[this.pointListIndex];

        var e = this.createLineEntity(doc, this.pointList[this.pointListIndex-1], this.pointList[this.pointListIndex]);
        var trans = di.applyOperation(new RAddObjectOperation(e));
        var id = this.getLineEntityId(trans);
        this.entityIdList[this.pointListIndex-1] = id;

        di.clearPreview();
        di.previewOperation(this.getOperation(true));

        qDebug("redone: this.pointListIndex: ", this.pointListIndex);
        qDebug("redone: this.pointList: ", this.pointList);
        qDebug("redone: this.entityIdList: ", this.entityIdList);
    }

    this.checkButtonStates();
};

//Line2P.prototype.slotRestrictChanged = function(value) {
//    var di = this.getDocumentInterface();
//    if (value) {
//        var guiAction = RGuiAction.getByScriptFile("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");
//        if (!isNull(guiAction)) {
//            guiAction.slotTrigger();
//        }
//        //var s = new RRestrictAngleLengthExtension();
//        //di.setSnapRestriction(s);
//    }
//    else {
//        di.setSnapRestriction(null);
//    }
//};

Line2P.prototype.slotRestrictAngleChanged = function(value) {
    this.restrictAngle = value;
};

Line2P.prototype.slotAngleChanged = function(value) {
    this.angle = value;
};

Line2P.prototype.slotRestrictLengthChanged = function(value) {
    this.restrictLength = value;
};

Line2P.prototype.slotLengthChanged = function(value) {
    this.length = value;
};

Line2P.prototype.checkButtonStates = function() {
    var w;

    var optionsToolBar = EAction.getOptionsToolBar();

    w = optionsToolBar.findChild("Undo");
    if (this.pointListIndex > 0) {
        w.enabled = true;
    } else {
        w.enabled = false;
    }

    w = optionsToolBar.findChild("Redo");
    if (this.pointListIndex >= 0 && this.pointListIndex < this.entityIdList.length) {
        w.enabled = true;
    } else {
        w.enabled = false;
    }
    
    w = optionsToolBar.findChild("Close");
    if (this.pointList.length < 3) {
        w.enabled = false;
    } else {
        w.enabled = true;
    }
};

Line2P.prototype.getLineEntityId = function(trans) {
    var objIds = trans.getAffectedObjects();
    for (var i=0; i<objIds.length; i++) {
        var objId = objIds[i];
        var obj = this.getDocument().queryObjectDirect(objId);
        if (isLineEntity(obj)) {
            return obj.getId();
        }
    }
};

/**
 * Allows commands to be entered in command line
 * Using the 'startsWith' function allows the user to enter only as many characters
 * as needed to distinguish between commands
 * In this case only the first character is needed. (But entering 'c', 'cl', 'clo', 'clos'
 * or 'close' would all invoke the close command. Similarly with undo and redo)
 */
Line2P.prototype.commandEvent = function(event) {
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
Line2P.prototype.restrict = function(relativeZero, pos, snapang, isDistance) {
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
