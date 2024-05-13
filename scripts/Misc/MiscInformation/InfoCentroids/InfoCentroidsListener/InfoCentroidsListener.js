/**Beta 0.12
 * InfoCentroidsListener Beta version 0.12 (As MiscInformationCentroids)
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
 * \class InfoCentroidsListener
 * \ingroup ecma_misc_information_centroids
 * \brief (De-)Activate a transaction listener for changes to 2D Centroid markers custom properties.
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function InfoCentroidsListener(guiAction) {
    InfoCentroids.call(this, guiAction);
};

// Deriving our class from the base class:
InfoCentroidsListener.prototype = new InfoCentroids();
InfoCentroidsListener.includeBasePath = includeBasePath;

/**
 * This GUI action (de)activates a 2D centroids transaction listener.
 * \author CVH © 2021
 */
// BeginEvent handler:
InfoCentroidsListener.prototype.beginEvent = function() {
   InfoCentroids.prototype.beginEvent.call(this);

//debugger;
    // Try to retrieve a stored adapter reference:
    var appWin = EAction.getMainWindow();
    var adapter = appWin.property("InfoCentroidsListenerAdapter");

    // Diversify between registering or removing a transaction adapter:
    if (isNull(adapter)) {    // Without an existing adapter ->
        this.register();
    }
    if (!isNull(adapter)) {    // With a known adapter ->
        this.remove();
    }

    // Button already toggles between usage, additionally also forced on/off

    // Terminate beginEvent:
    this.terminate();
    return;
};

/**
 * Install and activate a 2D centroids transaction listener.
 * Binds the properties 'Density' and 'Point mass'.
 * Binds 'PositionX/Y' and a new position by translation.
 * \author CVH © 2021
 */
// Based on ExTransactionListener.js
InfoCentroidsListener.prototype.register = function() {
    // Create a new transaction listener:
    var adapter = new RTransactionListenerAdapter();
    // Register transaction listener:
    var appWin = EAction.getMainWindow();
    appWin.addTransactionListener(adapter);
    // Preserve an adapter reference in an application property for deactivation:
    appWin.setProperty("InfoCentroidsListenerAdapter", adapter);

    // Connect transactionUpdated signal to a function that handles 2D Centroid markers custom property changes:
    adapter.transactionUpdated.connect(function(document, transaction) {
        var terms = InfoCentroids.Terms;
        var hasCustomChanges = false;

        // Avoiding invalid arguments and skip transactions that add/delete items:
        if (isNull(document) || isNull(transaction) || !transaction.hasOnlyChanges()) {
            return;
        }

        // Skip with no affected objects:
        var objIds = transaction.getAffectedObjects();
        if (objIds.length === 0) {
            return;
        }

//EAction.handleUserInfo("objectsLength: " + objIds.length);

        // Process all affected ID's:
        for (var i=0; i<objIds.length; i++) {
            var objId = objIds[i];
            var entity = document.queryEntity(objId);

            // Skip anything except polyline entities:
            if (!isPolylineEntity(entity)) {
                continue;
            }

            var type = entity.getCustomProperty("QCAD", terms.Title, undefined)

            // Skip anything except 2D Centroid markers entities:
            if (isNull(type)) {
                continue;
            }
            // Skip anything except 2D centroids:
            else if (type !== terms.PointMass &&
                     type !== terms.Area &&
                     type !== terms.Wire) {
                continue;
            }

            var changes = transaction.getPropertyChanges(objId);

//EAction.handleUserInfo("changesLength: " + changes.length);

            // Process all property changes:
            for (var k=0; k<changes.length; k++) {    // Cycle property changes
                var change = changes[k];
                var pid = change.getPropertyTypeId();

                // Catch position changes:
                if (pid.getId() === RPolylineEntity.PropertyVertexNX.getId() ||
                    pid.getId() === RPolylineEntity.PropertyVertexNY.getId()) {
                    // Handle position change:

//EAction.handleUserInfo("InfoCentroids.js: Position changed.");

                    InfoCentroidsListener.positionChanged(document, objId);
                    hasCustomChanges = true;
                    break;    // Stop cycling property changes
                }

                // Skip anything except custom properties:
                if (!pid.isCustom()) {
                    continue;    // Skip to next property change
                }

                var key = pid.getPropertyTitle();
                // Diversify on custom properties:
                // A: Density changed:
                if (key === terms.Density) {

//EAction.handleUserInfo("InfoCentroids.js: Density changed.");

                    InfoCentroidsListener.densityChanged(document, objId);
                    hasCustomChanges = true;
                }
                // B: Point mass changed:
                else if (key === terms.PointMass && type !== terms.PointMass) {

//EAction.handleUserInfo("InfoCentroids.js: Point mass changed.");

                    InfoCentroidsListener.pointMassChanged(document, objId);
                    hasCustomChanges = true;
                }
                // Else continue with next change
            } // Loop property changes
        } // Loop affected ID's

        // # Issue Fixed # Circular dependencies, impossible to update by an operation/transaction
        // # Workaround # Deselecting entities in question on any change:
        if (hasCustomChanges) {
            var di = EAction.getDocumentInterface();
            di.deselectAll();
        }
    }); // End Connect

    // Force button active, in normal conditions it toggles already:
    this.getGuiAction().setIcon(InfoCentroidsListener.includeBasePath + "/InfoCentroidsListenerActive.svg");
    this.getGuiAction().setChecked(true);
    // Report activation:
    EAction.handleUserInfo(qsTr("2D Centroids transaction listener active."));
};

