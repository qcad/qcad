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

PointMarkList.itemClicked = function(item, col) {
    var handle = item.data(0, Qt.UserRole);
    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return;
    }

    // find block reference and bounding box:
    var doc = di.getDocument();
    var blockRef = doc.queryObjectByHandle(handle);
    if (!isBlockReferenceEntity(blockRef)) {
        return;
    }
    var box = blockRef.getBoundingBox();

    // find attribute(s):
    var attribIds = doc.queryChildEntities(blockRef.getId(), RS.EntityAttribute);
    if (attribIds.length!==0) {
        for (var i=0; i<attribIds.length; i++) {
            var attribId = attribIds[i];
            var attrib = doc.queryEntityDirect(attribId);
            if (!isAttributeEntity(attrib)) {
                continue;
            }

            box.growToInclude(attrib.getBoundingBox());
        }
    }

    var view = di.getLastKnownViewWithFocus();
    if (isNull(view)) {
        return;
    }

    view.zoomTo(box, Math.min(view.getWidth(), view.getHeight())*0.4);
};

PointMarkList.updateFromDocument = function(di) {
    var appWin = RMainWindowQt.getMainWindow();
    var pointMarkTree = appWin.findChild("PointMarkTree");
    pointMarkTree.clear();

    if (isNull(di)) {
        // no document open, abort.
        return;
    }

    var doc = di.getDocument();
    var objIds = doc.queryAllBlockReferences();
    for (var i=0; i<objIds.length; i++) {
        var objId = objIds[i];
        var blockRef = doc.queryObjectDirect(objId);
        if (!isBlockReferenceEntity(blockRef)) {
            continue;
        }

        var handle = PointMark.getBenchmarkHandle(blockRef);
        if (handle===RObject.INVALID_HANDLE) {
            continue;
        }

        var label = PointMark.getMarkLabel(doc, objId);
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
            item.setData(0, Qt.UserRole, handle);
            pointMarkTree.addTopLevelItem(item);
        }
        // block ref is a point marker:
        else {

        }
    }
};

PointMarkList.updateFromTransaction = function(doc, transaction) {
    // TODO: find out if any marks were affected at all:
    PointMarkList.updateFromDocument(EAction.getDocumentInterface());
    return;

    /*

    if (isNull(doc) || isNull(transaction)) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    var pointMarkTree = appWin.findChild("PointMarkTree");

    // find out what has changed:
    var objIds = transaction.getAffectedObjects();
    for (var i=0; i<objIds.length; i++) {
        var objId = objIds[i];
        var blockRef = doc.queryObjectDirect(objId);
        if (!isBlockReferenceEntity(blockRef)) {
            continue;
        }

        var handle = PointMark.getBenchmarkHandle(blockRef);
        if (handle===RObject.INVALID_HANDLE) {
            continue;
        }

        var label = PointMark.getMarkLabel(doc, objId);
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
    }
    */
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

    var pointMarkTree = formWidget.findChild("PointMarkTree");
    pointMarkTree.itemClicked.connect(PointMarkList, "itemClicked");

    var dock = new RDockWidget(qsTr("Point Marker List"), appWin);
    dock.objectName = "PointMarkDock";
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);

    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });

    // create a transaction listener to keep widget up to date:
    var tAdapter = new RTransactionListenerAdapter();
    appWin.addTransactionListener(tAdapter);
    tAdapter.transactionUpdated.connect(PointMarkList, "updateFromTransaction");

    var fAdapter = new RFocusListenerAdapter();
    appWin.addFocusListener(fAdapter);
    fAdapter.focusUpdated.connect(PointMarkList, "updateFromDocument");
};
