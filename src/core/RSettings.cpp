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
#include <QtDebug>
#include <QApplication>
#include <QColor>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFrame>
#include <QPrinterInfo>
#include <QString>
#include <QStringList>
#include <QSysInfo>
#include <QTranslator>

#if QT_VERSION >= 0x050000
#  include <QWindow>
#  include <QStandardPaths>
#else
#  include <QDesktopServices>
#endif

#include "RDebug.h"
#include "RMath.h"
#include "RSettings.h"
#include "RVersion.h"

#ifdef Q_OS_MAC
#include "detectmacdarkmode.h"
#endif

bool RSettings::noWrite = false;
QVariantMap RSettings::cache;

QString RSettings::launchPath;
QString RSettings::themePath;

QFont* RSettings::rulerFont = NULL;
QFont* RSettings::snapLabelFont = NULL;
QFont* RSettings::infoLabelFont = NULL;
QFont* RSettings::statusBarFont = NULL;
RColor* RSettings::selectionColor = NULL;
RColor* RSettings::referencePointColor = NULL;
RColor* RSettings::startReferencePointColor = NULL;
RColor* RSettings::endReferencePointColor = NULL;
RColor* RSettings::secondaryReferencePointColor = NULL;
RColor* RSettings::tertiaryReferencePointColor = NULL;
int RSettings::darkMode = -1;
int RSettings::darkGuiBackground = -1;
int RSettings::snapRange = -1;
int RSettings::pickRange = -1;
int RSettings::zeroWeightWeight = -1;
int RSettings::showCrosshair = -1;
int RSettings::showLargeCrosshair = -1;
int RSettings::showLargeOriginAxis = -1;
int RSettings::concurrentDrawing = -1;
int RSettings::highResolutionGraphicsView = -1;
int RSettings::previewEntities = -1;
int RSettings::limitZoomAndScroll = -1;
int RSettings::autoScaleLinetypePattern = -1;
int RSettings::useSecondarySelectionColor = -1;
int RSettings::mouseThreshold = -1;
int RSettings::positionByMousePress = -1;
int RSettings::allowMouseMoveInterruptions = -1;
int RSettings::useSolidLineSelection = -1;
double RSettings::arcAngleLengthThreshold = -1;
double RSettings::fadingFactor = -1;
double RSettings::minArcAngleStep = -1;
int RSettings::dashThreshold = -1;
int RSettings::textRenderedAsText = -1;
int RSettings::layer0CompatibilityOn = -1;
int RSettings::selectBlockWithAttribute = -1;
int RSettings::hideAttributeWithBlock = -1;
int RSettings::importRecomputedDimBlocks = -1;
int RSettings::ignoreBlockReferencePoint = -1;
int RSettings::ignoreAllReferencePoints = -1;
int RSettings::referencePointSize = -1;
int RSettings::referencePointShape = -1;
int RSettings::propertyEditorShowOnRequest = -1;
QString RSettings::polarCoordinateSeparator = QString::null;
QString RSettings::cartesianCoordinateSeparator = QString::null;
QString RSettings::relativeCoordinatePrefix = QString::null;
QStringList RSettings::recentFiles;
QLocale* RSettings::numberLocale = NULL;
QString RSettings::applicationNameOverride;

QSettings* RSettings::qSettings = NULL;

QStringList RSettings::originalArguments;

bool RSettings::quitFlag = false;
bool RSettings::xDataEnabled = false;
bool RSettings::nextVersionEnabled = false;

bool RSettings::firstStart = false;
bool RSettings::newVersion = false;
int RSettings::previousVersion = 0;

QStringList RSettings::openGLMessages;


/**
 * App ID used for DXF/DWG exports / imports to identify app XData.
 */
QString RSettings::getAppId() {
    //QString ret = qApp->applicationName();
    //ret.replace(QRegExp("[^a-zA-Z0-9]"), "");
    // prevent 'empty record name' exception:
    //if (ret.isEmpty()) {
    //    ret = "QCAD";
    //}
    //return ret;
    return "QCAD";
}

/**
 * \return Device pixel ratio of the display. Usually 1 or 2 (for retina/high res displays).
 */
double RSettings::getDevicePixelRatio() {
    // DPR can be overridden in settings:
    int dpr = RSettings::getIntValue("Appearance/DevicePixelRatio", 0);
    if (dpr>0) {
        return dpr;
    }

#if QT_VERSION >= 0x050000
    QWindow* window = QGuiApplication::focusWindow();
    if (window!=NULL) {
        return window->devicePixelRatio();
    }
    return qApp->devicePixelRatio();
#else
    return 1.0;
#endif
}

/**
 * \return List of arguments passed to the application binary.
 */
QStringList RSettings::getOriginalArguments() {
    return originalArguments;
}

void RSettings::setOriginalArguments(const QStringList& a) {
    originalArguments = a;
}

/**
 * \return The argument after the first one of the given flags or the given default value.
 *
 * \param args Array of strings (program arguments)
 * \param shortFlag E.g. "-o"
 * \param longFlag E.g. "-output"
 */
QString RSettings::getArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const QString& def) {
    QStringList ret = getArguments(args, shortFlag, longFlag);
    if (ret.isEmpty()) {
        return def;
    }
    return ret[0];
}

/**
 * \return Array of all arguments after the given flags or an empty array.
 *
 * \param args Array of strings (program arguments)
 * \param shortFlag E.g. "-o"
 * \param longFlag E.g. "-output"
 */
QStringList RSettings::getArguments(const QStringList& args, const QString& shortFlag, const QString& longFlag) {
    QStringList ret;

    for (int k=0; k<args.length(); k++) {
        if (args[k]==shortFlag) {
            if (k+1 < args.length()) {
                ret.append(args[k+1]);
            }
        }

        if (args[k].startsWith(longFlag+"=")) {
            QStringList tokens = args[k].split("=");
            if (tokens.length()==2) {
                ret.append(tokens[1]);
            }
            //int j=args[k].indexOf("=");
            //ret.push(args[k].substr(j+1));
        }
    }

    return ret;
}

int RSettings::getIntArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, int def) {
    QString ret = getArgument(args, shortFlag, longFlag);
    if (ret.isNull()) {
        return def;
    }
    return ret.toInt();
}

