/**
 * Copyright (c) 2013 by Matthias Melcher. All rights reserved.
 * 
 * This file is an addition to the QCAD project.
 *
 * MOL Import is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MOL Import is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("../MiscIO.js");
include("MolImporter.js");

function MolImport(guiAction) {
    MiscIO.call(this, guiAction);
}

MolImport.prototype = new MiscIO();

MolImport.basePath = includeBasePath;

MolImport.prototype.beginEvent = function() {
    MiscIO.prototype.beginEvent.call(this);
    
    var lastDir = RSettings.getStringValue(
            "MolImport/Path",
            RSettings.getDocumentsLocation());
    var fileName = QFileDialog.getOpenFileName(
        this, qsTr("Import MOL"), lastDir,
        qsTr("MOL Files") + " (*.mol);;" + qsTr("All Files") + " (*)");
    if (fileName.length===0) {
        this.terminate();
        return;
    }
    RSettings.setValue("MolImport/Path", new QFileInfo(fileName).absolutePath());
    
    //this.importMol(MolImport.basePath + "/my.mol");
    var molImporter = new MolImporter(EAction.getDocument());
    molImporter.importFile(fileName);
    if (!isNull(EAction.getDocumentInterface())) {
        EAction.getDocumentInterface().regenerateScenes();
    }

    
    this.terminate();
};
