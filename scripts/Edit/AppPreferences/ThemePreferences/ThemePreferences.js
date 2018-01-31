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

include("../../EAction.js");
include("../../WidgetFactory.js");

function ThemePreferences(guiAction) {
    EAction.call(this, guiAction);
}

ThemePreferences.prototype = new EAction();

ThemePreferences.getPreferencesCategory = function() {
    return [qsTr("General"), qsTr("Theme")];
};

ThemePreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var cb = pageWidget.findChild("ThemeName");
    cb.addItem("Default");

    var d = new QDir("themes");
    var fs = new QDir.Filters(QDir.NoDotAndDotDot, QDir.Readable, QDir.Dirs, QDir.Executable);
    var sf = new QDir.SortFlags(QDir.Name);
    var themes = d.entryList([], fs, sf);
    cb.addItems(themes);
};

ThemePreferences.applyPreferences = function(doc, mdiChild) {
    // TODO: does not work for all theme related settings:
    //applyTheme();
};