QList<int> RSettings::getIntListArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, QList<int> def) {
    QString arg = getArgument(args, shortFlag, longFlag);
    if (arg.isNull()) {
        return def;
    }

    QList<int> ret;
    QStringList tokens = arg.split(",");

    bool singleInt = false;
    if (tokens.length()==1) {
        singleInt = true;
    }

    for (int i=0; i<tokens.length(); i++) {
        QString token = tokens[i];
        QStringList range = token.split("-");
        int start, stop;

        if (range.length()==1) {
            start = singleInt ? 0 : range[0].toInt();
            stop = range[0].toInt();
        }
        else if (range.length()==2) {
            start = range[0].toInt();
            stop = range[1].toInt();
        }
        else {
            qWarning() << "invalid token in list: " << token;
            continue;
        }

        for (int k=start; k<=stop; k++) {
            ret.append(k);
        }
    }

    return ret;
}

double RSettings::getFloatArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, double def) {
    QString ret = getArgument(args, shortFlag, longFlag);
    if (ret.isNull()) {
        return def;
    }
    return ret.toDouble();
}

RColor RSettings::getColorArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const RColor& def) {
    QString ret = getArgument(args, shortFlag, longFlag);
    if (ret.isNull()) {
        return def;
    }
    return RColor(ret);
}

RVector RSettings::getVectorArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const RVector& def) {
    QString ret = getArgument(args, shortFlag, longFlag);
    if (ret.isNull()) {
        return def;
    }
    QStringList parts = ret.split(',');
    if (parts.length()!=2) {
        return def;
    }
    QList<double> floatParts;
    for (int i=0; i<parts.length(); i++) {
        floatParts.append(parts[i].toDouble());
    }

    return RVector(floatParts[0], floatParts[1]);
}

RBox RSettings::getBoxArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const RBox& def) {
    QString ret = getArgument(args, shortFlag, longFlag);
    if (ret.isNull()) {
        return def;
    }
    QStringList parts = ret.split(',');
    if (parts.length()!=4) {
        return def;
    }
    QList<double> floatParts;
    for (int i=0; i<parts.length(); i++) {
        //parts[i] = parts[i].toDouble();
        floatParts.append(parts[i].toDouble());
    }

    return RBox(RVector(floatParts[0], floatParts[1]), RVector(floatParts[0] + floatParts[2], floatParts[1] + floatParts[3]));
}

/**
 * \return True if the given arguments contain one of the given flags.
 */
bool RSettings::testArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag) {
    if (!shortFlag.isEmpty() && args.contains(shortFlag)) {
        return true;
    }
    if (!longFlag.isEmpty()) {
        if (args.contains(longFlag)) {
            return true;
        }
        for (int k=0; k<args.length(); k++) {
            if (args[k].startsWith(longFlag+"=")) {
                return true;
            }
        }
    }

    return false;
}

/**
 * \return True if the application is deployed and all resources are inside the App bundle.
 * This always returns true if the OS is not a Mac OS.
 */
bool RSettings::isDeployed() {
#ifdef Q_OS_MAC
    QDir appDir(QApplication::applicationDirPath());
    if (appDir.dirName() == "MacOS") {
        appDir.cdUp();
        // deployed (scripts inside app bundle):
        return appDir.cd("Resources/scripts");
    }
    return false;
#else
    return true;
#endif
}

/**
 * \return Path where all application resources are stored ('scripts', 'patterns', 'ts', 'doc', 'linetypes', ...)
 */
QString RSettings::getApplicationPath() {
    QDir ret(QApplication::applicationDirPath());

#ifdef Q_OS_MAC
    if (ret.dirName() == "MacOS") {
        ret.cdUp();
        // deployed (scripts inside app bundle):
        if (ret.cd("Resources/scripts")) {
            ret.cdUp();
        }
        // development (scripts outside add bundle):
        else {
            ret.cdUp();
            ret.cdUp();
        }
    }
#endif

    if (ret.dirName() == "debug" || ret.dirName() == "release") {
        ret.cdUp();
    }

    return ret.path();
}

/**
 * \return List of all plugin paths for application plugins and add on
 * plugins in the application data location (for user specific plugins).
 */
QStringList RSettings::getPluginPaths() {
    QStringList ret;

    ret << RSettings::getPluginPath();

    QDir dataDir(RSettings::getDataLocation());
    QStringList addOns = dataDir.entryList(QDir::NoDotAndDotDot|QDir::Readable|QDir::Dirs|QDir::Executable, QDir::Name);

    for (int i=0; i<addOns.length(); i++) {
        if (addOns[i]=="scripts") {
            continue;
        }
        QFileInfo fi(dataDir.absolutePath() + QDir::separator() + addOns[i] + QDir::separator() + "plugins");
        if (fi.exists()) {
            ret.append(fi.absolutePath());
        }
    }

    return ret;
}

/**
 * \return Path to the application plugins folder.
 */
QString RSettings::getPluginPath() {
    QDir appDir = QDir(getApplicationPath());

#ifdef Q_OS_MAC
    if (isDeployed()) {
        appDir.cdUp();
    }
#endif

    QString pluginFolder = "plugins";
#ifdef Q_OS_MAC
    pluginFolder = "PlugIns";
#endif
    if (!appDir.cd(pluginFolder)) {
        qWarning() << QString("Folder '%1' does not exist").arg(pluginFolder);
        return QString();
    }

    return appDir.path();
}

/**
 * \return Path to current theme or empty to use the default theme.
 */
QString RSettings::getThemePath() {
    if (!themePath.isNull()) {
        return themePath;
    }

    QString theme = RSettings::getStringValue("Theme/ThemeName", "");
    if (theme.isEmpty() || theme=="Default") {
        return "";
    }

    themePath = "themes/" + theme;

    return themePath;
}

/**
 * \return Standard path for the given standard location.
 * \param sl QStandardPaths::StandardLocation or QDesktopServices::StandardLocation
 */
QString RSettings::getStandardLocation(int sl) {
#if QT_VERSION >= 0x050000
    QStringList candidates = QStandardPaths::standardLocations((QStandardPaths::StandardLocation)sl);
    if (candidates.length()>0) {
        return candidates[0];
    }
    return "";
#else
    return QDesktopServices::storageLocation((QDesktopServices::StandardLocation)sl);
#endif
}

/**
 * \return Standard path for caches.
 */
QString RSettings::getCacheLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::CacheLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::CacheLocation);
#endif
}

/**
 * \return Standard path for user data.
 */
QString RSettings::getDataLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::DataLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::DataLocation);
#endif
}

/**
 * \return Standard path for temporary files.
 */
