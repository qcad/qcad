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

/**
 * \defgroup ecma_file File Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of the
 * tools in the file menu.
 */
include("../EAction.js");

/**
 * \class File
 * \brief Base class for all file menu tools.
 * \ingroup ecma_file
 */
function File(guiAction) {
    EAction.call(this, guiAction);
}

File.prototype = new EAction();
File.includeBasePath = includeBasePath;

File.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="FileToolsPanelButton") {
        EAction.showCadToolBarPanel("FileToolsPanel");
        this.terminate();
    }
};

File.getMenu = function() {
    var menu = EAction.getMenu(File.getTitle(), "FileMenu");
    menu.setProperty("scriptFile", File.includeBasePath + "/File.js");
    return menu;
};

File.getToolBar = function() {
    var tb = EAction.getToolBar(File.getTitle(), "FileToolBar");
    return tb;
};

File.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "FileToolsPanelButton";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("File Tools"), mtb);
        action.setScriptFile(File.includeBasePath + "/File.js");
        action.objectName = actionName;
        action.setRequiresDocument(false);
        action.setIcon(File.includeBasePath + "/File.svg");
        action.setStatusTip(qsTr("Show file tools"));
        action.setNoState();
        action.setDefaultCommands(["filemenu"]);
        action.setGroupSortOrder(10);
        action.setSortOrder(100);
        //action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        File.getTitle(),
        "FileToolsPanel",
        true
    );
    return tb;
};


File.getTitle = function() {
    return qsTr("&File");
};

File.prototype.getTitle = function() {
    return File.getTitle();
};

File.init = function() {
    File.getMenu();
    File.getToolBar();
    File.getCadToolBarPanel();
};


/**
 * Advanced file save as dialog with extension completion.
 * This is what QFileDialog.getSaveFileName should be.
 *
 * \param parentWidget Parent widget or null
 * \param caption Dialog caption
 * \param dir Initial directory of the dialog
 * \param fileName Initial file name to suggest to user
 * \param filterStrings Array of filter strings in the format 'My File Type (*.mft *.mftype)'
 *
 * \return Array with complete file path and selected name filter or undefined.
 */
File.getSaveFileName = function(parentWidget, caption, dir, filterStrings) {
    var fileDialog = new QFileDialog(parentWidget);
    
    // use native dialog:
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, false);

    // overwrite is handled after extension has been added:
    fileDialog.setOption(QFileDialog.DontConfirmOverwrite, true);

    var fiDir = new QFileInfo(dir);

    fileDialog.setDirectory(fiDir.absolutePath());
    fileDialog.fileMode = QFileDialog.AnyFile;
    fileDialog.acceptMode = QFileDialog.AcceptSave;

    fileDialog.setNameFilters(filterStrings);
    
    //if (!isNull(fileName)) {
        //var fileInfo = new QFileInfo(fileName);
        fileDialog.selectFile(fiDir.completeBaseName());

        if (fiDir.suffix().length!==0) {
            // preselect first name filter that matches current extension:
            for (var i=0; i<filterStrings.length; ++i) {
                if (filterStrings[i].contains("*." + fiDir.suffix().toLowerCase())) {
                    fileDialog.selectNameFilter(filterStrings[i]);
                    break;
                }
            }
        }
    //}

    fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));

    var done = false;

    while (!done) {
        done = true;

        if (!fileDialog.exec()) {
            fileDialog.destroy();
            return undefined;
        }

        var fileToSave = fileDialog.selectedFiles()[0];
        var selectedNameFilter = fileDialog.selectedNameFilter();

        // file, possibly without suffix:
        var fi = new QFileInfo(fileToSave);
        if (fi.suffix().length===0) {
            var suffix = "";
            var regex = /\(\*(\.[^ )]*)/i;
            if (regex.test(selectedNameFilter)) {
                var matches = selectedNameFilter.match(regex);
                if (matches.length==2) {
                    suffix = selectedNameFilter.match(regex)[1];
                }
            }
            if (suffix.length!==0) {
                fileToSave += suffix;
            }
        }

        // file with suffix:
        fi = new QFileInfo(fileToSave);
        if (fi.exists()) {
            var buttons = new QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No);
            var ret = QMessageBox.warning(parentWidget, 
                qsTr("Overwrite File?"), 
                qsTr("The file '%1' already exists. Do you wish to overwrite it?").arg(fileToSave),
                buttons);
            if (ret!=QMessageBox.Yes) {
                done = false;
            }
        }
    }
    
    return [ fileToSave, selectedNameFilter ];
};

/**
 * \return True if the file version is recommendable (supports 24bit colors).
 * \param version String from the file version drop down in the save as dialog.
 */
File.isRecommendedVersion = function(version) {
    if (version.indexOf("R2.5")!==-1) {
        return false;
    }
    else if (version.indexOf("R2.6")!==-1) {
        return false;
    }
    else if (version.indexOf("R9")!==-1) {
        return false;
    }
    else if (version.indexOf("R10")!==-1) {
        return false;
    }
    else if (version.indexOf("R12")!==-1) {
        return false;
    }
    else if (version.indexOf("R13")!==-1) {
        return false;
    }
    else if (version.indexOf("R14")!==-1 && version.indexOf("Beta")!==-1) {
        return false;
    }
    else if (version.indexOf("R14")!==-1) {
        return false;
    }
    else if (version.indexOf("R15")!==-1) {
        return false;
    }
    else if (version.indexOf("R18")!==-1) {
        return true;
    }
    else if (version.indexOf("R21")!==-1) {
        return true;
    }
    else if (version.indexOf("R24")!==-1) {
        return true;
    }
    else if (version.indexOf("R27")!==-1) {
        return true;
    }
    else {
        return true;
    }
};
