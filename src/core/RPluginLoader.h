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
#if QT_VERSION < 0x060000
#include <QScriptEngine>
#endif

#include "RPluginInterface.h"
#include "RPluginInfo.h"

/**
 * Loads and registers plugins.
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
    static void unloadPlugin(QObject* plugin, bool remove = false);

    static void postInitPlugins(RPluginInterface::InitStatus status);

    /**
     * \nonscriptable
     */
    static void postInitPlugin(QObject* plugin, RPluginInterface::InitStatus status);

#if QT_VERSION < 0x060000
    /**
     * \nonscriptable
     */
    static void initScriptExtensions(QScriptEngine& engine);

    /**
     * \nonscriptable
     */
    static void initScriptExtensions(QObject* plugin, QScriptEngine& engine);
#else
    static void initScriptExtensions(RScriptHandler& handler);
    static void initScriptExtensions(QObject* plugin, RScriptHandler& handler);
#endif

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
    /**
     * \return The plugin objects loaded by loadPlugins (dynamically loaded
     * plugins in load order, then the statically linked plugins).
     */
    static QList<QObject*> getPluginObjects();

    static QList<RPluginInfo> pluginsInfo;
    static QStringList pluginFiles;
    /**
     * Instances of the dynamically loaded plugins (see loadPlugins). Used
     * by postInitPlugins, initScriptExtensions and initTranslations instead
     * of loading the plugins again by file name: a plugin file that has been
     * removed from the plugins directory since the start (e.g. by a launcher
     * script of another QCAD process that cleans the plugins directory)
     * cannot be found by QPluginLoader anymore, although the plugin is
     * loaded, and its script extensions would be missing in every script
     * engine created later (document engines are created on demand).
     */
    static QList<QObject*> plugins;
};

Q_DECLARE_METATYPE(RPluginLoader*)

#endif
