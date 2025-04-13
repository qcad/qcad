/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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

/**
 * \ingroup ecma_misc_examples_ioexamples
 * \class ExCsvExport
 * This action writes point coordinates to a CSV file.
 */
function ExCsvExport(guiAction) {
    EAction.call(this, guiAction);
}

ExCsvExport.prototype = new EAction();

ExCsvExport.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    // file dialog:
    var appWin = EAction.getMainWindow();

    var filterCsv = "CSV Files (*.csv)";
    var ret = File.getSaveFileName(appWin, "Export to CSV", QDir.homePath(), [filterCsv], filterCsv);
    if (isNull(ret)) {
        // file dialog canceled:
        return;
    }

    var fileName = ret[0];

    var file = new QFile(fileName);

    // open file for writing:
    var flags = makeQIODeviceOpenMode(QIODevice.WriteOnly, QIODevice.Text);
    if (!file.open(flags)) {
        EAction.handleUserWarning("cannot open file: " + fileName);
        this.terminate();
        return;
    }

    EAction.handleUserMessage("exporting: " + fileName);

    // create text stream:
    var ts = new QTextStream(file);
    setUtf8Codec(ts);
    ts.writeString("x, y\n");

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    // export points to CSV:
    var ids = document.queryAllEntities();
    ids = di.getStorage().orderBackToFront(ids);
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);

        if (isPointEntity(entity)) {
            var pos = entity.getPosition();
            ts.writeString("%1, %2\n".arg(pos.x).arg(pos.y));
        }
    }

    // clean up:
    destr(ts);
    file.close();

    EAction.handleUserMessage("export successful");

    this.terminate();
};
