/**
 * DrawFromCSV version 3.04
 * Copyright (c) 2021 of CVH.
 * All rights reserved.
 *
 * This file is a free extension of the QCAD project.
 * Permission to evaluate, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * This script and all related files are donated to the QCAD project.
 * Copyright (c) 2011-2021 by Andrew Mustun. All rights reserved.
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

include("scripts/Misc/MiscIO/MiscIO.js");
// Including File.js for a file dialog
include("scripts/File/File.js");

/**
 * \class DrawFromCSV
 * \brief This action draws entities declared in a CSV file and handles document layers.
 * Supports most basic QCAD shapes, 2 kinds of solids, text, attributes, custom properties ...
 * Allows different CSV styles, empty CSV lines, empty cells and commenting lines.
 * All details see: DrawCSV_doc.pdf
 * \ingroup ecma_misc_io
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor:
function DrawFromCSV(guiAction) {
    MiscIO.call(this, guiAction);
};

// Deriving our class from the base class:
DrawFromCSV.prototype = new MiscIO();
DrawFromCSV.includeBasePath = includeBasePath;

// BeginEvent handler:
DrawFromCSV.prototype.beginEvent = function() {
    MiscIO.prototype.beginEvent.call(this);

    // # Issue Fixed # Warnings/Info messages by dialog, many
    // Retrieve actual preferences for Warnings/Info messages if any:
    var oldWarningsAsDialog;
    if (RSettings.hasValue("CommandLine/WarningsAsDialog")) {
        oldWarningsAsDialog = RSettings.getBoolValue("CommandLine/WarningsAsDialog", false);
    }
    var oldInfoAsDialog;
    if (RSettings.hasValue("CommandLine/InfoAsDialog")) {
        oldInfoAsDialog = RSettings.getBoolValue("CommandLine/InfoAsDialog", false);
    }

    // Temporarily clear settings only when those existed and were set:
    if (oldWarningsAsDialog === true) RSettings.setValue("CommandLine/WarningsAsDialog", false);
    if (oldInfoAsDialog === true) RSettings.setValue("CommandLine/InfoAsDialog", false);

    // Call main script without file name:
    // The user can choose a file from a file dialog
    this.DrawFromCSVFile(this.getDocumentInterface(), undefined);

    // Restore former settings only when those existed and were set:
    if (oldWarningsAsDialog === true) RSettings.setValue("CommandLine/WarningsAsDialog", true);
    if (oldInfoAsDialog === true) RSettings.setValue("CommandLine/InfoAsDialog", true);

    // # Issue Fixed # Button toggles between usage, fixed with releasing
    this.getGuiAction().setChecked(false);

    // Terminate beginEvent:
    this.terminate();
    return;
};

/**
 * Process a CSV file by file name or by file name from a dialog.
 * \author  CVH © 2021
 *
 * \param di              Document interface.
 * \param (fileName)      Optional CSV file name.
 * 
 * \return A list with affected entities ID or undefined.
 */
