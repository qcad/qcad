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
 * File importer factory.
 *
 * Responsible for filter strings, checking if this importer is suitable
 * to import files of a given type and for instantiating the file importer
 * on request.
 */
function ExFileImporterFactory() {
    RFileImporterFactoryAdapter.call(this);
}

ExFileImporterFactory.prototype = new RFileImporterFactoryAdapter();

ExFileImporterFactory.prototype.getFilterStrings = function() {
    return [ qsTr("Example Files %1").arg("(*.example)") ];
};

ExFileImporterFactory.prototype.canImport = function(fileName, nameFilter) {
    var fi = new QFileInfo(fileName);
    if (fi.suffix().toLowerCase()==="example") {
        return 1;
    }
    return -1;
};

ExFileImporterFactory.prototype.instantiate = function(document, messageHandler, progressHandler) {
    return new ExFileImporter(document, messageHandler, progressHandler);
};




/**
 * \ingroup ecma_misc_examples_ioexamples
 * \class ExFileImporter
 * File importer implementation.
 * This class is instantiated if a file of the registered type is imported.
 */
function ExFileImporter(document, messageHandler, progressHandler) {
    RFileImporterAdapter.call(this, document, messageHandler, progressHandler);

    this.messageHandler = messageHandler;
};

ExFileImporter.prototype = new RFileImporterAdapter();

ExFileImporter.prototype.importFile = function(fileName, nameFilter) {
    var doc = this.getDocument();

    // the given file 'fileName' should be imported into doc here...
    var fi = new QFileInfo(fileName);

    var file = new QFile(fi.absoluteFilePath());
    var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
    if (!file.open(flags)) {
        return false;
    }

    this.startImport();

    var ts = new QTextStream(file);
    ts.setCodec("UTF-8");
    var line;

    do {
        line = ts.readLine();

        if (!isNull(this.messageHandler)) {
            this.messageHandler.handleUserMessage(qsTr("Read from file: \"%1\"").arg(line));
        }

        // use importObject to import an object read from the file:
        //this.importObject(new RLineEntity(doc, new RLineData(new RVector(0,0), new RVector(100,100))));

    } while (!ts.atEnd());

    file.close();

    this.endImport();

    return true;
};




/**
 * This action registers a file importer for files of type '.example'.
 */
function ExRegisterFileImporter(guiAction) {
    IOExamples.call(this, guiAction);
}

ExRegisterFileImporter.prototype = new IOExamples();

ExRegisterFileImporter.prototype.beginEvent = function() {
    // this can also be done in an init function to register the file importer
    // during the application initialization:
    RFileImporterRegistry.registerFileImporter(new ExFileImporterFactory());

    var appWin = EAction.getMainWindow();
    QMessageBox.information(
        appWin,
        qsTr("Info"),
        qsTr("Registered a file importer for file type \".example\". Use File > Open to see the filter in action.")
    );
};



/**
 * Adds a menu for this action.
 */
ExRegisterFileImporter.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Register File Importer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExRegisterFileImporter.js");
    action.setGroupSortOrder(71110);
    action.setSortOrder(200);
    action.setWidgetNames(["IOExamplesMenu"]);
};
