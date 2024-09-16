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
#include "RDimRadialEntity.h"
#include "RExporter.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimRadialEntity::PropertyCustom;
RPropertyTypeId RDimRadialEntity::PropertyHandle;
RPropertyTypeId RDimRadialEntity::PropertyProtected;
RPropertyTypeId RDimRadialEntity::PropertyWorkingSet;
RPropertyTypeId RDimRadialEntity::PropertyType;
RPropertyTypeId RDimRadialEntity::PropertyBlock;
RPropertyTypeId RDimRadialEntity::PropertyLayer;
RPropertyTypeId RDimRadialEntity::PropertyLinetype;
RPropertyTypeId RDimRadialEntity::PropertyLinetypeScale;
RPropertyTypeId RDimRadialEntity::PropertyLineweight;
RPropertyTypeId RDimRadialEntity::PropertyColor;
RPropertyTypeId RDimRadialEntity::PropertyDisplayedColor;
RPropertyTypeId RDimRadialEntity::PropertyDrawOrder;

RPropertyTypeId RDimRadialEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimRadialEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimRadialEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimRadialEntity::PropertyText;
RPropertyTypeId RDimRadialEntity::PropertyUpperTolerance;
RPropertyTypeId RDimRadialEntity::PropertyLowerTolerance;
RPropertyTypeId RDimRadialEntity::PropertyMeasuredValue;

RPropertyTypeId RDimRadialEntity::PropertyDimscale;
RPropertyTypeId RDimRadialEntity::PropertyDimlfac;
RPropertyTypeId RDimRadialEntity::PropertyDimtxt;
RPropertyTypeId RDimRadialEntity::PropertyDimgap;
RPropertyTypeId RDimRadialEntity::PropertyDimasz;
//RPropertyTypeId RDimRadialEntity::PropertyDimdli;
RPropertyTypeId RDimRadialEntity::PropertyDimexe;
RPropertyTypeId RDimRadialEntity::PropertyDimexo;
RPropertyTypeId RDimRadialEntity::PropertyDimtad;
RPropertyTypeId RDimRadialEntity::PropertyDimtih;
RPropertyTypeId RDimRadialEntity::PropertyDimtsz;
RPropertyTypeId RDimRadialEntity::PropertyDimlunit;
RPropertyTypeId RDimRadialEntity::PropertyDimdec;
RPropertyTypeId RDimRadialEntity::PropertyDimdsep;
RPropertyTypeId RDimRadialEntity::PropertyDimzin;
//RPropertyTypeId RDimRadialEntity::PropertyDimaunit;
//RPropertyTypeId RDimRadialEntity::PropertyDimadec;
//RPropertyTypeId RDimRadialEntity::PropertyDimazin;
RPropertyTypeId RDimRadialEntity::PropertyArchTick;
RPropertyTypeId RDimRadialEntity::PropertyDimclrt;

//RPropertyTypeId RDimRadialEntity::PropertyLinearFactor;
//RPropertyTypeId RDimRadialEntity::PropertyDimScale;
RPropertyTypeId RDimRadialEntity::PropertyDimBlockName;
RPropertyTypeId RDimRadialEntity::PropertyAutoTextPos;
RPropertyTypeId RDimRadialEntity::PropertyFontName;
RPropertyTypeId RDimRadialEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimRadialEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimRadialEntity::PropertyExtLineFix;
RPropertyTypeId RDimRadialEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimRadialEntity::PropertyCenterPointX;
RPropertyTypeId RDimRadialEntity::PropertyCenterPointY;
RPropertyTypeId RDimRadialEntity::PropertyCenterPointZ;
RPropertyTypeId RDimRadialEntity::PropertyChordPointX;
RPropertyTypeId RDimRadialEntity::PropertyChordPointY;
RPropertyTypeId RDimRadialEntity::PropertyChordPointZ;


RDimRadialEntity::RDimRadialEntity(RDocument* document, const RDimRadialData& data) :
    RDimensionEntity(document), data(document, data) {
}

RDimRadialEntity::~RDimRadialEntity() {
}

