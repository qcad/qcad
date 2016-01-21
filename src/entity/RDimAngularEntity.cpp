/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include "RDimAngularEntity.h"
#include "RExporter.h"

RPropertyTypeId RDimAngularEntity::PropertyCustom;
RPropertyTypeId RDimAngularEntity::PropertyHandle;
RPropertyTypeId RDimAngularEntity::PropertyProtected;
RPropertyTypeId RDimAngularEntity::PropertyType;
RPropertyTypeId RDimAngularEntity::PropertyBlock;
RPropertyTypeId RDimAngularEntity::PropertyLayer;
RPropertyTypeId RDimAngularEntity::PropertyLinetype;
RPropertyTypeId RDimAngularEntity::PropertyLinetypeScale;
RPropertyTypeId RDimAngularEntity::PropertyLineweight;
RPropertyTypeId RDimAngularEntity::PropertyColor;
RPropertyTypeId RDimAngularEntity::PropertyDisplayedColor;
RPropertyTypeId RDimAngularEntity::PropertyDrawOrder;

RPropertyTypeId RDimAngularEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimAngularEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimAngularEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimAngularEntity::PropertyText;
RPropertyTypeId RDimAngularEntity::PropertyUpperTolerance;
RPropertyTypeId RDimAngularEntity::PropertyLowerTolerance;
RPropertyTypeId RDimAngularEntity::PropertyMeasuredValue;
RPropertyTypeId RDimAngularEntity::PropertyFontName;

RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1StartX;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1StartY;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1StartZ;

RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1EndX;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1EndY;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1EndZ;

RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2StartX;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2StartY;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2StartZ;

RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2EndX;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2EndY;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2EndZ;

RPropertyTypeId RDimAngularEntity::PropertyDimArcPositionX;
RPropertyTypeId RDimAngularEntity::PropertyDimArcPositionY;
RPropertyTypeId RDimAngularEntity::PropertyDimArcPositionZ;



RDimAngularEntity::RDimAngularEntity(RDocument* document, const RDimAngularData& data, RObject::Id objectId) :
    RDimensionEntity(document, objectId), data(document, data) {
}

RDimAngularEntity::~RDimAngularEntity() {
}

void RDimAngularEntity::init() {
    RDimAngularEntity::PropertyCustom.generateId(typeid(RDimAngularEntity), RObject::PropertyCustom);
    RDimAngularEntity::PropertyHandle.generateId(typeid(RDimAngularEntity), RObject::PropertyHandle);
    RDimAngularEntity::PropertyProtected.generateId(typeid(RDimAngularEntity), RObject::PropertyProtected);
    RDimAngularEntity::PropertyType.generateId(typeid(RDimAngularEntity), REntity::PropertyType);
    RDimAngularEntity::PropertyBlock.generateId(typeid(RDimAngularEntity), REntity::PropertyBlock);
    RDimAngularEntity::PropertyLayer.generateId(typeid(RDimAngularEntity), REntity::PropertyLayer);
    RDimAngularEntity::PropertyLinetype.generateId(typeid(RDimAngularEntity), REntity::PropertyLinetype);
    RDimAngularEntity::PropertyLinetypeScale.generateId(typeid(RDimAngularEntity), REntity::PropertyLinetypeScale);
    RDimAngularEntity::PropertyLineweight.generateId(typeid(RDimAngularEntity), REntity::PropertyLineweight);
    RDimAngularEntity::PropertyColor.generateId(typeid(RDimAngularEntity), REntity::PropertyColor);
    RDimAngularEntity::PropertyDisplayedColor.generateId(typeid(RDimAngularEntity), REntity::PropertyDisplayedColor);
    RDimAngularEntity::PropertyDrawOrder.generateId(typeid(RDimAngularEntity), REntity::PropertyDrawOrder);

    RDimAngularEntity::PropertyMiddleOfTextX.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAngularEntity::PropertyMiddleOfTextY.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAngularEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimAngularEntity::PropertyText.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyText);
    RDimAngularEntity::PropertyUpperTolerance.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimAngularEntity::PropertyLowerTolerance.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimAngularEntity::PropertyMeasuredValue.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyMeasuredValue);
    RDimAngularEntity::PropertyFontName.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyFontName);

    RDimAngularEntity::PropertyExtensionLine1StartX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "X"), true);
    RDimAngularEntity::PropertyExtensionLine1StartY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
    RDimAngularEntity::PropertyExtensionLine1StartZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimAngularEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true);
    RDimAngularEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
    RDimAngularEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimAngularEntity::PropertyExtensionLine2StartX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "X"), true);
    RDimAngularEntity::PropertyExtensionLine2StartY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
    RDimAngularEntity::PropertyExtensionLine2StartZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimAngularEntity::PropertyExtensionLine2EndX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "X"), true);
    RDimAngularEntity::PropertyExtensionLine2EndY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
    RDimAngularEntity::PropertyExtensionLine2EndZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimAngularEntity::PropertyDimArcPositionX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "X"), true);
    RDimAngularEntity::PropertyDimArcPositionY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
    RDimAngularEntity::PropertyDimArcPositionZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Z"), true);
}

