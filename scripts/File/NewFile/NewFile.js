/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

include("../File.js");
include("../Save/Save.js");
include("scripts/Widgets/Viewport/Viewport.js");
include("../AutoSave/AutoSave.js");

if (new QFileInfo("scripts/DefaultAction.js").exists()) {
    include("scripts/DefaultAction.js");
}

if (new QFileInfo("scripts/Navigation/DefaultNavigation.js").exists()) {
    include("scripts/Navigation/DefaultNavigation.js");
}

// counter for default name of new documents:
var documentCounter;
if (documentCounter == undefined) {
    documentCounter = 1;
}

/**
 * \class NewFile
 * \brief Creates a new document.
 * \ingroup ecma_file
 */
function NewFile(guiAction) {
    File.call(this, guiAction);
}

NewFile.prototype = new File();
NewFile.includeBasePath = includeBasePath;

// list of actions to trigger after opening file:
NewFile.postOpenActions = [];

NewFile.getScriptFileName = function(scriptFile) {
    if (scriptFile.startsWith(":/")) {
        return ":" + scriptFile.mid(2);
    }
    return scriptFile;
};

/**
 * Adds the given script file as action to be triggered after a document
 * has been opened.
 */
NewFile.addPostOpenAction = function(scriptFile) {
    var sf = NewFile.getScriptFileName(scriptFile);
    if (!NewFile.postOpenActions.contains(sf)) {
        NewFile.postOpenActions.push(sf);
    }
};

/**
 * Removes the given script file as action to be triggered after a document
 * has been opened.
 */
NewFile.removePostOpenAction = function(scriptFile) {
    var sf = NewFile.getScriptFileName(scriptFile)
    NewFile.postOpenActions.remove(sf);
};

/**
 * \param isOpen True if new is called from a file open function.
 */
NewFile.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    NewFile.createMdiChild();
};

/**
 * Creates a new MDI child based on the given UI file and adds it to the
 * MDI area.
 */
