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

include("Tag.js");

function TagPeer() {
}

TagPeer.createTable = function(drop) {
    if (isNull(drop)) {
        drop = false;
    }
    var con = new DbConnection(Table.connectionName);
    var query = con.createQuery();
    if (drop) {
        con.execQuery("DROP TABLE IF EXISTS " + Tag.tableName);
    }
    con.execQuery(
        "CREATE TABLE IF NOT EXISTS " + Tag.tableName
        + " ("
        + "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        + "category_id INTEGER,"
        + "locale_id INTEGER,"
        + "text VARCHAR,"
        + "stem VARCHAR"
        + ")");
    con.execQuery("CREATE UNIQUE INDEX IF NOT EXISTS tag_id_text ON " + Tag.tableName + "(id, text)");
    con.execQuery("CREATE UNIQUE INDEX IF NOT EXISTS tag_category_id_locale_id_text ON " + Tag.tableName + "(category_id, locale_id, text)");
};

TagPeer.doInsert = function(tag) {
    var category = new TagCategory(tag.category);
    TagCategoryPeer.doInsert(category);

    var locale = new Locale(tag.locale);
    LocalePeer.doInsert(locale);

    // check if tag is already in table:
    var existingTag = TagPeer.doSelectByCategoryIdLocaleIdText(category.id, locale.id, tag.text, ["id"]);
    if (!isNull(existingTag)) {
        tag.id = existingTag.id;
        return;
    }
    
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "INSERT INTO " + Tag.tableName + " (category_id, locale_id, text, stem)"
        + " VALUES (:category_id, :locale_id, :text, :stem)");
    query.bindValue(":category_id", category.id);
    query.bindValue(":locale_id", locale.id);
    query.bindValue(":text", tag.text);
    query.bindValue(":stem", tag.stem);
    if (!con.execQuery(query)) {
        qWarning("TagPeer.js:", "doInsert(): cannot create tag");
        return;
    }
    
    tag.id = query.lastInsertId();
};

/**
 * Used to check if tag already exists.
 */
TagPeer.doSelectByCategoryIdLocaleIdText = function(categoryId, localeId, text, fields) {
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT " + fields.join() + " FROM " + Tag.tableName
        + " WHERE category_id=:category_id"
        + " AND locale_id=:locale_id"
        + " AND text=:text");
    query.bindValue(":category_id", categoryId);
    query.bindValue(":locale_id", localeId);
    query.bindValue(":text", text);
    con.execQuery(query);
    var tags = TagPeer.createFromQuery(query);
    return tags[0];
};

/**
 * Selects all tags which contain the given text (search) in the given locale
 * locale neutral.
 */
TagPeer.doSelectByText = function(text, localeIds, fields) {
    if (isNull(fields)) {
        fields = ["*"];
    }

    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "SELECT " + fields.join() + " FROM " + Tag.tableName
        + " WHERE locale_id IN (" + localeIds.join() + ")"
        + " AND (stem IS NOT NULL AND stem LIKE :text1) OR text LIKE :text2");
    query.bindValue(":text1", '%' + text + '%');
    query.bindValue(":text2", '%' + text + '%');
    con.execQuery(query);
    var tags = TagPeer.createFromQuery(query);
    return tags;
};

/**
 * Deletes the tag with the given ID.
 * \return 1 if the item was deleted, 0 otherwise.
 */
TagPeer.doDeleteById = function(id) {
    // delete item self:
    var con = new DbConnection(Table.connectionName);
    var query = con.prepareQuery(
        "DELETE FROM " + Tag.tableName + " WHERE id=:id");
    query.bindValue(":id", id);
    con.execQuery(query);
    return query.numRowsAffected();
};

/**
 * \return List of available tags in the given tag category and locale
 * with multiplicity ordered by multiplicity descending.
 *
 * \param categoryId Id of category
 * \param locale string Locale name, e.g. 'en'
 * \param itemIds Array of item IDs that restricts the result set to those
 *    tags that are used by the given items.
 */
TagPeer.doSelectByCategoryIdAndLocale = function(categoryId, locale, tagIds, fields) {
    if (isNull(fields)) {
        debugger;
        fields = ["*"];
    }

    var con = new DbConnection(Table.connectionName);
    var sqlItemCondition = "";
    var query;
    if (!isNull(tagIds) && tagIds.length!==0) {
        var tagFields = [];
        for (var i=0; i<fields.length; i++) {
            tagFields.push("tag." + fields[i]);
        }
        var tagFields2 = [];
        for (var i=0; i<fields.length; i++) {
            tagFields2.push("t2." + fields[i]);
        }
        query = con.prepareQuery(
            "SELECT " + tagFields2.join()
            + " FROM"
            + "  ( SELECT DISTINCT(item_id)"
            + "    FROM item_tag, tag, locale"
            + "    WHERE item_tag.tag_id=tag.id"
            + "    AND category_id=:category_id1"
            + "    AND locale_id=locale.id"
            + "    AND (locale.name=:locale1 OR locale.name='')"
            + "    AND tag.id IN (" + tagIds.join() + ")) AS t1,"
            + "  ( SELECT DISTINCT(item_id), " + tagFields.join()
            + "    FROM item_tag, tag, locale"
            + "    WHERE item_tag.tag_id=tag.id"
            + "    AND category_id=:category_id2"
            + "    AND locale_id=locale.id"
            + "    AND (locale.name=:locale2 OR locale.name='')) AS t2"
            + " WHERE t1.item_id=t2.item_id"
            + sqlItemCondition
            + " GROUP BY t2.id"
        );
        query.bindValue(":category_id1", categoryId);
        query.bindValue(":category_id2", categoryId);
        query.bindValue(":locale1", locale);
        query.bindValue(":locale2", locale);
    }
    else {
        var tagFields = [];
        for (var i=0; i<fields.length; i++) {
            tagFields.push("tag." + fields[i]);
        }
        fields = tagFields;

        query = con.prepareQuery(
            "SELECT " + fields.join()
            + " FROM tag, locale"
            + " WHERE category_id=:category_id"
            + " AND locale_id=locale.id"
            + " AND (locale.name=:locale OR locale.name='')"
        );
        query.bindValue(":category_id", categoryId);
        query.bindValue(":locale", locale);
    }

    con.execQuery(query);

    return TagPeer.createFromQuery(query);
};

TagPeer.createFromQuery = function(query) {
    var ret = [];
    while (query.next()) {
        var tag = new Tag();
        tag.addProperties(query);
        ret.push(tag);
    }
    return ret;
};
