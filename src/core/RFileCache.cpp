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
#include "RFileCache.h"

#include <QStringList>
#include <QFileInfo>
#include <QDebug>

QCache<QString, QBuffer> RFileCache::cache(10e6);

QString RFileCache::getContents(const QString& fileName, bool forceReload) {
    QBuffer* buffer = getBuffer(fileName, forceReload);
    if (buffer==NULL) {
        return QString();
    }

    QString ret = QString::fromUtf8((const char*)buffer->data());
    delete buffer;
    return ret;
}

QBuffer* RFileCache::getBuffer(const QString& fileName, bool forceReload) {
    QString abs = QFileInfo(fileName).canonicalFilePath();

    if (abs.isEmpty()) {
        return NULL;
    }

//    if (forceReload) {
//        cache.remove(abs);
//    }

//    if (cache.contains(abs)) {
//        return cache[abs];
//    }

    //qDebug() << "getBuffer for " << fileName;

    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "RFileCache::getBuffer: cannot read file: " << abs;
        return NULL;
    }

    QBuffer* buffer = new QBuffer();
    buffer->setData(f.readAll());
    //cache.insert(abs, buffer, buffer->size());
    f.close();

    return buffer;
}
