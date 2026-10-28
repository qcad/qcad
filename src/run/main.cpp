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
#include <stdio.h>

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QLoggingCategory>
#include <QFileInfo>
#include <QImageReader>
#include <QSettings>
#include <QSqlDatabase>
#include <QTime>

#if defined(Q_OS_MACOS) || defined(Q_OS_LINUX)
#include <signal.h>
#endif

#ifdef Q_OS_MAC
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>
#endif

#ifdef Q_OS_LINUX
#include <QMessageBox>
#include <QProcess>
#include <QStandardPaths>
#include <QTextStream>
#endif

#include "RArcEntity.h"
#include "RAttributeDefinitionEntity.h"
#include "RAttributeEntity.h"
#include "RBlock.h"
#include "RBlockReferenceEntity.h"
#include "RCircleEntity.h"
#include "RColorDialog.h"
#include "RDimAlignedEntity.h"
#include "RDimAngularEntity.h"
#include "RDimAngular2LEntity.h"
#include "RDimAngular3PEntity.h"
#include "RDimArcLengthEntity.h"
#include "RDimDiametricEntity.h"
#include "RDimOrdinateEntity.h"
#include "RDimRadialEntity.h"
#include "RDimRotatedEntity.h"
#include "RDimensionEntity.h"
#include "RDimLinearEntity.h"
#include "RDimStyle.h"
#include "RDocumentVariables.h"
#include "REllipseEntity.h"
#include "RFaceEntity.h"
#include "RPolyMeshEntity.h"
#include "RFontList.h"
#include "RHatchEntity.h"
#include "RImageEntity.h"
#include "RLayer.h"
#include "RLayerState.h"
#include "RLayout.h"
#include "RLeaderEntity.h"
#include "RLineEntity.h"
#include "RLinetype.h"
#include "RLinetypeListImperial.h"
#include "RLinetypeListMetric.h"
#include "RPatternListImperial.h"
#include "RPatternListMetric.h"
#include "RPluginLoader.h"
#include "RPointEntity.h"
#include "RPolylineEntity.h"
#include "RRayEntity.h"
#if QT_VERSION < 0x060000
#  include "RScriptHandlerEcma.h"
#else
#  include "RScriptHandler.h"
#endif
#include "RScriptHandlerRegistry.h"
#include "RSettings.h"
#include "RSingleApplication.h"
#include "RSingleton.h"
#include "RSolidEntity.h"
#include "RSplineEntity.h"
#include "RTextEntity.h"
#include "RToleranceEntity.h"
#include "RTraceEntity.h"
#include "RViewportEntity.h"
#include "RWipeoutEntity.h"
#include "RVersion.h"
#include "RView.h"
#include "RXLineEntity.h"

#ifdef Q_OS_MAC
#include "removemacmenus.h"
#endif


#if defined(Q_OS_MACOS) || defined(Q_OS_LINUX)
void catchSigPipe(int /*s*/){
    qDebug() << "SIGPIPE caught";
}
#endif

#ifdef Q_OS_LINUX
/**
 * Desktop entry ID of QCAD under Linux (org.qcad.QCAD.desktop).
 * Must match the name of the desktop file shipped with QCAD
 * (support/deployment/linux/org.qcad.QCAD.desktop).
 * Desktop environments associate the QCAD window with this desktop file
 * (and its icon) through the window's application ID / WM_CLASS.
 */
static const QString linuxDesktopFileBaseName = "org.qcad.QCAD";

/**
 * Installs the QCAD application icon into the user's hicolor icon theme
 * (used if no icon file is found next to the QCAD binary).
 * \return True on success.
 */
static bool installLinuxDesktopIcon() {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    if (dir.isEmpty()) {
        return false;
    }
    dir += "/icons/hicolor/256x256/apps";
    if (!QDir().mkpath(dir)) {
        return false;
    }
    QString target = dir + "/" + linuxDesktopFileBaseName + ".png";
    QFile::remove(target);
    return QFile::copy(":scripts/qcad_icon.png", target);
}

