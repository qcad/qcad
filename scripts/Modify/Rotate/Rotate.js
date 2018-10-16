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

/**
 * \class Rotate
 * \brief Rotates selected entities. Supports multiple copies.
 * \ingroup ecma_modify
 */
function Rotate(guiAction) {
    Transform.call(this, guiAction);

    this.centerPoint = undefined;
    this.referencePoint = undefined;
    this.targetPoint = undefined;
    this.angle = undefined;
    this.angleByMouse = false;

    this.useDialog = RSettings.getBoolValue("Rotate/UseDialog", true);

    if (!this.useDialog) {
        this.setUiOptions("Rotate.ui");
    }
}

Rotate.prototype = new Transform();
Rotate.includeBasePath = includeBasePath;

Rotate.getPreferencesCategory = function() {
    return [qsTr("Modify"), qsTr("Rotate")];
};

Rotate.State = {
    SettingCenterPoint : 0,
    SettingReferencePoint : 1,
    SettingTargetPoint : 2
};

Rotate.prototype.beginEvent = function() {
    Transform.prototype.beginEvent.call(this);

    if (!this.verifySelection()) {
        return;
    }

    this.setState(Rotate.State.SettingCenterPoint);
};

Rotate.prototype.setState = function(state) {
    Transform.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Rotate.State.SettingCenterPoint:
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        var trCenterPoint = qsTr("Center point");
        this.setCommandPrompt(trCenterPoint);
        this.setLeftMouseTip(trCenterPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Rotate.State.SettingReferencePoint:
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        this.angle = undefined;
        var trReferencePoint = qsTr("Reference point");
        this.setCommandPrompt(trReferencePoint);
        this.setLeftMouseTip(trReferencePoint);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Rotate.State.SettingTargetPoint:
        this.targetPoint = undefined;
        this.angle = undefined;
        var trTargetPoint = qsTr("Target point");
        this.setCommandPrompt(trTargetPoint);
        this.setLeftMouseTip(trTargetPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Rotate.prototype.escapeEvent = function() {
    switch (this.state) {
    case Rotate.State.SettingCenterPoint:
        Transform.prototype.escapeEvent.call(this);
        break;

    case Rotate.State.SettingReferencePoint:
        this.setState(Rotate.State.SettingCenterPoint);
        break;

    case Rotate.State.SettingTargetPoint:
        this.setState(Rotate.State.SettingReferencePoint);
        break;
    }
};

Rotate.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var op;

    switch (this.state) {
    case Rotate.State.SettingCenterPoint:
        this.centerPoint = event.getModelPosition();

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

            // define angle with mouse:
            if (this.angleByMouse===true) {
                di.setRelativeZero(this.centerPoint);
                this.setState(Rotate.State.SettingReferencePoint);
            }

            // angle defined in dialog:
            else {
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                    di.setRelativeZero(this.centerPoint);
                    this.terminate();
                }
            }
        }
        break;

    case Rotate.State.SettingReferencePoint:
        this.referencePoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Rotate.State.SettingTargetPoint);
        }
        break;

    case Rotate.State.SettingTargetPoint:
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
 * Shows the rotation dialog.
 *
 * \return True if the dialog was accepted, false if it was canceled.
 */
Rotate.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(Rotate.includeBasePath, "RotateDialog.ui");
    WidgetFactory.restoreState(dialog);
    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
        return false;
    }

    var widgets = getWidgets(dialog);
    if (widgets["DeleteOriginal"].checked===true) {
        this.copies = 0;
    }
    else if (widgets["KeepOriginal"].checked===true) {
        this.copies = 1;
    }
    else {
        this.copies = widgets["NumberOfCopies"].getValue();
    }

    if (widgets["AngleByMouse"].checked===true) {
        this.angleByMouse = true;
        this.angle = undefined;
    }
    else {
        this.angleByMouse = false;
        this.angle = widgets["Angle"].getValue();
    }

    this.useCurrentAttributes = (widgets["UseCurrentAttributes"].checked===true);

    WidgetFactory.saveState(dialog);

    dialog.destroy();
    EAction.activateMainWindow();
    return true;
}

Rotate.prototype.getOperation = function(preview) {
    if (!isValidVector(this.centerPoint)) {
        return undefined;
    }

    if (this.angleByMouse===true) {
        if (!isValidVector(this.referencePoint) || !isValidVector(this.targetPoint)) {
            return undefined;
        }

        var a1 = this.centerPoint.getAngleTo(this.referencePoint);
        var a2 = this.centerPoint.getAngleTo(this.targetPoint);
        this.angle = RMath.getAngleDifference(a1, a2);
    }

    if (!isNumber(this.angle)) {
        return undefined;
    }

    return Transform.prototype.getOperation.call(this, preview);
}

/**
 * Callback function for Transform.getOperation.
 */
Rotate.prototype.transform = function(entity, k, op, preview, flags) {
    entity.rotate(this.angle * k, this.centerPoint);
    op.addObject(entity, flags);
}

Rotate.prototype.getAuxPreview = function() {
    if (!isValidVector(this.centerPoint)) {
        return undefined;
    }

    var ret = [];

    if (this.state==Rotate.State.SettingReferencePoint || this.state==Rotate.State.SettingTargetPoint) {
        if (isValidVector(this.referencePoint)) {
            ret.push(new RLine(this.centerPoint, this.referencePoint));
        }
    }

    if (this.state==Rotate.State.SettingTargetPoint) {
        if (isValidVector(this.targetPoint)) {
            ret.push(new RLine(this.centerPoint, this.targetPoint));
        }
    }

    return ret;
};

Rotate.prototype.slotAngleChanged = function(v) {
    this.angle = v;
};

Rotate.prototype.slotAngleByMouseChanged = function(v) {
    this.angleByMouse = v;
};
