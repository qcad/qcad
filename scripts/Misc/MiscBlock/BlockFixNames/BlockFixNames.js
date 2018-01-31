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
 * This action fixes invalid block names from imported drawings.
 */
function BlockFixNames(guiAction) {
    MiscBlock.call(this, guiAction);
}

BlockFixNames.prototype = new MiscBlock();

/**
 * Renames blocks and terminates.
 */
BlockFixNames.prototype.beginEvent = function() {
    MiscBlock.prototype.beginEvent.call(this);

    var document = this.getDocument();
    var di = this.getDocumentInterface();

    var operation = new RModifyObjectsOperation();

    var blockIds = document.queryAllBlocks();
    for (var i=0; i<blockIds.length; i++) {
        var blockId = blockIds[i];

        var block = document.queryBlock(blockId);
        var name = block.getName();
        if (!name.startsWith("*")) {
            continue;
        }

        var nameUpper = name.toUpperCase();

        if (nameUpper===RBlock.modelSpaceName.toUpperCase() ||
            nameUpper.startsWith("*PAPER_SPACE")) {
            continue;
        }

        name = name.substring(1);
        var nameBase = name;

        var c = 1;
        while (document.hasBlock(name)) {
            name = nameBase + '_' + c++;
        }

        block.setName(name);
        operation.addObject(block);
    }

    di.applyOperation(operation);

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/BlockFixNames.
 */
BlockFixNames.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Fix Block Names"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/BlockFixNames.js");
    action.setGroupSortOrder(60100);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscBlockMenu", "MiscBlockToolBar", "MiscBlockToolsPanel"]);
};