QString RSettings::getTempLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::TempLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::TempLocation);
#endif
}

/**
 * \return Standard path for user desktop files.
 */
QString RSettings::getDesktopLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::DesktopLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::DesktopLocation);
#endif
}

/**
 * \return Standard path for user documents.
 */
QString RSettings::getDocumentsLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::DocumentsLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::DocumentsLocation);
#endif
}

/**
 * \return Standard path for user home.
 */
QString RSettings::getHomeLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::HomeLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::HomeLocation);
#endif
}

/**
 * \return True if the GUI is enabled (no -no-gui switch present).
 * The GUI is typically disabled for command line tools.
 */
bool RSettings::isGuiEnabled() {
    return !QCoreApplication::arguments().contains("-no-gui");
}

/**
 * \return True if the script debugger is enabled.
 */
bool RSettings::isDebuggerEnabled() {
    return QCoreApplication::arguments().contains("-enable-script-debugger");
}

/**
 * \return True if -quit was passed to the application binary.
 */
bool RSettings::hasQuitFlag() {
    return quitFlag;
}

void RSettings::setQuitFlag() {
    quitFlag = true;
}

//QString RSettings::getDefaultStyle(){
//    return "body { font-family:sans; font-size:11pt; }";
//}

/**
 * \return File name of the application settings file (.ini or .conf).
 */
QString RSettings::getFileName() {
    return getQSettings()->fileName();
}

/**
 * \return Path where the configuration file is stored.
 */
QString RSettings::getPath() {
    return QFileInfo(getFileName()).absolutePath();
}

void RSettings::setLaunchPath(const QString& path) {
    launchPath = path;
}

/**
 * \return Path from where the application was launched (can be any path).
 */
QString RSettings::getLaunchPath() {
    return launchPath;
}

/**
 * \return Locale to be used for translations ('en', 'de', 'de_DE', ...)
 */
QString RSettings::getLocale() {
    // override settings if the locale argument is provided
    QStringList args = QCoreApplication::arguments();
    for (int i=1; i<args.length(); ++i) {
        if (args[i] == "-locale") {
            ++i;
            if (i < args.length()) {
                return args[i];
            }
        }
    }

    return RSettings::getStringValue("Language/UiLanguage", "en");
}

/**
 * Loads the translations for the given module.
 * \param module Module name ('qcadcore', 'qcadentity', ...)
 * \param dirs List of directories to look for translation files or empty to check default directories.
 */
void RSettings::loadTranslations(const QString& module, const QStringList& dirs) {
    QString locale = RSettings::getLocale();

    QStringList translationsDirs = dirs;
    if (translationsDirs.isEmpty()) {
        translationsDirs = RS::getDirectoryList("ts");
    }

    QTranslator* translator = new QTranslator(qApp);
    for (int i=0; i<translationsDirs.size(); ++i) {
        QString name = module + "_" + locale;
        if (translator->load(name, translationsDirs[i])) {
            QCoreApplication::installTranslator(translator);
            break;
        }
        else {
            if (locale!="en") {
                qWarning() << "Cannot load translation:" << name;
            }
        }
    }
}

/**
 * Translates the given string for the given context.
 */
QString RSettings::translate(const QString& context, const QString& str) {
    return QCoreApplication::translate((const char*)context.toUtf8(), (const char*)str.toUtf8());
}

/**
 * \return List of all keys stored in the application settings file.
 */
QStringList RSettings::getAllKeys(const QString& group) {
    QSettings* qs = getQSettings();
    qs->beginGroup(group);
    QStringList res = qs->allKeys();
    qs->endGroup();
    return res;
}

/**
 * \return Pointer to underlying QSettings object.
 */
QSettings* RSettings::getQSettings() {
    if (qSettings==NULL) {
        QString appName = QCoreApplication::applicationName();
        if (!applicationNameOverride.isEmpty()) {
            appName = applicationNameOverride;
        }

        qSettings =
            new QSettings(
#if defined(Q_OS_WIN) || defined(Q_OS_MAC)
                QSettings::IniFormat,
#else
                QSettings::NativeFormat,
#endif
                QSettings::UserScope,
                QCoreApplication::organizationName(),
                appName
            );
    }
    return qSettings;
}

/**
 * Initializes the recent files list (recentFiles).
 */
void RSettings::initRecentFiles() {
    if (recentFiles.isEmpty()) {
        recentFiles = getValue("RecentFiles/Files", QStringList()).toStringList();
    }
}

/**
 * Adds a recent file to the list of recent files. 
 * The newest file is always at the end of the list.
 */
void RSettings::addRecentFile(const QString& fileName) {
    initRecentFiles();
    QFileInfo fi(fileName);
    QString absFileName = fi.absoluteFilePath();
    if (recentFiles.contains(absFileName)) {
        recentFiles.removeAll(absFileName);
    }
    recentFiles.append(fi.absoluteFilePath());
    shortenRecentFiles();
}

/**
 * \return List of recent files.
 */
QStringList RSettings::getRecentFiles() {
    initRecentFiles();
    shortenRecentFiles();
    return recentFiles;
}

/**
 * Purges recent files that exceed the RecentFiles/RecentFilesSize limit.
 */
void RSettings::shortenRecentFiles() {
    initRecentFiles();
    int historySize = getValue("RecentFiles/RecentFilesSize", 10).toInt();
    while (recentFiles.length() > historySize) {
        recentFiles.removeFirst();
    }
    setValue("RecentFiles/Files", recentFiles);
}

/**
 * Removes the given file from the list of recent files.
 */
void RSettings::removeRecentFile(const QString& fileName) {
    initRecentFiles();
    recentFiles.removeAll(QFileInfo(fileName).absoluteFilePath());
    setValue("RecentFiles/Files", recentFiles);
}

/**
 * Clears the list of recent files.
 */
void RSettings::clearRecentFiles() {
    recentFiles.clear();
    setValue("RecentFiles/Files", recentFiles);
}

void RSettings::setRulerFont(const QFont& font) {
    setValue("GraphicsViewFonts/Ruler", font);
    if (rulerFont!=NULL) {
        delete rulerFont;
    }
    rulerFont = new QFont(font);
}

QFont RSettings::getRulerFont() {
    if (rulerFont==NULL) {
        // get application's default font (pixel size is -1, point size e.g. 10pt):
        QFont font;
        font.setPointSize(9*getDevicePixelRatio());
        rulerFont = new QFont(getValue("GraphicsViewFonts/Ruler", font).value<QFont>());
    }
    return *rulerFont;
}

