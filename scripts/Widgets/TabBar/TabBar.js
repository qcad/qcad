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
