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
#include "RDimAlignedEntity.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimAlignedEntity::PropertyCustom;
RPropertyTypeId RDimAlignedEntity::PropertyHandle;
RPropertyTypeId RDimAlignedEntity::PropertyProtected;
RPropertyTypeId RDimAlignedEntity::PropertyWorkingSet;
RPropertyTypeId RDimAlignedEntity::PropertyType;
RPropertyTypeId RDimAlignedEntity::PropertyBlock;
RPropertyTypeId RDimAlignedEntity::PropertyLayer;
RPropertyTypeId RDimAlignedEntity::PropertyLinetype;
RPropertyTypeId RDimAlignedEntity::PropertyLinetypeScale;
RPropertyTypeId RDimAlignedEntity::PropertyLineweight;
RPropertyTypeId RDimAlignedEntity::PropertyColor;
RPropertyTypeId RDimAlignedEntity::PropertyDisplayedColor;
RPropertyTypeId RDimAlignedEntity::PropertyDrawOrder;

RPropertyTypeId RDimAlignedEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimAlignedEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimAlignedEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimAlignedEntity::PropertyText;
RPropertyTypeId RDimAlignedEntity::PropertyUpperTolerance;
RPropertyTypeId RDimAlignedEntity::PropertyLowerTolerance;
RPropertyTypeId RDimAlignedEntity::PropertyMeasuredValue;

RPropertyTypeId RDimAlignedEntity::PropertyDimscale;
RPropertyTypeId RDimAlignedEntity::PropertyDimlfac;
RPropertyTypeId RDimAlignedEntity::PropertyDimtxt;
RPropertyTypeId RDimAlignedEntity::PropertyDimgap;
RPropertyTypeId RDimAlignedEntity::PropertyDimasz;
//RPropertyTypeId RDimAlignedEntity::PropertyDimdli;
RPropertyTypeId RDimAlignedEntity::PropertyDimexe;
RPropertyTypeId RDimAlignedEntity::PropertyDimexo;
RPropertyTypeId RDimAlignedEntity::PropertyDimtad;
RPropertyTypeId RDimAlignedEntity::PropertyDimtih;
RPropertyTypeId RDimAlignedEntity::PropertyDimtsz;
RPropertyTypeId RDimAlignedEntity::PropertyDimlunit;
RPropertyTypeId RDimAlignedEntity::PropertyDimdec;
RPropertyTypeId RDimAlignedEntity::PropertyDimdsep;
RPropertyTypeId RDimAlignedEntity::PropertyDimzin;
//RPropertyTypeId RDimAlignedEntity::PropertyDimaunit;
//RPropertyTypeId RDimAlignedEntity::PropertyDimadec;
//RPropertyTypeId RDimAlignedEntity::PropertyDimazin;
RPropertyTypeId RDimAlignedEntity::PropertyArchTick;
RPropertyTypeId RDimAlignedEntity::PropertyDimclrt;


//RPropertyTypeId RDimAlignedEntity::PropertyLinearFactor;
//RPropertyTypeId RDimAlignedEntity::PropertyDimScale;
RPropertyTypeId RDimAlignedEntity::PropertyDimBlockName;
RPropertyTypeId RDimAlignedEntity::PropertyAutoTextPos;
RPropertyTypeId RDimAlignedEntity::PropertyFontName;
RPropertyTypeId RDimAlignedEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimAlignedEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimAlignedEntity::PropertyExtLineFix;
RPropertyTypeId RDimAlignedEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimAlignedEntity::PropertyDimensionLinePosX;
RPropertyTypeId RDimAlignedEntity::PropertyDimensionLinePosY;
RPropertyTypeId RDimAlignedEntity::PropertyDimensionLinePosZ;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint1X;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint1Y;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint1Z;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint2X;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint2Y;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint2Z;


RDimAlignedEntity::RDimAlignedEntity(RDocument* document, const RDimAlignedData& data) :
    RDimLinearEntity(document), data(document, data) {
}

RDimAlignedEntity::~RDimAlignedEntity() {
}

