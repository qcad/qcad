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

include("scripts/ImportExport/SvgImporter/SvgImporter.js");
include("scripts/DbConnection.js");
include("../Favorites.js");
include("Table.js");
include("ItemTag.js");
include("TagPeer.js");

Item.tableName = "item";

Item.Type = {
    Directory : 0,
    File : 1
};

Item.prototype = new Table();

Item.prototype.getTableName = function() {
    return Item.tableName;
};

function Item(parent_id, name, path, type, last_mod, last_mod_rdf, size, size_rdf) {
    Table.call(this);
    this.id = undefined;
    this.parent_id = parent_id;
    this.name = name;
    this.path = path;
    this.type = type;
    this.last_mod = last_mod;
    this.last_mod_rdf = last_mod_rdf;
    this.size = size;
    this.size_rdf = size_rdf;
    this.icon = undefined;
}

/**
 * \return The title tags of this item if available, the file base name otherwise.
 */
Item.prototype.getTitles = function(localeName) {
    var titles = ItemPeer.getItemTagValues(this.id, "title", localeName);
    if (isNull(titles) || titles.length===0) {
        titles = [ new QFileInfo(this.name).completeBaseName() ];
    }
    return titles;
};

/**
 * \return The license tags of this item if available.
 */
Item.prototype.getLicenses = function() {
    var licenses = ItemPeer.getItemTagValues(this.id, "license");
    if (isNull(licenses) || licenses.length===0) {
        licenses = [];
    }
    return licenses;
};

/**
 * \return The attribute-as tags of this item if available.
 */
Item.prototype.getAttributeAs = function() {
    var attributeAs = ItemPeer.getItemTagValues(this.id, "attribute-as");
    if (isNull(attributeAs) || attributeAs.length===0) {
        attributeAs = [];
    }
    return attributeAs;
};

/**
 * \return The creator tags of this item if available.
 */
Item.prototype.getCreators = function(localeName) {
    var creators = ItemPeer.getItemTagValues(this.id, "creator");
    if (isNull(creators) || creators.length===0) {
        creators = [];
    }
    return creators;
};

Item.prototype.save = function() {
    if (isNull(this.id)) {
        ItemPeer.doInsert(this);
    } else {
        ItemPeer.doUpdate(this);
    }
};

/**
 * \return Item path without file name.
 */
Item.prototype.getPath = function() {
    // item is a source:
    if (isNull(this.parent_id)) {
        return "";
    }

    var parent = ItemPeer.doSelectById(this.parent_id, ["name, parent_id"]);
    return parent.getFilePath();
};

/**
 * \return Item path with file name.
 */
Item.prototype.getFilePath = function() {
    if (isNull(this.parent_id)) {
        return this.name;
    }

    var parent = ItemPeer.doSelectById(this.parent_id, ["name, parent_id"]);
    return parent.getFilePath() + QDir.separator + this.name;
};

/**
 * \return File path of RDF file that belongs to this item.
 */
Item.prototype.getRdfFilePath = function() {
    var filePath = this.getFilePath();
    var fi = new QFileInfo(filePath);
    return fi.absolutePath() + QDir.separator + fi.completeBaseName() + ".rdf";
};

/**
 * \param small True: generate small icon for tree view,
 * false: large icon for list view.
 * \param noFavoritesMark True: suppress favorites mark (used in favorites
 * tab.
 */
