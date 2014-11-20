/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
    sd.widget.visible = RSettings.getBoolValue("StatusBar/SelectionDisplay", true);
    EAction.addToStatusBar(sd.widget, 300);
};

SelectionDisplay.prototype.selectionChanged = function(documentInterface) {
    var selectionText = this.widget.findChild("SelectionText");

    if (isNull(documentInterface)) {
        selectionText.text = "";
        return;
    }

    // create one of the following text strings:
    // 1/n line(s) on layer "X"
    // n lines on m layers
    // n entities on layer "X"
    // n entities on m layers

    var doc = documentInterface.getDocument();
    var entities = doc.querySelectedEntities();
    var count = entities.length;
    if (count == 0) {
        selectionText.text = qsTr("No selected entities.");
        return;
    }

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
    
    var str;
    if (typesSingular.length == 1) {
        var typeStr = entityTypeToString(typesSingular[0], count>1);
        if (layers.length == 1 ) {
            str = qsTr("%1 %2 on Layer '%3'").arg(entities.length).arg(typeStr).arg(layers[0]);
        }
        else {
            str = qsTr("%1 %2 on %3 Layers").arg(entities.length).arg(typeStr).arg(layers.length);
        }
    } else {
        if (layers.length == 1 ) {
            str = qsTr("%1 Entities on Layer '%2'").arg(entities.length).arg(layers[0]);
        }
        else {
            str = qsTr("%1 Entities on %2 Layers").arg(entities.length).arg(layers.length);
        }
    }

    selectionText.text = qsTr("Selected entities:\n%1.").arg(str);
};
