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
 * \class ExDrawColors
 * \ingroup ecma_misc_examples_draw
 * This action draws lines in different colors.
 */
function ExDrawColors(guiAction) {
    DrawExamples.call(this, guiAction);
}

ExDrawColors.prototype = new DrawExamples();

/**
 * Draws lines in different colors and terminates.
 */
ExDrawColors.prototype.beginEvent = function() {
    DrawExamples.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var op = new RAddObjectsOperation();

    for (var h=0; h<=255; h+=16) {
        for (var v=0; v<=255; v+=16) {
            for (var s=0; s<=255; s+=16) {
                var line = new RLine(new RVector(h/16, v/16+s), new RVector(h/16, v/16+s+0.5));
                var lineEntity = new RLineEntity(document, new RLineData(line));
                var c = new RColor();
                c.setHsv(h,s,v);
                lineEntity.setColor(c);
                op.addObject(lineEntity, false);
            }
        }
    }

    di.applyOperation(op);

    this.terminate();
};

/**
 * Adds a menu for this action.
 */
ExDrawColors.init = function(basePath) {
    var action = new RGuiAction(qsTr("Draw &Colors"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExDrawColors.js");
    action.setGroupSortOrder(73100);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawExamplesMenu"]);
};
