/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
include("scripts/Edit/AppPreferences/StylePreferences/StylePreferences.js");
include("scripts/File/OpenFile/OpenFile.js");
include("scripts/File/AutoSave/AutoSave.js");

/**
 * Prints version information.
 */
function version() {
    print();
    print("Version: " + RSettings.getVersionString());
    print("Qt Version: " + RSettings.getQtVersion());
    print("Release Date: " + RSettings.getReleaseDate());
    print();
}

/**
 * Prints command line usage information on stdout.
 */
function usage() {
    var styleNames = StylePreferences.getStyleNames();

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
          + "-config [path]                   Reads and stores settings to QCAD3.ini at the given\n"
          + "                                 location instead of the default location.\n"
          + "-enable-script-debugger          Enables the script debugger.\n"
          + "                                 NOT recommended as this may cause unexpected\n"
          + "                                 behavior when using QCAD.\n"
          + "-debug-action-order              Print action oder information in menus\n"
          + "-exec [script file] [options]    Executes the given script file directly\n"
          + "                                 after staring QCAD. Options after the script\n"
          + "                                 file are passed on to the script.\n"
          + "-gui-css-file [CSS file]         Loads the specified CSS file.\n"
          + "-gui-style [StyleName]           Loads a predefined style. Available styles are:\n"
          + "                                 " + styleNames.join(", ") + "\n"
          + "-help                            Displays this help.\n"
          + "-locale [locale]                 Sets the locale to be used (overrides\n"
          + "                                 the language set in the preferences).\n"
          + "                                 E.g. '-locale de' starts QCAD in German.\n"
          + "-no-gui                          Don't use GUI. X11: don't connect to X11 server.\n"
          + "-no-show                         Use but don't display GUI.\n"
          + "-filter [filter]                 Opens the subsequent file(s) with the explicitly \n"
          + "                                 given import filter.\n"
          + "-rescan                          Rescan scripts folder for new add-ons\n"
          + "-version                         Displays the application version.\n"
          + "-enable-xdata                    Enables XData (custom properties) support.\n"
          + "-quit                            Quits QCAD, for example after executing the\n"
          + "                                 given script(s).\n"
    );

    // Mac OS X only:
    if (RS.getSystemId()==="osx") {
        print("\nMac OS X specific options:\n");
        print("-no-dock-icon                    Don't show icon in dock. This should only be used\n"
            + "                                 in combination with -no-gui."  );
    }

    print("\n");
}

/**
 * Open files given as arguments args or creates a new document if
 * no files are given and createNew is true.
 */
function openFiles(args, createNew) {
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
        if (args[i] === "-gui-style" || args[i] === "-gui-css-file"
            || args[i] === "-locale" || args[i] === "-autostart"
            || args[i] === "-app-id" || args[i] === "-ignore"
            || args[i] === "-config") {
            // skip 2 arguments
            if (++i>=args.length) {
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
                    foundExisting = true;
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
            // run existing action:
            var action = RGuiAction.getByScriptFile(args[i]);
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

            // include script:
            else {
                var scriptFile = args[i];
                include(getAbsolutePathForArg(scriptFile));
            }
        }
        if (args[i] === "-quit") {
            RSettings.setQuitFlag();
        }
    }
}

/**
 * Loads application wide style sheets given as arguments after
 * -gui-style or -gui-css-file of placed in the user's home under
 * [config directory]/custom.css
 */
