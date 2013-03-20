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

include("Kms.js");

function ShortcutPreferences() {
}

ShortcutPreferences.widgets = undefined;

ShortcutPreferences.getPreferencesCategory = function() {
    return [ qsTr("General"), qsTr("Shortcuts and Commands") ];
};

ShortcutPreferences.addTopLevelItem = function(treeWidget, plugin) {
    // top level item
    var title = plugin.getTitle();
    var note = "";
    if (isNull(title)) {
        title = plugin.getClassName();
        //note = "getTitle() not implemeted";
    }
    var item = new QTreeWidgetItem(treeWidget, [ title, note ]);
    treeWidget.addTopLevelItem(item);
};

ShortcutPreferences.addMenuItem = function(treeWidget, plugin, parentPlugin) {
    if (isNull(parentPlugin)) {
        return;
    }
    if (isNull(plugin.getTitle()) || plugin.getTitle().length === 0) {
        // skip plugins without a title
        return;
    }
    
    // skip separators
    var action = plugin.getGuiAction();
    if (!isNull(action)) {
        if (action.isSeparator()) {
            return;
        }
    }
    
    var items = treeWidget.findItems(parentPlugin.getTitle(), Qt.MatchFixedString);
    var item;
    if (items.length === 0) {
        return;
    } else {
        item = items[0];
    }
    
    var subitem = new QTreeWidgetItem(item, [ plugin.getTitle() ]);
    item.addChild(subitem);
};

ShortcutPreferences.addActionItem = function(treeWidget, plugin, parentPlugin, reset) {
    if (isNull(parentPlugin)) {
        return;
    }

    //var parentTitle = parentPlugin.getTitle();
    var parentTitle;
    if (!isNull(parentPlugin.getGuiAction())) {
        parentTitle = parentPlugin.getGuiAction().text;
    }
    else {
        parentTitle = parentPlugin.getTitle();
    }

    var flags = new Qt.MatchFlags(Qt.MatchFixedString | Qt.MatchRecursive);
    var parentItems = treeWidget.findItems(parentTitle, flags);
    var parentItem;
    if (parentItems.length === 1) {
        parentItem = parentItems[0];
    } else {
        return;
    }

    var action = plugin.getGuiAction();

    // bind either user- or scheme-defined shortcuts to the action
    var userShortcuts = Kms.loadShortcutsFromSettings(action);
    if (!reset && !isNull(userShortcuts)) {
        // user defined shortcut from settings:
        action.setShortcuts(userShortcuts);
    } else {
        // shortcuts defined in current KMS scheme:
        if (!ShortcutPreferences.kms.bindShortcutsToAction(action)) {
            // the action's default shortcuts:
            action.setShortcuts(action.getDefaultShortcuts());
        }
    }

    // bind either user- or scheme-defined commands to the action
    var userCommands = Kms.loadCommandsFromSettings(action);
    if (!reset && !isNull(userCommands)) {
        // user defined commands from settings:
        action.setCommands(userCommands);
    } else {
        // commands defined in current KMS scheme:
        if (!ShortcutPreferences.kms.bindCommandsToAction(action)) {
            // the action's default commands:
            action.setCommands(action.getDefaultCommands());
        }
    }

    //qDebug("action.text: ", action.text);
    var actText = action.text.replace("&", "");
    //qDebug("actText 1: ", actText);
    var pos = actText.search("\t");
    if (pos !== -1) {
        actText = actText.substr(0, pos);
    }
    //qDebug("actText 2: ", actText);
    var scText = Kms.getKsListHumanReadable(action.shortcuts());
    var commandList = action.getCommands().join("\n");
    var userDefined = "";
    if ((!reset) && !(isNull(userShortcuts) && isNull(userCommands))) {
        userDefined = ShortcutPreferences.changedByUserCharacter;
    }    
    var item = new QTreeWidgetItem(parentItem, [ actText, scText, commandList,
            userDefined ]);
    item.setData(0, Qt.UserRole, action);
    item.setIcon(0, action.icon);
    item.setData(1, Qt.UserRole, action.shortcuts());
    item.setData(2, Qt.UserRole, action.getCommands());
    parentItem.addChild(item);
};

ShortcutPreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var flags, i, item, action, commandList, model, mi;
    
    if (isNull(calledByPrefDialog)) {
        calledByPrefDialog = false;
    }
    
    ShortcutPreferences.plugins = Plugin.getPlugins();
    ShortcutPreferences.widgets = getWidgets(pageWidget);
    var treeWidget = ShortcutPreferences.widgets["ShortcutTree"];
    treeWidget.setColumnWidth(0, 250);
    treeWidget.setColumnWidth(1, 150);
    treeWidget.setColumnWidth(2, 150);
    treeWidget.setColumnWidth(3, 20);
    var header = treeWidget.header();
    header.setResizeMode(header.logicalIndex(0),QHeaderView.ResizeToContents);
    header.setResizeMode(header.logicalIndex(1),QHeaderView.Interactive);
    header.setResizeMode(header.logicalIndex(2),QHeaderView.Stretch);
    header.setResizeMode(header.logicalIndex(3),QHeaderView.Interactive);
    treeWidget.resetState = function() {
        if (!calledByPrefDialog) {
            return;
        }
        
        var flags = new QMessageBox.StandardButtons(QMessageBox.Yes | QMessageBox.No);
        var ret = QMessageBox.question(
                    treeWidget,
                    qsTr("Restore Shortcuts and Commands"),
                    qsTr("Do you want to restore all shortcuts and commands?\n"
                            + "User defined shortcuts and commands will be lost."),
                    flags, QMessageBox.No);
        if (ret === QMessageBox.No) {
            return;
        }
        
        // remove groups from settings
        var settings = RSettings.getQSettings();
        settings.beginGroup("Commands");
        settings.remove("");
        settings.endGroup();
        settings.beginGroup("Shortcuts");
        settings.remove("");
        settings.endGroup();
        settings.sync();
        
        var schemeName = RSettings.getStringValue("Shortcuts/Scheme", "QCAD");
        ShortcutPreferences.updateShortcutTree(schemeName, true);
        ShortcutPreferences.updateConflicts(true);
        ShortcutPreferences.widgets["ScConflictsLabel"].clear();
        ShortcutPreferences.widgets["CmdConflictsLabel"].clear();        
    };

    var headerItem = treeWidget.headerItem();
    ShortcutPreferences.changedByUserCharacter = headerItem.text(3).substr(0,1);
    
    // fill shortcut scheme combo
    var schemeCombo = ShortcutPreferences.widgets["Scheme"];
    schemeCombo.clear();
    var dir = new QDir(Kms.getSchemeDirectory());
    var filters = new QDir.Filters(QDir.Files, QDir.NoDotAndDotDot, QDir.Readable);
    var sortFlags = new QDir.SortFlags(QDir.Name);
    var eil = dir.entryInfoList(new Array("*.kms"), filters, sortFlags);
    for ( var j = 0; j < eil.length; ++j) {
        var fi = eil[j];
        schemeCombo.addItem(fi.completeBaseName());
    }
    // set default scheme
    schemeCombo.currentIndex = schemeCombo.findText("QCAD");

    commandList = ShortcutPreferences.widgets["CommandList"];
    var itemDelegate = new QItemDelegate();
    commandList.setItemDelegate(itemDelegate);

    if (calledByPrefDialog) {
        // get keyboard mapping (shortcuts) from scheme and
        // build the shortcut tree
        var schemeName = RSettings.getStringValue("Shortcuts/Scheme", "QCAD");
        ShortcutPreferences.updateShortcutTree(schemeName);
        ShortcutPreferences.updateConflicts(true);
        ShortcutPreferences.widgets["ScConflictsLabel"].clear();
        ShortcutPreferences.widgets["CmdConflictsLabel"].clear();        
        ShortcutPreferences.currentIndex = schemeCombo.currentIndex;
    }
    
    // connections
    
    schemeCombo["currentIndexChanged(QString)"].connect(ShortcutPreferences, function(text) {
        if (!calledByPrefDialog) {
            return;
        }
        
        var changed = false;
        var treeWidget = ShortcutPreferences.widgets["ShortcutTree"];
        flags = new Qt.MatchFlags(Qt.MatchWildcard | Qt.MatchContains
                | Qt.MatchRecursive);
        var items = treeWidget.findItems("*", flags, 0);
        for ( i = 0; i < items.length; ++i) {
            item = items[i];
            action = item.data(0, Qt.UserRole);
            if (isNull(action)) {
                continue;
            }
            var font = item.font(0);
            if (font.bold()) {
                changed = true;
                break;
            }
        }
        if (changed) {
            flags = new QMessageBox.StandardButtons(QMessageBox.Ok
                    | QMessageBox.Cancel);
            var ret = QMessageBox.question(
                            pageWidget,
                            qsTr("Changes will be lost"),
                            qsTr("Any changes made since starting this dialog will be lost. "
                                    + "\nPress cancel and then apply to keep your changes"
                                    + "\nor press OK to continue."),
                            flags, QMessageBox.Ok);
            if (ret == QMessageBox.Cancel) {
                schemeCombo.blockSignals(true);
                schemeCombo.currentIndex = ShortcutPreferences.currentIndex;
                schemeCombo.blockSignals(false);
                return;
            }
        }
        
        ShortcutPreferences.currentIndex = schemeCombo.currentIndex;
        pageWidget.enabled = false;
        QApplication.setOverrideCursor(new QCursor(Qt.WaitCursor));        
        ShortcutPreferences.updateShortcutTree(text);
        QApplication.restoreOverrideCursor();
        ShortcutPreferences.updateConflicts(true);
        ShortcutPreferences.widgets["ScConflictsLabel"].clear();
        ShortcutPreferences.widgets["CmdConflictsLabel"].clear();
        pageWidget.enabled = true;
    });
    
    var filter = ShortcutPreferences.widgets["Filter"];
    filter.selectAll();
    filter.textChanged.connect(ShortcutPreferences, function(text) {
        ShortcutPreferences.filterTreeWidget(text);
    }); 
    //qApp.focusChanged.connect(ShortcutPreferences, "focusChanged");
    
    treeWidget.itemSelectionChanged.connect(ShortcutPreferences, function() {
        ShortcutPreferences.enableTreeItemRelatedWidgets(false);
        ShortcutPreferences.widgets["CmdMenuItemLabel"].clear();
        ShortcutPreferences.widgets["CmdConflictsLabel"].clear();
        
        var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
        shortcutList.clear();
        
        commandList = ShortcutPreferences.widgets["CommandList"];
        var model = new QStandardItemModel(pageWidget);
        commandList.setModel(model);
        
        var items = treeWidget.selectedItems();
        if (items.length != 1) {
            return;
        }
        item = items[0];
        if (isNull(item)) {
            return;
        }
        
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            // item clicked is a category
            return;
        }
        
        ShortcutPreferences.enableTreeItemRelatedWidgets();
        ShortcutPreferences.widgets["ScReplace"].enabled = false;
        ShortcutPreferences.widgets["ScRemove"].enabled = false;
        ShortcutPreferences.widgets["CmdEdit"].enabled = false;
        ShortcutPreferences.widgets["CmdRemove"].enabled = false;        
        ShortcutPreferences.widgets["ScMenuItemLabel"].text = item.text(0);        
        ShortcutPreferences.widgets["CmdMenuItemLabel"].text = item.text(0);
        
        ShortcutPreferences.updateConflictText(item);

        // fill shortcut list
        var scList = item.data(1, Qt.UserRole);
        for ( i = 0; i < scList.length; ++i) {
            var sc = scList[i];
            var listItem = new QListWidgetItem(sc.toString(QKeySequence.NativeText));
            shortcutList.addItem(listItem);
        }
        
        // fill command list
        var cmdList = item.data(2, Qt.UserRole);
        for ( i = 0; i < cmdList.length; ++i) {
            var cmd = cmdList[i];
            if (cmd.toString() == "") {
                continue;
            }
            var qsItem = new QStandardItem(cmd.toString());
            model.appendRow(qsItem);
        }        
    });
    
    ShortcutPreferences.widgets["UnbindShortcuts"].clicked.connect(ShortcutPreferences, function() {
        item = treeWidget.currentItem();
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            return;
        }

        ShortcutPreferences.widgets["ShortcutList"].clear();
        ShortcutPreferences.widgets["ShortcutLineEdit"].clear();
        ShortcutPreferences.updateScCell(item);
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);
    });
    
    ShortcutPreferences.widgets["UnbindCommands"].clicked.connect(ShortcutPreferences, function() {
        item = treeWidget.currentItem();
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            return;
        }

        // clear list by setting an empty model
        model = new QStandardItemModel(pageWidget);
        commandList.setModel(model);
        ShortcutPreferences.updateCmdCell(item);
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);
    });
    
    ShortcutPreferences.widgets["RestoreMenuItem"].clicked.connect(ShortcutPreferences, function() {
        item = treeWidget.currentItem();
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            return;
        }
        
        // restore shortcuts
        var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
        shortcutList.clear();
        ShortcutPreferences.widgets["ShortcutLineEdit"].clear();
        var scStrings = ShortcutPreferences.kms.getShortcutMap()[action.getScriptFile()];

        // get default key sequences from KMS file if present, default to
        // the ones set in the original plugin init function:
        var keysequences;
        if (!isNull(scStrings)) {
            keysequences = Kms.stringArraytoKsArray(scStrings);
        }
        else {
            keysequences = action.getDefaultShortcuts();
        }

        if (!isNull(keysequences)) {
            for ( var i = 0; i < keysequences.length; ++i) {
                var ks = keysequences[i];
                var listItem = new QListWidgetItem(ks.toString(QKeySequence.NativeText));
                shortcutList.addItem(listItem);
            }
        }
        
        // restore commands
        commandList = ShortcutPreferences.widgets["CommandList"];
        var model = new QStandardItemModel(pageWidget);
        commandList.setModel(model);
        // get default commands from KMS file if present, default to
        // the ones set in the original plugin init function:
        var commands = ShortcutPreferences.kms.getCommandMap()[action.getScriptFile()];
        if (isNull(commands)) {
            commands = action.getDefaultCommands();
        }
        if (!isNull(commands)) {
            for (var j = 0; j < commands.length; ++j) {
                var cmd = commands[j];
                var qsItem = new QStandardItem(cmd.toString());
                model.appendRow(qsItem);
            }
        }
        
        // update widgets
        ShortcutPreferences.updateScCell(item, true);
        ShortcutPreferences.updateScListWidgets();
        ShortcutPreferences.updateCmdCell(item, true);
        ShortcutPreferences.updateCmdListWidgets();
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);

    });    

    var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
    shortcutList.itemSelectionChanged.connect(ShortcutPreferences, function() {
        ShortcutPreferences.updateScListWidgets();
    });     
    
    ShortcutPreferences.widgets["ScAdd"].clicked.connect(ShortcutPreferences, function() {
        item = treeWidget.currentItem();
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            return;
        }

        var sc = ShortcutPreferences.widgets["ShortcutLineEdit"].text;
        var ks = new QKeySequence(sc);
        if (ks.isEmpty()) {
            return;
        }
        var ksList = item.data(1, Qt.UserRole);
        ksList.push(ks);
        item.setText(1, Kms.getKsListHumanReadable(ksList));
        item.setData(1, Qt.UserRole, ksList);
        ShortcutPreferences.highlightRow(item, 1);
        item.setText(3, ShortcutPreferences.changedByUserCharacter);
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);
        
        var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
        item = new QListWidgetItem(ks.toString(QKeySequence.NativeText));
        shortcutList.addItem(item);
        ShortcutPreferences.widgets["ShortcutLineEdit"].clear();
    });
    
    ShortcutPreferences.widgets["ScReplace"].clicked.connect(ShortcutPreferences, function() {
        item = treeWidget.currentItem();
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            return;
        }

        var sc = ShortcutPreferences.widgets["ShortcutLineEdit"].text;
        var ks = new QKeySequence(sc);
        if (ks.isEmpty()) {
            return;
        }
        var ci = ShortcutPreferences.widgets["ShortcutList"].currentItem();
        ci.setText(ks.toString(QKeySequence.NativeText));
        ShortcutPreferences.updateScCell(item);
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);
        ShortcutPreferences.updateScListWidgets();
        ShortcutPreferences.widgets["ShortcutLineEdit"].clear();
    });
    
    ShortcutPreferences.widgets["ScRemove"].clicked.connect(ShortcutPreferences, function() {
        item = treeWidget.currentItem();
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            return;
        }

        var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
        var currentRow = shortcutList.currentRow;
        shortcutList.model().removeRow(currentRow);
        ShortcutPreferences.updateScCell(item);
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);
        ShortcutPreferences.updateScListWidgets();
        ShortcutPreferences.widgets["ShortcutLineEdit"].clear();
    });
    
    ShortcutPreferences.widgets["ScClear"].clicked.connect(ShortcutPreferences, function() {
        ShortcutPreferences.widgets["ShortcutLineEdit"].clear();
    });
    
    commandList = ShortcutPreferences.widgets["CommandList"];
    commandList.clicked.connect(ShortcutPreferences, function(index) {
        ShortcutPreferences.updateCmdListWidgets();
    });    
    
    ShortcutPreferences.widgets["CmdAdd"].clicked.connect(ShortcutPreferences, function() {
        model = commandList.model();
        var qsItem = new QStandardItem("");
        model.insertRow(0, qsItem);
        mi = model.indexFromItem(qsItem);
        commandList.setCurrentIndex(mi);
        commandList.edit(mi);
    });
    
    ShortcutPreferences.widgets["CmdEdit"].clicked.connect(ShortcutPreferences, function() {
        var mi = commandList.currentIndex();
        commandList.setCurrentIndex(mi);
        commandList.edit(mi);
    });
    
    ShortcutPreferences.widgets["CmdRemove"].clicked.connect(ShortcutPreferences, function() {
        mi = commandList.currentIndex();
        model = commandList.model();
        var row = mi.row();
        model.removeRow(row);
        item = treeWidget.currentItem();
        ShortcutPreferences.updateCmdCell(item);
        ShortcutPreferences.updateCmdListWidgets();
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);
    });
    
    ShortcutPreferences.widgets["Expand"].clicked.connect(ShortcutPreferences, function() {
        treeWidget.expandAll();
        ShortcutPreferences.enableTreeItemRelatedWidgets(true);
    });

    ShortcutPreferences.widgets["Collapse"].clicked.connect(ShortcutPreferences, function() {
        treeWidget.collapseAll();
        ShortcutPreferences.enableTreeItemRelatedWidgets(false);
    });

    itemDelegate.closeEditor.connect(ShortcutPreferences, function(editor, hint) {
        var commandList = ShortcutPreferences.widgets["CommandList"];
        if (!isNull(editor) && !isNull(editor.text)) {
            if (editor.text.length===0) {
                // empty:
                var ci = commandList.currentIndex();
                commandList.edit(ci);
                return;
            }
        }

        item = treeWidget.currentItem();
        ShortcutPreferences.updateCmdCell(item);
        ShortcutPreferences.updateCmdListWidgets();
        ShortcutPreferences.updateConflicts();
        ShortcutPreferences.updateConflictText(item);
        pageWidget.settingChangedEvent();
    });
};

