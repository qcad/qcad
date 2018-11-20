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

/**
 * Command line tool.
 * Merges multiple drawing files (DWG, DXF) into one.
 */

include("scripts/Tools/arguments.js");
include("scripts/ImportExport/SvgImporter/SvgImporterInit.js");

function printHelp() {
    print("Usage: " + args[1] + " [OPTIONS]... <XML config file>");
    print();
    print("Merges multiple drawing files (DWG, DXF, ...) into one.");
    print();
    print("  -f, -force              Overwrite existing output file");
    print("  -h, -help               Display this help");
    print("  -t TYPE, -type=TYPE     Set file type to TYPE ");
    print("                          (e.g. R12...R27 or 2000...2013)");
    print("  -o FILE, -outfile=FILE  Set output file to FILE");
    print("                          default is same path and base name as input file");
    printGenericUsage();
    print();
    print("XML format:");
    print("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    print("<merge xmlns=\"http://qcad.org/merge/elements/1.0/\" unit=\"Millimeter\">");
    print("    <item src=\"file1.dxf\">");
    print("        <insert x=\"10\" y=\"0\" angle=\"30\" flipx=\"false\" flipy=\"false\" />");
    print("    </item>");
    print("</merge>");
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
    RSettings.setApplicationNameOverride("QCAD3");
    
    var xmlFile = args[args.length - 1];
    if (xmlFile.indexOf("-") === 0) {
        print("No input file. Try -h for help.");
        return;
    }

    RFileImporterRegistry.registerFileImporter(new SvgImporterFactory());

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

    var type = getArgument(args, "-t", "-type");
    if (type===undefined) {
        type = "";
    }

    // parse XML into array:
    //var file = new QFile(xmlFile);

    //var xmlReader = new QXmlSimpleReader();
    //var source = new QXmlInputSource(file);
    var handler = new XmlHandler();
    //xmlReader.setContentHandler(handler);
    //var ok = xmlReader.parse(source, false);
    parseXml(xmlFile, handler);

    //file.close();

    // target document:
    var docDest = new RDocument(new RMemoryStorage(), new RSpatialIndexSimple());
    docDest.setUnit(handler.outputUnit);
    var diDest = new RDocumentInterface(docDest);

    for (var i=0; i<handler.items.length; i++) {
        var item = handler.items[i];

        for (var k=0; k<item.inserts.length; k++) {
            var insert = item.inserts[k];

            qDebug("insert: ", item.src, insert.x);
            var doc = new RDocument(new RMemoryStorage(), new RSpatialIndexSimple());
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

            // input files without units are assumed to be in output unit:
//            if (doc.getUnit()===RS.None) {
//                qDebug("adjusting unit of unitless input file '%1' to '%2'.".arg(src).arg(RUnit.unitToName(handler.outputUnit)));
//                doc.setUnit(handler.outputUnit);
//            }

            var op = new RPasteOperation(doc);
            op.setOffset(new RVector(insert.x, insert.y));
            op.setRotation(insert.angle);
            op.setScale(insert.scale);
            op.setFlipHorizontal(insert.flipX);
            op.setFlipVertical(insert.flipY);
            op.setBlockName(new QFileInfo(src).completeBaseName());
            diDest.applyOperation(op);

            di.destroy();
        }
    }

    diDest.exportFile(outputFile, type);

    print("Converting");
    print("  from: " + xmlFile);
    print("  to  : " + outputFile);

    diDest.destroy();
}



/**
 * SAX style XML handler.
 */
function XmlHandler() {
    QXmlDefaultHandler.call(this);
    this.items = [];
    this.item = undefined;
    this.outputUnit = RS.Millimeter;
}

XmlHandler.prototype = new QXmlDefaultHandler();

/**
 * Handle element (tag).
 */
XmlHandler.prototype.startElement = function(namespaceURI, localName, qName, atts) {
    if (localName==="merge") {
        this.outputUnit = this.getUnitAttribute(atts, "unit", RS.Millimeter);
    }

    if (localName==="item") {
        this.item = {};
        this.item.src = atts.value("src");
        this.item.inserts = [];

        this.items.push(this.item);
    }

    if (localName==="insert") {
        if (this.item===undefined) {
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

XmlHandler.prototype.getUnitAttribute = function(atts, name, defaultValue) {
    var str = atts.value(name).toLowerCase();
    if (str.length===0) {
        return defaultValue;
    }
    return RUnit.parseUnit(str);
};


if (typeof(including)=='undefined' || including===false) {
    main();
}
