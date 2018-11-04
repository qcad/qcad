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

CoordinateDisplay.postInit = function(basePath) {
    CoordinateDisplay.widget = WidgetFactory.createWidget(basePath, "CoordinateDisplay.ui");
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
        if (CoordinateDisplay.singleShot.active) {
            // never mind previous update:
            CoordinateDisplay.singleShot.stop();
        }
        if (!isNull(CoordinateDisplay.singleShot)) {
            // catch exception when ran with script debugger:
            try {
                CoordinateDisplay.singleShot.destroy();
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
        CoordinateDisplay.singleShot = new QTimer();
        CoordinateDisplay.singleShot.singleShot = true;
        CoordinateDisplay.singleShot.timeout.connect(CoordinateDisplay.timedUpdate);
        CoordinateDisplay.singleShot.start(20);
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
