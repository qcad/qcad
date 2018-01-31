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

include("db/ItemPeer.js");

/**
 * File icon provider for the directory tree in the file system tab.
 */
function FileIconProvider() {
    QFileIconProvider.call(this);
}

FileIconProvider.prototype = new QFileIconProvider();
FileIconProvider.includeBasePath = includeBasePath;

FileIconProvider.prototype.toString = function() {
    return "FileIconProvider";
};

FileIconProvider.prototype.icon = function(fi) {
    //qDebug("FileIconProvider.prototype.icon");
    if (!isOfType(fi, QFileInfo)) {
        return this.icon_ori(fi);
    }

    if (!fi.isDir()) {
        return this.icon_ori(fi);
    }

    var item = ItemPeer.getItemFromPath(fi.absoluteFilePath(), undefined);
    if (isNull(item)) {
        return this.icon_ori(fi);
    }

    var icon = item.icon;
    if (isNull(icon)) {
        icon = new QIcon(FileIconProvider.includeBasePath + "/Open.svg");
    }

    return item.getIcon(true);
};

// TODO refactor
FileIconProvider.prototype.icon_ori = function(fi) {
    // prevents recursion:
    var s = FileIconProvider.prototype.icon;
    FileIconProvider.prototype.icon = undefined;
    var r = QFileIconProvider.prototype.icon.call(this, fi);
    FileIconProvider.prototype.icon = s;
};
