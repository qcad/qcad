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
include("scripts/sprintf.js");
include("scripts/WidgetFactory.js");
include("scripts/Widgets/StatusBar/StatusBar.js");

function CoordinateDisplay() {
}

CoordinateDisplay.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("Coordinate Display") ];
};

CoordinateDisplay.singleShot = undefined;

CoordinateDisplay.widget = undefined;
CoordinateDisplay.lAbs = undefined;
CoordinateDisplay.lRel = undefined;
CoordinateDisplay.lAbsPol = undefined;
CoordinateDisplay.lRelPol = undefined;

CoordinateDisplay.counter = 0;

/**
 * Holder for the coordinate display widget without a layout.
 *
 * The coordinate labels change their text on every mouse move. Inside a
 * layout, every text change propagates a geometry update up through the
 * status bar splitter and status bar to the main window layout, which
 * relayouts and repaints large parts of the main window for every mouse
 * move. This is expensive, especially with RHI graphics views on high
 * resolution displays (lagging cursor on Intel Macs with 5K displays).
 *
 * The holder has no layout, so geometry updates of the coordinate display
 * widget stop here. The holder resizes the coordinate display widget to
 * its own size when it is resized (e.g. through the status bar splitter).
 */
function CoordinateDisplayHolder(parent, child) {
    QWidget.call(this, parent);
    this.child = child;
    child.setParent(this);
    child.objectName = "CoordinateDisplayContent";
    this.objectName = "CoordinateDisplay";
    this.setSizePolicy(child.sizePolicy);
    this.setMinimumSize(child.minimumSize);
    this.setMaximumSize(child.maximumSize);
}

CoordinateDisplayHolder.prototype = new QWidget();

CoordinateDisplayHolder.prototype.resizeEvent = function(event) {
    QWidget.prototype.resizeEvent.call(this, event);
    this.child.setGeometry(0, 0, this.width, this.height);
};

CoordinateDisplay.postInit = function(basePath) {
    var w = WidgetFactory.createWidget(basePath, "CoordinateDisplay.ui");
    CoordinateDisplay.widget = new CoordinateDisplayHolder(null, w);
    StatusBar.addWidget(CoordinateDisplay.widget, 100, RSettings.getBoolValue("StatusBar/CoordinateDisplay", true));
    CoordinateDisplay.forcedUpdateInterval = RSettings.getIntValue("CoordinateDisplay/Interval", 8);

    CoordinateDisplay.lAbs = CoordinateDisplay.widget.findChild("Abs");
    CoordinateDisplay.lAbs.font = RSettings.getStatusBarFont();
    CoordinateDisplay.lRel = CoordinateDisplay.widget.findChild("Rel");
    CoordinateDisplay.lRel.font = RSettings.getStatusBarFont();
    CoordinateDisplay.lAbsPol = CoordinateDisplay.widget.findChild("AbsPol");
    CoordinateDisplay.lAbsPol.font = RSettings.getStatusBarFont();
    CoordinateDisplay.lRelPol = CoordinateDisplay.widget.findChild("RelPol");
    CoordinateDisplay.lRelPol.font = RSettings.getStatusBarFont();

    // screen readers: read the tool tip ("Absolute Cartesian Coordinate")
    // together with the coordinate (RAccessibleValueLabel):
    var labels = [CoordinateDisplay.lAbs, CoordinateDisplay.lRel, CoordinateDisplay.lAbsPol, CoordinateDisplay.lRelPol];
    for (var i=0; i<labels.length; i++) {
        labels[i].accessibleDescription = WidgetFactory.getPlainText(labels[i].toolTip);
    }

    var cartCoordSep;
    var polCoordSep;
    var relCoordPre;

    var adapter = new RCoordinateListenerAdapter();
    var appWin = EAction.getMainWindow();
    appWin.addCoordinateListener(adapter);

    adapter.coordinateUpdated.connect(CoordinateDisplay.update);
};

CoordinateDisplay.update = function(documentInterface) {
    if (!CoordinateDisplay.widget.enabled) {
        return;
    }

    if (isNull(documentInterface)) {
        // clear texts (no document open):
        CoordinateDisplay.lAbs.setText("");
        CoordinateDisplay.lAbsPol.setText("");
        CoordinateDisplay.lRel.setText("");
        CoordinateDisplay.lRelPol.setText("");
        return;
    }

    if (!isNull(CoordinateDisplay.singleShot)) {
        if (CoordinateDisplay.singleShot.active && !isNull(CoordinateDisplay.singleShot)) {
            // never mind previous update:
            CoordinateDisplay.singleShot.stop();
        }
        if (!isNull(CoordinateDisplay.singleShot)) {
            // catch exception when ran with script debugger:
            try {
                destr(CoordinateDisplay.singleShot);
                CoordinateDisplay.singleShot = undefined;
            }
            catch(e) {}
        }
    }

    // force immediate update every X mouse moves
    CoordinateDisplay.counter++;
    if (CoordinateDisplay.counter>=CoordinateDisplay.forcedUpdateInterval) {
        //CoordinateDisplay.singleShot.start(0);
        CoordinateDisplay.timedUpdate();
        CoordinateDisplay.counter = 0;
    }
    else {
        if (RSettings.getQtVersion()>=0x060000) {
            CoordinateDisplay.timedUpdate();
        }
        else {
            CoordinateDisplay.singleShot = new QTimer();
            CoordinateDisplay.singleShot.singleShot = true;
            CoordinateDisplay.singleShot.timeout.connect(CoordinateDisplay.timedUpdate);
            CoordinateDisplay.singleShot.start(20);
        }
    }
};

CoordinateDisplay.timedUpdate = function() {
    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return;
    }

    var doc = di.getDocument();
    if (isNull(doc)) {
        return;
    }

    StatusBar.clearMessage();
    var absPos = di.getCursorPosition();
    var relPos = absPos.operator_subtract(di.getRelativeZero());

    if (absPos.isValid()) {
        CoordinateDisplay.lAbs.setText(coordinateToString(absPos, 4, false, false, doc));
        CoordinateDisplay.lAbsPol.setText(coordinateToString(absPos, 4, false, true, doc));
    }
    else {
        CoordinateDisplay.lAbs.setText("-");
        CoordinateDisplay.lAbsPol.setText("-");
    }

    if (relPos.isValid()) {
        CoordinateDisplay.lRel.setText(coordinateToString(relPos, 4, true, false, doc));
        CoordinateDisplay.lRelPol.setText(coordinateToString(relPos, 4, true, true, doc));
    }
    else {
        CoordinateDisplay.lRel.setText("-");
        CoordinateDisplay.lRelPol.setText("-");
    }
};
