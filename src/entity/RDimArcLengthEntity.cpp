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
#include "RExporter.h"

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

RPropertyTypeId RDimArcLengthEntity::PropertyLinearFactor;
RPropertyTypeId RDimArcLengthEntity::PropertyDimScale;
RPropertyTypeId RDimArcLengthEntity::PropertyDimBlockName;
RPropertyTypeId RDimArcLengthEntity::PropertyAutoTextPos;
RPropertyTypeId RDimArcLengthEntity::PropertyMeasuredValue;
RPropertyTypeId RDimArcLengthEntity::PropertyFontName;
RPropertyTypeId RDimArcLengthEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimArcLengthEntity::PropertyArrow2Flipped;

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
    RDimArcLengthEntity::PropertyCustom.generateId(typeid(RDimArcLengthEntity), RObject::PropertyCustom);
    RDimArcLengthEntity::PropertyHandle.generateId(typeid(RDimArcLengthEntity), RObject::PropertyHandle);
    RDimArcLengthEntity::PropertyProtected.generateId(typeid(RDimArcLengthEntity), RObject::PropertyProtected);
    RDimArcLengthEntity::PropertyWorkingSet.generateId(typeid(RDimArcLengthEntity), RObject::PropertyWorkingSet);
    RDimArcLengthEntity::PropertyType.generateId(typeid(RDimArcLengthEntity), REntity::PropertyType);
    RDimArcLengthEntity::PropertyBlock.generateId(typeid(RDimArcLengthEntity), REntity::PropertyBlock);
    RDimArcLengthEntity::PropertyLayer.generateId(typeid(RDimArcLengthEntity), REntity::PropertyLayer);
    RDimArcLengthEntity::PropertyLinetype.generateId(typeid(RDimArcLengthEntity), REntity::PropertyLinetype);
    RDimArcLengthEntity::PropertyLinetypeScale.generateId(typeid(RDimArcLengthEntity), REntity::PropertyLinetypeScale);
    RDimArcLengthEntity::PropertyLineweight.generateId(typeid(RDimArcLengthEntity), REntity::PropertyLineweight);
    RDimArcLengthEntity::PropertyColor.generateId(typeid(RDimArcLengthEntity), REntity::PropertyColor);
    RDimArcLengthEntity::PropertyDisplayedColor.generateId(typeid(RDimArcLengthEntity), REntity::PropertyDisplayedColor);
    RDimArcLengthEntity::PropertyDrawOrder.generateId(typeid(RDimArcLengthEntity), REntity::PropertyDrawOrder);

    RDimArcLengthEntity::PropertyMiddleOfTextX.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimArcLengthEntity::PropertyMiddleOfTextY.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimArcLengthEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimArcLengthEntity::PropertyText.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyText);
    RDimArcLengthEntity::PropertyUpperTolerance.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimArcLengthEntity::PropertyLowerTolerance.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimArcLengthEntity::PropertyMeasuredValue.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyMeasuredValue);

    RDimArcLengthEntity::PropertyLinearFactor.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyLinearFactor);
    RDimArcLengthEntity::PropertyDimScale.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyDimScale);
    RDimArcLengthEntity::PropertyDimBlockName.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyDimBlockName);
    RDimArcLengthEntity::PropertyAutoTextPos.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimArcLengthEntity::PropertyFontName.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyFontName);
    RDimArcLengthEntity::PropertyArrow1Flipped.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimArcLengthEntity::PropertyArrow2Flipped.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimArcLengthEntity::PropertyExtLineFix.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyExtLineFix);
    RDimArcLengthEntity::PropertyExtLineFixLength.generateId(typeid(RDimArcLengthEntity), RDimensionEntity::PropertyExtLineFixLength);

//    RDimArcLengthEntity::PropertyCenterX.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyCenterY.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyCenterZ.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimArcLengthEntity::PropertyCenterX.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyCenterX);
    RDimArcLengthEntity::PropertyCenterY.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyCenterY);
    RDimArcLengthEntity::PropertyCenterZ.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyCenterZ);

    RDimArcLengthEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyExtensionLine1EndX);
    RDimArcLengthEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyExtensionLine1EndY);
    RDimArcLengthEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyExtensionLine1EndZ);

//    RDimArcLengthEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true);
//    RDimArcLengthEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
//    RDimArcLengthEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimArcLengthEntity::PropertyExtensionLine2EndX.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyExtensionLine2EndX);
    RDimArcLengthEntity::PropertyExtensionLine2EndY.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyExtensionLine2EndY);
    RDimArcLengthEntity::PropertyExtensionLine2EndZ.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyExtensionLine2EndZ);

//    RDimArcLengthEntity::PropertyDimArcPositionX.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyDimArcPositionY.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimArcLengthEntity::PropertyDimArcPositionZ.generateId(typeid(RDimArcLengthEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimArcLengthEntity::PropertyDimArcPositionX.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyDimArcPositionX);
    RDimArcLengthEntity::PropertyDimArcPositionY.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyDimArcPositionY);
    RDimArcLengthEntity::PropertyDimArcPositionZ.generateId(typeid(RDimArcLengthEntity), RDimAngularEntity::PropertyDimArcPositionZ);

    RDimArcLengthEntity::PropertyDimArcSymbolType.generateId(typeid(RDimArcLengthEntity), "", QT_TRANSLATE_NOOP("REntity", "Arc Symbol Type"));
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
