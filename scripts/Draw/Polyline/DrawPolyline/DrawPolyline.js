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

include("../Polyline.js");

/**
 * \class DrawPolyline
 * \brief Draw polyline, segment by segment.
 * This is also the base class for PolylineAppendNode.
 * \ingroup ecma_draw_polyline
 */
function DrawPolyline(guiAction) {
    Polyline.call(this, guiAction);

    this.polylineEntity = undefined;
    this.arcSegment = false;
    this.radius = 1.0;
    this.prepend = false;
    this.segment = undefined;

    this.setUiOptions("DrawPolyline.ui");
}

DrawPolyline.prototype = new Polyline();

DrawPolyline.State = {
    SettingFirstVertex : 0,
    SettingNextVertex : 1
};

DrawPolyline.prototype.beginEvent = function() {
    Polyline.prototype.beginEvent.call(this);

    this.setState(DrawPolyline.State.SettingFirstVertex);
    this.updateButtonStates();
};

DrawPolyline.prototype.initState = function() {
    Polyline.prototype.initState.call(this);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DrawPolyline.State.SettingFirstVertex:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trFirstVertex = qsTr("First vertex");
        this.setCommandPrompt(trFirstVertex);
        this.setLeftMouseTip(trFirstVertex);
        this.setRightMouseTip(EAction.trCancel);
        this.segment = undefined;
        EAction.showSnapTools();
        break;

    case DrawPolyline.State.SettingNextVertex:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trNextVertex = qsTr("Next vertex");
        this.setCommandPrompt(trNextVertex);
        this.setLeftMouseTip(trNextVertex);
        this.setRightMouseTip(qsTr("Done"));
        EAction.showSnapTools();
        break;
    }
};

DrawPolyline.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);
    this.updateButtonStates();
};

DrawPolyline.prototype.escapeEvent = function() {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case DrawPolyline.State.SettingFirstVertex:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DrawPolyline.State.SettingNextVertex:
        if (!isNull(this.polylineEntity)) {
            // remove polyline with one or zero vertices:
            if (this.polylineEntity.countVertices()<=1) {
                var op = new RDeleteObjectOperation(this.polylineEntity, false);
                this.applyOperation(op);
            }
        }

        this.setState(DrawPolyline.State.SettingFirstVertex);
        this.updateButtonStates();
        break;
    }
};

DrawPolyline.prototype.pickCoordinate = function(event, preview) {
    var point, op;
    
    var di = this.getDocumentInterface();
    var document = this.getDocument();

    switch (this.state) {
    // set first vertex, create polyline entity:
    case DrawPolyline.State.SettingFirstVertex:
        if (!preview) {
            point = event.getModelPosition();

            var pl = new RPolylineEntity(document, new RPolylineData());
            pl.appendVertex(point);
            op = new RAddObjectOperation(pl);
            this.applyOperation(op);

            di.setRelativeZero(point);
            this.setState(DrawPolyline.State.SettingNextVertex);
        }
        break;

    // set next vertex:
    case DrawPolyline.State.SettingNextVertex:
        point = event.getModelPosition();

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
                di.setRelativeZero(point);
                this.uncheckArcSegment();
            }
        }
        break;
    }

    if (!preview) {
        this.updateButtonStates();
    }
};

DrawPolyline.prototype.getOperation = function(preview) {
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
        entity.copyAttributesFrom(this.polylineEntity.data());
        return new RAddObjectOperation(entity, false);
    }
    else {
        return new RAddObjectOperation(this.polylineEntity, true, false);
    }
};

/**
 * Updates the polyline in storage and makes sure that this.polylineEntity
 * points to new new clone of the original entity.
 */
DrawPolyline.prototype.applyOperation = function(op) {
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
DrawPolyline.prototype.slotClose = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    var di = this.getDocumentInterface();

    if (this.polylineEntity.countVertices() >= 3) {
        this.polylineEntity.setClosed(true);
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
            this.setState(DrawPolyline.State.SettingFirstVertex);
        }
    }
    
    this.updateButtonStates();
};

/**
 * Called when user clicks the 'Undo' button to remove the last added vertex.
 */
DrawPolyline.prototype.slotUndo = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    var di = this.getDocumentInterface();

    if (this.polylineEntity.countVertices() >= 2) {
        this.polylineEntity.removeLastVertex();
        di.clearPreview();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
        }
    }

    this.updateButtonStates();
};

/**
 * Called when user toggles 'Arc segment' check box to indicate if the next
 * segment is a line or an arc segment.
 */
DrawPolyline.prototype.slotArcSegmentChanged = function(value) {
    this.arcSegment = value;
};

/**
 * Called when user enters a radius for the next arc segment.
 */
DrawPolyline.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
};

/**
 * Called internally to automatically uncheck the 'Arc segment' check box.
 */
DrawPolyline.prototype.uncheckArcSegment = function() {
    var w = objectFromPath("MainWindow::Options::ArcSegment");
    w.checked = false;
};

/**
 * Updates the state (enabled / disabled) of the undo and the close buttons
 * depending on the current progress.
 */
DrawPolyline.prototype.updateButtonStates = function() {
    var w;
    
    if (this.state==DrawPolyline.State.SettingFirstVertex) {
        this.uncheckArcSegment();
    }

    if (isNull(this.polylineEntity)) {
        return;
    }

    w = objectFromPath("MainWindow::Options::Undo");
    if (this.polylineEntity.countVertices() > 1) {
        w.enabled = true;
    } else {
        w.enabled = false;
    }
    
    w = objectFromPath("MainWindow::Options::Close");
    if (this.polylineEntity.countVertices() < 3) {
        w.enabled = false;
    } else {
        w.enabled = true;
    }
};

DrawPolyline.prototype.getAuxPreview = function() {
    var ret = [];

    if (this.state==DrawPolyline.State.SettingNextVertex) {
        if (!isNull(this.center) && !isNull(this.angle)) {
            var v = RVector.createPolar(this.radius, this.angle);
            ret.push(new RLine(this.center, this.center.operator_add(v)));
        }
    }

    return ret;
};
