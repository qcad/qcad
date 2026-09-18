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

/**
 * Cache of searchable, translated UI strings per preference page file.
 * Key: absolute .ui file name, value: newline separated string of all
 * visible labels, titles, tool tips, etc. of the page.
 * Built lazily on first use of the filter, never requires loading the UI.
 */
AbstractPreferences.uiStringsCache = {};
AbstractPreferences.uiStringsCacheLocale = undefined;

/**
 * Names of UI properties / attributes with user visible strings
 * that are searchable through the preferences filter.
 */
AbstractPreferences.searchableUiProperties = {
    "text": true,
    "title": true,
    "toolTip": true,
    "whatsThis": true,
    "placeholderText": true,
    "statusTip": true,
    "windowTitle": true
};

/**
 * Replaces the XML entities used in .ui files with their characters.
 */
AbstractPreferences.unescapeXml = function(str) {
    if (str.indexOf("&")===-1) {
        return str;
    }
    str = str.split("&lt;").join("<");
    str = str.split("&gt;").join(">");
    str = str.split("&quot;").join("\"");
    str = str.split("&apos;").join("'");
    str = str.split("&#10;").join("\n");
    str = str.split("&#13;").join("\r");
    str = str.split("&#9;").join("\t");
    // must be last:
    str = str.split("&amp;").join("&");
    return str;
};

/**
 * Removes HTML / rich text tags from the given string (e.g. tool tips
 * defined as rich text in Qt Designer).
 */
AbstractPreferences.stripTags = function(str) {
    var start = str.indexOf("<");
    if (start===-1) {
        return str;
    }

    var ret = "";
    var pos = 0;
    while (start!==-1) {
        ret += str.substring(pos, start);
        var end = str.indexOf(">", start);
        if (end===-1) {
            // unterminated tag: keep rest as is
            pos = start;
            break;
        }
        // tags separate words:
        ret += " ";
        pos = end + 1;
        start = str.indexOf("<", pos);
    }
    ret += str.substring(pos);
    return ret;
};

/**
 * Removes keyboard accelerator markers (single '&') from the given string.
 */
AbstractPreferences.stripAccelerators = function(str) {
    if (str.indexOf("&")===-1) {
        return str;
    }
    var placeholder = "\u0001";
    return str.split("&&").join(placeholder).split("&").join("").split(placeholder).join("&");
};

/**
 * Extracts and translates all user visible strings from the given
 * Qt Designer .ui file contents without loading the UI.
 *
 * Only string properties listed in AbstractPreferences.searchableUiProperties
 * (and tab titles) are considered. Strings marked as notr="true" are skipped.
 * Strings are translated using the same translation context that
 * QUiLoader uses when loading the UI (the &lt;class&gt; element of the form).
 *
 * Note that this uses indexOf based scanning rather than regular
 * expressions for performance reasons.
 *
 * \return Array of translated, plain text strings.
 */
