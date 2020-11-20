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
#include "RDimAngular3PEntity.h"
#include "RExporter.h"

RPropertyTypeId RDimAngular3PEntity::PropertyCustom;
RPropertyTypeId RDimAngular3PEntity::PropertyHandle;
RPropertyTypeId RDimAngular3PEntity::PropertyProtected;
RPropertyTypeId RDimAngular3PEntity::PropertyWorkingSet;
RPropertyTypeId RDimAngular3PEntity::PropertyType;
RPropertyTypeId RDimAngular3PEntity::PropertyBlock;
RPropertyTypeId RDimAngular3PEntity::PropertyLayer;
RPropertyTypeId RDimAngular3PEntity::PropertyLinetype;
RPropertyTypeId RDimAngular3PEntity::PropertyLinetypeScale;
RPropertyTypeId RDimAngular3PEntity::PropertyLineweight;
RPropertyTypeId RDimAngular3PEntity::PropertyColor;
RPropertyTypeId RDimAngular3PEntity::PropertyDisplayedColor;
RPropertyTypeId RDimAngular3PEntity::PropertyDrawOrder;

RPropertyTypeId RDimAngular3PEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimAngular3PEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimAngular3PEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimAngular3PEntity::PropertyText;
RPropertyTypeId RDimAngular3PEntity::PropertyUpperTolerance;
RPropertyTypeId RDimAngular3PEntity::PropertyLowerTolerance;
RPropertyTypeId RDimAngular3PEntity::PropertyMeasuredValue;

RPropertyTypeId RDimAngular3PEntity::PropertyDimScale;
RPropertyTypeId RDimAngular3PEntity::PropertyDimBlockName;
RPropertyTypeId RDimAngular3PEntity::PropertyAutoTextPos;
RPropertyTypeId RDimAngular3PEntity::PropertyFontName;
RPropertyTypeId RDimAngular3PEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimAngular3PEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimAngular3PEntity::PropertyExtLineFix;
RPropertyTypeId RDimAngular3PEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimAngular3PEntity::PropertyCenterX;
RPropertyTypeId RDimAngular3PEntity::PropertyCenterY;
RPropertyTypeId RDimAngular3PEntity::PropertyCenterZ;

RPropertyTypeId RDimAngular3PEntity::PropertyExtensionLine1EndX;
RPropertyTypeId RDimAngular3PEntity::PropertyExtensionLine1EndY;
RPropertyTypeId RDimAngular3PEntity::PropertyExtensionLine1EndZ;

RPropertyTypeId RDimAngular3PEntity::PropertyExtensionLine2EndX;
RPropertyTypeId RDimAngular3PEntity::PropertyExtensionLine2EndY;
RPropertyTypeId RDimAngular3PEntity::PropertyExtensionLine2EndZ;

RPropertyTypeId RDimAngular3PEntity::PropertyDimArcPositionX;
RPropertyTypeId RDimAngular3PEntity::PropertyDimArcPositionY;
RPropertyTypeId RDimAngular3PEntity::PropertyDimArcPositionZ;



RDimAngular3PEntity::RDimAngular3PEntity(RDocument* document, const RDimAngular3PData& data) :
    RDimAngularEntity(document), data(document, data) {
}

RDimAngular3PEntity::~RDimAngular3PEntity() {
}