void RSettings::setSnapLabelFont(const QFont& font) {
    setValue("GraphicsViewFonts/SnapLabel", font);
    if (snapLabelFont!=NULL) {
        delete snapLabelFont;
    }
    snapLabelFont = new QFont(font);
}

QFont RSettings::getSnapLabelFont() {
    if (snapLabelFont==NULL) {
        // get application's default font (pixel size is -1, point size e.g. 10pt):
        QFont font;
        font.setPointSize(9);
        snapLabelFont = new QFont(getValue("GraphicsViewFonts/SnapLabel", font).value<QFont>());
    }
    return *snapLabelFont;
}

QFont RSettings::getInfoLabelFont() {
    if (infoLabelFont==NULL) {
        // get application's default font (pixel size is -1, point size e.g. 10pt):
        QFont font;
        font.setPointSize(11);
        infoLabelFont = new QFont(getValue("GraphicsViewFonts/InfoLabel", font).value<QFont>());
    }
    return *infoLabelFont;
}

QFont RSettings::getStatusBarFont() {
    if (statusBarFont==NULL) {
        // get application's default font (pixel size is -1, point size e.g. 10pt):
        QFont font;
        font.setPointSize(9);
        statusBarFont = new QFont(getValue("StatusBar/Font", font).value<QFont>());
    }
    return *statusBarFont;
}

RColor RSettings::getSelectionColor() {
    if (selectionColor==NULL) {
        selectionColor = new RColor(getColor("GraphicsViewColors/SelectionColor", RColor(164,70,70,128)));
    }
    return *selectionColor;
}

RColor RSettings::getReferencePointColor() {
    if (referencePointColor==NULL) {
        referencePointColor = new RColor(getColor("GraphicsViewColors/ReferencePointColor", RColor(0,0,172)));
    }
    return *referencePointColor;
}

RColor RSettings::getStartReferencePointColor() {
    if (startReferencePointColor==NULL) {
        startReferencePointColor = new RColor(getColor("GraphicsViewColors/StartReferencePointColor", RColor(192,0,32)));
    }
    return *startReferencePointColor;
}

RColor RSettings::getEndReferencePointColor() {
    if (endReferencePointColor==NULL) {
        endReferencePointColor = new RColor(getColor("GraphicsViewColors/EndReferencePointColor", RColor(0,0,172)));
    }
    return *endReferencePointColor;
}

RColor RSettings::getSecondaryReferencePointColor() {
    if (secondaryReferencePointColor==NULL) {
        secondaryReferencePointColor = new RColor(getColor("GraphicsViewColors/SecondaryReferencePointColor", RColor(0,128,172)));
    }
    return *secondaryReferencePointColor;
}

RColor RSettings::getTertiaryReferencePointColor() {
    if (tertiaryReferencePointColor==NULL) {
        tertiaryReferencePointColor = new RColor(getColor("GraphicsViewColors/TertiaryReferencePointColor", RColor(0,64,172)));
    }
    return *tertiaryReferencePointColor;
}

bool RSettings::getAutoScaleGrid() {
    return getValue("GraphicsView/AutoScaleGrid", true).toBool();
}

bool RSettings::getAutoScaleMetaGrid() {
    return getValue("GraphicsView/AutoScaleMetaGrid", true).toBool();
}

bool RSettings::getAutoScalePatterns() {
    return getValue("GraphicsView/AutoScalePatterns", true).toBool();
}

bool RSettings::getAutoZoomOnLoad() {
    return getValue("GraphicsView/AutoZoomOnLoad", true).toBool();
}

bool RSettings::getColorCorrection() {
    return getValue("GraphicsView/ColorCorrection", true).toBool();
}

bool RSettings::getColorCorrectionDisableForPrinting() {
    return getValue("GraphicsView/ColorCorrectionDisableForPrinting", false).toBool();
}

int RSettings::getColorThreshold() {
    return getValue("GraphicsView/ColorThreshold", 10).toInt();
}

int RSettings::getTextHeightThreshold() {
    return getValue("GraphicsView/TextHeightThreshold", 3).toInt();
}

double RSettings::getFadingFactor() {
    if (fadingFactor<0.0) {
        fadingFactor = getValue("GraphicsView/FadingFactor", 3.5).toDouble();
    }
    return fadingFactor;
}

double RSettings::getArcAngleLengthThreshold() {
    if (arcAngleLengthThreshold<-0.9) {
        arcAngleLengthThreshold = RMath::deg2rad(getValue("GraphicsView/ArcAngleLengthThreshold", 0.0).toDouble());
    }
    return arcAngleLengthThreshold;
}

double RSettings::getMinArcAngleStep() {
    if (minArcAngleStep<-0.9) {
        minArcAngleStep = RMath::deg2rad(getValue("GraphicsView/MinArcAngleStep", 0.2).toDouble());
    }
    return minArcAngleStep;
}

int RSettings::getDashThreshold() {
    if (dashThreshold==-1) {
        dashThreshold = getValue("GraphicsView/DashThreshold", 1000).toInt();
    }
    return dashThreshold;
}

bool RSettings::isTextRenderedAsText() {
    if (textRenderedAsText==-1) {
        textRenderedAsText = getStringValue("TextRendering/RenderAs", "Text") == "Text";
    }
    return textRenderedAsText;
}

bool RSettings::isLayer0CompatibilityOn() {
    if (layer0CompatibilityOn==-1) {
        layer0CompatibilityOn = getStringValue("LayerCompatibility/Layer0", "QCAD") == "Compatibility";
    }
    return layer0CompatibilityOn;
}

bool RSettings::getSelectBlockWithAttribute() {
    if (selectBlockWithAttribute==-1) {
        selectBlockWithAttribute = getBoolValue("GraphicsView/SelectBlockWithAttribute", false);
    }
    return selectBlockWithAttribute;
}

bool RSettings::getHideAttributeWithBlock() {
    if (hideAttributeWithBlock==-1) {
        hideAttributeWithBlock = getBoolValue("GraphicsView/HideAttributeWithBlock", false);
    }
    return hideAttributeWithBlock;
}

bool RSettings::getImportRecomputedDimBlocks() {
    if (importRecomputedDimBlocks==-1) {
        importRecomputedDimBlocks = getBoolValue("Dwg/ImportRecomputedDimBlocks", false);
        if (!importRecomputedDimBlocks) {
            importRecomputedDimBlocks = originalArguments.contains("-recompute-dim") ? 1 : 0;
        }
    }
    return importRecomputedDimBlocks;
}

