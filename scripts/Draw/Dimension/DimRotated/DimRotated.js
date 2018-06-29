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

include("scripts/Draw/Dimension/Dimension.js");

/**
 * \class DimRotated
 * \brief Draw rotated dimension (horizontal, vertical or other fixed angle).
 * \ingroup ecma_draw_dimension
 */
function DimRotated(guiAction) {
    Dimension.call(this, guiAction);

    this.data = new RDimRotatedData();
    this.setUiOptions(["../Dimension.ui", "DimRotated.ui"], false);
}

DimRotated.prototype = new Dimension();

DimRotated.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1,
    SettingDimPos : 2
};

DimRotated.prototype.beginEvent = function() {
    Dimension.prototype.beginEvent.call(this);

    this.setState(DimRotated.State.SettingPoint1);
};

DimRotated.prototype.setState = function(state) {
    Dimension.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DimRotated.State.SettingPoint1:
        this.data.setExtensionPoint1(RVector.invalid);
        this.data.setExtensionPoint2(RVector.invalid);
        this.data.setDefinitionPoint(RVector.invalid);
        var trFirstPoint = qsTr("First extension line origin");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case DimRotated.State.SettingPoint2:
        this.data.setExtensionPoint2(RVector.invalid);
        this.data.setDefinitionPoint(RVector.invalid);
        var trSecondPoint = qsTr("Second extension line origin");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trBack);
        break;

    case DimRotated.State.SettingDimPos:
        this.data.setDefinitionPoint(RVector.invalid);
        var trDimPos = qsTr("Dimension line location");
        this.setCommandPrompt(trDimPos);
        this.setLeftMouseTip(trDimPos);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

DimRotated.prototype.escapeEvent = function() {
    switch (this.state) {
    case DimRotated.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DimRotated.State.SettingPoint2:
        this.setState(DimRotated.State.SettingPoint1);
        break;

    case DimRotated.State.SettingDimPos:
        this.setState(DimRotated.State.SettingPoint2);
        break;
    }
};

DimRotated.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var pos = event.getModelPosition();

    switch (this.state) {
    case DimRotated.State.SettingPoint1:
        this.autoAdjustScale(pos);
        this.data.setExtensionPoint1(pos);
        if (!preview) {
            di.setRelativeZero(pos);
            this.setState(DimRotated.State.SettingPoint2);
        }
        break;

    case DimRotated.State.SettingPoint2:
        this.data.setExtensionPoint2(pos);

        // set definition point (dimension line position) to something
        // reasonable for the preview:
        var angle =
            this.data.getExtensionPoint1().getAngleTo(this.data.getExtensionPoint2()) +
                Math.PI/2.0;
        var doc = di.getDocument();
        var dimtxt = doc.getKnownVariable(RS.DIMTXT, 2.5);
        var dimscale = doc.getKnownVariable(RS.DIMSCALE, 1.0);
        var dp = this.data.getExtensionPoint2();
        dp = dp.operator_add(RVector.createPolar(dimtxt*2*dimscale, angle));
        this.data.setDefinitionPoint(dp);

        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(pos);
            this.setState(DimRotated.State.SettingDimPos);
        }
        break;

    case DimRotated.State.SettingDimPos:
        this.data.setDefinitionPoint(pos);
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(pos);
                this.setState(DimRotated.State.SettingPoint1);
            }
        }
        break;
    }
};

DimRotated.prototype.getOperation = function(preview) {
    if (!this.data.isValid()) {
        return undefined;
    }

    var doc = this.getDocument();
    var scale = this.parseScale(this.getScaleString());
    var scaled_data = this.data;

    scaled_data.setLinearFactor(1/scale);

    var entity = new RDimRotatedEntity(doc, scaled_data);
    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

/*
DimRotated.prototype.showUiOptions = function(resume, restoreFromSettings) {
    Dimension.prototype.showUiOptions.call(this, resume, restoreFromSettings);
};

DimRotated.prototype.hideUiOptions = function(saveToSettings) {
            debugger;
    Dimension.prototype.hideUiOptions.call(this, saveToSettings);
};
*/

/**
 * Called when the user changes the angle in the options toolbar.
 */
DimRotated.prototype.slotAngleChanged = function(value) {
    if (!isNull(this.data)) {
        if (isNaN(value)) {
            value=0.0;
        }

        this.data.setRotation(value);
    }
};