DrawFromCSV.prototype.DrawFromCSVFile = function(di, fileName) {
    var decPnt;                                    // Decimal point
    var lstSep;                                    // List separator
    var msg;                                       // Intermediate message strings
    var file, flags, ts;                           // User selected file & related
    var op, transaction, ids;                      // Operation to collect additions & returned transaction & affected list
    var textLine, textLineCount;                   // A single line of text & counter
    var fields, fieldsCount;                       // The text line split in separate fields & counter
    var xtrField1, xtrField2                       // Additional fields
    var offsetRv;                                  // Current offset vector
    var polyRounding;                              // Rounding radius for polylines
    var layer;                                     // A layer object
    var layerOp;                                   // A layer operation
    var zoomToAll;                                 // Flag to zoom to all new after casting
    var selectAll;                                 // Flag to select all new after casting
    var newData;                                   // Newly created shape data
    var newEntity, newShape;                       // Newly created document entity/shape
    var anyError;                                  // Error message
    var refRv, refRv1, refRv2, refRv3, refRv4;     // Reference points RVectors
    var refs;                                      // Collection of references
    var radius;                                    // Radius value
    var angle1, angle2;                            // Angle values
    var bool;                                      // A boolean value
    var circle1, circle2, ips, chord               // Intersecting circles ArcTo
    var sizeX, sizeY;                              // X/Y size of square or rectangle
    var i;                                         // Common iterator
    var bulge;                                     // Bulge factor
    var txtHeight, txtWidth;                       // Text size attributes
    var txtVAlign, txtHAlign, txtDirection;        // Text align attributes
    var txtLSStyle, txtLineSpace;                  // Text Line space attributes
    var boldBool, italicBool, simpleBool;          // Text boolean values
    var attribText;                                // Entity textual custom attributes, unvalidated
    var customAttrib;                              // Entity custom attributes, default or validated
    var customProp;                                // Entity textual custom properties
    var keyValue;                                  // A Key:Value pair
    var castCount;                                 // Newly created document entities counter
    var graphicsView                               // View to zoom in

    this.di = di;
    this.doc = di.getDocument();

    // Without any, get a filename by dialog:
    if (isNull(fileName)) {    // Without a filename as parameter >
        fileName = this.getFileName();    // .getFileName as in BlockListExport.js
        // Validate return value:
        if (isNull(fileName)) {    // Without a filename >
            msg = qsTr("No import file selected.");
            EAction.handleUserWarning(msg);    // Push warning to history (Win)
            qDebug(msg);    // Push warning to stdout
            msg = qsTr("Command ended.");
            EAction.handleUserMessage(msg);    // Push message to history (Win)
            qDebug(msg);    // Push End to stdout
            return undefined;    // Failed, no filename
        } // End without a filename
    } // End without parameter
    // -> Continue with a fileName

    // Try to open the file to read from:
    file = new QFile(fileName);
    flags = makeQIODeviceOpenMode(QIODevice.ReadOnly, QIODevice.Text);
    if (!file.open(flags)) {    // Without a open file >
        msg = qsTr("No file opened.");
        EAction.handleUserWarning(msg);    // Push warning to history (Win)
        qDebug(msg);    // Push warning to stdout
        msg = qsTr("Command ended.");
        EAction.handleUserMessage(msg);    // Push message to history (Win)
        qDebug(msg);    // Push End to stdout
        return undefined;    // Failed, no open file
    } // End without open file
    // -> Continue with an open file

    // Additional Command History script notification:
    EAction.handleUserMessage(qsTr("DrawFromCSV script (v3.03) by CVH"));

    // Get QCAD native decimal point or a dot by default:
    decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");
    // This may alter at the point where a style is declared in the CSV.

    // Get QCAD native list separator or a comma by default:
    lstSep = RSettings.getStringValue("Input/CartesianCoordinateSeparator", ",");
    // This may alter at the point where a style is declared in the CSV.

    // Native list separator, persistent for user messages:
    this.nativeLstSep = lstSep;

    // Retrieve layer hierarchy separator, if any:
    this.layerSep = RLayer.getHierarchySeparator();    // Requires RLayer proxy
    // # Issue Fixed # Revert to 3 dots when not a string value (CE):
    // Approved by Andrew: PM Thu Nov 18, 2021 5:16 pm
    if (!isString(this.layerSep)) this.layerSep = " ... ";

    // Preset other initial values:
    this.currentLayerName = this.doc.getCurrentLayerName();    // Actual active layer name
    this.relativePos = new RVector(0.0, 0.0);                  // Reset relative position
    textLineCount = castCount = 0;                             // Reset counters
    offsetRv = new RVector(0.0, 0.0);                          // Reset offset vector
    polyRounding = 0.0;                                        // Reset rounding radius
    zoomToAll = selectAll = false                              // Reset zoom and select output flags

    // Initiate a TextStream:
    ts = new QTextStream(file);
    setUtf8Codec(ts);

    // Start a new transaction group:
    this.doc.startTransactionGroup();
    // Initiate an operation for adding entities:
    op = new RAddObjectsOperation();
    // Allow all transactions, layers can be hidden, frozen and or locked:
    op.setAllowAll(true); 
    // Set tool title used for undo/redo information:
    op.setText(qsTr("Cast CSV"));    // Translated tool title
    // Use global transaction group:
    op.setTransactionGroup(this.doc.getTransactionGroup());

    // Report reading from file:
    msg = qsTr("Reading from file: %1").arg(fileName);
    EAction.handleUserInfo(msg);    // Push info to history (Win)
    qDebug(msg);    // Push info to stdout

//debugger;
    // Stream input from file
    // - - - - - - - - - - - -
    // Process all definition lines:
    do {
        // Initial values every CSV text line:
        newEntity = "n/a";                    // No entity
        this.lastCoordinate = undefined;      // Empty = No last valid coordinate
        anyError = undefined;                 // Empty = No error
        xtrField1 = xtrField2 = undefined;    // Empty = None
        customAttrib = {                      // Default = Current layer & all byLayer & 1
            layer : this.currentLayerName,
            color : new RColor(RColor.ByLayer),
            lineweight : RLineweight.WeightByLayer,
            linetype : this.doc.getLinetypeId("BYLAYER"),
            LinetypeScale : 1.0};

        // Read a text line trimmed from leading and trailing whitespace:
        // # ToDo # Allow and strip trailing remark
        textLine = ts.readLine().trim();
        textLineCount++;

        // # Issue Fixed # For all CSV styles any tab is redundant.
        // # Issue # What about tab delimited files ... No example.
        // Remove any tab:
        textLine = textLine.replace(/\t+/,"");

        // # Issue Fixed # For all CSV styles any trailing comma or semicolon is redundant.
        // Remove any trailing list separator:
        textLine = textLine.replace(/[\;\,]+$/,"");

        // # Issue Fixed # For all CSV styles any double quotation marks is redundant.
        // Remove any double quotation marks:
        textLine = textLine.replace(/\"+/g,"");

        // Detect CSV style:
        if (textLine.toUpperCase().startsWith("CSV")) {    // With a CSV switch >
            // Process by short CSV style in uppercase:
            switch (textLine.slice(3).toUpperCase()) {
            case "COMMA/DOT":
                decPnt = ".";
                lstSep = ",";
                msg = qsTr("Switched to comma/dot CSV style.");
                break;
            case "SEMICOLON/DOT":
                decPnt = ".";
                lstSep = ";";
                msg = qsTr("Switched to semicolon/dot CSV style.");
                break;
            case "SEMICOLON/COMMA":
                decPnt = ",";
                lstSep = ";";
                msg = qsTr("Switched to semicolon/comma CSV style.");
                break;
            default:
                // Report unsupported CSV style switch:
                msg = qsTr("Unsupported or invalid CSV style, ignored. Text line: %1").arg(textLineCount);
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
                continue;    // Not valid, ignore line and skip
            } // End switch on short CSV style
            // -> Continue with a forced valid CSV style

            // Report CSV style switch:
            EAction.handleUserInfo(msg);    // Push info to history (Win)
            qDebug(msg);    // Push info to stdout

            // On a CSV style skip to next line:
            continue;
        } // End is CSV switch
        // -> Continue without a CSV switch

        // Detect comment line:
        if (textLine.startsWith(";")) {
            // On a comment line skip to next line
            continue;
        } // End is comment
        // -> Continue without a comment line

        // Detect empty line:
        if (textLine.length === 0) {    // When empty >
            // On an empty line skip to next line
            continue;
        } // End is empty
        // -> Continue without an empty line

        // Remove any empty field and all whitespace adjacent a list separator:
        if (lstSep === ";") {    // When using semicolon >
            textLine = textLine.replace(/\s*\;+\s*/g,";");
        } // End when semicolon
        else if (lstSep === ",") {    // When using comma >
            textLine = textLine.replace(/\s*\,+\s*/g,",");
        } // End when comma
        else {    // When using other >
            // Should not occur for now
        } // End when other
        // -> Continue without empty fields

        // Isolate extra fields:
        fields = textLine.split(lstSep + "\&\[");    // Reserved: ',&[' & ';&['
        if (fields.length === 3) {    // With two extra fields >
            // Store second extra field without closing bracket and trimmed:
            xtrField2 = fields[2].replace(/\]/g,"").trim();
        } // End with two extra
        if (fields.length > 1) {    // With any extra fields >
            // Store first extra field without closing bracket and trimmed:
            xtrField1 = fields[1].replace(/\]/g,"").trim();
        } // End with any extra
        textLine = fields[0];
        // -> Continue without optional entries

        // Adapt decimal point for semicolon style CSV:
        if (lstSep === ";") {    // when using semicolon >
            textLine = textLine.replace(/\,/g,".");
            if (!isNull(xtrField1)) xtrField1 = xtrField1.replace(/\,/g,".");
            if (!isNull(xtrField2)) xtrField2 = xtrField2.replace(/\,/g,".");
            // # Not an Issue # Husky used dot/semicolon
            // https://qcad.org/rsforum/viewtopic.php?t=8116
        } // End when semicolon
        // -> Continue with dots as decimal point

        // Split up definition line at list separators:
        fields = textLine.split(lstSep);
        fieldsCount = fields.length;

//debugger;
        // Process definition by nominator key in uppercase:
        switch (fields[0].toUpperCase()) {    // On nominator key in upper case
        case "NEWORIGIN":
            // Create new offset vector:
            refRv = this.getCoordinate(fields[1], fields[2]);
            // Set new offset vector if valid:
            if (!isNull(refRv)) {    // With a valid vector >
                offsetRv = refRv;
                // Reset relative position:
                this.relativePos = new RVector(0.0, 0.0);
            } // End valid
            else {    // Without a valid vector >
                msg = qsTr("Setting new relative origin failed, ignored. Text line: %1").arg(textLineCount);
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End NOT valid
            break;
        case "POLYROUND":
            // Set new polyline rounding radius:
            // Requires RPolyline proxy:
            if (RPolyline.hasProxy()) {    // With proxy >
                radius = parseFloat(fields[1]);
                //  Set new polyline rounding when valid:
                if (this.validateAsRadius(radius)) {    // With a valid radius >
                    polyRounding = radius;
                } // End valid
                else {    // Without a valid radius >
                    msg = qsTr("Setting new rounding radius failed, ignored. Text line: %1").arg(textLineCount);
                    EAction.handleUserWarning(msg);    // Push warning to history (Win)
                    qDebug(msg);    // Push warning to stdout
                } // End NOT valid
            } // End hasProxy
            else {    // Without proxy >
                msg = qsTr("Rounding polylines requires QCAD Professional, ignored. Text line: %1").arg(textLineCount);
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End without proxy
            break;
        case "LAYER":
            // Switch to an existing layer:
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, this.layerSep);
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    this.currentLayerName = fields[1];
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not switch to non-existing layers, ignored. Text line: %1%2 Layer: %3")
                                .arg(textLineCount).arg(this.nativeLstSep).arg("\'" + fields[1] + "\'");
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct set active \'Layer\' switch, ignored. Text line: %1").arg(textLineCount);
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "NEWLAYER":
            // Add a new or update an existing layer:
            msg = "";    // Empty
            if (fieldsCount === 7) {   // With 7 fields
                this.newOrUpdateLayer(fields, textLineCount);
            }
            else {    // With any but 7 fields >
                msg = qsTr("Not a correct \'New layer\' switch, ignored. Text line: %1").arg(textLineCount);
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End any
            break;
        case "HIDELAYER":
            // Hide an existing layer:
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, this.layerSep);
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    // Get the layer from the document:
                    layer = this.doc.queryLayer(fields[1]);
                    // Apply changes:
                    layer.setOff(true);
                    // Initiate an operation for updating a layer:
                    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
                    // Use global transaction group:
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not hide non-existing layers, ignored. Text line: %1%2 Layer: %3")
                                .arg(textLineCount).arg(this.nativeLstSep).arg("\'" + fields[1] + "\'");
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct \'HideLayer\' switch, ignored. Text line: %1").arg(textLineCount);
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "FREEZELAYER":
            // Freeze an existing layer:
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, this.layerSep);
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    // Get the layer from the document:
                    layer = this.doc.queryLayer(fields[1]);
                    // Apply changes:
                    layer.setFrozen(true);
                    // Initiate an operation for updating a layer:
                    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
                    // Use global transaction group:
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not freeze non-existing layers, ignored. Text line: %1%2 Layer: %3")
                                .arg(textLineCount).arg(this.nativeLstSep).arg("\'" + fields[1] + "\'");
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct \'FreezeLayer\' switch, ignored. Text line: %1").arg(textLineCount);
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "LOCKLAYER":
            // Lock an existing layer:
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, this.layerSep);
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    // Get the layer from the document:
                    layer = this.doc.queryLayer(fields[1]);
                    // Apply changes:
                    layer.setLocked(true);
                    // Initiate an operation for updating a layer:
                    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
                    // Use global transaction group:
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not lock non-existing layers, ignored. Text line: %1%2 Layer: %3")
                                .arg(textLineCount).arg(this.nativeLstSep).arg("\'" + fields[1] + "\'");
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct \'LockLayer\' switch, ignored. Text line: %1").arg(textLineCount);
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "ALLOWLAYER":
            // Show/Thaw/Unlock an existing layer:
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, this.layerSep);
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    // Get the layer from the document:
                    layer = this.doc.queryLayer(fields[1]);
                    // Apply changes:
                    layer.setOff(false);
                    layer.setFrozen(false);
                    layer.setLocked(false);
                    // Initiate an operation for updating a layer:
                    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
                    // Use global transaction group:
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not allow non-existing layers, ignored. Text line: %1%2 Layer: %3")
                                .arg(textLineCount).arg(this.nativeLstSep).arg("\'" + fields[1] + "\'");
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct \'AllowLayer\' switch, ignored. Text line: %1").arg(textLineCount);
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "ZOOMTOALL":
            // Set zoom to all flag:
            zoomToAll = true;
            break;
        case "SELECTALL":
            // Set select all flag:
            selectAll = true;
            break;
        case "POINT":
            // Create new Point entity:
            try {    // Try to create an entity >
                if (fieldsCount < 3) throw  qsTr("Low field count.");
                if (fieldsCount !== 3) throw qsTr("Odd field count.");
                refRv = this.getCoordinate(fields[1], fields[2]);    // Reference
                  if (isNull(refRv)) throw qsTr("Rv Invalid.");
                newData = new RPointData(refRv);
                newEntity = new RPointEntity(this.doc, newData);
                // Set single reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "LINE":
            // Create new Line entity:
            try {    // Try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Startpoint
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Set endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "LINETO":
            // Create new Line entity:
            try {    // Try to create an entity >
                if (fieldsCount < 3) throw  qsTr("Low field count.");
                if (fieldsCount !== 3) throw qsTr("Odd field count.");
                refRv1 = this.relativePos;    // Startpoint
                refRv2 = this.getCoordinate(fields[1], fields[2]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Set endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "VECTOR":
            // Create new Line entity:
            try {    // Try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Startpoint
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid.");
                angle1 = this.getAngleValue(fields[4], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid.");
                refRv = new RVector();
                refRv.setPolar(radius, angle1);
                refRv2 = refRv1.operator_add(refRv);    // Endpoint
                  if (!isValidVector(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Set endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "VECTORTO":
            // Create new Line entity:
            try {    // Try to create an entity >
                if (fieldsCount < 3) throw  qsTr("Low field count.");
                if (fieldsCount !== 3) throw qsTr("Odd field count.");
                refRv1 = this.relativePos;    // Startpoint
                radius = parseFloat(fields[1]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid.");
                angle1 = this.getAngleValue(fields[2], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid.");
                refRv = new RVector();
                refRv.setPolar(radius, angle1);
                refRv2 = this.relativePos.operator_add(refRv);    // Endpoint
                  if (!isValidVector(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Set endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RAY":
            // Create new Ray entity:
            try {    // Try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Base point
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Direction point
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                newShape = new RRay(refRv1, refRv2.operator_subtract(refRv1));
                newEntity = new RRayEntity(this.doc, new RRayData(newShape));
                // Set base point as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "XLINE":
            // Create new XLine entity:
            try {    // Try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Base point
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Direction point
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                newShape = new RXLine(refRv1, refRv2.operator_subtract(refRv1));
                newEntity = new RXLineEntity(this.doc, new RXLineData(newShape));
                // Set base point as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARC":
            // Create new Arc entity:
            try {    // Try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count.");
                if (fieldsCount !== 7) throw qsTr("Odd field count.");
                refRv = this.getCoordinate(fields[1], fields[2]);    // Center
                  if (isNull(refRv)) throw qsTr("Rv Invalid.");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid.");
                angle1 = this.getAngleValue(fields[4], false);
                  if (isNull(angle1)) throw qsTr("Angle1 Invalid.");
                angle2 = this.getAngleValue(fields[5], false);
                  if (isNull(angle2)) throw qsTr("Angle2 Invalid.");
                  if (RMath.fuzzyAngleCompare(angle1, angle2)) throw qsTr("Equal angles.");
                bool = fields[6].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape = new RArc(refRv, radius, angle1, angle2, bool);
                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Set endpoint as relative position:
                this.relativePos = newShape.getEndPoint();
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARC3P":
            // Create new Arc entity:
            try {    // Try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count.");
                if (fieldsCount !== 7) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Startpoint
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions 1-2.");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Endpoint
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 1-3.");
                  if (refRv2.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 2-3.");

                angle1 = refRv1.getAngleTo(refRv2);
                angle2 = refRv1.getAngleTo(refRv3);    // Assuming refRv1 is an endpoint
                  if (RMath.fuzzyAngleCompare(angle1, angle2)) throw qsTr("Near co-linear positions.");
                angle2 = refRv3.getAngleTo(refRv1);    // Assuming refRv1 is a fitpoint
                  if (RMath.fuzzyAngleCompare(angle1, angle2)) throw qsTr("Near co-linear positions.");
                newShape = RArc.createFrom3Points(refRv1, refRv2, refRv3);
                  if (!newShape.isValid()) throw qsTr("Arc Invalid.");
                  if (!this.validateAsRadius(newShape.getRadius())) throw qsTr("Radius Invalid.");

                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Set endpoint as relative position:
                this.relativePos = refRv3;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARCTO+A":
            // Create new Arc entity:
            try {    // Try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.relativePos;    // Startpoint
                refRv2 = this.getCoordinate(fields[1], fields[2]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                angle1 = this.getAngleValue(fields[3], true);
                  if (isNull(angle1)) throw qsTr("Angle Invalid.");
                bool = fields[4].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                // Bulge conversion:
                radius = refRv1.getDistanceTo2D(refRv2) / 2 / Math.sin(angle1 / 2);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid.");
                // Get center from intersecting circles:
                circle1 = new RCircle(refRv1, radius);
                circle2 = new RCircle(refRv2, radius);
                ips = circle1.getIntersectionPoints(circle2, false);
                chord = new RLine(refRv1, refRv2);
                if (ips.length === 2) {    // With 2 solutions >
                    // XNOR:    When true == true or false == false
                    if ((chord.getSideOfPoint(ips[0]) == RS.RightHand) == bool) {
                        refRv = ips[0];
                    }
                    else {
                        refRv = ips[1];
                    }
                }
                else if (ips.length === 1) {    // When center is in the middle >
                    refRv = chord.getMiddlePoint();
                }
                else {    // Without intersections >
                    // Should not occur
                    throw qsTr("Center Invalid.");
                }
                // With a center point:
                angle1 = refRv.getAngleTo(refRv1);
                angle2 = refRv.getAngleTo(refRv2);
                newShape = new RArc(refRv, radius, angle1, angle2, bool);
                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Set endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARCTO+R":
            // Create new Arc entity:
            try {    // Try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.relativePos;    // Startpoint
                refRv2 = this.getCoordinate(fields[1], fields[2]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid.");
                  if (2*radius < refRv1.getDistanceTo2D(refRv2)) throw qsTr("Radius too small.");
                bool = fields[4].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                // Get center from intersecting circles:
                circle1 = new RCircle(refRv1, radius);
                circle2 = new RCircle(refRv2, radius);
                ips = circle1.getIntersectionPoints(circle2, false);
                chord = new RLine(refRv1, refRv2);
                if (ips.length === 2) {    // With 2 solutions:
                    // XNOR:    true == true; false == false
                    if ((chord.getSideOfPoint(ips[0]) == RS.RightHand) == bool) {
                        refRv = ips[0];
                    }
                    else {
                        refRv = ips[1];
                    }
                }
                else if (ips.length === 1) {    // When the center is in the middle:
                    refRv = chord.getMiddlePoint();
                }
                else {    // Without intersections >
                    // Should not occur
                    throw qsTr("Center Invalid.");
                }
                // With a center point:
                angle1 = refRv.getAngleTo(refRv1);
                angle2 = refRv.getAngleTo(refRv2);
                newShape = new RArc(refRv, radius, angle1, angle2, bool);
                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Set endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CIRCLE":
            // Create new Circle entity:
            try {    // Try to create an entity >
                if (fieldsCount < 4) throw  qsTr("Low field count.");
                if (fieldsCount !== 4) throw qsTr("Odd field count.");
                refRv = this.getCoordinate(fields[1], fields[2]);    // Center
                  if (isNull(refRv)) throw qsTr("Rv Invalid.");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid.");
                newShape = new RCircle(refRv, radius);
                newEntity = new RCircleEntity(this.doc, new RCircleData(newShape));
                // Set center as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CIRCLE+P":
            // Create new Circle entity:
            try {    // Try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Center
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Fit point
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions.");
                radius = refRv1.getDistanceTo2D(refRv2);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid.");
                newShape = new RCircle(refRv1, radius);
                newEntity = new RCircleEntity(this.doc, new RCircleData(newShape));
                // Set fit point as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CIRCLE3P":
            // Create new Circle entity:
            try {    // Try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count.");
                if (fieldsCount !== 7) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions 1-2.");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 1-3.");
                  if (refRv2.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 2-3.");

                angle1 = refRv1.getAngleTo(refRv2);
                angle2 = refRv1.getAngleTo(refRv3);    // Assuming refRv1 is an endpoint
                  if (RMath.fuzzyAngleCompare(angle1, angle2)) throw qsTr("Near co-linear positions.");
                angle2 = refRv3.getAngleTo(refRv1);    // Assuming refRv1 is a fitpoint
                  if (RMath.fuzzyAngleCompare(angle1, angle2)) throw qsTr("Near co-linear positions.");
                newShape = RCircle.createFrom3Points(refRv1, refRv2, refRv3);
                  if (!newShape.isValid()) throw qsTr("Circle Invalid.");
                  if (!this.validateAsRadius(newShape.getRadius())) throw qsTr("Radius Invalid.");

                newEntity = new RCircleEntity(this.doc, new RCircleData(newShape));
                // Set third reference as relative position:
                this.relativePos = refRv3;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "TRIANGLE":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 7) throw  qsTr("Low field count.");
                if (fieldsCount !== 7) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions 1-2.");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 1-3.");
                  if (refRv2.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 2-3.");
                refs = new Array(refRv1, refRv2, refRv3);
                newShape = new RPolyline(refs, true);
                newShape = this.roundPolyline(newShape, polyRounding);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # General fix # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Set first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RSOLID3":
            // Create new Solid entity:
            try {    // Try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count.");
                if (fieldsCount !== 7) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions 1-2.");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 1-3.");
                  if (refRv2.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 2-3.");
                newData = new RSolidData(refRv1, refRv2, refRv3);
                newEntity = new RSolidEntity(this.doc, newData);
                // Set first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "QUAD":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 9) throw  qsTr("Low field count.");
                if (fieldsCount !== 9) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions 1-2.");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 1-3.");
                  if (refRv2.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 2-3.");
                refRv4 = this.getCoordinate(fields[7], fields[8]);    // Forth reference
                  if (isNull(refRv4)) throw qsTr("Rv4 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv4)) throw qsTr("Equal positions 1-4.");
                  if (refRv2.equalsFuzzy2D(refRv4)) throw qsTr("Equal positions 2-4.");
                  if (refRv3.equalsFuzzy2D(refRv4)) throw qsTr("Equal positions 3-4.");
                refs = new Array(refRv1, refRv2, refRv3, refRv4);
                newShape = new RPolyline(refs, true);
                newShape = this.roundPolyline(newShape, polyRounding);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # General fix # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Set first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RSOLID4":
            // Create new Solid entity:
            try {    // Try to create an entity >
                if (fieldsCount < 9) throw  qsTr("Low field count.");
                if (fieldsCount !== 9) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv2)) throw qsTr("Equal positions 1-2.");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 1-3.");
                  if (refRv2.equalsFuzzy2D(refRv3)) throw qsTr("Equal positions 2-3.");
                refRv4 = this.getCoordinate(fields[7], fields[8]);    // Forth reference
                  if (isNull(refRv4)) throw qsTr("Rv4 Invalid.");
                  if (refRv1.equalsFuzzy2D(refRv4)) throw qsTr("Equal positions 1-4.");
                  if (refRv2.equalsFuzzy2D(refRv4)) throw qsTr("Equal positions 2-4.");
                  if (refRv3.equalsFuzzy2D(refRv4)) throw qsTr("Equal positions 3-4.");
                newData = new RSolidData(refRv1, refRv2, refRv4, refRv3);
                newEntity = new RSolidEntity(this.doc, newData);
                // Set first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "SQUARE":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 5) throw  qsTr("Low field count.");
                if (fieldsCount !== 5) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Reference
                  if (isNull(refRv1)) throw qsTr("Rv Invalid.");
                sizeX = sizeY = parseFloat(fields[3]);
                  if (!isNumber(sizeX) || sizeX < RS.PointTolerance) throw qsTr("Size Invalid.");
                angle1 = this.getAngleValue(fields[4], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid.");
                refRv2 = new RVector(refRv1.x + sizeX, refRv1.y);
                  if (!isValidVector(refRv2)) throw qsTr("Rv2 Invalid.");
                refRv3 = new RVector(refRv1.x + sizeX, refRv1.y + sizeY);
                  if (!isValidVector(refRv3)) throw qsTr("Rv3 Invalid.");
                refRv4 = new RVector(refRv1.x, refRv1.y + sizeY);
                  if (!isValidVector(refRv4)) throw qsTr("Rv4 Invalid.");
                refs = new Array(refRv1, refRv2, refRv3, refRv4);
                newShape = new RPolyline(refs, true);
                newShape = this.roundPolyline(newShape, polyRounding);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # General fix # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Rotate the shape around refRv1:
                newEntity.rotate(angle1, refRv1);
                // Set first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RECTANGLE":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 6) throw  qsTr("Low field count.");
                if (fieldsCount !== 6) throw qsTr("Odd field count.");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid.");
                sizeX = parseFloat(fields[3]);
                  if (!isNumber(sizeX) || sizeX < RS.PointTolerance) throw qsTr("Size in X Invalid.");
                sizeY = parseFloat(fields[4]);
                  if (!isNumber(sizeY) || sizeY < RS.PointTolerance) throw qsTr("Size in Y Invalid.");
                angle1 = this.getAngleValue(fields[5], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid.");
                refRv2 = new RVector(refRv1.x + sizeX, refRv1.y);
                  if (!isValidVector(refRv2)) throw qsTr("Rv2 Invalid.");
                refRv3 = new RVector(refRv1.x + sizeX, refRv1.y + sizeY);
                  if (!isValidVector(refRv3)) throw qsTr("Rv3 Invalid.");
                refRv4 = new RVector(refRv1.x, refRv1.y + sizeY);
                  if (!isValidVector(refRv4)) throw qsTr("Rv4 Invalid.");
                refs = new Array(refRv1, refRv2, refRv3, refRv4);
                newShape = new RPolyline(refs, true);
                newShape = this.roundPolyline(newShape, polyRounding);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # General fix # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Rotate the shape around refRv1:
                newEntity.rotate(angle1, refRv1);
                // Set first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "POLYGON":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 11) throw qsTr("Polygon: less than 5 references.");
                if ((fieldsCount - 11)%2 !== 0) throw qsTr("Odd field count.");
                refs = [];    // Empty
                for (i=1; i<fieldsCount; i+=2) {    // Rv 1=1 3=2 5=3 Rv=(i+1)/2
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv%1 Invalid.").arg((i+1)/2);
                    refs.push(refRv);
                }
                newShape = new RPolyline(refs, true);
                newShape = this.roundPolyline(newShape, polyRounding);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # General fix # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Set first reference as relative position:
                this.relativePos = newShape.getStartPoint();
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "POLYLINE":
            // Create new Polyline entity:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 8) throw qsTr("Polyline, less than 2 references.");
                if ((fieldsCount - 8)%3 !== 0) throw qsTr("Odd field count.");
                newShape = new RPolyline();
                bool = fields[1].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape.setClosed(bool);
                for (i=2; i<fieldsCount; i+=3) {    // Rv 2=1 5=2 8=3 Rv=(i+1)/3
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv%1 Invalid.").arg((i+1)/3)
                    bulge = parseFloat(fields[i+2]);
                      if (!isNumber(bulge)) throw qsTr("Bulge%1 Invalid.").arg((i+1)/3);
                    newShape.appendVertex(refRv, bulge);
                }
                newShape = this.roundPolyline(newShape, polyRounding);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # General fix # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Set first/last reference as relative position:
                this.relativePos = (bool) ? newShape.getStartPoint() : refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "FITSPLINE":
            // Create new fit point Spline entity:
            try {    // Try to create an entity from a shape >
                if (!RSpline.hasProxy()) throw qsTr("Unsupported QCAD Professional feature.");
                if (fieldsCount < 8) throw qsTr("3th degree fit point Spline, less than 3 references.");
                if ((fieldsCount - 8)%2 !== 0) throw qsTr("Odd field count.");
                refs = [];    // Empty
                for (i=2; i<fieldsCount; i+=2) {    // Rv 2=1 4=2 6=3 Rv=i/2
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv%1 Invalid.").arg(i/2);
                    refs.push(refRv);
                }
                newShape = new RSpline();
                newShape.setDegree(3);    // Seems to be default
                newShape.setFitPoints(refs);
                bool = fields[1].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape.setPeriodic(bool);
                newEntity = new RSplineEntity(this.doc, new RSplineData(newShape));
                // Set last reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CONTROLSPLINE":
            // Create new control point Spline entity:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 10) throw qsTr("3th degree control point Spline, less than 4 references.");
                if ((fieldsCount - 10)%2 !== 0) throw qsTr("Odd field count.");
                newShape = new RSpline();
                newShape.setDegree(3);    // Seems to be default
                bool = fields[1].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape.setPeriodic(bool);
                for (i=2; i<fieldsCount; i+=2) {    // Rv 2=1 4=2 6=3 Rv=i/2
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv%1 Invalid.").arg(i/2);
                    newShape.appendControlPoint(refRv);
                }
                newEntity = new RSplineEntity(this.doc, new RSplineData(newShape));
                // Set last reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "TEXT":
        // create a text entity and add it to the operation:
            try {    // Try to create an entity from a shape >
                if (fieldsCount < 16) throw qsTr("Low field count.");
                if (fieldsCount !== 16) throw qsTr("Odd field count.");
                refRv = this.getCoordinate(fields[1], fields[2]);    // References
                  if (isNull(refRv)) throw qsTr("Rv Invalid.");
                txtHeight = parseFloat(fields[3]);
                  if (!isNumber(txtHeight) || txtHeight <= 0.0) throw qsTr("Height Invalid.");
                // # Issue Solved # Signature updated in 3.26.0, zero is 'none'
                txtWidth = parseFloat(fields[4]);
                  if (!isNumber(txtWidth) || txtWidth < 0.0) throw qsTr("Width Invalid.");
                txtVAlign = parseInt(fields[5]);
                  if (!isNumber(txtVAlign) || txtVAlign < 0 || txtVAlign > 3) throw qsTr("Vert. alignment Invalid.");
                txtHAlign = parseInt(fields[6]);
                  if (!isNumber(txtHAlign) || txtHAlign < 0 || txtHAlign > 5) throw qsTr("Horz. alignment Invalid.");
                txtDirection = parseInt(fields[7]);
                  if (!isNumber(txtDirection) || txtDirection < 0 || txtDirection > 2) throw qsTr("Drawing direction Invalid.");
                txtLSStyle = parseInt(fields[8]);
                  if (!isNumber(txtLSStyle) || txtLSStyle < 0 || txtLSStyle > 1) throw qsTr("Line spacing style Invalid.");
                txtLineSpace = parseInt(fields[9]);
                  if (!isNumber(txtLineSpace) || txtLineSpace <= 0.0) throw qsTr("Line spacing Invalid.");
                if (fields[10].toUpperCase() === "FILESTAMP") fields[10] = "File: " + fileName;
                if (fields[10].toUpperCase() === "DATESTAMP") fields[10] = "Date: " + new Date().toString();
                boldBool = fields[12].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                italicBool = fields[13].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                angle1 = this.getAngleValue(fields[14], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid.");
                simpleBool =  fields[15].toUpperCase() === "TRUE";    // Ignoring anything else to default to false

                newData = new RTextData(
                          refRv,                      // Position
                          refRv,                      // Alignment point
                          txtHeight,
                          txtWidth,                   // Text width since 3.26.0
                          txtVAlign,
                          txtHAlign,
                          txtDirection,
                          txtLSStyle,                 // Text line spacing style
                          txtLineSpace,               // Line spacing factor
                          fields[10],                 // The text message itself with/without formatting
                          fields[11],                 // Font
                          boldBool,
                          italicBool,
                          angle1,
                          simpleBool
                );
                newEntity = new RTextEntity(this.doc, newData);
                // Set single reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        default:
            // Method not listed among cases:
            msg = qsTr("Unsupported method. Text line: %1").arg(textLineCount);
            EAction.handleUserWarning(msg);    // Push warning to history (Win)
            qDebug(msg);    // Push warning to stdout
        } // End switch on nominator key

        // Reset attributes and custom properties:
        attribText = customProp = undefined;    // Empty

        // Diversify attributes and custom properties:
        if (isEntity(newEntity) && !isNull(xtrField1)) {
            xtrField1 = xtrField1.split(lstSep);
            if (xtrField1[0].toUpperCase() === "ATTRIB") {
                attribText = xtrField1;
            }
            else if (xtrField1[0].toUpperCase() === "CUSTOM") {
                customProp = xtrField1;
            }
            else {
                // Should not occur > reset entity
                anyError = qsTr("Error with first optional list.");
                newEntity = undefined;
            }
        }
        if (isEntity(newEntity) && !isNull(xtrField2)) {
            xtrField2 = xtrField2.split(lstSep);
            if (xtrField2[0].toUpperCase() === "ATTRIB" && isNull(attribText)) {
                attribText = xtrField2;
            }
            else if (xtrField2[0].toUpperCase() === "CUSTOM" && isNull(customProp)) {
                customProp = xtrField2;
            }
            else {
                // Should not occur > reset entity
                anyError = qsTr("Error with second optional list.");
                newEntity = undefined;
            }
        }

        // Validate layer attributes if any:
        if (!isNull(attribText)) {
            // Overwrite customAttrib with 5 verified attributes:
            customAttrib = this.validateAttributes(attribText, textLineCount);
        }

        // Finalize new drawing entity and add to operation:
        if (isEntity(newEntity)) {    // With a valid shape >
            // Apply general properties:
            newEntity.setLayerName(customAttrib.layer);
            newEntity.setColor(customAttrib.color);
            newEntity.setLineweight(customAttrib.lineweight);
            newEntity.setLinetypeId(customAttrib.linetype);
            newEntity.setLinetypeScale(customAttrib.LinetypeScale);

            // Apply general offset:
            newEntity.move(offsetRv);

            // Apply custom properties from key/value pairs:
            // customProp[0] matches 'CUSTOM', customProp are key/value pairs
            if (!isNull(customProp) && customProp.length > 1) {    // With any custom
                for (i=1; i<customProp.length; i++) {    // Cycle all custom props
                    keyValue = customProp[i].split(":");
                    if (keyValue.length !== 2) keyValue[1] = "";
                    if (!keyValue[0].trim().isEmpty()) {    // With a key
                        newEntity.setCustomProperty("QCAD", keyValue[0].trim(), keyValue[1].trim());
                    } // End with key
                } // Loop custom props
            } // End with any custom

            // Add to the operation:
            op.addObject(newEntity, false, false);    // NOTuseCurrentAttributes, NOTforceNew (all are new)
            castCount++;
        } // End with shape
        else if (newEntity !== "n/a") {    // Without a valid shape
            // # Issue Fixed # Locally thrown errors are strings, internal errors are objects.
            anyError = (isString(anyError)) ? anyError : anyError.message;
            // All locally thrown errors are translated message
            msg = qsTr("Not a correct entry, ignored. Text line: %1 > %2").arg(textLineCount).arg(anyError);
            EAction.handleUserWarning(msg);    // Push warning to history (Win)
            qDebug(msg);    // Push warning to stdout
        } // End without shape

    } while(!ts.atEnd());    // Loop when the text stream is not ended

//debugger;
    // Synchronize RelativeZero:
    di.setRelativeZero(this.relativePos.operator_add(offsetRv));

    // Synchronize document current layer:
/*
    this.doc.setCurrentLayer(this.currentLayerName);
//  Or
    di.setCurrentLayer(this.currentLayerName);
*/
    // # Issue # .setCurrentLayer is an extra action
    // Also encountered with AddLayer.js: adding is 1 action, to undo requires 2 actions
    // https://www.qcad.org/rsforum/viewtopic.php?t=8287

    // Based on: ActivateLayerState class 'restore current layer'
//    Initiate an operation for setting current layer:
//    layerOp = new RAddObjectOperation();
//    layerOp.setText(qsTr("Cast CSV"));    // Translated tool title
//    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
    // Update the document variables:
    var docVars = this.doc.queryDocumentVariables();
    docVars.setCurrentLayerId(this.doc.getLayerId(this.currentLayerName));
//    layerOp.addObject(docVars);
    op.addObject(docVars);
//    di.applyOperation(layerOp);
    // # Issue # Functional but change doesn't show in Layer List Widget
    //           Change is visible after drawing tab swap, new document or after undo + redo
    // # ToDo # HowTo set current layer without extra operation?
//    di.regenerateScenes();
//    di.repaintViews();
//    di.clearPreview();
/*
    // Based on: LayerList.js    Fails
    // 'this.blockSignals' [undefined] is not a function.
    this.blockSignals(true);
    di.setCurrentLayer(this.currentLayerName);
    this.blockSignals(false);
*/
/*
    // Based on: LayerList.js    Fails
    // ReferenceError: Can't find variable: RLayerListQt
    RLayerListQt.blockSignals(true);
    di.setCurrentLayer(this.currentLayerName);
    RLayerListQt.blockSignals(false);
*/

    // Apply all entity operations in one go:
    transaction = di.applyOperation(op);    // No fault without any

    // Retrieve the affected entities:
    ids = transaction.getAffectedObjects();

    // Apply optional selection with any entities:
    if (selectAll) {    // When the select all flag is set >
        if (ids.length > 0) {    // With new entities >
            di.selectEntities(ids, false);    // NOTaddToCurrent
        } // End with new
    } // End with flag

    // Apply optional zoom with any entities:
    if (zoomToAll) {    // When the zoom all flag is set >
        if (ids.length > 0) {    // With new entities >
            graphicsView = di.getGraphicsViewWithFocus();
            // Simple.js ... di.getLastKnownViewWithFocus();
            if (!isNull(graphicsView)) {
                getRGraphicsView(graphicsView).zoomToEntities(ids, 30);    // Margin in pixels
            }
        } // End with new
    } // End with flag

    // Report actions and terminate command:
    file.close();
    if (castCount > 0) {
        msg = qsTr("Casted entries: %1 out of %2 text lines").arg(castCount).arg(textLineCount);
        EAction.handleUserInfo(msg);    // Push message to history (Win)
        msg = qsTr("Importing CSV complete. Command ended.");
    }
    if (castCount === 0) {
        msg = qsTr("Nothing casted.");
        EAction.handleUserWarning(msg);    // Push warning to history (Win)
        msg = qsTr("Command ended.");
    }
    EAction.handleUserMessage(msg);    // Push message to history (Win)
    qDebug(msg);    // Push End to stdout

    // Return the affected entities if any:
    return (ids.length > 0) ? ids : undefined;
};

/**
 * Returns a file name and path from a file Dialog.
 * Adapted copy from BlockListExport.js; BlockListExport.prototype.getFileName = function().
 * \author Andrew Mustun
 *
 * \return Full path to the selected file or 'undefined' when none.
 */
DrawFromCSV.prototype.getFileName = function() {
    // # Known issues # Persistent behavior. Empty files with suffix(-es).
    // # ToDo # Enhance .getFileName
    // Requires: this.doc        Current document.
    var drawingFileName = this.doc.getFileName();
    var fi;
    var fileName;
    var initialPath = "";

    // # Issue # General idea should be:
    // With a drawing name the name.csv in the last folder or homeDir
    // Without a drawing name the last file or the windowTitle in the last folder or homeDir
    if (drawingFileName.length === 0) {
        var path = RSettings.getStringValue("DrawFromCSV/Path", QDir.homePath());
        fi = new QFileInfo(path);
        initialPath = fi.absoluteFilePath() + QDir.separator +
                      stripDirtyFlag(EAction.getMdiChild().windowTitle) + ".csv";
    }
    else {
        fi = new QFileInfo(drawingFileName);
        initialPath = fi.path() + QDir.separator + fi.completeBaseName() + ".csv";
    }

    var appWin = EAction.getMainWindow();
    var ret = File.getOpenFileName(appWin,
                                    qsTr("Draw from CSV"),
                                    initialPath,
                                    [qsTr("CSV") + " (*.csv)", qsTr("All Files") + " (*)" ],
                                    true);    // Not prefixing 'All files'
    if (isNull(ret)) {
        return undefined;    // Failed, no filename
    }
    fileName = ret[0];

    if (fileName === "") {
        return undefined;    // Failed, empty filename
    }

    if (drawingFileName.length === 0) {
        RSettings.setValue("DrawFromCSV/Path", new QFileInfo(fileName).absolutePath());
    }

    return fileName;
};

/**
 * Gets the absolute 2D coordinate vector from a textual coordinate pair.
 * Relative when xField starts with '@'.
 * Relative/polar when relative and yField starts with '<'
 * Validates both entries as numbers or polar notations as radius/angle.
 * \author  CVH © 2021
 *
 * \param xField        First textual coordinate.
 * \param yField        Second textual coordinate.
 * 
 * \return The resulting RVector or 'undefined' when failed.
 */
DrawFromCSV.prototype.getCoordinate = function(xField, yField) {
    // # Bug Fixed # Last validated reference may serve as relative position before something valid was cast.
    //               Were two different things before and opted for the bad. Reverted back.
    // Requires: this.relativePos       Last known relative position
    //           this.lastCoordinate    Last valid coordinate
    var xValue, yValue;                 // Absolute X/Y coordinates
    var newRv;                          // Intermediate new vector
    var ret;                            // Return value

    // Fail without both textual coordinates
    if (isNull(xField) || isNull(yField)) return undefined;

    // Calculate absolute return vector:
    if (xField.startsWith("@")) {    // When relative >
        // Fail when relative position is invalid:
        if (!isValidVector(this.relativePos)) return undefined;

        // Revert to relative position when last valid coordinate is empty:
        if (isNull(this.lastCoordinate)) this.lastCoordinate = this.relativePos

        // Fail when xValue is no number:
        xValue = parseFloat(xField.slice(1));
        if (!isNumber(xValue)) return undefined;

        // Check for polar:
        if (yField.startsWith("<")) {    // When relative/polar
            // Fail when xValue doesn't validate as a radius:
            if (!this.validateAsRadius(xValue)) return undefined;

            // Fail when yValue doesn't validate to a number:
            yValue = this.getAngleValue(yField.slice(1), false);
            if (isNull(yValue)) return undefined;

            // Set relative/polar vector
            newRv = new RVector();
            newRv.setPolar(xValue, yValue);
        } // End polar
        else {    // When NOT polar >
            // Fail when yValue is no number:
            yValue = parseFloat(yField);
            if (!isNumber(yValue)) return undefined;

            // Set relative vector
            newRv = new RVector(xValue, yValue);
        } // End NOT polar
        // -> Continue with a newRv

        // Fail when new vector is invalid:
        if (!isValidVector(newRv)) return undefined;

        // Use relative vector:
        ret = this.lastCoordinate.operator_add(newRv);
    } // End relative
    else {    // When absolute
        // Fail when one of the values is not a number:
        xValue = parseFloat(xField);
        yValue = parseFloat(yField);
        if (!isNumber(xValue) || !isNumber(yValue)) return undefined;

        // Use absolute vector:
        ret = new RVector(xValue, yValue);
    } // End absolute
    // -> Continue with a return vector

    // Return 'undefined' when invalid:
    if (!isValidVector(ret)) return udefined;

    // Remember last valid coordinate and return an RVector:
    this.lastCoordinate = ret;
    return ret;
}

/**
 * Validates a value as a radius within limits.
 * Returns 'true' when valid else 'false'.
 */
DrawFromCSV.prototype.validateAsRadius = function(value) {
    // Fail when not a number:
    if (!isNumber(value)) return false;

    // Restrict between +RS.PointTolerance (zero leads to Null-entities)
    //    and +1.0e6 (Conform QCAD Arc methods getCircles2TR/getArc2PR/getCircle2PR):
    return !(value < RS.PointTolerance || value > 1.0e6);
 };

/**
 * Gets an angle in radians from a textual value in degrees or radians.
 * Validates entry as angle or as sweep.
 * \author  CVH © 2021
 *
 * \param angleStr        A textual angle notation.
 * \param isSweep         True to validate as sweep angle.
 * 
 * \return The normalized angle in radians or 'undefined' when failed.
 */
DrawFromCSV.prototype.getAngleValue = function(angleStr, isSweep) {
    var ret;          // Return value
    var isRadians;    // Condition

    // Fail without a angle string:
    if (isNull(angleStr) || angleStr.length === 0) return undefined;

    // Fail when not a number:
    ret = parseFloat(angleStr);
    if (!isNumber(ret)) return undefined;

    // Use as radians or as degrees:
    isRadians = angleStr.toUpperCase().endsWith("R") || angleStr.toUpperCase().endsWith("RAD");
    if (!isRadians) {
        ret = RMath.deg2rad(ret);
    }

    // Optionally fail when outside +2Pi and -2Pi excluding the limits:
    if (isSweep) {
        if (ret >= Math.PI*2-RS.AngleTolerance) return undefined;
        if (ret <= -Math.PI*2+RS.AngleTolerance) return undefined;
    }

    // Return the normalized angle:
    return RMath.getNormalizedAngle(ret);
 };

/**
 * Validates a set of general properties from an attributes set.
 * \author  CVH © 2021
 *
 * \param fields          Attribute set.
 * \param textLine        CSV text line number.
 * 
 * \return Validated attributes set.
 */
DrawFromCSV.prototype.validateAttributes = function(fields, textLine) {
    // fields[0] matches 'ATTRIB', fields count >1, fields are key/value pairs
    // Requires: this.doc                  Current document
    //           this.currentLayerName     Script level current layer
    //           this.nativeLstSep         Native list separator for messages
    //           this.layerSep             Layer hierarchy separator
    var i, pairs;                          // Pair iterator and limit
    var keyValue;                          // Key/value pair a array
    var anyError = "";                     // Error message
    var layerName, color, weight, type;    // Attributes
    var ret = {                            // Default set = Current layer, byLayer & scale 1
        layer : this.currentLayerName,
        color : new RColor(RColor.ByLayer),
        lineweight : RLineweight.WeightByLayer,
        linetype : this.doc.getLinetypeId("BYLAYER"),
        LinetypeScale : 1};

    // Define pairs count:
    pairs = fields.length - 1;
    // Report none:
    if (pairs < 1) {
        anyError = qsTr("Attributes empty. Text line: %1").arg(textLine);
    }
    // Limit to 5 pairs, ignoring any extra field silently:
    if (pairs > 5) pairs = 5;
    // Add 1 for counter limit:
    pairs++;

//debugger;
    for (i=1; i<pairs; i++) {    // Cycle through up to 5 attributes pairs
        // Split the key/value pair:
        keyValue = fields[i].split(":");

        // Reset keyValue when not a pair:
        if (keyValue.length !== 2) keyValue = ["Dummy", "void"];

        // Process by key in uppercase:
        switch (keyValue[0].toUpperCase()) {
        case "LAYER":
            // Adapt layer naming to proper layer hierarchy separator:
            keyValue[1] = keyValue[1].replace(/\//g, this.layerSep);

            // Validate layer naming:
            layerName = this.validateLayerString(keyValue[1]);
            if (isNull(layerName)) {
                anyError = qsTr("Not a correct layer name, ignored. Text line: %1%2 Name: %3")
                                .arg(textLine).arg(this.nativeLstSep).arg("\'" + keyValue[1] + "\'");
            }
            // Check if the layer exist:
            if (this.doc.hasLayer(layerName)) {
                ret.layer = layerName;
            }
            else {
                anyError = qsTr("Layer doesn't exist, ignored. Text line: %1%2 Layer: %3")
                                .arg(textLine).arg(this.nativeLstSep).arg("\'" + keyValue[1] + "\'");
            }
            break;
        case "COLOR":
            // Validate Color attribute from string:
            color = this.validateColorString(keyValue[1], true);
            if (isNull(color)) {
                anyError = qsTr("Not a correct color, ignored. Text line: %1%2 Color: %3")
                                .arg(textLine).arg(this.nativeLstSep).arg("\'" + keyValue[1] + "\'");
            }
            else {
                ret.color = color;
            }
            break;
        case "LINEWEIGHT":
            // Validate Lineweight attribute from string:
            weight = this.validateWeightString(keyValue[1], true);
            if (isNull(weight)) {
                anyError = qsTr("Not a correct Lineweight, ignored. Text line: %1%2 Weight: %3")
                                .arg(textLine).arg(this.nativeLstSep).arg("\'" + keyValue[1] + "\'");
            }
            else {
                ret.lineweight = weight;
            }
            break;
        case "LINETYPE":
            // Validate Linetype attribute from string:
            type = this.validateTypeString(keyValue[1], true);
            if (isNull(type)) {
                anyError = qsTr("Not a correct Linetype, ignored. Text line: %1%2 Type: %3")
                                .arg(textLine).arg(this.nativeLstSep).arg("\'" + keyValue[1] + "\'");
            }
            else {
                ret.linetype = type;
            }
            break;
        case "LINETYPESCALE":
            // Validate LinetypeScale attribute from string:
            if (!isNumber(parseFloat(keyValue[1])) || parseFloat(keyValue[1]) < 0) {
                anyError = qsTr("Not a correct Linetype scale, ignored. Text line: %1%2 Scale: %3")
                                .arg(textLine).arg(this.nativeLstSep).arg("\'" + keyValue[1] + "\'");
            }
            else {
                ret.LinetypeScale = parseFloat(keyValue[1]);
            }
            break;
        default:
            // None of the above:
            anyError = qsTr("Unsupported attribute, ignored. Text line: %1 > %2").arg(textLine).arg(fields[i]);
        } // End switch on key
    } // Loop attributes pairs

    // Report any error:
    if (anyError.length > 0) {    // With an error message >
        EAction.handleUserWarning(anyError);    // Push warning to history (Win)
        qDebug(anyError);    // Push warning to stdout
    } // End message

    // Return attribute set:
    return ret;
};

/**
 * Validates a set of layer attributes from a layer switch.
 * Updates an exiting layer or creates a new layer if such doesn't exist.
 * New sublayers require an existing parent.
 * \author  CVH © 2021
 *
 * \param fields          Attribute set.
 * \param textLine        CSV text line number.
 * 
 * \return Nothing. Applies a layer operation, reports errors.
 *                  Updates script level current layer.
 */
DrawFromCSV.prototype.newOrUpdateLayer = function(fields, textLine) {
    // fields[0] matches 'NEWLAYER', fields count =7
    // Requires: this.di                               Document interface
    //           this.doc                              Current document
    //           this.currentLayerName                 Script level current layer
    //           this.nativeLstSep                     Native list separator for messages
    //           this.layerSep                         Layer hierarchy separator
    var anyError = "";                                 // Error message
    var layerName, color, weight, type, plot, snap;    // Layer attributes
    var parentLayer;                                   // Parent layer name
    var layer;                                         // A layer object
    var layerOp;                                       // Layer operation
    var defaultColor, defaultType, defaultWeight;      // Default attributes
    var msg = "";                                      // Intermediate message strings

//debugger;
    // Adapt layer naming to proper layer hierarchy separator:
    fields[1] = fields[1].replace(/\//g, this.layerSep);

    // Validate layer naming:
    layerName = this.validateLayerString(fields[1]);
    if (isNull(layerName)) {    // Without a valid layer name >
        anyError = qsTr("Not a correct layer name. Text line: %1%2 Name: %3")
                        .arg(textLine).arg(this.nativeLstSep).arg("\'" + fields[1] + "\'");
    } // End without name
    else {    // With a valid layer name >
        if (layerName.indexOf(this.layerSep) !== -1) {    // With a parent/sub layer >
            parentLayer = layerName.split(this.layerSep, layerName.count(this.layerSep)).join(this.layerSep);
            if (!this.doc.hasLayer(parentLayer)) {    // Without a parent layer >
                anyError = qsTr("Parent layer doesn't exist. Text line: %1%2 Layer: %3")
                                .arg(textLine).arg(this.nativeLstSep).arg("\'" + parentLayer + "\'");
            } // End without parent
        } //End with sub
        // -> Continue with a verified name

        // With a name, retrieve the layer or create a new one:
        if (this.doc.hasLayer(layerName)) {    // With an existing layer >
            layer = this.doc.queryLayer(layerName);
        } // End with existing
        else {   // Without an existing layer >
            // Get the application preferences or use defaults:
            defaultColor = RSettings.getColor("Layer/DefaultColor", new RColor("black"));
            defaultType = this.doc.getLinetypeId("CONTINUOUS");
            defaultWeight = RSettings.getIntValue("Layer/DefaultLineweight", RLineweight.Weight025);
            // Create new layer object:
            layer = new RLayer(this.doc, layerName, false , false,    // NOTfrozen, NOTlocked
                                    defaultColor,
                                    defaultType,
                                    defaultWeight,
                                    false);    // NOToff
        } // End with new
        // -> Continue with a layer object
    } // End with a valid layer name
    // -> Continue with/without a layer object

    // Validate attributes:
    if (!isNull(layer)) {    // With a layer object >
        // Validate Color from a string:
        color = this.validateColorString(fields[2], false);
        if (isNull(color)) {
            anyError = qsTr("Not a correct color. Text line: %1%2 Color: %3")
                            .arg(textLine).arg(this.nativeLstSep).arg("\'" + fields[2] + "\'");
        }
        else {
            layer.setColor(color);
        }

        // Validate Lineweight from a string:
        weight = this.validateWeightString(fields[3], false);
        if (isNull(weight)) {
            anyError = qsTr("Not a correct Lineweight. Text line: %1%2 Weight: %3")
                            .arg(textLine).arg(this.nativeLstSep).arg("\'" + fields[3] + "\'");
        }
        else {
            layer.setLineweight(weight);
        }

        // Validate Linetype from a string:
        type = this.validateTypeString(fields[4], false);
        if (isNull(type)) {
            anyError = qsTr("Not a correct Linetype. Text line: %1%2 Type: %3")
                            .arg(textLine).arg(this.nativeLstSep).arg("\'" + fields[4] + "\'");
        }
        else {
            layer.setLinetypeId(type);
        }

        // Set Plottable & Snappable:
        plot = !(fields[5].toUpperCase() === "FALSE");    // Ignoring anything else, default to true
        layer.setPlottable(plot);
        snap = !(fields[6].toUpperCase() === "FALSE");    // Ignoring anything else, default to true
        layer.setSnappable(snap);
    } // End with a layer object

    // Report any error:
    if (anyError.length > 0) {    // With an error message >
        EAction.handleUserWarning(anyError);    // Push warning to history (Win)
        qDebug(anyError);    // Push warning to stdout
        msg = qsTr("Add/Update layer ignored.");
        EAction.handleUserWarning(msg);    // Push warning to history (Win)
        qDebug(msg);    // Push warning to stdout
        return undefined;    // Failed, can't add or update
    } // End message
    // Continue without error ->

    // Diversify adding/updating:
    if (this.doc.hasLayer(layerName)) {
        msg = qsTr("Updated layer: %1").arg(layerName);
    }
    else {
        msg = qsTr("Added new layer: %1").arg(layerName);
    }

    // Initiate an operation for adding/updating a layer:
    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
    // Use global transaction group:
    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
    // Add/update the layer on the fly:
    this.di.applyOperation(layerOp)

    // Report change and set script level current layer:
    EAction.handleUserInfo(msg);    // Push info to history (Win)
    qDebug(msg);    // Push info to stdout
    this.currentLayerName = layerName;
};

/**
 * Validate a string as a layer name.
 * \param nameString        String to validate.
 *
 * \return Validated layer name or undefined.
 */
DrawFromCSV.prototype.validateLayerString = function(nameString) {
    // library.js fixSymbolTableName(name)...
    // https://qcad.org/rsforum/viewtopic.php?t=8248

    // Test naming with removing unallowed characters:
    var layerName = nameString.replace(/[<>/\\\":;\?\*|,=`]/g, "").trim();

    // Return 'undefined' when failing or return a layerName:
    if (layerName.length < 1 || layerName.length > 255 || layerName !== nameString) {
        return undefined;
    }
    return layerName;
 };

/**
 * Validate a string as a color. Provides in QCAD orange & gray.
 * \author  CVH © 2021
 *
 * \param colorString        String to validate.
 * \param asAttribute        True to validate as an entity attribute.
 *
 * \return Validated color or undefined.
 */
DrawFromCSV.prototype.validateColorString = function(colorString, asAttribute) {
    var colorList = new Array("red","lime","blue","cyan","magenta","yellow",
                              "maroon","green","navy","teal","purple","olive",
                              "black","silver","white");
    var color;         // Color from string
    var testString;    // Intermediate test string

    // # Issue Fixed # No CAD-Orange or CAD-Gray
    // Additional textual colors:
    colorList.push("Qorange");    // = #ff7f00
    colorList.push("Qgray");      // = #a0a0a4

    // Diversify on colorString and asAttribute flag:
    if (colorString.toUpperCase() === "BYLAYER" ) {
        // For attributes set ColorByLayer:
        color = (asAttribute) ? new RColor(RColor.ByLayer) : undefined;
    }
    else if (colorString.toUpperCase() === "BYBLOCK" ) {
        // For attributes set ColorByBlock:
        color = (asAttribute) ? new RColor(RColor.ByBlock) : undefined;
    }
    else if (colorString.startsWith("#") && colorString.length === 7) {
        // Test colorString with removing unallowed characters:
        testString = colorString.replace(/[^0-9a-fA-F\#]/g,"");
        if (testString !== colorString) {
            return undefined;    // Failed, invalid RGBColor
        }
        // Try setting colorString as HTML color code:
        color = new RColor(colorString);
    }
    else if (colorString === "Qorange") {
        // Additional QCAD orange:
        color = new RColor("#ff7f00");
    }
    else if (colorString === "Qgray") {
        // Additional QCAD gray:
        color = new RColor("#a0a0a4");
    }
    else if (colorList.containsIgnoreCase(colorString)) {
        // Try setting colorString as color name:
        color = new RColor(colorString);
    }

    // Return 'undefined' when failing or return a color:
    if (!isValidColor(color)) {
        return undefined;
        // Default = RSettings.getColor("Layer/DefaultColor", new RColor("black"))
        // Default = RSettings.getColor("Layer/DefaultColorLayer0", new RColor("white"))
    }
    return color;
};

/**
 * Validate a string as a Lineweight.
 * \param weightString        String to validate.
 * \param asAttribute         True to validate as an entity attribute.
 *
 * \return Validated Lineweight or undefined.
 */
DrawFromCSV.prototype.validateWeightString = function(weightString, asAttribute) {
    var lineWeight;    // Line weight from string

    // Diversify on weightString and asAttribute flag:
    if (weightString.toUpperCase() === "BYLAYER" ) {
        // For attributes set WeightByLayer:
        lineWeight = (asAttribute) ? RLineweight.WeightByLayer : undefined;
    }
    else if (weightString.toUpperCase() === "BYBLOCK" ) {
        // For attributes set WeightByBlock:
        lineWeight = (asAttribute) ? RLineweight.WeightByBlock : undefined;
    }
    else if (weightString.toUpperCase() === "DEFAULT" ) {
        // Set application default or Weight025:
        lineWeight = RSettings.getIntValue("Layer/DefaultLineweight", RLineweight.Weight025)
    }
    else if (isNumber(parseFloat(weightString))) {
        // Try setting weightString as number:
        lineWeight = parseFloat(weightString);
    }

    // Return 'undefined' when failing or return a lineweight:
    if (isNull(lineWeight) || RLineweight.getName(lineWeight).isEmpty()) {
        return undefined;
        // Default = RSettings.getIntValue("Layer/DefaultLineweight", RLineweight.Weight025)
        // Default = RSettings.getIntValue("GraphicsView/DefaultLineweight", RLineweight.Weight000);
    }
    return lineWeight;
};

/**
 * Validate a string as a Linetype.
 * \param typeString         String to validate.
 * \param asAttribute        True to validate as an entity attribute.
 *
 * \return Validated Linetype or undefined.
 */
DrawFromCSV.prototype.validateTypeString = function(typeString, asAttribute) {
    // # Oddity # RDocument.getLinetypeNames() are all in uppercase except "Continuous"
    // # Issue # How to include/allow textual RDocument.getLinetype labels?
    // Requires: this.doc    Current document
    var linetype;            // Line type from string

    // Diversify on typeString and asAttribute flag:
    if (typeString.toUpperCase() === "BYLAYER" ) {
        // For attributes set linetypeByLayer:
        linetype = (asAttribute) ? this.doc.getLinetypeByLayerId() : undefined;
    }
    else if (typeString.toUpperCase() === "BYBLOCK" ) {
        // For attributes set linetypeByBlock:
        linetype = (asAttribute) ? this.doc.getLinetypeByBlockId() : undefined;
    }
    else {
        // Try setting typeString textual:
        linetype = this.doc.getLinetypeId(typeString);
    }

//if (!isNull(linetype)) EAction.handleUserInfo(typeString + "||" + linetype + "||" + this.doc.getLinetypeLabel(linetype));

    // Return 'undefined' when failing or return a line type:
    if (isNull(linetype) || linetype < 0) {
        return undefined;
        // Default = this.doc.getLinetypeId()("CONTINUOUS")
    }
    return linetype;
};

/**
 * Returns the given polyline shape rounded by given radius if applicable.
 * Limited by used resource to non-bulging polyline shapes.
 * Limited by used resource to non-self-intersecting polyline shapes.
 * Limited to cut of 1/3 of the smallest edge adjacent to any enclosed angle.
 * (0° < enclosed angle <= 180°)
 *
 * \author CVH © 2021
 *
 * \param polylineShape        Polyline shape to round.
 * \param radius               Rounding radius.
 *
 * \return Polyline shape, rounded or original.
 */
DrawFromCSV.prototype.roundPolyline = function(polylineShape, radius) {
    // Based on: https://qcad.org/rsforum/viewtopic.php?t=8459
    // Rounding is fully unreliably with arc segments, self-intersecting or when R is too large.
    var edges, i, j, iMax;
    var enclosedAngle;
    var maxRadius;
    var isValidated = true;

//debugger;
    // Do nothing when NOT a polyline shape or without the required proxy:
    if (!isPolylineShape(polylineShape) || !RPolyline.hasProxy()) {
        return polylineShape;
    }

    // Do nothing when the radius is invalid:
    if (!this.validateAsRadius(radius)) {
        return polylineShape;
    }

    // Do nothing when the polyline shape has arc segments:
    if (polylineShape.hasArcSegments()) {
        return polylineShape;
    }

    // Do nothing when the polyline shape is self-intersecting:
    if (polylineShape.getSelfIntersectionPoints().length > 0) {
        return polylineShape;
    }

    // Get line shapes from given polyline shape:
    edges = polylineShape.getExploded();

    // Verify all successive edges pair-wise except last:
    iMax = edges.length;
    for (i=0; i<iMax; i++) {    // Cycle all edges
        j = i + 1;    // Points to next
        if (j === iMax) {
            if (polylineShape.isGeometricallyClosed()) {
                j = 0;    // Points to first edge with last
            }
            else {
                break;    // Stop cycling edges
            }
        }

        // Define absolute enclosed angle between edges:
        enclosedAngle = Math.abs(RMath.getAngleDifference180(edges[i].getAngle() + Math.PI, edges[j].getAngle()));

        // Avoid a retrace:
        if (RMath.fuzzyAngleCompare(enclosedAngle, 0.0)) {
            isValidated = false;    // Failed, can't round a retrace
            break;    // Stop cycling edges
        }
        // Avoid tan(90°) for inline segments:
        // # Informational # Inline segments are merged but the rounding may not land in or passed the point
        else if (RMath.fuzzyAngleCompare(enclosedAngle, Math.PI)) {
            maxRadius = Math.min(edges[i].getLength(), edges[j].getLength()) / 3;
        }
        // Define the local maximum rounding radius:
        else {
            maxRadius = Math.min(edges[i].getLength(), edges[j].getLength()) / 3 * Math.tan(enclosedAngle / 2);
        }

        // Limit cutoff to 1/3 of the smallest edge:
        if (radius > maxRadius) {
            isValidated = false;    // Failed, one or both edge(-s) too small
            break;    // Stop cycling edges
        }
    } // Loop edges


    // Return rounded polyline if validated:
    return (isValidated) ? polylineShape.roundAllCorners(radius) : polylineShape;
}

/*  # ToDo # Hatch entities
    Shape.complementOperation()
    var hatchData = new RHatchData();
    hatchData.setDocument(doc);
    hatchData.setAngle(0.0);
    hatchData.setScale(1.0);
    hatchData.setSolid(true);
    hatchData.setPatternName("SOLID");
    hatchData.newLoop();
    for (var k=0; k<shapes.length; ++k) {
        hatchData.addBoundary(shapes[k]);
    }
    op.addObject(new RHatchEntity(doc, hatchData));

Have a look at HatchDialog.prototype.patternChanged()
*/


