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

//include("WidgetFactory.js");

/**
 * \class Plugin
 * \brief Initializes and manages all plugins. Every directory in the
 * script directory of QCAD is a plugin if it contains an ECMAScript
 * file with the same name as the directory and the extension ".js".
 * For example MyPlugin/MyPlugin.js.
 */
function Plugin(pluginPath) {
    this.fileInfo = new QFileInfo(pluginPath);
    this.widget = undefined;
    Plugin.xslt = undefined;
}

/**
 * For debugging.
 */
Plugin.prototype.toString = function() {
    var actionText = "";
    if (!isNull(this.getGuiAction())) {
        actionText = this.getGuiAction().text;
    }
    return "Plugin("
        + "actionText: '" + actionText + "'"
        + ", groupName: " + this.getGroupName()
        + ", filePath: " + this.getFilePath()
        + ")";
};

/**
 * Called once on startup to initialize the plugin, its preference page
 * and its documentation if applicable.
 */
Plugin.prototype.init = function(splash, text) {
    this.initPlugin(splash, text);
    //this.initPreferencePage();
};

/**
 * Called once on startup to post-initialize the plugin.
 */
Plugin.prototype.postInit = function(splash, text) {
    this.postInitPlugin(splash, text);
};

/**
 * Loads the plugin by including its main source file.
 *
 * \param initOnly True: only load the plugin if no file ClassNameInit.js
 * is present.
 */
Plugin.prototype.load = function(initOnly) {
    if (isNull(initOnly)) {
        initOnly = false;
    }

    if (initOnly) {
        var initFilePath = this.getInitFilePath();
        if (new QFileInfo(initFilePath).exists()) {
            return;
        }
    }

    var fileName = this.getFilePath();
    if (!new QFileInfo(fileName).exists()) {
        qWarning("Plugin " + fileName + " not found and not loaded.");
        return;
    }

    include(fileName);
};

/**
 * \internal Called once on startup.
 */
Plugin.prototype.initPlugin = function(splash, text) {
    var className = this.getClassName();
    var path = this.getPath();

    var bak = includeBasePath;
    includeBasePath = path;

    var initFilePath = this.getInitFilePath();
    if (new QFileInfo(initFilePath).exists()) {
        include(initFilePath, className);
        eval("init('" + includeBasePath + "');");
    }
    else {
        eval("if (typeof(" + className + ")!='undefined' && isFunction(" + className + ".init)) {"
             + className + ".init('" + includeBasePath + "', splash, text);"
             + "}");

        /*
        if (!path.contains("/Developer/") && !path.contains("/Examples/")) {
            if (!new QFileInfo(path + "/PreferencesPage.ui").exists()) {
                qDebug("refactoring: ", className);
                this.refactor(false);
                this.refactor(true);
            }
            else {
                qDebug("not refactoring: ", className);
            }
        }
        */
    }

    includeBasePath = bak;

    // TODO: release plugin to free memory:
    //eval(className + " = undefined;");
};

/**
 * \internal Called once in the end after startup.
 */
Plugin.prototype.postInitPlugin = function(splash, text) {
    var className = this.getClassName();
    var path = this.getPath();

    var bak = includeBasePath;
    includeBasePath = path;

    var initFilePath = this.getPostInitFilePath();
    if (new QFileInfo(initFilePath).exists()) {
        include(initFilePath);
        eval("postInit('" + includeBasePath + "');");
    }
    else {
        eval("if (typeof(" + className + ")!='undefined' && isFunction(" + className + ".postInit)) {"
             + className + ".postInit('" + includeBasePath + "', splash, text);"
             + "}"
             );
    }

    includeBasePath = bak;
};

Plugin.prototype.uninit = function() {
    var className = this.getClassName();
    eval(className + " = undefined;");
};

/**
 * \internal Called once on startup.
 */
/*
Plugin.prototype.initPreferencePage = function() {
    var className = this.getClassName();
    var uiFileName = this.getPreferenceFile();

    // load preference page, if one exists
    if (new QFileInfo(uiFileName).exists()) {
        var settingsKey = "PreferencePageInitialized/" + className;
        var alreadyInitialized = RSettings.getBoolValue(settingsKey, false);

        // freak bug FS#406 with custom key codes / command configured:
        //isDeleted("");
        isNull();

        if (alreadyInitialized) {
            return;
        }

        var widget = WidgetFactory.createWidget("", uiFileName);
        try {
            eval("if( !isNull(" + className + ") && isFunction(" + className + ".initPreferences) ) {"
                 + className + ".initPreferences(widget);"
                 + "}");
        } catch (e) {
            qDebug("Plugin.js:", "Plugin has no method initPreferences(): " + e );
        }
        WidgetFactory.restoreState(widget);
        WidgetFactory.saveState(widget);
        WidgetFactory.requiresRestart = false;
        widget.destroy();

        RSettings.setValue(settingsKey, true);
    }
};
*/

