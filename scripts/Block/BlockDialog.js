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
function BlockDialog(document, block, allowOverwrite, allowSameName) {
    if (isNull(allowOverwrite)) {
        allowOverwrite = true;
    }
    if (isNull(allowSameName)) {
        allowSameName = false;
    }

    this.dialog = null;
    this.document = document;
    this.block = block;
    this.allowOverwrite = allowOverwrite;
    this.allowSameName = allowSameName;
}

BlockDialog.includeBasePath = includeBasePath;

BlockDialog.prototype.show = function() {
    var lt;
    
    this.dialog = WidgetFactory.createDialog(BlockDialog.includeBasePath, "BlockDialog.ui", EAction.getMainWindow());

    var widgets = getWidgets(this.dialog);
    var leBlockName = widgets["BlockName"];
    var rx = new RegExp("[^<>/\\\\\":;\?\*|,=`]{1,255}");
    this.validator = new QRegExpValidator(rx, leBlockName);
    leBlockName.setValidator(this.validator);
    leBlockName.textChanged.connect(this, "validate");
    var creatingBlock = isNull(this.block);

    if (!creatingBlock) {
        // user is editing an existing block:
        // init dialog to show attributes of given block:
        leBlockName.text = this.block.getName();
        if (leBlockName.text.startsWith("*")) {
            leBlockName.enabled = false;
        }
        if (!this.allowSameName) {
            // creating copy of block:
            // select name:
            leBlockName.selectAll();
        }
    }

    this.dialog.show();

    if (creatingBlock) {
        var c = 0;
        while (!this.validate()) {
            ++c;
            leBlockName.text = qsTr("block", "default block name prefix") + " " + c;
        }
        leBlockName.selectAll();
    }

    if (!this.dialog.exec()) {
        this.dialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    var text = leBlockName.text.trim();
	
    if (!creatingBlock) {
        // rename block:
        this.dialog.destroy();
        EAction.activateMainWindow();
        this.block.setName(text);
        return this.block;
    }
    else {
        // create new block:
        var block = new RBlock(this.document, text, new RVector(0,0));
        this.dialog.destroy();
        EAction.activateMainWindow();
        return block;
    }
};

/**
 * Block name validation.
 */
BlockDialog.prototype.validate = function() {
    var widgets = getWidgets(this.dialog);
    var leBlockName = widgets["BlockName"];
    return BlockDialog.validate(this.block, leBlockName.text, this.document, this.dialog, this.validator, this.allowOverwrite, this.allowSameName);
};

BlockDialog.validate = function(block, blockName, document, dialog, validator, allowOverwrite, allowSameName) {
    var creatingBlock = isNull(block);
    var widgets = getWidgets(dialog);

    var leBlockName = widgets["BlockName"];
    if (isNull(leBlockName)) {
        return false;
    }

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
        if (validator.validate(leBlockName.text, pos) != QValidator.Acceptable) {
            message.text = "<font color='red'>" + qsTr("Block name is invalid.") + "</font>";
            acceptable = false;
        }
    }

    var ret = acceptable;

    // block already exists:
    if (document.hasBlock(leBlockName.text)) {
        if (creatingBlock && allowOverwrite===true) {
            // warning: overwriting an existing block:
            message.text += "<font color='red'>" + qsTr("Block \"%1\" already exists<br>and will be overwritten.").arg(leBlockName.text.toString())  + "</font>";
            acceptable = true;
        }
        else if ((isNull(block) || block.getName().toLowerCase() !== leBlockName.text.toLowerCase()) && !allowSameName) {
            // error: renaming existing block to existing block name (not allowed):
            message.text = "<font color='red'>" + qsTr("Block already exists.") + "</font>";
            acceptable = false;
        }
        ret = false;
    }

    if (!isNull(widgets["ButtonBox"])) {
        widgets["ButtonBox"].button(QDialogButtonBox.Ok).enabled = acceptable;
    }

    return ret;
};
