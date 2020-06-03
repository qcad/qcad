/**
 * Copyright (c) 2015 by Robert S. All rights reserved.
 *               2020 by Andrew Mustun (refactor, add number format instead of precision)
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
 * \class Counter
 * \ingroup ecma_misc_draw
 *
 * \brief Implementation of the auto increment number text tool.
 */
include("scripts/EAction.js");
include("numeral.js");

/**
 * \class Counter
 * \brief Auto increment numbers.
 * \ingroup ecma_misc_miscdraw
 */
function Counter(guiAction) {
    EAction.call(this, guiAction);

    this.position = undefined;
    this.start = 1;
    this.increment = 1;
    this.numberFormat = "0";
    this.prefix = "";
    this.suffix = "";

    this.setUiOptions("Counter.ui");
}

Counter.prototype = new EAction();

Counter.State = {
    SettingPosition : 0
};

Counter.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(Counter.State.SettingPosition);
};

Counter.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPosition = qsTr("Position");
    this.setCommandPrompt(trPosition);
    this.setLeftMouseTip(trPosition);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

Counter.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    this.position = event.getModelPosition();

    var op = this.getOperation();
    if (preview) {
        di.previewOperation(op);
    }
    else {
        di.applyOperation(op);
        di.setRelativeZero(this.position);
        // set start number to start number + increment
        this.start = this.start + this.increment;
        var optionsToolBar = EAction.getOptionsToolBar();
        if (!isNull(optionsToolBar)) {
            var leStart = optionsToolBar.findChild("Start");
            leStart.text = Number((this.start).toFixed(4));
        }
    }
};

Counter.prototype.getOperation = function() {
    if (!isVector(this.position)) {
        return undefined;
    }

    var di = this.getDocumentInterface();
    var doc = di.getDocument();

    var pos = this.position;
    var str;

    if (this.numberFormat.length>0) {
        var num = numeral(this.start);
        str = num.format(this.numberFormat);
    }
    else {
        str = this.start.toFixed(0);
    }

    str = this.prefix + str + this.suffix;

    var fontName = RSettings.getStringValue("TextDialog/Font", "Arial");
    var fontHeight = RSettings.getDoubleValue("TextDialog/Height", 1.0);
    var fontWidth = RSettings.getDoubleValue("TextDialog/Width", 0.0);
    var fontValign = RSettings.getIntValue("TextDialog/VAlignment", 0);
    var fontHalign = RSettings.getIntValue("TextDialog/HAlignment", 0);
    var fontAngle = RSettings.getDoubleValue("TextDialog/Angle", 0.0);
    var fontBold = RSettings.getBoolValue("TextDialog/Bold", false);
    var fontItalic = RSettings.getBoolValue("TextDialog/Italic", false);
    var fontLineSpacingFactor = RSettings.getDoubleValue("TextDialog/LineSpacingFactor", 1.0);

    var td = new RTextData();
    td.setAlignmentPoint(pos);
    td.setVAlign(fontValign);
    td.setHAlign(fontHalign);
    td.setText(str);
    td.setTextHeight(fontHeight);
    td.setTextWidth(fontWidth);
    td.setFontName(fontName);
    td.setAngle(deg2rad(fontAngle));
    td.setBold(fontBold);
    td.setItalic(fontItalic);
    td.setLineSpacingFactor(fontLineSpacingFactor);
    var text = new RTextEntity(doc, td);
    var op = new RAddObjectOperation(text, this.getToolTitle());

    return op;
};

Counter.prototype.slotStartChanged = function(value) {
    this.start = value;
    this.updatePreview(true);
};

Counter.prototype.slotIncrementChanged = function(value) {
    this.increment = value;
};


Counter.prototype.slotNumberFormatChanged = function(value) {
    this.numberFormat = value;
    this.updatePreview(true);
};

Counter.prototype.slotPrefixChanged = function(value) {
    this.prefix = value;
    this.updatePreview(true);
};

Counter.prototype.slotSuffixChanged = function(value) {
    this.suffix = value;
    this.updatePreview(true);
};