ShortcutPreferences.enableTreeItemRelatedWidgets = function(enable) {
    if (isNull(enable)) {
        enable = true;
    }
    ShortcutPreferences.widgets["TabWidget"].enabled = enable;
    ShortcutPreferences.widgets["UnbindShortcuts"].enabled = enable;
    ShortcutPreferences.widgets["UnbindCommands"].enabled = enable;
    ShortcutPreferences.widgets["RestoreMenuItem"].enabled = enable;
};

ShortcutPreferences.filterTreeWidget = function(filterText) {
    if (isNull(filterText)) {
        filterText = "";
    }
    filterText = filterText.replace("+", "\\+");
    var treeWidget = ShortcutPreferences.widgets["ShortcutTree"];
    var rexp;
    try {
        rexp = new RegExp(filterText, "i");
    } catch (e) {
        rexp = new RegExp(".*", "i");
    }

    for ( var i = 0; i < treeWidget.topLevelItemCount; ++i) {
        var item = treeWidget.topLevelItem(i);
        var match = item.text(0).match(rexp);
        var found = ShortcutPreferences.filterItems(item, rexp, match);
        if (found || match) {
            item.setHidden(false);
            item.setExpanded(true);
        } else if (!match) {
            item.setHidden(true);
        }
    }

    var twItems = treeWidget.selectedItems();
    if (twItems.length == 0) {
        ShortcutPreferences.enableTreeItemRelatedWidgets(false);
    } else {
        ShortcutPreferences.enableTreeItemRelatedWidgets(true);
    }
};

