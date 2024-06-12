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

include("scripts/Snap/Snap.js");
include("scripts/WidgetFactory.js");

/**
 * RSnap implementation for coordinate snap.
 */
function RSnapCoordinate(guiAction) {
    RSnap.call(this);
    this.coordinate = new RVector();
    this.relative = false;

    if (isNull(guiAction)) {
        return;
    }

    this.initAction(guiAction);
}

RSnapCoordinate.prototype = new RSnap();

RSnapCoordinate.prototype.initAction = function(guiAction) {
    this.action = new EAction(guiAction);
    if (!isNull(this.action.setUiOptions)) {
        this.action.setUiOptions(SnapCoordinate.includeBasePath + "/SnapCoordinate.ui");
    }
    var snap = this;

    this.action.slotXChanged = function(value) {
        snap.coordinate.x = value;
        snap.update();
    };
    this.action.slotYChanged = function(value) {
        snap.coordinate.y = value;
        snap.update();
    };
    this.action.slotRelativeChanged = function(on) {
        snap.relative = on;
        snap.update();
    };
    this.action.slotSet = function() {
        var ce = snap.getCoordinateEvent();
        if (!isNull(ce)) {
            var di = EAction.getDocumentInterface();
            di.coordinateEvent(ce);
        }
    };
};

RSnapCoordinate.prototype.snap = function(position, view) {
    var di = EAction.getDocumentInterface();
    return this.getCoordinate();
};

RSnapCoordinate.prototype.showUiOptions = function() {
    if (isNull(this.action)) {
        qDebug("RSnapCoordinate.prototype.showUiOptions: action is NULL");
        return;
    }

    this.action.showUiOptions(false);

    // init Set button:
    var optionsToolBar = EAction.getOptionsToolBar();
    var setButton = optionsToolBar.findChild("Set");
    // can't have both Return and Enter here:
    setButton.shortcut = new QKeySequence("Return");
    setButton.toolTip =
        RGuiAction.formatToolTip(
            qsTr("Set coordinate"),
            qsTr("Enter")
        );

    // trigger snap when number pad enter is pressed in coordinate line edits:
    var self = this;
    var widgetNames = ["X", "Y", "R", "A"];
    for (var i=0; i<widgetNames.length; i++) {
        var widgetName = widgetNames[i];

        var le = optionsToolBar.findChild(widgetName);
        if (!isNull(le)) {
            le.returnPressed.connect(function() {
                self.action.slotSet();
            });
        }
    }
};

RSnapCoordinate.prototype.hideUiOptions = function() {
    this.action.hideUiOptions();
};

RSnapCoordinate.prototype.update = function() {
    var ce = this.getCoordinateEvent();
    if (isNull(ce)) {
        return;
    }
    var di = EAction.getDocumentInterface();
    di.clearPreview();
    di.coordinateEventPreview(ce);
    di.repaintViews();
};

RSnapCoordinate.prototype.getCoordinate = function() {
    var di = EAction.getDocumentInterface();
    var coordinate = this.coordinate;
    if (this.relative) {
        coordinate = coordinate.operator_add(di.getRelativeZero());
    }
    return coordinate;
};

RSnapCoordinate.prototype.getCoordinateEvent = function() {
    var di = EAction.getDocumentInterface();
    var view = di.getGraphicsViewWithFocus();
    if (isNull(view)) {
        return undefined;
    }
    var scene = view.getScene();
    if (isNull(scene)) {
        return undefined;
    }
    var ce = new RCoordinateEvent(this.getCoordinate(), scene, getRGraphicsView(view));
    return ce;
};



/**
 * \class SnapCoordinate
 * \ingroup ecma_snap
 * \brief Enter coordinate.
 */
function SnapCoordinate(guiAction) {
    Snap.call(this, guiAction);
}

SnapCoordinate.prototype = new Snap();
SnapCoordinate.includeBasePath = includeBasePath;

SnapCoordinate.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/SnapCoordinate/SnapCoordinate.js");
    var s = new RSnapCoordinate(guiAction);
    this.getDocumentInterface().setSnap(s);
    this.terminate();
};

