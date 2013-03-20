/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("../Block.js");
include("../BlockDialog.js");

/**
 * This action handles the user interaction to add a new block 
 * to the current drawing.
 */
function AddBlock(guiAction) {
    Block.call(this, guiAction);
}

AddBlock.prototype = new Block();

AddBlock.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var dlg = new BlockDialog(this.getDocument());
    this.block = dlg.show();
    if (isNull(this.block)) {
        this.terminate();
        return;
    }
    
    var operation = new RAddObjectOperation(this.block);
    var di = this.getDocumentInterface();
    di.applyOperation(operation);
    di.clearPreview();
    di.repaintViews();

    this.terminate();
};

AddBlock.prototype.getAddedBlock = function() {
    return this.block;
};
