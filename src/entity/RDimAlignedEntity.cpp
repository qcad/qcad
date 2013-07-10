/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
RPropertyTypeId RDimAlignedEntity::PropertyType;
RPropertyTypeId RDimAlignedEntity::PropertyBlock;
RPropertyTypeId RDimAlignedEntity::PropertyLayer;
RPropertyTypeId RDimAlignedEntity::PropertyLinetype;
RPropertyTypeId RDimAlignedEntity::PropertyLineweight;
RPropertyTypeId RDimAlignedEntity::PropertyColor;
RPropertyTypeId RDimAlignedEntity::PropertyDrawOrder;

RPropertyTypeId RDimAlignedEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimAlignedEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimAlignedEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimAlignedEntity::PropertyText;
RPropertyTypeId RDimAlignedEntity::PropertyUpperTolerance;
RPropertyTypeId RDimAlignedEntity::PropertyLowerTolerance;
RPropertyTypeId RDimAlignedEntity::PropertyLinearFactor;

RPropertyTypeId RDimAlignedEntity::PropertyDimensionLinePosX;
RPropertyTypeId RDimAlignedEntity::PropertyDimensionLinePosY;
RPropertyTypeId RDimAlignedEntity::PropertyDimensionLinePosZ;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint1X;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint1Y;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint1Z;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint2X;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint2Y;
RPropertyTypeId RDimAlignedEntity::PropertyExtensionPoint2Z;


RDimAlignedEntity::RDimAlignedEntity(RDocument* document, const RDimAlignedData& data, RObject::Id objectId) :
    RDimensionEntity(document, objectId), data(document, data) {
}

RDimAlignedEntity::~RDimAlignedEntity() {
}

void RDimAlignedEntity::init() {
    RDimAlignedEntity::PropertyCustom.generateId(typeid(RDimAlignedEntity), RObject::PropertyCustom);
    RDimAlignedEntity::PropertyHandle.generateId(typeid(RDimAlignedEntity), RObject::PropertyHandle);
    RDimAlignedEntity::PropertyType.generateId(typeid(RDimAlignedEntity), REntity::PropertyType);
    RDimAlignedEntity::PropertyBlock.generateId(typeid(RDimAlignedEntity), REntity::PropertyBlock);
    RDimAlignedEntity::PropertyLayer.generateId(typeid(RDimAlignedEntity), REntity::PropertyLayer);
    RDimAlignedEntity::PropertyLinetype.generateId(typeid(RDimAlignedEntity), REntity::PropertyLinetype);
    RDimAlignedEntity::PropertyLineweight.generateId(typeid(RDimAlignedEntity), REntity::PropertyLineweight);
    RDimAlignedEntity::PropertyColor.generateId(typeid(RDimAlignedEntity), REntity::PropertyColor);
    RDimAlignedEntity::PropertyDrawOrder.generateId(typeid(RDimAlignedEntity), REntity::PropertyDrawOrder);

    RDimAlignedEntity::PropertyMiddleOfTextX.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAlignedEntity::PropertyMiddleOfTextY.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAlignedEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimAlignedEntity::PropertyText.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyText);
    RDimAlignedEntity::PropertyUpperTolerance.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimAlignedEntity::PropertyLowerTolerance.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyLowerTolerance);

    RDimAlignedEntity::PropertyLinearFactor.generateId(typeid(RDimAlignedEntity), RDimensionEntity::PropertyLinearFactor);

    RDimAlignedEntity::PropertyDimensionLinePosX.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimAlignedEntity::PropertyDimensionLinePosY.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimAlignedEntity::PropertyDimensionLinePosZ.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Line"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RDimAlignedEntity::PropertyExtensionPoint1X.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimAlignedEntity::PropertyExtensionPoint1Y.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimAlignedEntity::PropertyExtensionPoint1Z.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 1"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RDimAlignedEntity::PropertyExtensionPoint2X.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimAlignedEntity::PropertyExtensionPoint2Y.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimAlignedEntity::PropertyExtensionPoint2Z.generateId(typeid(RDimAlignedEntity), QT_TRANSLATE_NOOP("REntity", "Extension Point 2"), QT_TRANSLATE_NOOP("REntity", "Z"));
}

bool RDimAlignedEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value);

    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyDimensionLinePosX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyDimensionLinePosY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyDimensionLinePosZ == propertyTypeId);

    ret = ret || RObject::setMember(data.extensionPoint1.x, value, PropertyExtensionPoint1X == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionPoint1.y, value, PropertyExtensionPoint1Y == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionPoint1.z, value, PropertyExtensionPoint1Z == propertyTypeId);

    ret = ret || RObject::setMember(data.extensionPoint2.x, value, PropertyExtensionPoint2X == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionPoint2.y, value, PropertyExtensionPoint2Y == propertyTypeId);
    ret = ret || RObject::setMember(data.extensionPoint2.z, value, PropertyExtensionPoint2Z == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimAlignedEntity::getProperty(
        RPropertyTypeId propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyType) {
        return qMakePair(QVariant(RS::EntityDimAligned),
            RPropertyAttributes(RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId == PropertyDimensionLinePosX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimensionLinePosY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimensionLinePosZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint1X) {
        return qMakePair(QVariant(data.extensionPoint1.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint1Y) {
        return qMakePair(QVariant(data.extensionPoint1.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint1Z) {
        return qMakePair(QVariant(data.extensionPoint1.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint2X) {
        return qMakePair(QVariant(data.extensionPoint2.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint2Y) {
        return qMakePair(QVariant(data.extensionPoint2.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyExtensionPoint2Z) {
        return qMakePair(QVariant(data.extensionPoint2.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}

void RDimAlignedEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimAlignedEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", extensionPoint1: " << getData().extensionPoint1
                  << ", extensionPoint2: " << getData().extensionPoint2
                  << ")";
}
