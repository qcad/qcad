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

include("scripts/Select/Select.js");

/**
 * \class SelectRectangle
 * \ingroup ecma_select
 * \brief Selects all entities inside a user specified rectangle.
 */
function SelectRectangle(guiAction) {
    Select.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;

    this.setUiOptions("SelectRectangle.ui");
}

SelectRectangle.prototype = new Select();

SelectRectangle.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1
};

SelectRectangle.prototype.selectEntities = function() {
    var di = EAction.getDocumentInterface();
    var doc = EAction.getDocument();
    var box = new RBox(this.point1, this.point2);
    var matchingEntities;
    if (this.crossSelection) {
        matchingEntities = doc.queryIntersectedEntitiesXY(box);
    }
    else {
        matchingEntities = doc.queryContainedEntitiesXY(box);
    }

    this.selectWithMode(matchingEntities);
};

SelectRectangle.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);

    this.setState(SelectRectangle.State.SettingPoint1);
};

SelectRectangle.prototype.setState = function(state) {
    Select.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case SelectRectangle.State.SettingPoint1:
        tr = qsTr("First corner");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        this.point1 = undefined;
        this.point2 = undefined;
        break;

    case SelectRectangle.State.SettingPoint2:
        tr = qsTr("Second corner");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

SelectRectangle.prototype.escapeEvent = function() {
    switch (this.state) {
    case SelectRectangle.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case SelectRectangle.State.SettingPoint2:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

SelectRectangle.prototype.coordinateEvent = function(event) {
    switch (this.state) {
    case SelectRectangle.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        this.setState(SelectRectangle.State.SettingPoint2);
        break;

    case SelectRectangle.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        this.selectEntities();
        this.getDocumentInterface().clearPreview();
        this.getDocumentInterface().repaintViews();
        this.setState(SelectRectangle.State.SettingPoint1);
        break;
    }
};

SelectRectangle.prototype.coordinateEventPreview = function(event) {
    switch (this.state) {
    case SelectRectangle.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        this.preview();
        break;
    default:
        break;
    }
};

SelectRectangle.prototype.preview = function() {
    if (this.state != SelectRectangle.State.SettingPoint2) {
        return;
    }

    Select.previewSelectionBox(
        this.getDocumentInterface(),
        new RBox(this.point1, this.point2),
        this.crossSelection
    );

    /*
    var points = new Array(
        this.point1,
        new RVector(this.point1.x, this.point2.y),
        this.point2,
        new RVector(this.point2.x, this.point1.y),
        this.point1
    );
    this.previewSelectionPolygon(points);
    */
};

