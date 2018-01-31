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

//include("scripts/DbConnection.js");
include("Table.js");

Locale.tableName = "locale";

Locale.Neutral = "";

Locale.prototype = new Table();

function Locale(name) {
    Table.call(this);

    this.id = -1;
    this.name = name;
}

Locale.prototype.getTableName = function() {
    return Locale.tableName;
};

Locale.prototype.save = function() {
    if (this.id === -1) {
        LocalePeer.doInsert(this);
    } else {
        LocalePeer.doUpdate(this);
    }
};
