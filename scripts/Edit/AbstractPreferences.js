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

include("../AddOn.js");
include("Edit.js");

function AbstractPreferences(guiAction, appPreferences, initialClassName) {
    Edit.call(this, guiAction);
    if (isNull(appPreferences)) {
        appPreferences = true;
    }
    this.appPreferences = appPreferences;
    this.restartWarningShown = false;
    this.initialClassName = initialClassName;
}

AbstractPreferences.prototype = new Edit();
AbstractPreferences.includeBasePath = includeBasePath;

AbstractPreferences.prototype.beginEvent = function() {
    Edit.prototype.beginEvent.call(this);
    
    this.dialog = this.createWidget(AbstractPreferences.includeBasePath + "/AbstractPreferences.ui");
    // TODO: Qt 5: add this flag (?)
    //var flags = new Qt.WindowFlags(Qt.WindowTitleHint);
    //this.dialog.setWindowFlags(flags);
    this.treeWidget = this.dialog.findChild("twCategory");
    var title;
    if (this.appPreferences) {
        title = qsTr("Application Preferences");
    } else {
        title = qsTr("Drawing Preferences");
    }
    this.dialog.setWindowTitle(title);
    this.treeWidget.setHeaderLabel(title);
    this.pageWidget = this.dialog.findChild("stwPage");
    this.filterWidget = this.dialog.findChild("leFilter");
    this.titleWidget = this.dialog.findChild("lbTitle");
    
    var splitter = this.dialog.findChild("splitter");
    splitter.setStretchFactor(0, 1);
    splitter.setStretchFactor(1, 4);
    
    // connections:
    this.treeWidget.itemSelectionChanged.connect(this, "showPage");
    this.filterWidget.textChanged.connect(this, "filterTree");    

    var btApply = this.dialog.findChild("buttonBox").button(QDialogButtonBox.Apply);
    btApply.clicked.connect(this, "apply");

    this.addOns = AddOn.getAddOns();

    AbstractPreferences.fillTreeWidget(this.addOns, this.treeWidget, this.appPreferences);
    this.treeWidget.expandAll();

    if (!isNull(this.initialClassName)) {
        this.showPageFor(this.initialClassName);
    }

    if (this.dialog.exec() === QDialog.Accepted.valueOf()) {
        // apply calls save and apply:
        this.apply();
    }
    this.uninit();
    this.dialog.destroy();
    EAction.activateMainWindow();
    this.terminate();
};

/**
 * Initializes the navigation tree based on available add-ons with preferences.
 */
AbstractPreferences.fillTreeWidget = function(addOns, treeWidget, appPreferences) {
    for (var i = 0; i < addOns.length; ++i) {
        var addOn = addOns[i];
        var className = addOn.getClassName();

        var scriptFile = addOn.getFilePath();
        if (appPreferences===false) {
            if (!scriptFile.contains("DrawingPreferences")) {
                continue;
            }
        }

        try {
            // include normally not needed
            var doInclude = false;
            if (isNull(global[className])) {
                doInclude = true;
            }
            if(doInclude) {
                include(addOn.getFilePath());
            }
        } catch (e1) {
            qWarning("AppPreferences.js: Exception: ", e1);
            continue;
        }
        var cat;
        cat = undefined;
        try {
            if (!isNull(global[className]) && isFunction(global[className].getPreferencesCategory)) {
                cat = global[className].getPreferencesCategory(appPreferences);
            }
            if (isNull(cat)) {
                continue;
            }
        } catch (e2) {
            qWarning("AppPreferences.js: Add-on class not found: ", className, " exception: ", e2);
            continue;
        }
        
        if (!addOn.preferenceFileExists()) {
            continue;
        }

        // update tree
        var items = treeWidget.findItems(cat[0], Qt.MatchFixedString);
        var item;
        item = undefined;
        if (items.length === 0) {
            item = new QTreeWidgetItem(treeWidget, [ cat[0] ]);
            treeWidget.addTopLevelItem(item);
            if (cat.length === 1) {
                item.setData(0, Qt.UserRole, i);
            }
        } else {
            item = items[0];
        }
        var parent = item;
        for (var x = 1; x < cat.length; ++x) {
            var subitem;
            subitem = undefined;
            for (var c = 0; c < parent.childCount(); ++c) {
                var child = parent.child(c);
                if (child.text(0) === cat[x]) {
                    subitem = child;
                    break;
                }
            }
            if (isNull(subitem)) {
                subitem = new QTreeWidgetItem(parent, [ cat[x] ]);
                parent.addChild(subitem);
                if (x == cat.length - 1) {
                    subitem.setData(0, Qt.UserRole, i);
                }
            }
            parent = subitem;
        }
    }
    treeWidget.sortItems(0, Qt.AscendingOrder);
};

