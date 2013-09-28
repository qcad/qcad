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

#ifndef RDXFSERVICES_H
#define RDXFSERVICES_H

#include <QString>

#include "dxf_global.h"

#include "RS.h"
#include "RColor.h"
#include "RLineweight.h"

/**
 * \brief DXF support tools, mainly for QCAD 2 DXF imports.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RDxfServices {
public:
    RDxfServices();

    void reset();

    void fixBlockName(QString& blockName);
    void fixLayerName(QString& layerName);
    QString fixFontName(const QString& fontName) const;

    void fixQCad2String(QString& str) const;
    void fixDimensionLabel(QString& text, QString& uTol, QString& lTol);
    void detectQCad2Format(const QString& fileName);

    bool hasDIMZIN() const {
        return qcad2GotDIMZIN;
    }
    bool hasDIMAZIN() const {
        return qcad2GotDIMAZIN;
    }
    bool hasInvalidEllipse() const {
        return qcad2GotInvalidEllipse;
    }
    bool getQCad2Compatibility() const {
        return qcad2Compatibility;
    }
    bool getQCad3Compatibility() const {
        return qcad3Compatibility;
    }

    QString getQCad2LayerName(const QString& layerName) const;
    QString getQCad2BlockName(const QString& blockName) const;
    QString getQCad2Font(const QString& handle) const;
    QString getQCad2DimensionLabel(const QString& handle) const;

    QString collectQCad2Info(const QString& fileName);

    double getQCad2PatternAngle(double angle, const QString& patternName) const;
    double getQCad2PatternScale(double scale, const QString& patternName) const;
    QString getQCad2PatternName(const QString& patternName) const;

    void fixQCad2HatchData(QString& patternName, double& angle, double& scale, bool solid) const;

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
    static bool isVariable2D(RS::KnownVariable v);

private:
    bool qcad2GotDIMZIN;
    bool qcad2GotDIMAZIN;
    bool qcad2GotInvalidEllipse;
    bool qcad2Compatibility;
    bool qcad3Compatibility;

    QMap<QString, QString> qcad2BlockMapping;
    QMap<QString, QString> qcad2LayerMapping;
    QMap<QString, QString> qcad2TextFonts;
    QMap<QString, QString> qcad2DimensionLabels;

    QTextCodec* codec;
};

Q_DECLARE_METATYPE(RDxfServices)
Q_DECLARE_METATYPE(RDxfServices*)

#endif
