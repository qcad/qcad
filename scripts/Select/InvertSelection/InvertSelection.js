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

include("scripts/Select/Select.js");

/**
 * \class InvertSelection
 * \ingroup ecma_select
 * \brief Invert selection.
 */
function InvertSelection(guiAction) {
    Select.call(this, guiAction);
}

InvertSelection.prototype = new Select();

InvertSelection.prototype.selectEntities = function() {
    var doc = EAction.getDocument();
    var di = EAction.getDocumentInterface();

    var ids = doc.queryAllEntities();
    var selectIds = [];
    for (var i = 0; i < ids.length; ++i) {
        var id = ids[i];
        if (!doc.isSelected(id)) {
            selectIds.push(id);
        }
    }

    di.selectEntities(selectIds, false);
};

InvertSelection.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);
    this.selectEntities();
    this.terminate();
};

