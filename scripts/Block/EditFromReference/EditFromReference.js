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

include("scripts/Block/Block.js");

/**
 * \class EditFromReference
 * \brief Edits the block that is referenced by the block reference
 * the user clicks.
 * \ingroup ecma_block
 */
function EditFromReference(guiAction) {
    Block.call(this, guiAction);

    this.entity = undefined;
}

EditFromReference.prototype = new Block();

EditFromReference.State = {
    ChoosingEntity : 0
};

EditFromReference.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    this.setState(EditFromReference.State.ChoosingEntity);
};

EditFromReference.prototype.setState = function(state) {
    Block.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case EditFromReference.State.ChoosingEntity:
        var tr = qsTr("Choose block reference");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

EditFromReference.prototype.escapeEvent = function() {
    switch (this.state) {
    case EditFromReference.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

EditFromReference.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);

    if (isNull(entity)) {
        return;
    }

    switch (this.state) {
    case EditFromReference.State.ChoosingEntity:
        if (isBlockReferenceEntity(entity)) {
            this.entity = entity;
        }
        else {
            if (!preview) {
                EAction.warnNotBlockReference();
            }
            break;
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            var blockName = entity.getReferencedBlockName();
            //di.setCurrentBlock(blockName);
            this.editBlock(blockName);

            this.terminate();
        }
        break;
    }
};

EditFromReference.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};


