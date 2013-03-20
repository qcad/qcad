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

function ViewDialog(action, view) {
    this.formWidget = null;
    this.action = action;
    this.view = view;
}

ViewDialog.prototype.show = function() {
    this.formWidget = WidgetFactory.createHeaderDialog("scripts/View", "ViewDialog.ui");
    this.formWidget.objectName = "ViewDialog";
    this.formWidget.setWindowTitle(qsTr("View Data"));
    if (isNull(this.view)) {
        this.formWidget.setTitle(qsTr("Enter View Data"));
    } else {
        this.formWidget.setTitle(qsTr("Edit View Data"));
    }
    this.formWidget.setText(qsTr("Enter the name for the new view."));
    //this.formWidget.windowIcon = new QIcon("scripts/View/Edit/Edit.svg");
    var leViewName = this.formWidget.findChild("leViewName");
    leViewName.selectAll();
    var rx = new RegExp("[^<>/\\\\\":;\?\*|,=`]{1,255}");
    var validator = new QRegExpValidator(rx, leViewName);
    leViewName.setValidator(validator);
    leViewName.textChanged.connect(this, "validate");
    leViewName.setFocus(Qt.OtherFocusReason);
    var btOk = this.formWidget.findChild("OK");
    btOk.enabled = false;
    
    if (!isNull(this.view)) {
        leViewName.text = this.view.getName();
    }
    
    this.formWidget.show();
    
    var c = 0;
    while (!this.validate()) {
        ++c;
        leViewName.text = "view " + c;
    }
    
    if (this.formWidget.exec()) {
        var text = leViewName.text.trim();
        if (!isNull(this.view)) {
            this.view.setName(text);
            return this.view;
        }
        this.formWidget.setAttribute(Qt.WA_DeleteOnClose);
        this.formWidget.close();
        
        this.di = EAction.getDocumentInterface();
        var gv = this.di.getGraphicsViewWithFocus();
        if (isNull(gv)) {
            qWarning("ViewDialog.js:",
                    "show(): GraphicsViewWithFocus() is undefined");
            return undefined;
        }
        var doc = this.di.getDocument();
        var view = new RView(doc, text, gv.getBox().getCenter(), gv.getBox()
                .getSize().x, gv.getBox().getSize().y);
        return view;
    }
    return undefined;
};

ViewDialog.prototype.validate = function() {
    var leViewName = this.formWidget.findChild("leViewName");
    var validator = leViewName.validator();
    var pos = 0;
    var acceptable = true;
    if (validator.validate(leViewName.text, pos) != QValidator.Acceptable) {
        this.formWidget.setText("View name is emtpy.", true);
        acceptable = false;
    }
    if (this.action.getDocument().hasView(leViewName.text)) {
        if (isNull(this.view) || this.view.getName() != leViewName.text) {
            this.formWidget.setText("View already exists.", true);
            acceptable = false;
        }
    }
    if (acceptable) {
        this.formWidget.setText("");
    }
    var btOk = this.formWidget.findChild("OK");
    btOk.enabled = acceptable;
    return acceptable;
};
