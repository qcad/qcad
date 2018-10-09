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
function main() {

//! [main]
//! [include]
// include class Print:
include("scripts/File/Print/Print.js");
//! [include]

//! [init]
// init application name:
qApp.applicationName = "MyApplication";

//! [document]
var storage = new RMemoryStorage();
var spatialIndex = new RSpatialIndexSimple();
var document = new RDocument(storage, spatialIndex);
document.setUnit(RS.Millimeter);

// create document interface (needed for file export functionality):
var di = new RDocumentInterface(document);
//! [document]

//! [operation]
// create an operation:
var operation = new RAddObjectsOperation();

// corner point of the triangle::
var p1 = new RVector(0, 0);
var p2 = new RVector(10, 0);
var p3 = new RVector(5, Math.sin(RMath.deg2rad(60))*10);

// add line entity to operation:
operation.addObject(new RLineEntity(document, new RLineData(p1, p2)));
operation.addObject(new RLineEntity(document, new RLineData(p2, p3)));
operation.addObject(new RLineEntity(document, new RLineData(p3, p1)));

// apply operation to document:
operation.apply(document);
//! [operation]

//! [view]
var scene = new RGraphicsSceneQt(di);
var view = new RGraphicsViewImage();
view.setScene(scene);
//! [view]

//! [settings]
// set up page and paper settings as document variables:
var pageWidth = 210;
var pageHeight = 297;
var bb = document.getBoundingBox(true, true);
var scale = 10.0;

// paper unit:
document.setVariable("PageSettings/PaperUnit", RS.Millimeter);
// paper width:
document.setVariable("PageSettings/PaperWidth", pageWidth);
// paper height:
document.setVariable("PageSettings/PaperHeight", pageHeight);

// page orientation ("Portrait" | "Landscape"):
document.setVariable("PageSettings/PageOrientation", "Portrait");

// color mode ("FullColor" | "GrayScale" | "BlackWhite"):
document.setVariable("ColorSettings/ColorMode", "FullColor");

// background color:
document.setVariable("ColorSettings/BackgroundColor", new RColor("white"));

// drawing scale as string:
document.setVariable("PageSettings/Scale", "10:1");

// offset of drawing origin to lower left corner in drawing units:
document.setVariable("PageSettings/OffsetX", -(pageWidth/scale - bb.getWidth()) / 2);
document.setVariable("PageSettings/OffsetY", -(pageHeight/scale - bb.getHeight()) / 2);

// number of pages (rows / columns):
document.setVariable("MultiPageSettings/Rows", 1);
document.setVariable("MultiPageSettings/Columns", 1);

// switch on / off crop marks:
document.setVariable("MultiPageSettings/PrintCropMarks", false);

// switch on / off page tags:
document.setVariable("PageTagSettings/EnablePageTags", false);
//! [settings]

//! [export]
var print = new Print(undefined, document, view);
print.print("example.pdf");
//! [export]

//! [main]
}

if (typeof(including)=='undefined' || including===false) {
    main();
}
