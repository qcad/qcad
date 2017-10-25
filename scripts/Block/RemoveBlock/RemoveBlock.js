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
include("scripts/library.js");
include("scripts/Widgets/BlockList/BlockList.js");

/**
 * \class RemoveBlock
 * \ingroup ecma_block
 * \brief Remove the selected block.
 */
function RemoveBlock(guiAction) {
    Block.call(this, guiAction);
}

RemoveBlock.prototype = new Block();

RemoveBlock.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var blockList = EAction.getMainWindow().findChild("BlockList");
    if (isNull(blockList)) {
        this.terminate();
        return;
    }

    var item = blockList.currentItem();
    if (isNull(item)) {
        this.terminate();
        return;
    }

    var di = this.getDocumentInterface();
    var doc = di.getDocument();

    var block = doc.queryBlock(item.data(BlockList.colName, Qt.UserRole));

    if (isNull(block)) {
        this.terminate();
        return;
    }

    if (block.getId()===doc.getCurrentBlockId()) {
        // deleting current block: activate model space:
        Block.editBlock(di, doc.getBlockName(doc.getModelSpaceBlockId()));
    }

    var op = new RDeleteObjectOperation(block);
    op.setText(this.getToolTitle());
    di.applyOperation(op);
    di.clearPreview();
    di.repaintViews();

    this.terminate();
};

