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
#include "RDimDiametricEntity.h"
#include "RExporter.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimDiametricEntity::PropertyCustom;
RPropertyTypeId RDimDiametricEntity::PropertyHandle;
RPropertyTypeId RDimDiametricEntity::PropertyProtected;
RPropertyTypeId RDimDiametricEntity::PropertyWorkingSet;
RPropertyTypeId RDimDiametricEntity::PropertyType;
RPropertyTypeId RDimDiametricEntity::PropertyBlock;
RPropertyTypeId RDimDiametricEntity::PropertyLayer;
RPropertyTypeId RDimDiametricEntity::PropertyLinetype;
RPropertyTypeId RDimDiametricEntity::PropertyLinetypeScale;
RPropertyTypeId RDimDiametricEntity::PropertyLineweight;
RPropertyTypeId RDimDiametricEntity::PropertyColor;
RPropertyTypeId RDimDiametricEntity::PropertyDisplayedColor;
RPropertyTypeId RDimDiametricEntity::PropertyDrawOrder;

RPropertyTypeId RDimDiametricEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimDiametricEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimDiametricEntity::PropertyMiddleOfTextZ;

RPropertyTypeId RDimDiametricEntity::PropertyText;
RPropertyTypeId RDimDiametricEntity::PropertyUpperTolerance;
RPropertyTypeId RDimDiametricEntity::PropertyLowerTolerance;
RPropertyTypeId RDimDiametricEntity::PropertyMeasuredValue;

RPropertyTypeId RDimDiametricEntity::PropertyDimscale;
RPropertyTypeId RDimDiametricEntity::PropertyDimlfac;
RPropertyTypeId RDimDiametricEntity::PropertyDimtxt;
RPropertyTypeId RDimDiametricEntity::PropertyDimgap;
RPropertyTypeId RDimDiametricEntity::PropertyDimasz;
//RPropertyTypeId RDimDiametricEntity::PropertyDimdli;
RPropertyTypeId RDimDiametricEntity::PropertyDimexe;
RPropertyTypeId RDimDiametricEntity::PropertyDimexo;
RPropertyTypeId RDimDiametricEntity::PropertyDimtad;
RPropertyTypeId RDimDiametricEntity::PropertyDimtih;
RPropertyTypeId RDimDiametricEntity::PropertyDimtsz;
RPropertyTypeId RDimDiametricEntity::PropertyDimlunit;
RPropertyTypeId RDimDiametricEntity::PropertyDimdec;
RPropertyTypeId RDimDiametricEntity::PropertyDimdsep;
RPropertyTypeId RDimDiametricEntity::PropertyDimzin;
//RPropertyTypeId RDimDiametricEntity::PropertyDimaunit;
//RPropertyTypeId RDimDiametricEntity::PropertyDimadec;
//RPropertyTypeId RDimDiametricEntity::PropertyDimazin;
RPropertyTypeId RDimDiametricEntity::PropertyArchTick;
RPropertyTypeId RDimDiametricEntity::PropertyDimclrt;

//RPropertyTypeId RDimDiametricEntity::PropertyLinearFactor;
//RPropertyTypeId RDimDiametricEntity::PropertyDimScale;
RPropertyTypeId RDimDiametricEntity::PropertyDimBlockName;
RPropertyTypeId RDimDiametricEntity::PropertyAutoTextPos;
RPropertyTypeId RDimDiametricEntity::PropertyFontName;
RPropertyTypeId RDimDiametricEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimDiametricEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimDiametricEntity::PropertyExtLineFix;
RPropertyTypeId RDimDiametricEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimDiametricEntity::PropertyChordPointX;
RPropertyTypeId RDimDiametricEntity::PropertyChordPointY;
RPropertyTypeId RDimDiametricEntity::PropertyChordPointZ;

RPropertyTypeId RDimDiametricEntity::PropertyFarChordPointX;
RPropertyTypeId RDimDiametricEntity::PropertyFarChordPointY;
RPropertyTypeId RDimDiametricEntity::PropertyFarChordPointZ;


RDimDiametricEntity::RDimDiametricEntity(RDocument* document, const RDimDiametricData& data) :
    RDimensionEntity(document), data(document, data) {
}

RDimDiametricEntity::~RDimDiametricEntity() {
}

