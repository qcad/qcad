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

#ifndef RDXFSERVICES_H
#define RDXFSERVICES_H

#include <QString>

#include "dxf_global.h"

#include "RS.h"
#include "RColor.h"
#include "RLineweight.h"
#include "RLinetypePattern.h"

/**
 * \brief DXF support tools, mainly for QCAD 2 DXF imports.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RDxfServices {
public:
    enum Type {
        Unknown,
        String,
        Int,
        Float,
        Vector
    };

public:
    RDxfServices();

    void reset();

    static QString getSafeBlockName(QString& blockName);

    void fixBlockName(QString& blockName);
    void fixLayerName(QString& layerName);
    QString fixFontName(const QString& fontName) const;

    void fixVersion2String(QString& str) const;
    void fixDimensionLabel(QString& text, QString& uTol, QString& lTol) const;
    void detectVersion2Format(const QString& fileName);

    bool hasDIMZIN() const {
        return version2GotDIMZIN;
    }
    bool hasDIMAZIN() const {
        return version2GotDIMAZIN;
    }
    bool hasInvalidEllipse() const {
        return version2GotInvalidEllipse;
    }
    bool getVersion2Compatibility() const {
        return dxflibMajorVersion==2;
    }
    bool getVersion3_1Compatibility() const {
        return (dxflibMajorVersion==3 && dxflibMinorVersion==0) ||
               (dxflibMajorVersion==3 && dxflibMinorVersion==1 && dxflibPatchVersion==0);
    }
    int getMajorVersion() const {
        return dxflibMajorVersion;
    }
    int getMinorVersion() const {
        return dxflibMinorVersion;
    }
    int getPatchVersion() const {
        return dxflibPatchVersion;
    }

    QString getVersion2LayerName(const QString& layerName) const;
    QString getVersionBlockName(const QString& blockName) const;
    QString getVersion2Font(const QString& handle) const;
    QString getVersion2DimensionLabel(const QString& handle) const;

    QString collectVersion2Info(const QString& fileName);

    double getVersion2PatternAngle(double angle, const QString& patternName) const;
    double getVersion2PatternScale(double scale, const QString& patternName) const;
    QString getVersion2PatternName(const QString& patternName) const;

    void fixVersion2HatchData(QString& patternName, double& angle, double& scale, bool solid) const;

    QTextCodec* getCodec() const {
        return codec;
    }

    void setCodec(QTextCodec* codec) {
        this->codec = codec;
    }

    /**
     * \nonscriptable
     */
    static RColor attributesToColor(int color, int color24, const double dxfColors[][3], bool forLayer=false);
    /**
     * \nonscriptable
     */
    static RColor numberToColor(int num, const double dxfColors[][3], bool comp=false, bool forLayer=false);
    static RColor numberToColor24(int num);
    static RLineweight::Lineweight numberToWeight(int num);

    static int widthToNumber(RLineweight::Lineweight w);
    static int colorToNumber24(const RColor& col);
    /**
     * \nonscriptable
     */
    static int colorToNumber(const RColor& col, const double dxfColors[][3]);

    static RS::KnownVariable stringToVariable(const QString& s);
    static QString variableToString(RS::KnownVariable v);
    static int getCodeForVariable(RS::KnownVariable v);
    static RDxfServices::Type getTypeForVariable(RS::KnownVariable v);
    static bool isVariable2D(RS::KnownVariable v);

    static QString escapeUnicode(const QString& str);
    static QString parseUnicode(const QString& str);

    static void autoFixLinetypePattern(RLinetypePattern& pattern);

private:
    bool version2GotDIMZIN;
    bool version2GotDIMAZIN;
    bool version2GotInvalidEllipse;
    int dxflibMajorVersion;
    int dxflibMinorVersion;
    int dxflibPatchVersion;

    QMap<QString, QString> version2BlockMapping;
    QMap<QString, QString> version2LayerMapping;
    QMap<QString, QString> version2TextFonts;
    QMap<QString, QString> version2DimensionLabels;

    QTextCodec* codec;
};

Q_DECLARE_METATYPE(RDxfServices::Type)
Q_DECLARE_METATYPE(RDxfServices)
Q_DECLARE_METATYPE(RDxfServices*)

#endif
