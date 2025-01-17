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
#include "RDimArcLengthEntity.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimArcLengthEntity::PropertyCustom;
RPropertyTypeId RDimArcLengthEntity::PropertyHandle;
RPropertyTypeId RDimArcLengthEntity::PropertyProtected;
RPropertyTypeId RDimArcLengthEntity::PropertyWorkingSet;
RPropertyTypeId RDimArcLengthEntity::PropertyType;
RPropertyTypeId RDimArcLengthEntity::PropertyBlock;
RPropertyTypeId RDimArcLengthEntity::PropertyLayer;
RPropertyTypeId RDimArcLengthEntity::PropertyLinetype;
RPropertyTypeId RDimArcLengthEntity::PropertyLinetypeScale;
RPropertyTypeId RDimArcLengthEntity::PropertyLineweight;
RPropertyTypeId RDimArcLengthEntity::PropertyColor;
RPropertyTypeId RDimArcLengthEntity::PropertyDisplayedColor;
RPropertyTypeId RDimArcLengthEntity::PropertyDrawOrder;

RPropertyTypeId RDimArcLengthEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimArcLengthEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimArcLengthEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimArcLengthEntity::PropertyText;
RPropertyTypeId RDimArcLengthEntity::PropertyUpperTolerance;
RPropertyTypeId RDimArcLengthEntity::PropertyLowerTolerance;

//RPropertyTypeId RDimArcLengthEntity::PropertyLinearFactor;
//RPropertyTypeId RDimArcLengthEntity::PropertyDimScale;
RPropertyTypeId RDimArcLengthEntity::PropertyDimBlockName;
RPropertyTypeId RDimArcLengthEntity::PropertyAutoTextPos;
RPropertyTypeId RDimArcLengthEntity::PropertyMeasuredValue;
RPropertyTypeId RDimArcLengthEntity::PropertyFontName;
RPropertyTypeId RDimArcLengthEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimArcLengthEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimArcLengthEntity::PropertyDimscale;
RPropertyTypeId RDimArcLengthEntity::PropertyDimlfac;
RPropertyTypeId RDimArcLengthEntity::PropertyDimtxt;
RPropertyTypeId RDimArcLengthEntity::PropertyDimgap;
RPropertyTypeId RDimArcLengthEntity::PropertyDimasz;
//RPropertyTypeId RDimArcLengthEntity::PropertyDimdli;
RPropertyTypeId RDimArcLengthEntity::PropertyDimexe;
RPropertyTypeId RDimArcLengthEntity::PropertyDimexo;
RPropertyTypeId RDimArcLengthEntity::PropertyDimtad;
RPropertyTypeId RDimArcLengthEntity::PropertyDimtih;
RPropertyTypeId RDimArcLengthEntity::PropertyDimtsz;
RPropertyTypeId RDimArcLengthEntity::PropertyDimlunit;
RPropertyTypeId RDimArcLengthEntity::PropertyDimdec;
RPropertyTypeId RDimArcLengthEntity::PropertyDimdsep;
RPropertyTypeId RDimArcLengthEntity::PropertyDimzin;
//RPropertyTypeId RDimArcLengthEntity::PropertyDimaunit;
//RPropertyTypeId RDimArcLengthEntity::PropertyDimadec;
//RPropertyTypeId RDimArcLengthEntity::PropertyDimazin;
RPropertyTypeId RDimArcLengthEntity::PropertyArchTick;
RPropertyTypeId RDimArcLengthEntity::PropertyDimclrt;

RPropertyTypeId RDimArcLengthEntity::PropertyExtLineFix;
RPropertyTypeId RDimArcLengthEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimArcLengthEntity::PropertyCenterX;
RPropertyTypeId RDimArcLengthEntity::PropertyCenterY;
RPropertyTypeId RDimArcLengthEntity::PropertyCenterZ;

RPropertyTypeId RDimArcLengthEntity::PropertyExtensionLine1EndX;
RPropertyTypeId RDimArcLengthEntity::PropertyExtensionLine1EndY;
RPropertyTypeId RDimArcLengthEntity::PropertyExtensionLine1EndZ;