void RDimRadialEntity::init() {
    RDimRadialEntity::PropertyCustom.generateId(RDimRadialEntity::getRtti(), RObject::PropertyCustom);
    RDimRadialEntity::PropertyHandle.generateId(RDimRadialEntity::getRtti(), RObject::PropertyHandle);
    RDimRadialEntity::PropertyProtected.generateId(RDimRadialEntity::getRtti(), RObject::PropertyProtected);
    RDimRadialEntity::PropertyWorkingSet.generateId(RDimRadialEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimRadialEntity::PropertyType.generateId(RDimRadialEntity::getRtti(), REntity::PropertyType);
    RDimRadialEntity::PropertyBlock.generateId(RDimRadialEntity::getRtti(), REntity::PropertyBlock);
    RDimRadialEntity::PropertyLayer.generateId(RDimRadialEntity::getRtti(), REntity::PropertyLayer);
    RDimRadialEntity::PropertyLinetype.generateId(RDimRadialEntity::getRtti(), REntity::PropertyLinetype);
    RDimRadialEntity::PropertyLinetypeScale.generateId(RDimRadialEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimRadialEntity::PropertyLineweight.generateId(RDimRadialEntity::getRtti(), REntity::PropertyLineweight);
    RDimRadialEntity::PropertyColor.generateId(RDimRadialEntity::getRtti(), REntity::PropertyColor);
    RDimRadialEntity::PropertyDisplayedColor.generateId(RDimRadialEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimRadialEntity::PropertyDrawOrder.generateId(RDimRadialEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimRadialEntity::PropertyMiddleOfTextX.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimRadialEntity::PropertyMiddleOfTextY.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimRadialEntity::PropertyMiddleOfTextZ.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimRadialEntity::PropertyText.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimRadialEntity::PropertyUpperTolerance.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimRadialEntity::PropertyLowerTolerance.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimRadialEntity::PropertyMeasuredValue.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimRadialEntity::PropertyDimscale.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        RDimRadialEntity::PropertyDimlfac.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimRadialEntity::PropertyDimtxt.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimRadialEntity::PropertyDimgap.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimRadialEntity::PropertyDimasz.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimRadialEntity::PropertyDimdli.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimRadialEntity::PropertyDimexe.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimRadialEntity::PropertyDimexo.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimRadialEntity::PropertyDimtad.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimRadialEntity::PropertyDimtih.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimRadialEntity::PropertyDimtsz.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
        RDimRadialEntity::PropertyDimlunit.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
        RDimRadialEntity::PropertyDimdec.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimRadialEntity::PropertyDimdsep.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
        RDimRadialEntity::PropertyDimzin.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimzin);
    //    RDimRadialEntity::PropertyDimaunit.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
    //    RDimRadialEntity::PropertyDimadec.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimadec);
    //    RDimRadialEntity::PropertyDimazin.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimRadialEntity::PropertyArchTick.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimRadialEntity::PropertyDimclrt.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

//    RDimRadialEntity::PropertyLinearFactor.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyLinearFactor);
//    RDimRadialEntity::PropertyDimScale.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimScale);
    RDimRadialEntity::PropertyDimBlockName.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);
    RDimRadialEntity::PropertyAutoTextPos.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyAutoTextPos);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimRadialEntity::PropertyFontName.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimRadialEntity::PropertyArrow1Flipped.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        //RDimRadialEntity::PropertyArrow2Flipped.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        //RDimRadialEntity::PropertyExtLineFix.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        //RDimRadialEntity::PropertyExtLineFixLength.generateId(RDimRadialEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

    RDimRadialEntity::PropertyCenterPointX.generateId(RDimRadialEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyCenterPointY.generateId(RDimRadialEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyCenterPointZ.generateId(RDimRadialEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimRadialEntity::PropertyChordPointX.generateId(RDimRadialEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyChordPointY.generateId(RDimRadialEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyChordPointZ.generateId(RDimRadialEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RDimRadialEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyCenterPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyCenterPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyCenterPointZ == propertyTypeId);

    ret = ret || RObject::setMember(data.chordPoint.x, value, PropertyChordPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.y, value, PropertyChordPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.z, value, PropertyChordPointZ == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimRadialEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyCenterPointX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterPointY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterPointZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointX) {
        return qMakePair(QVariant(data.chordPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointY) {
        return qMakePair(QVariant(data.chordPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointZ) {
        return qMakePair(QVariant(data.chordPoint.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimRadialEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimRadialEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", definitionPoint: " << getData().definitionPoint
                  << ", definitionPoint2: " << getData().chordPoint
                  << ")";
}
