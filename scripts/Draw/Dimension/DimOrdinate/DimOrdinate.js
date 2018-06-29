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
 * \class DimOrdinate
 * \brief Draw ordinate dimension.
 * \ingroup ecma_draw_dimension
 */
function DimOrdinate(guiAction) {
    Dimension.call(this, guiAction);

    this.data = new RDimOrdinateData();
    this.data.setOrigin(new RVector(0,0));
    this.setUiOptions("../Dimension.ui");
}

DimOrdinate.prototype = new Dimension();

DimOrdinate.State = {
    SettingDefiningPoint : 0,
    SettingLeaderEndPoint : 1
};

DimOrdinate.prototype.beginEvent = function() {
    Dimension.prototype.beginEvent.call(this);

    this.setState(DimOrdinate.State.SettingDefiningPoint);
};

DimOrdinate.prototype.setState = function(state) {
    var tr;
    
    Dimension.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DimOrdinate.State.SettingDefiningPoint:
        this.data.setDefiningPoint(RVector.invalid);
        this.data.setLeaderEndPoint(RVector.invalid);
        tr = qsTr("Feature location");
        this.setCommandPrompt(tr);
        this.setLeftMouseTip(tr);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case DimOrdinate.State.SettingLeaderEndPoint:
        this.data.setLeaderEndPoint(RVector.invalid);
        tr = qsTr("Endpoint of leader");
        this.setCommandPrompt(tr);
        this.setLeftMouseTip(tr);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

DimOrdinate.prototype.escapeEvent = function() {
    switch (this.state) {
    case DimOrdinate.State.SettingDefiningPoint:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DimOrdinate.State.SettingLeaderEndPoint:
        this.setState(DimOrdinate.State.SettingDefiningPoint);
        break;
    }
};

DimOrdinate.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case DimOrdinate.State.SettingDefiningPoint:
        this.data.setDefiningPoint(event.getModelPosition());
        if (!preview) {
            di.setRelativeZero(event.getModelPosition());
            this.setState(DimOrdinate.State.SettingLeaderEndPoint);
        }
        break;

    case DimOrdinate.State.SettingLeaderEndPoint:
        this.data.setLeaderEndPoint(event.getModelPosition());

        var dx = this.data.getLeaderEndPoint().x-this.data.getDefiningPoint().x;
        var dy = this.data.getLeaderEndPoint().y-this.data.getDefiningPoint().y;

        if (Math.abs(dx) > Math.abs(dy)) {
            this.data.setMeasuringYAxis();
        }
        else {
            this.data.setMeasuringXAxis();
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(event.getModelPosition());
                this.setState(DimOrdinate.State.SettingDefiningPoint);
            }
        }
        break;
    }
};

DimOrdinate.prototype.getOperation = function(preview) {
    if (!this.data.isValid()) {
        return undefined;
    }

    var doc = this.getDocument();
    var entity = new RDimOrdinateEntity(doc, this.data);
    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