/**
 * Checks if a desktop file for QCAD is installed (user or system wide) and
 * offers to create one in the user's applications directory if it is not.
 * Without a matching desktop file, the window of QCAD cannot be associated
 * with the QCAD icon by the dock / task bar (e.g. when QCAD is started from
 * a terminal or extracted from a tar.gz archive).
 * The user can choose to not be asked again (Linux/OfferDesktopFile).
 */
static void offerLinuxDesktopFile() {
    if (!qEnvironmentVariableIsEmpty("FLATPAK_ID") ||
        !qEnvironmentVariableIsEmpty("SNAP") ||
        !qEnvironmentVariableIsEmpty("APPIMAGE")) {
        // sandboxed / bundled: desktop file is provided by the package
        return;
    }

    if (!RSettings::getBoolValue("Linux/OfferDesktopFile", true)) {
        // user chose not to be asked again
        return;
    }

    QString desktopFileName = linuxDesktopFileBaseName + ".desktop";

    if (!QStandardPaths::locate(QStandardPaths::ApplicationsLocation, desktopFileName).isEmpty()) {
        // desktop file already installed (user or system wide)
        return;
    }

    QString targetDir = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    if (targetDir.isEmpty()) {
        return;
    }

    QString appPath = RSettings::getApplicationPath();

    QMessageBox::StandardButton ret = QMessageBox::question(
        NULL,
        QObject::tr("Application Menu Entry"),
        QObject::tr("QCAD has not been added to the application menu yet.\n\n"
                    "Without an application menu entry, the QCAD icon "
                    "cannot be shown in the dock or task bar.\n\n"
                    "Add QCAD in\n%1\nto the application menu now?").arg(appPath),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::Yes
    );

    if (ret!=QMessageBox::Yes) {
        // don't ask again:
        RSettings::setValue("Linux/OfferDesktopFile", false);
        return;
    }

    // command to start QCAD (start script if available, binary otherwise):
    QString exec = appPath + "/qcad";
    if (!QFileInfo(exec).isExecutable()) {
        exec = QCoreApplication::applicationFilePath();
    }

    // icon (shipped with QCAD or installed into user's icon theme):
    QString icon = appPath + "/" + linuxDesktopFileBaseName + ".png";
    if (!QFileInfo(icon).exists()) {
        icon = appPath + "/qcad_icon.png";
    }
    if (!QFileInfo(icon).exists()) {
        if (installLinuxDesktopIcon()) {
            icon = linuxDesktopFileBaseName;
        }
        else {
            icon = "";
        }
    }

    // read desktop file template shipped with QCAD:
    QStringList lines;
    QFile templateFile(appPath + "/" + desktopFileName);
    if (templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(&templateFile);
        while (!ts.atEnd()) {
            lines.append(ts.readLine());
        }
        templateFile.close();
    }
    else {
        // minimal fallback (e.g. development environment):
        lines
            << "[Desktop Entry]"
            << "Type=Application"
            << "Name=QCAD"
            << "GenericName=CAD Software"
            << "Comment=A 2D CAD System"
            << "Exec="
            << "Icon="
            << "Terminal=false"
            << "X-MultipleArgs=true"
            << "StartupNotify=true"
            << "StartupWMClass=qcad-bin"
            << "Categories=Graphics;VectorGraphics;Engineering;Construction;2DGraphics;Science;"
            << "MimeType=application/dxf;application/dwg;image/vnd.dxf;image/vnd.dwg;image/x-dwg;";
    }

    for (int i=0; i<lines.length(); i++) {
        if (lines[i].startsWith("Exec=")) {
            lines[i] = QString("Exec=\"%1\" %F").arg(exec);
        }
        else if (lines[i].startsWith("Icon=")) {
            lines[i] = QString("Icon=%1").arg(icon);
        }
    }

    if (!QDir().mkpath(targetDir)) {
        qWarning() << "cannot create directory:" << targetDir;
        return;
    }

    QFile desktopFile(targetDir + "/" + desktopFileName);
    if (!desktopFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "cannot write desktop file:" << desktopFile.fileName();
        return;
    }
    QTextStream ts(&desktopFile);
    ts << lines.join("\n") << "\n";
    desktopFile.close();

    // update desktop database (mime type associations) if tool is available:
    QProcess::startDetached("update-desktop-database", QStringList() << targetDir);

    qDebug() << "desktop file created:" << desktopFile.fileName();
}
#endif

