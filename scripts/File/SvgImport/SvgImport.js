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

include("scripts/File/File.js");
include("scripts/ImportExport/SvgImporter/SvgImporter.js");

function SvgImport(guiAction) {
    File.call(this, guiAction);
}

SvgImport.prototype = new File();

SvgImport.getPreferencesCategory = function() {
    return [ qsTr("File"), qsTr("SVG Import")];
};

SvgImport.includeBasePath = includeBasePath;

SvgImport.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    var fileName = undefined;

    if (!isNull(this.guiAction)) {
        var args = this.guiAction.getArguments();
        this.guiAction.clearArguments();
        if (args.length>0) {
            fileName = args[0];

            var fi = new QFileInfo(fileName);
            if (!fi.isAbsolute()) {
                fileName = RSettings.getLaunchPath() + QDir.separator + fileName;
                fi = new QFileInfo(fileName);
            }

            if (!fi.exists()) {
                qWarning("file does not exist: ", fileName);
                this.terminate();
                return;
            }
        }
    }
    
    if (isNull(fileName)) {
        var lastDir = RSettings.getStringValue( "SvgImport/Path", RSettings.getDocumentsLocation());
        fileName = QFileDialog.getOpenFileName(
            this, qsTr("Import SVG"), lastDir,
            qsTr("SVG Files") + " (*.svg);;" + qsTr("All Files") + " (*)");
        if (fileName.length===0) {
            this.terminate();
            return;
        }
        RSettings.setValue("SvgImport/Path", new QFileInfo(fileName).absolutePath());
    }

    var appWin = EAction.getMainWindow();
    var dialog = WidgetFactory.createDialog(SvgImport.includeBasePath, "SvgImportDialog.ui", appWin);
    var resolutionCombo = dialog.findChild("Resolution");

    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
        this.terminate();
        return;
    }
    
    var resolution = parseFloat(resolutionCombo.currentText);
    if (isNaN(resolution) || resolution<=0) {
        resolution = 90;
    }

    var svgImporter = new SvgImporter(this.getDocument(), resolution);
    svgImporter.importFile(fileName);

    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        di.regenerateScenes();
        di.autoZoom();
    }

    if (!isNull(appWin)) {
        appWin.notifyListeners();
    }
    
    dialog.destroy();
    EAction.activateMainWindow();
    this.terminate();
};