bool RDimAngularEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.extensionLine1Start.x, value, PropertyExtensionLine1StartX == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine1Start.y, value, PropertyExtensionLine1StartY == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine1Start.z, value, PropertyExtensionLine1StartZ == propertyTypeId);

    ret = ret || RObject::setMember(data.extensionLine1End.x, value, PropertyExtensionLine1EndX == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine1End.y, value, PropertyExtensionLine1EndY == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine1End.z, value, PropertyExtensionLine1EndZ == propertyTypeId);

    ret = ret || RObject::setMember(data.extensionLine2Start.x, value, PropertyExtensionLine2StartX == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine2Start.y, value, PropertyExtensionLine2StartY == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionLine2Start.z, value, PropertyExtensionLine2StartZ == propertyTypeId);

    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyExtensionLine2EndX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyExtensionLine2EndY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyExtensionLine2EndZ == propertyTypeId);

    ret = ret || RObject::setMember(data.dimArcPosition.x, value, PropertyDimArcPositionX == propertyTypeId);
    ret = ret || RObject::setMember(data.dimArcPosition.y, value, PropertyDimArcPositionY == propertyTypeId);
    ret = ret || RObject::setMember(data.dimArcPosition.z, value, PropertyDimArcPositionZ == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimAngularEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyExtensionLine1StartX) {
        return qMakePair(QVariant(data.extensionLine1Start.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine1StartY) {
        return qMakePair(QVariant(data.extensionLine1Start.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine1StartZ) {
        return qMakePair(QVariant(data.extensionLine1Start.z), RPropertyAttributes());
    }

      else if (propertyTypeId == PropertyExtensionLine1EndX) {
        return qMakePair(QVariant(data.extensionLine1End.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine1EndY) {
        return qMakePair(QVariant(data.extensionLine1End.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine1EndZ) {
        return qMakePair(QVariant(data.extensionLine1End.z), RPropertyAttributes());
    }

      else if (propertyTypeId == PropertyExtensionLine2StartX) {
        return qMakePair(QVariant(data.extensionLine2Start.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine2StartY) {
        return qMakePair(QVariant(data.extensionLine2Start.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine2StartZ) {
        return qMakePair(QVariant(data.extensionLine2Start.z), RPropertyAttributes());
    }

      else if (propertyTypeId == PropertyExtensionLine2EndX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine2EndY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionLine2EndZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    }

      else if (propertyTypeId == PropertyDimArcPositionX) {
        return qMakePair(QVariant(data.dimArcPosition.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimArcPositionY) {
        return qMakePair(QVariant(data.dimArcPosition.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimArcPositionZ) {
        return qMakePair(QVariant(data.dimArcPosition.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}

void RDimAngularEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimAngularEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", extensionLine1Start: " << getData().extensionLine1Start
                  << ", extensionLine1End: " << getData().extensionLine1End
                  << ", extensionLine2Start: " << getData().extensionLine2Start
                  << ", extensionLine2End: " << getData().definitionPoint
                  << ", dimArcPosition: " << getData().dimArcPosition
                  << ", text: " << getData().textData.getText()
                  << ")";
}
