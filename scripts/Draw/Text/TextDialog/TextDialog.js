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

include("scripts/library.js");
include("scripts/map.js");
include("scripts/WidgetFactory.js");
include("CharacterMapDialog.js");

/**
 * \class SymbolMenuData
 * \brief Helper class for symbol popup menu.
 * \ingroup ecma_draw_text
 */
function SymbolMenuData(textWidget, data) {
    this.textWidget = textWidget;
    this.data = data;
}

SymbolMenuData.prototype.triggered = function() {
    var cursor = this.textWidget.textCursor();
    cursor.insertText(this.data);
};


/**
 * \class TextDialog
 * \brief Text creation or editing dialog.
 * \ingroup ecma_draw_text
 */
function TextDialog(mode) {
    if (isNull(mode)) {
        mode = TextDialog.Mode.Text;
    }
    this.mode = mode;

    this.dialog = undefined;

    this.textEdit = undefined;
    this.sourceEdit = undefined;

    this.actionTextBold = undefined;
    this.actionTextItalic = undefined;
    this.actionTextUnderline = undefined;

    this.actionSubscript = undefined;
    this.actionSuperscript = undefined;

    this.actionTextColor = undefined;
    //this.actionZoomIn = undefined;
    //this.actionZoomOut = undefined;
    
    this.actionTextSymbol = undefined;

    this.actionUndo = undefined;
    this.actionRedo = undefined;

    this.actionCut = undefined;
    this.actionCopy = undefined;
    this.actionPaste = undefined;

    this.comboFont = undefined;
    this.comboSize = undefined;

    // display text in text edit with this factor, compared to drawing unit:
    this.fontHeightFactor = 10.0;

    this.mainFont = undefined;
    this.initialColor = new RColor();
}

TextDialog.Mode = {
    Text : 0,
    Attribute : 1,
    AttributeDefinition : 2
};

TextDialog.prototype.setMode = function(mode) {
    this.mode = mode;
};

TextDialog.prototype.getTextDocument = function() {
    if (RSettings.isQt(5)) {
        return this.textEdit.document;
    }
    else {
        return this.textEdit.document();
    }
};

TextDialog.prototype.getSourceDocument = function() {
    return this.sourceEdit.document();
};


