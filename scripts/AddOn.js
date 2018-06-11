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

//include("WidgetFactory.js");

/**
 * \class AddOn
 * \brief Initializes and manages all add-ons. Every directory in the
 * script directory of QCAD is a add-on if it contains an ECMAScript
 * file with the same name as the directory and the extension ".js".
 * For example MyAddOn/MyAddOn.js.
 */
function AddOn(addOnPath) {
    this.fileInfo = new QFileInfo(addOnPath);
    this.widget = undefined;
    AddOn.xslt = undefined;
}

/**
 * For debugging.
 */
AddOn.prototype.toString = function() {
    var actionText = "";
    if (!isNull(this.getGuiAction())) {
        actionText = this.getGuiAction().text;
    }
    return "AddOn("
        + "actionText: '" + actionText + "'"
        + ", groupName: " + this.getGroupName()
        + ", filePath: " + this.getFilePath()
        + ")";
};

/**
 * Called once on startup to initialize the add-on, its preference page
 * and its documentation if applicable.
 */
AddOn.prototype.init = function(splash, text) {
    this.initAddOn(splash, text);

    // slow:
    //this.initPreferencePage();
};

/**
 * Called once on startup to post-initialize the add-on.
 */
AddOn.prototype.postInit = function(splash, text) {
    this.postInitAddOn(splash, text);
};

/**
 * Loads the add-on by including its main source file.
 *
 * \param initOnly True: only load the add-on if no file ClassNameInit.js
 * is present.
 */
AddOn.prototype.load = function(initOnly) {
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
        qWarning("AddOn " + fileName + " not found and not loaded.");
        return;
    }

    include(fileName);
};

/**
 * \internal Called once on startup.
 */
AddOn.prototype.initAddOn = function(splash, text) {
    var className = this.getClassName();
    var path = this.getPath();

    var bak = includeBasePath;
    includeBasePath = path;

    var initFilePath = this.getInitFilePath();
    if (new QFileInfo(initFilePath).exists()) {
        include(initFilePath, className, true);
        init(includeBasePath);
    }
    else {
        if (typeof(global[className])!=='undefined' && isFunction(global[className].init)) {
            global[className].init(includeBasePath, splash, text);
        }
    }

    includeBasePath = bak;

    // TODO: release add-on to free memory:
    //global[className] = undefined;
};

/**
 * \internal Called once in the end after startup.
 */
AddOn.prototype.postInitAddOn = function(splash, text) {
    var className = this.getClassName();
    var path = this.getPath();

    var bak = includeBasePath;
    includeBasePath = path;

    var postInitFilePath = this.getPostInitFilePath();
    if (new QFileInfo(postInitFilePath).exists()) {
        include(postInitFilePath);
        postInit(includeBasePath);
    }
    else {
        if (!isNull(global[className]) && isFunction(global[className].postInit)) {
            global[className].postInit(includeBasePath, splash, text);
        }
    }

    includeBasePath = bak;
};

AddOn.prototype.uninit = function() {
    //var className = this.getClassName();
    //global[className] = undefined;
    var className = this.getClassName();
    var path = this.getPath();

    //var bak = includeBasePath;
    //includeBasePath = path;

    var uninitFilePath = this.getUninitFilePath();
    if (new QFileInfo(uninitFilePath).exists()) {
        include(uninitFilePath, className);
        uninit();
    }
    else {
        if (typeof(global[className])!=='undefined' && isFunction(global[className].uninit)) {
            global[className].uninit();
        }
    }

    //includeBasePath = bak;
};

/**
 * \internal Called once on startup.
 */
/*
AddOn.prototype.initPreferencePage = function() {
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
            qDebug("AddOn.js:", "AddOn has no method initPreferences(): " + e );
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
 * \return Absolute path of the preference UI definition for this add-on.
 * The file name is PreferencesPage.ui and it must be located in the add-on
 * path to be found.
 */
AddOn.prototype.getPreferenceFile = function() {
    var path = this.getPath();
    var uiFile = new QFileInfo("%1/PreferencesPage.ui".arg(path));
    return uiFile.absoluteFilePath();
};

/**
 * \return True if this add-on has a preferences UI file.
 */
AddOn.prototype.preferenceFileExists = function() {
    var uiFileName = this.getPreferenceFile();
    var ret = (new QFileInfo(uiFileName).exists());
    if (!ret) {
        qWarning("AddOn.js: File does not exists: " + uiFileName);
    }
    return ret;
};

