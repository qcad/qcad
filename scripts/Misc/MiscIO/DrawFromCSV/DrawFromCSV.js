/**
 * DrawFromCSV version 3.01
 * Copyright (c) 2021 of CVH.
 * All rights reserved.
 *
 * This file is a free extension of the QCAD project.
 * Permission to evaluate, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * This file is donated to the QCAD project.
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

include("../MiscIO.js");
// Including File.js for a file dialog
include("scripts/File/File.js");
// Included for Arc3P & Circle3P
include("scripts/ShapeAlgorithms.js");

/**
 * \class DrawFromCSV
 * \brief This action draws entities declared in a CSV file and handles document layers.
 * Supports the most common shapes, 2 solids, text ...
 * Allows different CSV styles, empty CSV lines, empty cells and commenting lines.
 * All details see: DrawCSV_doc.pdf
 * \ingroup ecma_misc_io
 * \author CVH © 2021
 */

// Define the class constructor, which calls the base class constructor
function DrawFromCSV(guiAction) {
    MiscIO.call(this, guiAction);
};

// We derive our class from the base class
DrawFromCSV.prototype = new MiscIO();
DrawFromCSV.includeBasePath = includeBasePath;

// BeginEvent handler:
DrawFromCSV.prototype.beginEvent = function() {
    MiscIO.prototype.beginEvent.call(this);

    // Call main script without file name:
    this.DrawFromCSVFile(this.getDocumentInterface(), undefined);
    // The user can choose a file from a file dialog

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
 * \return ids            List with affected entities ID or undefined.
 */
DrawFromCSV.prototype.DrawFromCSVFile = function(di, fileName) {
    var decPnt;                                    // Decimal point
    var lstSep;                                    // List separator
    var msg;                                       // Intermediate message strings
    var file, flags, ts;                           // User selected file & related
    var op, transaction, ids;                      // Operation to collect additions & returned transaction & affected list
    var textLine, defLineCount;                    // A single line of text & counter
    var fields, fieldsCount;                       // The text line split in separate fields & counter
    var xtrField1, xtrField2                       // Additional fields
    var offsetRv;                                  // Current offset vector
    var layer;                                     // A layer object
    var layerOp;                                   // A layer operation
    var zoomToAll = false;                         // Flag to select all & set zoom to all
    var selectAll = false;                         // Flag to select all after casting
    var newData;                                   // Newly created shape data
    var newEntity, newShape;                       // 515 Newly created document entity/shape
    var anyError;                                  // Error message
    var refRv, refRv1, refRv2, refRv3, refRv4;     // Reference points RVectors
    var refs;                                      // Collection of references
    var radius;                                    // Radius value
    var angle1, angle2;                            // 641Angle values
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

    // start a new transaction group:
    this.doc.startTransactionGroup();

    // Get QCAD decimal point or a dot by default:
    decPnt = RSettings.getStringValue("Input/DecimalPoint", ".");
    // Get QCAD list separator or a comma by default:
    lstSep = RSettings.getStringValue("Input/CartesianCoordinateSeparator", ",");
    // This may alter at the point where a style is declared in the CSV.

    // Without any, get filename by dialog:
    if (isNull(fileName)) {    // Without a filename as parameter >
        fileName = this.getFileName();    // .getFileName as in BlockListExport.js
        // Validate return value:
        if (isNull(fileName)) {    // Without a filename >
            msg = qsTr("No import file selected !");    // translated message
            EAction.handleUserWarning(msg);    // Push warning to history (Win)
            qDebug(msg);    // Push warning to stdout
            msg = qsTr("Command ended.");    // translated message
            EAction.handleUserMessage(msg);    // Push message to history (Win)
            qDebug(msg);    // Push End to stdout
            return undefined;    // Failed ! No filename
        } // End without a filename
    } // End without parameter
    // -> Continue with a fileName

    // Try to open file to read from:
    file = new QFile(fileName);
    flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
    if (!file.open(flags)) {    // Without a open file
        msg = qsTr("No file opened!");    // translated message
        EAction.handleUserWarning(msg);    // Push warning to history (Win)
        qDebug(msg);    // Push warning to stdout
        msg = qsTr("Command ended.");    // translated message
        EAction.handleUserMessage(msg);    // Push message to history (Win)
        qDebug(msg);    // Push End to stdout
        return undefined;    // Failed ! No open file
    } // End without open file
    // -> Continue with an open file

    // Retrieve actual active layer name:
    this.currentLayerName = this.doc.getCurrentLayerName();

    // Initiate a TextStream:
    ts = new QTextStream(file);
    ts.setCodec("UTF-8");

    // Initiate an operation for adding entities:
    op = new RAddObjectsOperation();
    // Set tool title used for undo/redo information:
    op.setAllowAll(true);    // Allow all transactions, layers can be hidden, frozen and or locked
    op.setText(qsTr("Cast CSV"));    // translated tool title
    op.setTransactionGroup(this.doc.getTransactionGroup());

    // Reset counters:
    defLineCount = castCount = 0;
    // Reset offset vector:
    offsetRv = new RVector(0.0, 0.0);
    // Reset relative position:
    this.relativePos = new RVector(0.0, 0.0);

    // Report reading from file:
    msg = qsTr("Reading from file: %1").arg(fileName);    // translated message
    EAction.handleUserInfo(msg);    // Push info to history (Win)
    qDebug(msg);    // Push info to stdout

//debugger;
    // Stream input from file
    // - - - - - - - - - - - -
    // Process all definition lines:
    do {
        // Initial values every CSV text line:
        newEntity = "n/a";                    // No entity
        anyError = undefined;                 // Empty = No error
        xtrField1 = xtrField2 = undefined;    // Empty = None
        customAttrib = {                      // Default = Current layer & all byLayer
            layer : this.currentLayerName,
            color : new RColor(RColor.ByLayer),
            lineweight : RLineweight.WeightByLayer,
            linetype : this.doc.getLinetypeId("BYLAYER"),
            LinetypeScale : 1};

        // Read a text line trimmed from leading and trailing whitespace:
        // # ToDo # Allow and strip trailing remark
        textLine = ts.readLine().trim();
        defLineCount++;

        // # Issue fixed # For all CSV styles any tab is redundant.
        // # Issue # What about tab delimited files ... No example.
        // Remove any tab:
        textLine = textLine.replace(/\t+/,"");

        // # Issue fixed # For all CSV styles any trailing comma or semicolon is redundant.
        // Remove any trailing list separator:
        textLine = textLine.replace(/[\;\,]+$/,"");

        // # Issue fixed # For all CSV styles any double quotation marks is redundant.
        // Remove any double quotation marks:
        textLine = textLine.replace(/\"+/g,"");

        // Detect CSV style:
        if (textLine.toUpperCase().startsWith("CSV")) {    // With a CSV switch >
            // Process by short CSV style in uppercase:
            switch (textLine.slice(3).toUpperCase()) {
            case "COMMA/DOT":
                decPnt = ".";
                lstSep = ",";
                msg = qsTr("Switched to comma/dot CSV style.");    // translated message
                break;
            case "SEMICOLON/DOT":
                decPnt = ".";
                lstSep = ";";
                msg = qsTr("Switched to semicolon/dot CSV style.");    // translated message
                break;
            case "SEMICOLON/COMMA":
                decPnt = ",";
                lstSep = ";";
                msg = qsTr("Switched to semicolon/comma CSV style.");    // translated message
                break;
            default:
                // Report unsupported CSV style switch:
                msg = qsTr("Unsupported or invalid CSV style, ignored ! Text line %1").arg(defLineCount);    // translated message
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
                continue;    // Not valid, ignore line and skip
            } // End switch on short CSV style
            // -> Continue with a forced valid CSV style

            // Report CSV style switch:
            EAction.handleUserInfo(msg);    // Push info to history (Win)
            qDebug(msg);    // Push info to stdout

            // On an CSV style skip to next line:
            continue;
        } // End is CSV switch
        // -> Continue without a CSV switch

        // Detect comment line:
        if (textLine.startsWith(";")) {
            // On an comment line skip to next line
            continue;
        } // End is comment
        // -> Continue without a comment line

        // Detect empty line:
        if (textLine.length === 0) {    // when empty >
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
            // Should not occur !
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
                msg = qsTr("Setting new relative origin failed, ignored ! Text line %1").arg(defLineCount);    // translated message
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End NOT valid
            break;
        case "LAYER":
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, RLayer.getHierarchySeparator());
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    this.currentLayerName = fields[1];
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not switch to layer, ignored ! Text line %1 layer: %2").arg(defLineCount).arg(fields[1]);    // translated message
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct  layer switch, ignored ! Text line %1").arg(defLineCount);    // translated message
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "NEWLAYER":
            msg = "";    // Empty
            if (fieldsCount === 7) {   // With 7 fields
                this.newOrUpdateLayer(fields, defLineCount);
            }
            else {    // With any but 7 fields >
                msg = qsTr("Not a correct  new layer switch, ignored ! Text line %1").arg(defLineCount);    // translated message
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End any
            break;
        case "HIDELAYER":
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, RLayer.getHierarchySeparator());
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    // Get the layer from the document:
                    layer = this.doc.queryLayer(fields[1]);
                    // Apply changes:
                    layer.setOff(true);
                    // Initiate an operation for updating a layer:
                    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    this.di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not hide layer, ignored ! Text line %1 layer: %2").arg(defLineCount).arg(fields[1]);    // translated message
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct  hide layer switch, ignored ! Text line %1").arg(defLineCount);    // translated message
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "FREEZELAYER":
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, RLayer.getHierarchySeparator());
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    // Get the layer from the document:
                    layer = this.doc.queryLayer(fields[1]);
                    // Apply changes:
                    layer.setFrozen(true);
                    // Initiate an operation for updating a layer:
                    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    this.di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not freeze layer, ignored ! Text line %1 layer: %2").arg(defLineCount).arg(fields[1]);    // translated message
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct  freeze layer switch, ignored ! Text line %1").arg(defLineCount);    // translated message
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "LOCKLAYER":
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, RLayer.getHierarchySeparator());
                // Validate layer switch:
                if (this.doc.hasLayer(fields[1])) {    // When the layer exists >
                    // Get the layer from the document:
                    layer = this.doc.queryLayer(fields[1]);
                    // Apply changes:
                    layer.setLocked(true);
                    // Initiate an operation for updating a layer:
                    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    this.di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not lock layer, ignored ! Text line %1 layer: %2").arg(defLineCount).arg(fields[1]);    // translated message
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct  lock layer switch, ignored ! Text line %1").arg(defLineCount);    // translated message
            } // End any
            // Report any message:
            if (msg.length > 0) {    // With a message >
                EAction.handleUserWarning(msg);    // Push warning to history (Win)
                qDebug(msg);    // Push warning to stdout
            } // End message
            break;
        case "ALLOWLAYER":
            msg = "";    // Empty
            if (fieldsCount === 2) {   // With 2 fields
                // Adapt naming to proper layer hierarchy separator:
                fields[1] = fields[1].replace(/\//g, RLayer.getHierarchySeparator());
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
                    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
                    // Update the layer on the fly:
                    this.di.applyOperation(layerOp);
                } // End existing
                else {    // When the layer doesn't exists >
                    msg = qsTr("Can not allow layer, ignored ! Text line %1 layer: %2").arg(defLineCount).arg(fields[1]);    // translated message
                } // End NOT existing
            } // End with 2 fields
            else {    // With any but 2 fields >
                msg = qsTr("Not a correct  allow layer switch, ignored ! Text line %1").arg(defLineCount);    // translated message
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
            try {    // try to create an entity >
                if (fieldsCount < 3) throw  qsTr("Low field count !");
                if (fieldsCount !== 3) throw qsTr("Odd field count !");
                refRv = this.getCoordinate(fields[1], fields[2]);    // Reference
                  if (isNull(refRv)) throw qsTr("Rv Invalid !");
                newData = new RPointData(refRv);
                newEntity = new RPointEntity(this.doc, newData);
                // Store single reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "LINE":
            // Create new Line entity:
            try {    // try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Startpoint
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Store endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "LINETO":
            // Create new Line entity:
            try {    // try to create an entity >
                if (fieldsCount < 3) throw  qsTr("Low field count !");
                if (fieldsCount !== 3) throw qsTr("Odd field count !");
                refRv1 = this.relativePos;    // Startpoint
                refRv2 = this.getCoordinate(fields[1], fields[2]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv Invalid !");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Store endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "VECTOR":
            // Create new Line entity:
            try {    // try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Startpoint
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid !");
                angle1 = this.getAngleValue(fields[4], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid !");
                refRv = new RVector();
                refRv.setPolar(radius, angle1);
                refRv2 = refRv1.operator_add(refRv);    // Endpoint
                  if (!refRv2.isValid()) throw qsTr("Rv2 Invalid !");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Store endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "VECTORTO":
            // Create new Line entity:
            try {    // try to create an entity >
                if (fieldsCount < 3) throw  qsTr("Low field count !");
                if (fieldsCount !== 3) throw qsTr("Odd field count !");
                refRv1 = this.relativePos;    // Startpoint
                radius = parseFloat(fields[1]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid !");
                angle1 = this.getAngleValue(fields[2], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid !");
                refRv = new RVector();
                refRv.setPolar(radius, angle1);
                refRv2 = this.relativePos.operator_add(refRv);    // Endpoint
                  if (!refRv2.isValid()) throw qsTr("Rv2 Invalid !");
                newShape = new RLine(refRv1, refRv2);
                newEntity = new RLineEntity(this.doc, new RLineData(newShape));
                // Store endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RAY":
            // Create new Ray entity:
            try {    // try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Base point
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Direction point
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                newShape = new RRay(refRv1, refRv2.operator_subtract(refRv1));
                newEntity = new RRayEntity(this.doc, new RRayData(newShape));
                // Store base point as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "XLINE":
            // Create new XLine entity:
            try {    // try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Base point
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Direction point
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                newShape = new RXLine(refRv1, refRv2.operator_subtract(refRv1));
                newEntity = new RXLineEntity(this.doc, new RXLineData(newShape));
                // Store base point as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARC":
            // Create new Arc entity:
            try {    // try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count !");
                if (fieldsCount !== 7) throw qsTr("Odd field count !");
                refRv = this.getCoordinate(fields[1], fields[2]);    // Center
                  if (isNull(refRv)) throw qsTr("Rv Invalid !");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid !");
                angle1 = this.getAngleValue(fields[4], false);
                  if (isNull(angle1)) throw qsTr("Angle1 Invalid !");
                angle2 = this.getAngleValue(fields[5], false);
                  if (isNull(angle2)) throw qsTr("Angle2 Invalid !");
                  if (RMath.fuzzyCompare(angle1, angle2, RS.AngleTolerance)) throw qsTr("Equal angles !");
                bool = fields[6].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape = new RArc(refRv, radius, angle1, angle2, bool);
                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Store endpoint as relative position:
                this.relativePos = newShape.getEndPoint();
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARC3P":
            // Create new Arc entity:
            try {    // try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count !");
                if (fieldsCount !== 7) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Startpoint
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Endpoint
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid !");
                newShape = ShapeAlgorithms.createArcFrom3Points(refRv1, refRv2, refRv3)
                  if (isNull(newShape) || !isArcShape(newShape)) throw qsTr("Arc Invalid !");
                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Store endpoint as relative position:
                this.relativePos = refRv3;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARCTO+A":
            // Create new Arc entity:
            try {    // try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.relativePos;    // Startpoint
                refRv2 = this.getCoordinate(fields[1], fields[2]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv Invalid !");
                angle1 = this.getAngleValue(fields[3], true);
                  if (isNull(angle1)) throw qsTr("Angle Invalid !");
                bool = fields[4].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                // Bulge conversion:
                radius = refRv1.getDistanceTo2D(refRv2) / 2 / Math.sin(angle1 / 2);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid !");
                // Get center from intersecting circles:
                circle1 = new RCircle(refRv1, radius);
                circle2 = new RCircle(refRv2, radius);
                ips = circle1.getIntersectionPoints(circle2, false);
                chord = new RLine(refRv1, refRv2);
                if (ips.length === 2) {    // With 2 solutions >
                    // XNOR:
                    if ((chord.getSideOfPoint(ips[0]) == RS.RightHand) == bool) {
                        refRv = ips[0];    // When true == true or false == false
                    }
                    else {
                        refRv = ips[1];
                    }
                }
                else if (ips.length === 1) {    // When center is in the middle >
                    refRv = chord.getMiddlePoint();
                }
                else {
                    // Should not occur !
                    throw qsTr("Center Invalid !");
                }
                // With a center point:
                angle1 = refRv.getAngleTo(refRv1);
                angle2 = refRv.getAngleTo(refRv2);
                newShape = new RArc(refRv, radius, angle1, angle2, bool);
                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Store endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "ARCTO+R":
            // Create new Arc entity:
            try {    // try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.relativePos;    // Startpoint
                refRv2 = this.getCoordinate(fields[1], fields[2]);    // Endpoint
                  if (isNull(refRv2)) throw qsTr("Rv Invalid !");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid !");
                  if (2*radius < refRv1.getDistanceTo2D(refRv2)) throw qsTr("Radius too small !");
                bool = fields[4].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                // Get center from intersecting circles:
                circle1 = new RCircle(refRv1, radius);
                circle2 = new RCircle(refRv2, radius);
                ips = circle1.getIntersectionPoints(circle2, false);
                chord = new RLine(refRv1, refRv2);
                if (ips.length === 2) {    // With 2 solutions:
                    // XNOR:
                    if ((chord.getSideOfPoint(ips[0]) == RS.RightHand) == bool) {
                        refRv = ips[0];    // true == true; false == false
                    }
                    else {
                        refRv = ips[1];
                    }
                }
                else if (ips.length === 1) {    // When center is in the middle:
                    refRv = chord.getMiddlePoint();
                }
                else {
                    // Should not occur !
                    throw qsTr("Center Invalid !");
                }
                // With a center point:
                angle1 = refRv.getAngleTo(refRv1);
                angle2 = refRv.getAngleTo(refRv2);
                newShape = new RArc(refRv, radius, angle1, angle2, bool);
                newEntity = new RArcEntity(this.doc, new RArcData(newShape));
                // Store endpoint as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CIRCLE":
            // Create new Circle entity:
            try {    // try to create an entity >
                if (fieldsCount < 4) throw  qsTr("Low field count !");
                if (fieldsCount !== 4) throw qsTr("Odd field count !");
                refRv = this.getCoordinate(fields[1], fields[2]);    // Center
                  if (isNull(refRv)) throw qsTr("Rv Invalid !");
                radius = parseFloat(fields[3]);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid !");
                newShape = new RCircle(refRv, radius);
                newEntity = new RCircleEntity(this.doc, new RCircleData(newShape));
                // Store single reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CIRCLE+P":
            // Create new Circle entity:
            try {    // try to create an entity >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Center
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Fit point
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                radius = refRv1.getDistanceTo2D(refRv2);
                  if (!this.validateAsRadius(radius)) throw qsTr("Radius Invalid !");
                newShape = new RCircle(refRv1, radius);
                newEntity = new RCircleEntity(this.doc, new RCircleData(newShape));
                // Store fit point as relative position:
                this.relativePos = refRv2;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CIRCLE3P":
            // Create new Circle entity:
            try {    // try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count !");
                if (fieldsCount !== 7) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid !");
                newShape = ShapeAlgorithms.createCircleFrom3Points(refRv1, refRv2, refRv3);
                  if (isNull(newShape) || !isCircleShape(newShape)) throw qsTr("Circle Invalid !");
                newEntity = new RCircleEntity(this.doc, new RCircleData(newShape));
                // Store third reference as relative position:
                this.relativePos = refRv3;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "TRIANGLE":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 7) throw  qsTr("Low field count !");
                if (fieldsCount !== 7) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid !");
                refs = new Array(refRv1, refRv2, refRv3);
                newShape = new RPolyline(refs, true);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # Issue fixed # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Store first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RSOLID3":    // Only Line-segments, No bulging
            // Create new Solid entity:
            try {    // try to create an entity >
                if (fieldsCount < 7) throw  qsTr("Low field count !");
                if (fieldsCount !== 7) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid !");
                newData = new RSolidData(refRv1, refRv2, refRv3);
                newEntity = new RSolidEntity(this.doc, newData);
                // Store first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "QUAD":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 9) throw  qsTr("Low field count !");
                if (fieldsCount !== 9) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid !");
                refRv4 = this.getCoordinate(fields[7], fields[8]);    // Forth reference
                  if (isNull(refRv4)) throw qsTr("Rv4 Invalid !");
                refs = new Array(refRv1, refRv2, refRv3, refRv4);
                newShape = new RPolyline(refs, true);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # Issue fixed # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Store first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RSOLID4":    // Only Line-segments, No bulging
            // Create new Solid entity:
            try {    // try to create an entity >
                if (fieldsCount < 9) throw  qsTr("Low field count !");
                if (fieldsCount !== 9) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // First reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                refRv2 = this.getCoordinate(fields[3], fields[4]);    // Second reference
                  if (isNull(refRv2)) throw qsTr("Rv2 Invalid !");
                refRv3 = this.getCoordinate(fields[5], fields[6]);    // Third reference
                  if (isNull(refRv3)) throw qsTr("Rv3 Invalid !");
                refRv4 = this.getCoordinate(fields[7], fields[8]);    // Forth reference
                  if (isNull(refRv4)) throw qsTr("Rv4 Invalid !");
                newData = new RSolidData(refRv1, refRv2, refRv4, refRv3);
                newEntity = new RSolidEntity(this.doc, newData);
                // Store first reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "SQUARE":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 5) throw  qsTr("Low field count !");
                if (fieldsCount !== 5) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Reference
                  if (isNull(refRv1)) throw qsTr("Rv Invalid !");
                sizeX = sizeY = parseFloat(fields[3]);
                  if (!isNumber(sizeX) || sizeX < RS.PointTolerance) throw qsTr("Size Invalid !");
                angle1 = this.getAngleValue(fields[4], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid !");
                refRv2 = new RVector(refRv1.x + sizeX, refRv1.y);
                  if (!refRv2.isValid()) throw qsTr("Rv2 Invalid !");
                refRv3 = new RVector(refRv1.x + sizeX, refRv1.y + sizeY);
                  if (!refRv3.isValid()) throw qsTr("Rv3 Invalid !");
                refRv4 = new RVector(refRv1.x, refRv1.y + sizeY);
                  if (!refRv4.isValid()) throw qsTr("Rv4 Invalid !");
                refs = new Array(refRv1, refRv2, refRv3, refRv4);
                newShape = new RPolyline(refs, true);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # Issue fixed # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Rotate the shape around refRv1:
                newEntity.rotate(angle1, refRv1);
                // Store single reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "RECTANGLE":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 6) throw  qsTr("Low field count !");
                if (fieldsCount !== 6) throw qsTr("Odd field count !");
                refRv1 = this.getCoordinate(fields[1], fields[2]);    // Reference
                  if (isNull(refRv1)) throw qsTr("Rv1 Invalid !");
                sizeX = parseFloat(fields[3]);
                  if (!isNumber(sizeX) || sizeX < RS.PointTolerance) throw qsTr("Size in X Invalid !");
                sizeY = parseFloat(fields[4]);
                  if (!isNumber(sizeY) || sizeY < RS.PointTolerance) throw qsTr("Size in Y Invalid !");
                angle1 = this.getAngleValue(fields[5], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid !");
                refRv2 = new RVector(refRv1.x + sizeX, refRv1.y);
                  if (!refRv2.isValid()) throw qsTr("Rv2 Invalid !");
                refRv3 = new RVector(refRv1.x + sizeX, refRv1.y + sizeY);
                  if (!refRv3.isValid()) throw qsTr("Rv3 Invalid !");
                refRv4 = new RVector(refRv1.x, refRv1.y + sizeY);
                  if (!refRv4.isValid()) throw qsTr("Rv4 Invalid !");
                refs = new Array(refRv1, refRv2, refRv3, refRv4);
                newShape = new RPolyline(refs, true);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # Issue fixed # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Rotate the shape around refRv1:
                newEntity.rotate(angle1, refRv1);
                // Store single reference as relative position:
                this.relativePos = refRv1;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "POLYGON":    // Only Line-segments, No bulging
            // Create new closed Polyline entity:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 11) throw qsTr("Polygon, less than 5 references !");
                if ((fieldsCount - 11)%2 !== 0) throw qsTr("Odd field count !");
                refs = [];    // Empty
                for (i=1; i<fieldsCount; i+=2) {    // Rv 1=1 3=2 5=3 Rv=(i+1)/2
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv %1 Invalid !").arg((i+1)/2);
                    refs.push(refRv);
                }
                newShape = new RPolyline(refs, true);
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # Issue fixed # Polylines with NaN widths.
                newEntity.setGlobalWidth(0.0);
                // Store first reference as relative position:
                this.relativePos = newShape.getStartPoint();
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "POLYLINE":
            // Create new Polyline entity:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 8) throw qsTr("Polyline, less than 2 references !");
                if ((fieldsCount - 8)%3 !== 0) throw qsTr("Odd field count !");
                newShape = new RPolyline();
                bool = fields[1].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape.setClosed(bool);
                for (i=2; i<fieldsCount; i+=3) {    // Rv 2=1 5=2 8=3 Rv=(i+1)/3
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv %1 Invalid !").arg((i+1)/3)
                    bulge = parseFloat(fields[i+2]);
                      if (!isNumber(bulge)) throw qsTr("Bulge %1 Invalid !").arg((i+1)/3);
                    newShape.appendVertex(refRv, bulge);
                }
                newEntity = new RPolylineEntity(this.doc, new RPolylineData(newShape));
                // # Issue fixed # Polylines with NaN widths.
                // https://www.ribbonsoft.com/bugtracker/index.php?do=details&task_id=2218
                // Should default to zero!? .appendVertex(RVector, Bulge=0, width1=0, width2=0)
                newEntity.setGlobalWidth(0.0);
                // Store first/last reference as relative position:
                this.relativePos = (bool) ? newShape.getStartPoint() : refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "FITSPLINE":
            // Create new fit point Spline entity:
            try {    // try to create an entity from a shape >
                if (!RSpline.hasProxy()) throw qsTr("Unsupported PRO feature !").arg(i/2);
                if (fieldsCount < 8) throw qsTr("Fit point Spline, less than 3 references !");
                if ((fieldsCount - 8)%2 !== 0) throw qsTr("Odd field count !");
                refs = [];    // Empty
                for (i=2; i<fieldsCount; i+=2) {    // Rv 2=1 4=2 6=3 Rv=i/2
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv %1 Invalid !").arg(i/2);
                    refs.push(refRv);
                }
                newShape = new RSpline();
                newShape.setDegree(3);    // Seems to be default
                newShape.setFitPoints(refs);
                bool = fields[1].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape.setPeriodic(bool);
                newEntity = new RSplineEntity(this.doc, new RSplineData(newShape));
                // Store last reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "CONTROLSPLINE":
            // Create new control point Spline entity:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 10) throw qsTr("Control point Spline, less than 4 references !");
                if ((fieldsCount - 10)%2 !== 0) throw qsTr("Odd field count !");
                newShape = new RSpline();
                newShape.setDegree(3);    // Seems to be default
                bool = fields[1].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                newShape.setPeriodic(bool);
                for (i=2; i<fieldsCount; i+=2) {    // Rv 2=1 4=2 6=3 Rv=i/2
                    refRv = this.getCoordinate(fields[i], fields[i+1]);    // References
                      if (isNull(refRv)) throw qsTr("Rv %1 Invalid !").arg(i/2);
                    newShape.appendControlPoint(refRv);
                }
                newEntity = new RSplineEntity(this.doc, new RSplineData(newShape));
                // Store last reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "TEXT":
        // create a text entity and add it to the operation:
            try {    // try to create an entity from a shape >
                if (fieldsCount < 16) throw qsTr("Text, low field count !");
                if (fieldsCount !== 16) throw qsTr("Text, odd field count !");
                refRv = this.getCoordinate(fields[1], fields[2]);    // References
                  if (isNull(refRv)) throw qsTr("Rv Invalid !");
                txtHeight = parseFloat(fields[3]);
                  if (!isNumber(txtHeight) || txtHeight <= 0.0) throw qsTr("Height Invalid !");
                // # Issue Solved # Signature updated in 3.26.0 !!
                txtWidth = parseFloat(fields[4]);
                  if (!isNumber(txtWidth) || txtWidth < 0.0) throw qsTr("Width Invalid !");
                txtVAlign = parseInt(fields[5]);
                  if (!isNumber(txtVAlign) || txtVAlign < 0 || txtVAlign > 3) throw qsTr("Vert. alignment Invalid !");
                txtHAlign = parseInt(fields[6]);
                  if (!isNumber(txtHAlign) || txtHAlign < 0 || txtHAlign > 5) throw qsTr("Horz. alignment Invalid !");
                txtDirection = parseInt(fields[7]);
                  if (!isNumber(txtDirection) || txtDirection < 0 || txtDirection > 2) throw qsTr("Drawing direction Invalid !");
                txtLSStyle = parseInt(fields[8]);
                  if (!isNumber(txtLSStyle) || txtLSStyle < 0 || txtLSStyle > 1) throw qsTr("Line spacing style Invalid !");
                txtLineSpace = parseInt(fields[9]);
                  if (!isNumber(txtLineSpace) || txtLineSpace <= 0.0) throw qsTr("Line spacing Invalid !");
                if (fields[10].toUpperCase() === "FILESTAMP") fields[10] = "File: " + fileName;
                if (fields[10].toUpperCase() === "DATESTAMP") fields[10] = "Date: " + new Date().toString();
                boldBool = fields[12].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                italicBool = fields[13].toUpperCase() === "TRUE";    // Ignoring anything else to default to false
                angle1 = this.getAngleValue(fields[14], false);
                  if (isNull(angle1)) throw qsTr("Angle Invalid !");
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
                // Store single reference as relative position:
                this.relativePos = refRv;
            }
            catch(err) {    // On any error > reset entity
                anyError = err;
                newEntity = undefined;
            }
            break;
        case "SPARE1":
//            break;
        case "SPARE2":
//            break;
        default:
            // Entry failed all cases:
            msg = qsTr("Unsupported entry ! Text line %1").arg(defLineCount);    // translated message
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
                // Should not occur ! > reset entity
                anyError = qsTr("Error with first optional list !");
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
                // Should not occur ! > reset entity
                anyError = qsTr("Error with second optional list !");
                newEntity = undefined;
            }
        }

        // Validate layer attributes if any:
        if (!isNull(attribText)) {
            // Overwrite customAttrib with 5 verified attributes:
            customAttrib = this.validateAttributes(attribText, defLineCount);
        }

        // Finalize new drawing entity and add to operation:
        if (isEntity(newEntity)) {    // With a valid shape >
            // Apply general properties:
            // A) Entity Layer:
            newEntity.setLayerName(customAttrib.layer);
            // B) Entity Color:
            newEntity.setColor(customAttrib.color);
            // C) Entity Lineweight:
            newEntity.setLineweight(customAttrib.lineweight);
            // D) Entity Linetype:
            newEntity.setLinetypeId(customAttrib.linetype);
            // E) Entity Linetype:
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
            // # Issue Fixed # Local errors are strings, internal errors are objects.
            anyError = (isString(anyError)) ? anyError : anyError.message;
            msg = qsTr("Not a correct entry ! Text line %1 : %2").arg(defLineCount).arg(anyError);    // translated message
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
    this.di.setCurrentLayer(this.currentLayerName);
*/
    // # Issue # .setCurrentLayer is an extra action!
    // Also encountered with AddLayer.js: adding is 1 action undo is 2 actions
    // https://www.qcad.org/rsforum/viewtopic.php?t=8287

    // Based on ActivateLayerState class 'restore current layer'
//    Initiate an operation for setting current layer:
//    layerOp = new RAddObjectOperation();
//    layerOp.setText(qsTr("Cast CSV"));    // translated tool title
//    layerOp.setTransactionGroup(this.doc.getTransactionGroup());
    // Update the document variables:
    var docVars = this.doc.queryDocumentVariables();
    docVars.setCurrentLayerId(this.doc.getLayerId(this.currentLayerName));
//    layerOp.addObject(docVars);
    op.addObject(docVars);
//    this.di.applyOperation(layerOp);
    // # Issue # Functional but change doesn't show in Layer List Widget
    //           Change is visible after drawing tab swap, new document or after undo + redo
//    this.di.regenerateScenes();
//    this.di.repaintViews();
/*
    // Based on LayerList.js
    // 'this.blockSignals' [undefined] is not a function.
    this.blockSignals(true);
    this.di.setCurrentLayer(this.currentLayerName);
    this.blockSignals(false);
*/
/*
    // Based on LayerList.js
    // ReferenceError: Can't find variable: RLayerListQt
    RLayerListQt.blockSignals(true);
    this.di.setCurrentLayer(this.currentLayerName);
    RLayerListQt.blockSignals(false);
*/

    // Apply all entity operations in one go:
    transaction = this.di.applyOperation(op);    // No fault without any

    // Retrieve the affected entities:
    ids = transaction.getAffectedObjects();

    // Apply optional selection with any entities:
    if (selectAll) {
        if (ids.length > 0) {
            this.di.selectEntities(ids, false);    // NOTaddToCurrent
        }
    }

    // Apply optional zoom with any entities:
    if (zoomToAll) {
        if (ids.length > 0) {
            graphicsView = this.di.getGraphicsViewWithFocus();
            // Simple.js di.getLastKnownViewWithFocus();
            if (!isNull(graphicsView)) {
                graphicsView.getRGraphicsView().zoomToEntities(ids, 30);    // Margin in pixels
            }
        }
    }

    // Terminate command:
    file.close();
    if (castCount > 0) {
        msg = qsTr("Casted entries : %1 with %2 text lines").arg(castCount).arg(defLineCount);    // translated message
        EAction.handleUserInfo(msg);    // Push message to history (Win)
        msg = qsTr("Importing CSV complete. Command ended.");    // translated message
    }
    if (castCount === 0) {
        msg = qsTr("Nothing casted !");    // translated message
        EAction.handleUserWarning(msg);    // Push warning to history (Win)
        msg = qsTr("Command ended.");    // translated message
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
 * \param this.doc        Current document.
 *
 * \return Full path to file or 'undefined' when none.    (String)
 */
// CVH added: .getFileName
// Known issues: Persistent behavior.
//          Empty files with suffix(-es).
DrawFromCSV.prototype.getFileName = function() {
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
        return undefined;
    }
    fileName = ret[0];

    if (fileName === "") {
        return undefined;
    }

    if (drawingFileName.length === 0) {
        RSettings.setValue("DrawFromCSV/Path", new QFileInfo(fileName).absolutePath());
    }

    return fileName;
};

/**
 * Gets the absolute coordinate vector from a textual coordinate pair.
 * Relative when xField starts with '@'.
 * Relative/polar when relative and yField starts with '<'
 * Validates both entries as numbers.
 * \author  CVH © 2021
 *
 * \param xField        First coordinate.
 * \param yField        Second coordinate.
 * 
 * \return The resulting RVector or 'undefined' when failed.
 */
DrawFromCSV.prototype.getCoordinate = function(xField, yField) {
    var xValue, yValue;
    var newRv, ret;

    if(isNull(xField) || isNull(yField)) return undefined;

    // Calculate absolute return vector:
    if (xField.startsWith("@")) {    // When relative
        // Fail when relative position is invalid:
        if (!this.relativePos.isValid()) return undefined;

        xValue = parseFloat(xField.slice(1));
        // Fail when xValue is no number:
        if (!isNumber(xValue)) return undefined;

        // Check for polar:
        if (yField.startsWith("<")) {    // When relative/polar
            yValue = this.getAngleValue(yField.slice(1), false);
            // Fail when yValue didn't validate to a number:
            if (isNull(yValue)) return undefined;
            // Set relative/polar vector
            newRv = new RVector();
            newRv.setPolar(xValue, yValue);
        } // End polar
        else {    // When NOT polar
            yValue = parseFloat(yField);
            // Fail when yValue is no number:
            if (!isNumber(yValue)) return undefined;
            // Set relative vector
            newRv = new RVector(xValue, yValue);
        } // End NOT polar
        // -> Continue with a newRv

        // Fail when new vector is invalid:
        if (!newRv.isValid()) return undefined;

        // Use relative vector:
        ret = this.relativePos.operator_add(newRv);
    } // End relative
    else {    // When absolute
        xValue = parseFloat(xField);
        yValue = parseFloat(yField);
        // Fail when one of the values is no number:
        if (!isNumber(xValue) || !isNumber(yValue)) return undefined;

        // Use absolute vector:
        ret = new RVector(xValue, yValue);
    } // End absolute
    // -> Continue with a return vector

    // Validate and return vector or failed:
    if (ret.isValid()) {
        this.relativePos = ret;
        return ret;
    }
    return udefined;
}

/**
 * Validates a value as a radius value within limits.
 * Returns 'true' when valid else 'false'.
 */
DrawFromCSV.prototype.validateAsRadius = function(value) {
    // Fail when not a number:
    if (!isNumber(value)) return false;

    // Restrict between +RS.PointTolerance and +1.0e6:
    // Conform QCAD Arc methods.
    return !(value > 1.0e6  || value < RS.PointTolerance);
 };

/**
 * Gets an angle in radians from a textual value in degrees or radians.
 * Validates entry as angle or as sweep.
 * \author  CVH © 2021
 *
 * \param angleStr        A textual angle notation.
 * \param isSweep         True to validate as sweep angle.
 * 
 * \return The resulting angle in radians or 'undefined' when failed.
 */
DrawFromCSV.prototype.getAngleValue = function(angleStr, isSweep) {
    var ret;

    // Fail without a value string:
    if (isNull(angleStr) || angleStr.length === 0) return undefined;

    // Use radians or degrees:
    if (angleStr.toUpperCase().endsWith("R") || angleStr.toUpperCase().endsWith("RAD")) {
        ret = parseFloat(angleStr);
    }
    else {
        ret = RMath.deg2rad(parseFloat(angleStr));
    }

    // Fail when not a number:
    if (!isNumber(ret)) return undefined;

    // Optionally restrict return between +2Pi and -2Pi:
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
 * \param this.doc        Current document.
 * \param fields          Attribute set.
 * \param line            CSV text line number.
 * 
 * \return Validated attributes set.
 */
DrawFromCSV.prototype.validateAttributes = function(fields, line) {
    // fields[0] matches 'ATTRIB', fields count >1, fields are key/value pairs
    var i, pairs;
    var keyValue;
    var anyError = "";
    var layerName, color, weigth, type;
    var ret = {                       // Default = Current layer, byLayer & scale 1
        layer : this.currentLayerName,
        color : new RColor(RColor.ByLayer),
        lineweight : RLineweight.WeightByLayer,
        linetype : this.doc.getLinetypeId("BYLAYER"),
        LinetypeScale : 1};

    // Define pairs count:
    pairs = fields.length - 1;
    // Report none:
    if (pairs < 1) {
        anyError = qsTr("Attributes empty ! Text line %1").arg(line);    // translated message
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
            keyValue[1] = keyValue[1].replace(/\//g, RLayer.getHierarchySeparator());

            // Validate layer naming:
            layerName = this.validateLayerString(keyValue[1]);
            if (isNull(layerName)) {
                anyError = qsTr("Not a correct layer name ! Text line %1 name: %2").arg(line).arg(keyValue[1]);    // translated message
            }
            // Check if layer exist:
            if (this.doc.hasLayer(layerName)) {
                ret.layer = layerName;
            }
            else {
                anyError = qsTr("Layer doesn't exist, ignored ! Text line %1 layer: %2").arg(line).arg(keyValue[1]);    // translated message
            }
            break;
        case "COLOR":
            // Validate Color attribute from string:
            color = this.validateColorString(keyValue[1], true);
            if (isNull(color)) {
                anyError = qsTr("Not a correct color, ignored ! Text line %1 color: %2").arg(line).arg(keyValue[1]);    // translated message
            }
            else {
                ret.color = color;
            }
            break;
        case "LINEWEIGHT":
            // Validate Lineweight attribute from string:
            weigth = this.validateWeightString(keyValue[1], true);
            if (isNull(weigth)) {
                anyError = qsTr("Not a correct Lineweight, ignored ! Text line %1 weight: %2").arg(line).arg(keyValue[1]);    // translated message
            }
            else {
                ret.lineweight = weigth;
            }
            break;
        case "LINETYPE":
            // Validate Linetype attribute from string:
            type = this.validateTypeString(keyValue[1], true);
            if (isNull(type)) {
                anyError = qsTr("Not a correct Linetype, ignored ! Text line %1 type: %2").arg(line).arg(keyValue[1]);    // translated message
            }
            else {
                ret.linetype = type;
            }
            break;
        case "LINETYPESCALE":
            // Validate LinetypeScale attribute from string:
            if (!isNumber(parseFloat(keyValue[1])) || parseFloat(keyValue[1]) < 0) {
                anyError = qsTr("Not a correct Linetype scale, ignored ! Text line %1 scale: %2").arg(line).arg(keyValue[1]);    // translated message
            }
            else {
                ret.LinetypeScale = parseFloat(keyValue[1]);
            }
            break;
        default:
            // None of the above:
            anyError = qsTr("Not a correct attribute, ignored ! Text line %1 > %2").arg(line).arg(fields[i]);    // translated message
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
 * Updates an exiting layer.
 * Initiates the creation of a new layer if such doesn't exist.
 * \author  CVH © 2021
 *
 * \param this.di                      Document interface.
 * \param this.doc                     Current document.
 * \param this.currentLayerName        Script level current layer.
 * \param fields                       Attribute set.
 * \param line                         CSV text line number.
 * 
 * \return Nothing, updates or adds a layer, reports errors.
 */
DrawFromCSV.prototype.newOrUpdateLayer = function(fields, line) {
    // fields[0] matches 'NEWLAYER', fields count = 7
    var anyError = "";
    var layerName, color, weigth, type, plot, snap;
    var parentLayer;
    var layer;
    var layerOp;
    var defaultColor, defaultType, defaultWeight;
    var msg = "";
    var subSep = RLayer.getHierarchySeparator();

//debugger;
    // Adapt layer naming to proper layer hierarchy separator:
    fields[1] = fields[1].replace(/\//g, RLayer.getHierarchySeparator());

    // Validate layer naming:
    layerName = this.validateLayerString(fields[1]);
    if (isNull(layerName)) {    // Without a valid layer name >
        anyError = qsTr("Not a correct layer name ! Text line %1 name: %2").arg(line).arg(fields[1]);    // translated message
    } // End without name
    else {    // With a valid layer name >
        if (layerName.indexOf(RLayer.getHierarchySeparator()) !== -1) {    // With parent/sub layer >
            parentLayer = layerName.split(subSep, layerName.count(subSep)).join(subSep);
            if (!this.doc.hasLayer(parentLayer)) {    // Without a parent layer >
                anyError = qsTr("Parent layer doesn't exist ! Text line %1 layer: %2").arg(line).arg(parentLayer);    // translated message
            } // End without parent
        } //End with sub
        // -> Continue with a verified name

        // With a name, retrieve the layer or create a new one:
        if (this.doc.hasLayer(layerName)) {   // With an existing layer >
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
            anyError = qsTr("Not a correct color ! Text line %1 color: %2").arg(line).arg(fields[2]);    // translated message
        }
        else {
            layer.setColor(color);
        }

        // Validate Lineweight from a string:
        weigth = this.validateWeightString(fields[3], false);
        if (isNull(weigth)) {
            anyError = qsTr("Not a correct Lineweight ! Text line %1 weight: %2").arg(line).arg(fields[3]);    // translated message
        }
        else {
            layer.setLineweight(weigth);
        }

        // Validate Linetype from a string:
        type = this.validateTypeString(fields[4], false);
        if (isNull(type)) {
            anyError = qsTr("Not a correct Linetype ! Text line %1 type: %2").arg(line).arg(fields[4]);    // translated message
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
        msg = qsTr("Add/Update layer ignored !");    // translated message
        EAction.handleUserWarning(msg);    // Push warning to history (Win)
        qDebug(msg);    // Push warning to stdout
        return undefined;    // Failed.
    } // End message

    // Use new layer as current:
    this.currentLayerName = layerName;

    // Diversify adding/updating and report change:
    if (this.doc.hasLayer(layerName)) {
        msg = qsTr("Updated layer : %1").arg(layerName);    // translated message
    }
    else {
        msg = qsTr("Added new layer : %1").arg(layerName);    // translated message
    }
    EAction.handleUserInfo(msg);    // Push info to history (Win)
    qDebug(msg);    // Push info to stdout

    // Initiate an operation for adding/updating a layer:
    layerOp = new RAddObjectOperation(layer, false);    // NOTuseCurrentAttributes, undoAble=true
    layerOp.setTransactionGroup(this.doc.getTransactionGroup());

    // Add/update the layer on the fly:
    this.di.applyOperation(layerOp)
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

    // Try removing unallowed characters:
    var layerName = nameString.replace(/[<>/\\\":;\?\*|,=`]/g, "");

    // Return layerName or 'undefined' when failing:
    if (layerName.length === 0 || layerName.length > 255 || layerName !== nameString) {
        return undefined;
    }
    return layerName;
 };

/**
 * Validate a string as a color.
 * \param colorString        String to validate.
 * \param asAttribute        True to validate as an entity attribute.
 *
 * \return Validated color or undefined.
 */
DrawFromCSV.prototype.validateColorString = function(colorString, asAttribute) {
    var colorList = new Array("red","lime","blue","cyan","magenta","yellow","n/a",
                              "maroon","green","navy","teal","purple","olive",
                              "black","n/a","silver","white");
//    No CAD-Orange & CAD-Gray
//    colorList.push("light gray");    // # TEST case #

    var color;

    // Additional textual colors:
    colorList.push("Qorange");    // = #ff7f00
    colorList.push("Qgray");      // = #a0a0a4

    // Diversify on colorString and asAttribute flag:
    if (colorString.toUpperCase() === "BYLAYER" ) {
        // For attributes set ColorByLayer:
        color = (asAttribute) ? new RColor(RColor.ByLayer) : undefined;
    }
    else if (colorString.toUpperCase() === "BYBLOCK" ) {
        // For attributes set ColorByBlock):
        color = (asAttribute) ? new RColor(RColor.ByBlock) : undefined;
    }
    else if (colorString.startsWith("#") && colorString.length === 7) {
        // # ToDo # Regex check [0-9 a-f A-F]
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

    // Return color or 'undefined' when failing:
    if (!isValidColor(color)) {
        return undefined;
        //= RSettings.getColor("Layer/DefaultColor", new RColor("black"))
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
    var lineWeight;

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

    // Return lineweight or 'undefined' when failing:
    if (isNull(lineWeight) || RLineweight.getName(lineWeight).isEmpty()) {
        return undefined;
        //= RSettings.getIntValue("Layer/DefaultLineweight", RLineweight.Weight025)
    }
    return lineWeight;
};

/**
 * Validate a string as a Linetype.
 * \param this.doc          Current document.
 * \param typeString        String to validate.
 * \param asAttribute       True to validate as an entity attribute.
 *
 * \return Validated Linetype or undefined.
 */
DrawFromCSV.prototype.validateTypeString = function(typeString, asAttribute) {
    // # ODDITY # RDocument.getLinetypeNames() are all in uppercase except "Continuous"
    // # Issue # How to include/allow textual RDocument.getLinetype labels?
    var linetype;

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

//if (!isNull(linetype)) EAction.handleUserInfo(typeString + ";" + linetype + ";" + this.doc.getLinetypeLabel(linetype));

    // Return linetype or 'undefined' when failed:
    if (isNull(linetype) || linetype < 0) {
        return undefined;
        //= this.doc.getLinetypeId()("CONTINUOUS")
    }
    return linetype;
};

/**
 * Adds a menu for the DrawFromCSV action to Misc | Script Examples | Import/Export menu.
 */
DrawFromCSV.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Draw from CSV"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);    // Can't draw without a document
    action.setRequiresSelection(false);    // No selection required
    action.setScriptFile(basePath + "/DrawFromCSV.js");
    action.setIcon(basePath + "/DrawFromCSV.svg");
//    action.setDefaultShortcut(new QKeySequence("d,c,s,v"));    // Ruled out (no good option)
    action.setDefaultCommands(["drawcsv","dcsv"]);    // An Array!
    var tip = qsTr("Draws entities based on textual entries in a CSV file");
    action.setStatusTip(tip);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tip);    // Displays aside Toolbars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(52100);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscIOMenu", "MiscIOToolBar", "MiscIOToolsPanel"]);
};