TextDialog.prototype.show =  function(textDataIn) {
    if (!isNull(textDataIn)) {
        if (isOfType(textDataIn, RAttributeData)) {
            this.mode = TextDialog.Mode.Attribute;
        }
        else if (isOfType(textDataIn, RAttributeDefinitionData)) {
            this.mode = TextDialog.Mode.AttributeDefinition;
        }
        else {
            this.mode = TextDialog.Mode.Text;
        }
    }

    this.dialog = WidgetFactory.createDialog(TextDialog.basePath, "TextDialog.ui", EAction.getMainWindow());

    // initialize dialog controls:
    this.textEdit = this.dialog.findChild("Text");
    this.sourceEdit = this.dialog.findChild("Source");
    this.tabWidget = this.dialog.findChild("TabWidget");

    // brighter background of text area in dark mode:
    if (RSettings.hasDarkGuiBackground()) {
        var p = this.textEdit.palette;
        p.setColor(QPalette.Active, QPalette.Base, new QColor(Qt.gray));
        this.textEdit.palette = p;
    }

    // main font combo box:
    var comboMainFont = this.dialog.findChild("MainFont");
    var comboFont = this.dialog.findChild("Font");

    initFontComboBox(comboMainFont);
    initFontComboBox(comboFont);

    comboMainFont.currentFontChanged.connect(this, "mainFontChanged");

    // main font height:
    var editMainHeight = this.dialog.findChild("MainHeight");
    editMainHeight.valueChanged.connect(this, "mainFontChanged");

    // main font bold:
    var checkMainBold = this.dialog.findChild("MainBold");
    checkMainBold.toggled.connect(this, "mainFontChanged");

    // main font italic:
    var checkMainItalic = this.dialog.findChild("MainItalic");
    checkMainItalic.toggled.connect(this, "mainFontChanged");

    // default line spacing:
    //var checkBoxDefaultLineSpacing = this.dialog.findChild("DefaultLineSpacing");
    //checkBoxDefaultLineSpacing.toggled.connect(this, "useDefaultLineSpacing");

    // line spacing:
    var editLineSpacingFactor = this.dialog.findChild("LineSpacingFactor");

    // angle:
    var editAngle = this.dialog.findChild("Angle");

    /*
    var buttonNew = this.dialog.findChild("New");
    buttonNew.clicked.connect(this.textEdit, "clear");
    var buttonOpen = this.dialog.findChild("Open");
    var buttonSaveAs = this.dialog.findChild("SaveAs");
    */

    this.setupEditActions();
    this.setupTextActions();

    // update status buttons bold / italic / underline:
    this.textEdit.currentCharFormatChanged.connect(this, "currentCharFormatChanged");
    this.textEdit.cursorPositionChanged.connect(this, "cursorPositionChanged");

    var td = this.getTextDocument();
    td.undoAvailable.connect(this.actionUndo, "setEnabled");
    td.redoAvailable.connect(this.actionRedo, "setEnabled");

    this.actionUndo.setEnabled(td.isUndoAvailable());
    this.actionRedo.setEnabled(td.isRedoAvailable());

    this.actionUndo.triggered.connect(this.textEdit, "undo");
    this.actionRedo.triggered.connect(this.textEdit, "redo");

    this.actionCut.setEnabled(false);
    this.actionCopy.setEnabled(false);

    this.actionCut.triggered.connect(this.textEdit, "cut");
    this.actionCopy.triggered.connect(this.textEdit, "copy");
    this.actionPaste.triggered.connect(this.textEdit, "paste");

    this.textEdit.copyAvailable.connect(this.actionCut, "setEnabled");
    this.textEdit.copyAvailable.connect(this.actionCopy, "setEnabled");

    var cbSimpleText = this.dialog.findChild("SimpleText");
    cbSimpleText.toggled.connect(this, "simpleTextToggled");

    var buttonTopLeft = this.dialog.findChild("AlignTopLeft");
    var buttonTopCenter = this.dialog.findChild("AlignTopCenter");
    var buttonTopRight = this.dialog.findChild("AlignTopRight");
    var buttonMiddleLeft = this.dialog.findChild("AlignMiddleLeft");
    var buttonMiddleCenter = this.dialog.findChild("AlignMiddleCenter");
    var buttonMiddleRight = this.dialog.findChild("AlignMiddleRight");
    var buttonBaseLeft = this.dialog.findChild("AlignBaseLeft");
    var buttonBaseCenter = this.dialog.findChild("AlignBaseCenter");
    var buttonBaseRight = this.dialog.findChild("AlignBaseRight");
    var buttonBottomLeft = this.dialog.findChild("AlignBottomLeft");
    var buttonBottomCenter = this.dialog.findChild("AlignBottomCenter");
    var buttonBottomRight = this.dialog.findChild("AlignBottomRight");

    getClipboard().dataChanged.connect(this, "clipboardDataChanged");

    // change dialog into attribute / attribute definition dialog:
    if (this.mode === TextDialog.Mode.AttributeDefinition ||
        this.mode === TextDialog.Mode.Attribute) {

        this.dialog.findChild("Separator").visible = false;
        this.dialog.findChild("LineSpacingFactorLabel").visible = false;
        editLineSpacingFactor.visible = false;
        cbSimpleText.visible = false;
        this.tabWidget.removeTab(1);
        this.tabWidget.removeTab(0);
        this.dialog.resize(0,0);

        if (this.mode === TextDialog.Mode.AttributeDefinition) {
            this.dialog.windowTitle = entityTypeToString(RS.EntityAttributeDefinition, false);
        }
        else if (this.mode === TextDialog.Mode.Attribute) {
            this.dialog.windowTitle = entityTypeToString(RS.EntityAttribute, false);
        }
    }
    else {
        this.tabWidget.removeTab(2);
    }

    // sync rich text / source:
    this.tabWidget["currentChanged(int)"].connect(this, "tabChanged");

    if (this.mode === TextDialog.Mode.AttributeDefinition) {
        this.dialog.findChild("ValueLabel").text = qsTr("Default value:");
    }

    // initialize dialog from given text data (textDataIn):
    if (!isNull(textDataIn)) {
        cbSimpleText.checked = textDataIn.isSimple();
        this.initialColor = textDataIn.getColor();
        activateFont(comboMainFont, textDataIn.getFontName());
        checkMainBold.checked = textDataIn.isBold();
        checkMainItalic.checked = textDataIn.isItalic();
        editMainHeight.setValue(textDataIn.getTextHeight());
        this.sourceEdit.setPlainText(textDataIn.getEscapedText());
        this.updateRichText(true);
        //qDebug("this.sourceEdit:", this.sourceEdit.plainText);
        if (textDataIn.getVAlign()==RS.VAlignTop) {
            if (textDataIn.getHAlign()==RS.HAlignLeft || textDataIn.getHAlign()==RS.HAlignFit || textDataIn.getHAlign()==RS.HAlignAlign) {
                buttonTopLeft.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignCenter) {
                buttonTopCenter.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignRight) {
                buttonTopRight.checked = true;
            }
        }
        else if (textDataIn.getVAlign()==RS.VAlignMiddle) {
            if (textDataIn.getHAlign()==RS.HAlignLeft || textDataIn.getHAlign()==RS.HAlignFit || textDataIn.getHAlign()==RS.HAlignAlign) {
                buttonMiddleLeft.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignCenter || textDataIn.getHAlign()==RS.HAlignMid) {
                buttonMiddleCenter.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignRight) {
                buttonMiddleRight.checked = true;
            }
        }
        else if (textDataIn.getVAlign()==RS.VAlignBase) {
            if (textDataIn.getHAlign()==RS.HAlignLeft || textDataIn.getHAlign()==RS.HAlignFit || textDataIn.getHAlign()==RS.HAlignAlign) {
                buttonBaseLeft.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignCenter) {
                buttonBaseCenter.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignRight) {
                buttonBaseRight.checked = true;
            }
        }
        else if (textDataIn.getVAlign()==RS.VAlignBottom) {
            if (textDataIn.getHAlign()==RS.HAlignLeft || textDataIn.getHAlign()==RS.HAlignFit || textDataIn.getHAlign()==RS.HAlignAlign) {
                buttonBottomLeft.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignCenter) {
                buttonBottomCenter.checked = true;
            }
            else if (textDataIn.getHAlign()==RS.HAlignRight) {
                buttonBottomRight.checked = true;
            }
        }

        editLineSpacingFactor.setValue(textDataIn.getLineSpacingFactor());
        editAngle.setValue(textDataIn.getAngle());

        // init values specific to attributes / attribute definitions:
        if (this.mode === TextDialog.Mode.Attribute ||
            this.mode === TextDialog.Mode.AttributeDefinition) {

            this.dialog.findChild("AttributeTag").text = textDataIn.getTag();
            this.dialog.findChild("AttributeValue").text = textDataIn.getText();

            if (this.mode === TextDialog.Mode.AttributeDefinition) {
                this.dialog.findChild("AttributePrompt").text = textDataIn.getPrompt();
            }
            else {
                this.dialog.findChild("AttributePrompt").visible = false;
                this.dialog.findChild("PromptLabel").visible = false;
                this.dialog.findChild("AttributeTag").enabled = false;
                this.dialog.findChild("AttributeValue").selectAll();
            }
        }
    }
    else {
        WidgetFactory.restoreState(this.dialog);

        cbSimpleText.checked = RSettings.getBoolValue("TextDialog/SimpleText", false);

        // restore widgets that are not supported by WidgetFactory:
        var mainFontName = RSettings.getStringValue("TextDialog/MainFont", "Arial");
        var mainFontIndex = comboMainFont.findText(mainFontName);
        if (mainFontIndex>0) {
            comboMainFont.currentIndex = mainFontIndex;
        }

        this.sourceEdit.setPlainText(RSettings.getStringValue("TextDialog/Source", ""));
        this.updateRichText(true);

        var vAlignment = RSettings.getIntValue("TextDialog/VAlignment", RS.VAlignTop);
        var hAlignment = RSettings.getIntValue("TextDialog/HAlignment", RS.HAlignLeft);

        if (vAlignment==RS.VAlignTop) {
            if (hAlignment==RS.HAlignLeft || hAlignment==RS.HAlignFit || hAlignment==RS.HAlignAlign) {
                buttonTopLeft.checked = true;
            }
            else if (hAlignment==RS.HAlignCenter) {
                buttonTopCenter.checked = true;
            }
            else if (hAlignment==RS.HAlignRight) {
                buttonTopRight.checked = true;
            }
        }
        else if (vAlignment==RS.VAlignMiddle) {
            if (hAlignment==RS.HAlignLeft || hAlignment==RS.HAlignFit || hAlignment==RS.HAlignAlign) {
                buttonMiddleLeft.checked = true;
            }
            else if (hAlignment==RS.HAlignCenter) {
                buttonMiddleCenter.checked = true;
            }
            else if (hAlignment==RS.HAlignRight) {
                buttonMiddleRight.checked = true;
            }
        }
        else if (vAlignment==RS.VAlignBase) {
            if (hAlignment==RS.HAlignLeft || hAlignment==RS.HAlignFit || hAlignment==RS.HAlignAlign) {
                buttonBaseLeft.checked = true;
            }
            else if (hAlignment==RS.HAlignCenter) {
                buttonBaseCenter.checked = true;
            }
            else if (hAlignment==RS.HAlignRight) {
                buttonBaseRight.checked = true;
            }
        }
        else if (vAlignment==RS.VAlignBottom) {
            if (hAlignment==RS.HAlignLeft || hAlignment==RS.HAlignFit || hAlignment==RS.HAlignAlign) {
                buttonBottomLeft.checked = true;
            }
            else if (hAlignment==RS.HAlignCenter) {
                buttonBottomCenter.checked = true;
            }
            else if (hAlignment==RS.HAlignRight) {
                buttonBottomRight.checked = true;
            }
        }

        var di = EAction.getDocumentInterface();
        if (!isNull(di)) {
            // initial text color is current color (e.g. ByLayer, red, ..):
            this.initialColor = di.getCurrentColor();
        }
        else {
            // initial color is invalid (no document, never reached):
            this.initialColor = new RColor();
            debugger;
        }
    }

    this.mainFontChanged();

    this.colorChanged(this.textEdit.textColor());
    this.colorChanged(this.initialColor);

    if (cbSimpleText.checked) {
        this.sourceEdit.setFocus(Qt.OtherFocusReason);
        this.sourceEdit.selectAll();
    }
    else {
        this.textEdit.setFocus(Qt.OtherFocusReason);
        this.textEdit.selectAll();
    }

    this.currentCharFormatChanged(this.textEdit.currentCharFormat());
    //this.colorChanged();

    // exec text dialog:
    var res = this.dialog.exec();
    if (this.tabWidget.currentIndex===0) {
        this.updateSource(true);
    }

    // analize dialog input:
    var textDataOut;
    if (isNull(textDataIn)) {
        if (this.mode === TextDialog.Mode.Attribute) {
            textDataOut = new RAttributeData();
        }
        else if (this.mode === TextDialog.Mode.AttributeDefinition) {
            textDataOut = new RAttributeDefinitionData();
        }
        else {
            textDataOut = new RTextData();
        }
    }
    else {
        textDataOut = textDataIn;
    }

    textDataOut.setFontName(comboMainFont.currentFont.family());
    textDataOut.setBold(checkMainBold.checked);
    textDataOut.setItalic(checkMainItalic.checked);
    textDataOut.setTextHeight(editMainHeight.getValue());

    if (buttonTopLeft.checked || buttonTopCenter.checked || buttonTopRight.checked) {
        textDataOut.setVAlign(RS.VAlignTop);
    }
    else if (buttonMiddleLeft.checked || buttonMiddleCenter.checked || buttonMiddleRight.checked) {
        textDataOut.setVAlign(RS.VAlignMiddle);
    }
    else if (buttonBaseLeft.checked || buttonBaseCenter.checked || buttonBaseRight.checked) {
        textDataOut.setVAlign(RS.VAlignBase);
    }
    else if (buttonBottomLeft.checked || buttonBottomCenter.checked || buttonBottomRight.checked) {
        textDataOut.setVAlign(RS.VAlignBottom);
    }

    if (buttonTopLeft.checked || buttonMiddleLeft.checked || buttonBaseLeft.checked || buttonBottomLeft.checked) {
        textDataOut.setHAlign(RS.HAlignLeft);
    }
    else if (buttonTopCenter.checked || buttonMiddleCenter.checked || buttonBaseCenter.checked || buttonBottomCenter.checked) {
        textDataOut.setHAlign(RS.HAlignCenter);
    }
    else if (buttonTopRight.checked || buttonMiddleRight.checked || buttonBaseRight.checked || buttonBottomRight.checked) {
        textDataOut.setHAlign(RS.HAlignRight);
    }

    //textDataOut.setDrawingDirection();
    //textDataOut.setLineSpacingStyle();

    textDataOut.setLineSpacingFactor(editLineSpacingFactor.getValue());
    textDataOut.setAngle(editAngle.getValue());

    // init values specific to attributes / attribute definitions:
    if (this.mode === TextDialog.Mode.Attribute ||
        this.mode === TextDialog.Mode.AttributeDefinition) {

        textDataOut.setSimple(true);
        textDataOut.setTag(this.dialog.findChild("AttributeTag").text);
        if (this.mode === TextDialog.Mode.AttributeDefinition) {
            textDataOut.setPrompt(this.dialog.findChild("AttributePrompt").text);
        }
        textDataOut.setText(this.dialog.findChild("AttributeValue").text);
    }
    else {
        textDataOut.setSimple(cbSimpleText.checked);
        textDataOut.setText(this.sourceEdit.toPlainText());
    }

    WidgetFactory.saveState(this.dialog);

    // save state of unsupported widgets:
    RSettings.setValue("TextDialog/VAlignment", textDataOut.getVAlign());
    RSettings.setValue("TextDialog/HAlignment", textDataOut.getHAlign());
    RSettings.setValue("TextDialog/MainFont", textDataOut.getFontName());

    this.dialog.destroy();
    EAction.activateMainWindow();

    if (res) {
        return textDataOut;
    }
    else {
        return undefined;
    }
};

