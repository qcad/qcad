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

include("../BlockExamples.js");

/**
 * \ingroup ecma_misc_examples_block
 * \class ExAddBlock
 * This action adds a block called 'MyBlock' with a line and an arc as contents.
 * A block reference is also inserted into the main drawing.
 */
function ExAddBlock(guiAction) {
    BlockExamples.call(this, guiAction);
}

ExAddBlock.prototype = new BlockExamples();

/**
 * Adds a block and terminates.
 */
ExAddBlock.prototype.beginEvent = function() {
    BlockExamples.prototype.beginEvent.call(this);

    var document = this.getDocument();
    var di = this.getDocumentInterface();

    // create new block definition:
    var block = new RBlock(document, "MyBlock", new RVector(0,0));
    var operation = new RAddObjectOperation(block);
    di.applyOperation(operation);

    // make new block the current block:
    di.setCurrentBlock("MyBlock");

    // add a line and an arc to the block definition:
    var p1 = new RVector(0,0);
    var p2 = new RVector(50,0);

    var line = new RLineEntity(document, new RLineData(p1, p2));
    var center = new RVector(25,0);
    var radius = 25;
    var arc = new RArcEntity(document, new RArcData(center, radius, 0.0, Math.PI, false));

    operation = new RAddObjectsOperation();
    operation.addObject(line);
    operation.addObject(arc);
    di.applyOperation(operation);

    // switch back to main drawing (block "*Model_Space"):
    di.setCurrentBlock(RBlock.modelSpaceName);

    // create block reference in main drawing at 10/20, scale 1, angle 30:
    var position = new RVector(10,20);
    var scale = new RVector(1,1);
    var angle = RMath.deg2rad(30);
    var blockId = document.getBlockId("MyBlock");
    var blockRef = new RBlockReferenceEntity(document, new RBlockReferenceData(blockId, position, scale, angle));

    operation = new RAddObjectOperation(blockRef);
    di.applyOperation(operation);

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/ExAddBlock.
 */
ExAddBlock.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Create Block"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExAddBlock.js");
    action.setGroupSortOrder(79100);
    action.setSortOrder(100);
    action.setWidgetNames(["BlockExamplesMenu"]);
};
