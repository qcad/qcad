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

include("../Projection.js");

/**
 * \class IsometricProjection
 * \brief Base class for all isometric projection tools.
 * \ingroup ecma_projection
 */
function IsometricProjection(guiAction) {
    Projection.call(this, guiAction);
}

IsometricProjection.prototype = new Projection();
IsometricProjection.includeBasePath = includeBasePath;

IsometricProjection.prototype.beginEvent = function() {
    Projection.prototype.beginEvent.call(this);
};

IsometricProjection.getToolBar = function() {
    var tb = EAction.getToolBar(IsometricProjection.getTitle(), "IsometricProjection");
    tb.visible = false;
    return tb;
};

IsometricProjection.getCadToolBarPanel = function() {
    return Projection.getCadToolBarPanel();
};

IsometricProjection.getTitle = function() {
    return qsTr("&Isometric Projection");
};

IsometricProjection.prototype.getTitle = function() {
    return IsometricProjection.getTitle();
};
