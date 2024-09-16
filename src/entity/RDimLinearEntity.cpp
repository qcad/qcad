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
#include "RDimLinearEntity.h"
#include "RExporter.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimLinearEntity::PropertyCustom;
RPropertyTypeId RDimLinearEntity::PropertyHandle;
RPropertyTypeId RDimLinearEntity::PropertyProtected;
RPropertyTypeId RDimLinearEntity::PropertyWorkingSet;
RPropertyTypeId RDimLinearEntity::PropertyType;
RPropertyTypeId RDimLinearEntity::PropertyBlock;
RPropertyTypeId RDimLinearEntity::PropertyLayer;
RPropertyTypeId RDimLinearEntity::PropertyLinetype;
RPropertyTypeId RDimLinearEntity::PropertyLinetypeScale;
RPropertyTypeId RDimLinearEntity::PropertyLineweight;
RPropertyTypeId RDimLinearEntity::PropertyColor;
RPropertyTypeId RDimLinearEntity::PropertyDisplayedColor;
RPropertyTypeId RDimLinearEntity::PropertyDrawOrder;

RPropertyTypeId RDimLinearEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimLinearEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimLinearEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimLinearEntity::PropertyText;
RPropertyTypeId RDimLinearEntity::PropertyUpperTolerance;
RPropertyTypeId RDimLinearEntity::PropertyLowerTolerance;
RPropertyTypeId RDimLinearEntity::PropertyMeasuredValue;

RPropertyTypeId RDimLinearEntity::PropertyDimscale;
RPropertyTypeId RDimLinearEntity::PropertyDimlfac;
RPropertyTypeId RDimLinearEntity::PropertyDimtxt;
RPropertyTypeId RDimLinearEntity::PropertyDimgap;
RPropertyTypeId RDimLinearEntity::PropertyDimasz;
//RPropertyTypeId RDimLinearEntity::PropertyDimdli;
RPropertyTypeId RDimLinearEntity::PropertyDimexe;
RPropertyTypeId RDimLinearEntity::PropertyDimexo;
RPropertyTypeId RDimLinearEntity::PropertyDimtad;
RPropertyTypeId RDimLinearEntity::PropertyDimtih;
RPropertyTypeId RDimLinearEntity::PropertyDimtsz;
RPropertyTypeId RDimLinearEntity::PropertyDimlunit;
RPropertyTypeId RDimLinearEntity::PropertyDimdec;
RPropertyTypeId RDimLinearEntity::PropertyDimdsep;
RPropertyTypeId RDimLinearEntity::PropertyDimzin;
RPropertyTypeId RDimLinearEntity::PropertyDimaunit;
RPropertyTypeId RDimLinearEntity::PropertyDimadec;
RPropertyTypeId RDimLinearEntity::PropertyDimazin;
RPropertyTypeId RDimLinearEntity::PropertyArchTick;
RPropertyTypeId RDimLinearEntity::PropertyDimclrt;

//RPropertyTypeId RDimLinearEntity::PropertyLinearFactor;
//RPropertyTypeId RDimLinearEntity::PropertyDimScale;
RPropertyTypeId RDimLinearEntity::PropertyDimBlockName;
RPropertyTypeId RDimLinearEntity::PropertyAutoTextPos;
RPropertyTypeId RDimLinearEntity::PropertyFontName;
RPropertyTypeId RDimLinearEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimLinearEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimLinearEntity::PropertyExtLineFix;
RPropertyTypeId RDimLinearEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimLinearEntity::PropertyDimensionLinePosX;
RPropertyTypeId RDimLinearEntity::PropertyDimensionLinePosY;
RPropertyTypeId RDimLinearEntity::PropertyDimensionLinePosZ;
RPropertyTypeId RDimLinearEntity::PropertyExtensionPoint1X;
RPropertyTypeId RDimLinearEntity::PropertyExtensionPoint1Y;
RPropertyTypeId RDimLinearEntity::PropertyExtensionPoint1Z;
RPropertyTypeId RDimLinearEntity::PropertyExtensionPoint2X;
RPropertyTypeId RDimLinearEntity::PropertyExtensionPoint2Y;
RPropertyTypeId RDimLinearEntity::PropertyExtensionPoint2Z;


RDimLinearEntity::RDimLinearEntity(RDocument* document) :
    RDimensionEntity(document) {
}

RDimLinearEntity::~RDimLinearEntity() {
}

