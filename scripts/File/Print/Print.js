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

include("../File.js");
include("sprintf.js");
if (typeof(PrintPreview)=="undefined") {
    include("../PrintPreview/PrintPreview.js");
}
if (typeof(PageSettings)=="undefined") {
    include("scripts/Edit/DrawingPreferences/PageSettings/PageSettings.js");
}

/**
 * Used to print the given document with the settings stored inside the document
 * or the default settings.
 */
function Print(guiAction, document, view) {
    File.call(this, guiAction);

    this.document = document;
    this.view = view;

    // save and restore current view:
    this.saveView = false;

    if (!isNull(view)) {
        this.scene = view.getScene();
    }
}

Print.prototype = new File();

Print.defaultPrinter = new QPrinter();

Print.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    // switch to print preview:
    if (!PrintPreview.isRunning()) {
        var guiAction = RGuiAction.getByScriptFile("scripts/File/PrintPreview/PrintPreview.js");
        var action = new PrintPreview(guiAction);
        action.saveView = this.saveView;
        action.initialAction = "Print";
        var di = this.getDocumentInterface();
        di.setCurrentAction(action);
    }
    else {
        var pp = PrintPreview.getInstance();
        pp.slotPrint();
    }

    this.terminate();
};

/**
 * Prints the given document.
 */
Print.prototype.print = function(pdfFile) {
    var printer = new QPrinter(QPrinter.HighResolution);

    if (isString(pdfFile)) {
        printer.setOutputFormat(QPrinter.PdfFormat);
        printer.setOutputFileName(pdfFile);
    }

    var paperSizeEnum = Print.getPaperSizeEnum(this.document);
    if (paperSizeEnum!==QPrinter.Custom) {
        printer.setPaperSize(paperSizeEnum);
    }
    else {
        //printer.setPaperSize(QPrinter.Custom);
        var paperSizeMM = Print.getPaperSizeMM(this.document);
        printer.setPaperSize(paperSizeMM, QPrinter.Millimeter);
    }
    printer.setFullPage(true);
    printer.setOrientation(Print.getPageOrientationEnum(this.document));

    var colorMode = Print.getColorMode(this.document);
    if (colorMode == RGraphicsView.FullColor) {
        printer.setColorMode(QPrinter.Color);
    } else {
        printer.setColorMode(QPrinter.GrayScale);
    }

    // show printer dialog if we are not printing to a PDF file:
    if (!isString(pdfFile)) {
        Print.cancel = false;
        Print.printDialog = new QPrintDialog(printer, EAction.getMainWindow());

        // Mac, Win: exec() never returns without destroying the dialog through these signals:
        // Linux: make sure that cancel is caught correctly:
        Print.printDialog["accepted(QPrinter*)"].connect(
                    function() {
                        Print.cancel = false;
                        Print.printDialog.close();
                        if (RS.getSystemId()==="osx" && !RSettings.isQt(5)) {
                            Print.printDialog.destroy();
                        }
                    });

        Print.printDialog.rejected.connect(
                    function() {
                        Print.cancel = true;
                        Print.printDialog.close();
                        if (RS.getSystemId()==="osx" && !RSettings.isQt(5)) {
                            Print.printDialog.destroy();
                        }
                    });

        // Windows:
        if (RS.getSystemId()==="win") {
            // slot 'dummy' is never called:
            Print.printDialog.open(this, "dummy");
        }

        // Mac OS X, Linux, various other unices:
        else {
            Print.printDialog.exec();
        }

        if (Print.cancel===true) {
            printer.destroy();
            return;
        }
    }

    // set background color of view to match printing preference:
    var bgColor = this.view.getBackgroundColor();

    this.view.setBackgroundColor(Print.getBackgroundColor(this.document));
    this.view.setPrinting(true);

    var draftMode = false;
    var screenBasedLinetypes = false;
    if (!isNull(this.scene)) {
        draftMode = this.scene.getDraftMode();
        screenBasedLinetypes = this.scene.getScreenBasedLinetypes();

        this.scene.setDraftMode(false);
        this.scene.setScreenBasedLinetypes(false);
        this.scene.regenerate();
    }

    var painter = new QPainter();
    if (!painter.begin(printer)) {
        printer.destroy();
        return false;
    }

    // scale factor from drawing unit to mm:
    var unitScale = Print.getUnitScale(this.document);

    var widthInMM = printer.paperRect(QPrinter.Millimeter).width();
    var heightInMM = printer.paperRect(QPrinter.Millimeter).height();

    // factor from mm to printer unit:
    var printerFactor = new RVector(
        printer.paperRect().width() / widthInMM,
        printer.paperRect().height() / heightInMM
    );

    // printer calibration goes here (future use):
    //printerFactor.x *= 200/200.05;
    //printerFactor.y *= 280/280.30;

    this.view.setPrintPointSize(new RVector(1.0/printerFactor.x, 1.0/printerFactor.y));

    var scale = Print.getScale(this.document);
    var offset = Print.getOffset(this.document);

    var previousPixelSizeHint = this.scene.getPixelSizeHint();

    var widthInDrawingUnits = RUnit.convert(widthInMM, RS.Millimeter, this.document.getUnit());
    if (printer.paperRect().width()>0) {
        var pixelSizeHint = 1.0/printer.paperRect().width()*widthInDrawingUnits;
        pixelSizeHint = pixelSizeHint / scale;
        this.scene.setPixelSizeHint(pixelSizeHint);
    }

    // iterate through all pages and print the appropriate area
    var first = true;

    var pages = Print.getPages(this.document);
    for (var i = 0; i < pages.length; ++i) {
        // if this is not the first page, add new page:
        if (!first) {
            printer.newPage();
        }
        else {
            first = false;
        }

        var c = Print.getBackgroundColor(this.document);
        var qclr = new QColor(c.red(),c.green(),c.blue());
        if (!qclr.equals(new QColor(Qt.white))) {
            painter.setWorldTransform(new QTransform());
            painter.setBackground(new QBrush(qclr, Qt.SolidPattern));
            painter.eraseRect(printer.paperRect());
        }

        // paper size in mm:
        var paperBorder = Print.getPaperBorder(this.document, pages[i]);

        var paperBorderTransformed = Print.getTransformed(this.document, paperBorder);

        var pageBorderTransformed = Print.getTransformed(this.document, pages[i]);

        // scale paper border from mm to unit measures:
//        paperBorderTransformed.setRect(paperBorderTransformed.x()/unitScale,
//                                       paperBorderTransformed.y()/unitScale,
//                                       paperBorderTransformed.width()/unitScale,
//                                       paperBorderTransformed.height()/unitScale);

//        pageBorderTransformed.setRect(pageBorderTransformed.x()/unitScale,
//                                      pageBorderTransformed.y()/unitScale,
//                                      pageBorderTransformed.width()/unitScale,
//                                      pageBorderTransformed.height()/unitScale);

        // set up transform (TODO: move to function):
        var transform = new QTransform();
        // move zero to bottom left corner, set up X/Y axis:
        transform.scale(1, -1);

        // scale to printer units:
        transform.scale(printerFactor.x, printerFactor.y);

        transform.translate(-paperBorder.x(), -paperBorder.y()-paperBorder.height());

        // apply user defined offset and scale:
        transform.translate(-offset.x*scale*unitScale, -offset.y*scale*unitScale);
        transform.scale(scale, scale);

        // scale drawing unit to mm:
        transform.scale(unitScale, unitScale);

        painter.setWorldTransform(transform);

        this.printPage(painter, paperBorderTransformed);

        if (Print.getPrintCropMarks(this.document)) {
            Print.drawCropMarks(
                    this.document,
                    painter,
                    pageBorderTransformed,
                    true
            );
        }

        if (Print.getEnablePageTags()) {
            Print.drawPageTags(this.document, painter, i, pageBorderTransformed, true, printerFactor);
        }
    }

    painter.end();
    printer.destroy();

    this.scene.setPixelSizeHint(previousPixelSizeHint);

    this.scene.setScreenBasedLinetypes(screenBasedLinetypes);
    this.scene.setDraftMode(draftMode);
    this.scene.regenerate();

    this.view.setBackgroundColor(bgColor);
    this.view.setPrinting(false);

    return true;
};

