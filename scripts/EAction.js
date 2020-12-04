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

include("WidgetFactory.js");
include("scripts/Widgets/OptionsToolBar/OptionsToolBar.js");

if (RSettings.isGuiEnabled()) {
    if (exists("scripts/Widgets/CadToolBar/CadToolBar.js")) {
        include("scripts/Widgets/CadToolBar/ColumnLayout.js");
        include("scripts/Widgets/CadToolBar/CadToolBar.js");
    }
}

/**
 * Base class for all ECMAScript based actions.
 */
function EAction(guiAction) {
    RActionAdapter.call(this);
    this.guiAction = guiAction;
    if (!isNull(guiAction)) {
        this.setGuiAction(guiAction);
    }

    // Constructor is called without arguments to create prototype
    // for derived class. At this point, includeBasePath is set correctly:
    if (isNull(guiAction)) {
        this.includeBasePath = includeBasePath;
    }

    this.delegate = undefined;
    this.state = undefined;
    this.settingsGroup = undefined;
    this.uiFile = undefined;
    this.splitUiOptions = false;
    this.additionalOptionsToolBars = undefined;
    this.optionsToolBarEnabled = true;
    this.relativeZeroPos = undefined;

    // set to true to prefer dialog over options tool bar:
    this.useDialog = false;
    this.dialogUiFile = undefined;

    this.waitingForContextMenu = false;

    this.optOutRelativeZeroResume = false;

    this.resuming = false;
}

EAction.prototype = new RActionAdapter();
EAction.includeBasePath = includeBasePath;

// some commonly used translated strings:
EAction.trBack = qsTr("Back");
EAction.trCancel = qsTr("Cancel");
EAction.trDone = qsTr("Done");

EAction.crossCursor = undefined;
EAction.noRelativeZeroResume = false;

/**
 * Called when the user starts this action by clicking a button, choosing a
 * menu, entering a command, etc.
 * 
 * Shows the GUI elements that refer to this action as checked. Displays GUI
 * options if this.uiFile is set to a valid UI file. Displays tool help in Help
 * Viewer if available.
 */
EAction.prototype.beginEvent = function() {
    if (this.delegate) {
        this.delegate.beginEvent();
    }

    if (this.hasNoState()) {
        return;
    }

    var appWin = EAction.getMainWindow();

    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(true);
    }
    this.showUiOptions(false);

    // reset snap to auto snap / no restriction:
    if (isNull(this.getGuiAction())
            || (this.getGuiAction().getGroup() !== "snaps" &&
                this.getGuiAction().getGroup() !== "snaprestrictions" &&
                this.getGuiAction().property("NoSnapReset")!==true)) {

        var di = this.getDocumentInterface();
        if (!isNull(di)) {
            if (!di.isSnapLocked()) {
                var guiAction = RGuiAction.getByScriptFile("scripts/Snap/SnapAuto/SnapAuto.js");
                if (!isNull(guiAction)) {
                    guiAction.slotTrigger();
                }
                di.setSnap(new RSnapAuto());

                guiAction = RGuiAction.getByScriptFile("scripts/Snap/RestrictOff/RestrictOff.js");
                if (!isNull(guiAction)) {
                    guiAction.slotTrigger();
                }
                di.setSnapRestriction(new RRestrictOff(di));
            }
        }
    }
};

/**
 * Called when this action is terminated.
 * 
 * Shows the GUI elements that refer to this action as un-checked. Hides GUI
 * options if this.uiFile is set to a valid UI file. Clears up mouse tips, etc.
 */
EAction.prototype.finishEvent = function() {
    if (this.hasNoState()) {
        return;
    }

    var guiAction = this.getGuiAction();

    // unckeck tool GUI action:
    if (!isNull(guiAction) && !isDeleted(guiAction)) {
        if (guiAction.getGroup().isEmpty() || guiAction.isOverride()) {
            guiAction.setChecked(false);
        }
    }

    this.hideUiOptions();

    // clear mouse tips:
    if (!isNull(EAction.getMainWindow())) {
        this.setLeftMouseTip("");
        this.setRightMouseTip("");
    }

    // reset CAD tool bar:
    if (!isNull(guiAction) && guiAction.getGroup() === "") {
        if (typeof(CadToolBar) !== "undefined") {
            if (CadToolBar.getCurrentPanelName()==="SnapToolsPanel") {
                CadToolBar.back();
            }
        }
    }

    // to remove snap info:
    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        di.repaintViews();
    }

    this.setCommandPrompt();
};

/**
 * Does nothing. Needs to be implemented here to avoid recursion when child
 * classes call the base class implementation.
 */
EAction.prototype.mousePressEvent = function(event) {
};

EAction.prototype.mouseReleaseEvent = function(event) {
    if (event.button() === Qt.RightButton) {
        this.escapeEvent();
    }
};

EAction.prototype.mouseDoubleClickEvent = function(event) {
    if (event.button() == Qt.RightButton) {
        // right double-click to reset:
        if (RSettings.getBoolValue("GraphicsView/RightDoubleClickToReset", false)) {
            var di = this.getDocumentInterface();
            if (!isNull(di)) {
                di.killAllActions();
            }
            EAction.showMainTools();
        }
    }
};

/**
 * Sets the UI options toolbar content for this tool. By default, a tool shows
 * the options toolbar defined in "DefaultOptions.ui".
 * 
 * \param uiFile A path to a single UI file or an array of UI file paths.
 * \param split If true, the options are split up into multiple toolbars.
 */
EAction.prototype.setUiOptions = function(uiFile, split) {
    if (isNull(split)) {
        split = false;
    }

    this.splitUiOptions = split;

    if (isNull(uiFile)) {
        this.uiFile = undefined;
        return;
    }

    if (isArray(uiFile)) {
        this.uiFile = uiFile;
    } else {
        this.uiFile = [ uiFile ];
    }
};

/**
 * Set the state of this action. Action implementations overwrite this function
 * to initialize this action for the given state. This includes setting the
 * appropriate click mode, displaying the appropriate CAD toolbar, setting
 * mouse tips, mouse cursor, etc.
 */
EAction.prototype.setState = function(state) {
    if (!isNumber(state)) {
        qWarning("EAction.prototype.setState: invalid state");
        debugger;
        return;
    }

    this.state = state;

    this.initState();

    if (state!==-1) {
        this.simulateMouseMoveEvent();
    }
};

/**
 * Called to initialize a new state of this action. Overwrite to
 * set mouse tips, show desired toolbars, etc.
 */
EAction.prototype.initState = function() {
};

/**
 * Called whenver the action resumes its operation, for example after it was
 * temporary suspended for another action.
 */
EAction.prototype.resumeEvent = function() {
    if (this.hasNoState()) {
        return;
    }

    var appWin = EAction.getMainWindow();

    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(true);
    }
    this.showUiOptions(true);
    if (!isNull(this.state)) {
        this.setState(this.state);
    }

    if (!this.optOutRelativeZeroResume) {
        // restore relative zero position when returning from another command:
        var di = this.getDocumentInterface();
        if (!isNull(di) && isValidVector(this.relativeZeroPos)) {
            if (EAction.noRelativeZeroResume===true) {
                EAction.noRelativeZeroResume = false;
            }
            else {
                di.setRelativeZero(this.relativeZeroPos);
            }
        }
        this.relativeZeroPos = undefined;
    }
};

/**
 * Called whenver the action is suspended, for example if another action is
 * started while this action is active.
 */
EAction.prototype.suspendEvent = function() {
    if (this.hasNoState()) {
        return;
    }

    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(false);
    }

    this.hideUiOptions();

    // store relative zero position:
    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        this.relativeZeroPos = di.getRelativeZero();
    }
};

/**
 * Shows the UI options of this action if this.uiFile is set. UI options are
 * typically shown in a horizontal toolbar at the top of the drawing area.
 * 
 * Usually this function does not need to be called directly by implementing
 * actions.
 * 
 * \param resume Action was resumed from suspension.
 * \param restoreFromSettings Restore settings from document / config file (default).
 */
