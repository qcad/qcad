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

/**
 * \defgroup ecma_block Block Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of
 * block related tools.
 */
include("scripts/EAction.js");
include("scripts/Widgets/BlockList/BlockList.js");

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

Block.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="BlockToolsPanelAction") {
        EAction.showCadToolBarPanel("BlockToolsPanel");
        this.terminate();
    }
};

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

Block.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "BlockToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Block Tools"), mtb);
        action.setScriptFile(Block.includeBasePath + "/Block.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Block.includeBasePath + "/Block.svg");
        //action.setStatusTip(qsTr("Show block tools"));
        action.setDefaultShortcut(new QKeySequence("w,b"));
        action.setNoState();
        action.setDefaultCommands(["blockmenu"]);
        action.setGroupSortOrder(60);
        action.setSortOrder(100);
        action.setWidgetNames(["!MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Block.getTitle(),
        "BlockToolsPanel",
        true
    );
    return tb;
};

Block.getToolMatrixPanel = function() {
    RSettings.setValue("Block/VisibleInMatrixPanel", false, false);
    return EAction.getToolMatrixPanel(Block.getTitle(), "BlockMatrixPanel", 8000);
};

Block.getTitle = function() {
    return qsTr("&Block");
};

Block.prototype.getTitle = function() {
    return Block.getTitle();
};

Block.init = function() {
    Block.getMenu();
    Block.getToolBar();
    Block.getCadToolBarPanel();
    Block.getToolMatrixPanel();
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

    var list = blockList.selectedItems();
    if (list.length === 0) {
        return RObject.INVALID_ID;
    }

    var item = list[0];
    if (isNull(item)) {
        return RObject.INVALID_ID;
    }

    var document = EAction.getDocument();
    if (isNull(document)) {
        return RObject.INVALID_ID;
    }

    var blockId = document.getBlockId(item.data(BlockList.colName, Qt.UserRole));

    return blockId;
};

Block.showHide = function(show, action, blockId) {
    var op = new RModifyObjectsOperation();
    op.setText(action.getToolTitle());
    var blocks = action.getDocument().queryAllBlocks();
    for (var b = 0; b < blocks.length; ++b) {
        var block = action.getDocument().queryBlock(blocks[b]);
        if (blocks[b] !== blockId) {
            block.setFrozen(!show);
        } else {
            block.setFrozen(false);
        }
        op.addObject(block);
    }
    var di = action.getDocumentInterface();
    di.applyOperation(op);
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

    if (doc.isEditingWorkingSet()) {
        EAction.handleUserWarning(qsTr("Cannot edit block while editing a block in-place"));
        return;
    }

    // store offset and zoom factor of all views in a map blockId -> [factor, offset vector]:
    var blockId = doc.getCurrentBlockId();
    for (i=0; i<views.length; i++) {
        view = views[i];

        if (!isFunction(view.property)) {
            continue;
        }

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

        if (!isFunction(view.property)) {
            continue;
        }

        blockZoom = view.property("blockZoom");
        if (isNull(blockZoom)) {
            view.autoZoom(-1, true);
            continue;
        }

        if (isNull(blockZoom[blockId]) || blockZoom[blockId].length!==2) {
            view.autoZoom(-1, true);
        }
        else {
            view.setFactor(blockZoom[blockId][0]);
            view.setOffset(blockZoom[blockId][1]);
            //print("restored zoom for block: ", blockId, ", view: ", i, ", factor: ", view.getFactor());
        }
    }
};
