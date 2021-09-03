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
#include "RDxfServices.h"
#include "RDocument.h"

RPropertyTypeId RDimStyle::PropertyCustom;
RPropertyTypeId RDimStyle::PropertyHandle;
RPropertyTypeId RDimStyle::PropertyProtected;

RPropertyTypeId RDimStyle::PropertyDimscale;
RPropertyTypeId RDimStyle::PropertyDimlfac;
RPropertyTypeId RDimStyle::PropertyDimtxt;
RPropertyTypeId RDimStyle::PropertyDimgap;
RPropertyTypeId RDimStyle::PropertyDimasz;
RPropertyTypeId RDimStyle::PropertyDimdli;
RPropertyTypeId RDimStyle::PropertyDimexe;
RPropertyTypeId RDimStyle::PropertyDimexo;
RPropertyTypeId RDimStyle::PropertyDimtad;
RPropertyTypeId RDimStyle::PropertyDimtih;
RPropertyTypeId RDimStyle::PropertyDimtsz;
RPropertyTypeId RDimStyle::PropertyDimlunit;
RPropertyTypeId RDimStyle::PropertyDimdec;
RPropertyTypeId RDimStyle::PropertyDimdsep;
RPropertyTypeId RDimStyle::PropertyDimzin;
RPropertyTypeId RDimStyle::PropertyDimaunit;
RPropertyTypeId RDimStyle::PropertyDimadec;
RPropertyTypeId RDimStyle::PropertyDimazin;
RPropertyTypeId RDimStyle::PropertyArchTick;
RPropertyTypeId RDimStyle::PropertyDimclrt;

QList<QPair<RPropertyTypeId, RS::KnownVariable> > RDimStyle::propertyVariables;

RDimStyleProxy* RDimStyle::dimStyleProxy = NULL;

RDimStyle::RDimStyle() : RObject(), RDimStyleData(false) {
}

