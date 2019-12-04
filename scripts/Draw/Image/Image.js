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

/**
 * \defgroup ecma_draw_image Image Drawing Tool
 * \ingroup ecma_draw
 *
 * \brief This module contains the ECMAScript implementation of the image
 * drawing tool.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Image
 * \brief Inserts an image (bitmap) into the drawing.
 * \ingroup ecma_draw_image
 */
function Image(guiAction) {
    Draw.call(this, guiAction);

    this.fileName = undefined;
    this.image = undefined;
    this.width = undefined;
    this.height = undefined;
    this.angle = undefined;
    this.pos = undefined;

    this.setUiOptions(Image.includeBasePath + "/Image.ui");
}

Image.State = {
    SettingPosition : 0
};

Image.prototype = new Draw();

Image.includeBasePath = includeBasePath;

Image.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (isNull(this.fileName)) {
        this.fileName = this.getFileName();
    }

    if (isNull(this.fileName)) {
        this.terminate();
        return;
    }

    this.image = new RImageEntity(
        this.getDocument(),
             new RImageData(this.fileName,
                            new RVector(0,0),
                            new RVector(1,0),
                            new RVector(0,1),
                            50, 50, 0)
    );

    // initial size is image size in pixels (i.e. one pixel -> one unit):
    this.width = this.image.getPixelWidth();
    this.height = this.image.getPixelHeight();

    var optionsToolBar = EAction.getOptionsToolBar();
    var widthEdit = optionsToolBar.findChild("Width");
    var heightEdit = optionsToolBar.findChild("Height");
    widthEdit.setValue(this.width);
    heightEdit.setValue(this.height);

    this.setState(Image.State.SettingPosition);
};

Image.prototype.finishEvent = function() {
    Draw.prototype.finishEvent.call(this);
    if (!isNull(this.image)) {
        this.image.destroy();
    }
};

