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

/**
 * Represents a panel in the tool matrix. Panels are embedded as child items under
 * the root item of the appropriate category in the tool matrix tree.
 */
function RCadToolMatrixTreePanel(parent, objectName) {
    QWidget.call(this, parent);

    this.objectName = objectName;
    this.autoFillBackground = true;

    var layout = new RFlowLayout(1,1,1);
    var iconSize = RSettings.getIntValue("CadToolMatrix/IconSize", 24);
    layout.setIconSize(new QSize(iconSize, iconSize));
    this.setLayout(layout);

    //var pal = new QPalette();
    //var color = pal.color(QPalette.Active, QPalette.Window);
    //var colorName = color.name();
    //var colorLightName = color.lighter(105).name();

    if (!RSettings.hasCustomStyleSheet()) {
        this.styleSheet =
              //"QWidget#" + objectName + " { background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 " + colorName + ", stop:1 " + colorLightName + "); }"
             "QToolButton {"
            + "  border-style: none;"
            + "}"
            + RCadToolMatrixTreePanel.getCheckedStyle()
            + RCadToolMatrixTreePanel.getPressedStyle();
    }
}

RCadToolMatrixTreePanel.prototype = new QWidget();

RCadToolMatrixTreePanel.getCheckedStyle = function() {
    return "QToolButton:checked {"
            + "  border-radius: 4px; "
            + "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b7b7b7, stop: 0.8 #cfcfcf, stop: 1 #d1d1d1);"
            + "}";
};

RCadToolMatrixTreePanel.getPressedStyle = function() {
    return "QToolButton:pressed {"
            + "  border-radius: 4px; "
            + "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #a4a4a4, stop: 0.8 #b3b3b3, stop: 1 #b5b5b5);"
            + "}";
}

/**
 * Inserts actions added to the panel into the flow layout of the panel.
 */
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
            var li = layout.takeAt(index);
            if (!isNull(li)) {
                var w = li.widget();
                if (!isNull(w)) {
                    if (isFunction(w.destroy)) {
                        w.destroy();
                    }
                }
                li.invalidate();
            }
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
    this.setAttribute(Qt.WA_MacShowFocusRect, 0);
    this.selectionMode = QAbstractItemView.NoSelection;
    this.verticalScrollMode = QAbstractItemView.ScrollPerPixel;
    if (RSettings.isQt(5)) {
        this.header().setSectionResizeMode(0, QHeaderView.Stretch);
    }
    else {
        this.header().setResizeMode(0, QHeaderView.Stretch);
    }

    this.setItemDelegate(new RToolMatrixItemDelegate(this, this));

    this.itemPressed.connect(this, "handleItemPress");

    this.minimumWidth = 120;
    this.sizeIncrement = new QSize(32,0);

    var p = this.palette;
    p.setColor(QPalette.Base, new QColor("#dddddd"));
    this.palette = p;

    this.listViewMode = false;

    this.panStartValue = undefined;
    this.panStartY = undefined;
}

RCadToolMatrixTree.prototype = new RTreeWidget();

RCadToolMatrixTree.prototype.resizeEvent = function(event) {
    RTreeWidget.prototype.resizeEvent.call(this, event);
    this.updatePanelSizes();
};

RCadToolMatrixTree.prototype.updatePanelSizes = function() {
    var embeddedWidgets = RCadToolMatrixTree.getItemsAndEmbeddedWidgets(this);
    for (var i=0; i<embeddedWidgets.length; i++) {
        var item = embeddedWidgets[i][0];
        var subItem = embeddedWidgets[i][1];
        var embeddedWidget = embeddedWidgets[i][2];
        var width = this.header().width;
        embeddedWidget.setFixedWidth(width);
        var layout = embeddedWidget.layout();
        var height = layout.heightForWidth(width);
        embeddedWidget.setFixedHeight(height);
        subItem.setSizeHint(0, new QSize(width, height));
    }
    //this.updateGeometries();
};

/**
 * Expand / collapse with single click.
 */