/**
 * Prints a single page to the given printer. The area to print is given
 * as coordinates x/y and width/height.
 *
 * \param rect QRectF object that represents the page border.
 */
Print.prototype.printPage = function(painter, rect) {
    //var document = EAction.getDocument();
    //var mdiChild = EAction.getMdiChild();
    //var view = mdiChild.getLastKnownViewWithFocus();

    this.view.paintEntities(
        painter,
        new RBox(
            new RVector(rect.x(), rect.y()),
            new RVector(rect.x()+rect.width(), rect.y()+rect.height())
        )
    );
};

/**
 * \return Maximum extents of paper
 */
Print.getPaperBox = function(document) {
    //var document = this.getDocument();
    var pages = Print.getPages(document);
    var box = new RBox();

    for (var i=0; i<pages.length; ++i) {
        var paperBorder = Print.getPaperBorder(document, pages[i]);
        var paperBorderTransformed = Print.getTransformed(document, paperBorder);

        var paperBox = new RBox(paperBorderTransformed);
        if (!box.isValid()) {
            box = paperBox;
        }
        else {
            box.growToIncludeBox(paperBox);
        }
    }

    return box;
};

/**
 * Auto fit drawing to page size.
 */
Print.autoFitDrawing = function(document) {
    // drawing bounding box in drawing units:
    var bBox = document.getBoundingBox(true, true);
    Print.autoFitBox(document, bBox);
    Print.centerBox(document, bBox);
};

/**
 * Auto fit given box to page size.
 */
Print.autoFitBox = function(document, bBox) {
    var paperUnit = Print.getPaperUnit(document);

    // paper bounding box in drawing units, multiplied by scale:
    var pBox = Print.getPaperBox(document);

    var scale = Print.getScale(document);

    // margins in paper unit:
    var glueWidth = Print.getGlueMarginLeft(document) + Print.getGlueMarginRight(document);
    var glueHeight = Print.getGlueMarginTop(document) + Print.getGlueMarginBottom(document);
    glueWidth = RUnit.convert(glueWidth, paperUnit, document.getUnit());
    glueHeight = RUnit.convert(glueHeight, paperUnit, document.getUnit());

    var wf = undefined;
    var hf = undefined;
    if (bBox.getWidth()>1.0e-6) {
        wf = (pBox.getWidth() * scale - glueWidth) / bBox.getWidth();
    }
    if (bBox.getHeight()>1.0e-6) {
        hf = (pBox.getHeight() * scale - glueHeight) / bBox.getHeight();
    }
    var f = 1.0;
    if (!isNull(wf) && !isNull(hf)) {
        f = Math.min(wf, hf);
    }
    else if (!isNull(wf)) {
        f = wf;
    }
    else if (!isNull(hf)) {
        f = hf;
    }

    if (f<0) {
        f = 1.0;
    }

    Print.setScale(document, f);
    Print.centerBox(document, bBox);
};