/**
 * \return True if dragging the reference points of selected block references should be
 * treated like dragging the whole selection.
 */
bool RSettings::getIgnoreBlockReferencePoint() {
    if (ignoreBlockReferencePoint==-1) {
        ignoreBlockReferencePoint = getBoolValue("GraphicsView/IgnoreBlockReferencePoint", false);
    }
    return ignoreBlockReferencePoint;
}

/**
 * \return True if dragging reference points should be treated like dragging the whole selection.
 */
bool RSettings::getIgnoreAllReferencePoints() {
    if (ignoreAllReferencePoints==-1) {
        ignoreAllReferencePoints = getBoolValue("GraphicsView/IgnoreAllReferencePoints", false);
    }
    return ignoreAllReferencePoints;
}

/**
 * \return Size of reference points.
 */
int RSettings::getReferencePointSize() {
    if (referencePointSize==-1) {
        referencePointSize = getIntValue("GraphicsView/ReferencePointSize", 10);
    }
    return referencePointSize;
}

/**
 * \return Shape of reference points.
 */
int RSettings::getReferencePointShape() {
    if (referencePointShape==-1) {
        referencePointShape = getIntValue("GraphicsView/ReferencePointShape", 0);
    }
    return referencePointShape;
}

/**
 * \return True to show slow properties availabe on request.
 */
bool RSettings::getPropertyEditorShowOnRequest() {
    if (propertyEditorShowOnRequest==-1) {
        propertyEditorShowOnRequest = getBoolValue("PropertyEditor/ShowOnRequest", false);
    }
    return propertyEditorShowOnRequest;
}

/**
 * \return Polar coordinate separator (<).
 */
QString RSettings::getPolarCoordinateSeparator() {
    if (polarCoordinateSeparator.isNull()) {
        polarCoordinateSeparator = getStringValue("Input/PolarCoordinateSeparator", "<");
    }
    return polarCoordinateSeparator;
}

/**
 * \return Cartesian coordinate separator (,).
 */
QString RSettings::getCartesianCoordinateSeparator() {
    if (cartesianCoordinateSeparator.isNull()) {
        cartesianCoordinateSeparator = getStringValue("Input/CartesianCoordinateSeparator", ",");
    }
    return cartesianCoordinateSeparator;
}

/**
 * \return Relative coordinate prefix (@).
 */
QString RSettings::getRelativeCoordinatePrefix() {
    if (relativeCoordinatePrefix.isNull()) {
        relativeCoordinatePrefix = getStringValue("Input/RelativeCoordinatePrefix", "@");
    }
    return relativeCoordinatePrefix;
}

/**
 * \return True for macOS dark mode only.
 */
bool RSettings::isDarkMode() {
    if (darkMode==-1) {
#ifdef Q_OS_MAC
        darkMode = (isMacDarkMode() ? 1 : 0);
#else
        darkMode = 0;
#endif
    }
    return darkMode==1;
}

bool RSettings::hasDarkGuiBackground() {
    if (darkGuiBackground==-1) {
        // detect dark QCAD theme:
        if (qApp->styleSheet().contains("IconPostfix:inverse", Qt::CaseInsensitive)) {
            darkGuiBackground = 1;
        }
        else {
#ifdef Q_OS_MAC
            // detect macOS dark mode:
            if (isMacDarkMode()) {
                darkGuiBackground = 1;
            }
            else {
                darkGuiBackground = 0;
            }
            // TODO: support Windows Dark Theme:
//#elif Q_OS_WINDOWS
//            QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",QSettings::NativeFormat);
//            if (settings.value("AppsUseLightTheme")==0){
//                darkGuiBackground = 1;
//            }
//            else {
//                darkGuiBackground = 0;
//            }
#else
            darkGuiBackground = 0;
#endif
        }
    }
    return darkGuiBackground==1;
}

/**
 * \return True if a custom stylesheet is present for the whole application. Z.B. a theme is present.
 */
bool RSettings::hasCustomStyleSheet() {
    return !qApp->styleSheet().isEmpty();
}

QStringList RSettings::getPrinterNames() {
#if QT_VERSION >= 0x050300
    return QPrinterInfo::availablePrinterNames();
#else
    QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
    QStringList ret;
    for (int i=0; i<printers.length(); i++) {
        ret.append(printers[i].printerName());
    }
    return ret;
#endif
}

QString RSettings::getDefaultPrinterName() {
#if QT_VERSION >= 0x050300
    return QPrinterInfo::defaultPrinterName();
#else
    QPrinterInfo printer = QPrinterInfo::defaultPrinter();
    if (printer.isNull()) {
        return QString();
    }
    return printer.printerName();
#endif
}

void RSettings::appendOpenGLMessage(const QString& msg) {
    if (openGLMessages.contains(msg)) {
        // avoid redundant messages:
        return;
    }
    openGLMessages.append(msg);
}

QStringList RSettings::getOpenGLMessages() {
    return openGLMessages;
}

/**
 * \return Qt version as int (Qt 1.2.3 -> 0x010203).
 */
int RSettings::getQtVersion() {
    return QT_VERSION;
}

/**
 * \return Qt version as human readable string ("1.2.3").
 */
QString RSettings::getQtVersionString() {
    return qVersion();
}

/**
 * \return True if application was compiled against the given major Qt version.
 */
bool RSettings::isQt(int majorVersion) {
    return QT_VERSION >= majorVersion<<16;
}

/**
 * \return Compiler name and version as human readable string.
 */
QString RSettings::getCompilerVersion() {
#if defined(Q_CC_CLANG)
    return QString("Clang %1.%2.%3").arg(__clang_major__).arg(__clang_minor__).arg(__clang_patchlevel__);
#elif defined(Q_CC_GNU)
    return QString("gcc %1.%2.%3").arg(__GNUC__).arg(__GNUC_MINOR__).arg(__GNUC_PATCHLEVEL__);
#elif defined(Q_CC_MSVC)
#   if _MSC_VER==1310
        return "MSVC++ 7.1 (2003)";
#   elif _MSC_VER==1400
        return "MSVC++ 8.0 (2005)";
#   elif _MSC_VER==1500
        return "MSVC++ 9.0 (2008)";
#   elif _MSC_VER==1600
        return "MSVC++ 10.0 (2010)";
#   elif _MSC_VER==1700
        return "MSVC++ 11.0 (2012)";
#   elif _MSC_VER==1800
        return "MSVC++ 12.0 (2013)";
#   elif _MSC_VER==1900
        return "MSVC++ 14.0 (2015)";
#   endif
#endif
    return "Unknown";
}

