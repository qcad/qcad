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

#ifndef RPLUGININFO_H
#define RPLUGININFO_H

#include "core_global.h"

#include <QMap>
#include <QString>
#include <QStringList>
#include <QMetaType>
#include <QVariant>

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif

/**
 * Information about a plugin. Ususally shown in an about dialog.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RPluginInfo {
public:
    RPluginInfo() {
        map.insert("QtVersion", qVersion());
    }

    void set(const QString& key, const QVariant& value) {
        map.insert(key, value);
    }

    QVariant get(const QString& key, const QVariant& def = RDEFAULT_QVARIANT) const {
        if (map.contains(key)) {
            return map.value(key);
        }
        return def;
    }

    QStringList getKeys() const {
        return map.keys();
    }

private:
    QVariantMap map;
};

Q_DECLARE_METATYPE(RPluginInfo)
Q_DECLARE_METATYPE(RPluginInfo*)

#endif
