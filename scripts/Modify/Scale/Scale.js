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

include("../Transform.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Scale
 * \brief Scales selected entities. Supports multiple copies.
 * \ingroup ecma_modify
 */
function Scale(guiAction) {
    Transform.call(this, guiAction);

    this.focusPoint = undefined;
    this.referencePoint = undefined;
    this.targetPoint = undefined;
    this.factorX = undefined;
    this.factorY = undefined;
}

Scale.prototype = new Transform();

Scale.includeBasePath = includeBasePath;

Scale.State = {
    SettingCenterPoint : 0,
    SettingReferencePoint : 1,
    SettingTargetPoint : 2
};

Scale.prototype.beginEvent = function() {
    Transform.prototype.beginEvent.call(this);

    if (!this.verifySelection()) {
        return;
    }

    this.setState(Scale.State.SettingCenterPoint);
};

Scale.prototype.setState = function(state) {
    Transform.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Scale.State.SettingCenterPoint:
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        this.factorX = undefined;
        this.factorY = undefined;
        var trCenterPoint = qsTr("Focus point");
        this.setCommandPrompt(trCenterPoint);
        this.setLeftMouseTip(trCenterPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Scale.State.SettingReferencePoint:
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        this.factorX = undefined;
        this.factorY = undefined;
        var trReferencePoint = qsTr("Reference point");
        this.setCommandPrompt(trReferencePoint);
        this.setLeftMouseTip(trReferencePoint);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Scale.State.SettingTargetPoint:
        this.targetPoint = undefined;
        this.factorX = undefined;
        this.factorY = undefined;
        var trTargetPoint = qsTr("Target point");
        this.setCommandPrompt(trTargetPoint);
        this.setLeftMouseTip(trTargetPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Scale.prototype.escapeEvent = function() {
    switch (this.state) {
    case Scale.State.SettingCenterPoint:
        Transform.prototype.escapeEvent.call(this);
        break;

    case Scale.State.SettingReferencePoint:
        this.setState(Scale.State.SettingCenterPoint);
        break;

    case Scale.State.SettingTargetPoint:
        this.setState(Scale.State.SettingReferencePoint);
        break;
    }
};

Scale.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var op;

    switch (this.state) {
    case Scale.State.SettingCenterPoint:
        if (!preview) {
            this.focusPoint = event.getModelPosition();
            this.setState(-1);

            if (!this.showDialog()) {
                // dialog canceled:
                this.terminate();
                return;
            }

            // define factor with mouse:
            if (this.factorByMouse===true) {
                this.setState(Scale.State.SettingReferencePoint);
            }

            // factor defined in dialog:
            else {
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                    di.setRelativeZero(this.focusPoint);
                    this.terminate();
                }
            }
        }
        break;

    case Scale.State.SettingReferencePoint:
        this.referencePoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.referencePoint);
            this.setState(Scale.State.SettingTargetPoint);
        }
        break;

    case Scale.State.SettingTargetPoint:
        this.targetPoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            di.applyOperation(op);
            di.setRelativeZero(this.targetPoint);
            this.setState(-1);
            this.terminate();
        }
        break;
    }
};

/**
 * Shows the scaling dialog.
 *
 * \return True if the dialog was accepted, false if it was canceled.
 */
