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

include("../../Arc/ArcTPR/ArcTPR.js");

/**
 * \class CircleTPR
 * \brief Circle tangential to entity, through point with given radius.
 * \ingroup ecma_draw_circle
 */
function CircleTPR(guiAction) {
    ArcTPR.call(this, guiAction);
    this.fullCircle = true;
    this.setUiOptions("CircleTPR.ui");
}

CircleTPR.prototype = new ArcTPR();

CircleTPR.prototype.setState = function(state) {
    ArcTPR.prototype.setState.call(this, state);

    if (this.state===ArcTPR.State.SettingPoint) {
        var trPoint = qsTr("Point on circle");
        this.setCommandPrompt(trPoint);
        this.setLeftMouseTip(trPoint);
    }
};
