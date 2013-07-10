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

include("scripts/DefaultAction.js");
include("scripts/Edit/DrawingPreferences/PageSettings/PageSettings.js");
include("scripts/File/File.js");
include("scripts/File/Print/Print.js");

/**
 * Switches the current document to print preview mode.
 * In print preview mode, the paper is shown in the background of
 * the drawing.
 */
function PrintPreview(guiAction) {
    DefaultAction.call(this, guiAction);

    this.enableSlotPaperSizeChanged = false;
    
    this.setUiOptions(PrintPreview.includeBasePath + "/PrintPreview.ui");
    
    this.panningOffset = false;
    this.panOffsetOrigin = new RVector();

    this.updateDisabled = false;

    var bitmap = new QBitmap(PrintPreview.includeBasePath + "/PrintPreviewOffsetCursor.png", "PNG");
    var mask = new QBitmap(PrintPreview.includeBasePath + "/PrintPreviewOffsetCursorMask.png", "PNG");
    this.cursor = new QCursor(bitmap, mask, 15, 13);
    this.view = undefined;
}

PrintPreview.prototype = new DefaultAction();
PrintPreview.includeBasePath = includeBasePath;

if (typeof(printPreviewRunning)==="undefined") {
    printPreviewRunning = false;
}

/**
 * Additional states of PrintPreview compared with base class DefaultAction.
 */
PrintPreview.State = {
    SettingOffset : 100
};

PrintPreview.isRunning = function() {
    return printPreviewRunning;
};

PrintPreview.getInstance = function() {
    return printPreviewInstance;
};

PrintPreview.prototype.beginEvent = function() {
    if (PrintPreview.isRunning()) {
        // allows use of print preview button to close print preview:
        if (!isNull(printPreviewInstance)) {
            printPreviewInstance.terminate();
        }
        if (!isNull(this.guiAction)) {
            this.guiAction.setChecked(false);
        }
        this.terminate();
        return;
    }

    if (!isNull(this.guiAction)) {
        this.guiAction.setChecked(true);
    }

    printPreviewRunning = true;
    printPreviewInstance = this;

    var mdiChild = EAction.getMdiChild();
    this.view = mdiChild.getLastKnownViewWithFocus();

    DefaultAction.prototype.beginEvent.call(this);
    
    if (!isNull(this.view)) {
        var document = this.getDocument();
        this.bgColor = this.view.getBackgroundColor();

        // background needs to be set to white (or other user preference)
        // for printing / preview:
        this.view.setBackgroundColor(Print.getBackgroundColor(document));
        this.view.setColorMode(Print.getColorMode(document));
        this.view.setPrintPreview(true);

        this.updateBackgroundDecoration();

        // needed to update pattern scaling according to drawing scale:
        var di = EAction.getDocumentInterface();
        di.regenerateScenes();
    }

    var action = RGuiAction.getByScriptFile("scripts/Edit/DrawingPreferences/DrawingPreferences.js");
    action.triggered.connect(this, "updateBackgroundDecoration");

    if (this.initialAction==="Print") {
        this.slotPrint();
    }
    else if (this.initialAction==="PdfExport") {
        this.slotPdfExport();
    }
};

/**
 * Handles additional state changes for offset moving state.
 */
