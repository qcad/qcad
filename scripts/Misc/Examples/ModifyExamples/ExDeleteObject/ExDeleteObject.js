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

include("../ModifyExamples.js");

/**
 * \ingroup ecma_misc_examples_modifyexamples
 * \class ExDeleteObject
 */
function ExDeleteObject(guiAction) {
    ModifyExamples.call(this, guiAction);
}

ExDeleteObject.prototype = new ModifyExamples();

ExDeleteObject.prototype.beginEvent = function() {
    ModifyExamples.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var op, entity, id;

    // add line entity,
    // document takes ownership of entity:
    op = new RAddObjectsOperation();
    entity = new RLineEntity(document, new RLineData(new RVector(0,0), new RVector(100,100)));
    op.addObject(entity);
    di.applyOperation(op);

    // after applying the operation, the ID of the newly added entity is known
    // and can be stored as reference for the added entity:
    id = entity.getId();
    EAction.handleUserMessage(qsTr("Added line with ID %1".arg(id)));

    // query a copy of the stored entity from the document
    // and use it to delete the entity:
    entity = document.queryEntity(id);
    op = new RDeleteObjectsOperation();
    op.deleteObject(entity);
    di.applyOperation(op);

    EAction.handleUserMessage(qsTr("Deleted line with ID %1").arg(id));
    EAction.handleUserMessage(qsTr("You can use <i>Edit > Undo</i> to restore the line entity."), false);

    this.terminate();
};

/**
 * Adds a menu for this action.
 */
ExDeleteObject.init = function(basePath) {
    var action = new RGuiAction(qsTr("Add and Delete Line"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExDeleteObject.js");
    action.setGroupSortOrder(78200);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyExamplesMenu"]);
};
