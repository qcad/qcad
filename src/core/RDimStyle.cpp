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
RPropertyTypeId RDimStyle::PropertyDimblk;
RPropertyTypeId RDimStyle::PropertyDimblk1;
RPropertyTypeId RDimStyle::PropertyDimblk2;

QList<QPair<RPropertyTypeId, RS::KnownVariable> > RDimStyle::propertyVariables;

RDimStyleProxy* RDimStyle::dimStyleProxy = NULL;

RDimStyle::RDimStyle() : RObject(), RDimStyleData(false) {
}

RDimStyle::RDimStyle(RDocument* document)
    : RObject(document), RDimStyleData(false) {

}

RDimStyle::~RDimStyle() {
}

void RDimStyle::init() {
    RDimStyle::PropertyCustom.generateId(RDimStyle::getRtti(), RObject::PropertyCustom);
    RDimStyle::PropertyHandle.generateId(RDimStyle::getRtti(), RObject::PropertyHandle);
    RDimStyle::PropertyProtected.generateId(RDimStyle::getRtti(), RObject::PropertyProtected);

    QString tsStyle = QT_TRANSLATE_NOOP("REntity", "Style");
    RDimStyle::PropertyDimscale.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Overall dimension scale"));
    RDimStyle::PropertyDimlfac.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Linear measurement factor"));
    RDimStyle::PropertyDimtxt.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text height"));
    RDimStyle::PropertyDimgap.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Dimension line gap"));
    RDimStyle::PropertyDimasz.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Arrow size"));
    RDimStyle::PropertyDimdli.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Dimension line increment"));
    RDimStyle::PropertyDimexe.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Extension line extension"));
    RDimStyle::PropertyDimexo.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Extension line offset"));
    RDimStyle::PropertyDimtad.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text above dimension line"));
    RDimStyle::PropertyDimtih.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text inside horizontal"));
    RDimStyle::PropertyDimtsz.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Tick size"));
    RDimStyle::PropertyDimlunit.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Linear format"));
    RDimStyle::PropertyDimdec.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Decimal places"));
    RDimStyle::PropertyDimdsep.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Decimal separator"));
    RDimStyle::PropertyDimzin.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Zero suppression"));
    RDimStyle::PropertyDimaunit.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Angular format"));
    RDimStyle::PropertyDimadec.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Angular decimal places"));
    RDimStyle::PropertyDimazin.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Angular zero suppression"));
    RDimStyle::PropertyArchTick.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Architectur tick"));
    RDimStyle::PropertyDimclrt.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Text color"));
    RDimStyle::PropertyDimblk.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Arrow block"));
    RDimStyle::PropertyDimblk1.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Arrow block 1"));
    RDimStyle::PropertyDimblk2.generateId(RDimStyle::getRtti(), tsStyle, QT_TRANSLATE_NOOP("REntity", "Arrow block 2"));

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
    initDimX(PropertyDimclrt, RS::DIMCLRT, RS::VarTypeColor);
    initDimX(PropertyDimblk, RS::DIMBLK, RS::VarTypeInt);
    initDimX(PropertyDimblk1, RS::DIMBLK1, RS::VarTypeInt);
    initDimX(PropertyDimblk2, RS::DIMBLK2, RS::VarTypeInt);
}

void RDimStyle::initDimX(const RPropertyTypeId& propertyTypeId, RS::KnownVariable var, RS::KnownVariableType type) {
    propertyVariables.append(QPair<RPropertyTypeId, RS::KnownVariable>(propertyTypeId, var));
    RDimStyleData::dimXTypes[var] = type;
}

void RDimStyle::updateDocumentVariables() {
    RDocument* doc = getDocument();

    for (int i=0; i<propertyVariables.length(); i++) {
        doc->setKnownVariable(propertyVariables[i].second, getVariant(propertyVariables[i].second));
    }
}

void RDimStyle::updateFromDocumentVariables() {
    RDocument* doc = getDocument();

    for (int i=0; i<propertyVariables.length(); i++) {
        QVariant v = doc->getKnownVariable(propertyVariables[i].second);
        setVariant(propertyVariables[i].second, v);
    }
}

QPair<QVariant, RPropertyAttributes> RDimStyle::getProperty(RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    for (int i=0; i<propertyVariables.length(); i++) {
        if (propertyTypeId==propertyVariables[i].first) {
            return qMakePair(getVariant(propertyVariables[i].second), RPropertyAttributes());
        }
    }

    if (propertyTypeId==PropertyArchTick) {
        return qMakePair(getDouble(RS::DIMTSZ) > 0.0, RPropertyAttributes());
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

bool RDimStyle::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {

    bool ret = false;

    for (int i=0; i<propertyVariables.length(); i++) {
        if (propertyTypeId==propertyVariables[i].first) {
            setVariant(propertyVariables[i].second, value);
            ret = true;
        }
    }

    if (propertyTypeId==PropertyArchTick) {
        if (value.toBool()==true) {
            setDouble(RS::DIMTSZ, getDouble(RS::DIMASZ));
        }
        else {
            setDouble(RS::DIMTSZ, 0.0);
        }
    }

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
