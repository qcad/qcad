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
 * \brief This module contains the ECMAScript implementation of the text
 * editing tool.
 */
include("scripts/Modify/Modify.js");
include("scripts/Draw/Text/TextDialog/TextDialog.js");

/**
 * \class EditText
 * \brief Edit text.
 * \ingroup ecma_modify
 */
function EditText(guiAction) {
    Modify.call(this, guiAction);

    this.entity = undefined;
}

EditText.prototype = new Modify();

EditText.State = {
    ChoosingEntity : 0
};

EditText.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(EditText.State.ChoosingEntity);
};

EditText.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case EditText.State.ChoosingEntity:
        var tr = qsTr("Choose text")
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

EditText.prototype.pickEntity = function(event, preview) {
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);

    if (isNull(entity)) {
        this.entity = undefined;
        this.updatePreview();
        return;
    }

    switch (this.state) {
    case EditText.State.ChoosingEntity:
        if (isTextEntity(entity) ||
            isAttributeEntity(entity) ||
            isAttributeDefinitionEntity(entity)) {

            this.entity = entity;
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            EditText.editText(entity);
        }
        break;
    }
};

EditText.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

/**
 * This static method may also be accessed by other tools to edit the
 * given text entity in a text dialog.
 */
EditText.editText = function(entity) {
    if (!isTextEntity(entity) &&
        !isAttributeEntity(entity) &&
        !isAttributeDefinitionEntity(entity)) {
        return;
    }

    var dialog = new TextDialog();
    var textData = dialog.show(entity.getData());
    if (isNull(textData)) {
        // dialog canceled:
        return;
    }

    var newEntity = entity.clone();
    newEntity.setData(textData);

    var op = new RModifyObjectOperation(newEntity);
    if (!isNull(op)) {
        var di = EAction.getDocumentInterface();
        di.applyOperation(op);
        di.selectEntity(entity.getId());
    }
};