RPropertyTypeId RDimArcLengthEntity::PropertyExtensionLine2EndX;
RPropertyTypeId RDimArcLengthEntity::PropertyExtensionLine2EndY;
RPropertyTypeId RDimArcLengthEntity::PropertyExtensionLine2EndZ;

RPropertyTypeId RDimArcLengthEntity::PropertyDimArcPositionX;
RPropertyTypeId RDimArcLengthEntity::PropertyDimArcPositionY;
RPropertyTypeId RDimArcLengthEntity::PropertyDimArcPositionZ;

RPropertyTypeId RDimArcLengthEntity::PropertyDimArcSymbolType;

RDimArcLengthEntity::RDimArcLengthEntity(RDocument* document, const RDimArcLengthData& data) :
    RDimAngularEntity(document), data(document, data) {
}

RDimArcLengthEntity::~RDimArcLengthEntity() {
}

void RDimArcLengthEntity::init() {
    RDimArcLengthEntity::PropertyCustom.generateId(RDimArcLengthEntity::getRtti(), RObject::PropertyCustom);
    RDimArcLengthEntity::PropertyHandle.generateId(RDimArcLengthEntity::getRtti(), RObject::PropertyHandle);
    RDimArcLengthEntity::PropertyProtected.generateId(RDimArcLengthEntity::getRtti(), RObject::PropertyProtected);
    RDimArcLengthEntity::PropertyWorkingSet.generateId(RDimArcLengthEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimArcLengthEntity::PropertyType.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyType);
    RDimArcLengthEntity::PropertyBlock.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyBlock);
    RDimArcLengthEntity::PropertyLayer.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyLayer);
    RDimArcLengthEntity::PropertyLinetype.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyLinetype);
    RDimArcLengthEntity::PropertyLinetypeScale.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimArcLengthEntity::PropertyLineweight.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyLineweight);
    RDimArcLengthEntity::PropertyColor.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyColor);
    RDimArcLengthEntity::PropertyDisplayedColor.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimArcLengthEntity::PropertyDrawOrder.generateId(RDimArcLengthEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimArcLengthEntity::PropertyMiddleOfTextX.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimArcLengthEntity::PropertyMiddleOfTextY.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimArcLengthEntity::PropertyMiddleOfTextZ.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimArcLengthEntity::PropertyText.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimArcLengthEntity::PropertyUpperTolerance.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimArcLengthEntity::PropertyLowerTolerance.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimArcLengthEntity::PropertyMeasuredValue.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimArcLengthEntity::PropertyDimscale.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        RDimArcLengthEntity::PropertyDimlfac.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimArcLengthEntity::PropertyDimtxt.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimArcLengthEntity::PropertyDimgap.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimArcLengthEntity::PropertyDimasz.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimArcLengthEntity::PropertyDimdli.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimArcLengthEntity::PropertyDimexe.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimArcLengthEntity::PropertyDimexo.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimArcLengthEntity::PropertyDimtad.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimArcLengthEntity::PropertyDimtih.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimArcLengthEntity::PropertyDimtsz.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
        RDimArcLengthEntity::PropertyDimlunit.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
        RDimArcLengthEntity::PropertyDimdec.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimArcLengthEntity::PropertyDimdsep.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
        RDimArcLengthEntity::PropertyDimzin.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimzin);
    //    RDimArcLengthEntity::PropertyDimaunit.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
    //    RDimArcLengthEntity::PropertyDimadec.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimadec);
    //    RDimArcLengthEntity::PropertyDimazin.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimArcLengthEntity::PropertyArchTick.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimArcLengthEntity::PropertyDimclrt.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