TextDialog.basePath = includeBasePath;

TextDialog.prototype.setupEditActions = function() {
    var a;

    a = this.actionUndo = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Undo.svg")), qsTr("&Undo"), this.dialog);
    a.shortcut = QKeySequence.Undo;
    this.dialog.findChild("Undo").setDefaultAction(a);

    a = this.actionRedo = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Redo.svg")), qsTr("&Redo"), this.dialog);
    a.shortcut = QKeySequence.Redo;
    this.dialog.findChild("Redo").setDefaultAction(a);

    a = this.actionCut = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Cut.svg")), qsTr("Cu&t"), this.dialog);
    a.shortcut = QKeySequence.Cut;
    this.dialog.findChild("Cut").setDefaultAction(a);

    a = this.actionCopy = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Copy.svg")), qsTr("&Copy"), this.dialog);
    a.shortcut = QKeySequence.Copy;
    this.dialog.findChild("Copy").setDefaultAction(a);

    a = this.actionPaste = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Paste.svg")), qsTr("&Paste"), this.dialog);
    a.shortcut = QKeySequence.Paste;
    this.dialog.findChild("Paste").setDefaultAction(a);

    this.actionPaste.setEnabled(!getClipboard().text().isEmpty());
};

TextDialog.prototype.setupTextActions = function() {
    this.actionTextBold = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Bold.svg")), qsTr("&Bold"), this.dialog);
    this.actionTextBold.shortcut = new QKeySequence(Qt.ControlModifier | Qt.Key_B);
    var bold = new QFont();
    bold.setBold(true);
    this.actionTextBold.font = bold;
    this.actionTextBold.triggered.connect(this, "textBold");
    this.actionTextBold.checkable = true;
    this.dialog.findChild("Bold").setDefaultAction(this.actionTextBold);

    this.actionTextItalic = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Italic.svg")), qsTr("&Italic"), this.dialog);
    this.actionTextItalic.shortcut = new QKeySequence(Qt.ControlModifier | Qt.Key_I);
    var italic = new QFont();
    italic.setItalic(true);
    this.actionTextItalic.font = italic;
    this.actionTextItalic.triggered.connect(this, "textItalic");
    this.actionTextItalic.checkable = true;
    this.dialog.findChild("Italic").setDefaultAction(this.actionTextItalic);

    this.actionTextUnderline = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Underline.svg")), qsTr("&Underline"), this.dialog);
    this.actionTextUnderline.shortcut = Qt.CTRL + Qt.Key_U;
    var underline = new QFont();
    underline.setUnderline(true);
    this.actionTextUnderline.font = underline;
    this.actionTextUnderline.triggered.connect(this, "textUnderline");
    this.actionTextUnderline.checkable = true;
    this.dialog.findChild("Underline").setDefaultAction(this.actionTextUnderline);

    this.actionSubscript = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Subscript.svg")), qsTr("&Subscript"), this.dialog);
    this.actionSubscript.shortcut = new QKeySequence(Qt.ShiftModifier | Qt.ControlModifier | Qt.Key_B);
    this.actionSubscript.triggered.connect(this, "textSubscript");
    this.actionSubscript.checkable = true;
    this.dialog.findChild("Subscript").setDefaultAction(this.actionSubscript);

    this.actionSuperscript = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Superscript.svg")), qsTr("&Superscript"), this.dialog);
    this.actionSuperscript.shortcut = new QKeySequence(Qt.ShiftModifier | Qt.ControlModifier | Qt.Key_P);
    this.actionSuperscript.triggered.connect(this, "textSuperscript");
    this.actionSuperscript.checkable = true;
    this.dialog.findChild("Superscript").setDefaultAction(this.actionSuperscript);

//    this.actionZoomIn = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/ZoomIn.svg")), qsTr("Zoom &In"), this.dialog);
//    this.actionZoomIn.shortcut = new QKeySequence(Qt.ControlModifier | Qt.Key_Plus);
//    this.actionZoomIn.triggered.connect(this.textEdit, "zoomIn");
//    this.dialog.findChild("ZoomIn").setDefaultAction(this.actionZoomIn);

//    this.actionZoomOut = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/ZoomOut.svg")), qsTr("Zoom &Out"), this.dialog);
//    this.actionZoomOut.shortcut = new QKeySequence(Qt.ControlModifier | Qt.Key_Minus);
//    this.actionZoomOut.triggered.connect(this.textEdit, "zoomOut");
//    this.dialog.findChild("ZoomOut").setDefaultAction(this.actionZoomOut);

    var pix = new QPixmap(16, 16);
    pix.fill(Qt.black);
    this.actionTextColor = new QAction(new QIcon(pix), qsTr("&Color..."), this.dialog);
    this.actionTextColor.triggered.connect(this, "textColor");
    this.dialog.findChild("Color").setDefaultAction(this.actionTextColor);

    this.actionTextSymbol = new QAction(new QIcon(autoIconPath(TextDialog.basePath + "/Symbol.svg")), qsTr("&Special Characters..."), this.dialog);
    this.actionTextSymbol.triggered.connect(this, "textSymbol");
    this.dialog.findChild("Symbol").setDefaultAction(this.actionTextSymbol);
    
    this.comboFont = this.dialog.findChild("Font");
    this.comboFont["activated(QString)"].connect(this, "textFamily");

    this.comboSize = this.dialog.findChild("Height");
    this.comboSize.editable = true;
    this.comboSize["activated(QString)"].connect(this, "textSize");
    this.comboSize.setEditText("1.0");
    this.comboSize.editTextChanged.connect(this, "textSize");
};

