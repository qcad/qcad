/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include <QCoreApplication>
#include <QFileInfo>
#include <QStringList>
#include <QTranslator>

#if QT_VERSION >= 0x050000
#  include <QStandardPaths>
#else
#  include <QDesktopServices>
#endif

#include "RDebug.h"
#include "RMath.h"
#include "RSettings.h"
#include "RVersion.h"

QVariantMap RSettings::cache;

QString RSettings::launchPath;

QFont* RSettings::rulerFont = NULL;
QFont* RSettings::snapLabelFont = NULL;
QFont* RSettings::infoLabelFont = NULL;
QFont* RSettings::statusBarFont = NULL;
RColor* RSettings::selectionColor = NULL;
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
double RSettings::minArcAngleStep = -1;
int RSettings::dashThreshold = -1;
int RSettings::textRenderedAsText = -1;
int RSettings::layer0CompatibilityOn = -1;
int RSettings::selectBlockWithAttribute = -1;
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

QString RSettings::getAppId() {
    QString ret = qApp->applicationName();
    ret.replace(QRegExp("[^a-zA-Z0-9]"), "");
    // prevent 'empty record name' exception:
    if (ret.isEmpty()) {
        ret = "QCAD";
    }
    return ret;
}

double RSettings::getDevicePixelRatio() {
#if QT_VERSION >= 0x050000
    return qApp->devicePixelRatio();
#else
    return 1.0;
#endif
}

QStringList RSettings::getOriginalArguments() {
    return originalArguments;
}

void RSettings::setOriginalArguments(const QStringList& a) {
    originalArguments = a;
}

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
 * plugins in the application data location.
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

QString RSettings::getCacheLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::CacheLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::CacheLocation);
#endif
}

QString RSettings::getDataLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::DataLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::DataLocation);
#endif
}

QString RSettings::getTempLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::TempLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::TempLocation);
#endif
}

QString RSettings::getDesktopLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::DesktopLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::DesktopLocation);
#endif
}

QString RSettings::getDocumentsLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::DocumentsLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::DocumentsLocation);
#endif
}

QString RSettings::getHomeLocation() {
#if QT_VERSION >= 0x050000
    return RSettings::getStandardLocation(QStandardPaths::HomeLocation);
#else
    return RSettings::getStandardLocation(QDesktopServices::HomeLocation);
#endif
}

bool RSettings::isGuiEnabled() {
    return !QCoreApplication::arguments().contains("-no-gui");
}

bool RSettings::isDebuggerEnabled() {
    return QCoreApplication::arguments().contains("-enable-script-debugger");
}

bool RSettings::hasQuitFlag() {
    return quitFlag;
}

void RSettings::setQuitFlag() {
    quitFlag = true;
}

QString RSettings::getDefaultStyle(){
    return "body { font-family:sans; font-size:11pt; }";
}

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

QString RSettings::getLaunchPath() {
    return launchPath;
}

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

void RSettings::loadTranslations(const QString& module, const QStringList& dirs) {
    QString locale = RSettings::getLocale();
    if (locale == "en" || locale.toLower() == "en_us") {
        return;
    }

    QStringList translationsDirs = dirs;
    if (translationsDirs.isEmpty()) {
        translationsDirs = RS::getDirectoryList("ts");
    }

    QTranslator* translator = new QTranslator(qApp);
    bool success = false;
    for (int i=0; i<translationsDirs.size(); ++i) {
        if (translator->load(module + "_" + locale, translationsDirs[i])) {
            QCoreApplication::installTranslator(translator);
            success = true;
            break;
        }
    }
}

QString RSettings::translate(const QString& context, const QString& str) {
    return QCoreApplication::translate((const char*)context.toLatin1(), (const char*)str.toLatin1());
}

QStringList RSettings::getAllKeys(const QString& group) {
    QSettings* qs = getQSettings();
    qs->beginGroup(group);
    QStringList res = qs->allKeys();
    qs->endGroup();
    return res;
}

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

QStringList RSettings::getRecentFiles() {
    initRecentFiles();
    shortenRecentFiles();
    return recentFiles;
}

void RSettings::shortenRecentFiles() {
    initRecentFiles();
    int historySize = getValue("RecentFiles/RecentFilesSize", 10).toInt();
    while (recentFiles.length() > historySize) {
        recentFiles.removeFirst();
    }
    setValue("RecentFiles/Files", recentFiles);
}

