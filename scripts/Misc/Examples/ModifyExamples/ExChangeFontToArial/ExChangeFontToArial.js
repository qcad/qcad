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

include("../ModifyExamples.js");

/**
 * This action changes the font of all texts to 'Arial'.
 */
function ExChangeFontToArial(guiAction) {
    ModifyExamples.call(this, guiAction);
}

ExChangeFontToArial.prototype = new ModifyExamples();

/**
 * Changes the color of all white layers to black and terminates.
 */
ExChangeFontToArial.prototype.beginEvent = function() {
    ModifyExamples.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var op = new RModifyObjectsOperation();

    var ids = document.querySelectedEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);

        if (isTextEntity(entity)) {
            entity.setFontName("Arial");
            entity.update();
            op.addObject(entity);
        }
    }

    di.applyOperation(op);

    this.terminate();
};

/**
 * Adds a menu for this action.
 */
ExChangeFontToArial.init = function(basePath) {
    var action = new RGuiAction("Set font to Arial", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/ExChangeFontToArial.js");
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, ModifyExamples, true, false, false);

    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
};
