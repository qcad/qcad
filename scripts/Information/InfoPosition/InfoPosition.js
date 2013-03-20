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

include("../Information.js");

function InfoPosition(guiAction) {
    Information.call(this, guiAction);
}

InfoPosition.prototype = new Information();

InfoPosition.State = {
    SettingPoint : 0
};

InfoPosition.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.setState(InfoPosition.State.SettingPoint);
};

InfoPosition.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    di.setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoPosition.State.SettingPoint:
        var tsPoint = qsTr("Point");
        this.setCommandPrompt(tsPoint);
        this.setLeftMouseTip(tsPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

InfoPosition.prototype.escapeEvent = function() {
    switch (this.state) {
    case InfoPosition.State.SettingPoint:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

InfoPosition.prototype.pickCoordinate = function(event, preview) {
    var appWin = EAction.getMainWindow();
    var di = this.getDocumentInterface();

    switch (this.state) {
    case InfoPosition.State.SettingPoint:
        if (!preview) {
            var p = event.getModelPosition();
            appWin.handleUserInfo(coordinateToString(p, 4, false, false));
            di.setRelativeZero(p);
        }
        break;
    }
};
