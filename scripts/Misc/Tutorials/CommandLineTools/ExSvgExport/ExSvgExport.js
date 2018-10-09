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
// include class SvgExporterPG:
include("scripts/Pro/ImportExport/SvgExporter/SvgExporterPG.js");
//! [include]

//! [init]
// init application name:
qApp.applicationName = "MyApplication";

//! [document]
var storage = new RMemoryStorage();
var spatialIndex = new RSpatialIndexSimple();
var document = new RDocument(storage, spatialIndex);
document.setUnit(RS.Millimeter);
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

//! [export]
var exporter = new SvgExporterPG(document, { "scale": "10:1"});
exporter.exportFile("example.svg");
//! [export]

//! [main]
}

if (typeof(including)=='undefined' || including===false) {
    main();
}
