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
include("BitmapExportWorker.js");
include("scripts/Tools/arguments.js");

function BitmapExport(guiAction) {
    File.call(this, guiAction);
}

BitmapExport.prototype = new File();

BitmapExport.includeBasePath = includeBasePath;

BitmapExport.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    var bmpFileName = undefined;
    var properties = [];

    if (!isNull(this.guiAction)) {
        // get output name from command line:
        bmpFileName = getArgument(this.guiAction.getArguments(), "-o", "", undefined);
        properties = [];
        properties["width"] = getIntArgument(this.guiAction.getArguments(), "-x", "", 640);
        properties["height"] = getIntArgument(this.guiAction.getArguments(), "-y", "", 480);
        properties["margin"] = 10;
        properties["antialiasing"] = false;
    }

    if (isNull(bmpFileName)) {
        // get file name / properties from dialogs:
        bmpFileName = this.getFilename();

        if (isNull(bmpFileName)) {
            // file dialog cancelled:
            this.terminate();
            return;
        }

        properties = this.getProperties();
        if (isNull(properties)) {
            // properties dialog cancelled:
            this.terminate();
            return;
        }
    }

    if (isNull(bmpFileName)) {
        this.terminate();
        return;
    }

    var res = this.exportBitmap(this.getDocumentInterface(), bmpFileName, properties);

    var appWin = EAction.getMainWindow();
    if (!res[0]) {
        print("Error: cannot save file: ", bmpFileName);
        print("Error: ", res[1]);
        appWin.handleUserWarning(
                qsTr("Error while generating bitmap file \"%1\": %2")
                    .arg(bmpFileName).arg(res[1]));
    }
    else {
        appWin.handleUserMessage(
                qsTr("Bitmap file has been exported to \"%1\"").arg(bmpFileName));
    }

    this.terminate();
};

BitmapExport.prototype.getFilename = function() {
    var fi;

    var drawingFileName = this.getDocument().getFileName();
    var lastUsedExtension = RSettings.getStringValue("BitmapExport/Extension", "bmp");

    var initialPath = File.getInitialSaveAsPath(drawingFileName, lastUsedExtension);

    var formats = QImageWriter.supportedImageFormats();
    var filters = [];

    var filterAllImages = "";
    for (var i=0; i<formats.length; ++i) {
        var format = formats[i];
        var formatAlt = "";
        if (format==="jpg" || format==="tif") {
            continue;
        }

        if (format==="jpeg") {
            formatAlt = "jpg";
        }
        else if (format==="tiff") {
            formatAlt = "tif";
        }

        //if (filters.length!==0) {
        //    filters += ";;";
        //}

        var filter = format.toUpper() + " " + qsTr("Files") + " (";
        if (formatAlt.length!==0) {
            filter += "*." + formatAlt + " ";
        }
        filter += "*." + format;
        filter += ")";

        filters.push(filter);
    }

    var ret = File.getSaveFileName(this, qsTr("Export as Bitmap"), initialPath, filters);

    if (isNull(ret)) {
        return undefined;
    }

    var fileName = ret[0];

    if (isNull(fileName) || fileName.length===0) {
        return undefined;
    }

    RSettings.setValue("BitmapExport/Extension", new QFileInfo(fileName).suffix());

    return fileName;
};

BitmapExport.prototype.getProperties = function() {
    var appWin = EAction.getMainWindow();
    this.dialog = WidgetFactory.createDialog(BitmapExport.includeBasePath, "BitmapExportDialog.ui", appWin);
    WidgetFactory.restoreState(this.dialog);

    var widthEdit = this.dialog.findChild("Width");
    var heightEdit = this.dialog.findChild("Height");
    var resolutionCombo = this.dialog.findChild("Resolution");
    var marginCombo = this.dialog.findChild("Margin");

    var whiteRadio = this.dialog.findChild("WhiteBackground");
    var blackRadio = this.dialog.findChild("BlackBackground");
    var transparentRadio = this.dialog.findChild("TransparentBackground");

    var monoRadio = this.dialog.findChild("ColorMonochrome");
    var grayRadio = this.dialog.findChild("ColorGrayscale");
    var colorRadio = this.dialog.findChild("ColorFull");

    var antiAliasingCheckbox = this.dialog.findChild("AntiAliasing");

    var selectionCheckbox = this.dialog.findChild("Selection");
    selectionCheckbox.toggled.connect(this, "selectionChanged");
    var weightMarginCheckbox = this.dialog.findChild("WeightMargin");

    widthEdit.valueChanged.connect(
                function() {
                    resolutionCombo.index = 0;
                });
    heightEdit.valueChanged.connect(
                function() {
                    resolutionCombo.index = 0;
                });
    resolutionCombo.editTextChanged.connect(this, "resolutionChanged");
    this.resolutionChanged(resolutionCombo.currentText);

    if (!this.dialog.exec()) {
        this.dialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    WidgetFactory.saveState(this.dialog);

    var ret = [];

    if (resolutionCombo.currentText!=="auto") {
        ret["resolution"] = parseInt(resolutionCombo.currentText);
    }
    else {
        ret["width"] = Math.ceil(widthEdit.getValue());
        ret["height"] = Math.ceil(heightEdit.getValue());
    }
    if (whiteRadio.checked) {
        ret["backgroundColor"] = new QColor("white");
    }
    else if (blackRadio.checked) {
        ret["backgroundColor"] = new QColor("black");
    }
    else {
        ret["backgroundColor"] = new QColor("#000000ff");
    }

    ret["margin"] = RMath.eval(marginCombo.currentText);
    ret["antialiasing"] = antiAliasingCheckbox.checked;
    if (monoRadio.checked) {
      ret["monochrome"] = true;
    }
    if (grayRadio.checked) {
      ret["grayscale"] = true;
    }

    ret["noWeightMargin"] = !weightMarginCheckbox.checked;

    if (selectionCheckbox.checked) {
        var doc = this.getDocument();
        ret["entityIds"] = doc.querySelectedEntities();
    }

    this.dialog.destroy();
    EAction.activateMainWindow();
    return ret;
};

BitmapExport.prototype.selectionChanged = function(value) {
    this.documentWidth = undefined;
    this.documentHeight = undefined;

    var resolutionCombo = this.dialog.findChild("Resolution");
    this.resolutionChanged(resolutionCombo.currentText);
};

BitmapExport.prototype.resolutionChanged = function(str) {
    if (str==="auto") {
        return;
    }

    var res = parseInt(str, 10);
    if (isNaN(res)) {
        return;
    }

    var widthEdit = this.dialog.findChild("Width");
    var heightEdit = this.dialog.findChild("Height");
    var selectionCheckbox = this.dialog.findChild("Selection");

    if (isNull(this.documentWidth) || isNull(this.documentHeight)) {
        var document = this.getDocument();
        var bb;
        if (selectionCheckbox.checked) {
            bb = document.getSelectionBox();
        }
        else {
            bb = document.getBoundingBox(true, true);
        }
        this.documentWidth = bb.getWidth();
        this.documentHeight = bb.getHeight();
    }

    widthEdit.setValue(Math.ceil(res * this.documentWidth));
    heightEdit.setValue(Math.ceil(res * this.documentHeight));
};

BitmapExport.prototype.exportBitmap = function(di, fileName, properties) {
    // make sure nothing is selected:
    di.deselectAll();
    var view = di.getLastKnownViewWithFocus();
    var scene = view.getScene();

    var ret = exportBitmap(di.getDocument(), scene, fileName, properties);

    // restore selection before export:
    if (!isNull(properties["entityids"])) {
        di.selectEntities(properties["entityids"]);
    }

    return ret;
};

