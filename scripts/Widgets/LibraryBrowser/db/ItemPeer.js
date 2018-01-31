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

include("Item.js");

function ItemPeer() {
}

ItemPeer.createTable = function(drop) {
    if (isNull(drop)) {
        drop = false;
    }

    var con = new DbConnection(Table.connectionName);
    if (drop) {
        con.execQuery("DROP TABLE IF EXISTS " + Item.tableName);
    }
    con.execQuery(
        "CREATE TABLE IF NOT EXISTS " + Item.tableName
        + " ("
        + "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        + "parent_id INTEGER,"
        + "type INTEGER NOT NULL," // 0: file, 1: directory
        + "name VARCHAR,"          // depending on type: source path, file name, directory name
        + "path VARCHAR,"          // path
        + "last_mod VARCHAR,"      // last modification
        + "last_mod_rdf VARCHAR,"  // last modification of RDF
        + "size,"                  // last file size
        + "size_rdf,"              // last file size of RDF
        + "icon BLOB"              // the icon as a QPixmap
        + ")");
    con.execQuery("CREATE UNIQUE INDEX IF NOT EXISTS item_name_parent_id ON " + Item.tableName + "(name, parent_id)");
    con.execQuery("CREATE INDEX IF NOT EXISTS item_name ON " + Item.tableName + "(name)");
    //con.execQuery("CREATE INDEX IF NOT EXISTS item_path ON " + Item.tableName + "(path)");
    con.execQuery("CREATE INDEX IF NOT EXISTS item_id_parent_id_type ON " + Item.tableName + "(id, parent_id, type)");
};

/**
 * \return Available sources in DB as array of Item objects.
 * \param fields Fields to query from DB or undefined to query all fields.
 */
ItemPeer.getSourceItems = function(fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }

    var con = new DbConnection(Table.connectionName);
    var query = con.execQuery("SELECT " + fields.join() + " FROM " + Item.tableName + " WHERE parent_id is NULL");
    return ItemPeer.createFromQuery(query);
};

/**
 * \return The tag values of the tags in the given category
 * of the item with the given ID and all ancestors if available,
 * undefined otherwise.
 *
 * \param id Item ID.
 * \param categoryName Tag category name. E.g. "title"
 * \param localeName Locale name e.g. "en".
 */
ItemPeer.getItemTagValues = function(id, categoryName, localeName) {
    if (isNull(localeName)) {
        localeName = RSettings.getLocale();
    }

    var locale = LocalePeer.doSelectOrInsertByName(localeName);
    var localeNeutral = LocalePeer.doSelectNeutral();

    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT text"
        + " FROM item_tag,tag,tag_category"
        + " WHERE tag.id=item_tag.tag_id"
        + " AND tag.category_id=tag_category.id"
        + " AND tag_category.name=:category_name"
        + " AND item_tag.item_id=:id"
        + " AND (tag.locale_id=:locale_id OR tag.locale_id=:locale_neutral_id)");
    query.bindValue(":category_name", categoryName);
    query.bindValue(":id", id);
    query.bindValue(":locale_id", locale.id);
    query.bindValue(":locale_neutral_id", localeNeutral.id);
    if (!con.execQuery(query)) {
        qWarning("ItemPeer.getItemTagValues: cannot get tag for item: ", id);
        return undefined;
    }

    var ret = [];
    while (query.next()) {
        ret.push(query.value(0));
    }

    // add values from parent items (not for titles which are not inherited):
    if (categoryName!=="title") {
        var item = ItemPeer.doSelectById(id, ["parent_id"]);
        if (!isNull(item.parent_id)) {
            ret = ret.concat(ItemPeer.getItemTagValues(item.parent_id, categoryName, localeName));
        }
    }

    return ret;
};


/**
 * \return Item with the given absolute path or relative path or name and
 * parent ID.
 *
 * \param path Absolute path of the item or relative path  if parentId is given.
 * \param parentId ID of parent item or undefined if the given path is absolute.
 * \param fields Fields to query from DB or undefined to query all fields.
 */
