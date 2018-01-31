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
include("Table.js");

ItemTag.tableName = "item_tag";

ItemTag.prototype = new Table();

ItemTag.prototype.getTableName = function() {
    return ItemTag.tableName;
};

function ItemTag(item_id, tag_id) {
    Table.call(this);
    this.id = -1;
    this.item_id = item_id;
    this.tag_id = tag_id;
}

/*
ItemTag.prototype.save = function() {
    if (this.id === -1) {
        ItemTagPeer.doInsert(this);
    } else {
        ItemTagPeer.doUpdate(this);
    }
};
*/
