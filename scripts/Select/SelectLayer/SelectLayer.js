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

include("../Select.js");

function SelectLayer(guiAction) {
    Select.call(this, guiAction);

    this.setUiOptions("SelectLayer.ui");
}

SelectLayer.prototype = new Select();

SelectLayer.State = {
    ChoosingEntity : 0
};

SelectLayer.prototype.selectEntities = function(entityId) {
    var entity = this.doc.queryEntity(entityId);
    if (isNull(entity)) {
        return;
    }

    var layerId = entity.getLayerId();

    // select all entities on the same layer:
    this.matchingEntities = this.doc.queryLayerEntities(layerId);
};


SelectLayer.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);

    this.doc = this.getDocument();
    this.di = this.getDocumentInterface();

    this.setState(SelectLayer.State.ChoosingEntity);
};

SelectLayer.prototype.setState = function(state) {
    Select.prototype.setState.call(this, state);
    this.setCrosshairCursor();

    this.getDocumentInterface().setClickMode(RAction.PickEntity);

    var appWin = RMainWindowQt.getMainWindow();
    this.setLeftMouseTip(qsTr("Choose entity on layer"));
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

SelectLayer.prototype.entityPickEvent = function(event) {
    this.matchingEntities = new Array();
    this.selectEntities(event.getEntityId());
    this.selectWithMode(this.matchingEntities);
};

SelectLayer.prototype.entityPickEventPreview = function(event) {
    this.di.highlightEntity(event.getEntityId());
};

