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
 * \class ToggleBlockVisibility
 * \ingroup ecma_block
 * \brief Toggle block visibility.
 */
function ToggleBlockVisibility(guiAction) {
    Block.call(this, guiAction);
}

ToggleBlockVisibility.prototype = new Block();

ToggleBlockVisibility.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var blockId = Block.getActiveBlockId();
    if (blockId===RObject.INVALID_ID) {
        this.terminate();
        return;
    }

    var block = this.getDocument().queryBlock(blockId);
    block.setFrozen(!block.isFrozen());

    var operation = new RModifyObjectOperation(block);
    var di = this.getDocumentInterface();
    di.applyOperation(operation);

    this.terminate();
};

