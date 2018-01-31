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
 * SAX style XML handler.
 */
function MyXmlHandler() {
    QXmlDefaultHandler.call(this);
}

MyXmlHandler.prototype = new QXmlDefaultHandler();

/**
 * Handle element (tag).
 */
MyXmlHandler.prototype.startElement = function(namespaceURI, localName, qName, atts) {
    EAction.handleUserMessage("tag: " + localName);
    for (var i=0; i<atts.length(); i++) {
        EAction.handleUserMessage("  attribute: " + atts.localName(i) + ": " + atts.value(i));
    }
    return true;
};

MyXmlHandler.prototype.endElement = function(namespaceURI, localName, qName) {
    return true;
};

/**
 * Handle character data.
 */
MyXmlHandler.prototype.characters = function(str) {
    EAction.handleUserMessage("CDATA: " + str);
    return true;
};



/**
 * \ingroup ecma_misc_examples_ioexamples
 * \class ExXmlImport
 * This action reads an XML file and outputs information to stderr.
 * This can be used as starting point for XML importers.
 */
function ExXmlImport(guiAction) {
    EAction.call(this, guiAction);
}

ExXmlImport.prototype = new EAction();

ExXmlImport.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = EAction.getMainWindow();
    var initialPath = QDir.homePath();
    var filterAll = qsTr("All Files") + " (*)";
    var fileDialog = new QFileDialog(appWin, qsTr("Import XML"), initialPath, "");
    fileDialog.setNameFilters([ filterAll ]);
    fileDialog.selectNameFilter(filterAll);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
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

    //var file = new QFile(fileName);

    EAction.handleUserMessage("importing: " + fileName);

    //var xmlReader = new QXmlSimpleReader();
    //var source = new QXmlInputSource(file);
    var handler = new MyXmlHandler();
    //xmlReader.setContentHandler(handler);
    //var ok = xmlReader.parse(source, false);
    var ok = parseXml(fileName, handler);

    if (ok) {
        EAction.handleUserMessage("import successful");
    }
    else {
        EAction.handleUserMessage("import failed");
    }

    //file.close();

    this.terminate();
};