/**
 * \return True if shortcuts can be defined for this add-on (default) or
 *      false if a add-on explicitely defines, that is does not support
 *      shortcuts (ClassName.hasShortcuts()).
 */
AddOn.prototype.hasShortcuts = function() {
    var className = this.getClassName();
    try {
        var ret = true;
        if (!isNull(global[className]) && isFunction(global[className].hasShortcuts)) {
            ret = global[className].hasShortcuts();
        }
        return ret;
    } catch (e) {
        debugger;
    }
    return undefined;
};

/**
 * \return True if this add-on has a GUI action (QAction) attached to it
 *      which can be used to launch the action this add-on represents.
 */
AddOn.prototype.hasGuiAction = function() {
    return this.getGuiAction() != null;
};

/**
 * \return The GUI action attached to this add-on.
 */
AddOn.prototype.getGuiAction = function() {
    return RGuiAction.getByScriptFile(this.getFilePath());
};

AddOn.prototype.setPreferenceWidget = function(w) {
    this.widget = w;
};

AddOn.prototype.getPreferenceWidget = function() {
    return this.widget;
};

AddOn.prototype.getGroupName = function() {
    var dir = new QDir(this.fileInfo.path());
    dir.cdUp();
    return dir.dirName();
};

/**
 * \return Translated title of this add on (from GUI action or class info).
 */
AddOn.prototype.getTitle = function() {
    var title;

    // try to get title from class (getTitle):
    var className = this.getClassName();
    title = AddOn.getClassTitle(className);

    if (isNull(title)) {
        // try to get title from gui action:
        var a = this.getGuiAction();
        if (!isNull(a)) {
            title = a.text;
        }
    }

    if (!isNull(title)) {
        title = title.replace("&", "");

        // remove everything after tab (shortcuts under windows):
        if (title.indexOf("\t")!==-1) {
            title = title.substring(0, title.indexOf("\t"));
        }
    }

    return title;
};

/**
 * \return The title of this add-on's parent add-on. E.g. for
 *      scripts/Draw/Line/Line2P.js, that's the title returned by
 *      Line.getTitle().
 */
AddOn.prototype.getParentTitle = function() {
    var gn = this.getGroupName();
    return AddOn.getClassTitle(gn);
};

/**
 * \return Translated title for the given class name.
 */
AddOn.getClassTitle = function(cn) {
    var title;
    try {
        if (!isNull(global[cn]) && isFunction(global[cn].getTitle)) {
            title = global[cn].getTitle();
        }
    } catch (e) {
        qWarning("AddOn.js:", "getClassTitle(): Exception:", e);
    }

    if (!isNull(title)) {
        title = title.replace("&", "");
    }
    return title;
};

/**
 * \return Hierarchy of titles for this add on (e.g. [Draw, Line, Line 2P]).
 */
AddOn.prototype.getParentTitles = function() {
    var ret = [];

    var dir = new QDir(this.fileInfo.path());
    ret.unshift(this.getTitle());
    do {
        if (!dir.cdUp()) {
            break;
        }
        var dn = dir.dirName();
        var title = AddOn.getClassTitle(dn);
        if (isNull(title)) {
            break;
        }
        ret.unshift(title);

    } while (true);

    return ret;
};

/**
 * \return true If the add-on's parent is "scripts", the top level
 *      directory that contains all script add-ons.
 */
AddOn.prototype.isTopLevel = function() {
    return this.getGroupName() === "scripts";
};

AddOn.prototype.getClassName = function() {
    return this.fileInfo.completeBaseName();
};

AddOn.prototype.getPath = function() {
    return this.fileInfo.path();
};

/**
 * \return The ECMAScript file path of the add-on implementation.
 */
AddOn.prototype.getFilePath = function() {
    return this.fileInfo.filePath();
};

/**
 * \return The ECMAScript file path of the add-on init function implementation.
 */
AddOn.prototype.getInitFilePath = function() {
    return this.fileInfo.absolutePath() + QDir.separator + this.fileInfo.completeBaseName() + "Init.js";
};

/**
 * \return The ECMAScript file path of the add-on postInit function implementation.
 */
AddOn.prototype.getPostInitFilePath = function() {
    return this.fileInfo.absolutePath() + QDir.separator + this.fileInfo.completeBaseName() + "PostInit.js";
};

AddOn.prototype.getUninitFilePath = function() {
    return this.fileInfo.absolutePath() + QDir.separator + this.fileInfo.completeBaseName() + "Uninit.js";
};

