/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 *
 * Copyright (c) 2014 by Robert S. All rights reserved.
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
include("scripts/simple.js");

/**
 * \class RunScript
 * \brief Handles all user interaction to load and run scripts.
 * \ingroup ecma_file
 */
function RunScript(guiAction) {
    EAction.call(this, guiAction);
}

RunScript.prototype = new EAction();
RunScript.includeBasePath = includeBasePath;

RunScript.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var fileNames = [];
    var i;

    // get file names from command line:
    if (!isNull(this.guiAction)) {
        fileNames = this.guiAction.getArguments();
        for (i=0; i<fileNames.length; i++) {
            if (!new QFileInfo(fileNames[i]).isAbsolute()) {
                fileNames[i] = RSettings.getLaunchPath() + QDir.separator + fileNames[i];
            }
        }
        // make sure next run asks user for file names:
        this.guiAction.clearArguments();
    }

    // show file dialog:
    if (fileNames.length===0) {
        var lastOpenScriptDir = RSettings.getStringValue("RunScript/Path", RSettings.getDocumentsLocation());

        var appWin = EAction.getMainWindow();
        var fileDialog = new QFileDialog(appWin, qsTr("Open Script File"), lastOpenScriptDir, "");
        var filters = new Array(qsTr("All Files") + " (*)", qsTr("ECMAScript Files") + " (*.js)");
        fileDialog.setNameFilters(filters);
        fileDialog.selectNameFilter(filters[0]);
        fileDialog.setOption(QFileDialog.DontUseNativeDialog, false);
        fileDialog.fileMode = QFileDialog.ExistingFiles;
        //fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));
        if (!fileDialog.exec()) {
            fileDialog.destroy();
            EAction.activateMainWindow();
            return;
        }
        RSettings.setValue("RunScript/Path", fileDialog.directory().absolutePath());

        fileNames = fileDialog.selectedFiles();
        fileDialog.destroy();
        EAction.activateMainWindow();

        // show warning:
        if (RSettings.getBoolValue("RunScript/DontShowDialog", false)!==true) {
            var dialog = WidgetFactory.createDialog(RunScript.includeBasePath, "RunScriptDialog.ui", appWin);
            var bb = dialog.findChild("ButtonBox");
            var b = bb.addButton(qsTr("Run Script"), QDialogButtonBox.AcceptRole);
            b["default"] = false;
            bb.button(QDialogButtonBox.Cancel)["default"] = true;
            var l = dialog.findChild("Message");
            l.text = l.text.arg(fileNames.join("<br>"));
            var ret = dialog.exec();
            if (ret!==QDialog.Accepted.valueOf()) {
                dialog.destroy();
                EAction.activateMainWindow();
                return;
            }
            WidgetFactory.saveState(dialog);
            dialog.destroy();
            EAction.activateMainWindow();
        }
    }

    for (i=0; i<fileNames.length; i++) {
        // user chose an action (derived from EAction and already initialized):
        var action = RGuiAction.getByScriptFile(fileNames[i]);
        if (!isNull(action)) {
            action.slotTrigger();
            continue;
        }

        // user chose any js file:
        var file = new QFile(fileNames[i]);
        var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
        if (!file.open(flags)) {
            continue;
        } 
        else {
            var textStream = new QTextStream(file);
            textStream.setCodec("UTF-8");
            var contents = textStream.readAll();
            file.close();
            try {
                var func = new Function(contents);
                func();
            }
            catch (e) {
                EAction.handleUserWarning("Script exception in script '" + fileNames[i] + "': " + e);
            }
        }
    }
};
