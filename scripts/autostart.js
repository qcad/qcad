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

include("library.js");
include("AddOn.js");
include("scripts/File/OpenFile/OpenFile.js");
include("scripts/File/AutoSave/AutoSave.js");
include("scripts/Tools/arguments.js");

// allow plugins to extend autostart through autostart1.js, autostart2.js, ...:
for (var i=1; i<10; i++) {
    var fn = "scripts/autostart" + i + ".js";
    if (new QFileInfo(fn).exists() || new QFileInfo(":/" + fn).exists()) {
        include(fn);
    }
}


/**
 * Prints version information.
 */
function version() {
    print();
    print("Version: " + RSettings.getVersionString());
    print("Qt Version: " + RSettings.getQtVersionString());
    print("Release Date: " + RSettings.getReleaseDate());
    print();
}

/**
 * Prints command line usage information on stdout.
 */
function usage() {
    print("\nUsage: " + QCoreApplication.arguments()[0] + " [Options] [Files to open]\n"
          + "\n"
          + "-allow-multiple-instances        Don't try to avoid multiple instances from running\n"
          + "                                 simultaneously.\n"
          + "-always-load-scripts             Forces reloading of scripts when they are used.\n"
          + "                                 This is mainly useful during script development,\n"
          + "                                 to apply changes without restarting QCAD.\n"
          + "-app-id [ID]                     Set application ID. Multiple instances of the\n"
          + "                                 same application (same ID) cannot run\n"
          + "                                 simultaneously unless -allow-multiple-instances\n"
          + "                                 is used.\n"
          + "-autostart [script file]         Starts the given script file instead of the default\n"
          + "                                 scripts/autostart.js. Note that with this option,\n"
          + "                                 QCAD is not started but rather the application \n"
          + "                                 implemented in the given script.\n"
          + "-config [path]                   Reads and stores settings in a configuration file\n"
          + "                                 at the given location instead of the default location.\n"
          + "-debug-action-order              Print action order information in menus\n"
          + "-enable-script-debugger          Enables the script debugger.\n"
          + "                                 NOT recommended as this may cause unexpected\n"
          + "                                 behavior when using QCAD.\n"
          + "-exec [script file] [options]    Executes the given script file directly\n"
          + "                                 after staring QCAD. Options after the script\n"
          + "                                 file are passed on to the script.\n"
          + "-help                            Displays this help.\n"
          + "-ignore-script-files             Ignore script files on disk.\n"
          + "                                 Only load scripts from plugins if applicable.\n"
          + "-locale [locale]                 Sets the locale to be used (overrides\n"
          + "                                 the language set in the preferences).\n"
          + "                                 E.g. '-locale de' starts QCAD in German.\n"
          + "-no-gui                          Don't use GUI. X11: don't connect to X11 server.\n"
          + "-no-show                         Use but don't display GUI.\n"
          + "-filter [filter]                 Opens the subsequent file(s) with the explicitly \n"
          + "                                 given import filter.\n"
          + "-font-substitution A B           Substitute font A with font B.\n"
          + "-rescan                          Rescan scripts folder for new add-ons\n"
          + "-version                         Displays the application version.\n"
          + "-enable-xdata                    Enables XData (custom properties) support.\n"
          + "-quit                            Quits QCAD, for example after executing the\n"
          + "                                 given script(s).\n"
    );

    printGenericUsage();

    print("\n");
}

/**
 * Open files given as arguments args
 *
 * \param createNew Creates a new document if no files are given
 * \param close Closes existing open MDI widgets
 */
