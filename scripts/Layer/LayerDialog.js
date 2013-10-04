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

include("../WidgetFactory.js");

/**
 * Creates a dialog to edit the attributes of a layer.
 *
 * \param document RDocument the layer is in.
 * \param block RLayer object to edit or undefined to show a dialog for a new layer.
 */
function LayerDialog(document, layer) {
    this.dialog = null;
    this.document = document;
    this.layer = layer;
}

LayerDialog.prototype.show = function() {
    var lt;
    
    this.dialog = WidgetFactory.createDialog("scripts/Layer", "LayerDialog.ui");
    //this.dialog.windowIcon = new QIcon("scripts/Layer/EditLayer/EditLayer.svg");

    var widgets = getWidgets(this.dialog);
    var layerName = widgets["LayerName"];
    layerName.selectAll();
    var rx = new RegExp("[^<>/\\\\\":;\?\*|,=`]{1,255}");
    var validator = new QRegExpValidator(rx, layerName);
    layerName.setValidator(validator);
    layerName.textChanged.connect(this, "validate");
    var color = widgets["Color"];
    var lineweight = widgets["Lineweight"];
    var linetype = widgets["Linetype"];

    if (!isNull(this.layer)) {
        layerName.text = this.layer.getName();
        if (layerName.text == "0") {
            layerName.enabled = false;
        }
        color.setColor(this.layer.getColor());
        lineweight.setLineweight(this.layer.getLineweight());
        var ltP = this.document.queryLinetype(this.layer.getLinetypeId());
        lt = ltP.data();
        linetype.setLinetype(lt);
    }

    this.dialog.show();

    var c = 0;
    while (!this.validate()) {
        ++c;
        layerName.text = "layer " + c;
    }

    if (this.dialog.exec()) {
        var text = layerName.text.trim();
        var clr = color.getColor();
        var lw = lineweight.getLineweight();
        lt = linetype.getLinetype();
        var ltId = this.document.getLinetypeId(lt.getName());
        if (!isNull(this.layer)) {
            this.layer.setName(text);
            this.layer.setColor(clr);
            this.layer.setLinetypeId(ltId);
            this.layer.setLineweight(lw);
            return this.layer;
        }
        this.dialog.setAttribute(Qt.WA_DeleteOnClose);
        this.dialog.close();
        var layer = new RLayer(this.document, text, false, false,
                clr, ltId, lw);
        return layer;
    }
};

/**
 * Layer name validation.
 */
LayerDialog.prototype.validate = function() {
    var widgets = getWidgets(this.dialog);

    var leLayerName = widgets["LayerName"];
    var message = widgets["Message"];
    var validator = leLayerName.validator();
    var pos = 0;
    var acceptable = true;
    message.clear();
    if (validator.validate(leLayerName.text, pos) != QValidator.Acceptable) {
        message.text = "<font color='red'>" + qsTr("Layer name is empty.") + "</font>";
        acceptable = false;
    }

    // layer exists: check if name exists:
    if (this.document.hasLayer(leLayerName.text)) {
        // error if we're creating a new layer and the layer name is taken or
        // we're trying to rename a layer to an existing name
        if (isNull(this.layer) ||
            this.layer.getName().toLowerCase() != leLayerName.text.toLowerCase()) {

            message.text = "<font color='red'>" + qsTr("Layer already exists.") + "</font>";
            acceptable = false;
        }
    }
    widgets["ButtonBox"].button(QDialogButtonBox.Ok).enabled = acceptable;
    return acceptable;
};
