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

include("TagCategory.js");

function TagCategoryPeer() {
}

TagCategoryPeer.createTable = function(drop) {
    if (isNull(drop)) {
        drop = false;
    }
    var con = new DbConnection(Table.connectionName);
    if (drop) {
        con.execQuery("DROP TABLE IF EXISTS " + TagCategory.tableName);
    }
    con.execQuery(
        "CREATE TABLE IF NOT EXISTS " + TagCategory.tableName
        + " ("
        + "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        + "name VARCHAR"
        + ")");
    con.execQuery("CREATE UNIQUE INDEX IF NOT EXISTS tag_category_id_name ON " + TagCategory.tableName + "(id, name)");
};

TagCategoryPeer.doInsert = function(tagCategory) {
    var existingTagCategory = TagCategoryPeer.doSelectByName(tagCategory.name, true);
    if (!isNull(existingTagCategory)) {
        // tagCategory already in table
        tagCategory.id = existingTagCategory.id;
        //tagCategory.name = existingTagCategory.name;
        return;
    }
    
    var con = new DbConnection(Table.connectionName);
    var sql = "INSERT INTO " + TagCategory.tableName + " (name)"
        + "VALUES (:name)";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", tagCategory.name);
    if (!con.execQuery(query)) {
        qWarning("TagCategoryPeer.js:", "doInsert(): cannot create tagCategory");
        return;
    }
    tagCategory.id = query.lastInsertId();
};

TagCategoryPeer.doSelectAll = function(fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }

    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT " + fields.join()
        + " FROM tag_category"
        + " ORDER BY name");
    con.execQuery(query);
    return TagCategoryPeer.createFromQuery(query);
};

/*
TagCategoryPeer.doSelectOrInsert = function(tagCategory, fields) {
    var con = new DbConnection(Table.connectionName);
    var query = con.createQuery();
    query.exec("SELECT " + fields.join() + " FROM " + TagCategory.tableName
            + " WHERE name=:name");
    query.bindValue(":name", name);
    var res = TagCategoryPeer.createFromQuery(query);
    if (res.length === 1) {
        return res[0];
    }
    else if (res.length === 0) {
        TagCategoryPeer.doInsert(tagCategory);
        return tagCategory;
    }
    else {
        debugger;
    }
};
*/

/*
TagCategoryPeer.doUpdate = function(tagCategory) {
    var con = new DbConnection(Table.connectionName);
    var sql = "UPDATE " + TagCategory.tableName
        + " SET name=:name"
        + " WHERE id=:id";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", tagCategory.name);
    query.bindValue(":id", tagCategory.id);
    if (!con.execQuery(query)) {
        qWarning("TagCategoryPeer.js:", "doUpdate(): cannot update tagCategory");
        return;
    }   
};

TagCategoryPeer.doSelectAll = function() {
    var con = new DbConnection(Table.connectionName);
    var query = con.createQuery();
    query.exec("SELECT * FROM " + TagCategory.tableName + " ORDER BY id");
    return TagCategoryPeer.createFromQuery(query);
};
*/


/*TagCategoryPeer.doSelectOrInsertByName = function(name) {
    var tagCategory = TagCategoryPeer.doSelectByName(name);
    if (isNull(tagCategory)) {
        tagCategory = new TagCategory(name);
        TagCategoryPeer.doInsert(tagCategory);
    }
    return tagCategory;
};*/

TagCategoryPeer.doSelectByName = function(name) {
    var con = new DbConnection(Table.connectionName);
    var sql = "SELECT * FROM " + TagCategory.tableName + " WHERE name=:name";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", name);
    con.execQuery(query);
    var tagCategory = TagCategoryPeer.createFromQuery(query);
    if (tagCategory.length === 0) {
        return undefined;
    }
    return tagCategory[0];
};

/*
TagCategoryPeer.doSelectById = function(id) {
    var con = new DbConnection(Table.connectionName);
    var sql = "SELECT * FROM " + TagCategory.tableName + " WHERE id=:id";
    var query = con.prepareQuery(sql);
    query.bindValue(":id", id);
    con.execQuery(query);
    var tagCategory = TagCategoryPeer.createFromQuery(query);
    // has to be the first entry in the result set
    return tagCategory[0];
};

TagCategoryPeer.doSelectIndependent = function() {
    var con = new DbConnection(Table.connectionName);
    var sql = "SELECT * FROM " + TagCategory.tableName + " WHERE name=:name";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", TagCategory.Independent);
    con.execQuery(query);
    var tagCategory = TagCategoryPeer.createFromQuery(query);
    if (tagCategory.length == 0) {
        TagCategoryPeer.doSelectOrInsertByName(TagCategory.Independent);
        return TagCategoryPeer.doSelectIndependent;
    }
    return tagCategory[0];
};

TagCategoryPeer.getAllTagCategorys = function() {
    var con = new DbConnection(Table.connectionName);
    var query = con.createQuery();
    query.exec("SELECT DISTINCT name FROM " + TagCategory.tableName
            + " ORDER BY name");
    var ret = [];
    while (query.next()) {
        ret.push(String(query.value(0)));
    }
    return ret;
};
*/

TagCategoryPeer.createFromQuery = function(query) {
    var ret = [];
    while (query.next()) {
        var tagCategory = new TagCategory();
        tagCategory.addProperties(query);
        ret.push(tagCategory);
    }
    return ret;
};
