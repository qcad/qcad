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

include("../../WidgetFactory.js");

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
    var doc = EAction.getDocument();
    if (isNull(doc)) {
        return;
    }

    this.dialog = WidgetFactory.createDialog(HatchDialog.basePath, "HatchDialog.ui", EAction.getMainWindow());

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

    var previewDoc = new RDocument(new RMemoryStorage(), new RSpatialIndexSimple());
    //previewDoc.setMeasurement(doc.getMeasurement());
    this.previewDi = new RDocumentInterface(previewDoc);
    this.previewDi.setNotifyListeners(false);
    var layout = this.dialog.findChild("PreviewLayout");

    // keep this include here to make sure command line tools
    // can use Hatch.js without requiring a GUI:
    include("scripts/Widgets/AutoZoomView/AutoZoomView.js");
    var view = new AutoZoomView(this.dialog);
    view.objectName = "PreviewView";
    view.setPaintOrigin(false);
    layout.addWidget(view, 0, 0);
    view.setScene(new RGraphicsSceneQt(this.previewDi));
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
        var rbSolidFill = this.dialog.findChild("SolidFill");
        var rbHatchPattern = this.dialog.findChild("HatchPattern");
        if (hatchDataIn.isSolid()) {
            rbSolidFill.checked = true;
        }
        else {
            rbHatchPattern.checked = true;
        }

        var cbPattern = this.dialog.findChild("Pattern");
        var idx = cbPattern.findText(hatchDataIn.getPatternName(), Qt.MatchFixedString);
//        if (idx===-1) {
//            cbPattern.currentIndex = 0;
//        }
//        else {
            cbPattern.currentIndex = idx;
//        }

        var leAngle = this.dialog.findChild("Angle");
        leAngle.setValue(hatchDataIn.getAngle());
        var leScale = this.dialog.findChild("Scale");
        leScale.setValue(hatchDataIn.getScale());
    }
    else {
        // initialize dialog from previous values (ini file):
        WidgetFactory.restoreState(this.dialog);
    }

    this.dialog.show();
    this.patternChanged();

    var res = this.dialog.exec();
    this.previewDi.destroy();
    if (!res) {
        this.dialog.destroy();
        EAction.activateMainWindow();
        return undefined;
    }

    WidgetFactory.saveState(this.dialog);

    // analyze dialog input:
    var hatchDataOut = isNull(hatchDataIn) ? new RHatchData() : hatchDataIn;
    hatchDataOut.setDocument(EAction.getDocument());
    hatchDataOut.setAngle(editAngle.getValue());
    hatchDataOut.setScale(editScale.getValue());
    hatchDataOut.setSolid(radioSolid.checked);
    hatchDataOut.setPatternName(radioSolid.checked ? "SOLID" : comboPattern.currentText);

    this.dialog.destroy();
    EAction.activateMainWindow();
    return hatchDataOut;
};

HatchDialog.prototype.patternChanged = function() {
    this.previewDi.clear();
    var previewDoc = this.previewDi.getDocument();
    var metric = EAction.getDocument().isMetric();

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

    // size of preview square:
    var size = 30.0;

    if (radioSolid.checked) {
        //size = 30.0;
        patternName = "SOLID";
    }
    else {
        var pattern;
        if (metric) {
            previewDoc.setUnit(RS.Millimeter);
            previewDoc.setMeasurement(RS.Metric);
            pattern = RPatternListMetric.get(patternName);
            if (patternName.startsWith("AR-") /*|| patternName.startsWith("ACAD_")*/) {
                size = 900.0;
            }
        }
        else {
            size = 2;
            previewDoc.setUnit(RS.Inch);
            previewDoc.setMeasurement(RS.Imperial);
            pattern = RPatternListImperial.get(patternName);
            if (patternName.startsWith("ACAD_")) {
                size = 30.0;
            }
            if (patternName.startsWith("AR-") /*|| patternName.startsWith("ACAD_")*/) {
                size = 30.0;
            }
        }

        if (isNull(pattern)) {
            return;
        }
    }

    var data = new RHatchData(radioSolid.checked, 1.0, angle, patternName);
    data.setDocument(previewDoc);
    data.setLineweight(RLineweight.Weight015);
    var bgColor = RSettings.getColor("GraphicsViewColors/BackgroundColor", new RColor("black"));
    if (bgColor.lightness()>200) {
        data.setColor(new RColor("black"));
    }
    else {
        data.setColor(new RColor("white"));
    }
    data.newLoop();
    data.addBoundary(new RLine(new RVector(0,0), new RVector(size,0)));
    data.addBoundary(new RLine(new RVector(size,0), new RVector(size,size)));
    data.addBoundary(new RLine(new RVector(size,size), new RVector(0,size)));
    data.addBoundary(new RLine(new RVector(0,size), new RVector(0,0)));
    var hatch = new RHatchEntity(previewDoc, data);
    var op = new RAddObjectOperation(hatch, false, false);
    this.previewDi.applyOperation(op);
    this.previewDi.autoZoom();
};
