/**
 * Copyright (c) 2014-2015 by Robert S. All rights reserved.
 *
 * 2018 A. Mustun: correct use of segment (region cut off from circle)
 * and sector (portion of circle enclosed by two radii and an arc).
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

include("scripts/Information/Information.js");

/**
 * \class InfoArcCircleArea
 * \ingroup ecma_information
 * \brief Measure area of arc, elliptical arc, circle or ellipse.
 */
function InfoArcCircleArea(guiAction) {
    Information.call(this, guiAction);
    this.pi = Math.PI;
    this.shape = undefined;
    this.radius1 = undefined;       // major radius for ellipse
    this.radius2 = undefined;       // minor radius for ellipse
    this.segmentMode = true;
    this.addEntity = true;
    this.addChord = true;
    this.addLength = true;
    this.label1 = "";
    this.label2 = "";
    this.label3 = "";

    this.setUiOptions(["../Information.ui", "InfoArcCircleArea.ui"]);
}

InfoArcCircleArea.prototype = new Information();

InfoArcCircleArea.State = {
    SelectingShape : 0
};

InfoArcCircleArea.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.slotAddToDrawingChanged(this.addToDrawing);
    this.setState(InfoArcCircleArea.State.SelectingShape);
};

//InfoArcCircleArea.prototype.escapeEvent = function() {
//    EAction.prototype.escapeEvent.call(this);
//};

InfoArcCircleArea.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    di.setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var trSelectEntity = qsTr("Choose arc, circle, ellipse or elliptical arc");
    this.setCommandPrompt(trSelectEntity);
    this.setLeftMouseTip(trSelectEntity);
    this.setRightMouseTip(EAction.trDone);

    EAction.showSnapTools();
};

InfoArcCircleArea.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    this.shape = entity.getClosestShape(pos);
    if (!isArcShape(this.shape) &&
        !isCircleShape(this.shape) &&
        !isEllipseShape(this.shape) &&
        !isEllipseArcShape(this.shape)) {
        if (!preview) {
            EAction.warnNotArcCircleEllipse();
        }
        return;
    }
    if (isArcShape(this.shape) || isCircleShape(this.shape)) {
        this.radius1 = this.shape.getRadius();
        this.radius2 = this.radius1;
    } else {        // Ellipse or Elliptical Arc
        this.radius1 = this.shape.getMajorRadius();
        this.radius2 = this.shape.getMinorRadius();
    }

    if (!preview) {
        //this.updatePreview();
        this.calculate();
    } else {
        this.updatePreview();
    }
};

InfoArcCircleArea.prototype.getOperation = function(preview) {
    var v = undefined;

    var di = this.getDocumentInterface();
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    if (this.addEntity) {
        var entClone = this.shape.clone();
        this.addShape(op, entClone, preview);
    }

    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();

    if (isArcShape(this.shape) || isEllipseArcShape(this.shape)) {
        if (this.segmentMode) {
            if (this.addChord) {
                var p1 = this.shape.getStartPoint();
                var p2 = this.shape.getEndPoint();
                var chord = new RLine(p1, p2);
                this.addShape(op, chord, preview);
            }
        } else {
            if (this.addChord) {
                p1 = this.shape.getStartPoint();
                p2 = this.shape.getEndPoint();
                var cen = this.shape.getCenter();
                var lin1 = new RLine(p1, cen);
                var lin2 = new RLine(p2, cen);
                this.addShape(op, lin1, preview);
                this.addShape(op, lin2, preview);
            }
        }
    }

    var label = this.getInfo(false);
    view.clearTextLabels();
    if (isCircleShape(this.shape) || (isEllipseShape(this.shape) && !isEllipseArcShape(this.shape))) {
        var c = this.shape.getCenter();
    } else {
        c = this.shape.getEndPoint();
    }

    if (c.isValid()) {
        if (!preview) {
            if (this.label3 !== "") {
                this.addTextLabel(op, view, c, this.label3, preview);
                v = new RVector(0, this.textHeight * 1.4);
                c = c.operator_add(v);
            }
            if (this.label2 !== "") {
                this.addTextLabel(op, view, c, this.label2, preview);
                v = new RVector(0, this.textHeight * 1.4);
                c = c.operator_add(v);
            }
        }
        if (this.label1 !== "") {
            this.addTextLabel(op, view, c, this.label1, preview);
        }
    }

    return op;
};

// Return area of circle or ellipse
InfoArcCircleArea.prototype.getCircleEllipseArea = function() {
    return (this.pi * this.radius1 * this.radius2);
};

