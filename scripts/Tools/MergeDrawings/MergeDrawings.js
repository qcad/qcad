/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

/**
 * Command line tool.
 * Marges multiple drawing files (DWG, DXF) into one.
 */

include("scripts/library.js");
include("scripts/Tools/arguments.js");

function printHelp() {
    print("Usage: " + args[1] + " [OPTIONS]... <XML config file>");
    print();
    print("Merges multiple drawing files (DWG, DXF, ...) into one.");
    print();
    print("  -f, -force              Overwrite existing output file");
    print("  -h, -help               Display this help");
    print("  -o FILE, -outfile=FILE  Set output file to FILE");
    print("                          default is same path and base name as input file");
    print();
    print("XML format:");
    print("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    print("<items>");
    print("    <item src=\"file1.dxf\">");
    print("        <insert x=\"10\" y=\"0\" angle=\"30\" flipx=\"false\" flipy=\"false\" />");
    print("    </item>");
    print("</items>");
    print();
}

function main() {
    if (testArgument(args, "-h", "-help")) {
        printHelp();
        return;
    }

    if (args.length < 3) {
        print("No input file given. Try -h for help.");
        return;
    }

    qApp.organizationName = "QCAD";
    qApp.organizationDomain = "QCAD.org";
    qApp.applicationVersion = RSettings.getVersionString();
    qApp.applicationName = "QCAD";
    RSettings.setApplicationName("QCAD3");
    
    var xmlFile = args[args.length - 1];
    if (xmlFile.indexOf("-") === 0) {
        print("No input file. Try -h for help.");
        return;
    }

    var fi = new QFileInfo(xmlFile);
    if (!fi.isAbsolute()) {
        xmlFile = RSettings.getLaunchPath() + QDir.separator + xmlFile;
        fi = new QFileInfo(xmlFile);
    }

    var outputFile = getArgument(args, "-o", "-outfile");
    if (outputFile!==undefined) {
        if (!new QFileInfo(outputFile).isAbsolute()) {
            outputFile = RSettings.getLaunchPath() + QDir.separator + outputFile;
        }
    }
    else {
        outputFile = fi.absolutePath() + QDir.separator + fi.completeBaseName() + ".dxf";
    }

    if (new QFileInfo(outputFile).exists() && !testArgument(args, "-f", "-force")) {
        print("Output file exists already, not overwriting: ", outputFile);
        print("Use -f to force overwrite");
        return;
    }

    // parse XML into array:
    var file = new QFile(xmlFile);

    var xmlReader = new QXmlSimpleReader();
    var source = new QXmlInputSource(file);
    var handler = new XmlHandler();
    xmlReader.setContentHandler(handler);
    var ok = xmlReader.parse(source, false);

    file.close();

    // target document:
    var docDest = new RDocument(new RMemoryStorage(), new RSpatialIndexNavel());
    var diDest = new RDocumentInterface(docDest);

    for (var i=0; i<handler.items.length; i++) {
        var item = handler.items[i];

        for (var k=0; k<item.inserts.length; k++) {
            var insert = item.inserts[k];

            qDebug("insert: ", item.src, insert.x);
            var doc = new RDocument(new RMemoryStorage(), new RSpatialIndexNavel());
            var di = new RDocumentInterface(doc);

            var src;
            if (!new QFileInfo(item.src).isAbsolute()) {
                src = fi.absolutePath() + QDir.separator + item.src;
            }
            else {
                src = item.src;
            }

            if (di.importFile(src) !== RDocumentInterface.IoErrorNoError) {
               qWarning("cannot import file: ", src);
            }

            var op = new RPasteOperation(doc);
            op.setOffset(new RVector(insert.x, insert.y));
            op.setRotation(insert.angle);
            op.setScale(insert.scale);
            op.setFlipHorizontal(insert.flipX);
            op.setFlipVertical(insert.flipY);
            op.setBlockName(new QFileInfo(src).completeBaseName());
            diDest.applyOperation(op);
        }
    }

    diDest.exportFile(outputFile);

    print("Converting");
    print("  from: " + xmlFile);
    print("  to  : " + outputFile);
}



/**
 * SAX style XML handler.
 */
function XmlHandler() {
    QXmlDefaultHandler.call(this);
    this.items = [];
    this.item = undefined;
}

XmlHandler.prototype = new QXmlDefaultHandler();

/**
 * Handle element (tag).
 */
XmlHandler.prototype.startElement = function(namespaceURI, localName, qName, atts) {
    if (localName==="item") {
        this.item = {};
        this.item.src = atts.value("src");
        this.item.inserts = [];

        this.items.push(this.item);
    }

    if (localName==="insert") {
        if (isNull(this.item)) {
            qWarning("insert element found outside of the scope of an item element");
            return false;
        }
        var insert = {};
        insert.x = this.getDoubleAttribute(atts, "x", 0);
        insert.y = this.getDoubleAttribute(atts, "y", 0);
        insert.angle = RMath.deg2rad(this.getDoubleAttribute(atts, "angle", 0));
        insert.scale = this.getDoubleAttribute(atts, "scale", 1.0);
        insert.flipX = this.getBoolAttribute(atts, "flipx", false);
        insert.flipY = this.getBoolAttribute(atts, "flipy", false);
        this.item.inserts.push(insert);
    }

    return true;
};

XmlHandler.prototype.getDoubleAttribute = function(atts, name, defaultValue) {
    var str = atts.value(name);
    if (str.length===0) {
        return defaultValue;
    }
    return parseFloat(str);
};

XmlHandler.prototype.getBoolAttribute = function(atts, name, defaultValue) {
    var str = atts.value(name).toLowerCase();
    if (str.length===0) {
        return defaultValue;
    }
    return str==="true" || str==="1";
};

if (typeof(including)=='undefined' || including===false) {
    main();
}
