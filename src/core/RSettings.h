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

#ifndef RSETTINGS_H
#define RSETTINGS_H

#include "core_global.h"

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

#ifndef RDEFAULT_QSTRINGLIST
#define RDEFAULT_QSTRINGLIST QStringList()
#endif

/**
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RSettings {
public:
    static void uninit();
    static void setNoWrite(bool on = true);

    static QString getAppId();

    static double getDevicePixelRatio();

    static QString getLocale();
    static void loadTranslations(const QString& module, const QStringList& dirs = RDEFAULT_QSTRINGLIST);
    static QString translate(const QString& context, const QString& str);

    static QStringList getOriginalArguments();
    static void setOriginalArguments(const QStringList& a);

    static bool isDeployed();
    static QString getApplicationPath();
    static QStringList getPluginPaths();
    static QString getPluginPath();

    static QString getStandardLocation(int sl);
    static QString getCacheLocation();
    static QString getDataLocation();
    static QString getTempLocation();
    static QString getDesktopLocation();
    static QString getDocumentsLocation();
    static QString getHomeLocation();

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

    //static QString getDefaultStyle();

    // GraphicsView Appearance Fonts
    static void setRulerFont(const QFont& font);
    static QFont getRulerFont();
    static void setSnapLabelFont(const QFont& font);
    static QFont getSnapLabelFont();
    static QFont getInfoLabelFont();
    static QFont getStatusBarFont();

    static RColor getSelectionColor();
    static RColor getReferencePointColor();
    static RColor getSecondaryReferencePointColor();

    static bool getHighResolutionGraphicsView();
    static bool getAutoScaleGrid();
    static bool getAutoScaleMetaGrid();
    static bool getAutoScalePatterns();
    static bool getAutoZoomOnLoad();
    static bool getColorCorrection();
    static int getColorThreshold();
    static int getTextHeightThreshold();
    static double getArcAngleLengthThreshold();
    static double getMinArcAngleStep();
    static int getDashThreshold();
    static int getQtVersion();
    static QString getQtVersionString();
    static bool isQt(int majorVersion);
    static QString getCompilerVersion();
    static QString getOSVersion();
    static QString getReleaseDate();
    static QString getVersionString();
    static QString getNumericalVersionString();
    static int getMajorVersion();
    static int getMinorVersion();
    static int getRevisionVersion();
    static int getBuildVersion();
    static QString getRevisionString();
    static void setFirstStart(bool on) {
        firstStart = on;
    }
    static bool isFirstStart() {
        return firstStart;
    }
    static void setNewVersion(bool on) {
        newVersion = on;
    }
    static bool isNewVersion() {
        return newVersion;
    }
    static void setPreviousVersion(int pv) {
        previousVersion = pv;
    }
    /**
     * \return Current version as int in format 11223344 where
     * 11 is the major version, 22 the minor version, 33 the revision
     * and 44 the build version.
     */
    static int getCurrentVersion() {
        return getMajorVersion()*1000000 +
               getMinorVersion()*10000 +
               getRevisionVersion()*100 +
               getBuildVersion();
    }
    static int getPreviousVersion() {
        return previousVersion;
    }

    static int getSnapRange();
    static int getPickRange();
    static int getZeroWeightWeight();
    static int getPreviewEntities();
    static bool getLimitZoomAndScroll();
    static bool getShowCrosshair();
    static void setShowCrosshair(bool on);
    static bool getShowLargeCrosshair();
    static void setShowLargeCrosshair(bool on);
    static bool getShowLargeOriginAxis();
    static void setShowLargeOriginAxis(bool on);
    static bool getConcurrentDrawing();
    static void setConcurrentDrawing(bool on);
    static QLocale getNumberLocale();

    static void initRecentFiles();
    static void addRecentFile(const QString& fileName);
    static void removeRecentFile(const QString& fileName);
    static QStringList getRecentFiles();
    static void clearRecentFiles();

    static RColor getColor(const QString& key, const RColor& defaultValue=RDEFAULT_RCOLOR);

    static bool hasValue(const QString& key);
    static QVariant getValue(const QString& key, const QVariant& defaultValue=RDEFAULT_QVARIANT);
    static RColor getColorValue(const QString& key, const RColor& defaultValue);
    static bool getBoolValue(const QString& key, bool defaultValue);
    static double getDoubleValue(const QString& key, double defaultValue);
    static int getIntValue(const QString& key, int defaultValue);
    static QString getStringValue(const QString& key, const QString& defaultValue);
    static QStringList getStringListValue(const QString& key, const QStringList& defaultValue);

    static void setValue(const QString& key, const QVariant& value, bool overwrite=true);
    static void removeValue(const QString& key);

    static void setApplicationNameOverride(const QString& n);
    static bool hasApplicationNameOverride();

    static QStringList getAllKeys(const QString& group);

    static QSettings* getQSettings();

    static void resetCache();

    static void setXDataEnabled(bool on);
    static bool isXDataEnabled();

    static void setNextVersionEnabled(bool on);
    static bool isNextVersionEnabled();

    static bool getAutoScaleLinetypePatterns();
    static bool getUseSecondarySelectionColor();
    static bool getUseSolidLineSelection();

    static int getMouseThreshold();
    static bool getPositionByMousePress();
    static bool getAllowMouseMoveInterruptions();

    static bool isTextRenderedAsText();
    static bool isLayer0CompatibilityOn();
    static bool getSelectBlockWithAttribute();
    static bool getHideAttributeWithBlock();
    static bool getImportRecomputedDimBlocks();
    static bool getIgnoreBlockReferencePoint();
    static bool getIgnoreAllReferencePoints();

    static bool hasDarkGuiBackground();
    static bool hasCustomStyleSheet();

    static QStringList getPrinterNames();
    static QString getDefaultPrinterName();

private:
    static bool isInitialized();
    static void shortenRecentFiles();

private:
    static bool noWrite;
    // cache for faster access:
    static QVariantMap cache;

    // variables for very fast access:
    static QFont* rulerFont;
    static QFont* snapLabelFont;
    static QFont* infoLabelFont;
    static QFont* statusBarFont;
    static RColor* selectionColor;
    static RColor* referencePointColor;
    static RColor* secondaryReferencePointColor;
    static int darkGuiBackground;
    static int snapRange;
    static int pickRange;
    static int zeroWeightWeight;
    static int showCrosshair;
    static int showLargeCrosshair;
    static int showLargeOriginAxis;
    static int concurrentDrawing;
    static int highResolutionGraphicsView;
    static int previewEntities;
    static int limitZoomAndScroll;
    static int autoScaleLinetypePattern;
    static int useSolidLineSelection;
    static int useSecondarySelectionColor;
    static int mouseThreshold;
    static int positionByMousePress;
    static int allowMouseMoveInterruptions;
    static double arcAngleLengthThreshold;
    static double minArcAngleStep;
    static int dashThreshold;
    static int textRenderedAsText;
    static int layer0CompatibilityOn;
    static int selectBlockWithAttribute;
    static int hideAttributeWithBlock;
    static int importRecomputedDimBlocks;
    static int ignoreBlockReferencePoint;
    static int ignoreAllReferencePoints;
    static QStringList recentFiles;
    static QLocale* numberLocale;

    static QString applicationNameOverride;

    static QString launchPath;

    static QSettings* qSettings;

    static QStringList originalArguments;

    static bool quitFlag;

    static bool xDataEnabled;
    static bool nextVersionEnabled;

    static bool firstStart;
    static bool newVersion;
    static int previousVersion;
};

Q_DECLARE_METATYPE(RSettings*)

#endif
