/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("Modify.js");

/**
 * \class Transform
 * \brief Base class for all transformation tools (move, copy, rotate, mirror, ...).
 */
function Transform(guiAction) {
    Modify.call(this, guiAction);
    
    this.useCurrentAttributes = false;
}

Transform.prototype = new Modify();
Transform.includeBasePath = includeBasePath;

Transform.prototype.verifySelection = function() {
    var di = this.getDocumentInterface();
    if (!di.hasSelection()) {
        EAction.handleUserWarning(qsTr("This tool requires a selection"));
        this.terminate();
        return false;
    }

    return true;
};

/**
 * Implemetation of getOperation for tools that operate on a selection and
 * do something with every entity in the selection (e.g. move, rotate, ...).
 * The callback function 'this.transform(entity, copy number)' is called for
 * every selected entity.
 */
Transform.prototype.getOperation = function(preview, selectResult) {
    if (isNull(this.copies)) {
        return undefined;
    }

    if (isNull(selectResult)) {
        selectResult = true;
    }

    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var storage = document.getStorage();
    var ids = document.querySelectedEntities();
    var i, k, id, entity;
    var num = this.copies;
    if (num===0) {
        num=1;
    }

    var op = new RAddObjectsOperation();
    for (k=1; k<=num; k++) {
        for (i=0; i<ids.length; i++) {
            if (preview && op.getPreviewCounter()>RSettings.getPreviewEntities()) {
                break;
            }

            id = ids[i];
            entity = document.queryEntity(id);
            if (isNull(entity)) {
                continue;
            }
            entity = entity.data();

            // copy: assign new IDs
            if (this.copies>0) {
                if (!preview && !selectResult) {
                    entity.setSelected(false);
                }
            }

            this.transform(entity, k, op, preview, this.copies>0);
        }
        op.endCycle();
    }

    // deselect original entities, all copies are selected:
    if (!preview && selectResult) {
        di.deselectEntities(ids);
    }

    return op;
};
