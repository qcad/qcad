/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

CoordinateDisplay.postInit = function(basePath) {
    var widget = WidgetFactory.createWidget(basePath, "CoordinateDisplay.ui");
    StatusBar.addWidget(widget, 100, RSettings.getBoolValue("StatusBar/CoordinateDisplay", true));

    var lAbs = widget.findChild("Abs");
    lAbs.font = RSettings.getStatusBarFont();
    var lRel = widget.findChild("Rel");
    lRel.font = RSettings.getStatusBarFont();
    var lAbsPol = widget.findChild("AbsPol");
    lAbsPol.font = RSettings.getStatusBarFont();
    var lRelPol = widget.findChild("RelPol");
    lRelPol.font = RSettings.getStatusBarFont();

    var cartCoordSep;
    var polCoordSep;
    var relCoordPre;

    var adapter = new RCoordinateListenerAdapter();
    var appWin = EAction.getMainWindow();
    appWin.addCoordinateListener(adapter);

    var counter=0;
    var singleShot = undefined;

    adapter.coordinateUpdated.connect(function(documentInterface) {
        if (!widget.enabled) {
            return;
        }

        if (isNull(documentInterface)) {
            // clear texts (no document open):
            lAbs.setText("");
            lAbsPol.setText("");
            lRel.setText("");
            lRelPol.setText("");
            return;
        }


        if (!isNull(singleShot)) {
            if (singleShot.active) {
                singleShot.stop();
            }
        }

        singleShot = new QTimer();
        singleShot.singleShot = true;
        singleShot.timeout.connect(function() {
            StatusBar.clearMessage();
            var absPos = documentInterface.getCursorPosition();
            var relPos = absPos.operator_subtract(documentInterface.getRelativeZero());

            if (absPos.isValid()) {
                lAbs.setText(coordinateToString(absPos, 4, false, false));
                lAbsPol.setText(coordinateToString(absPos, 4, false, true));
            }
            else {
                lAbs.setText("-");
                lAbsPol.setText("-");
            }

            if (relPos.isValid()) {
                lRel.setText(coordinateToString(relPos, 4, true, false));
                lRelPol.setText(coordinateToString(relPos, 4, true, true));
            }
            else {
                lRel.setText("-");
                lRelPol.setText("-");
            }
        });

        // force immediate update every 10 mouse moves
        counter++;
        if (counter>=10) {
            singleShot.start(0);
            counter = 0;
        }
        else {
            singleShot.start(20);
        }
    });
};