NewFile.createMdiChild = function(fileName, nameFilter) {
    var isOpen = !isNull(fileName);

    if (isNull(nameFilter)) {
        nameFilter = "";
    }

    if (isOpen && !isUrl(fileName)) {
        if (!isNull(AutoSave) && !new QFileInfo(fileName).baseName().startsWith("~")) {
            if (!AutoSave.recover(fileName)) {
                // canceled file recovering:
                return undefined;
            }
        }
    }

    var appWin = EAction.getMainWindow();
    var mdiArea = appWin.centralWidget();

    if (isOpen) {
        appWin.handleUserMessage(qsTr("Opening drawing:") + " " + fileName + "...");
    }

    // create document:
    var storage = new RMemoryStorage();
    var spatialIndex = new RSpatialIndexNavel();
    var document = new RDocument(storage, spatialIndex);
    var documentInterface = new RDocumentInterface(document);

    if (isOpen) {
        //appWin.setProgressText(qsTr("Loading..."));
        var errorCode;
        if (isUrl(fileName)) {
            errorCode = documentInterface.importUrl(new QUrl(fileName), nameFilter);
            document.setFileName("");
            document.setModified(true);
        }
        else {
            errorCode = documentInterface.importFile(fileName, nameFilter);
        }
        if (errorCode !== RDocumentInterface.IoErrorNoError) {
            var dialog = new QMessageBox(
                QMessageBox.Warning,
                qsTr("Import Error"),
                "",
                QMessageBox.OK
            );
            var path = fileName.elidedText(dialog.font, 500);
            var text = qsTr("Cannot open file") + "\n\n'%1'.\n\n".arg(path);
            switch (errorCode) {
            case RDocumentInterface.IoErrorNoImporterFound:
                text += qsTr("No suitable Importer found. "
                             + "Please check file format and extension.");
                break;
            case RDocumentInterface.IoErrorNotFound:
                text += qsTr("File not found.");
                break;
            case RDocumentInterface.IoErrorPermission:
                text += qsTr("Please check your access rights, "
                             + "the file format and file extension.");
                break;
            case RDocumentInterface.IoErrorGeneralImportError:
                text += qsTr("Import failed.");
                break;
            case RDocumentInterface.IoErrorZeroSize:
                text += qsTr("File is empty.");
                break;
            }
            dialog.text = text;
            appWin.handleUserWarning(text);
            dialog.exec();
            dialog.destroy();
            EAction.activateMainWindow();
            RSettings.removeRecentFile(fileName);
            return undefined;
        }
        else {
            appWin.handleUserMessage(qsTr("Drawing loaded successfully:") + " " + fileName);
        }

        if (document.getFileVersion().length!==0) {
            appWin.handleUserMessage(qsTr("Format:") + " " + document.getFileVersion());
        }

        RSettings.removeRecentFile(fileName);
        RSettings.addRecentFile(fileName);
    }

    if (!isOpen) {
        // color of layer 0 defaults to black if background color is bright:
        var bgColor = RSettings.getColor("GraphicsViewColors/BackgroundColor", new RColor("black"));
        if (bgColor.lightness()>200) {
            var layer0 = document.queryLayer("0");
            layer0.setColor(new RColor("black"));
            var op = new RModifyObjectOperation(layer0, false);
            documentInterface.applyOperation(op);
            document.setModified(false);
        }
    }

    var uiFileName = undefined;

    // get viewport template from drawing settings
    if (isOpen) {
        uiFileName = document.getVariable("Viewport/ViewportList.data");
    }
    if (!isOpen || isNull(uiFileName)) {
        uiFileName = RSettings.getStringValue("Viewport/ViewportList.data", "00_Single.ui");
    }

    var mdiChild = new RMdiChildQt();
    mdiChild.setDocumentInterface(documentInterface);
    mdiArea.addSubWindow(mdiChild);
    mdiChild.updatesEnabled = false;
    mdiChild.showMaximized();

    // load ui file and set the MDI content widget:
    //qDebug("initMdiChild");
    Viewport.initMdiChild(mdiChild, uiFileName);

    var viewports = Viewport.getViewports(mdiChild, documentInterface);
    mdiChild.viewports = viewports;
    //qDebug("initViewports");
    Viewport.initializeViewports(viewports);
    //qDebug("initViewports: done");
    NewFile.updateTitle(mdiChild);

    var idleGuiAction = RGuiAction.getByScriptFile("scripts/Reset/Reset.js");

    if (typeof(DefaultAction)!=="undefined") {
        var idleAction = new DefaultAction(idleGuiAction);
        documentInterface.setDefaultAction(idleAction);
    }

    Viewport.initEventHandler(viewports);

    RGuiAction.triggerGroupDefaults();

    mdiChild.closeRequested.connect(NewFile, "closeRequested");
    mdiChild.modifiedStatusChanged.connect(NewFile, "updateTitle");
    appWin.resumedTab.connect(NewFile, "updateTitle");

    // make sure the MDI widget is maximized before performing an auto zoom:
    // TODO: fix for Qt 5:
    //if (!RSettings.isQt(5)) {
        appWin.enabled = false;
        for (var i=0; i<5; i++) {
            QCoreApplication.processEvents();
        }
        appWin.enabled = true;
    //}

    //qDebug("subWindowActivated");
    appWin.subWindowActivated(mdiChild);
    //qDebug("updateViewports");
    if (!isDeleted(mdiChild)) {
        mdiChild.updatesEnabled = true;
        Viewport.updateViewports(viewports);
    }

    if (isOpen) {
        // trigger post open actions (actions configured by the user to be
        // shown whenever a file is opened, for example to show a font
        // replacement dialog, etc):
        for (var k=0; k<NewFile.postOpenActions.length; k++) {
            if (!isNull(NewFile.postOpenActions[k])) {
                var action = RGuiAction.getByScriptFile(NewFile.postOpenActions[k]);
                if (!isNull(action)) {
                    action.slotTrigger();
                }
            }
        }
    }

    return mdiChild;
};

