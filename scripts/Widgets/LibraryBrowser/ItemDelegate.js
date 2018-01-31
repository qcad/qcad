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

function ItemDelegate(parent) {
    QItemDelegate.call(this, parent);
}

ItemDelegate.prototype = new QItemDelegate();

ItemDelegate.prototype.toString = function() {
    return "ItemDelegate()";
};

ItemDelegate.prototype.createEditor = function(parent, option, index) {
    var le = new QLineEdit(parent);
    le.styleSheet = "border: 1px solid grey;";
    return le;
};

ItemDelegate.prototype.setModelData = function(editor, model, index) {
    var qsItem = model.item(index.row());
    // update RDF
    var filePath = qsItem.data(Qt.UserRole);
    var rdfFi = Rdf.getRdfFileInfo(filePath);
    var rdf = new Rdf(rdfFi);
    if (!rdf.isValid()) {
        // no RDF present, create one
        rdf.createDomDocument(rdfFi);
        rdf.save();
        // reload RDF
        rdfFi = Rdf.getRdfFileInfo(filePath);
        rdf = new Rdf(rdfFi);
    }
    var localeName = RSettings.getLocale();
    var titleElem = rdf.getTitleElement(localeName);
    if (!isNull(titleElem)) {
        titleElem.setAttribute("rs:resource", editor.text);
    }
    rdf.save();
    // update DB
    var itemId = qsItem.data(Qt.UserRole + 1);
    var item = ItemPeer.doSelectById(itemId);
    item.title = editor.text;
    item.save();
    qsItem.setText(editor.text);

    LibraryBrowser.updateCompleter();

    // var newFileName = editor.text;
    // var qsItem = model.item(index.row());
    // var filePath = qsItem.data(Qt.UserRole);
    // var absolutePath = new QFileInfo(filePath).absolutePath();
    // var ext = new QFileInfo(filePath).suffix();
    // var newFilePath = absolutePath + QDir.separator + newFileName + "." +
    // ext;
    // var itemId = qsItem.data(Qt.UserRole + 1);
    // ItemPeer.rename(filePath, newFilePath, itemId, qsItem);
    //    
    // LibraryBrowser.updateCompleter();

    // var btFind = LibraryBrowser.formWidget.findChild("btFind");
    // btFind.enabled = true;
};

// provides "basename-only" editor (doesn't allow editing the suffix)

// ItemDelegate.prototype.createEditor = function(parent, option, index) {
// var le = new QLineEdit(parent);
// le.styleSheet = "border: 1px solid grey;";
// var done = false;
// le.selectionChanged.connect(function() {
// if (le.done) {
// return;
// }
// le.blockSignals(true);
// var fm = new QFontMetrics(le.font);
// var w = fm.width(le.text);
// var maxw = le.parent().width - le.pos.x() - 2;
// var cw = w + 8 <= maxw ? w + 8 : maxw;
// le.setMinimumSize(cw, 20);
// var mode = RSettings.getValue("LibraryBrowser/ViewMode");
// if (mode == "List") {
// le.setMaximumSize(cw, 20);
// // var iconSize = RSettings.getValue("LibraryBrowser/IconSize");
// var iconSize = parent.parent().iconSize.width();
// le.move(le.pos.x() + 1, le.pos.y() + iconSize / 2
// - (fm.height() / 2) - 2);
// }
// var t = le.text;
// var p = t.lastIndexOf(".");
// le.setSelection(0, p);
// le.done = true;
// le.blockSignals(false);
// });
// return le;
// }
