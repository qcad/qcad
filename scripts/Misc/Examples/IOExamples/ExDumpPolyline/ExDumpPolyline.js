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

include("../IOExamples.js");

/**
 * \ingroup ecma_misc_examples_ioexamples
 * \class ExDumpPolyline
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
            var ori = entity.getOrientation(true);
            if (ori===RS.CW) {
                EAction.handleUserMessage(qsTr("Clockwise polyline:"));
            }
            else if (ori===RS.CCW) {
                EAction.handleUserMessage(qsTr("Counterclockwise polyline:"));
            }

            var n = entity.countVertices();
            for (var k=0; k<n; k++) {
                var v = entity.getVertexAt(k);
                EAction.handleUserMessage("%1,%2,".arg(v.x).arg(v.y));
            }
        }
    }

    this.terminate();
};

ExDumpPolyline.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Output Polyline Vertices"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExDumpPolyline.js");
    action.setGroupSortOrder(71100);
    action.setSortOrder(100);
    action.setWidgetNames(["IOExamplesMenu"]);
};
