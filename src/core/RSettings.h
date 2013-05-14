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

#ifndef RSETTINGS_H
#define RSETTINGS_H

#include "core_global.h"

#include <QColor>
#include <QDir>
#include <QSettings>
#include <QFont>

#include "RColor.h"

// workaround for src2srcml bug:
#ifndef RDEFAULT_RCOLOR
#define RDEFAULT_RCOLOR RColor()
#endif

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif

/**
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RSettings {
public:
    static void uninit();

    static QString getLocale();
    static void loadTranslations(const QString& module, const QStringList& dirs = QStringList());

    static QStringList getOriginalArguments();
    static void setOriginalArguments(const QStringList& a);

    static bool isDeployed();
    static QString getApplicationPath();
    static QString getPluginPath();

    //static void setEventBlocking(bool on);
    //static bool isEventBlockingEnabled();
    static bool isGuiEnabled();
    static bool isDebuggerEnabled();
    static bool hasQuitFlag();
    static void setQuitFlag();

    static QString getFileName();
    static QString getPath();
    static QString getLaunchPath();
    static void setLaunchPath(const QString& launchPath);

    static QString getDefaultStyle();

    // GraphicsView Appearance Fonts
    static void setRulerFont(const QFont& font);
    static QFont getRulerFont();
    static void setSnapLabelFont(const QFont& font);
    static QFont getSnapLabelFont();
    static QFont getInfoLabelFont();
    static QFont getStatusBarFont();

    static bool getAutoScalePatterns();
    static bool getColorCorrection();
    static int getColorThreshold();
    static int getTextHeightThreshold();
    static QString getQtVersion();
    static QString getReleaseDate();
    static QString getVersionString();
    static QString getNumericalVersionString();
    static int getMajorVersion();
    static int getMinorVersion();
    static int getRevisionVersion();
    static int getBuildVersion();
    static int getSnapRange();
    static int getPreviewEntities();
    static bool getShowCrosshair();
    static void setShowCrosshair(bool on);
    static bool getShowLargeCrosshair();
    static void setShowLargeCrosshair(bool on);
    static bool getConcurrentDrawing();
    static void setConcurrentDrawing(bool on);
    static QLocale getNumberLocale();

    static void initRecentFiles();
    static void addRecentFile(const QString& fileName);
    static void removeRecentFile(const QString& fileName);
    static QStringList getRecentFiles();
    static void clearRecentFiles();

    static RColor getColor(const QString& key, const RColor& defaultValue=RDEFAULT_RCOLOR);

    static QVariant getValue(const QString& key, const QVariant& defaultValue=RDEFAULT_QVARIANT);
    static bool getBoolValue(const QString& key, bool defaultValue);
    static double getDoubleValue(const QString& key, double defaultValue);
    static int getIntValue(const QString& key, int defaultValue);
    static QString getStringValue(const QString& key, const QString& defaultValue);

    static void setValue(const QString& key, const QVariant& value);
    static void removeValue(const QString& key);

    static void setApplicationName(const QString& n);

    static QStringList getAllKeys(const QString& group);

    static QSettings* getQSettings();

    static void resetCache();

    static bool isXDataEnabled();

private:
    static bool isInitialized();
    static void shortenRecentFiles();

private:
    // cache for faster access:
    static QMap<QString, QVariant> cache;

    // variables for very fast access:
    static QFont* rulerFont;
    static QFont* snapLabelFont;
    static QFont* infoLabelFont;
    static QFont* statusBarFont;
    static int snapRange;
    static int showCrosshair;
    static int showLargeCrosshair;
    static int concurrentDrawing;
    static int previewEntities;
    static QStringList recentFiles;
    static QLocale* numberLocale;

    static QString applicationNameOverride;

    static QString launchPath;

    static QSettings* qSettings;

    static QStringList originalArguments;

    static int enableXData;

    static bool quitFlag;
};

Q_DECLARE_METATYPE(RSettings*)

#endif
