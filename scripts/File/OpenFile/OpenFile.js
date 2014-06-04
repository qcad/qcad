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

include("../NewFile/NewFile.js");

if (new QFileInfo("scripts/File/AutoSave/AutoSave.js")) {
    include("scripts/File/AutoSave/AutoSave.js");
}

/**
 * \class OpenFile
 * \brief Handles all user interaction to open documents.
 * \ingroup ecma_file
 */
function OpenFile(guiAction) {
    NewFile.call(this, guiAction);
}

OpenFile.prototype = new NewFile();

OpenFile.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    var filters = RFileImporterRegistry.getFilterStrings();
    if (filters.length===0) {
        var dlg = new QMessageBox(QMessageBox.Warning,
                qsTr("No import filters"),
                "",
                QMessageBox.OK);
        dlg.text = qsTr("No import filters have been found. Aborting...");
        dlg.exec();
        return;
    }

    if (!isNull(this.guiAction)) {
        var fileName = this.guiAction.data();
        if (!isNull(fileName)) {
            NewFile.createMdiChild(fileName);
            return;
        }
    }
    
    var lastOpenFileDir = RSettings.getStringValue(
            "OpenFile/Path",
            RSettings.getDocumentsLocation());
    var appWin = EAction.getMainWindow();
    var fileDialog = new QFileDialog(appWin, qsTr("Open Drawing"), lastOpenFileDir, "");
    var allFilter = filters[0];
    filters = new Array(qsTr("All Files") + " (*)").concat(filters);
    fileDialog.setNameFilters(filters);
    fileDialog.selectNameFilter(allFilter);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, false);
    fileDialog.fileMode = QFileDialog.ExistingFiles;

    // global function qcadInitFileDialog may be registered to perform
    // additional initialization
    if (isFunction(qcadInitFileDialog)) {
        qcadInitFileDialog(fileDialog);
    }

    if (!fileDialog.exec()) {
        fileDialog.destroy();
        return;
    }
    RSettings.setValue("OpenFile/Path", fileDialog.directory().absolutePath());
    
    var fileNames = fileDialog.selectedFiles();
    var nameFilter = fileDialog.selectedNameFilter();
    for ( var i = 0; i < fileNames.length; ++i) {
        NewFile.createMdiChild(fileNames[i], nameFilter);
    }
    fileDialog.destroy();
};