// Return area of arc sector
InfoArcCircleArea.prototype.getSectorArea = function() {
    if (isArcShape(this.shape) || isCircleShape(this.shape)) {
        return this.shape.getArea();
    } else if (isEllipseArcShape(this.shape)) {
        return ((this.shape.getAngleLength(false) * this.radius1 * this.radius2) / 2);
    } else {    // Ellipse shape
        return (this.pi * this.radius1 * this.radius2);
    }
};


// getSegmentArea returns the area of the segment
// i.e. the area bounded by arc and chord
InfoArcCircleArea.prototype.getSegmentArea = function() {
    var segmentArea = 0.0;
    var angleLength = this.shape.getAngleLength(false);
    var sweep = RMath.rad2deg(this.shape.getSweep());
    if (sweep < 180) {
        segmentArea = (this.radius1 * this.radius2 * (angleLength - Math.sin(angleLength))) / 2.0;
    } else if (sweep === 180) {
        segmentArea = 0.5 * this.getCircleEllipseArea();
    } else {
        var remainAngle = RMath.deg2rad(360 - sweep);
        var remainSliceArea = (this.radius1 * this.radius2 * remainAngle) / 2.0;
        var remainSegmentArea = (this.radius1 * this.radius2 * (remainAngle - Math.sin(remainAngle))) / 2.0;
        segmentArea = this.getSectorArea() + (remainSliceArea - remainSectorArea);
    }

    return segmentArea;
}

InfoArcCircleArea.prototype.getCircumference = function() {
    var circ = 0.0;
    if (isCircleShape(this.shape)) {
        circ = this.shape.getCircumference();
    } else {
        circ = this.shape.getLength();
    }

    return circ;
};

// centre of gravity for the segment
InfoArcCircleArea.prototype.getCenter = function() {
};

InfoArcCircleArea.prototype.calculate = function() {
    var info = "";
    var di = this.getDocumentInterface();

    info = this.getInfo(true);
    if (this.addToDrawing) {
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
        }
    }

    di.clearPreview();
    this.updatePreview();
    di.regenerateViews();
    di.repaintViews();

    EAction.getMainWindow().handleUserInfo(info);
};

/**
  * Called when the user changes mode
  */
InfoArcCircleArea.prototype.slotModeChanged = function(button) {
    if (button.objectName === "Segment") {
        this.segmentMode = true;
    }
    else {
        this.segmentMode = false;
    }
};

/**
  * called when user clicks Entity button
  */
InfoArcCircleArea.prototype.slotEntityChanged = function(value) {
    this.addEntity = value;
}

/**
  * called when user clicks Chord button
  */
InfoArcCircleArea.prototype.slotChordChanged = function(value) {
    this.addChord = value;
}

/**
  * called when user clicks Length button
  */
InfoArcCircleArea.prototype.slotLengthChanged = function(value) {
    this.addLength = value;
}

