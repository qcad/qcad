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

    var item = blockList.currentItem();
    if (isNull(item)) {
        this.terminate();
        return;
    }

    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var views = this.getGraphicsViews();

    // don't display another block when activating one:
    blockList.blockSignals(true);

    var i, view, blockZoom;

    // store offset and zoom factor of all views in a map blockId -> [factor, offset vector]:
    var blockId = doc.getCurrentBlockId();
    for (i=0; i<views.length; i++) {
        view = views[i];

        blockZoom = view.property("blockZoom");
        if (isNull(blockZoom)) {
            blockZoom = new Object();
        }

        blockZoom[blockId] = [view.getFactor(), view.getOffset()];
        view.setProperty("blockZoom", blockZoom);
        //print("stored zoom for block: ", blockId, ", view: ", i, ", factor: ", view.getFactor());
    }

    // change current block that is being edited:
    di.setCurrentBlock(item.text());

    // restore offset and zoom factor for all views:
    blockId = doc.getCurrentBlockId();
    for (i=0; i<views.length; i++) {
        view = views[i];

        blockZoom = view.property("blockZoom");
        if (isNull(blockZoom)) {
            view.autoZoom();
            continue;
        }

        if (isNull(blockZoom[blockId]) || blockZoom[blockId].length!==2) {
            view.autoZoom();
        }
        else {
            view.setFactor(blockZoom[blockId][0]);
            view.setOffset(blockZoom[blockId][1]);
            //print("restored zoom for block: ", blockId, ", view: ", i, ", factor: ", view.getFactor());
        }
    }

    blockList.blockSignals(false);

    this.terminate();
};
