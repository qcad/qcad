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

include("scripts/DbConnection.js");
include("Locale.js");
include("Table.js");

Tag.tableName = "tag";

Tag.prototype = new Table();

Tag.prototype.getTableName = function() {
    return Tag.tableName;
};

/**
 * Creates a tag from the given category, locale and text.
 *
 * \param category string Category name, e.g. 'audience'
 * \param locale string Locale name, e.g. 'en'
 * \param text string Text value of tag, e.g. 'architecture'
 * \param stem string Stem of tag, e.g. 'architectur'
 */
function Tag(category, locale, text, stem) {
    Table.call(this);

    if (isNull(locale)) {
        locale = Locale.Neutral;
    }
//    if (isNull(category)) {
//        category = "tag";
//    }

    this.id = -1;
    this.category = category;
    this.locale = locale;
    this.text = text;
    this.stem = stem;

//    if (!isNull(text)) {
//        this.text = text.toLowerCase();
//    }
//    if (!isNull(stem)) {
//        this.text = stem.toLowerCase();
//    }
}

Tag.prototype.save = function() {
    if (this.id === -1) {
        TagPeer.doInsert(this);
    } else {
        TagPeer.doUpdate(this);
    }
};
