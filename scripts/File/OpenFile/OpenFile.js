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

    if (!isNull(this.guiAction)) {
        var fileName = this.guiAction.data();
        if (!isNull(fileName)) {
            NewFile.createMdiChild(fileName);
            return;
        }
    }
    
    var lastOpenFileDir = RSettings.getStringValue(
            "OpenFile/Path",
            QDesktopServices.storageLocation(QDesktopServices.DocumentsLocation));
    var appWin = EAction.getMainWindow();
    var fileDialog = new QFileDialog(appWin, qsTr("Open Drawing"), lastOpenFileDir, "");
    var filters = RFileImporterRegistry.getFilterStrings();
    var allFilter = filters[0];
    filters = new Array(qsTr("All Files") + " (*)").concat(filters);
    fileDialog.setNameFilters(filters);
    fileDialog.selectNameFilter(allFilter);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, false);
    fileDialog.fileMode = QFileDialog.ExistingFiles;
    //fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));
    if (!fileDialog.exec()) {
        fileDialog.destroy();
        return;
    }
    RSettings.setValue("OpenFile/Path", fileDialog.directory().absolutePath());
    
    var fileNames = fileDialog.selectedFiles();
    var nameFilter = fileDialog.selectedNameFilter();
    for ( var i = 0; i < fileNames.length; ++i) {
        NewFile.createMdiChild(fileNames[i], nameFilter);
        //this.openFile(fileNames[i], nameFilter);
    }
    fileDialog.destroy();
};

/**
 * Opens the given file 'fileName' in a new MDI window with the givne nameFilter.
 * \param noTitle true: don't set the window title or file name.
 */
//OpenFile.prototype.openFile = function(fileName, nameFilter) {
//    NewFile.createMdiChild(fileName, nameFilter);


//    NewFile.prototype.beginEvent.call(this, true);

//    if (isNull(nameFilter)) {
//        nameFilter = "";
//    }

//    if (!isNull(AutoSave) && !new QFileInfo(fileName).baseName().startsWith("~")) {
//        if (!AutoSave.recover(fileName)) {
//            // canceled file recovering:
//            return false;
//        }
//    }

//    var appWin = EAction.getMainWindow();
//    appWin.setProgressText(qsTr("Loading..."));
//    var errorCode = this.documentInterface.importFile(fileName, nameFilter);
//    if (errorCode !== RDocumentInterface.IoErrorNoError) {
//        var dlg = new QMessageBox(QMessageBox.Warning,
//                qsTr("Import Error"),
//                "",
//                QMessageBox.OK);
//        var path = fileName.elidedText(dlg.font, 500);
//        var text = qsTr("Cannot open file\n\n'%1'.\n\n").arg(path) + " ";
//        switch (errorCode) {
//        case RDocumentInterface.IoErrorNoImporterFound:
//            text += qsTr("No suitable Importer found. "
//                    + "Please check file format and extension.");
//            break;
//        case RDocumentInterface.IoErrorGeneralImportError:
//            text += qsTr("Please check your access rights, "
//                    + "the file format and file extension.");
//            break;
//        }
//        dlg.text = text;
//        dlg.exec();
//        RSettings.removeRecentFile(fileName);
//        var mdiArea = appWin.centralWidget();
//        return false;
//    }

//    // get viewport template from drawing settings
//    var document = this.documentInterface.getDocument();
//    var uiFileName = document.getVariable("Viewport/ViewportList.data");
//    if (isNull(uiFileName)) {
//        // fall back to application wide settings
//        uiFileName = RSettings.getStringValue("Viewport/ViewportList.data", "00_Single.ui");
//    }
//    this.mdiChild = NewFile.createMdiChild(uiFileName, this.documentInterface, true);
//    var viewports = Viewport.getViewports(this.mdiChild, this.documentInterface);
//    this.mdiChild.viewports = viewports;
//    Viewport.initializeViewports(viewports);
    
//    var fi = new QFileInfo(fileName);
//    var name = fi.fileName();
//    var roStr = qsTr("read-only");
//    this.mdiChild.setWindowTitle(name + (fi.isWritable() ? " [*]" : " " + roStr));
//    this.mdiChild.objectName = name;
//    var tabBar = appWin.getTabBar();
//    tabBar.setTabToolTip(tabBar.currentIndex, fileName);

//    this.showMdiChild();
//    this.mdiChild.ensurePolished();

//    // make sure that everything is shown and initialized before
//    // triggering any actions:
//    QCoreApplication.processEvents();

//    Viewport.initEventHandler(viewports);
//    Viewport.updateViewports(viewports);
    
//    RSettings.removeRecentFile(fileName);
//    RSettings.addRecentFile(fileName);

//    RGuiAction.triggerGroupDefaults();

//    return true;
//};

