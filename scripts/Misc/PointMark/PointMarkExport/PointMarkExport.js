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
    ts.writeString("X\tY\tLabel");

    var doc = this.getDocument();
    var tree = PointMark.getPointMarkTree(doc);
    var item;

    for (var i=0; i<tree.length; i++) {
        var list = tree[i];

        for (var k=0; k<list.length; k++) {
            ts.writeString(
                "\n%1\t%2\t%3"
                .arg(list[k][1].x)
                .arg(list[k][1].y)
                .arg(list[k][0])
            );
        }
    }

    file.close();

    this.terminate();
};

PointMarkExport.prototype.getFileName = function() {
    var drawingFileName = this.getDocument().getFileName();
    var fi;
    var fileName;
    var initialPath = "";
    if (drawingFileName.length === 0) {
        var path = RSettings.getStringValue("PointMarkExport/Path", QDir.homePath());
        fi = new QFileInfo(path);
        initialPath = fi.absoluteFilePath() + QDir.separator
                + stripDirtyFlag(EAction.getMdiChild().windowTitle) + ".csv";
    } else {
        fi = new QFileInfo(drawingFileName);
        initialPath = fi.path() + QDir.separator + fi.completeBaseName() + ".csv";
    }

    var appWin = EAction.getMainWindow();
    var ret = File.getSaveFileName(appWin, qsTr("Export Point Label (CSV)"),
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
