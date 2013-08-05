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

include("../../WidgetFactory.js");

function SelectionDisplay() {
    this.widget = undefined;
}

SelectionDisplay.init = function(basePath) {
    var sd = new SelectionDisplay();
    sd.widget = WidgetFactory.createWidget(basePath, "SelectionDisplay.ui");
    var selectionText = sd.widget.findChild("SelectionText");
    selectionText.font = RSettings.getStatusBarFont();
    var appWin = EAction.getMainWindow();
    var adapter = new RSelectionListenerAdapter();
    appWin.addSelectionListener(adapter);
    adapter.selectionChanged.connect(sd, "selectionChanged");
    EAction.addToStatusBar(sd.widget, 300);
};

SelectionDisplay.prototype.selectionChanged = function(documentInterface) {
    var selectionText = this.widget.findChild("SelectionText");

    if (isNull(documentInterface)) {
        selectionText.text = "";
        return;
    }

    // create one of the following text strings:
    // 1 line on layer "3"
    // x lines on layer "3"
    // x mixed entities on layer "3"
    // x mixed entities on y layers

    var doc = documentInterface.getDocument();
    var entities = doc.querySelectedEntities();
    var count = entities.length;
    if (count == 0) {
        selectionText.text = qsTr("No selected entities.");
        return;
    }

    var str = entities.length + " ";
    var typesSingular = [];
    var layers = [];
    var pt = new RPropertyTypeId(0);
    for (var i = 0; i < count; ++i) {
        var entityId = entities[i];
        if (entityId == undefined || entityId == "") {
            continue;
        }
        var entity = doc.queryEntity(entityId);
        typesSingular.push(entity.getType());
        layers.push(entity.getLayerName());
    }
    typesSingular = typesSingular.unique();
    layers = layers.unique();
    
    if (typesSingular.length == 1) {
        str += entityTypeToString(typesSingular[0], count>1);
    } else {
        str += qsTr("Entities");
    }
    str += " " + qsTr("on") + " ";
    if (layers.length == 1 ) {
        str += qsTr("Layer '%1'").arg(layers[0]);
    } else {
        str += qsTr("%1 Layers").arg(layers.length);
    }

    selectionText.text = qsTr("Selected entities:\n%1.").arg(str);
};
