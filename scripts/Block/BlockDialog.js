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

include("../WidgetFactory.js");

/**
 * \class BlockDialog
 * \ingroup ecma_block
 *
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
    
    this.dialog = WidgetFactory.createDialog(BlockDialog.includeBasePath, "BlockDialog.ui", EAction.getMainWindow());
    //this.dialog.windowIcon = new QIcon(BlockDialog.includeBasePath + "/EditBlock/EditBlock.svg");

    var widgets = getWidgets(this.dialog);
    var leBlockName = widgets["BlockName"];
    leBlockName.selectAll();
    var rx = new RegExp("[^<>/\\\\\":;\?\*|,=`]{1,255}");
    this.validator = new QRegExpValidator(rx, leBlockName);
    leBlockName.setValidator(this.validator);
    leBlockName.textChanged.connect(this, "validate");

    // init dialog to show attributes of given block:
    if (!isNull(this.block)) {
        leBlockName.text = this.block.getName();
        if (leBlockName.text.startsWith("*")) {
            leBlockName.enabled = false;
        }
    }

    this.dialog.show();

    if (isNull(this.block)) {
        var c = 0;
        while (!this.validate()) {
            ++c;
            leBlockName.text = "block " + c;
        }
    }

    if (!this.dialog.exec()) {
        this.dialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    var text = leBlockName.text.trim();
    if (!isNull(this.block)) {
        this.block.setName(text);
        return this.block;
    }
    //this.dialog.setAttribute(Qt.WA_DeleteOnClose);
    //this.dialog.close();
    var block = new RBlock(this.document, text, new RVector(0,0));
    this.dialog.destroy();
    EAction.activateMainWindow();
    return block;
};

/**
 * Block name validation.
 */
BlockDialog.prototype.validate = function() {
    var widgets = getWidgets(this.dialog);

    var leBlockName = widgets["BlockName"];
    var message = widgets["Message"];
    var pos = 0;
    var acceptable = true;
    message.clear();

    if (leBlockName.text!==leBlockName.text.trim()) {
        message.text = "<font color='red'>" + qsTr("Leading or trailing spaces.") + "</font>";
        acceptable = false;
    }

    if (leBlockName.text.isEmpty()) {
        message.text = "<font color='red'>" + qsTr("Block name is empty.") + "</font>";
        acceptable = false;
    }
    else {
        if (this.validator.validate(leBlockName.text, pos) != QValidator.Acceptable) {
            message.text = "<font color='red'>" + qsTr("Block name is invalid.") + "</font>";
            acceptable = false;
        }
    }

    if (this.document.hasBlock(leBlockName.text)) {
        if (isNull(this.block) ||
            this.block.getName().toLowerCase() !== leBlockName.text.toLowerCase()) {

            message.text = "<font color='red'>" + qsTr("Block already exists.") + "</font>";
            acceptable = false;
        }
    }

    widgets["ButtonBox"].button(QDialogButtonBox.Ok).enabled = acceptable;
    return acceptable;
};