function openFiles(args, createNew, close) {
    var appWin = RMainWindowQt.getMainWindow();
    if (isNull(appWin)) {
        // application is shutting down..
        return;
    }
    var mdiArea = appWin.getMdiArea();
    var mdiChildren = mdiArea.subWindowList();
    var foundFile = false;
    var filter = undefined;

    for (var i = 0; i < args.length; ++i) {
        // arguments with one parameter:
        if (args[i] === "-locale" || args[i] === "-autostart"
            || args[i] === "-app-id" || args[i] === "-ignore"
            || args[i] === "-config") {
            // skip 2 arguments
            i++;
            if (i>=args.length) {
                break;
            }
            continue;
        }

        // argument with two parameters
        if (args[i] === "-font-substitution" || args[i] === "-fs" || args[i] === "-ts") {
            // skip 3 arguments
            i+=2;
            if (i>=args.length) {
                break;
            }
            continue;
        }

        if (isNull(args[i])) {
            continue;
        }

        // all arguments after -exec are script files or script arguments:
        if (args[i] === "-exec") {
            break;
        }

        if (args[i] === "-filter") {
            if (++i>=args.length) {
                break;
            }
            filter = args[i];
            continue;
        }


        // skip other arguments without parameter:
        if (args[i][0] === "-") {
            continue;
        }

        foundFile = true;
        var foundExisting = false;

        var arg = args[i];
        var isLocalFile = true;

        if (isUrl(arg)) {
            var url = new QUrl(arg);
            if (url.isLocalFile()) {
                // arg is now a path:
                arg = url.toLocalFile();
            }
            else {
                isLocalFile = false;
            }
        }

        if (isLocalFile) {
            // if the file is already open, activate that appropriate sub window instead
            // of opening the file again:
            var document = undefined;
            var fileName = undefined;
            var fileInfo = undefined;
            var argFileInfo = undefined;
            for (var k=0; k<mdiChildren.length; k++) {
                document = mdiChildren[k].getDocument();
                fileName = document.getFileName();
                fileInfo = new QFileInfo(fileName);
                argFileInfo = new QFileInfo(getAbsolutePathForArg(arg));

                if (fileInfo.absoluteFilePath()===argFileInfo.absoluteFilePath()) {
                    mdiArea.setActiveSubWindow(mdiChildren[k]);
                    if (close) {
                        mdiArea.closeActiveSubWindow();
                    }
                    else {
                        foundExisting = true;
                    }
                    break;
                }
            }
        }

        // open the file if it is not already open:
        if (!foundExisting) {
            if (isLocalFile) {
                NewFile.createMdiChild(getAbsolutePathForArg(arg), filter);
            }
            else {
                NewFile.createMdiChild(arg, filter);
            }
        }
    }

    // create new document if no files were loaded:
    if (!foundFile && createNew===true) {
        var fileNewAction = RGuiAction.getByScriptFile("scripts/File/NewFile/NewFile.js");
        if (!isNull(fileNewAction)) {
            fileNewAction.slotTrigger();
        }
    }
}

/**
 * Executes the scripts that are given as arguments of -exec.
 * \return true if the application should quit after executing the
 * scripts, false otherwise.
 */
function execScripts(args) {
    for (var i = 1; i < args.length; ++i) {
        if (args[i] === "-exec") {
            ++i;
            if (isNull(args[i])) {
                break;
            }

            // check for existing action (e.g. "scripts/File/NewFile/NewFile.js"):
            var action = RGuiAction.getByScriptFile(args[i]);

            // script is not an existing action:
            if (isNull(action)) {
                // include (run) script which might or might not be action:
                var scriptFile = args[i];
                var scriptFilePath = getAbsolutePathForArg(scriptFile);
                if (new QFileInfo(scriptFilePath).exists()) {

                    // including the script evaluates (runs) it:
                    include(scriptFilePath);

                    // check if script created a class of same name as file base name:
                    var fi = new QFileInfo(scriptFile);
                    var className = fi.baseName();
                    if (!isNull(global[className])) {
                        // gui action might not exist yet for this script, create one:
                        action = new RGuiAction("");
                        action.setScriptFile(scriptFilePath);
                        action.setRequiresDocument(false);
                    }
                }
                else {
                    qWarning("script not found: ", args[i]);
                }
            }

            // script is action or created action:
            if (!isNull(action)) {
                ++i;
                // handle script arguments:
                while (!isNull(args[i]) && args[i] !== "-exec") {
                    action.addArgument(args[i]);
                    ++i;
                }
                --i;
                action.slotTrigger();
            }
        }
        if (args[i] === "-quit") {
            RSettings.setQuitFlag();
        }
    }
}

/**
 * Sets up drag and drop support (droping files on the application window
 * opens them).
 */
function setUpDragAndDrop(appWin) {
    appWin.dragEnter.connect(function(event) {
        event.acceptProposedAction();
    });

    appWin.drop.connect(function(evt) {
        // workaround for Qt keyboard focus bug:
        var appWin = RMainWindowQt.getMainWindow();
        if (!isNull(appWin)) {
            appWin.activateWindow();
            appWin.raise();
            appWin.setFocus(Qt.OtherFocusReason);
        }

        var urls = getUrlsFromMimeData(evt.mimeData());
        var urlStrings = [];
        for (var i = 0; i < urls.length; ++i) {
            urlStrings.push(urls[i].toString());
        }

        openFiles(urlStrings, false);
    });
}

