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
    if (fromUnit === 0 || toUnit === 0) {
        return [1, qsTr("RS.None selected - Nothing to be done")];
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
        } else if (isDimensionEntity(entity)) {
            var s = entity.getDimScale();
            s = s * factor;
            entity.setDimScale(s);
            entity.scale(factor);
        } else {
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

ConvertUnit.initUnitCombo = function(unitCombo) {
    // available units in DXF/DWG
    // int values correspond to unit codes from DXF spec
    unitCombo.clear();
    unitCombo.addItem(qsTr("None"), RS.None);
    unitCombo.addItem(qsTr("Inch"), RS.Inch);
    unitCombo.addItem(qsTr("Foot"), RS.Foot);
    unitCombo.addItem(qsTr("Mile"), RS.Mile);
    unitCombo.addItem(qsTr("Millimeter"), RS.Millimeter);
    unitCombo.addItem(qsTr("Centimeter"), RS.Centimeter);
    unitCombo.addItem(qsTr("Meter"), RS.Meter);
    unitCombo.addItem(qsTr("Kilometer"), RS.Kilometer);
    unitCombo.addItem(qsTr("Microinch"), RS.Microinch);
    unitCombo.addItem(qsTr("Mil"), RS.Mil);
    unitCombo.addItem(qsTr("Yard"), RS.Yard);
    unitCombo.addItem(qsTr("Angstrom"), RS.Angstrom);
    unitCombo.addItem(qsTr("Nanometer"), RS.Nanometer);
    unitCombo.addItem(qsTr("Micron"), RS.Micron);
    unitCombo.addItem(qsTr("Decimeter"), RS.Decimeter);
    unitCombo.addItem(qsTr("Decameter"), RS.Decameter);
    unitCombo.addItem(qsTr("Hectometer"), RS.Hectometer);
    unitCombo.addItem(qsTr("Gigameter"), RS.Gigameter);
    unitCombo.addItem(qsTr("Astro"), RS.Astro);
    unitCombo.addItem(qsTr("Lightyear"), RS.Lightyear);
    unitCombo.addItem(qsTr("Parsec"), RS.Parsec);
    //unitCombo.addItem(qsTr("Plu"), RS.Plu);
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
