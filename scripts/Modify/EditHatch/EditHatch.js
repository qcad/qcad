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

/**
 * \ingroup ecma_modify
 *
 * \brief This module contains the ECMAScript implementation of the hatch
 * editing tool.
 */
include("scripts/Modify/Modify.js");
include("scripts/Draw/Hatch/HatchDialog.js");

/**
 * \class EditHatch
 * \brief Edit hatch.
 * \ingroup ecma_modify
 */
function EditHatch(guiAction) {
    Modify.call(this, guiAction);

    this.entity = undefined;
}

EditHatch.prototype = new Modify();

EditHatch.State = {
    ChoosingEntity : 0
};

EditHatch.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(EditHatch.State.ChoosingEntity);
};

EditHatch.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case EditHatch.State.ChoosingEntity:
        var tr = qsTr("Choose hatch");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

EditHatch.prototype.pickEntity = function(event, preview) {
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);

    if (isNull(entity)) {
        this.entity = undefined;
        this.updatePreview();
        return;
    }

    switch (this.state) {
    case EditHatch.State.ChoosingEntity:
        if (isHatchEntity(entity)) {
            this.entity = entity;
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            EditHatch.editHatch(entity);
        }
        break;
    }
};

EditHatch.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

/**
 * This static method may also be accessed by other tools to edit the
 * given hatch entity in a hatch dialog.
 */
EditHatch.editHatch = function(entity) {
    if (!isHatchEntity(entity)) {
        return;
    }

    var dialog = new HatchDialog();
    var hatchData = dialog.show(entity.getData());
    if (isNull(hatchData)) {
        // dialog canceled:
        return;
    }

    var newEntity = entity.clone();
    newEntity.setData(hatchData);

    var op = new RModifyObjectOperation(newEntity);
    if (!isNull(op)) {
        var di = EAction.getDocumentInterface();
        di.applyOperation(op);
        di.selectEntity(entity.getId());
    }
};