RCadToolMatrixTree.prototype.handleItemPress = function(item) {
    if (isNull(item)) {
        return;
    }

    if (isFunction(QApplication.mouseButtons)) {
        // Qt 4:
        if (QApplication.mouseButtons().valueOf() !== Qt.LeftButton.valueOf()) {
            return;
        }
    }
    else {
        // Qt 5:
        if (QGuiApplication.mouseButtons().valueOf() !== Qt.LeftButton.valueOf()) {
            return;
        }
    }

    if (isNull(item.parent())) {
        item.setExpanded(!item.isExpanded());
    }

    // set focus to mdiChild
    var appWin = RMainWindowQt.getMainWindow();
    if (!isNull(appWin)) {
        var w = appWin.getMdiChild();
        if (!isNull(w)) {
            w.setFocus();
        }
    }
};

RCadToolMatrixTree.prototype.mousePressEvent = function(event) {
    if (event.button().valueOf() !== Qt.MidButton.valueOf()) {
        RTreeWidget.prototype.mousePressEvent.call(this, event);
        return;
    }

    // start panning:
    var sb = this.verticalScrollBar();
    this.panStartValue = sb.value;
    this.panStartY = event.y();
    this.mouseTracking = true;
};

RCadToolMatrixTree.prototype.mouseReleaseEvent = function(event) {
    if (event.button().valueOf() !== Qt.MidButton.valueOf()) {
        RTreeWidget.prototype.mouseReleaseEvent.call(this, event);
        return;
    }
    // stop panning:
    this.panStartValue = undefined;
    this.panStartY = undefined;
    this.mouseTracking = false;
};

RCadToolMatrixTree.prototype.mouseMoveEvent = function(event) {
    if (isNull(this.panStartValue) || isNull(this.panStartY)) {
        return;
    }
    var sb = this.verticalScrollBar();
    sb.value = this.panStartValue + (this.panStartY - event.y()) * 4;
};

RCadToolMatrixTree.getItemsAndEmbeddedWidgets = function(tree) {
    var ret = [];
    for (var i=0; i<tree.topLevelItemCount; i++) {
        var item = tree.topLevelItem(i);
        var subItem = item.child(0);
        if (isNull(subItem)) {
            continue;
        }

        var embeddedWidget = tree.itemWidget(subItem, 0);
        if (isNull(embeddedWidget)) {
            continue;
        }

        ret.push([item, subItem, embeddedWidget]);
    }
    return ret;
};

RCadToolMatrixTree.prototype.filter = function(text) {
    var re;
    // hide all tool buttons / categories which don't match the filter:
    try {
        re = new RegExp(text, "gi");
    }
    catch(e) {
        re = new RegExp("", "gi");
    }

    var embeddedWidgets = RCadToolMatrixTree.getItemsAndEmbeddedWidgets(this);
    for (var i=0; i<embeddedWidgets.length; i++) {
        var item = embeddedWidgets[i][0];
        var objectName = item.data(0, Qt.UserRole+1);
        var settingsKey = objectName.replace("MatrixPanel", "");
        var embeddedWidget = embeddedWidgets[i][2];

        //qDebug("settingsKey:", settingsKey);

        var children = embeddedWidget.children();
        var found = false;
        for (var k=0; k<children.length; k++) {
            var child = children[k];
            if (!isOfType(child, RToolButton) && !isOfType(child, QToolButton)) {
                continue;
            }

            var action = child.defaultAction();
            if (isNull(action)) {
                continue;
            }

            if (text.length===0) {
                // no filter:
                found = true;
                //child.styleSheet = "QToolButton { border-style: none; }";
                child.visible = true;
            }
            else {
                var actionText = action.text.replace("&", "");
                var commands = action.getCommands();
                var match = re.test(actionText) || re.test(item.text(0));
                match = match || commands.contains(actionText, function(t) { return re.test(t); });

                if (match) {
                    // filter match:
                    child.visible = true;
                    found = true;
//                    child.styleSheet = "QToolButton { border-style: none; border-radius: 4px; background-color: white; }"
//                            + RCadToolMatrixTreePanel.getCheckedStyle() + RCadToolMatrixTreePanel.getPressedStyle();
                }
                else {
                    // filter does not match:
                    child.visible = false;
//                    child.styleSheet = "";
                }
            }
        }

        if (!found || RSettings.getBoolValue(settingsKey + "/VisibleInMatrixPanel", true)===false) {
            // hide category:
            item.setHidden(true);
        }
        else {
            item.setHidden(false);
        }
    }

    //this.updatePanelSizes();
    RCadToolMatrixTree.prototype.updatePanelSizes.call(this);
};

