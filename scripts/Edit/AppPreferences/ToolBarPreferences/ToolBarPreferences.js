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

include("../../../EAction.js");
include("../../../WidgetFactory.js");

function ToolBarPreferences(guiAction) {
    EAction.call(this, guiAction);
}

ToolBarPreferences.prototype = new EAction();

ToolBarPreferences.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("Toolbars")];
};

/**
 * \return True if the current theme comes with its own application style
 * plugin (e.g. Modern), which implements the button spacing preference.
 */
ToolBarPreferences.hasStylePlugin = function() {
    var theme = RSettings.getValue("Theme/ThemeName", undefined);
    return !isNull(theme) && RPluginLoader.hasPlugin(theme.toUpperCase() + "STYLE");
};

ToolBarPreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    // button spacing (ToolBar/ButtonSpacing, percent) is implemented by the
    // theme's style plugin, other styles use their fixed spacing:
    if (!ToolBarPreferences.hasStylePlugin()) {
        var widgets = ["labelButtonSpacing", "ButtonSpacing"];
        for (var i=0; i<widgets.length; i++) {
            var w = pageWidget.findChild(widgets[i]);
            if (!isNull(w)) {
                w.visible = false;
            }
        }
    }
};

ToolBarPreferences.applyPreferences = function(doc) {
    var appWin = EAction.getMainWindow();
    var children = appWin.children();
    var s = RSettings.getIntValue("ToolBar/IconSize", 32);
    for (var i=0; i<children.length; i++) {
        var c = children[i];
        if (isOfType(c, QToolBar)) {
            c.iconSize = new QSize(s,s);
        }
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    var ftb = EAction.getMainWindow().findChild("FileToolBar");
    if (!isNull(ftb)) {
        optionsToolBar.setFixedHeight(ftb.sizeHint.height());
    }
};