NewFile.updateTitle = function(mdiChild) {
    var appWin = EAction.getMainWindow();
    var tabBar = appWin.getTabBar();

    if (isNull(mdiChild)) {
        mdiChild = appWin.getMdiChild();
    }

    if (isNull(mdiChild)) {
        return;
    }

    var document = mdiChild.getDocument();
    var fileName = document.getFileName();
    var title = undefined;

    // untitled:
    if (fileName==="") {
        if (mdiChild.windowTitle==="") {
            title = addDirtyFlag(qsTr("Untitled %1").arg(documentCounter));
            if (!isNull(tabBar)) {
                tabBar.setTabToolTip(tabBar.currentIndex, title);
            }
            mdiChild.objectName = "Untitled%1".arg(documentCounter);
            documentCounter++;
            mdiChild.setWindowTitle(title);
        }
    }
    else {
        var fi = new QFileInfo(fileName);
        var name = fi.fileName();
        var roStr = qsTr("read-only");
        if (fi.isWritable()) {
            title = addDirtyFlag(name);
        }
        else {
            title = name + " " + roStr;
        }

        mdiChild.objectName = name;
        if (!isNull(tabBar)) {
            tabBar.setTabToolTip(tabBar.currentIndex, fileName);
        }
        mdiChild.setWindowTitle(title);
    }

    appWin.setWindowTitle(
        stripDirtyFlag(mdiChild.windowTitle) +
        (document.isModified() ? " *" : "") +
        " - " + qApp.applicationName
    );

    var mdiArea = EAction.getMdiArea();
    if (!isNull(mdiArea)) {
        mdiArea.updateTabBar();
    }
};

/**
 * Called when the user is about to close the drawing.
 */
NewFile.closeRequested = function(mdiChild) {
    // make sure the closing MDI child is the active one
    // (not the case if inactive tab is closed using close button on tab):
    var appWin = EAction.getMainWindow();
    var mdiArea = EAction.getMdiArea();
    mdiArea.setActiveSubWindow(mdiChild);

    var di = mdiChild.getDocumentInterface();
    var document = mdiChild.getDocument();

    if (!document.isModified()) {
        mdiChild.setCloseEventAccepted();
        return;
    }

    var dialog = WidgetFactory.createDialog(NewFile.includeBasePath, "CloseDialog.ui", mdiChild);

    var fileName = new QFileInfo(document.getFileName()).fileName();
    if (fileName.length===0) {
        fileName = stripDirtyFlag(mdiChild.windowTitle);
    }

    var label1 = dialog.findChild("Text1");
    label1.text = "<b>" + qsTr("Do you want to save the changes you made in<br>" +
                       "the document '%1'?").arg(fileName) + "</b>";
    var label2 = dialog.findChild("Text2");
    label2.text = qsTr("Your changes will be lost if you don't save them.");

    var buttonBox = dialog.findChild("ButtonBox");

    var discardButton = buttonBox.button(QDialogButtonBox.Discard);
    discardButton.autoDefault = false;
    discardButton['default'] = false;

    var saveButton = buttonBox.button(QDialogButtonBox.Save);
    saveButton.autoDefault = true;
    saveButton['default'] = true;

    var bakFileName = AutoSave.getAutoSaveFileNameCurrent();

    buttonBox.clicked.connect(function(button) {
            var standardButton = buttonBox.standardButton(button);
            switch (standardButton) {
            // cancel:
            case QDialogButtonBox.Cancel:
                dialog.reject();
                break;
            // discard (don't save):
            case QDialogButtonBox.Discard:
                dialog.accept();
                break;
            // save:
            case QDialogButtonBox.Save:
                var saveAction = new Save();
                di.setCurrentAction(saveAction);

                // if the 'save' or 'save as' was successful, the document is now unmodified:
                if (!document.isModified()) {
                    dialog.accept();
                }
                break;
            // save all:
            //case QDialogButtonBox.SaveAll:
            //    dialog.accept();
            //    break;
            }
        });

    if (dialog.exec()) {
        mdiChild.setCloseEventAccepted();
        AutoSave.cleanUp(bakFileName);
    }
    else {
        mdiChild.setCloseEventRejected();
    }
    dialog.destroy();
    EAction.activateMainWindow();
};

