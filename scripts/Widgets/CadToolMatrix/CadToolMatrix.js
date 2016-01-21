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
    this.setLayout(layout);

    //this.minimumSize = new QSize(100, 100);
    //this.sizeHint = new QSize(100,100);
}

RCadToolMatrixTreePanel.prototype = new QWidget();

//RCadToolMatrixTreePanel.prototype.sizeHint = function() {
//    qDebug("RCadToolMatrixTreePanel.prototype.sizeHint");
//    return new QSize(100,300);
//};

//RCadToolMatrixTreePanel.prototype.hasHeightForWidth = function() {
//    qDebug("RCadToolMatrixTreePanel.prototype.hasHeightForWidth");
//    return true;
//};

RCadToolMatrixTreePanel.prototype.actionEvent = function(event) {
    var action = event.action();
    //qDebug("action event: ", action);

    /*
    //var widgetAction = qobject_cast<QWidgetAction*>(action);

    if (layout==NULL) {
        // first action added: add widget with flow layout to dock:
        QWidget* w = new QWidget();
        layout = new RFlowLayout(2,2,2);
        w->setLayout(layout);
        setWidget(w);
    }
    */

    var layout = this.layout();
    var index;

    switch (event.type()) {
    case QEvent.ActionAdded:
//        qDebug("action added");
//        qDebug("layout: ", layout);
//        qDebug("action added: before: ", event.before());
        index = layout.count();
        if (event.before()) {
//            debugger;
            index = layout.indexOf(event.before().getQAction());
//            qDebug("action added: index: ", index);
        }
        layout.insertAction(index, action);
        break;

    case QEvent.ActionChanged:
        layout.invalidate();
        break;

    case QEvent.ActionRemoved: {
        index = layout.indexOf(action);
        if (index !== -1) {
            //delete layout->takeAt(index);
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

    this.indentation = 0;
    this.header().close();
    this.columnCount = 1;
    this.selectionMode = QAbstractItemView.NoSelection;
    if (RSettings.isQt(5)) {
        this.header().setSectionResizeMode(0, QHeaderView.Stretch);
    }
    else {
        this.header().setResizeMode(0, QHeaderView.Stretch);
    }

    this.itemPressed.connect(this, "handleMousePress");

//    var item = new QTreeWidgetItem();
//    item.setText(0, qsTr("Lines"));
//    this.addTopLevelItem(item);

//    var subItem = new QTreeWidgetItem();
//    var matrix = new QWidget();
//    var layout = new RFlowLayout(2,2,2);
//    matrix.setLayout(layout);
//    layout.addWidget(new QToolButton());
//    //matrix.minimumSize = new QSize(100, 100);
//    matrix.autoFillBackground = true;
//    item.addChild(subItem);

//    this.setItemWidget(subItem, 0, matrix);

    //this.expandAll();

    //var treeWidget = new RTreeWidget(this);

//    var layout = new QVBoxLayout();
//    layout.objectName = "Layout";
//    layout.setContentsMargins(0,0,0,0);
//    this.setLayout(layout);
}

RCadToolMatrixTree.prototype = new RTreeWidget();

RCadToolMatrixTree.prototype.resizeEvent = function(event) {
    RTreeWidget.prototype.resizeEvent.call(this, event);
    //qDebug("resize");

    for (var i=0; i<this.topLevelItemCount; i++) {
        var item = this.topLevelItem(i);
        var subItem = item.child(0);
        var embeddedWidget = this.itemWidget(subItem, 0);
        var width = this.header().width;
        embeddedWidget.setFixedWidth(width);
        //w.setFixedHeight(100);
        //subItem.setSizeHint(0, new QSize(-1, 100));
        //qDebug("sizeHint: ", embeddedWidget.sizeHint);
        var height = embeddedWidget.layout().heightForWidth(width);
        //qDebug("heightForWidth: ", height);
        embeddedWidget.setFixedHeight(height);
        //subItem.setSizeHint(0, embeddedWidget.sizeHint);
        subItem.setSizeHint(0, new QSize(width, height));
    }
};

RCadToolMatrixTree.prototype.handleMousePress = function(item) {
    qDebug("mouse press");

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

//RCadToolMatrixTree.getPreferencesCategory = function() {
//    return [qsTr("Widgets"), qsTr("CAD Tool Matrix")];
//};

//RCadToolMatrixTree.applyPreferences = function(doc) {
//};

//RCadToolMatrixTree.prototype.contextMenuEvent = function(event) {
//};



function CadToolMatrix(guiAction) {
    Widgets.call(this, guiAction);
}

CadToolMatrix.prototype = new Widgets();
CadToolMatrix.includeBasePath = includeBasePath;

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
        item.setText(0, title/* + "_" + order*/);
        item.setData(0, Qt.UserRole, order);
        var found = false;
        for (var i=0; i<tm.topLevelItemCount; i++) {
            var topLevelItem = tm.topLevelItem(i);
            var o = topLevelItem.data(0, Qt.UserRole);
            qDebug("existing order:", o);
            if (o>order) {
                //debugger;
                tm.insertTopLevelItem(i, item);
                found = true;
                break;
            }
        }

        if (!found) {
            tm.addTopLevelItem(item);
        }
        //tm.insertTopLevelItem(i, item);
        //qDebug("add item: ", title);
    }
    else {
        item = items[0];
    }

    var subItem = new QTreeWidgetItem();
    //subItem.setText(0, title);
    dw = new RCadToolMatrixTreePanel();
    dw.objectName = objectName;
    //var layout = new RFlowLayout(2,2,2);
    //dw.setLayout(layout);
    //layout.addWidget(new QToolButton());
    //matrix.minimumSize = new QSize(100, 100);
    dw.autoFillBackground = true;
    item.addChild(subItem);
    tm.setItemWidget(subItem, 0, dw);
    tm.expandAll();

    return dw;
};

CadToolMatrix.init = function(basePath) {
};
