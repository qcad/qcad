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

#include "RS.h"
#include "RColor.h"
#include "RPropertyTypeId.h"
//#include "RDocument.h"

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

    static RS::KnownVariableType getType(RS::KnownVariable key) {
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
            qDebug() << "set bool:" << val.toBool();
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

//    double getDimscale() const {
//        if (mapDouble.contains(RS::DIMSCALE)) {
//            return mapDouble[RS::DIMSCALE];
//        }
//        return dimscale;
//    }

//    void setDimscale(double v) {
//        dimscale = v;
//    }

//    double getDimlfac() const {
//        return dimlfac;
//    }

//    void setDimlfac(double v) {
//        dimlfac = v;
//    }

//    double getDimtxt() const {
//        return dimtxt;
//    }

//    void setDimtxt(double v) {
//        dimtxt = v;
//    }

//    double getDimgap() const {
//        return dimgap;
//    }

//    void setDimgap(double v) {
//        dimgap = v;
//    }

//    double getDimasz() const {
//        return dimasz;
//    }

//    void setDimasz(double v) {
//        dimasz = v;
//    }

//    double getDimdli() const {
//        return dimdli;
//    }

//    void setDimdli(double v) {
//        dimdli = v;
//    }

//    double getDimexe() const {
//        return dimexe;
//    }

//    void setDimexe(double v) {
//        dimexe = v;
//    }

//    double getDimexo() const {
//        return dimexo;
//    }

//    void setDimexo(double v) {
//        dimexo = v;
//    }

//    int getDimtad() const {
//        return dimtad;
//    }

//    void setDimtad(int v) {
//        dimtad = v;
//    }

//    int getDimtih() const {
//        return dimtih;
//    }

//    void setDimtih(int v) {
//        dimtih = v;
//    }

//    double getDimtsz() const {
//        return dimtsz;
//    }

//    void setDimtsz(double v) {
//        dimtsz = v;
//    }

//    int getDimlunit() const {
//        return dimlunit;
//    }

//    void setDimlunit(int v) {
//        dimlunit = v;
//    }

//    int getDimdec() const {
//        return dimdec;
//    }

//    void setDimdec(int v) {
//        dimdec = v;
//    }

//    int getDimdsep() const {
//        return dimdsep;
//    }
//    void setDimdsep(int v) {
//        dimdsep = v;
//    }
//    int getDimzin() const {
//        return dimzin;
//    }
//    void setDimzin(int v) {
//        dimzin = v;
//    }
//    int getDimaunit() const {
//        return dimaunit;
//    }
//    void setDimaunit(int v) {
//        dimaunit = v;
//    }
//    int getDimadec() const {
//        return dimadec;
//    }
//    void setDimadec(int v) {
//        dimadec = v;
//    }
//    int getDimazin() const {
//        return dimazin;
//    }
//    void setDimazin(int v) {
//        dimazin = v;
//    }

//    bool useArchTick() const {
//        return archTick;
//    }

//    void setArchTick(bool on) {
//        archTick = on;
//    }

//    RColor getDimclrt() const {
//        return dimclrt;
//    }
//    void setDimclrt(const RColor& v) {
//        dimclrt = v;
//    }

//    template<class T>
//    T getDimX(RS::KnownVariable var) {
//        switch (var) {
//        case RS::DIMEXO:
//            return dimexo * dimscale;

//        default:
//            qWarning() << "unhandled dimesion variable:" << var;
//            break;
//        }
//    }

public:
//    struct RDimXVar {
//        RDimXVar() : propertyTypeId(), var(RS::INVALID), type(RS::VarInt) {}

//        RDimXVar(RPropertyTypeId propertyTypeId, RS::KnownVariable var, RS::KnownVariableType type) :
//            propertyTypeId(propertyTypeId),
//            var(var),
//            type(type) {

//            dimXTypes[var] = type;
//        }

//        RPropertyTypeId propertyTypeId;
//        RS::KnownVariable var;
//        RS::KnownVariableType type;
//    };
    //static QList<RDimXVar> propertyVariables;
    static QMap<RS::KnownVariable, RS::KnownVariableType> dimXTypes;

protected:
    QMap<RS::KnownVariable, double> mapDouble;
    QMap<RS::KnownVariable, int> mapInt;
    QMap<RS::KnownVariable, bool> mapBool;
    QMap<RS::KnownVariable, RColor> mapColor;

    static QMap<RS::KnownVariable, QVariant> mapDefaults;

//    double dimscale;
//    double dimlfac;
//    double dimtxt;
//    double dimgap;
//    double dimasz;
//    double dimdli;
//    double dimexe;
//    double dimexo;
//    int dimtad;
//    int dimtih;
//    double dimtsz;
//    int dimlunit;
//    int dimdec;
//    int dimdsep;
//    int dimzin;
//    int dimaunit;
//    int dimadec;
//    int dimazin;
//    bool archTick;
//    RColor dimclrt;

    // TODO:
    // Dimension text movement rules
    //int dimtmove;
};

Q_DECLARE_METATYPE(RDimStyleData)
Q_DECLARE_METATYPE(RDimStyleData*)

#endif