PrintPreview.prototype.setState = function(state) {
    DefaultAction.prototype.setState.call(this, state);

    if (this.state == PrintPreview.State.SettingOffset) {
        EAction.getDocumentInterface().setClickMode(RAction.PickingDisabled);
        EAction.getGraphicsView().setCursor(this.cursor);
        EAction.showMainTools();
        EAction.getMainWindow().setLeftMouseTip(qsTr("Drag to move paper"));
        EAction.getMainWindow().setRightMouseTip(qsTr("Done"));
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    var offsetButton = optionsToolBar.findChild("Offset");
    if (offsetButton) {
        offsetButton.checked = (this.state == PrintPreview.State.SettingOffset);
    }
};

PrintPreview.prototype.suspendEvent = function() {
    EAction.prototype.suspendEvent.call(this);
};

PrintPreview.prototype.finishEvent = function() {
    DefaultAction.prototype.finishEvent.call(this);
        
    if (!isNull(this.view)) {
        this.view.setPrintPreview(false);
        this.view.setBackgroundColor(this.bgColor);
        this.view.setColorMode(RGraphicsView.FullColor);
        this.view.clearBackground();

        // needed to update pattern scaling without using drawing scale:
        var di = EAction.getDocumentInterface();
        di.regenerateScenes();

        var action = RGuiAction.getByScriptFile("scripts/Edit/DrawingPreferences/DrawingPreferences.js");
        action.triggered.disconnect(this, "updateBackgroundDecoration");
    }

    printPreviewRunning = false;
    printPreviewInstance = undefined;
};

/**
 * Implements moving of paper (offset).
 */
PrintPreview.prototype.mousePressEvent = function(event) {
    if (this.state == PrintPreview.State.SettingOffset) {
        if (event.button() == Qt.LeftButton &&
            event.modifiers().valueOf() != Qt.ControlModifier.valueOf()) {

            this.panOffsetOrigin = event.getScreenPosition();
            this.panningOffset = true;
        }
    }
    else {
        DefaultAction.prototype.mousePressEvent.call(this, event);
    }
};

/**
 * Reimplemented from EAction to prevent that a right-click closes the
 * print preview.
 */
PrintPreview.prototype.mouseReleaseEvent = function(event) {
    if (event.button() == Qt.RightButton) {
        if (this.state!=DefaultAction.State.Neutral) {
            EAction.getDocumentInterface().clearPreview();
            EAction.getDocumentInterface().repaintViews();
            this.setState(DefaultAction.State.Neutral);
        }
    }
    else {
        DefaultAction.prototype.mouseReleaseEvent.call(this, event);
    }
};

/**
 * Implements moving of paper (offset).
 */
PrintPreview.prototype.mouseMoveEvent = function(event) {
    if (this.state != PrintPreview.State.SettingOffset) {
        DefaultAction.prototype.mouseMoveEvent.call(this, event);
    }

    if (event.buttons().valueOf() & Qt.LeftButton.valueOf() &&
        event.modifiers().valueOf() != Qt.ControlModifier.valueOf()) {

        if (!this.panningOffset) {
            return;
        }

        var panTarget = event.getScreenPosition();
        var panDelta = panTarget.operator_subtract(this.panOffsetOrigin);
        if (Math.abs(panDelta.x) < 1 && Math.abs(panDelta.y) < 1) {
            return;
        }
        this.panOffsetOrigin = panTarget;

        var document = this.getDocument();
        var offset = Print.getOffset(document);
        offset.x += this.view.mapDistanceFromView(panDelta.x);
        offset.y -= this.view.mapDistanceFromView(panDelta.y);

        // update document variables
        Print.setOffset(document, offset);

        this.updateBackgroundTransform();

        this.view.regenerate();
    }
};

/**
 * Reimplementation from EAction. Implements initialization of options
 * toolbar from member variables.
 */
PrintPreview.prototype.showUiOptions = function(resume) {
    this.updateDisabled = true;
    EAction.prototype.showUiOptions.call(this, resume);
    this.updateDisabled = false;

    var optionsToolBar = EAction.getOptionsToolBar();
    var widgets = getWidgets(optionsToolBar);

    var document = this.getDocument();
    var scaleString = Print.getScaleString(document);

    this.initScaleCombo();

    // update option toolbar widgets
    widgets["ShowPaperBorders"].blockSignals(true);
    widgets["ShowPaperBorders"].checked = Print.getShowPaperBorders(document);
    widgets["ShowPaperBorders"].blockSignals(false);

    widgets["PrintCropMarks"].blockSignals(true);
    widgets["PrintCropMarks"].checked = Print.getPrintCropMarks(document);
    widgets["PrintCropMarks"].blockSignals(false);

    var scaleCombo = widgets["Scale"];
    scaleCombo.blockSignals(true);
    scaleCombo.setEditText(scaleString);
    this.slotScaleChanged(scaleString);
    scaleCombo.blockSignals(false);
    
    var action = RGuiAction.getByScriptFile("scripts/Edit/DrawingPreferences/DrawingPreferences.js");
    widgets["ShowMoreOptions"].setDefaultAction(action);

    switch(Print.getColorMode(document)) {
    case RGraphicsView.FullColor:
        widgets["FullColor"].blockSignals(true);
        widgets["FullColor"].checked=true;
        widgets["FullColor"].blockSignals(false);
        break;
    case RGraphicsView.GrayScale:
        widgets["Grayscale"].blockSignals(true);
        widgets["Grayscale"].checked=true;
        widgets["Grayscale"].blockSignals(false);
        break;
    case RGraphicsView.BlackWhite:
        widgets["BlackWhite"].blockSignals(true);
        widgets["BlackWhite"].checked=true;
        widgets["BlackWhite"].blockSignals(false);
        break;
    }
    
    widgets["Portrait"].blockSignals(true);
    widgets["Landscape"].blockSignals(true);
    if (Print.getPageOrientationEnum() == QPrinter.Portrait) {
        widgets["Portrait"].checked=true;
    } else {
        widgets["Landscape"].checked=true;
    }
    widgets["Landscape"].blockSignals(false);
    widgets["Portrait"].blockSignals(false);
};

/**
 * Initializes the scale combo box in the options toolbar with defaults.
 */
PrintPreview.prototype.initUiOptions = function(resume) {
    this.initScaleCombo();
};

PrintPreview.prototype.initScaleCombo = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleCombo = optionsToolBar.findChild("Scale");
    scaleCombo.blockSignals(true);
    var prev = scaleCombo.currentText;
    scaleCombo.clear();
    var scales = this.getScales();
    for (var i=0; i<scales.length; ++i) {
        scaleCombo.addItem(scales[i]);
    }
    scaleCombo.currentText = prev;
    scaleCombo.blockSignals(false);
};

