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
include("scripts/sprintf.js");
include("scripts/Widgets/Widgets.js");
include("ListViewEventHandler.js");
include("ItemDelegate.js");
include("FileIconProvider.js");
include("Rdf.js");
include("scripts/Block/InsertScriptItem/InsertScriptItem.js");
include("scripts/Block/InsertBlockItem/InsertBlockItem.js");
include("scripts/AddOn.js");

include("db/ItemPeer.js");
include("db/ItemTagPeer.js");
include("db/LocalePeer.js");
include("db/TagCategoryPeer.js");
include("db/TagPeer.js");


/**
 * Library browser class. 
 * Toggles the library browser dockable widget.
 */
function LibraryBrowser(guiAction) {
    Widgets.call(this, guiAction);
}

LibraryBrowser.prototype = new Widgets();

LibraryBrowser.dbFileName = "library_3_0_0_9.db";
LibraryBrowser.tagHtmlDate = undefined;
LibraryBrowser.includeBasePath = includeBasePath;
LibraryBrowser.regenerateIcons = false;
LibraryBrowser.selectedTagIds = [];
LibraryBrowser.openCategoryIds = [];
LibraryBrowser.maxProgress = Math.max(RSettings.getIntValue("LibraryBrowser/ItemCount", 0), 10000);

LibraryBrowser.tagResultItemsPerPage = RSettings.getIntValue("LibraryBrowser/ItemsPerPage", 36);
LibraryBrowser.tagResultPage = 1;
LibraryBrowser.fsModel = undefined;

LibraryBrowser.ignoredCategories = [
    "creator",
    "dimension",
    "modified",
    "file-name",
    "attribute-as"
];

LibraryBrowser.ignoredCategoriesCompleter = [
    "creator",
    "levelOfDetail",
    "license"
];

QT_TR_NOOP("audience");
QT_TR_NOOP("creator");
QT_TR_NOOP("dimension");
QT_TR_NOOP("levelOfDetail");
QT_TR_NOOP("license");
QT_TR_NOOP("perspective");
QT_TR_NOOP("presentation");
QT_TR_NOOP("publisher");
QT_TR_NOOP("subject");
QT_TR_NOOP("title");

LibraryBrowser.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("Library Browser") ];
};

LibraryBrowser.initPreferences = function(pageWidget) {
    var widgets = getWidgets(pageWidget);
    //LibraryBrowser.widgets = widgets;

    var viewModeCombo = widgets["ViewMode"];
    viewModeCombo.addItem(qsTr("Icon"), "Icon");
    viewModeCombo.addItem(qsTr("List"), "List");

    var dirList = new DirectoryList(pageWidget, "SourceList", qsTr("Choose Source Folder"));
};

LibraryBrowser.applyPreferences = function(doc) {
    //var author = PreferencesPage.widgets["DefaultAuthor"].text;
    //var license = PreferencesPage.widgets["DefaultLicense"].currentText;
    //RSettings.setValue("LibraryBrowser/DefaultAuthor", author);
    //RSettings.setValue("LibraryBrowser/DefaultLicense", license);
//    if (typeof (doc) == "undefined") {
//        // app preferences
//        qDebug("PreferencesPage.js:",
//                "LibraryBrowser: applyPreferences(): appPreferences");
//        return;
//    }
//    // doc preferences
//    qDebug("PreferencesPage.js:",
//            "LibraryBrowser: applyPreferences(): appPreferences: doc:", doc);
};


/**
 * Shows / hides the library browser.
 */
LibraryBrowser.prototype.beginEvent = function() {
    Widgets.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("LibraryBrowserDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
        if (dock.visible) dock.raise();
    }

    if (dock.visible) {
        // the library browser only initializes itself if it is shown for the
        // first time. this can be during startup or later:
        LibraryBrowser.showFirstTime();
    }
};

LibraryBrowser.prototype.finishEvent = function() {
    Widgets.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("LibraryBrowserDock");
    this.getGuiAction().setChecked(dock.visible);
};


/**
 * \return Path and file name of the SQLite database file.
 * Adjusted every time the DB schema changes.
 */
LibraryBrowser.getDbFileName = function() {
    return RSettings.getPath() + QDir.separator + LibraryBrowser.dbFileName;
};

/**
 * \return Source paths (root paths for library items).
 */
LibraryBrowser.getSourceList = function() {
    var i;

    // get list of sources (root paths) from ini file:
    var sourceList = RSettings.getValue("LibraryBrowser/SourceList");
    if (isNull(sourceList)) {
        sourceList = [];
    }
    else {
        for (i=0; i<sourceList.length; i++) {
            sourceList[i] = QDir.fromNativeSeparators(sourceList[i]);
        }
    }

    var noSourcesConfigured = sourceList.length===0;

    var filters = new QDir.Filters(QDir.AllDirs, QDir.NoDotAndDotDot, QDir.Readable);
    var sortFlags = new QDir.SortFlags(QDir.Name, QDir.IgnoreCase);
    var librariesDir;
    var libs;

    // no configuration: add all libraries available in libraries subdir:
    librariesDir = new QDir("libraries");
    libs = librariesDir.entryList([], filters, sortFlags);
    for (i=0; i<libs.length; i++) {
        // always add default library if available:
        if (libs[i]==="default" || noSourcesConfigured) {
            sourceList.push(QDir.fromNativeSeparators(new QDir("libraries/%1".arg(libs[i])).absolutePath()));
        }
    }

    // always add libraries of installed add-ons:
    var localAddOns = AddOn.getLocalAddOns();
    for (var k=0; k<localAddOns.length; k++) {
        var localAddOnDir = RSettings.getDataLocation() + "/" + localAddOns[k];
        var fi = new QFileInfo(localAddOnDir);
        if (fi.exists()) {
            //sourceList.push(new QDir(fi.absoluteFilePath() + "/libraries/%1".arg(libs[i])).absolutePath());
            librariesDir = new QDir(fi.absoluteFilePath() + "/libraries");
            libs = librariesDir.entryList([], filters, sortFlags);
            for (i=0; i<libs.length; i++) {
                var path = new QDir(fi.absoluteFilePath() + "/libraries/%1".arg(libs[i])).absolutePath();
                path = QDir.fromNativeSeparators(path);
                qDebug("adding libraries dir of add-on: ", path);
                sourceList.push(path);
            }
        }
    }

    sourceList = sourceList.unique();

    return sourceList;
};

LibraryBrowser.getMd5Sum = function(str) {
    return str;
    //return QCryptographicHash.hash(new QByteArray(str), QCryptographicHash.Md5);
};

/**
 * \return Currently selected source path from source combo box in the
 * file system tab.
 */
LibraryBrowser.getCurrentSourcePath = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");

    // fill source combo
    var sourceCombo = formWidget.findChild("SourceCombo");
    if (sourceCombo.currentIndex === -1) {
        return;
    }

    var sourcePath = sourceCombo.itemData(sourceCombo.currentIndex);
    if (isNull(sourcePath)) {
        //sourceCombo.currentIndex = 0;
        return;
    }
    return sourcePath;
};

/**
 * Creates and shows the dock widget.
 */
//LibraryBrowser.prototype.initGui = function() {
//    var appWin = EAction.getMainWindow();
//    var existingDock = appWin.findChild("LibraryBrowser");
//    var formWidget = WidgetFactory.createWidget(LibraryBrowser.includeBasePath, "LibraryBrowser.ui");
//    var dock = new QDockWidget(qsTr("Library Browser"), appWin);
//    dock.objectName = "LibraryBrowser";

////    var width = RSettings.getIntValue("LibraryBrowser/Width", 300);
////    var height = RSettings.getIntValue("LibraryBrowser/Height", appWin.height);
////    var x = RSettings.getIntValue("LibraryBrowser/X", appWin.x + appWin.width + 10);
////    var y = RSettings.getIntValue("LibraryBrowser/Y", appWin.y);
//    //dock.floating = RSettings.getBoolValue("LibraryBrowser/Floating", true);
////    if (dock.floating) {
////        dock.resize(width, height);
////        dock.move(x, y);
////    }
//    dock.setWidget(formWidget);
//    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
//};

