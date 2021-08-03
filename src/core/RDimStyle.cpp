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
#include "RDimStyle.h"
#include "RSettings.h"

RPropertyTypeId RDimStyle::PropertyCustom;
RPropertyTypeId RDimStyle::PropertyHandle;
RPropertyTypeId RDimStyle::PropertyProtected;

RPropertyTypeId RDimStyle::PropertyDimtxt;
RPropertyTypeId RDimStyle::PropertyDimgap;
RPropertyTypeId RDimStyle::PropertyDimtad;
RPropertyTypeId RDimStyle::PropertyDimtih;

RDimStyleProxy* RDimStyle::dimStyleProxy = NULL;

RDimStyle::RDimStyle() : RObject() {
}

RDimStyle::RDimStyle(RDocument* document)
    : RObject(document),
      dimtxt(0.0),
      dimgap(0.0),
      dimasz(0.0),
      dimexe(0.0),
      dimexo(0.0),
      dimtad(1),
      dimtih(0),
      archTick(false){

    dimtxt = RSettings::getDoubleValue("DimensionSettings/DIMTXT", 2.5);
    dimgap = RSettings::getDoubleValue("DimensionSettings/DIMGAP", 0.625);
    dimasz = RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5);
    dimexe = RSettings::getDoubleValue("DimensionSettings/DIMEXE", 1.25);
    dimexo = RSettings::getDoubleValue("DimensionSettings/DIMEXO", 0.625);

    dimtad = RSettings::getIntValue("DimensionSettings/DIMTAD", 1);
    dimtih = RSettings::getIntValue("DimensionSettings/DIMTIH", 0);

    //docVars->setKnownVariable(RS::DIMSCALE, RSettings::getDoubleValue("DimensionSettings/DIMSCALE", 1.0));
    //docVars->setKnownVariable(RS::DIMDLI, RSettings::getDoubleValue("DimensionSettings/DIMDLI", 5.0));
    //docVars->setKnownVariable(RS::DIMCLRT, RSettings::getColorValue("DimensionSettings/DimensionTextColor", RColor(RColor::ByBlock)));

    // arrow head:
    if (RSettings::getStringValue("DimensionSettings/ArrowStyle", "Arrow")=="Arrow") {
        // tick size is 0 for arrows:
        //docVars->setKnownVariable(RS::DIMTSZ, 0.0);
        archTick = false;
    }

    // arch tick head:
    else {
        //docVars->setKnownVariable(RS::DIMTSZ, RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5));
        archTick = true;
    }

    //docVars->setKnownVariable(RS::DIMLUNIT, RSettings::getIntValue("DimensionSettings/LinearFormat", RS::Decimal));
    //docVars->setKnownVariable(RS::DIMDEC, RSettings::getIntValue("DimensionSettings/LinearPrecision", 4));
    //docVars->setKnownVariable(RS::DIMDSEP, RSettings::getIntValue("DimensionSettings/DecimalPoint", '.'));

    // show trailing zeroes:
//    if (RSettings::getBoolValue("DimensionSettings/LinearShowTrailingZeros", false)) {
//        docVars->setKnownVariable(RS::DIMZIN, 0);
//    }

    // suppress trailing zeroes:
//    else {
//        docVars->setKnownVariable(RS::DIMZIN, 8);
//    }

//    docVars->setKnownVariable(RS::DIMAUNIT, RSettings::getIntValue("DimensionSettings/AngularFormat", RS::DegreesDecimal));
//    docVars->setKnownVariable(RS::DIMADEC, RSettings::getIntValue("DimensionSettings/AngularPrecision", 0));

    // show trailing zeroes:
//    if (RSettings::getBoolValue("DimensionSettings/AngularShowTrailingZeros", false)) {
//        docVars->setKnownVariable(RS::DIMAZIN, 0);
//    }

    // suppress trailing zeroes:
//    else {
//        docVars->setKnownVariable(RS::DIMAZIN, 2);
//    }
}

RDimStyle::~RDimStyle() {
}

void RDimStyle::init() {
    RDimStyle::PropertyCustom.generateId(typeid(RDimStyle), RObject::PropertyCustom);
    RDimStyle::PropertyHandle.generateId(typeid(RDimStyle), RObject::PropertyHandle);
    RDimStyle::PropertyProtected.generateId(typeid(RDimStyle), RObject::PropertyProtected);

    RDimStyle::PropertyDimtxt.generateId(typeid(RDimStyle), "", QT_TRANSLATE_NOOP("RDimStyle", "Text height"));
    RDimStyle::PropertyDimgap.generateId(typeid(RDimStyle), "", QT_TRANSLATE_NOOP("RDimStyle", "Dimension line gap"));
    RDimStyle::PropertyDimtad.generateId(typeid(RDimStyle), "", QT_TRANSLATE_NOOP("RDimStyle", "Text above dimension line"));
    RDimStyle::PropertyDimtih.generateId(typeid(RDimStyle), "", QT_TRANSLATE_NOOP("RDimStyle", "Text inside horizontal"));
}

void RDimStyle::clear() {
    dimtxt = 0.0;
}

QPair<QVariant, RPropertyAttributes> RDimStyle::getProperty(RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyDimtxt) {
        return qMakePair(QVariant(dimtxt), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyDimgap) {
        return qMakePair(QVariant(dimgap), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyDimtad) {
        return qMakePair(QVariant(dimtad), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyDimtih) {
        return qMakePair(QVariant(dimtih), RPropertyAttributes());
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

bool RDimStyle::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {

    bool ret = false;

    ret = ret || RObject::setMember(dimtxt, value, PropertyDimtxt == propertyTypeId);
    ret = ret || RObject::setMember(dimgap, value, PropertyDimgap == propertyTypeId);
    ret = ret || RObject::setMember(dimtad, value, PropertyDimtad == propertyTypeId);
    ret = ret || RObject::setMember(dimtih, value, PropertyDimtih == propertyTypeId);

    ret = ret || RObject::setProperty(propertyTypeId, value, transaction);

    return ret;
}
