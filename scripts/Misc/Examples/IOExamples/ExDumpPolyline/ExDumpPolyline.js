/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

include("../IOExamples.js");

/**
 * This action dumps all selected polylines as plain text into the 
 * command line history.
 */
function ExDumpPolyline(guiAction) {
    IOExamples.call(this, guiAction);
}

ExDumpPolyline.prototype = new IOExamples();

ExDumpPolyline.prototype.beginEvent = function() {
    IOExamples.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var ids = document.querySelectedEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);

        if (isPolylineEntity(entity)) {
            EAction.handleUserMessage("Clockwise polyline dump:");

            if (!ExDumpPolyline.isClockwise(entity)) {
                EAction.handleUserWarning("Polyline not clockwise: reversing.");
                entity.reverse();
            }

            var n = entity.countVertices();
            for (var k=0; k<n; k++) {
                var v = entity.getVertexAt(k);
                EAction.handleUserMessage("%1,%2,".arg(v.x).arg(-v.y));
            }
        }
    }

    this.terminate();
};

ExDumpPolyline.isClockwise = function(polyline) {
    var n = polyline.countVertices();

    // find minimum vertex:
    var vMin = RVector.invalid;
    var vBefore, vAfter;
    for (var i=0; i<n; i++) {
        var v = polyline.getVertexAt(i);
        if (!vMin.isValid() || v.x<vMin.x || (v.x==vMin.x && v.y<vMin.y)) {
            vMin = v;
            vBefore = polyline.getVertexAt(i===0 ? n-1 : i-1);
            vAfter = polyline.getVertexAt(i===n-1 ? 0 : i+1);
        }
    }

    var xa = vBefore.x;
    var ya = vBefore.y;
    var xb = vMin.x;
    var yb = vMin.y;
    var xc = vAfter.x;
    var yc = vAfter.y;

    var det = (xb-xa) * (yc-ya) - (xc-xa) * (yb-ya);

    return det<0.0;
};

/**
 * Adds a menu for this action to Examples/Math Examples/ExDumpPolyline.
 */
ExDumpPolyline.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Dump Polyline"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExDumpPolyline.js");
    action.setGroupSortOrder(71100);
    action.setSortOrder(100);
    action.setWidgetNames(["IOExamplesMenu"]);
};
