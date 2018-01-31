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

/**
 * This action draws a bounding box around each selected entity.
 */
function DrawBoundingBox(guiAction) {
    EAction.call(this, guiAction);

    // bounding box offset:
    this.offset = 0.0;
}

DrawBoundingBox.prototype = new EAction();

/**
 * Draws the bounding box(es) of the selected entities and terminates.
 */
DrawBoundingBox.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    // find all selected entities:
    var ids = document.querySelectedEntities();

    var i, k;

    var op = new RAddObjectsOperation();

    // add four lines for each bounding box of each entity:
    for (i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        var boundingBox = entity.getBoundingBox();
        var lineShapes = boundingBox.getLines2d();
        for (k=0; k<lineShapes.length; k++) {
            var lineEntity = shapeToEntity(document, lineShapes[k]);
            op.addObject(lineEntity, false);
        }
    }

    di.applyOperation(op);

    this.terminate();
};

/**
 * Adds a menu for this action.
 */
DrawBoundingBox.init = function(basePath) {
    var action = new RGuiAction(qsTr("Draw &Bounding Box"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DrawBoundingBox.js");
    action.setGroupSortOrder(54500);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscDrawMenu"]);
};
