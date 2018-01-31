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

/**
 * \ingroup ecma_misc_examples_qtexamples
 * \class ExDirListing
 * This action lists the contents of the home directory and prints
 * it into the QCAD command line history.
 */
function ExDirListing(guiAction) {
    EAction.call(this, guiAction);
}

ExDirListing.prototype = new EAction();

ExDirListing.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    // create QDir object that represents a directory:
    var dir = new QDir.home();

    // get directory listing:
    var fileInfos = dir.entryInfoList(
        // name filter(s):
        ["*"],
        // we don't want to get information about '.' or '..', we want all directories and all files:
        new QDir.Filters(QDir.NoDotAndDotDot, QDir.Dirs, QDir.Files),
        // sort by name:
        QDir.Name
    );

    // print some of the available information:
    for (var i=0; i<fileInfos.length; i++) {
        EAction.handleUserMessage(
            fileInfos[i].fileName() + 
            " [" + (fileInfos[i].isDir() ? "Directory" : "File") + "] " + 
            fileInfos[i].size() + " Bytes"
        );
    }

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/ExDirListing.
 */
ExDirListing.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Directory Listing"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExDirListing.js");
    action.setGroupSortOrder(79600);
    action.setSortOrder(100);
    action.setWidgetNames(["QtExamplesMenu"]);
};
