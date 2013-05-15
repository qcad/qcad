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

include("../Save/Save.js");

/**
 * This action handles all user interaction to save drawings under a new name.
 */
function SaveAs(guiAction) {
    Save.call(this, guiAction);
}

SaveAs.prototype = new Save();

SaveAs.getPreferencesCategory = function() {
    return [ qsTr("Load/Save"), qsTr("Save as")];
};

SaveAs.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);

    var nameFilters = RFileExporterRegistry.getFilterStrings();

    // Offer only a limited choice here as not all file format versions
    // are suitable for saving all information (e.g. 24 bit colors):
    for (var i=0; i<nameFilters.length; i++) {
        var nameFilter = nameFilters[i];
        if (File.isRecommendedVersion(nameFilter)) {
            widgets["Filter"].addItem(nameFilter);
        }
    }
};

SaveAs.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    var nameFilters = RFileExporterRegistry.getFilterStrings();
    if (nameFilters.length===0) {
        var dlg = new QMessageBox(QMessageBox.Warning,
                qsTr("No export filters"),
                "",
                QMessageBox.OK);
        dlg.text = qsTr("No export filters have been found. Aborting...");
        dlg.exec();
        this.terminate();
        return;
    }

    var appWin = EAction.getMainWindow();
    var lastSaveAsFileDir = RSettings.getStringValue("SaveAs/Path", QDir.homePath());
    var defaultNameFilter = RSettings.getStringValue("SaveAs/Filter", "");
    var fileDialog = new QFileDialog(appWin);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, false);
    // overwrite is handled after extension has been added:
    fileDialog.setOption(QFileDialog.DontConfirmOverwrite, true);
    fileDialog.fileMode = QFileDialog.AnyFile;
    fileDialog.acceptMode = QFileDialog.AcceptSave;
    var fileName = this.getDocument().getFileName();
    var fileInfo = new QFileInfo(fileName);
    if (fileName.length!==0) {
        fileDialog.selectFile(fileInfo.completeBaseName());
        fileDialog.setDirectory(fileInfo.absolutePath());
    }
    else {
        fileDialog.setDirectory(lastSaveAsFileDir);
    }
    fileDialog.setNameFilters(nameFilters);

    var suffix = fileInfo.suffix().toLowerCase();

    if (suffix.length!==0 && !defaultNameFilter.containsIgnoreCase(suffix)) {
        // preselect first name filter that matches current extension:
        for (var i=0; i<nameFilters.length; ++i) {
            if (nameFilters[i].contains("*." + suffix)) {
                fileDialog.selectNameFilter(nameFilters[i]);
                break;
            }
        }
    }
    else {
        // preselect configured name filter:
        if (defaultNameFilter.length===0) {
            fileDialog.selectNameFilter(nameFilters[0]);
        }
        else {
            fileDialog.selectNameFilter(defaultNameFilter);
        }
    }

    fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));

    if (!fileDialog.exec()) {
        qDebug("save as: canceled");
        fileDialog.destroy();
        this.terminate();
        return;
    }

    RSettings.setValue("SaveAs/Path", fileDialog.directory().absolutePath());
    var file = fileDialog.selectedFiles()[0];

    this.save(fileDialog.selectedFiles()[0], fileDialog.selectedNameFilter(), true);

    this.terminate();
    fileDialog.destroy();
};

