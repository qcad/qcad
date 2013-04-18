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
#include <stdio.h>

#include <QApplication>
#include <QDebug>
#include <QImageReader>
#include <QTextStream>
#include <QSqlDatabase>

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
#include <signal.h>
#endif

#ifdef Q_OS_MAC
#include <Carbon/Carbon.h>
#include <CoreServices/CoreServices.h>
#endif

#include "RArcEntity.h"
#include "RBlockReferenceEntity.h"
#include "RCircleEntity.h"
#include "RDebug.h"
#include "RDimAlignedEntity.h"
#include "RDimAngularEntity.h"
#include "RDimDiametricEntity.h"
#include "RDimOrdinateEntity.h"
#include "RDimRadialEntity.h"
#include "RDimRotatedEntity.h"
#include "RDimensionEntity.h"
#include "REllipseEntity.h"
#include "RFontList.h"
#include "RHatchEntity.h"
#include "RImageEntity.h"
#include "RLeaderEntity.h"
#include "RLineEntity.h"
#include "RPatternListImperial.h"
#include "RPatternListMetric.h"
#include "RPluginLoader.h"
#include "RPointEntity.h"
#include "RPolylineEntity.h"
#include "RScriptHandlerEcma.h"
#include "RScriptHandlerRegistry.h"
#include "RSettings.h"
#include "RSingleApplication.h"
#include "RSingleton.h"
#include "RSolidEntity.h"
#include "RSplineEntity.h"
#include "RTextEntity.h"

//##Q_IMPORT_PLUGIN(customwidgetsplugin)


#ifdef Q_OS_MAC
void qt_mac_set_menubar_icons(bool);
#endif


#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
void catchSigPipe(int /*s*/){
    qDebug() << "SIGPIPE caught";
}
#endif


int main(int argc, char *argv[]) {

    // 20130418 (experimental):
    // For correct Unicode translation, apply the current system locale:
    setlocale(LC_ALL, "");
    // But use usual conversion for scanf()/sprintf():
    setlocale(LC_NUMERIC, "C");

    RMainWindow::installMessageHandler();
#ifdef Q_OS_MAC
    // TODO: make available as script function:
    qt_mac_set_menubar_icons(false);
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
        if (!strcmp(argv[i], "-no-gui")) {
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
#endif

    if (!app->arguments().contains("-allow-multiple-instances")) {
        // send arguments to running instance for further processing:
        if (app->sendMessage(app->arguments().join("\n"), 30000)) {
            qWarning("Application already running. Aborting...");
            return 0;
        }
    }

#ifdef Q_OS_WIN32
    // SVG icons are only rendered if this line is present under windows:
    QImageReader::supportedImageFormats();

    // the SQLite plugin can only be loaded if this line is present under windows:
    QSqlDatabase::drivers();
#endif

    if (guiEnabled) {
        //##Q_INIT_RESOURCE(core);
    }

    qRegisterMetaType<RColor>();
    qRegisterMetaTypeStreamOperators<RColor>("RColor");

    qRegisterMetaType<RVector>();
    qRegisterMetaTypeStreamOperators<RVector>("RVector");

    QString cwd = QDir::currentPath();
    RSettings::setLaunchPath(cwd);

    // set current working directory:
    QDir::setCurrent(RSettings::getApplicationPath());

    // disable Qt library paths to avoid plugins for Qt designer from being found:
    QString pluginPath = RSettings::getPluginPath();
    if (pluginPath.isEmpty()) {
        qWarning() << QString("Folder '%1' does not exist").arg(pluginPath);
        return -1;
    }
    app->setLibraryPaths(QStringList() << pluginPath);

    RMath::init();
    RFontList::init();
    RPatternListMetric::init();
    RPatternListImperial::init();

    // init entity properties (depends on translations):
    RObject::init();
    REntity::init();
    RArcEntity::init();
    RBlockReferenceEntity::init();
    RCircleEntity::init();
    RDimensionEntity::init();
    RDimAlignedEntity::init();
    RDimAngularEntity::init();
    RDimDiametricEntity::init();
    RDimOrdinateEntity::init();
    RDimRadialEntity::init();
    RDimRotatedEntity::init();
    REllipseEntity::init();
    RImageEntity::init();
    RHatchEntity::init();
    RLeaderEntity::init();
    RLineEntity::init();
    RPointEntity::init();
    RPolylineEntity::init();
    RSolidEntity::init();
    RSplineEntity::init();
    RTextEntity::init();

    RUcs::init();
    RLayer::init();
    RLinetype::init();
    RBlock::init();
    RView::init();

    RPluginLoader::loadPlugins();

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

    RSettings::uninit();
    RFontList::uninit();
    RPatternListMetric::uninit();
    RPatternListImperial::uninit();
    RSingleton::cleanUp();
    RMath::uninit();

    return ret;
}
