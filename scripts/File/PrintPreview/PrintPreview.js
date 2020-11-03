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

include("scripts/Edit/DrawingPreferences/PageSettings/PageSettings.js");
include("scripts/File/File.js");
include("scripts/File/NewFile/NewFile.js");
include("scripts/File/Print/Print.js");
include("scripts/sprintf.js");

/**
 * Switches the current document to print preview mode.
 * In print preview mode, the paper is shown in the background of
 * the drawing.
 */
function PrintPreview(guiAction) {
    EAction.call(this, guiAction);
}

PrintPreview.prototype = new EAction();
PrintPreview.includeBasePath = includeBasePath;
PrintPreview.instance = undefined;

PrintPreview.getInstance = function() {
    return PrintPreview.instance;
};

PrintPreview.isRunning = function() {
    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return false;
    }

    var a = di.getDefaultAction();
    var ga = a.getGuiAction();
    if (isNull(ga)) {
        return true;
    }
    else {
        return false;
    }
};

/**
 * Starts the print preview.
 */
PrintPreview.start = function(initialAction, instance) {
    var di = EAction.getDocumentInterface();
    var a = di.getDefaultAction();
    a.finishEvent();
    if (isNull(instance)) {
        PrintPreview.instance = new PrintPreviewImpl();
    }
    else {
        PrintPreview.instance = instance;
    }
    if (!isNull(initialAction)) {
        PrintPreview.instance.initialAction = initialAction;
    }
    di.setDefaultAction(PrintPreview.instance);

    var ga = RGuiAction.getByScriptFile("scripts/File/PrintPreview/PrintPreview.js")
    if (!isNull(ga)) {
        ga.setChecked(true);
    }
};

/**
 * Exits the print preview.
 */
PrintPreview.exit = function() {
    var di = EAction.getDocumentInterface();
    var a = di.getDefaultAction();
    a.finishEvent();
    NewFile.setupDefaultAction(di);

    var ga = RGuiAction.getByScriptFile("scripts/File/PrintPreview/PrintPreview.js")
    if (!isNull(ga)) {
        ga.setChecked(false);
    }
};

PrintPreview.prototype.beginEvent = function() {
    if (PrintPreview.isRunning()) {
        // exit print preview:
        PrintPreview.exit();
    }
    else {
        // start print preview:
        PrintPreview.start();
    }

    this.terminate();
};



/**
 * Implementation of interactive print preview action.
 * Intended to be used as default action.
 */
function PrintPreviewImpl(guiAction) {
    // parent class can be DefaultAction or other configured
    // default action:
    var defaultActionClass = NewFile.getDefaultActionClass();
    this.parentClass = global[defaultActionClass];

    this.parentClass.call(this, guiAction);

    this.enableSlotPaperSizeChanged = false;

    this.setUiOptions(PrintPreviewImpl.includeBasePath + "/PrintPreview.ui");

    this.panningOffset = false;
    this.panOffsetOrigin = new RVector();

    this.updateDisabled = false;

    var bitmap = new QBitmap(PrintPreviewImpl.includeBasePath + "/PrintPreviewOffsetCursor.png", "PNG");
    var mask = new QBitmap(PrintPreviewImpl.includeBasePath + "/PrintPreviewOffsetCursorMask.png", "PNG");
    this.cursor = new QCursor(bitmap, mask, 15, 13);
    this.view = undefined;
    this.saveView = false;
    this.savedScale = undefined;
    this.savedOffset = undefined;
    this.savedColumns = undefined;
    this.savedRows = undefined;

    this.optOutRelativeZeroResume = true;
}

PrintPreviewImpl.prototype = NewFile.getDefaultAction(false);
PrintPreviewImpl.includeBasePath = includeBasePath;

PrintPreviewImpl.State = {
    SettingOffset : 100
};