void RSettings::removeRecentFile(const QString& fileName) {
    initRecentFiles();
    recentFiles.removeAll(QFileInfo(fileName).absoluteFilePath());
    setValue("RecentFiles/Files", recentFiles);
}

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
        // get application's default font (pixel size is -1, point size e.g. 10pt):
        selectionColor = new RColor(getColor("GraphicsViewColors/SelectionColor", RColor(164,70,70,128)));
    }
    return *selectionColor;
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

bool RSettings::getColorCorrection() {
    return getValue("GraphicsView/ColorCorrection", true).toBool();
}

int RSettings::getColorThreshold() {
    return getValue("GraphicsView/ColorThreshold", 10).toInt();
}

int RSettings::getTextHeightThreshold() {
    return getValue("GraphicsView/TextHeightThreshold", 3).toInt();
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

int RSettings::getQtVersion() {
    return QT_VERSION;
}

QString RSettings::getQtVersionString() {
    return qVersion();
}

bool RSettings::isQt(int majorVersion) {
    return QT_VERSION >= majorVersion<<16;
}

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

QString RSettings::getOSVersion() {
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
        return "Mac OS X 10.3";
    case QSysInfo::MV_10_4:
        return "Mac OS X 10.4";
    case QSysInfo::MV_10_5:
        return "Mac OS X 10.5";
    case QSysInfo::MV_10_6:
        return "Mac OS X 10.6";
    case QSysInfo::MV_10_7:
        return "Mac OS X 10.7";
    case QSysInfo::MV_10_8:
        return "Mac OS X 10.8";
    // QSysInfo::MV_10_9:
    case 0x000B:
        return "Mac OS X 10.9";
    // QSysInfo::MV_10_10:
    case 0x000C:
        return "Mac OS X 10.10";
    // QSysInfo::MV_10_11:
    case 0x000D:
        return "Mac OS X 10.11";
    default:
    case QSysInfo::MV_Unknown:
        return "Mac OS X > 10.11";
    }
#else
    return "Unknown";
#endif
}

QString RSettings::getVersionString() {
    return R_QCAD_VERSION_STRING;
}

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
    }
    return snapRange;
}

int RSettings::getPickRange() {
    if (pickRange==-1) {
        pickRange = getValue("GraphicsView/PickRange", QVariant(10)).toInt();
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

QVariant RSettings::getValue(const QString& key, const QVariant& defaultValue) {
    if (!isInitialized()) {
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

bool RSettings::getBoolValue(const QString& key, bool defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toBool();
}

RColor RSettings::getColorValue(const QString& key, const RColor& defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    if (ret.canConvert<RColor>()) {
        return ret.value<RColor>();
    }
    else {
        return defaultValue;
    }
}

double RSettings::getDoubleValue(const QString& key, double defaultValue) {
    QVariant ret = getValue(key, defaultValue);

    // if the variant is a list or string list, return the first entry
    // used for example for stored RMathLineEdit values
    if (ret.type()==QVariant::List || ret.canConvert<QStringList>()) {
        if (ret.toList().count()>0) {
            ret = ret.toList().at(0);
        }
    }

    double d = ret.toDouble();
    if (RMath::isNaN(d)) {
        return defaultValue;
    }
    return d;
}

int RSettings::getIntValue(const QString& key, int defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toInt();
}

QString RSettings::getStringValue(const QString& key, const QString& defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toString();
}

QStringList RSettings::getStringListValue(const QString& key, const QStringList& defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toStringList();
}

void RSettings::setValue(const QString& key, const QVariant& value, bool overwrite) {
    if (!isInitialized()) {
        return;
    }

    if (!overwrite && hasValue(key)) {
        // value exists and will not be overwritten:
        return;
    }

    cache[key] = value;
    // TODO: fix:
    if (QString(value.typeName())=="QPrinter::PageSize") {
        getQSettings()->setValue(key, value.toInt());
    }
    else {
        getQSettings()->setValue(key, value);
    }
    //getQSettings()->sync();
}

void RSettings::removeValue(const QString& key) {
    if (!isInitialized()) {
        return;
    }

    cache.remove(key);
    getQSettings()->remove(key);
    //getQSettings()->sync();
}

bool RSettings::isInitialized() {
    return !qApp->organizationName().isEmpty();
}

void RSettings::setApplicationName(const QString& n) {
    applicationNameOverride = n;
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
    mouseThreshold = -1;
    cache.clear();
}

void RSettings::uninit() {
    if (qSettings!=NULL) {
        delete qSettings;
        qSettings = NULL;
    }
}