/**
 * Deactivate (removes) an existing 2D centroids transaction listener.
 * \author CVH © 2021
 */
InfoCentroidsListener.prototype.remove = function() {
    // Retrieve active adapter:
    var appWin = EAction.getMainWindow();
    var adapter = appWin.property("InfoCentroidsListenerAdapter");
    // Remove listener:
    appWin.removeTransactionListener(adapter);
    // Clear adapter reference:
    appWin.setProperty("InfoCentroidsListenerAdapter", undefined);

    // Force button inactive, in normal conditions it toggles already:
    this.getGuiAction().setIcon(InfoCentroidsListener.includeBasePath + "/InfoCentroidsListenerInactive.svg");
    this.getGuiAction().setChecked(false);
    // Report deactivation:
    EAction.handleUserInfo(qsTr("Deactivated/removed the 2D Centroids transaction listener."));
};

/**
 * This function is called whenever a custom property '2D Centroid:Density' is changed.
 * Given that the centroids transaction listener is active.
 * Updates the custom property 'Point mass' in direct.
 * \author CVH © 2021
 */
InfoCentroidsListener.densityChanged = function(doc, id) {
    var terms = InfoCentroids.Terms;

    // Retrieve entity and custom properties:
    var entity = doc.queryEntityDirect(id);
    var weight = entity.getCustomProperty("QCAD", terms.Weighted, "0.0");
    var density = entity.getCustomProperty("QCAD", terms.Density, terms.Undefined);
//var oldMass = entity.getCustomProperty("QCAD", terms.PointMass, terms.Undefined);

    // Diversify on new value:
    if (density === terms.Undefined) {
        var newMass = density;    // Is also undefined
    }
    else {
        density = RMath.eval(density.replace(/\,/g, "."));
        if (isNull(density) || !isNumber(density)) {
            var newMass = qsTr("Syntax error: \'%1\' parse error").arg(terms.Density);
        }
        else {
            var newMass = parseFloat(weight.replace(/\,/g, ".")) * density;
            if (!isNumber(newMass)) {
                var newMass = qsTr("Syntax error: \'%1\' parse error").arg(terms.Weighted);
            }
            else {
                // Retrieve application decimal separator preference:
                var decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");    // Default =dot
                // Update defined density:
                var newMass = newMass.toPrecision(17).replace(".", decPnt);
            }
        }
    }

    // Adapt custom property:
    entity.setCustomProperty("QCAD", terms.PointMass, newMass);

//EAction.handleUserInfo("Old mass: " + oldMass);
//EAction.handleUserInfo("New mass: " + newMass);
};

/**
 * This function is called whenever a custom property '2D Centroid:Point mass' is changed.
 * Given that the centroids transaction listener is active.
 * Updates the custom property 'Density' in direct.
 * \author CVH © 2021
 */
InfoCentroidsListener.pointMassChanged = function(doc, id) {
    var terms = InfoCentroids.Terms;

    // Retrieve entity and custom properties:
    var entity = doc.queryEntityDirect(id);
    var weight = entity.getCustomProperty("QCAD", terms.Weighted, "0.0");
    var mass = entity.getCustomProperty("QCAD", terms.PointMass, terms.Undefined);
//var oldDensity = entity.getCustomProperty("QCAD", terms.Density, terms.Undefined);

    // Diversify on new value:
    if (mass === terms.Undefined) {
        var newDensity = mass;
    }
    else {
        mass = RMath.eval(mass.replace(/\,/g, "."));
        if (isNull(mass) || !isNumber(mass)) {
            var newDensity = qsTr("Syntax error: \'%1\' parse error").arg(terms.PointMass);
        }
        else {
            var newDensity = mass / parseFloat(weight.replace(/\,/g, "."));
            if (!isNumber(newDensity)) {
                var newDensity = qsTr("Syntax error: \'%1\' parse error").arg(terms.Weighted);
            } 
            else {
                // Retrieve application decimal separator preference:
                var decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");    // Default =dot
                // Update defined density:
                var newDensity = newDensity.toPrecision(17).replace(".", decPnt);
            }
        }
    }

    // Adapt custom property:
    entity.setCustomProperty("QCAD", terms.Density, newDensity);

//EAction.handleUserInfo("Old Density: " + oldDensity);
//EAction.handleUserInfo("New Density: " + newDensity);
};

/**
 * This function is called whenever a 2D Centroid marker is translated.
 * Given that the centroids transaction listener is active.
 * Updates the custom properties 'Position X/Y' in direct.
 * \author CVH © 2021
 */
InfoCentroidsListener.positionChanged = function(doc, id) {
    // Retrieve entity and middle point:
    var entity = doc.queryEntityDirect(id);
    var center = RVector.getAverage(entity.getStartPoint(), entity.getEndPoint());

    // Retrieve application decimal separator preference:
    var decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");    // Default =dot
    // Adapt custom properties:
    entity.setCustomProperty("QCAD", InfoCentroids.Terms.PositionX, center.getX().toPrecision(17).replace(".", decPnt));
    entity.setCustomProperty("QCAD", InfoCentroids.Terms.PositionY, center.getY().toPrecision(17).replace(".", decPnt));

//EAction.handleUserInfo("New Position: " + center);
};

