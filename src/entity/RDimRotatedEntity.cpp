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
#include "RDimRotatedEntity.h"
#include "RExporter.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimRotatedEntity::PropertyCustom;
RPropertyTypeId RDimRotatedEntity::PropertyHandle;
RPropertyTypeId RDimRotatedEntity::PropertyProtected;
RPropertyTypeId RDimRotatedEntity::PropertyWorkingSet;
RPropertyTypeId RDimRotatedEntity::PropertyType;
RPropertyTypeId RDimRotatedEntity::PropertyBlock;
RPropertyTypeId RDimRotatedEntity::PropertyLayer;
RPropertyTypeId RDimRotatedEntity::PropertyLinetype;
RPropertyTypeId RDimRotatedEntity::PropertyLinetypeScale;
RPropertyTypeId RDimRotatedEntity::PropertyLineweight;
RPropertyTypeId RDimRotatedEntity::PropertyColor;
RPropertyTypeId RDimRotatedEntity::PropertyDisplayedColor;
RPropertyTypeId RDimRotatedEntity::PropertyDrawOrder;

RPropertyTypeId RDimRotatedEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimRotatedEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimRotatedEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimRotatedEntity::PropertyText;
RPropertyTypeId RDimRotatedEntity::PropertyUpperTolerance;
RPropertyTypeId RDimRotatedEntity::PropertyLowerTolerance;
RPropertyTypeId RDimRotatedEntity::PropertyMeasuredValue;

RPropertyTypeId RDimRotatedEntity::PropertyDimscale;
RPropertyTypeId RDimRotatedEntity::PropertyDimlfac;
RPropertyTypeId RDimRotatedEntity::PropertyDimtxt;
RPropertyTypeId RDimRotatedEntity::PropertyDimgap;
RPropertyTypeId RDimRotatedEntity::PropertyDimasz;
//RPropertyTypeId RDimRotatedEntity::PropertyDimdli;
RPropertyTypeId RDimRotatedEntity::PropertyDimexe;
RPropertyTypeId RDimRotatedEntity::PropertyDimexo;
RPropertyTypeId RDimRotatedEntity::PropertyDimtad;
RPropertyTypeId RDimRotatedEntity::PropertyDimtih;
RPropertyTypeId RDimRotatedEntity::PropertyDimtsz;
RPropertyTypeId RDimRotatedEntity::PropertyDimlunit;
RPropertyTypeId RDimRotatedEntity::PropertyDimdec;
RPropertyTypeId RDimRotatedEntity::PropertyDimdsep;
RPropertyTypeId RDimRotatedEntity::PropertyDimzin;
//RPropertyTypeId RDimRotatedEntity::PropertyDimaunit;
//RPropertyTypeId RDimRotatedEntity::PropertyDimadec;
//RPropertyTypeId RDimRotatedEntity::PropertyDimazin;
RPropertyTypeId RDimRotatedEntity::PropertyArchTick;
RPropertyTypeId RDimRotatedEntity::PropertyDimclrt;

//RPropertyTypeId RDimRotatedEntity::PropertyLinearFactor;
//RPropertyTypeId RDimRotatedEntity::PropertyDimScale;
RPropertyTypeId RDimRotatedEntity::PropertyDimBlockName;
RPropertyTypeId RDimRotatedEntity::PropertyAutoTextPos;
RPropertyTypeId RDimRotatedEntity::PropertyFontName;
RPropertyTypeId RDimRotatedEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimRotatedEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimRotatedEntity::PropertyExtLineFix;
RPropertyTypeId RDimRotatedEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimRotatedEntity::PropertyDimensionLinePosX;
RPropertyTypeId RDimRotatedEntity::PropertyDimensionLinePosY;
RPropertyTypeId RDimRotatedEntity::PropertyDimensionLinePosZ;

RPropertyTypeId RDimRotatedEntity::PropertyExtensionPoint1X;
RPropertyTypeId RDimRotatedEntity::PropertyExtensionPoint1Y;
RPropertyTypeId RDimRotatedEntity::PropertyExtensionPoint1Z;

RPropertyTypeId RDimRotatedEntity::PropertyExtensionPoint2X;
RPropertyTypeId RDimRotatedEntity::PropertyExtensionPoint2Y;
RPropertyTypeId RDimRotatedEntity::PropertyExtensionPoint2Z;

RPropertyTypeId RDimRotatedEntity::PropertyAngle;


RDimRotatedEntity::RDimRotatedEntity(RDocument* document, const RDimRotatedData& data) :
    RDimLinearEntity(document), data(document, data) {
}

RDimRotatedEntity::~RDimRotatedEntity() {
}

