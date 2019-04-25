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

include("scripts/File/File.js");

/**
 * Starts PDF Export and first the print preview if it is not already running.
 */
function PdfExport(guiAction) {
    File.call(this, guiAction);
}

PdfExport.prototype = new File();

PdfExport.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    include("scripts/File/PrintPreview/PrintPreview.js");

    var di = this.getDocumentInterface();
    if (!PrintPreview.isRunning()) {
        PrintPreview.start("PdfExport");
    }
    else {
        var pp = PrintPreview.getInstance();
        pp.slotPdfExport();
    }

    this.terminate();
};