PrintPreviewImpl.prototype.beginEvent = function() {
    var di = this.getDocumentInterface();

    var appWin = RMainWindowQt.getMainWindow();
    var initialZoom = appWin.property("PrintPreview/InitialZoom");

    if (initialZoom==="View") {
        this.savedScale = Print.getScale(this.getDocument());
        this.savedOffset = Print.getOffset(this.getDocument());
        this.savedColumns = Print.getColumns(this.getDocument());
        this.savedRows = Print.getRows(this.getDocument());
        this.saveView = true;
    }

//    if (!isNull(this.guiAction)) {
//        this.guiAction.setChecked(true);
//    }

    // globals:
    //PrintPreview.setRunning(true);
    //PrintPreview.setInstance(this);

    var mdiChild = EAction.getMdiChild();
    this.view = mdiChild.getLastKnownViewWithFocus();

    this.parentClass.prototype.beginEvent.call(this);

    if (!isNull(this.view)) {
        var document = this.getDocument();
        this.bgColor = this.view.getBackgroundColor();

        this.updateBackgroundDecoration();

        if (!isNull(this.view.getScene())) {

            if (RSettings.getBoolValue("GraphicsView/AutoSwitchLinetypes", false)===true) {
                this.view.getScene().setScreenBasedLinetypes(false);
                var ltModeAction = RGuiAction.getByScriptFile("scripts/View/LinetypeMode/LinetypeMode.js");
                ltModeAction.setChecked(false);
            }
        }

        // needed to update pattern scaling according to drawing scale:
        di.regenerateScenes();
    }

    var action = RGuiAction.getByScriptFile("scripts/Edit/DrawingPreferences/DrawingPreferences.js");
    action.triggered.connect(this, "updateBackgroundDecoration");

    if (initialZoom==="Auto") {
        this.slotAutoFitDrawing();
    }
    else if (initialZoom==="View") {
        Print.setColumns(di, 1);
        Print.setRows(di, 1);
        this.slotAutoFitBox(this.view.getBox());
    }

    if (this.initialAction==="Print") {
        this.slotPrint();
    }
    else if (this.initialAction==="PdfExport") {
        this.slotPdfExport();
    }

    // create listener to update preview when preferences changed:
    this.pAdapter = new RPreferencesListenerAdapter();
    appWin.addPreferencesListener(this.pAdapter);
    this.pAdapter.preferencesUpdated.connect(this, "updateFromPreferences");

    this.bAdapter = new RBlockListenerAdapter();
    appWin.addBlockListener(this.bAdapter);
    this.bAdapter.blocksUpdated.connect(this, "updateBackgroundTransform");
    this.bAdapter.currentBlockSet.connect(this, "updateBackgroundTransform");
    this.bAdapter.blocksUpdated.connect(this, "updateBackgroundDecoration");
    this.bAdapter.currentBlockSet.connect(this, "updateBackgroundDecoration");
};

/**
 * Handles additional state changes for offset moving state.
 */