void RDimAngular3PEntity::init() {
    RDimAngular3PEntity::PropertyCustom.generateId(typeid(RDimAngular3PEntity), RObject::PropertyCustom);
    RDimAngular3PEntity::PropertyHandle.generateId(typeid(RDimAngular3PEntity), RObject::PropertyHandle);
    RDimAngular3PEntity::PropertyProtected.generateId(typeid(RDimAngular3PEntity), RObject::PropertyProtected);
    RDimAngular3PEntity::PropertyWorkingSet.generateId(typeid(RDimAngular3PEntity), RObject::PropertyWorkingSet);
    RDimAngular3PEntity::PropertyType.generateId(typeid(RDimAngular3PEntity), REntity::PropertyType);
    RDimAngular3PEntity::PropertyBlock.generateId(typeid(RDimAngular3PEntity), REntity::PropertyBlock);
    RDimAngular3PEntity::PropertyLayer.generateId(typeid(RDimAngular3PEntity), REntity::PropertyLayer);
    RDimAngular3PEntity::PropertyLinetype.generateId(typeid(RDimAngular3PEntity), REntity::PropertyLinetype);
    RDimAngular3PEntity::PropertyLinetypeScale.generateId(typeid(RDimAngular3PEntity), REntity::PropertyLinetypeScale);
    RDimAngular3PEntity::PropertyLineweight.generateId(typeid(RDimAngular3PEntity), REntity::PropertyLineweight);
    RDimAngular3PEntity::PropertyColor.generateId(typeid(RDimAngular3PEntity), REntity::PropertyColor);
    RDimAngular3PEntity::PropertyDisplayedColor.generateId(typeid(RDimAngular3PEntity), REntity::PropertyDisplayedColor);
    RDimAngular3PEntity::PropertyDrawOrder.generateId(typeid(RDimAngular3PEntity), REntity::PropertyDrawOrder);

    RDimAngular3PEntity::PropertyMiddleOfTextX.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAngular3PEntity::PropertyMiddleOfTextY.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAngular3PEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimAngular3PEntity::PropertyText.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyText);
    RDimAngular3PEntity::PropertyUpperTolerance.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimAngular3PEntity::PropertyLowerTolerance.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimAngular3PEntity::PropertyMeasuredValue.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyMeasuredValue);

    RDimAngular3PEntity::PropertyDimScale.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyDimScale);
    RDimAngular3PEntity::PropertyDimBlockName.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyDimBlockName);
    RDimAngular3PEntity::PropertyAutoTextPos.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimAngular3PEntity::PropertyFontName.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyFontName);
    RDimAngular3PEntity::PropertyArrow1Flipped.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimAngular3PEntity::PropertyArrow2Flipped.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimAngular3PEntity::PropertyExtLineFix.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyExtLineFix);
    RDimAngular3PEntity::PropertyExtLineFixLength.generateId(typeid(RDimAngular3PEntity), RDimensionEntity::PropertyExtLineFixLength);

//    RDimAngular3PEntity::PropertyCenterX.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimAngular3PEntity::PropertyCenterY.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimAngular3PEntity::PropertyCenterZ.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular3PEntity::PropertyCenterX.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyCenterX);
    RDimAngular3PEntity::PropertyCenterY.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyCenterY);
    RDimAngular3PEntity::PropertyCenterZ.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyCenterZ);

    RDimAngular3PEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyExtensionLine1EndX);
    RDimAngular3PEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyExtensionLine1EndY);
    RDimAngular3PEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyExtensionLine1EndZ);

//    RDimAngular3PEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true);
//    RDimAngular3PEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
//    RDimAngular3PEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimAngular3PEntity::PropertyExtensionLine2EndX.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyExtensionLine2EndX);
    RDimAngular3PEntity::PropertyExtensionLine2EndY.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyExtensionLine2EndY);
    RDimAngular3PEntity::PropertyExtensionLine2EndZ.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyExtensionLine2EndZ);

//    RDimAngular3PEntity::PropertyDimArcPositionX.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimAngular3PEntity::PropertyDimArcPositionY.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimAngular3PEntity::PropertyDimArcPositionZ.generateId(typeid(RDimAngular3PEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular3PEntity::PropertyDimArcPositionX.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyDimArcPositionX);
    RDimAngular3PEntity::PropertyDimArcPositionY.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyDimArcPositionY);
    RDimAngular3PEntity::PropertyDimArcPositionZ.generateId(typeid(RDimAngular3PEntity), RDimAngularEntity::PropertyDimArcPositionZ);
}

bool RDimAngular3PEntity::setProperty(RPropertyTypeId propertyTypeId,
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

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimAngular3PEntity::getProperty(
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

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimAngular3PEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimAngular3PEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", center: " << getData().center
                  << ")";
}
