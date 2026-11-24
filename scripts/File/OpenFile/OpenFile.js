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

include("scripts/File/NewFile/NewFile.js");

if (exists("scripts/File/AutoSave/AutoSave.js")) {
    include("scripts/File/AutoSave/AutoSave.js");
}

/**
 * \class OpenFile
 * \brief Handles all user interaction to open documents.
 * \ingroup ecma_file
 */
function OpenFile(guiAction) {
    NewFile.call(this, guiAction);

    if (!isNull(guiAction)) {
        this.args = guiAction.getArguments();
    }
}

OpenFile.prototype = new NewFile();

/**
 * Preferences page File > Open. The preferences are stored under the
 * settings group "SaveAs" (e.g. SaveAs/OpenZeroSizeFile) for backwards
 * compatibility, see root widget name in PreferencesPage.ui.
 */
OpenFile.getPreferencesCategory = function() {
    return [ qsTranslate("SaveAs", "File", "PrefSectionTitle"), qsTr("Open")];
};

/**
 * \return Folder shown by File > Open (OpenFile/Path). This is the last used
 * folder or the folder configured in the preferences.
 */
OpenFile.getPath = function() {
    var ret = RSettings.getStringValue("OpenFile/Path", "");
    if (ret.length===0) {
        ret = RSettings.getDocumentsLocation();
    }
    return ret;
};

/**
 * \return True if File > Open always starts in the configured folder
 * (OpenFile/AlwaysUsePath), false if the last used folder is stored
 * automatically (default).
 */
OpenFile.getAlwaysUsePath = function() {
    return RSettings.getBoolValue("OpenFile/AlwaysUsePath", false);
};

/**
 * Loads the folder preferences. These are stored under OpenFile/... and not
 * under the settings group of the page (SaveAs/...), so they are handled
 * here instead of by WidgetFactory.
 */
OpenFile.initPreferences = function(pageWidget, calledByPrefDialog, document, preferences) {
    var pathEdit = pageWidget.findChild("Path");
    var browseButton = pageWidget.findChild("OpenFile");
    var alwaysCheckBox = pageWidget.findChild("AlwaysUsePath");

    pathEdit.text = QDir.toNativeSeparators(OpenFile.getPath());
    alwaysCheckBox.checked = OpenFile.getAlwaysUsePath();

    browseButton.clicked.connect(function() {
        var dlg = new QFileDialog(pageWidget, qsTr("Folder for Opening Files"), QDir.fromNativeSeparators(pathEdit.text), "");
        dlg.fileMode = QFileDialog.Directory;
        dlg.setOption(QFileDialog.ShowDirsOnly, true);
        dlg.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
        if (dlg.exec()) {
            var dirs = dlg.selectedFiles();
            if (dirs.length>0) {
                pathEdit.text = QDir.toNativeSeparators(dirs[0]);
            }
        }
        destrDialog(dlg);
    });

    // reset to defaults:
    if (!isNull(preferences) && !isNull(preferences.dialog)) {
        var resetButton = preferences.dialog.findChild("ResetToDefaults");
        if (!isNull(resetButton)) {
            resetButton.clicked.connect(function() {
                if (isDeleted(pageWidget) || preferences.pageWidget.currentWidget()!==pageWidget) {
                    return;
                }
                pathEdit.text = QDir.toNativeSeparators(RSettings.getDocumentsLocation());
                alwaysCheckBox.checked = false;
            });
        }
    }
};

OpenFile.postInitPreferences = function(pageWidget, calledByPrefDialog, document, preferences) {
    // mark page as changed if the folder preferences change:
    if (!isFunction(pageWidget.slotSettingChanged)) {
        return;
    }
    pageWidget.findChild("Path").textChanged.connect(pageWidget, pageWidget.slotSettingChanged);
    pageWidget.findChild("AlwaysUsePath").toggled.connect(pageWidget, pageWidget.slotSettingChanged);
};

OpenFile.savePreferences = function(pageWidget, calledByPrefDialog, document, transaction) {
    var path = QDir.fromNativeSeparators(pageWidget.findChild("Path").text.trim());
    RSettings.setValue("OpenFile/Path", path);
    RSettings.setValue("OpenFile/AlwaysUsePath", pageWidget.findChild("AlwaysUsePath").checked);
};

OpenFile.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    var filterStrings = RFileImporterRegistry.getFilterStrings();
    filterStrings = translateFilterStrings(filterStrings);
    if (filterStrings.length===0) {
        EAction.handleUserWarning(qsTr("No import filters have been found. Aborting..."));
        return;
    }

    var fileName;
    if (!isNull(this.args) && this.args.length>=1) {
        fileName = this.args[this.args.length-1];
        if (!new QFileInfo(fileName).isAbsolute()) {
            fileName = RSettings.getLaunchPath() + QDir.separator + fileName;
        }
        if (!isNull(fileName)) {
            NewFile.createMdiChild(fileName);
            return;
        }
    }

    if (!isNull(this.guiAction)) {
        fileName = this.guiAction.data();
        if (!isNull(fileName)) {
            NewFile.createMdiChild(fileName);
            return;
        }
    }
    
    // last used folder or folder configured in preferences:
    var lastOpenFileDir = OpenFile.getPath();
    var appWin = EAction.getMainWindow();
    var fileDialog = new QFileDialog(appWin, qsTr("Open Drawing"), lastOpenFileDir, "");
    filterStrings = new Array(qsTr("All Files") + " (*)").concat(filterStrings);
    var allFilter = filterStrings[0];
    fileDialog.setNameFilters(filterStrings);
    fileDialog.selectNameFilter(allFilter);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
    if (!isNull(QFileDialog.DontUseCustomDirectoryIcons)) {
        fileDialog.setOption(QFileDialog.DontUseCustomDirectoryIcons, true);
    }
    fileDialog.fileMode = QFileDialog.ExistingFiles;

    // global function qcadInitFileDialog may be registered to perform
    // additional initialization
    if (typeof qcadInitFileDialog!="undefined" && isFunction(qcadInitFileDialog)) {
        qcadInitFileDialog(fileDialog);
    }

    if (!fileDialog.exec()) {
        destrDialog(fileDialog);
        EAction.activateMainWindow();
        return;
    }
    EAction.activateMainWindow();
    if (!OpenFile.getAlwaysUsePath()) {
        // remember last used folder:
        RSettings.setValue("OpenFile/Path", fileDialog.directory().absolutePath());
    }
    
    var fileNames = fileDialog.selectedFiles();
    var nameFilter = fileDialog.selectedNameFilter();
    for ( var i = 0; i < fileNames.length; ++i) {
        NewFile.createMdiChild(fileNames[i], nameFilter);
    }
    destrDialog(fileDialog);
    EAction.activateMainWindow();
};

