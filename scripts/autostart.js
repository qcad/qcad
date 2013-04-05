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
          + "-enable-script-debugger          Enables the script debugger.\n"
          + "                                 NOT recommended as this may cause unexpected \n"
          + "                                 behavior when using QCAD.\n"
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
          + "-open [filter] [file]            Opens the given file with the explicitly \n"
          + "                                 given import filter.\n"
          + "-rescan                          Rescan scripts folder for new add-ons\n"
          + "-version                         Displays the application version.\n"
          + "-quit                            Quits QCAD, for example after executing the\n"
          + "                                 given script(s).\n"
          //+ "-no-fail                         Ignores test failures (test mode only).\n"
          //+ "-test                            Launches QCAD in test mode (developer mode).\n"
    );


    if (RS.getSystemId()=="osx") {
        print("\nMac OS X specific options:\n");
        // Mac OS X only:
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
        filter = undefined;

        // arguments with one parameter:
        if (args[i] === "-gui-style" || args[i] === "-gui-css-file"
            || args[i] === "-locale" || args[i] === "-autostart"
            || args[i] === "-app-id" || args[i] === "-ignore") {
            // skip 2 arguments
            if (++i>=args.length) {
                break;
            }
            continue;
        }


        // all arguments after -exec are script files or script arguments:
        if (args[i] === "-exec") {
            break;
        }

        if (args[i] === "-open") {
            if (++i>=args.length) {
                break;
            }
            filter = args[i];
            if (++i>=args.length) {
                break;
            }
        }

        // skip other argument without parameter:
        if (args[i][0] === "-") {
            continue;
        }

        foundFile = true;

        // if the file is already open, activate that appropriate sub window instead
        // of opening the file again:
        var document = undefined;
        var fileName = undefined;
        var fileInfo = undefined;
        var argFileInfo = undefined;
        var foundExisting = false;
        for (var k=0; k<mdiChildren.length; k++) {
            document = mdiChildren[k].getDocument();
            fileName = document.getFileName();
            fileInfo = new QFileInfo(fileName);
            argFileInfo = new QFileInfo(getAbsolutePathForArg(args[i]));

            if (fileInfo.equals(argFileInfo)) {
                mdiArea.setActiveSubWindow(mdiChildren[k]);
                foundExisting = true;
                break;
            }
        }

        // open the file if it is not already open:
        if (!foundExisting) {
            NewFile.createMdiChild(getAbsolutePathForArg(args[i]), filter);
        }
    }

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
        qDebug("Loading Style Sheets ...");
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
        if (event.mimeData().hasUrls()) {
            event.acceptProposedAction();
        }
    });

    appWin.drop.connect(function(evt) {
        var urls = evt.mimeData().urls();
        var files = new Array();
        for (var i = 0; i < urls.length; ++i) {
            var file = new QUrl(urls[i]).toLocalFile();
            include("scripts/Edit/InsertScriptItem/InsertScriptItem.js");
            if (InsertScriptItem.isScriptFile(file)) {
                qWarning("autostart.js:", "main(): cannot open script file:", file);
                return;
            }
            files.push(file);
        }

        openFiles(files, false);
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
        splash.showMessage("Loading translations ...\n", Qt.AlignBottom);
    }

    var translationsDirs = RS.getDirectoryList("ts");
    var translator;
    var i;

    // load C++ translations:
    var modules = ["qt", "assistant", "qt_help", "core", "entity", "gui"];
    for (var mi=0; mi<modules.length; ++mi) {
        var module = modules[mi];
        translator = new QTranslator(qApp);
        var success = false;
        for (i=0; i<translationsDirs.length; ++i) {
            if (translator.load(module + "_" + locale, translationsDirs[i])) {
                QCoreApplication.installTranslator(translator);
                success = true;
                break;
            }
        }

        if (!success) {
            qWarning("Cannot load translation: ", module + "_" + locale);
            qWarning("Directories: ", translationsDirs);
        }
    }

    // script translator (source files in ./scripts/):
    /*
    translator = new QTranslator(qApp);
    if (translator.load("scripts_" + locale, "scripts/ts")) {
        QCoreApplication.installTranslator(translator);
    }
    else {
        qWarning("Cannot load translation: ", "scripts_" + locale);
        qWarning("Directory: ", "scripts/ts");
    }

    // install all script translations in one QTranslator:
    translator = new QTranslator(qApp);
    if (translator.load("scripts_" + locale, "")) {
        QCoreApplication.installTranslator(translator);
    }
    else {
        qWarning("Cannot load translation: ", "scripts_" + locale);
        qWarning("Directory: ", ".");
    }
    */

    // install one QTranslator for each script add-on (random crashes):
    if (!isNull(splash)) {
        splash.showMessage(qsTr("Loading add-on translations ...") + "\n", Qt.AlignBottom);
        QCoreApplication.processEvents();
    }
    for (i = 0; i < addOns.length; ++i) {
        var addOn = addOns[i];

        translator = new QTranslator(qApp);
        if (translator.load(addOn.getClassName() + "_" + locale, addOn.getPath() + "/ts")) {
            QCoreApplication.installTranslator(translator);
        }
        else {
            qWarning("Cannot load translation: ", addOn.getClassName() + "_" + locale);
            qWarning("Directory: ", addOn.getPath() + "/ts");
        }
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
        splash.showMessage(qsTr("Loading add-ons ...") + "\n", Qt.AlignBottom);
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
        splash.showMessage(qsTr("Initializing add-ons ...") + "\n", Qt.AlignBottom);
        QCoreApplication.processEvents();
    }

    var addOn;
    var i;
    var text;

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
        splash.showMessage(qsTr("Post-initializing add-ons ...") + "\n", Qt.AlignBottom);
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

/**
 * Loads the add-ons and starts QCAD.
 */
function main() {
    qApp.organizationName = "QCAD";
    qApp.organizationDomain = "QCAD.org";
    qApp.applicationVersion = RSettings.getVersionString();

    var i;
    var filesToOpen = new Array();

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

    // install custom message handler for qDebug, etc.
    RMainWindow.installMessageHandler();
    RPluginLoader.loadPlugins();

    var args = QCoreApplication.arguments();
    if (args.contains("-help") || args.contains("-h")) {
        usage();
        return;
    }
    if (args.contains("-version") || args.contains("-v")) {
        version();
        return;
    }

    var gotCamExtension = (new QFileInfo("scripts/Cam").exists() && !AddOn.isIgnored("scripts/Cam"));

    // in test mode, clean up first:
    qApp.applicationName = "QCAD";
    // app name for ini file differs to avoid conflict with
    // older QCAD versions:
    RSettings.setApplicationName("QCAD3");

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


    // mark config file with current version number:
    RSettings.setValue("Application/Version", RSettings.getNumericalVersionString());
    
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

    // save locale
    appWin.setProperty("Locale", RSettings.getLocale());
    
    // set some object names for later look up:
    var menuBar = appWin.menuBar();
    menuBar.objectName = "MenuBar";

    // load add-ons:
    RDebug.startTimer(0);
    loadAddOns(addOns, splash);
    RDebug.stopTimer(0, "loading addOns");

    RDebug.startTimer(0);
    initAddOns(addOns, splash);
    RDebug.stopTimer(0, "initializing add-ons");

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

    if (!QCoreApplication.arguments().contains("-no-show")) {
        appWin.show();
    }

    postInitAddOns(addOns, splash);

    if (!isNull(splash)) {
        splash.close();
        splash.destroy();
    }

    // if the window position / size was not read from a config file,
    // automatically position property editor and library browser (first start):
    if (isFirstStart) {
        var propertyEditorDock = appWin.findChild("PropertyEditorDock");
        if (!isNull(propertyEditorDock)) {
            propertyEditorDock.floating = true;
            propertyEditorDock.move(appWin.x + appWin.width + 20, appWin.y);
            propertyEditorDock.resize(300, appWin.height/3*2);
        }

        var libraryBrowserDock = appWin.findChild("LibraryBrowserDock");
        if (!isNull(libraryBrowserDock)) {
            libraryBrowserDock.floating = true;
            libraryBrowserDock.move(appWin.x + appWin.width + 20, appWin.y + appWin.height/3*2+20);
            libraryBrowserDock.resize(300, appWin.height/3-20);
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

    // execute scripts given on command line:
    execScripts(args);

    var statusBar = appWin.statusBar();
    var action = RGuiAction.getByScriptFile("scripts/View/ToggleStatusBar/ToggleStatusBar.js");
    action.setChecked(statusBar.visible);

    if (!RSettings.hasQuitFlag()) {
        // start and enter the main application loop:
        QCoreApplication.exec();
    }

    // don't use RSettings below this point

    // and we're done:
    appWin.destroy();
    qDebug("done");
}

// call main here, in the global context:
main();