LibraryBrowser.initFileSystemTab = function() {
    var i;
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");

    // fill source combo
    var sourceCombo = formWidget.findChild("SourceCombo");
//    var icon = new QIcon(LibraryBrowser.includeBasePath + "/Open.svg");
//    var sources = ItemPeer.getSourceItems();
//    for (i=0; i<sources.length; ++i) {
//        var fi = new QFileInfo(sources[i].getFilePath());
//        // TODO adjust length
//        //var elidedPath = fi.absolutePath().elidedText(sourceCombo.font, 200);
//        var sourceTitles = sources[i].getTitles();
//        var title = fi.fileName();
//        if (!isNull(sourceTitles) && sourceTitles.length>0) {
//            title = sourceTitles[0];
//        }

//        sourceCombo.addItem(icon, title /*+ " [" + elidedPath + "]"*/, fi.filePath());
//    }
    sourceCombo['currentIndexChanged(QString)'].connect(LibraryBrowser, "sourceChanged");
    LibraryBrowser.sourceChanged("");

    // file system list view
    var itemView = formWidget.findChild("FileSystemListView");
    LibraryBrowser.initEventHandler(itemView);

    // item delegate (to rename items?)
    //var fsListView = formWidget.findChild("FileSystemListView");
    //var itemDelegate = new ItemDelegate(this);
    //fsListView.setItemDelegate(itemDelegate);

    // connect dir tree:
    var dirTree = formWidget.findChild("DirectoryTree");

    // context menu for directories
    dirTree.contextMenuPolicy = Qt.CustomContextMenu;
    // avoid multiple connection
    dirTree.customContextMenuRequested.connect(
        function(point) {
            var index = dirTree.indexAt(point);
            if (!index.isValid()) {
                return;
            }
            var model = dirTree.model();
            var filePath = model.filePath(index);
            var menu = LibraryBrowser.createItemContextMenu(dirTree, filePath, undefined, index);
            menu.exec(QCursor.pos());
        });

    dirTree.installEventFilter(new REventFilter(QEvent.KeyPress.valueOf(), true));
    dirTree.installEventFilter(new REventFilter(QEvent.KeyRelease.valueOf(), true));
};

LibraryBrowser.updateFileSystemTab = function() {
    var i;
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");

    var sources = ItemPeer.getSourceItems();

    var sourceCombo = formWidget.findChild("SourceCombo");

    var doUpdate = true;
    if (sources.length===sourceCombo.count) {
        doUpdate = false;
        for (i=0; i<sources.length; i++) {
            if (new QFileInfo(sources[i].getFilePath()).filePath()!==sourceCombo.itemData(i)) {
                doUpdate = true;
                break;
            }
        }
    }

    if (!doUpdate) {
        return;
    }

    // update source combo
    sourceCombo.clear();
    var icon = new QIcon(LibraryBrowser.includeBasePath + "/Open.svg");
    for (i=0; i<sources.length; ++i) {
        var fi = new QFileInfo(sources[i].getFilePath());
        // TODO adjust length
        //var elidedPath = fi.absolutePath().elidedText(sourceCombo.font, 200);
        var sourceTitles = sources[i].getTitles();
        var title = fi.fileName();
        if (!isNull(sourceTitles) && sourceTitles.length>0) {
            title = sourceTitles[0];
        }

        sourceCombo.addItem(icon, title /*+ " [" + elidedPath + "]"*/, fi.filePath());
    }
}

/**
 * Initializes the favorites tab.
 */
LibraryBrowser.initFavoritesTab = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var itemView = appWin.findChild("FavoritesListView");

    var model = new QStandardItemModel(formWidget);
    itemView.setModel(model);

    LibraryBrowser.initEventHandler(itemView);
};

/**
 * Updates the items shown in the favorites tab.
 */
LibraryBrowser.updateFavoritesTab = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var itemView = appWin.findChild("FavoritesListView");
    LibraryBrowser.initItemView(itemView);

    var model = itemView.model();
    model.clear();

    var items = Favorites.getAllAsItems();
    for (var i = 0; i < items.length; ++i) {
        var item = items[i];
        var qsItem = LibraryBrowser.createQsItem(item, true);
        model.appendRow(qsItem);
    }
};

/**
 * Initializes the tags tab.
 */
LibraryBrowser.initTagsTab = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
//    var tagsBrowser = appWin.findChild("TagsBrowser");
//    var webPage = tagsBrowser.page();
//    webPage.linkDelegationPolicy = QWebPage.DelegateAllLinks;

    // make web view transparent:
//    var palette = tagsBrowser.palette;
//    palette.setBrush(QPalette.Base, new QColor(0,0,0,0));
//    webPage.palette = palette;
//    if (!RSettings.isQt(5)) {
//        tagsBrowser.setAttribute(Qt.WA_OpaquePaintEvent, false);
//    }
//    tagsBrowser.linkClicked.connect(LibraryBrowser, "linkClicked");

    var itemView =formWidget.findChild("TagsListView");
    var model = new QStandardItemModel(formWidget);
    itemView.setModel(model);
    LibraryBrowser.initEventHandler(itemView);
    //LibraryBrowser.initItemView(itemView);

    //var splitter =formWidget.findChild("TagsSplitter");
    //splitter.setSizes([splitter.height/2,splitter.height/2]);

    // navigation:
    var prevButton = formWidget.findChild("TagsNaviPrevious");
    prevButton.clicked.connect(function() {
        LibraryBrowser.tagResultPage--;
        LibraryBrowser.updateTagsView();
    });

    var nextButton = formWidget.findChild("TagsNaviNext");
    nextButton.clicked.connect(function() {
        LibraryBrowser.tagResultPage++;
        LibraryBrowser.updateTagsView();
    });

    // search:
    var clearButton = formWidget.findChild("ClearFindText");
    clearButton.clicked.connect(function() {
        var findEdit = formWidget.findChild("FindText");
        findEdit.clear();
        LibraryBrowser.updateTagsView();
    });

    var findEdit = formWidget.findChild("FindText");
    findEdit.returnPressed.connect(function() {
        LibraryBrowser.updateTagsView();
    });

    var findButton = formWidget.findChild("Find");
    findButton.clicked.connect(function() {
        LibraryBrowser.updateTagsView();
    });
};

/**
 * Called when user clicks (toggles) a category or tag in the tag browser.
 * The category or tag ID is passed as fragment with a leading 'c' or 't':
 * e.g. #t100 or #c3
 */
LibraryBrowser.linkClicked = function(url) {
    //qDebug("url: ", url);
    //qDebug("fragment: ", url.fragment());

    var fragment = url.fragment();
    if (fragment.length<2) {
        debugger;
    }

    // type is 'c' for category or 't' for tag:
    var type = fragment[0];

    var id = parseInt(fragment.substring(1), 10);

    if (type==='t') {
        // toggle tag:
        if (LibraryBrowser.selectedTagIds.contains(id)) {
            LibraryBrowser.selectedTagIds.remove(id);
        }
        else {
            LibraryBrowser.selectedTagIds.push(id);
        }

        //LibraryBrowser.updateTagsTab(true);
        LibraryBrowser.updateTagsView(fragment);
    }
    else if (type==='c') {
        // toggle category:
        if (LibraryBrowser.openCategoryIds.contains(id)) {
            LibraryBrowser.openCategoryIds.remove(id);
        }
        else {
            LibraryBrowser.openCategoryIds.push(id);
        }
    }
    else {
        debugger;
    }

};

/**
 * Updates the tag categories in the top part of the tags tab.
 * \param force true: update HTML even if DB has not changed.
 */