EAction.prototype.showUiOptions = function(resume, restoreFromSettings) {
    if (isNull(restoreFromSettings)) {
        restoreFromSettings = true;
    }

    if (!isNull(this.optionWidgetActions)) {
        return;
    }

    if (this.optionsToolBarEnabled === false) {
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    if (isNull(optionsToolBar)) {
        qWarning("EAction.prototype.showUiOptions: no options toolbar");
        return;
    }

    this.optionWidgetActions = [];

    var guiAction = this.getGuiAction();
    if (!isNull(guiAction) &&
        guiAction.getGroup() !== "snaps" &&
        guiAction.getGroup() !== "snaprestrictions") {

        // automatically add icon of current action to toolbar:
        if (!guiAction.icon.isNull() && !guiAction.isOverride()) {
            var iconLabel = optionsToolBar.findChild("Icon");
            if (!isNull(iconLabel)) {
                iconLabel.toolTip = qsTr("Active Tool:") + " " + guiAction.text.replace("&", "");
                OptionsToolBar.setIcon(guiAction.icon);
                iconLabel.setFixedWidth(iconLabel.height + 12);
            }
        }
    }

    // add widgets from action specific options toolbar:
    if (isNull(this.uiFile)) {
        return;
    }

    this.resuming = true;

    this.optionWidgetActions = [];
    for (var i = 0; i < this.uiFile.length; ++i) {
        var uiFile = this.uiFile[i];
        var wOptions = this.createWidget(uiFile);
        //qDebug("adjust icons for uiFile: ", uiFile);

        if (isNull(wOptions)) {
            qWarning("Cannot create widget from UI file: ", uiFile);
            continue;
        }

        // create new toolbar for additional tool options:
        if (this.splitUiOptions === true && i != 0) {
            EAction.getMainWindow().addToolBarBreak();
            optionsToolBar = new QToolBar(EAction.getMainWindow());
            optionsToolBar.objectName = wOptions.objectName;
            EAction.getMainWindow().addToolBar(Qt.TopToolBarArea, optionsToolBar);
            if (isNull(this.additionalOptionsToolBars)) {
                this.additionalOptionsToolBars = [];
            }
            this.additionalOptionsToolBars.push(optionsToolBar);
        }

        // show:
        this.settingsGroup = wOptions.objectName;
        this.optionWidgetActions = this.optionWidgetActions
                .concat(WidgetFactory.moveChildren(wOptions, optionsToolBar,
                        this.settingsGroup));

        // required for undocked options tool bar:
        if (optionsToolBar.floating) {
            optionsToolBar.resize(optionsToolBar.sizeHint.width(), optionsToolBar.height);
        }
        wOptions.destroy();

        // automatically add separator to toolbar:
        var a = optionsToolBar.addSeparator();
        a.objectName = "LastSeparator";
        this.optionWidgetActions.push(a);

        // give action a chance to initialize toolbar widgets that cannot
        // be initialized in Qt Designer:
        this.initUiOptions(resume, optionsToolBar);

        // restore previously stored state:
        if (restoreFromSettings===true) {
            WidgetFactory.restoreState(optionsToolBar, this.settingsGroup, this);
        }
    }

    // hide options tool bar widgets which are shown in a dialog instead:
    this.hideOptionsToolBarWidgets();

    this.resuming = false;
};

/**
 * Overwrite to initialize combo boxes and other UI elements of the options tool
 * bar.
 */
EAction.prototype.initUiOptions = function(resume, optionsToolBar) {
    var prefixChar = RSettings.getStringValue("ToolBar/PrefixChar", ",");

    if (isNull(optionsToolBar)) {
        return;
    }

    var children = optionsToolBar.children();
    for (var i=0; i<children.length; i++) {
        var child = children[i];
        var shortCut = child.shortcut;
        if (!isNull(shortCut) && !shortCut.isEmpty()) {
            var str = shortCut.toString();
            var firstChar = str[0];

            // if first key is Ctrl then the string starts with Ctrl+
            // so check for a + sign, which indicates a modifier key has been used
            // '+' and '-' should not be used as prefix, as they zoom in and out
            if (str.indexOf('+') === -1) {                       // no plus sign
                if (firstChar >= '!' && firstChar <= '~') {      // isgraph()
                    str = str.replace(firstChar, prefixChar);
                    child.shortcut = new QKeySequence(str);
                    child.toolTip = RGuiAction.formatToolTip(child.toolTip, str);
                }
            }
        }
    }
};

/**
 * Hides the UI options of this action.
 * 
 * Usually this function does not need to be called directly by implementing
 * actions.
 * \param saveToSettings if true, the state is saved to settings
 */
EAction.prototype.hideUiOptions = function(saveToSettings) {
    if (isNull(saveToSettings)) {
        saveToSettings = true;
    }
    if (isNull(this.optionWidgetActions)) {
        return;
    }

    if (this.optionsToolBarEnabled === false) {
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    if (isNull(optionsToolBar)) {
        return;
    }

    if (saveToSettings) {
        WidgetFactory.saveState(optionsToolBar, this.settingsGroup);
    }

    // automatically reset icon of current action from toolbar:
    if (!isNull(this.getGuiAction()) &&
            this.getGuiAction().getGroup() !== "snaps" &&
            this.getGuiAction().getGroup() !== "snaprestrictions") {

        if (!this.getGuiAction().icon.isNull()) {
            var iconLabel = optionsToolBar.findChild("Icon");
            if (!isNull(iconLabel)) {
                OptionsToolBar.setIcon("scripts/Reset/Reset.svg");
                iconLabel.toolTip = qsTr("Active Tool:") + " " + qsTr("None");
            }
        }
    }

    // delete all option widgets / actions of this tool:
    var i;
    while (this.optionWidgetActions.length>0) {
        var a = this.optionWidgetActions.pop();
        if (!isNull(optionsToolBar)) {
            optionsToolBar.removeAction(a);
        }
        a.destroy();
    }

    // delete additional toolbars of this tool if available:
    if (!isNull(this.additionalOptionsToolBars)) {
        for (i = 0; i < this.additionalOptionsToolBars.length; ++i) {
            var tb = this.additionalOptionsToolBars[i];
            if (isDeleted(tb)) {
                continue;
            }
            tb.destroy();
        }
    }

    // required for undocked options tool bar:
    if (optionsToolBar.floating) {
        optionsToolBar.resize(optionsToolBar.sizeHint.width(), optionsToolBar.height);
    }

    this.optionWidgetActions = undefined;
    this.additionalOptionsToolBars = undefined;
};

/**
 * Hides all widgets in the options tool bar which are shown in the tool dialog instead.
 */
EAction.prototype.hideOptionsToolBarWidgets = function(widgets, noSyncWidgets) {
    if (!this.useDialog) {
        return;
    }

    if (isNull(widgets)) {
        widgets = [];
    }
    if (isNull(noSyncWidgets)) {
        noSyncWidgets = [];
    }

    // collect widgets which are tagged to be shown in the dialog:
    var i, c;
    //var widgets = [];
    //var noSyncWidgets = [];
    var optionsToolBar = EAction.getOptionsToolBar();
    var children = optionsToolBar.children();
    for (i = 0; i < children.length; ++i) {
        c = children[i];
        if (c["HideInDialogMode"]===true) {
            c.destroy();
        }
        else if (c["MoveToDialog"]===true) {
            widgets.push(c);
        }
        else {
            if (isQWidget(c)) {
                noSyncWidgets.push(c);
            }
        }
    }

    if (widgets.length===0) {
        // no widgets to show in dialog, return to normal operation without dialog:
        return;
    }

    WidgetFactory.saveState(optionsToolBar, this.settingsGroup);

    for (i = 0; i < widgets.length; i++) {
        var a = optionsToolBar.findChild(widgets[i].objectName + "Action");
        if (!isNull(a)) {
            a.visible = false;
        }
    }

    // remove double separators:
    OptionsToolBar.normalizeSeparators(this);
};

/**
 * Called when user presses enter. Default implementation calls showDialog if configured.
 */
EAction.prototype.enterEvent = function() {
    if (RSettings.getBoolValue("Transform/EnterShowsDialog", false)===true) {
        this.showDialog();
    }
};

/**
 * Show dialog to enter some or all of the options.
 * The default implementation creates a dialog based on this.dialogUiFile.
 * Widgets in the options tool bar which have the property "MoveToDialog" or
 * "HideInDialogMode" set are hidden in the options tool bar.
 */
EAction.prototype.showDialog = function() {
    if (!this.useDialog) {
        return QDialog.Rejected;
    }

    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        di.clearPreview();
        di.repaintViews();
    }

    var widgets = [];
    var noSyncWidgets = [];

    this.hideOptionsToolBarWidgets(widgets, noSyncWidgets);

    // show dialog and move tool bar widgets to its layout:
    var formLayout = undefined;
    if (isNull(this.dialogUiFile)) {
        return QDialog.Rejected;
    }

    this.dialog = WidgetFactory.createDialog(this.includeBasePath, this.dialogUiFile, EAction.getMainWindow());
    this.initUiOptions(false, this.dialog);
    WidgetFactory.restoreState(this.dialog, this.settingsGroup, this);
    var title = this.getToolTitle();
    if (title.indexOf("\t")!==-1) {
        // remove shortcuts Windows:
        title = title.replace(/\t.*/g, "");
    }
    this.dialog.windowTitle = title;
    this.dialog.windowIcon = new QIcon();

    // give focus to control with custom property 'DefaultFocus':
    var children = this.dialog.children();
    var i;
    for (i=0; i<children.length; i++) {
        if (children[i].property("DefaultFocus")===true) {
            children[i].setFocus();
            if (isFunction(children[i].selectAll)) {
                // select all text in line edits:
                children[i].selectAll();
            }
            break;
        }
    }

    this.initDialog(this.dialog);

    var ret = this.dialog.exec();

    // TODO:
    //WidgetFactory.saveState(this.dialog, "Shape");
    WidgetFactory.saveState(this.dialog, this.settingsGroup);

    // sync invisible part of options tool bar with dialog:
    for (i=0; i<noSyncWidgets.length; i++) {
        if (isDeleted(noSyncWidgets[i])) {
            continue;
        }

        noSyncWidgets[i].setProperty("Loaded", true);
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    WidgetFactory.restoreState(optionsToolBar, this.settingsGroup, this);

    for (i=0; i<noSyncWidgets.length; i++) {
        if (isDeleted(noSyncWidgets[i])) {
            continue;
        }

        noSyncWidgets[i].setProperty("Loaded", false);
    }

    this.dialog.destroy();
    this.dialog = undefined;

//    var view = EAction.getGraphicsView();
//    if (!isNull(view)) {
//        // view loses focus because of dialog:
//        view.giveFocus();
//    }

    EAction.activateMainWindow();

    this.simulateMouseMoveEvent();
    //this.updatePreview(true);

    return ret;
};

/**
 * Called before dialog is shown. Default implementation does nothing.
 */
EAction.prototype.initDialog = function(dialog) {
};

/**
 * Called if the user clicks the reset button of an action. A reset button may
 * be displayed as part of the UI options of this action and must have the
 * object name "Reset".
 */
EAction.prototype.slotReset = function() {
    if (this.optionsToolBarEnabled === false) {
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    if (isNull(optionsToolBar)) {
        return;
    }
    WidgetFactory.resetState(optionsToolBar, this.settingsGroup);
};

/**
 * Called when the user presses Escape or clicks the right mouse button.
 */
EAction.prototype.escapeEvent = function() {
    this.setArrowCursor();
    this.getDocumentInterface().clearPreview();
    this.getDocumentInterface().repaintViews();
    this.terminate();
};

/**
 * Called when the user presses a key. By default, the event is ignored.
 */
EAction.prototype.keyPressEvent = function(event) {
    if (isNull(event)) {
        return;
    }

    // prevent focus shift when entering keycode (e.g. "D2"):
    var appWin = EAction.getMainWindow();
    if (appWin.getKeyLog().length===0) {
        if ((event.key() >= Qt.Key_0.valueOf() && event.key() <= Qt.Key_9.valueOf()) || event.key() === Qt.Key_Period.valueOf()) {
            // number or dot entered:
            // give focus to first input widget in options tool bar and set text to number entered:
            var w = OptionsToolBar.getFirstInputWidget();
            if (!isNull(w)) {
                w.setFocus(Qt.OtherFocusReason);
                w.text = String.fromCharCode(event.key());
                event.accept();
                return;
            }
        }
    }

    event.ignore();
};

/**
 * Called when the user releases a key. By default, the event is ignored.
 */
EAction.prototype.keyReleaseEvent = function(event) {
    event.ignore();
};

/**
 * Sets the current cursor of the current document interface (all views attached
 * to it) to crosshair cursor.
 */
EAction.prototype.setCrosshairCursor = function() {
    if (isNull(EAction.crossCursor)) {
        var bitmap, mask
        if (RSettings.getDevicePixelRatio()===2 && RS.getSystemId()!=="osx") {
            bitmap = new QBitmap(EAction.includeBasePath + "/CrosshairCursor@2x.png", "PNG");
            mask = new QBitmap(EAction.includeBasePath + "/CrosshairCursorMask@2x.png", "PNG");
            //bitmap.setDevicePixelRatio(2);
            //mask.setDevicePixelRatio(2);
            EAction.crossCursor = new QCursor(bitmap, mask, 30, 30);
        }
        else {
            bitmap = new QBitmap(EAction.includeBasePath + "/CrosshairCursor.png", "PNG");
            mask = new QBitmap(EAction.includeBasePath + "/CrosshairCursorMask.png", "PNG");
            EAction.crossCursor = new QCursor(bitmap, mask, 15, 15);
        }
    }

    this.setCursor(EAction.crossCursor, "CrossCursor");
};

/**
 * Sets the current cursor of the current document interface (all views attached
 * to it) to the normal arrow cursor.
 */
EAction.prototype.setArrowCursor = function() {
    this.setCursor(new QCursor(Qt.ArrowCursor));
};

EAction.prototype.setCursor = function(cursor, name) {
    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        di.setCursor(cursor);
    }
//    if (!isNull(name)) {
//        var views = this.getGraphicsViews();
//        for (var i=0; i<views.length; i++) {
//            if (isFunction(views[i].setProperty)) {
//                views[i].setProperty("CursorName", name);
//            }
//        }
//    }
};

/**
 * Creates a new widget based on the given UI file with the given parent. This
 * is a helper function for WidgetFactory.createWidget.
 */
EAction.prototype.createWidget = function(uiFile, parent) {
    return WidgetFactory.createWidget(this.includeBasePath, uiFile, parent);
};

/**
 * Creates a new dialog based on the given UI file with the given parent. This
 * is a helper function for WidgetFactory.createDialog.
 */
EAction.prototype.createDialog = function(uiFile, parent) {
    return WidgetFactory.createDialog(this.includeBasePath, uiFile, parent);
};

/**
 * \return The current document or null.
 */
EAction.getDocument = function() {
    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return undefined;
    }
    return di.getDocument();
};

/**
 * \return The storage of the current document or null.
 */
EAction.getStorage = function() {
    var doc = EAction.getDocument();
    if (isNull(doc)) {
        return undefined;
    }
    return doc.getStorage();
};

EAction.prototype.getDocumentInterface = function() {
    if (!isNull(global.gDocumentInterface)) {
        return global.gDocumentInterface;
    }

    return RAction.prototype.getDocumentInterface.call(this);
};

/**
 * \return The current document interface or null.
 */
EAction.getDocumentInterface = function() {
    if (!isNull(global.gDocumentInterface)) {
        return global.gDocumentInterface;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }

    return appWin.getDocumentInterface();
};

/**
 * \return The current main window.
 */
EAction.getMainWindow = function() {
    if (!isNull(global.gMainWindow)) {
        return global.gMainWindow;
    }

    return RMainWindowQt.getMainWindow();
};

/**
 * Reactivates the main window after showing a dialog.
 * This is necessary with Qt>=5.
 * Not necessary with Qt>=5.10.
 */
EAction.activateMainWindow = function() {
//    if (RSettings.isQt(5)) {
//        var appWin = EAction.getMainWindow();
//        if (isNull(appWin)) {
//            return;
//        }
//        appWin.activateWindow();

//        var view = EAction.getGraphicsView();
//        if (!isNull(view)) {
//            // view loses focus because of dialogs:
//            view.giveFocus();
//        }
//    }
};

/**
 * \return The current MDI child or null.
 */
EAction.getMdiChild = function() {
    var appWin = RMainWindowQt.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }
    return appWin.getMdiChild();
};