/**
 * Loads translations for all add-ons if appropriate.
 */
function loadTranslations(addOns, splash) {
    var locale = RSettings.getLocale();

    if (!isNull(splash)) {
        // no translations yet:
        splash.showMessage("Loading translations...\n", Qt.AlignBottom);
    }

    // load C++ translations:
    var modules = ["qt", "assistant", "qt_help", "qcadcore", "qcadentity", "qcadgui"];
    if (RSettings.isQt(5)) {
        modules.unshift("qtbase");
    }

    var i;
    var module;

    for (var mi=0; mi<modules.length; ++mi) {
        module = modules[mi];

        RSettings.loadTranslations(module);
    }

    //RSettings.loadTranslations("scripts_" + locale, [autoPath("scripts/ts")]);

    // load translations from arguments:
    var args = QCoreApplication.arguments();
    for (i = 0; i < args.length; ++i) {
        if (args[i] === "-ts") {
            if (++i>=args.length) {
                break;
            }
            module = args[i];
            if (++i>=args.length) {
                break;
            }
            var dir = args[i];

            RSettings.loadTranslations(module, [autoPath(dir)]);
        }
    }

//    RSettings.loadTranslations("scripts", [autoPath("ts")]);
//    RSettings.loadTranslations("proscripts", [autoPath("../qcadpro/ts")]);
//    RSettings.loadTranslations("camscripts", [autoPath("../qcadcam/ts")]);

    // install one QTranslator for each script add-on if available:
    if (!isNull(splash)) {
        splash.showMessage(qsTr("Loading add-on translations...") + "\n", Qt.AlignBottom);
        QCoreApplication.processEvents();
    }

    //RSettings.loadTranslations("Scripts_" + locale, [autoPath("scripts/ts")]);

    for (i = 0; i < addOns.length; ++i) {
        var addOn = addOns[i];
        if (isNull(addOn)) {
            qWarning("Null add on found");
            continue;
        }

        var fi = new QFileInfo(addOn.getPath() + "/ts");
        if (!fi.exists()) {
            // no ts dir:
            continue;
        }

        RSettings.loadTranslations(addOn.getClassName(), [addOn.getPath() + "/ts"]);
    }
}

/**
 * Loads and initializes all add-ons.
 *
 * \param addOns array of AddOn objects.
 * \param splash the splash window for displaying status updates.
 */
function loadAddOns(addOns, splash) {
    if (!isNull(splash)) {
        splash.showMessage(qsTr("Loading add-ons...") + "\n", Qt.AlignBottom);
        QCoreApplication.processEvents();
    }

    var addOn;
    var i;

    for (i=0; i<addOns.length; ++i) {
        addOn = addOns[i];
        addOn.load(true);
    }
}

function initAddOns(addOns, splash) {
    if (!isNull(splash)) {
        splash.showMessage(qsTr("Initializing add-ons...") + "\n", Qt.AlignBottom);
        QCoreApplication.processEvents();
    }

    var addOn;
    var i;
    var text = "";

    for (i=0; i<addOns.length; ++i) {
        addOn = addOns[i];
        if (i%10===0 && !isNull(splash)) {
            text = qsTr("Initializing add-ons:") +
                " %1%\n%2"
                .arg(Math.round(i/addOns.length*100))
                .arg(addOn.getClassName());
            splash.showMessage(text, Qt.AlignBottom);
            QCoreApplication.processEvents();
        }
        addOn.init(splash, text);
    }
}

function postInitAddOns(addOns, splash) {
//    if (!isNull(splash)) {
//        splash.showMessage(qsTr("Post-initializing add-ons...") + "\n", Qt.AlignBottom);
//        QCoreApplication.processEvents();
//    }

    var addOn;
    var i;

    var viewToolBarsAddOn = undefined;
    for (i=0; i<addOns.length; ++i) {
        addOn = addOns[i];
        if (addOn.getClassName()==="ViewToolbars") {
            viewToolBarsAddOn = addOn;
        }
        else {
            addOn.postInit();
        }
    }

    if (!isNull(viewToolBarsAddOn)) {
        viewToolBarsAddOn.postInit();
    }
}

function uninitAddOns(addOns) {
    var addOn;
    var i;

    for (i=0; i<addOns.length; ++i) {
        addOn = addOns[i];
        addOn.uninit();
    }
}

/**
 * Loads the add-ons and starts QCAD.
 */
