/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
include("../BlockDialog.js");

/**
 * \class CreateBlock
 * \ingroup ecma_block
 * \brief This action handles the user interaction to create a new block
 * from existing entities.
 */
function CreateBlock(guiAction) {
    Block.call(this, guiAction);

    this.referencePoint = undefined;
}

CreateBlock.prototype = new Block();

CreateBlock.State = {
    SettingPosition : 0
};

CreateBlock.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    this.setState(CreateBlock.State.SettingPosition);
};

CreateBlock.prototype.setState = function(state) {
    Block.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    this.setLeftMouseTip(qsTr("Reference Point"));
    this.setRightMouseTip(EAction.trCancel);

    EAction.showSnapTools();
};

CreateBlock.prototype.coordinateEvent = function(event) {
    var pos = event.getModelPosition();
    this.getDocumentInterface().setRelativeZero(pos);
    this.referencePoint = pos;

    var dlg = new BlockDialog(this.getDocument());
    var block = dlg.show();
    if (isNull(block)) {
        this.terminate();
        return;
    }

    var i, entity;
    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var storage = document.getStorage();
    var ids = document.querySelectedEntities();

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    op.addObject(block);

    var blockId;
    if (document.hasBlock(block.getName())) {
        // add selection to existing block:
        blockId = document.getBlockId(block.getName());

        // clear existing block:
        var oldIds = document.queryBlockEntities(blockId);
        for (i=0; i<oldIds.length; i++) {
            entity = document.queryEntity(oldIds[i]);
            if (isNull(entity)) {
                continue;
            }
            op.deleteObject(entity);
        }
    }
    else {
        // add selection to new block:
        blockId = storage.getMaxObjectId();
    }

    for (i=0; i<ids.length; i++) {
        var id = ids[i];

        // deselect original entity:
        di.deselectEntity(id);

        entity = document.queryEntity(id);
        if (isNull(entity)) {
            continue;
        }

        // move entity to new block:
        // note that the original entity is moved to the new block (same id)
        entity.setBlockId(blockId);

        // deselect entity which is part of the new block (avoid selected entities inside blocks):
        entity.move(pos.getNegated());

        op.addObject(entity, false);
    }

    // create block reference from selection:
    var blockReference = new RBlockReferenceEntity(document, new RBlockReferenceData(blockId, pos, new RVector(1,1,1), 0.0));
    blockReference.setSelected(true);
    op.addObject(blockReference, false);

    di.applyOperation(op);

    this.terminate();
};