int main(int argc, char *argv[]) {
    qDebug() << "QCAD version " << R_QCAD_VERSION_STRING;
    // For correct Unicode translation, apply the current system locale:
    setlocale(LC_ALL, "");
    // But use usual conversion for scanf()/sprintf():
    setlocale(LC_NUMERIC, "C");

    QString cwd = QDir::currentPath();

    // Finetuning Japanese encoding for correct DXF/DWG import.
    // see http://qt-project.org/doc/qt-4.8/codecs-jis.html
#ifdef Q_OS_WIN
    _putenv_s("UNICODEMAP_JP", "cp932");
#else
    setenv("UNICODEMAP_JP", "cp932", 1);
#endif

#ifdef Q_OS_WIN
#if QT_VERSION >= 0x050200
    // enable OpenGL logging under Windows
    // this info can then be shown in the about dialog
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qpa.gl=true"));
#endif
#endif

#ifdef Q_OS_MAC
    // TODO: fix linking with objective c
    removeMacMenus();
#endif

    // these are defaults:
    qApp->setOrganizationName("QCAD");
    qApp->setOrganizationDomain("QCAD.org");
    qApp->setApplicationName("QCAD");
    qApp->setApplicationVersion(RSettings::getVersionString());

    // alternative path for QCAD3.ini:
    for (int i=0; i<argc; i++) {
        QString a = argv[i];
        if (a == "-config") {
            ++i;
            if (i < argc) {
                a = argv[i];
                QFileInfo fi(a);
                QString absConfigFile;
                if (fi.isAbsolute() || a.startsWith(":")){
                    absConfigFile = a;
                }
                else {
                    // relative path (prepend application dir):
                    absConfigFile = cwd + QDir::separator() + a;
                }

                qDebug() << "absConfigFile:" << absConfigFile;

                QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, absConfigFile);
#if !defined(Q_OS_WIN) && !defined(Q_OS_MACOS)
                // RSettings uses NativeFormat on Linux / Unix:
                QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, absConfigFile);
#endif
            }
        }
    }

    RSettings::setApplicationNameOverride("QCAD3");

    // Auto scale up user interface for high res displays under Windows:
//#ifdef Q_OS_WIN
#if QT_VERSION >= 0x050600
    //_putenv_s("QT_SCALE_FACTOR", "auto");
    if (RSettings::getBoolValue("Ui/QT_AUTO_SCREEN_SCALE_FACTOR", true)==true) {
#ifdef Q_OS_WIN
        _putenv_s("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
#else
        setenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1", 1);
#endif
    }
    if (RSettings::getBoolValue("Ui/EnableHighDpiScaling", false)==true) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }
    else {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, false);
    }
    double qsf = RSettings::getDoubleValue("Ui/QT_SCALE_FACTOR", -1.0);
    if (qsf>0.0 && qsf>0.49 && qsf<4.1) {
#ifdef Q_OS_WIN
        _putenv_s("QT_SCALE_FACTOR", (const char*)QString("%1").arg(qsf).toLocal8Bit());
#else
        setenv("QT_SCALE_FACTOR", (const char*)QString("%1").arg(qsf).toLocal8Bit(), 1);
#endif
    }

        //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#else
#ifdef Q_OS_WIN
    _putenv_s("QT_DEVICE_PIXEL_RATIO", "auto");
#else
    setenv("QT_DEVICE_PIXEL_RATIO", "auto", 1);
#endif
#endif
//#endif

    RMainWindow::installMessageHandler();

#if QT_VERSION >= 0x050000
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

#if QT_VERSION < 0x060000
#  ifdef Q_OS_MAC
    if (QSysInfo::MacintoshVersion>=0x000B) {
        // system font change bug fix on OS X 10.9 (Mavericks):
        QFont::insertSubstitution(".Lucida Grande UI", "Lucida Grande");
    }
#  endif
#else
    // TODO #qt6
#endif

