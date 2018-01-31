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

include("../Circle.js");

/**
 * \class CircleCP
 * \brief Circle from center point and point on circle line.
 * \ingroup ecma_draw_circle
 */
function CircleCP(guiAction) {
    Circle.call(this, guiAction);
}

CircleCP.prototype = new Circle();

CircleCP.State = {
    SettingCenter : 0,
    SettingRadius : 1
};

CircleCP.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(CircleCP.State.SettingCenter);
};

CircleCP.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case CircleCP.State.SettingCenter:
        this.center = undefined;
        this.radius = undefined;

        var trCenter = qsTr("Center");
        this.setCommandPrompt(trCenter);
        this.setLeftMouseTip(trCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case CircleCP.State.SettingRadius:
        var trPointOnCircle = qsTr("Point on circle or radius");
        this.setCommandPrompt(trPointOnCircle);
        this.setLeftMouseTip(trPointOnCircle);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

CircleCP.prototype.escapeEvent = function() {
    switch (this.state) {
    case CircleCP.State.SettingCenter:
        EAction.prototype.escapeEvent.call(this);
        break;

    case CircleCP.State.SettingRadius:
        this.setState(CircleCP.State.SettingCenter);
        break;
    }
};

CircleCP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case CircleCP.State.SettingCenter:
        if (!preview) {
            this.center = event.getModelPosition();
            di.setRelativeZero(this.center);
            this.setState(CircleCP.State.SettingRadius);
        }
        break;

    case CircleCP.State.SettingRadius:
        this.radius = this.center.getDistanceTo(event.getModelPosition());
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(event.getModelPosition());
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(CircleCP.State.SettingCenter);
            }
        }
        break;
    }
};

CircleCP.prototype.getOperation = function(preview) {
    if (isNull(this.center) || !isNumber(this.radius)) {
        return undefined;
    }

    if (this.state != CircleCP.State.SettingRadius) {
        return undefined;
    }

    var circle = new RCircleEntity(
        this.getDocument(),
        new RCircleData(
            this.center,
            this.radius
        )
    );

    return new RAddObjectOperation(circle, this.getToolTitle());
};

CircleCP.prototype.applyCommand = function(event, preview) {
    var di = this.getDocumentInterface();
    var cmd = event.getCommand();

    var pos = RMath.parseCoordinate(cmd);
    if (pos.isValid()) {
        return;
    }

    var value = RMath.eval(cmd);
    if (pos.isValid()) {
        return;
    }

    switch (this.state) {
    case CircleCP.State.SettingRadius:
        event.accept();
        this.radius = value;
        if (preview) {
            this.updatePreview(true);
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(CircleCP.State.SettingCenter);
            }
        }
        break;
    }
};