Print.autoCenter = function(document) {
    var bBox = document.getBoundingBox(true, true);
    if (!bBox.isValid()) {
        return;
    }
    Print.centerBox(document, bBox);
};

Print.centerBox = function(document, bBox) {
    var paperUnit = Print.getPaperUnit(document);

    var glueLeft = Print.getGlueMarginLeft(document);
    glueLeft = RUnit.convert(glueLeft, paperUnit, document.getUnit());
    var glueRight = Print.getGlueMarginRight(document);
    glueRight = RUnit.convert(glueRight, paperUnit, document.getUnit());
    var glueTop = Print.getGlueMarginTop(document);
    glueTop = RUnit.convert(glueTop, paperUnit, document.getUnit());
    var glueBottom = Print.getGlueMarginBottom(document);
    glueBottom = RUnit.convert(glueBottom, paperUnit, document.getUnit());

    var glueWidth = glueLeft + glueRight;
    var glueHeight = glueTop + glueBottom;

    var pBox = Print.getPaperBox(document);
    var scale = Print.getScale(document);

    var w2 = (pBox.getWidth() - bBox.getWidth()) / 2;
    var h2 = (pBox.getHeight() - bBox.getHeight()) / 2;
    var dw = (glueRight - glueLeft) / scale;
    var dh = (glueTop - glueBottom) / scale;
    var offset = bBox.getMinimum().operator_subtract(new RVector(w2, h2));
    offset = offset.operator_add(new RVector(dw/2, dh/2));
    Print.setOffset(document, offset);
};

/**
 * Draws the crop marks for the given page.
 * \param painter QPainter object if we are printing, RPainterPath for print preview.
 */
Print.drawCropMarks = function(document, painter, border, printing) {
    var scale = Print.getScale(document);
    var unitScale = Print.getUnitScale(document);
    var colorMode = Print.getColorMode(document);
    var backgroundColor = Print.getBackgroundColor(document);
    var width = printing ? 0.1 / scale / unitScale : 1.5;

    var color = new QColor("darkBlue");
    if (colorMode == RGraphicsView.BlackWhite || colorMode == RGraphicsView.GrayScale) {
        if (backgroundColor.value() < 64) {
            color = new QColor("white");
        } else {
            color = new QColor("black");
        }
    }
    var pen = new QPen(new QBrush(color), width, Qt.SolidLine, Qt.FlatCap, Qt.MiterJoin);
    painter.setPen(pen);
    painter.setBrush(new QBrush(Qt.NoBrush));

    var lines = [];
    Print.pushCropMarkLines(document, lines, border.bottomLeft(), printing);
    Print.pushCropMarkLines(document, lines, border.topLeft(), printing);
    Print.pushCropMarkLines(document, lines, border.topRight(), printing);
    Print.pushCropMarkLines(document, lines, border.bottomRight(), printing);

    // printing:
    if (isFunction(painter.drawLinesF)) {
        painter.drawLinesF(lines);
    }

    // preview:
    else {
        for (var i=0; i<lines.length; ++i) {
            painter.moveTo(new RVector(lines[i].x1(), lines[i].y1()));
            painter.lineTo(new RVector(lines[i].x2(), lines[i].y2()));
        }
    }

};

/**
 * Helper function for drawCropMarks.
 */
Print.pushCropMarkLines = function(document, lineArray, center, printing) {
    var scale = Print.getScale(document);
    var unitScale = Print.getUnitScale(document);
    var l = printing ? 10 / 2 / scale / unitScale : 10/2;

    lineArray.push(new QLineF(center.x() - l, center.y(), center.x() + l, center.y()));
    lineArray.push(new QLineF(center.x(), center.y() - l, center.x(), center.y() + l));
};

/**
 * \return A printable ID for the page with the given index, e.g. "B6".
 */
Print.getPageId = function(document, index) {
    var columns = Print.getColumns(document);
    var column = index % columns;
    var row = Math.ceil((index + 1) / columns);
    var str = sprintf("%c%d", 65 + column, row);
    return str;
}

/**
 * Draws the page tags for printing (black, small, border area).
 * \param index page index
 * \param border page border geometry of the page
 * \param painter QPainter object if we are printing, RPainterPath for print preview.
 * \param printerFactor Factor from Millimeter to printer unit.
 */
