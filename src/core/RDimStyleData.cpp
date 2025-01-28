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
#include "RDimStyleData.h"
#include "RSettings.h"

QMap<RS::KnownVariable, QVariant> RDimStyleData::mapDefaults;
//QList<RDimStyleData::RDimXVar> RDimStyleData::propertyVariables;
QMap<RS::KnownVariable, RS::KnownVariableType> RDimStyleData::dimXTypes;

RDimStyleData::RDimStyleData(bool override) {
    if (!override) {
        initFromSettings();
    }
}

RDimStyleData::~RDimStyleData() {
}

void RDimStyleData::init() {

}

void RDimStyleData::initDefaults() {
    mapDefaults[RS::DIMSCALE] = 1.0;
    mapDefaults[RS::DIMLFAC] = 1.0;
    mapDefaults[RS::DIMTXT] = 2.5;
    mapDefaults[RS::DIMGAP] = 0.625;
    mapDefaults[RS::DIMASZ] = 2.5;
    mapDefaults[RS::DIMEXE] = 1.25;
    mapDefaults[RS::DIMEXO] = 0.625;
    mapDefaults[RS::DIMTAD] = 1;
    mapDefaults[RS::DIMTIH] = false;
    mapDefaults[RS::DIMDLI] = 5.0;
    QVariant v;
    v.setValue<RColor>(RColor(RColor::ByBlock));
    mapDefaults[RS::DIMCLRT] = v;
    mapDefaults[RS::DIMTSZ] = 0.0;
    mapDefaults[RS::DIMLUNIT] = RS::Decimal;
    mapDefaults[RS::DIMDEC] = 4;
    mapDefaults[RS::DIMDSEP] = '.';
    mapDefaults[RS::DIMZIN] = 8;
    mapDefaults[RS::DIMAUNIT] = RS::DegreesDecimal;
    mapDefaults[RS::DIMADEC] = 0;
    mapDefaults[RS::DIMAZIN] = 2;

    mapDefaults[RS::DIMBLK] = "";
}

QVariant RDimStyleData::getVariantDefault(RS::KnownVariable key) {
    if (mapDefaults.isEmpty()) {
        RDimStyleData::initDefaults();
    }
    if (mapDefaults.contains(key)) {
        return mapDefaults[key];
    }
    return QVariant();
}

double RDimStyleData::getDoubleDefault(RS::KnownVariable key) {
    if (mapDefaults.isEmpty()) {
        RDimStyleData::initDefaults();
    }
    if (mapDefaults.contains(key)) {
        return mapDefaults[key].toDouble();
    }
    return RNANDOUBLE;
}

int RDimStyleData::getIntDefault(RS::KnownVariable key) {
    if (mapDefaults.isEmpty()) {
        RDimStyleData::initDefaults();
    }
    if (mapDefaults.contains(key)) {
        return mapDefaults[key].toInt();
    }
    return RMININT;
}

bool RDimStyleData::getBoolDefault(RS::KnownVariable key) {
    if (mapDefaults.isEmpty()) {
        RDimStyleData::initDefaults();
    }
    if (mapDefaults.contains(key)) {
        return mapDefaults[key].toBool();
    }
    return false;
}

RColor RDimStyleData::getColorDefault(RS::KnownVariable key) {
    if (mapDefaults.isEmpty()) {
        RDimStyleData::initDefaults();
    }
    if (mapDefaults.contains(key)) {
        return mapDefaults[key].value<RColor>();
    }
    return RColor();
}

