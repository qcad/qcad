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

include("../MiscModify.js");
include("scripts/ShapeAlgorithms.js");

/**
 * Converts (selected) straight splines to lines.
 */
function SplineToLine(guiAction) {
    MiscModify.call(this, guiAction);
}

SplineToLine.prototype = new MiscModify();

SplineToLine.prototype.beginEvent = function() {
    MiscModify.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var op = new RModifyObjectsOperation();

    var ids;
    if (document.hasSelection()) {
        ids = document.querySelectedEntities();
    }
    else {
        ids = document.queryAllVisibleEntities();
    }

    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);

        if (isSplineEntity(entity)) {
            var shape = entity.castToShape();
            var line = ShapeAlgorithms.splineToLineOrArc(shape, 0.01, true);
            if (isLineShape(line)) {
                var newEntity = shapeToEntity(document, line);
                newEntity.copyAttributesFrom(entity.data());

                op.deleteObject(entity.clone());
                op.addObject(newEntity);
            }
        }
    }

    di.applyOperation(op);

    this.terminate();
};

SplineToLine.init = function(basePath) {
    var action = new RGuiAction(qsTr("Convert Straight Splines to Lines"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SplineToLine.js");
    action.setGroupSortOrder(56170);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscModifyMenu", "MiscModifyToolBar", "MiscModifyToolsPanel"]);
};