AbstractPreferences.parseUiStrings = function(contents) {
    var ret = [];
    if (!isString(contents)) {
        return ret;
    }

    // translation context is the class name of the form:
    var context = "";
    var ci = contents.indexOf("<class>");
    if (ci!==-1) {
        var ce = contents.indexOf("</class>", ci);
        if (ce!==-1) {
            context = contents.substring(ci+7, ce);
        }
    }

    var pos = 0;
    while (true) {
        var i = contents.indexOf("<string", pos);
        if (i===-1) {
            break;
        }
        var tagEnd = contents.indexOf(">", i);
        if (tagEnd===-1) {
            break;
        }
        var tag = contents.substring(i+7, tagEnd);

        // '<stringlist>' or other tags starting with '<string':
        if (tag.length>0 && tag.charAt(0)!==" " && tag.charAt(0)!=="/") {
            pos = tagEnd + 1;
            continue;
        }

        var text;
        var end;
        if (tag.charAt(tag.length-1)==="/") {
            // empty string element: <string/>
            text = "";
            end = tagEnd + 1;
        }
        else {
            end = contents.indexOf("</string>", tagEnd);
            if (end===-1) {
                break;
            }
            text = contents.substring(tagEnd+1, end);
            end += 9;
        }
        pos = end;

        if (text.length===0) {
            continue;
        }

        // untranslatable string (usually a value, not a label):
        if (tag.indexOf("notr=\"true\"")!==-1) {
            continue;
        }

        // find enclosing property or attribute element:
        var pi = contents.lastIndexOf("<property name=\"", i);
        var ai = contents.lastIndexOf("<attribute name=\"", i);
        var nameStart;
        if (pi===-1 && ai===-1) {
            continue;
        }
        if (pi>ai) {
            nameStart = pi + 16;
        }
        else {
            nameStart = ai + 17;
        }
        // property / attribute must be the direct parent of the string
        // (not already closed, e.g. string inside a stringlist):
        var pc = contents.lastIndexOf("</property>", i);
        var ac = contents.lastIndexOf("</attribute>", i);
        if (Math.max(pc, ac) > Math.max(pi, ai)) {
            continue;
        }
        var nameEnd = contents.indexOf("\"", nameStart);
        if (nameEnd===-1) {
            continue;
        }
        var propertyName = contents.substring(nameStart, nameEnd);
        if (AbstractPreferences.searchableUiProperties[propertyName]!==true) {
            continue;
        }

        // disambiguation:
        var comment = undefined;
        var cs = tag.indexOf("comment=\"");
        if (cs!==-1) {
            var cse = tag.indexOf("\"", cs+9);
            if (cse!==-1) {
                comment = AbstractPreferences.unescapeXml(tag.substring(cs+9, cse));
            }
        }

        text = AbstractPreferences.unescapeXml(text);

        // translate:
        var translated;
        if (isNull(comment)) {
            translated = qsTranslate(context, text);
        }
        else {
            translated = qsTranslate(context, text, comment);
        }
        if (!isString(translated) || translated.length===0) {
            translated = text;
        }

        // rich text:
        if (translated.indexOf("<")!==-1) {
            translated = AbstractPreferences.stripTags(translated);
            translated = AbstractPreferences.unescapeXml(translated);
        }
        translated = AbstractPreferences.stripAccelerators(translated);
        translated = translated.trim();
        if (translated.length===0) {
            continue;
        }

        ret.push(translated);
    }

    return ret;
};

/**
 * \return Newline separated string with all searchable, translated
 * strings (labels, group titles, tool tips, ...) of the given
 * preference page UI file. The UI file is parsed as text and never
 * loaded as a widget. Results are cached.
 */
AbstractPreferences.getUiStrings = function(uiFileName) {
    if (!isString(uiFileName) || uiFileName.length===0) {
        return "";
    }

    // invalidate cache on locale change:
    var locale = RSettings.getLocale();
    if (AbstractPreferences.uiStringsCacheLocale!==locale) {
        AbstractPreferences.uiStringsCache = {};
        AbstractPreferences.uiStringsCacheLocale = locale;
    }

    var cache = AbstractPreferences.uiStringsCache;
    if (cache.hasOwnProperty(uiFileName)) {
        return cache[uiFileName];
    }

    var ret = "";
    var contents = readTextFile(uiFileName);
    if (isString(contents)) {
        ret = AbstractPreferences.parseUiStrings(contents).join("\n");
    }
    cache[uiFileName] = ret;
    return ret;
};

