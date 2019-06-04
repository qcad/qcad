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

#ifndef RPLUGININTERFACE_H
#define RPLUGININTERFACE_H

#include "core_global.h"

#include <QtPlugin>
#include <QMetaType>

#include "RPluginInfo.h"

class QString;
class QScriptEngine;

/**
 * Interface for all C++ QCAD plugins.
 * 
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RPluginInterface {
public:
    enum InitStatus {
        GotSplashWindow,    /**< Splashscreen showing. */
        AddOnsInitialized,  /**< Add ons are initialized, actions created but not added to widgets. */
        ActionsAdded,       /**< Actions have been added to widgets. */
        GotMainWindowBeforeShow,      /**< Main window created but not shown yet. */
        GotMainWindow,      /**< Main window with all tools and menus has been created. */
        LoadedFiles,        /**< Loaded files given on command line. */
        ScriptsExecuted,    /**< Executed scripts given on command line. */
        AllDone             /**< Application is ready and idle. */
    };

public:
    virtual ~RPluginInterface() {}

    /**
     * Called immediately after the plugin has been loaded, directly
     * after starting the application. Implementations typically perform
     * plugin initialization, registration of file importers, exporter, etc.
     */
    virtual bool init() = 0;

    /**
     * Called before a plugin is removed / unloaded.
     */
    virtual void uninit(bool remove = false) = 0;

    /**
     * Called after the application has been fully loaded, directly before
     * entering the main event loop. Implementations typically perform
     * initialization that depends on the application being up and running.
     */
    virtual void postInit(RPluginInterface::InitStatus status) = 0;

    /**
     * Called whenever a new script engine is instantiated.
     * Implementations may register their own script extensions by making
     * C / C++ code scriptable.
     *
     * \nonscriptable
     */
    virtual void initScriptExtensions(QScriptEngine& engine) = 0;

    /**
     * Called when the user chosen language changed.
     *
     * \nonscriptable
     */
    virtual void initTranslations() = 0;

    /**
     * \return An RPluginInfo object with at least the following keys:
     * - 'Version' - Version string
     * - 'Name' - Plugin name
     * - 'Description' - Longer description of the plugin
     * - 'License' - Licensing information (e.g. 'GPLv3', 'proprietary', ...)
     * - 'URL' - URL where more information about the plugin can be found
     *
     * This is typically used by an about dialog or debugging / developer tools.
     */
    virtual RPluginInfo getPluginInfo() = 0;

    /**
     * \return True if the plugin license is valid.
     */
    virtual bool checkLicense() = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(RPluginInterface, "org.qcad.QCAD.RPluginInterface/1.0")
QT_END_NAMESPACE

Q_DECLARE_METATYPE(RPluginInterface*)
Q_DECLARE_METATYPE(RPluginInterface::InitStatus)
Q_DECLARE_METATYPE(RPluginInterface::InitStatus*)

#endif
