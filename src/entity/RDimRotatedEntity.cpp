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
RPropertyTypeId RDimRotatedEntity::PropertyDimaunit;
RPropertyTypeId RDimRotatedEntity::PropertyDimadec;
RPropertyTypeId RDimRotatedEntity::PropertyDimazin;
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
    RDimRotatedEntity::PropertyCustom.generateId(typeid(RDimRotatedEntity), RObject::PropertyCustom);
    RDimRotatedEntity::PropertyHandle.generateId(typeid(RDimRotatedEntity), RObject::PropertyHandle);
    RDimRotatedEntity::PropertyProtected.generateId(typeid(RDimRotatedEntity), RObject::PropertyProtected);
    RDimRotatedEntity::PropertyWorkingSet.generateId(typeid(RDimRotatedEntity), RObject::PropertyWorkingSet);
    RDimRotatedEntity::PropertyType.generateId(typeid(RDimRotatedEntity), REntity::PropertyType);
    RDimRotatedEntity::PropertyBlock.generateId(typeid(RDimRotatedEntity), REntity::PropertyBlock);
    RDimRotatedEntity::PropertyLayer.generateId(typeid(RDimRotatedEntity), REntity::PropertyLayer);
    RDimRotatedEntity::PropertyLinetype.generateId(typeid(RDimRotatedEntity), REntity::PropertyLinetype);
    RDimRotatedEntity::PropertyLinetypeScale.generateId(typeid(RDimRotatedEntity), REntity::PropertyLinetypeScale);
    RDimRotatedEntity::PropertyLineweight.generateId(typeid(RDimRotatedEntity), REntity::PropertyLineweight);
    RDimRotatedEntity::PropertyColor.generateId(typeid(RDimRotatedEntity), REntity::PropertyColor);
    RDimRotatedEntity::PropertyDisplayedColor.generateId(typeid(RDimRotatedEntity), REntity::PropertyDisplayedColor);
    RDimRotatedEntity::PropertyDrawOrder.generateId(typeid(RDimRotatedEntity), REntity::PropertyDrawOrder);

    RDimRotatedEntity::PropertyMiddleOfTextX.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimRotatedEntity::PropertyMiddleOfTextY.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimRotatedEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimRotatedEntity::PropertyText.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyText);
    RDimRotatedEntity::PropertyUpperTolerance.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimRotatedEntity::PropertyLowerTolerance.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimRotatedEntity::PropertyMeasuredValue.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyMeasuredValue);

    //RDimRotatedEntity::PropertyDimtxt.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimtxt);

    RDimRotatedEntity::PropertyDimscale.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimscale);
    RDimRotatedEntity::PropertyDimlfac.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimlfac);
    RDimRotatedEntity::PropertyDimtxt.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimtxt);
    RDimRotatedEntity::PropertyDimgap.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimgap);
    RDimRotatedEntity::PropertyDimasz.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimasz);
    //RDimRotatedEntity::PropertyDimdli.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimdli);
    RDimRotatedEntity::PropertyDimexe.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimexe);
    RDimRotatedEntity::PropertyDimexo.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimexo);
    RDimRotatedEntity::PropertyDimtad.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimtad);
    RDimRotatedEntity::PropertyDimtih.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimtih);
    RDimRotatedEntity::PropertyDimtsz.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimtsz);
    RDimRotatedEntity::PropertyDimlunit.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimlunit);
    RDimRotatedEntity::PropertyDimdec.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimdec);
    RDimRotatedEntity::PropertyDimdsep.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimdsep);
    RDimRotatedEntity::PropertyDimzin.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimzin);
    RDimRotatedEntity::PropertyDimaunit.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimaunit);
    RDimRotatedEntity::PropertyDimadec.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimadec);
    RDimRotatedEntity::PropertyDimazin.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimazin);
    RDimRotatedEntity::PropertyArchTick.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyArchTick);
    RDimRotatedEntity::PropertyDimclrt.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimclrt);

//    RDimRotatedEntity::PropertyLinearFactor.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyLinearFactor);
//    RDimRotatedEntity::PropertyDimScale.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimScale);
    RDimRotatedEntity::PropertyDimBlockName.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyDimBlockName);
    RDimRotatedEntity::PropertyAutoTextPos.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimRotatedEntity::PropertyFontName.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyFontName);
    RDimRotatedEntity::PropertyArrow1Flipped.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimRotatedEntity::PropertyArrow2Flipped.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimRotatedEntity::PropertyExtLineFix.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyExtLineFix);
    RDimRotatedEntity::PropertyExtLineFixLength.generateId(typeid(RDimRotatedEntity), RDimensionEntity::PropertyExtLineFixLength);

    RDimRotatedEntity::PropertyDimensionLinePosX.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyDimensionLinePosX);
    RDimRotatedEntity::PropertyDimensionLinePosY.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyDimensionLinePosY);
    RDimRotatedEntity::PropertyDimensionLinePosZ.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyDimensionLinePosZ);

    RDimRotatedEntity::PropertyExtensionPoint1X.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyExtensionPoint1X);
    RDimRotatedEntity::PropertyExtensionPoint1Y.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyExtensionPoint1Y);
    RDimRotatedEntity::PropertyExtensionPoint1Z.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyExtensionPoint1Z);

    RDimRotatedEntity::PropertyExtensionPoint2X.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyExtensionPoint2X);
    RDimRotatedEntity::PropertyExtensionPoint2Y.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyExtensionPoint2Y);
    RDimRotatedEntity::PropertyExtensionPoint2Z.generateId(typeid(RDimRotatedEntity), RDimLinearEntity::PropertyExtensionPoint2Z);

    RDimRotatedEntity::PropertyAngle.generateId(typeid(RDimRotatedEntity), "", QT_TRANSLATE_NOOP("REntity", "Dimension Angle"), false, RPropertyAttributes::Geometry);
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