/**
 * \return Main font to use with main height set in in drawing units
 * as points. E.g. a font with point size 15.0 means the font height
 * is really 15 drawing units.
 */
TextDialog.prototype.getMainFont = function() {
    // get main font with main height:
    var comboMainFont = this.dialog.findChild("MainFont");
    var font = comboMainFont.currentFont;

    var editMainHeight = this.dialog.findChild("MainHeight");
    font.setPointSizeF(editMainHeight.getValue());

    var checkMainBold = this.dialog.findChild("MainBold");
    font.setBold(checkMainBold.checked);

    var checkMainItalic = this.dialog.findChild("MainItalic");
    font.setItalic(checkMainItalic.checked);

    return font;
};


/**
 * Called when user changes the main font (initial font for text).
 */
TextDialog.prototype.mainFontChanged = function() {
    var font = this.getMainFont();
    this.fontHeightFactor = 14.0 / font.pointSizeF();

    if (this.tabWidget.currentIndex===1) {
        this.updateRichText(true);
    }

    var document = this.getTextDocument();
    var html = document.toHtml();

//    qDebug("\n\nmainFontChanged: html before fix: ", html, "\n\n");

    html = this.fixHtml(html);

//    qDebug("\n\nmainFontChanged: html after fix: ", html, "\n\n");

    var previousMainFont = this.mainFont;
    this.mainFont = font;

    font.setPointSizeF(font.pointSizeF() * this.fontHeightFactor);
    this.textEdit.font = font;
    document.defaultFont = font;

    //qDebug("\n\nHTML after setting default font: \n", html, "\n\n");

    // replace all fonts that matched the previous main font with new
    // main font. this is _most likely_ what the user expects:
    if (!isNull(previousMainFont)) {
        html.replace("font-family:'%1';".arg(previousMainFont.family()),
                     "font-family:'%1';".arg(font.family()));
    }

//    qDebug("\n\nmainFontChanged: html after font replace: ", html, "\n\n");

    this.textEdit.setHtml(html);

//    qDebug("\n\nnew html: ", this.getTextDocument().toHtml(), "\n\n");

    this.updateSource(true);

};

