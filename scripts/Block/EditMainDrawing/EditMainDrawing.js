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
 * \class EditMainDrawing
 * \ingroup ecma_block
 * \brief Back to model space block
 */
function EditMainDrawing(guiAction) {
    Block.call(this, guiAction);
}

EditMainDrawing.prototype = new Block();

EditMainDrawing.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var blockList = EAction.getMainWindow().findChild("BlockList");
    if (isNull(blockList)) {
        this.terminate();
        return;
    }

    // don't display another block when activating one:
    blockList.blockSignals(true);
    //this.getDocumentInterface().setCurrentBlock(RBlock.modelSpaceName);
    this.editBlock(RBlock.modelSpaceName);
    blockList.blockSignals(false);

    this.terminate();
};