/**
 * Applies the settings of all preference pages by calling
 * 'applyPreferences' for every add-on class.
 */
AbstractPreferences.prototype.apply = function() {
    var mdiChild, document;

    // force all settings to be reloaded from RSettings when they are
    // used next time:
    RSettings.resetCache();
    
    this.save();

    for (var i = 0; i < this.addOns.length; ++i) {
        var addOn = this.addOns[i];
        var className = addOn.getClassName();
        
        var widget = addOn.getPreferenceWidget();
        if (isNull(widget) || widget.hasChanged !== true) {
            continue;
        }

        try {
            // include normally not needed
            var doInclude = false;
            if (isNull(global[className])) {
                doInclude = true;
            }
            if (doInclude) {
                include(addOn.getFilePath());
            }

            // apply application settings globally:
            if (this.appPreferences) {
                if (!isNull(global[className]) && isFunction(global[className].applyPreferences)) {
                    global[className].applyPreferences(undefined, undefined, widget);
                }

                var mdiArea = EAction.getMdiArea();
                var mdiChildren = mdiArea.subWindowList();
                for (var j = 0; j < mdiChildren.length; ++j) {
                    mdiChild = mdiChildren[j];
                    document = mdiChild.getDocument();
                    if (!isNull(global[className]) && isFunction(global[className].applyPreferences)) {
                        global[className].applyPreferences(document, mdiChild, widget);
                    }
                }
            }

            // apply document specific settings to current document:
            else {
                mdiChild = EAction.getMdiChild();
                document = EAction.getDocument();
                if (!isNull(global[className]) && isFunction(global[className].applyPreferences)) {
                    global[className].applyPreferences(document, mdiChild, widget);
                }
            }
        } catch (e) {
            qWarning("AbstractPreferences.js:",
                "apply(): Exception: %1; %2; %3"
                .arg(e.message).arg(e.fileName).arg(e.lineNumber));
            continue;
        }
    }

    var di = EAction.getDocumentInterface();
    if (!isNull(di)) {
        di.regenerateScenes();
    }

    var appWin = EAction.getMainWindow();
    if (this.appPreferences) {
        appWin.notifyPreferencesListeners(null);
    }
    else {
        appWin.notifyPreferencesListeners(di);
    }
};

/**
 * Cleans up settings of all preference pages by calling
 * 'uninitPreferences' for every add-on class.
 */
AbstractPreferences.prototype.uninit = function() {
    var mdiChild, document;

    for (var i = 0; i < this.addOns.length; ++i) {
        var addOn = this.addOns[i];
        var className = addOn.getClassName();

        var widget = addOn.getPreferenceWidget();
        if (isNull(widget) || widget.hasChanged !== true) {
            continue;
        }

        try {
            // include normally not needed
            var doInclude = false;
            if (isNull(global[className])) {
                doInclude = true;
            }
            if (doInclude) {
                include(addOn.getFilePath());
            }

            // uninit application settings globally:
            if (this.appPreferences) {
                if (!isNull(global[className]) && isFunction(global[className].uninitPreferences)) {
                    global[className].uninitPreferences(undefined, undefined, widget);
                }
            }

            // uninit document specific settings to current document:
            else {
                mdiChild = EAction.getMdiChild();
                document = EAction.getDocument();
                if (!isNull(global[className]) && isFunction(global[className].uninitPreferences)) {
                    global[className].uninitPreferences(document, mdiChild, widget);
                }
            }
        } catch (e) {
            qWarning("AbstractPreferences.js:",
                     "uninit(): Exception: %1; %2; %3"
                     .arg(e.message).arg(e.fileName).arg(e.lineNumber));
            continue;
        }
    }
};

/**
 * Loads the preference page of the given add-on.
 * Called by 'showPage'.
 */
AbstractPreferences.prototype.load = function(addOn) {
    var widget = addOn.getPreferenceWidget();
    if (widget == undefined) {
        return;
    }
    // load preferences
    var className = addOn.getClassName();
    var document;
    document = undefined;
    if (!this.appPreferences) {
        document = EAction.getDocument();
    }
    if (!isNull(global[className]) && isFunction(global[className].initPreferences)) {
        global[className].initPreferences(widget, true, document, this);
    }

    // check if preferences apply to block:
    var store = document;
    if (!this.appPreferences) {
        var preferencesScope = "document";
        if (!isNull(global[className]) && isFunction(global[className].getPreferencesScope)) {
            if (document.getCurrentBlockId()!==document.getModelSpaceBlockId()) {
                preferencesScope = global[className].getPreferencesScope();
            }
        }
        if (!isNull(document) && preferencesScope==="block") {
            store = document.queryCurrentBlock();
        }
    }

    WidgetFactory.restoreState(widget, undefined, undefined, false, store);

    if (!isNull(global[className]) && isFunction(global[className].postInitPreferences)) {
        global[className].postInitPreferences(widget, true, document, this);
    }
};

