/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
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

include("scripts/Draw/Spline/Spline.js");

/**
 * \class SplineControlPoints
 * \brief Spline from control points and degree.
 * \ingroup ecma_draw_spline
 */
function SplineControlPoints(guiAction) {
    Spline.call(this, guiAction);

    this.spline = undefined;
    this.degree = 3;
    this.closed = false;

    this.setUiOptions("SplineControlPoints.ui");
}

SplineControlPoints.prototype = new Spline();

SplineControlPoints.State = {
    SettingFirstPoint : 0,
    SettingNextPoint : 1
};

SplineControlPoints.prototype.beginEvent = function() {
    Spline.prototype.beginEvent.call(this);

    this.setState(SplineControlPoints.State.SettingFirstPoint);
    this.updateButtonStates();
};

SplineControlPoints.prototype.setState = function(state) {
    Spline.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case SplineControlPoints.State.SettingFirstPoint:
        var trFirstPoint = qsTr("First control point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        this.spline = new RSpline();
        this.spline.setDegree(this.degree);
        break;

    case SplineControlPoints.State.SettingNextPoint:
        var trNextPoint = qsTr("Next control point");
        this.setCommandPrompt(trNextPoint);
        this.setLeftMouseTip(trNextPoint);
        if (this.spline.isValid()) {
            this.setRightMouseTip(EAction.trDone);
        }
        else {
            this.setRightMouseTip(EAction.trCancel);
        }
        break;
    }

    EAction.showSnapTools();
};

SplineControlPoints.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);
    this.updateButtonStates();
};

SplineControlPoints.prototype.escapeEvent = function() {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case SplineControlPoints.State.SettingFirstPoint:
        EAction.prototype.escapeEvent.call(this);
        break;

    case SplineControlPoints.State.SettingNextPoint:
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
        }
        this.setState(SplineControlPoints.State.SettingFirstPoint);
        this.updateButtonStates();
        break;
    }
};

SplineControlPoints.prototype.pickCoordinate = function(event, preview) {
    var point;
    
    var di = this.getDocumentInterface();

    switch (this.state) {
    case SplineControlPoints.State.SettingFirstPoint:
        if (!preview) {
            point = event.getModelPosition();
            this.spline.appendControlPoint(point);
            di.setRelativeZero(point);
            this.setState(SplineControlPoints.State.SettingNextPoint);
        }
        break;

    case SplineControlPoints.State.SettingNextPoint:
        point = event.getModelPosition();
        this.spline.appendControlPoint(point);
        if (preview) {
            this.updatePreview();
            //this.spline.removeLastControlPoint(false);
            this.spline.removeLastControlPoint();
        }
        else {
            di.setRelativeZero(point);
            this.setState(SplineControlPoints.State.SettingNextPoint);
        }
        break;
    }

    if (!preview) {
        this.updateButtonStates();
    }
};

SplineControlPoints.prototype.getOperation = function(preview) {
    if (isNull(this.spline)) {
        return undefined;
    }

    var spline = this.spline.clone();

    spline.setPeriodic(this.closed);
    //if (this.closed) {
        //spline.close();
    //}

    var e = new RSplineEntity(
        this.getDocument(),
        new RSplineData(spline)
    );

    if (!e.isValid()) {
        e.destroy();
        return undefined;
    }

    /*
    // create bezier segments instead of NURBS:
    var op = new RAddObjectsOperation();
    var beziers = spline.getBezierSegments();
    for (var i=0; i<beziers.length; i++) {
        var e = new RSplineEntity(
            this.getDocument(),
            new RSplineData(beziers[i])
        );
        op.addObject(e);
    }
    return op;
    */

    return new RAddObjectOperation(e, this.getToolTitle());
};

SplineControlPoints.prototype.getAuxPreview = function() {
    var ret = [];

    if (isNull(this.spline)) {
        return ret;
    }

    var controlPoints = this.spline.getControlPoints();

    for (var i=0; i<controlPoints.length; ++i) {
        var v1 = controlPoints[i];
        var v2 = controlPoints[(i+1)%controlPoints.length];

        if (i+1 < controlPoints.length || this.closed) {
            ret.push(new RLine(v1, v2));
        }
    }

    return ret;
};

SplineControlPoints.prototype.slotClosedChanged = function(value) {
    this.closed = value;
    //if (!isNull(this.spline)) {
    //    this.spline.setClosed(this.closed);
    //}

    this.updatePreview(true);
};

SplineControlPoints.prototype.slotDegreeChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var degreeCombo = optionsToolBar.findChild("Degree");
    this.degree = parseInt(degreeCombo.currentText, 10);
    if (!isNull(this.spline)) {
        this.spline.setDegree(this.degree);
    }

    this.updatePreview(true);
};

SplineControlPoints.prototype.slotUndo = function() {
    if (this.spline.countControlPoints() >= 2) {
        this.spline.removeLastControlPoint();
        //this.getDocumentInterface().undo();
        //this.point1 = this.pointList[this.pointList.length - 1];
        //this.getDocumentInterface().clearPreview();
        //this.getDocumentInterface().previewOperation(this.getOperation(false));
    }

    this.updateButtonStates();
    this.updatePreview(true);
};

SplineControlPoints.prototype.updateButtonStates = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("Undo");
    if (!isNull(this.spline) && isFunction(this.spline.countControlPoints) && this.spline.countControlPoints() > 1) {
        w.enabled = true;
    } else {
        w.enabled = false;
    }
    
    /*
    var w = optionsToolBar.findChild("Close");
    if (isNull(this.spline) || this.spline.countControlPoints() < 3) {
        w.enabled = false;
    } else {
        w.enabled = true;
    }
    */
};

