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
 * \class ExDrawFonts
 * \ingroup ecma_misc_examples_draw
 * Adds a text entity for every CAD font available on the system.
 */
function ExDrawFonts(guiAction) {
    DrawExamples.call(this, guiAction);
}

ExDrawFonts.prototype = new DrawExamples();

ExDrawFonts.prototype.beginEvent = function() {
    DrawExamples.prototype.beginEvent.call(this);

    var x = 0;
    var y = 10;

    // create an operation for adding objects:
    var op = new RAddObjectsOperation();

    var fontNames = RFontList.getNames();

    for (var i=0; i<fontNames.length; i++) {
        var fontName = fontNames[i];

        if (y<0) {
            y = 10;
            x += 30;
        }

        // create a text entity and add it to the operation:
        var text = new RTextEntity(
            this.getDocument(),
            new RTextData(
                  new RVector(x,y),    // position
                  new RVector(x,y),    // alignment point
                  1.0,                 // height
                  1.0,                 // text width (ignored for now)
                  RS.VAlignTop,        // alignments
                  RS.HAlignCenter,
                  RS.LeftToRight,
                  RS.Exact,
                  1.0,                 // line spacing factor
                  "Abcdefg (" + fontName + ")",  // the text
                  fontName,     // font
                  false,        // bold
                  false,        // italic
                  0.0,          // angle
                  false         // simple text without formatting
            )
        );
        op.addObject(text);

        y-=2;
    }


    // apply the operation to the current drawing:
    this.getDocumentInterface().applyOperation(op);

    this.terminate();
};

ExDrawFonts.init = function(basePath) {
    var action = new RGuiAction(qsTr("Draw &Fonts"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExDrawFonts.js");
    action.setGroupSortOrder(73100);
    action.setSortOrder(400);
    action.setWidgetNames(["DrawExamplesMenu"]);
};