/**
 * \return OS name and version as human readable string.
 */
QString RSettings::getOSVersion() {
#if QT_VERSION >= 0x050400
    return QSysInfo::productVersion();
#else
#ifdef Q_OS_WIN
    switch (QSysInfo::windowsVersion()) {
    case QSysInfo::WV_NT:
        return "Windows NT (operating system version 4.0)";
    case QSysInfo::WV_2000:
        return "Windows 2000 (operating system version 5.0)";
    case QSysInfo::WV_XP:
        return "Windows XP (operating system version 5.1)";
    case QSysInfo::WV_2003:
        return "Windows Server 2003, Windows Server 2003 R2, Windows Home Server, Windows XP Professional x64 Edition (operating system version 5.2)";
    case QSysInfo::WV_VISTA:
        return "Windows Vista, Windows Server 2008 (operating system version 6.0)";
    case QSysInfo::WV_WINDOWS7:
        return "Windows 7, Windows Server 2008 R2 (operating system version 6.1)";
    // QSysInfo::WV_WINDOWS8:
    case 0x00a0:
        return "Windows 8";
    // QSysInfo::WV_WINDOWS8_1:
    case 0x00b0:
        return "Windows 8.1";
    // QSysInfo::WV_WINDOWS10:
    case 0x00c0:
        return "Windows 10";
    default:
        return "Windows >= 10";
    }
#elif defined (Q_OS_MAC)
    switch (QSysInfo::MacintoshVersion) {
    case QSysInfo::MV_9:
        return "Mac OS 9 (Unsupported)";
    case QSysInfo::MV_10_0:
        return "Mac OS X 10.0 (Unsupported)";
    case QSysInfo::MV_10_1:
        return "Mac OS X 10.1 (Unsupported)";
    case QSysInfo::MV_10_2:
        return "Mac OS X 10.2 (Unsupported)";
    case QSysInfo::MV_10_3:
        return "Mac OS X 10.3 (Panther)";
    case QSysInfo::MV_10_4:
        return "Mac OS X 10.4 (Tiger)";
    case QSysInfo::MV_10_5:
        return "Mac OS X 10.5 (Leopard)";
    case QSysInfo::MV_10_6:
        return "Mac OS X 10.6 (Snow Leopard)";
    case QSysInfo::MV_10_7:
        return "Mac OS X 10.7 (Lion)";
    case QSysInfo::MV_10_8:
        return "Mac OS X 10.8 (Mountain Lion)";
    // QSysInfo::MV_10_9:
    case 0x000B:
        return "Mac OS X 10.9 (Mavericks)";
    // QSysInfo::MV_10_10:
    case 0x000C:
        return "Mac OS X 10.10 (Yosemite)";
    // QSysInfo::MV_10_11:
    case 0x000D:
        return "Mac OS X 10.11 (El Capitan)";
    // QSysInfo::MV_10_12:
    case 0x000E:
        return "macOS 10.12 (Sierra)";
    // QSysInfo::MV_10_13:
    case 0x000F:
        return "macOS 10.13 (High Sierra)";
    // QSysInfo::MV_10_14:
    case 0x0010:
        return "macOS 10.14 (Mojave)";
    // QSysInfo::MV_10_15:
    case 0x0011:
        return "macOS 10.15 (Catalina)";
    default:
    case QSysInfo::MV_Unknown:
        return "macOS > 10.15 (Unsupported)";
    }
#else
    return "Unknown";
#endif
#endif
}

/**
 * \return Application version as human readable string.
 */
QString RSettings::getVersionString() {
    return R_QCAD_VERSION_STRING;
}

/**
 * \return Application version as 01020304 for 1.2.3.4
 */
QString RSettings::getNumericalVersionString() {
    return QString("%1%2%3%4")
            .arg(R_QCAD_VERSION_MAJOR, 2, 10, QChar('0'))
            .arg(R_QCAD_VERSION_MINOR, 2, 10, QChar('0'))
            .arg(R_QCAD_VERSION_REV, 2, 10, QChar('0'))
            .arg(R_QCAD_VERSION_BUILD, 2, 10, QChar('0'));
}

int RSettings::getMajorVersion() {
    return R_QCAD_VERSION_MAJOR;
}

int RSettings::getMinorVersion() {
    return R_QCAD_VERSION_MINOR;
}

int RSettings::getRevisionVersion() {
    return R_QCAD_VERSION_REV;
}

int RSettings::getBuildVersion() {
    return R_QCAD_VERSION_BUILD;
}

/**
 * \return Git revision number, stored in file revision.txt for deployed applications.
 */
QString RSettings::getRevisionString() {
    QString ret = "";
    QFile f("revision.txt");
    if (f.open(QFile::ReadOnly)) {
        ret = QString(f.readAll());
        f.close();
    }
    return ret;
}

QString RSettings::getReleaseDate() {
    return __DATE__;
}

int RSettings::getSnapRange() {
    if (snapRange==-1) {
        snapRange = getValue("GraphicsView/SnapRange", QVariant(10)).toInt();
        if (getHighResolutionGraphicsView()) {
            snapRange *= getDevicePixelRatio();
        }
    }
    return snapRange;
}

int RSettings::getPickRange() {
    if (pickRange==-1) {
        pickRange = getValue("GraphicsView/PickRange", QVariant(10)).toInt();
        if (getHighResolutionGraphicsView()) {
            pickRange *= getDevicePixelRatio();
        }
    }
    return pickRange;
}

int RSettings::getZeroWeightWeight() {
    if (zeroWeightWeight==-1) {
        zeroWeightWeight = getValue("GraphicsView/ZeroWeightWeight", QVariant(100)).toInt();
    }
    return zeroWeightWeight;
}

int RSettings::getPreviewEntities() {
    if (previewEntities==-1) {
        previewEntities = getValue("GraphicsView/PreviewEntities", QVariant(50)).toInt();
    }
    return previewEntities;
}

bool RSettings::getLimitZoomAndScroll() {
    if (limitZoomAndScroll==-1) {
        limitZoomAndScroll = getValue("GraphicsViewNavigation/LimitZoomAndScroll", QVariant(false)).toBool();
    }
    return (bool)limitZoomAndScroll;
}

