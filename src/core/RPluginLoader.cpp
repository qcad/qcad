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

QList<RPluginInfo> RPluginLoader::pluginsInfo;

/**
 * TODO: should be done in a script library, called by the script that initializes the plugin
 */
void RPluginLoader::loadPlugins() {
    QString pluginsPath = getPluginsPath();
    if (pluginsPath.isNull()) {
        return;
    }

    QDir pluginsDir = QDir(pluginsPath);

    qDebug() << "Trying to load plugins from folder " << pluginsDir.path();
    QStringList nameFilter;
#if defined(Q_OS_WIN)
    nameFilter.append("*.dll");
#else
#   if defined(Q_OS_MAC)
    nameFilter.append("*.dylib");
#   else
    nameFi.append("*.so");
#   endif
#endif

    foreach (QString fileName, pluginsDir.entryList(nameFilter, QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject* plugin = loader.instance();
        RPluginInfo info;
        if (plugin) {
            RPluginInterface* p = qobject_cast<RPluginInterface*>(plugin);
            if (p) {
                p->init();
                info = p->getPluginInfo();
                info.setFileName(fileName);
            }
            else {
                info.setFileName(fileName);
                info.setErrorString(loader.errorString());
                qDebug() << "Plugin loader reported error: " << loader.errorString();
            }
        }
        else {
            info.setFileName(fileName);
            info.setErrorString(loader.errorString());
            qDebug() << "Plugin loader reported error: " << loader.errorString();
        }
        pluginsInfo.append(info);
    }
}

void RPluginLoader::initScriptExtensions(QScriptEngine& engine) {
    QString pluginsPath = getPluginsPath();
    if (pluginsPath.isNull()) {
        return;
    }

    QDir pluginsDir = QDir(pluginsPath);

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject* plugin = loader.instance();
        RPluginInterface* p = qobject_cast<RPluginInterface*>(plugin);
        if (p) {
            p->initScriptExtensions(engine);
        }
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