void RDimRotatedEntity::init() {
    RDimRotatedEntity::PropertyCustom.generateId(RDimRotatedEntity::getRtti(), RObject::PropertyCustom);
    RDimRotatedEntity::PropertyHandle.generateId(RDimRotatedEntity::getRtti(), RObject::PropertyHandle);
    RDimRotatedEntity::PropertyProtected.generateId(RDimRotatedEntity::getRtti(), RObject::PropertyProtected);
    RDimRotatedEntity::PropertyWorkingSet.generateId(RDimRotatedEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimRotatedEntity::PropertyType.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyType);
    RDimRotatedEntity::PropertyBlock.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyBlock);
    RDimRotatedEntity::PropertyLayer.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyLayer);
    RDimRotatedEntity::PropertyLinetype.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyLinetype);
    RDimRotatedEntity::PropertyLinetypeScale.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimRotatedEntity::PropertyLineweight.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyLineweight);
    RDimRotatedEntity::PropertyColor.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyColor);
    RDimRotatedEntity::PropertyDisplayedColor.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimRotatedEntity::PropertyDrawOrder.generateId(RDimRotatedEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimRotatedEntity::PropertyMiddleOfTextX.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimRotatedEntity::PropertyMiddleOfTextY.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimRotatedEntity::PropertyMiddleOfTextZ.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimRotatedEntity::PropertyText.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimRotatedEntity::PropertyUpperTolerance.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimRotatedEntity::PropertyLowerTolerance.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimRotatedEntity::PropertyMeasuredValue.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    //RDimRotatedEntity::PropertyDimtxt.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimtxt);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimRotatedEntity::PropertyDimscale.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        RDimRotatedEntity::PropertyDimlfac.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimRotatedEntity::PropertyDimtxt.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimRotatedEntity::PropertyDimgap.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimRotatedEntity::PropertyDimasz.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimRotatedEntity::PropertyDimdli.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimRotatedEntity::PropertyDimexe.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimRotatedEntity::PropertyDimexo.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimRotatedEntity::PropertyDimtad.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimRotatedEntity::PropertyDimtih.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimRotatedEntity::PropertyDimtsz.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
        RDimRotatedEntity::PropertyDimlunit.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
        RDimRotatedEntity::PropertyDimdec.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimRotatedEntity::PropertyDimdsep.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
        RDimRotatedEntity::PropertyDimzin.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimzin);
    //    RDimRotatedEntity::PropertyDimaunit.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
    //    RDimRotatedEntity::PropertyDimadec.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimadec);
    //    RDimRotatedEntity::PropertyDimazin.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimRotatedEntity::PropertyArchTick.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimRotatedEntity::PropertyDimclrt.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

//    RDimRotatedEntity::PropertyLinearFactor.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyLinearFactor);
//    RDimRotatedEntity::PropertyDimScale.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimScale);
    RDimRotatedEntity::PropertyDimBlockName.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);
    RDimRotatedEntity::PropertyAutoTextPos.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyAutoTextPos);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimRotatedEntity::PropertyFontName.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimRotatedEntity::PropertyArrow1Flipped.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        RDimRotatedEntity::PropertyArrow2Flipped.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        RDimRotatedEntity::PropertyExtLineFix.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        RDimRotatedEntity::PropertyExtLineFixLength.generateId(RDimRotatedEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

    RDimRotatedEntity::PropertyDimensionLinePosX.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyDimensionLinePosX);
    RDimRotatedEntity::PropertyDimensionLinePosY.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyDimensionLinePosY);
    RDimRotatedEntity::PropertyDimensionLinePosZ.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyDimensionLinePosZ);

    RDimRotatedEntity::PropertyExtensionPoint1X.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint1X);
    RDimRotatedEntity::PropertyExtensionPoint1Y.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint1Y);
    RDimRotatedEntity::PropertyExtensionPoint1Z.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint1Z);

    RDimRotatedEntity::PropertyExtensionPoint2X.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint2X);
    RDimRotatedEntity::PropertyExtensionPoint2Y.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint2Y);
    RDimRotatedEntity::PropertyExtensionPoint2Z.generateId(RDimRotatedEntity::getRtti(), RDimLinearEntity::PropertyExtensionPoint2Z);

    RDimRotatedEntity::PropertyAngle.generateId(RDimRotatedEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Dimension Angle"), false, RPropertyAttributes::Geometry);
}

bool RDimRotatedEntity::setProperty(RPropertyTypeId propertyTypeId,
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

    ret = ret || RObject::setMember(data.rotation, value, PropertyAngle == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimRotatedEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

//    qDebug() << "getProperty: " << propertyTypeId.getPropertyGroupTitle() << propertyTypeId.getPropertyTitle();

//    if (propertyTypeId == PropertyDimensionLinePosX) {
//        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyDimensionLinePosY) {
//        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyDimensionLinePosZ) {
//        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());

//    } else if (propertyTypeId == PropertyExtensionPoint1X) {
//        return qMakePair(QVariant(data.extensionPoint1.x), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint1Y) {
//        return qMakePair(QVariant(data.extensionPoint1.y), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint1Z) {
//        return qMakePair(QVariant(data.extensionPoint1.z), RPropertyAttributes());
//    }

//    else if (propertyTypeId == PropertyExtensionPoint2X) {
//        return qMakePair(QVariant(data.extensionPoint2.x), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint2Y) {
//        return qMakePair(QVariant(data.extensionPoint2.y), RPropertyAttributes());
//    } else if (propertyTypeId == PropertyExtensionPoint2Z) {
//        return qMakePair(QVariant(data.extensionPoint2.z), RPropertyAttributes());
    if (propertyTypeId == PropertyAngle) {
        return qMakePair(QVariant(data.rotation), RPropertyAttributes(RPropertyAttributes::Angle));
    }

    //qDebug() << "getProperty:" << propertyTypeId.getPropertyTitle();

    QPair<QVariant, RPropertyAttributes> ret = RDimLinearEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
    //qDebug() << "  val:" << ret.first;
    return ret;
}

void RDimRotatedEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimRotatedEntity(";
    RDimLinearEntity::print(dbg);
    dbg.nospace() << ", extensionPoint1: " << getData().extensionPoint1
                  << ", extensionPoint2: " << getData().extensionPoint2
                  << ", angle: " << getData().rotation
                  << ")";
}
