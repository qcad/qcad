include("scripts/simple.js");
include("scripts/Tools/arguments.js");

function printHelp() {
    print("Usage: " + args[1] + " [OPTION]... <drawing file>");
    print();
    print("This tool does...");
    print();
    print("  -f, -force              Overwrite existing output file");
    print("  -h, -help               Display this help");
    print("  -o, -outfile=FILE       Set output file to FILE");
    print("  -p, -parameter          Some parameter...");
    print("  ...");
    printGenericUsage();
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
    
    var inFile = args[args.length - 1];
    if (inFile.indexOf("-") === 0) {
        print("No input file. Try -h for help.");
        return;
    }

    var fi = new QFileInfo(inFile);
    if (!fi.isAbsolute()) {
        inFile = RSettings.getLaunchPath() + QDir.separator + inFile;
        fi = new QFileInfo(inFile);
    }

    var outFile = getArgument(args, "-o", "-outfile");
    if (outFile!==undefined) {
        outFile = getAbsolutePathForArg(outFile);
    }
    else {
        print("No output file. Try -h for help.");
    }

    if (new QFileInfo(outFile).exists() && !testArgument(args, "-f", "-force")) {
        print("Output file exists already, not overwriting: ", outFile);
        print("Use -f to force overwrite");
        return;
    }

    // create new document (off screen):
    var doc = new RDocument(new RMemoryStorage(), new RSpatialIndexSimple());
    var di = new RDocumentInterface(doc);

    // import given file:
    if (di.importFile(inFile) != RDocumentInterface.IoErrorNoError) {
        di.destroy();
        print("Cannot import file:", inFile);
        return;
    }

    // add line to drawing (usine QCAD Simple API):
    startTransaction(di);
    addLine(0,0, 100,100);
    endTransaction()

    // export to given file (-o)
    if (!di.exportFile(outFile)) {
        di.destroy();
        print("Cannot export file:", outFile);
        return;
    }
    
    di.destroy();
}

if (typeof(including)=='undefined' || including===false) {
    main();
}