/**
  * return text to print on command line or add to drawing
  * Param cmdLime - if true, format for command line
  *                 if false, format for drawing
*/
InfoArcCircleArea.prototype.getInfo = function(cmdLine) {
    var info = "";
    var area = 0.0;
    var circ = 0.0;
    var len = 0.0;
    var chord = 0.0;
    var rad1 = 0.0;
    var rad2 = 0.0;

    var di = this.getDocumentInterface();

    if (isCircleShape(this.shape)) {
        area = this.getCircleEllipseArea();
        circ = this.shape.getCircumference();
        if (!cmdLine) {
            area = area.toFixed(4);
            circ = circ.toFixed(4);
            this.label1 = qsTr("Area") + " = " + this.formatAreaResult(area, true);
            if (this.addLength) {
                this.label2 = qsTr("Circumference") + " = " + circ;
            } else {
                this.label2 = "";
            }
            this.label3 = "";
            info = this.label1;
        } else {
            info = qsTr("Circle area:") + " " + this.formatAreaResult(area, false) +
            ", " +  qsTr("circumference:") + " " + circ;
        }
    } else if (isEllipseArcShape(this.shape)) {
        if (this.segmentMode) {
            area = this.getSegmentArea();
            len = this.shape.getLength();
            chord = (this.shape.getStartPoint()).getDistanceTo(this.shape.getEndPoint());
            if (!cmdLine) {
                area = area.toFixed(4);
                len = len.toFixed(4);
                chord = chord.toFixed(4);
                this.label1 = qsTr("Area") + " = " + this.formatAreaResult(area, true);
                if (this.addLength) {
                    this.label2 = qsTr("Length") + " = " + len;
                    this.label3 = qsTr("Chord") + " = " + chord;
                } else {
                    this.label2 = "";
                    this.label3 = "";
                }
                info = this.label1;
            } else {
                info = qsTr("Ellipse arc area:") + " " + this.formatAreaResult(area, false) +
                ", " + qsTr("arc length:") + " " + len +
                ", " + qsTr("chord:") + " " + chord;
            }
        } else {
            area = this.getSectorArea();
            len = this.shape.getLength();
            rad1 = (this.shape.getCenter()).getDistanceTo(this.shape.getStartPoint());
            rad2 = (this.shape.getCenter()).getDistanceTo(this.shape.getEndPoint());
            if (!cmdLine) {
                area = area.toFixed(4);
                len = len.toFixed(4);
                rad1 = rad1.toFixed(4);
                rad2 = rad2.toFixed(4);
                this.label1 = qsTr("Area") + " = " + this.formatAreaResult(area, true);
                if (this.addLength) {
                    this.label2 = qsTr("Length") + " = " + len;
                    this.label3 = qsTr("Distance") + " = " + rad1 + " x " + rad2;
                } else {
                    this.label2 = "";
                    this.label3 = "";
                }
                info = this.label1;
            } else {
                info = qsTr("Ellipse arc area:") + " " + this.formatAreaResult(area, false) +
                ", " + qsTr("arc length:") + " " + len +
                ", " + qsTr("distance:") + " " + rad1 + " x " + rad2;
            }
        }
    } else if (isEllipseShape(this.shape)) {
        area = this.getCircleEllipseArea();
        circ = this.shape.getLength();
        if (!cmdLine) {
            area = area.toFixed(4);
            circ = circ.toFixed(4);
            this.label1 = qsTr("Area") + " = " + this.formatAreaResult(area, true);
            if (this.addLength) {
                this.label2 = qsTr("Circumference") + " = " + circ;
                this.label3 = "";
            } else {
                this.label2 = "";
                this.label3 = "";
            }
            info = this.label1;
        } else {
            info = qsTr("Ellipse area:") + " " + this.formatAreaResult(area, false) +
            ", " + qsTr("circumference:") + " " + circ;
        }
    } else {   // Arc shape
        if (this.segmentMode) {
            area = this.getSegmentArea();
            len = this.shape.getLength();
            chord = (this.shape.getStartPoint()).getDistanceTo(this.shape.getEndPoint());
            if (!cmdLine) {
                area = area.toFixed(4);
                len = len.toFixed(4);
                chord = chord.toFixed(4);
                this.label1 = qsTr("Area") + " = " + this.formatAreaResult(area, true);
                if (this.addLength) {
                    this.label2 = qsTr("Length") + " = " + len;
                    this.label3 = qsTr("Chord") + " = " + chord;
                } else {
                    this.label2 = "";
                    this.label3 = "";
                }
                info = this.label1;
            } else {
                info = qsTr("Arc area:") + " " + this.formatAreaResult(area, false) +
                ", " + qsTr("arc length:") + " " + len +
                ", " + qsTr("chord:") + " " + chord;
            }
        } else {
            area = this.getSectorArea();
            len = this.shape.getLength();
            rad1 = this.radius1;
            if (!cmdLine) {
                area = area.toFixed(4);
                len = len.toFixed(4);
                rad1 = rad1.toFixed(4);
                this.label1 = qsTr("Area") + " = " + this.formatAreaResult(area, true);
                if (this.addLength) {
                    this.label2 = qsTr("Length") + " = " + len;
                    this.label3 = qsTr("Radius") + " = " + rad1;
                } else {
                    this.label2 = "";
                    this.label3 = "";
                }
                info = this.label1;
            } else {
                info = qsTr("Arc area:") + " " + this.formatAreaResult(area, false) +
                ", " + qsTr("arc length:") + " " + len +
                ", " + qsTr("radius:") + " " + rad1;
            }
        }
    }
    return info;
};

InfoArcCircleArea.prototype.slotAddToDrawingChanged = function(value) {
    this.addToDrawing = value;
    var optionsToolBar = EAction.getOptionsToolBar();
    var textHeightEdit = optionsToolBar.findChild("TextHeight");
    textHeightEdit.enabled = value;
    var textHeightLabel = optionsToolBar.findChild("TextHeightLabel");
    textHeightLabel.enabled = value;

    var addLabel = optionsToolBar.findChild("Add");
    if (!isNull(addLabel)) {
        addLabel.enabled = value;
    }
    var entityButton = optionsToolBar.findChild("Entity");
    if (!isNull(entityButton)) {
        entityButton.enabled = value;
    }
    var chordButton = optionsToolBar.findChild("Chord");
    if (!isNull(chordButton)) {
        chordButton.enabled = value;
    }
    var lengthButton = optionsToolBar.findChild("Length");
    if (!isNull(lengthButton)) {
        lengthButton.enabled = value;
    }
};
