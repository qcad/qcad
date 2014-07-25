function exportBitmap(doc, scene, fileName, properties) {
    var view = new RGraphicsViewImage();
    view.setScene(scene, false);

    view.setPaintOrigin(properties["origin"]==null ? false : properties["origin"]);
    view.setTextHeightThresholdOverride(0);
    view.setAntialiasing(properties["antialiasing"]==null ? true : properties["antialiasing"]);
    //qDebug("-a: ", properties["antialiasing"]==null ? true : properties["antialiasing"]);
    //view.setAntialiasing(true);

    if (properties["monochrome"]===true) {
        view.setColorMode(RGraphicsView.BlackWhite);
    }
    else if (properties["grayscale"]===true) {
        view.setColorMode(RGraphicsView.GrayScale);
    }

    if (properties["backgroundColor"]) {
        view.setBackgroundColor(properties["backgroundColor"]);
    }

    if (properties["resolution"]) {
        var bb = doc.getBoundingBox(true, true);
        properties["width"] = Math.round(bb.getWidth() * properties["resolution"] + 2 * properties["margin"]);
        properties["height"] = Math.round(bb.getHeight() * properties["resolution"] + 2 * properties["margin"]);
        //print("size: ", width, "x", height);
    }

    if (!properties["width"]) {
        properties["width"] = 640;
    }
    if (!properties["height"]) {
        properties["height"] = 480;
    }

    view.resizeImage(properties["width"], properties["height"]);

    view.autoZoom(properties["margin"]==null ? 20 : properties["margin"], true);

    //view.setAntialiasing(true);
    //view.setPaintOrigin(false);
    //view.setTextHeightThresholdOverride(0);

    // disabled: produces very thin lines, invisible for units >= Meter
    //view.setPrinting(true);

    //view.setBackgroundColor(properties.background);
    //view.resizeImage(properties.width, properties.height);

    //view.autoZoom(properties.margin);

    //di.regenerateScenes();
    scene.regenerate();

    // export file
    var buffer = view.getBuffer();

    scene.unregisterView(view);

    var iw = new QImageWriter(fileName);
    // always empty
    //qDebug("BitmapExport.js:", "exportBitmap(): format:", iw.format());
    var ext = new QFileInfo(fileName).suffix().toLowerCase();
    if (ext === "png") {
        iw.setQuality(9);
        //iw.setCompression(9);
    } else if (ext === "jpg" || ext === "jpeg") {
        iw.setQuality(properties["quality"]==null ? 100 : properties["quality"]);
    } else if (ext === "tif" || ext === "tiff") {
        iw.setCompression(1);
    } else if (ext === "bmp") {
        iw.setCompression(1);
    }

    //var appWin = EAction.getMainWindow();
    var ret;
    if (!iw.write(buffer)) {
        //print("Error: cannot save file: ", fileName);
        //print("Error: ", iw.errorString());
        ret = [false, iw.errorString()];
        //[false, qsTr("Error while generating Bitmap file '%1': %2")
        //            .arg(fileName).arg(iw.errorString())];
    } else {
        //print("Conversion finished.");
        ret = [true, ""];
        //[true, qsTr("Bitmap file has been exported to '%1'").arg(fileName);
    }
    iw.destroy();

    return ret;
}
