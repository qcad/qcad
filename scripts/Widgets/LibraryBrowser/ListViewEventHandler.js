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

/**
 * Event handler for drag and drop, clicks, double-click.
 *
 * \param listView List view of directory and file items (bottom part of
 * file system tab)
 * \param treeView Tree view of directory items (top part of file system tab).
 */
function ListViewEventHandler(listView, treeView) {
    this.listView = listView;
    this.treeView = treeView;
}

/**
 * Handle double-clicks on directory items in list view (bottom).
 */
ListViewEventHandler.prototype.doubleClicked = function(file) {
    //var listModel = this.listView.model();
    //var file = listModel.data(index, Qt.UserRole);
    var fi = new QFileInfo(file);

    // double click on dir opens dir:
    if (fi.isDir()) {
        LibraryBrowser.showDirectory(file);
    }

    // double click on file inserts file:
    else if (fi.isFile()) {
        LibraryBrowser.insertItem(this.listView);
    }
};

/**
 * Implements dragging.
 */
ListViewEventHandler.prototype.mouseMoveEvent = function(evt) {
    //qDebug("mousemove")
    if (!(evt.buttons() & Qt.LeftButton)) {
        return;
    }

    var index = this.listView.indexAt(evt.pos());
    if (!index.isValid()) {
        return;
    }
    var model = this.listView.model();
    var file = model.data(index, Qt.UserRole);

    // directories cannot be dragged anywhere:
    if (new QFileInfo(file).isDir()) {
        return;
    }
    
    var p = evt.pos();
    p.operator_subtract_assign(this.dragStartPosition);
    var delta = p;
    if (delta.manhattanLength() < qApp.startDragDistance*2) {
        return;
    }
    
    var fileUrl = QUrl.fromLocalFile(file);
    var urlList = [];
    urlList.push(fileUrl);
    
    var id = model.data(index, Qt.UserRole + 1);
    var item = ItemPeer.doSelectById(id);
    if (isNull(item)) {
        // when starting a drag and drop process in the middle of
        // renaming a file, the item returned may be undefined
        return;
    }
    
    var mimeData = new QMimeData();
    mimeData.setUrls(urlList);
    mimeData.setImageData(item.icon);
    
    var drag = new QDrag(this.listView);
    drag.setMimeData(mimeData);
    drag.setPixmap(item.icon);
    drag.setHotSpot(new QPoint(-16, -16));
    drag.exec(Qt.CopyAction);
};

/**
 * Implements dragging.
 */
ListViewEventHandler.prototype.mousePressEvent = function(evt) {
    if (evt.button() === Qt.LeftButton) {
        this.dragStartPosition = evt.pos();
    }
};