LibraryBrowser.updateTagsTab = function(force) {
    // disabled:
    return;

    if (force!==true) {
        var dbFileName = LibraryBrowser.getDbFileName();
        var dbMod = new QFileInfo(dbFileName).lastModified();
        //qDebug("LibraryBrowser.tagHtmlDate: ", LibraryBrowser.tagHtmlDate);
        //qDebug("dbMod: ", dbMod);
        if (!isNull(LibraryBrowser.tagHtmlDate) && dbMod<LibraryBrowser.tagHtmlDate) {
            return;
        }
    }

    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var itemView = appWin.findChild("TagsListView");
    var tagsBrowser = appWin.findChild("TagsBrowser");
    LibraryBrowser.initItemView(itemView);
    var locale = RSettings.getLocale();

    LibraryBrowser.tagResultPage=1;

    var mainFrame = tagsBrowser.page().mainFrame();

    var width = tagsBrowser.page().viewportSize.width() - 20;
    var columns = Math.floor(width / 100);
    if (columns===0) {
        columns = 1;
    }

    var colWidth = Math.floor(width/columns) - 16;

    mainFrame.setScrollBarPolicy(Qt.Horizontal,Qt.ScrollBarAlwaysOff);
    mainFrame.setScrollBarPolicy(Qt.Vertical,Qt.ScrollBarAlwaysOn);

    var categories = TagCategoryPeer.doSelectAll();

    var url = QUrl.fromLocalFile(LibraryBrowser.includeBasePath + "/TagStyles.css");

    var html = "";
    html += "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.0//EN' 'http://www.w3.org/TR/REC-html40/strict.dtd'>\n";
    html += "<html>\n";
    html += "<head>\n";
    html += "<link rel='stylesheet' type='text/css' href='" + url.toString() + "'/>\n";
    html += "<script language='JavaScript'>\n";
    html += "function toggleCategory(tagsId, catId) {\n";
    html += "    var el = document.getElementById(tagsId);\n";
    html += "    if (el.className == 'tagsClosed') {\n";
    html += "        el.className = 'tagsOpen';\n";
    html += "    }\n";
    html += "    else {\n";
    html += "        el.className = 'tagsClosed';\n";
    html += "    }\n";
    html += "    el = document.getElementById(catId);\n";
    html += "    if (el.className == 'categoryClosed') {\n";
    html += "        el.className = 'categoryOpen';\n";
    html += "    }\n";
    html += "    else {\n";
    html += "        el.className = 'categoryClosed';\n";
    html += "    }\n";
    html += "    return false;\n";
    html += "}\n";
    html += "function toggleTag(id) {\n";
    html += "    var el = document.getElementById(id);\n";
    html += "    if (el.className == 'tagOff') {\n";
    html += "        el.className = 'tagOn';\n";
    html += "    }\n";
    html += "    else {\n";
    html += "        el.className = 'tagOff';\n";
    html += "    }\n";
    html += "    return false;\n";
    html += "}\n";
    html += "</script>\n";
    html += "</head>\n";
    html += "<body>\n";

    var i;

    // File and dir items that match the current tag selection and search string.
    // Only tags which further limit this item selection will be shown.
    var itemIds = ItemPeer.getIdsByTagIdsAndText(LibraryBrowser.selectedTagIds, "");

    // add parent items:
    var parentIds = [];
    for (i=0; i<itemIds.length; i++) {
        parentIds = parentIds.concat(ItemPeer.getAncestorIds(itemIds[i]));
    }
    parentIds.sortNumerical();
    parentIds = parentIds.unique();
    itemIds = itemIds.concat(parentIds);
    itemIds.sortNumerical();
    itemIds = itemIds.unique();

    var completerWordList = [];

    // iterate through categories:
    for (i=0; i<categories.length; i++) {
        var cat = categories[i];

        // ignore 'modified', 'file name' and 'attribute-as' categories for now:
        if (LibraryBrowser.ignoredCategories.indexOf(cat.name)!==-1) {
            continue;
        }

        var col = 1;
        var tags = TagPeer.doSelectByCategoryIdAndLocale(cat.id, locale, [], ["text", "id"]);
        //var tags = TagPeer.doSelectByCategoryIdAndLocale(cat.id, locale, LibraryBrowser.selectedTagIds, ["text", "id"]);
        //var tags = TagPeer.doSelectByCategoryIdAndLocale(cat.id, locale, itemIds, ["text", "id"]);
        //var tags = TagPeer.doSelectByCategoryIdAndLocale(cat.id, locale, [], ["text", "id"]);

        // skip empty categories:
        if (tags.length===0) {
            continue;
        }

        var cssClass;
        var tagsHtml = "";
        for (var k=0; k<tags.length; k++) {
            var tag = tags[k];
            var tagText = tag.text;

            if (cat.name==="license") {
                if (tag.text.startsWith("http://creativecommons.org/licenses/by-nc")) {
                    tagText = "CC BY NC";
                }
                else if (tag.text.startsWith("http://creativecommons.org/licenses/by")) {
                    tagText = "CC BY";
                }
                else if (tag.text.startsWith("http://creativecommons.org/publicdomain/mark")) {
                    tagText = "Public Domain Mark";
                }
                else if (tag.text.startsWith("https://creativecommons.org/about/cc0")) {
                    tagText = "CC0";
                }
                // obsolete?
                else if (tag.text.startsWith("http://creativecommons.org/licenses/publicdomain")) {
                    tagText = "Public Domain";
                }
            }

            // if category is not ignored for word completion: add word to completion list:
            if (LibraryBrowser.ignoredCategoriesCompleter.indexOf(cat.name)===-1) {
                completerWordList.push(tag.text);
            }

            var selected = LibraryBrowser.selectedTagIds.contains(tag.id);
            cssClass = (selected ? "tagOn" : "tagOff");
            tagsHtml += "<a onclick='javascript:toggleTag(\"t" + tag.id + "\")' "
                         + "href='#t" + tag.id + "' "
                         + "title='" + tag.text + "'>";
            tagsHtml += "<div id='t" + tag.id + "' "
                 +       "class='" + cssClass + "' style='width:" + colWidth + "px'>";
            tagsHtml += tagText;
            tagsHtml += "</div>";
            tagsHtml += "</a>\n";
        }

        var categoryIsOpen = LibraryBrowser.openCategoryIds.contains(cat.id);
        html += "<div class='clear'></div>\n";
        html += "<a name='category" + cat.id + "'/>";
        html += "<a onclick='javascript:toggleCategory(\"c" + cat.id + "\", \"ct" + cat.id + "\");' "
                 + "href='#c" + cat.id + "'>\n";
        cssClass = categoryIsOpen ? "categoryOpen" : "categoryClosed";
        html += "<div class='" + cssClass + "' id='ct" + cat.id + "'>";
        html += qsTr(cat.name);
        html += "</div>\n";
        html += "</a>\n";

        cssClass = categoryIsOpen ? "tagsOpen" : "tagsClosed";
        html += "<div class='" + cssClass + "' id='c" + cat.id + "'>\n";

        html += tagsHtml;

        html += "</div>\n";
    }

    html += "</body>\n";
    html += "</html>\n";

    LibraryBrowser.tagHtmlDate = new Date();

    //qDebug("html: ", html);

    tagsBrowser.setHtml(html);

    //mainFrame.scrollPosition = pos;

    //LibraryBrowser.scrollTagsTab(scrollToFragment);

    //LibraryBrowser.updateTagsView();

    completerWordList = completerWordList.sort();
    completerWordList = completerWordList.unique();
    LibraryBrowser.updateCompleter(completerWordList);
};

LibraryBrowser.scrollTagsTab = function(fragment) {
    // disabled:
    return;

    var appWin = RMainWindowQt.getMainWindow();
    var tagsBrowser = appWin.findChild("TagsBrowser");

    if (!isNull(fragment)) {
        tagsBrowser.page().mainFrame().evaluateJavaScript(
            "window.location.hash='" + fragment + "';");
    }
};

/**
 * Updates the word completer in the search field.
 */
LibraryBrowser.updateCompleter = function(wordList) {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var findEdit = formWidget.findChild("FindText");

    var completer = new QCompleter(wordList);
    completer.caseSensitivity = Qt.CaseInsensitive;
    findEdit.setCompleter(completer);
};

/**
 * Called to update tag results.
 */
LibraryBrowser.updateTagsView = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var itemView =formWidget.findChild("TagsListView");
    var findEdit = formWidget.findChild("FindText");
    var locale = RSettings.getLocale();

    var searchString = findEdit.text;

    // stem single words only:
    if (searchString.indexOf(" ")===-1) {
        searchString = RStemmer.stem(searchString, locale);
    }

    LibraryBrowser.initItemView(itemView);
    itemView.scrollToTop();

    // clear previously shown results:
    var model = itemView.model();
    model.clear();

    // all matching item IDs:
    var itemIds = ItemPeer.getIdsByTagIdsAndText(LibraryBrowser.selectedTagIds, searchString);
    // all matching item IDs and names, ordered by name:
    var items = ItemPeer.doSelectByIds(itemIds, ["id", "name"]);

    //items.sort(ItemPeer.sort);