/**
 * Saves all preferences to the current document (this.appPreferences==false)
 * or to a global settings file (this.appPreferences==true).
 */
AbstractPreferences.prototype.save = function() {
    var document = undefined;
    var transaction = undefined;
    if (!this.appPreferences) {
        document = EAction.getDocument();
        transaction = new RTransaction(document.getStorage(), qsTr("Apply preferences"), true);
    }

    for (var i = 0; i < this.addOns.length; ++i) {
        var addOn = this.addOns[i];
        var widget = addOn.getPreferenceWidget();
        if (isNull(widget) || widget.hasChanged !== true) {
            continue;
        }
        var className = addOn.getClassName();

        if (!isNull(global[className]) && isFunction(global[className].savePreferences)) {
            global[className].savePreferences(widget, true, document, transaction);
        }

        // check if preferences apply to block:
        var store = document;
        var preferencesScope = "document";
        if (!this.appPreferences) {
            if (!isNull(global[className]) && isFunction(global[className].getPreferencesScope)) {
                if (document.getCurrentBlockId()!==document.getModelSpaceBlockId()) {
                    preferencesScope = global[className].getPreferencesScope();
                }
            }
            if (!isNull(document) && preferencesScope==="block") {
                store = document.queryCurrentBlock();
            }
        }
        WidgetFactory.saveState(widget, undefined, store);
        if (!this.appPreferences) {
            if (preferencesScope==="block") {
                transaction.addObject(store);
            }
        }
    }

    if (!this.appPreferences) {
        transaction.end();
    }

    // check if preference changes require application restart and show
    // message if appropriate:
    if (WidgetFactory.requiresRestart===true && this.restartWarningShown === false) {
        var appWin = EAction.getMainWindow();
        QMessageBox.warning(appWin,
                qsTr("Restart required"),
                qsTr("Please restart QCAD for\nthe preference changes to take effect.")
        );
        this.restartWarningShown = true;
    }

    WidgetFactory.requiresRestart = false;
};

/**
 * Updates the navigation tree based on the given filter string.
 */
AbstractPreferences.prototype.updateTreeWidget = function(filterText) {
    if (isNull(filterText)) {
        filterText = "";
    }

    var rexp;
    try{
        rexp = new RegExp(filterText, "i");
    } catch (e) {
        rexp = new RegExp(".*", "i");
    }
    
    for(var i=0; i<this.treeWidget.topLevelItemCount; ++i) {
        var item = this.treeWidget.topLevelItem(i);
        var match = item.text(0).match(rexp);
        var found = this.filterItems(item, rexp, match);
        if (found || match) {
            item.setHidden(false);
            item.setExpanded(true);
        } else if(!match) {
            item.setHidden(true);
        }
    }
};

/**
 * \internal
 */
AbstractPreferences.prototype.filterItems = function(item, rexp, showAll) {
    var foundAny = false;
    for(var i=0; i<item.childCount(); ++i) {
        var subitem = item.child(i);
        var match = subitem.text(0).match(rexp);
        var found = this.filterItems(subitem, rexp, match);
        if (found || match) {
            subitem.setHidden(false);
            subitem.setExpanded(true);
            foundAny = true;
        } else if(!match) {
            if(!showAll) {
                subitem.setHidden(true);
            }
        }
    }
    return foundAny;
};

/**
 * Called when user enters a filter text for the navigation tree.
 */
AbstractPreferences.prototype.filterTree = function(text) {
    this.updateTreeWidget(text);
};

/**
 * Loads and shows the appropriate preferences page for the
 * current selected item in the navigation tree. Called
 * when the user selects an item in the tree.
 */