#if QT_VERSION < 0x060000
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
#endif

    QStringList originalArguments;
    for (int i=0; i<argc; i++) {
        QString a = argv[i];
        originalArguments.append(a);
    }
    RSettings::setOriginalArguments(originalArguments);

    QString appId = "QCAD";
    for (int i=0; i<argc; i++) {
        QString a = argv[i];
        if (a=="-app-id" && i+1<argc) {
            appId = argv[i+1];
        }
    }

    bool guiEnabled = true;
    for (int i=1; i<argc; i++) {
        if (!strcmp(argv[i], "-no-gui") || !strcmp(argv[i], "-help")) {
            guiEnabled = false;
        }
    }

    RSingleApplication* app = new RSingleApplication(appId, argc, argv, guiEnabled);

    // make sure arguments are correctly encoded:
    RSettings::setOriginalArguments(QCoreApplication::arguments());

#if defined(Q_OS_LINUX) && QT_VERSION >= 0x050700
    // desktop file name (without .desktop) used by desktop environments to
    // associate the QCAD window with its application menu entry and icon
    // (sets _GTK_APPLICATION_ID under X11 and app_id under Wayland):
    QGuiApplication::setDesktopFileName(linuxDesktopFileBaseName);
#endif

#if defined(Q_OS_MACOS) || defined(Q_OS_LINUX)
    // note that SIGPIPE is only ignored in release mode, gdb catches SIGPIPE
    // by default. To disable that behavior in gdb, use:
    // handle SIGPIPE nostop noprint pass
    signal(SIGPIPE,catchSigPipe);
#endif

#ifdef Q_OS_MAC
    // activate macOS dock icon if desired:
    if (!app->arguments().contains("-no-dock-icon") &&
            !app->arguments().contains("-help") && !app->arguments().contains("-h") &&
            !app->arguments().contains("-version") && !app->arguments().contains("-v")) {
        ProcessSerialNumber psn;
        if (GetCurrentProcess(&psn) == noErr) {
            TransformProcessType(&psn, kProcessTransformToForegroundApplication);
        }
    }
#endif

    if (RSettings::getBoolValue("MenuBar/ShowIcons", true)==false) {
        QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus, true);
    }
    else {
        QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus, false);
    }

    if (!app->arguments().contains("-allow-multiple-instances")) {
        // send arguments to running instance for further processing:
        if (app->sendMessage(app->arguments().join("\n"), 30000)) {
            qWarning("Application already running. Aborting...");
            return 0;
        }
    }

#ifdef Q_OS_WIN
    // SVG icons are only rendered if this line is present under windows:
    QImageReader::supportedImageFormats();

    // the SQLite plugin can only be loaded if this line is present under windows:
    QSqlDatabase::drivers();
#endif

#if QT_VERSION < 0x060000
    qRegisterMetaType<RColor>();
    qRegisterMetaTypeStreamOperators<RColor>("RColor");

    qRegisterMetaType<RVector>();
    qRegisterMetaTypeStreamOperators<RVector>("RVector");

    qRegisterMetaType<QVector<int> >();
#else
    // TODO #qt6 ?
#endif

    RSettings::setLaunchPath(cwd);

    // set current working directory:
    QDir::setCurrent(RSettings::getApplicationPath());

#ifdef Q_OS_LINUX
    if (guiEnabled &&
        !app->arguments().contains("-help") && !app->arguments().contains("-h") &&
        !app->arguments().contains("-version") && !app->arguments().contains("-v")) {
        // offer to create a desktop file (application menu entry, dock icon):
        offerLinuxDesktopFile();
    }
#endif

#ifdef Q_OS_WIN
#if QT_VERSION >= 0x060000
    QString path;
    path  = QString("PATH=") + getenv("PATH");
    path += ";";
    path += RSettings::getApplicationPath() + QDir::separator() + "plugins";
    QByteArray ba = path.toLocal8Bit();
    _putenv_s("PATH", ba.data());
