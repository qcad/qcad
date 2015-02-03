/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

StylePreferences.stylePath = "scripts/Edit/AppPreferences/StylePreferences/Predefined";

function StylePreferences() {
}

StylePreferences.getPreferencesCategory = function() {
    return [ qsTr("Layout"), qsTr("Styles") ];
};

StylePreferences.init = function(basePath) {
    StylePreferences.update();
};

StylePreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);
    var styleNames = StylePreferences.getStyleNames();
    var styleCombo = widgets["StyleName"];
    for ( var i = 0; i < styleNames.length; ++i) {
        var style = styleNames[i];
        styleCombo.addItem(style);
    }    
};

StylePreferences.applyPreferences = function() {
    StylePreferences.update();
};

StylePreferences.update = function() {
    var styleName = RSettings.getStringValue("Style/StyleName", qsTr("None"));
    if (styleName != qsTr("None")) {
        StylePreferences.loadByName(styleName);
        return;
    }
    var appWin = EAction.getMainWindow();
    appWin.styleSheet = "";
};

StylePreferences.load = function(file) {
    var cssFile = new QFile(file);
    if (!cssFile.exists()) {
        // qDebug(" No such file:", cssFile.fileName());
        return;
    }

    var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
    if (cssFile.open(flags)) {
        var textStream = new QTextStream(cssFile);
        var appWin = EAction.getMainWindow();
        var str = textStream.readAll();
        appWin.styleSheet = str;
        qDebug("    Style Sheets loaded:", cssFile.fileName());
        cssFile.close();
    } else {
        qDebug("    Cannot open file:", cssFile.fileName());
    }
};

StylePreferences.loadByName = function(styleName) {
    qDebug("    Loading style: ", styleName);
    if (styleName == qsTr("None")) {
        var appWin = EAction.getMainWindow();
        appWin.styleSheet = "";
        return;
    }
    var fi = new QFileInfo(RSettings.getQSettings().fileName());
    var cssFile = StylePreferences.stylePath + QDir.separator + styleName + ".css";
    StylePreferences.load(cssFile);
};

StylePreferences.loadCustomStyles = function() {
    var fi = new QFileInfo(RSettings.getQSettings().fileName());
    var path = fi.absoluteDir().absolutePath();
    var cssFile = path + QDir.separator + "custom.css";
    StylePreferences.load(cssFile);
};

StylePreferences.getStyleNames = function() {
    var dir = new QDir(StylePreferences.stylePath);
    var fileFilter = new QDir.Filters(QDir.Readable, QDir.Files);
    var sortFlags = new QDir.SortFlags(QDir.Name);
    var files = dir.entryInfoList( [ "*.css" ], fileFilter, sortFlags);
    var names = new Array(qsTr("None"));
    for ( var i = 0; i < files.length; ++i) {
        var fi = files[i];
        names.push(fi.completeBaseName());
    }
    return names;
};
