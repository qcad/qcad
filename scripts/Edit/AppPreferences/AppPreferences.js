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

include("../AbstractPreferences.js");

/**
 * \class AppPreferences
 * \brief Shows the application preferences dialog.
 * \ingroup ecma_edit
 */
function AppPreferences(guiAction, initialClassName) {
    AbstractPreferences.call(this, guiAction, true, initialClassName);
}

AppPreferences.prototype = new AbstractPreferences();

AppPreferences.init = function(basePath) {
    var action;
    var gotPrefMenu = false;

    // OS X also has a preferences menu under the application menu
    // (only if OS X is configured to use the same language as the application):
    if (RS.getSystemId() === "osx") {
        var sysLang = QLocale.system().name();
        if (sysLang.length>=2) {
            sysLang = sysLang.substring(0,2);
        }
        var appLang = RSettings.getLocale();
        if (appLang.length>=2) {
            appLang = appLang.substring(0,2);
        }

        if (sysLang===appLang) {
            action = new RGuiAction("Preferences", RMainWindowQt.getMainWindow());
            action.menuRole = QAction.PreferencesRole;
            // preferences menu under Mac OS X has no icon:
            action.disableIcon();
            action.setDefaultShortcut(new QKeySequence(QKeySequence.Preferences));
            action.setRequiresDocument(false);
            action.setScriptFile(basePath + "/AppPreferences.js");
            action.setNoState();
            action.setGroupSortOrder(0);
            action.setSortOrder(0);
            action.setWidgetNames(["EditMenu"]);
            gotPrefMenu = true;
        }
    }

    action = new RGuiAction(qsTr("Application &Preferences"), RMainWindowQt.getMainWindow());
    if (RS.getSystemId() === "osx" && !gotPrefMenu) {
        action.setDefaultShortcut(new QKeySequence(QKeySequence.Preferences));
    }
    else {
        action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.Key_Comma));
    }
    action.setDefaultCommands(["preferences"]);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/AppPreferences.js");
    action.setIcon(basePath + "/AppPreferences.svg");
    action.setNoState();
    action.setGroupSortOrder(2800);
    action.setSortOrder(200);
    action.setWidgetNames(["EditMenu"]);
};
