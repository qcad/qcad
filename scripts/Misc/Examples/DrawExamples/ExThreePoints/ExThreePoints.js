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

//! [main]
//! [include]
include("scripts/EAction.js");
//! [include]

//! [constructor]
/**
 * \class ExThreePoints
 * \ingroup ecma_misc_examples_draw
 */
function ExThreePoints(guiAction) {
    EAction.call(this, guiAction);
}
//! [constructor]

//! [State]
ExThreePoints.State = {
    SettingPosition : 0
};
//! [State]

//! [inheritance]
ExThreePoints.prototype = new EAction();
//! [inheritance]

//! [setState]
ExThreePoints.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    // set crosshair cursor for choosing the coordinate:
    this.setCrosshairCursor();

    // we are interested in coordinates the user clicks 
    // (as opposed to entities):
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    // status bar user information:
    var appWin = RMainWindowQt.getMainWindow();
    var tr = qsTr("Position");
    this.setLeftMouseTip(tr);
    this.setCommandPrompt(tr);
    this.setRightMouseTip(EAction.trCancel);

    // show the snap toolbar, so the user can choose an alternative 
    // snap tool if desired:
    EAction.showSnapTools();
};
//! [setState]

//! [beginEvent]
ExThreePoints.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(ExThreePoints.State.SettingPosition);
};
//! [beginEvent]

//! [coordinateEvent]
ExThreePoints.prototype.coordinateEvent = function(event) {
    // the exact position that was clicked or 
    // entered by the user:
    var pos = event.getModelPosition();

    // move relative zero point to that position:
    this.getDocumentInterface().setRelativeZero(pos);

    // create an operation for adding objects:
    var op = new RAddObjectsOperation();
    for (var i=0; i<3; i++) {
        // create a point entity and add it to the operation:
        var point = new RPointEntity(
            this.getDocument(),
            new RPointData(new RVector(pos.x + i, pos.y))
        );
        op.addObject(point);
    }

    // apply the operation to the current drawing:
    this.getDocumentInterface().applyOperation(op);
};
//! [coordinateEvent]

//! [init]
ExThreePoints.init = function(basePath) {
    var action = new RGuiAction(qsTr("Three Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExThreePoints.js");
    //action.setIcon(basePath + "/ExThreePoints.svg");
    action.setStatusTip(qsTr("Draw three points"));
    action.setDefaultShortcut(new QKeySequence("p,3"));
    action.setDefaultCommands(["point3"]);
    action.setGroupSortOrder(73100);
    action.setSortOrder(400);
    action.setWidgetNames(["DrawExamplesMenu"]);
};
//! [init]
//! [main]