//    for (var k=0; k<items.length; k++) {
//        qDebug(items["id"], items["name"]);
//    }

    // paging:
    var page = LibraryBrowser.tagResultPage;
    var limit = LibraryBrowser.tagResultItemsPerPage;
    var pages = Math.max(1, Math.ceil(items.length / limit));
    var start = (page-1)*limit;
    var end = start+limit;
    var i;

    var itemsSlice = items.slice(start, end);
    var itemsSliceIds = [];
    for (i=0; i<itemsSlice.length; i++) {
        itemsSliceIds.push(itemsSlice[i].id);
    }

    // only items of current page:
    items = ItemPeer.doSelectByIds(itemsSliceIds);

    for (i=0; i<items.length; i++) {
        var item = items[i];
        var qsItem = LibraryBrowser.createQsItem(item, false);
        model.appendRow(qsItem);
    }

    // update page status:
    var label = formWidget.findChild("TagsNaviInfo");
    label.text = qsTr("Page %1 of %2").arg(page).arg(pages===0 ? 1 : pages);

    // enable / disable prev / next buttons:
    var prevButton = formWidget.findChild("TagsNaviPrevious");
    if (page===1) {
        prevButton.enabled = false;
    }
    else {
        prevButton.enabled = true;
    }

    var nextButton = formWidget.findChild("TagsNaviNext");
    if (page===pages) {
        nextButton.enabled = false;
    }
    else {
        nextButton.enabled = true;
    }
};

/**
 * Shows the next result page of the tag results.
 */
LibraryBrowser.showNext = function() {
    LibraryBrowser.tagResultPage++;
    LibraryBrowser.updateTagsView();
};

/**
 * Called when user changes the source (root path) in the file system tab.
 */
LibraryBrowser.sourceChanged = function(text) {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");

    var sourceCombo = formWidget.findChild("SourceCombo");
//    if (sourceCombo.currentIndex === -1) {
//        //LibraryBrowser.setSource(undefined);
//        return;
//    }

//    var itemData = sourceCombo.itemData(sourceCombo.currentIndex);
//    if (isNull(itemData)) {
//        sourceCombo.currentIndex = 0;
//        return;
//    }

    var sourcePath = LibraryBrowser.getCurrentSourcePath();

    if (isNull(sourcePath)) {
        //qWarning("LibraryBrowser: no source selected");
        return;
    }

    var libPath = new QFileInfo(sourcePath);
    //LibraryBrowser.setSource(libPath.absoluteFilePath());
    sourceCombo.toolTip = libPath.absoluteFilePath();
    if (!libPath.exists()) {
        qWarning("LibraryBrowser: library path doesn't exist: ", libPath.fileName());
        return;
    }

    LibraryBrowser.fsModel = new RFileSystemModel();
    LibraryBrowser.fsModel.setIconProvider(new FileIconProvider());
    //LibraryBrowser.fsModel.readOnly = true;
    var filter = new QDir.Filters(QDir.Dirs, QDir.NoDotAndDotDot);
    LibraryBrowser.fsModel.setFilter(filter);

    // the Qt way of hiding all folders named "_META"...
    LibraryBrowser.fsModel.setNameFilterDisables(false);
    var nf = [];
    var ch;
    // TODO:
    for ( var i = 0; i < 26; ++i) {
        ch = sprintf("%c*", 65 + i);
        nf.push(ch);
        ch = sprintf("%c*", 97 + i);
        nf.push(ch);
    }
    for ( var i = 0; i < 10; ++i) {
        ch = sprintf("%c*", 48 + i);
        nf.push(ch);
    }
    LibraryBrowser.fsModel.setNameFilters(nf);

    LibraryBrowser.fsModel.setRootPath(libPath.path());
    var dirTree = formWidget.findChild("DirectoryTree");

    // this should be possible, but isn't properly scriptable:
    //var proxyModel = new QSortFilterProxyModel(dirTree);
    //proxyModel.setSourceModel(LibraryBrowser.fsModel);
    //dirTree.setModel(proxyModel.castToQAbstractItemModel());

    dirTree.setModel(LibraryBrowser.fsModel);

    // context menu for directories
//    dirTree.contextMenuPolicy = Qt.CustomContextMenu;
//    // avoid multiple connection
//    if (!LibraryBrowser.directoryContextMenuConnected) {
//        dirTree.customContextMenuRequested.connect(
//                this,
//                function(point) {
//                    var index = dirTree.indexAt(point);
//                    if (!index.isValid()) {
//                        return;
//                    }
//                    var menu = LibraryBrowser.createDirectoryContextMenu(dirTree, index);
//                    menu.exec(QCursor.pos());
//                }, Qt.UniqueConnection);
//        LibraryBrowser.directoryContextMenuConnected = true;
//    }

    var selectionModel = dirTree.selectionModel();
    selectionModel.selectionChanged.connect(LibraryBrowser, "directoryChanged");
    var index = LibraryBrowser.fsModel.pathIndex(libPath.path(), 0);
    dirTree.setRootIndex(index);

    LibraryBrowser.fsModel.rowsInserted.connect(function(parent, start, end) {
        var fileName = new QFileInfo(LibraryBrowser.fsModel.rootPath()).fileName();
        var model = dirTree.model();
        if (fileName !== model.data(parent)) {
            return;
        }
        for ( var r = 0; r < model.rowCount(parent); ++r) {
            var index = model.index(r, 0, parent);
            var dir = model.data(index);
            if (dir !== libPath.fileName()) {
                dirTree.setRowHidden(r, parent, true);
            }
        }
    });

    var header = dirTree.header();
    // hide sections size, type and date modified
    header.hideSection(header.logicalIndex(1));
    header.hideSection(header.logicalIndex(2));
    header.hideSection(header.logicalIndex(3));

    var itemView = formWidget.findChild("FileSystemListView");
    if (!isNull(itemView)) {
        itemView.setModel(null);
    }
};

LibraryBrowser.getSelectedIndexes = function(selectionModel) {
    if (isNull(selectionModel)) {
        return undefined;
    }

    if (isFunction(selectionModel.selectedIndexes)) {
        // Qt 4:
        return selectionModel.selectedIndexes();
    }
    else {
        // Qt 5:
        return selectionModel.selection.indexes();
    }
};

/**
 * Called when user changes the directory in the file system tree (top).
 * Updates the list view (bottom).
 *
 * \param selected QItemSelection Selected items.
 */
LibraryBrowser.directoryChanged = function(selected, deselected) {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");

    if (isNull(selected)) {
        var dirTree = formWidget.findChild("DirectoryTree");
        var selectionModel = dirTree.selectionModel();
        if (!isNull(selectionModel)) {
            selected = LibraryBrowser.getSelectedIndexes(selectionModel);
        }
    }
    else {
        selected = selected.indexes();
    }

    var listView = formWidget.findChild("FileSystemListView");
    var model = new QStandardItemModel(formWidget);
    listView.setModel(model);
    if (isNull(selected) || selected.length === 0) {
        return;
    }

    var index = selected[0];
    // TODO: needed every time or one time only?
    // -> possibly every time (update view according to settings).
    LibraryBrowser.initItemView(listView);
    //var dirPath = index.model().filePath(index);
    var dirPath = LibraryBrowser.fsModel.filePath(index);

    // TODO:
    //var source = DirectoryPeer.doSelectSourceByName(sourceCombo.itemData(sourceCombo.currentIndex));
    //var sourcePath = sourceCombo.itemData(sourceCombo.currentIndex);
//    if (isNull(source)) {
//        return;
//    }

    //qDebug("LibraryBrowser.directoryChanged: dirPath: ", dirPath);
    setOverrideWaitCursor();
    LibraryBrowser.updateFsView(dirPath, model);
    restoreOverrideCursor();

    RSettings.setValue("LibraryBrowser/Path", dirPath);
};

/**
 * Called when user changes into a directory.
 * Syncs the directory and updates the list view in the file system tab.
 */
LibraryBrowser.updateFsView = function(dirPath, model) {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var sourcePath = LibraryBrowser.getCurrentSourcePath();
    var sourceItem = ItemPeer.getItemFromPath(sourcePath, undefined, ["id"]);

    if (isNull(sourceItem)) {
        return;
    }

    // sync dir:
    LibraryBrowser.sync(dirPath, undefined, undefined, 1);

    // update files:
    var filters = new QDir.Filters(QDir.Files, QDir.AllDirs, QDir.NoDotAndDotDot, QDir.Readable);
    var sort = new QDir.SortFlags(QDir.DirsFirst, QDir.Name, QDir.IgnoreCase);
    var dir = new QDir(dirPath);
    var pats = RFileImporterRegistry.getFilterExtensionPatterns();
    pats.push("*.js");
    pats.push("*.svg");
    var eil = dir.entryInfoList(pats, filters, sort);
    var sourceDir = new QDir(sourcePath);

    var progressDialog = new QProgressDialog(
        qsTr("Updating icons..."),
        qsTr("Abort"), 0, eil.length, this
    );
    progressDialog.windowModality = Qt.WindowModal;
    progressDialog.minimumDuration = 2000;
    progressDialog.setCancelButton(null);

    for (var i=0; i<eil.length; ++i) {
        var fi = eil[i];

        if (fi.fileName()==="_META") {
            continue;
        }

        var item = ItemPeer.getItemFromPath(sourceDir.relativeFilePath(fi.absoluteFilePath()), sourceItem.id);

        // item not in DB (e.g. auto save backup file):
        if (isNull(item)) {
            continue;
        }

        var qsItem = LibraryBrowser.createQsItem(item, false);
        model.appendRow(qsItem);

        progressDialog.value++;
    }

    progressDialog.reset();
};

