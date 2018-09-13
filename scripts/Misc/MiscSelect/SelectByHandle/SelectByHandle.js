/**
 * Copyright (c) 2011-2018 by RibbonSoft, GmbH. All rights reserved.
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

include("scripts/EAction.js");

/**
 * \class SelectByHandle
 * \ingroup ecma_misc_select
 *
 * \brief Selects an entity by its handle.
 */
function SelectByHandle(guiAction) {
    EAction.call(this, guiAction);
}

SelectByHandle.prototype = new EAction();
SelectByHandle.includeBasePath = includeBasePath;

SelectByHandle.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var dialog = WidgetFactory.createDialog(SelectByHandle.includeBasePath, "SelectByHandleDialog.ui");

    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
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
        EAction.handleUserMessage(qsTr("Object selected:") + " " + obj.getId());
    }
    else {
        EAction.handleUserMessage(qsTr("Object is not a drawing entity:") + " " + obj);
    }

    dialog.destroy();
    EAction.activateMainWindow();
    this.terminate();
};