PrintPreviewImpl.prototype.setState = function(state) {
    this.parentClass.prototype.setState.call(this, state);

    if (this.state === PrintPreviewImpl.State.SettingOffset) {
        this.getDocumentInterface().setClickMode(RAction.PickingDisabled);
        this.setCursor(this.cursor, "PrintPreviewOffsetCursor");
        EAction.showMainTools();
        EAction.getMainWindow().setLeftMouseTip(qsTr("Drag to move paper"));
        EAction.getMainWindow().setRightMouseTip(qsTr("Done"));
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    var offsetButton = optionsToolBar.findChild("Offset");
    if (offsetButton) {
        offsetButton.checked = (this.state == PrintPreviewImpl.State.SettingOffset);
    }
};

PrintPreviewImpl.prototype.suspendEvent = function() {
    EAction.prototype.suspendEvent.call(this);
};

PrintPreviewImpl.prototype.finishEvent = function() {
    this.parentClass.prototype.finishEvent.call(this);
    var di = this.getDocumentInterface();

    var appWin = RMainWindowQt.getMainWindow();
    var initialZoom = appWin.property("PrintPreview/InitialZoom");

    if (!isNull(this.view)) {
        this.view.setPrintPreview(false);
        this.view.setBackgroundColor(this.bgColor);
        this.view.setColorMode(RGraphicsView.FullColor);
        this.view.clearBackground();

        if (!isNull(this.view.getScene())) {
            if (RSettings.getBoolValue("GraphicsView/AutoSwitchLinetypes", false)===true) {
                this.view.getScene().setScreenBasedLinetypes(true);
                var ltModeAction = RGuiAction.getByScriptFile("scripts/View/LinetypeMode/LinetypeMode.js");
                ltModeAction.setChecked(true);
            }
        }

        // needed to update pattern scaling without using drawing scale:
        if (!isNull(di)) {
            di.regenerateScenes();
        }

        var action = RGuiAction.getByScriptFile("scripts/Edit/DrawingPreferences/DrawingPreferences.js");
        action.triggered.disconnect(this, "updateBackgroundDecoration");
    }

    //PrintPreviewImpl.setRunning(false);
    //PrintPreviewImpl.setInstance(undefined);

    if (this.saveView===true) {
        if (!isNull(this.savedScale)) {
            Print.setScale(di, this.savedScale);
        }
        if (!isNull(this.savedOffset)) {
            Print.setOffset(di, this.savedOffset);
        }
        if (!isNull(this.savedColumns)) {
            Print.setColumns(di, this.savedColumns);
        }
        if (!isNull(this.savedRows)) {
            Print.setRows(di, this.savedRows);
        }
    }

    if (!isNull(this.pAdapter)) {
        appWin.removePreferencesListener(this.pAdapter);
    }
    if (!isNull(this.bAdapter)) {
        appWin.removeBlockListener(this.bAdapter);
    }
};

/**
 * Implements moving of paper (offset).
 */
PrintPreviewImpl.prototype.mousePressEvent = function(event) {
    if (this.state === PrintPreviewImpl.State.SettingOffset) {
        if (event.button() == Qt.LeftButton &&
            event.modifiers().valueOf() != Qt.ControlModifier.valueOf()) {

            this.panOffsetOrigin = event.getScreenPosition();
            this.panningOffset = true;
        }
    }
    else {
        this.parentClass.prototype.mousePressEvent.call(this, event);
    }
};

/**
 * Reimplemented from EAction to prevent that a right-click closes the
 * print preview.
 */
//PrintPreviewImpl.prototype.mouseReleaseEvent = function(event) {
//    if (event.button() == Qt.RightButton) {
//        if (this.state!=DefaultAction.State.Neutral) {
//            EAction.getDocumentInterface().clearPreview();
//            EAction.getDocumentInterface().repaintViews();
//            this.setState(DefaultAction.State.Neutral);
//        }
//    }
//    else {
//        this.parentClass.prototype.mouseReleaseEvent.call(this, event);
//    }
//};

/**
 * Implements moving of paper (offset).
 */
PrintPreviewImpl.prototype.mouseMoveEvent = function(event) {
    if (this.state !== PrintPreviewImpl.State.SettingOffset) {
        this.parentClass.prototype.mouseMoveEvent.call(this, event);
        return;
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

        var di = this.getDocumentInterface();
        var document = di.getDocument();
        var offset = Print.getOffset(document);
        offset.x += this.view.mapDistanceFromView(panDelta.x);
        offset.y -= this.view.mapDistanceFromView(panDelta.y);

        // update document variables
        Print.setOffset(di, offset);

        this.updateBackgroundTransform();

        this.view.regenerate();
    }
};

/**
 * Reimplementation from EAction. Implements initialization of options
 * toolbar from member variables.
 */
PrintPreviewImpl.prototype.showUiOptions = function(resume) {
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

    if (Print.getHairlineMode(document)) {
        if (!isNull(widgets["Hairline"])) {
            widgets["Hairline"].blockSignals(true);
            widgets["Hairline"].checked=true;
            widgets["Hairline"].blockSignals(false);
        }
    }

    widgets["Portrait"].blockSignals(true);
    widgets["Landscape"].blockSignals(true);
    if (Print.getPageOrientationEnum(document).valueOf() === QPrinter.Portrait.valueOf()) {
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
PrintPreviewImpl.prototype.initUiOptions = function(resume, optionsToolBar) {
    this.initScaleCombo();
};

PrintPreviewImpl.prototype.initScaleCombo = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleCombo = optionsToolBar.findChild("Scale");
    scaleCombo.blockSignals(true);
    var prev = scaleCombo.currentText;
    scaleCombo.clear();
    var scales = this.getScales();
    for (var i=0; i<scales.length; ++i) {
        scaleCombo.addItem(scales[i]);
    }
    scaleCombo.setEditText(prev);
    scaleCombo.blockSignals(false);
};

PrintPreviewImpl.prototype.hideUiOptions = function() {
    EAction.prototype.hideUiOptions.call(this, false);
};

/**
 * Called to update the background decoration (paper borders) if the scale
 * or paper settings change.
 */
PrintPreviewImpl.prototype.updateBackgroundDecoration = function() {
    var document = this.getDocument();

    if (isNull(document) || isNull(this.view)) {
        return;
    }

    // initialize graphics view for printing / print preview:
    this.view.setBackgroundColor(Print.getBackgroundColor(document));
    this.view.setColorMode(Print.getColorMode(document));
    this.view.setHairlineMode(Print.getHairlineMode(document));
    this.view.setPrintPreview(true);

    this.view.clearBackground();

    var pages = Print.getPages(document);
    var backgroundColor = Print.getBackgroundColor(document);
    var i, color, path;

    if (pages.length===0) {
        qWarning("PrintPreviewImpl.prototype.updateBackgroundDecoration: no pages");
        return;
    }

    var colBg;
    var colShadow;
    var colBorder;

    if (RSettings.hasDarkGuiBackground()) {
        colBg = "#888888";
        colShadow = "#333333";
        colBorder = "black";
    }
    else {
        colBg = "lightgray";
        colShadow = "gray";
        colBorder = "#c8c8c8";
    }

    path = new RPainterPath();
    path.setPen(new QPen(Qt.NoPen));
    path.setBrush(new QBrush(new QColor(colBg)));
    path.addRect(new QRectF(-1.0e8, -1.0e8, 2.0e8, 2.0e8));
    this.view.addToBackground(RGraphicsSceneDrawable.createFromPainterPath(path));

    // page border with shadow
    if (Print.getShowPaperBorders(document)) {
        // shadow
        for (i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            path.setPen(new QPen(Qt.NoPen));
            path.setBrush(new QBrush(new QColor(colShadow)));
            this.drawShadow(path, pages[i]);
            this.view.addToBackground(RGraphicsSceneDrawable.createFromPainterPath(path));
        }

        // paper background
        for (i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            path.setPen(new QPen(Qt.NoPen));
            color = new QColor(backgroundColor.red(), backgroundColor.green(),
                    backgroundColor.blue());
            path.setBrush(new QBrush(color));
            this.drawPaper(path, pages[i]);
            this.view.addToBackground(RGraphicsSceneDrawable.createFromPainterPath(path));
        }

        // paper border
        for (i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            path.setPen(new QPen(new QColor(colBorder)));
            path.setBrush(new QBrush(Qt.NoBrush));
            this.drawPaper(path, pages[i]);
            this.view.addToBackground(RGraphicsSceneDrawable.createFromPainterPath(path));
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
        qWarning("PrintPreviewImpl.js: no pages");
    }

    for (i = 0; i < pages.length; ++i) {
        this.drawGlueMargins(path, pages[i]);
    }
    this.view.addToBackground(RGraphicsSceneDrawable.createFromPainterPath(path));

    // hook for page tags, footer, etc.:
    this.addDecorations(pages);

    // crop marks:
    if (Print.getPrintCropMarks(document)) {
        for ( i = 0; i < pages.length; ++i) {
            path = new RPainterPath();
            Print.drawCropMarks(document, path, pages[i], false);
            this.view.addToBackground(RGraphicsSceneDrawable.createFromPainterPath(path));
        }
    }

    this.view.regenerate(true);
};

/**
 * Overwritable hook to add more decorations to the print preview.
 */
PrintPreviewImpl.prototype.addDecorations = function(pages) {};

/**
 * Updates the background decoration transformation.
 */
PrintPreviewImpl.prototype.updateBackgroundTransform = function() {
    var document = this.getDocument();

    if (isNull(document)) {
        return;
    }

    var scale = Print.getScale(document);
    var offset = Print.getOffset(document);

    // the smaller the scale, the bigger the paper is shown,
    // relative to the drawing:
    var unitScale = RUnit.convert(1.0, RS.Millimeter, document.getUnit());
    var factor = 1.0 / scale * unitScale;

    if (!isNull(this.view)) {
        this.view.setBackgroundTransform(factor, offset);
    }
};

/**
 * Draws the paper border for the given page.
 */
PrintPreviewImpl.prototype.drawPaper = function(path, border) {
    var document = this.getDocument();
    var paperBorder = Print.getPaperBorder(document, border);
    if (!paperBorder.isValid()) {
        return;
    }
    path.addRect(paperBorder);
};

/**
 * Draws the glue margins for the given page.
 */
PrintPreviewImpl.prototype.drawGlueMargins = function(path, border) {
    if (!border.isValid()) {
        return;
    }
    path.addRect(border);
};

/**
 * Draws the shadow for the given page.
 */
PrintPreviewImpl.prototype.drawShadow = function(path, border) {
    var document = this.getDocument();
    var paper = Print.getPaperBorder(document, border);
    var offset = Print.getPaperSizeMM(document).width() * 0.02;
    var shadow = paper.adjusted(offset, -offset, offset, -offset);
    if (!shadow.isValid()) {
        return;
    }
    path.addRect(shadow);
};

PrintPreviewImpl.prototype.slotPdfExport = function() {
    var appWin = EAction.getMainWindow();
    var fileName = this.getDocument().getFileName();
    var initialFileName = QDir.homePath();
    if (fileName!=="") {
        var fileInfo = new QFileInfo(fileName);
        initialFileName = fileInfo.absoluteFilePath();
    }

    var filterStrings = [ "PDF File (*.pdf)",  "PDF/A-1B File (*.pdf)"];
    if (RSettings.getQtVersion()<0x050A00) {
        filterStrings = [ "PDF File (*.pdf)" ];
    }

    filterStrings = translateFilterStrings(filterStrings);

    var ret = File.getSaveFileName(appWin, qsTr("Export to PDF"),
                   initialFileName, filterStrings);

    if (isNull(ret)) {
        return;
    }

    var pdfFile = ret[0];
    var pdfVersion = undefined;
    if (ret[1].indexOf("PDF/A")!==-1) {
        pdfVersion = "A-1B";
    }

    appWin.handleUserMessage(qsTr("Exporting to %1...").arg(pdfFile));

    var success = this.slotPrint(pdfFile, pdfVersion);

    if (success) {
        appWin.handleUserMessage(qsTr("Export complete: %1").arg(pdfFile));
    }
    else {
        appWin.handleUserWarning(qsTr("Export failed (cannot open file for writing): %1").arg(pdfFile));
    }
};

/**
 * Called when user clicks the PDF export button in the options toolbar.
 */
PrintPreviewImpl.slotPdfExport = function() {
    var pp = PrintPreviewImpl.getInstance();
    pp.slotPdfExport();
};

PrintPreviewImpl.prototype.slotPrint = function(pdfFile, pdfVersion) {
    return PrintPreviewImpl.slotPrint(pdfFile, pdfVersion);
};

/**
 * Prints the drawing or exports it to the given PDF file.
 */
PrintPreviewImpl.slotPrint = function(pdfFile, pdfVersion) {
    var mdiChild = EAction.getMdiChild();
    var view = mdiChild.getLastKnownViewWithFocus();
    var print = new Print(undefined, EAction.getDocument(), view);
    return print.print(pdfFile, undefined, pdfVersion);
};

/**
 * Called whenever the user changes the drawing scale in the print preview.
 */
PrintPreviewImpl.prototype.slotScaleChanged = function(scaleString) {
    if (this.updateDisabled===true) {
        return;
    }

    var di = this.getDocumentInterface();
    if (isNull(di) || this.updateDisabled===true) {
        return;
    }

    Print.setScaleString(di, scaleString);

    this.updateBackgroundTransform();

    // update pattern scale accordint to drawing scale:
    di.regenerateScenes();
};

PrintPreviewImpl.setScale = function(di, scale) {
    PrintPreviewImpl.setScaleString(di, sprintf("%.6f", scale));
};

PrintPreviewImpl.setScaleString = function(di, scaleString) {
    Print.setScaleString(di, scaleString);

    PrintPreviewImpl.updateScaleString(document);
};

PrintPreviewImpl.updateScaleString = function(document) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleCombo = optionsToolBar.findChild("Scale");
    if (Print.getScale(document) != RMath.parseScale(scaleCombo.currentText)) {
        scaleCombo.blockSignals(true);
        scaleCombo.setEditText(Print.getScaleString(document));
        scaleCombo.blockSignals(false);
    }
};

/**
 * Triggered by the offset tool button in the options toolbar.
 * Activates / deactivates the offset tool.
 */
PrintPreviewImpl.prototype.slotOffsetChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }

    if (checked) {
        this.setState(PrintPreviewImpl.State.SettingOffset);
    }
    else {
        this.setState(DefaultAction.State.Neutral);
    }
};

