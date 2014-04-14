/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

include("../../../WidgetFactory.js");

function PointMarkList(guiAction) {
    Widgets.call(this, guiAction);
}

PointMarkList.prototype = new Widgets();

/**
 * Shows / hides the layer list.
 */
PointMarkList.prototype.beginEvent = function() {
    Widgets.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PointMarkDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
    }
};

PointMarkList.prototype.finishEvent = function() {
    Widgets.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PointMarkDock");
    this.getGuiAction().setChecked(dock.visible);
};

PointMarkList.update = function(document, transaction) {
    //qDebug("update point marker list: ", document);
    if (isNull(document) || isNull(transaction)) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    var pointMarkTree = appWin.findChild("PointMarkTree");
    pointMarkTree.clear();

    // find out what has changed:
    var objIds = transaction.getAffectedObjects();
    for (var i=0; i<objIds.length; i++) {
        var objId = objIds[i];
        var blockRef = document.queryObjectDirect(objId);
        if (!isBlockReferenceEntity(blockRef)) {
            continue;
        }

        var handle = PointMark.getBenchmarkHandle(blockRef);
        if (handle===RObject.INVALID_HANDLE) {
            continue;
        }

        var label = PointMark.getMarkLabel(document, objId);
        var pos = blockRef.getPosition();

        // block ref is a benchmark:
        if (handle===blockRef.getHandle()) {
            var item = new QTreeWidgetItem(
                [
                    label,
                    RUnit.doubleToString(pos.x, 2),
                    RUnit.doubleToString(pos.y, 2),
                    RUnit.doubleToString(pos.z, 2),
                    blockRef.getLayerName()
                ]
            );
            pointMarkTree.addTopLevelItem(item);
        }
        // block ref is a point marker:
        else {

        }

        qDebug("point marker found...");
    }
};

PointMarkList.init = function(basePath) {
    var appWin = RMainWindowQt.getMainWindow();

    var action = new RGuiAction(qsTr("&Point Marker List"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/PointMarkList.js");
    action.setIcon(basePath + "/PointMarkList.svg");
    action.setDefaultShortcut(new QKeySequence("g,t"));
    action.setDefaultCommands(["gt"]);
    action.setSortOrder(10000);
    EAction.addGuiActionTo(action, Widgets, true, true, false);

    var formWidget = WidgetFactory.createWidget(basePath, "PointMarkList.ui");

    var dock = new RDockWidget(qsTr("Point Marker List"), appWin);
    dock.objectName = "PointMarkDock";
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);

    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });

    // create a transaction listener to keep widget up to date:
    var adapter = new RTransactionListenerAdapter();
    appWin.addTransactionListener(adapter);
    adapter.transactionUpdated.connect(PointMarkList, "update");
};
