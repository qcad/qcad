/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("../File.js");
include("scripts/ImportExport/SvgImporter/SvgImporter.js");

function SvgImport(guiAction) {
    File.call(this, guiAction);
}

SvgImport.prototype = new File();

SvgImport.basePath = includeBasePath;

SvgImport.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);
    
    var lastDir = RSettings.getStringValue(
            "SvgImport/Path",
            QDesktopServices.storageLocation(QDesktopServices.DocumentsLocation));
    var fileName = QFileDialog.getOpenFileName(
        this, qsTr("Import SVG"), lastDir,
        qsTr("SVG Files") + " (*.svg);;" + qsTr("All Files") + " (*)");
    if (fileName.length===0) {
        this.terminate();
        return;
    }
    RSettings.setValue("SvgImport/Path", new QFileInfo(fileName).absolutePath());
    
    var svgImporter = new SvgImporter(this.getDocument());
    svgImporter.importFile(fileName);

    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        di.regenerateScenes();
    }

    var appWin = EAction.getMainWindow();
    if (!isNull(appWin)) {
        appWin.notifyListeners();
    }
    
    this.terminate();
};
