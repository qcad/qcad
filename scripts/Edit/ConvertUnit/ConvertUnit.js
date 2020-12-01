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

include("scripts/EAction.js");

/**
 * \brief This tool converts a drawing from the current drawing unit to another unit.
 * The coordinates in the drawing are scaled accordingly.
 */
function ConvertUnit(guiAction) {
    EAction.call(this, guiAction);

    this.fromUnit = undefined;
    this.toUnit = undefined;

    this.setUiOptions("ConvertUnit.ui");
}

ConvertUnit.prototype = new EAction();
ConvertUnit.includeBasePath = includeBasePath;

ConvertUnit.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var doc = di.getDocument();
    var optionsToolBar = EAction.getOptionsToolBar();

    // fill combo boxes with available units
    var fromCombo = optionsToolBar.findChild("From");
    ConvertUnit.initUnitCombo(fromCombo);
    var toCombo = optionsToolBar.findChild("To");
    ConvertUnit.initUnitCombo(toCombo);

    this.fromUnit = doc.getUnit();
    fromCombo.currentIndex = this.fromUnit;
    this.toUnit = RS.None;
    toCombo.currentIndex = this.toUnit;
};

ConvertUnit.prototype.doConvert = function() {
    var ret = ConvertUnit.convert(this.getDocumentInterface(), this.fromUnit, this.toUnit);
    if (!isNull(ret)) {
        if (ret[0]===0) {
            EAction.handleUserMessage(ret[1]);
        }
        if (ret[0]===1) {
            EAction.handleUserWarning(ret[1]);
        }
    }

    // The focus ends up in ToolMatrix filter box, for unknown reason
    // Change it back to drawing
    var mdiChild = EAction.getMdiChild();
    mdiChild.setFocus();

    this.terminate();
}

ConvertUnit.convert = function(di, fromUnit, toUnit) {
    if (isNull(di)) {
        return;
    }

    var doc = di.getDocument();

    //var fromUnit = doc.getUnit();

    if (fromUnit===toUnit) {
        return [1, qsTr("Nothing to be done.")];
    }
    if (fromUnit === RS.None || toUnit === RS.None) {
        return [1, qsTr("Unit \"%1\" selected. Nothing to be done").arg(RUnit.unitToName(RS.None))];
    }

    var factor = RUnit.convert(1.0, fromUnit, toUnit);

    doc.startTransactionGroup();

    var docVars = doc.queryDocumentVariables();
    // make sure we don't end up with a metric document with imperial dimension format:
    if (doc.getLinearFormat()===RS.Engineering || doc.getLinearFormat()===RS.ArchitecturalStacked || doc.getLinearFormat()===RS.Architectural) {
        if (!RUnit.isMetric(doc.getUnit()) && RUnit.isMetric(toUnit)) {
            docVars.setKnownVariable(RS.DIMLUNIT, RS.Decimal);
        }
    }
    docVars.setUnit(toUnit);
    docVars.setKnownVariable(RS.DIMSCALE, doc.getKnownVariable(RS.DIMSCALE, 1.0) * factor);

    var op = new RAddObjectsOperation();
    op.setTransactionGroup(doc.getTransactionGroup());
    op.addObject(docVars);
    di.applyOperation(op);

    op = new RAddObjectsOperation();
    op.setTransactionGroup(doc.getTransactionGroup());
    op.setAllowAll(true);

    var ids, i, id;

    // all entities on all blocks:
    ids = doc.queryAllEntities(false, true);
    for (i=0; i<ids.length; i++) {
        id = ids[i];
        var entity = doc.queryEntity(id);
        if (isNull(entity)) {
            continue;
        }

        var blockId = entity.getBlockId();
        var block = doc.queryBlockDirect(blockId);
        if (!isNull(block) && block.isPixelUnit()) {
            // don't touch entities in pixel unit blocks:
            continue;
        }

        // don't scale block references as block content is scaled instead:
        if (isBlockReferenceEntity(entity)) {
            var p = entity.getPosition();
            entity.setPosition(p.operator_multiply(factor));
            var cs = entity.getColumnSpacing();
            entity.setColumnSpacing(cs*factor);
            var rs = entity.getRowSpacing();
            entity.setRowSpacing(rs*factor);
        } else if (isViewportEntity(entity)) {
            var s = entity.getScale();
            entity.scale(factor);
            entity.setScale(s);
            var vc = entity.getViewCenter();
            vc.scale(factor);
            entity.setViewCenter(vc);
            var tc = entity.getViewTarget();
            tc.scale(factor);
            entity.setViewTarget(tc);
        } else if (isDimensionEntity(entity)) {
            var s = entity.getDimScale(false);
            entity.scale(factor);
            if (!RMath.fuzzyCompare(0.0, s)) {
                // dimension has individual scale factor (property, override):
                entity.setDimScale(s*factor);
            }
        } else {
            entity.scale(factor);
        }
        op.addObject(entity, false);
    }

    // adjust views:
    ids = doc.queryAllViews();
    for (i=0; i<ids.length; i++) {
        id = ids[i];
        var v = doc.queryView(id);
        v.scale(factor);
        op.addObject(v, false);
    }

    // adjust view:
    var view = di.getLastKnownViewWithFocus();
    if (!isNull(view)) {
        var box = view.getBox();
        var c1 = box.getCorner1();
        var c2 = box.getCorner2();
        c1.scale(factor);
        c2.scale(factor);
        view.zoomTo(new RBox(c1, c2));
    }

    // convert all print offsets in all blocks:
    // convert all stored block zoom factors / offsets:
    var views = EAction.getGraphicsViews(di);
    var blockIds = doc.queryAllBlocks();
    for (var k=0; k<blockIds.length; k++) {
        var blockId = blockIds[k];
        var block = doc.queryBlock(blockId);
        var offsetX = block.getCustomProperty("QCAD", "PageSettings/OffsetX", undefined);
        var offsetY = block.getCustomProperty("QCAD", "PageSettings/OffsetY", undefined);

        if (!isNull(offsetX)) {
            block.setCustomProperty("QCAD", "PageSettings/OffsetX", offsetX*factor);
            block.setCustomProperty("QCAD", "PageSettings/OffsetY", offsetY*factor);
        }
        op.addObject(block);

        for (i=0; i<views.length; i++) {
            view = views[i];

            if (!isFunction(view.property)) {
                continue;
            }

            var blockZoom = view.property("blockZoom");
            if (isNull(blockZoom)) {
                continue;
            }

            blockZoom[blockId] = [view.getFactor() * factor, view.getOffset().operator_multiply(factor)];
            view.setProperty("blockZoom", blockZoom);
        }
    }

    di.applyOperation(op);

    //var offset = Print.getOffset(doc);
    //offset.scale(factor);
    //Print.setOffset(di, offset);

    doc.rebuildSpatialIndex();

    return [0, qsTr("Converted drawing from %1 to %2").arg(RUnit.unitToName(fromUnit)).arg(RUnit.unitToName(toUnit)) ];
};

ConvertUnit.initUnitCombo = function(unitCombo) {
    // available units in DXF/DWG
    // int values correspond to unit codes from DXF spec
    unitCombo.clear();
    for (var u=RS.None; u<=RS.MaxUnit; u++) {
        unitCombo.addItem(RUnit.unitToName(u), u);
    }
};

ConvertUnit.prototype.slotFromChanged = function(value) {
    this.fromUnit = value;
}

ConvertUnit.prototype.slotToChanged = function(value) {
    this.toUnit = value;
}

ConvertUnit.prototype.slotConvert = function() {
    this.doConvert();
}
