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
include("../BlockDialog.js");

/**
 * \class RenameBlock
 * \ingroup ecma_block
 * \brief Renames the active (selected) block.
 */
function RenameBlock(guiAction, blockId) {
    Block.call(this, guiAction);

    if (isNull(blockId)) {
        blockId = RObject.INVALID_ID;
    }

    this.blockId = blockId;
}

RenameBlock.prototype = new Block();

RenameBlock.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var blockId;
    if (this.blockId!==RObject.INVALID_ID) {
        blockId = this.blockId;
    }
    else {
        blockId = Block.getActiveBlockId();
    }

    if (blockId===RObject.INVALID_ID) {
        this.terminate();
        return;
    }

    var doc = this.getDocument();

    var block = doc.queryBlock(blockId);
    if (isNull(block)) {
        this.terminate();
        return;
    }

    var oldBlockName = block.getName();

    var dlg = this.createDialog(doc, block);
    if (isNull(dlg)) {
        this.terminate();
        return;
    }

    var newBlock = dlg.show();
    if (isNull(newBlock)) {
        this.terminate();
        return;
    }

    this.renameBlock(oldBlockName, newBlock, false);

    this.terminate();
};

RenameBlock.prototype.renameBlock = function(oldBlockName, newBlock, useTransactionGroup) {
    var op = new RAddObjectOperation(newBlock);
    op.setText(this.getToolTitle());
    var di = this.getDocumentInterface();
    var doc = di.getDocument();
    if (useTransactionGroup) {
        op.setTransactionGroup(doc.getTransactionGroup());
    }
    di.applyOperation(op);
    di.clearPreview();
    di.repaintViews();
};

RenameBlock.prototype.createDialog = function(doc, block) {
    return new BlockDialog(doc, block, true, true);
};
