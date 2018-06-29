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

include("scripts/Snap/Snap.js");

/**
 * \class SnapAuto
 * \ingroup ecma_snap
 * \brief Auto snap.
 */
function SnapAuto(guiAction) {
    Snap.call(this, guiAction);
}

SnapAuto.prototype = new Snap();

SnapAuto.getPreferencesCategory = function() {
    return [qsTr("Snap"), qsTr("Auto Snap")];
};

SnapAuto.applyPreferences = function(doc, mdiChild) {
    RSnapAuto.init(true);
};

SnapAuto.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        di.setSnap(new RSnapAuto());
    }
    this.terminate();
};

