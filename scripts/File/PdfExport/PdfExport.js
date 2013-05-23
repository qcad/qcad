/*
 * Copyright (c) 2011 by RibbonSoft, GmbH. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * Licensees holding valid QCAD Professional Edition licenses 
 * may use this file in accordance with the QCAD License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, 
 * INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE.
 * 
 * See http://www.ribbonsoft.com for further details.
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
    if (!PrintPreview.isRunning()) {
        var action = this.getPrintPreviewAction();
        action.initialAction = "PdfExport";
        var di = this.getDocumentInterface();
        di.setCurrentAction(action);
        this.terminate();
    }
    else {
        PrintPreview.slotPdfExport();
        this.terminate();
    }
};

PdfExport.prototype.getPrintPreviewAction = function() {
    return new PrintPreview();
};

