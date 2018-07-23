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
include("scripts/Widgets/BlockList/BlockList.js");
 
/**
 * \class SelectBlockReferences
 * \ingroup ecma_block
 * \brief Select block references from block.
 */
function SelectBlockReferences(guiAction) {
    Block.call(this, guiAction);
}

SelectBlockReferences.prototype = new Block();

SelectBlockReferences.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var doc = this.getDocument();
    var di = this.getDocumentInterface();

    var item = BlockList.getActiveItem();
    if (isNull(item)) {
        this.terminate();
        return;
    }

    var blockId = doc.getBlockId(item.data(BlockList.colName, Qt.UserRole));
    if (blockId===RObject.INVALID_ID) {
        this.terminate();
        return;
    }

    var ids = doc.queryBlockReferences(blockId);
    di.selectEntities(ids, true);

    this.terminate();
};