PrintPreview.prototype.hideUiOptions = function() {
    EAction.prototype.hideUiOptions.call(this, false);
};

/**
 * Called to update the background decoration (paper borders) if the scale
 * or paper settings change.
 */
PrintPreview.prototype.updateBackgroundDecoration = function() {
    this.view.clearBackground();

    var document = this.getDocument();
    var pages = Print.getPages(document);
    var backgroundColor = Print.getBackgroundColor(document);
    var i, color, path;

    if (pages.length===0) {
        qWarning("PrintPreview.prototype.updateBackgroundDecoration: no pages");
        return;
    }

    path = new RPainterPath();
    path.setPen(new QPen(Qt.NoPen));
    path.setBrush(new QBrush(new QColor("lightgray")));
    path.addRect(new QRectF(-1.0e8, -1.0e8, 2.0e8, 2.0e8));
    this.view.addToBackground(path);

    // page border with shadow
    if (Print.getShowPaperBorders(document)) {
        // shadow
        for (i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            path.setPen(new QPen(Qt.NoPen));
            path.setBrush(new QBrush(new QColor("gray")));
            this.drawShadow(path, pages[i]);
            this.view.addToBackground(path);
        }

        // paper background
        for (i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            path.setPen(new QPen(Qt.NoPen));
            color = new QColor(backgroundColor.red(), backgroundColor.green(),
                    backgroundColor.blue());
            path.setBrush(new QBrush(color));
            this.drawPaper(path, pages[i]);
            this.view.addToBackground(path);
        }

        // paper border
        for (i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            path.setPen(new QPen(new QColor(0xc8, 0xc8, 0xc8)));
            path.setBrush(new QBrush(Qt.NoBrush));
            this.drawPaper(path, pages[i]);
            this.view.addToBackground(path);
        }
    }

    // glue margins and page borders as blue rectangle:
    path = new RPainterPath();
    path.setPen(new QPen(new QColor(0x84, 0x84, 0xff)));
    if (!Print.getShowPaperBorders(document)) {
        color = new QColor(backgroundColor.red(), backgroundColor.green(),
                backgroundColor.blue());
        path.setBrush(new QBrush(color));
    } else {
        path.setBrush(new QBrush(Qt.NoBrush));
    }

    if (pages.length===0) {
        qWarning("PrintPreview.js: no pages");
    }

    for (i = 0; i < pages.length; ++i) {
        this.drawGlueMargins(path, pages[i]);
    }
    this.view.addToBackground(path);

    // TODO: hook for page tags
    this.addDecorations(pages);

    // crop marks
    if (Print.getPrintCropMarks(document)) {
        for ( i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            Print.drawCropMarks(document, path, pages[i], false);
            this.view.addToBackground(path);
        }
    }

    this.view.regenerate(true);
};

