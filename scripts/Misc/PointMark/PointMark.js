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

/**
 * \defgroup ecma_misc_point PointMark Mark Tools
 * \ingroup ecma_misc
 *
 * \brief This module contains ECMAScript implementations of 
 * point mark drawing, export and visualization tools.
 */
include("../Misc.js");

/**
 * \class PointMark
 * \brief Base class for all point mark tools.
 * \ingroup ecma_misc_point
 */
function PointMark(guiAction) {
    Misc.call(this, guiAction);
}

PointMark.prototype = new Misc();
PointMark.includeBasePath = includeBasePath;

PointMark.prototype.beginEvent = function() {
    Misc.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName=="PointMarkMenu") {
        EAction.showCadToolBarPanel("PointMarkToolsPanel");
        this.terminate();
    }
};

PointMark.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        20000,
        PointMark.getTitle(),
        "pointmark",
        PointMark.includeBasePath + "/PointMark.svg"
    );
    menu.setProperty("scriptFile", PointMark.includeBasePath + "/PointMark.js");
    return menu;
};

PointMark.getToolBar = function() {
    var tb = EAction.getToolBar(PointMark.getTitle(), "PointMark");
    tb.visible = false;
    return tb;
};

PointMark.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "PointMarkMenu";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Point Mark Tools"), mtb);
        action.setScriptFile(PointMark.includeBasePath + "/PointMark.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(PointMark.includeBasePath + "/PointMark.svg");
        action.setStatusTip(qsTr("Show point mark tools"));
        action.setDefaultShortcut(new QKeySequence("w,t"));
        action.setNoState();
        action.setProperty("SortOrder", 20000);
        action.setDefaultCommands(["pointmarkmenu"]);
        CadToolBarPanel.prototype.addAction.call(mtb, action);
    }

    var tb = EAction.getCadToolBarPanel(
        PointMark.getTitle(),
        "PointMarkToolsPanel",
        true
    );
    return tb;
};

PointMark.getTitle = function() {
    return qsTr("&Point Mark");
};

PointMark.prototype.getTitle = function() {
    return PointMark.getTitle();
};

/**
 * \return All block reference IDs representing benchmarks or point marks.
 * \param type 'b', 'p', 'a' (benchmarks, points, all [default])
 */
PointMark.queryAllMarkIds = function(doc, type) {
    if (isNull(type)) {
        type='a';
    }

    var ret = [];

    var ids = doc.queryAllBlockReferences();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var blockRef = doc.queryEntityDirect(id);
        if (isNull(blockRef)) {
            continue;
        }

        var handle = PointMark.getBenchmarkHandle(blockRef);
        if (handle===RObject.INVALID_HANDLE) {
            continue;
        }

        if (type==='a') {
            ret.push(id);
            continue;
        }

        if (type==='b' && handle===blockRef.getHandle()) {
            ret.push(id);
            continue;
        }

        if (type==='p' && handle!==blockRef.getHandle()) {
            ret.push(id);
            continue;
        }
    }

    return ret;
};

/**
 * \return String representing label of the given benchmark or point mark.
 */
PointMark.getMarkLabel = function(doc, blockRefId) {
    var blockAttribIds = doc.queryChildEntities(blockRefId, RS.EntityAttribute);
    if (blockAttribIds.length!==1) {
        return undefined;
    }
    return doc.queryEntityDirect(blockAttribIds[0]);
};

/**
 * \return String representing label of the given benchmark or point mark.
 */
PointMark.getMarkLabelText = function(doc, blockRefId) {
    var attrib = PointMark.getMarkLabel(doc, blockRefId);
    if (isNull(attrib)) {
        return "";
    }

    return attrib.getPlainText();
};

/**
 * \return Nummerical benchmark handle the given point mark or benchmark refers to or -1.
 */
PointMark.getBenchmarkHandle = function(blockRef) {
    var handle = blockRef.getCustomProperty("QCAD", "benchmark", undefined);
    if (isNull(handle)) {
        return RObject.INVALID_HANDLE;
    }
    return parseInt(handle, 16);
};