TextDialog.prototype.fixHtml = function(html) {
    var font = this.getMainFont();

    //html = html.replace(/>[ ]*</, "><");
    var htmlNbsp = "";
    var cdata = false;
    for (var i=0; i<html.length; i++) {
        if (html[i]==='<') {
            cdata = false;
        }
        else if (html[i]==='>') {
            cdata = true;
        }
        // create nbsp from all spaces. QTextEdit will simplify white space
        // to one single space otherwise.
        else if (cdata && (html[i]===' ' || html[i]==='\u00A0')) {
            htmlNbsp += '&nbsp;';
            continue;
        }

        htmlNbsp += html[i];
    }

    // change font in HTML directly. changing default font of document
    // keeps content formatting by adding font style with previous
    // default font to all content:
    var dom = new QDomDocument();
    dom.setContent(htmlNbsp, false);
    var docElem = dom.documentElement();

    //qDebug("initial font color: ", this.initialColor);

    var n = docElem.firstChild();
    while (!n.isNull()) {
        var e = n.toElement();
        if(!e.isNull()) {
            if (e.tagName().toLowerCase()==="body") {
                var qcol = this.initialColor.toCompat();
                e.setAttribute("style",
                               ("font-family:'%1';" +
                               "font-size:%2pt;" +
                               "font-weight:%3;" +
                               "font-style:%4;" +
                               "color:%5;")
                               .arg(font.family())
                               .arg(font.pointSizeF() * this.fontHeightFactor)
                               .arg(font.weight()<=QFont.Normal ? "normal" : "bold")
                               .arg(font.italic() ? "italic" : "normal")
                               .arg(qcol.name()));
            }
        }
        n = n.nextSibling();
    }

    return dom.toString(-1);
};

