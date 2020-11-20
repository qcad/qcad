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
#include "RDimAngular2LEntity.h"
#include "RExporter.h"

RPropertyTypeId RDimAngular2LEntity::PropertyCustom;
RPropertyTypeId RDimAngular2LEntity::PropertyHandle;
RPropertyTypeId RDimAngular2LEntity::PropertyProtected;
RPropertyTypeId RDimAngular2LEntity::PropertyWorkingSet;
RPropertyTypeId RDimAngular2LEntity::PropertyType;
RPropertyTypeId RDimAngular2LEntity::PropertyBlock;
RPropertyTypeId RDimAngular2LEntity::PropertyLayer;
RPropertyTypeId RDimAngular2LEntity::PropertyLinetype;
RPropertyTypeId RDimAngular2LEntity::PropertyLinetypeScale;
RPropertyTypeId RDimAngular2LEntity::PropertyLineweight;
RPropertyTypeId RDimAngular2LEntity::PropertyColor;
RPropertyTypeId RDimAngular2LEntity::PropertyDisplayedColor;
RPropertyTypeId RDimAngular2LEntity::PropertyDrawOrder;

RPropertyTypeId RDimAngular2LEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimAngular2LEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimAngular2LEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimAngular2LEntity::PropertyText;
RPropertyTypeId RDimAngular2LEntity::PropertyUpperTolerance;
RPropertyTypeId RDimAngular2LEntity::PropertyLowerTolerance;

RPropertyTypeId RDimAngular2LEntity::PropertyDimScale;
RPropertyTypeId RDimAngular2LEntity::PropertyDimBlockName;
RPropertyTypeId RDimAngular2LEntity::PropertyAutoTextPos;
RPropertyTypeId RDimAngular2LEntity::PropertyMeasuredValue;
RPropertyTypeId RDimAngular2LEntity::PropertyFontName;
RPropertyTypeId RDimAngular2LEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimAngular2LEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimAngular2LEntity::PropertyExtLineFix;
RPropertyTypeId RDimAngular2LEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine1StartX;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine1StartY;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine1StartZ;

RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine1EndX;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine1EndY;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine1EndZ;

RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine2StartX;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine2StartY;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine2StartZ;

RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine2EndX;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine2EndY;
RPropertyTypeId RDimAngular2LEntity::PropertyExtensionLine2EndZ;

RPropertyTypeId RDimAngular2LEntity::PropertyDimArcPositionX;
RPropertyTypeId RDimAngular2LEntity::PropertyDimArcPositionY;
RPropertyTypeId RDimAngular2LEntity::PropertyDimArcPositionZ;



RDimAngular2LEntity::RDimAngular2LEntity(RDocument* document, const RDimAngular2LData& data) :
    RDimAngularEntity(document), data(document, data) {
}

RDimAngular2LEntity::~RDimAngular2LEntity() {
}

void RDimAngular2LEntity::init() {
    RDimAngular2LEntity::PropertyCustom.generateId(typeid(RDimAngular2LEntity), RObject::PropertyCustom);
    RDimAngular2LEntity::PropertyHandle.generateId(typeid(RDimAngular2LEntity), RObject::PropertyHandle);
    RDimAngular2LEntity::PropertyProtected.generateId(typeid(RDimAngular2LEntity), RObject::PropertyProtected);
    RDimAngular2LEntity::PropertyWorkingSet.generateId(typeid(RDimAngular2LEntity), RObject::PropertyWorkingSet);
    RDimAngular2LEntity::PropertyType.generateId(typeid(RDimAngular2LEntity), REntity::PropertyType);
    RDimAngular2LEntity::PropertyBlock.generateId(typeid(RDimAngular2LEntity), REntity::PropertyBlock);
    RDimAngular2LEntity::PropertyLayer.generateId(typeid(RDimAngular2LEntity), REntity::PropertyLayer);
    RDimAngular2LEntity::PropertyLinetype.generateId(typeid(RDimAngular2LEntity), REntity::PropertyLinetype);
    RDimAngular2LEntity::PropertyLinetypeScale.generateId(typeid(RDimAngular2LEntity), REntity::PropertyLinetypeScale);
    RDimAngular2LEntity::PropertyLineweight.generateId(typeid(RDimAngular2LEntity), REntity::PropertyLineweight);
    RDimAngular2LEntity::PropertyColor.generateId(typeid(RDimAngular2LEntity), REntity::PropertyColor);
    RDimAngular2LEntity::PropertyDisplayedColor.generateId(typeid(RDimAngular2LEntity), REntity::PropertyDisplayedColor);
    RDimAngular2LEntity::PropertyDrawOrder.generateId(typeid(RDimAngular2LEntity), REntity::PropertyDrawOrder);

    RDimAngular2LEntity::PropertyMiddleOfTextX.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAngular2LEntity::PropertyMiddleOfTextY.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAngular2LEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimAngular2LEntity::PropertyText.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyText);
    RDimAngular2LEntity::PropertyUpperTolerance.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimAngular2LEntity::PropertyLowerTolerance.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimAngular2LEntity::PropertyMeasuredValue.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyMeasuredValue);

    RDimAngular2LEntity::PropertyDimScale.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyDimScale);
    RDimAngular2LEntity::PropertyDimBlockName.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyDimBlockName);
    RDimAngular2LEntity::PropertyAutoTextPos.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimAngular2LEntity::PropertyFontName.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyFontName);
    RDimAngular2LEntity::PropertyArrow1Flipped.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimAngular2LEntity::PropertyArrow2Flipped.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimAngular2LEntity::PropertyExtLineFix.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyExtLineFix);
    RDimAngular2LEntity::PropertyExtLineFixLength.generateId(typeid(RDimAngular2LEntity), RDimensionEntity::PropertyExtLineFixLength);

    RDimAngular2LEntity::PropertyExtensionLine1StartX.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine1StartY.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine1StartZ.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular2LEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyExtensionLine1EndX);
    RDimAngular2LEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyExtensionLine1EndY);
    RDimAngular2LEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyExtensionLine1EndZ);

//    RDimAngular2LEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular2LEntity::PropertyExtensionLine2StartX.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine2StartY.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine2StartZ.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

//    RDimAngular2LEntity::PropertyExtensionLine2EndX.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine2EndY.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine2EndZ.generateId(typeid(RDimAngular2LEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular2LEntity::PropertyExtensionLine2EndX.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyExtensionLine2EndX);
    RDimAngular2LEntity::PropertyExtensionLine2EndY.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyExtensionLine2EndY);
    RDimAngular2LEntity::PropertyExtensionLine2EndZ.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyExtensionLine2EndZ);

    RDimAngular2LEntity::PropertyDimArcPositionX.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyDimArcPositionX);
    RDimAngular2LEntity::PropertyDimArcPositionY.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyDimArcPositionY);
    RDimAngular2LEntity::PropertyDimArcPositionZ.generateId(typeid(RDimAngular2LEntity), RDimAngularEntity::PropertyDimArcPositionZ);
}

bool RDimAngular2LEntity::setProperty(RPropertyTypeId propertyTypeId,
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

QPair<QVariant, RPropertyAttributes> RDimAngular2LEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

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

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimAngular2LEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimAngular2LEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", extensionLine1Start: " << getData().extensionLine1Start
                  << ", extensionLine2Start: " << getData().extensionLine2Start
                  << ")";
}