void RDimStyleData::initFromSettings() {
    // initialize defaults for dim style as part of a new document (as opposed to a dimension entity override):
    setDouble(RS::DIMSCALE, RSettings::getDoubleValue("DimensionSettings/DIMSCALE", getDoubleDefault(RS::DIMSCALE)));
    setDouble(RS::DIMTXT, RSettings::getDoubleValue("DimensionSettings/DIMTXT", getDoubleDefault(RS::DIMTXT)));
    setDouble(RS::DIMGAP, RSettings::getDoubleValue("DimensionSettings/DIMGAP", getDoubleDefault(RS::DIMGAP)));
    setDouble(RS::DIMASZ, RSettings::getDoubleValue("DimensionSettings/DIMASZ", getDoubleDefault(RS::DIMASZ)));
    setDouble(RS::DIMEXE, RSettings::getDoubleValue("DimensionSettings/DIMEXE", getDoubleDefault(RS::DIMEXE)));
    setDouble(RS::DIMEXO, RSettings::getDoubleValue("DimensionSettings/DIMEXO", getDoubleDefault(RS::DIMEXO)));

    // preference is stored in settings as true/false:
    setInt(RS::DIMTAD, (int)RSettings::getBoolValue("DimensionSettings/DIMTAD", getIntDefault(RS::DIMTAD)));
    setBool(RS::DIMTIH, RSettings::getBoolValue("DimensionSettings/DIMTIH", getBoolDefault(RS::DIMTIH)));

    setDouble(RS::DIMDLI, RSettings::getDoubleValue("DimensionSettings/DIMDLI", getDoubleDefault(RS::DIMDLI)));

    setColor(RS::DIMCLRT, RSettings::getColorValue("DimensionSettings/DimensionTextColor", getColorDefault(RS::DIMCLRT)));
    //qDebug() << "default dimclrt (def):" << getColorDefault(RS::DIMCLRT);
    //qDebug() << "default dimclrt (settings):" << RSettings::getColorValue("DimensionSettings/DimensionTextColor", getColorDefault(RS::DIMCLRT));
    //RDebug::printBacktrace();

    if (RSettings::getStringValue("DimensionSettings/ArrowStyle", "Arrow")=="Arrow") {
        // tick size is 0 for arrows:
        setDouble(RS::DIMTSZ, 0.0);
    }
    else {
        // arch tick head:
        setDouble(RS::DIMTSZ, RSettings::getDoubleValue("DimensionSettings/DIMASZ", getDoubleDefault(RS::DIMASZ)));
    }

    setInt(RS::DIMLUNIT, RSettings::getIntValue("DimensionSettings/LinearFormat", getIntDefault(RS::DIMLUNIT)));
    setInt(RS::DIMDEC, RSettings::getIntValue("DimensionSettings/LinearPrecision", getIntDefault(RS::DIMDEC)));
    setInt(RS::DIMDSEP, RSettings::getIntValue("DimensionSettings/DecimalPoint", getIntDefault(RS::DIMDSEP)));

    if (RSettings::getBoolValue("DimensionSettings/LinearShowTrailingZeros", false)) {
        // show trailing zeroes:
        setInt(RS::DIMZIN, 0);
    }
    else {
        // suppress trailing zeroes:
        setInt(RS::DIMZIN, 8);
    }

    setInt(RS::DIMAUNIT, RSettings::getIntValue("DimensionSettings/AngularFormat", getIntDefault(RS::DIMAUNIT)));
    setInt(RS::DIMADEC, RSettings::getIntValue("DimensionSettings/AngularPrecision", getIntDefault(RS::DIMADEC)));

    // show trailing zeroes:
    if (RSettings::getBoolValue("DimensionSettings/AngularShowTrailingZeros", false)) {
        setInt(RS::DIMAZIN, 0);
    }

    // suppress trailing zeroes:
    else {
        setInt(RS::DIMAZIN, 2);
    }

    // arrow head:
    if (RSettings::getStringValue("DimensionSettings/ArrowStyle", "Arrow")=="Arrow") {
        // tick size is 0 for arrows:
        setDouble(RS::DIMTSZ, 0.0);
    }

    // arch tick head:
    else {
        setDouble(RS::DIMTSZ, getDouble(RS::DIMASZ));
    }
}
