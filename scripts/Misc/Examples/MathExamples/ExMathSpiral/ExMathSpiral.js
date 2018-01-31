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

include("../MathExamples.js");

/**
 * \ingroup ecma_misc_examples_mathexamples
 * \class ExMathSpiral
 * This action draws a simple spiral (center at 0/0).
 */
function ExMathSpiral(guiAction) {
    MathExamples.call(this, guiAction);
}

ExMathSpiral.prototype = new MathExamples();

/**
 * Draws a spiral and terminates.
 */
ExMathSpiral.prototype.beginEvent = function() {
    MathExamples.prototype.beginEvent.call(this);

    var document = this.getDocument();
    var di = this.getDocumentInterface();

    var operation = new RAddObjectsOperation(true);
    var r = 0;
    var aDelta = 2 * Math.PI / 100;
    var rDelta = 0.01;
    var c = 0;

    for (var a = 0.0; a < 10 * Math.PI; a += aDelta) {
        var lineData = new RLineData(
                new RVector(
                    Math.cos(a) * r, 
                    Math.sin(a) * r
                ),
                new RVector(
                    Math.cos(a + aDelta) * (r+rDelta), 
                    Math.sin(a + aDelta) * (r+rDelta)
                )
            );
        var line = new RLineEntity(document, lineData);
        operation.addObject(line);
        ++c;
        r += rDelta;
    }
    di.applyOperation(operation);

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/Spiral.
 */
ExMathSpiral.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Spiral"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExMathSpiral.js");
    action.setGroupSortOrder(79700);
    action.setSortOrder(100);
    action.setWidgetNames(["MathExamplesMenu"]);
};
