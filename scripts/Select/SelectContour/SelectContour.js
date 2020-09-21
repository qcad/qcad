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
 * \class SelectContour
 * \ingroup ecma_select
 * \brief Select connected entities.
 */
function SelectContour(guiAction) {
    Select.call(this, guiAction);

    this.tolerance = 0.0;
    this.sameLayer = false;

    this.setUiOptions("SelectContour.ui");
}

SelectContour.prototype = new Select();

SelectContour.State = {
    ChoosingEntity : 0
};

SelectContour.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);

    this.setState(SelectContour.State.ChoosingEntity);
};

SelectContour.prototype.setState = function(state) {
    var di = this.getDocumentInterface();
    di.setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    var tr = qsTr("Choose entity of contour");
    this.setLeftMouseTip(tr);
    this.setCommandPrompt(tr);
    this.setRightMouseTip(EAction.trCancel);
};

SelectContour.prototype.entityPickEvent = function(event) {
    this.selectEntities(this.getEntityId(event, false));
};

SelectContour.prototype.selectEntities = function(entityId) {
    var doc = this.getDocument();
    var layerId = RObject.INVALID_ID;
    if (this.sameLayer) {
        var e = doc.queryEntityDirect(entityId);
        if (!isNull(e)) {
            layerId = e.getLayerId();
        }
    }

    var matchingEntities = SelectContour.getConnectedEntities(doc, entityId, this.tolerance, layerId);
    this.selectWithMode(matchingEntities);
};

SelectContour.prototype.entityPickEventPreview = function(event) {
    var di = this.getDocumentInterface();
    var id = this.getEntityId(event, true);
    di.highlightEntity(id);
};

SelectContour.prototype.slotToleranceChanged = function(value) {
    this.tolerance = value;
};

SelectContour.prototype.slotSameLayerChanged = function(value) {
    this.sameLayer = value;
};

/**
 * \return Array of entity IDs of entities which are directly or indirectly
 * connected to the given entity, including the given entityId.
 */
SelectContour.getConnectedEntities = function(doc, entityId, tolerance, layerId) {
    if (isNull(layerId)) {
        layerId = RObject.INVALID_ID;
    }

    return doc.queryConnectedEntities(entityId, tolerance, layerId);
};
