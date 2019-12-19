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

    this.useDialog = RSettings.getBoolValue("Scale/UseDialog", true);

    if (!this.useDialog) {
        this.setUiOptions("Scale.ui");
    }
}

Scale.prototype = new Transform();
Scale.includeBasePath = includeBasePath;

Scale.getPreferencesCategory = function() {
    return [qsTr("Modify"), qsTr("Scale")];
};

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
        //this.factorX = undefined;
        //this.factorY = undefined;
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

Scale.prototype.initUiOptions = function(resume, optionsToolBar) {
    EAction.prototype.initUiOptions.call(this, resume, optionsToolBar);

    this.initWidgets(optionsToolBar, "Sq");
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
        this.focusPoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            if (this.useDialog) {
                this.setState(-1);
                if (!this.showDialog()) {
                    // dialog canceled:
                    this.terminate();
                    return;
                }
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
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.targetPoint);
                this.setState(-1);
                this.terminate();
            }
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

    this.initWidgets(dialog);

    WidgetFactory.restoreState(dialog);

    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
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
        this.factorX = undefined;
        this.factorY = undefined;
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
    EAction.activateMainWindow();
    return true;
};

Scale.prototype.initWidgets = function(widget, postfix) {
    if (isNull(postfix)) {
        postfix = "";
    }

    var widgets = getWidgets(widget);
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
                        widgets["KeepProportions"].icon = new QIcon(Scale.includeBasePath + "/KeepProportionsOn" + postfix + ".svg");
                    }
                    else {
                        widgets["KeepProportions"].icon = new QIcon(Scale.includeBasePath + "/KeepProportionsOff" + postfix + ".svg");
                    }
                });
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
        if (s2<RS.PointTolerance) {
            return undefined;
        }

        this.factorX = s2/s1;
        this.factorY = undefined;
    }

    if (!isNumber(this.factorX)) {
        return undefined;
    }

    return Transform.prototype.getOperation.call(this, preview);
};

Scale.prototype.transformArc = function(shape, sv) {
    var s = shape;
    if (isFunction(shape.data)) {
        s = shape.data();
    }

    if (isCircleShape(s)) {
        s = ShapeAlgorithms.circleToArc(s, 0.0);
    }

    return RShape.scaleArc(s, sv, this.focusPoint);
};

/**
 * Callback function for Transform.getOperation.
 */
Scale.prototype.transform = function(entity, k, op, preview, flags) {
    // uniform scaling (supported by all entities):
    if (isNull(this.factorY) || RMath.fuzzyCompare(this.factorX, this.factorY)) {
        entity.scale(Math.pow(this.factorX, k), this.focusPoint);
        op.addObject(entity, flags);
        return;
    }

    var e;

    // non-uniform scaling of arc, circle or ellipse:
    var sv = new RVector(Math.pow(this.factorX, k), Math.pow(this.factorY, k));

    if (isArcEntity(entity) || isCircleEntity(entity) || isEllipseEntity(entity)) {
        var arc = entity.castToShape();

        var shape = this.transformArc(arc, sv);

        e = shapeToEntity(this.getDocument(), shape);
        if (!isNull(e)) {
            e.copyAttributesFrom(entity);
            e.setDrawOrder(entity.getDrawOrder());
            e.setSelected(true);
        }

        if (this.getCopies()===0) {
            op.deleteObject(entity);
        }
        if (!isNull(e)) {
            op.addObject(e, flags);
        }
        return;
    }

    // non-uniform scaling of hatches:
    if (isHatchEntity(entity)) {
        //debugger;
        var data = entity.getData();
        var newHatchData = new RHatchData();
        newHatchData.setDocument(data.getDocument());
        newHatchData.copyAttributesFrom(data);

        //newHatchData.clearBoundary();

        for (var i=0; i<entity.getLoopCount(); i++) {
            newHatchData.newLoop();

            var shapes = entity.getLoopBoundary(i);
            for (var n=0; n<shapes.length; n++) {
                shape = shapes[n];

                if (isArcShape(shape) || isCircleShape(shape) || isEllipseShape(shape)) {
                    var newShape = this.transformArc(shape, sv);
                    newHatchData.addBoundary(newShape);
                }
                else {
                    // line, spline:
                    shape.scale(sv, this.focusPoint);
                    newHatchData.addBoundary(shape);
                }
            }
        }
        newHatchData.setSolid(entity.isSolid());
        newHatchData.setPatternName(entity.getPatternName());
        newHatchData.setScale(entity.getScale());
        newHatchData.setAngle(entity.getAngle());
        newHatchData.setOriginPoint(entity.getOriginPoint());

        entity.setData(newHatchData);
        op.addObject(entity, flags);
        return;
    }

    // non-uniform scaling of other entities:
    entity.scale(sv, this.focusPoint);
    op.addObject(entity, flags);
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

Scale.prototype.slotFactorXChanged = function(v) {
    this.factorX = v;
};

Scale.prototype.slotFactorYChanged = function(v) {
    this.factorY = v;
};

Scale.prototype.slotFactorByMouseChanged = function(v) {
    this.factorByMouse = v;
};
