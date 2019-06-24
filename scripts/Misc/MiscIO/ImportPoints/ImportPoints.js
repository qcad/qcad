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

include("scripts/EAction.js");

/**
 * This action imports points from a file in the format:
 * x1,y1
 * x2,y2
 * ...
 */
function ImportPoints(guiAction) {
    EAction.call(this, guiAction);
}

ImportPoints.prototype = new EAction();

ImportPoints.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = EAction.getMainWindow();
    var initialPath = QDir.homePath();
    var filterAll = qsTr("All Files") + " (*)";
    var fileDialog = new QFileDialog(appWin, qsTr("Import Points"), initialPath, "");
    fileDialog.setNameFilters([ filterAll ]);
    fileDialog.selectNameFilter(filterAll);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
    if (!isNull(QFileDialog.DontUseCustomDirectoryIcons)) {
        fileDialog.setOption(QFileDialog.DontUseCustomDirectoryIcons, true);
    }
    fileDialog.fileMode = QFileDialog.ExistingFiles;
    if (!fileDialog.exec()) {
        fileDialog.destroy();
        EAction.activateMainWindow();
        this.terminate();
        return;
    }

    var files = fileDialog.selectedFiles();
    if (files.length===0) {
        fileDialog.destroy();
        EAction.activateMainWindow();
        this.terminate();
        return;
    }

    fileDialog.destroy();
    EAction.activateMainWindow();

    var fileName = files[0];

    var document = this.getDocument();
    var di = this.getDocumentInterface();

    var file = new QFile(fileName);
    var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
    if (!file.open(flags)) {
        this.terminate();
        return;
    }

    var ts = new QTextStream(file);
    ts.setCodec("UTF-8");
    var line;
    var coordinates;
    var point;

    var operation = new RAddObjectsOperation();
    do {
        line = ts.readLine();
        coordinates = line.split(',');
        if (coordinates.length!==2) {
            // skip line with invalid point format
            continue;
        }

        var v = new RVector(parseFloat(coordinates[0]), parseFloat(coordinates[1]));
        point = new RPointEntity(document, new RPointData(v));
        operation.addObject(point);
    } while(!ts.atEnd());

    file.close();

    di.applyOperation(operation);

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/ImportPoints.
 */
ImportPoints.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Import Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ImportPoints.js");
    action.setGroupSortOrder(52100);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscIOMenu", "MiscIOToolBar", "MiscIOToolsPanel"]);
};
