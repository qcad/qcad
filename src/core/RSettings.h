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

#ifndef RSETTINGS_H
#define RSETTINGS_H

#include "core_global.h"

#include <QDir>
#include <QSettings>
#include <QFont>

#include "RColor.h"
#include "RBox.h"

// workaround for src2srcml bug:
#ifndef RDEFAULT_RCOLOR
#define RDEFAULT_RCOLOR RColor()
#endif

#ifndef RDEFAULT_RBOX
#define RDEFAULT_RBOX RBox()
#endif

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif

#ifndef RDEFAULT_QSTRING
#define RDEFAULT_QSTRING QString()
#endif

#ifndef RDEFAULT_QSTRINGLIST
#define RDEFAULT_QSTRINGLIST QStringList()
#endif

#ifndef RDEFAULT_QLISTINT
#define RDEFAULT_QLISTINT QList<int>()
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

    static QString getArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const QString& def = RDEFAULT_QSTRING);
    static QStringList getArguments(const QStringList& args, const QString& shortFlag, const QString& longFlag);
    static int getIntArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, int def);
    static QList<int> getIntListArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, QList<int> def = RDEFAULT_QLISTINT);
    static double getFloatArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, double def = RNANDOUBLE);
    static RColor getColorArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const RColor& def = RDEFAULT_RCOLOR);
    static RVector getVectorArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const RVector& def = RDEFAULT_RVECTOR);
    static RBox getBoxArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag, const RBox& def = RDEFAULT_RBOX);
    static bool testArgument(const QStringList& args, const QString& shortFlag, const QString& longFlag);

    static bool isDeployed();
    static QString getApplicationPath();
    static QStringList getPluginPaths();
    static QString getPluginPath();
    static QString getThemePath();

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
    static RColor getStartReferencePointColor();
    static RColor getEndReferencePointColor();
    static RColor getSecondaryReferencePointColor();
    static RColor getTertiaryReferencePointColor();

    static bool getHighResolutionGraphicsView();
    static bool getAutoScaleGrid();
    static bool getAutoScaleMetaGrid();
    static bool getAutoScalePatterns();
    static bool getAutoZoomOnLoad();
    static bool getColorCorrection();
    static bool getColorCorrectionDisableForPrinting();
    static int getColorThreshold();
    static double getFadingFactor();
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
    /**
     * \return True if this is the first start of the software or
     * the current version is a newer version than the one previously installed
     * while the current version is the same or newer than versionCheck.
     * This can be used to check for an update from a version older than the given
     * version to a version newer or equal to the given version.
     */
    static int isUpdated(int versionCheck=-1) {
        if (isNewVersion()) {
            return true;
        }
        if (versionCheck==-1) {
            if (getCurrentVersion()>getPreviousVersion()) {
                return true;
            }
        }
        if (getCurrentVersion()>=versionCheck && getPreviousVersion()<versionCheck) {
            return true;
        }
        return false;
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

    /**
     * \nonscriptable
     */
    static QChar getCharValue(const QString& key, const QChar& defaultValue);

    static void setValue(const QString& key, const QVariant& value, bool overwrite=true);
    static void removeValue(const QString& key);

    static void setApplicationNameOverride(const QString& n);
    static QString getApplicationNameOverride();
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
    static int getReferencePointSize();
    static int getReferencePointShape();
    static bool getPropertyEditorShowOnRequest();
    static QString getPolarCoordinateSeparator();
    static QString getCartesianCoordinateSeparator();
    static QString getRelativeCoordinatePrefix();

    static bool isDarkMode();
    static bool hasDarkGuiBackground();
    static bool hasCustomStyleSheet();

    static QStringList getPrinterNames();
    static QString getDefaultPrinterName();

    static void appendOpenGLMessage(const QString& msg);
    static QStringList getOpenGLMessages();

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
    static RColor* startReferencePointColor;
    static RColor* endReferencePointColor;
    static RColor* secondaryReferencePointColor;
    static RColor* tertiaryReferencePointColor;
    static int darkMode;
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
    static double fadingFactor;
    static double minArcAngleStep;
    static int dashThreshold;
    static int textRenderedAsText;
    static int layer0CompatibilityOn;
    static int selectBlockWithAttribute;
    static int hideAttributeWithBlock;
    static int importRecomputedDimBlocks;
    static int ignoreBlockReferencePoint;
    static int ignoreAllReferencePoints;
    static int referencePointSize;
    static int referencePointShape;
    static int propertyEditorShowOnRequest;
    static QString polarCoordinateSeparator;
    static QString cartesianCoordinateSeparator;
    static QString relativeCoordinatePrefix;

    static QStringList recentFiles;
    static QLocale* numberLocale;

    static QString applicationNameOverride;

    static QString launchPath;
    static QString themePath;

    static QSettings* qSettings;

    static QStringList originalArguments;

    static bool quitFlag;

    static bool xDataEnabled;
    static bool nextVersionEnabled;

    static bool firstStart;
    static bool newVersion;
    static int previousVersion;

    static QStringList openGLMessages;
};

Q_DECLARE_METATYPE(RSettings*)

#endif
