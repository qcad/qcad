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
include("scripts/Edit/Edit.js");

/**
 * \class Reset
 * \brief Kills all running actions and returns to the default action.
 */
function Reset(guiAction) {
    EAction.call(this, guiAction);
}

Reset.prototype = new EAction();

Reset.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);
    this.getDocumentInterface().killAllActions();
    EAction.showMainTools();
    this.terminate();
};
