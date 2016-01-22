/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

function RCadToolMatrixTreePanel(parent) {
    QWidget.call(this, parent);

    var layout = new RFlowLayout(2,2,2);
    //layout.sizeConstraint = QLayout.SetMinimumSize;
    //layout.sizeConstraint = QLayout.SetFixedSize;
    var iconSize = RSettings.getIntValue("CadToolMatrix/IconSize", 20);
    layout.setIconSize(new QSize(iconSize, iconSize));
    this.setLayout(layout);
}

RCadToolMatrixTreePanel.prototype = new QWidget();

RCadToolMatrixTreePanel.prototype.actionEvent = function(event) {
    var action = event.action();

    var layout = this.layout();
    var index;

    switch (event.type()) {
    case QEvent.ActionAdded:
        index = layout.count();
        if (event.before()) {
            index = layout.indexOf(event.before().getQAction());
        }
        layout.insertAction(index, action);
        break;

    case QEvent.ActionChanged:
        layout.invalidate();
        break;

    case QEvent.ActionRemoved: {
        index = layout.indexOf(action);
        if (index !== -1) {
            var w = layout.takeAt(index);
            w.destroy();
        }
        break;
    }

    default:
        break;
    }
};


/**
 * CAD tool matrix tree widget.
 */
function RCadToolMatrixTree(parent) {
    RTreeWidget.call(this, parent);

    //var buttonSize = RSettings.getIntValue("CadToolMatrix/IconSize", 32) * 1.25;

    this.header().hide();
    this.indentation = 0;
    this.rootIsDecorated = false;
    this.columnCount = 1;
    this.selectionMode = QAbstractItemView.NoSelection;
    this.verticalScrollMode = QAbstractItemView.ScrollPerPixel;
    if (RSettings.isQt(5)) {
        this.header().setSectionResizeMode(0, QHeaderView.Stretch);
    }
    else {
        this.header().setResizeMode(0, QHeaderView.Stretch);
    }

    this.setItemDelegate(new RToolMatrixItemDelegate(this, this));

    this.itemPressed.connect(this, "handleMousePress");
}

RCadToolMatrixTree.prototype = new RTreeWidget();

RCadToolMatrixTree.prototype.resizeEvent = function(event) {
    RTreeWidget.prototype.resizeEvent.call(this, event);

    for (var i=0; i<this.topLevelItemCount; i++) {
        var item = this.topLevelItem(i);
        var subItem = item.child(0);
        var embeddedWidget = this.itemWidget(subItem, 0);
        var width = this.header().width;
        embeddedWidget.setFixedWidth(width);
        var height = embeddedWidget.layout().heightForWidth(width);
        embeddedWidget.setFixedHeight(height);
        subItem.setSizeHint(0, new QSize(width, height));
    }
};

/**
 * Expand / collapse with single click.
 */
RCadToolMatrixTree.prototype.handleMousePress = function(item) {
    if (isNull(item)) {
        return;
    }

    if (QGuiApplication.mouseButtons().valueOf() !== Qt.LeftButton.valueOf()) {
        return;
    }

    if (isNull(item.parent())) {
        item.setExpanded(!item.isExpanded());
        return;
    }
};




function CadToolMatrix(guiAction) {
    Widgets.call(this, guiAction);
}

CadToolMatrix.prototype = new Widgets();
CadToolMatrix.includeBasePath = includeBasePath;

CadToolMatrix.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("CAD Tool Matrix")];
};

CadToolMatrix.getToolMatrix = function() {
    var appWin = EAction.getMainWindow();

    var toolMatrix = appWin.findChild("ToolMatrix");
    if (isNull(toolMatrix)) {
        var formWidget = WidgetFactory.createWidget(CadToolMatrix.includeBasePath, "CadToolMatrix.ui");
        var layout = formWidget.findChild("VerticalLayout");
        toolMatrix = new RCadToolMatrixTree(appWin);
        toolMatrix.objectName = "ToolMatrix";
        layout.addWidget(toolMatrix, 1, 0);

        var dock = new RDockWidget(qsTr("CAD Tools"), appWin);
        dock.objectName = "CadToolMatrix";
        dock.setWidget(formWidget);
        appWin.addDockWidget(Qt.LeftDockWidgetArea, dock);
    }

    return toolMatrix;
};

CadToolMatrix.getToolMatrixPanel = function(title, objectName, order) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }

    var dw = appWin.findChild(objectName);
    if (!isNull(dw)) {
        return dw;
    }

    title = title.replace("&", "");

    var tm = CadToolMatrix.getToolMatrix();

    var flags = new Qt.MatchFlags(Qt.MatchFixedString | Qt.MatchRecursive);
    var items = tm.findItems(title, flags);
    var item;
    if (items.length===0) {
        item = new QTreeWidgetItem();
        item.setChildIndicatorPolicy(QTreeWidgetItem.ShowIndicator);
        item.setText(0, title/* + "_" + order*/);
        item.setData(0, Qt.UserRole, order);
        var found = false;
        for (var i=0; i<tm.topLevelItemCount; i++) {
            var topLevelItem = tm.topLevelItem(i);
            var o = topLevelItem.data(0, Qt.UserRole);
            if (o>order) {
                tm.insertTopLevelItem(i, item);
                found = true;
                break;
            }
        }

        if (!found) {
            tm.addTopLevelItem(item);
        }
    }
    else {
        item = items[0];
    }

    var subItem = new QTreeWidgetItem();
    dw = new RCadToolMatrixTreePanel();
    dw.objectName = objectName;
    dw.autoFillBackground = true;
    item.addChild(subItem);
    tm.setItemWidget(subItem, 0, dw);
    tm.expandAll();

    return dw;
};

CadToolMatrix.init = function(basePath) {
};