//    RDimArcLengthEntity::PropertyLinearFactor.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyLinearFactor);
//    RDimArcLengthEntity::PropertyDimScale.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimScale);
    RDimArcLengthEntity::PropertyDimBlockName.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);
    RDimArcLengthEntity::PropertyAutoTextPos.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyAutoTextPos);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimArcLengthEntity::PropertyFontName.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimArcLengthEntity::PropertyArrow1Flipped.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        RDimArcLengthEntity::PropertyArrow2Flipped.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        RDimArcLengthEntity::PropertyExtLineFix.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        RDimArcLengthEntity::PropertyExtLineFixLength.generateId(RDimArcLengthEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

//    RDimArcLengthEntity::PropertyCenterX.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyCenterY.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyCenterZ.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimArcLengthEntity::PropertyCenterX.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyCenterX);
    RDimArcLengthEntity::PropertyCenterY.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyCenterY);
    RDimArcLengthEntity::PropertyCenterZ.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyCenterZ);

    RDimArcLengthEntity::PropertyExtensionLine1EndX.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine1EndX);
    RDimArcLengthEntity::PropertyExtensionLine1EndY.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine1EndY);
    RDimArcLengthEntity::PropertyExtensionLine1EndZ.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine1EndZ);

//    RDimArcLengthEntity::PropertyExtensionLine1EndX.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true);
//    RDimArcLengthEntity::PropertyExtensionLine1EndY.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
//    RDimArcLengthEntity::PropertyExtensionLine1EndZ.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimArcLengthEntity::PropertyExtensionLine2EndX.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine2EndX);
    RDimArcLengthEntity::PropertyExtensionLine2EndY.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine2EndY);
    RDimArcLengthEntity::PropertyExtensionLine2EndZ.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine2EndZ);

//    RDimArcLengthEntity::PropertyDimArcPositionX.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyDimArcPositionY.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyDimArcPositionZ.generateId(RDimArcLengthEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimArcLengthEntity::PropertyDimArcPositionX.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyDimArcPositionX);
    RDimArcLengthEntity::PropertyDimArcPositionY.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyDimArcPositionY);
    RDimArcLengthEntity::PropertyDimArcPositionZ.generateId(RDimArcLengthEntity::getRtti(), RDimAngularEntity::PropertyDimArcPositionZ);

    RDimArcLengthEntity::PropertyDimArcSymbolType.generateId(RDimArcLengthEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Arc Symbol Type"));
}

bool RDimArcLengthEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.center.x, value, PropertyCenterX == propertyTypeId);
    ret = ret || RObject::setMember(data.center.y, value, PropertyCenterY == propertyTypeId);
    ret = ret || RObject::setMember(data.center.z, value, PropertyCenterZ == propertyTypeId);

    ret = ret || RObject::setMember(data.extensionLine1End.x, value, PropertyExtensionLine1EndX == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine1End.y, value, PropertyExtensionLine1EndY == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine1End.z, value, PropertyExtensionLine1EndZ == propertyTypeId);

    ret = ret || RObject::setMember(data.extensionLine2End.x, value, PropertyExtensionLine2EndX == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine2End.y, value, PropertyExtensionLine2EndY == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine2End.z, value, PropertyExtensionLine2EndZ == propertyTypeId);

    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyDimArcPositionX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyDimArcPositionY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyDimArcPositionZ == propertyTypeId);

    if (PropertyDimArcSymbolType == propertyTypeId) {
        ret = ret || RObject::setMember(data.arcSymbolType, value.toInt(), true);
    }

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimArcLengthEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyCenterX) {
        return qMakePair(QVariant(data.center.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterY) {
        return qMakePair(QVariant(data.center.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterZ) {
        return qMakePair(QVariant(data.center.z), RPropertyAttributes());
    }

      else if (propertyTypeId == PropertyExtensionLine1EndX) {
        return qMakePair(QVariant(data.extensionLine1End.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine1EndY) {
        return qMakePair(QVariant(data.extensionLine1End.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine1EndZ) {
        return qMakePair(QVariant(data.extensionLine1End.z), RPropertyAttributes());
    }

      else if (propertyTypeId == PropertyExtensionLine2EndX) {
        return qMakePair(QVariant(data.extensionLine2End.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine2EndY) {
        return qMakePair(QVariant(data.extensionLine2End.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine2EndZ) {
        return qMakePair(QVariant(data.extensionLine2End.z), RPropertyAttributes());
    }

      else if (propertyTypeId == PropertyDimArcPositionX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimArcPositionY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimArcPositionZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyDimArcSymbolType) {
        return qMakePair(QVariant(data.arcSymbolType), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimArcLengthEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimArcLengthEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", center: " << getData().center
                  << ")";
}
