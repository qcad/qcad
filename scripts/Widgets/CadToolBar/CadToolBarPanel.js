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

// don't include ColumnLayout here, causes maximum call stack reached
// include before CadToolBarPanel.js instead
//include("ColumnLayout.js");

function CadToolBarPanel(parent, hasBackButton) {
    RWidget.call(this, parent);

    var layout = new ColumnLayout(
        this, parent.parentWidget(), RSettings.getIntValue("CadToolBar/IconSize", 32) * 1.25
    );
    this.setLayout(layout);
    this.sizePolicy = new QSizePolicy(
        QSizePolicy.MinimumExpanding,
        QSizePolicy.MinimumExpanding
    );

    this.backMenuName = "MainToolsPanel";

    if (hasBackButton) {
        var backAction = new RGuiAction(qsTr("Back"), this);
        backAction.objectName = "Back";
        backAction.checkable = false;
        backAction.setIcon(autoPath("scripts/Widgets/CadToolBar/Back.svg"));
        this.addAction(backAction);
        backAction.triggered.connect(CadToolBar, "back");
    }
}

CadToolBarPanel.prototype = new RWidget();

CadToolBarPanel.setBackMenuName = function(panel, name) {
    panel.setProperty("backMenuName", name);
};

CadToolBarPanel.prototype.toString = function() {
    return "CadToolBarPanel";
};

CadToolBarPanel.getButtonName = function(action) {
    var buttonName = action.objectName;
    if (buttonName.endsWith("Action")) {
        buttonName = buttonName.left(buttonName.length-"Action".length);
    }
    buttonName+="Button";
    return buttonName;
};

CadToolBarPanel.prototype.removeAction = function(action) {
    ColumnLayout.prototype.removeAction.call(this.layout(), action);
    QWidget.prototype.removeAction.call(this, action);

    var buttonName = CadToolBarPanel.getButtonName(action);
    var w = this.findChild(buttonName);
    if (!isNull(w)) {
        w.visible = false;
    }
};

CadToolBarPanel.prototype.insertAction = function(before, action) {
    this.addAction(action);
//    QWidget.prototype.insertAction.call(this, before, action);
};

CadToolBarPanel.prototype.addAction = function(action) {
    if (action.isSeparator()) {
        action.setProperty("SortOrder", action.getSortOrder());
        action.setProperty("GroupSortOrder", action.getGroupSortOrder());
        ColumnLayout.prototype.addItem.call(this.layout(), action);
        return;
    }

    var buttonName = CadToolBarPanel.getButtonName(action);

    // check if button already exists for this action:
    var button = this.findChild(buttonName);
    if (isNull(button)) {
        button = new QToolButton(this);
    }
    button.visible = true;
    button.setDefaultAction(action);
    button.objectName = buttonName;
    var s = RSettings.getIntValue("CadToolBar/IconSize", 32);
    button.iconSize = new QSize(s, s);
    if (isNumber(action.property("GroupSortOrder"))) {
        button.setProperty("GroupSortOrder", ColumnLayout.getGroupSortOrder(action, this.objectName));
    }
    if (isNumber(action.property("SortOrder"))) {
        button.setProperty("SortOrder", ColumnLayout.getSortOrder(action, this.objectName));
    }
    if (button.objectName==="BackButton") {
        button.toolTip = qsTr("Back");
        button.sizePolicy = new QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum);
    }

    ColumnLayout.prototype.addItem.call(this.layout(), button);
    QWidget.prototype.addAction.call(this, action);
};