void RDimDiametricEntity::init() {
    RDimDiametricEntity::PropertyCustom.generateId(RDimDiametricEntity::getRtti(), RObject::PropertyCustom);
    RDimDiametricEntity::PropertyHandle.generateId(RDimDiametricEntity::getRtti(), RObject::PropertyHandle);
    RDimDiametricEntity::PropertyProtected.generateId(RDimDiametricEntity::getRtti(), RObject::PropertyProtected);
    RDimDiametricEntity::PropertyWorkingSet.generateId(RDimDiametricEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimDiametricEntity::PropertyType.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyType);
    RDimDiametricEntity::PropertyBlock.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyBlock);
    RDimDiametricEntity::PropertyLayer.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyLayer);
    RDimDiametricEntity::PropertyLinetype.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyLinetype);
    RDimDiametricEntity::PropertyLinetypeScale.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimDiametricEntity::PropertyLineweight.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyLineweight);
    RDimDiametricEntity::PropertyColor.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyColor);
    RDimDiametricEntity::PropertyDisplayedColor.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimDiametricEntity::PropertyDrawOrder.generateId(RDimDiametricEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimDiametricEntity::PropertyMiddleOfTextX.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimDiametricEntity::PropertyMiddleOfTextY.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimDiametricEntity::PropertyMiddleOfTextZ.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimDiametricEntity::PropertyText.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimDiametricEntity::PropertyUpperTolerance.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimDiametricEntity::PropertyLowerTolerance.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimDiametricEntity::PropertyMeasuredValue.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimDiametricEntity::PropertyDimscale.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        RDimDiametricEntity::PropertyDimlfac.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimDiametricEntity::PropertyDimtxt.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimDiametricEntity::PropertyDimgap.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimDiametricEntity::PropertyDimasz.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimDiametricEntity::PropertyDimdli.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimDiametricEntity::PropertyDimexe.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimDiametricEntity::PropertyDimexo.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimDiametricEntity::PropertyDimtad.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimDiametricEntity::PropertyDimtih.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimDiametricEntity::PropertyDimtsz.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
        RDimDiametricEntity::PropertyDimlunit.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
        RDimDiametricEntity::PropertyDimdec.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimDiametricEntity::PropertyDimdsep.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
        RDimDiametricEntity::PropertyDimzin.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimzin);
    //    RDimDiametricEntity::PropertyDimaunit.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
    //    RDimDiametricEntity::PropertyDimadec.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimadec);
    //    RDimDiametricEntity::PropertyDimazin.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimDiametricEntity::PropertyArchTick.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimDiametricEntity::PropertyDimclrt.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

//    RDimDiametricEntity::PropertyLinearFactor.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyLinearFactor);
//    RDimDiametricEntity::PropertyDimScale.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimScale);
    RDimDiametricEntity::PropertyDimBlockName.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);
    RDimDiametricEntity::PropertyAutoTextPos.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyAutoTextPos);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimDiametricEntity::PropertyFontName.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimDiametricEntity::PropertyArrow1Flipped.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        RDimDiametricEntity::PropertyArrow2Flipped.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        RDimDiametricEntity::PropertyExtLineFix.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        RDimDiametricEntity::PropertyExtLineFixLength.generateId(RDimDiametricEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

    RDimDiametricEntity::PropertyChordPointX.generateId(RDimDiametricEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyChordPointY.generateId(RDimDiametricEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyChordPointZ.generateId(RDimDiametricEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RDimDiametricEntity::PropertyFarChordPointX.generateId(RDimDiametricEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Far Chord Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyFarChordPointY.generateId(RDimDiametricEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Far Chord Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyFarChordPointZ.generateId(RDimDiametricEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Far Chord Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RDimDiametricEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyChordPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyChordPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyChordPointZ == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.x, value, PropertyFarChordPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.y, value, PropertyFarChordPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.z, value, PropertyFarChordPointZ == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimDiametricEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyChordPointX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyFarChordPointX) {
        return qMakePair(QVariant(data.chordPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyFarChordPointY) {
        return qMakePair(QVariant(data.chordPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyFarChordPointZ) {
        return qMakePair(QVariant(data.chordPoint.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimDiametricEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimDiametricEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", definitionPoint: " << getData().definitionPoint
                  << ", definitionPoint2: " << getData().chordPoint
                  << ")";
}