ShortcutPreferences.filterItems = function(item, rexp, showAll) {
    var foundAny = false;
    for ( var i = 0; i < item.childCount(); ++i) {
        var subitem = item.child(i);
        var match = subitem.text(0).match(rexp) || subitem.text(1).match(rexp)
                || subitem.text(2).match(rexp);
        var found = ShortcutPreferences.filterItems(subitem, rexp, match);
        if (found || match) {
            subitem.setHidden(false);
            subitem.setExpanded(true);
            foundAny = true;
        } else if (!match) {
            if (!showAll) {
                subitem.setHidden(true);
            }
        }
    }
    return foundAny;
};

/*
ShortcutPreferences.focusChanged = function(oldWidget, newWidget) {
    if (newWidget && newWidget.objectName == "Filter") {
        var filter = ShortcutPreferences.widgets["Filter"];
        filter.clear();
        qApp.focusChanged.disconnect(ShortcutPreferences, "focusChanged");
    }
};
*/

ShortcutPreferences.updateScListWidgets = function() {
    var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
    var scItems = shortcutList.selectedItems();
    if (shortcutList.count === 0 || scItems.length === 0) {
        ShortcutPreferences.widgets["ScRemove"].enabled = false;
        ShortcutPreferences.widgets["ScReplace"].enabled = false;
    } else {
        ShortcutPreferences.widgets["ScRemove"].enabled = true;
        ShortcutPreferences.widgets["ScReplace"].enabled = true;
    }
};