/**
 * \return The MDI area or null.
 */
EAction.getMdiArea = function() {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }
    return appWin.getMdiArea();
};

/**
 * \return List of all graphics views attached to the current document interface.
 */
EAction.prototype.getGraphicsViews = function() {
    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return [];
    }

    return EAction.getGraphicsViews(di);

};

EAction.getGraphicsViews = function(di) {
    var ret = [];
    var scenes = di.getGraphicsScenes();
    for (var i=0; i<scenes.length; i++) {
        var views = scenes[i].getGraphicsViews();
        ret = ret.concat(views);
    }
    return ret;
}

EAction.prototype.getGraphicsView = function() {
    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return undefined;
    }

    return di.getLastKnownViewWithFocus();
};

/**
 * \return Graphics view with focus or last known graphics view with focus.
 */
EAction.getGraphicsView = function() {
    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return undefined;
    }

    return di.getLastKnownViewWithFocus();
};

/**
 * \return the existing menu with the given object name or, if no such menu
 * exists, a new menu with the given title and the given object name.
 * 
 * \param title Translated title to use for the menu. E.g. qsTr("&File"). \param
 * objectName Object name to use for the menu. Used mainly for later
 * identification of the menu. E.g. "file". \param initFunction Function that is
 * called only if a new menu is created. Used to initialize the menu, e.g.
 * connecting signals, etc.
 */
