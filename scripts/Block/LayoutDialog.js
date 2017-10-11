/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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
 * \class LayoutDialog
 * \ingroup ecma_block
 *
 * Creates a dialog to edit the attributes of a layout (currently name only).
 *
 * \param document RDocument the layout is in.
 * \param layout RLayout object to edit or undefined to create and return a new layout.
 */
function LayoutDialog(document, layout, allowOverwrite, allowSameName) {
    if (isNull(allowOverwrite)) {
        allowOverwrite = true;
    }
    if (isNull(allowSameName)) {
        allowSameName = false;
    }

    this.dialog = null;
    this.document = document;
    this.layout = layout;
    this.allowOverwrite = allowOverwrite;
    this.allowSameName = allowSameName;
}

LayoutDialog.includeBasePath = includeBasePath;

LayoutDialog.prototype.show = function() {
    var lt;
    
    this.dialog = WidgetFactory.createDialog(LayoutDialog.includeBasePath, "LayoutDialog.ui", EAction.getMainWindow());

    var widgets = getWidgets(this.dialog);
    var leLayoutName = widgets["LayoutName"];
    leLayoutName.selectAll();
    var rx = new RegExp("[^<>/\\\\\":;\?\*|,=`]{1,255}");
    this.validator = new QRegExpValidator(rx, leLayoutName);
    leLayoutName.setValidator(this.validator);
    leLayoutName.textChanged.connect(this, "validate");
    var creatingLayout = isNull(this.layout);

    if (!creatingLayout) {
        // user is editing an existing layout:
        // init dialog to show attributes of given layout:
        leLayoutName.text = this.layout.getName();
        if (!this.allowSameName) {
            // creating copy of layout:
            // select name:
            leLayoutName.selectAll();
        }
    }

    this.dialog.show();

    if (creatingLayout) {
        var c = 0;
        while (!this.validate()) {
            ++c;
            leLayoutName.text = "layout " + c;
        }
    }

    if (!this.dialog.exec()) {
        this.dialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    var text = leLayoutName.text.trim();
	
    if (!creatingLayout) {
        // rename layout:
        this.dialog.destroy();
        EAction.activateMainWindow();
        this.layout.setName(text);
        return this.layout;
    }
    else {
        // create new layout:
        var layout = new RLayout(this.document, text, new RVector(0,0));
        this.dialog.destroy();
        EAction.activateMainWindow();
        return layout;
    }
};

/**
 * Layout name validation.
 */
LayoutDialog.prototype.validate = function() {
    var widgets = getWidgets(this.dialog);
    var leLayoutName = widgets["LayoutName"];
    return LayoutDialog.validate(this.layout, leLayoutName.text, this.document, this.dialog, this.validator, this.allowOverwrite);
};

LayoutDialog.validate = function(layout, layoutName, document, dialog, validator, allowOverwrite) {
    var creatingLayout = isNull(layout);
    var widgets = getWidgets(dialog);

    var leLayoutName = widgets["LayoutName"];
    if (isNull(leLayoutName)) {
        return false;
    }

    var message = widgets["Message"];
    var pos = 0;
    var acceptable = true;
    message.clear();

    if (leLayoutName.text!==leLayoutName.text.trim()) {
        message.text = "<font color='red'>" + qsTr("Leading or trailing spaces.") + "</font>";
        acceptable = false;
    }

    if (leLayoutName.text.isEmpty()) {
        message.text = "<font color='red'>" + qsTr("Layout name is empty.") + "</font>";
        acceptable = false;
    }
    else {
        if (validator.validate(leLayoutName.text, pos) != QValidator.Acceptable) {
            message.text = "<font color='red'>" + qsTr("Layout name is invalid.") + "</font>";
            acceptable = false;
        }
    }

    var ret = acceptable;

    // layout already exists:
    if (document.hasLayout(leLayoutName.text)) {
        if (creatingLayout && allowOverwrite===true) {
            // warning: overwriting an existing layout:
            message.text += "<font color='red'>" + qsTr("Layout '%1' already exists<br>and will be overwritten.").arg(leLayoutName.text.toString())  + "</font>";
            acceptable = true;
        }
        else if (isNull(layout) || layout.getName().toLowerCase() !== leLayoutName.text.toLowerCase() || !this.allowSameName) {
            // error: renaming existing layout to existing layout name (not allowed):
            message.text = "<font color='red'>" + qsTr("Layout already exists.") + "</font>";
            acceptable = false;
        }
        ret = false;
    }

    if (!isNull(widgets["ButtonBox"])) {
        widgets["ButtonBox"].button(QDialogButtonBox.Ok).enabled = acceptable;
    }

    return ret;
};