Print.drawPageTags = function(document, painter, index, border, printing, printerFactor) {
    var font, fm, x, y, width, height;

    var path = new QPainterPath();
    
    if (isNull(printing)) {
        printing = false;
    }

    var backgroundColor = Print.getBackgroundColor(document);
    var scale = Print.getScale(document);

    var str = Print.getPageId(document, index);

    // border of visible area after gluing:
    var correctedBorder = border.translated(0,0);
    var top = correctedBorder.top();
    correctedBorder.setTop(correctedBorder.bottom());
    correctedBorder.setBottom(top);

    font = Print.getTagFont();
    font.setPointSizeF(1.0);
//    qDebug("TagFont: ", font);
//    if (printing) {
//        qDebug("TagFont: size A: ", font.pointSizeF());
//        //var sf = font.pointSizeF() / printerFactor.y / scale;
//        var sf = font.pointSizeF();
//        qDebug("sf 1: ", sf);
//        sf = font.pointSizeF() / 72.0 * 25.4;
//        qDebug("sf 2: ", sf);
//        sf = RUnit.convert(sf, RS.Millimeter, document.getUnit());
//        qDebug("sf 3: ", sf);
//        sf = sf / scale;
//        qDebug("sf 4: ", sf);
//        // convert point size to millimeter:
//        //sf = font.pointSizeF() / 72.0 * 25.4;
//        // scale millimeter by drawing scale:
//        //sf = sf * scale;
//        // convert millimeter to drawing unit:
//        //sf = sf / Print.getUnitScale(document);
//        // convert millimeter to printer units:
//        //sf /= printerFactor.y;
//        // convert printer unit to points:
//        //sf
//        //font.setPointSizeF(font.pointSizeF() / printerFactor.y / scale); // / Print.getUnitScale(document));
//        if (sf<0.5) {
//            sf = 0.5;
//        }
//        qDebug("sf 5: ", sf);
//        font.setPointSizeF(sf);
//        qDebug("TagFont: size B: ", font.pointSizeF());
//    }
//    else {
//        // 1pt = 1/72" ~= 0.3527 mm
//        font.setPointSizeF(font.pointSizeF() * (25.4 / 72)); // / Print.getUnitScale(document));
//    }
//    qDebug("TagFont: scaled: ", font);

//    if (printing) {
//        qDebug("window: ", painter.window());
//        qDebug("viewport: ", painter.viewport());
//    }

//    if (printing) {
//        path.moveTo(0,0);
//        path.lineTo(10,0);
//        path.lineTo(10,10);
//        path.lineTo(0,10);
//        path.lineTo(0,0);
//    }

    var sf = 1.0;
    // font size is given in points:
    sf *= Print.getTagFont().pointSizeF();
    // convert points to mm:
    sf = sf * 25.4 / 72;

    // font scaling for printing:
    if (printing) {
        // convert mm to drawing unit:
        sf = RUnit.convert(sf, RS.Millimeter, document.getUnit());
        // scale:
        sf /= scale;
        //sf = 1.0;
    }

    // font scaling for print preview:
    else {
        //sf = 25.4 / 72;
    }

    path.addText(0,0, font, str);

    // mirror text that is currently upside down:
    var t = new QTransform();
    t.scale(sf,-sf);
    path = t.map(path);

    var outside = (Print.getTagAlignment() == "Outside");

    width = path.boundingRect().width();
    height = path.boundingRect().height();
    //fm = new QFontMetricsF(font);
    //width = fm.width(str);
    //height = fm.height();
    //height = font.pointSizeF();
    //qDebug("width/height: ", width, height);
    //qDebug("printer factor: ", printerFactor.x, printerFactor.y);

    switch (Print.getTagPosition()) {
    case "Top":
    case "Bottom":
        x = (correctedBorder.left() + correctedBorder.right()) / 2 - width / 2;
        break;
    default:
    case "Left":
    case "TopLeft":
    case "BottomLeft":
        x = correctedBorder.left();
        if (outside) {
            x-=width*1.25;
        }
        break;
    case "Right":
    case "TopRight":
    case "BottomRight":
        x = correctedBorder.right() - width;
        if (outside) {
            x+=width*1.25;
        }
        break;
    }

    switch (Print.getTagPosition()) {
    case "Top":
    case "TopLeft":
    case "TopRight":
    default:
        y = correctedBorder.top();
        if (outside) {
            //y+=height*1.25;
        }
        else {
            y -= height*1.25;
        }
        break;
    case "Left":
    case "Right":
        y = (correctedBorder.top() + correctedBorder.bottom()) / 2 - height / 2;
        break;
    case "Bottom":
    case "BottomLeft":
    case "BottomRight":
        y = correctedBorder.bottom();
        if (outside) {
            y -= height*1.25;
        }
        break;
    }

    //qDebug("correctedBorder: ", correctedBorder);
    //qDebug("x,y: ", x, y);

    var color;
    if (backgroundColor.value() > 128) {
        color = new QColor("black");
    } else {
        color = new QColor("white");
    }

//    font = new QFont("Helvetica");
//    font.setPointSizeF(10.0);
//    x = 0;
//    y = 0;
    painter.setPen(new QPen(color));
    painter.setBrush(new QBrush(color));

    //var t = new QTransform();
    //t.scale(1.0,-1.0);
    //path = t.map(path);
    path.translate(x,y);

    if (printing) {
        //painter.setPen(new QPen(color));
        //painter.setFont(font);
        //painter.drawText(x, y, str);
        painter.drawPath(path);
    }
    else {
        //path.translate(x,y);
        painter.addPath(new RPainterPath(path));
    }

        //painter.setFont(font);
//        painter.drawText(
//                correctedBorder.adjusted(bo,bo,-bo,-bo),
//                alignment,
//                str,
//                new QRectF()
//        );
//    }

//    if (printing) {
//        painter.setTransform(savedTransform2);
//    }
};

/**
 * Called when the user accepts the print dialog
 * (OK, Preview, Save as PDF, ...).
 * Destroys the print dialog (required on OS X to continue execution of script).
 */
//Print.prototype.accept = function() {
//    this.cancel = false;
//    if (!isNull(Print.printDialog)) {
//        Print.printDialog.close();
//    }
//    //this.printDialog.destroy();
//};

/**
 * Called when the user cancels the print dialog.
 * Destroys the print dialog (required on OS X to continue execution of script).
 */
//Print.prototype.reject = function() {
//    this.cancel = true;
//    if (!isNull(Print.printDialog)) {
//        Print.printDialog.close();
//        Print.printDialog.destroy();
//    }
//};

