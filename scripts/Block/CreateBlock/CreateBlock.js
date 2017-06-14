/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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
    var referencePoint = event.getModelPosition();
    this.getDocumentInterface().setRelativeZero(referencePoint);

    var dlg = new BlockDialog(this.getDocument());
    var block = dlg.show();
    if (isNull(block)) {
        this.terminate();
        return;
    }

    var di = this.getDocumentInterface();
    var doc = di.getDocument();
    var ids = doc.querySelectedEntities();
    CreateBlock.createBlock(di, block, referencePoint, ids, this.getToolTitle(), true);

    this.terminate();
};

/**
 * Adds the given block to the drawing based on the given entities.
 *
 * \param di RDocumentInterface
 * \param block RBlock block data.
 * \param referencePoint RVector reference point for block reference.
 * \param entityIds Entity IDs.
 * \param title Tool title (used for transaction log).
 * \param select True to select created block reference.
 * \param copy True to copy the entities into the new block, false to move entities.
 * \param createReference True to create a block reference in place of the entities.
 */
CreateBlock.createBlock = function(di, block, referencePoint, entityIds, title, select, copy, createReference) {
    if (isNull(select)) {
        select = false;
    }
    if (isNull(copy)) {
        copy = false;
    }
    if (isNull(createReference)) {
        createReference = true;
    }

    var i, entity;
    var doc = di.getDocument();
    var storage = doc.getStorage();

    var op = new RAddObjectsOperation();
    op.setText(title);
    op.addObject(block);

    var blockId;
    if (doc.hasBlock(block.getName())) {
        // add selection to existing block / overwrite block:
        blockId = doc.getBlockId(block.getName());

        // clear existing block:
        var oldIds = doc.queryBlockEntities(blockId);
        for (i=0; i<oldIds.length; i++) {
            entity = doc.queryEntity(oldIds[i]);
            if (isNull(entity)) {
                continue;
            }
            op.deleteObject(entity);
        }
    }
    else {
        blockId = storage.getMaxObjectId();
    }

    // add selection to new block:
    for (i=0; i<entityIds.length; i++) {
        var id = entityIds[i];

        // deselect original entity:
        di.deselectEntity(id);

        entity = doc.queryEntity(id);
        if (isNull(entity)) {
            continue;
        }

        // move entity to new block:
        // note that the original entity is moved to the new block (same id)
        entity.setBlockId(blockId);

        entity.move(referencePoint.getNegated());

        op.addObject(entity, false, copy);
    }

    // create block reference from selection:
    var blockReference = undefined;
    if (createReference) {
        blockReference = new RBlockReferenceEntity(doc, new RBlockReferenceData(blockId, referencePoint, new RVector(1,1,1), 0.0));
        if (select) {
            blockReference.setSelected(true);
        }
        op.addObject(blockReference, false);
    }

    di.applyOperation(op);

    if (isNull(blockReference)) {
        return RObject.INVALID_ID;
    }
    else {
        return blockReference.getId();
    }
};
