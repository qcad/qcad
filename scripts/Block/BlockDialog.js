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

include("../WidgetFactory.js");

/**
 * Creates a dialog to edit the attributes of a block (currently name only).
 *
 * \param document RDocument the block is in.
 * \param block RBlock object to edit or undefined to create and return a new block.
 */
function BlockDialog(document, block) {
    this.dialog = null;
    this.document = document;
    this.block = block;
}

BlockDialog.includeBasePath = includeBasePath;

BlockDialog.prototype.show = function() {
    var lt;
    
    this.dialog = WidgetFactory.createDialog(BlockDialog.includeBasePath, "BlockDialog.ui");
    //this.dialog.windowIcon = new QIcon(BlockDialog.includeBasePath + "/EditBlock/EditBlock.svg");

    var widgets = getWidgets(this.dialog);
    var blockName = widgets["BlockName"];
    blockName.selectAll();
    var rx = new RegExp("[^<>/\\\\\":;\?\*|,=`]{1,255}");
    var validator = new QRegExpValidator(rx, blockName);
    blockName.setValidator(validator);
    blockName.textChanged.connect(this, "validate");

    // init dialog to show attributes of given block:
    if (!isNull(this.block)) {
        blockName.text = this.block.getName();
        if (blockName.text.startsWith("*")) {
            blockName.enabled = false;
        }
    }

    this.dialog.show();

    var c = 0;
    while (!this.validate()) {
        ++c;
        blockName.text = "block " + c;
    }

    if (this.dialog.exec()) {
        var text = blockName.text.trim();
        if (!isNull(this.block)) {
            this.block.setName(text);
            return this.block;
        }
        this.dialog.setAttribute(Qt.WA_DeleteOnClose);
        this.dialog.close();
        var block = new RBlock(this.document, text, new RVector(0,0));
        return block;
    }
};

/**
 * Block name validation.
 */
BlockDialog.prototype.validate = function() {
    var widgets = getWidgets(this.dialog);

    var leBlockName = widgets["BlockName"];
    var message = widgets["Message"];
    var validator = leBlockName.validator();
    var pos = 0;
    var acceptable = true;
    message.clear();
    if (validator.validate(leBlockName.text, pos) != QValidator.Acceptable) {
        message.text = "<font color='red'>" + qsTr("Block name is empty.") + "</font>";
        acceptable = false;
    }
    if (this.document.hasBlock(leBlockName.text)) {
        if (isNull(this.block) ||
            this.block.getName().toLowerCase() != leBlockName.text.toLowerCase()) {

            message.text = "<font color='red'>" + qsTr("Block already exists.") + "</font>";
            acceptable = false;
        }
    }
    widgets["ButtonBox"].button(QDialogButtonBox.Ok).enabled = acceptable;
    return acceptable;
};
