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

    this.styleSheet =
          "QWidget#" + objectName + " { background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #dddddd, stop:1 #eeeeee); }"
        + "QToolButton {"
        + "  border-style: none;"
        + "}"
        + RCadToolMatrixTreePanel.getCheckedStyle()
        + RCadToolMatrixTreePanel.getPressedStyle();

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

    this.minimumWidth = 120;
    this.sizeIncrement = new QSize(32,0);

    var p = this.palette;
    p.setColor(QPalette.Base, new QColor("#dddddd"));
    this.palette = p;
}

RCadToolMatrixTree.prototype = new RTreeWidget();

RCadToolMatrixTree.prototype.resizeEvent = function(event) {
    RTreeWidget.prototype.resizeEvent.call(this, event);
    this.updatePanelSizes();
};

RCadToolMatrixTree.prototype.updatePanelSizes = function() {
    for (var i=0; i<this.topLevelItemCount; i++) {
        var item = this.topLevelItem(i);
        var subItem = item.child(0);
        if (isNull(subItem)) {
            continue;
        }
        var embeddedWidget = this.itemWidget(subItem, 0);
        if (isNull(embeddedWidget)) {
            continue;
        }
        var width = this.header().width;
        embeddedWidget.setFixedWidth(width);
        var layout = embeddedWidget.layout();
        var height = layout.heightForWidth(width);
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

RCadToolMatrixTree.prototype.filter = function(text) {
    // hide all tool buttons / categories which don't match the filter:
    var re = new RegExp(text, "gi");

    for (var i=0; i<this.topLevelItemCount; i++) {
        var item = this.topLevelItem(i);
        var subItem = item.child(0);
        if (isNull(subItem)) {
            continue;
        }

        var embeddedWidget = this.itemWidget(subItem, 0);
        if (isNull(embeddedWidget)) {
            continue;
        }

        var children = embeddedWidget.children();
        var found = false;
        for (var k=0; k<children.length; k++) {
            var child = children[k];
            if (!isOfType(child, QToolButton)) {
                continue;
            }

            var action = child.defaultAction();
            if (isNull(action)) {
                continue;
            }


            if (text.length===0) {
                // no filter:
                found = true;
                child.styleSheet = "QToolButton { border-style: none; }";
            }
            else {
                var actionText = action.text.replace("&", "");
                var commands = action.getCommands();
                var match = re.test(actionText) || re.test(item.text(0));
                match = match || commands.contains(actionText, function(t) { return re.test(t); });

                if (match) {
                    // filter match:
                    //child.visible = true;
                    found = true;
                    //child.styleSheet = "QToolButton { border-style: none; border-radius: 4px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7b7b7, stop: 0.8 #efcfcf, stop: 1 #f1d1d1); }";
                    child.styleSheet = "QToolButton { border-style: none; border-radius: 4px; background-color: white; }"
                            + RCadToolMatrixTreePanel.getCheckedStyle() + RCadToolMatrixTreePanel.getPressedStyle();
                }
                else {
                    // filter does not match:
                    //child.visible = false;
                    //child.styleSheet = "QToolButton { border-style: none; }";
                    child.styleSheet = "";
                }
            }
        }

        if (!found) {
            // hide category:
            // CRASH if tool tip is visible for one of the tool buttons in this category:
            //item.setHidden(true);
            //item.setData(0, Qt.UserRole+2, true);
        }
        else {
            //item.setHidden(false);
            //item.setData(0, Qt.UserRole+2, false);
        }
    }

    //QCoreApplication.processEvents();

    this.updatePanelSizes();
};

RCadToolMatrixTree.prototype.updateIconSize = function() {
    var iconSize = RSettings.getIntValue("CadToolMatrix/IconSize", 24);
    iconSize = new QSize(iconSize, iconSize);

    for (var i=0; i<this.topLevelItemCount; i++) {
        var item = this.topLevelItem(i);
        var subItem = item.child(0);
        if (isNull(subItem)) {
            continue;
        }
        var embeddedWidget = this.itemWidget(subItem, 0);
        if (isNull(embeddedWidget)) {
            continue;
        }

        var layout = embeddedWidget.layout();
        layout.setIconSize(iconSize);

        var children = embeddedWidget.children();
        var found = false;
        for (var k=0; k<children.length; k++) {
            var child = children[k];
            if (!isOfType(child, QToolButton)) {
                continue;
            }
            child.iconSize = iconSize;
        }

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



function CadToolMatrix(guiAction) {
    Widgets.call(this, guiAction);
}

CadToolMatrix.prototype = new Widgets();
CadToolMatrix.includeBasePath = includeBasePath;

CadToolMatrix.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("CAD Tool Matrix")];
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

    // TODO:
    //var cadToolMatrix = appWin.findChild("ToolMatrix");
    //RCadToolMatrixTree.prototype.updateIconSize.call(cadToolMatrix);
    //RCadToolMatrixTree.prototype.updatePanelSizes.call(cadToolMatrix);
    //cadToolMatrix.update();
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
        var dock = new RDockWidget(qsTr("CAD Tools"), appWin);
        dock.objectName = "ToolMatrixDock";
        dock.setWidget(formWidget);
        appWin.addDockWidget(Qt.LeftDockWidgetArea, dock);
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

    var tm = CadToolMatrix.getToolMatrix();

    var flags = new Qt.MatchFlags(Qt.MatchFixedString | Qt.MatchRecursive);
    var items = tm.findItems(title, flags);
    var item;
    if (items.length===0) {
        item = new QTreeWidgetItem();
        item.setChildIndicatorPolicy(QTreeWidgetItem.ShowIndicator);
        item.setText(0, title);
//        item.setText(0, title + "_" + order);
        item.setData(0, Qt.UserRole, order);
        item.setData(0, Qt.UserRole+1, objectName);
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
CadToolMatrix.init = function(basePath) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }

    var toolMatrix = appWin.findChild("ToolMatrix");
    if (isNull(toolMatrix)) {
        return;
    }

    var closedCategories = RSettings.getStringValue("CadToolMatrix/ClosedCategories", "");
    if (closedCategories.isEmpty()) {
        return;
    }

    closedCategories = closedCategories.split(",");
    for (var i=0; i<toolMatrix.topLevelItemCount; i++) {
        var item = toolMatrix.topLevelItem(i);
        var id = item.data(0, Qt.UserRole+1);
        if (closedCategories.contains(id)) {
            item.setExpanded(false);
        }
    }
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
};
