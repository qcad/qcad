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
 * \defgroup ecma_draw_text Text Drawing Tool
 * \ingroup ecma_draw
 *
 * \brief This module contains the ECMAScript implementation of the text
 * drawing tool.
 */
include("scripts/Draw/Draw.js");
include("scripts/WidgetFactory.js");
include("TextDialog/TextDialog.js");

/**
 * \class Text
 * \brief Insert text.
 * \ingroup ecma_draw_text
 */
function Text(guiAction, mode) {
    if (isNull(mode)) {
        mode = TextDialog.Mode.Text;
    }

    Draw.call(this, guiAction);

    this.textData = undefined;

    this.mode = mode;

    this.setUiOptions("Text.ui");
}

Text.prototype = new Draw();

Text.State = {
    SettingPosition : 0
};

Text.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    var dialog = new TextDialog(this.mode);
    this.textData = dialog.show();
    if (isNull(this.textData)) {
        this.terminate();
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();

    var contentsEdit = optionsToolBar.findChild("Contents");
    WidgetFactory.initLineEdit(contentsEdit, false);
    contentsEdit.text = this.textData.getEscapedText();

    var heightEdit = optionsToolBar.findChild("Height");
    heightEdit.setValue(this.textData.getTextHeight());

    var angleEdit = optionsToolBar.findChild("Angle");
    angleEdit.setValue(this.textData.getAngle());

    this.setState(Text.State.SettingPosition);
};

Text.prototype.setState = function(state) {
    Draw.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var tr = qsTr("Position");
    this.setLeftMouseTip(tr);
    this.setCommandPrompt(tr);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

Text.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    var pos = event.getModelPosition();
    if (!preview) {
        di.setRelativeZero(pos);
    }
    this.textData.setAlignmentPoint(pos);

    if (preview) {
        this.updatePreview();
    }
    else {
        this.applyOperation();
    }
};

Text.prototype.getOperation = function(preview) {
    if (isNull(this.textData)) {
        return undefined;
    }

    var text;
    if (isOfType(this.textData, RAttributeDefinitionData)) {
        text = new RAttributeDefinitionEntity(this.getDocument(), this.textData);
    }
    else {
        text = new RTextEntity(this.getDocument(), this.textData);
    }

    return new RAddObjectOperation(text, this.getToolTitle());
};

Text.prototype.slotContentsChanged = function(value) {
    if (isNull(this.textData)) {
        return;
    }

    this.textData.setText(value);
    this.updatePreview(true);
};

Text.prototype.slotHeightChanged = function(value) {
    if (isNull(this.textData)) {
        return;
    }

    this.textData.setTextHeight(value);
    this.updatePreview(true);
};

Text.prototype.slotAngleChanged = function(value) {
    if (isNull(this.textData)) {
        return;
    }

    this.textData.setAngle(value);
    this.updatePreview(true);
};