/**
 * Updates the QStandardItem with the given Id.
 */
LibraryBrowser.updateQsItem = function(itemView, itemId) {
    var item = ItemPeer.doSelectById(itemId);
    var qsItem = LibraryBrowser.createQsItem(item);

    var model = itemView.model();
    var mi = itemView.currentIndex();
    if (!mi.isValid()) {
        return;
    }
    model.setItem(mi.row(), qsItem);
};

/**
 * Creates a QStandardItem from the given library browser Item.
 */
LibraryBrowser.createQsItem = function(item, noFavoritesMark) {
    var path = item.getFilePath();
    var fi = new QFileInfo(path);

    var icon = item.getIcon(false, LibraryBrowser.regenerateIcons, noFavoritesMark);
//    if (item.isFavorite()) {
//        icon = LibraryBrowser.createFavoriteIcon(icon);
//    }
    var titles = item.getTitles();
//    var licenses = item.getLicenses();
//    var attributeAs = item.getAttributeAs();

    var qsItem = new QStandardItem(icon, titles[0]);
    qsItem.setData(fi.absoluteFilePath(), Qt.UserRole);
    qsItem.setData(item.id, Qt.UserRole + 1);

    // tool tip
//    var html = "<html>";
//    for (var i=0; i<titles.length && i<3; i++) {
//        html += "<b>" + titles[i] + "</b><br>";
//    }
//    html += "<i>" + qsTr("File:") + "</i> " + fi.fileName() + "<br>";
//    html += "<i>" + qsTr("Folder:") + "</i><br>";
//    html += fi.absolutePath() + "<br>";
//    for (i=0; i<licenses.length && i<3; i++) {
//        html += "<i>" + qsTr("License:") + "</i> " + licenses[i] + "<br>";
//    }
//    for (i=0; i<attributeAs.length && i<1; i++) {
//        html += "<i>" + qsTr("Attribute as:") + "</i> " + attributeAs[i];
//    }

//    qsItem.setToolTip(html);

    if (!fi.isWritable()) {
        qsItem.setEditable(false);
        var font = qsItem.font();
        font.setItalic(true);
        qsItem.setFont(font);
    }
    return qsItem;
};

/**
 * Creates and initializes an event handler for the given item view.
 */
LibraryBrowser.initEventHandler = function(itemView) {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var dirTree = formWidget.findChild("DirectoryTree");
    var tabWidget = formWidget.findChild("TabWidget");
//    var viewName = viewNames[i];
//    var itemView = formWidget.findChild(viewName);

    var eventHandler = new ListViewEventHandler(itemView, dirTree);
    itemView.signalMousePressEvent.connect(this, function(evt) {
        eventHandler.mousePressEvent(evt);
    });
    itemView.signalMouseMoveEvent.connect(function(evt) {
        eventHandler.mouseMoveEvent(evt);
    });
    itemView.doubleClicked.connect(function(index) {
        var listModel = itemView.model();
        var file = listModel.data(index, Qt.UserRole);
        var fi = new QFileInfo(file);
        if (fi.isDir()) {
            tabWidget.currentIndex = 0;
        }
        eventHandler.doubleClicked(file);
    });
    // file system context menu:
    itemView.contextMenuPolicy = Qt.CustomContextMenu;
    itemView.customContextMenuRequested.connect(function(point) {
        var index = itemView.indexAt(point);
        if (!index.isValid()) {
            return;
        }
        var model = itemView.model();
        var filePath = model.data(index, Qt.UserRole);
        var itemId = model.data(index, Qt.UserRole + 1);
        var menu = LibraryBrowser.createItemContextMenu(itemView, filePath, itemId, index);
        menu.exec(QCursor.pos());
    });
};

/**
 * Initializes the given item view (icon size, properties, ...).
 */
LibraryBrowser.initItemView = function(itemView) {
    var s = RSettings.getIntValue("LibraryBrowser/IconSize", 64);
    itemView.iconSize = new QSize(s, s);
    itemView.uniformItemSizes = true;
    itemView.layoutMode = QListView.SinglePass;

    var mode = RSettings.getStringValue("LibraryBrowser/ViewMode", "Icon");
    if (mode === "List") {
        itemView.viewMode = QListView.ListMode;
        itemView.isWrapping = false;
        itemView.flow = QListView.TopToBottom;
    } else {
//        var showAsGrid = RSettings.getBoolValue("LibraryBrowser/ShowAsGrid", true);
//        if (showAsGrid) {
            itemView.gridSize = new QSize(s + 24, s + 24);
            itemView.wordWrap = true;
//        } else {
//            itemView.gridSize = new QSize();
//            itemView.wordWrap = false;
//        }
        itemView.viewMode = QListView.IconMode;
        itemView.isWrapping = true;
        itemView.flow = QListView.LeftToRight;
    }
    itemView.movement = QListView.Static;
    //itemView.viewport().acceptDrops = true;
    itemView.resizeMode = QListView.Adjust;
    itemView.editTriggers = new QAbstractItemView.EditTriggers(QAbstractItemView.NoEditTriggers);

    // itemView.acceptDrops = true;
    itemView.acceptDrops = false;
    itemView.dragEnabled = false;
    // itemView.dropIndicatorShown = true;

    itemView.signalToolTipRequested.connect(function(e) {
        var idx = itemView.indexAt(e.pos());
        if (!idx.isValid()) {
            return;
        }

        var id = itemView.model().data(idx, Qt.UserRole + 1);
        var item = ItemPeer.doSelectById(id);
        if (isNull(item)) {
            return;
        }

        var path = item.getFilePath();
        var fi = new QFileInfo(path);

        var titles = item.getTitles();
        var licenses = item.getLicenses();
        var creators = item.getCreators();
        var attributeAs = item.getAttributeAs();

        var html = "<html>";
        for (var i=0; i<titles.length && i<3; i++) {
            html += "<b>" + titles[i] + "</b><br>";
        }
        html += "<i>" + qsTr("File:") + "</i> " + fi.fileName() + "<br>";
        html += "<i>" + qsTr("Folder:") + "</i><br>";
        html += fi.absolutePath() + "<br>";
        for (i=0; i<licenses.length && i<3; i++) {
            html += "<i>" + qsTr("License:") + "</i> " + licenses[i] + "<br>";
        }
        for (i=0; i<attributeAs.length && i<1; i++) {
            html += "<i>" + qsTr("Attribute as:") + "</i> " + attributeAs[i];
        }
        for (i=0; i<creators.length && i<1; i++) {
            html += "<i>" + qsTr("Creator:") + "</i> " + creators[i];
        }

        QToolTip.showText(e.globalPos(), html, itemView);
    });
};


/**
 * Synchronizes DB from file system while showing a progress dialog.
 */
LibraryBrowser.syncWithProgress = function(startUp) {
    //qDebug("LibraryBrowser.syncWithProgress");
    //qDebug("LibraryBrowser.maxProgress: ", LibraryBrowser.maxProgress);

    var progressDialog = new QProgressDialog(
        qsTr("Updating library index:"),
        qsTr("Abort"), 0, LibraryBrowser.maxProgress!==0 ? LibraryBrowser.maxProgress : 100, this
    );
    progressDialog.windowTitle = qsTr("Library Browser");
    progressDialog.originalLabelText = progressDialog.labelText;
    progressDialog.windowModality = Qt.WindowModal;
    // show dialog after 2 seconds:
    progressDialog.minimumDuration = 2000;

    if (!LibraryBrowser.syncAll(progressDialog, startUp)) {
        qWarning("LibraryBrowser: sync canceled");
        return;
    }

    progressDialog.reset();
};

