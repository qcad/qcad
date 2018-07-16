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

/**
 * \defgroup ecma_window Window Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * window tools.
 */
include("scripts/EAction.js");

function MenuData(d) {
    this.data = d;
}

MenuData.prototype.triggered = function() {
    var mdiArea = EAction.getMdiArea();
    this.data.show();
    mdiArea.setActiveSubWindow(this.data);
};


/**
 * \class Window
 * \brief Base class for all window tools.
 * \ingroup ecma_window
 */
function Window(guiAction) {
    EAction.call(this, guiAction);
}

Window.prototype = new EAction();
Window.includeBasePath = includeBasePath;

Window.getMenu = function() {
    var i, action;

    var menu = EAction.getMenu(Window.getTitle(), "WindowMenu", function(menu) {
        menu.aboutToShow.connect(function() {
            var mdiArea = EAction.getMdiArea();
            var windows = mdiArea.subWindowList();

            var actions = menu.actions();
            for (i = 0; i < actions.length; ++i) {
                action = actions[i];
                if (action.objectName === "MdiChild") {
                    menu.removeAction(action);
                }
            }

            var separator = new RGuiAction("", menu);
            separator.setSeparator(true);
            separator.objectName = "MdiChild";
            separator.addToMenu(menu);

            for (i = 0; i < windows.length; ++i) {
                var window = windows[i];
                var file = window.getDocument().getFileName();
                var modified = window.getDocument().isModified();
                var text = new QFileInfo(file).fileName();
                if (text === "") {
                    text = stripDirtyFlag(window.windowTitle);
                }
                if (modified) {
                    text += " *";
                }
                action = menu.addAction(text);
                action.checkable = true;
                if (!isNull(mdiArea.activeSubWindow()) && window.getObjectId() == mdiArea.activeSubWindow().getObjectId()) {
                    action.checked = true;
                } else {
                    action.checked = false;
                }
                action.objectName = "MdiChild";
                var menuData = new MenuData(windows[i]);
                action.triggered.connect(menuData, "triggered");
            }
        });
    });
    menu.setProperty("scriptFile", Window.includeBasePath + "/Window.js");
    return menu;
};

Window.getToolBar = function() {
    var tb = EAction.getToolBar(Window.getTitle(), "WindowToolBar");
    tb.visible = false;
    return tb;
};

Window.getTitle = function() {
    return qsTr("&Window");
};

Window.prototype.getTitle = function() {
    return Window.getTitle();
};

Window.init = function() {
    Window.getMenu();
    Window.getToolBar();

    // make sure there's an action:
    var appWin = EAction.getMainWindow();
    var action = new RGuiAction(qsTr("Window Tools"), appWin);
    action.setScriptFile(Window.includeBasePath + "/Window.js");
    action.setWidgetNames([]);
};