AbstractPreferences.prototype.beginEvent = function() {
    Edit.prototype.beginEvent.call(this);
    
    this.dialog = this.createDialog(AbstractPreferences.includeBasePath + "/AbstractPreferences.ui");

    WidgetFactory.restoreSize(this.dialog);

    // TODO: Qt 5: add this flag (?)
    //var flags = new Qt.WindowFlags(Qt.WindowTitleHint);
    //this.dialog.setWindowFlags(flags);
    this.treeWidget = this.dialog.findChild("Category");
    var title;
    if (this.appPreferences) {
        title = qsTr("Application Preferences");
    } else {
        title = qsTr("Drawing Preferences");
    }
    this.dialog.setWindowTitle(title);
    this.treeWidget.setHeaderLabel(title);
    this.pageWidget = this.dialog.findChild("Page");
    this.filterWidget = this.dialog.findChild("Filter");
    this.titleWidget = this.dialog.findChild("Title");

    // the tree header is hidden, so screen readers (e.g. macOS VoiceOver)
    // have no label for the navigation tree and the filter field:
    this.treeWidget.accessibleName = title;
    this.filterWidget.accessibleName = this.filterWidget.placeholderText;

    var splitter = this.dialog.findChild("splitter");
    splitter.setStretchFactor(0, 1);
    splitter.setStretchFactor(1, 4);
    
    // connections:
    this.treeWidget.itemSelectionChanged.connect(this, this.showPage);
    this.filterWidget.textChanged.connect(this, this.filterTree);
    // Down in the filter field moves on to the (filtered) navigation tree.
    // A widget shortcut is used because the line edit does not use the arrow
    // keys and its key events cannot be intercepted from script code
    // (Return is not used here: it activates the OK button of the dialog):
    this.treeShortcut = new QShortcut(this.filterWidget);
    this.treeShortcut.objectName = "FilterToTree";
    this.treeShortcut.context = Qt.WidgetShortcut;
    // note: QKeySequence has no binding for the int / QKeyCombination
    // constructor, the key is given as portable text:
    this.treeShortcut.key = new QKeySequence("Down");
    this.treeShortcut.activated.connect(this, this.focusTreeWidget);

    var btApply = this.dialog.findChild("ButtonBox").button(QDialogButtonBox.Apply);
    btApply.clicked.connect(this, this.applyPreferences);

    this.addOns = AddOn.getAddOns();

    AbstractPreferences.fillTreeWidget(this.addOns, this.treeWidget, this.appPreferences);
    this.treeWidget.expandAll();

    if (!isNull(this.initialClassName)) {
        this.showPageFor(this.initialClassName);
    }

    // make sure the navigation tree always has a current item: without one
    // there is nothing for a screen reader to announce when the tree gets
    // the focus and the arrow keys have no anchor to start from:
    if (isNull(this.treeWidget.currentItem())) {
        var firstItem = AbstractPreferences.getFirstVisibleItem(this.treeWidget);
        if (!isNull(firstItem)) {
            this.treeWidget.setCurrentItem(firstItem);
        }
    }

    this.filterWidget.setFocus();

    if (this.dialog.exec() === QDialog.Accepted.valueOf()) {
        // apply calls save and apply:
        this.applyPreferences();
    }
    this.uninit();

    WidgetFactory.saveSize(this.dialog);
    destrDialog(this.dialog);
    EAction.activateMainWindow();
    this.terminate();
};

/**
 * Makes the text of the given navigation tree item available to screen
 * readers.
 *
 * Qt maps a tree item to macOS as a plain group: QAccessible::TreeItem is
 * not in the role map of the Cocoa plugin, and it is not covered by
 * QCocoaAccessible::hasValueAttribute either, so the item has neither a
 * useful role nor an AXValue. Its text ends up in AXTitle only, which
 * VoiceOver does not read for a group. The accessible label of the item
 * (AXDescription) comes from QAccessible::Description, which Qt reads from
 * Qt::AccessibleDescriptionRole - so setting that role gives VoiceOver
 * something to announce.
 */
AbstractPreferences.initAccessibleItemText = function(item, text) {
    item.setData(0, Qt.AccessibleDescriptionRole, text);
};

/**
 * Initializes the navigation tree based on available add-ons with preferences.
 */
