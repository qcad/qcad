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


/**
 * Provides a connection to a SQLite database.
 * 
 * \param connectionName The connection name to use.
 */
function DbConnection(connectionName) {
    if (isNull(connectionName)) {
        return;
    }
    this.db = QSqlDatabase.database(connectionName, false);
}

DbConnection.prototype.dump = function() {
    var query = this.createQuery();
    query.execQuery(".dump");
};

DbConnection.prototype.transaction = function() {
    this.db.transaction();
};

DbConnection.prototype.commit = function() {
    this.db.commit();
};

DbConnection.prototype.rollback = function() {
    this.db.rollback();
};

/**
 * Executes the given QSqlQuery or SQL string and handles errors if appropriate.
 */
DbConnection.prototype.execQuery = function(query) {
    try {
        var ret = false;
        if (isString(query)) {
            var sql = query;
            query = new QSqlQuery(this.db);
            ret = query.exec(sql);
        }
        else {
            ret = query.exec();
        }

        if (!ret) {
            qCritical("DbConnection.js:", "execQuery(): error:", query
                    .lastError().text());
            qCritical("DbConnection.js:", "execQuery(): query failed:\n", query
                    .executedQuery());
            debugger;
        }
    } catch (e) {
        qCritical("DbConnection.js:", "execQuery(): exception:", e);
        debugger;
    }
    return query;
};

/**
 * \return New QSqlQuery object.
 */
DbConnection.prototype.createQuery = function() {
    return new QSqlQuery(this.db);
};

DbConnection.prototype.prepareQuery = function(sql) {
    var query = new QSqlQuery(this.db);
    var ret = query.prepare(sql);
    if (!ret) {
        qCritical("DbConnection.js:", "prepareQuery(): SQL prepare failed:\n",
                sql, "\n", query.lastError().text());
        debugger;
    }
    return query;
};

DbConnection.prototype.vacuum = function(sql) {
    var query = this.createQuery();
    query.exec("VACUUM");
};

/**
 * Converts the given QPixmap into a QByteArray for storage in a BLOB.
 */
DbConnection.pixmapToByteArray = function(pixmap) {
    if (pixmap == undefined || pixmap == null) {
        return null;
    }
    var ba = new QByteArray();
    var buffer = new QBuffer(ba);
    buffer.open(QIODevice.WriteOnly);
    pixmap.save(buffer, "PNG"); // writes pixmap into ba in PNG format
    return ba;
};
