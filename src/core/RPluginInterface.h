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

#ifndef RPLUGININTERFACE_H
#define RPLUGININTERFACE_H

#include "core_global.h"

#include <QtPlugin>
#include <QMetaType>

#include "RPluginInfo.h"

QT_BEGIN_NAMESPACE
class QString;
class QScriptEngine;
QT_END_NAMESPACE

class QCADCORE_EXPORT RPluginInterface {
public:
    virtual ~RPluginInterface() {}

    /**
     * Called immediately after the plugin has been loaded, directly
     * after starting the application. Implementations typically perform
     * plugin initialization, registration of file importers, exporter, etc.
     */
    virtual bool init() = 0;

    /**
     * Called after the application has been fully loaded, directly before
     * entering the main event loop. Implementations typically perform
     * initialization that depends on the application being up and running.
     */
    virtual void postInit() = 0;

    /**
     * Called whenever a new script engine is instantiated.
     * Implementations may register their own script extensions by making
     * C / C++ code scriptable.
     */
    virtual void initScriptExtensions(QScriptEngine& engine) = 0;

    /**
     * \return An RPluginInfo object with at least the following keys:
     * - 'Version' - Version string
     * - 'About' - Plugin name
     * - 'Description' - Longer description of the plugin
     * - 'License' - Licensing information (e.g. 'GPLv3', 'proprietary', ...)
     * - 'URL' - URL where more information about the plugin can be found
     *
     * This is typically used by an about dialog or debugging / developer tools.
     */
    virtual RPluginInfo getPluginInfo() = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(RPluginInterface, "org.qcad.QCAD.RPluginInterface/1.0")
QT_END_NAMESPACE

Q_DECLARE_METATYPE(RPluginInterface*)


#endif