ShortcutPreferences.updateCmdListWidgets = function() {
    var commandList = ShortcutPreferences.widgets["CommandList"];
    var selModel = commandList.selectionModel();
    if (selModel.hasSelection()) {
        ShortcutPreferences.widgets["CmdRemove"].enabled = true;
        ShortcutPreferences.widgets["CmdEdit"].enabled = true;
    } else {
        ShortcutPreferences.widgets["CmdRemove"].enabled = false;
        ShortcutPreferences.widgets["CmdEdit"].enabled = false;
    }
};

ShortcutPreferences.updateConflicts = function(forceInit) {
    var i, k, item, action;

    QApplication.setOverrideCursor(new QCursor(Qt.WaitCursor));

    if (isNull(ShortcutPreferences.treeItems)
            || (!isNull(forceInit) && forceInit == true)) {
        var treeWidget = ShortcutPreferences.widgets["ShortcutTree"];
        var flags = new Qt.MatchFlags(Qt.MatchWildcard | Qt.MatchContains
                | Qt.MatchRecursive);
        ShortcutPreferences.treeItems = treeWidget.findItems("*", flags, 0);
    }

    // clear conflicts
    for (i = 0; i < ShortcutPreferences.treeItems.length; ++i) {
        item = ShortcutPreferences.treeItems[i];
        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            continue;
        }
        ShortcutPreferences.clearConflicts(item, 1);
        ShortcutPreferences.clearConflicts(item, 2);
        item.setData(0, Qt.UserRole + 1, false);
    }

    // mark conflicts
    for (i = 0; i < ShortcutPreferences.treeItems.length; ++i) {
        item = ShortcutPreferences.treeItems[i];

        // skip if item has been checked already
        var checked = item.data(0, Qt.UserRole + 1);
        if (checked == true) {
            continue;
        }
        // mark item as already checked
        item.setData(0, Qt.UserRole + 1, true);

        action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            continue;
        }

        var ksList = item.data(1, Qt.UserRole);
        var cmdList = item.data(2, Qt.UserRole);

        for ( var i2 = 0; i2 < ShortcutPreferences.treeItems.length; ++i2) {
            var item2 = ShortcutPreferences.treeItems[i2];

            // skip if item has been checked already
            var checked2 = item2.data(0, Qt.UserRole + 1);
            if (checked2 == true) {
                continue;
            }

            var action2 = item2.data(0, Qt.UserRole);
            if (isNull(action2)) {
                continue;
            }

            if (action.getScriptFile() == action2.getScriptFile()) {
                continue;
            }

            var ksList2 = item2.data(1, Qt.UserRole);
            for (k = 0; k < ksList.length; ++k) {
                if (typeof (ksList[k]) == "string") {
                    ksList[k] = new QKeySequence(ksList[k]);
                }
                for ( var k2 = 0; k2 < ksList2.length; ++k2) {
                    if (typeof (ksList2[k2]) == "string") {
                        ksList2[k2] = new QKeySequence(ksList2[k2]);
                    }
                    if (ksList[k].matches(ksList2[k2]) == QKeySequence.ExactMatch) {
                        ShortcutPreferences.markConflicts(item, 1);
                        ShortcutPreferences.markConflicts(item2, 1);
                        break;
                    }
                }
            }

            var cmdList2 = item2.data(2, Qt.UserRole);
            for (k = 0; k < cmdList2.length; ++k) {
                if (cmdList.contains(cmdList2[k])) {
                    ShortcutPreferences.markConflicts(item, 2);
                    ShortcutPreferences.markConflicts(item2, 2);
                    break;
                }
            }
        }
    }

    QApplication.restoreOverrideCursor();
};

