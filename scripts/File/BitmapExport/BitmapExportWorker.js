/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
 *  properties["width"]: width of bitmap in pixels (ignored if resolution is present)
 *  properties["height"]: height of bitmap in pixels (ignored if resolution is present)
 *  properties["resolution"]: resolution in pixels / drawing unit
 *  properties["margin"]: margin at borders in pixels
 *  properties["backgroundColor"]: background color (RColor)
 *  properties["origin"]: true: export origin point as red cross
 *  properties["antialiasing"]: true: use antialiasing
 *  properties["quality"]: Export quality (0..100), JPEG only
 *  properties["monochrome"]: true: Export as black / white
 *  properties["grayscale"]: true: Export as grayscale
 */
function exportBitmap(doc, scene, fileName, properties) {
    var view = new RGraphicsViewImage();
    view.setScene(scene, false);

    view.setPaintOrigin(properties["origin"]==null ? false : properties["origin"]);
    view.setTextHeightThresholdOverride(0);
    view.setAntialiasing(properties["antialiasing"]==null ? true : properties["antialiasing"]);

    if (properties["monochrome"]===true) {
        view.setColorMode(RGraphicsView.BlackWhite);
    }
    else if (properties["grayscale"]===true) {
        view.setColorMode(RGraphicsView.GrayScale);
    }

    if (properties["backgroundColor"]) {
        view.setBackgroundColor(properties["backgroundColor"]);
    }

    if (properties["colorCorrection"]) {
        view.setColorCorrectionOverride(properties["colorCorrection"]);
    }

    if (typeof(properties["margin"])==="undefined") {
        properties["margin"] = 20;
    }

    if (properties["resolution"]) {
        var bb = doc.getBoundingBox(true, true);
        properties["width"] = Math.round(bb.getWidth() * properties["resolution"] + 2 * properties["margin"]);
        properties["height"] = Math.round(bb.getHeight() * properties["resolution"] + 2 * properties["margin"]);
    }

    if (!properties["width"]) {
        properties["width"] = 640;
    }
    if (!properties["height"]) {
        properties["height"] = 480;
    }

    view.resizeImage(properties["width"], properties["height"]);

    view.autoZoom(properties["margin"], true);

    scene.regenerate();

    // export file
    var buffer = view.getBuffer();

    scene.unregisterView(view);

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

    var ret;
    if (!iw.write(buffer)) {
        ret = [false, iw.errorString()];
    } else {
        ret = [true, ""];
    }
    iw.destroy();

    return ret;
}