/**
 * Triggered by the "Done" button in the options toolbar.
 * Terminates this action and returns to normal drawing mode.
 */
PrintPreviewImpl.prototype.slotDone = function() {
    PrintPreview.exit();
};

/**
 * Triggered by the b/w button in the options toolbar.
 * Activates / deactivates the black white mode.
 */
PrintPreviewImpl.prototype.slotFullColorChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    if (checked) {
        Print.setColorMode(this.getDocumentInterface(), RGraphicsView.FullColor);
        this.colorModeUpdate();
    }
};

PrintPreviewImpl.prototype.slotBlackWhiteChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    if (checked) {
        Print.setColorMode(this.getDocumentInterface(), RGraphicsView.BlackWhite);
        this.colorModeUpdate();
    }
};

PrintPreviewImpl.prototype.slotGrayscaleChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    if (checked) {
        Print.setColorMode(this.getDocumentInterface(), RGraphicsView.GrayScale);
        this.colorModeUpdate();
    }
};

PrintPreviewImpl.prototype.colorModeUpdate = function() {
    if (!isNull(this.view)) {
        this.view.setColorMode(Print.getColorMode(this.getDocument()));
        this.view.regenerate(true);
    }    
};

PrintPreviewImpl.prototype.slotHairlineChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    Print.setHairlineMode(this.getDocumentInterface(), checked);
    if (!isNull(this.view)) {
        this.view.setHairlineMode(checked)
        this.view.regenerate(true);
    }
};