Scale.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(Scale.includeBasePath, "ScaleDialog.ui");
    var widgets = getWidgets(dialog);

    widgets["FactorX"].textChanged.connect(
                function(text) {
                    if (widgets["KeepProportions"].checked===true) {
                        widgets["FactorY"].text = text;
                    }
                });

    widgets["KeepProportions"].toggled.connect(
                function(checked) {
                    if (checked) {
                        widgets["FactorY"].text = widgets["FactorX"].text;
                    }

                    if (checked) {
                        widgets["KeepProportions"].icon = new QIcon(Scale.includeBasePath + "/KeepProportionsOn.svg");
                    }
                    else {
                        widgets["KeepProportions"].icon = new QIcon(Scale.includeBasePath + "/KeepProportionsOff.svg");
                    }
                });

    WidgetFactory.restoreState(dialog);

    if (!dialog.exec()) {
        dialog.destroy();
        return false;
    }

    if (widgets["DeleteOriginal"].checked===true) {
        this.copies = 0;
    }
    else if (widgets["KeepOriginal"].checked===true) {
        this.copies = 1;
    }
    else {
        this.copies = widgets["NumberOfCopies"].getValue();
    }

    if (widgets["FactorByMouse"].checked===true) {
        this.factorByMouse = true;
        this.factor = undefined;
    }
    else {
        this.factorByMouse = false;
        this.factorX = widgets["FactorX"].getValue();
        if (widgets["KeepProportions"].checked===false) {
            this.factorY = widgets["FactorY"].getValue();
        }
        else {
            this.factorY = undefined;
        }
    }

    this.useCurrentAttributes = (widgets["UseCurrentAttributes"].checked===true);

    WidgetFactory.saveState(dialog);

    dialog.destroy();
    return true;
};

Scale.prototype.getOperation = function(preview) {
    if (!isValidVector(this.focusPoint)) {
        return undefined;
    }

    if (this.factorByMouse===true) {
        if (!isValidVector(this.referencePoint) || !isValidVector(this.targetPoint)) {
            return undefined;
        }

        var s1, s2;
        s1 = this.focusPoint.getDistanceTo(this.referencePoint);
        if (s1<RS.PointTolerance) {
            return undefined;
        }

        s2 = this.focusPoint.getDistanceTo(this.targetPoint);

        this.factorX = s2/s1;
        this.factorY = undefined;
    }

    if (!isNumber(this.factorX)) {
        return undefined;
    }

    return Transform.prototype.getOperation.call(this, preview);
};

/**
 * Callback function for Transform.getOperation.
 */
Scale.prototype.transform = function(entity, k, op, preview, forceNew) {
    // uniform scaling (supported by all entities):
    if (isNull(this.factorY)) {
        entity.scale(Math.pow(this.factorX, k), this.focusPoint);
        op.addObject(entity, this.useCurrentAttributes, forceNew);
        return;
    }

    // non-uniform scaling of arc, circle or ellipse:
    var sv = new RVector(Math.pow(this.factorX, k), Math.pow(this.factorY, k));
    if (isArcEntity(entity) || isCircleEntity(entity) || isEllipseEntity(entity)) {
        var arc = entity.castToShape();
        if (isCircleShape(arc)) {
            arc = ShapeAlgorithms.circleToArc(arc);
        }

        var self=this;
        var shape = ShapeAlgorithms.transformArc(
            arc,
            function(p) {
                return p.scale(sv, self.focusPoint);
            }
        );

        var e = shapeToEntity(this.getDocument(), shape);
        e.copyAttributesFrom(entity);
        e.setDrawOrder(entity.getDrawOrder());
        e.setSelected(true);

        if (this.copies===0) {
            op.deleteObject(entity);
        }
        op.addObject(e, this.useCurrentAttributes, forceNew);
        return;
    }

    // non-uniform scaling of other entities:
    entity.scale(sv, this.focusPoint);
    op.addObject(entity, this.useCurrentAttributes, forceNew);
};

Scale.prototype.getAuxPreview = function() {
    if (!isValidVector(this.focusPoint)) {
        return undefined;
    }

    var ret = [];

    if (this.state==Scale.State.SettingReferencePoint || this.state==Scale.State.SettingTargetPoint) {
        if (isValidVector(this.referencePoint)) {
            ret.push(new RLine(this.focusPoint, this.referencePoint));
        }
    }

    if (this.state==Scale.State.SettingTargetPoint) {
        if (isValidVector(this.targetPoint)) {
            ret.push(new RLine(this.focusPoint, this.targetPoint));
        }
    }

    return ret;
};