/**
 * Initializes the DB link. Called only once.
 */
LibraryBrowser.initDb = function(dropTables) {
    if (isNull(dropTables)) {
        dropTables = false;
    }
    var dbFileName = LibraryBrowser.getDbFileName();
    var db = QSqlDatabase.addDatabase("QSQLITE", Table.connectionName);
    db.setDatabaseName(dbFileName);
    if (!db.open()) {
        var err = db.lastError();
        QMessageBox.warning(null,
                        qsTr("DB error"),
                        qsTr("Plugin LibraryBrowser: cannot connect to DB.\n" +
                             "Driver error: %1\n" +
                             "Database error: %2\n" +
                             "Database file: %3\n" +
                             "Library browser will not be available.")
                             .arg(err.driverText())
                             .arg(err.databaseText())
                             .arg(db.databaseName())
        );
        return false;
    }

    var con = new DbConnection(Table.connectionName);
    con.transaction();
    LocalePeer.createTable(dropTables);
    TagCategoryPeer.createTable(dropTables);
    ItemPeer.createTable(dropTables);
    TagPeer.createTable(dropTables);
    ItemTagPeer.createTable(dropTables);
    con.commit();

    return true;
};

/**
 * Complete synchronization of the DB from all available sources.
 *
 * \param progressDialog QProgressDialog or undefined
 *
 * \return false if process was canceled.
 */
LibraryBrowser.syncAll = function(progressDialog, startUp) {
    var i;

    var force = false;

    // check if source was removed:
    var sourceListDb = ItemPeer.getSourceItems(["id", "name"]);
    var sourceList = LibraryBrowser.getSourceList();
    for (i=0; i<sourceListDb.length; i++) {
        var sourceDb = QDir.fromNativeSeparators(sourceListDb[i].name);
        if (!sourceList.contains(sourceDb)) {
            // source deleted: drop entire DB:
            EAction.handleUserWarning(qsTr("Source removed from part library: %1").arg(sourceListDb[i].name));
            EAction.handleUserWarning(qsTr("Force database update."));
            LibraryBrowser.initDb(true);
            force = true;
            qDebug("Rebuilding DB...");
            break;
        }
    }

    if (startUp && !force) {
        var updateOnStartup = RSettings.getBoolValue("LibraryBrowser/UpdateOnStartup", true);
        if (!updateOnStartup) {
            // setting, not cancelation:
            return true;
        }
    }

    var con = new DbConnection(Table.connectionName);
    con.transaction();

    //qDebug("sync...");
    var totalNum = 0;
    for (i=0; i<sourceList.length; i++) {
        var source = sourceList[i];
        var num = LibraryBrowser.sync(source, undefined, progressDialog);
        // canceled:
        if (isNull(num)) {
            con.rollback();
            return false;
        }

        totalNum+=num;
    }
    //qDebug("sync: ok");

    con.commit();

    //qDebug("synced items: ", totalNum);
    RSettings.setValue("LibraryBrowser/ItemCount", totalNum);

    return true;
};

/**
 * Synchronizes the DB with the disk.
 *
 * \param path Path where to start synchronization. Can be a directory or a
 * single item.
 * \param parentId Parent item ID or 'undefined' for a source.
 * \param progressDialog QProgressDialog or undefined
 * \param levels to sync or undefined (=all levels)
 *
 * \return undefined if process was canceled, otherwise number of items sync'ed.
 */
LibraryBrowser.sync = function(path, parentId, progressDialog, levels) {
    //qDebug("LibraryBrowser.prototype.sync: ", path);
    var fi = new QFileInfo(path);

    if (!LibraryBrowser.increaseProgress(progressDialog)) {
        return undefined;
    }

    var item, itemId;
    if (isNull(parentId)) {
        item = ItemPeer.getItemFromPath(path, parentId, ["id"]);
    }
    else {
        item = ItemPeer.getItemFromPath(fi.fileName(), parentId, ["id"]);
    }

    // item is not in DB: add to DB:
    if (isNull(item) || isNull(item.id)) {
        itemId = LibraryBrowser.addItem(fi, parentId);
    }

    // item is in DB but not in sync: update:
    else {
        itemId = item.id;
        var rdfFi = Rdf.getRdfFileInfo(fi);
        var lastMod = LibraryBrowser.getLastMod(fi);
        var size = LibraryBrowser.getSize(fi);
        var lastModRdf = LibraryBrowser.getLastMod(rdfFi);
        var sizeRdf = LibraryBrowser.getSize(rdfFi);

        item = ItemPeer.doSelectById(itemId, ["last_mod", "last_mod_rdf", "size", "size_rdf"]);

        // update file item (delete item and add again):
        if (fi.isFile() && (lastMod!==item.last_mod || size!==item.size)) {
            LibraryBrowser.deleteItem(fi.fileName(), parentId);
            LibraryBrowser.addItem(fi, parentId);
            return 1;
        }

        // update RDF info only:
        if (lastModRdf!==item.last_mod_rdf || sizeRdf!==item.size_rdf) {
            ItemTagPeer.doDeleteByItemId(itemId);
            var rdf = new Rdf(fi);
            LibraryBrowser.addRdf(rdf, itemId);

            // update last_mod_rdf and size_rdf in item table:
            ItemPeer.doUpdateRdf(itemId, lastModRdf, sizeRdf);
        }
    }

    if (!isNull(levels)) {
        if (levels===0) {
            return 1;
        }
        levels--;
    }

    var totalNum = 1;
    if (fi.isDir()) {
        // disk file listing:
        var filters = new QDir.Filters(QDir.Files, QDir.AllDirs, QDir.NoDotAndDotDot, QDir.Readable);
        var sortFlags = new QDir.SortFlags(QDir.Name, QDir.IgnoreCase);
        var dir = new QDir(path);
        var pats = RFileImporterRegistry.getFilterExtensionPatterns();
        pats.push("*.js");
        pats.push("*.svg");
        var fileNames = dir.entryList(pats, filters, sortFlags);
        fileNames.remove("_META");

        // DB file listing:
        var dbNames = ItemPeer.doSelectNamesByParentId(itemId);

        // find and delete obsolete DB items:
        var obsDbNames = dbNames.difference(fileNames);
        for (var k=0; k<obsDbNames.length; ++k) {
            var dbName = obsDbNames[k];
            LibraryBrowser.deleteItem(dbName, itemId);
        }

        for (var i=0; i<fileNames.length; ++i) {
            var fileName = fileNames[i];

            // ignore auto save and system files:
            if (fileName.startsWith("~") || fileName.startsWith(".")) {
                continue;
            }

            var num = LibraryBrowser.sync(fi.filePath() + QDir.separator + fileName, itemId, progressDialog, levels);
            if (isNull(num)) {
                // canceled:
                return undefined;
            }

            totalNum+=num;
        }
    }

    return totalNum;
};

/**
 * Deletes an obsolete item from the DB.
 *
 * \param name Item name as known from DB.
 * \param parentId Parent ID in DB.
 */
LibraryBrowser.deleteItem = function(name, parentId) {
    qDebug("LibraryBrowser.deleteItem: ", name);
    var item = ItemPeer.doSelectByNameAndParentId(name, parentId, ["id"]);
    ItemPeer.doDeleteById(item.id);
};

/**
 * Adds an item for the given file to the DB.
 *
 * \param fi QFileInfo of file
 * \param parentId ID of parent item in DB or -1 for source items.
 */
LibraryBrowser.addItem = function(fi, parentId) {
    //qDebug("LibraryBrowser.addItem: ", fi.fileName());

    var name;

    // source: name is path:
    if (isNull(parentId)) {
        name = fi.absoluteFilePath();
    }
    else {
        name = fi.fileName();
    }

    var type = fi.isDir() ? Item.Type.Directory : Item.Type.File;
    var rdf = new Rdf(fi);
    var item = new Item(
        parentId,
        name,
        fi.absolutePath(),
        type,
        LibraryBrowser.getLastMod(fi),
        LibraryBrowser.getLastMod(rdf.getFileInfo()),
        LibraryBrowser.getSize(fi),
        LibraryBrowser.getSize(rdf.getFileInfo())
    );
    ItemPeer.doInsert(item);
    var itemId = item.id;
    //qDebug("LibraryBrowser.sync: inserted item: ", itemId);

    // add RDF metadata:
    LibraryBrowser.addRdf(rdf, itemId);

    return itemId;
};

