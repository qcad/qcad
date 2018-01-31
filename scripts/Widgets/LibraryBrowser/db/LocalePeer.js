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

include("Locale.js");

function LocalePeer() {
}

LocalePeer.createTable = function(drop) {
    if (isNull(drop)) {
        drop = false;
    }
    var con = new DbConnection(Table.connectionName);
    if (drop) {
        con.execQuery("DROP TABLE IF EXISTS " + Locale.tableName);
    }
    con.execQuery(
        "CREATE TABLE IF NOT EXISTS " + Locale.tableName
        + " ("
        + "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        + "name VARCHAR"
        + ")");
    con.execQuery("CREATE UNIQUE INDEX IF NOT EXISTS locale_id_name ON " + Locale.tableName + "(id, name)");
};

LocalePeer.doInsert = function(locale) {
    var existingLocale = LocalePeer.doSelectByName(locale.name, true);
    if (!isNull(existingLocale)) {
        // locale already in table
        locale.id = existingLocale.id;
        return;
    }
    
    var con = new DbConnection(Table.connectionName);
    var sql = "INSERT INTO " + Locale.tableName + " (name)"
        + "VALUES (:name)";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", locale.name);
    if (!con.execQuery(query)) {
        qWarning("LocalePeer.js:", "doInsert(): cannot create locale");
        return;
    }
    locale.id = query.lastInsertId();
};

/*
LocalePeer.doUpdate = function(locale) {
    var con = new DbConnection(Table.connectionName);
    var sql = "UPDATE " + Locale.tableName
        + " SET name=:name"
        + " WHERE id=:id";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", locale.name);
    query.bindValue(":id", locale.id);
    if (!con.execQuery(query)) {
        qWarning("LocalePeer.js:", "doUpdate(): cannot update locale");
        return;
    }   
};

LocalePeer.doSelectAll = function() {
    var con = new DbConnection(Table.connectionName);
    var query = con.createQuery();
    query.exec("SELECT * FROM " + Locale.tableName + " ORDER BY id");
    return LocalePeer.createFromQuery(query);
};
*/

LocalePeer.doSelectOrInsertByName = function(name) {
    var locale = LocalePeer.doSelectByName(name);
    if (isNull(locale) || locale.length === 0) {
        LocalePeer.doInsert(new Locale(name));
        locale = LocalePeer.doSelectByName(name);
    }
    return locale;
};

LocalePeer.doSelectByName = function(name) {
    var con = new DbConnection(Table.connectionName);
    var sql = "SELECT * FROM " + Locale.tableName + " WHERE name=:name";
    var query = con.prepareQuery(sql);
    query.bindValue(":name", name);
    con.execQuery(query);
    var locale = LocalePeer.createFromQuery(query);
    if (locale.length === 0) {
        return undefined;
    }
    return locale[0];
};

/*
LocalePeer.doSelectById = function(id) {
    var con = new DbConnection(Table.connectionName);
    var sql = "SELECT * FROM " + Locale.tableName + " WHERE id=:id";
    var query = con.prepareQuery(sql);
    query.bindValue(":id", id);
    con.execQuery(query);
    var locale = LocalePeer.createFromQuery(query);
    // has to be the first entry in the result set
    return locale[0];
};
*/

LocalePeer.doSelectNeutral = function() {
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT *"
        + " FROM " + Locale.tableName
        + " WHERE name=:name");
    query.bindValue(":name", Locale.Neutral);
    con.execQuery(query);
    var locale = LocalePeer.createFromQuery(query);
    if (locale.length === 0) {
        LocalePeer.doSelectOrInsertByName(Locale.Neutral);
        return LocalePeer.doSelectNeutral();
    }
    return locale[0];
};

/*
LocalePeer.getAllLocales = function() {
    var con = new DbConnection(Table.connectionName);
    var query = con.createQuery();
    query.exec("SELECT DISTINCT name FROM " + Locale.tableName
            + " ORDER BY name");
    var ret = [];
    while (query.next()) {
        ret.push(String(query.value(0)));
    }
    return ret;
};
*/

LocalePeer.createFromQuery = function(query) {
    var ret = [];
    while (query.next()) {
        var locale = new Locale();
        locale.addProperties(query);
        ret.push(locale);
    }
    return ret;
};
