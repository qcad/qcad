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

include("../Print/Print.js");

/**
 * Used to print the current view (override settings).
 */
function PrintCurrentView(guiAction, document, view) {
    Print.call(this, guiAction);
}

PrintCurrentView.prototype = new Print();

PrintCurrentView.prototype.beginEvent = function() {
    var appWin = RMainWindowQt.getMainWindow();
    appWin.setProperty("PrintPreview/InitialZoom", "View");

    // Print beginEvent switches to print preview:
    Print.prototype.beginEvent.call(this);
};

PrintCurrentView.prototype.finishEvent = function() {
    var appWin = RMainWindowQt.getMainWindow();
    appWin.setProperty("PrintPreview/InitialZoom", "Stored");
};