PointMark.setBenchmarkHandle = function(blockRef, handle) {
    blockRef.setCustomProperty("QCAD", "benchmark", "0x" + handle.toString(16));
};

/**
 * \return Nummerical leader handle the given point mark or benchmark refers to or -1.
 */
PointMark.getLeaderHandle = function(blockRef) {
    var handle = blockRef.getCustomProperty("QCAD", "leader", undefined);
    if (isNull(handle)) {
        return RObject.INVALID_HANDLE;
    }
    return parseInt(handle, 16);
};

PointMark.setLeaderHandle = function(blockRef, handle) {
    blockRef.setCustomProperty("QCAD", "leader", "0x" + handle.toString(16));
};

/**
 * \return List of all point marks including bechmarks with
 * position and label in the format:
 *
 * [
 *   [ ["BM001",RVector(0,0,0),"pt_layer","0xb1"], ["POINT001",RVector(10,5,0),"pt_layer","0xb2"], ... ],
 *   [ ["BM002",RVector(0,0,0),"pt_layer","0xc1"], ["POINT001",RVector(-7,2,0),"pt_layer","0xc2"], ... ],
 *   ...
 * ]
 */
PointMark.getPointMarkTree = function(doc) {
    var ret = [];

    var handleMap = {};
    var i;

    //var objIds = doc.queryAllBlockReferences();
    var objIds = PointMark.queryAllMarkIds(doc);

    // two passes: add benchmarks, add points:
    for (var p=0; p<2; p++) {
        for (i=0; i<objIds.length; i++) {
            var objId = objIds[i];
            var blockRef = doc.queryObjectDirect(objId);
            if (!isBlockReferenceEntity(blockRef)) {
                continue;
            }

            // get benchmark handle from custom property:
            var bmHandle = PointMark.getBenchmarkHandle(blockRef);
            if (bmHandle===RObject.INVALID_HANDLE) {
                continue;
            }

            // first loop, not a benchmark:
            if (p==0 && bmHandle!==blockRef.getHandle()) {
                continue;
            }

            // second loop, not a point mark:
            if (p==1 && bmHandle===blockRef.getHandle()) {
                continue;
            }

            // query benchmark:
            var bm = doc.queryObjectByHandle(bmHandle);
            if (isNull(bm) || !isBlockReferenceEntity(bm)) {
                continue;
            }

            var label = PointMark.getMarkLabelText(doc, objId);
            var pos = blockRef.getPosition().operator_subtract(bm.getPosition());

            if (p===0) {
                // benchmark found:
                ret.push([[label,pos,blockRef.getLayerName(),bmHandle]]);
                handleMap[bmHandle] = ret.length-1;
            }
            else {
                // point mark found:
                if (isNull(handleMap[bmHandle])) {
                    continue;
                }
                if (isNull(ret[handleMap[bmHandle]])) {
                    continue;
                }

                ret[handleMap[bmHandle]].push([label,pos,blockRef.getLayerName(),blockRef.getHandle()]);
            }
        }
    }

    // sort by benchmark:
    ret.sort(function(a,b) {
        if (a[0].length===0) return -1;
        if (b[0].length===0) return 1;

        if (a[0][0] < b[0][0]) return -1;
        if (a[0][0] > b[0][0]) return 1;
        return 0;
    });

    // sort by points:
    for (i=0; i<ret.length; i++) {
        ret[i] = [ret[i][0]].concat(
            ret[i].slice(1).sort(function(a,b) {
                if (a[0] < b[0]) return -1;
                if (a[0] > b[0]) return 1;
                return 0;
            })
        );
    }

    return ret;
};

PointMark.getDock = function() {
    var appWin = RMainWindowQt.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }
    return appWin.findChild("PointMarkDock");
};

PointMark.getTreeWidget = function() {
    var dock = PointMark.getDock();
    if (isNull(dock)) {
        return undefined;
    }
    return dock.findChild("PointMarkTree");
};
