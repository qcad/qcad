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
include("../Save/Save.js");
include("scripts/Widgets/ViewportWidget/ViewportWidget.js");
include("../AutoSave/AutoSave.js");
include("scripts/Reset/Reset.js");

if (exists("scripts/DefaultAction.js")) {
    include("scripts/DefaultAction.js");
}

if (exists("scripts/Navigation/DefaultNavigation.js")) {
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
NewFile.postNewActions = [];

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
 * Adds the given script file as action to be triggered after a new document
 * has been created.
 */
NewFile.addPostNewAction = function(scriptFile) {
    var sf = NewFile.getScriptFileName(scriptFile);
    if (!NewFile.postNewActions.contains(sf)) {
        NewFile.postNewActions.push(sf);
    }
};

/**
 * Removes the given script file as action to be triggered after a new document
 * has been created.
 */
NewFile.removePostNewAction = function(scriptFile) {
    var sf = NewFile.getScriptFileName(scriptFile)
    NewFile.postNewActions.remove(sf);
};

/**
 * \param isOpen True if new is called from a file open function.
 */
NewFile.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    var w = NewFile.createMdiChild();
};

/**
 * Creates a new MDI child based on the given UI file and adds it to the
 * MDI area.
 *
 * \param fileName File name of file to open.
 * \param nameFilter Filter to use to import file.
 * \param uiFile UI file to use for view port (defaults to ViewportWidgetQt.ui).
 * \param graphicsSceneClass Class to use for graphics scene (defaults to "RGraphicsSceneQt")
 */
NewFile.createMdiChild = function(fileName, nameFilter, uiFile, graphicsSceneClass, silent) {
    var isOpen = !isNull(fileName);

    if (isNull(nameFilter)) {
        nameFilter = "";
    }
    if (isNull(silent)) {
        silent = false;
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
    var spatialIndex = createSpatialIndex();
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
            var dialog = undefined;
            var path = fileName;
            if (!silent) {
                dialog = new QMessageBox(
                    QMessageBox.Warning,
                    qsTr("Import Error"),
                    "",
                    QMessageBox.OK
                );
                path = fileName.elidedText(dialog.font, 500);
            }
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
            appWin.handleUserWarning(text);

            if (!isNull(dialog)) {
                dialog.text = text;
                dialog.exec();
                dialog.destroy();
                EAction.activateMainWindow();
            }

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
    mdiChild.windowIcon = new QIcon(autoPath("scripts/qcad_icon.png"));
    mdiChild.setDocumentInterface(documentInterface);
    var flags = new Qt.WindowFlags(Qt.FramelessWindowHint);
    mdiChild.setWindowFlags(flags);
    mdiArea.addSubWindow(mdiChild);
    mdiChild.updatesEnabled = false;

    // load ui file and set the MDI content widget:
    //qDebug("initMdiChild");
    ViewportWidget.initMdiChild(mdiChild, uiFileName);
    
    // fix Qt bug in which Qt icon is shown at the top left if tab bar is off:
    mdiChild.showMaximized();

    var viewports = ViewportWidget.getViewports(mdiChild, documentInterface);
    mdiChild.viewports = viewports;
    ViewportWidget.initializeViewports(viewports, uiFile, graphicsSceneClass);
    NewFile.updateTitle(mdiChild);

    NewFile.setupDefaultAction(documentInterface);

    ViewportWidget.initEventHandler(viewports);

    RGuiAction.triggerGroupDefaults();

    mdiChild.closeRequested.connect(NewFile, "closeRequested");
    mdiChild.modifiedStatusChanged.connect(NewFile, "updateTitle");
    appWin.resumedTab.connect(NewFile, "updateTitle");

    // make sure the MDI widget is maximized before performing an auto zoom:

    // Qt 5 / Unity bug workaround:
    // breaks Ubuntu Unity menu on start:
    if (RS.getSystemId()!=="linux" || !RSettings.isQt(5) || appWin.property("starting")!==true) {
        appWin.disable();
    }
    for (var i=0; i<5; i++) {
        QCoreApplication.processEvents();
    }
    if (!appWin.enabled) {
        appWin.enable();
    }

    //qDebug("subWindowActivated");
    appWin.subWindowActivated(mdiChild);
    //qDebug("updateViewports");
    if (!isDeleted(mdiChild)) {
        mdiChild.updatesEnabled = true;
        ViewportWidget.updateViewports(viewports);
    }

    var k, action;
    if (isOpen) {
        // trigger post open actions (actions configured by the user to be
        // run whenever a file is opened, for example to show a font
        // replacement dialog, etc):
        for (k=0; k<NewFile.postOpenActions.length; k++) {
            if (!isNull(NewFile.postOpenActions[k])) {
                action = RGuiAction.getByScriptFile(NewFile.postOpenActions[k]);
                if (!isNull(action)) {
                    action.slotTrigger();
                }
            }
        }
    }
    else {
        // trigger post new action (e.g. to load template file):
        for (k=0; k<NewFile.postNewActions.length; k++) {
            if (!isNull(NewFile.postNewActions[k])) {
                include(NewFile.postNewActions[k]);
                if (isFunction(initNewFile)) {
                    initNewFile(mdiChild);
                }
                action = RGuiAction.getByScriptFile(NewFile.postNewActions[k]);
                if (!isNull(action)) {
                    action.slotTrigger();
                }
            }
        }
    }

    if (!isNull(mdiChild) && !isDeleted(mdiChild)) {
        mdiChild.setFocus();
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

    if (!isNull(appWin) && appWin.property("NewFile/DiscardChanges")===true) {
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
    // this would allow the user to not save by pressing the space bar
    // seems dangerous though
    //discardButton.setFocus();

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

/**
 * Setup default action for the given document interface.
 */
NewFile.setupDefaultAction = function(documentInterface) {
    var defaultAction = NewFile.getDefaultAction();
    if (!isNull(defaultAction)) {
        documentInterface.setDefaultAction(defaultAction);
    }
};

/**
 * Returns name of default action class.
 */
NewFile.getDefaultActionClass = function() {
    var defaultActionClass = "DefaultAction";

    var defaultActionFile = RSettings.getStringValue("NewFile/DefaultAction", "");
    if (defaultActionFile.length===0) {
        return defaultActionClass;
    }

    var defaultActionFileInfo = new QFileInfo(defaultActionFile);
    if (!defaultActionFileInfo.exists()) {
        defaultActionFileInfo = new QFileInfo(":/" + defaultActionFile);
    }
    if (defaultActionFileInfo.exists()) {
        include(defaultActionFile);
        defaultActionClass = new QFileInfo(defaultActionFile).baseName();
    }
    else {
        qWarning("custom default action class not found:", defaultActionFile);
    }

    return defaultActionClass;
};

/**
 * Returns new default action as configured in settings ("NewFile/DefaultAction")
 * or instance of DefaultAction.
 */
NewFile.getDefaultAction = function(useGuiAction) {
    if (isNull(useGuiAction)) {
        useGuiAction = true;
    }

    // set up default action:
    var defaultGuiAction = undefined;
    if (useGuiAction) {
        defaultGuiAction = RGuiAction.getByScriptFile("scripts/Reset/Reset.js");
    }
    var defaultActionClass = NewFile.getDefaultActionClass();
    var defaultAction = undefined;
    if (typeof(global[defaultActionClass])!=="undefined") {
        defaultAction = new global[defaultActionClass](defaultGuiAction);
        if (isFunction(global[defaultActionClass].init)) {
            global[defaultActionClass].init();
        }
    }
    return defaultAction;
};
