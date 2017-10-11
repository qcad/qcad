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
include("../LayoutDialog.js");

/**
 * \class RenameBlock
 * \ingroup ecma_block
 * \brief Renames the active (selected) block.
 */
function RenameBlock(guiAction) {
    Block.call(this, guiAction);
}

RenameBlock.prototype = new Block();

RenameBlock.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var blockId = Block.getActiveBlockId();
    if (blockId===RObject.INVALID_ID) {
        this.terminate();
        return;
    }

    var doc = this.getDocument();
    var dlg;

    var block = doc.queryBlock(blockId);
    if (block.hasLayout()) {
        var layoutId = block.getLayoutId();
        var layout = doc.queryLayout(layoutId);
        if (isNull(layout)) {
            this.terminate();
            return;
        }
        dlg = new LayoutDialog(doc, layout);
    }
    else {
        dlg = new BlockDialog(doc, block);
    }

    var newBlockOrLayout = dlg.show();
    if (isNull(newBlockOrLayout)) {
        this.terminate();
        return;
    }

    var op = new RAddObjectOperation(newBlockOrLayout);
    op.setText(this.getToolTitle());
    var di = this.getDocumentInterface();
    di.applyOperation(op);
    di.clearPreview();
    di.repaintViews();

    this.terminate();
};
