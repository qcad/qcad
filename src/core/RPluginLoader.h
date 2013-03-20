/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RPLUGINLOADER_H
#define RPLUGINLOADER_H

#include <QList>
#include <QMetaType>
#include <QScriptEngine>

#include "RPluginInfo.h"
#include "RPluginInterface.h"

/**
 * Loads and registeres plugins.
 *
 * \ingroup core
 * \scriptable
 */
class RPluginLoader {
public:
    static void loadPlugins();

    /**
     * \nonscriptable
     */
    static void initScriptExtensions(QScriptEngine& engine);

    static int countPlugins() {
        return pluginsInfo.count();
    }

    static RPluginInfo getPluginInfo(int i) {
        if (i<0 || i>pluginsInfo.count()) {
            return RPluginInfo();
        }
        return pluginsInfo[i];
    }

private:
    static QList<RPluginInfo> pluginsInfo;
};

Q_DECLARE_METATYPE(RPluginLoader*)

#endif
