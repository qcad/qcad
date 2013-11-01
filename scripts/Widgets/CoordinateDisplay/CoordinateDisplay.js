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
include("../../EAction.js");


function CoordinateDisplay() {
}

CoordinateDisplay.init = function(basePath) {
    var widget = WidgetFactory.createWidget(basePath, "CoordinateDisplay.ui");

    EAction.addToStatusBar(widget, 100);

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
    var statusBar = appWin.statusBar();

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
            statusBar.clearMessage();
            var absPos = documentInterface.getCursorPosition();
            var relPos = absPos.operator_subtract(documentInterface.getRelativeZero());

            lAbs.setText(coordinateToString(absPos, 4, false, false));
            lAbsPol.setText(coordinateToString(absPos, 4, false, true));

            if (relPos.isValid()) {
                lRel.setText(coordinateToString(relPos, 4, true, false));
                lRelPol.setText(coordinateToString(relPos, 4, true, true));
            }
            else {
                lRel.setText("-");
                lRelPol.setText("-");
            }
        });

        singleShot.start(counter++%10==0 ? 0 : 20);
    });
};
