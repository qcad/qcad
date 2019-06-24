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

include("../IOExamples.js");


/**
 * File exporter factory.
 *
 * Responsible for filter strings, checking if this exporter is suitable
 * to export files of a given type and for instantiating the file exporter
 * on request.
 */
function ExFileExporterFactory() {
    RFileExporterFactoryAdapter.call(this);
}

ExFileExporterFactory.prototype = new RFileExporterFactoryAdapter();

ExFileExporterFactory.prototype.getFilterStrings = function() {
    return [ qsTr("Example Files %1").arg("(*.example)") ];
};

ExFileExporterFactory.prototype.canExport = function(fileName, nameFilter) {
    var fi = new QFileInfo(fileName);
    if (fi.suffix().toLowerCase()==="example") {
        return 1;
    }
    return -1;
};

ExFileExporterFactory.prototype.instantiate = function(document, messageHandler, progressHandler) {
    return new ExFileExporter(document, messageHandler, progressHandler);
};




/**
 * \ingroup ecma_misc_examples_ioexamples
 * \class ExFileExporter
 * File exporter implementation.
 * This class is instantiated if a file of the registered type is exported.
 */
function ExFileExporter(document, messageHandler, progressHandler) {
    RFileExporterAdapter.call(this, document, messageHandler, progressHandler);
};

ExFileExporter.prototype = new RFileExporterAdapter();

ExFileExporter.prototype.getCorrectedFileName = function(fileName, nameFilter) {
    var ret = fileName;
    var ext = new QFileInfo(ret).suffix().toLowerCase();

    if (ext!=="example") {
        ret += ".example";
    }

    return ret;
};

ExFileExporter.prototype.exportFile = function(fileName, nameFilter, setFileName) {
    var doc = this.getDocument();

    // the document 'doc' should be exported to file 'fileName' here...
    var file = new QFile(fileName);
    var flags = new QIODevice.OpenMode(QIODevice.WriteOnly | QIODevice.Text);
    if (!file.open(flags)) {
        return false;
    }

    if (setFileName) {
        doc.setFileName(fileName);
    }

    var ts = new QTextStream(file);
    ts.setCodec("UTF-8");
    ts.writeString("Example");

    file.close();

    return true;
};




/**
 * This action registers a file exporter for files of type '.example'.
 */
function ExRegisterFileExporter(guiAction) {
    IOExamples.call(this, guiAction);
}

ExRegisterFileExporter.prototype = new IOExamples();

ExRegisterFileExporter.prototype.beginEvent = function() {
    // this can also be done in an init function to register the file exporter
    // during the application initialization:
    RFileExporterRegistry.registerFileExporter(new ExFileExporterFactory());

    var appWin = EAction.getMainWindow();
    QMessageBox.information(
        appWin,
        qsTr("Info"),
        qsTr("Registered a file exporter for file type \".example\". Use File > Save As to see the filter in action.")
    );
};



/**
 * Adds a menu for this action.
 */
ExRegisterFileExporter.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Register File Exporter"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExRegisterFileExporter.js");
    action.setGroupSortOrder(71110);
    action.setSortOrder(200);
    action.setWidgetNames(["IOExamplesMenu"]);
};
