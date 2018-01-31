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
include("../DrawExamples.js");

/**
 * \class ExText
 * \ingroup ecma_misc_examples_draw
 * Adds a text entity to the drawing.
 */
function ExText(guiAction) {
    DrawExamples.call(this, guiAction);
}

ExText.prototype = new DrawExamples();

ExText.prototype.beginEvent = function() {
    DrawExamples.prototype.beginEvent.call(this);

    var pos = new RVector(5,10)

    // create an operation for adding objects:
    var op = new RAddObjectsOperation();
    // create a text entity and add it to the operation:
    var text = new RTextEntity(
        this.getDocument(),
        new RTextData(
              pos,                 // position
              pos,                 // alignment point
              2.0,                 // height
              2.0,                 // text width (ignored for now)
              RS.VAlignTop,        // alignments
              RS.HAlignCenter,
              RS.LeftToRight,
              RS.Exact,
              1.0,                 // line spacing factor
              "Test",              // the text
              "Arial",      // font
              false,        // bold
              false,        // italic
              0.0,          // angle
              false         // simple text without formatting
        )
    );
    op.addObject(text);

    // apply the operation to the current drawing:
    this.getDocumentInterface().applyOperation(op);

    this.terminate();
};

ExText.init = function(basePath) {
    var action = new RGuiAction(qsTr("Text"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExText.js");
    action.setStatusTip(qsTr("Draw text"));
    action.setGroupSortOrder(73100);
    action.setSortOrder(300);
    action.setWidgetNames(["DrawExamplesMenu"]);
};