/**
 * \return Absolute path of the preference UI definition for this plugin.
 * The file name is PreferencesPage.ui and it must be located in the plugin
 * path to be found.
 */
Plugin.prototype.getPreferenceFile = function() {
    var path = this.getPath();
    var uiFile = new QFileInfo("%1/PreferencesPage.ui".arg(path));
    return uiFile.absoluteFilePath();
};

/**
 * \return True if this plugin has a preferences UI file.
 */
Plugin.prototype.preferenceFileExists = function() {
    var uiFileName = this.getPreferenceFile();
    var ret = (new QFileInfo(uiFileName).exists());
    if (!ret) {
        qWarning("Plugin.js: File does not exists: " + uiFileName);
    }
    return ret;
};

/**
 * \return True if shortcuts can be defined for this plugin (default) or
 *      false if a plugin explicitely defines, that is does not support
 *      shortcuts (ClassName.hasShortcuts()).
 */
Plugin.prototype.hasShortcuts = function() {
    var className = this.getClassName();
    try {
        var ret = true;
        eval("if (typeof(" + className + ")!='undefined' && isFunction(" + className + ".hasShortcuts)) {"
                + "ret = " + className + ".hasShortcuts();"
                + "}");
        return ret;
    } catch (e) {
        debugger;
    }
    return undefined;
};

/**
 * \return True if this plugin has a GUI action (QAction) attached to it
 *      which can be used to launch the action this plugin represents.
 */
Plugin.prototype.hasGuiAction = function() {
    return this.getGuiAction() != null;
};

/**
 * \return The GUI action attached to this plugin.
 */
Plugin.prototype.getGuiAction = function() {
    return RGuiAction.getByScriptFile(this.getFilePath());
};

Plugin.prototype.setPreferenceWidget = function(w) {
    this.widget = w;
};

Plugin.prototype.getPreferenceWidget = function() {
    return this.widget;
};

Plugin.prototype.getGroupName = function() {
    var dir = new QDir(this.fileInfo.path());
    dir.cdUp();
    return dir.dirName();
};

Plugin.prototype.getTitle = function() {
    var title;
    try {
        var className = this.getClassName();
        eval("if( typeof(" + className + ")!='undefined' && isFunction(" + className + ".getTitle) ) {"
                + "title = " + className + ".getTitle();"
                + "}");
        if (!isNull(title)) {
            title = title.replace("&", "");
        }
    } catch (e) {
        qWarning("Plugin.js:", "getTitle(): Exception:", e);
    }
    return title;
};

/**
 * \return The title of this plugin's parent plugin. E.g. for
 *      scripts/Draw/Line/Line2P.js, that's the title returned by
 *      Line.getTitle().
 */
Plugin.prototype.getParentTitle = function() {
    var parentTitle;
    try {
        var gn = this.getGroupName();
        eval("if( " + gn + ".getTitle != undefined ) {"
                + "parentTitle = " + gn + ".getTitle()"
                + "}");
        if (!isNull(parentTitle)) {
            parentTitle = parentTitle.replace("&", "");
        }        
    } catch (e) {
        qWarning("Plugin.js:", "getParentTitle(): Exception:", e);
    }
    return parentTitle;
};

/**
 * \return true If the plugin's parent is "scripts", the top level
 *      directory that contains all script plugins.
 */
Plugin.prototype.isTopLevel = function() {
    return this.getGroupName() === "scripts";
};

Plugin.prototype.getClassName = function() {
    return this.fileInfo.completeBaseName();
};

Plugin.prototype.getPath = function() {
    return this.fileInfo.path();
};

/**
 * \return The ECMAScript file path of the plugin implementation.
 */
Plugin.prototype.getFilePath = function() {
    return this.fileInfo.filePath();
};

/**
 * \return The ECMAScript file path of the plugin init function implementation.
 */
Plugin.prototype.getInitFilePath = function() {
    return this.fileInfo.absolutePath() + QDir.separator + this.fileInfo.completeBaseName() + "Init.js";
};

/**
 * \return The ECMAScript file path of the plugin postInit function implementation.
 */
Plugin.prototype.getPostInitFilePath = function() {
    return this.fileInfo.absolutePath() + QDir.separator + this.fileInfo.completeBaseName() + "PostInit.js";
};

Plugin.prototype.getBaseName = function() {
    return this.fileInfo.completeBaseName();
};

Plugin.prototype.hasDoc = function() {
    return this.getDocPath().exists();
};

Plugin.prototype.getDocPath = function() {
    return new QFileInfo(this.getPath() + "/doc");
};

