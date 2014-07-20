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
 * \brief Draw cross at the centre of an arc, circle or ellipse.
 * \ingroup ecma_misc_draw
 */
function Cross(guiAction) {
    EAction.call(this, guiAction);

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
    var trEntity = qsTr("Select arc, circle, ellipse or elliptical arc");
    this.setCommandPrompt(trEntity);
    this.setLeftMouseTip(trEntity);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

Cross.prototype.pickEntity = function(event, preview) {
    //var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    var shape = entity.getClosestShape(pos);
    if (!isArcShape(shape) &&
            !isCircleShape(shape) &&
            !isEllipseShape(shape) &&
            !isEllipseArcShape(shape)) {

        if (!preview) {
            EAction.warnNotArcCircleEllipse();
        }
        return;
    }
    if (!preview) {
        this.drawCross(shape);
    }
};

Cross.prototype.drawCross = function(shape) {
    var lengthX, lengthY;

    var ellipseangle = 0.0;
    var cp = shape.getCenter();
    var ex = objectFromPath("MainWindow::Options::ExtendX");
    var ey = objectFromPath("MainWindow::Options::ExtendY");
    var mode = objectFromPath("MainWindow::Options::Mode");
    var or = objectFromPath("MainWindow::Options::Orientation");
    var orient = or.value;
    if (mode.currentIndex === 0) {      //Extend
        if (isArcShape(shape) || isCircleShape(shape)) {
            lengthX = shape.getRadius() + RMath.eval(ex.text);
            if (ey.text === "") {
                lengthY = lengthX;
            } else {
                lengthY = shape.getRadius() + RMath.eval(ey.text);
            }
            ellipseangle = 0.0;
        } else if (isEllipseShape(shape) || isEllipseArcShape(shape)) {
            lengthX = shape.getMajorRadius() + RMath.eval(ex.text);
            if (ey.text === "") {
                lengthY = shape.getMinorRadius() + RMath.eval(ex.text);
            } else {
                lengthY = shape.getMinorRadius() + RMath.eval(ey.text);
            }
            ellipseangle = shape.getAngle();
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
            if (isEllipseShape(shape) || isEllipseArcShape(shape)) {
                ellipseangle = shape.getAngle();
            } else {
                ellipseangle = 0.0;
            }
    }

    var v = new RVector();
    if (lengthX <= 0.0) {
        lengthX = 0.0;
        var point1 = cp;
        var point2 = cp
    } else {
        v.setPolar(lengthX, RMath.deg2rad(orient + 180) + ellipseangle);
        point1 = cp.operator_add(v);
        v.setPolar(lengthX, RMath.deg2rad(orient) + ellipseangle);
        point2 = cp.operator_add(v);
    }
    if (lengthY <= 0.0) {
        lengthY = 0.0;
        var point3 = cp;
        var point4 = cp;
    } else {
        v.setPolar(lengthY, RMath.deg2rad(orient - 90) + ellipseangle);
        point3 = cp.operator_add(v);
        v.setPolar(lengthY, RMath.deg2rad(orient + 90) + ellipseangle);
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
        this.getDocumentInterface().applyOperation(op);
    }
};
