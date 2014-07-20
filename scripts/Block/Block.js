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

/**
 * \defgroup ecma_block Block Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of
 * block related tools.
 */
include("../EAction.js");

/**
 * \class Block
 * \ingroup ecma_block
 * \brief Base class for block tools.
 */
function Block(guiAction) {
    EAction.call(this, guiAction);
}

Block.prototype = new EAction();
Block.includeBasePath = includeBasePath;

Block.getMenu = function() {
    var menu = EAction.getMenu(Block.getTitle(), "BlockMenu");
    menu.setProperty("scriptFile", Block.includeBasePath + "/Block.js");
    return menu;
};

Block.getToolBar = function() {
    var tb = EAction.getToolBar(Block.getTitle(), "BlockToolBar");
    tb.visible = false;
    return tb;
};

Block.getTitle = function() {
    return qsTr("&Block");
};

Block.prototype.getTitle = function() {
    return Block.getTitle();
};

/**
 * \return The ID of the block that is currently highlighted (selected) in
 * the block list. This is usually not that block that is currently being edited.
 */
Block.getActiveBlockId = function() {
    var blockList = EAction.getMainWindow().findChild("BlockList");
    if (isNull(blockList)) {
        return RObject.INVALID_ID;
    }

    var item = blockList.currentItem();
    if (isNull(item)) {
        return RObject.INVALID_ID;
    }

    var document = EAction.getDocument();
    if (isNull(document)) {
        return RObject.INVALID_ID;
    }

    var blockId = document.getBlockId(item.text());

    return blockId;
};

Block.showHide = function(show, obj, blockId) {
    var operation = new RModifyObjectsOperation();
    var blocks = obj.getDocument().queryAllBlocks();
    for (var b = 0; b < blocks.length; ++b) {
        var block = obj.getDocument().queryBlock(blocks[b]);
        if (blocks[b] != blockId) {
            block.setFrozen(!show);
        } else {
            block.setFrozen(false);
        }
        operation.addObject(block);
    }
    var di = obj.getDocumentInterface();
    di.applyOperation(operation);
    di.clearPreview();
    di.repaintViews();
};

/**
 * Makes the given block the one that is being edited. This method
 * stores / restores the zoom and zoom offset per block.
 */
Block.prototype.editBlock = function(blockName) {
    var di = this.getDocumentInterface();
    //var doc = this.getDocument();
    //var views = this.getGraphicsViews();

    Block.editBlock(di, blockName);
};

Block.editBlock = function(di, blockName) {
    var doc = di.getDocument();
    var views = EAction.getGraphicsViews(di);

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
    di.setCurrentBlock(blockName);

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
};
