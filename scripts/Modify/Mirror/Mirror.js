/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
 * \class Mirror
 * \brief Mirrors selected entities.
 * \ingroup ecma_modify
 */
function Mirror(guiAction) {
    Transform.call(this, guiAction);

    this.axisPoint1 = undefined;
    this.axisPoint2 = undefined;
}

Mirror.prototype = new Transform();

Mirror.includeBasePath = includeBasePath;

Mirror.State = {
    SettingAxisPoint1 : 0,
    SettingAxisPoint2 : 1
};

Mirror.prototype.beginEvent = function() {
    Transform.prototype.beginEvent.call(this);

    if (!this.verifySelection()) {
        return;
    }

    this.setState(Mirror.State.SettingAxisPoint1);
};

Mirror.prototype.setState = function(state) {
    Transform.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Mirror.State.SettingAxisPoint1:
        var trAxisPoint1 = qsTr("First point of symmetry axis");
        this.setCommandPrompt(trAxisPoint1);
        this.setLeftMouseTip(trAxisPoint1);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Mirror.State.SettingAxisPoint2:
        var trAxisPoint2 = qsTr("Second point of symmetry axis");
        this.setCommandPrompt(trAxisPoint2);
        this.setLeftMouseTip(trAxisPoint2);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Mirror.prototype.escapeEvent = function() {
    switch (this.state) {
    case Mirror.State.SettingAxisPoint1:
        Transform.prototype.escapeEvent.call(this);
        break;

    case Mirror.State.SettingAxisPoint2:
        this.setState(Mirror.State.SettingAxisPoint1);
        break;
    }
};

Mirror.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Mirror.State.SettingAxisPoint1:
        if (!preview) {
            this.axisPoint1 = event.getModelPosition();
            di.setRelativeZero(this.axisPoint1);
            this.setState(Mirror.State.SettingAxisPoint2);
        }
        break;

    case Mirror.State.SettingAxisPoint2:
        this.axisPoint2 = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(-1);
            if (!this.showDialog()) {
                // dialog canceled:
                this.terminate();
                return;
            }

            di.applyOperation(this.getOperation(false));
            di.setRelativeZero(this.axisPoint2);
            this.terminate();
        }
        break;
    }
};

/**
 * Shows the translation dialog.
 *
 * \return True if the dialog was accepted, false if it was canceled.
 */
Mirror.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(Mirror.includeBasePath, "MirrorDialog.ui");
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

    this.useCurrentAttributes = (widgets["UseCurrentAttributes"].checked===true);

    WidgetFactory.saveState(dialog);

    dialog.destroy();
    EAction.activateMainWindow();
    return true;
};

/**
 * Callback function for Transform.getOperation.
 */
Mirror.prototype.transform = function(entity, k, op, preview, forceNew) {
    entity.mirror(this.axisPoint1, this.axisPoint2);
    op.addObject(entity, this.useCurrentAttributes, forceNew);
};

Mirror.prototype.getAuxPreview = function() {
    if (!isValidVector(this.axisPoint1) || !isValidVector(this.axisPoint1)) {
        return undefined;
    }

    var ret = [];

    ret.push(new RLine(this.axisPoint1, this.axisPoint2));

    return ret;
};