/**
 * \return All pages (printable areas) as QRectF objects in Millimeter
 *      without any offset or scale applied.
 */
Print.getPages = function(document) {
    var paperUnit;
    if (!isNull(document)) {
        paperUnit = Print.getPaperUnit(document);
    }
    else {
        paperUnit = Print.getDefaultPaperUnit();
    }

    var glueWidth = Print.getGlueMarginLeft(document) + Print.getGlueMarginRight(document);
    var glueHeight = Print.getGlueMarginTop(document) + Print.getGlueMarginBottom(document);
    var glueMarginLeft = Print.getGlueMarginLeft(document);
    var glueMarginBottom = Print.getGlueMarginBottom(document);

    glueWidth = RUnit.convert(glueWidth, paperUnit, RS.Millimeter);
    glueHeight = RUnit.convert(glueHeight, paperUnit, RS.Millimeter);
    glueMarginLeft = RUnit.convert(glueMarginLeft, paperUnit, RS.Millimeter);
    glueMarginBottom = RUnit.convert(glueMarginBottom, paperUnit, RS.Millimeter);

    var ret = [];

    var w;
    var h;
    var paperSizeMM = Print.getPaperSizeMM(document);
    if (Print.getPageOrientationEnum(document) === QPrinter.Portrait) {
        w = paperSizeMM.width();
        h = paperSizeMM.height();
    } else {
        w = paperSizeMM.height();
        h = paperSizeMM.width();
    }

    var rows = Print.getRows(document);
    var columns = Print.getColumns(document);
    for (var r = rows-1; r >= 0; --r) {
        for (var c = 0; c < columns; ++c) {
            var rect =  new QRectF(
                    c * (w - glueWidth) + glueMarginLeft,
                    r * (h - glueHeight) + glueMarginBottom,
                    w - glueWidth,
                    h - glueHeight
            );
            ret.push(rect);
        }
    }

    return ret;
};

/**
 * \return Paper border for the given printable area in mm.
 * \param border QRectF rectangle.
 */
Print.getPaperBorder = function(document, border) {
    var paperUnit;
    if (!isNull(document)) {
        paperUnit = Print.getPaperUnit(document);
    }
    else {
        paperUnit = Print.getDefaultPaperUnit();
    }

    var glueMarginLeft = Print.getGlueMarginLeft(document);
    var glueMarginTop = Print.getGlueMarginTop(document);
    var glueMarginRight = Print.getGlueMarginRight(document);
    var glueMarginBottom = Print.getGlueMarginBottom(document);

    glueMarginLeft = RUnit.convert(glueMarginLeft, paperUnit, RS.Millimeter);
    glueMarginTop = RUnit.convert(glueMarginTop, paperUnit, RS.Millimeter);
    glueMarginRight = RUnit.convert(glueMarginRight, paperUnit, RS.Millimeter);
    glueMarginBottom = RUnit.convert(glueMarginBottom, paperUnit, RS.Millimeter);

    return border.adjusted(
            -glueMarginLeft,
            -glueMarginBottom,
            glueMarginRight,
            glueMarginTop
    );
};

/**
 * \return The given rectangle (QRectF) in Millimeter, transformed to the
 * model space unit and with the scale and offset used to print the given
 * document.
 */
Print.getTransformed = function(document, rect) {
    var unitScale = Print.getUnitScale(document);
    var scale = Print.getScale(document);
    var offset = Print.getOffset(document);

    var ret = rect.translated(0,0);
    ret.setLeft(ret.left()/scale/unitScale);
    ret.setRight(ret.right()/scale/unitScale);
    ret.setTop(ret.top()/scale/unitScale);
    ret.setBottom(ret.bottom()/scale/unitScale);
    ret = ret.translated(offset.x, offset.y);

    return ret;
};

Print.getColorMode = function(document) {
    var colorModeString = EAction.getValue("ColorSettings/ColorMode", "FullColor", document);
    return Print.getColorModeEnum(colorModeString);
};

Print.setColorMode = function(document, colorMode) {
    if (isString(colorMode)) {
        document.setVariable("ColorSettings/ColorMode", colorMode);
    }
    else {
        Print.setColorMode(document, Print.getColorModeString(colorMode));
    }
};

Print.getHairlineMode = function(document) {
    return EAction.getBoolValue("Print/HairlineMode", false, document);
};

Print.setHairlineMode = function(document, onOff) {
    document.setVariable("Print/HairlineMode", onOff);
};

/**
 * Converts the given color mode as string into a color mode enum
 * (RGraphicsView::ColorMode).
 */
Print.getColorModeEnum = function(colorModeString) {
    switch (colorModeString) {
    case "FullColor":
        return RGraphicsView.FullColor;
    case "Grayscale":
        return RGraphicsView.GrayScale;
    case "BlackWhite":
        return RGraphicsView.BlackWhite;
    default:
        return RGraphicsView.FullColor;
    }
};

/**
 * Converts the given color mode as enum (RGraphicsView::ColorMode) into a
 * color mode string as stored in a document as variable.
 */
Print.getColorModeString = function(colorModeEnum) {
    switch (colorModeEnum) {
    case RGraphicsView.FullColor:
        return "FullColor";
    case RGraphicsView.GrayScale:
        return "Grayscale";
    case RGraphicsView.BlackWhite:
        return "BlackWhite";
    default:
        return "FullColor";
    }
};

/**
 * \return Default page rect of default printer in paper units.
 */
