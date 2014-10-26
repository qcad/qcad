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

include("CadToolBarPanel.js");


/**
 * CAD tool bar with configurable number of columns of tool buttons.
 *
 * \param parent A QToolBar
 */
function CadToolBar(parent) {
    QWidget.call(this, parent);

    var buttonSize = RSettings.getIntValue("CadToolBar/IconSize", 32) * 1.25;
    
    this.includeBasePath = includeBasePath;

    // widget inside toolbar is needed to allow two rows of
    // tool buttons in a layout:
    this.objectName="CadToolBar";
    this.minimumWidth = buttonSize;
    this.minimumHeight = buttonSize;
    var stackedLayout = new QStackedLayout();
    stackedLayout.objectName = "StackedLayout";
    stackedLayout.setContentsMargins(0,0,0,0);
    this.setLayout(stackedLayout);

    RMainWindowQt.getMainWindow().escape.connect(CadToolBar, "back");
}

CadToolBar.prototype = new QWidget();

CadToolBar.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("CAD Toolbar")];
};

CadToolBar.applyPreferences = function(doc) {
    if (!isNull(doc)) {
        // document settings: nothing to do
        return;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }

    var cadToolBar = appWin.findChild("CadToolBar");
    CadToolBar.prototype.updateIconSize.call(cadToolBar);
};

CadToolBar.prototype.contextMenuEvent = function(event) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    //var cadToolBar = appWin.findChild("CadToolBar");
    var panelName = CadToolBar.getCurrentPanelName();
    if (panelName!=="MainToolsPanel") {
        CadToolBar.showPanel("MainToolsPanel");
    }
    else {
        var menu = new QMenu(this);
        menu.objectName = "ContextMenu";
        var action = menu.addAction(qsTr("Toggle Handle"));
        var tb = appWin.findChild("CadQToolBar");
        action.triggered.connect(function(checked) {
            tb.movable = !tb.movable;
        });
        // TODO: make floating tool bar vertical
//        if (tb.floating) {
//            action = menu.addAction(qsTr("Vertical/Horizontal"));
//            action.triggered.connect(function(checked) {
//                if (isNull(tb.verticalWhenFloating)) {
//                    tb.verticalWhenFloating = false;
//                }
//                qDebug("tb.verticalWhenFloating: ", tb.verticalWhenFloating);
//                tb.setProperty("verticalWhenFloating", !tb.verticalWhenFloating);
//                qDebug("tb.verticalWhenFloating: ", tb.verticalWhenFloating);
//                //tb.resize(10,10);
//                //tb.hide();
//                //tb.show();
//                //var tbw = appWin.findChild("CadToolBar");
//                //tbw.updateGeometry();
//                //var sh = tb.sizeHint;
//                //qDebug("sh: ", sh);
//                //tb.resize(sh.height(), sh.width());
//                //var tb = appWin.findChild("CadQToolBar");
//                //tb.movable = !tb.movable;
//                //tb.movable = !tb.movable;
//            });
//        }
        menu.exec(QCursor.pos());
    }
};

CadToolBar.getSizeHint = function(toolBar, sHint) {
    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);
    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);

    var w, h;

    if (toolBar.floating) {
        //qDebug("sizeHint for floating");
        w = columns * iconSize * 1.25;
        h = !isNull(sHint) ? sHint.height() : 0;
    }
    else {
        if (toolBar.orientation===Qt.Horizontal/* && !toolBar.floating*/) {
            //qDebug("sizeHint for horizontal");
            //x = 12 * iconSize * 1.25;
            w = 0; //!isNull(sHint) ? sHint.width() : 0;
            //h = Math.max(columns * iconSize * 1.25, (!isNull(sHint) ? sHint.height() : 0));
            h = columns * iconSize * 1.25;
        }
        else {
            //qDebug("sizeHint for vertical");
            //w = Math.max(columns * iconSize * 1.25, (!isNull(sHint) ? sHint.width() : 0));
            w = columns * iconSize * 1.25;
            //y = 12 * iconSize * 1.25;
            h = 0; //!isNull(sHint) ? sHint.height() : 0;
        }
    }
    //qDebug("sizeHint", w, h);
    return new QSize(w, h);
};

CadToolBar.back = function() {
    var panel = CadToolBar.getCurrentPanel();
    if (isNull(panel)) {
        return;
    }

    // no back for main tools panel:
    if (panel.objectName==="MainToolsPanel") {
        return;
    }

    CadToolBar.showPanel(panel.backMenuName, true);
};

CadToolBar.getPanel = function(title, name, hasBackButton) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }
    var cadToolBar = appWin.findChild("CadToolBar");
    if (isNull(cadToolBar)) {
        return undefined;
    }

    var stackedLayout = cadToolBar.layout();

    var panel = cadToolBar.findChild(name);
    if (!isNull(panel)) {
        return panel;
    }

    panel = new CadToolBarPanel(cadToolBar, hasBackButton);
    panel.objectName = name;
    stackedLayout.addWidget(panel);
    return panel;
};

CadToolBar.showPanel = function(name, isBack) {
    if (isNull(isBack)) {
        isBack = false;
    }

    if (isNull(name)) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    if (isNull(appWin)) {
        return;
    }

    var cadToolBar = appWin.findChild("CadToolBar");
    if (isNull(cadToolBar)) {
        return;
    }

    var backMenuName = CadToolBar.getCurrentPanelName();

    var stackedLayout = cadToolBar.layout();
    var panel = cadToolBar.findChild(name);
    if (isNull(panel)) {
        qWarning("CadToolBar: panel does not exist: ", name);
        return;
    }

    for (var i=0; i<stackedLayout.count(); ++i) {
        var w = stackedLayout.widget(i);
        if (!isNull(w)) {
            w.minimumHeight = 0;
            w.minimumWidth = 0;
        }
    }
    stackedLayout.setCurrentWidget(panel);

    if (!isBack && backMenuName!==panel.objectName && backMenuName!=="SnapToolsPanel") {
        CadToolBarPanel.setBackMenuName(panel, backMenuName);
    }
};

CadToolBar.getCurrentPanel = function() {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    var cadToolBar = appWin.findChild("CadToolBar");
    if (isNull(cadToolBar)) {
        return undefined;
    }

    var stackedLayout = cadToolBar.layout();

    if (stackedLayout.currentIndex<0 || stackedLayout.currentIndex >= stackedLayout.count()) {
        return undefined;
    }

    return stackedLayout.widget(stackedLayout.currentIndex);
};

CadToolBar.getCurrentPanelName = function() {
    var w = CadToolBar.getCurrentPanel();
    if (isNull(w)) {
        return "";
    }

    return w.objectName;
};

CadToolBar.prototype.updateIconSize = function() {
    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);
    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);
    var buttonSize = iconSize * 1.25;

    var toolBar = this.parentWidget();

    toolBar.iconSize = new QSize(columns*iconSize, columns*iconSize);
    qDebug("iconSize: ", toolBar.iconSize);

    toolBar.minimumWidth = buttonSize;
    toolBar.minimumHeight = buttonSize;
    //this.updateGeometry();

    //this.setFixedWidth(buttonSize*columns);
};
