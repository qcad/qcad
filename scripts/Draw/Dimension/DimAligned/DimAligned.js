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
 * \class DimAligned
 * \brief Draw aligned dimension.
 * \ingroup ecma_draw_dimension
 */
function DimAligned(guiAction) {
    Dimension.call(this, guiAction);

    this.data = new RDimAlignedData();
    this.setUiOptions("../Dimension.ui");
}

DimAligned.prototype = new Dimension();

DimAligned.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1,
    SettingDimPos : 2
};

DimAligned.prototype.beginEvent = function() {
    Dimension.prototype.beginEvent.call(this);

    this.setState(DimAligned.State.SettingPoint1);
};

DimAligned.prototype.setState = function(state) {
    Dimension.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DimAligned.State.SettingPoint1:
        this.data.setExtensionPoint1(RVector.invalid);
        this.data.setExtensionPoint2(RVector.invalid);
        this.data.setDefinitionPoint(RVector.invalid);
        var trFirstPoint = qsTr("First extension line origin");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case DimAligned.State.SettingPoint2:
        this.data.setExtensionPoint2(RVector.invalid);
        this.data.setDefinitionPoint(RVector.invalid);
        var trSecondPoint = qsTr("Second extension line origin");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trBack);
        break;

    case DimAligned.State.SettingDimPos:
        this.data.setDefinitionPoint(RVector.invalid);
        var trDimPos = qsTr("Dimension line location");
        this.setCommandPrompt(trDimPos);
        this.setLeftMouseTip(trDimPos);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

DimAligned.prototype.escapeEvent = function() {
    switch (this.state) {
    case DimAligned.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DimAligned.State.SettingPoint2:
        this.setState(DimAligned.State.SettingPoint1);
        break;

    case DimAligned.State.SettingDimPos:
        this.setState(DimAligned.State.SettingPoint2);
        break;
    }
};

DimAligned.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var pos = event.getModelPosition();

    switch (this.state) {
    case DimAligned.State.SettingPoint1:
        this.autoAdjustScale(pos);
        this.data.setExtensionPoint1(pos);
        if (!preview) {
            di.setRelativeZero(pos);
            this.setState(DimAligned.State.SettingPoint2);
        }
        break;

    case DimAligned.State.SettingPoint2:
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
            this.setState(DimAligned.State.SettingDimPos);
        }
        break;

    case DimAligned.State.SettingDimPos:
        this.data.setDefinitionPoint(pos);
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(pos);
                this.setState(DimAligned.State.SettingPoint1);
            }
        }
        break;

    }
};

DimAligned.prototype.getOperation = function(preview) {
    if (!this.data.isValid()) {
        return undefined;
    }

    var doc = this.getDocument();
    var scale = this.parseScale(this.getScaleString());
    var scaled_data = this.data;

    scaled_data.setLinearFactor(1/scale);

    var entity = new RDimAlignedEntity(doc, scaled_data);
    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

