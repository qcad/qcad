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
 * \brief This tool converts a drawing from the current drawing unit to inch.
 * The coordinates in the drawing are scaled accordingly.
 */
include("scripts/EAction.js");

function ConvertToInch(guiAction) {
    EAction.call(this, guiAction);
}

ConvertToInch.prototype = new EAction();
ConvertToInch.includeBasePath = includeBasePath;

ConvertToInch.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var ret = ConvertToInch.convert(this.getDocumentInterface(), RS.Inch);

    if (!isNull(ret)) {
        if (ret[0]===0) {
            EAction.handleUserMessage(ret[1]);
        }
        if (ret[0]===1) {
            EAction.handleUserWarning(ret[1]);
        }
    }

    this.terminate();
};


ConvertToInch.convert = function(di, toUnit) {
    if (isNull(di)) {
        return;
    }

    var doc = di.getDocument();

    var fromUnit = doc.getUnit();

    if (fromUnit===toUnit) {
        return [1, qsTr("Nothing to be done.")];
    }

    var factor = RUnit.convert(1.0, fromUnit, toUnit);

    var op = new RAddObjectsOperation();
    op.setAllowAll(true);
    // all entities on all blocks:
    var ids = doc.queryAllEntities(false, true);

    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = doc.queryEntity(id);
        if (isNull(entity)) {
            continue;
        }

        // don't scale block references as block content is scaled instead:
        if (isBlockReferenceEntity(entity)) {
            var p = entity.getPosition();
            entity.setPosition(p.operator_multiply(factor));
        }
        else {
            entity.scale(factor);
        }
        op.addObject(entity, false);
    }

    var docVars = doc.queryDocumentVariables();
    docVars.setUnit(toUnit);
    docVars.setKnownVariable(RS.DIMSCALE, doc.getKnownVariable(RS.DIMSCALE, 1.0) * factor);
    op.addObject(docVars);

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

    di.applyOperation(op);

    doc.rebuildSpatialIndex();

    return [0, qsTr("Converted drawing from %1 to %2").arg(RUnit.unitToName(fromUnit)).arg(RUnit.unitToName(toUnit)) ];
};
