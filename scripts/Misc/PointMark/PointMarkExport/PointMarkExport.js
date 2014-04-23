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
include("scripts/EAction.js");
include("scripts/File/File.js");
include("../PointMark.js");

/**
 * This action exports bench marks and point marks as CSV file.
 */
function PointMarkExport(guiAction) {
    EAction.call(this, guiAction);
}

PointMarkExport.prototype = new EAction();

PointMarkExport.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var treeWidget = appWin.findChild("PointMarkTree");
    var exportBenchmarkHandle = undefined;
    if (!isNull(treeWidget)) {
        var currentItem = treeWidget.currentItem();
        if (!isNull(currentItem)) {
            if (!isNull(currentItem.parent())) {
                currentItem = currentItem.parent();
            }

            exportBenchmarkHandle = currentItem.data(0, Qt.UserRole);
        }
    }

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
    ts.writeString("NAME,E(x),N(y),z,DESC");

    var doc = this.getDocument();
    var tree = PointMark.getPointMarkTree(doc);
    var item;

    for (var i=0; i<tree.length; i++) {
        var list = tree[i];

        if (!isNull(exportBenchmarkHandle)) {
            if (list.length>0 && list[0][3]!==exportBenchmarkHandle) {
                // skip other benchmarks than the selected one:
                continue;
            }
        }

        for (var k=0; k<list.length; k++) {
            var label = list[k][0];

            // prevent commas in data fields:
            label = label.replace(/,/g, '_');

            ts.writeString(
                "\n%1,%2,%3,%4,%5"
                .arg(label)
                .arg(sprintf("%.12f", list[k][1].x))
                .arg(sprintf("%.12f", list[k][1].y))
                .arg(0.0)
                .arg(label)
            );
        }
    }

    file.close();

    this.terminate();
};

PointMarkExport.prototype.getFileName = function() {
    var doc = this.getDocument();
    var drawingFileName = doc.getFileName();

    var unitPostfix = RUnit.unitToName(doc.getUnit(), false).toLowerCase();
    if (unitPostfix==="none") {
        unitPostfix = "";
    }
    else {
        unitPostfix = "_" + unitPostfix;
    }

    var fi;
    var fileName;
    var initialPath = "";
    if (drawingFileName.length === 0) {
        var path = RSettings.getStringValue("PointMarkExport/Path", QDir.homePath());
        fi = new QFileInfo(path);
        initialPath = fi.absoluteFilePath() + QDir.separator
                + stripDirtyFlag(EAction.getMdiChild().windowTitle) + unitPostfix + ".csv";
    } else {
        fi = new QFileInfo(drawingFileName);
        initialPath = fi.path() + QDir.separator + fi.completeBaseName() + unitPostfix + ".csv";
    }

    qDebug("initialPath: ", initialPath);

    var appWin = EAction.getMainWindow();
    var ret = File.getSaveFileName(appWin, qsTr("Export Point Mark List (CSV)"),
                                   initialPath, [ qsTr("CSV") + " (*.csv)" ]);
    if (isNull(ret)) {
        return undefined;
    }
    fileName = ret[0];

    if (fileName === "") {
        return undefined;
    }
    if (drawingFileName.length === 0) {
        RSettings.setValue("PointMarkExport/Path", new QFileInfo(fileName).absolutePath());
    }

    return fileName;
};