/**
 * Overwritable hook to add more decorations to the print preview.
 */
PrintPreview.prototype.addDecorations = function(pages) {};

/**
 * Updates the background decoration transformation.
 */
PrintPreview.prototype.updateBackgroundTransform = function() {
    var document = EAction.getDocument();
    var scale = Print.getScale(document);
    var offset = Print.getOffset(document);

    // the smaller the scale, the bigger the paper is shown,
    // relative to the drawing:
    var unitScale = RUnit.convert(1.0, RS.Millimeter, document.getUnit());
    var factor = 1.0 / scale * unitScale;

    this.view.setBackgroundTransform(factor, offset);
};

/**
 * Draws the paper border for the given page.
 */
PrintPreview.prototype.drawPaper = function(path, border) {
    var document = EAction.getDocument();
    var paperBorder = Print.getPaperBorder(document, border);
    if (!paperBorder.isValid()) {
        return;
    }
    path.addRect(paperBorder);
};

/**
 * Draws the glue margins for the given page.
 */
PrintPreview.prototype.drawGlueMargins = function(path, border) {
    if (!border.isValid()) {
        return;
    }
    path.addRect(border);
};

/**
 * Draws the shadow for the given page.
 */
PrintPreview.prototype.drawShadow = function(path, border) {
    var document = EAction.getDocument();
    var paper = Print.getPaperBorder(document, border);
    var offset = Print.getPaperSizeMM(document).width() * 0.02;
    var shadow = paper.adjusted(offset, -offset, offset, -offset);
    if (!shadow.isValid()) {
        return;
    }
    path.addRect(shadow);
};

PrintPreview.prototype.slotPdfExport = function() {
    PrintPreview.slotPdfExport();
};

/**
 * Called when user clicks the PDF export button in the options toolbar.
 */
PrintPreview.slotPdfExport = function() {
    var appWin = EAction.getMainWindow();
    var fileName = EAction.getDocument().getFileName();
    var initialFileName = QDir.homePath();
    if (fileName!=="") {
        var fileInfo = new QFileInfo(fileName);
        initialFileName = fileInfo.absoluteFilePath();
    }

    var filters = [ "PDF File (*.pdf)" ];

    var ret = File.getSaveFileName(appWin, qsTr("Export to PDF"),
                   initialFileName, filters);

    if (isNull(ret)) {
        return;
    }

    var pdfFile = ret[0];

    appWin.handleUserMessage(qsTr("Exporting to %1...").arg(pdfFile));

    PrintPreview.slotPrint(pdfFile);

    appWin.handleUserMessage(qsTr("Export complete: %1").arg(pdfFile));
};

PrintPreview.prototype.slotPrint = function(pdfFile) {
    PrintPreview.slotPrint(pdfFile);
};

/**
 * Prints the drawing or exports it to the given PDF file.
 */
PrintPreview.slotPrint = function(pdfFile) {
    var mdiChild = EAction.getMdiChild();
    var view = mdiChild.getLastKnownViewWithFocus();
    var print = new Print(undefined, EAction.getDocument(), view);
    print.print(pdfFile);
};

/**
 * Called whenever the user changes the drawing scale in the print preview.
 */
PrintPreview.prototype.slotScaleChanged = function(scaleString) {
    if (this.updateDisabled===true) {
        return;
    }

    var document = this.getDocument();

    if (isNull(document) || this.updateDisabled===true) {
        return;
    }

    Print.setScaleString(document, scaleString);

    this.updateBackgroundTransform();

    // update pattern scale accordint to drawing scale:
    var di = EAction.getDocumentInterface();
    di.regenerateScenes();
};

PrintPreview.setScale = function(document, scale) {
    PrintPreview.setScaleString(document, sprintf("%.6f", scale));
};

