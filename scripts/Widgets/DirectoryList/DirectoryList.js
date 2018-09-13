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
 * Fills the list widget "listWidgetName", a child of pageWidget with
 * directories (from where?)
 */
function DirectoryList(pageWidget, listWidgetName, fileDlgTitle) {
    this.doInit(pageWidget, listWidgetName, fileDlgTitle);
}

DirectoryList.prototype.doInit = function(pageWidget, listWidgetName, fileDlgTitle) {
    var widgets = getWidgets(pageWidget);
    var listWidget = widgets[listWidgetName];
    listWidget.dragDropMode = QAbstractItemView.InternalMove;

    listWidget.itemClicked.connect(this, function(item) {
        var btRemove = widgets["btRemove"];
        btRemove.enabled = true;
        this.checkButtonStatus(listWidget, widgets);
    });

    var btAdd = widgets["btAdd"];
    btAdd.clicked.connect(this, function() {
        var dir = QFileDialog.getExistingDirectory(this, fileDlgTitle);
        if (dir.length===0) {
            return;
        }

        var found = false;
        for ( var i = 0; i < listWidget.count; ++i) {
            var item = listWidget.item(i);
            if (item.text() == dir) {
                found = true;
                break;
            }
        }
        if (!found) {
            listWidget.addItem(dir);
        } else {
            var text = qsTr("The folder\n\"%1\"\nis already in the list.").arg(dir);
            var appWin = EAction.getMainWindow();
            QMessageBox.information(appWin, qsTr("Folder not added"), text);
        }
        this.checkButtonStatus(listWidget, widgets);
    });

    var btRemove = widgets["btRemove"];
    btRemove.enabled = false;
    btRemove.clicked.connect(this, function() {
        var currentRow = listWidget.currentRow;
        if (currentRow == -1) {
            this.checkButtonStatus(listWidget, widgets);
            return;
        }
        listWidget.model().removeRow(currentRow);
        if (listWidget.count == 0) {
            btRemove.enabled = false;
        }
        this.checkButtonStatus(listWidget, widgets);
    });

    var btUp = widgets["btUp"];
    btUp.clicked.connect(this, function() {
        var currentRow = listWidget.currentRow;
        if (currentRow == -1) {
            return;
        }
        var item = listWidget.takeItem(currentRow);
        if (isNull(item)) {
            return;
        }
        listWidget.insertItem(currentRow - 1, item);
        listWidget.setCurrentItem(item);
        this.checkButtonStatus(listWidget, widgets);
    });

    var btDown = widgets["btDown"];
    btDown.clicked.connect(this, function() {
        var currentRow = listWidget.currentRow;
        if (currentRow == -1) {
            return;
        }
        var item = listWidget.takeItem(currentRow);
        if (isNull(item)) {
            return;
        }

        listWidget.insertItem(currentRow + 1, item);
        listWidget.setCurrentItem(item);
        this.checkButtonStatus(listWidget, widgets);
    });
};

DirectoryList.prototype.checkButtonStatus = function(listWidget, widgets) {
    var currentRow = listWidget.currentRow;

    var btUp = widgets["btUp"];
    if (currentRow < 1) {
        btUp.enabled = false;
    } else {
        btUp.enabled = true;
    }

    var btDown = widgets["btDown"];
    if (currentRow == listWidget.count - 1) {
        btDown.enabled = false;
    } else {
        btDown.enabled = true;
    }
};
