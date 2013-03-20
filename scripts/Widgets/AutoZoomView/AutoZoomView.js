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

function AutoZoomView(parent) {
    RGraphicsViewQt.call(this, parent, false);
}

AutoZoomView.prototype = new RGraphicsViewQt();

/*
AutoZoomView.prototype.event = function(event) {
    if (event.type()==QEvent.ToolTip) {
        this.toolTip =
             qsTr("Unit: %1").arg(RUnit.unitToName(this.getDocument().getUnit()));
    }

    // TypeError: Result of expression 'RGraphicsViewQt.prototype.event.call' [undefined] is not a function.
    RGraphicsViewQt.prototype.event.call(this, event);
};
*/

AutoZoomView.prototype.resizeEvent = function(event) {
    RGraphicsViewQt.prototype.resizeEvent.call(this, event);
    this.autoZoom();
};
