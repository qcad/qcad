// run with 
// qcad -autostart examples/scripts/createlayer.js

include("scripts/simple.js");

// create a document:
var doc = createOffScreenDocument();

// add layer "MyLayer" to the document
// red, continuous line type and line thickness of 0.25mm:
startTransaction(doc);
addLayer("MyLayer", "red", "CONTINUOUS", RLineweight.Weight025);
endTransaction();

// activate layer and add line to it:
startTransaction(doc);
doc.setCurrentLayer("MyLayer");
addLine(0,0, 100,100);
endTransaction();

// export the document to a DXF file:
var di = new RDocumentInterface(doc);
di.exportFile("qcad_createlayer.dxf");

