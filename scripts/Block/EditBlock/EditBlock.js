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
 * \class EditBlock
 * \ingroup ecma_block
 * \brief Edit selected block
 */
function EditBlock(guiAction) {
    Block.call(this, guiAction);
}

EditBlock.prototype = new Block();

EditBlock.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var blockList = EAction.getMainWindow().findChild("BlockList");
    if (isNull(blockList)) {
        this.terminate();
        return;
    }

    var item = BlockList.getActiveItem();
    if (isNull(item)) {
        this.terminate();
        return;
    }

    // don't display another block when activating one:
    blockList.blockSignals(true);

    this.editBlock(item.data(BlockList.colName, Qt.UserRole));

    blockList.blockSignals(false);

    this.terminate();
};
