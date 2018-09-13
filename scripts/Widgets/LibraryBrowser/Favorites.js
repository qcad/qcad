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

Favorites.checksum = "";

function Favorites() {
}

Favorites.settingsKey = "LibraryBrowser/Favorites";

/*
Favorites.updateChecksum = function() {
    var items = Favorites.getAllAsItems();
    var checkStr = "";
    for ( var i = 0; i < items.length; ++i) {
        var item = items[i];
        checkStr += item.getMd5Sum();
    }
    var checksum = QCryptographicHash.hash(new QByteArray(checkStr),
            QCryptographicHash.Md5);
    Favorites.checksum = serialize(checksum);
};

Favorites.hasChanged = function() {
    var oldChecksum = Favorites.checksum;
    Favorites.updateChecksum();
    if (oldChecksum != Favorites.checksum) {
        return true;
    }
    return false;
};
*/

Favorites.getAllAsItems = function() {
    Favorites.removeOrphans();

    var items = [];
    var fileList = Favorites.loadFromSettings();
    for (var i = 0; i < fileList.length; ++i) {
        var file = fileList[i];
        //var fi = new QFileInfo(file);
        var item = ItemPeer.getItemFromPath(file);
        if (isNull(item)) {
            // item doesn't exist in DB
            qWarning("Favorites.js:", "getAllAsItems(): item is null");
            continue;
        }
        items.push(item);
    }
    items.sort(ItemPeer.sort);
    return items;
};

/*
Favorites.countAll = function() {
    var pairList = Favorites.loadFromSettings();
    if (isNull(pairList)) {
        return 0;
    }
    return pairList.length;
};

*/

Favorites.isFavorite = function(fileName) {
    var fileList = Favorites.loadFromSettings();
    if (fileList.contains(fileName)) {
        return true;
    }
    return false;
};

/**
 * Adds the given file or directory to favorites.
 */
Favorites.add = function(fileName) {
    Favorites.removeOrphans();

    var fileList = Favorites.loadFromSettings();
    if (!fileList.contains(fileName)) {
        fileList.push(fileName);
        Favorites.saveToSettings(fileList);
    }

    var fi = new QFileInfo(fileName);
//    EAction.handleUserMessage(
//            qsTr("Item \"%1\" has been added to your favorites.".arg(fi
//                    .fileName())));
};

/**
 * Removes the given file or directory from favorites.
 */
Favorites.remove = function(fileName) {
    var fileList = Favorites.loadFromSettings();
    var newList = [];
    for ( var i = 0; i < fileList.length; ++i) {
        var file = fileList[i];
        if (file !== fileName) {
            newList.push(file);
        }
    }
    Favorites.saveToSettings(newList);

    var fi = new QFileInfo(fileName);
//    EAction.handleUserMessage(
//            qsTr("Item \"%1\" has been removed from your favorites.".arg(fi.fileName())));
};

/**
 * Removes non-existing files from favorites.
 */
Favorites.removeOrphans = function() {
    var fileList = Favorites.loadFromSettings();
    var cleanList = [];
    for ( var i = 0; i < fileList.length; ++i) {
        var file = fileList[i];
        if (QFile.exists(file)) {
            cleanList.push(file);
        }
    }
    Favorites.saveToSettings(cleanList);
};

Favorites.saveToSettings = function(fileList) {    
    RSettings.setValue(Favorites.settingsKey, fileList);
};

Favorites.loadFromSettings = function() {
    var fileList = RSettings.getValue(Favorites.settingsKey, new Array());
    if (isNull(fileList)) {
        return [];
    }
    return fileList;
};
