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

include("../../WidgetFactory.js");
include("scripts/Widgets/AutoZoomView/AutoZoomView.js");

/**
 * \class HatchDialog
 * \brief Hatch creation or editing dialog.
 * \ingroup ecma_draw_hatch
 */
function HatchDialog() {
    this.dialog = undefined;
}

HatchDialog.basePath = includeBasePath;

HatchDialog.prototype.show =  function(hatchDataIn) {
    this.dialog = WidgetFactory.createDialog(HatchDialog.basePath, "HatchDialog.ui", EAction.getMainWindow());
    //this.dialog.windowIcon = new QIcon(HatchDialog.basePath + "/Hatch.svg");

    var radioSolid = this.dialog.findChild("SolidFill");
    var radioHatch = this.dialog.findChild("HatchPattern");
    var comboPattern = this.dialog.findChild("Pattern");
    var editAngle = this.dialog.findChild("Angle");
    var editScale = this.dialog.findChild("Scale");
    var groupPattern = this.dialog.findChild("PatternGroup");

    if (radioSolid.checked) {
        groupPattern.enabled = false;
    }

    editAngle.valueChanged.connect(this, "patternChanged");
    radioSolid.toggled.connect(this, "patternChanged");
    //comboPattern["activated(QString)"].connect(this, "patternChanged");
    comboPattern["currentIndexChanged(QString)"].connect(this, "patternChanged");

    var storage = new RMemoryStorage();
    var spatialIndex = new RSpatialIndexSimple();
    var document = new RDocument(storage, spatialIndex);
    this.documentInterface = new RDocumentInterface(document);
    this.documentInterface.setNotifyListeners(false);
    var layout = this.dialog.findChild("PreviewLayout");
    var view = new AutoZoomView(this.dialog);
    view.objectName = "PreviewView";
    layout.addWidget(view, 0, 0);
    view.setScene(new RGraphicsSceneQt(this.documentInterface));
    view.disableGestures();

    var patternNames;
    if (RUnit.isMetric(EAction.getDocument().getUnit())) {
        patternNames = RPatternListMetric.getNames();
    }
    else {
        patternNames = RPatternListImperial.getNames();
    }

    for (var i=0; i<patternNames.length; i++) {
        var patternName = patternNames[i];
        comboPattern.addItem(patternName);
    }

    if (!isNull(hatchDataIn)) {
        // initialize dialog from given hatch data (hatchDataIn):
        // TODO
    }
    else {
        // initialize dialog from previous values (ini file):
        WidgetFactory.restoreState(this.dialog);
    }

    this.dialog.show();
    this.patternChanged();

    var res = this.dialog.exec();
    this.documentInterface.destroy();
    if (!res) {
        this.dialog.destroy();
        return undefined;
    }

    WidgetFactory.saveState(this.dialog);

    // analyze dialog input:
    var hatchDataOut = isNull(hatchDataIn) ? new RHatchData() : hatchDataIn;
    hatchDataOut.setAngle(editAngle.getValue());
    hatchDataOut.setScale(editScale.getValue());
    hatchDataOut.setSolid(radioSolid.checked);
    hatchDataOut.setPatternName(radioSolid.checked ? "SOLID" : comboPattern.currentText);

    this.dialog.destroy();
    return hatchDataOut;
};

HatchDialog.prototype.patternChanged = function() {
    this.documentInterface.clear();
    var document = this.documentInterface.getDocument();
    var metric = RUnit.isMetric(EAction.getDocument().getUnit());

    var radioSolid = this.dialog.findChild("SolidFill");
    var comboPattern = this.dialog.findChild("Pattern");
    var editAngle = this.dialog.findChild("Angle");
    var editScale = this.dialog.findChild("Scale");

    var patternName = comboPattern.currentText;
    var angle = editAngle.getValue();
    if (isNaN(angle)) {
        angle = 0.0;
    }

    var scale = editScale.getValue();
    if (isNaN(scale)) {
        scale = 1.0;
    }

    var s;

    if (radioSolid.checked) {
        s = 30.0;
        patternName = "SOLID";
    }
    else {
        var pattern;
        if (metric) {
            document.setUnit(RS.Millimeter);
            pattern = RPatternListMetric.get(patternName);
            s = 30.0;
        }
        else {
            document.setUnit(RS.Inch);
            pattern = RPatternListImperial.get(patternName);
            if (patternName.startsWith("AR-") || patternName.startsWith("ACAD_")) {
                s = 30.0;
            }
            else {
                s = 3.0;
            }
        }

        if (isNull(pattern)) {
            return;
        }
        //s = pattern.getSize().getWidth() * 1.5;
    }

    var data = new RHatchData(radioSolid.checked, 1.0, angle, patternName);
    data.setLineweight(RLineweight.Weight015);
    var bgColor = RSettings.getColor("GraphicsViewColors/BackgroundColor", new RColor("black"));
    if (bgColor.lightness()>200) {
        data.setColor(new RColor("black"));
    }
    else {
        data.setColor(new RColor("white"));
    }
    data.newLoop();
    data.addBoundary(new RLine(new RVector(0,0), new RVector(s,0)));
    data.addBoundary(new RLine(new RVector(s,0), new RVector(s,s)));
    data.addBoundary(new RLine(new RVector(s,s), new RVector(0,s)));
    data.addBoundary(new RLine(new RVector(0,s), new RVector(0,0)));
    var hatch = new RHatchEntity(document, data);
    var op = new RAddObjectOperation(hatch, false, false);
    this.documentInterface.applyOperation(op);
    this.documentInterface.autoZoom();
};