Plugin.prototype.getDocJsFile = function() {
    return new QFile(this.getDocPath().filePath() + "/" + this.getClassName()
            + "_doc.js");
};

Plugin.prototype.getDocHtmlUrl = function() {
    return QUrl.fromLocalFile(this.getDocPath().absoluteFilePath() + "/"
            + this.getClassName() + "_" + RSettings.getLocale()
            + ".html");
};

Plugin.findByGroupName = function(plugins, groupName) {
    for ( var i = 0; i < plugins.length; ++i) {
        var plugin = plugins[i];
        //qDebug("class name: ", plugin.getClassName(), " groupName: ", groupName);
        if (plugin.getClassName() === groupName) {
            return plugin;
        }
    }
    return undefined;
};

Plugin.getParentPlugin = function(plugins, plugin) {
    var ret = Plugin.findByGroupName(plugins, plugin.getGroupName());
    if (isNull(ret)) {
        qWarning("Plugin.getParentPlugin: no parent plugin found for group name: ", plugin.getGroupName());
    }
    return ret;
};

/**
 * \return Array of all Plugin objects found.
 */
Plugin.getPlugins = function(dir, ignores) {
    var fileMenuList, i, k;
    
    var plugins = new Array();
    var dirFilter = new QDir.Filters(QDir.NoDotAndDotDot, QDir.Readable, QDir.Dirs);
    var sortFlags = new QDir.SortFlags(QDir.NoSort);
    
    // first call without recursion:
    if (isNull(dir)) {
        var args = QCoreApplication.arguments();

        dir = "scripts";
        // fixed set of directories that will be scanned for plugins first to 
        // ensure fixed order of menus:
        fileMenuList = [
                new QFileInfo("scripts/Reset"),
                new QFileInfo("scripts/File"),
                new QFileInfo("scripts/Edit"),
                new QFileInfo("scripts/View"),
                new QFileInfo("scripts/Select"),
                new QFileInfo("scripts/Draw"),
                new QFileInfo("scripts/Dimension"),
                new QFileInfo("scripts/Modify"),
                new QFileInfo("scripts/Snap"),
                new QFileInfo("scripts/Information"),
                new QFileInfo("scripts/Layer"),
                new QFileInfo("scripts/Block"),
                new QFileInfo("scripts/Developer"),
                new QFileInfo("scripts/Cam"),
                new QFileInfo("scripts/Window"),
                new QFileInfo("scripts/Widgets"),
                new QFileInfo("scripts/Examples"),
                new QFileInfo("scripts/Local")
            ];
                
        // append directories not in the list above:
        var menuList = new QDir(dir).entryInfoList(dirFilter, sortFlags);
        for (i=0; i<menuList.length; ++i) {
            if (!fileMenuList.contains(menuList[i], "equals")) {
                fileMenuList.push(menuList[i]);
            }
        }
    } else {
        fileMenuList = new QDir(dir).entryInfoList(dirFilter, sortFlags);
    }
    
    for (i=0; i<fileMenuList.length; ++i) {
        var dirInfo = fileMenuList[i];
        if (!dirInfo.exists()) {
            continue;
        }

        if (Plugin.isIgnored(dirInfo.filePath())) {
            continue;
        }

        // don't dive into translation, doc or Tests folders:
        if (dirInfo.fileName() === "ts" || dirInfo.fileName() === "doc" || dirInfo.fileName() === "Tests") {
            continue;
        }
        var fileInfo = new QFileInfo(dirInfo.filePath() + "/" + dirInfo.fileName() + ".js");
        if (fileInfo.exists() && !Plugin.isIgnored(fileInfo.absoluteFilePath())) {
            plugins.push(new Plugin(fileInfo.filePath()));
        }

        plugins = plugins.concat(Plugin.getPlugins(dirInfo.filePath(), ignores));
    }

    return plugins;
};

Plugin.isIgnored = function(path) {
    if (isNull(Plugin.ignores)) {
        var args = QCoreApplication.arguments();
        Plugin.ignores = [];
        for (var i=1; i < args.length; ++i) {
            if (args[i] === "-ignore") {
                ++i;
                if (isNull(args[i])) {
                    break;
                }
                Plugin.ignores.push(args[i]);
            }
        }
    }

    for (var k=0; k<Plugin.ignores.length; ++k) {
        if (path.contains(Plugin.ignores[k])) {
            return true;
        }
    }

    return false;
};

Plugin.getPluginPath = function(name) {
    var plugins = Plugin.getPlugins();
    for (var i = 0; i < plugins.length; ++i) {
        var plugin = plugins[i];
        if (plugin.getClassName()===name) {
            return plugin.getPath();
        }
    }
};
