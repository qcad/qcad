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
#include <QtDebug>
#include <QApplication>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFontMetrics>
#include <QStringList>

#include "RDebug.h"
#include "RMath.h"
#include "RSettings.h"
#include "RVersion.h"

QMap<QString, QVariant> RSettings::cache;

QString RSettings::launchPath;

QFont* RSettings::rulerFont = NULL;
QFont* RSettings::snapLabelFont = NULL;
QFont* RSettings::infoLabelFont = NULL;
QFont* RSettings::statusBarFont = NULL;
int RSettings::snapRange = -1;
int RSettings::showCrosshair = -1;
int RSettings::showLargeCrosshair = -1;
int RSettings::concurrentDrawing = -1;
int RSettings::previewEntities = -1;
int RSettings::enableXData = -1;
QStringList RSettings::recentFiles;
QLocale* RSettings::numberLocale = NULL;
QString RSettings::applicationNameOverride;
QSettings* RSettings::qSettings = NULL;

QStringList RSettings::originalArguments;

bool RSettings::quitFlag = false;

QStringList RSettings::getOriginalArguments() {
    return originalArguments;
}

void RSettings::setOriginalArguments(const QStringList& a) {
    originalArguments = a;
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
        font.setPointSize(9);
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

QString RSettings::getQtVersion() {
    return qVersion();
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

QString RSettings::getReleaseDate() {
    return __DATE__;
}

int RSettings::getSnapRange() {
    if (snapRange==-1) {
        snapRange = getValue("GraphicsView/SnapRange", QVariant(10)).toInt();
    }
    return snapRange;
}

int RSettings::getPreviewEntities() {
    if (previewEntities==-1) {
        previewEntities = getValue("GraphicsView/PreviewEntities", QVariant(50)).toInt();
    }
    return previewEntities;
}

bool RSettings::getShowCrosshair() {
    if (showCrosshair==-1) {
        showCrosshair = getValue("GraphicsView/ShowCrosshair", 
            QVariant(true)).toBool();
    }
    return (bool)showCrosshair;
}

void RSettings::setShowCrosshair(bool on) {
    setValue("GraphicsView/ShowCrosshair", on);
    showCrosshair = on;
}

bool RSettings::getShowLargeCrosshair() {
    if (showLargeCrosshair==-1) {
        showLargeCrosshair = getValue("GraphicsView/ShowLargeCrosshair",
                                 QVariant(true)).toBool();
    }
    return (bool)showLargeCrosshair;
}

void RSettings::setShowLargeCrosshair(bool on) {
    setValue("GraphicsView/ShowLargeCrosshair", on);
    showLargeCrosshair = on;
}

bool RSettings::getConcurrentDrawing() {
    if (concurrentDrawing==-1) {
        concurrentDrawing = getValue("GraphicsView/ConcurrentDrawing", 
            QVariant(false)).toBool();
    }
    return (bool)concurrentDrawing;
}

void RSettings::setConcurrentDrawing(bool on) {
    setValue("GraphicsView/ConcurrentDrawing", on);
    concurrentDrawing = on;
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

QVariant RSettings::getValue(const QString& key, const QVariant& defaultValue) {
    if (!isInitialized()) {
        return defaultValue;
    }
    if (cache.contains(key)) {
        return cache[key];
    }

    // slow operation:
    QVariant ret = getQSettings()->value(key, defaultValue);
    //if (defaultValue.isValid()) {
        //ret.convert(defaultValue.type());
    //}
    cache[key] = ret;
    return ret;
}

bool RSettings::getBoolValue(const QString& key, bool defaultValue) {
    QVariant ret = getValue(key, defaultValue);
    return ret.toBool();
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

void RSettings::setValue(const QString& key, const QVariant& value) {
    if (!isInitialized()) {
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

bool RSettings::isXDataEnabled() {
    if (enableXData==-1) {
        QStringList args = QCoreApplication::arguments();
        enableXData = (bool)args.contains("-enable-xdata");
    }
    return (bool)enableXData;
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
    showCrosshair = -1;
    showLargeCrosshair = -1;
    concurrentDrawing = -1;
    previewEntities = -1;
    cache.clear();
}

void RSettings::uninit() {
    if (qSettings!=NULL) {
        delete qSettings;
        qSettings = NULL;
    }
}
