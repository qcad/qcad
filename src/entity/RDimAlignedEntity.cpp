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
#include "RExporter.h"

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

RPropertyTypeId RDimAlignedEntity::PropertyLinearFactor;
RPropertyTypeId RDimAlignedEntity::PropertyDimScale;
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
    RDimAlignedEntity::PropertyCustom.generateId(typeid(RDimAlignedEntity), RObject::PropertyCustom);
    RDimAlignedEntity::PropertyHandle.generateId(typeid(RDimAlignedEntity), RObject::PropertyHandle);
    RDimAlignedEntity::PropertyProtected.generateId(typeid(RDimAlignedEntity), RObject::PropertyProtected);
    RDimAlignedEntity::PropertyWorkingSet.generateId(typeid(RDimAlignedEntity), RObject::PropertyWorkingSet);
    RDimAlignedEntity::PropertyType.generateId(typeid(RDimAlignedEntity), REntity::PropertyType);
    RDimAlignedEntity::PropertyBlock.generateId(typeid(RDimAlignedEntity), REntity::PropertyBlock);
    RDimAlignedEntity::PropertyLayer.generateId(typeid(RDimAlignedEntity), REntity::PropertyLayer);
    RDimAlignedEntity::PropertyLinetype.generateId(typeid(RDimAlignedEntity), REntity::PropertyLinetype);
    RDimAlignedEntity::PropertyLinetypeScale.generateId(typeid(RDimAlignedEntity), REntity::PropertyLinetypeScale);
    RDimAlignedEntity::PropertyLineweight.generateId(typeid(RDimAlignedEntity), REntity::PropertyLineweight);
    RDimAlignedEntity::PropertyColor.generateId(typeid(RDimAlignedEntity), REntity::PropertyColor);
    RDimAlignedEntity::PropertyDisplayedColor.generateId(typeid(RDimAlignedEntity), REntity::PropertyDisplayedColor);
    RDimAlignedEntity::PropertyDrawOrder.generateId(typeid(RDimAlignedEntity), REntity::PropertyDrawOrder);

    RDimAlignedEntity::PropertyMiddleOfTextX.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAlignedEntity::PropertyMiddleOfTextY.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAlignedEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimAlignedEntity::PropertyText.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyText);
    RDimAlignedEntity::PropertyUpperTolerance.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimAlignedEntity::PropertyLowerTolerance.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimAlignedEntity::PropertyMeasuredValue.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyMeasuredValue);

    RDimAlignedEntity::PropertyLinearFactor.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyLinearFactor);
    RDimAlignedEntity::PropertyDimScale.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyDimScale);
    RDimAlignedEntity::PropertyDimBlockName.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyDimBlockName);
    RDimAlignedEntity::PropertyAutoTextPos.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimAlignedEntity::PropertyFontName.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyFontName);
    RDimAlignedEntity::PropertyArrow1Flipped.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimAlignedEntity::PropertyArrow2Flipped.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimAlignedEntity::PropertyExtLineFix.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyExtLineFix);
    RDimAlignedEntity::PropertyExtLineFixLength.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyExtLineFixLength);

    RDimAlignedEntity::PropertyDimensionLinePosX.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyDimensionLinePosX);
    RDimAlignedEntity::PropertyDimensionLinePosY.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyDimensionLinePosY);
    RDimAlignedEntity::PropertyDimensionLinePosZ.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyDimensionLinePosZ);

    RDimAlignedEntity::PropertyExtensionPoint1X.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyExtensionPoint1X);
    RDimAlignedEntity::PropertyExtensionPoint1Y.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyExtensionPoint1Y);
    RDimAlignedEntity::PropertyExtensionPoint1Z.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyExtensionPoint1Z);

    RDimAlignedEntity::PropertyExtensionPoint2X.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyExtensionPoint2X);
    RDimAlignedEntity::PropertyExtensionPoint2Y.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyExtensionPoint2Y);
    RDimAlignedEntity::PropertyExtensionPoint2Z.generateId(typeid(RDimAlignedEntity), RDimLinearEntity::PropertyExtensionPoint2Z);
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