PrintPreview.setScaleString = function(document, scaleString) {
    Print.setScaleString(document, scaleString);

    PrintPreview.updateScaleString(document);
};

PrintPreview.updateScaleString = function(document) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleCombo = optionsToolBar.findChild("Scale");
    if (Print.getScale(document) != RMath.parseScale(scaleCombo.currentText)) {
        scaleCombo.blockSignals(true);
        scaleCombo.setEditText(Print.getScaleString());
        scaleCombo.blockSignals(false);
    }
};

/**
 * Triggered by the offset tool button in the options toolbar.
 * Activates / deactivates the offset tool.
 */
PrintPreview.prototype.slotOffsetChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }

    if (checked) {
        this.setState(PrintPreview.State.SettingOffset);
    }
    else {
        this.setState(DefaultAction.State.Neutral);
    }
};

/**
 * Triggered by the "Done" button in the options toolbar.
 * Terminates this action and returns to normal drawing mode.
 */
PrintPreview.prototype.slotDone = function() {
    this.terminate();
};

/**
 * Triggered by the b/w button in the options toolbar.
 * Activates / deactivates the black white mode.
 */
PrintPreview.prototype.slotFullColorChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    Print.setColorMode(EAction.getDocument(), RGraphicsView.FullColor);
    this.colorModeUpdate();
};

PrintPreview.prototype.slotBlackWhiteChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    Print.setColorMode(EAction.getDocument(), RGraphicsView.BlackWhite);
    this.colorModeUpdate();
};

PrintPreview.prototype.slotGrayscaleChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    Print.setColorMode(EAction.getDocument(), RGraphicsView.GrayScale);
    this.colorModeUpdate();
};

PrintPreview.prototype.colorModeUpdate = function() {
    if (!isNull(this.view)) {
        this.view.setColorMode(Print.getColorMode());
        this.view.regenerate(true);
    }    
};

/**
 * Page borders toggled in options toolbar.
 */
PrintPreview.prototype.slotShowPaperBordersChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    var document = EAction.getDocument();
    Print.setShowPaperBorders(document, checked);

    this.updateBackgroundDecoration();
};

/**
 * Crop marks toggled in options toolbar.
 */
PrintPreview.prototype.slotPrintCropMarksChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    var document = EAction.getDocument();
    Print.setPrintCropMarks(document, checked);

    this.updateBackgroundDecoration();
};

/**
 * Auto fit drawing button clicked in options toolbar.
 */
PrintPreview.prototype.slotAutoFitDrawing = function() {
    var document = this.getDocument();
    Print.autoFitDrawing(document);
    PrintPreview.updateScaleString(document);

    // needed to update pattern scaling according to drawing scale:
    var di = this.getDocumentInterface();
    di.regenerateScenes();

    this.updateBackgroundTransform();
    this.slotAutoZoomToPage();
    this.updateBackgroundDecoration();
};

PrintPreview.prototype.slotAutoCenter = function() {
    Print.autoCenter(this.getDocument());

    this.updateBackgroundTransform();
    this.slotAutoZoomToPage();
    this.updateBackgroundDecoration();
};

PrintPreview.prototype.slotPortraitChanged = function() {
    if (this.updateDisabled===true) {
        return;
    }
    var document = this.getDocument();
    Print.setPageOrientationEnum(document, QPrinter.Portrait);

    this.updateBackgroundDecoration();
    this.slotAutoZoomToPage();
};

PrintPreview.prototype.slotLandscapeChanged = function() {
    if (this.updateDisabled===true) {
        return;
    }
    var document = this.getDocument();
    Print.setPageOrientationEnum(document, QPrinter.Landscape);

    this.updateBackgroundDecoration();
    this.slotAutoZoomToPage();
};

/**
 * \return Maximum extents of paper
 */
PrintPreview.prototype.getPaperBox = function() {
    return Print.getPaperBox(this.getDocument());
};

PrintPreview.prototype.slotAutoZoomToPage = function() {
    if (!isNull(this.view)) {
        var pBox = this.getPaperBox();
        this.view.zoomTo(pBox, 10);
    }
};