EAction.getMenu = function(title, objectName, initFunction) {
    if (isNull(objectName)) {
        objectName = "";
    }
    var appWin = EAction.getMainWindow();
    var menuBar = appWin.menuBar();
    var menu;
    for ( var i in menuBar.children()) {
        menu = menuBar.children()[i];
        if (menu.objectName === objectName) {
            break;
        }
        menu = undefined;
    }
    if (isNull(menu)) {
        menu = new QMenu(title, menuBar);
        menu.objectName = objectName;
        menuBar.addMenu(menu);
        if (initFunction != undefined) {
            initFunction(menu);
        }
    }
    return menu;
};

/**
 * \return the existing submenu with the given object name or creates a new
 * submenu as child of the given menu, with the given sort order, title and
 * icon.
 * 
 * \param menu Parent menu.
 * \param sortOrder Sort oder among other submenus. All
 *      submenus within the same menu are ordered by this number.
 * \param title Translated title of the submenu. E.g. qsTr("&Line").
 * \param objectName Object name to use for the menu. Used mainly for
 *      later identification of the menu.
 * E.g. "line". \param iconFile Path and file name of icon to use for this
 * submenu.
 */
EAction.getSubMenu = function(menu, groupSortOrder, sortOrder, title, objectName, iconFile) {
    var subMenu = menu.findChild(objectName);
    if (isNull(subMenu)) {
        //var action = menu.addMenu(subMenu);

        var action = new RGuiAction(title, menu);
        action.objectName = objectName + "Action";
        //subMenu = new QMenu(title + " {%1,%2}".arg(groupSortOrder).arg(sortOrder), menu);
        subMenu = new QMenu(title, menu);
        subMenu.objectName = objectName;
        if (!isNull(iconFile)) {
            subMenu.icon = new QIcon(iconFile);
        }
        action.setMenu(subMenu);
        RGuiAction.setGroupSortOrderStatic(action, groupSortOrder);
        RGuiAction.setSortOrderStatic(action, sortOrder);
        RGuiAction.setWidgetNamesStatic(action, [menu.objectName]);

        // re-add action at correct position:
        //RGuiAction.addToWidget(action, menu);

//        subMenu = new QMenu(title, menu);

//        var subMenuActions = menu.actions();
//        var actionBefore = undefined;
//        for (var i = 0; i < subMenuActions.length; ++i) {
//            var so = subMenuActions[i].property("SortOrder");
//            if (!isNull(so) && so > sortOrder) {
//                actionBefore = subMenuActions[i];
//                break;
//            }
//        }
//        subMenu = new QMenu(title, menu);
//        if (!isNull(iconFile)) {
//            subMenu.icon = new QIcon(iconFile);
//        }

//        var separator;
//        if (addSeparator) {
//            separator = new RGuiAction("", RMainWindowQt.getMainWindow());
//            separator.setSeparator(true);
//            separator.setSortOrder(sortOrder - 1);
//            separator.addToMenu(menu);
//        }

//        var subMenuAction;
//        if (isNull(actionBefore)) {
//            subMenuAction = menu.addMenu(subMenu);
//        } else {
//            subMenuAction = menu.insertMenu(actionBefore, subMenu);
//        }
//        subMenu.objectName = objectName;
//        subMenuAction.setProperty("SortOrder", sortOrder);
    }
    return subMenu;
};

/**
 * \return Existing or new toolbar.
 * 
 * \param title Translated title of the toolbar. E.g. qsTr("Snap").
 * \param objectName Object name to use for the toolbar. Used mainly for later
 * identification of the toolbar. E.g. "line".
 * \param toolBarArea Area where the new toolbar should be added. Note that the
 * actual location where the toolbar is added may also depend on the previously
 * saved state of the tool bars. Defaults to Qt.TopToolBarArea.
 */
EAction.getToolBar = function(title, objectName, toolBarArea, category, before) {
    if (isNull(objectName)) {
        objectName = "";
    }
    if (isNull(toolBarArea)) {
        toolBarArea = Qt.TopToolBarArea;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }

    var tb;
    if (objectName.length !== 0) {
        tb = appWin.findChild(objectName);
    }

    if (!isNull(tb) && !isOfType(tb, QToolBar)) {
        qWarning("Not a toolbar: ", tb);
        return undefined;
    }

    if (isNull(tb)) {
        tb = new QToolBar(title);

        // style tool buttons in options toolbar:
        if (RSettings.isQt(5)) {
            if (!RSettings.hasCustomStyleSheet()) {
                if (RSettings.hasDarkGuiBackground()) {
                    tb.setStyleSheet(
                          "QToolButton {"
                             // make sure unchecked button renders with same size as checked
                             // prevents things from moving around when checking / unchecking
                        + "  border: 1px solid transparent;"
                        + "} "
                        + "QToolButton:checked { "
                        + "  border-top: 1px solid #161616;"
                        + "  border-left: 1px solid #161616;"
                        + "  border-bottom: 1px solid #777777;"
                        + "  border-right: 1px solid #777777;"
                        + "  background-color: #222222;"
                        + "}");
                }
                else {
                    tb.setStyleSheet(
                        "QToolButton {" +
                        "  border: 1px solid transparent;" +
                        "} " +
                        "QToolButton:checked { " +
                        "  border:1px solid #7f7f7f; " +
                        "  background: qlineargradient(x1:0 y1:0, x2:0 y2:1 stop:0 #c0c0c0, stop:0.1 #8a8a8a stop:0.2 #a3a3a3 stop:1 transparent); " +
                        "}");
                }
            }
        }
        tb.objectName = objectName;
        if (!isNull(category)) {
            tb.setProperty("Category", category);
        }
        var s = RSettings.getIntValue("ToolBar/IconSize", tb.iconSize.width());
        tb.iconSize = new QSize(s,s);
        if (isNull(before)) {
            appWin.addToolBar(toolBarArea, tb);
        }
        else {
            appWin.insertToolBar(before, tb);
        }
    }

    return tb;
};

