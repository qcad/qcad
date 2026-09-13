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

function TabBar() {
}

TabBar.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("Tab Bar") ];
};

TabBar.applyPreferences = function(doc, mdiChild) {
    var appWin = RMainWindowQt.getMainWindow();
    var mdiArea = appWin.getMdiArea();
    if (isNull(mdiArea)) {
        return;
    }

    if (RSettings.getBoolValue("TabBar/ShowTabBar", true)===false) {
        mdiArea.viewMode = QMdiArea.SubWindowView;
        if (!isNull(mdiChild)) {
            mdiChild.showMaximized();
        }
    }
    else {
        mdiArea.viewMode = QMdiArea.TabbedView;
        TabBar.initTabBar();
    }
};

TabBar.init = function(basePath) {
    var appWin = RMainWindowQt.getMainWindow();
    var mdiArea = appWin.getMdiArea();
    if (isNull(mdiArea)) {
        return;
    }

    mdiArea.documentMode = true;
    if (RSettings.getBoolValue("TabBar/ShowTabBar", true)===false) {
        mdiArea.viewMode = QMdiArea.SubWindowView;
    }
    else {
        mdiArea.viewMode = QMdiArea.TabbedView;
        TabBar.initTabBar();
    }
};

/**
 * \return Path of the icon to use for the close button of document tabs,
 * ready to be used in a Qt style sheet url(), or undefined if no such icon
 * can be found.
 *
 * Themes can override the icon by providing icons/CloseTab.svg (affects the
 * tab close buttons only) or icons/CloseFile.svg (shared with the
 * File > Close action) in the theme directory. Dark themes are served the
 * -inverse variant if the theme provides one.
 */
TabBar.getCloseIconPath = function() {
    // theme specific icon for the tab close button only (not shipped by
    // default, purely an override hook for themes):
    var path = autoIconPath("scripts/Widgets/TabBar/CloseTab.svg");
    if (isNull(path) || path.length===0) {
        // default: same icon as the File > Close action:
        path = autoIconPath("scripts/File/CloseFile/CloseFile.svg");
    }
    if (isNull(path) || path.length===0) {
        return undefined;
    }

    // style sheet URLs are always forward slash separated:
    path = path.replace(/\\/g, "/");

    if (path.startsWith(":")) {
        // resource path: autoPath() yields ":scripts/...", url() wants ":/scripts/...":
        if (!path.startsWith(":/")) {
            path = ":/" + path.substring(1);
        }
    }
    else {
        // relative paths in style sheets are resolved against the working
        // directory, which is not necessarily the application directory:
        path = new QFileInfo(path).absoluteFilePath();
    }

    return path;
};

/**
 * Replaces the generic close indicator Qt draws for closable tabs with the
 * QCAD close icon (see TabBar.getCloseIconPath).
 */
TabBar.updateCloseIcon = function(tabBar) {
    var path = TabBar.getCloseIconPath();
    if (isNull(path)) {
        tabBar.styleSheet = "";
        return;
    }

    // only the close-button subcontrol is styled, so tabs themselves are
    // still rendered by the active style:
    tabBar.styleSheet =
        "QTabBar::close-button { image: url(\"" + path + "\"); width: 16px; height: 16px; }";
};

TabBar.initTabBar = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var tabBar = appWin.getTabBar();
    if (isNull(tabBar)) {
        return;
    }
    tabBar.elideMode = Qt.ElideRight;
    tabBar.tabsClosable = true;
    tabBar.usesScrollButtons = true;
    tabBar.contextMenuPolicy = Qt.NoContextMenu;
    tabBar.objectName = "DocumentTabBar";
    TabBar.updateCloseIcon(tabBar);
    // somewhat buggy:
    //tabBar.movable = true;

    if (RSettings.getQtVersionString().startsWith("4.7.")) {
        // starting with Qt 4.8, this is no longer necessary:
        tabBar.tabCloseRequested.connect(function(tabIndex) {
            tabBar.setCurrentIndex(tabIndex);
            var closeEvent = new RCloseCurrentEvent();
            QCoreApplication.postEvent(appWin, closeEvent);
        });
    }

    if (RSettings.getBoolValue("TabBar/ShowAddTabButton", false)) {
        var mdiArea = appWin.getMdiArea();
        if (!isNull(mdiArea)) {
            var button = mdiArea.getAddTabButton();
            button.styleSheet = "border:0px";

            var fileNewAction = RGuiAction.getByScriptFile("scripts/File/NewFile/NewFile.js");
            //action.icon = new QIcon(autoPath("scripts/Widgets/TabBar/AddTab.svg"));
            //button.icon = new QIcon(autoPath("scripts/Widgets/TabBar/AddTab.svg"));

            var action = new RGuiAction(fileNewAction.text, RMainWindowQt.getMainWindow());
            action.setProperty("Configurable", false);
            action.setRequiresDocument(false);
            action.setScriptFile(fileNewAction.getScriptFile(), true);
            action.setIcon(autoPath("scripts/Widgets/TabBar/AddTab.svg"));
            action.setNoState();

            button.setDefaultAction(action);
        }
    }
};