AddOn.prototype.getBaseName = function() {
    return this.fileInfo.completeBaseName();
};

AddOn.prototype.hasDoc = function() {
    return this.getDocPath().exists();
};

AddOn.prototype.getDocPath = function() {
    return new QFileInfo(this.getPath() + "/doc");
};

AddOn.prototype.getDocJsFile = function() {
    return new QFile(this.getDocPath().filePath() + "/" + this.getClassName()
            + "_doc.js");
};

AddOn.prototype.getDocHtmlUrl = function() {
    return QUrl.fromLocalFile(this.getDocPath().absoluteFilePath() + "/"
            + this.getClassName() + "_" + RSettings.getLocale()
            + ".html");
};

AddOn.findByGroupName = function(addOns, groupName) {
    for ( var i = 0; i < addOns.length; ++i) {
        var addOn = addOns[i];
        //qDebug("class name: ", addOn.getClassName(), " groupName: ", groupName);
        if (addOn.getClassName() === groupName) {
            return addOn;
        }
    }
    return undefined;
};

AddOn.getParentAddOn = function(addOns, addOn) {
    var ret = AddOn.findByGroupName(addOns, addOn.getGroupName());
    if (isNull(ret)) {
        qWarning("AddOn.getParentAddOn: no parent add-on found for group name: ", addOn.getGroupName());
    }
    return ret;
};

/**
 * \return Array of all AddOn objects found.
 *
 * \param dir Used internally for recursive calls
 */
