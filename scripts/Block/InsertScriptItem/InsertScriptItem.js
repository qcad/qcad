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

include("scripts/Block/Block.js");
include("../InsertBlockItem/InsertBlockItem.js");

/**
 * \class InsertScriptItem
 * \brief Called when a script is inserted from the part library.
 * \ingroup ecma_block
 */
function InsertScriptItem(guiAction) {
    InsertBlockItem.call(this, guiAction);

    if (!isNull(guiAction)) {
        this.setUiOptions("../InsertBlockItem/InsertBlockItem.ui");
    }

    this.diItem = undefined;
    this.docItem = undefined;
    this.file = undefined;
    //this.offset = undefined;
}

InsertScriptItem.prototype = new InsertBlockItem();

InsertScriptItem.prototype.beginEvent = function() {
    var ms = new RMemoryStorage();
    var si = createSpatialIndex();
    this.docItem = new RDocument(ms, si);
    this.diItem = new RDocumentInterface(this.docItem);
    // this document does never update the layer list, block list, etc:
    this.diItem.setNotifyListeners(false);
    
    Block.prototype.beginEvent.call(this);

    if (isNull(this.url) || !this.url.isLocalFile()) {
        this.terminate();
        return;
    }

    this.file = this.url.toLocalFile();
    include(this.file);
    
    InsertScriptItem.evalInit(this.file);

    this.generate();

    this.setState(InsertBlockItem.State.SettingPosition);
};

InsertScriptItem.prototype.finishEvent = function() {
    var dock = objectFromPath("MainWindow::"
            + InsertScriptItem.getObjectName(this.file));
    if (!isNull(dock)) {
        dock.hide();
        dock.destroy();
    }
    InsertBlockItem.prototype.finishEvent.call(this);
};

/**
 * Generates the script item into a temporary document for insertion.
 */
InsertScriptItem.prototype.generate = function() {
    this.diItem.clear();
    var operation = InsertScriptItem.evalGenerate(this.diItem, this.file);
    if (!isNull(operation)) {
        this.diItem.applyOperation(operation);
    }
};

InsertScriptItem.isScriptFile = function(file) {
    return new QFileInfo(file).suffix().toLowerCase() == "js";
};

InsertScriptItem.hasUiFile = function(file) {
    var uiFile = InsertScriptItem.getUiFilePath(file);
    return new QFileInfo(uiFile).isFile();
};

InsertScriptItem.getUiFilePath = function(file) {
    var fi = new QFileInfo(file);
    return fi.absolutePath() + QDir.separator + fi.completeBaseName() + ".ui";
};

InsertScriptItem.getWidget = function(file) {
    return objectFromPath("MainWindow::" + InsertScriptItem.getObjectName(file)).widget();
};

InsertScriptItem.getObjectName = function(file) {
    var str = "";
    var sa = file.split(QDir.separator);
    for ( var i = 0; i < sa.length; ++i) {
        var s = sa[i];
        if (s.length === 0) {
            continue;
        }
        var first = s.slice(0, 1).toUpperCase();
        var rest = s.slice(1, s.length);
        str += first + rest;
    }
    var re = /\.js$/;
    return str.replace(re, "");
};

InsertScriptItem.getFileTitle = function(file) {
    return new QFileInfo(file).completeBaseName();
};

/**
 * Called when a script item is about to be inserted to initialize the
 * user interface component that displays script parameters and call
 * the script init function.
 */
InsertScriptItem.evalInit = function(file) {
    var formWidget;
    var className = new QFileInfo(file).completeBaseName();
    
    if (InsertScriptItem.hasUiFile(file)) {
        var dock = objectFromPath("MainWindow::" + InsertScriptItem.getObjectName(file));
        if (isNull(dock)) {
            // create script item UI as a dock widget:
            var basePath = new QFileInfo(file).absolutePath();
            var uiFile = new QFileInfo(InsertScriptItem.getUiFilePath(file)).fileName();
            formWidget = WidgetFactory.createWidget(basePath, uiFile);
            var appWin = RMainWindowQt.getMainWindow();
            dock = new QDockWidget(InsertScriptItem.getFileTitle(file), appWin);
            dock.objectName = InsertScriptItem.getObjectName(file);
            dock.setWidget(formWidget);
            appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
        } else {
            // show previously used and hidden script item UI again:
            if (!QCoreApplication.arguments().contains("-no-show")) {
                dock.visible = true;
            }
            formWidget = dock.widget();
        }
    }

    // call init()
    if (!isNull(global[className]) && isFunction(global[className].init)) {
        global[className].init(formWidget);
    }
};

InsertScriptItem.evalGenerate = function(di, file) {
    var operation = undefined;
    
    var className = new QFileInfo(file).completeBaseName();

    if (!isNull(global[className]) && isFunction(global[className].generate)) {
        operation = global[className].generate(di, file);
    }

    return operation;
};