TextDialog.prototype.simpleTextToggled = function(enable) {
    if (this.mode!==TextDialog.Mode.Text) {
        return;
    }

    var editLineSpacingFactor = this.dialog.findChild("LineSpacingFactor");

    if (enable) {
        this.tabWidget.setTabEnabled(0, false);
        this.tabWidget.currentIndex = 1;
        editLineSpacingFactor.enabled = false;
    }
    else {
        this.tabWidget.setTabEnabled(0, true);
        this.tabWidget.currentIndex = 0;
        editLineSpacingFactor.enabled = true;
    }
};

TextDialog.prototype.mergeFormatOnWordOrSelection = function(format) {
    var cursor = this.textEdit.textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor.WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    this.textEdit.mergeCurrentCharFormat(format);
};

/**
 * Called when user clicks bold button.
 */
TextDialog.prototype.textBold = function() {
    var fmt = new QTextCharFormat();
    fmt.setFontWeight(this.actionTextBold.checked ? QFont.Bold : QFont.Normal);
    this.mergeFormatOnWordOrSelection(fmt);
};

/**
 * Called when user clicks italic button.
 */
TextDialog.prototype.textItalic = function() {
    var fmt = new QTextCharFormat();
    fmt.setFontItalic(this.actionTextItalic.checked);
    this.mergeFormatOnWordOrSelection(fmt);
};

/**
 * Called when user clicks underline button.
 */
TextDialog.prototype.textUnderline = function() {
    var fmt = new QTextCharFormat();
    fmt.setFontUnderline(this.actionTextUnderline.checked);
    this.mergeFormatOnWordOrSelection(fmt);
};

