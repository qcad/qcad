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

include("../Circle.js");

/**
 * \class CircleCR
 * \brief Circle from center and radius.
 * \ingroup ecma_draw_circle
 */
function CircleCR(guiAction) {
    Circle.call(this, guiAction);

    this.setUiOptions("CircleCR.ui");
}

CircleCR.prototype = new Circle();

CircleCR.State = {
    SettingCenter : 0
};

CircleCR.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(CircleCR.State.SettingCenter);
};

CircleCR.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case CircleCR.State.SettingCenter:
        this.center = undefined;

        this.setCommandPrompt(qsTr("Center or radius"));
        this.setLeftMouseTip(qsTr("Center"));
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

CircleCR.prototype.escapeEvent = function() {
    switch (this.state) {
    case CircleCR.State.SettingCenter:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

CircleCR.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case CircleCR.State.SettingCenter:
        this.center = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.center);
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
        }
        break;
    }
};

CircleCR.prototype.getOperation = function(preview) {
    if (isNull(this.center) || !isNumber(this.radius)) {
        return undefined;
    }

    var circle = new RCircleEntity(
        this.getDocument(),
        new RCircleData(
            this.center,
            this.radius
        )
    );

    return new RAddObjectOperation(circle);
};

CircleCR.prototype.applyCommand = function(event, preview) {
    var di = this.getDocumentInterface();

    var value = RMath.eval(event.getCommand());
    if (isNaN(value)) {
        return;
    }

    switch (this.state) {
    case CircleCR.State.SettingCenter:
        event.accept();
        if (preview) {
            var r = this.radius;
            this.radius = value;
            this.updatePreview(true);
            this.radius = r;
        }
        else {
            //this.radius = value;
            //this.updateOptionsUi();
            this.setRadius(event.getCommand());
        }
        break;
    }
};

CircleCR.prototype.setRadius = function(expr) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("Radius");
    if (isQWidget(w)) {
        w.text = expr;
    }
};

CircleCR.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
    this.updatePreview(true);
};

