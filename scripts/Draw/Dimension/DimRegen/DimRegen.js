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

include("scripts/Draw/Dimension/Dimension.js");

/**
 * \class DimRegen
 * \brief Regenerates dimensions to use automatic text position.
 * \ingroup ecma_modify
 */
function DimRegen(guiAction) {
    Dimension.call(this, guiAction);
}

DimRegen.prototype = new Dimension();

DimRegen.prototype.beginEvent = function() {
    Dimension.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    // find all selected entities:
    var ids = document.querySelectedEntities();

    var counter = 0;

    var op = new RModifyObjectsOperation();
    op.setText(this.getToolTitle());

    // reset all text positions of all selected dimension entities:
    for (i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isDimensionEntity(entity) && entity.hasCustomTextPosition()) {
            entity.setCustomTextPosition(false);
            entity.getData().update();
            entity.getData().getShapes();
            op.addObject(entity, false);
            counter++;
        }
    }

    di.applyOperation(op);

    var msg;
    if (counter==0) {
        msg = qsTr("No dimension entities with custom label positions selected.");
    }
    else {
        msg = qsTr("Label position of %n dimension(s) was reset.", "", counter);
    }

    EAction.handleUserMessage(msg);

    this.terminate();
};