ShortcutPreferences.updateShortcutTree = function(schemeName, reset) {
    if (isNull(reset)) {
        reset = false;
    }
    var treeWidget = ShortcutPreferences.widgets["ShortcutTree"];
    treeWidget.enabled = false;
    treeWidget.clear();
    treeWidget.layoutMode = QListView.Batched;
    treeWidget.batchSize = 1000;
    ShortcutPreferences.kms = new Kms(schemeName);
    for ( var i = 0; i < ShortcutPreferences.plugins.length; ++i) {
        var plugin = ShortcutPreferences.plugins[i];

        if (RS.getSystemId()==="osx") {
            if (plugin.getClassName()==="AppPreferences") {
                continue;
            }
        }
        
        if (!plugin.hasShortcuts()) {
            continue;
        }

        if (plugin.isTopLevel()) {
            ShortcutPreferences.addTopLevelItem(treeWidget, plugin);
            continue;
        }

        //debugger;
        var parentPlugin = Plugin.getParentPlugin(ShortcutPreferences.plugins, plugin);
        if (!plugin.hasGuiAction()) {
            ShortcutPreferences.addMenuItem(treeWidget, plugin, parentPlugin);
            continue;
        }
        
        ShortcutPreferences.addActionItem(treeWidget, plugin, parentPlugin, reset);
    }
    treeWidget.expandAll();
    treeWidget.resizeColumnToContents(0);
    treeWidget.enabled = true;
};