ItemPeer.getItemFromPath = function(path, parentId, fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }

    var i;
    path = QDir.toNativeSeparators(path);

    if (isNull(parentId)) {
        // make sure we query at least id and name:
        fields.push("id", "name");
        fields = fields.unique();
        var sources = ItemPeer.getSourceItems(fields);

        for (i=0; i<sources.length; i++) {
            var source = sources[i];
            var sourcePath = new QFileInfo(source.name).absoluteFilePath();
            sourcePath = QDir.toNativeSeparators(sourcePath);

            // path is a source item:
            if (path === sourcePath) {
                return source;
            }

            if (path.startsWith(sourcePath + QDir.separator)) {
                var sourceDir = new QDir(sourcePath);
                var relPath = sourceDir.relativeFilePath(path);
                return ItemPeer.getItemFromPath(relPath, source.id, fields);
            }
        }

        // source not found in DB:
        return undefined;
    }

    var dirList = path.split(QDir.separator);
    var itemId = parentId;
    for (i=0; i<dirList.length; ++i) {
        var item = ItemPeer.doSelectByNameAndParentId(dirList[i], itemId, fields);
        if (isNull(item)) {
            return undefined;
        }
        itemId = item.id;
    }
    return item;
};

ItemPeer.doInsert = function(item) {
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "INSERT INTO item"
            + " (parent_id, type, name, path, last_mod, last_mod_rdf, size, size_rdf, icon)"
            + " VALUES (:parent_id, :type, :name, :path, :last_mod, :last_mod_rdf, :size, :size_rdf, :icon)");
    query.bindValue(":parent_id", item.parent_id);
    query.bindValue(":type", item.type);
    query.bindValue(":name", item.name);
    query.bindValue(":path", item.path);
    query.bindValue(":last_mod", item.last_mod);
    query.bindValue(":last_mod_rdf", item.last_mod_rdf);
    query.bindValue(":size", item.size);
    query.bindValue(":size_rdf", item.size_rdf);
    query.bindValue(":icon", DbConnection.pixmapToByteArray(item.icon));

    if (!con.execQuery(query)) {
        qWarning("ItemPeer.doInsert: cannot insert item:", item);
        return;
    }
        
    item.id = query.lastInsertId();

    //qDebug("ItemPeer.doInsert: ", item);
};


ItemPeer.doUpdateRdf = function(id, lastModRdf, sizeRdf) {
    var con = new DbConnection(Table.connectionName);
    var sql = "UPDATE " + Item.tableName
            + " SET last_mod_rdf=:last_mod_rdf, size_rdf=:size_rdf"
            + " WHERE id=:id";
    var query = con.prepareQuery(sql);
    query.bindValue(":last_mod_rdf", lastModRdf);
    query.bindValue(":size_rdf", sizeRdf);
    query.bindValue(":id", id);
    con.execQuery(query);
};

/**
 * Updates the given existing item in the DB.
 */
ItemPeer.doUpdate = function(item) {
    var con = new DbConnection(Table.connectionName);
    var sql = "UPDATE " + Item.tableName
            + " SET parent_id=:parent_id, type=:type, name=:name, "
            + "   last_mod=:last_mod, last_mod_rdf=:last_mod_rdf, "
            + "   size=:size, size_rdf=:size_rdf, icon=:icon"
            + " WHERE id=:id";
    var query = con.prepareQuery(sql);
    query.bindValue(":parent_id", item.parent_id);
    query.bindValue(":type", item.type);
    query.bindValue(":name", item.name);
    query.bindValue(":last_mod", item.last_mod);
    query.bindValue(":last_mod_rdf", item.last_mod_rdf);
    query.bindValue(":size", item.size);
    query.bindValue(":size_rdf", item.size_rdf);
    query.bindValue(":icon", DbConnection.pixmapToByteArray(item.icon));
    query.bindValue(":id", item.id);
    if (!con.execQuery(query)) {
        qWarning("ItemPeer.js:", "doUpdate(): cannot update item:", item);
        return;
    }
};

/**
 * \return Item with the given ID.
 * \param fields Fields to query from DB or undefined to query all fields.
 */