function loadStyleSheets(args) {
    var idx;

    // load predefined style sheets
    idx = args.indexOf("-gui-style");
    if (idx>-1) {
        qDebug("Loading Style Sheets...");
        if (idx+1<args.length) {
            StylePreferences.loadByName(args[idx + 1]);
        }
        else {
            qWarning("No argument given to -gui-style");
        }
    }

    // load custom style sheets, if any
    StylePreferences.loadCustomStyles();

    // load CSS file if given by argument
    idx = args.indexOf("-gui-css-file");
    if (idx>-1) {
        if (idx+1<args.length) {
            StylePreferences.load(args[idx + 1]);
        }
        else {
            qWarning("No argument given to -gui-css-file");
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
    if (locale === "en" || locale.toLowerCase() === "en_us") {
        return;
    }

    if (!isNull(splash)) {
        // no translations yet:
        splash.showMessage("Loading translations...\n", Qt.AlignBottom);
    }

    // load C++ translations:
    var modules = ["qt", "assistant", "qt_help", "qcadcore", "qcadentity", "qcadgui"];
    for (var mi=0; mi<modules.length; ++mi) {
        var module = modules[mi];

        RSettings.loadTranslations(module);
    }


    // install one QTranslator for each script add-on:
    if (!isNull(splash)) {
        splash.showMessage(qsTr("Loading add-on translations...") + "\n", Qt.AlignBottom);
        QCoreApplication.processEvents();
    }

    RSettings.loadTranslations("Scripts_" + locale, ["scripts/ts"]);

    for (var i = 0; i < addOns.length; ++i) {
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
    if (!isNull(splash)) {
        splash.showMessage(qsTr("Post-initializing add-ons...") + "\n", Qt.AlignBottom);
        QCoreApplication.processEvents();
    }

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
    if (!isNull(qApp.applicationNameOverride)) {
        qApp.applicationName = qApp.applicationNameOverride;
    }

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
    RSettings.setApplicationName("QCAD3");

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
    if (RSettings.getIntValue("Application/Version", 0)<=3000006) {
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
            var configBak = configPath + QDir.separator + "QCAD3_old." + fi.suffix();
            qDebug("Renaming old unversioned config file from '" + configPath + "' to '"+ configBak + "'");
            QFile.remove(configBak);
            QFile.rename(configFile, configBak);
        }
    }

    // detect very first start of this installation:
    var fiSettings = new QFileInfo(RSettings.getQSettings().fileName());
    var isFirstStart = !fiSettings.exists();

    // if locale is given, don't show first start dialog:
    if (isFirstStart && !QCoreApplication.arguments().contains("-locale")) {
        include("Widgets/FirstStart/FirstStart.js");
        var first = new FirstStart();
        first.showDialog();
    }

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
    
    // splash:
    var splash;
    splash = undefined;
    if (RSettings.getBoolValue("Start/EnableSplashScreen", true)) {
        var fn = "scripts/splashscreen.png";
        var pixmap = new QPixmap(fn);
        splash = new QSplashScreen(pixmap);
        if (!QCoreApplication.arguments().contains("-no-show")) {
            splash.show();
        }
    }

    RFontList.initSubstitutions();

    RPluginLoader.postInitPlugins(RPluginInterface.GotSplashWindow);

    // mark config file with current version number:
    var previousVersion = RSettings.getStringValue("Application/Version", "");
    RSettings.setValue("Application/Version", RSettings.getNumericalVersionString());

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
    // animated is nice, but crashes sometimes (Qt 4.7.2):
    appWin.animated = false;
    appWin.objectName = "MainWindow";
    appWin.windowTitle = qApp.applicationName;

    // save first start information:
    appWin.setProperty("FirstStart", isFirstStart);
    // save new version information:
    appWin.setProperty("NewVersion", newVersion);
    appWin.setProperty("PreviousVersion", previousVersion);

    // save locale
    appWin.setProperty("Locale", RSettings.getLocale());
    
    // set some object names for later look up:
    var menuBar = appWin.menuBar();
    menuBar.objectName = "MenuBar";

    // load add-ons:
    RDebug.startTimer(0);
    loadAddOns(addOns, splash);
    RDebug.stopTimer(0, "loading add-ons");

    RDebug.startTimer(0);
    initAddOns(addOns, splash);
    RDebug.stopTimer(0, "initializing add-ons");

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
    appWin.setTabPosition(Qt.RightDockWidgetArea, QTabWidget.West);
    appWin.setTabPosition(Qt.LeftDockWidgetArea, QTabWidget.West);
    appWin.setTabPosition(Qt.TopDockWidgetArea, QTabWidget.West);
    appWin.setTabPosition(Qt.BottomDockWidgetArea, QTabWidget.West);

    setUpDragAndDrop(appWin);

    // load CSS:
    loadStyleSheets(args);

    appWin.windowIcon = new QIcon("scripts/qcad_icon.png");
    if (!ignoreDockappWindows) {
        appWin.readSettings();
    }

    RPluginLoader.postInitPlugins(RPluginInterface.GotMainWindowBeforeShow);

    if (!QCoreApplication.arguments().contains("-no-show")) {
        appWin.show();
    }

    postInitAddOns(addOns, splash);
    RPluginLoader.postInitPlugins(RPluginInterface.GotMainWindow);

    if (!isNull(splash)) {
        splash.close();
        splash.destroy();
    }

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
    openFiles(clickedFilesAndArgs, !recovered);

    RPluginLoader.postInitPlugins(RPluginInterface.LoadedFiles);


    // execute scripts given on command line:
    execScripts(args);

    RPluginLoader.postInitPlugins(RPluginInterface.ScriptsExecuted);

    //var statusBar = appWin.statusBar();
    //var action = RGuiAction.getByScriptFile("scripts/View/ToggleStatusBar/ToggleStatusBar.js");
    //action.setChecked(statusBar.visible);

    RPluginLoader.postInitPlugins(RPluginInterface.AllDone);

    appWin.setFocus();

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
