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

function FlipHorizontal(guiAction) {
    EAction.call(this, guiAction);
}

FlipHorizontal.prototype = new EAction();

FlipHorizontal.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    FlipHorizontal.flip(this.getDocumentInterface(), true, this.getToolTitle());

    this.terminate();
};

/**
 * \param horizontally True: flip horizontally, false: flip vertically
 */
FlipHorizontal.flip = function(di, horizontally, toolTitle) {
    var document = di.getDocument();
    var box = document.getSelectionBox();
    var center = box.getCenter();
    var axis;
    if (horizontally) {
        axis = new RLine(center, center.operator_add(new RVector(0,1)));
    }
    else {
        axis = new RLine(center, center.operator_add(new RVector(1,0)));
    }

    var ids = document.querySelectedEntities();
    var i;

    var op = new RModifyObjectsOperation();
    op.setText(toolTitle);

    for (i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isNull(entity)) {
            debugger;
        }

        entity.mirror(axis);
        op.addObject(entity, false);
    }

    di.applyOperation(op);
};
