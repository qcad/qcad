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

include("../MiscBlock.js");
include("scripts/File/File.js");

/**
 * \class BlockListExport
 * \brief This action exports the block list as CSV file.
 * \ingroup ecma_misc_block
 */
function BlockListExport(guiAction) {
    MiscBlock.call(this, guiAction);
}

BlockListExport.prototype = new MiscBlock();

BlockListExport.prototype.beginEvent = function() {
    MiscBlock.prototype.beginEvent.call(this);

    var fileName = this.getFileName();

    if (isNull(fileName)) {
        this.terminate();
        return;
    }

    var file = new QFile(fileName);
    var flags = new QIODevice.OpenMode(QIODevice.WriteOnly | QIODevice.Text);
    if (!file.open(flags)) {
        this.terminate();
        return;
    }

    var ts = new QTextStream(file);
    ts.setCodec("UTF-8");
    ts.writeString("Reference Count\tBlock Name");

    var doc = this.getDocument();

    var block;
    var result = doc.queryAllBlocks();
    for (var i=0; i<result.length; ++i) {
        var id = result[i];
        block = doc.queryBlock(id);
        if (block.isNull()) {
            continue;
        }
        var blockRefIds = doc.queryBlockReferences(id);

        ts.writeString("\n%1\t%2".arg(blockRefIds.length).arg(block.getName()));
    }

    file.close();

    this.terminate();
};

BlockListExport.prototype.getFileName = function() {
    var drawingFileName = this.getDocument().getFileName();

    var fi;
    var fileName;
    var initialPath = "";
    if (drawingFileName.length === 0) {
        var path = RSettings.getStringValue("BlockListExport/Path", QDir.homePath());
        fi = new QFileInfo(path);
        initialPath = fi.absoluteFilePath() + QDir.separator
                + stripDirtyFlag(EAction.getMdiChild().windowTitle) + ".csv";
    } else {
        fi = new QFileInfo(drawingFileName);
        initialPath = fi.path() + QDir.separator + fi.completeBaseName() + ".csv";
    }

    var appWin = EAction.getMainWindow();
    var ret = File.getSaveFileName(appWin, qsTr("Export Block List (CSV)"),
                                   initialPath, [ qsTr("CSV") + " (*.csv)" ]);
    if (isNull(ret)) {
        return undefined;
    }
    fileName = ret[0];

    if (fileName === "") {
        return undefined;
    }
    if (drawingFileName.length === 0) {
        RSettings.setValue("BlockListExport/Path", new QFileInfo(fileName).absolutePath());
    }

    return fileName;
};

/**
 * Adds a menu for this action to the Misc menu.
 */
BlockListExport.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Export Block List"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/BlockListExport.js");
    action.setGroupSortOrder(60100);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscBlockMenu", "MiscBlockToolBar", "MiscBlockToolsPanel"]);
};