Print.getDefaultPageRect = function(document, paperUnit) {
    var r = Print.defaultPrinter.pageRect(QPrinter.Millimeter);
    if (isNull(paperUnit)) {
        if (!isNull(document)) {
            paperUnit = Print.getPaperUnit(document);
        }
        else {
            paperUnit = Print.getDefaultPaperUnit();
        }
    }

    var x = RUnit.convert(r.x(), RS.Millimeter, paperUnit);
    var y = RUnit.convert(r.y(), RS.Millimeter, paperUnit);
    var w = RUnit.convert(r.width(), RS.Millimeter, paperUnit);
    var h = RUnit.convert(r.height(), RS.Millimeter, paperUnit);

    return new QRectF(x, y, w, h);
};

/**
 * \return Default paper rect of default printer in paper units.
 */
Print.getDefaultPaperRect = function(document, paperUnit) {
    var r = Print.defaultPrinter.paperRect(QPrinter.Millimeter);
    if (isNull(paperUnit)) {
        if (!isNull(document)) {
            paperUnit = Print.getPaperUnit(document);
        }
        else {
            paperUnit = Print.getDefaultPaperUnit();
        }
    }

    var x = RUnit.convert(r.x(), RS.Millimeter, paperUnit);
    var y = RUnit.convert(r.y(), RS.Millimeter, paperUnit);
    var w = RUnit.convert(r.width(), RS.Millimeter, paperUnit);
    var h = RUnit.convert(r.height(), RS.Millimeter, paperUnit);

    return new QRectF(x, y, w, h);
};

Print.getGlueMarginLeft = function(document) {
    return EAction.getDoubleValue("MultiPageSettings/GlueMarginsLeft", Print.getDefaultPrintMarginLeft(document), document);
};

Print.getDefaultPrintMarginLeft = function(document, paperUnit) {
    var pageRect = Print.getDefaultPageRect(document, paperUnit);
    return pageRect.left().toFixed(4);
};

Print.getGlueMarginTop = function(document) {
    return EAction.getDoubleValue( "MultiPageSettings/GlueMarginsTop", Print.getDefaultPrintMarginTop(document), document);
};

Print.getDefaultPrintMarginTop = function(document, paperUnit) {
    var pageRect = Print.getDefaultPageRect(document, paperUnit);
    return pageRect.top().toFixed(4);
};

Print.getGlueMarginRight = function(document) {
    return EAction.getDoubleValue( "MultiPageSettings/GlueMarginsRight", Print.getDefaultPrintMarginRight(document), document);
};

Print.getDefaultPrintMarginRight = function(document, paperUnit) {
    var paperRect = Print.getDefaultPaperRect(document, paperUnit);
    var pageRect = Print.getDefaultPageRect(document, paperUnit);
    return (paperRect.right() - pageRect.right()).toFixed(4);
};

Print.getGlueMarginBottom = function(document) {
    return EAction.getDoubleValue( "MultiPageSettings/GlueMarginsBottom", Print.getDefaultPrintMarginBottom(document), document);
};

Print.getDefaultPrintMarginBottom = function(document, paperUnit) {
    var paperRect = Print.getDefaultPaperRect(document, paperUnit);
    var pageRect = Print.getDefaultPageRect(document, paperUnit);
    return (paperRect.bottom() - pageRect.bottom()).toFixed(4);
};

Print.getOffset = function(document) {
    var x = EAction.getDoubleValue("PageSettings/OffsetX", 0, document);
    var y = EAction.getDoubleValue("PageSettings/OffsetY", 0, document);
//    x += Print.getGlueMarginLeft();
//    y += Print.getGlueMarginBottom();
    return new RVector(x, y);
};

Print.setOffset = function(document, offset) {
    document.setVariable("PageSettings/OffsetX", offset.x);
    document.setVariable("PageSettings/OffsetY", offset.y);
};

/**
 * \return Paper size in MM as QSizeF object.
 */
Print.getPaperSizeMM = function(document) {
    //var defaultPaperSizeMM = Print.defaultPrinter.paperSize(QPrinter.Millimeter);
    var wMM = RUnit.convert(Print.getPaperWidth(document), Print.getPaperUnit(document), RS.Millimeter);
    var hMM = RUnit.convert(Print.getPaperHeight(document), Print.getPaperUnit(document), RS.Millimeter);
    return new QSizeF(wMM, hMM);
};

/**
 * \return Default paper size in MM as QSizeF object from configuration file
 * or QPrinter.
 */
Print.getDefaultPaperSizeMM = function() {
    var defaultPaperSizeMM = Print.defaultPrinter.paperSize(QPrinter.Millimeter);

    var dwMM = defaultPaperSizeMM.width();
    var dhMM = defaultPaperSizeMM.height();

    // get w / h in paper unit from settings:
    var dw = RUnit.convert(dwMM, RS.Millimeter, Print.getDefaultPaperUnit());
    var dh = RUnit.convert(dhMM, RS.Millimeter, Print.getDefaultPaperUnit());
    var w = RSettings.getDoubleValue("PageSettings/PaperWidth", dw);
    var h = RSettings.getDoubleValue("PageSettings/PaperHeight", dh);

    // convert to mm:
    w = RUnit.convert(w, Print.getDefaultPaperUnit(), RS.Millimeter);
    h = RUnit.convert(h, Print.getDefaultPaperUnit(), RS.Millimeter);

    return new QSizeF(w, h);
};

/**
 * \return Paper width in PaperUnit.
 */
