/**
 * Copyright (c) 2013 by Robert S.. All rights reserved.
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

include("scripts/EAction.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Cross
 * \brief Draw cross at the center of an arc, circle or ellipse.
 * \ingroup ecma_draw_line
 */
function Cross(guiAction) {
    EAction.call(this, guiAction);

    this.shape = undefined;

    this.setUiOptions("Cross.ui");
}

Cross.prototype = new EAction();

Cross.State = {
    ChoosingShape : 0
};

Cross.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(Cross.State.ChoosingShape);
};

Cross.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    this.shape = undefined;
    var trEntity = qsTr("Select arc, circle, ellipse or elliptical arc");
    this.setCommandPrompt(trEntity);
    this.setLeftMouseTip(trEntity);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

Cross.prototype.pickEntity = function(event, preview) {
    var doc = this.getDocument();
    var di = this.getDocumentInterface();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    var shape = entity.getClosestSimpleShape(pos);
    if (!isArcShape(shape) &&
        !isCircleShape(shape) &&
        !isEllipseShape(shape) &&
        !isEllipseArcShape(shape)) {

        if (!preview) {
            EAction.warnNotArcCircleEllipse();
        }
        return;
    }
    else {
        this.shape = shape;
    }

    if (preview) {
        this.updatePreview();
    }
    else {
        this.applyOperation();
    }
};

Cross.prototype.getOperation = function() {
    var lengthX, lengthY;

    var ellipseangle = 0.0;
    var cp = this.shape.getCenter();
    var ex = objectFromPath("MainWindow::Options::ExtendX");
    var ey = objectFromPath("MainWindow::Options::ExtendY");
    var mode = objectFromPath("MainWindow::Options::Modes");
    var or = objectFromPath("MainWindow::Options::Orientation");
    var orient = or.getValue();
    if (mode.currentIndex === 0) {      //Extend
        if (isArcShape(this.shape) || isCircleShape(this.shape)) {
            lengthX = this.shape.getRadius() + RMath.eval(ex.text);
            if (ey.text === "") {
                lengthY = lengthX;
            } else {
                lengthY = this.shape.getRadius() + RMath.eval(ey.text);
            }
            ellipseangle = 0.0;
        } else if (isEllipseShape(this.shape) || isEllipseArcShape(this.shape)) {
            lengthX = this.shape.getMajorRadius() + RMath.eval(ex.text);
            if (ey.text === "") {
                lengthY = this.shape.getMinorRadius() + RMath.eval(ex.text);
            } else {
                lengthY = this.shape.getMinorRadius() + RMath.eval(ey.text);
            }
            ellipseangle = this.shape.getAngle();
        }
    } else if (mode.currentIndex === 1) {       //Length
            // divide length by 2 because cp.operator_add(v) (see below)
            // adds the length to both ends of the line.
            lengthX = RMath.eval(ex.text) / 2;
            if (ey.text === "") {
                lengthY = lengthX;
            } else {
                lengthY = RMath.eval(ey.text) / 2;
            }
            if (isEllipseShape(this.shape) || isEllipseArcShape(this.shape)) {
                ellipseangle = this.shape.getAngle();
            } else {
                ellipseangle = 0.0;
            }
    } else if (mode.currentIndex === 2) {       //Percent
        if (isArcShape(this.shape) || isCircleShape(this.shape)) {
            lengthX = this.shape.getRadius() * RMath.eval(ex.text) / 100;
            if (ey.text === "") {
                lengthY = lengthX;
            } else {
                lengthY = this.shape.getRadius() * RMath.eval(ey.text) / 100;
            }
            ellipseangle = 0.0;
        } else if (isEllipseShape(this.shape) || isEllipseArcShape(this.shape)) {
            lengthX = this.shape.getMajorRadius() * RMath.eval(ex.text) / 100;
            if (ey.text === "") {
                lengthY = this.shape.getMinorRadius() * RMath.eval(ex.text) / 100;
            } else {
                lengthY = this.shape.getMinorRadius() * RMath.eval(ey.text) / 100;
            }
            ellipseangle = this.shape.getAngle();
        }
    }

    var v = new RVector();
    if (lengthX <= 0.0) {
        lengthX = 0.0;
        var point1 = cp;
        var point2 = cp
    } else {
        v.setPolar(lengthX, orient + Math.PI + ellipseangle);
        point1 = cp.operator_add(v);
        v.setPolar(lengthX, orient + ellipseangle);
        point2 = cp.operator_add(v);
    }
    if (lengthY <= 0.0) {
        lengthY = 0.0;
        var point3 = cp;
        var point4 = cp;
    } else {
        v.setPolar(lengthY, orient - Math.PI/2 + ellipseangle);
        point3 = cp.operator_add(v);
        v.setPolar(lengthY, orient + Math.PI/2 + ellipseangle);
        point4 = cp.operator_add(v);
    }

    var op = new RAddObjectsOperation();
    var empty = true;

    // draw horizontal line from point1 to point2
    if (!point1.equalsFuzzy(point2)) {
        var line = new RLineEntity(
                this.getDocument(),
                new RLineData(point1, point2)
                )
        op.addObject(line);
        empty = false;
    }

    // draw vertical line from point3 to point4
    if (!point3.equalsFuzzy(point4)) {
        line = new RLineEntity(
                    this.getDocument(),
                    new RLineData(point3, point4)
                    )
        op.addObject(line);
        empty = false;
    }

    if (!empty) {
        return op;
    }
};
