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
 * \class Rotate2
 * \brief Rotates and counter-rotates selected entities. Supports multiple copies.
 * \ingroup ecma_modify
 */
function Rotate2(guiAction) {
    Transform.call(this, guiAction);

    this.primaryCenter = undefined;
    this.secondaryCenter = undefined;

    this.primaryAngle = 0.0;
    this.secondaryAngle = 0.0;

    this.setUiOptions("Rotate2.ui");
}

Rotate2.prototype = new Transform();

Rotate2.includeBasePath = includeBasePath;

Rotate2.State = {
    SettingPrimaryCenter : 0,
    SettingSecondaryCenter : 1
};

Rotate2.prototype.beginEvent = function() {
    Transform.prototype.beginEvent.call(this);

    if (!this.verifySelection()) {
        return;
    }

    this.setState(Rotate2.State.SettingPrimaryCenter);
};

Rotate2.prototype.setState = function(state) {
    Transform.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Rotate2.State.SettingPrimaryCenter:
        var trPrimaryCenter = qsTr("Center of primary rotation");
        this.setCommandPrompt(trPrimaryCenter);
        this.setLeftMouseTip(trPrimaryCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Rotate2.State.SettingSecondaryCenter:
        var trSecondaryCenter = qsTr("Center of secondary rotation");
        this.setCommandPrompt(trSecondaryCenter);
        this.setLeftMouseTip(trSecondaryCenter);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Rotate2.prototype.escapeEvent = function() {
    switch (this.state) {
    case Rotate2.State.SettingPrimaryCenter:
        Transform.prototype.escapeEvent.call(this);
        break;

    case Rotate2.State.SettingSecondaryCenter:
        this.setState(Rotate2.State.SettingPrimaryCenter);
        break;
    }
};

Rotate2.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Rotate2.State.SettingPrimaryCenter:
        if (!preview) {
            this.primaryCenter = event.getModelPosition();
            di.setRelativeZero(this.primaryCenter);
            this.setState(Rotate2.State.SettingSecondaryCenter);
        }
        break;

    case Rotate2.State.SettingSecondaryCenter:
        this.secondaryCenter = event.getModelPosition();

        if (preview) {
            di.previewOperation(this.getOperation(true));
        }
        else {
            this.setState(-1);
            if (!this.showDialog()) {
                // dialog canceled:
                this.terminate();
                return;
            }

            di.applyOperation(this.getOperation(false));
            di.setRelativeZero(this.secondaryCenter);
            this.terminate();
        }
        break;
    }
};

/**
 * Shows the rotation dialog.
 *
 * \return True if the dialog was accepted, false if it was canceled.
 */
Rotate2.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(Rotate2.includeBasePath, "Rotate2Dialog.ui");
    WidgetFactory.restoreState(dialog);

    var widgets = getWidgets(dialog);

    // initialize dialog angles to angles used in tool options toolbar:
    widgets["PrimaryAngle"].setValue(this.primaryAngle);
    widgets["SecondaryAngle"].setValue(this.secondaryAngle);

    if (this.copies<0.5) {
        widgets["DeleteOriginal"].checked = true;
    }
    else if (this.copies<1.5) {
        widgets["KeepOriginal"].checked = true;
    }
    else {
        widgets["MultipleCopies"].checked = true;
        widgets["NumberOfCopies"].setValue(this.copies);
    }

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

    this.primaryAngle = widgets["PrimaryAngle"].getValue();
    this.secondaryAngle = widgets["SecondaryAngle"].getValue();

    this.useCurrentAttributes = (widgets["UseCurrentAttributes"].checked===true);

    WidgetFactory.saveState(dialog);

    dialog.destroy();
    EAction.activateMainWindow();
    return true;
};

/**
 * Callback function for Transform.getOperation.
 */
Rotate2.prototype.transform = function(entity, k, op, preview, flags) {
//    qDebug("sc (transform): ", this.secondaryCenter);

    entity.rotate(this.primaryAngle * k, this.primaryCenter);
    var sc = this.secondaryCenter.copy();
    sc.rotate(this.primaryAngle * k, this.primaryCenter);
    entity.rotate(this.secondaryAngle * k, sc);
    op.addObject(entity, flags);
};

Rotate2.prototype.slotPrimaryAngleChanged = function(value) {
    this.primaryAngle = value;
    qDebug("this.primaryAngle: ", this.primaryAngle);
    if (this.primaryAngle>29.9) {
        debugger;
    }
};

Rotate2.prototype.slotSecondaryAngleChanged = function(value) {
    this.secondaryAngle = value;
};

Rotate2.prototype.slotNumberOfCopiesChanged = function(value) {
    this.copies = value;
};