/**
 * Page borders toggled in options toolbar.
 */
PrintPreviewImpl.prototype.slotShowPaperBordersChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    var di = this.getDocumentInterface();
    Print.setShowPaperBorders(di, checked);

    this.updateBackgroundDecoration();
};

/**
 * Crop marks toggled in options toolbar.
 */
PrintPreviewImpl.prototype.slotPrintCropMarksChanged = function(checked) {
    if (this.updateDisabled===true) {
        return;
    }
    var di = this.getDocumentInterface();
    Print.setPrintCropMarks(di, checked);

    this.updateBackgroundDecoration();
};

/**
 * Auto fit box to page.
 */
PrintPreviewImpl.prototype.slotAutoFitBox = function(box) {
    var di = this.getDocumentInterface();
    var doc = di.getDocument();
    Print.autoFitBox(di, box);
    PrintPreviewImpl.updateScaleString(doc);

    // needed to update pattern scaling according to drawing scale:
    //var di = this.getDocumentInterface();
    di.regenerateScenes();

    this.updateBackgroundTransform();
    //this.slotAutoZoomToPage();
    this.updateBackgroundDecoration();
    this.showUiOptions(true);
};

/**
 * Auto fit drawing button clicked in options toolbar.
 */
PrintPreviewImpl.prototype.slotAutoFitDrawing = function() {
    var di = this.getDocumentInterface();
    var document = di.getDocument();
    Print.autoFitDrawing(di);
    PrintPreviewImpl.updateScaleString(document);

    // needed to update pattern scaling according to drawing scale:
    di.regenerateScenes();

    this.updateBackgroundTransform();
    this.slotAutoZoomToPage();
    this.updateBackgroundDecoration();
    this.showUiOptions(true);
};

