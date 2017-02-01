/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

include("scripts/Edit/Paste/Paste.js");

/**
 * \class ImportFile
 * \brief Inserts a file into the drawing.
 * The target point is specified by the user.
 * \ingroup ecma_edit
 */
function ImportFile(guiAction) {
    Paste.call(this, guiAction);

    this.sourceDocument = new RDocument(new RMemoryStorage(), new RSpatialIndexNavel());
    this.sourceDi = new RDocumentInterface(this.sourceDocument);
    this.sourceDi.setNotifyListeners(false);
}

ImportFile.prototype = new Paste();

ImportFile.prototype.beginEvent = function() {
    Paste.prototype.beginEvent.call(this);

    var fileDialogInfo = this.getFileName();
    if (isNull(fileDialogInfo)) {
        this.sourceDi.destroy();
        this.sourceDi = undefined;
        this.terminate();
        return;
    }

    if (this.sourceDi.importFile(fileDialogInfo[0], fileDialogInfo[1], false)!==RDocumentInterface.IoErrorNoError) {
        EAction.handleUserWarning(qsTr("Error while importing file %1").arg(fileDialogInfo[0]));
        if (!isNull(this.sourceDi)) {
            this.sourceDi.destroy();
            this.sourceDi = undefined;
        }
        this.terminate();
        return;
    }
};

ImportFile.prototype.finishEvent = function() {
    if (!isNull(this.sourceDi)) {
        this.sourceDi.destroy();
    }
    Paste.prototype.finishEvent.call(this);
};


ImportFile.prototype.getFileName = function() {
    var lastOpenFileDir = RSettings.getStringValue("ImportFile/Path", RSettings.getDocumentsLocation());

    var filters = RFileImporterRegistry.getFilterStrings();
    if (filters.length===0) {
        EAction.handleUserWarning(qsTr("No import filters have been found. Aborting..."));
        return undefined;
    }

    filters = new Array(qsTr("All Files") + " (*)").concat(filters);

    var appWin = EAction.getMainWindow();
    var fileDialog = new QFileDialog(appWin, qsTr("Import Drawing"), lastOpenFileDir, "");
    var allFilter = filters[0];
    fileDialog.setNameFilters(filters);
    fileDialog.selectNameFilter(allFilter);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
    if (!isNull(QFileDialog.DontUseCustomDirectoryIcons)) {
        fileDialog.setOption(QFileDialog.DontUseCustomDirectoryIcons, true);
    }
    fileDialog.fileMode = QFileDialog.ExistingFiles;
    fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));
    if (!fileDialog.exec()) {
        fileDialog.destroy();
        return undefined;
    }

    var fileNames = fileDialog.selectedFiles();
    if (fileNames.length===0) {
        fileDialog.destroy();
        return undefined;
    }

    var fileName = fileNames[0];

    var suffix = new QFileInfo(fileName).suffix();
    suffix = suffix.toUpperCase();

    var imageFormats = QImageReader.supportedImageFormats();
    for (var i=0; i<imageFormats.length; i++) {
        var format = imageFormats[i];
        if (suffix===format.toString().toUpperCase()) {
            // delegate import to image action:
            include("scripts/Draw/Image/Image.js");
            var imageAction = new Image();
            imageAction.fileName = fileName;
            this.getDocumentInterface().queueAction(imageAction);
            this.terminate();
            return;
        }
    }

    RSettings.setValue("ImportFile/Path", fileDialog.directory().absolutePath());

    return [ fileNames[0], fileDialog.selectedNameFilter() ];
};
