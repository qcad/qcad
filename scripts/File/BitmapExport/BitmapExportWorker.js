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
 * Exports the given RDocument (doc) to a bitmap (BMP, PNG, JPEG, TIFF, ...).
 * \param doc RDocument document
 * \param scene Graphics scene to export (e.g. RGraphicsSceneQt)
 * \param fileName File name for exported bitmap. Extension determines format.
 * \param properties Various properties:
 *
 *  - properties["width"]: width of bitmap in pixels (ignored if resolution is present)
 *  - properties["height"]: height of bitmap in pixels (ignored if resolution is present)
 *  - properties["resolution"]: resolution in pixels / drawing unit
 *  - properties["margin"]: margin at borders in pixels
 *  - properties["noWeightMargin"]: true to disable margin for lineweight, defaults to false
 *  - properties["backgroundColor"]: background color (RColor)
 *  - properties["origin"]: true: export origin point as red cross
 *  - properties["antialiasing"]: true: use antialiasing
 *  - properties["quality"]: Export quality (0..100), JPEG only
 *  - properties["monochrome"]: true: Export as black / white
 *  - properties["grayscale"]: true: Export as grayscale
 *  - properties["window"]: RBox: window to export in drawing coordinates
 *  - properties["entityIds"]: Array: zoom to bounding box of given entities
 *  - properties["initView"]: Callback to initialize view
 *  - properties["zoomAll"]: Auto zoom to all entities, including those on invisible layers
 *  - properties["metaData"]: Key / value pairs of meta data to write to image header
 *
 * \param view Optional graphics view to use.
 */
function exportBitmap(doc, scene, fileName, properties, view) {
    var ret;

    var viewCreated = false;
    if (typeof(view)==="undefined") {
        view = new RGraphicsViewImage();
        view.setScene(scene, false);
        viewCreated = true;
    }
    var numThreadsOri = view.getNumThreads();

    var antialiasing = (properties["antialiasing"]==null ? true : properties["antialiasing"]);

    // crashes with multiple threads:
    view.setNumThreads(1);
    view.setAlphaEnabled(true);

    view.setPaintOrigin(properties["origin"]==null ? false : properties["origin"]);
    view.setTextHeightThresholdOverride(0);
    view.setAntialiasing(antialiasing);

    if (properties["monochrome"]===true) {
        view.setColorMode(RGraphicsView.BlackWhite);
    }
    else if (properties["grayscale"]===true) {
        view.setColorMode(RGraphicsView.GrayScale);
    }

    if (properties["backgroundColor"]) {
        view.setBackgroundColor(properties["backgroundColor"]);
    }

    if (typeof(properties["colorCorrection"])!=="undefined") {
        view.setColorCorrectionOverride(properties["colorCorrection"]);
    }

    if (typeof(properties["margin"])==="undefined") {
        properties["margin"] = 20;
    }

    if (typeof(properties["noWeightMargin"])==="undefined") {
        properties["noWeightMargin"] = false;
    }

    if (typeof(properties["zoomAll"])==="undefined") {
        properties["zoomAll"] = false;
    }

    if (properties["resolution"]) {
        var bb;
        if (typeof(properties["entityIds"])!=="undefined") {
            bb = doc.getEntitiesBox(properties["entityIds"]);
        }
        else {
            bb = doc.getBoundingBox(true, true);
        }

        if (properties["noWeightMargin"]===false) {
            // grow bounding box by max line weight:
            var wm = RUnit.convert(doc.getMaxLineweight()/100.0/2, RS.Millimeter, doc.getUnit());
            bb.growXY(wm);
        }

        properties["width"] = Math.ceil(bb.getWidth() * properties["resolution"] + 2 * properties["margin"]);
        properties["height"] = Math.ceil(bb.getHeight() * properties["resolution"] + 2 * properties["margin"]);
    }

    if (!properties["width"]) {
        properties["width"] = 640;
    }
    if (!properties["height"]) {
        properties["height"] = 480;
    }

    if (properties["width"] * properties["height"] > 2147483647/4) {
        qDebug("invalid image size");
        ret = [ false, qsTr("Invalid image size (width x height must be less than %1)").arg(536870911) ];
        view.setNumThreads(numThreadsOri);
        return ret;
    }

    view.resizeImage(properties["width"], properties["height"]);

    if (properties["window"]) {
        view.zoomTo(properties["window"], properties["margin"]);
    }
    else if (properties["zoomAll"]) {
        var bbz = doc.getBoundingBox(false, true);
        view.zoomTo(bbz, properties["margin"]);
    }
    else if (typeof(properties["entityIds"])!=="undefined") {
        view.zoomToEntities(properties["entityIds"], properties["margin"]);
    }
    else {
        view.autoZoom(properties["margin"], true, properties["noWeightMargin"]);
    }

    // make sure we use the desired resolution:
    // auto zoom might be slightly off, due to rounding canvas to pixels:
    if (properties["resolution"]) {
        view.setFactor(properties["resolution"]);
    }

    view.clear();
    view.setExporting(true);
    view.setHairlineMinimumMode(true);

    if (properties["regen"]!==false) {
        scene.regenerate();
        view.repaintView();
    }

    if (isFunction(properties["initView"])) {
        properties["initView"](view);
    }

    // export file
    var buffer = view.getBuffer();

    if (properties["monochrome"]===true && !antialiasing) {
        buffer = buffer.convertToFormat(QImage.Format_Mono);
    }

    view.setNumThreads(numThreadsOri);
    if (viewCreated) {
        scene.unregisterView(view);
        view.destroy();
    }

    var iw = new QImageWriter(fileName);
    var ext = new QFileInfo(fileName).suffix().toLowerCase();
    if (ext === "png") {
        iw.setQuality(9);
    } else if (ext === "jpg" || ext === "jpeg") {
        iw.setQuality(properties["quality"]==null ? 100 : properties["quality"]);
    } else if (ext === "tif" || ext === "tiff") {
        iw.setCompression(1);
    } else if (ext === "bmp") {
        iw.setCompression(1);
    }

    if (isArray(properties["metaData"])) {
        for (var i=0; i<properties["metaData"].length; i++) {
            // meta data:
            iw.setText(properties["metaData"][0], properties["metaData"][1]);
        }
    }

    if (!iw.write(buffer)) {
        ret = [false, iw.errorString()];
    } else {
        ret = [true, ""];
    }
    iw.destroy();

    return ret;
}
