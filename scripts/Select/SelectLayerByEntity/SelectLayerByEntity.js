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

include("scripts/Select/Select.js");

/**
 * \class SelectLayerByEntity
 * \ingroup ecma_select
 * \brief Select all entities on the same layer.
 */
function SelectLayerByEntity(guiAction) {
    Select.call(this, guiAction);

    this.setUiOptions("SelectLayerByEntity.ui");
}

SelectLayerByEntity.prototype = new Select();

SelectLayerByEntity.State = {
    ChoosingEntity : 0
};

SelectLayerByEntity.prototype.selectEntities = function(entityId) {
    var entity = this.doc.queryEntity(entityId);
    if (isNull(entity)) {
        return;
    }

    var layerId = entity.getLayerId();

    // select all entities on the same layer:
    this.matchingEntities = this.doc.queryLayerEntities(layerId);
};


SelectLayerByEntity.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);

    this.doc = this.getDocument();
    this.di = this.getDocumentInterface();

    this.setState(SelectLayerByEntity.State.ChoosingEntity);
};

SelectLayerByEntity.prototype.setState = function(state) {
    Select.prototype.setState.call(this, state);
    this.setCrosshairCursor();

    this.getDocumentInterface().setClickMode(RAction.PickEntity);

    var appWin = RMainWindowQt.getMainWindow();
    var tr = qsTr("Choose entity on layer");
    this.setLeftMouseTip(tr);
    this.setCommandPrompt(tr);
    this.setRightMouseTip(EAction.trCancel);
};

SelectLayerByEntity.prototype.entityPickEvent = function(event) {
    this.matchingEntities = [];
    this.selectEntities(this.getEntityId(event, false));
    this.selectWithMode(this.matchingEntities);
};

SelectLayerByEntity.prototype.entityPickEventPreview = function(event) {
    this.di.highlightEntity(this.getEntityId(event, true));
};