bool RSettings::getShowCrosshair() {
    if (showCrosshair==-1) {
        showCrosshair = getValue("GraphicsView/ShowCrosshair",  QVariant(true)).toBool();
    }
    return (bool)showCrosshair;
}

void RSettings::setShowCrosshair(bool on) {
    setValue("GraphicsView/ShowCrosshair", on);
    showCrosshair = on;
}

bool RSettings::getShowLargeCrosshair() {
    if (showLargeCrosshair==-1) {
        showLargeCrosshair = getValue("GraphicsView/ShowLargeCrosshair",  QVariant(true)).toBool();
    }
    return (bool)showLargeCrosshair;
}

void RSettings::setShowLargeCrosshair(bool on) {
    setValue("GraphicsView/ShowLargeCrosshair", on);
    showLargeCrosshair = on;
}

bool RSettings::getShowLargeOriginAxis() {
    if (showLargeOriginAxis==-1) {
        showLargeOriginAxis = getValue("GraphicsView/ShowLargeOriginAxis", QVariant(false)).toBool();
    }
    return (bool)showLargeOriginAxis;
}

void RSettings::setShowLargeOriginAxis(bool on) {
    setValue("GraphicsView/ShowLargeOriginAxis", on);
    showLargeOriginAxis = on;
}

bool RSettings::getConcurrentDrawing() {
    if (concurrentDrawing==-1) {
        concurrentDrawing = getValue("GraphicsView/ConcurrentDrawing",  QVariant(false)).toBool();
    }
    return (bool)concurrentDrawing;
}

void RSettings::setConcurrentDrawing(bool on) {
    setValue("GraphicsView/ConcurrentDrawing", on);
    concurrentDrawing = on;
}

bool RSettings::getHighResolutionGraphicsView() {
    if (highResolutionGraphicsView==-1) {
        highResolutionGraphicsView = getValue("GraphicsView/HighResolutionGraphicsView", QVariant(false)).toBool();
    }
    return (bool)highResolutionGraphicsView;
}

QLocale RSettings::getNumberLocale() {
    if (numberLocale==NULL) {
        if (getValue("Input/DecimalPoint", ".").toString()==",") {
            // any locale that uses commas instead of dots will do:
            numberLocale = new QLocale(QLocale::German, QLocale::Germany);
            numberLocale->setNumberOptions(QLocale::OmitGroupSeparator);
        }
        else {
            numberLocale = new QLocale(QLocale::C, QLocale::AnyCountry);
            numberLocale->setNumberOptions(QLocale::OmitGroupSeparator);
        }
    }

    return *numberLocale;
}

/**
 * \return Value of the given setting as color or defaultValue.
 */
RColor RSettings::getColor(const QString& key, const RColor& defaultValue) {
    // colors are 'different' and need to be handled without RSettings::getValue:
    if (!isInitialized()) {
        return defaultValue;
    }
    if (cache.contains(key)) {
        return cache[key].value<RColor>();
    }

    // slow operation:
    QVariant stored = getQSettings()->value(key);
    if (!stored.isValid()) {
        return defaultValue;
    }
    RColor ret = stored.value<RColor>();
    QVariant v;
    v.setValue(ret);
    cache[key] = v;

    return ret;
}

/**
 * \return True if the given key is available in the application settings file.
 */
bool RSettings::hasValue(const QString& key) {
    if (!isInitialized()) {
        return false;
    }
    if (cache.contains(key)) {
        return true;
    }
    QVariant ret = getQSettings()->value(key);
    return ret.isValid();
}

/**
 * \return Value of the given setting as variant or defaultValue.
 */
QVariant RSettings::getValue(const QString& key, const QVariant& defaultValue) {
    if (!isInitialized()) {
        qDebug() << "RSettings not initialized";
        return defaultValue;
    }
    if (cache.contains(key)) {
        return cache[key];
    }

    // slow operation:
    QVariant ret = getQSettings()->value(key);
    if (!ret.isValid()) {
        return defaultValue;
    }
    if (ret.canConvert<RColor>()) {
        RColor col = ret.value<RColor>();
        QVariant v;
        v.setValue(col);
        cache[key] = v;
    }
    else {
        //if (defaultValue.isValid()) {
            //ret.convert(defaultValue.type());
        //}
        cache[key] = ret;
    }

    return ret;
}

/**
 * \return Value of the given setting as boolean or defaultValue.
 */
bool RSettings::getBoolValue(const QString& key, bool defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toBool();
}

/**
 * \return Value of the given setting as color or defaultValue.
 */
