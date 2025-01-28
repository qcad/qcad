/**
 * Copyright (c) 2011-2021 by Andrew Mustun. All rights reserved.
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

#ifndef RDIMSTYLEDATA_H
#define RDIMSTYLEDATA_H

#include "core_global.h"

#include "RSEnums.h"
#include "RColor.h"

#include <QVariant>

/**
 * Dimension style data class.
 *
 * \ingroup entity
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RDimStyleData {

public:
    RDimStyleData(bool override = false);
    virtual ~RDimStyleData();

    static void init();
    static void initDefaults();
    static QVariant getVariantDefault(RS::KnownVariable key);
    static double getDoubleDefault(RS::KnownVariable key);
    static int getIntDefault(RS::KnownVariable key);
    static bool getBoolDefault(RS::KnownVariable key);
    static RColor getColorDefault(RS::KnownVariable key);

    void initFromSettings();

    bool hasOverride(RS::KnownVariable key) const {
        return mapBool.contains(key) || mapDouble.contains(key) || mapInt.contains(key) || mapColor.contains(key);
    }

    bool isValid() const {
        return !mapBool.isEmpty() || !mapDouble.isEmpty() || !mapInt.isEmpty() || !mapColor.isEmpty();
    }

    void clear() {
        mapBool.clear();
        mapInt.clear();
        mapDouble.clear();
        mapColor.clear();
    }

    static RS::KnownVariableType getVariableType(RS::KnownVariable key) {
        if (dimXTypes.contains(key)) {
            return dimXTypes[key];
        }
        else {
            return RS::VarTypeUnknown;
        }
    }

    QVariant getVariant(RS::KnownVariable key) const {
        if (mapDouble.contains(key)) {
            return mapDouble[key];
        }
        else if (mapInt.contains(key)) {
            return mapInt[key];
        }
        else if (mapBool.contains(key)) {
            return mapBool[key];
        }
        else if (mapColor.contains(key)) {
            QVariant v;
            v.setValue<RColor>(mapColor[key]);
            return v;
        }
        else {
            return getVariantDefault(key);
        }
    }

    void setVariant(RS::KnownVariable key, const QVariant& val) {
        if (!dimXTypes.contains(key)) {
            qWarning() << "unregistered dim x type:" << key;
            return;
        }

        RS::KnownVariableType type = dimXTypes[key];
        switch (type) {
        case RS::VarTypeDouble:
            setDouble(key, val.toDouble());
            break;

        case RS::VarTypeInt:
            setInt(key, val.toInt());
            break;

        case RS::VarTypeBool:
            setBool(key, val.toBool());
            break;

        case RS::VarTypeColor:
            {
                RColor col = val.value<RColor>();
                setColor(key, col);
            }
            break;

        default:
            qWarning() << "unknown type:" << type;
            break;
        }
    }

    double getDouble(RS::KnownVariable key) const {
        if (mapDouble.contains(key)) {
            return mapDouble[key];
        }
        else {
            return getDoubleDefault(key);
        }
    }

    virtual void setDouble(RS::KnownVariable key, double val) {
        mapDouble[key] = val;
    }

    void removeDouble(RS::KnownVariable key) {
        mapDouble.remove(key);
    }

    int getInt(RS::KnownVariable key) const {
        if (mapInt.contains(key)) {
            return mapInt[key];
        }
        else {
            return getIntDefault(key);
        }
    }

    virtual void setInt(RS::KnownVariable key, int val) {
        mapInt[key] = val;
    }

    void removeInt(RS::KnownVariable key) {
        mapInt.remove(key);
    }

    bool getBool(RS::KnownVariable key) const {
        if (mapBool.contains(key)) {
            return mapBool[key];
        }
        else {
            return getBoolDefault(key);
        }
    }

    virtual void setBool(RS::KnownVariable key, bool val) {
        mapBool[key] = val;
    }

    void removeBool(RS::KnownVariable key) {
        mapBool.remove(key);
    }

    RColor getColor(RS::KnownVariable key) const {
        if (mapColor.contains(key)) {
            return mapColor[key];
        }
        else {
            return getColorDefault(key);
        }
    }

    virtual void setColor(RS::KnownVariable key, const RColor& val) {
        mapColor[key] = val;
    }

    void removeColor(RS::KnownVariable key) {
        mapColor.remove(key);
    }

public:
    static QMap<RS::KnownVariable, RS::KnownVariableType> dimXTypes;

    friend QDebug operator<<(QDebug dbg, const RDimStyleData& d) {
        dbg.nospace() << "RDimSyleData(";
        dbg.nospace() << d.mapBool;
        dbg.nospace() << d.mapInt;
        dbg.nospace() << d.mapDouble;
        dbg.nospace() << d.mapColor;
        dbg.nospace() << ")";
        return dbg;
    }

protected:
    QMap<RS::KnownVariable, double> mapDouble;
    QMap<RS::KnownVariable, int> mapInt;
    QMap<RS::KnownVariable, bool> mapBool;
    QMap<RS::KnownVariable, RColor> mapColor;

    static QMap<RS::KnownVariable, QVariant> mapDefaults;
};

Q_DECLARE_METATYPE(RDimStyleData)
Q_DECLARE_METATYPE(RDimStyleData*)
typedef QMap<RS::KnownVariable, RS::KnownVariableType> _QMapRSKnownVariableRSKnownVariableType;
Q_DECLARE_METATYPE(_QMapRSKnownVariableRSKnownVariableType)

#endif