AbstractPreferences.prototype.showPage = function() {
    var items = this.treeWidget.selectedItems();
    if (items.length!==1) {
        return;
    }
    var item = items[0];
    if (isNull(item)) {
        return;
    }

    var parent = item.parent();

    var warningLabel = this.dialog.findChild("Warning");
    warningLabel.text = "";
    warningLabel.visible = false;
    if (!isNull(parent)) {
        if (parent.text(0).contains(qsTr("Defaults for"))) {
            warningLabel.text = "<font color='red'>" +
                    qsTr("These are default preferences for new drawings.") + "<br/>" +
                    qsTr("Changes will affect new drawings but NOT the current drawing.") + "<br/>" +
                    qsTr("Preferences of the current drawing can be changed under<br/><i>Edit &gt; Drawing Preferences</i>.") +
                    "</font>";
            warningLabel.visible = true;
        }
    }

    var pText = "";
    while (!isNull(parent)) {
        pText += parent.text(0) + ": " + pText;
        parent = parent.parent();
    }
    if (pText == "") {
        this.titleWidget.text = item.text(0);
    } else {
        this.titleWidget.text = pText + item.text(0);
    }
    var i = item.data(0, Qt.UserRole);
    var widget;
    if (!isNull(i)) {
        var addOn = this.addOns[i];
        widget = addOn.getPreferenceWidget();
        if (isNull(widget)) {
            var prefFile = addOn.getPreferenceFile();
            widget = this.createWidget(prefFile);
            this.pageWidget.addWidget(widget);
            addOn.setPreferenceWidget(widget);
            this.load(addOn);
            var treeWidget = this.treeWidget;
            widget.settingChangedEvent = function() {
                var font = treeWidget.currentItem().font(0);
                font.setBold(true);
                treeWidget.currentItem().setFont(0, font);
            };
            var btReset = this.dialog.findChild("ResetToDefaults");
            try {
                btReset.clicked.disconnect(this, "reset");
            } catch (e) {
                // ignored: signal might not be connected
            }
            btReset.clicked.connect(this, "reset");
        }
    } else {
        widget = this.pageWidget.findChild("empty");
    }
    this.pageWidget.setCurrentWidget(widget);
    this.treeWidget.setCurrentItem(item);
};

AbstractPreferences.prototype.showPageFor = function(className) {
    var flags = new Qt.MatchFlags(Qt.MatchWildcard | Qt.MatchContains | Qt.MatchRecursive);
    var items = this.treeWidget.findItems("*", flags, 0);
    for (var i = 0; i < items.length; ++i) {
        var item = items[i];
        var ix = item.data(0, Qt.UserRole);
        if (!isNull(ix)) {
            var addOn = this.addOns[ix];
            if (addOn.getClassName()===className) {
                this.treeWidget.setCurrentItem(item);
            }
        }

    }
};

/**
 * Called when user clicks reset button on preferences page.
 */
AbstractPreferences.prototype.reset = function() {
    var widget = this.pageWidget.currentWidget();
    //qDebug("AbstractPreferences.js:", "reset(): widget.objectName:", widget.objectName);
//    debugger;
    WidgetFactory.resetState(widget);
};

/**
 * Called when the global or drawing unit changes. Notifies all loaded
 * add-on pages.
 */
AbstractPreferences.prototype.unitUpdated = function(unit) {
    for (var i=0; i<this.addOns.length; ++i) {
        var addOn = this.addOns[i];
        var className = addOn.getClassName();

        // pref page of this add-on is not opened yet, skip:
        var widget = addOn.getPreferenceWidget();
        if (isNull(widget)) {
            continue;
        }

        if (!isNull(global[className]) && isFunction(global[className].updateUnit)) {
            global[className].updateUnit(unit);
        }
    }
};

/**
 * Called when the global or drawing paper unit changes. Notifies all loaded
 * add-on pages.
 */
AbstractPreferences.prototype.paperUnitUpdated = function(unit) {
    for (var i=0; i<this.addOns.length; ++i) {
        var addOn = this.addOns[i];
        var className = addOn.getClassName();

        // pref page of this add-on is not opened yet, skip:
        var widget = addOn.getPreferenceWidget();
        if (isNull(widget)) {
            continue;
        }

        if (!isNull(global[className]) && isFunction(global[className].updatePaperUnit)) {
            global[className].updatePaperUnit(unit);
        }
    }
};

AbstractPreferences.prototype.linearFormatUpdated = function(linearFormat) {
    for (var i=0; i<this.addOns.length; ++i) {
        var addOn = this.addOns[i];
        var className = addOn.getClassName();

        // pref page of this add-on is not opened yet, skip:
        var widget = addOn.getPreferenceWidget();
        if (isNull(widget)) {
            continue;
        }

        if (!isNull(global[className]) && isFunction(global[className].updateLinearFormat)) {
            global[className].updateLinearFormat(linearFormat);
        }
    }
};
