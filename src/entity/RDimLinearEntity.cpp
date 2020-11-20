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

RPropertyTypeId RDimLinearEntity::PropertyLinearFactor;
RPropertyTypeId RDimLinearEntity::PropertyDimScale;
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
    RDimLinearEntity::PropertyCustom.generateId(typeid(RDimLinearEntity), RObject::PropertyCustom);
    RDimLinearEntity::PropertyHandle.generateId(typeid(RDimLinearEntity), RObject::PropertyHandle);
    RDimLinearEntity::PropertyProtected.generateId(typeid(RDimLinearEntity), RObject::PropertyProtected);
    RDimLinearEntity::PropertyWorkingSet.generateId(typeid(RDimLinearEntity), RObject::PropertyWorkingSet);
    RDimLinearEntity::PropertyType.generateId(typeid(RDimLinearEntity), REntity::PropertyType);
    RDimLinearEntity::PropertyBlock.generateId(typeid(RDimLinearEntity), REntity::PropertyBlock);
    RDimLinearEntity::PropertyLayer.generateId(typeid(RDimLinearEntity), REntity::PropertyLayer);
    RDimLinearEntity::PropertyLinetype.generateId(typeid(RDimLinearEntity), REntity::PropertyLinetype);
    RDimLinearEntity::PropertyLinetypeScale.generateId(typeid(RDimLinearEntity), REntity::PropertyLinetypeScale);
    RDimLinearEntity::PropertyLineweight.generateId(typeid(RDimLinearEntity), REntity::PropertyLineweight);
    RDimLinearEntity::PropertyColor.generateId(typeid(RDimLinearEntity), REntity::PropertyColor);
    RDimLinearEntity::PropertyDisplayedColor.generateId(typeid(RDimLinearEntity), REntity::PropertyDisplayedColor);
    RDimLinearEntity::PropertyDrawOrder.generateId(typeid(RDimLinearEntity), REntity::PropertyDrawOrder);

    RDimLinearEntity::PropertyMiddleOfTextX.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimLinearEntity::PropertyMiddleOfTextY.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimLinearEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimLinearEntity::PropertyText.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyText);
    RDimLinearEntity::PropertyUpperTolerance.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimLinearEntity::PropertyLowerTolerance.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyLowerTolerance);

    RDimLinearEntity::PropertyLinearFactor.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyLinearFactor);
    RDimLinearEntity::PropertyDimScale.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyDimScale);
    RDimLinearEntity::PropertyDimBlockName.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyDimBlockName);
    RDimLinearEntity::PropertyAutoTextPos.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimLinearEntity::PropertyFontName.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyFontName);
    RDimLinearEntity::PropertyArrow1Flipped.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimLinearEntity::PropertyArrow2Flipped.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimLinearEntity::PropertyExtLineFix.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyExtLineFix);
    RDimLinearEntity::PropertyExtLineFixLength.generateId(typeid(RDimLinearEntity), RDimensionEntity::PropertyExtLineFixLength);

    RDimLinearEntity::PropertyDimensionLinePosX.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyDimensionLinePosY.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyDimensionLinePosZ.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RDimLinearEntity::PropertyExtensionPoint1X.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint1Y.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint1Z.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RDimLinearEntity::PropertyExtensionPoint2X.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint2Y.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimLinearEntity::PropertyExtensionPoint2Z.generateId(typeid(RDimLinearEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
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
