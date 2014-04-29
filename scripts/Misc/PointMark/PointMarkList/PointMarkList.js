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

include("scripts/WidgetFactory.js");
include("../PointMarkDraw/PointMarkDraw.js");

function PointMarkList(guiAction) {
    Widgets.call(this, guiAction);
}

PointMarkList.prototype = new Widgets();
PointMarkList.includeBasePath = includeBasePath;

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

    if (!blockRef.isSelected()) {
        di.selectEntity(blockRef.getId());
    }

    // if we are drawing marks, set current parent benchmark:
    if (PointMark.getBenchmarkHandle(blockRef)===handle) {
        PointMarkDraw.setBenchmark(handle);
    }

    // zoom to mark:
//    var box = blockRef.getBoundingBox();

//    // find attribute(s):
//    var attribIds = doc.queryChildEntities(blockRef.getId(), RS.EntityAttribute);
//    if (attribIds.length!==0) {
//        for (var i=0; i<attribIds.length; i++) {
//            var attribId = attribIds[i];
//            var attrib = doc.queryEntityDirect(attribId);
//            if (!isAttributeEntity(attrib)) {
//                continue;
//            }

//            box.growToInclude(attrib.getBoundingBox());
//        }
//    }

    var view = di.getLastKnownViewWithFocus();
    if (isNull(view)) {
        return;
    }

//    view.zoomTo(box, Math.min(view.getWidth(), view.getHeight())*0.4);

    // only pan to mark:
    view.centerToPoint(blockRef.getPosition());
};

PointMarkList.updateFromDocument = function(doc) {
    if (isOfType(doc, RDocumentInterface)) {
        doc = doc.getDocument();
    }

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PointMarkDock");
    if (!dock.visible) {
        return;
    }

    var treeWidget = appWin.findChild("PointMarkTree");
    var currentItem = treeWidget.currentItem();

    var selectedHandle = PointMarkDraw.getBenchmark();

    if (!isNull(currentItem) && isNull(selectedHandle)) {
        selectedHandle = currentItem.data(0, Qt.UserRole);
    }

    treeWidget.clear();

    if (isNull(doc)) {
        // no document open, abort.
        return;
    }

    var treeData = PointMark.getPointMarkTree(doc);
    var item;

    for (var i=0; i<treeData.length; i++) {
        var list = treeData[i];

        var rootItem = undefined;
        for (var k=0; k<list.length; k++) {
            item = new QTreeWidgetItem(
                [
                    list[k][0],
                    RUnit.doubleToString(list[k][1].x, 0.01),
                    RUnit.doubleToString(list[k][1].y, 0.01),
                    RUnit.doubleToString(list[k][1].z, 0.01),
                    list[k][2]
                ]
            );
            item.setData(0, Qt.UserRole, list[k][3]);
            item.setTextAlignment(1, Qt.AlignRight);
            item.setTextAlignment(2, Qt.AlignRight);
            item.setTextAlignment(3, Qt.AlignRight);

            if (k===0) {
                item.setIcon(0, new QIcon(PointMarkList.includeBasePath + "/Benchmark.svg"));
                treeWidget.addTopLevelItem(item);
                rootItem = item;
            }
            else {
                if (isNull(rootItem)) {
                    continue;
                }

                item.setIcon(0, new QIcon(PointMarkList.includeBasePath + "/Point.svg"));
                rootItem.setExpanded(true);
                rootItem.addChild(item);
                //rootItem.sortChildren(0, Qt.AscendingOrder);
            }

            if (list[k][3]===selectedHandle) {
                treeWidget.setCurrentItem(item);
            }
        }
    }

    //treeWidget.sortItems(0, Qt.AscendingOrder);
    for (var col=0; col<4; col++) {
        treeWidget.resizeColumnToContents(col);
    }
};

PointMarkList.updateFromTransaction = function(doc, transaction) {
    //qDebug("PointMarkList.updateFromTransaction: ", transaction);
    // TODO: find out if any marks were affected at all:
    PointMarkList.updateFromDocument(doc);
};

