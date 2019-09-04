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

include("scripts/EAction.js");
include("scripts/simple.js");

/**
 * \ingroup ecma_misc_examples_mathexamples
 * \class ExMandelbrot
 * This action plots the Mandelbrot set.
 */
function ExMandelbrot(guiAction) {
    EAction.call(this, guiAction);
}

ExMandelbrot.prototype = new EAction();

/**
 * Draws Mandelbrot set.
 */
ExMandelbrot.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    startTransaction(this.getDocumentInterface());
    mandelbrot(-2, -1, 1, 1, 100);
    endTransaction();

    this.terminate();
};

ExMandelbrot.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Mandelbrot Example"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExMandelbrot.js");
    action.setGroupSortOrder(79700);
    action.setSortOrder(200);
    action.setWidgetNames(["MathExamplesMenu"]);
};


function mandelIter(cx, cy, maxIter) {
    var x = 0.0;
    var y = 0.0;
    var xx = 0;
    var yy = 0;
    var xy = 0;

    var i = maxIter;
    while (i-- && xx + yy <= 4) {
        xy = x * y;
        xx = x * x;
        yy = y * y;
        x = xx - yy + cx;
        y = xy + xy + cy;
    }
    return maxIter - i;
}

function mandelbrot(xmin, ymin, xmax, ymax, iterations) {
    var r,g,b;
    var res = 0.01;
    var factor=5;

    for (var x = xmin; x < xmax; x+=res) {
        qDebug(x);
        for (var y = ymin; y < ymax; y+=res) {
            var i = mandelIter(x, y, iterations);

            if (i > iterations) {
                r = 0;
                g = 0;
                b = 0;
            } else {
                var c = 3 * Math.log(i) / Math.log(iterations - 1.0);

                if (c < 1) {
                    r = 255 * c;
                    g = 0;
                    b = 0;
                }
                else if ( c < 2 ) {
                    r = 255;
                    g = 255 * (c - 1);
                    b = 0;
                } else {
                    r = 255;
                    g = 255;
                    b = 255 * (c - 2);
                }
            }

            var color = new RColor(r,g,b);
            var pt = new RPoint(new RVector(x*factor, y*factor, 0));
            addShape(pt, color, "CONTINUOUS", RLineweight.Weight005);
        }
    }
}
