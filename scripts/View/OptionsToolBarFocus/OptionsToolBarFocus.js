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

include("../View.js");

function OptionsToolBarFocus(guiAction) {
    View.call(this, guiAction);
}

OptionsToolBarFocus.prototype = new View();

OptionsToolBarFocus.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var appWin = EAction.getMainWindow();
    var ot = EAction.getOptionsToolBar();
    var widgets = getWidgets(ot);
    for (var p in widgets) {
        var w = widgets[p];
        if (isOfType(w, QLineEdit) ||
            isOfType(w, RMathLineEdit) ||
            isOfType(w, QSpinBox) ||
            isOfType(w, QComboBox)) {

            w.setFocus(Qt.OtherFocusReason);
            break;
        }
    }

    this.terminate();
};

