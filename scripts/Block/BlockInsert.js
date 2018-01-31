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

include("Block.js");
 
/**
 * \class Block
 * \ingroup ecma_block
 * \brief Base action for actions that insert blocks from the drawing or
 * other sources.
 */
function BlockInsert(guiAction) {
    Block.call(this, guiAction);
    this.attributes = {};
}

BlockInsert.prototype = new Block();

BlockInsert.includeBasePath = includeBasePath;

BlockInsert.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    // hide attribute widgets by default:
    this.showAttributeControls(false);
};

BlockInsert.prototype.showAttributeControls = function(show) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var widgetActionNames = [
                "AttributeLabelAction",
                "AttributeTagAction",
                "AttributeEqualLabelAction",
                "AttributeValueAction",
                "AttributeSeparatorAction"
            ];

    for (var i=0; i<widgetActionNames.length; i++) {
        var widgetActionName = widgetActionNames[i];

        var w = optionsToolBar.findChild(widgetActionName);
        if (!isNull(w)) {
            w.visible = show;
        }
    }
};

BlockInsert.prototype.slotReset = function() {
    Block.prototype.slotReset.call(this);
    this.attributes = [];
    this.slotAttributeTagChanged();
};

BlockInsert.prototype.slotAttributeTagChanged = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var tagCombo = optionsToolBar.findChild("AttributeTag");
    var valueEdit = optionsToolBar.findChild("AttributeValue");

    var data = tagCombo.itemData(tagCombo.currentIndex);
    if (isNull(data)) {
        return;
    }

    var tag = data[0];
    var defaultValue = data[1];

    if (!isNull(this.attributes[tag])) {
        valueEdit.text = this.attributes[tag];
    }
    else {
        // init line edit with default value:
        valueEdit.text = data[1];
    }
};

BlockInsert.prototype.slotAttributeValueChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var tagCombo = optionsToolBar.findChild("AttributeTag");
    var valueEdit = optionsToolBar.findChild("AttributeValue");

    var data = tagCombo.itemData(tagCombo.currentIndex);
    if (isNull(data)) {
        return;
    }

    var tag = data[0];

    this.attributes[tag] = value;
};
