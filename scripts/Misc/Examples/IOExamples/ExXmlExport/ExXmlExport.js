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
 * \ingroup ecma_misc_examples_ioexamples
 * \class ExXmlExport
 * This action writes an XML file.
 * This can be used as starting point for XML exporters.
 */
function ExXmlExport(guiAction) {
    EAction.call(this, guiAction);
}

ExXmlExport.prototype = new EAction();

ExXmlExport.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = EAction.getMainWindow();
    var initialPath = QDir.homePath();
    var filterAll = qsTr("All Files") + " (*)";
    var fileDialog = new QFileDialog(appWin, qsTr("Export XML"), initialPath, "");
    fileDialog.setNameFilters([ filterAll ]);
    fileDialog.selectNameFilter(filterAll);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
    fileDialog.setOption(QFileDialog.DontConfirmOverwrite, true);
    fileDialog.fileMode = QFileDialog.AnyFile;
    fileDialog.acceptMode = QFileDialog.AcceptSave;
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

    var fileName = files[0];

    var file = new QFile(fileName);

    var flags = new QIODevice.OpenMode(QIODevice.WriteOnly | QIODevice.Text);
    if (!file.open(flags)) {
        EAction.handleUserWarning("cannot open file: " + fileName);
        this.terminate();
        return;
    }

    EAction.handleUserMessage("exporting: " + fileName);

    var stream = new QXmlStreamWriter(file);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();

    stream.writeStartElement("QCAD");
    stream.writeComment("QCAD XML export example");

    stream.writeStartElement("tag");
    stream.writeEndElement();

    stream.writeEndElement();

    stream.writeEndDocument();

    stream.destroy();

    file.close();

    EAction.handleUserMessage("export successful");

    this.terminate();
};