ShortcutPreferences.markConflicts = function(item, col) {
    item.setForeground(col, new QColor(Qt.red));
};

ShortcutPreferences.clearConflicts = function(item, col) {
    item.setForeground(col, new QColor(Qt.black));
};

ShortcutPreferences.updateConflictText = function(item) {
    if (isNull(item)) {
        return;
    }

    if (item.foreground(1) == new QColor(Qt.red)) {
        ShortcutPreferences.widgets["ScConflictsLabel"].text =
            qsTr("Shortcuts conflict with at least one other shortcut.");
    } else {
        ShortcutPreferences.widgets["ScConflictsLabel"].text = qsTr("No conflicts.");
    }

    if (item.foreground(2) == new QColor(Qt.red)) {
        ShortcutPreferences.widgets["CmdConflictsLabel"].text =
            qsTr("Commands conflict with at least one other command.");
    } else {
        ShortcutPreferences.widgets["CmdConflictsLabel"].text = qsTr("No conflicts.");
    }
};

ShortcutPreferences.lowlightRow = function(item) {
    for ( var i = 0; i < item.columnCount() - 1; ++i) {
        var font = item.font(i);
        font.setBold(false);
        item.setFont(i, font);
    }
};

ShortcutPreferences.highlightRow = function(item, col) {
    var font;
    
    font = item.font(0);
    font.setBold(true);
    item.setFont(0, font);

    font = item.font(col);
    font.setBold(true);
    item.setFont(col, font);
};

