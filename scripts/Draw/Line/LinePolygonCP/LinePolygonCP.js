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
 * \class LinePolygonCP
 * \brief Polygon with center, corner point and number of edges.
 * \ingroup ecma_draw_line
 */
function LinePolygonCP(guiAction) {
    Line.call(this, guiAction);

    this.center = undefined;
    this.corner = undefined;

    this.setUiOptions("LinePolygonCP.ui");
}

LinePolygonCP.prototype = new Line();

LinePolygonCP.State = {
    SettingCenter : 0,
    SettingCorner : 1
};

LinePolygonCP.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LinePolygonCP.State.SettingCenter);
};

LinePolygonCP.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LinePolygonCP.State.SettingCenter:
        var trCenter = qsTr("Center");
        this.setCommandPrompt(trCenter);
        this.setLeftMouseTip(trCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case LinePolygonCP.State.SettingCorner:
        var trCornerPoint = qsTr("Corner point");
        this.setCommandPrompt(trCornerPoint);
        this.setLeftMouseTip(trCornerPoint);
        this.setRightMouseTip(qsTr("Done"));
        break;
    }

    EAction.showSnapTools();
};

LinePolygonCP.prototype.escapeEvent = function() {
    switch (this.state) {
    case LinePolygonCP.State.SettingCenter:
        EAction.prototype.escapeEvent.call(this);
        break;

    case LinePolygonCP.State.SettingCorner:
        this.setState(LinePolygonCP.State.SettingCenter);
        break;
    }
};

LinePolygonCP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case LinePolygonCP.State.SettingCenter:
        if (!preview) {
            this.center = event.getModelPosition();
            di.setRelativeZero(this.center);
            //di.repaintViews();
            this.setState(LinePolygonCP.State.SettingCorner);
        }
        break;

    case LinePolygonCP.State.SettingCorner:
        this.corner = event.getModelPosition();
        if (preview) {
            this.updatePreview();
            //di.previewOperation();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.corner);
                this.setState(LinePolygonCP.State.SettingCenter);
            }
        }
        break;
    }
};

LinePolygonCP.prototype.getOperation = function(preview) {
    if (isNull(this.center) || isNull(this.corner)) {
        return undefined;
    }

    var c1;
    var c2 = this.corner;

    var op = new RAddObjectsOperation();
    for (var n=1; n<=this.numberOfCorners; ++n) {
        c1 = c2.copy();
        c2.rotate((Math.PI*2.0)/this.numberOfCorners, this.center);

        var line = new RLineEntity(
            this.getDocument(),
            new RLineData(c1, c2)
        );

        op.addObject(line);
    }

    return op;
};

LinePolygonCP.prototype.slotCornersChanged = function(value) {
    this.numberOfCorners = value;
    this.updatePreview(true);
};

