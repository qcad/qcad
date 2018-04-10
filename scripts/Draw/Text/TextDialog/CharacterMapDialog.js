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
 * \class CharacterMapDialog
 * \brief Provides a character map dialog that shows available Unicode
 *      characters to insert into a text field.
 * \ingroup ecma_draw_text
 */
function CharacterMapDialog(parent) {
    this.parent = parent;
}

CharacterMapDialog.includeBasePath = includeBasePath;

CharacterMapDialog.prototype.show = function() {
    var font, pointSize;
    
    var dlg = WidgetFactory.createWidget(CharacterMapDialog.includeBasePath,
            "CharacterMapDialog.ui", this.parent.dialog);
    //dlg.windowIcon = new QIcon(autoPath("scripts/Draw/Text/Text.svg"));

    var characterMap = new RCharacterWidget(dlg);
    var fontFamily = this.parent.comboFont
            .itemText(this.parent.comboFont.currentIndex);
    var bold = this.parent.actionTextBold.checked ? true : false;
    var italic = this.parent.actionTextItalic.checked ? true : false;
    pointSize = this.parent.comboSize.itemText(this.parent.comboSize.currentIndex)
            * this.parent.fontHeightFactor;
    var style = "";
    style += bold ? "Bold" : "";
    style += italic ? " Italic" : "";
    font = new QFont(fontFamily, pointSize, bold ? QFont.Bold : QFont.Normal,
            italic);
    characterMap.updateFont(font);
    characterMap.updateSize(pointSize);
    characterMap.updateStyle(style);
    characterMap.updateFontMerging(true);

    characterMap.characterSelected.connect(this, function(character) {
        var textWidget = this.parent.dialog.findChild("Text");
        var cursor = textWidget.textCursor();
        cursor.insertText(character);
        
        var singleShot = new QTimer();
        singleShot.singleShot = true;
        singleShot.timeout.connect(this, function() {
            dlg.accept();
        });
        singleShot.start(250);
    });

    var widgets = getWidgets(dlg);
    widgets["ScrollArea"].setWidget(characterMap);
    widgets["ZoomIn"].clicked.connect(this, function() {
        font = characterMap.getDisplayFont();
        pointSize = font.pointSize();
        ++pointSize;
        characterMap.updateSize(pointSize);
        this.updateSlider(widgets["ZoomSlider"], pointSize);
    });
    widgets["ZoomOut"].clicked.connect(this, function() {
        font = characterMap.getDisplayFont();
        pointSize = font.pointSize();
        pointSize = Math.max(1, --pointSize);
        characterMap.updateSize(pointSize);
        this.updateSlider(widgets["ZoomSlider"], pointSize);
    });
    widgets["ZoomSlider"].valueChanged.connect(this, function(value) {
        pointSize = Math.max(1, Math.round(value / 2));
        characterMap.updateSize(pointSize);
    });

    font = characterMap.getDisplayFont();
    pointSize = font.pointSize();
    this.updateSlider(widgets["ZoomSlider"], pointSize);
    widgets["ScrollArea"].setFocus(Qt.MouseFocusReason);
    dlg.show();
};

CharacterMapDialog.prototype.updateSlider = function(slider, pointSize) {
    var value = Math.round(100 / 50 * pointSize);
    slider.setValue(value);
};
