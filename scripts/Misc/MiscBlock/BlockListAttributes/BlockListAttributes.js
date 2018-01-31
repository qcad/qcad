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

include("../MiscBlock.js");

/**
 * \class BlockListAttributes
 * \brief This action lists all block references with attributes to the command line history.
 * \ingroup ecma_misc_block
 */
function BlockListAttributes(guiAction) {
    MiscBlock.call(this, guiAction);
}

BlockListAttributes.prototype = new MiscBlock();

BlockListAttributes.prototype.beginEvent = function() {
    MiscBlock.prototype.beginEvent.call(this);

    var doc = this.getDocument();

    // iterate through all block definitions:
    var blockIds = doc.queryAllBlocks();
    for (var i=0; i<blockIds.length; ++i) {
        var blockId = blockIds[i];
        var block = doc.queryBlock(blockId);
        if (isNull(block)) {
            continue;
        }

        EAction.handleUserMessage(qsTr("Block:") + " " + block.getName());

        // iterate through all block references of the current block:
        var blockRefIds = doc.queryBlockReferences(blockId);
        for (var k=0; k<blockRefIds.length; ++k) {
            var blockRefId = blockRefIds[k];
            EAction.handleUserMessage("  " + qsTr("Block reference ID:") + " " + blockRefId);

            // iterate through all attributes of the current block reference:
            var attributeIds = doc.queryChildEntities(blockRefId, RS.EntityAttribute);
            for (var c=0; c<attributeIds.length; c++) {
                var attributeId = attributeIds[c];
                var attribute = doc.queryEntityDirect(attributeId);
                if (attribute.isNull()) {
                    continue;
                }

                EAction.handleUserMessage("    " + qsTr("Block attribute:") + " " + attribute.getTag() + ": " + attribute.getPlainText());
            }
        }
    }

    this.terminate();
};

/**
 * Adds a menu for this action to the Misc menu.
 */
BlockListAttributes.init = function(basePath) {
    var action = new RGuiAction(qsTr("&List Block Attributes"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/BlockListAttributes.js");
    action.setGroupSortOrder(60100);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscBlockMenu", "MiscBlockToolBar", "MiscBlockToolsPanel"]);
};