/**
 * Called when user clicks subscript button.
 */
TextDialog.prototype.textSubscript = function() {
    var fmt = new QTextCharFormat();
    fmt.setVerticalAlignment(this.actionSubscript.checked ? QTextCharFormat.AlignSubScript : QTextCharFormat.AlignNormal);
    this.mergeFormatOnWordOrSelection(fmt);
};

/**
 * Called when user clicks superscript button.
 */
TextDialog.prototype.textSuperscript = function() {
    var fmt = new QTextCharFormat();
    fmt.setVerticalAlignment(this.actionSuperscript.checked ? QTextCharFormat.AlignSuperScript : QTextCharFormat.AlignNormal);
    this.mergeFormatOnWordOrSelection(fmt);
};

/**
 * Called when user changes font.
 */
TextDialog.prototype.textFamily = function(f) {
    var fmt = new QTextCharFormat();
    // Qt 5.13, 5.14, 5.15 bug: appends the font as fall-back instead of setting the font:
    //fmt.setFontFamily(f);
    fmt.setFontFamilies([f]);
    this.mergeFormatOnWordOrSelection(fmt);
};

/**
 * Called when user changes font size.
 */
TextDialog.prototype.textSize = function(p) {
    var pointSize = parseFloat(p);
    if (pointSize > 0) {
        var fmt = new QTextCharFormat();
        fmt.setFontPointSize(pointSize * this.fontHeightFactor);
        this.mergeFormatOnWordOrSelection(fmt);
    }
};

/**
 * Called when user changes font color.
 */
TextDialog.prototype.textColor = function() {
    var menu = new QMenu(this.dialog);

    var colorList = RColor.getList(false);

    for (var i=0; i < colorList.length; ++i) {
        var label = colorList[i][0];
        var color = colorList[i][1];
        var action = menu.addAction(RColor.getIcon(color, new QSize(16,16)), label);
        action.setProperty("color", color);
    }

    var chosenAction = menu.exec(QCursor.pos());
    if (isNull(chosenAction)) {
        return;
    }

    var chosenColor = chosenAction.property("color");
    if (chosenColor.isValid()) {
        if (chosenColor.isByLayer()) {
            chosenColor = RColor.CompatByLayer;
        }
        else if (chosenColor.isByBlock()) {
            chosenColor = RColor.CompatByBlock;
        }
        else {
            chosenColor = new QColor(chosenColor.red(), chosenColor.green(), chosenColor.blue(), chosenColor.alpha());
        }
    }
    else {
        // custom color: show color dialog:
        chosenColor = QColorDialog.getColor(this.textEdit.textColor(), this.dialog);
        if (!chosenColor.isValid()) {
            // color dialog canceled:
            return;
        }
    }

    var fmt = new QTextCharFormat();
    fmt.setForeground(chosenColor);
    this.mergeFormatOnWordOrSelection(fmt);
    this.colorChanged(chosenColor);
};

/**
 * Called when user is about to insert a symbol (special character).
 */
TextDialog.prototype.textSymbol = function() {
    var action;
    
    var menu = new QMenu(this.dialog);
    
    // common special characters
    var textWidget = this.dialog.findChild("Text");
    var charsMap = this.getSpecialCharsMap();
    var keys = charsMap.getKeys();
    for (var i = 0; i < keys.length; ++i) {
        var str = charsMap.get(keys[i])[0];
        var character = charsMap.get(keys[i])[1];
        action = menu.addAction(str + "\t" + character);
        var menuData = new SymbolMenuData(textWidget, character);
        action.triggered.connect(menuData, "triggered");
    }

    // other characters
    menu.addSeparator();
    action = menu.addAction(qsTr("Others..."));
    action.triggered.connect(this, function(){
        var dlg = new CharacterMapDialog(this);
        dlg.show();
    });
    
    menu.exec(QCursor.pos());
};

/**
 * Character format under cursor changed. Update relevant controls.
 */
TextDialog.prototype.currentCharFormatChanged = function(format) {
    this.fontChanged(format.font());
    this.colorChanged(format.foreground().color());

    this.actionSubscript.setChecked(format.verticalAlignment()==QTextCharFormat.AlignSubScript);
    this.actionSuperscript.setChecked(format.verticalAlignment()==QTextCharFormat.AlignSuperScript);
};

/**
 * Called when user changes the current font or the font under the cursor changed.
 */
TextDialog.prototype.fontChanged = function(font) {
    activateFont(this.comboFont, font.family());

    this.comboSize.blockSignals(true);
    this.comboSize.setEditText("%1".arg(font.pointSizeF() / this.fontHeightFactor));
    this.comboSize.blockSignals(false);

    this.actionTextBold.setChecked(font.bold());
    this.actionTextItalic.setChecked(font.italic());
    this.actionTextUnderline.setChecked(font.underline());
};

/**
 * Called when user changes the current color or the color under the cursor changed.
 */