Item.prototype.getIcon = function(small, regenerate, noFavoritesMark) {
    var fi = new QFileInfo(this.getFilePath());
    var evalStr, lb;
    
    if (isNull(regenerate)) {
        regenerate = false;
    }
    if (isNull(noFavoritesMark)) {
        noFavoritesMark = false;
    }

    var iconSize = RSettings.getIntValue("LibraryBrowser/IconSize", 64);

    // directory item:
    if (this.type===Item.Type.Directory || fi.isDir()) {
        var iconFile = fi.absoluteFilePath() + QDir.separator
            + "_META" + QDir.separator + "icon.svg";
        var iconFi = new QFileInfo(iconFile);
        if (!iconFi.exists()) {
            iconFile = LibraryBrowser.includeBasePath + QDir.separator + "DefaultDirectoryIcon.svg";
        }

        var pm = new QPixmap(iconFile);
        this.icon = pm.scaled(iconSize, iconSize);
        this.last_mod = LibraryBrowser.getLastMod(fi);
        this.save();
        return this.markIcon(this.icon, small, !noFavoritesMark && this.isFavorite(), false, false);
    }

    // return cached icon if file has not changed, icon size has 
    // not changed and regeneration is not forced:
    if (this.type === Item.Type.File
            && !isNull(this.icon)
            && LibraryBrowser.getLastMod(fi) === this.last_mod
            && iconSize === this.icon.width()
            && regenerate === false) {

        return this.markIcon(this.icon, small, !noFavoritesMark && this.isFavorite(), this.isScript(), false);
    }

    // generate icon:
    var ms = new RMemoryStorage();
    var si = new RSpatialIndexSimple();
    var doc = new RDocument(ms, si);
    var di = new RDocumentInterface(doc);
    di.setNotifyListeners(false);
    var scene = new RGraphicsSceneQt(di);
    var view = new RGraphicsViewImage();
    view.setAntialiasing(true);
    view.setPaintOrigin(false);
    if (RSettings.hasDarkGuiBackground() ||
        RSettings.getBoolValue("LibraryBrowser/DarkIconBackground", false)) {
        view.setBackgroundColor(new QColor(Qt.black));
    }
    else {
        view.setBackgroundColor(new QColor(Qt.white));
    }
    view.setColorCorrectionOverride(true);
    view.setMargin(2);
    view.setScene(scene);
    view.resizeImage(iconSize, iconSize);

    if (this.isScript()) {
        try {
            include(fi.absoluteFilePath());

            var className = this.getScriptClassName();

            // call init()
            if (!isNull(global[className]) && isFunction(global[className].init)) {
                global[className].init(undefined);
            }

            // call generatePreview
            var failed = false;
            var operation = undefined;

            if (!isNull(global[className]) && isFunction(global[className].generatePreview)) {
                operation = global[className].generatePreview(di, iconSize);
            }
            else {
                failed = true;
            }

            // no preview available for script item:
            if (failed) {
                this.icon = QPixmap.fromImage(view.getBuffer());
                this.save();
                return this.markIcon(undefined, small, !noFavoritesMark && this.isFavorite(), true, true);
            }
            di.applyOperation(operation);
            di.regenerateScenes();
            di.autoZoom();
        } catch (e) {
            qWarning("Item.js:", "getIcon(): exception:", e);
        }

        this.icon = QPixmap.fromImage(view.getBuffer());
        this.save();

        return this.markIcon(this.icon, small, !noFavoritesMark && this.isFavorite(), true, false);
    }

    // not a script, import the file (DXF,DWG,SVG):
    if (di.importFile(fi.filePath()) != RDocumentInterface.IoErrorNoError) {
        return this.markIcon(undefined, small, !noFavoritesMark && this.isFavorite(), false, false);
    }

    di.regenerateScenes();
    di.autoZoom();
    this.icon = QPixmap.fromImage(view.getBuffer());
    this.last_mod = LibraryBrowser.getLastMod(fi);
    this.save();
    di.destroy();

    return this.markIcon(this.icon, small, !noFavoritesMark && this.isFavorite(), false, false);
};

/**
 * Marks the given icon with futher information (favorite star, script wheel, error).
 * \param icon QPixmap or undefined.
 * \param favorite True: mark as favorite.
 * \param script True: mark as script.
 * \param failed True: mark as error.
 * \return New QIcon.
 */
Item.prototype.markIcon = function(icon, small, favorite, script, failed) {
    var iconSize = RSettings.getIntValue("LibraryBrowser/IconSize", 64);
    var pixmap = icon;
    if (isNull(pixmap)) {
        pixmap = new QPixmap(iconSize, iconSize);
        pixmap.fill();
    }

    if (!favorite && !script && !failed) {
        return new QIcon(pixmap);
    }

    var p = new QPainter();
    p.begin(pixmap);

    var pm;
    var s = iconSize / (small ? 1.5 : 3);;
    if (favorite) {
        pm = new QPixmap(LibraryBrowser.includeBasePath + "/Favorite.svg");
        pm = pm.scaled(s, s);
        p.drawPixmap(0, 0, pm);
    }

    if (script) {
        pm = new QPixmap(LibraryBrowser.includeBasePath + "/JsFile.svg");
        pm = pm.scaled(s, s);
        p.drawPixmap(iconSize-s, iconSize-s, pm);
    }

    if (failed) {
        pm = new QPixmap(LibraryBrowser.includeBasePath + "/Error.svg");
        pm = pm.scaled(s, s);
        p.drawPixmap(iconSize-s, 0, pm);
    }

    p.end();
    return new QIcon(pixmap);
};

Item.prototype.isFavorite = function() {
    return Favorites.isFavorite(this.getFilePath());
};

Item.prototype.isScript = function() {
    return new QFileInfo(this.name).suffix().toLowerCase() == "js";
};

Item.prototype.getScriptClassName = function() {
    return new QFileInfo(this.name).completeBaseName();
};
