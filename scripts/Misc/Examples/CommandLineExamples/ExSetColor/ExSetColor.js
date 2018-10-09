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
include("scripts/library.js");

function printHelp() {
    print("Usage: " + args[1] + " [OPTIONS]... <input-file> <output-file>");
    print();
    print("Changes the color of all solid lines in the given file to blue.");
    print();
    print("  -h, -help               Display this help");
    printGenericUsage();
    print();
}

/**
 * \ingroup ecma_misc_examples_commandlineexamples
 * Command line tool.
 * Changes the color of all solid lines in the given file to blue.
 * Execute with ./qcad -autostart scripts/Misc/Examples/CommandLineExamples/ExSetColor/ExSetColor.js
 */
function main() {
    if (args.length < 3) {
        print("No input file given. Try -h for help.");
        return;
    }

    var opts = [ 
                 [ "help", false, "h" ]
               ];

    var ret = getOpt(args, opts);

    if (ret["h"] !== undefined) {
        printHelp();
        return;
    }
    
    var inputFile = args[args.length - 2];
    if (inputFile.indexOf("-") === 0) {
        print("No input file. Try -h for help.");
        return;
    }

    if (!new QFileInfo(inputFile).isAbsolute()) {
        inputFile = RSettings.getLaunchPath() + QDir.separator + inputFile;
    }

    var outputFile = args[args.length - 1];
    if (outputFile.indexOf("-") === 0) {
        print("No output file. Try -h for help.");
        return;
    }

    if (!new QFileInfo(outputFile).isAbsolute()) {
        outputFile = RSettings.getLaunchPath() + QDir.separator + outputFile;
    }

    var storage = new RMemoryStorage();
    var spatialIndex = new RSpatialIndexSimple();
    var doc = new RDocument(storage, spatialIndex);
    var di = new RDocumentInterface(doc);

    if (di.importFile(inputFile) != RDocumentInterface.IoErrorNoError) {
        qWarning("Cannot import file:", inputFile);
        return;
    }

    print("Converting");
    print("  from: " + inputFile);
    print("  to  : " + outputFile);

    var continuousId = doc.getLinetypeId("CONTINUOUS");
    var byLayerId = doc.getLinetypeId("BYLAYER");

    var op = new RModifyObjectsOperation();

    var ids = doc.queryAllEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = doc.queryEntity(id);
        var match = false;

        // only look at line entities:
        if (isLineEntity(entity)) {

            // entity linetype is fixed to 'continuous':
            if (entity.getLinetypeId()===continuousId) {
                match = true;
            }

            // entity linetype is 'ByLayer':
            else if (entity.getLinetypeId()===byLayerId) {
                var layerId = entity.getLayerId();
                var layer = doc.queryLayer(layerId);
                // layer linetype is 'continuous':
                if (layer.getLinetypeId()===continuousId) {
                    match = true;
                }
            }
        }

        if (match) {
            entity.setColor(new RColor("blue"));
            op.addObject(entity, false);
        }
    }

    di.applyOperation(op);

    di.exportFile(outputFile, "R24 (2010) DXF");
}

if (typeof(including)=='undefined' || including===false) {
    main();
}
