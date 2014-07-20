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

include("../Snap.js");

/**
 * \class SnapOnEntity
 * \ingroup ecma_snap
 * \brief Snap to points on entities.
 */
function SnapOnEntity(guiAction) {
    Snap.call(this, guiAction);
}

SnapOnEntity.prototype = new Snap();

SnapOnEntity.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    this.getDocumentInterface().setSnap(new RSnapOnEntity());
    this.terminate();
};