ItemPeer.doSelectById = function(id, fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }
    var con = new DbConnection(Table.connectionName);
    var sql =
        "SELECT " + fields.join()
        + " FROM " + Item.tableName
        + " WHERE id=:id";
    var query = con.prepareQuery(sql);
    query.bindValue(":id", id);
    con.execQuery(query);
    var items = ItemPeer.createFromQuery(query);
    return items[0];
};

/**
 * \return All items with the given IDs, sorted by directory / file, name.
 * \param ids Array of item IDs.
 * \param fields Fields to query from DB or undefined to query all fields.
 */
ItemPeer.doSelectByIds = function(ids, fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }
    else {
        // type and name are always needed for sorting
        if (!fields.contains("type")) {
            fields.push("type");
        }
        if (!fields.contains("name")) {
            fields.push("name");
        }
    }

    var sqlIds = ids.join(",");
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT " + fields.join()
        + " FROM " + Item.tableName
        + " WHERE id IN ( " + sqlIds + " )");
    con.execQuery(query);
    var items = ItemPeer.createFromQuery(query);
    items.sort(ItemPeer.sort);
    return items;
};

/**
 * \return IDs of all ancestor items.
 */
ItemPeer.getAncestorIds = function(itemId) {
    var item = ItemPeer.doSelectById(itemId, ["parent_id"]);
    if (!isNull(item.parent_id)) {
        var ret = [ item.parent_id ];
        return ret.concat(ItemPeer.getAncestorIds(item.parent_id));
    }
    return [];
};

/**
 * \return Array of item IDs that match the given tag IDs and search text.
 * \param tagIds Array of tag IDs.
 * \param text Search text.
 * \param onlyFiles True: return only IDs of file items (directory matches
 *   return all file items in them recursively). Default.
 *   False: return matching directory item IDs without searching for descendants.
 */
ItemPeer.getIdsByTagIdsAndText = function(tagIds, text) {

    var matchingItemIds = undefined;
    var i;
    var tagId;
    var itemIds;

    // tags are reducing the potential result set:
    for (i=0; i<tagIds.length; i++) {
        tagId = tagIds[i];

        itemIds = ItemPeer.getIdsByTagIdsRecursive([tagId]);

        if (isNull(matchingItemIds)) {
            matchingItemIds = itemIds;
        }
        else {
            matchingItemIds.sortNumerical();
            itemIds.sortNumerical();
            matchingItemIds = Array.intersect(matchingItemIds, itemIds);
        }
    }

    if (isNull(text) || text.length===0) {
        if (isNull(matchingItemIds)) {
            return [];
        }
        return matchingItemIds;
    }

    var localeNeutral = LocalePeer.doSelectNeutral();
    var locales = [localeNeutral.id];

    var localeName = RSettings.getLocale();
    var locale = LocalePeer.doSelectByName(localeName);
    if (!isNull(locale)) {
        locales.push(locale.id);
    }

    // always search english locale anyway for now:
    if (localeName!=="en") {
        var localeEn = LocalePeer.doSelectByName("en");
        if (!isNull(localeEn)) {
            locales.push(localeEn.id);
        }
    }

    // text search:
    var tags = TagPeer.doSelectByText(text, locales, ["id"]);
    var searchTagIds = [];
    for (i=0; i<tags.length; i++) {
        searchTagIds.push(tags[i].id);
    }
    itemIds = ItemPeer.getIdsByTagIdsRecursive(searchTagIds);
    if (isNull(matchingItemIds)) {
        matchingItemIds = itemIds;
    }
    else {
        matchingItemIds.sortNumerical();
        itemIds.sortNumerical();
        matchingItemIds = Array.intersect(matchingItemIds, itemIds);
    }

    return matchingItemIds;
};

/**
 * \return Array of file items which match the given tags and search text.
 * \param tagIds Array of tag IDs.
 * \param text Search string.
 * \param fields Fields to query from DB or undefined to query all fields.
 */
ItemPeer.doSelectByTagIdsAndText = function(tagIds, text, fields) {
    return ItemPeer.doSelectByIds(ItemPeer.getIdsByTagIdsAndText(tagIds, text), fields);
};

/**
 * \return Array of item IDs which match the given tag IDs.
 */
