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

#ifndef RFILECACHE_H_
#define RFILECACHE_H_

#include "core_global.h"

#include <QMetaType>
#include <QBuffer>
#include <QCache>
#include <QMap>

/**
 * QBuffer based file cache.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFileCache {
public:
    static QString getContents(const QString& fileName, bool forceReload=false);
    static QBuffer* getBuffer(const QString& fileName, bool forceReload=false);

private:
    static QCache<QString, QBuffer> cache;
};

Q_DECLARE_METATYPE(RFileCache)
Q_DECLARE_METATYPE(RFileCache*)

#endif