function main() {
    var i;
    var filesToOpen = [];

    // open file that was clicked in Finder if application was not yet running (Mac OS X):
    qApp.fileOpenRequestReceived.connect(function(fileName) {
        filesToOpen.push(fileName);
    });

    // open file(s) given on command line when application is started but
    // already running:
    qApp.messageReceived.connect(function(message) {
        var args = message.split("\n");
        openFiles(args.slice(1), false);
        execScripts(args);
    });

    var args = QCoreApplication.arguments();
    if (args.contains("-help") || args.contains("-h")) {
        usage();
        return;
    }
    if (args.contains("-version") || args.contains("-v")) {
        version();
        return;
    }
    if (args.contains("-enable-xdata")) {
        RSettings.setXDataEnabled(true);
    }

    // app name for ini file differs to avoid conflict with
    // older QCAD versions:
    // note that a plugin might have set a name override already:
    if (!RSettings.hasApplicationNameOverride()) {
        RSettings.setApplicationNameOverride("QCAD3");
    }
    // make sure settings file path is reinitialized:
    RSettings.uninit();

    // alternative path for QCAD3.ini:
    for (i=1; i<args.length; ++i) {
        if (args[i] === "-config") {
            ++i;
            if (i < args.length) {
                QSettings.setPath(QSettings.IniFormat, QSettings.UserScope, getAbsolutePathForArg(args[i]));
            }
        }
    }

    // ignore config file if it does not identify itself with a version
    // number or is known as being incompatible
    var reset = false;
    var ignoreDockappWindows = false;
    var newVersion = false;
    if (RSettings.getStringValue("Application/Version", "").length===0) {
        reset = true;
    }

    // Prevent errors with old configuration files:
    // QCAD 3 Beta
    if (RSettings.getIntValue("Application/Version", 0)<=3000003) {
        reset = true;
    }

    // Prevent errors with old configuration files:
    // QCAD 3 RC2/3: Reset toolbar location
    if (RSettings.hasValue("Application/Version") && RSettings.getIntValue("Application/Version", 0)<=3000006) {
        ignoreDockappWindows = true;
    }

    // Prevent errors with old configuration files:
    // QCAD 3 <= RC5: grid color without alpha, RC6: alpha added, ignore some color settings:
    if (RSettings.getIntValue("Application/Version", 0)<=3000008) {
        RSettings.removeValue("GraphicsViewColors/MetaGridColor");
        RSettings.removeValue("GraphicsViewColors/OriginColor");
        RSettings.removeValue("GraphicsViewColors/RelativeZeroColor");
        RSettings.removeValue("GraphicsViewColors/GridColor");
        RSettings.removeValue("GraphicsViewColors/SelectionColor");
    }

    if (RSettings.getStringValue("Application/Version", "")!==RSettings.getNumericalVersionString()) {
        newVersion = true;
    }

    if (reset===true) {
        var configFile = RSettings.getFileName();
        RSettings.uninit();
        var fi = new QFileInfo(configFile);
        if (fi.exists()) {
            var configPath = fi.absolutePath();
            var configBak = configPath + QDir.separator + fi.baseName() + "_old." + fi.suffix();
            qDebug("Renaming old unversioned config file from '" + configFile + "' to '"+ configBak + "'");
            QFile.remove(configBak);
            QFile.rename(configFile, configBak);
        }
    }

    // detect very first start of this installation:
    var fiSettings = new QFileInfo(RSettings.getQSettings().fileName());
    var isFirstStart = !fiSettings.exists();

    var numPlugins = RPluginLoader.countPlugins();
    var pluginInfo;

    // look up app name override:
    for (i=0; i<numPlugins; i++) {
        pluginInfo = RPluginLoader.getPluginInfo(i);
        var n = pluginInfo.get("NameOverride");
        if (!isNull(n)) {
            qApp.applicationName = n;
        }
    }

    // if locale is given, don't show first start dialog:
    if (isFirstStart && !QCoreApplication.arguments().contains("-locale")) {
        include("Widgets/FirstStart/FirstStart.js");
        var first = new FirstStart();
        first.showDialog();
    }

    RPluginLoader.initTranslations();

    // correct library paths from 'library' to 'libraries':
    if (RSettings.getIntValue("Application/Version", 0)<=3000008) {
        var oldDefaultSource = new QFileInfo("library").absoluteFilePath();
        var librarySources = RSettings.getValue("LibraryBrowser/SourceList", []);
        if (!isNull(librarySources)) {
            for (i=0; i<librarySources.length; i++) {
                if (new QFileInfo(librarySources[i]).absoluteFilePath()===oldDefaultSource) {
                    librarySources[i] = new QFileInfo("libraries/default").absoluteFilePath();
                }
            }
            RSettings.setValue("LibraryBrowser/SourceList", librarySources);
        }
    }

    // theme:
    applyTheme();

    // native / non-native menubar:
    if (RSettings.getBoolValue("MenuBar/UseNativeMenuBar", true)===false) {
        QCoreApplication.setAttribute(Qt.AA_DontUseNativeMenuBar);
    }

    // splash:
    var splash = undefined;
    if (RSettings.getBoolValue("Startup/EnableSplashScreen", true)) {
        var fn;
        var key;
        if (RSettings.getDevicePixelRatio()===2) {
            key = "SplashOverride@2x";
            fn = "scripts/splashscreen@2x.png";
        }
        else {
            key = "SplashOverride";
            fn = "scripts/splashscreen.png";
        }

        // look up slash screen override:
        var maxPri = undefined;
        for (i=0; i<numPlugins; i++) {
            pluginInfo = RPluginLoader.getPluginInfo(i);

            // override priority:
            var pri = pluginInfo.get("OverridePriority");
            if (!isNull(pri)) {
                pri = parseInt(pri);
            }
            else {
                // default to lowest priority:
                pri = 0;
            }

            if (isNull(maxPri) || pri>maxPri) {
                var s = pluginInfo.get(key);
                if (!isNull(s)) {
                    fn = s;
                    maxPri = pri;
                }
            }
        }

        var pixmap = new QPixmap(fn);
        splash = new QSplashScreen(pixmap);
        splash.objectName = "Splash";
        if (!QCoreApplication.arguments().contains("-no-show")) {
            splash.show();
        }
    }

    RFontList.initSubstitutions();

    // mark config file with current version number:
    var previousVersion = RSettings.getStringValue("Application/Version", "");
    RSettings.setValue("Application/Version", RSettings.getNumericalVersionString());

    // save first start information:
    RSettings.setFirstStart(isFirstStart);
    // save new version information:
    RSettings.setNewVersion(newVersion);
    RSettings.setPreviousVersion(parseInt(previousVersion, 10));

    RPluginLoader.postInitPlugins(RPluginInterface.GotSplashWindow);

    // scan for script add-ons (forced for first start, first start after
    // update, if configured):
    var addOns;
    var addOnFilePaths = RSettings.getValue("AddOns/List", []);
    if (addOnFilePaths.length===0 || newVersion ||
            QCoreApplication.arguments().contains("-rescan") ||
            RSettings.getBoolValue("Scripting/Rescan", true)===true) {

        if (!isNull(splash)) {
            // no translations yet:
            splash.showMessage("...\n", Qt.AlignBottom);
            QCoreApplication.processEvents();
        }
        addOns = AddOn.getAddOns();

        var addOnList = [];
        for (i = 0; i < addOns.length; ++i) {
            addOnList.push(addOns[i].getFilePath());
        }
        RSettings.setValue("AddOns/List", addOnList);
    }
    else {
        addOns = [];
        for (i=0; i<addOnFilePaths.length; i++) {
            addOns.push(new AddOn(addOnFilePaths[i]));
        }
    }

    // load add-on translations:
    loadTranslations(addOns, splash);

    // create application window:
    var appWin = new RMainWindowQt();

    // Note: animated MUST be true for Qt 5.7:
    // Qt 5.7.0 will not allow tabifying dock widgets if animations are turned off:
    if (RSettings.getQtVersion()<0x050600) {
        // animated must be false for Qt 4.7.2, 5.6.0 (crashes):
        appWin.animated = false;
    }

    appWin.objectName = "MainWindow";
    appWin.windowTitle = qApp.applicationName;

    // save locale
    appWin.setProperty("Locale", RSettings.getLocale());
    
    // set some object names for later look up:
    var menuBar = appWin.menuBar();
    menuBar.objectName = "MenuBar";

    // load add-ons:
    //RDebug.startTimer(0);
    loadAddOns(addOns, splash);
    //RDebug.stopTimer(0, "loading add-ons");

    //RDebug.startTimer(0);
    initAddOns(addOns, splash);
    //RDebug.stopTimer(0, "initializing add-ons");

    // auto load scripts in AutoLoad folders for global script engine:
    var files = RAutoLoadEcma.getAutoLoadFiles();
    for (i=0; i<files.length; i++) {
        include(files[i]);
    }

    RPluginLoader.postInitPlugins(RPluginInterface.AddOnsInitialized);

    addActionsToWidgets();

    RPluginLoader.postInitPlugins(RPluginInterface.ActionsAdded);

    appWin.updateGuiActions();
    appWin.acceptDrops = true;
    appWin.dockNestingEnabled = true;
    appWin.setCorner(Qt.TopLeftCorner, Qt.LeftDockWidgetArea);
    appWin.setCorner(Qt.BottomLeftCorner, Qt.LeftDockWidgetArea);
    appWin.setCorner(Qt.TopRightCorner, Qt.RightDockWidgetArea);
    appWin.setCorner(Qt.BottomRightCorner, Qt.RightDockWidgetArea);
    appWin.setTabPosition(Qt.RightDockWidgetArea, QTabWidget.West);
    appWin.setTabPosition(Qt.LeftDockWidgetArea, QTabWidget.South);
    appWin.setTabPosition(Qt.TopDockWidgetArea, QTabWidget.South);
    appWin.setTabPosition(Qt.BottomDockWidgetArea, QTabWidget.West);

    setUpDragAndDrop(appWin);

    appWin.windowIcon = new QIcon(autoPath("scripts/qcad_icon.png"));
    if (!ignoreDockappWindows) {
        appWin.readSettings();
    }

    RPluginLoader.postInitPlugins(RPluginInterface.GotMainWindowBeforeShow);

    if (!QCoreApplication.arguments().contains("-no-show")) {
        appWin.show();
    }

    if (!isNull(splash)) {
        splash.close();
        splash.destroy();
    }

    postInitAddOns(addOns);
    RPluginLoader.postInitPlugins(RPluginInterface.GotMainWindow);

    // if the window position / size was not read from a config file,
    // automatically position property editor and library browser (first start):
    if (isFirstStart) {
        var propertyEditorDock = appWin.findChild("PropertyEditorDock");
        if (!isNull(propertyEditorDock)) {
            if (propertyEditorDock["Initialized"]!==true) {
                propertyEditorDock.floating = true;
                propertyEditorDock.move(appWin.x + appWin.width + 20, appWin.y);
                propertyEditorDock.resize(300, appWin.height/3*2);
            }
        }

        var libraryBrowserDock = appWin.findChild("LibraryBrowserDock");
        if (!isNull(libraryBrowserDock)) {
            if (libraryBrowserDock["Initialized"]!==true) {
                libraryBrowserDock.floating = true;
                libraryBrowserDock.move(appWin.x + appWin.width + 20, appWin.y + appWin.height/3*2+20);
                libraryBrowserDock.resize(300, appWin.height/3-20);
            }
        }
    }

    // open files clicked in Finder if application is alreay running (Mac):
    qApp.fileOpenRequestReceived.connect(function(fileName) {
        openFiles([fileName], false);
    });

    // recover auto save files:
    var recovered = AutoSave.recoverUntitled();

    // open files given on command line:
    var clickedFilesAndArgs = filesToOpen.concat(args.slice(1));
    QCoreApplication.processEvents();
    appWin.setProperty("starting", true);
    var restored = false;
    if (typeof(restoreFiles)=="function") {
        restored = restoreFiles();
    }
    openFiles(clickedFilesAndArgs, !recovered && !restored);
    appWin.setProperty("starting", false);

    RPluginLoader.postInitPlugins(RPluginInterface.LoadedFiles);


    // execute scripts given on command line:
    execScripts(args);

    RPluginLoader.postInitPlugins(RPluginInterface.ScriptsExecuted);

    //var statusBar = appWin.statusBar();
    //var action = RGuiAction.getByScriptFile("scripts/View/ToggleStatusBar/ToggleStatusBar.js");
    //action.setChecked(statusBar.visible);

    RPluginLoader.postInitPlugins(RPluginInterface.AllDone);

    appWin.setFocus();
    var w = appWin.getMdiChild();
    if (!isNull(w)) {
        w.setFocus();
    }

    if (!RSettings.hasQuitFlag()) {
        // start and enter the main application loop:
        QCoreApplication.exec();
    }

    uninitAddOns(addOns);

    // don't use RSettings below this point

    // and we're done:
    appWin.destroy();
    qDebug("done");
}

// call main here, in the global context:
main();