Print.getPaperWidth = function(document) {
    var defaultPaperSizeMM = Print.defaultPrinter.paperSize(QPrinter.Millimeter);
    var dwMM = defaultPaperSizeMM.width();
    var dw = RUnit.convert(dwMM, RS.Millimeter, Print.getPaperUnit(document));

    var w = EAction.getValue("PageSettings/PaperWidth", dw, document);

    // compat:
    if (isArray(w)) {
        w = w[0];
    }

    if (isString(w)) {
        w = parseFloat(w);
    }

    return w;
};

/**
 * \return Paper height in PaperUnit.
 */
Print.getPaperHeight = function(document) {
    var defaultPaperSizeMM = Print.defaultPrinter.paperSize(QPrinter.Millimeter);
    var dhMM = defaultPaperSizeMM.height();
    var dh = RUnit.convert(dhMM, RS.Millimeter, Print.getPaperUnit(document));

    var h = EAction.getValue("PageSettings/PaperHeight", dh, document);
    // compat:
    if (isArray(h)) {
        h = h[0];
    }

    if (isString(h)) {
        h = parseFloat(h);
    }

    return h;
};

/**
 * \return Paper unit enum.
 */
Print.getPaperUnit = function(document) {
    return EAction.getIntValue("UnitSettings/PaperUnit", RS.Millimeter, document);
};

Print.getDefaultPaperUnit = function() {
    return RSettings.getIntValue("UnitSettings/PaperUnit", RS.Millimeter);
};

Print.getPaperSizeEnum = function(document) {
    var paperSizeMM = Print.getPaperSizeMM(document);

    for (var i=0; i<PageSettings.paperSizes.length; ++i) {
        // paper[0]: name
        // paper[1]: QSizeF
        // paper[2]: QPrinter::PaperSize
        var paper = PageSettings.paperSizes[i];
        var sizeMM = paper[1];
        if (Math.abs(sizeMM.width()-paperSizeMM.width()) < 1.0e-2 &&
            Math.abs(sizeMM.height()-paperSizeMM.height()) < 1.0e-2) {

            return paper[2];
        }
    }

    return QPrinter.Custom;
};

/**
 * \return paper size name for given paper size.
 *
 * \param paperSizeMM QSizeF paper size in mm.
 */
Print.getPaperSizeNameFromSize = function(paperSizeMM) {
    for (var i=0; i<PageSettings.paperSizes.length; ++i) {
        // paper[0]: name
        // paper[1]: QSizeF
        // paper[2]: QPrinter::PaperSize
        var paper = PageSettings.paperSizes[i];
        var sizeMM = paper[1];
        var cw = sizeMM.width();
        var ch = sizeMM.height();
        var w = paperSizeMM.width();
        var h = paperSizeMM.height();
        if ((Math.abs(cw-w) < 1.0e-2 && Math.abs(ch-h) < 1.0e-2) ||
            (Math.abs(cw-h) < 1.0e-2 && Math.abs(ch-w) < 1.0e-2)) {

            //qDebug("found match: ", paper);
            //qDebug("found match: ", paper[0]);
            return paper[0];
        }
    }

    return "";
};

/**
 * \return paper size for given paper size name.
 *
 * \param paperSizeName paper size name (A4, letter, ...).
 */
Print.getPaperSizeFromSizeName = function(paperSizeName) {
    for (var i=0; i<PageSettings.paperSizes.length; ++i) {
        // paper[0]: name
        // paper[1]: QSizeF
        // paper[2]: QPrinter::PaperSize
        var paper = PageSettings.paperSizes[i];
        var sizeName = paper[0];
        var sizeNameAlt1 = "";
        var sizeNameAlt2 = "";

        if (sizeName.indexOf("ISO")===0) {
            sizeNameAlt1 = paper[0].replace("ISO ", "");
        }
        if (sizeName==="ANSI A (Letter)") {
            sizeName = "ANSI A";
            sizeNameAlt1 = "Letter";
        }
        if (sizeName==="ANSI B (Ledger, Tabloid)") {
            sizeName = "ANSI B";
            sizeNameAlt1 = "Ledger";
            sizeNameAlt2 = "Tabloid";
        }
        if (sizeName==="F4 (Folio, Foolscap)") {
            sizeName = "F4";
            sizeNameAlt1 = "Folio";
            sizeNameAlt2 = "Foolscap";
        }

        var sizeMM = paper[1];
        var cw = sizeMM.width();
        var ch = sizeMM.height();
        //var w = paperSizeMM.width();
        //var h = paperSizeMM.height();
        if (sizeName.toLowerCase()===paperSizeName.toLowerCase() ||
            sizeNameAlt1.toLowerCase()===paperSizeName.toLowerCase() ||
            sizeNameAlt2.toLowerCase()===paperSizeName.toLowerCase()) {
            //qDebug("found match: ", paper);
            //qDebug("found match: ", paper[0]);
            return paper[1];
        }
    }

    return new QSizeF();
};


/**
 * \return Paper size name (always based on paper size values).
 */
Print.getPaperSizeName = function(document) {
    var paperSizeMM = Print.getPaperSizeMM(document);
    var ret = Print.getPaperSizeNameFromSize(paperSizeMM);
    if (ret==="") {
        // return translated 'Custom':
        return PageSettings.paperSizes[0][0];
    }
    return ret;
};

/**
 * \return Default paper size name as configured (config file) or from QPrinter.
 */
