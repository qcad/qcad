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

include("Modify.js");

/**
 * \class Transform
 * \brief Base class for all transformation tools (move, copy, rotate, mirror, ...).
 */
function Transform(guiAction) {
    Modify.call(this, guiAction);
    
    this.useCurrentAttributes = false;
    this.copies = 0;
    this.copy = undefined;

    this.useDialog = true;
}

Transform.prototype = new Modify();
Transform.includeBasePath = includeBasePath;

Transform.prototype.finishEvent = function() {
    this.clearCache();
    Modify.prototype.finishEvent.call(this);
};

Transform.prototype.verifySelection = function() {
    var di = this.getDocumentInterface();
    if (!di.hasSelection()) {
        EAction.handleUserWarning(qsTr("This tool requires a selection"));
        this.terminate();
        return false;
    }

    return true;
};

/**
 * Implemetation of getOperation for tools that operate on a selection and
 * do something with every entity in the selection (e.g. move, rotate, ...).
 * The callback function 'this.transform(entity, copy number)' is called for
 * every selected entity.
 */
Transform.prototype.getOperation = function(preview, selectResult, cache) {
    if (isNull(this.copies)) {
        return undefined;
    }

    if (isNull(selectResult)) {
        selectResult = true;
    }
    if (isNull(cache)) {
        cache = false;
    }

    var op, di, ids;

    var doc = this.getDocument();

    if (cache) {
        // return cached document as paste operation:
        if (!isNull(this.diTrans) && preview) {
            op = new RPasteOperation(this.diTrans.getDocument());
            op.setOffset(this.targetPoint);
            return op;
        }

        this.clearCache();

        var docTrans = new RDocument(new RMemoryStorage(), new RSpatialIndexSimple());
        docTrans.copyVariablesFrom(doc);
        this.diTrans = new RDocumentInterface(docTrans);
        this.diTrans.setNotifyListeners(false);

        // copy selection to cache document:
        var copyOp = new RCopyOperation(new RVector(0,0), doc);
        copyOp.setClear(false);
        this.diTrans.applyOperation(copyOp);
        di = this.diTrans;
        ids = this.diTrans.getDocument().queryAllEntities();
    }
    else {
        di = this.getDocumentInterface();
        ids = di.getDocument().querySelectedEntities();
    }

    var document = di.getDocument();
    var i, k, id, entity, entityP;
    var copies = this.getCopies();
    var num = copies;
    if (num===0) {
        num=1;
    }

    op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    for (k=1; k<=num; k++) {
        for (i=0; i<ids.length; i++) {
            if (!cache && preview && op.getPreviewCounter()>RSettings.getPreviewEntities()) {
                break;
            }

//            if (i%1000===0) {
//                qDebug("progress: %1%".arg(i/ids.length*100));
//            }

            id = ids[i];
            entityP = document.queryEntity(id);
            if (isNull(entityP)) {
                continue;
            }
            //qDebug("%1 / %2".arg(i).arg(ids.length-1));

            // entity is valid as long as entityP is valid:
            //entity = entityP.data();
            entity = entityP.clone();

            // copy: assign new IDs
            if (copies>0) {
                if (!preview && !selectResult) {
                    entity.setSelected(false);
                }
            }

            var f = RAddObjectsOperation.NoFlags;
            if (!this.useCurrentAttributes) {
                f = RAddObjectsOperation.UseAttributes | RAddObjectsOperation.GeometryOnly;
            }

            if (cache) {
                op.deleteObject(entity);
                this.transform(entity, k, op, preview, f | RAddObjectsOperation.ForceNew);
            }
            else {
                if (copies>0) {
                    f = f | RAddObjectsOperation.ForceNew;
                }
                this.transform(entity, k, op, preview, f);
            }
        }
        op.endCycle();
    }

    if (cache) {
        di.applyOperation(op);
    }

    // deselect original entities, all copies are selected:
    if (!preview && selectResult) {
        di.deselectEntities(ids);
    }

    if (cache) {
        op = new RPasteOperation(this.diTrans.getDocument());
        op.setOffset(this.targetPoint);
    }

    return op;
};

Transform.prototype.clearCache = function() {
    // clear cache:
    if (!isNull(this.diTrans)) {
        this.diTrans.destroy();
    }

    this.diTrans = undefined;
    //Modify.prototype.updatePreview.call(this);
};

Transform.prototype.slotCopyChanged = function(checked) {
    this.copy = checked;

    var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("LabelNumberOfCopies");
    if (!isNull(w)) {
        w.enabled = checked;
    }
    w =  optionsToolBar.findChild("NumberOfCopies");
    if (!isNull(w)) {
        w.enabled = checked;
    }
};

Transform.prototype.slotNumberOfCopiesChanged = function(v) {
    this.copies = v;
};

Transform.prototype.slotUseCurrentAttributesChanged = function(checked) {
    this.useCurrentAttributes = checked;
};

Transform.prototype.getCopies = function() {
    if (this.copy===false) {
        return 0;
    }
    return this.copies;
};