void RDimLinearEntity::init() {
    RDimLinearEntity::PropertyCustom.generateId(RDimLinearEntity::getRtti(), RObject::PropertyCustom);
    RDimLinearEntity::PropertyHandle.generateId(RDimLinearEntity::getRtti(), RObject::PropertyHandle);
    RDimLinearEntity::PropertyProtected.generateId(RDimLinearEntity::getRtti(), RObject::PropertyProtected);
    RDimLinearEntity::PropertyWorkingSet.generateId(RDimLinearEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimLinearEntity::PropertyType.generateId(RDimLinearEntity::getRtti(), REntity::PropertyType);
    RDimLinearEntity::PropertyBlock.generateId(RDimLinearEntity::getRtti(), REntity::PropertyBlock);
    RDimLinearEntity::PropertyLayer.generateId(RDimLinearEntity::getRtti(), REntity::PropertyLayer);
    RDimLinearEntity::PropertyLinetype.generateId(RDimLinearEntity::getRtti(), REntity::PropertyLinetype);
    RDimLinearEntity::PropertyLinetypeScale.generateId(RDimLinearEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimLinearEntity::PropertyLineweight.generateId(RDimLinearEntity::getRtti(), REntity::PropertyLineweight);
    RDimLinearEntity::PropertyColor.generateId(RDimLinearEntity::getRtti(), REntity::PropertyColor);
    RDimLinearEntity::PropertyDisplayedColor.generateId(RDimLinearEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimLinearEntity::PropertyDrawOrder.generateId(RDimLinearEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimLinearEntity::PropertyMiddleOfTextX.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimLinearEntity::PropertyMiddleOfTextY.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimLinearEntity::PropertyMiddleOfTextZ.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimLinearEntity::PropertyText.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimLinearEntity::PropertyUpperTolerance.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimLinearEntity::PropertyLowerTolerance.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimLinearEntity::PropertyMeasuredValue.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    //RDimLinearEntity::PropertyDimtxt.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimtxt);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimLinearEntity::PropertyDimscale.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        RDimLinearEntity::PropertyDimlfac.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimLinearEntity::PropertyDimtxt.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimLinearEntity::PropertyDimgap.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimLinearEntity::PropertyDimasz.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimLinearEntity::PropertyDimdli.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimLinearEntity::PropertyDimexe.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimLinearEntity::PropertyDimexo.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimLinearEntity::PropertyDimtad.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimLinearEntity::PropertyDimtih.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimLinearEntity::PropertyDimtsz.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
        RDimLinearEntity::PropertyDimlunit.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
        RDimLinearEntity::PropertyDimdec.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimLinearEntity::PropertyDimdsep.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
        RDimLinearEntity::PropertyDimzin.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimzin);
        RDimLinearEntity::PropertyDimaunit.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
        RDimLinearEntity::PropertyDimadec.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimadec);
        RDimLinearEntity::PropertyDimazin.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimLinearEntity::PropertyArchTick.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimLinearEntity::PropertyDimclrt.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

//    RDimLinearEntity::PropertyLinearFactor.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyLinearFactor);
//    RDimLinearEntity::PropertyDimScale.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimScale);
    RDimLinearEntity::PropertyDimBlockName.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);
    RDimLinearEntity::PropertyAutoTextPos.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyAutoTextPos);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimLinearEntity::PropertyFontName.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimLinearEntity::PropertyArrow1Flipped.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        RDimLinearEntity::PropertyArrow2Flipped.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        RDimLinearEntity::PropertyExtLineFix.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        RDimLinearEntity::PropertyExtLineFixLength.generateId(RDimLinearEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

    RDimLinearEntity::PropertyDimensionLinePosX.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyDimensionLinePosY.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyDimensionLinePosZ.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RDimLinearEntity::PropertyExtensionPoint1X.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint1Y.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint1Z.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RDimLinearEntity::PropertyExtensionPoint2X.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint2Y.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint2Z.generateId(RDimLinearEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RDimLinearEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(getData().definitionPoint.x, value, PropertyDimensionLinePosX == propertyTypeId);
    ret = ret || RObject::setMember(getData().definitionPoint.y, value, PropertyDimensionLinePosY == propertyTypeId);
    ret = ret || RObject::setMember(getData().definitionPoint.z, value, PropertyDimensionLinePosZ == propertyTypeId);

    ret = ret || RObject::setMember(getData().extensionPoint1.x, value, PropertyExtensionPoint1X == propertyTypeId);
    ret = ret || RObject::setMember(getData().extensionPoint1.y, value, PropertyExtensionPoint1Y == propertyTypeId);
    ret = ret || RObject::setMember(getData().extensionPoint1.z, value, PropertyExtensionPoint1Z == propertyTypeId);

    ret = ret || RObject::setMember(getData().extensionPoint2.x, value, PropertyExtensionPoint2X == propertyTypeId);
    ret = ret || RObject::setMember(getData().extensionPoint2.y, value, PropertyExtensionPoint2Y == propertyTypeId);
    ret = ret || RObject::setMember(getData().extensionPoint2.z, value, PropertyExtensionPoint2Z == propertyTypeId);

    if (ret) {
        getData().update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimLinearEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyDimensionLinePosX) {
        return qMakePair(QVariant(getData().definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimensionLinePosY) {
        return qMakePair(QVariant(getData().definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimensionLinePosZ) {
        return qMakePair(QVariant(getData().definitionPoint.z), RPropertyAttributes());
    }

    else if (propertyTypeId == PropertyExtensionPoint1X) {
        return qMakePair(QVariant(getData().extensionPoint1.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint1Y) {
        return qMakePair(QVariant(getData().extensionPoint1.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint1Z) {
        return qMakePair(QVariant(getData().extensionPoint1.z), RPropertyAttributes());
    }

    else if (propertyTypeId == PropertyExtensionPoint2X) {
        return qMakePair(QVariant(getData().extensionPoint2.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint2Y) {
        return qMakePair(QVariant(getData().extensionPoint2.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint2Z) {
        return qMakePair(QVariant(getData().extensionPoint2.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimLinearEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimLinearEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", extensionPoint1: " << getData().extensionPoint1
                  << ", extensionPoint2: " << getData().extensionPoint2
                  << ")";
}
