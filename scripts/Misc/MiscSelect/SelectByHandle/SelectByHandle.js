/*
 * Copyright (c) 2011-2013 by RibbonSoft, GmbH. All rights reserved.
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

include("scripts/EAction.js");

/**
 * This action draws lines in different colors.
 */
function SelectByHandle(guiAction) {
    EAction.call(this, guiAction);
}

SelectByHandle.prototype = new EAction();
SelectByHandle.includeBasePath = includeBasePath;

/**
 * Changes the color of all white layers to black and terminates.
 */
SelectByHandle.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var dialog = WidgetFactory.createDialog(SelectByHandle.includeBasePath, "SelectByHandleDialog.ui");

    if (!dialog.exec()) {
        dialog.destroy();
        this.terminate();
        return;
    }

    var handleEdit = dialog.findChild("Handle");

    var handle = handleEdit.text;

    var di = this.getDocumentInterface();
    var document = this.getDocument();

    var obj = document.queryObjectByHandle(parseInt(handle, 16));

    if (isEntity(obj)) {
        di.selectEntity(obj.getId());
        EAction.handleUserMessage(qsTr("Object selected: ") + obj.getId());
    }
    else {
        EAction.handleUserMessage(qsTr("Object is not an entity: ") + obj);
    }

    dialog.destroy();
    this.terminate();
};
