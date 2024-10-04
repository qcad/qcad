/**Beta 0.11
 * InfoAddCustomCentroid Beta version 0.11 (As MiscInformationCentroids)
 * Copyright (c) 2021 by CVH.
 * All rights reserved.
 *
 * This file is a free extension of the QCAD project.
 * Permission to evaluate, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * This script is donated to the QCAD project.
 * Copyright (c) 2011-2020 by Andrew Mustun. All rights reserved.
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

include("scripts/Misc/MiscInformation/InfoCentroids/InfoCentroids.js");

/**
 * \class InfoAddCustomCentroid
 * \ingroup ecma_misc_information_centroids
 * \brief This action creates a custom 2D Centroid marker from a dialog.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoAddCustomCentroid(guiAction) {
    InfoCentroids.call(this, guiAction);

    // Presets:
    this.massMode = true;
    this.point = undefined;
    this.positionX = undefined;
    this.positionY = undefined;
    this.mass = undefined;
};

// Initiating states: 
InfoAddCustomCentroid.State = {
    SettingPosition : 0
};

// Deriving our class from the base class:
InfoAddCustomCentroid.prototype = new InfoCentroids();
InfoAddCustomCentroid.includeBasePath = includeBasePath;

/**
 * This GUI action creates a point mass 2D Centroid marker customizable by dialog.
 */
// BeginEvent handler:
InfoAddCustomCentroid.prototype.beginEvent = function() {
    InfoCentroids.prototype.beginEvent.call(this);

    // Continue in first state:
    this.setState(InfoAddCustomCentroid.State.SettingPosition);
};

// States handler:
InfoAddCustomCentroid.prototype.setState = function(state) {
    InfoCentroids.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    this.setCommandPrompt(qsTr("Position"));
    this.setLeftMouseTip(qsTr("Specify position"));
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

// PickCoordinateEvent handler:
InfoAddCustomCentroid.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    // Store the click point:
    this.point = event.getModelPosition();

    // Diversify on preview:
    if (preview) {    // While hovering >
        this.updatePreview();
    } // End preview
    else {    // When a point is picked >
        this.setState(-1);

        // Show a dialog for user input:
        if (!this.showDialog()) {    // With the dialog canceled >
            // Pick point considered invalid:
            this.point = undefined;

            // Ruled out, would end the tool here:
            //    this.terminate();
            //    return;
        }
        else {    // With the dialog accepted >
            this.applyOperation();
            di.setRelativeZero(this.point);
        }
    } // End point picked

    // -> Continue in first state
};

// Preview/final operation handler:
InfoAddCustomCentroid.prototype.getOperation = function(preview) {
    var doc = this.getDocument();
    var op;
    var dataC;
    var markerSize;

    // Fail without a valid pick point:
    if (!isVector(this.point)) {
        return undefined;    // Failed, invalid point
    }

    // Initiate an operation:
    op = new RAddObjectsOperation();
    // Set tool title used for undo/redo information:
    op.setText(qsTr("2D point mass Centroid"));

    // Create a centroid data set:
    dataC = [this.point.x, this.point.y, this.point, this.mass];

    // Add a 2D Centroid marker with minimal size:
    markerSize = this.getMarkerSize()
    this.addCentroidMarker(doc, op, dataC, markerSize);

    // Return the operation:
    return op;
};

/**
 * Shows the associated 2D Centroid dialog for user input.
 * \author CVH © 2021
 *
 * \return True when accepted, false when rejected.
 */
InfoAddCustomCentroid.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(InfoAddCustomCentroid.includeBasePath, "AddCentroidDialog.ui");
    var widgets = getWidgets(dialog);
    var dialogPoint;

    // Load persistent dialog entries:
    //    On first use there is nothing to restore from >> UI defaults
    WidgetFactory.restoreState(dialog);

    // Preset PositionX/Y with click point data, use application decPnt & full precision:
    // Update the RMathLineEdit text.
    widgets["PositionX"].setText(this.formatPropValue(this.point.x));
    widgets["PositionY"].setText(this.formatPropValue(this.point.y));

    // Initiates a dialog reset button click function:
    widgets["Reset"].clicked.connect(
        function() {
            // Update the RMathLineEdit text:
            widgets["PointMass"].setText(qsTr("Undefined"));
        }
    );


    // Activate the AddCentroidDialog dialog:    Always modal on WinOS
        // dialog.exec() shows dialog, returns Accepted/Rejected
        if (!dialog.exec()) {    // When the dialog was rejected >
            destrDialog(dialog);
            EAction.activateMainWindow();
            return false;    // Dialog rejected
            } // End dialog rejected
    // -> Continue with the dialog accepted


//debugger;
    // Retrieve and store user input:
    this.positionX = widgets["PositionX"].getValue();    // RMathLineEdit
    this.positionY = widgets["PositionY"].getValue();    // RMathLineEdit
    this.mass = widgets["PointMass"].text;    // Plain text from a RMathLineEdit

    // Use dialog position when valid:
    dialogPoint = new RVector(this.positionX, this.positionY, 0.0);
    if (isValidVector(dialogPoint)) {
        this.point = dialogPoint;
    }

    // Save all dialog states persistent and finish:
    WidgetFactory.saveState(dialog);
    destrDialog(dialog);
    EAction.activateMainWindow();
    return true;
};

