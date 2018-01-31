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

include("scripts/Widgets/ViewportWidget/ViewportWidget.js");

function ViewportSettings() {
}

ViewportSettings.getPreferencesCategory = function(appPreferences) {
    if (appPreferences) {
        return [ qsTr("Defaults for New Drawings"), qsTr("Layout - Viewports") ];
    }
    return [ qsTr("Layout"), qsTr("Viewports") ];
};

ViewportSettings.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);

    var vpList = widgets["ViewportList"];
    var previewWidget = widgets["PreviewWidget"];

    vpList.clear();
    var dir = new QDir(ViewportWidget.templateDir);
    var filters = new QDir.Filters(QDir.Files, QDir.NoDotAndDotDot, QDir.Readable);
    var sortFlags = new QDir.SortFlags(QDir.Name);
    var eil = dir.entryInfoList(new Array("*.ui"), filters, sortFlags);
    var defaultRow = -1;
    for ( var j = 0; j < eil.length; ++j) {
        var fi = eil[j];
        var w = WidgetFactory.createWidget(ViewportWidget.templateDir, fi.fileName());
        var lwi = new QListWidgetItem(w.windowTitle, vpList, QListWidgetItem.Type.valueOf());
        lwi.setData(Qt.UserRole, fi.fileName());
        // default viewport setting
        if (fi.fileName() == "00_Single.ui") {
            defaultRow = j;
        }
        w.destroy();
    }
    if (defaultRow != -1) {
        vpList.currentRow = defaultRow;
        ViewportSettings.updatePreview(previewWidget, vpList.item(vpList.currentRow));
    }

    vpList["currentItemChanged(QListWidgetItem*,QListWidgetItem*)"].connect(
        this, function(current, previous) {
            ViewportSettings.updatePreview(previewWidget, current);
        });
};

ViewportSettings.updatePreview = function(previewWidget, item) {
    var chs = previewWidget.children();
    for (i = 0; i < chs.length; ++i) {
        chs[i].destroy();
    }
    var fileName = item.data(Qt.UserRole);
    if (fileName == undefined) {
        return;
    }
    var w = WidgetFactory.createWidget(ViewportWidget.templateDir, fileName);
    w.setParent(previewWidget);
    w.enabled = false;
    w.setFixedSize(new QSize(320, 240));
    w.show();
};

ViewportSettings.applyPreferences = function(doc) {
    if (typeof(doc) == "undefined") {
        // application wide settings: nothing to do
        return;
    }
    
    var mdiChild = EAction.getMdiChild();
    // doc preferences
    //qDebug("ViewportSettings.js:", "applyPreferences(): appPreferences: doc:",doc);
//    var chs = mdiChild.children();
//    for ( var i = 0; i < chs.length; ++i) {
//        var child = chs[i];
//        child.destroy();
//    }
    
    var uiFileName = doc.getVariable("Viewport/ViewportList.data");
    if (uiFileName == undefined) {
        // fall back to application wide settings
        uiFileName = RSettings.getStringValue("Viewport/ViewportList.data", "00_Single.ui");
    }
    
    ViewportWidget.initMdiChild(mdiChild, uiFileName);
    
    var viewports = ViewportWidget.getViewports(mdiChild, mdiChild.getDocumentInterface());
    mdiChild.viewports = viewports;
    for ( var i = 0; i < viewports.length; ++i) {
        viewports[i].init();
        viewports[i].initEventHandler();
    }
};