LibraryBrowser.addRdf = function(rdf, itemId) {
    //qDebug("LibraryBrowser.addRdf: ", rdf.getFileName());

    var tags = rdf.getTags();
    for (var i=0; i<tags.length; i++) {
        var tag = tags[i];

        // insert tag:
        TagPeer.doInsert(tag);
        var tagId = tag.id;

        // link item with tag:
        var itemTag = new ItemTag(itemId, tagId);
        ItemTagPeer.doInsert(itemTag);
    }
};

LibraryBrowser.getLastMod = function(fileInfo) {
    if (!fileInfo.isFile()) {
        return "NO_RDF";
    }

    return new QDateTime(fileInfo.lastModified()).toString("yyyyMMddhhmmss");
};

LibraryBrowser.getSize = function(fileInfo) {
    if (!fileInfo.isFile()) {
        return 0;
    }

    return fileInfo.size();
};

/**
 * Increases progress of the given progress dialog and returns false if user
 * pressed cancel.
 *
 * \param progressDialog QProgressDialog or undefined
 */
LibraryBrowser.increaseProgress = function(progressDialog) {
    if (isNull(progressDialog)) {
        return true;
    }

    if (isNull(progressDialog.counter)) {
        progressDialog.counter = 0;
    }

//    qDebug("LibraryBrowser.maxProgress: ", LibraryBrowser.maxProgress);
//    qDebug("progressDialog.value: ", progressDialog.value);
//    qDebug("progressDialog.maximum: ", progressDialog.maximum);

    progressDialog.labelText = progressDialog.originalLabelText + " [" + progressDialog.counter + "]";
    progressDialog.value++;
    progressDialog.counter++;
    //if (LibraryBrowser.maxProgress===0) {
        if (progressDialog.value>progressDialog.maximum-5000) {
            var p = progressDialog.value / progressDialog.maximum;
            progressDialog.maximum+=2500;
            progressDialog.value = progressDialog.maximum * p;
        }
    //}

    if (progressDialog.wasCanceled) {
        return false;
    }

    return true;
};

/**
 * Creates the context menu for a directory item.
 */
/*
LibraryBrowser.createDirectoryContextMenu = function(itemView, filePath / *dirTree, index* /) {
    var flags;

    //var model = dirTree.model();
    //var file = model.filePath(index);
    var menu = new QMenu(itemView);
    menu.objectName = "DirectoryContextMenu";

    // show directory in native file browser
    var fileBrowser;
    if (RS.getSystemId()==="win") {
        fileBrowser = "Explorer";
    }
    else if (RS.getSystemId()==="osx") {
        fileBrowser = "Finder";
    }
    else {
        fileBrowser = qsTr("File Browser");
    }

    var openAct = menu.addAction(qsTr("&Show in %1...").arg(fileBrowser));
    openAct.icon = new QIcon(LibraryBrowser.includeBasePath + "/Open.svg");
    openAct.triggered.connect(function() {
        QDesktopServices.openUrl(QUrl.fromLocalFile(filePath));
    });

    // add to / remove from favorites
    var icon = LibraryBrowser.includeBasePath + "/Favorite.svg";
    if (Favorites.isFavorite(filePath)) {
        var action = menu.addAction(new QIcon(icon),
                qsTr("&Remove from Favorites"));
        action.triggered.connect(this, function() {
            Favorites.remove(filePath);

            // update favorite icon:
            var model = itemView.model();
            var i = itemView.currentIndex();
            model.setIconProvider(new FileIconProvider());
            itemView.update(i);
        });
    } else {
        var action = menu.addAction(new QIcon(icon), qsTr("&Add to Favorites"));
        action.triggered.connect(LibraryBrowser, function() {
            Favorites.add(filePath, LibraryBrowser.getCurrentSourcePath());

            // update favorite icon:
            var model = itemView.model();
            var i = itemView.currentIndex();
            model.setIconProvider(new FileIconProvider());
            itemView.update(i);
        });
    }


    // regenerate icons
    //var action = menu.addAction(qsTr("&Regenerate Icons"));
    //action.triggered.connect(function() {
    //    var selectionModel = dirTree.selectionModel();
        // flag "QItemSelectionModel.SelectCurrent" doesn't work here,
        // since 'selected' will be empty in directoryChanged()
//        flags = new QItemSelectionModel.SelectionFlags(
//                QItemSelectionModel.Deselect);
//        selectionModel.select(index, flags);
        //LibraryBrowser.regenerateIcons = true;
//        flags = new QItemSelectionModel.SelectionFlags(
//                QItemSelectionModel.Select);
//        selectionModel.select(index, flags);
        //LibraryBrowser.regenerateIcons = false;
    //});
    return menu;
};
*/

/**
 * Inserts the current item of the given view into the current drawing.
 */
LibraryBrowser.insertItem = function(itemView) {
    var index = itemView.currentIndex();
    if (!index.isValid()) {
        return;
    }
    var model = itemView.model();
    var file = model.data(index, Qt.UserRole);
    var action;
    if (InsertScriptItem.isScriptFile(file)) {
        action = RGuiAction.getByScriptFile(
                    "scripts/Block/InsertScriptItem/InsertScriptItem.js");
    } else {
        action = RGuiAction.getByScriptFile(
                    "scripts/Block/InsertBlockItem/InsertBlockItem.js");
    }
    action.setData(QUrl.fromLocalFile(file));
    action.slotTrigger();
};

/**
 * Creates the context menu for a file item.
 */
