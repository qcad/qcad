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

include("scripts/Widgets/LibraryBrowser/LibraryBrowser.js");
include("../../File/File.js");
include("../Block.js");
include("../BlockDialog.js");

function CreateLibraryItem(guiAction) {
    Block.call(this, guiAction);

    this.referencePoint = undefined;
}

CreateLibraryItem.prototype = new Block();

CreateLibraryItem.State = {
    SettingPosition : 0
};

CreateLibraryItem.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    this.setState(CreateLibraryItem.State.SettingPosition);
};

CreateLibraryItem.prototype.setState = function(state) {
    Block.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    this.setLeftMouseTip(qsTr("Reference Point"));
    this.setRightMouseTip(EAction.trCancel);

    EAction.showSnapTools();
};

CreateLibraryItem.prototype.coordinateEvent = function(event) {
    var pos = event.getModelPosition();
    this.getDocumentInterface().setRelativeZero(pos);
    this.referencePoint = pos;

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var itemStorage = new RMemoryStorage();
    var itemSpatialIndex = new RSpatialIndexNavel();
    var itemDocument = new RDocument(itemStorage, itemSpatialIndex);
    itemDocument.setUnit(document.getUnit());
    var itemDocumentInterface = new RDocumentInterface(itemDocument);
    itemDocumentInterface.setNotifyListeners(false);

    var op = new RCopyOperation(pos.getNegated(), document);
    itemDocumentInterface.applyOperation(op);

    var res = File.getSaveFileName(
        EAction.getMainWindow(),
        qsTr("Save library item as..."),
        RSettings.getLaunchPath() + "/libraries",
        RFileExporterRegistry.getFilterStrings());

    if (!isNull(res)) {
        itemDocumentInterface.exportFile(res[0], res[1]);
        LibraryBrowser.showDirectory(new QFileInfo(res[0]).absolutePath());
    }

    itemDocumentInterface.destroy();
    this.terminate();
};