/**
 * \return Existing or new dock.
 *
 * \param title Translated title of the dock widget. E.g. qsTr("Snap").
 * \param objectName Object name to use for the dock widget. Used mainly for later
 * identification of the dock widget. E.g. "line".
 * \param toolBarArea Area where the new dock should be added. Note that the
 * actual location where the dock is added may also depend on the previously
 * saved state of the docks. Defaults to Qt.LeftDockWidgetArea.
 */
EAction.getToolMatrixPanel = function(title, objectName, order) {
    if (isNull(objectName)) {
        objectName = "";
    }
    include("scripts/Widgets/CadToolMatrix/CadToolMatrix.js");
    return CadToolMatrix.getToolMatrixPanel(title, objectName, order);
};

/**
 * \return Existing or new options toolbar (used to display options for the
 * current tool).
 */
EAction.getOptionsToolBar = function() {
    var appWin = EAction.getMainWindow();
    if (isNull(EAction.optionsToolBar)) {
        if (!isNull(appWin)) {
            appWin.addToolBarBreak();
        }
        EAction.optionsToolBar = EAction.getToolBar(qsTr("Options"), "Options");
    }

    if (!isNull(EAction.optionsToolBar)) {
        if (!QCoreApplication.arguments().contains("-no-show")) {
            EAction.optionsToolBar.visible = true;
        }
    }

    return EAction.optionsToolBar;
};

/**
 * \return Existing or new block toolbar (used to display options for the
 * current block).
 */
//EAction.getBlockToolBar = function() {
//    if (isNull(EAction.blockToolBar)) {
//        EAction.blockToolBar = EAction.getToolBar(qsTr("Block Options"), "BlockOptions");
//    }

//    return EAction.blockToolBar;
//};

/**
 * \return The main (top) CAD toolbar panel.
 */
EAction.getMainCadToolBarPanel = function() {
    return EAction.getCadToolBarPanel(qsTr("Main Tools"), "MainToolsPanel", false);
};

/**
 * \return Existing or new CAD toolbar panel. Each CAD toolbar panel contains
 * a set of tools, e.g. to draw lines, change the snap tool, etc. The CAD tool
 * bar itself is created automatically when this function is called for the
 * first time.
 * 
 * \param title Translated title to use for the CAD toolbar panel. E.g.
 * qsTr("Snap"). \param objectName Object name to use for the panel. Used mainly
 * for later identification of the panel. E.g. "snap". \param hasBackButton True
 * to display a back button at the top or left to allow the user to navigate
 * back to the main CAD toolbar panel.
 */
EAction.getCadToolBarPanel = function(title, objectName, hasBackButton) {
    if (typeof(CadToolBar) === "undefined") {
        return undefined;
    }

    var appWin = EAction.getMainWindow();
    var cadToolBar = appWin.findChild("CadQToolBar");

    // create CAD toolbar if it does not exist already:
    if (isNull(cadToolBar)) {
        var toolBar = new QToolBar(qsTr("CAD Tools"), appWin);
        toolBar.objectName = "CadQToolBar";
        cadToolBar = new CadToolBar(toolBar);
        toolBar.addWidget(cadToolBar);
        cadToolBar.updateIconSize();

        toolBar.topLevelChanged.connect(function(onOff) {
            RSettings.setValue("CadToolBar/VerticalWhenFloating", false);
        });
        toolBar.orientationChanged.connect(function(orientation) {
            RSettings.setValue("CadToolBar/VerticalWhenFloating", false);
        });
    }

    return CadToolBar.getPanel(title, objectName, hasBackButton);
};

/**
 * Shows the CAD toolbar panel with the given objectName.
 */
EAction.showCadToolBarPanel = function(objectName) {
    if (typeof (CadToolBar) == "undefined") {
        return;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }

    CadToolBar.showPanel(objectName);
};

/**
 * Shows the CAD toolbar panel with the snap tools.
 */
