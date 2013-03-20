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

include("../Line.js");

/**
 * \class LineRectangleSize
 * \brief Rectangle from point and size.
 * \ingroup ecma_draw_line
 */
function LineRectangleSize(guiAction) {
    Line.call(this, guiAction);

    this.State = {
        SettingPosition : 0
    };

    this.setUiOptions("LineRectangleSize.ui");

    // note: these are not default (default are defined in the .ui file),
    // values are provided here to make this class functional from the start.
    this.pos = undefined;
    this.width = 1;
    this.height = 1;
    //this.connected = false;
    
    // reference point window
    //this.rpw = undefined;
    
    // [ObjectName], [Shown Text], offset vector
    this.rbReferencePoints = new Array(
        [ "TopLeft", qsTr("Top Left"), new RVector(-1, 1) ],
        [ "Top", qsTr("Top"), new RVector(0, 1) ],
        [ "TopRight", qsTr("Top Right"), new RVector(1, 1) ],
        [ "Left", qsTr("Left"), new RVector(-1, 0) ],
        [ "Middle", qsTr("Middle"), new RVector(0, 0) ],
        [ "Right", qsTr("Right"), new RVector(1, 0) ],
        [ "BottomLeft", qsTr("Bottom Left"), new RVector(-1, -1) ],
        [ "Bottom", qsTr("Bottom"), new RVector(0, -1) ],
        [ "BottomRight", qsTr("Bottom Right"), new RVector(1, -1) ]
    );
    this.referencePoint = this.rbReferencePoints[0][2]; 
}

LineRectangleSize.prototype = new Line();

LineRectangleSize.prototype.initUiOptions = function(resume) {
    Line.prototype.initUiOptions.call(this, resume);
    
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");

    for (var i=0; i<this.rbReferencePoints.length; i++) {
        refPointCombo.addItem(this.rbReferencePoints[i][1], this.rbReferencePoints[i][2]);
    }

    //if (!this.connected) {
    //    refPointCombo.clicked.connect(this, "showReferencePointWidget");
    //    this.connected = true;
    //}
    
    //var icon = new QIcon(this.basePath + "/Down.svg");
    //refPointCombo = objectFromPath("MainWindow::Options::ReferencePointButton");
    //refPointCombo.icon = icon;
};

LineRectangleSize.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);
    this.setState(this.State.SettingPosition);
};

/*
LineRectangleSize.prototype.showReferencePointWidget = function() {
    qDebug("LineRectangleSize.prototype.showReferencePointWidget");

    var btRefPoint = objectFromPath("MainWindow::Options::ReferencePointButton");
    this.rpw = this.createWidget("ReferencePoint.ui");
    this.rpw.setParent(objectFromPath("MainWindow"));
    var flags = new Qt.WindowFlags(Qt.Popup);
    this.rpw.setWindowFlags(flags);
    var p = btRefPoint.mapToGlobal(new QPoint(0, btRefPoint.height + 2));
    var icon = new QIcon(this.basePath + "/Up.svg");
    btRefPoint.icon = icon;
    // this.rpw.move(p.x, p.y);
    this.rpw.pos = p;
    this.rpw.setFixedSize(100, 70);
    var w = this.rpw.findChild("InnerWidget");
    w.setFixedSize(90, 60);
    this.rpw.show();
    for ( var i = 0; i < this.rbReferencePoints.length; ++i) {
        var rb = this.rbReferencePoints[i];
        w = this.rpw.findChild(rb[0]);
        if (rb[2] == this.referencePoint) {
            w.checked = true;
        }
        w.clicked.connect(this, "setReferencePointSlot");
    }
};
*/

/*
LineRectangleSize.prototype.setReferencePointSlot = function() {
    if (isNull(this.rpw)) {
        return;
    }
    
    for (var i = 0; i < this.rbReferencePoints.length; ++i) {
        var rb = this.rbReferencePoints[i];
        var w = this.rpw.findChild(rb[0]);
        if (w.checked) {
            var tw = objectFromPath("MainWindow::Options::ReferencePointButton");
            tw.text = rb[1];
            this.referencePoint = rb[2];
            break;
        }
    }
    var icon = new QIcon(this.basePath + "/Down.svg");
    var btRefPoint = objectFromPath("MainWindow::Options::ReferencePointButton");
    btRefPoint.icon = icon;

    // short delay before closing
    var date = new Date();
    var curDate = null;
    var c = 0;
    do {
        curDate = new Date();
        ++c;
    } while (curDate - date < 200);

    this.rpw.close();
    this.update();
};
*/

LineRectangleSize.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPosition = qsTr("Position");
    this.setCommandPrompt(trPosition);
    this.setLeftMouseTip(trPosition);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

LineRectangleSize.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();
    this.pos = event.getModelPosition();
    var op = this.getOperation(false);
    if (!isNull(op)) {
        di.applyOperation(op);
        di.setRelativeZero(this.pos);
    }
};

LineRectangleSize.prototype.coordinateEventPreview = function(event) {
    this.pos = event.getModelPosition();
    var op = this.getOperation(false);
    if (isNull(op)) {
        return;
    }
    this.getDocumentInterface().previewOperation(op);
};

LineRectangleSize.prototype.getOperation = function(preview) {
    var i;
    
    if (isNull(this.pos) || isNull(this.width) || isNull(this.height)) {
        return;
    }
    
    var x = this.pos.x;
    var y = this.pos.y;
    var w2 = this.width / 2;
    var h2 = this.height / 2;
    var corners = new Array(
        new RVector(x - w2, y - h2),
        new RVector(x + w2, y - h2),
        new RVector(x + w2, y + h2),
        new RVector(x - w2, y + h2)
    );
    // apply reference point vector
    for (i = 0; i < corners.length; ++i) {
        corners[i] = new RVector(
                corners[i].x - w2 * this.referencePoint.x,
                corners[i].y - h2 * this.referencePoint.y);
    }

    var op = new RAddObjectsOperation();
    for (i = 0; i < 4; ++i) {
        var line = new RLineEntity(this.getDocument(),
                new RLineData(corners[i], corners[(i + 1) % 4]));
        op.addObject(line);
    }
    return op;
};

/*
LineRectangleSize.prototype.update = function() {
    var di = this.getDocumentInterface();
    di.clearPreview();
    var op = this.getOperation(false);
    if (!isNull(op)) {
        di.previewOperation(op);
    }
    di.repaintViews();
};
*/

LineRectangleSize.prototype.slotWidthChanged = function(value) {
    this.width = value;
    this.updatePreview(true);
};

LineRectangleSize.prototype.slotHeightChanged = function(value) {
    this.height = value;
    this.updatePreview(true);
};

LineRectangleSize.prototype.slotReferencePointChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");

    this.referencePoint = refPointCombo.itemData(refPointCombo.currentIndex);

    this.updatePreview(true);
};

