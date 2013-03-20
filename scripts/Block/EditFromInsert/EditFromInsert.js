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

include("../Block.js");

/**
 * \class EditFromInsert
 * \brief Edits the block that is referenced by the insert (reference)
 * the user clicks.
 * \ingroup ecma_draw_line
 */
function EditFromInsert(guiAction) {
    Block.call(this, guiAction);

    this.entity = undefined;
}

EditFromInsert.prototype = new Block();

EditFromInsert.State = {
    ChoosingEntity : 0
};

EditFromInsert.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    this.setState(EditFromInsert.State.ChoosingEntity);
};

EditFromInsert.prototype.setState = function(state) {
    Block.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case EditFromInsert.State.ChoosingEntity:
        this.setLeftMouseTip(qsTr("Choose block reference"));
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

EditFromInsert.prototype.escapeEvent = function() {
    switch (this.state) {
    case EditFromInsert.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

EditFromInsert.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);

    if (isNull(entity)) {
        return;
    }

    switch (this.state) {
    case EditFromInsert.State.ChoosingEntity:
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
            di.setCurrentBlock(blockName);

            this.terminate();
        }
        break;
    }
};

EditFromInsert.prototype.getHighlightedEntities = function() {
    var ret = new Array();
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};


