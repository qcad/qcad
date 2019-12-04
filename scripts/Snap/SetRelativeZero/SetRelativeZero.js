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

include("scripts/Snap/Snap.js");

/**
 * \class SetRelativeZero
 * \brief Sets a new position for the relative zero point.
 * \ingroup ecma_snap
 */
function SetRelativeZero(guiAction) {
    Snap.call(this, guiAction);
}

SetRelativeZero.State = {
    SettingPosition : 0
};

SetRelativeZero.prototype = new Snap();

SetRelativeZero.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);

    this.setState(SetRelativeZero.State.SettingPosition);
};

SetRelativeZero.prototype.setState = function(state) {
    Snap.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var tr = qsTr("Position");
    this.setLeftMouseTip(tr);
    this.setCommandPrompt(tr);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

SetRelativeZero.prototype.coordinateEvent = function(event) {
    var pos = event.getModelPosition();
    var di = this.getDocumentInterface();
    if(isNull(di)) {
        this.terminate();
        return;
    }

    var locked = di.isRelativeZeroLocked();
    if (locked) {
        di.unlockRelativeZero();
    }

    di.setRelativeZero(pos);
    EAction.noRelativeZeroResume = true;

    if (locked) {
        di.lockRelativeZero();
    }

    this.terminate();
};

