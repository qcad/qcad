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
 * \class SelectIntersectedEntities
 * \ingroup ecma_select
 * \brief Select entities intersected with line.
 */
function SelectIntersectedEntities(guiAction, select) {
    Select.call(this, guiAction);

    if (select == undefined) {
        select = true;
    }
    
    this.State = {
        SettingPoint1 : 0,
        SettingPoint2 : 1
    };
    this.point1 = undefined;
    this.point2 = undefined;
    this.select = select;

    this.setUiOptions("SelectIntersectedEntities.ui");
}

SelectIntersectedEntities.prototype = new Select();

SelectIntersectedEntities.prototype.selectEntities = function() {
    var match;
    
    var line = new RLine(this.point1, this.point2);

    var matchingEntities = [];

    // limit search to bounding box of line:
    var box = line.getBoundingBox();
    var entities = EAction.getDocument().queryIntersectedEntitiesXY(box);
    for (var e = 0; e < entities.length; ++e) {
        var entity = EAction.getDocument().queryEntity(entities[e]);
        match = false;

        // check if the entity intersects with any of the polygon edges:
        match = false;
        if (entity.intersectsWith(line)) {
            match = true;
        }

        if (match) {
            matchingEntities.push(entities[e]);
        }
    }

    this.selectWithMode(matchingEntities);
};

SelectIntersectedEntities.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);
    this.setState(this.State.SettingPoint1);
};

SelectIntersectedEntities.prototype.setState = function(state) {
    Select.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case this.State.SettingPoint1:
        tr = qsTr("First point");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case this.State.SettingPoint2:
        tr = qsTr("Second point");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

SelectIntersectedEntities.prototype.escapeEvent = function() {
    switch (this.state) {
    case this.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case this.State.SettingPoint2:
        this.setState(this.State.SettingPoint1);
        break;
    }
};

SelectIntersectedEntities.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case this.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        di.setRelativeZero(this.point1);
        this.setState(this.State.SettingPoint2);
        break;

    case this.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        this.selectEntities();
        di.setRelativeZero(this.point2);
        this.point1 = this.point2;
        this.setState(this.State.SettingPoint1);
        break;
    }
};

SelectIntersectedEntities.prototype.coordinateEventPreview = function(event) {
    switch (this.state) {
    case this.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        this.getDocumentInterface().addAuxShapeToPreview(
                new RLine(this.point1, this.point2));
        break;
    default:
        break;
    }
};

