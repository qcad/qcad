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

include("scripts/Edit/Edit.js");

/**
 * \class Duplicate
 * \brief Copies the current selection to the clipboard. 
 * The reference point is the center of the current selection.
 * \ingroup ecma_edit
 */
function Duplicate(guiAction) {
    Edit.call(this, guiAction);
}

Duplicate.prototype = new Edit();

Duplicate.prototype.beginEvent = function() {
    Edit.prototype.beginEvent.call(this);

    var doc = this.getDocument();
    var di = this.getDocumentInterface();
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var ids = doc.querySelectedEntities();
    for (var i = 0; i < ids.length; ++i) {
        var id = ids[i];
        var e = doc.queryEntity(id);
        op.addObject(e, false, true);
    }

    // deselect originals, duplicates will be selected:
    di.deselectEntities(ids);

    di.applyOperation(op);

    EAction.handleUserMessage(qsTr("%n entity/ies duplicated", "", ids.length));

    this.terminate();
};
