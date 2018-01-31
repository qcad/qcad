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

include("scripts/date.js");

/**
 * Abstract base class for all table objects.
 */
function Table() {
}

Table.connectionName = "library_browser_connection";

Table.prototype.toString = function() {
    var ret = this.getTableName();
    if (this.type) {
        if (this.type === Item.Type.Directory) {
            ret += " [type directory]";
        } else if (this.type === Item.Type.File) {
            ret += " [type file]";
        } else {
            ret += " [UNKNOWN TYPE]";
        }
    }
    ret += "(";
    for ( var i in this) {
        if (!isFunction(this[i])) {
            var val = this[i];
            if (this[i] === undefined) {
                val = "undefined";
            } else if (this[i] === null) {
                val = "null";
            } else if (this[i].length == 0) {
                if (isArray(this[i])) {
                    val = "<empty array>";
                } else {
                    val = "<empty string>";
                }
            }
            ret += i + "='" + val + "', ";
        }
    }
    ret += ")";
    return ret;
};

/**
 * Adds the fields from the query record to this object as properties.
 */
Table.prototype.addProperties = function(query) {
    var record = query.record();
    for ( var i = 0; i < record.count(); ++i) {
        var field = record.field(i);
        var name = field.name();
        if (record.isNull(i)) {
            this[name] = null;
        } else {
            this[name] = query.value(i);
        }
        // always returns QVariant(QVariant::Type)
        if (name == "icon") {
            if (this[name] == null) {
                continue;
            }
            var pixmap = new QPixmap();
            pixmap.loadFromData(this[name]);
            this[name] = pixmap;
            continue;
        }
        if ((this.type == Item.type && name == "hash")
                || (name == "rdfhash" && this[name] != null)) {
            var ts = new Date(getDateFromFormat(this[name],
                    "yyyy-MM-dd HH:mm:ss"));
            this[name] = ts;
            continue;
        }
    }
};