Print.getDefaultPaperSizeName = function(document) {
    var paperSizeMM = Print.getDefaultPaperSizeMM();
    var ret = Print.getPaperSizeNameFromSize(paperSizeMM);
    if (ret==="") {
        // return translated 'Custom':
        return PageSettings.paperSizes[0][0];
    }
    return ret;
};

/**
 * \return Page orientation as QPrinter::Orientation enum.
 */
Print.getPageOrientationEnum = function(document) {
    var pageOrientationString = Print.getPageOrientationString(document);
    if (pageOrientationString==="Landscape") {
        return QPrinter.Landscape;
    }
    else {
        return QPrinter.Portrait;
    }
};

Print.getPageOrientationString = function(document) {
    return EAction.getValue("PageSettings/PageOrientation", "Portrait", document);
};

Print.setPageOrientationString = function(document, pageOrientation) {
    document.setVariable("PageSettings/PageOrientation", pageOrientation);
};

Print.setPageOrientationEnum = function(document, pageOrientation) {
    if (pageOrientation==QPrinter.Landscape) {
        Print.setPageOrientationString(document, "Landscape");
    }
    else {
        Print.setPageOrientationString(document, "Portrait");
    }
};

Print.getShowPaperBorders = function(document) {
    return EAction.getBoolValue("PageSettings/ShowPaperBorders", true, document);
};

Print.setShowPaperBorders = function(document, showPaperBorders) {
    document.setVariable("PageSettings/ShowPaperBorders", showPaperBorders);
};

//Print.getShowBoundingBox = function(document) {
//    return EAction.getBoolValue("PageSettings/ShowBoundingBox", false, document);
//};

Print.getPrintCropMarks = function(document) {
    return EAction.getBoolValue("MultiPageSettings/PrintCropMarks", true, document);
};

Print.setPrintCropMarks = function(document, printCropMarks) {
    document.setVariable("MultiPageSettings/PrintCropMarks", printCropMarks);
};

Print.getScaleString = function(document) {
    var str = EAction.getStringValue("PageSettings/Scale", "1:1", document);

    // round:
    if (/^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$/.test(str)) {
        var v = parseFloat(str);
        if (v>1) {
            str = sprintf("%.2f", v);
        }
        else if (v>0.1) {
            str = sprintf("%.3f", v);
        }
        else if (v>0.01) {
            str = sprintf("%.4f", v);
        }
        else if (v>0.001) {
            str = sprintf("%.5f", v);
        }
        else if (v>0.0001) {
            str = sprintf("%.6f", v);
        }
        else if (v>0.00001) {
            str = sprintf("%.7f", v);
        }
        else if (v>0.000001) {
            str = sprintf("%.8f", v);
        }
        else {
            str = sprintf("%.12f", v);
        }
    }

    return str;
};

/**
 * \return Drawing scale as factor.
 */
Print.getScale = function(document) {
    var scaleString = Print.getScaleString(document);
    return Print.parseScale(scaleString);
};

/**
 * \return Scale factor from drawing unit to mm.
 */
Print.getUnitScale = function(document) {
    return RUnit.convert(1.0, document.getUnit(), RS.Millimeter);
};

Print.setScale = function(document, scale) {
    this.setScaleString(document, scale.toString());
};

Print.setScaleString = function(document, scaleString) {
    document.setVariable("PageSettings/Scale", scaleString);
};

Print.getColumns = function(document) {
    return EAction.getIntValue("MultiPageSettings/Columns", 1, document);
};

Print.setColumns = function(document, columns) {
    document.setVariable("MultiPageSettings/Columns", columns);
};

Print.getRows = function(document) {
    return EAction.getIntValue("MultiPageSettings/Rows", 1, document);
};

Print.setRows = function(document, rows) {
    document.setVariable("MultiPageSettings/Rows", rows);
};

Print.getBackgroundColor = function(document) {
    // this might return a string or an RColor object:
    var color = EAction.getValue("ColorSettings/BackgroundColor", new RColor("white"), document);

    if (isOfType(color, RColor)) {
        return color;
    }
    else if (isString(color)) {
        var ret = new RColor(color);
        if (ret.isValid()) {
            return ret;
        }
        // invalid color name: default to white:
        return new RColor("white");
    }
    else {
        debugger;
        return new RColor("white");
    }
};

Print.getEnablePageTags = function(document) {
    return EAction.getBoolValue("PageTagSettings/EnablePageTags", false, document);
};

Print.getIdentifyPageTags = function(document) {
    return EAction.getBoolValue("PageTagSettings/IdentifyPageTags", false, document);
};

Print.getTagFont = function(document) {
    var ret = EAction.getValue("PageTagSettings/TagFont", new QFont(), document);
    if (isOfType(ret, QFont)) {
        return ret;
    }

    if (isString(ret)) {
        var f = new QFont();
        f.fromString(ret);
        return f;
    }

    qWarning("TagFont is not a valid font");
    return new QFont();
};

Print.getTagPosition = function(document) {
    return EAction.getValue("PageTagSettings/TagPosition", "TopLeft", document);
};

Print.getTagAlignment = function(document) {
    return EAction.getValue("PageTagSettings/TagAlignment", "Inside", document);
};

//Print.getPaperSizeMM = function(document) {
//    return EAction.getValue("PageSettings/PaperSizeMM", new QSizeF(210,297), document);
//}

/**
 * Parses the given scale string (e.g. "1:2") and returns the scale as number (e.g. 0.5).
 */
Print.parseScale = function(scaleString) {
    return RMath.parseScale(scaleString);
};

/*
*/
