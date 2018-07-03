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

include("scripts/Modify/Modify.js");

function ToFront(guiAction) {
    Modify.call(this, guiAction);
}

ToFront.prototype = new Modify();

ToFront.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);
    this.moveTo(true);
    this.terminate();
};

ToFront.prototype.moveTo = function(front) {
    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var storage = this.getStorage();
    var ids = document.querySelectedEntities();
    var i;

    var op = new RModifyObjectsOperation();

    var drawOrder;
    var offset;
    if (front===true) {
        drawOrder = storage.getMaxDrawOrder();
        offset = 0;
    }
    else {
        drawOrder = storage.getMinDrawOrder();
        offset = 0;
    }

    for (i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isNull(entity)) {
            debugger;
        }

        entity.setDrawOrder(drawOrder+offset);
        op.addObject(entity, false);
    }

    di.applyOperation(op);
};