EAction.showSnapTools = function() {
    EAction.showCadToolBarPanel("SnapToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the main tools.
 */
EAction.showMainTools = function() {
    EAction.showCadToolBarPanel("MainToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the point tools.
 */
EAction.showPointTools = function() {
    EAction.showCadToolBarPanel("PointToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the line tools.
 */
EAction.showLineTools = function() {
    EAction.showCadToolBarPanel("LineToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the arc tools.
 */
EAction.showArcTools = function() {
    EAction.showCadToolBarPanel("ArcToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the circle tools.
 */
EAction.showCircleTools = function() {
    EAction.showCadToolBarPanel("CircleToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the dimension tools.
 */
EAction.showDimensionTools = function() {
    EAction.showCadToolBarPanel("DimensionToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the ellipse tools.
 */
EAction.showEllipseTools = function() {
    EAction.showCadToolBarPanel("EllipseToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the spline tools.
 */
EAction.showSplineTools = function() {
    EAction.showCadToolBarPanel("SplineToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the polyline tools.
 */
EAction.showPolylineTools = function() {
    EAction.showCadToolBarPanel("PolylineToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the shape tools.
 */
EAction.showShapeTools = function() {
    EAction.showCadToolBarPanel("ShapeToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the modification tools.
 */
EAction.showModificationTools = function() {
    EAction.showCadToolBarPanel("ModifyToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the measuring / info tools.
 */
EAction.showInformationTools = function() {
    EAction.showCadToolBarPanel("InformationToolsPanel");
};

/**
 * Shows the CAD toolbar panel with the selection tools.
 */
EAction.showSelectTools = function() {
    EAction.showCadToolBarPanel("SelectToolsPanel");
};

/**
 * Helper function to conveniently add the given action to a menu, toolbar and
 * CAD toolbar.
 * 
 * \param action RAction object.
 * \param iface Interface to use to retrieve the appropriate menu, toolbar and CAD toolbar panel.
 * \param addToMenu True to add this action to the appropriate menu.
 * \param addToToolbar True to add this action to the appropriate toolbar.
 * \param addToCadToolbar True to add this action to the appropriate CAD toolbar panel.
 * \param addSeparator True to add a separator before this action.
 */
EAction.addGuiActionTo = function(action, iface, addToMenu, addToToolBar,
        addToCadToolBar, addSeparator) {

    var className = action.getScriptClass();

    if (isNull(addToMenu)) {
        addToMenu = false;
    }
    if (isNull(addToToolBar)) {
        addToToolBar = false;
    }
    if (isNull(addToCadToolBar)) {
        addToCadToolBar = false;
    }
    if (isNull(addSeparator)) {
        addSeparator = false;
    }

    if (className.length!==0) {
        var key = className + "/VisibleInMenu";
        addToMenu = RSettings.getBoolValue(key, addToMenu);
        if (!RSettings.hasValue(key)) {
            RSettings.setValue(key, addToMenu);
        }
        key = className + "/VisibleInToolBar";
        addToToolBar = RSettings.getBoolValue(key, addToToolBar);
        if (!RSettings.hasValue(key)) {
            RSettings.setValue(key, addToToolBar);
        }
        key = className + "/VisibleInCadToolBar";
        addToCadToolBar = RSettings.getBoolValue(key, addToCadToolBar);
        if (!RSettings.hasValue(key)) {
            RSettings.setValue(key, addToCadToolBar);
        }
    }

    if (isNull(iface)) {
        qWarning("EAction.js:", "addGuiActionTo(): iface not defined");
    }



    if (action.icon.isNull() && !action.isIconDisabled()) {
        action.setIcon(autoPath("scripts/Empty.svg"));
    }

    var separator;
    if (addSeparator) {
        separator = new RGuiAction("", RMainWindowQt.getMainWindow());
        separator.setSeparator(true);
        //separator.setSortOrder(action.getSortOrder() - 1);
    }

    if (addToMenu) {
        if (isFunction(iface.getMenu)) {
            var menu = iface.getMenu();
            if (!isNull(menu)) {
                if (!isNull(separator)) {
                    separator.addToMenu(menu);
                }
                action.addToMenu(menu);
            }
        }
    }

    if (addToToolBar) {
        if (isFunction(iface.getToolBar)) {
            var tb = iface.getToolBar();
            if (!isNull(tb)) {
                action.addToToolBar(tb);
                if (addSeparator) {
                    var sp = new RGuiAction("", RMainWindowQt.getMainWindow());
                    sp.setSeparator(true);
                    sp.setSortOrder(action.getSortOrder() - 1);
                    sp.addToToolBar(tb);
                }
            }
        }
    }

    if (addToCadToolBar) {
        if (isFunction(iface.getCadToolBarPanel)) {
            var ctb = iface.getCadToolBarPanel();
            if (!isNull(ctb)) {
//                if (!isNull(separator)) {
//                    CadToolBarPanel.prototype.addAction.call(ctb, separator);
//                }
                //CadToolBarPanel.prototype.addAction.call(ctb, action);
                //ctb.addAction(action);
                action.addToWidget(ctb);
            }
        }
    }
};

//EAction.addGuiActionToWidgets = function(action, widgetNames) {
//    var appWin = EAction.getMainWindow();
//    var className = action.getScriptClass();
//    var addToMenu, addToToolBar, addToCadToolBar;

//    if (className.length!==0) {
//        var key = className + "/VisibleInMenu";
//        addToMenu = RSettings.getBoolValue(key, addToMenu);
//        if (!RSettings.hasValue(key)) {
//            RSettings.setValue(key, addToMenu);
//        }
//        key = className + "/VisibleInToolBar";
//        addToToolBar = RSettings.getBoolValue(key, addToToolBar);
//        if (!RSettings.hasValue(key)) {
//            RSettings.setValue(key, addToToolBar);
//        }
//        key = className + "/VisibleInCadToolBar";
//        addToCadToolBar = RSettings.getBoolValue(key, addToCadToolBar);
//        if (!RSettings.hasValue(key)) {
//            RSettings.setValue(key, addToCadToolBar);
//        }
//    }

//    var i, w;
//    var oldWidgets = action.associatedWidgets();
//    for (i=0; i<oldWidgets.length; i++) {
//        w = oldWidgets[i];
//        w.removeAction(action);
//    }

//    for (i=0; i<widgetNames.length; i++) {
//        var wn = widgetNames[i];
//        w = appWin.findChild(wn);
//        action.addToWidget(w);
//    }
//};

/**
 * \return The boolean value of the given variable from the document if it
 * exists in the document, from the settings file if it exists there. If the
 * variable does not exist in the document nor the settings file, the given
 * defaultValue is returned.
 */
EAction.getBoolValue = function(varName, defaultValue, document) {
    if (isNull(document)) {
        document = EAction.getDocument();
    }

    if (!isNull(document)) {
        var val = document.getVariable(varName);
        if (typeof (val) != "undefined") {
            return val;
        }
    }
    return RSettings.getBoolValue(varName, defaultValue);
};

/**
 * \return The int value of the given variable from the document if it exists in
 * the document, from the settings file if it exists there. If the variable does
 * not exist in the document nor the settings file, the given defaultValue is
 * returned.
 */
EAction.getIntValue = function(varName, defaultValue, document) {
    if (isNull(document)) {
        document = EAction.getDocument();
    }

    if (!isNull(document)) {
        var val = document.getVariable(varName);
        if (typeof (val) != "undefined") {
            return parseInt(val, 10);
        }
    }
    return RSettings.getIntValue(varName, parseInt(defaultValue, 10));
};

/**
 * \return The float value of the given variable from the document if it exists
 * in the document, from the settings file if it exists there. If the variable
 * does not exist in the document nor the settings file, the given defaultValue
 * is returned.
 */
EAction.getDoubleValue = function(varName, defaultValue, document) {
    if (isNull(document)) {
        document = EAction.getDocument();
    }

    if (!isNull(document)) {
        var val = document.getVariable(varName);
        if (typeof (val) != "undefined") {
            return parseFloat(val);
        }
    }
    return RSettings.getDoubleValue(varName, parseFloat(defaultValue));
};

/**
 * \return The string value of the given variable from the document if it exists
 * in the document, from the settings file if it exists there. If the variable
 * does not exist in the document nor the settings file, the given defaultValue
 * is returned.
 */
EAction.getStringValue = function(varName, defaultValue, document) {
    if (isNull(document)) {
        document = EAction.getDocument();
    }

    if (!isNull(document)) {
        var val = document.getVariable(varName);
        if (typeof (val) != "undefined") {
            return val.toString();
        }
    }
    return RSettings.getStringValue(varName, defaultValue);
};

/**
 * \return The value of the given variable from the document if it exists in the
 * document, from the settings file if it exists there. If the variable does not
 * exist in the document nor the settings file, the given defaultValue is
 * returned.
 */
EAction.getValue = function(varName, defaultValue, document) {
    if (isNull(document)) {
        document = EAction.getDocument();
    }

    if (!isNull(document)) {
        var val = document.getVariable(varName, defaultValue);
        if (!isNull(val)) {
            return val;
        }
    }
    return RSettings.getValue(varName, defaultValue);
};

/**
 * Adds the given widgets to the status bar of the application.
 * \param sortOrder Defines the sort order of widgets in the status bar.
 */
EAction.addToStatusBar = function(widget, sortOrder) {
    include("scripts/Widgets/StatusBar/StatusBar.js");
    StatusBar.addWidget(widget, sortOrder);
};

EAction.prototype.getScales = function() {
    var doc = this.getDocument();
    if (isNull(doc)) {
        return [];
    }
    return EAction.getScales(doc.getUnit());
};

EAction.getScales = function(unit) {
    var scales;
    if (RUnit.isMetric(unit)) {
        // common metric scales:
        scales = new Array(
                "1:1", "1:2", "1:5", "1:10", "1:20", "1:25", "1:50", "1:75",
                "1:100", "1:125", "1:150", "1:175",
                "1:200", "1:250", "1:500", "1:750",
                "1:1000", "1:2500", "1:5000", "1:7500",
                "1:10000", "1:25000", "1:50000", "1:75000",
                "1:100000", "1:250000", "1:500000", "1:750000",
                "1:1000000",
                "2:1", "5:1", "10:1", "20:1", "25:1", "50:1", "75:1",
                "100:1", "125:1", "150:1", "175:1",
                "200:1", "250:1", "500:1", "750:1",
                "1000:1", "2500:1", "5000:1", "7500:1",
                "10000:1", "25000:1", "50000:1", "75000:1",
                "100000:1", "250000:1", "500000:1", "750000:1",
                "1000000:1");
    } else {
        // common imperial scales:
        scales = new Array(
                '1" = 1"', '1" = 2"', '1" = 4"', '1" = 8"', '1" = 16"',
                '1" = 32"', '1" = 64"', '1" = 128"', '1" = 256"',
                '1" = 512"', '1" = 1024"', '1" = 2048"', '1" = 4096"',
                '1/4096" = 1\'-0"', '1/2048" = 1\'-0"', '1/1024" = 1\'-0"',
                '1/512" = 1\'-0"', '1/256" = 1\'-0"', '1/128" = 1\'-0"',
                '1/64" = 1\'-0"', '1/32" = 1\'-0"', '1/16" = 1\'-0"',
                '1/8" = 1\'-0"', '1/4" = 1\'-0"', '3/4" = 1\'-0"', '1/2" = 1\'-0"',
                '1" = 1\'-0"', '2" = 1\'-0"', '3" = 1\'-0"', '4" = 1\'-0"',
                '5" = 1\'-0"', '6" = 1\'-0"', '7" = 1\'-0"', '8" = 1\'-0"',
                '9" = 1\'-0"', '10" = 1\'-0"', '11" = 1\'-0"');
    }
    return scales;
};

/**
 * Called by updatePreview. Implementations must return an ROperation subclass
 * object for the operation that should be previewed.
 */
EAction.prototype.getOperation = function(preview) {
    return undefined;
};

/**
 * Called by updatePreview. Implementations must return an array of RShape
 * objects that should be displayed as auxiliary construction.
 */
EAction.prototype.getAuxPreview = function() {
    return undefined;
};

/**
 * Called by updatePreview. Implementations must return an array of enitity IDs
 * which should be highlighted.
 */
EAction.prototype.getHighlightedEntities = function() {
    return undefined;
};

/**
 * Called by updatePreview. Implementations must handle errors during preview.
 */
EAction.prototype.handlePreviewError = function() {
    return;
};

/**
 * Updates the preview based on the operation returned by getOperation and the
 * auxiliary construction returned be getAuxPreview.
 * 
 * \param clear True to clear the preview first. This is necessary if the
 * preview is updated not as a result of a mouse move event, e.g. when changing
 * action parameters in the options toolbar.
 */
EAction.prototype.updatePreview = function(clear) {
    if (isNull(clear)) {
        clear = false;
    }

    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return;
    }

    if (clear === true) {
        di.clearPreview();
    }
    var op = this.getOperation(true);
    if (!isNull(op)) {
        di.previewOperation(op);
    }
    else {
        this.handlePreviewError();
    }

    var i;
    var previewShapes = this.getAuxPreview();
    if (!isNull(previewShapes)) {
        for (i = 0; i < previewShapes.length; ++i) {
            di.addAuxShapeToPreview(previewShapes[i]);
        }
    }

    var highlightedEntities = this.getHighlightedEntities();
    if (!isNull(highlightedEntities)) {
        for (i = 0; i < highlightedEntities.length; ++i) {
            di.highlightEntity(highlightedEntities[i]);
        }
    }

    di.repaintViews();
};

/**
 * Applies the operation returned by this.getOperation().
 */
EAction.prototype.applyOperation = function() {
    var di = this.getDocumentInterface();
    var op = this.getOperation(false);
    if (isNull(op)) {
        qWarning("Operation returned by this.getOperation() is undefined");
        return false;
    }
    this.complementOperation(op);
    di.applyOperation(op);
    return true;
};

/**
 * Can be reimplemented to complement the operation of an action.
 */
EAction.prototype.complementOperation = function(op) {
    return;
};

/**
 * High level event triggered when a coordinate was specified by the user of a
 * coordinate specification should be previewed.
 */
EAction.prototype.pickCoordinate = function(event, preview) {
};

/**
 * Default implementation. Calls pickCoordinate(event, false)
 */
EAction.prototype.coordinateEvent = function(event) {
    this.pickCoordinate(event, false);
};

/**
 * Default implementation. Calls pickCoordinate(event, true)
 */
EAction.prototype.coordinateEventPreview = function(event) {
    this.pickCoordinate(event, true);
};

/**
 * High level event triggered when an entity was picked by the user or to
 * preview picking an entity.
 */
EAction.prototype.pickEntity = function(event, preview) {
};

/**
 * Default implementation. Calls pickEntity(event, false)
 */
EAction.prototype.entityPickEvent = function(event) {
    this.pickEntity(event, false);
};

/**
 * Default implementation. Calls pickEntity(event, true)
 */
EAction.prototype.entityPickEventPreview = function(event) {
    this.pickEntity(event, true);
};

/**
 * High level event triggered when a command line command should be applied or
 * previewed.
 */
EAction.prototype.applyCommand = function(event, preview) {
};

/**
 * Default implementation. Calls applyCommand(event, false)
 */
EAction.prototype.commandEvent = function(event) {
    this.applyCommand(event, false);
};

/**
 * Default implementation. Calls applyCommand(event, true)
 */
EAction.prototype.commandEventPreview = function(event) {
    this.applyCommand(event, true);
};

EAction.prototype.simulateMouseMoveEvent = function() {
    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return;
    }

    var view = di.getLastKnownViewWithFocus();
    if (isNull(view)) {
        return;
    }

    if (isFunction(view.getRGraphicsView)) {
        view = view.getRGraphicsView();
    }

    if (isNull(view)) {
        return;
    }
    view.simulateMouseMoveEvent();
};

/**
 * Shows the given warning to the user.
 *
 * \param escape True to escape rich text and disaply the message
 * exactly as given (default), false to allow rich text in message
 * (colors, indentation, links, etc.)
 */
EAction.handleUserWarning = function(message, escape) {
    if (isNull(message)) {
        return;
    }
    if (isNull(escape)) {
        escape = true;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    appWin.handleUserWarning(message, false, escape);
};

EAction.handleUserMessage = function(message, escape) {
    if (isNull(message)) {
        return;
    }
    if (isNull(escape)) {
        escape = true;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    appWin.handleUserMessage(message, escape);
};

EAction.handleUserInfo = function(message, escape) {
    if (isNull(message)) {
        return;
    }
    if (isNull(escape)) {
        escape = true;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    appWin.handleUserInfo(message, escape);
};

EAction.handleUserCommand = function(message, escape) {
    if (isNull(message)) {
        return;
    }
    if (isNull(escape)) {
        escape = true;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    appWin.handleUserCommand(message, escape);
};

EAction.setProgress = function(p) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    appWin.setProgress(p);
};

EAction.setProgressText = function(t) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    EAction.handleUserMessage(t);
    appWin.setProgressText(t);
};

EAction.setProgressEnd = function() {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    appWin.setProgressEnd();
};

/**
 * Checks if the given entity is editable (not on a locked layer) and prints a
 * warning if quiet is false and this is not the case.
 */
EAction.assertEditable = function(entity, quiet) {
    if (!entity.isEditable()) {
        if (!quiet) {
            if (!entity.isInWorkingSet()) {
                EAction.handleUserWarning(qsTr("Entity is not in working set."));
            }
            else {
                EAction.handleUserWarning(qsTr("Entity is on a locked layer."));
            }
        }
        return false;
    }

    return true;
};

/**
 * Allows all actions to handle property change events. This is neccessary to
 * ensure that properties can be changed even if a tool is active (e.g. while
 * drawing lines).
 */
EAction.prototype.propertyChangeEvent = function(event) {
    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return;
    }

    var operation = new RChangePropertyOperation(event);
    di.applyOperation(operation);
    di.clearPreview();
    di.repaintViews();
};

EAction.prototype.setLeftMouseTip = function(tip) {
    var appWin = EAction.getMainWindow();
    if (!isNull(appWin) && isFunction(appWin.setLeftMouseTip)) {
        appWin.setLeftMouseTip(tip);
    }
};

EAction.prototype.setRightMouseTip = function(tip) {
    var appWin = EAction.getMainWindow();
    if (!isNull(appWin) && isFunction(appWin.setRightMouseTip)) {
        appWin.setRightMouseTip(tip);
    }
};

EAction.prototype.setCommandPrompt = function(prompt) {
    if (isNull(prompt)) {
        prompt = "";
    }

    var appWin = EAction.getMainWindow();
    if (!isNull(appWin) && isFunction(appWin.setCommandPrompt)) {
        appWin.setCommandPrompt(prompt);
    }
};

EAction.prototype.getToolTitle = function() {
    var guiAction = this.getGuiAction();
    if (isNull(guiAction)) {
        return "";
    }
    return guiAction.text.replace("&", "");
};

EAction.disableCoordinateWidget = function() {
    EAction.enableCoordinateWidget(false);
};

EAction.enableCoordinateWidget = function(enable) {
    if (isNull(enable)) {
        enable=true;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    var statusBar = appWin.findChild("StatusBar");
    if (isNull(statusBar)) {
        return;
    }
    var cd = statusBar.findChild("CoordinateDisplay");
    if (!isNull(cd)) {
        cd.enabled = enable;
    }
};

/**
 * \return ID of entity closest to the mouse cursor. No handling of ambiguous results.
 * \param event RRInputEvent
 * \param range Cursor range in pixels
 */
EAction.getEntityIdUnderCursor = function(di, event, range, selectable) {
    if (isNull(di)) {
        return [];
    }
    if (isNull(selectable)) {
        selectable = false;
    }

    var view = event.getGraphicsView();
    if (isNull(range)) {
        range = RSettings.getPickRange();
    }

    range = view.mapDistanceFromView(range);

    var strictRange = view.mapDistanceFromView(10);
    return di.getClosestEntity(event.getModelPosition(), range, strictRange, !selectable);
};

/**
 * \return Array of entity IDs of entities closest to the mouse cursor.
 * \param event RRInputEvent
 * \param range Cursor range in pixels
 */
EAction.getEntityIdsUnderCursor = function(di, event, range, selectable) {
    if (isNull(di)) {
        return [];
    }
    if (isNull(selectable)) {
        selectable = false;
    }

    var view = event.getGraphicsView();
    if (isNull(range)) {
        range = RSettings.getPickRange();
    }

    range = view.mapDistanceFromView(range);

    var doc = di.getDocument();
    return doc.queryIntersectedEntitiesXY(new RBox(event.getModelPosition(), range), false, !selectable);
};

/**
 * \return Entity ID under the mouse cursor. User may choose between multiple candidates if
 * result is ambiguous and Alt key is pressed.
 *
 * \param event RInputEvent
 * \param preview for previewing purposes
 * \param selectable Only return selectable (editable) entities
 */
EAction.prototype.getEntityId = function(event, preview, selectable) {
    if (isNull(preview)) {
        preview = false;
    }
    if (isNull(selectable)) {
        selectable = false;
    }

    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return RObject.INVALID_ID;
    }

    return EAction.getEntityId(di, this, event, preview, selectable);
};

EAction.getEntityId = function(di, action, event, preview, selectable) {
    if (isNull(preview)) {
        preview = false;
    }
    if (isNull(selectable)) {
        selectable = false;
    }

    var altPressed = isAltPressed(event);
    if (!altPressed || preview || RSettings.getBoolValue("GraphicsView/DisableAltPicking", false)===true) {
        if (!isNull(action.idFromContextMenu)) {
            // user already chose an entity from the context menu:
            return action.idFromContextMenu;
        }
        else {
            return EAction.getEntityIdUnderCursor(di, event, undefined, selectable);
        }
    }

    // fixed range, we never want to show a lot of entities in the context menu:
    var r = 10 * (RSettings.getHighResolutionGraphicsView() ? RSettings.getDevicePixelRatio() : 1);
    var entityIds = EAction.getEntityIdsUnderCursor(di, event, r, selectable);
    entityIds = di.getStorage().orderBackToFront(entityIds);
    if (entityIds.length===0) {
        // no entity under cursor:
        return RObject.INVALID_ID;
    }

    if (entityIds.length===1) {
        // one single entity under cursor:
        return entityIds[0];
    }

    // multiple entities under cursor, offer context menu:
    var ret = RObject.INVALID_ID;
    var doc = di.getDocument();
    var menu = new QMenu(EAction.getGraphicsView());
    menu.objectName = "EntityContextMenu";

    // reacts to hovering and clicking of context menu items:
    function Reactor(id) {
        this.id = id;
    }
    Reactor.prototype.trigger = function() {
        ret = this.id;
    };
    Reactor.prototype.hover = function() {
        di.clearPreview();
        di.highlightEntity(this.id);
        action.idFromContextMenu = this.id;
        action.entityPickEventPreview(event);
        action.idFromContextMenu = undefined;
        di.repaintViews();
    };

    // invalid entity id is used to to cancel:
    entityIds.push(RObject.INVALID_ID);

    var a, reactor;
    for (var i=0; i<entityIds.length && i<20; i++) {
        var id = entityIds[i];
        var str;
        var icon = undefined;
        if (id!==RObject.INVALID_ID) {
            var e = doc.queryEntityDirect(id);
            str = entityTypeToString(e.getType(), false);
            //str += " / " + e.getProperty(REntity.PropertyDisplayedColor)[0].getName();
            str += " / " + e.getLayerName();
            if  (isFunction(e.getLength)) {
                var l = e.getLength();
                if (isNumber(l)) {
                    str += " / " + qsTr("Length:") + " " + numberToString(e.getLength(), 3);
                }
            }
            var col = e.getProperty(REntity.PropertyDisplayedColor, true)[0];
            if (!isNull(col)) {
                icon = RColor.getIcon(col, new QSize(16,16));
            }
        }
        else {
            str = qsTr("Cancel");
            menu.addSeparator();
        }

        // add menu entry in format [Type] / [Layer] / [Color] / [Length]
        a = menu.addAction(str);
        if (!isNull(icon)) {
            a.icon = icon;
        }

        reactor = new Reactor(id);
        a.triggered.connect(reactor, "trigger");
        a.hovered.connect(reactor, "hover");
    }

    // show context menu:
    if (!menu.isEmpty()) {
        var prev = QCoreApplication.testAttribute(Qt.AA_DontShowIconsInMenus);
        QCoreApplication.setAttribute(Qt.AA_DontShowIconsInMenus, false);
        this.waitingForContextMenu = true;
        menu.exec(new QPoint(QCursor.pos().x(), QCursor.pos().y()+10));
        this.waitingForContextMenu = false;
        QCoreApplication.setAttribute(Qt.AA_DontShowIconsInMenus, prev);
        di.clearPreview();
    }

    return ret;
};

EAction.prototype.isEntitySnappable = function(e) {
    if (!isEntity(e)) {
        return false;
    }

    var layerId = e.getLayerId();
    var data = e.getData();
    var doc = data.getDocument();
    if (isNull(doc)) {
        return false;
    }

    return doc.isLayerSnappable(layerId);
};

/**
 * Some common, shared translated warnings:
 */
EAction.warnNotBlockReference = function() {
    EAction.handleUserWarning(qsTr("Entity is not a block reference."));
};

EAction.warnNotLineArc = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line or arc."))
};

EAction.warnNotLineArcPolyline = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line, arc or polyline."))
};

EAction.warnNotLine = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line."));
};

EAction.warnNotArc = function() {
    EAction.handleUserWarning(qsTr("Entity is not an arc."));
};

EAction.warnNotArcCircle = function() {
    EAction.handleUserWarning(qsTr("Entity is not an arc or circle."));
};

EAction.warnNotLineArcCircle = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line, arc or circle."));
};

EAction.warnNotArcCircleEllipse = function() {
    EAction.handleUserWarning(qsTr("Entity is not an arc, circle or ellipse."));
};

EAction.warnNotLineArcCircleEllipse = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line, arc, circle or ellipse."));
};

EAction.warnNotLineArcCircleEllipsePolyline = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line, arc, circle, ellipse or polyline."));
};

EAction.warnNotLineArcCircleEllipseSpline = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line, arc, circle, ellipse or spline."));
};

EAction.warnNotLineArcCircleSplinePolyline = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line, arc, circle, spline or polyline."));
};

EAction.warnNotLineArcCircleEllipseSplinePolyline = function() {
    EAction.handleUserWarning(qsTr("Entity is not a line, arc, circle, ellipse, spline or polyline."));
};

EAction.warnNotPolyline = function() {
    EAction.handleUserWarning(qsTr("Entity is not a polyline."));
};

EAction.warnNotSplineWithFitPoints = function() {
    EAction.handleUserWarning(qsTr("Entity is not a spline with fit points."));
};
