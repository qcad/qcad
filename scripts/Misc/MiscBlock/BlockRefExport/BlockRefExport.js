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
 * \class BlockRefExport
 * \brief This action exports block references and positions as CSV file.
 * \ingroup ecma_misc_block
 */
function BlockRefExport(guiAction) {
    MiscBlock.call(this, guiAction);
}

BlockRefExport.prototype = new MiscBlock();

BlockRefExport.prototype.beginEvent = function() {
    MiscBlock.prototype.beginEvent.call(this);

    var fileName = this.getFileName();

    if (isNull(fileName)) {
        this.terminate();
        return;
    }

    var file = new QFile(fileName);
    var flags = makeQIODeviceOpenMode(QIODevice.WriteOnly, QIODevice.Text);
    if (!file.open(flags)) {
        this.terminate();
        return;
    }

    var ts = new QTextStream(file);
    setUtf8Codec(ts);
    ts.writeString("Block Name\tX\tY");

    var doc = this.getDocument();

    var block;
    var result = doc.queryAllBlocks();
    result = doc.sortBlocks(result);
    for (var i=0; i<result.length; ++i) {
        var id = result[i];
        block = doc.queryBlock(id);
        if (isNull(block)) {
            continue;
        }
        var blockRefIds = doc.queryBlockReferences(id);

        for (var k=0; k<blockRefIds.length; k++) {
            var blockRef = doc.queryEntity(blockRefIds[k]);
            ts.writeString("\n%1\t%2\t%3".arg(block.getName()).arg(blockRef.getPosition().x).arg(blockRef.getPosition().y));
        }

    }

    file.close();

    this.terminate();
};

BlockRefExport.prototype.getFileName = function() {
    var drawingFileName = this.getDocument().getFileName();

    var fi;
    var fileName;
    var initialPath = "";
    if (drawingFileName.length === 0) {
        var path = RSettings.getStringValue("BlockRefExport/Path", QDir.homePath());
        fi = new QFileInfo(path);
        initialPath = fi.absoluteFilePath() + QDir.separator
                + stripDirtyFlag(EAction.getMdiChild().windowTitle) + ".csv";
    } else {
        fi = new QFileInfo(drawingFileName);
        initialPath = fi.path() + QDir.separator + fi.completeBaseName() + ".csv";
    }

    var appWin = EAction.getMainWindow();
    var ret = File.getSaveFileName(appWin, qsTr("Export Block References List (CSV)"),
                                   initialPath, [ qsTr("CSV") + " (*.csv)" ]);
    if (isNull(ret)) {
        return undefined;
    }
    fileName = ret[0];

    if (fileName === "") {
        return undefined;
    }
    if (drawingFileName.length === 0) {
        RSettings.setValue("BlockRefExport/Path", new QFileInfo(fileName).absolutePath());
    }

    return fileName;
};

/**
 * Adds a menu for this action to the Misc menu.
 */
BlockRefExport.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Export Block References List") + "…", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/BlockRefExport.js");
    action.setGroupSortOrder(60100);
    action.setSortOrder(250);
    action.setWidgetNames(["MiscBlockMenu", "MiscBlockToolBar", "MiscBlockToolsPanel"]);
};
