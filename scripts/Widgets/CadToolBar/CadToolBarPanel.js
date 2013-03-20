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

include("ColumnLayout.js");

function CadToolBarPanel(parent, hasBackButton) {
    QWidget.call(this, parent);

    var layout = new ColumnLayout(
        this, RSettings.getIntValue("CadToolBar/IconSize", 32) * 1.25
    );
    this.setLayout(layout);
    this.sizePolicy = new QSizePolicy(
        QSizePolicy.MinimumExpanding,
        QSizePolicy.MinimumExpanding
    );

    this.backMenuName = "MainToolsPanel";

    if (hasBackButton) {
        var backAction = new QAction(this);
        backAction.objectName = "Back";
        this.addAction(backAction, 0);
        backAction.triggered.connect(CadToolBar, "back");
    }
}

CadToolBarPanel.prototype = new QWidget();

CadToolBarPanel.setBackMenuName = function(panel, name) {
    panel.setProperty("backMenuName", name);
};

CadToolBarPanel.prototype.addAction = function(action) {
    if (action.isSeparator()) {
        action.setProperty("SortOrder", action.getSortOrder());
        ColumnLayout.prototype.addItem.call(this.layout(), action);
        return;
    }

    var button = new QToolButton(this);
    button.setDefaultAction(action);
    //button.setProperty("SortOrder", sortOrder);
    button.objectName = action.objectName;
    if (button.objectName.endsWith("Action")) {
        button.objectName = button.objectName.left(button.objectName.length-"Action".length);
    }
    button.objectName+="Button";
    var s = RSettings.getIntValue("CadToolBar/IconSize", 32);
    button.iconSize = new QSize(s, s);
    if (isFunction(action.getSortOrder)) {
        button.setProperty("SortOrder", action.getSortOrder());
    }
    if (isNumber(action.property("SortOrder"))) {
        button.setProperty("SortOrder", action.property("SortOrder"));
    }
    if (button.objectName=="BackButton") {
        //button.arrowType=Qt.LeftArrow;
        button.icon = new QIcon("scripts/Widgets/CadToolBar/Back.svg");
        button.toolTip = qsTr("Back");
    }
    ColumnLayout.prototype.addItem.call(this.layout(), button);
};