TextDialog.prototype.colorChanged = function(c) {
    if (!RSettings.hasDarkGuiBackground()) {
        // make sure that very bright text is readable:
        if (c.lightness()>240) {
            var p = this.textEdit.palette;
            p.setColor(QPalette.Active, QPalette.Base, new QColor(Qt.lightGray));
            this.textEdit.palette = p;
        }
    }

    var pix = new QPixmap(16, 16);
    pix.fill(c);
    this.actionTextColor.icon = new QIcon(pix);
};

TextDialog.prototype.cursorPositionChanged = function() {
    //alignmentChanged(textEdit->alignment());
};

/**
 * Called to switch to default line spacing (factor 1.0).
 */
/*
TextDialog.prototype.useDefaultLineSpacing = function(checked) {
    var editLineSpacingFactor = this.dialog.findChild("LineSpacingFactor");
    if (checked) {
        editLineSpacingFactor.text = "1.0";
    }
    editLineSpacingFactor.enabled = !checked;
};
*/

/**
 * Called when clipboard text becomes available / unavailable.
 */
TextDialog.prototype.clipboardDataChanged = function() {
    if (isDeleted(this.actionPaste)) {
        return;
    }

    this.actionPaste.setEnabled(!getClipboard().text().isEmpty());
};

TextDialog.prototype.tabChanged = function(index) {
    switch (index) {
    case 0:
        this.updateRichText(false);
        break;

    case 1:
        this.updateSource(false);
        break;
    }
};

/**
 * Updates the source based on the rich text edit.
 */
TextDialog.prototype.updateSource = function(force) {
    if (this.getTextDocument().modified || force===true) {
        var html = this.textEdit.html;
        html = this.fixHtml(html);
        var textDocument = new QTextDocument();
        textDocument.setHtml(html);
        textDocument.defaultFont = this.getTextDocument().defaultFont;
        var cbSimpleText = this.dialog.findChild("SimpleText");
        var source = RTextBasedData.toEscapedText(textDocument, this.initialColor, this.fontHeightFactor, cbSimpleText.checked);
        //qDebug("source: \n\n", source, "\n\n");
        this.sourceEdit.setPlainText(source);
        this.getTextDocument().modified = false;
    }
};

/**
 * Updates the rich text edit based on the source.
 */
TextDialog.prototype.updateRichText = function(force) {
    if (this.getSourceDocument().modified || force===true) {
        var source = this.getSourceDocument().toPlainText();
        source = source.replace("\n", "\\P");
        var richText = RTextBasedData.toRichText(source, this.getMainFont(), this.fontHeightFactor);
        //richText = richText.replace("<html>", "<html xmlns='http://www.w3.org/1999/xhtml' xml:space='preserve'>");
        //qDebug("richText: \n\n", richText, "\n\n");
        this.textEdit.setHtml(richText);
        //qDebug("HTML from text edit: \n\n", this.textEdit.html, "\n\n");
        this.getSourceDocument().modified = false;
    }
};

//TextDialog.prototype.activateFont = function(fontComboBox, fontName) {
//    var index = fontComboBox.findText(fontName, Qt.MatchFixedString);
//    fontComboBox.setCurrentIndex(index);
//};

TextDialog.prototype.getSpecialCharsMap = function() {
    if (isNull(TextDialog.specialChars)) {
        TextDialog.specialChars = new Map();
        TextDialog.specialChars.put("degree", [ qsTr("Degree"), "\u00B0" ]);
        TextDialog.specialChars.put("plus_minus", [ qsTr("Plus-Minus"), "\u00B1" ]);
        //TextDialog.specialChars.put("diameter", [ qsTr("Diameter"), "\u2300" ]);
        TextDialog.specialChars.put("diameter", [ qsTr("Diameter"), "\u00F8" ]);
        TextDialog.specialChars.put("allmost_equal", [ qsTr("Almost equal"), "\u2248" ]);
        TextDialog.specialChars.put("multiplication", [ qsTr("Multiplication"), "\u00D7" ]);
        TextDialog.specialChars.put("division", [ qsTr("Division"), "\u00F7" ]);
        TextDialog.specialChars.put("delta", [ qsTr("Delta"), "\u0394" ]);
        TextDialog.specialChars.put("pi", [ qsTr("Pi"), "\u03C0" ]);
        TextDialog.specialChars.put("identity", [ qsTr("Identity"), "\u2261" ]);
        TextDialog.specialChars.put("not_equal", [ qsTr("Not equal"), "\u2260" ]);
        TextDialog.specialChars.put("ohm", [ qsTr("Ohm"), "\u2126" ]);
        TextDialog.specialChars.put("omega", [ qsTr("Omega"), "\u03A9" ]);
        TextDialog.specialChars.put("squared", [ qsTr("Squared"), "\u00B2" ]);
        TextDialog.specialChars.put("cubed", [ qsTr("Cubed"), "\u00B3" ]);
        TextDialog.specialChars.put("nbsp", [ qsTr("No-break space"), "&nbsp;" ]);
    }
    return TextDialog.specialChars;
};