void RDimAlignedEntity::init() {
    RDimAlignedEntity::PropertyCustom.generateId(RDimAlignedEntity::getRtti(), RObject::PropertyCustom);
    RDimAlignedEntity::PropertyHandle.generateId(RDimAlignedEntity::getRtti(), RObject::PropertyHandle);
    RDimAlignedEntity::PropertyProtected.generateId(RDimAlignedEntity::getRtti(), RObject::PropertyProtected);
    RDimAlignedEntity::PropertyWorkingSet.generateId(RDimAlignedEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimAlignedEntity::PropertyType.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyType);
    RDimAlignedEntity::PropertyBlock.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyBlock);
    RDimAlignedEntity::PropertyLayer.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyLayer);
    RDimAlignedEntity::PropertyLinetype.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyLinetype);
    RDimAlignedEntity::PropertyLinetypeScale.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimAlignedEntity::PropertyLineweight.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyLineweight);
    RDimAlignedEntity::PropertyColor.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyColor);
    RDimAlignedEntity::PropertyDisplayedColor.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimAlignedEntity::PropertyDrawOrder.generateId(RDimAlignedEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimAlignedEntity::PropertyMiddleOfTextX.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAlignedEntity::PropertyMiddleOfTextY.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAlignedEntity::PropertyMiddleOfTextZ.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimAlignedEntity::PropertyText.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimAlignedEntity::PropertyUpperTolerance.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimAlignedEntity::PropertyLowerTolerance.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimAlignedEntity::PropertyMeasuredValue.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimAlignedEntity::PropertyDimscale.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        RDimAlignedEntity::PropertyDimlfac.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimAlignedEntity::PropertyDimtxt.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimAlignedEntity::PropertyDimgap.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimAlignedEntity::PropertyDimasz.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimAlignedEntity::PropertyDimdli.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimAlignedEntity::PropertyDimexe.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimAlignedEntity::PropertyDimexo.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimAlignedEntity::PropertyDimtad.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimAlignedEntity::PropertyDimtih.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimAlignedEntity::PropertyDimtsz.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
        RDimAlignedEntity::PropertyDimlunit.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
        RDimAlignedEntity::PropertyDimdec.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimAlignedEntity::PropertyDimdsep.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
        RDimAlignedEntity::PropertyDimzin.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimzin);
    //    RDimAlignedEntity::PropertyDimaunit.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
    //    RDimAlignedEntity::PropertyDimadec.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimadec);
    //    RDimAlignedEntity::PropertyDimazin.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimAlignedEntity::PropertyArchTick.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimAlignedEntity::PropertyDimclrt.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

    //RDimAlignedEntity::PropertyLinearFactor.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyLinearFactor);
    //RDimAlignedEntity::PropertyDimScale.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimScale);
    RDimAlignedEntity::PropertyDimBlockName.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);
    RDimAlignedEntity::PropertyAutoTextPos.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyAutoTextPos);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimAlignedEntity::PropertyFontName.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimAlignedEntity::PropertyArrow1Flipped.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        RDimAlignedEntity::PropertyArrow2Flipped.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        RDimAlignedEntity::PropertyExtLineFix.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        RDimAlignedEntity::PropertyExtLineFixLength.generateId(RDimAlignedEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

    RDimAlignedEntity::PropertyDimensionLinePosX.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyDimensionLinePosX);
    RDimAlignedEntity::PropertyDimensionLinePosY.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyDimensionLinePosY);
    RDimAlignedEntity::PropertyDimensionLinePosZ.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyDimensionLinePosZ);

    RDimAlignedEntity::PropertyExtensionPoint1X.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint1X);
    RDimAlignedEntity::PropertyExtensionPoint1Y.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint1Y);
    RDimAlignedEntity::PropertyExtensionPoint1Z.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint1Z);

    RDimAlignedEntity::PropertyExtensionPoint2X.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint2X);
    RDimAlignedEntity::PropertyExtensionPoint2Y.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint2Y);
    RDimAlignedEntity::PropertyExtensionPoint2Z.generateId(RDimAlignedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint2Z);
}

bool RDimAlignedEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimLinearEntity::setProperty(propertyTypeId, value, transaction);

//    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyDimensionLinePosX == propertyTypeId);
//    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyDimensionLinePosY == propertyTypeId);
//    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyDimensionLinePosZ == propertyTypeId);

//    ret = ret || RObject::setMember(data.extensionPoint1.x, value, PropertyExtensionPoint1X == propertyTypeId);
//    ret = ret || RObject::setMember(data.extensionPoint1.y, value, PropertyExtensionPoint1Y == propertyTypeId);
//    ret = ret || RObject::setMember(data.extensionPoint1.z, value, PropertyExtensionPoint1Z == propertyTypeId);

//    ret = ret || RObject::setMember(data.extensionPoint2.x, value, PropertyExtensionPoint2X == propertyTypeId);
//    ret = ret || RObject::setMember(data.extensionPoint2.y, value, PropertyExtensionPoint2Y == propertyTypeId);
//    ret = ret || RObject::setMember(data.extensionPoint2.z, value, PropertyExtensionPoint2Z == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimAlignedEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
//    if (propertyTypeId == PropertyDimensionLinePosX) {
//        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyDimensionLinePosY) {
//        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyDimensionLinePosZ) {
//        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
//    }
//    } else if (propertyTypeId == PropertyExtensionPoint1X) {
//        return qMakePair(QVariant(data.extensionPoint1.x), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint1Y) {
//        return qMakePair(QVariant(data.extensionPoint1.y), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint1Z) {
//        return qMakePair(QVariant(data.extensionPoint1.z), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint2X) {
//        return qMakePair(QVariant(data.extensionPoint2.x), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint2Y) {
//        return qMakePair(QVariant(data.extensionPoint2.y), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint2Z) {
//        return qMakePair(QVariant(data.extensionPoint2.z), RPropertyAttributes());
//    }

    return RDimLinearEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimAlignedEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimAlignedEntity(";
    RDimLinearEntity::print(dbg);
    dbg.nospace() << ", extensionPoint1: " << getData().extensionPoint1
                  << ", extensionPoint2: " << getData().extensionPoint2
                  << ")";
}