ShortcutPreferences.updateCmdCell = function(item, restored) {
    if (isNull(restored)) {
        restored = false;
    }

    var commandList = ShortcutPreferences.widgets["CommandList"];
    var cmdList = new Array();
    var model = commandList.model();
    for ( var i = 0; i < model.rowCount(); ++i) {
        var mi = model.index(i, 0);
        var cmd = model.data(mi);
        if (cmd.length!=0) {
            cmdList.push(cmd);
        }
    }        
    item.setData(2, Qt.UserRole, cmdList);
    item.setText(2, cmdList.join("\n"));
    
    if (restored) {
        ShortcutPreferences.lowlightRow(item);
        item.setText(3, "");
    } else {
        ShortcutPreferences.highlightRow(item, 2);
        item.setText(3, ShortcutPreferences.changedByUserCharacter);
    }
};

ShortcutPreferences.updateScCell = function(item, restored) {
    if (isNull(restored)) {
        restored = false;
    }
    
    var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
    var ksList = new Array();
    for ( var i = 0; i < shortcutList.count; ++i) {
        var sc = shortcutList.item(i).text();
        var ks = new QKeySequence(sc);
        ksList.push(ks.toString(QKeySequence.NativeText));
    }
    item.setText(1, Kms.getKsListHumanReadable(ksList));
    item.setData(1, Qt.UserRole, ksList);
    if (restored) {
        ShortcutPreferences.lowlightRow(item);
        item.setText(3, "");
    } else {
        ShortcutPreferences.highlightRow(item, 1);
        item.setText(3, ShortcutPreferences.changedByUserCharacter);
    }
};

ShortcutPreferences.applyPreferences = function() {
    var treeWidget = ShortcutPreferences.widgets["ShortcutTree"];
    var flags = new Qt.MatchFlags(Qt.MatchWildcard | Qt.MatchContains | Qt.MatchRecursive);
    var items = treeWidget.findItems("*", flags, 0);
    for (var i = 0; i < items.length; ++i) {
        var item = items[i];
        var action = item.data(0, Qt.UserRole);
        if (isNull(action)) {
            continue;
        }

        var ksList = item.data(1, Qt.UserRole);
        action.setShortcuts(ksList);
        var cmdList = item.data(2, Qt.UserRole);
        action.setCommands(cmdList);
        if (item.text(3) === ShortcutPreferences.changedByUserCharacter) {
            Kms.saveToSettings(action);
        } else {
            Kms.removeFromSettings(action);
        }        
    }
};

ShortcutPreferences.getShortcutsAsList = function() {
    var shortcutList = ShortcutPreferences.widgets["ShortcutList"];
    var shortcuts = new Array();
    for(var i=0;i<shortcutList.count;++i) {
        var sc = shortcutList.item(i).text();
        shortcuts.push(sc);
    }
    return shortcuts;
};

/**
 * Initializes user defined shortcuts and commands.
 */
/*
ShortcutPreferences.postInit = function() {
    var settings = RSettings.getQSettings();
    var keys = RSettings.getAllKeys("Shortcuts");

    var i, key, action;

    for (i=0; i<keys.length; i++) {
        key = keys[i];
        action = RGuiAction.getByScriptFile(key);
        if (isNull(action)) {
            continue;
        }
        var scStringList = settings.value("Shortcuts/" + key);

        // explicitely no shortcuts:
        if (isNull(scStringList)) {
            action.setShortcuts([]);
            continue;
        }

        var scList = new Array();
        for (var k=0; k<scStringList.length; k++) {
            var sc = new QKeySequence(scStringList[k]);
            scList.push(sc);
        }
        action.setShortcuts(scList);
    }

    keys = RSettings.getAllKeys("Commands");

    for (i=0; i<keys.length; i++) {
        key = keys[i];
        action = RGuiAction.getByScriptFile(key);
        if (isNull(action)) {
            continue;
        }
        var cmStringList = settings.value("Commands/" + key);

        // explicitely no commands:
        if (isNull(cmStringList)) {
            action.setCommands([]);
            continue;
        }

        action.setCommands(cmStringList);
    }
};*/