AbstractPreferences.fillTreeWidget = function(addOns, treeWidget, appPreferences) {

    var appWin = EAction.getMainWindow();
    var defaultPage = appWin.property("PreferencesPage");
    appWin.setProperty("PreferencesPage", "");

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
            qWarning("AbstractPreferences.js: exception: ", e1);
            qWarning("AbstractPreferences.js: file: ", addOn.getFilePath());
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
            qWarning("AbstractPreferences.js: add-on class not found: ", className, " exception: ", e2);
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
            AbstractPreferences.initAccessibleItemText(item, cat[0]);
            treeWidget.addTopLevelItem(item);
            if (cat.length === 1) {
                item.setData(0, Qt.UserRole, i);
            }
        } else {
            item = items[0];
        }
        var parent = item;
        for (var x = 1; x < cat.length; ++x) {
            var subItem;
            subItem = undefined;
            for (var c = 0; c < parent.childCount(); ++c) {
                var child = parent.child(c);
                if (child.text(0) === cat[x]) {
                    subItem = child;
                    break;
                }
            }
            if (isNull(subItem)) {
                subItem = new QTreeWidgetItem(parent, [ cat[x] ]);
                AbstractPreferences.initAccessibleItemText(subItem, cat[x]);
                parent.addChild(subItem);
                if (x == cat.length - 1) {
                    subItem.setData(0, Qt.UserRole, i);

                    // select a default page:
                    if (className===defaultPage) {
                        subItem.setSelected(true);
                    }
                }
            }
            parent = subItem;
        }
    }
    treeWidget.sortItems(0, Qt.AscendingOrder);
};

/**
 * Applies the settings of all preference pages by calling
 * 'applyPreferences' for every add-on class.
 */