RColor RSettings::getColorValue(const QString& key, const RColor& defaultValue) {
    QVariant vd;
    vd.setValue(defaultValue);
    QVariant ret = getValue(key, vd);
    if (ret.canConvert<RColor>()) {
        return ret.value<RColor>();
    }
#if QT_VERSION >= 0x050000
    else if (ret.canConvert(QMetaType::QString)) {
#else
    else if (ret.canConvert(QVariant::String)) {
#endif
        return RColor(ret.toString());
    }
#if QT_VERSION >= 0x050000
    else if (ret.canConvert(QMetaType::QColor)) {
#else
    else if (ret.canConvert(QVariant::Color)) {
#endif
        return RColor(ret.value<QColor>());
    }
    else {
        return defaultValue;
    }
}

/**
 * \return Value of the given setting as double or defaultValue.
 */
double RSettings::getDoubleValue(const QString& key, double defaultValue) {
    QVariant ret = getValue(key, defaultValue);

    // if the variant is a list or string list, return the first entry
    // used for example for stored RMathLineEdit values
    if (ret.type()==QVariant::List || ret.canConvert<QStringList>()) {
        if (ret.toList().count()>0) {
            ret = ret.toList().at(0);
        }
    }

    QString str = ret.toString();
    double d;
    if (str.isEmpty()) {
        return defaultValue;
    }
    else if (QRegExp("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$").exactMatch(str)) {
        d = ret.toDouble();
    }
    else {
        d = RMath::eval(str);
    }

    if (RMath::isNaN(d)) {
        return defaultValue;
    }
    return d;
}

/**
 * \return Value of the given setting as int or defaultValue.
 */
int RSettings::getIntValue(const QString& key, int defaultValue) {
    QVariant retVar = getValue(key, defaultValue);
    bool ok;
    int ret = retVar.toInt(&ok);
    if (!ok) {
        return defaultValue;
    }
    return ret;
}

/**
 * \return Value of the given setting as string or defaultValue.
 */
QString RSettings::getStringValue(const QString& key, const QString& defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toString();
}

/**
 * \return Value of the given setting as string list or defaultValue.
 */
QStringList RSettings::getStringListValue(const QString& key, const QStringList& defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toStringList();
}

/**
 * \return Value of the given setting as char or defaultValue.
 */
QChar RSettings::getCharValue(const QString& key, const QChar& defaultValue) {
    QString ret = getStringValue(key, defaultValue);
    if (ret.isEmpty()) {
        return defaultValue;
    }
    return ret[0];
}

/**
 * Sets the variable with the given key and value, overwriting an existing value if overwrite is true (default).
 */
void RSettings::setValue(const QString& key, const QVariant& value, bool overwrite) {
    if (!isInitialized()) {
        return;
    }

    if (!overwrite && hasValue(key)) {
        // value exists and will not be overwritten:
        return;
    }

    cache[key] = value;

    if (!noWrite) {
        // TODO: fix:
        if (QString(value.typeName())=="QPrinter::PageSize") {
            getQSettings()->setValue(key, value.toInt());
        }
        else {
            getQSettings()->setValue(key, value);
        }
    }
}

/**
 * Removes the value for the given key.
 */
void RSettings::removeValue(const QString& key) {
    if (!isInitialized()) {
        return;
    }

    cache.remove(key);

    if (!noWrite) {
        getQSettings()->remove(key);
    }
}

bool RSettings::isInitialized() {
    return !qApp->organizationName().isEmpty();
}

/**
 * Sets the application name override used for the configuration file name (e.g. QCAD3).
 */
void RSettings::setApplicationNameOverride(const QString& n) {
    applicationNameOverride = n;
}

QString RSettings::getApplicationNameOverride() {
    return applicationNameOverride;
}

bool RSettings::hasApplicationNameOverride() {
    return !applicationNameOverride.isEmpty();
}

void RSettings::setXDataEnabled(bool on) {
    xDataEnabled = on;
}

bool RSettings::isXDataEnabled() {
    return xDataEnabled;
}

void RSettings::setNextVersionEnabled(bool on) {
    nextVersionEnabled = on;
}

bool RSettings::isNextVersionEnabled() {
    return nextVersionEnabled;
}

bool RSettings::getAutoScaleLinetypePatterns() {
    if (autoScaleLinetypePattern==-1) {
        autoScaleLinetypePattern = getValue("GraphicsView/AutoScaleLinetypePatterns", QVariant(true)).toBool();
    }
    return (bool)autoScaleLinetypePattern;
}

bool RSettings::getUseSecondarySelectionColor() {
    if (useSecondarySelectionColor==-1) {
        useSecondarySelectionColor = getValue("GraphicsViewColors/UseSecondarySelectionColor", QVariant(false)).toBool();
    }
    return (bool)useSecondarySelectionColor;
}

bool RSettings::getUseSolidLineSelection() {
    if (useSolidLineSelection==-1) {
        useSolidLineSelection = getValue("GraphicsView/UseSolidLineSelection", QVariant(true)).toBool();
    }
    return (bool)useSolidLineSelection;
}

int RSettings::getMouseThreshold() {
    if (mouseThreshold==-1) {
        mouseThreshold = getValue("GraphicsView/MouseThreshold", QVariant(5)).toInt();
    }
    return mouseThreshold;
}

bool RSettings::getPositionByMousePress() {
    if (positionByMousePress==-1) {
        positionByMousePress = getValue("GraphicsView/PositionByMousePress", QVariant(false)).toBool();
    }
    return (bool)positionByMousePress;
}

bool RSettings::getAllowMouseMoveInterruptions() {
    if (allowMouseMoveInterruptions==-1) {
        allowMouseMoveInterruptions = getValue("GraphicsView/AllowMouseMoveInterruptions", QVariant(true)).toBool();
    }
    return (bool)allowMouseMoveInterruptions;
}

void RSettings::resetCache() {
    if (rulerFont!=NULL) {
        delete rulerFont;
        rulerFont = NULL;
    }
    if (snapLabelFont!=NULL) {
        delete snapLabelFont;
        snapLabelFont = NULL;
    }
    if (infoLabelFont!=NULL) {
        delete infoLabelFont;
        infoLabelFont = NULL;
    }
    if (statusBarFont!=NULL) {
        delete statusBarFont;
        statusBarFont = NULL;
    }
    if (selectionColor!=NULL) {
        delete selectionColor;
        selectionColor = NULL;
    }
    if (referencePointColor!=NULL) {
        delete referencePointColor;
        referencePointColor = NULL;
    }
    if (secondaryReferencePointColor!=NULL) {
        delete secondaryReferencePointColor;
        secondaryReferencePointColor = NULL;
    }
    if (tertiaryReferencePointColor!=NULL) {
        delete tertiaryReferencePointColor;
        tertiaryReferencePointColor = NULL;
    }
    snapRange = -1;
    zeroWeightWeight = -1;
    showCrosshair = -1;
    showLargeCrosshair = -1;
    showLargeOriginAxis = -1;
    concurrentDrawing = -1;
    highResolutionGraphicsView = -1;
    previewEntities = -1;
    limitZoomAndScroll = -1;
    autoScaleLinetypePattern = -1;
    useSecondarySelectionColor = -1;
    useSolidLineSelection = -1;
    arcAngleLengthThreshold = -1;
    positionByMousePress = -1;
    minArcAngleStep = -1;
    dashThreshold = -1;
    textRenderedAsText = -1;
    layer0CompatibilityOn = -1;
    selectBlockWithAttribute = -1;
    hideAttributeWithBlock = -1;
    importRecomputedDimBlocks = -1;
    ignoreBlockReferencePoint = -1;
    ignoreAllReferencePoints = -1;
    referencePointSize = -1;
    referencePointShape = -1;
    cartesianCoordinateSeparator = QString::null;
    polarCoordinateSeparator = QString::null;
    relativeCoordinatePrefix = QString::null;
    mouseThreshold = -1;
    themePath = QString();
    cache.clear();
    darkMode = -1;
    darkGuiBackground = -1;
    fadingFactor = -1;
}

void RSettings::uninit() {
    if (qSettings!=NULL) {
        delete qSettings;
        qSettings = NULL;
    }
}

void RSettings::setNoWrite(bool on) {
    noWrite = on;
}
