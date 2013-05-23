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
#include <QDir>
#include <QDebug>
#include <QPluginLoader>

#include "RPluginInterface.h"
#include "RPluginLoader.h"

QList<RPluginInfo > RPluginLoader::pluginsInfo;
QStringList RPluginLoader::pluginFiles;


QStringList RPluginLoader::getPluginFiles() {
    if (!pluginFiles.isEmpty()) {
        return pluginFiles;
    }

    QString pluginsPath = getPluginsPath();
    if (pluginsPath.isNull()) {
        return pluginFiles;
    }

    QDir pluginsDir = QDir(pluginsPath);

    QStringList nameFilter;

#if defined(Q_OS_WIN)
    nameFilter.append("*.dll");
#elif defined(Q_OS_MAC)
    nameFilter.append("*.dylib");
#else
    nameFilter.append("*.so");
#endif

    foreach (QString fileName, pluginsDir.entryList(nameFilter, QDir::Files)) {
        if (fileName.contains("_debug.")) {
#ifndef QT_DEBUG
            // debug plugin but built in release mode: skip:
            continue;
#endif
        }
        else {
#ifdef QT_DEBUG
            // release plugin but built in debug mode: skip:
            continue;
#endif
        }

        pluginFiles.append(pluginsDir.absoluteFilePath(fileName));
    }

    return pluginFiles;
}

/**
 * Tries to loads all QCAD plugins located in ./plugins.
 */
void RPluginLoader::loadPlugins(bool init) {
    pluginsInfo.clear();

    foreach (QString fileName, getPluginFiles()) {
        QPluginLoader loader(fileName);
        QObject* plugin = loader.instance();
        loadPlugin(plugin, init, fileName, loader.errorString());
    }

    QObjectList staticPlugins = QPluginLoader::staticInstances();
    for (int i=0; i<staticPlugins.size(); i++) {
        QObject* plugin = staticPlugins[i];
        loadPlugin(plugin, init);
    }
}

void RPluginLoader::loadPlugin(QObject* plugin, bool init, const QString& fileName, const QString& errorString) {
    RPluginInfo info;
    if (plugin) {
        RPluginInterface* p = qobject_cast<RPluginInterface*>(plugin);
        if (p) {
            if (init) {
                p->init();
            }
            info = p->getPluginInfo();
        }
        else {
            // ignore other Qt plugins
            return;
        }
    }
    else {
        info.set("Error", errorString);
        qDebug() << "Plugin loader reported error: " << errorString;
    }
    if (!fileName.isEmpty()) {
        info.set("FileName", fileName);
    }

    pluginsInfo.append(info);
}

void RPluginLoader::postInitPlugins() {
    foreach (QString fileName, getPluginFiles()) {
        QPluginLoader loader(fileName);
        QObject* plugin = loader.instance();
        postInitPlugin(plugin);
    }

    QObjectList staticPlugins = QPluginLoader::staticInstances();
    for (int i=0; i<staticPlugins.size(); i++) {
        QObject* plugin = staticPlugins[i];
        qDebug() << "postInitPlugin (static)";
        postInitPlugin(plugin);
    }
}

void RPluginLoader::postInitPlugin(QObject* plugin) {
    RPluginInterface* p = qobject_cast<RPluginInterface*>(plugin);
    if (p) {
        p->postInit();
    }
}

void RPluginLoader::initScriptExtensions(QScriptEngine& engine) {
    foreach (QString fileName, getPluginFiles()) {
        QPluginLoader loader(fileName);
        QObject* plugin = loader.instance();
        initScriptExtensions(plugin, engine);
    }

    QObjectList staticPlugins = QPluginLoader::staticInstances();
    for (int i=0; i<staticPlugins.size(); i++) {
        QObject* plugin = staticPlugins[i];
        initScriptExtensions(plugin, engine);
    }
}

void RPluginLoader::initScriptExtensions(QObject* plugin, QScriptEngine& engine) {
    RPluginInterface* p = qobject_cast<RPluginInterface*>(plugin);
    if (p) {
        p->initScriptExtensions(engine);
    }
}

QString RPluginLoader::getPluginsPath() {
    QDir pluginsDir = QDir(".");
    if (!pluginsDir.cd("plugins")) {
        pluginsDir.cdUp();
        if (!pluginsDir.cd("PlugIns")) {
            qWarning() << "RPluginLoader::loadPlugins: No plugins directory found.";
            return QString();
        }
    }
    return pluginsDir.absolutePath();
}