ItemPeer.getItemIdsByTagId = function(tagId) {
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT id,type"
        + " FROM item,item_tag"
        + " WHERE id=item_id"
        + "  AND tag_id=:tag_id"
        + " ORDER BY id");
    query.bindValue(":tag_id", tagId);
    con.execQuery(query);
    var ret = [];
    while (query.next()) {
        ret.push(query.value(0));
    }
    ret.sortNumerical();
    return ret;
};

ItemPeer.getIdsByTagIdsRecursive = function(tagIds) {
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
                "SELECT item_id, type"
                + " FROM item_tag, item"
                + " WHERE tag_id in (" + tagIds.join() + ")"
                + " AND item_id=item.id"
                + " ORDER BY item_id");
    con.execQuery(query);

    var ret = {};
    while (query.next()) {
        var itemId = query.value(0);

        if (ret.hasOwnProperty(itemId)) {
            //qDebug("getItems: have already: ", itemId);
            //qDebug("getItems: ret: ", ret.length);
            continue;
        }

        var type = query.value(1);

        ret[itemId] = true;
        if (type===Item.Type.Directory) {
            //qDebug("dir...");
            var desc = ItemPeer.getFileDescendants(itemId/*, ret*/);
            ret = mergeProperties(ret, desc);
        }
    }
    ret = Object.keys(ret);

    var ret2 = [];
    for (var i=0; i<ret.length; i++) {
        ret2.push(parseInt(ret[i], 10));
    }
    ret2.sortNumerical();
    return ret2;
};

/**
 * \return Object with item IDs of all decendants (children, grand children, ...)
 * of type file of the given parent item as properties.
 */
ItemPeer.getFileDescendants = function(parentId/*, excludeIds*/) {
    var item = ItemPeer.doSelectById(parentId, ["parent_id", "path", "name"]);
    if (isNull(item)) {
        return {};
    }

    var path;
    if (isNull(item.parent_id)) {
        path = item.name;
    }
    else {
        path = item.path + "/" + item.name;
    }

    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT id,type"
        + " FROM item"
        //+ " WHERE parent_id=:parent_id"
        + " WHERE SUBSTR(path,0,:len)=:path"
        + " ORDER BY id");
    query.bindValue(":parent_id", parentId);
    query.bindValue(":len", path.length+1);
    query.bindValue(":path", path);
    con.execQuery(query);
    var ret = {};
    while (query.next()) {
        var itemId = query.value(0);

        var type = query.value(1);
        if (type===Item.Type.File) {
            ret[itemId]=true;
        }
//        else {
//            var desc = ItemPeer.getFileDescendants(itemId);
//            ret = mergeProperties(ret, desc);
//        }
    }
    return ret;
};

// ItemPeer.doSelectByDirectoryId
ItemPeer.doSelectByParentId = function(parentId, fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }

    var con = new DbConnection(Table.connectionName);
    var sql =
        "SELECT " + fields.join() +
        " FROM " + Item.tableName +
        " WHERE parent_id=:parent_id " +
        " ORDER BY LOWER(name)";
    var query = con.prepareQuery(sql);
    query.bindValue(":parent_id", parentId);
    con.execQuery(query);
    return ItemPeer.createFromQuery(query);
};

ItemPeer.doSelectNamesByParentId = function(parentId) {
    var con = new DbConnection(Table.connectionName);
    var sql =
        "SELECT name" +
        " FROM " + Item.tableName +
        " WHERE parent_id=:parent_id " +
        " ORDER BY LOWER(name)";
    var query = con.prepareQuery(sql);
    query.bindValue(":parent_id", parentId);
    con.execQuery(query);
    var names = [];
    while (query.next()) {
        names.push(query.value(0).toString());
    }
    return names;
};

//ItemPeer.doSelectByFileAndDirectoryId
ItemPeer.doSelectByNameAndParentId = function(name, parent_id, fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }

    var con = new DbConnection(Table.connectionName);
    var sql =
        "SELECT " + fields.join()
        + " FROM " + Item.tableName
        + " WHERE name=:name "
        + " AND parent_id=:parent_id";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", name);
    query.bindValue(":parent_id", parent_id);
    con.execQuery(query);
    var items = ItemPeer.createFromQuery(query);
    return items[0];
};

