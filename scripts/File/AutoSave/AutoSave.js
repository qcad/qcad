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

include("scripts/File/File.js");
include("scripts/sprintf.js");

var documentCounter;
if (documentCounter == undefined) {
    documentCounter = 1;
}

function AutoSave(guiAction) {
    File.call(this, guiAction);
}

AutoSave.prototype = new File();

AutoSave.getPreferencesCategory = function() {
    return [ qsTr("File"), qsTr("Autosave")];
};

/**
 * Restarts or stopes the timer after preferences have been changed.
 */
AutoSave.applyPreferences = function(doc, mdiChild) {
    var interval = RSettings.getIntValue("AutoSave/Interval", 5)  * 60 * 1000;
    var enableAutoSave = RSettings.getBoolValue("AutoSave/EnableAutoSave", true);

    AutoSave.autoSaveTimer.interval = interval;

    if (enableAutoSave) {
        if (!AutoSave.autoSaveTimer.active) {
            AutoSave.autoSaveTimer.start(interval);
        }
    }
    else {
        if (AutoSave.autoSaveTimer.active) {
            AutoSave.autoSaveTimer.stop();
        }
    }
};

/*
AutoSave.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var browseButton = pageWidget.findChild("AutoSaveBrowse");
    var pathEdit = pageWidget.findChild("AutoSavePath");
    var autoPathLabel = pageWidget.findChild("AutoPath");

    autoPathLabel.text = QDir.homePath();

    browseButton.clicked.connect(function() {
        var path = QFileDialog.getExistingDirectory(pageWidget, qsTr("Choose Autosave Directory"), QDir.homePath());
        RSettings.setValue("AutoSave/AutoSavePath", path);
        pathEdit.text = path;
    });

    pathEdit.textChanged.connect(function(text) {
        if (text.length===0) {
            autoPathLabel.text = QDir.homePath();
        }
        else {
            autoPathLabel.text = "";
        }
    });
};
*/

AutoSave.getTimestamp = function() {
    return QTime.currentTime().toString("hh:mm:ss");
};

AutoSave.init = function(basePath) {
    AutoSave.autoSaveTimer = new QTimer(this);
    AutoSave.autoSaveTimer.timeout.connect(AutoSave, "autoSave");

    // start autosave timer for the first time:
    AutoSave.applyPreferences();
};

/**
 * Called periodically to perform an auto save of the current document.
 */
AutoSave.autoSave = function() {
    var appWin = EAction.getMainWindow();
    if (appWin.property("DisableAutoSave")==true) {
        return;
    }

    var filterStrings = RFileExporterRegistry.getFilterStrings();
    if (filterStrings.length===0) {
        // don't attempt autosave if no filters are available to save:
        return;
    }

    var fi;
    var document = EAction.getDocument();
    var documentInterface = EAction.getDocumentInterface();

    if (isNull(document) || isNull(documentInterface)) {
        qDebug("autosave skipped [" + AutoSave.getTimestamp() + "]: no document");
        return undefined;
    }

    if (!document.isModified()) {
        qDebug("autosave skipped [" + AutoSave.getTimestamp() + "]: no modifications");
        return undefined;
    }

    var bakFileName = AutoSave.getAutoSaveFileNameCurrent();
    if (isNull(bakFileName)) {
        return undefined;
    }

    qDebug("autosaving [" + AutoSave.getTimestamp() + "]: file: ", bakFileName);

    var fileVersion = "R2012 DXF";

    EAction.handleUserMessage("[" + AutoSave.getTimestamp() + "] "
        + qsTr("Autosaving to:") + " "
        + QDir.toNativeSeparators(bakFileName) + "...");

    fi = new QFileInfo(bakFileName);

    var failed = true;

    // temp file name to make sure that a failed save does not overwrite
    // a good save (e.g. /home/tux/data/~~file.dxf):
    var tmpBakFileName = fi.absolutePath() + QDir.separator + "~" + fi.fileName();
    var fiDir = new QFileInfo(fi.absolutePath());
    if (fiDir.isWritable()) {
        if (documentInterface.exportFile(tmpBakFileName, fileVersion, false)) {
            var bakFile = new QFile(bakFileName);
            var tmpBakFile = new QFile(tmpBakFileName);
            if ((!bakFile.exists() || bakFile.remove()) && tmpBakFile.rename(bakFileName)) {
                failed = false;
            }
        }
    }

    if (failed) {
        EAction.handleUserWarning("[" + AutoSave.getTimestamp() + "] "
            + qsTr("Autosave failed:") + " "
            + QDir.toNativeSeparators(bakFileName));
        return undefined;
    }
    else {
        EAction.handleUserMessage("[" + AutoSave.getTimestamp() + "] "
            + qsTr("Autosave complete."));
        return bakFileName;
    }
};

/**
 * Checks if there are backup files available for the given drawing file and
 * offers the user a choice to recover them if desired.
 *
 * \return true if files were recovered.
 */
