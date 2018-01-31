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

include("scripts/View/View.js");

/**
 * Specialized base class for isometric viewing tools.
 * Allows for separate isometric tool bar.
 */
function IsometricView(guiAction) {
    View.call(this, guiAction);
}

IsometricView.prototype = new View();
IsometricView.includeBasePath = includeBasePath;

IsometricView.getMenu = function() {
    return View.getMenu();
};

IsometricView.getToolBar = function() {
    var tb = EAction.getToolBar(IsometricView.getTitle(), "IsometricViewToolBar");
    tb.visible = false;
    return tb;
};

IsometricView.getTitle = function() {
    return qsTr("&Isometric View");
};

IsometricView.prototype.getTitle = function() {
    return IsometricView.getTitle();
};

IsometricView.init = function() {
    IsometricView.getToolBar();
};

IsometricView.getGrid = function(view) {
    if (isNull(view)) {
        return undefined;
    }
    var grid = view.getGrid();
    if (isNull(grid)) {
        return undefined;
    }
    if (!isOfType(grid, ROrthoGrid)) {
        return undefined;
    }
    return grid;
};
