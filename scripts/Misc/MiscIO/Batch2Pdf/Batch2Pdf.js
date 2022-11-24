include("scripts/File/Print/Print.js");
include("scripts/File/File.js");
include("scripts/File/NewFile/NewFile.js");
include("scripts/EAction.js");
include("scripts/library.js");
include("scripts/simple.js");

function Batch2Pdf(guiAction) {
    EAction.call(this, guiAction);
}

Batch2Pdf.prototype = new EAction();

Batch2Pdf.prototype.setPdfFileName = function () {
    var appWin = EAction.getMainWindow();
    var fileName = this.getDocument().getFileName();
    var initialFileName = QDir.homePath();
    if (fileName !== "") {
        var fileInfo = new QFileInfo(fileName);
        initialFileName = fileInfo.absoluteFilePath();
    }

    var filterStrings = ["PDF File (*.pdf)", "PDF/A-1B File (*.pdf)"];
    if (RSettings.getQtVersion() < 0x050A00) {
        filterStrings = ["PDF File (*.pdf)"];
    }

    filterStrings = translateFilterStrings(filterStrings);

    var ret = File.getSaveFileName(appWin, qsTr("Export to PDF"), initialFileName, filterStrings);

    return ret;
}


Batch2Pdf.prototype.toPdf = function () {

    var doc = this.getDocument();
    var keeperCurrentBlockId = doc.getCurrentBlockId();

    // Get all layout blocks Ids
    var blockIdArrAll = doc.queryAllLayoutBlocks();

    // Filter only unfrozen blocks
    var blockIdArr = [];
    for (i = 0; i < blockIdArrAll.length; i++) {
        if (!doc.isBlockFrozen(blockIdArrAll[i])) {
            blockIdArr.push(blockIdArrAll[i]);
        }
    }

    // Set order blocks as in BlockList widget
    blockIdArr = doc.sortBlocks(blockIdArr);

    var di = new RDocumentInterface(doc);
    var scene = new RGraphicsSceneQt(di);
    var view = new RGraphicsViewImage();
    view.setScene(scene);
    var p = new Print(undefined, doc, view);

    var fileName = this.setPdfFileName();
    if (isNull(fileName)) {
        return "No exported";
    }
    var printer = p.createPrinter(fileName[0]);
    var painter = new QPainter();

    painter.begin(printer);

    // Print blocks
    for (i = 0; i < blockIdArr.length; i++) {
        doc.setCurrentBlock(blockIdArr[i]);
        p.printCurrentBlock(printer, painter);
        if (i < blockIdArr.length - 1) {
            printer.newPage();
        }
    }

    painter.end();
    destr(printer);

    doc.setCurrentBlock(keeperCurrentBlockId);
    return "Exported to: " + fileName[0];
}


Batch2Pdf.prototype.beginEvent = function () {
    EAction.prototype.beginEvent.call(this);
    var msg = this.toPdf();
    // Send message to console
    EAction.handleUserMessage(qsTr(msg));
    this.terminate();
}