RCadToolMatrixTree.prototype.updateIconSize = function() {
    var iconSize = RSettings.getIntValue("CadToolMatrix/IconSize", 24);
    iconSize = new QSize(iconSize, iconSize);

    var embeddedWidgets = RCadToolMatrixTree.getItemsAndEmbeddedWidgets(this);
    for (var i=0; i<embeddedWidgets.length; i++) {
        var embeddedWidget = embeddedWidgets[i][2];

        var layout = embeddedWidget.layout();
        layout.setIconSize(iconSize);

//        var children = embeddedWidget.children();
//        var found = false;
//        for (var k=0; k<children.length; k++) {
//            var child = children[k];
//            if (!isOfType(child, QToolButton)) {
//                continue;
//            }
//            child.iconSize = iconSize;
//        }

        //layout.invalidate();
        //item.setExpanded(!item.isExpanded());
        //item.setExpanded(!item.isExpanded());

//        var width = this.header().width;
//        embeddedWidget.setFixedWidth(width);
//        var height = embeddedWidget.layout().heightForWidth(width);
//        embeddedWidget.setFixedHeight(height);
//        subItem.setSizeHint(0, new QSize(width, height));
    }

    //this.resize(this.size);
    //this.updatePanelSizes();
};

RCadToolMatrixTree.prototype.contextMenuEvent = function(event) {
    var menu = new QMenu(RMainWindowQt.getMainWindow());
    var self = this;
    var a;

    a = menu.addAction(qsTr("Expand all"));
    a.triggered.connect(function() {
        self.expandAll();
    });
    a = menu.addAction(qsTr("Collapse all"));
    a.triggered.connect(function() {
        self.collapseAll();
    });

    menu.addSeparator();

    a = menu.addAction(qsTr("List View"));
    a.triggered.connect(function() {
        self.setListViewMode(true);
    });
    a = menu.addAction(qsTr("Icon View"));
    a.triggered.connect(function() {
        self.setListViewMode(false);
    });

    menu.exec(QCursor.pos());
};

RCadToolMatrixTree.prototype.updateListViewMode = function() {
    var listViewMode = RSettings.getBoolValue("CadToolMatrix/ListViewMode", false);
    RCadToolMatrixTree.prototype.setListViewMode.call(this, listViewMode);
};

RCadToolMatrixTree.prototype.setListViewMode = function(enable) {
    if (isFunction(this.setProperty)) {
        this.setProperty("listViewMode", enable);
    }
    var embeddedWidgets = RCadToolMatrixTree.getItemsAndEmbeddedWidgets(this);
    for (var i=0; i<embeddedWidgets.length; i++) {
        var embeddedWidget = embeddedWidgets[i][2];
        var layout = embeddedWidget.layout();
        layout.setListViewMode(enable);
    }
    RCadToolMatrixTree.prototype.updatePanelSizes.call(this);
};



function CadToolMatrix(guiAction) {
    Widgets.call(this, guiAction);
}

CadToolMatrix.prototype = new Widgets();
CadToolMatrix.includeBasePath = includeBasePath;

CadToolMatrix.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("Tool Matrix")];
};

CadToolMatrix.applyPreferences = function(doc) {
    if (!isNull(doc)) {
        // document settings: nothing to do
        return;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }

    var cadToolMatrix = appWin.findChild("ToolMatrix");
    RCadToolMatrixTree.prototype.updateIconSize.call(cadToolMatrix);
    RCadToolMatrixTree.prototype.updateListViewMode.call(cadToolMatrix);

    var cadToolMatrixDock = appWin.findChild("ToolMatrixDock");
    RCadToolMatrixTree.prototype.filter.call(cadToolMatrix, cadToolMatrixDock.findChild("FilterEdit").text);
    //RCadToolMatrixTree.prototype.updatePanelSizes.call(cadToolMatrix);
};

/**
 * \return Newly created or existing instance of RCadToolMatrixTree.
 */
