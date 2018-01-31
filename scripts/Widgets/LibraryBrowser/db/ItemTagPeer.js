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

include("ItemTag.js");

function ItemTagPeer() {
}

ItemTagPeer.createTable = function(drop) {
    if (isNull(drop)) {
        drop = false;
    }
    var con = new DbConnection(Table.connectionName);
    if (drop) {
        con.execQuery("DROP TABLE IF EXISTS " + ItemTag.tableName);
    }
    con.execQuery(
        "CREATE TABLE IF NOT EXISTS " + ItemTag.tableName
        + " ("
        + "item_id INTEGER,"
        + "tag_id INTEGER"
        + ")");
    con.execQuery("CREATE UNIQUE INDEX IF NOT EXISTS item_tag_item_id_tag_id ON " + ItemTag.tableName + "(item_id, tag_id)");
};

ItemTagPeer.doInsert = function(itemTag) {
    var con = new DbConnection(Table.connectionName);
    var sql = "INSERT OR IGNORE INTO " + ItemTag.tableName + " (item_id, tag_id)"
        + " VALUES (:item_id, :tag_id)";
    var query = con.prepareQuery(sql);
    query.bindValue(":item_id", itemTag.item_id);
    query.bindValue(":tag_id", itemTag.tag_id);
    if (!con.execQuery(query)) {
        qWarning("ItemTagPeer.js:", "doInsert(): cannot create ItemTag");
        return;
    }
    id = query.lastInsertId();
};

/*
ItemTagPeer.doUpdate = function(itemTag) {
    qCritical("ItemTagPeer.js:", "doUpdate(): not supported yet");
    debugger;
};

ItemTagPeer.doSelectByItem = function(item) {
    var con = new DbConnection(Table.connectionName);
    var sql = "SELECT * FROM " + ItemTag.tableName + " WHERE item_id=:item_id";
    var query = con.prepareQuery(sql);
    query.bindValue(":item_id", item.id);
    con.execQuery(query);
    return ItemTagPeer.createFromQuery(query);
};
*/

ItemTagPeer.doDeleteByItemId = function(itemId) {
    var con = new DbConnection(Table.connectionName);

    // find tags that might have to be deleted:
    var query = con.prepareQuery(
        "SELECT id"
        + " FROM item_tag,tag "
        + " WHERE tag_id=id AND item_id=:item_id");
    query.bindValue(":item_id", itemId);
    con.execQuery(query);

    var tagIds = [];
    while (query.next()) {
        tagIds.push(query.value(0));
    }

    for (var i=0; i<tagIds.length; i++) {
        query = con.prepareQuery(
            "SELECT count(*)"
            + " FROM item_tag,tag"
            + " WHERE tag_id=id AND id=:id");
        query.bindValue(":id", tagIds[i]);
        con.execQuery(query);
        query.next();
        if (query.value(0)===1) {
            TagPeer.doDeleteById(tagIds[i]);
        }
    }

    query = con.prepareQuery(
        "DELETE FROM " + ItemTag.tableName
        + " WHERE item_id=:item_id");
    query.bindValue(":item_id", itemId);
    return con.execQuery(query);
};

/*
ItemTagPeer.doDeleteByTag = function(item_id, text) {
    var tags = TagPeer.findByText(text);
    if (tags.length == 0) {
        // tag doesn't exists
        return false;
    }
    var sql = "DELETE FROM " + ItemTag.tableName
        + " WHERE tag_id=:tag_id AND item_id=:item_id";
    
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(sql);
    query.bindValue(":item_id", item_id);
    query.bindValue(":tag_id", tags[0].id);
    return con.execQuery(query);
};

ItemTagPeer.removeOrphans = function() {
    var sql = "DELETE FROM ITEM_tag "
        + "WHERE ITEM_tag.item_id IN ( "
        + "SELECT DISTINCT ITEM_tag.item_id "
        + "FROM ITEM_tag LEFT JOIN ITEM on ITEM.id = ITEM_tag.item_id "
        + "WHERE  ITEM.id IS NULL )";
    
    var con = new DbConnection(Table.connectionName);
    var query = con.createQuery();
    query.exec(sql);
    return query.numRowsAffected();
};

ItemTagPeer.createFromQuery = function(query) {
    var ret = [];
    while (query.next()) {
        var tag = TagPeer.doSelectById(query.value(1));
        ret.push(tag.text);
    }
    return ret;
};
*/