RDimStyle::RDimStyle(RDocument* document)
    : RObject(document), RDimStyleData(false) {

//    dimscale = RSettings::getDoubleValue("DimensionSettings/DIMSCALE", 1.0);
//    dimtxt = RSettings::getDoubleValue("DimensionSettings/DIMTXT", 2.5);
//    dimgap = RSettings::getDoubleValue("DimensionSettings/DIMGAP", 0.625);
//    dimasz = RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5);
//    dimexe = RSettings::getDoubleValue("DimensionSettings/DIMEXE", 1.25);
//    dimexo = RSettings::getDoubleValue("DimensionSettings/DIMEXO", 0.625);

//    dimtad = RSettings::getIntValue("DimensionSettings/DIMTAD", 1);
//    dimtih = RSettings::getIntValue("DimensionSettings/DIMTIH", 0);

//    dimdli = RSettings::getDoubleValue("DimensionSettings/DIMDLI", 5.0);
//    dimclrt = RSettings::getColorValue("DimensionSettings/DimensionTextColor", RColor(RColor::ByBlock));

//    if (RSettings::getStringValue("DimensionSettings/ArrowStyle", "Arrow")=="Arrow") {
//        // tick size is 0 for arrows:
//        dimtsz = RSettings::getIntValue("DimensionSettings/DIMTIH", 0);
//    }
//    else {
//        // arch tick head:
//        dimtsz = RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5);
//    }

//    dimlunit = RSettings::getIntValue("DimensionSettings/LinearFormat", RS::Decimal);
//    dimdec = RSettings::getIntValue("DimensionSettings/LinearPrecision", 4);
//    dimdsep = RSettings::getIntValue("DimensionSettings/DecimalPoint", '.');

//    if (RSettings::getBoolValue("DimensionSettings/LinearShowTrailingZeros", false)) {
//        // show trailing zeroes:
//        dimzin = 0;
//    }
//    else {
//        // suppress trailing zeroes:
//        dimzin = 8;
//    }

//    dimaunit = RSettings::getIntValue("DimensionSettings/AngularFormat", RS::DegreesDecimal);
//    dimadec = RSettings::getIntValue("DimensionSettings/AngularPrecision", 0);

//    // show trailing zeroes:
//    if (RSettings::getBoolValue("DimensionSettings/AngularShowTrailingZeros", false)) {
//        dimazin = 0;
//    }

//    // suppress trailing zeroes:
//    else {
//        dimazin = 2;
//    }

    //docVars->setKnownVariable(RS::DIMSCALE, RSettings::getDoubleValue("DimensionSettings/DIMSCALE", 1.0));
    //docVars->setKnownVariable(RS::DIMDLI, RSettings::getDoubleValue("DimensionSettings/DIMDLI", 5.0));
    //docVars->setKnownVariable(RS::DIMCLRT, RSettings::getColorValue("DimensionSettings/DimensionTextColor", RColor(RColor::ByBlock)));

    // arrow head:
//    if (RSettings::getStringValue("DimensionSettings/ArrowStyle", "Arrow")=="Arrow") {
//        // tick size is 0 for arrows:
//        //docVars->setKnownVariable(RS::DIMTSZ, 0.0);
//        archTick = false;
//    }

//    // arch tick head:
//    else {
//        //docVars->setKnownVariable(RS::DIMTSZ, RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5));
//        archTick = true;
//    }

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

    QString tsStyle = QT_TRANSLATE_NOOP("REntity", "Style");
    RDimStyle::PropertyDimscale.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Overall dimension scale"));
    RDimStyle::PropertyDimlfac.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Linear measurement factor"));
    RDimStyle::PropertyDimtxt.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text height"));
    RDimStyle::PropertyDimgap.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Dimension line gap"));
    RDimStyle::PropertyDimasz.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Arrow size"));
    RDimStyle::PropertyDimdli.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Dimension line increment"));
    RDimStyle::PropertyDimexe.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Extension line extension"));
    RDimStyle::PropertyDimexo.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Extension line offset"));
    RDimStyle::PropertyDimtad.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text above dimension line"));
    RDimStyle::PropertyDimtih.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text inside horizontal"));
    RDimStyle::PropertyDimtsz.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Tick size"));
    RDimStyle::PropertyDimlunit.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Linear format"));
    RDimStyle::PropertyDimdec.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Decimal places"));
    RDimStyle::PropertyDimdsep.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Decimal separator"));
    RDimStyle::PropertyDimzin.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Zero suppression"));
    RDimStyle::PropertyDimaunit.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Angular format"));
    RDimStyle::PropertyDimadec.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Angular decimal places"));
    RDimStyle::PropertyDimazin.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Angular zero suppression"));
    RDimStyle::PropertyArchTick.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Architectur tick"));
    RDimStyle::PropertyDimclrt.generateId(typeid(RDimStyle), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text color"));

    RDimStyleData::init();

    initDimX(PropertyDimscale, RS::DIMSCALE, RS::VarTypeDouble);
    initDimX(PropertyDimlfac, RS::DIMLFAC, RS::VarTypeDouble);
    initDimX(PropertyDimtxt, RS::DIMTXT, RS::VarTypeDouble);
    initDimX(PropertyDimgap, RS::DIMGAP, RS::VarTypeDouble);
    initDimX(PropertyDimasz, RS::DIMASZ, RS::VarTypeDouble);
    initDimX(PropertyDimdli, RS::DIMDLI, RS::VarTypeDouble);
    initDimX(PropertyDimexe, RS::DIMEXE, RS::VarTypeDouble);
    initDimX(PropertyDimexo, RS::DIMEXO, RS::VarTypeDouble);
    initDimX(PropertyDimtad, RS::DIMTAD, RS::VarTypeInt);
    initDimX(PropertyDimtih, RS::DIMTIH, RS::VarTypeBool);
    initDimX(PropertyDimtsz, RS::DIMTSZ, RS::VarTypeDouble);
    initDimX(PropertyDimlunit, RS::DIMLUNIT, RS::VarTypeInt);
    initDimX(PropertyDimdec, RS::DIMDEC, RS::VarTypeInt);
    initDimX(PropertyDimdsep, RS::DIMDSEP, RS::VarTypeInt);
    initDimX(PropertyDimzin, RS::DIMZIN, RS::VarTypeInt);
    initDimX(PropertyDimaunit, RS::DIMAUNIT, RS::VarTypeInt);
    initDimX(PropertyDimadec, RS::DIMADEC, RS::VarTypeInt);
    initDimX(PropertyDimazin, RS::DIMAZIN, RS::VarTypeInt);
    initDimX(PropertyArchTick, RS::QCADARCHTICK, RS::VarTypeBool);
    initDimX(PropertyDimclrt, RS::DIMCLRT, RS::VarTypeColor);
}

void RDimStyle::initDimX(const RPropertyTypeId& propertyTypeId, RS::KnownVariable var, RS::KnownVariableType type) {
    propertyVariables.append(QPair<RPropertyTypeId, RS::KnownVariable>(propertyTypeId, var));
    RDimStyleData::dimXTypes[var] = type;
}

void RDimStyle::clear() {
    //dimtxt = 0.0;
    //*((RDimStyleData*)this) = RDimStyleData(false);
}

void RDimStyle::updateDocumentVariables() {
    RDocument* doc = getDocument();

    //doc->setKnownVariable(RS::DIMTXT, getVariant(RS::DIMTXT));

    for (int i=0; i<propertyVariables.length(); i++) {
        //RDimXVar p = propertyVariables[i];

//        if (p.var==RS::DIMCLRT) {
//            qDebug() << "update DIMCLRT to" << getVariant(p.var);
//        }

        doc->setKnownVariable(propertyVariables[i].second, getVariant(propertyVariables[i].second));
    }
}

//void RDimStyle::setDouble(RS::KnownVariable key, double val) {
//    RDimStyleData::setDouble(key, val);
//    //getDocument()->setKnownVariable(key, val);
//}

//void RDimStyle::setInt(RS::KnownVariable key, int val) {
//    RDimStyleData::setInt(key, val);
//    //getDocument()->setKnownVariable(key, val);
//}

//void RDimStyle::setColor(RS::KnownVariable key, const RColor& val) {
//    RDimStyleData::setColor(key, val);
//    //getDocument()->setKnownVariable(key, val);
//}

QPair<QVariant, RPropertyAttributes> RDimStyle::getProperty(RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    for (int i=0; i<propertyVariables.length(); i++) {
        //RDimXVar p = propertyVariables[i];

        if (propertyTypeId==propertyVariables[i].first) {
            return qMakePair(getVariant(propertyVariables[i].second), RPropertyAttributes());
        }
    }

//    if (propertyTypeId == PropertyDimscale) {
//        return qMakePair(getVariant(RS::DIMSCALE), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimlfac) {
//        return qMakePair(getVariant(RS::DIMLFAC), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimtxt) {
//        return qMakePair(getVariant(RS::DIMTXT), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimgap) {
//        return qMakePair(getVariant(RS::DIMGAP), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimasz) {
//        return qMakePair(getVariant(RS::DIMASZ), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimdli) {
//        return qMakePair(getVariant(RS::DIMDLI), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimexe) {
//        return qMakePair(getVariant(RS::DIMEXE), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimexo) {
//        return qMakePair(getVariant(RS::DIMEXO), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimtad) {
//        return qMakePair(getVariant(RS::DIMTAD), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimtih) {
//        return qMakePair(getVariant(RS::DIMTIH), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimtsz) {
//        return qMakePair(getVariant(RS::DIMTSZ), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimlunit) {
//        return qMakePair(getVariant(RS::DIMLUNIT), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimdec) {
//        return qMakePair(getVariant(RS::DIMDEC), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimdsep) {
//        return qMakePair(getVariant(RS::DIMDSEP), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimzin) {
//        return qMakePair(getVariant(RS::DIMZIN), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimaunit) {
//        return qMakePair(getVariant(RS::DIMAUNIT), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimadec) {
//        return qMakePair(getVariant(RS::DIMADEC), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimazin) {
//        return qMakePair(getVariant(RS::DIMAZIN), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyArchTick) {
//        return qMakePair(getVariant(RS::QCADARCHTICK), RPropertyAttributes());
//    }

//    if (propertyTypeId == PropertyDimclrt) {
//        return qMakePair(getVariant(RS::DIMCLRT), RPropertyAttributes());
//    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

bool RDimStyle::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {

    bool ret = false;

    for (int i=0; i<propertyVariables.length(); i++) {
        //RDimXVar p = propertyVariables[i];

        if (propertyTypeId==propertyVariables[i].first) {
            setVariant(propertyVariables[i].second, value);
            ret = true;
        }
    }

//    if (PropertyDimscale == propertyTypeId) {
//        setDouble(RS::DIMSCALE, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimscale, value, PropertyDimscale == propertyTypeId);
//    if (PropertyDimlfac == propertyTypeId) {
//        setDouble(RS::DIMLFAC, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimlfac, value, PropertyDimlfac == propertyTypeId);
//    if (PropertyDimtxt == propertyTypeId) {
//        setDouble(RS::DIMTXT, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimtxt, value, PropertyDimtxt == propertyTypeId);
//    if (PropertyDimgap == propertyTypeId) {
//        setDouble(RS::DIMGAP, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimgap, value, PropertyDimgap == propertyTypeId);
//    if (PropertyDimasz == propertyTypeId) {
//        setDouble(RS::DIMASZ, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimasz, value, PropertyDimasz == propertyTypeId);
//    if (PropertyDimdli == propertyTypeId) {
//        setDouble(RS::DIMDLI, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimdli, value, PropertyDimdli == propertyTypeId);
//    if (PropertyDimexe == propertyTypeId) {
//        setDouble(RS::DIMEXE, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimexe, value, PropertyDimexe == propertyTypeId);
//    if (PropertyDimexo == propertyTypeId) {
//        setDouble(RS::DIMEXO, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimexo, value, PropertyDimexo == propertyTypeId);
//    if (PropertyDimtad == propertyTypeId) {
//        setInt(RS::DIMTAD, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimtad, value, PropertyDimtad == propertyTypeId);
//    if (PropertyDimtih == propertyTypeId) {
//        setInt(RS::DIMTIH, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimtih, value, PropertyDimtih == propertyTypeId);
//    if (PropertyDimtsz == propertyTypeId) {
//        setDouble(RS::DIMTSZ, value.toDouble());
//    }
////    ret = ret || RObject::setMember(dimtsz, value, PropertyDimtsz == propertyTypeId);
//    if (PropertyDimlunit == propertyTypeId) {
//        setInt(RS::DIMLUNIT, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimlunit, value, PropertyDimlunit == propertyTypeId);
//    if (PropertyDimdec == propertyTypeId) {
//        setInt(RS::DIMDEC, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimdec, value, PropertyDimdec == propertyTypeId);
//    if (PropertyDimdsep == propertyTypeId) {
//        setInt(RS::DIMDSEP, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimdsep, value, PropertyDimdsep == propertyTypeId);
//    if (PropertyDimzin == propertyTypeId) {
//        setInt(RS::DIMZIN, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimzin, value, PropertyDimzin == propertyTypeId);
//    if (PropertyDimaunit == propertyTypeId) {
//        setInt(RS::DIMAUNIT, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimaunit, value, PropertyDimaunit == propertyTypeId);
//    if (PropertyDimadec == propertyTypeId) {
//        setInt(RS::DIMADEC, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimadec, value, PropertyDimadec == propertyTypeId);
//    if (PropertyDimazin == propertyTypeId) {
//        setInt(RS::DIMAZIN, value.toInt());
//    }
////    ret = ret || RObject::setMember(dimazin, value, PropertyDimazin == propertyTypeId);
//    if (PropertyArchTick == propertyTypeId) {
//        setInt(RS::QCADARCHTICK, value.toInt());
//    }
////    ret = ret || RObject::setMember(archTick, value, PropertyArchTick == propertyTypeId);
//    if (PropertyDimclrt == propertyTypeId) {
//        setColor(RS::DIMCLRT, value.value<RColor>());
//    }
//    ret = ret || RObject::setMember(dimclrt, value, PropertyDimclrt == propertyTypeId);

    ret = ret || RObject::setProperty(propertyTypeId, value, transaction);

    return ret;
}

QDebug operator<<(QDebug dbg, const RDimStyle& s) {
    dbg.nospace() << "RDimStyle(";
    for (int i=RS::ANGBASE; i<RS::MaxKnownVariable; i++) {
        dbg.nospace() << RDxfServices::variableToString((RS::KnownVariable)i) << ": " << s.getVariant((RS::KnownVariable)i).toString() << "\n";
    }
    dbg.nospace() << ")";

    return dbg;
}
