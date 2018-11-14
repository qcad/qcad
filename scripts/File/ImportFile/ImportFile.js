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

include("scripts/Edit/Paste/Paste.js");

/**
 * \class ImportFile
 * \brief Inserts a file into the drawing.
 * The target point is specified by the user.
 * \ingroup ecma_edit
 */
function ImportFile(guiAction, fileName) {
    Paste.call(this, guiAction);

    this.sourceDocument = new RDocument(new RMemoryStorage(), createSpatialIndex());
    this.sourceDi = new RDocumentInterface(this.sourceDocument);
    this.sourceDi.setNotifyListeners(false);

    // unit tests pass file name directly to action:
    this.fileName = fileName;
    this.blockName = undefined;
    this.asBlock = false;

    this.setUiOptions(ImportFile.includeBasePath + "/ImportFile.ui");
}

ImportFile.prototype = new Paste();
ImportFile.includeBasePath = includeBasePath;

ImportFile.prototype.beginEvent = function() {
    Paste.prototype.beginEvent.call(this);

    var fileDialogInfo;
    if (!isNull(this.fileName)) {
        fileDialogInfo = [ this.fileName, "" ];
    }
    else {
        fileDialogInfo = this.getFileName();
    }

    // workaround for Qt keyboard focus bug:
    var appWin = RMainWindowQt.getMainWindow();
    if (!isNull(appWin)) {
        appWin.activateWindow();
        appWin.raise();
        appWin.setFocus(Qt.OtherFocusReason);
    }

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

ImportFile.prototype.initOperation = function(op) {
    if (this.asBlock && !isNull(this.blockName) && this.blockName.length>0) {
        op.setBlockName(this.blockName);
    }
};

ImportFile.prototype.getFileName = function() {
    var lastOpenFileDir = RSettings.getStringValue("ImportFile/Path", RSettings.getDocumentsLocation());

    var filterStrings = RFileImporterRegistry.getFilterStrings();
    filterStrings = translateFilterStrings(filterStrings);
    if (filterStrings.length===0) {
        EAction.handleUserWarning(qsTr("No import filters have been found. Aborting..."));
        return undefined;
    }

    filterStrings = new Array(qsTr("All Files") + " (*)").concat(filterStrings);

    var appWin = EAction.getMainWindow();
    var fileDialog = new QFileDialog(appWin, qsTr("Import Drawing"), lastOpenFileDir, "");
    var allFilter = filterStrings[0];
    fileDialog.setNameFilters(filterStrings);
    fileDialog.selectNameFilter(allFilter);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
    if (!isNull(QFileDialog.DontUseCustomDirectoryIcons)) {
        fileDialog.setOption(QFileDialog.DontUseCustomDirectoryIcons, true);
    }
    fileDialog.fileMode = QFileDialog.ExistingFiles;
    fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));
    if (!fileDialog.exec()) {
        fileDialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    var fileNames = fileDialog.selectedFiles();
    if (fileNames.length===0) {
        fileDialog.destroy();
        EAction.activateMainWindow();
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

    var nameFilter = fileDialog.selectedNameFilter();

    fileDialog.destroy();
    EAction.activateMainWindow();

    //this.blockName = new QFileInfo(fileNames[0]).baseName();
    //RSettings.setValue("ImportFile/BlockName", new QFileInfo(fileNames[0]).baseName());
    var optionsToolBar = EAction.getOptionsToolBar();
    if (!isNull(optionsToolBar)) {
        var leBlockName = optionsToolBar.findChild("BlockName");
        if (!isNull(leBlockName)) {
            var blockName = new QFileInfo(fileNames[0]).completeBaseName();
            blockName = RDxfServices.getSafeBlockName(blockName);
            leBlockName.text = blockName;
        }
    }

    return [ fileNames[0], nameFilter ];
};

ImportFile.prototype.slotAsBlockChanged = function(value) {
    this.asBlock = value;
    this.updatePreview(true);
};

ImportFile.prototype.slotBlockNameChanged = function(value) {
    this.blockName = value;
    this.updatePreview(true);
};
