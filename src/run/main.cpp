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
#include <QFileInfo>
#include <QImageReader>
#include <QTextStream>
#include <QTime>
#include <QSqlDatabase>

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
#include <signal.h>
#endif

#ifdef Q_OS_MAC
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>
#endif

#include "RArcEntity.h"
#include "RAttributeDefinitionEntity.h"
#include "RAttributeEntity.h"
#include "RBlockReferenceEntity.h"
#include "RCircleEntity.h"
#include "RDebug.h"
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
#include "RDocumentVariables.h"
#include "REllipseEntity.h"
#include "RFaceEntity.h"
#include "RFontList.h"
#include "RHatchEntity.h"
#include "RImageEntity.h"
#include "RLayer.h"
#include "RLayerState.h"
#include "RLeaderEntity.h"
#include "RLineEntity.h"
#include "RLinetypeListImperial.h"
#include "RLinetypeListMetric.h"
#include "RPatternListImperial.h"
#include "RPatternListMetric.h"
#include "RPluginLoader.h"
#include "RPointEntity.h"
#include "RPolylineEntity.h"
#include "RRayEntity.h"
#include "RScriptHandlerEcma.h"
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
#include "RVersion.h"
#include "RXLineEntity.h"

#ifdef Q_OS_MAC
#include "removemacmenus.h"
#endif


#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
void catchSigPipe(int /*s*/){
    qDebug() << "SIGPIPE caught";
}
#endif

int main(int argc, char *argv[]) {
    qDebug() << "QCAD version " << R_QCAD_VERSION_STRING;
    // For correct Unicode translation, apply the current system locale:
    setlocale(LC_ALL, "");
    // But use usual conversion for scanf()/sprintf():
    setlocale(LC_NUMERIC, "C");

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

    RSettings::setApplicationNameOverride("QCAD3");

    // Auto scale up user interface for high res displays under Windows:
#ifdef Q_OS_WIN
#if QT_VERSION >= 0x050600
    //_putenv_s("QT_SCALE_FACTOR", "auto");
    if (RSettings::getBoolValue("Ui/QT_AUTO_SCREEN_SCALE_FACTOR", true)==true) {
        qDebug() << "auto scale";
        _putenv_s("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    }
    if (RSettings::getBoolValue("Ui/EnableHighDpiScaling", false)==true) {
        qDebug() << "enable high dpi scaling";
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }
    double qsf = RSettings::getDoubleValue("Ui/QT_SCALE_FACTOR", -1.0);
    if (qsf>0.0) {
        _putenv_s("QT_SCALE_FACTOR", (const char*)QString("%1").arg(qsf).toLocal8Bit());
    }

        //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#else
    _putenv_s("QT_DEVICE_PIXEL_RATIO", "auto");
#endif
#endif

    RMainWindow::installMessageHandler();

#if QT_VERSION >= 0x050000
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

#ifdef Q_OS_MAC
    if (QSysInfo::MacintoshVersion>=0x000B) {
        // system font change bug fix on OS X 10.9 (Mavericks):
        QFont::insertSubstitution(".Lucida Grande UI", "Lucida Grande");
    }
#endif

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

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

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    // note that SIGPIPE is only ignored in release mode, gdb catches SIGPIPE
    // by default. To disable that behavior in gdb, use:
    // handle SIGPIPE nostop noprint pass
    signal(SIGPIPE,catchSigPipe);
#endif

#ifdef Q_OS_MAC
    // activate Mac OS X dock icon if desired:
    if (!app->arguments().contains("-no-dock-icon") &&
            !app->arguments().contains("-help") && !app->arguments().contains("-h") &&
            !app->arguments().contains("-version") && !app->arguments().contains("-v")) {
        ProcessSerialNumber psn;
        if (GetCurrentProcess(&psn) == noErr) {
            TransformProcessType(&psn, kProcessTransformToForegroundApplication);
        }
    }

    // TODO: make available as script function:
    if (!app->arguments().contains("-show-menu-icons")) {
        QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
    }
#endif

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

    qRegisterMetaType<RColor>();
    qRegisterMetaTypeStreamOperators<RColor>("RColor");

    qRegisterMetaType<RVector>();
    qRegisterMetaTypeStreamOperators<RVector>("RVector");

    QString cwd = QDir::currentPath();
    RSettings::setLaunchPath(cwd);

    // set current working directory:
    QDir::setCurrent(RSettings::getApplicationPath());

    // disable Qt library paths to avoid plugins for Qt designer from being found:
    QStringList pluginPaths = RSettings::getPluginPaths();
    if (pluginPaths.isEmpty()) {
        qWarning() << "No plugin paths found";
        return -1;
    }
    app->setLibraryPaths(pluginPaths);

    RMath::init();
    RFontList::init();
    RPatternListMetric::init();
    RPatternListImperial::init();

    // init object properties:
    RObject::init();
    REntity::init();
    RDocumentVariables::init();

    RArcEntity::init();
    RBlockReferenceEntity::init();
    RCircleEntity::init();
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
    REllipseEntity::init();
    RImageEntity::init();
    RHatchEntity::init();
    RLeaderEntity::init();
    RToleranceEntity::init();
    RLineEntity::init();
    RPointEntity::init();
    RPolylineEntity::init();
    RSolidEntity::init();
    RTraceEntity::init();
    RFaceEntity::init();
    RSplineEntity::init();
    RXLineEntity::init();
    RRayEntity::init();
    RViewportEntity::init();

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

    RLinetypeListMetric::init();
    RLinetypeListImperial::init();

    // check for autostart option:
    QString autostartFile;
    QStringList arguments = app->arguments();
    int i = arguments.indexOf("-autostart");
    if (i!=-1 && arguments.count()>i+1) {
        autostartFile = arguments.at(i+1);
    }

    RScriptHandlerRegistry::registerScriptHandler(RScriptHandlerEcma::factory,
            RScriptHandlerEcma::getSupportedFileExtensionsStatic());
    RScriptHandler* handler = RScriptHandlerRegistry::getGlobalScriptHandler("js");
    Q_ASSERT(handler!=NULL);
    handler->init(autostartFile, arguments.mid(i+1));

    int ret = 0;
    if (handler->hasUncaughtExceptions()) {
        ret = 1;
    }

    // delete script handler and print uncaught exceptions:
    delete handler;

    RPluginLoader::unloadPlugins();

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
