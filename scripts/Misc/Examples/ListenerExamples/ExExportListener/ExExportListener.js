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
 * \ingroup ecma_misc_examples_listenerexamples
 * \class ExExportListener
 * This action installs an export listener and prints information about
 * exports (files being saved) to stdout.
 */
function ExExportListener(guiAction) {
    EAction.call(this, guiAction);
}

ExExportListener.prototype = new EAction();

/**
 * Adds a menu for this action to the menu.
 */
ExExportListener.init = function(basePath) {
    // comment this return out to enable this example:
    return;

    // create a new export listener:
    var adapter = new RExportListenerAdapter();

    // register export listener:
    var appWin = EAction.getMainWindow();
    appWin.addExportListener(adapter);

    // connect postExport signal to function ExExportListener.fileExported:
    adapter.postExport.connect(ExExportListener.fileExported);
};

/**
 * This function is called whenever a file is exported. This implementation
 * prints the file path to stdout. Another implementation might trigger an
 * external process, upload the file, update a data base, etc.
 */
ExExportListener.fileExported = function(documentInterface) {
    if (isNull(documentInterface)) {
        return;
    }
    print("file saved: ", documentInterface.getDocument().getFileName());
};
