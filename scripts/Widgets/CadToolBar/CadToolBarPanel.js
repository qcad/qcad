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
        var backAction = new QAction(this);
        backAction.objectName = "Back";
        this.addAction(backAction);
        backAction.triggered.connect(CadToolBar, "back");
    }

    //this.actionAdded.connect(this, "handleNewAction");
}

CadToolBarPanel.prototype = new RWidget();

CadToolBarPanel.setBackMenuName = function(panel, name) {
    panel.setProperty("backMenuName", name);
};

CadToolBarPanel.prototype.toString = function() {
    return "CadToolBarPanel";
};

CadToolBarPanel.prototype.insertAction = function(before, action) {
//    if (action.text==="Line from &2 Points") {
        //qDebug("insertAction to CAD tool bar: ", action.text);
//    //}
    //QWidget.prototype.insertAction.call(this, before, action);
    this.addAction(action);
};

CadToolBarPanel.prototype.addAction = function(action) {
    //if (action.text==="Line from &2 Points") {
//        qDebug("addAction to CAD tool bar: ", action.text);
    //}

    if (action.isSeparator()) {
        //if (this.objectName==="LineToolsPanel") qDebug("addAction: separator");
        action.setProperty("SortOrder", action.getSortOrder());
        action.setProperty("GroupSortOrder", action.getGroupSortOrder());
        ColumnLayout.prototype.addItem.call(this.layout(), action);
        return;
    }

    var button = new QToolButton(this);
    button.setDefaultAction(action);
//    action.changed.connect(function() {
//        button.setProperty("VisibleOverride", action.visible);
//    });
    //button.setProperty("SortOrder", sortOrder);
    button.objectName = action.objectName;
    if (button.objectName.endsWith("Action")) {
        button.objectName = button.objectName.left(button.objectName.length-"Action".length);
    }
    button.objectName+="Button";
    var s = RSettings.getIntValue("CadToolBar/IconSize", 32);
    button.iconSize = new QSize(s, s);
//    if (isFunction(action.getSortOrder)) {
//        button.setProperty("SortOrder", ColumnLayout.getSortOrder(action));
//    }
    if (isNumber(action.property("GroupSortOrder"))) {
        button.setProperty("GroupSortOrder", ColumnLayout.getGroupSortOrder(action, this.objectName));
    }
    if (isNumber(action.property("SortOrder"))) {
        button.setProperty("SortOrder", ColumnLayout.getSortOrder(action, this.objectName));
    }
    if (button.objectName==="BackButton") {
        //button.arrowType=Qt.LeftArrow;
        button.icon = new QIcon("scripts/Widgets/CadToolBar/Back.svg");
        button.toolTip = qsTr("Back");
        button.sizePolicy = new QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum);
    }
    ColumnLayout.prototype.addItem.call(this.layout(), button);

    QWidget.prototype.addAction.call(this, action);
};

//CadToolBarPanel.prototype.resizeEvent = function(e) {
//    qDebug("CadToolBarPanel.resizeEvent");
//};