PointMarkList.updateLeaders = function(doc, transaction) {
    //qDebug("PointMarkList.updateLeaders: ", transaction);
    //var doc = di.getDocument();
    //debugger;
    if (isNull(doc)) {
        qDebug("PointMarkList.updateLeaders: doc is NULL");
        return;
    }
    var storage = doc.getStorage();

    var i, objIds, objId, leader;

    var affectedIds = transaction.getAffectedObjects();

    // update existing leaders:
    // query all auto leaders:
    objIds = PointMark.queryAllAutoLeaders(doc);
    for (i=0; i<objIds.length; i++) {
        objId = objIds[i];
        leader = doc.queryObject(objId);
        if (!isLeaderEntity(leader)) {
            continue;
        }

        // attribute:
        var attributeHandle = PointMark.getFromHandle(leader);
        var attribute = doc.queryObjectByHandle(attributeHandle);
        if (!isAttributeEntity(attribute)) {
            continue;
        }

        // block ref:
        var blockRefHandle = PointMark.getToHandle(leader);
        var blockRef = doc.queryObjectByHandle(blockRefHandle);
        if (!isBlockReferenceEntity(blockRef)) {
            continue;
        }

        // check if one of the linked entities has changed:
        if (!affectedIds.contains(attribute.getId()) &&
            !affectedIds.contains(blockRef.getId())) {
            // leader remains unchanged:
            continue;
        }

        // update leader position:
        leader.clear();
        leader.appendVertex(blockRef.getPosition());
        leader.appendVertex(attribute.getAlignmentPoint());
        transaction.addObject(leader, false);

        // update attribute alignment:
        if (blockRef.getPosition().getAngleTo(attribute.getAlignmentPoint()) < Math.PI/4) {
            qDebug("updating attribute text alignment");
            attribute.setHAlign(RS.HAlignLeft);
            attribute.setVAlign(RS.VAlignMiddle);
            transaction.addObject(attribute, false);
        }

        //found = true;
    }


    /*
    // create missing leaders (on load only):
    //var op = new RAddObjectsOperation();
    if (isNull(transaction) || transaction.getText()==="Importing") {
        // loading drawing: update all:
        objIds = PointMark.queryAllMarkIds(doc);
    }
    else {
        // ignore undo / redo (handled internally):
        if (transaction.isUndoing() || transaction.isRedoing()) {
            return;
        }

        objIds = transaction.getAffectedObjects();
        transaction.setKeepHandles(true);
    }
    var found = false;
    for (i=0; i<objIds.length; i++) {
        objId = objIds[i];
        blockRef = doc.queryObjectDirect(objId);
        //qDebug(blockRef);
        if (!isBlockReferenceEntity(blockRef)) {
            continue;
        }

        //debugger;

        // not a point mark:
        if (PointMark.getBenchmarkHandle(blockRef)===RObject.INVALID_HANDLE) {
            continue;
        }

        // query block attrib:
        var attrib = PointMark.getMarkLabel(doc, blockRef.getId());
        if (isNull(attrib)) {
            continue;
        }

        // get leader handle from custom property:
        var leaderHandle = PointMark.getLeaderHandle(blockRef);

        // query leader:
        leader = doc.queryObjectByHandle(leaderHandle);
        if (isNull(leader) || !isLeaderEntity(leader)) {
            // no leader exists for this mark: create new leader with fixed handle:
            leader = new RLeaderEntity(doc, new RLeaderData(new RPolyline(), false));
            storage.setObjectHandle(leader, storage.getNewObjectHandle());
        }

        leader.clear();
        leader.appendVertex(blockRef.getPosition());
        leader.appendVertex(attrib.getPosition());
        leader.setCustomProperty("QCAD", "From", "0x" + attrib.getHandle().toString(16));
        leader.setCustomProperty("QCAD", "To", "0x" + blockRef.getHandle().toString(16));
        //op.addObject(leader);

        transaction.addObject(leader);
        found = true;
    }

//    if (found) {
//        // adjust leaders:
//        var trans = EAction.getDocumentInterface().applyOperation(op);

//        // link block refs to leaders:
//        objIds = trans.getAffectedObjects();
//        for (i=0; i<objIds.length; i++) {
//            objId = objIds[i];
//            leader = doc.queryObjectDirect(objId);
//            if (!isLeaderEntity(leader)) {
//                continue;
//            }

//            var blockRefId = leader.getCustomProperty("QCAD", "blockRefId", RObject.INVALID_ID);
//            if (blockRefId===RObject.INVALID_ID) {
//                debugger;
//                continue;
//            }

//            blockRef = doc.queryObjectDirect(blockRefId);
//            PointMark.setLeaderHandle(blockRef, leader.getHandle());
//            leader.removeCustomProperty("QCAD", "blockRefId");
//        }
//    }
    */
};

/**
 * Called when user adjusts scale factor of point marks.
 */
