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

/**
 * \class Reverse
 * \brief Reverses all selected entities which support reversing (lines, arcs, splines).
 * \ingroup ecma_modify
 */
function Reverse(guiAction) {
    Modify.call(this, guiAction);
}

Reverse.prototype = new Modify();

Reverse.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.applyOperation();
    this.terminate();
};

Reverse.prototype.applyOperation = function() {
    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var ids = document.querySelectedEntities();
    var i, k, id, entity;

    var op = new RModifyObjectsOperation();
    for (i=0; i<ids.length; i++) {
        id = ids[i];
        entity = document.queryEntity(id);

        if (isFunction(entity.reverse)) {
            entity.reverse();
        }

        op.addObject(entity, false);
    }

    this.getDocumentInterface().applyOperation(op);
};