//ItemPeer.existsByFileAndDirectoryId
ItemPeer.existsByNameAndParentId = function(name, parent_id) {
    var con = new DbConnection(Table.connectionName);
    var sql = "SELECT count(*) FROM " + Item.tableName
        + " WHERE name=:name AND parent_id=:parent_id";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", name);
    query.bindValue(":parent_id", parent_id);
    con.execQuery(query);
    query.next();
    return query.value(0) != 0;
};

ItemPeer.doSelectAll = function(offset, limit, idsOnly) {
    var con = new DbConnection(Table.connectionName);
    var sql = "";
    sql = "SELECT * FROM item"
        + " WHERE item.type=" + Item.type
        + " ORDER BY LOWER(item.name)";
    if (!(isNull(offset) || isNull(limit))) {
        sql += " LIMIT " + offset + "," + limit;
    }
    
    var query = con.execQuery(sql);
    
    if (idsOnly) {
        var ret = [];
        while (query.next()) {
            ret.push(query.value(0));
        }
        return ret;
    }

    return ItemPeer.createFromQuery(query);
};

//ItemPeer.doCountAll
ItemPeer.doCountAllFiles = function() {
    var con = new DbConnection(Table.connectionName);
    var query = con.execQuery("SELECT COUNT(*) FROM item"
            + " WHERE type=" + Item.File);
    query.next();
    return query.value(0);
};

ItemPeer.createFromQuery = function(query) {
    var ret = [];
    while (query.next()) {
        var item = new Item();
        item.addProperties(query);      
        ret.push(item);
    }
    return ret;
};

/**
 * Deletes the item with the given ID and all sub items.
 * \return 1 if the item was deleted, 0 otherwise.
 */
ItemPeer.doDeleteById = function(itemId, progressDialog, rec) {
//    if (isNull(itemId)) {
//        return false;
//    }
    if (!LibraryBrowser.increaseProgress(progressDialog)) {
        return undefined;
    }

//    if (!isNull(progressDialog)) {
//        progressDialog.labelText = progressDialog.originalLabelText +
//            " [%1/%2]".arg(progressDialog.value).arg(progressDialog.maximum);
//        progressDialog.value++;
//        if (progressDialog.wasCanceled) {
//            return undefined;
//        }
//    }

    // select child items:
    var items = ItemPeer.doSelectByParentId(itemId, ["id"]);
    for (var i=0; i<items.length; i++) {
        var item = items[i];
        if (isNull(ItemPeer.doDeleteById(item.id, progressDialog, true))) {
            // canceled:
            return undefined;
        }
    }

    // delete child items:
    var con = new DbConnection(Table.connectionName);
    var sql = "DELETE FROM " + Item.tableName + " WHERE parent_id=:parent_id";
    qDebug("deleting child items of: ", itemId);
    var query = con.prepareQuery(sql);
    query.bindValue(":parent_id", itemId);
    con.execQuery(query);

    // delete link to tags:
    ItemTagPeer.doDeleteByItemId(itemId);

    // delete item self:
    if (!rec) {
        var con = new DbConnection(Table.connectionName);
        var sql = "DELETE FROM " + Item.tableName + " WHERE id=:id";
        qDebug("deleting item: ", itemId);
        var query = con.prepareQuery(sql);
        query.bindValue(":id", itemId);
        con.execQuery(query);

    }

    // delete link to tags:
    ItemTagPeer.doDeleteByItemId(itemId);

    //qDebug("ItemPeer.doDeleteById: deleted: ", itemId);
    return query.numRowsAffected();
};

ItemPeer.sort = function(a, b) {
    // dirs first:
    if (a.type!==b.type) {
        if (a.type===Item.Type.Directory) {
            return -1;
        }
        else {
            return 1;
        }
    }
    if (a.name.toLowerCase() < b.name.toLowerCase()) {
        return -1;
    }
    if (a.name.toLowerCase() > b.name.toLowerCase()) {
        return 1;
    }
    return 0;
};