AddOn.getAddOns = function(dir) {
    var topCall = isNull(dir);
    if (topCall && !isNull(AddOn.addOns)) {
        // return cached list:
        return AddOn.addOns;
    }

    var fileMenuList, i, k;

    var addOns = [];
    var dirFilter = new QDir.Filters(QDir.NoDotAndDotDot, QDir.Readable, QDir.Dirs);
    var sortFlags = new QDir.SortFlags(QDir.NoSort);
    
    // first call without recursion:
    if (topCall) {
        var args = QCoreApplication.arguments();

        // ignore all scripts in ./scripts directory
        // and only load scripts from plugins
        // used mainly for testing / development
        if (RSettings.getOriginalArguments().contains("-ignore-script-files")) {
            dir = undefined;
        }
        else {
            dir = "scripts";
        }

        // fixed set of directories that will be scanned for add-ons first to 
        // ensure fixed order of menus and tool bars:
        fileMenuList = [
                // scripts compiled as resources in plugins:
                new QFileInfo(":scripts"),
                // local scripts:
                new QFileInfo(RSettings.getDataLocation() + "/scripts"),
            ];

        // local scripts from installed add-ons:
        var localAddOns = AddOn.getLocalAddOns();

        for (i=0; i<localAddOns.length; i++) {
            var localAddOnDir = RSettings.getDataLocation() + "/" + localAddOns[i] + "/scripts";
            var fi = new QFileInfo(localAddOnDir);
            if (fi.exists()) {
                qDebug("adding scripts dir of add-on: ", localAddOnDir);
                fileMenuList.push(fi);
            }
        }

        // append directories not in the list above:
        if (!isNull(dir)) {
            var menuList = new QDir(dir).entryInfoList(dirFilter, sortFlags);
            for (i=0; i<menuList.length; ++i) {
                if (!fileMenuList.contains(menuList[i], function(a,b) { return a.absoluteFilePath()===b.absoluteFilePath(); })) {
                    fileMenuList.push(menuList[i]);
                }
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

        if (AddOn.isIgnored(dirInfo.filePath())) {
            continue;
        }

        // don't dive into translation, doc or Tests folders:
        if (dirInfo.fileName() === "ts" || dirInfo.fileName() === "doc" || dirInfo.fileName() === "Tests") {
            continue;
        }
        var fileInfo = new QFileInfo(dirInfo.filePath() + "/" + dirInfo.fileName() + ".js");

        if (dirInfo.fileName().startsWith("AutoLoad")) {
            RAutoLoadEcma.addAutoLoadFile(fileInfo.filePath());
        }
        else {
            if (fileInfo.exists() && !AddOn.isIgnored(fileInfo.absoluteFilePath())) {
//                if (addOns.contains(fileInfo.filePath(), function(a,b) { qDebug(a.getPath(), b); return a.getPath()===b; })) {
//                    qDebug("already loaded: ", fileInfo.filePath());
//                }

                if (!addOns.contains(fileInfo.filePath(), function(a,b) { return a.getPath()===b; })) {
                    addOns.push(new AddOn(fileInfo.filePath()));
                }
            }
        }

        addOns = addOns.concat(AddOn.getAddOns(dirInfo.filePath()));
    }

    if (topCall) {
        // sort add ons by menu order:
        var menuNames = {
                    "Reset":10, "File":20, "Edit":30, "View":40, "Select":50, "Draw":60, "Dimension":70,
                    "Modify":80, "Snap":90, "Information":100, "Layer":110, "Block":120, "Developer":130,
                    "Window":140, "Widgets":150, "Misc":160, "Local":170, "Help":100000
                };

        var rx1 = new RegExp(":?\/?scripts\/");
        var rx2 = new RegExp("\/.*");
        var gotRegularFile = false;
        addOns.sort(function(a,b) {
            var aPath = a.getPath();
            var bPath = b.getPath();

            if (!gotRegularFile && (aPath[0]!==":" || bPath[0]!==":")) {
                gotRegularFile = true;
            }

            // get top dir name after scripts (e.g. 'File', 'Layer', ...):
            var da = aPath.replace(rx1, "").replace(rx2, "");
            var db = bPath.replace(rx1, "").replace(rx2, "");

            // first priority:
            // sort by predefined menu order:
            // get sort order from menuNames map:
            var oa = menuNames[da];
            var ob = menuNames[db];

            // menu not in list:
            // insert between Local and Help:
            if (isNull(oa)) {
                oa = 1000;
            }
            if (isNull(ob)) {
                ob = 1000;
            }

            if (oa!==ob) {
                return oa-ob;
            }

            // secondary priority:
            // sort alphabetically:
            var aPathNoColon = aPath;
            var bPathNoColon = bPath;
            if (aPathNoColon[0]===":") {
                aPathNoColon = aPathNoColon.substring(1);
            }
            if (bPathNoColon[0]===":") {
                bPathNoColon = bPathNoColon.substring(1);
            }

            if (aPathNoColon!==bPathNoColon) {
                return (aPathNoColon>bPathNoColon) ? 1 : -1;
            }

            // prioritize 'scripts' paths (QCAD) over ':scripts' (plugin):
            if (!aPath.startsWith(":") && bPath.startsWith(":")) {
                return -1;
            }
            else if (aPath.startsWith(":") && !bPath.startsWith(":")) {
                return 1;
            }
            else {
                return 0;
            }
        });

//        for (var i=0; i<addOns.length; i++) {
//            qDebug("addOn: ", addOns[i].getPath());
//        }

        if (gotRegularFile) {
            // filter out duplicate paths from plugins:
            // files take priority over resources:
            var addOnsFiltered = [];
            var prevPathNoColon = undefined;
            for (var i=0; i<addOns.length; i++) {
                var addOn = addOns[i];
                var pathNoColon = addOn.fileInfo.filePath();
                if (pathNoColon[0]===":") {
                    pathNoColon = pathNoColon.substring(1);
                }

                if (!isNull(prevPathNoColon) && prevPathNoColon===pathNoColon) {
                    continue;
                }

                addOnsFiltered.push(addOn);

                prevPathNoColon = pathNoColon;
            }
            addOns = addOnsFiltered;
        }

        // cache:
        AddOn.addOns = addOns;
    }

    return addOns;
};

AddOn.getLocalAddOns = function() {
    var dataDir = new QDir(RSettings.getDataLocation());
    var fs = new QDir.Filters(QDir.NoDotAndDotDot, QDir.Readable, QDir.Dirs, QDir.Executable);
    var sf = new QDir.SortFlags(QDir.Name);
    return dataDir.entryList([], fs, sf);
};

AddOn.isIgnored = function(path) {
    if (isNull(AddOn.ignores)) {
        var args = QCoreApplication.arguments();
        AddOn.ignores = [];
        for (var i=1; i < args.length; ++i) {
            if (args[i] === "-ignore") {
                ++i;
                if (isNull(args[i])) {
                    break;
                }
                AddOn.ignores.push(args[i]);
            }
        }
    }

    for (var k=0; k<AddOn.ignores.length; ++k) {
        if (path.contains(AddOn.ignores[k])) {
            return true;
        }
    }

    return false;
};

AddOn.getAddOnPath = function(name) {
    var addOns = AddOn.getAddOns();
    for (var i = 0; i < addOns.length; ++i) {
        var addOn = addOns[i];
        if (addOn.getClassName()===name) {
            return addOn.getPath();
        }
    }
};