AutoSave.recoverUntitled = function() {
    var dir = new QDir(RSettings.getPath());
    var list = dir.entryList(["~*"]);

    if (list.length===0) {
        return false;
    }

    var msg = qsTr("%n autosave backup file(s) for (an) untitled drawing(s) was/were found.\n" +
            "Do you wish to recover it/them?", "", list.length);

    var buttons = new QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No, QMessageBox.Cancel);
    var ret = QMessageBox.warning(null,
        qsTr("Recover Files?"),
        msg,
        buttons);

    if (ret===QMessageBox.Yes) {
        for (var i=0; i<list.length; i++) {
            var fileName = RSettings.getPath() + QDir.separator + list[i];
            var mdiChild = NewFile.createMdiChild(fileName);
            if (isNull(mdiChild)) {
                qWarning("Cannot recover file " + fileName);
                continue;
            }

            var document = mdiChild.getDocument();
            document.setFileName("");
            document.setModified(true);
            mdiChild.setWindowTitle(addDirtyFlag(qsTr("Recovered") + " %1".arg(documentCounter)));
            mdiChild.objectName = "Recovered%1".arg(documentCounter);
            documentCounter++;
            var autoSaveFileName = AutoSave.autoSave();

            if (fileName!==autoSaveFileName) {
                var file = new QFile(fileName);
                file.remove();
            }
        }

        return true;
    }
    else if (ret===QMessageBox.No) {
        for (var i=0; i<list.length; i++) {
            var fileName = RSettings.getPath() + QDir.separator + list[i];
            var file = new QFile(fileName);
            file.remove();
        }

        return false;
    }

    return false;
};

/**
 * Checks if there is a backup file available for the given drawing file and
 * offers the user a choice to recover it if desired.
 *
 * \return true no auto save file or auto save file handled. False: cancel.
 */
AutoSave.recover = function(fileName) {
    var bakFileName = AutoSave.getAutoSaveFileName(fileName);
    var fi = new QFileInfo(fileName);
    //fi.absolutePath() + QDir.separator + "~" + fi.fileName();
    var bakFi = new QFileInfo(bakFileName);

    // no backup file found,
    // tell caller to open the original file:
    if (!bakFi.exists()) {
        return true;
    }

    // backup file found: ask user what to do:
    var buttons = new QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.No, QMessageBox.Cancel);
    var ret = QMessageBox.warning(null,
            qsTr("Recover File?"),
            qsTr("An autosave backup file for \"%1\" exists.\n" +
                "Do you wish to recover it?").arg(fi.fileName()),
            buttons);

    // canceled:
    if (ret===QMessageBox.Cancel) {
        return false;
    }

    // find an available name for a numbered backup file (e.g. file.001.dxf):
    var file = new QFile(fileName);
    var bakFile = new QFile(bakFileName);
    var bakFileNameNumbered;
    var num = 0;
    do {
        var postfix = sprintf("bak%03d", num++);
        bakFileNameNumbered =
            fi.absolutePath() + QDir.separator +
            fi.completeBaseName() + "." + postfix + "." + fi.suffix();
    } while(new QFileInfo(bakFileNameNumbered).exists());

    // move backup file away and open regular file:
    if (ret===QMessageBox.No) {
        if (!bakFile.rename(bakFileNameNumbered)) {
            EAction.handleUserWarning("[" + AutoSave.getTimestamp() + "] "
                + qsTr("Cannot rename file:") + ' ' + bakFileName);
            return false;
        }
        EAction.handleUserMessage(qsTr("Moved autosave backup file to:") + ' ' + bakFileNameNumbered);
        return true;
    }

    // move regular file away and make backup file regular file to open:
    else if (ret===QMessageBox.Yes) {
        if (!file.rename(bakFileNameNumbered)) {
            EAction.handleUserWarning("[" + AutoSave.getTimestamp() + "] "
                + qsTr("Cannot rename file:") + ' ' + fileName);
            return false;
        }
        if (!bakFile.rename(fileName)) {
            EAction.handleUserWarning("[" + AutoSave.getTimestamp() + "] "
                + qsTr("Cannot rename file:") + ' ' + bakFileName);
            return false;
        }
        EAction.handleUserMessage(qsTr("Moved original file to:") + ' ' + bakFileNameNumbered);
        return true;
    }

    return false;
};

/**
 * Called when the user saves a file. Removes the auto save file (if available).
 */
AutoSave.cleanUp = function(bakFileName) {
    //var bakFileName = AutoSave.getAutoSaveFileNameCurrent();
    var file = new QFile(bakFileName);
    if (file.exists()) {
        if (!file.remove()) {
            EAction.handleUserWarning("[" + AutoSave.getTimestamp() + "] "
                + qsTr("Cannot remove file:") + ' ' + bakFileName);
        }
    }
};

/**
 * \return File name of autosave file for the current document.
 */
AutoSave.getAutoSaveFileNameCurrent = function() {
    var document = EAction.getDocument();
    if (isNull(document)) {
        return undefined;
    }

    var bakFileName = document.getFileName();
    if (bakFileName!=="") {
        return AutoSave.getAutoSaveFileName(bakFileName);
    }

    // file not saved yet:
    var mdiChild = EAction.getMdiChild();
    var counter = 0;
    //var postfix = "";
    var title = mdiChild.windowTitle;
    title = stripDirtyFlag(title);
    title = title.replace(" ", "_");
    bakFileName = RSettings.getPath() + QDir.separator + "~" + title + ".dxf";
//        do {
//            // e.g. /home/tux/data/~file.dxf or /home/tux/data/~file_001.dxf
//            bakFileName = RSettings.getPath() + QDir.separator + "~" + title + postfix + ".dxf";
//            if (!new QFileInfo(bakFileName).exists()) {
//                break;
//            }
//            postfix = "_%1".arg(counter++, 3, 10, '0');
//        } while(true);

    return bakFileName;
};

/**
 * \return Auto save file name for the given file name.
 */
AutoSave.getAutoSaveFileName = function(fileName) {
    var fi = new QFileInfo(fileName);
    var suffix = fi.suffix();
    if (suffix.toLowerCase()!=="dxf") {
        suffix = "dxf";
    }

    return fi.absolutePath() + QDir.separator + "~" + fi.completeBaseName() + "." + suffix;
};