PointMarkList.setScale = function(str) {
    var f = parseFloat(str, 10);

    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return;
    }
    var doc = di.getDocument();

    var op = new RAddObjectsOperation();
    var ids = PointMark.queryAllMarkIds(doc, 'a');
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];

        var blockRef = doc.queryEntity(id);
        if (isNull(blockRef) || !isBlockReferenceEntity(blockRef)) {
            continue;
        }

        blockRef.setScaleFactors(new RVector(f,f,f));
        op.addObject(blockRef);
    }

    di.applyOperation(op);
};

/**
 * Called when user adjusts label size.
 */
PointMarkList.setLabelSize = function(str) {
    if (str.length===0) {
        return;
    }
    var h = parseFloat(str, 10);
    if (h<RS.PointTolerance) {
        return;
    }

    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return;
    }
    var doc = di.getDocument();

    var op = new RAddObjectsOperation();
    var ids = PointMark.queryAllMarkIds(doc, 'a');
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];

        var blockRef = doc.queryEntity(id);
        if (isNull(blockRef) || !isBlockReferenceEntity(blockRef)) {
            continue;
        }

        var attribIds = doc.queryChildEntities(blockRef.getId(), RS.EntityAttribute);
        if (attribIds.length===0) {
            continue;
        }

        for (var k=0; k<attribIds.length; k++) {
            var attribId = attribIds[k];
            var attrib = doc.queryEntity(attribId);
            if (isNull(attrib)) {
                continue;
            }

            attrib.setTextHeight(h);
            op.addObject(attrib);
        }
    }

    di.applyOperation(op);
};


PointMarkList.init = function(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();

    var action = new RGuiAction(qsTr("&Show / Hide Point Mark List"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/PointMarkList.js");
    action.setIcon(basePath + "/PointMarkList.svg");
    action.setDefaultShortcut(new QKeySequence("g,t"));
    action.setDefaultCommands(["gt"]);
    action.setSortOrder(10000);
    EAction.addGuiActionTo(action, PointMark, true, true, false);

    var formWidget = WidgetFactory.createWidget(basePath, "PointMarkList.ui");

    // set up tree widget:
    var pointMarkTree = formWidget.findChild("PointMarkTree");
    pointMarkTree.itemClicked.connect(PointMarkList, "itemClicked");
    pointMarkTree.header().resizeSection(0, 150);
    pointMarkTree.header().resizeSection(1, 80);
    pointMarkTree.header().resizeSection(2, 80);
    pointMarkTree.header().resizeSection(3, 80);

    var scaleCombo = formWidget.findChild("Scale");
    scaleCombo["editTextChanged"].connect(PointMarkList, "setScale");

    var labelSizeCombo = formWidget.findChild("LabelSize");
    labelSizeCombo["editTextChanged"].connect(PointMarkList, "setLabelSize");

    // set up tool buttons:
    var widgets = getWidgets(formWidget);
    widgets["PointMarkDraw"].setDefaultAction(
            RGuiAction.getByScriptFile("scripts/Misc/PointMark/PointMarkDraw/PointMarkDraw.js"));
    widgets["PointMarkExport"].setDefaultAction(
            RGuiAction.getByScriptFile("scripts/Misc/PointMark/PointMarkExport/PointMarkExport.js"));

    // set up dock widget:
    var dock = new RDockWidget(qsTr("Point Mark List"), appWin);
    dock.objectName = "PointMarkDock";
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
    dock.shown.connect(function() {
        action.setChecked(true);
        PointMarkList.updateFromDocument(EAction.getDocumentInterface());
    });
    dock.hidden.connect(function() {
        action.setChecked(false);
    });
    dock.visible = false;

    // create a transaction listener to keep widget up to date:
    var tAdapter = new RTransactionListenerAdapter();
    appWin.addTransactionListener(tAdapter);
    tAdapter.transactionUpdated.connect(PointMarkList, "updateFromTransaction");

    // create a transaction listener to add / adjust leaders:
    var tiAdapter = new RInterTransactionListenerAdapter();
    appWin.addInterTransactionListener(tiAdapter);
    tiAdapter.transactionInProgress.connect(PointMarkList, "updateLeaders");

    // create a focus listener to keep widget up to date if document changes:
    var fAdapter = new RFocusListenerAdapter();
    appWin.addFocusListener(fAdapter);
    fAdapter.focusUpdated.connect(PointMarkList, "updateFromDocument");
};
