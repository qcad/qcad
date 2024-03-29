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

    var ids = doc.querySelectedEntities();

//    var op = new RAddObjectsOperation();
//    op.setText(this.getToolTitle());
//    var ids = doc.querySelectedEntities();
//    for (var i = 0; i < ids.length; ++i) {
//        var id = ids[i];
//        var e = doc.queryEntity(id);
//        op.addObject(e, false, true);
//    }
//    di.applyOperation(op);

    // copy to a local clipboard:
    var ms = new RMemoryStorage();
    var si = createSpatialIndex();
    var tmpDoc = new RDocument(ms, si);
    var tmpDi = new RDocumentInterface(tmpDoc);
    tmpDi.setNotifyListeners(false);

    var op = new RCopyOperation(new RVector(0,0), doc);
    op.setText(this.getToolTitle());
    tmpDi.applyOperation(op);

    op = new RPasteOperation(tmpDoc);
    op.setText(this.getToolTitle());
    op.setOffset(new RVector(0,0));
    op.setScale(1.0);
    op.setRotation(0.0);
    op.setFlipHorizontal(false);
    op.setFlipVertical(false);
    op.setToCurrentLayer(false);
    op.setOverwriteLayers(false);
    op.setOverwriteBlocks(false);

    // make sure duplicates are selected:
    tmpDi.selectAll();
    op.setKeepSelection(true);

    di.applyOperation(op);

    destr(tmpDi);

    // deselect originals, duplicates stay selected:
    di.deselectEntities(ids);

    EAction.handleUserMessage(qsTr("%n entity/ies duplicated", "", ids.length));

    this.terminate();
};