LibraryBrowser.createItemContextMenu = function(itemView, filePath, itemId, index) {
    var icon, action;

    var menu = new QMenu(itemView);
    menu.objectName = "ContextMenu";
    if (isNull(filePath)) {
        return menu;
    }

    var fi = new QFileInfo(filePath);

    var readOnly = !fi.isWritable();

    // insert item:
    if (fi.isFile()) {
        action = menu.addAction(qsTr("&Insert"));
        action.triggered.connect(function() {
            LibraryBrowser.insertItem(itemView);
        });
    }

    // open file for editing (script, svg, drawing):
    if (fi.isFile()) {
        if (InsertScriptItem.isScriptFile(filePath)) {
            // edit script
            action = menu.addAction(qsTr("&Edit Script File..."));
            action.icon = new QIcon(LibraryBrowser.includeBasePath + "/EditDrawing.svg");
            action.triggered.connect(LibraryBrowser, function() {
                                          QDesktopServices.openUrl(QUrl.fromLocalFile(filePath));
                                      });
        } else {
            if (fi.suffix().toLowerCase() === "svg") {
                // open SVG file
                action = menu.addAction(qsTr("Open &SVG File..."));
                action.icon = new QIcon(LibraryBrowser.includeBasePath + "/Open.svg");
                action.triggered.connect(LibraryBrowser, function() {
                                              QDesktopServices.openUrl(QUrl.fromLocalFile(filePath));
                                          });
            } else {
                // edit / open drawing
                var text = "";
                if (readOnly) {
                    text = qsTr("&Open...");
                    icon = LibraryBrowser.includeBasePath + "/Open.svg";
                } else {
                    text = qsTr("&Edit...");
                    icon = LibraryBrowser.includeBasePath + "/EditDrawing.svg";
                }
                action = new RGuiAction(text, menu);
                action.setData(filePath);
                action.setRequiresDocument(false);
                action.setScriptFile(LibraryBrowser.includeBasePath + "/../../../scripts/File/OpenFile/OpenFile.js");
                action.setIcon(icon);
                action.addToMenu(menu);
            }
        }

        menu.addSeparator();
    }

    // show dir item in native file browser:
    else {
        var fileBrowser;
        if (RS.getSystemId()==="win") {
            fileBrowser = "Explorer";
        }
        else if (RS.getSystemId()==="osx") {
            fileBrowser = "Finder";
        }
        else {
            fileBrowser = qsTr("File Browser");
        }
        action = menu.addAction(qsTr("&Show in %1...").arg(fileBrowser));
        action.icon = new QIcon(LibraryBrowser.includeBasePath + "/Open.svg");
        action.triggered.connect(function() {
            QDesktopServices.openUrl(QUrl.fromLocalFile(filePath));
        });
    }

    // rename:
//    var renameAct = menu.addAction(qsTr("&Rename..."));
//    if (readOnly) {
//        renameAct.enabled = false;
//    }
//    renameAct.triggered.connect(LibraryBrowser, function() {
//        itemView.edit(itemView.currentIndex());
//    });

    // edit meta data
//    var editAct = EditMetaData.initMenu(LibraryBrowser.includeBasePath, menu, id, readOnly);
//    editAct.triggered.connect(LibraryBrowser, function() {
//        var id = editAct.data();
//        LibraryBrowser.updateQsItem(itemView, id);
//    });

//    menu.addSeparator();

    // add to / remove from favorites:
    icon = LibraryBrowser.includeBasePath + "/Favorite.svg";
    if (Favorites.isFavorite(filePath)) {
        action = menu.addAction(new QIcon(icon), qsTr("&Remove from Favorites"));
        action.triggered.connect(this, function() {
            Favorites.remove(filePath);

            if (isOfType(itemView, RListView)) {
                if (itemView.objectName==="FavoritesListView") {
                    // if the context menu was used in the favorites view,
                    // update view:
                    LibraryBrowser.updateFavoritesTab();
                }
                else {
                    // update item only:
                    LibraryBrowser.updateQsItem(itemView, itemId);
                }
            }
            LibraryBrowser.updateTreeViewIcons();

        });
    } else {
        action = menu.addAction(new QIcon(icon),
                qsTr("&Add to Favorites"));
        action.triggered.connect(LibraryBrowser, function() {
            Favorites.add(filePath, LibraryBrowser.currentSourceName);

            if (isOfType(itemView, RListView)) {
                LibraryBrowser.updateQsItem(itemView, itemId);
            }
            else {
                LibraryBrowser.updateTreeViewIcons();
            }
        });
    }

//    menu.addSeparator();

    // delete file
//    var deleteAct = menu.addAction(qsTr("&Delete..."));
//    if (readOnly) {
//        deleteAct.enabled = false;
//    }
//    deleteAct.triggered.connect(this, function() {
//        var flags = new QMessageBox.StandardButtons(QMessageBox.Yes
//                | QMessageBox.No);
//        var ret = QMessageBox.question(itemView, qsTr("Delete File"), qsTr(
//                "Do you want to delete the file\n\n%1\n\nfrom the hard disk?")
//                .arg(filePath), flags, QMessageBox.No);
//        if (ret == QMessageBox.No) {
//            return;
//        }
//        ItemPeer.remove(id, filePath, itemView);
//    });


    if (fi.isFile()) {
        action = menu.addAction(qsTr("&Regenerate Icon"));
        action.triggered.connect(
            function() {
                LibraryBrowser.regenerateIcons = true;
                LibraryBrowser.updateQsItem(itemView, itemId);
                LibraryBrowser.regenerateIcons = false;
            });
    }

    else {
        // regenerate icons
        action = menu.addAction(qsTr("&Regenerate Icons"));
        action.triggered.connect(
            function() {
                var selectionModel = itemView.selectionModel();
                // flag "QItemSelectionModel.SelectCurrent" doesn't work here,
                // since 'selected' will be empty in directoryChanged()
                var flags = new QItemSelectionModel.SelectionFlags(QItemSelectionModel.Deselect);
                selectionModel.select(index, flags);
                LibraryBrowser.regenerateIcons = true;
                flags = new QItemSelectionModel.SelectionFlags(QItemSelectionModel.Select);
                selectionModel.select(index, flags);
                LibraryBrowser.regenerateIcons = false;
            });
    }

    return menu;
};

/**
 * Updates the icons in the directory tree of the file system tab to make sure
 * favorite folders are marked as such.
 */
LibraryBrowser.updateTreeViewIcons = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var dirTree = formWidget.findChild("DirectoryTree");
    var model = dirTree.model();
    var i = dirTree.currentIndex();
    model.setIconProvider(new FileIconProvider());
    dirTree.update(i);
};

/**
 * Called when the current tab changes.
 */
LibraryBrowser.tabChanged = function(index) {

    if (index===0) {
        LibraryBrowser.directoryChanged();
        LibraryBrowser.updateFileSystemTab();
    }

    // favorites tab was activated:
    else if (index===1) {
        LibraryBrowser.updateTagsTab();
        LibraryBrowser.updateTagsView();
    }

    // tags tab was activated:
    else if (index===2) {
        LibraryBrowser.updateFavoritesTab();
    }

    RSettings.setValue("LibraryBrowser/Tab", index);
};

/**
 * Plugin initialization. This is very fast as the real initialization
 * happens if the library browser dock widget is shown for the first time.
 */
/*
*/

/*
LibraryBrowser.postInit = function(basePath) {
    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("LibraryBrowserDock");
    var formWidget = dock.findChild("LibraryBrowserForm");
    var tabWidget = formWidget.findChild("TabWidget");

    // tab changed:
    tabWidget["currentChanged(int)"].connect(LibraryBrowser, "tabChanged");
    //LibraryBrowser.tabChanged(tabWidget.currentIndex);

    // the library browser only initializes itself if it is shown for the
    // first time. this can be during startup or later:
    dock.shown.connect(LibraryBrowser, "showFirstTime");

    if (dock.visible) {
        //debugger;
        LibraryBrowser.showFirstTime();
    }
};
*/

LibraryBrowser.updateCurrentTab = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("LibraryBrowserDock");
    var formWidget = dock.findChild("LibraryBrowserForm");
    var tabWidget = formWidget.findChild("TabWidget");
    LibraryBrowser.tabChanged(tabWidget.currentIndex);
};

LibraryBrowser.showDirectory = function(dirName) {
    if (!new QFileInfo(dirName).isAbsolute()) {
        dirName = QDir.currentPath() + QDir.separator + dirName;
    }

    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var dirTree = formWidget.findChild("DirectoryTree");
    var listView = formWidget.findChild("FileSystemListView");
    var tabWidget = formWidget.findChild("TabWidget");
    var sourceCombo = formWidget.findChild("SourceCombo");

    tabWidget.currentIndex = 0;

    // select source:
    for (var i=0; i<sourceCombo.count; i++) {
        var src = sourceCombo.itemData(i);
        if (dirName.startsWith(src)) {
            sourceCombo.currentIndex = i;
            break;
        }
    }

    var dirModel = dirTree.model();
    if (!isNull(dirModel)) {
        var treeIndex = dirModel.pathIndex(dirName);
        LibraryBrowser.deselectAllDirs();
        var selectionModel = dirTree.selectionModel();
        var flags = new QItemSelectionModel.SelectionFlags(QItemSelectionModel.Select);
        var idxList = LibraryBrowser.getSelectedIndexes(selectionModel);
        selectionModel.select(treeIndex, flags);
        while (treeIndex.isValid()) {
            dirTree.setExpanded(treeIndex, true);
            treeIndex = treeIndex.parent();
            QCoreApplication.processEvents();
        }
        treeIndex = dirModel.pathIndex(dirName);
        dirTree.scrollTo(treeIndex);
    }
    listView.scrollToTop();
};

/**
 * Heper function. Deselects everything in directory tree view.
 */
LibraryBrowser.deselectAllDirs = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var formWidget = appWin.findChild("LibraryBrowserForm");
    var dirTree = formWidget.findChild("DirectoryTree");

    var selectionModel = dirTree.selectionModel();
    var flags = new QItemSelectionModel.SelectionFlags(QItemSelectionModel.Deselect);
    var idxList = LibraryBrowser.getSelectedIndexes(selectionModel);
    for (var i=0; i<idxList.length; i++) {
        selectionModel.select(idxList[i], flags);
    }
};


LibraryBrowser.showFirstTime = function() {
    var appWin = RMainWindowQt.getMainWindow();
    if (isNull(appWin.property("LibraryBrowser/FirstShow"))) {
        var dock = appWin.findChild("LibraryBrowserDock");
        var formWidget = dock.findChild("LibraryBrowserForm");
        var tabWidget = formWidget.findChild("TabWidget");

        // tab changed:
        tabWidget["currentChanged(int)"].connect(LibraryBrowser, "tabChanged");

        if (LibraryBrowser.initDb()) {
            LibraryBrowser.syncWithProgress(true);
            LibraryBrowser.initFileSystemTab();
            LibraryBrowser.initFavoritesTab();
            LibraryBrowser.initTagsTab();
            tabWidget.currentIndex = RSettings.getValue("LibraryBrowser/Tab", 0);
            LibraryBrowser.updateCurrentTab();
        }
        //LibraryBrowser.firstShow = false;
        appWin.setProperty("LibraryBrowser/FirstShow", true);

        var initialPath = RSettings.getStringValue("LibraryBrowser/Path", "");
        LibraryBrowser.showDirectory(initialPath);
    }
};