Image.prototype.getFileName = function() {
    var lastOpenFileDir = RSettings.getStringValue(
            "Image/Path",
            RSettings.getDocumentsLocation());
    var formats = QImageReader.supportedImageFormats();
    var filters = [];

    var filterAllImages = "";
    for (var i=0; i<formats.length; ++i) {
        var format = formats[i];
        var formatAlt = "";

        // ignore format aliases:
        if (format=="jpg" ||
            format=="tif") {
            continue;
        }

        // ignore unsupported formats:
        if (format=="ico" || format=="mng" ||
            format=="pbm" || format=="pgm" || format=="ppm" ||
            format=="svg" || format=="svgz" ||
            format=="xbm" || format=="xpm") {
            continue;
        }

        if (format=="jpeg") {
            formatAlt = "jpg";
        }
        else if (format=="tiff") {
            formatAlt = "tif";
        }

//        if (filters.length!==0) {
//            filters += ";;";
//        }

        var filter = format.toUpper() + " " + qsTr("Files") + " (";
        filter += "*." + format;

        if (filterAllImages.length!==0) {
            filterAllImages += " ";
        }
        filterAllImages += "*." + format;

        if (formatAlt.length!==0) {
            filter += " *." + formatAlt;
            filterAllImages += " *." + formatAlt;
        }
        filter += ")";
        filters.push(filter);
    }

    // default filter (first) is for all image files:
    var allFilter = qsTr("All Image Files (%1)").arg(filterAllImages);
    filters.push(allFilter);
    filters.push(qsTr("All Files") + " (*)");


    // Shorter, but crashes under XUbuntu:
    //var fileName = QFileDialog.getOpenFileName(this, qsTr("Import Bitmap"),
    //               initialPath, filters);

    var appWin = EAction.getMainWindow();
    var fileDialog = new QFileDialog(appWin, qsTr("Import Bitmap"), lastOpenFileDir, "");
    fileDialog.setNameFilters(filters);
    fileDialog.selectNameFilter(allFilter);
    fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());
    if (!isNull(QFileDialog.DontUseCustomDirectoryIcons)) {
        fileDialog.setOption(QFileDialog.DontUseCustomDirectoryIcons, true);
    }
    fileDialog.fileMode = QFileDialog.ExistingFiles;
    fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));
    if (!fileDialog.exec()) {
        fileDialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    var files = fileDialog.selectedFiles();
    if (files.length===0) {
        fileDialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    RSettings.setValue("Image/Path", fileDialog.directory().absolutePath());

    return files[0];
};


Image.prototype.setState = function(state) {
    Draw.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var tr = qsTr("Position");
    this.setLeftMouseTip(tr);
    this.setCommandPrompt(tr);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

Image.prototype.pickCoordinate = function(event, preview) {
    this.pos = event.getModelPosition();

    var op = this.getOperation();
    if (!isNull(op)) {
        if (preview) {
            this.updatePreview();
        }
        else {
            this.getDocumentInterface().setRelativeZero(this.pos);
            this.applyOperation();
        }
    }
};

Image.prototype.getOperation = function(preview) {
    if (isNull(this.image)) {
        return undefined;
    }
    if (isNull(this.width) || isNull(this.height) || isNull(this.angle) || isNull(this.pos)) {
        return undefined;
    }

    this.image.setInsertionPoint(this.pos);
    this.image.setWidth(this.width);
    this.image.setHeight(this.height);
    this.image.setAngle(this.angle);

    return new RAddObjectOperation(this.image.clone(), this.getToolTitle());
};

Image.prototype.slotKeepProportionsChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var widthEdit = optionsToolBar.findChild("Width");
    var heightEdit = optionsToolBar.findChild("Height");
    //var heightLabel = optionsToolBar.findChild("HeightLabel");
    var keepProportionsSwitch = optionsToolBar.findChild("KeepProportions");

    if (value===true) {
        //heightEdit.enabled = false;
        //heightLabel.enabled = false;
        keepProportionsSwitch.icon = new QIcon(Image.includeBasePath + "/KeepProportionsOn.svg");

        // adjust height to width:
        var w = this.image.getPixelWidth();
        var f = widthEdit.getValue() / w;
        var h = this.image.getPixelHeight();
        heightEdit.setValue(h * f);
    }
    else {
        //heightEdit.enabled = true;
        //heightLabel.enabled = true;
        keepProportionsSwitch.icon = new QIcon(Image.includeBasePath + "/KeepProportionsOff.svg");
    }

    this.updatePreview(true);
}

Image.prototype.slotWidthChanged = function(value) {
    if (isNaN(value)) {
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    var heightEdit = optionsToolBar.findChild("Height");
    var keepProportionsSwitch = optionsToolBar.findChild("KeepProportions");
    var keepProportions = keepProportionsSwitch.checked;

    this.width = value;

    if (!isNull(this.image)) {
        this.image.setWidth(value, keepProportions);
        this.height = this.image.getHeight();
        //qDebug("kp: ", keepProportions);
        //qDebug("height: ", this.height);
        heightEdit.blockSignals(true);
        heightEdit.setValue(this.height);
        heightEdit.blockSignals(false);
    }

    this.updatePreview(true);
};

Image.prototype.slotHeightChanged = function(value) {
    if (isNaN(value)) {
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    var widthEdit = optionsToolBar.findChild("Width");
    var keepProportionsSwitch = optionsToolBar.findChild("KeepProportions");
    var keepProportions = keepProportionsSwitch.checked;

    this.height = value;

    if (!isNull(this.image)) {
        this.image.setHeight(value, keepProportions);
        this.width = this.image.getWidth();
        widthEdit.blockSignals(true);
        widthEdit.setValue(this.width);
        widthEdit.blockSignals(false);
    }

    this.updatePreview(true);
};

Image.prototype.slotAngleChanged = function(value) {
    this.angle = value;
    if (!isNull(this.image)) {
        this.image.setAngle(value);
    }

    this.updatePreview(true);
};