#endif
#endif

    // disable Qt library paths to avoid plugins for Qt designer from being found:
    QStringList pluginPaths = RSettings::getPluginPaths();
    if (pluginPaths.isEmpty()) {
        qWarning() << "No plugin paths found";
        return -1;
    }
    app->setLibraryPaths(pluginPaths);

    // make sure basic entities are initialized before loading plugins:
    RDimStyleData::initDefaults();
    RMath::init();
    RFontList::init();
    RPatternListMetric::init();
    RPatternListImperial::init();

    // init object properties:
    RObject::init();
    REntity::init();
    RDocumentVariables::init();
    RDimStyle::init();

    RArcEntity::init();
    RBlockReferenceEntity::init();
    RCircleEntity::init();

    REllipseEntity::init();
    RImageEntity::init();
    RLineEntity::init();
    RPointEntity::init();
    RSolidEntity::init();
    RTraceEntity::init();
    RFaceEntity::init();
    RPolyMeshEntity::init();
    RSplineEntity::init();
    RXLineEntity::init();
    RRayEntity::init();
    RViewportEntity::init();
    RWipeoutEntity::init();

    RTextBasedEntity::init();
    RTextEntity::init();
    RAttributeDefinitionEntity::init();
    RAttributeEntity::init();

    RUcs::init();
    RLayer::init();
    RLayerState::init();
    RLayout::init();
    RLinetype::init();
    RBlock::init();
    RView::init();

    // make sure plugins can find plugin related settings:
    // these are always stored in "QCAD3.ini/conf":
    RPluginLoader::loadPlugins(true);

    // initialization of entities whos properties may depend on available plugins:
    RPolylineEntity::init();
    RHatchEntity::init();
    RDimensionEntity::init();
    RDimLinearEntity::init();
    RDimAlignedEntity::init();
    RDimAngularEntity::init();
    RDimAngular2LEntity::init();
    RDimAngular3PEntity::init();
    RDimArcLengthEntity::init();
    RDimDiametricEntity::init();
    RDimOrdinateEntity::init();
    RDimRadialEntity::init();
    RDimRotatedEntity::init();
    RToleranceEntity::init();
    RLeaderEntity::init();

    RLinetypeListMetric::init();
    RLinetypeListImperial::init();

    if (guiEnabled) {
        // restore the custom colors of the color dialog (QCAD3.ini):
        RColorDialog::loadCustomColors();
    }

    // check for autostart option:
    QString autostartFile;
    QStringList arguments = app->arguments();
    int i = arguments.indexOf("-autostart");
    if (i!=-1 && arguments.count()>i+1) {
        autostartFile = arguments.at(i+1);
    }

#if QT_VERSION >= 0x060000
    // allow loading of larger bitmaps (configurable):
    QImageReader::setAllocationLimit(RSettings::getIntValue("GraphicsView/ImageAllocationLimit", 256));
#endif

    int ret = 0;

#if QT_VERSION >= 0x060000
    RScriptHandler* handler = RScriptHandlerRegistry::getGlobalScriptHandler("js");
    if (handler!=NULL) {
        // got a custom JS handler from a plugin:
        handler->autostart(autostartFile, arguments.mid(i+1));
        delete handler;
    }
    else {
        qWarning() << "No script handler found...";
    }
#endif

#if QT_VERSION < 0x060000
    RScriptHandlerRegistry::registerScriptHandler(RScriptHandlerEcma::factory,
            RScriptHandlerEcma::getSupportedFileExtensionsStatic());

    RScriptHandler* handler = RScriptHandlerRegistry::getGlobalScriptHandler("js");
    Q_ASSERT(handler!=NULL);
    handler->autostart(autostartFile, arguments.mid(i+1));

    if (handler->hasUncaughtExceptions()) {
        ret = 1;
    }

    // delete script handler and print uncaught exceptions:
    delete handler;
#endif

    RPluginLoader::unloadPlugins();

    // store the custom colors of the color dialog (QCAD3.ini):
    RColorDialog::saveCustomColors();

    RSettings::uninit();
    RFontList::uninit();
    RPatternListMetric::uninit();
    RPatternListImperial::uninit();
    RSingleton::cleanUp();
    RMath::uninit();

    RDocumentInterface::deleteClipboard();

    //RDebug::printCounters();

    return ret;
}
