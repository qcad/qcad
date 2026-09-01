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
 * \param scene Graphics scene to export (e.g. RGraphicsSceneQt, RGraphicsSceneRhi3D)
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
 *  - properties["colorCorrection"]: explicitely enable / disable color correction
 *
 * \param view Optional graphics view to use.
 *
 * An image based scene (RGraphicsSceneQt) is rendered into an image by an
 * image based view (RGraphicsViewImage). An RHI based scene
 * (RGraphicsSceneRhi3D) exports its entities into the view it is attached
 * to (i.e. onto the GPU) and cannot be rendered by an image based view:
 * the rendered frame is read back from the RHI based view instead (see
 * \ref renderBitmapRhi).
 */
function exportBitmap(doc, scene, fileName, properties, view) {
    var ret;

    initBitmapProperties(doc, properties);

    if (properties["width"] * properties["height"] > 2147483647/4) {
        qDebug("invalid image size");
        return [ false, qsTr("Invalid image size (width x height must be less than %1)").arg(536870911) ];
    }

    var buffer;

    var rhiView = getRhiViewOfScene(scene, view);
    if (!isNull(rhiView)) {
        // RHI based scene (RGraphicsSceneRhi3D):
        buffer = renderBitmapRhi(doc, scene, properties, rhiView);
    }
    else {
        // image based scene (RGraphicsSceneQt):
        buffer = renderBitmapImage(doc, scene, properties, view);
    }

    if (isNull(buffer) || buffer.isNull()) {
        qDebug("cannot render image");
        return [ false, qsTr("Cannot render image") ];
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
    destr(iw);

    return ret;
}

/**
 * Initializes the properties which are used by all views: applies the
 * defaults and converts a resolution into the size of the image.
 */
function initBitmapProperties(doc, properties) {
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
}

/**
 * Zooms the given view (RGraphicsView) to the area which is exported
 * (window, entities, bounding box of the drawing).
 *
 * \param margin Margin at the borders in the pixel unit of the view.
 */
function zoomBitmapView(doc, view, properties, margin) {
    // remember the box we zoom to, so we can re-center on it below when a
    // fixed resolution is used:
    var zoomBox;
    if (properties["window"]) {
        zoomBox = properties["window"];
        view.zoomTo(zoomBox, margin);
    }
    else if (properties["zoomAll"]) {
        zoomBox = doc.getBoundingBox(false, true);
        view.zoomTo(zoomBox, margin);
    }
    else if (typeof(properties["entityIds"])!=="undefined") {
        zoomBox = doc.getEntitiesBox(properties["entityIds"]);
        view.zoomToEntities(properties["entityIds"], margin);
    }
    else {
        zoomBox = doc.getBoundingBox(true, true);
        view.autoZoom(margin, true, properties["noWeightMargin"]);
    }

    // make sure we use the desired resolution:
    // auto zoom might be slightly off, due to rounding canvas to pixels:
    if (properties["resolution"]) {
        view.setFactor(properties["resolution"]);
        // setFactor() changes the zoom factor but keeps the offset that
        // zoomTo() computed for its own (margin adjusted) factor. That leaves
        // the drawing off-center, putting the whole margin on one side and
        // pushing the opposite side out of the image. Re-center on the
        // exported box so the margin is distributed evenly on all sides:
        if (!isNull(zoomBox) && zoomBox.isValid()) {
            view.centerToBox(zoomBox);
        }
    }
}

/**
 * Renders the given image based scene (RGraphicsSceneQt) into an image.
 *
 * \param view Optional image based view (RGraphicsViewImage) to use. A
 * temporary view is created and attached to the scene if no view is given.
 *
 * \return QImage or undefined.
 */
function renderBitmapImage(doc, scene, properties, view) {
    var viewCreated = false;
    if (isNull(view)) {
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
    if (typeof(properties["textHeightThreshold"])!=="undefined") {
        view.setTextHeightThresholdOverride(properties["textHeightThreshold"]);
        view.setForceTextHeightThreshold(true);
    }
    else {
        view.setTextHeightThresholdOverride(0);
    }

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

    view.resizeImage(properties["width"], properties["height"]);

    zoomBitmapView(doc, view, properties, properties["margin"]);

    view.clear();
    view.setExporting(true);
    view.setHairlineMinimumMode(true);

    if (properties["regen"]!==false) {
        scene.regenerate();
    }

    view.updateImage();

    if (isFunction(properties["initView"])) {
        properties["initView"](view);
    }

    var buffer = view.getBuffer();

    if (properties["monochrome"]===true && !antialiasing) {
        buffer = buffer.convertToFormat(QImage.Format_Mono);
    }

    view.setNumThreads(numThreadsOri);
    if (viewCreated) {
        scene.unregisterView(view);
        destr(view);
    }

    return buffer;
}

/**
 * Renders the given RHI based scene (RGraphicsSceneRhi3D) by reading the
 * frame rendered by the given RHI based view back from the GPU.
 *
 * The RHI based view renders into its own (on screen) window and not into
 * an image of arbitrary size: it is resized and zoomed to the exported
 * area for the export and restored afterwards. The rendered frame is in
 * device pixels and scaled to the exported size.
 *
 * Options which are implemented by the image based view only (paint
 * origin, antialiasing, alpha channel, text height threshold, number of
 * threads) are not available. The color modes (monochrome, grayscale) are
 * applied to the rendered image.
 *
 * The grid and the decorations (origin, crosshair, reference points, snap
 * label) are not rendered while the view is exporting. The colors of the
 * entities are resolved when they are exported into the view however:
 * selected entities are rendered in the selection color (deselect before
 * exporting, as BitmapExport does).
 *
 * \param rhiView RGraphicsViewRhi2D or RGraphicsViewRhi3D.
 *
 * \return QImage or undefined.
 */
function renderBitmapRhi(doc, scene, properties, rhiView) {
    // the RGraphicsView interface of the view (navigation, zooming):
    // owned by the view, 2D views only:
    var view = undefined;
    if (isFunction(rhiView.getRGraphicsView)) {
        view = rhiView.getRGraphicsView();
    }

    // the view is displayed on screen: remember its state to restore it
    // after the export:
    var oriWidth = rhiView.width;
    var oriHeight = rhiView.height;
    var oriFactor, oriOffset, oriBackgroundColor, oriExporting, oriHairlineMinimumMode, oriColorCorrection;
    if (!isNull(view)) {
        oriFactor = view.getFactor();
        oriOffset = view.getOffset();
        oriBackgroundColor = view.getBackgroundColor();
        oriExporting = view.isExporting();
        oriHairlineMinimumMode = view.getHairlineMinimumMode();
        oriColorCorrection = rhiView.getColorCorrectionOverride();
    }

    // the zoom depends on the size of the view: resize first:
    rhiView.resize(properties["width"], properties["height"]);
    QCoreApplication.processEvents();

    if (!isNull(view)) {
        if (properties["backgroundColor"]) {
            view.setBackgroundColor(properties["backgroundColor"]);
        }

        if (typeof(properties["colorCorrection"])!=="undefined") {
            rhiView.setColorCorrectionOverride(properties["colorCorrection"]);
        }

        view.setExporting(true);
        view.setHairlineMinimumMode(true);

        zoomBitmapView(doc, view, properties, getRhiMargin(properties["margin"]));
    }

    // the colors of the entities of an RHI based scene are resolved at
    // export time (color correction, background color): always regenerate
    // if the colors might have changed:
    if (properties["regen"]!==false ||
        properties["backgroundColor"] ||
        typeof(properties["colorCorrection"])!=="undefined") {

        scene.regenerate();
    }
    QCoreApplication.processEvents();

    if (isFunction(properties["initView"])) {
        properties["initView"](isNull(view) ? rhiView : view);
    }

    // render a frame and read it back from the GPU:
    var buffer = rhiView.grab().toImage();

    // restore the state of the view:
    rhiView.resize(oriWidth, oriHeight);
    if (!isNull(view)) {
        view.setExporting(oriExporting);
        view.setHairlineMinimumMode(oriHairlineMinimumMode);
        if (properties["backgroundColor"]) {
            view.setBackgroundColor(oriBackgroundColor);
        }
        if (typeof(properties["colorCorrection"])!=="undefined") {
            rhiView.setColorCorrectionOverride(oriColorCorrection);
        }
        rhiView.setOffset(oriOffset);
        rhiView.setFactor(oriFactor);
    }
    scene.regenerate();
    QCoreApplication.processEvents();

    if (isNull(buffer) || buffer.isNull()) {
        return undefined;
    }

    // the view renders in device pixels (e.g. twice the size of the view
    // on a high resolution screen):
    if (buffer.width()!==properties["width"] || buffer.height()!==properties["height"]) {
        buffer = buffer.scaled(properties["width"], properties["height"],
                               Qt.IgnoreAspectRatio, Qt.SmoothTransformation);
    }

    // RHI based views do not implement the color modes of the image based
    // view: convert the rendered image:
    if (properties["monochrome"]===true) {
        buffer = buffer.convertToFormat(QImage.Format_Mono);
    }
    else if (properties["grayscale"]===true) {
        buffer = buffer.convertToFormat(QImage.Format_Grayscale8);
    }

    return buffer;
}

/**
 * \return Margin to use for zooming an RHI based view.
 *
 * RGraphicsView.zoomTo doubles the margin if the high resolution graphics
 * view is enabled: the image of an image based view is in device pixels.
 * RHI based views navigate in device independent pixels (the frame is
 * scaled to the exported size after rendering): compensate, so the margin
 * is the same in the exported image.
 */
function getRhiMargin(margin) {
    if (RSettings.getHighResolutionGraphicsView()) {
        return Math.floor(margin / 2);
    }

    return margin;
}

/**
 * \return The RHI based view (RGraphicsViewRhi2D / RGraphicsViewRhi3D)
 * which renders the given scene or undefined if the given scene is
 * rendered by an image based view (RGraphicsSceneQt / RGraphicsViewImage)
 * or if RHI based views are not available (RHI3D plugin not installed).
 *
 * Note that the scene returned by RGraphicsView.getScene is always an
 * RGraphicsScene for an RHI based view (the script wrapper of the scene
 * of a plugin is not created for a pointer returned by a core class):
 * such a scene is detected through the views which are registered with
 * it (an RHI based 2D view registers the RGraphicsView adapter it owns).
 *
 * \param scene Graphics scene (RGraphicsSceneQt, RGraphicsSceneRhi3D, ...).
 * \param view Optional graphics view: the RHI based view itself or the
 * RGraphicsView adapter it owns.
 */
function getRhiViewOfScene(scene, view) {
    if (typeof(RGraphicsViewRhi2D)==="undefined") {
        // RHI3D plugin not available:
        return undefined;
    }

    var rhiView;

    if (!isNull(view)) {
        // the given view is the RHI based view itself:
        if (isOfType(view, RGraphicsViewRhi2D) || isOfType(view, RGraphicsViewRhi3D)) {
            return view;
        }

        // the given view is the adapter owned by an RHI based view:
        rhiView = RGraphicsViewRhi2D.getViewOf(view);
        if (!isNull(rhiView)) {
            return rhiView;
        }
    }

    // the scene is known to be an RHI based scene (e.g. created by the
    // caller of exportBitmap):
    if (isOfType(scene, RGraphicsSceneRhi3D)) {
        rhiView = scene.getView();
        if (!isNull(rhiView)) {
            return rhiView;
        }
    }

    // one of the views registered with the scene is the adapter of an RHI
    // based view:
    var views = scene.getGraphicsViews();
    for (var i=0; i<views.length; i++) {
        rhiView = RGraphicsViewRhi2D.getViewOf(views[i]);
        if (!isNull(rhiView)) {
            return rhiView;
        }
    }

    return undefined;
}