PrintPreviewImpl.prototype.slotAutoCenter = function() {
    Print.autoCenter(this.getDocumentInterface());

    this.updateBackgroundTransform();
    this.slotAutoZoomToPage();
    this.updateBackgroundDecoration();
};

PrintPreviewImpl.prototype.slotPortraitChanged = function() {
    if (this.updateDisabled===true) {
        return;
    }
    var di = this.getDocumentInterface();
    Print.setPageOrientationEnum(di, QPrinter.Portrait);

    this.updateBackgroundDecoration();
    this.slotAutoZoomToPage();
};

PrintPreviewImpl.prototype.slotLandscapeChanged = function() {
    if (this.updateDisabled===true) {
        return;
    }
    var di = this.getDocumentInterface();
    Print.setPageOrientationEnum(di, QPrinter.Landscape);

    this.updateBackgroundDecoration();
    this.slotAutoZoomToPage();
};

/**
 * \return Maximum extents of paper
 */
PrintPreviewImpl.prototype.getPaperBox = function() {
    return Print.getPaperBox(this.getDocument());
};

PrintPreviewImpl.prototype.slotAutoZoomToPage = function() {
    if (!isNull(this.view)) {
        var pBox = this.getPaperBox();
        this.view.zoomTo(pBox, 10);
    }
};

/**
 * Updates the background (paper preview) transform when page settings
 * are changed (e.g. offset).
 */
PrintPreviewImpl.prototype.updateFromPreferences = function() {
    this.showUiOptions(true);
    this.updateBackgroundDecoration();
    this.updateBackgroundTransform();
};
