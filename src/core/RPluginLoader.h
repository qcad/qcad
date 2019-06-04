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

#ifndef RPLUGINLOADER_H
#define RPLUGINLOADER_H

#include "core_global.h"

#include <QList>
#include <QMetaType>
#include <QScriptEngine>

#include "RPluginInterface.h"
#include "RPluginInfo.h"

/**
 * Loads and registeres plugins.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RPluginLoader {
public:
    static QString getPluginSuffix();
    static QStringList getPluginFiles();
    static void loadPlugins(bool init);
    static void unloadPlugins();
    static void loadPlugin(QObject* plugin, bool init, const QString& fileName = QString(), const QString& errorString = QString());
    static void unloadPlugin(const QString& fileName, bool remove = false);
    static void unloadPlugin(const QObject* plugin, bool remove = false);

    static void postInitPlugins(RPluginInterface::InitStatus status);

    /**
     * \nonscriptable
     */
    static void postInitPlugin(QObject* plugin, RPluginInterface::InitStatus status);

    /**
     * \nonscriptable
     */
    static void initScriptExtensions(QScriptEngine& engine);

    /**
     * \nonscriptable
     */
    static void initScriptExtensions(QObject* plugin, QScriptEngine& engine);

    static void initTranslations();

    /**
     * \nonscriptable
     */
    static void initTranslations(QObject* plugin);

    static int countPlugins() {
        return pluginsInfo.count();
    }

    static RPluginInfo getPluginInfo(int i);
    static RPluginInfo getPluginInfo(const QString& id);

    static QString getPluginsPath();
    static bool hasPlugin(const QString& id);

    static bool checkPluginLicenses();
    static bool checkPluginLicense(QObject* plugin);

private:
    static QList<RPluginInfo> pluginsInfo;
    static QStringList pluginFiles;
};

Q_DECLARE_METATYPE(RPluginLoader*)

#endif