CadToolMatrix.getToolMatrix = function() {
    var appWin = EAction.getMainWindow();

    var toolMatrix = appWin.findChild("ToolMatrix");
    if (isNull(toolMatrix)) {
        var formWidget = WidgetFactory.createWidget(CadToolMatrix.includeBasePath, "CadToolMatrix.ui");

        var layout = formWidget.findChild("VerticalLayout");

        // add tool matrix:
        toolMatrix = new RCadToolMatrixTree(appWin);
        toolMatrix.objectName = "ToolMatrix";
        layout.addWidget(toolMatrix, 1, 0);

        // init filter widget:
        var filterEdit = formWidget.findChild("FilterEdit");
        filterEdit.textChanged.connect(toolMatrix, "filter");
        var clearButton = formWidget.findChild("Clear");
        if (filterEdit.clearButtonEnabled===true) {
            clearButton.hide();
        }
        var dock = new RDockWidget(qsTr("Tool Matrix"), appWin);
        dock.objectName = "ToolMatrixDock";
        dock.setWidget(formWidget);
        appWin.addDockWidget(Qt.LeftDockWidgetArea, dock);
        dock.visible = false;
    }

    return toolMatrix;
};

/**
 * \return RCadToolMatrixTreePanel with RFlowLayout to which QActions can be added as part of a
 * tool panel in the tools matrix. The category in the tool matrix tree is added if
 * it is not yet present.
 */
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
    //var settingsKey = objectName.replace("MatrixPanel", "");

    var tm = CadToolMatrix.getToolMatrix();

    // find existing root item:
    var flags = new Qt.MatchFlags(Qt.MatchFixedString | Qt.MatchRecursive);
    var items = tm.findItems(title, flags);
    var item;
    if (items.length===0) {
        // add root item at desired position:
        item = new QTreeWidgetItem();
        item.setChildIndicatorPolicy(QTreeWidgetItem.ShowIndicator);
        item.setText(0, title);
//        item.setText(0, title + "_" + order);
        item.setData(0, Qt.UserRole, order);
        item.setData(0, Qt.UserRole+1, objectName);

//        if (RSettings.getBoolValue(settingsKey + "/VisibleInMatrixPanel", true)===false) {
//            //item.setHidden(true);
//            item.setData(0, Qt.UserRole+2, false);
//        }

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
    dw = new RCadToolMatrixTreePanel(tm, objectName);
    item.addChild(subItem);
    tm.setItemWidget(subItem, 0, dw);
    tm.expandAll();

    return dw;
};

/**
 * Restore state of collapsed categories.
 */
CadToolMatrix.postInit = function(basePath) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }

    var toolMatrix = appWin.findChild("ToolMatrix");
    if (isNull(toolMatrix)) {
        return;
    }

    var listViewMode = RSettings.getBoolValue("CadToolMatrix/ListViewMode", false);
    RCadToolMatrixTree.prototype.setListViewMode.call(toolMatrix, listViewMode);
    var closedCategories = RSettings.getStringValue("CadToolMatrix/ClosedCategories", "");

    closedCategories = closedCategories.split(",");
    for (var i=0; i<toolMatrix.topLevelItemCount; i++) {
        var item = toolMatrix.topLevelItem(i);
        var id = item.data(0, Qt.UserRole+1);
        if (closedCategories.contains(id)) {
            item.setExpanded(false);
        }
    }

    RCadToolMatrixTree.prototype.filter.call(toolMatrix, "");
};

/**
 * Store state of collapsed categories.
 */
CadToolMatrix.uninit = function() {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }

    var toolMatrix = appWin.findChild("ToolMatrix");
    if (isNull(toolMatrix)) {
        return;
    }

    // store expanded state:
    var closedCategories = [];
    for (var i=0; i<toolMatrix.topLevelItemCount; i++) {
        var item = toolMatrix.topLevelItem(i);
        if (!item.isExpanded()) {
            var id = item.data(0, Qt.UserRole+1);
            closedCategories.push(id);
        }
    }
    RSettings.setValue("CadToolMatrix/ClosedCategories", closedCategories.join(","));
    RSettings.setValue("CadToolMatrix/ListViewMode", toolMatrix.listViewMode);
};