AbstractPreferences.prototype.applyPreferences = function() {
    var mdiChild, document;

    // force all settings to be reloaded from RSettings when they are
    // used next time:
    RSettings.resetCache();
    
    this.save();

    for (var i=0; i<this.addOns.length; ++i) {
        var addOn = this.addOns[i];
        var className = addOn.getClassName();
        
        var widget = addOn.getPreferenceWidget();
        if (isNull(widget)) {
            continue;
        }
        var hasChanged = widget.property("hasChanged");
        if (hasChanged !== true) {
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
                "applyPreferences(): Exception: %1; %2; %3"
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

        // break link from add on to preference widget (preference widget is deleted with dialog):
        addOn.setPreferenceWidget(undefined);

        if (isNull(widget)) {
            continue;
        }
        var hasChanged = widget.property("hasChanged");
        if (hasChanged !== true) {
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
        if (isNull(widget)) {
            continue;
        }
        var hasChanged = widget.property("hasChanged");
        if (hasChanged !== true) {
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
                // saving to block:
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
        rexp = new RegExp(filterText, "im");
    } catch (e) {
        rexp = new RegExp(".*", "im");
    }
    
    for(var i=0; i<this.treeWidget.topLevelItemCount; ++i) {
        var item = this.treeWidget.topLevelItem(i);
        var match = this.itemMatches(item, rexp);
        var found = this.filterItems(item, rexp, match);
        if (found || match) {
            item.setHidden(false);
            item.setExpanded(true);
        } else if(!match) {
            item.setHidden(true);
        }
    }

    // the filter may have hidden the current item: move on to the first
    // remaining category, so that the tree keeps a current item a screen
    // reader can announce and the arrow keys can start from.
    // an item that shows a preference page is left alone: the user is
    // working on that page and it must not disappear while typing a filter.
    // only top level items are considered as the new current item, so that
    // typing a filter does not load a page for every matching sub category.
    var current = this.treeWidget.currentItem();
    if (isNull(current) ||
        (current.isHidden() && isNull(current.data(0, Qt.UserRole)))) {

        var firstItem = AbstractPreferences.getFirstVisibleItem(this.treeWidget);
        if (!isNull(firstItem)) {
            this.treeWidget.setCurrentItem(firstItem);
        }
    }
};

/**
 * \internal
 * \return True if the given navigation tree item matches the given
 * filter regular expression. Matches against the item text (category
 * or page title) and, for pages, against the labels, group titles,
 * tool tips, etc. of the page (see AbstractPreferences.getUiStrings).
 */
AbstractPreferences.prototype.itemMatches = function(item, rexp) {
    if (rexp.test(item.text(0))) {
        return true;
    }

    // match contents of the preferences page (labels, tool tips, ...)
    // without loading the page:
    var i = item.data(0, Qt.UserRole);
    if (isNull(i)) {
        return false;
    }
    var addOn = this.addOns[i];
    if (isNull(addOn)) {
        return false;
    }
    var uiStrings = AbstractPreferences.getUiStrings(addOn.getPreferenceFile());
    if (uiStrings.length===0) {
        return false;
    }
    return rexp.test(uiStrings);
};

/**
 * \internal
 */
AbstractPreferences.prototype.filterItems = function(item, rexp, showAll) {
    var foundAny = false;
    for(var i=0; i<item.childCount(); ++i) {
        var subitem = item.child(i);
        var match = this.itemMatches(subitem, rexp);
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
 * \return The first top level item of the given navigation tree that is
 * not hidden by the filter or undefined if the filter matches nothing.
 */
AbstractPreferences.getFirstVisibleItem = function(treeWidget) {
    for (var i=0; i<treeWidget.topLevelItemCount; ++i) {
        var item = treeWidget.topLevelItem(i);
        if (!item.isHidden()) {
            return item;
        }
    }
    return undefined;
};

/**
 * Moves the keyboard focus from the filter field to the navigation tree
 * and makes sure the tree has a visible current item. This is the keyboard
 * (and screen reader) path from the filter to the matching categories,
 * in addition to Tab.
 */
AbstractPreferences.prototype.focusTreeWidget = function() {
    var item = this.treeWidget.currentItem();
    if (isNull(item) || item.isHidden()) {
        item = AbstractPreferences.getFirstVisibleItem(this.treeWidget);
        if (!isNull(item)) {
            this.treeWidget.setCurrentItem(item);
        }
    }
    this.treeWidget.setFocus();
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
            var col = "red";
            if (RSettings.hasDarkGuiBackground()) {
                col = "#C00000";
            }
            warningLabel.text = "<font color='" + col + "'>" +
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
    // label the page area for screen readers (the title label above it is
    // not associated with the page widget):
    this.pageWidget.accessibleName = this.titleWidget.text;
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

            // loads (initializes) the page:
            this.load(addOn);

            var treeWidget = this.treeWidget;
            widget.settingChangedEvent = function() {
                // mark changed category in bold:
                var font = treeWidget.currentItem().font(0);
                font.setBold(true);
                treeWidget.currentItem().setFont(0, font);
            };
            var btReset = this.dialog.findChild("ResetToDefaults");
            try {
                btReset.clicked.disconnect(this, this.reset);
            } catch (e) {
                // ignored: signal might not be connected
            }
            btReset.clicked.connect(this, this.reset);
        }
    } else {
        widget = this.pageWidget.findChild("empty");
    }
    this.pageWidget.setCurrentWidget(widget);
    this.treeWidget.setCurrentItem(item);
};

AbstractPreferences.prototype.showPageFor = function(className) {
    var flags = makeQtMatchFlags(Qt.MatchWildcard, Qt.MatchContains, Qt.MatchRecursive);
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
    WidgetFactory.resetState(widget);

    var treeWidget = this.treeWidget;
    var font = treeWidget.currentItem().font(0);
    font.setBold(true);
    treeWidget.currentItem().setFont(0, font);
    widget.setProperty("hasChanged", true);
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
