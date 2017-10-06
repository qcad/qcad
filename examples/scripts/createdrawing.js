// run with 
// qcad -autostart examples/scripts/createdrawing.js

include("scripts/simple.js");

// create a document:
var doc = createOffScreenDocument();

// add something to the document:
startTransaction(doc);
addLine(0,0, 100,100);
endTransaction();

// export the document to a DXF file:
var di = new RDocumentInterface(doc);
di.exportFile("qcad_createdrawing.dxf");
