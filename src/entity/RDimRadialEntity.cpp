/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
#include "RDimRadialEntity.h"
#include "RExporter.h"

RPropertyTypeId RDimRadialEntity::PropertyCustom;
RPropertyTypeId RDimRadialEntity::PropertyHandle;
RPropertyTypeId RDimRadialEntity::PropertyProtected;
RPropertyTypeId RDimRadialEntity::PropertyType;
RPropertyTypeId RDimRadialEntity::PropertyBlock;
RPropertyTypeId RDimRadialEntity::PropertyLayer;
RPropertyTypeId RDimRadialEntity::PropertyLinetype;
RPropertyTypeId RDimRadialEntity::PropertyLinetypeScale;
RPropertyTypeId RDimRadialEntity::PropertyLineweight;
RPropertyTypeId RDimRadialEntity::PropertyColor;
RPropertyTypeId RDimRadialEntity::PropertyDisplayedColor;
RPropertyTypeId RDimRadialEntity::PropertyDrawOrder;

RPropertyTypeId RDimRadialEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimRadialEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimRadialEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimRadialEntity::PropertyText;
RPropertyTypeId RDimRadialEntity::PropertyUpperTolerance;
RPropertyTypeId RDimRadialEntity::PropertyLowerTolerance;
RPropertyTypeId RDimRadialEntity::PropertyMeasuredValue;

RPropertyTypeId RDimRadialEntity::PropertyLinearFactor;
RPropertyTypeId RDimRadialEntity::PropertyDimScale;
RPropertyTypeId RDimRadialEntity::PropertyAutoTextPos;
RPropertyTypeId RDimRadialEntity::PropertyFontName;

RPropertyTypeId RDimRadialEntity::PropertyCenterPointX;
RPropertyTypeId RDimRadialEntity::PropertyCenterPointY;
RPropertyTypeId RDimRadialEntity::PropertyCenterPointZ;
RPropertyTypeId RDimRadialEntity::PropertyChordPointX;
RPropertyTypeId RDimRadialEntity::PropertyChordPointY;
RPropertyTypeId RDimRadialEntity::PropertyChordPointZ;


RDimRadialEntity::RDimRadialEntity(RDocument* document, const RDimRadialData& data, RObject::Id objectId) :
    RDimensionEntity(document, objectId), data(document, data) {
}

RDimRadialEntity::~RDimRadialEntity() {
}

void RDimRadialEntity::init() {
    RDimRadialEntity::PropertyCustom.generateId(typeid(RDimRadialEntity), RObject::PropertyCustom);
    RDimRadialEntity::PropertyHandle.generateId(typeid(RDimRadialEntity), RObject::PropertyHandle);
    RDimRadialEntity::PropertyProtected.generateId(typeid(RDimRadialEntity), RObject::PropertyProtected);
    RDimRadialEntity::PropertyType.generateId(typeid(RDimRadialEntity), REntity::PropertyType);
    RDimRadialEntity::PropertyBlock.generateId(typeid(RDimRadialEntity), REntity::PropertyBlock);
    RDimRadialEntity::PropertyLayer.generateId(typeid(RDimRadialEntity), REntity::PropertyLayer);
    RDimRadialEntity::PropertyLinetype.generateId(typeid(RDimRadialEntity), REntity::PropertyLinetype);
    RDimRadialEntity::PropertyLinetypeScale.generateId(typeid(RDimRadialEntity), REntity::PropertyLinetypeScale);
    RDimRadialEntity::PropertyLineweight.generateId(typeid(RDimRadialEntity), REntity::PropertyLineweight);
    RDimRadialEntity::PropertyColor.generateId(typeid(RDimRadialEntity), REntity::PropertyColor);
    RDimRadialEntity::PropertyDisplayedColor.generateId(typeid(RDimRadialEntity), REntity::PropertyDisplayedColor);
    RDimRadialEntity::PropertyDrawOrder.generateId(typeid(RDimRadialEntity), REntity::PropertyDrawOrder);

    RDimRadialEntity::PropertyMiddleOfTextX.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimRadialEntity::PropertyMiddleOfTextY.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimRadialEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimRadialEntity::PropertyText.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyText);
    RDimRadialEntity::PropertyUpperTolerance.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimRadialEntity::PropertyLowerTolerance.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimRadialEntity::PropertyMeasuredValue.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyMeasuredValue);

    RDimRadialEntity::PropertyLinearFactor.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyLinearFactor);
    RDimRadialEntity::PropertyDimScale.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyDimScale);
    RDimRadialEntity::PropertyAutoTextPos.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimRadialEntity::PropertyFontName.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyFontName);

    RDimRadialEntity::PropertyCenterPointX.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true);
    RDimRadialEntity::PropertyCenterPointY.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true);
    RDimRadialEntity::PropertyCenterPointZ.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true);

    RDimRadialEntity::PropertyChordPointX.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimRadialEntity::PropertyChordPointY.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimRadialEntity::PropertyChordPointZ.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
}

bool RDimRadialEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyCenterPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyCenterPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyCenterPointZ == propertyTypeId);

    ret = ret || RObject::setMember(data.chordPoint.x, value, PropertyChordPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.y, value, PropertyChordPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.z, value, PropertyChordPointZ == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimRadialEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyCenterPointX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterPointY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterPointZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointX) {
        return qMakePair(QVariant(data.chordPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointY) {
        return qMakePair(QVariant(data.chordPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointZ) {
        return qMakePair(QVariant(data.chordPoint.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}

void RDimRadialEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimRadialEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", definitionPoint: " << getData().definitionPoint
                  << ", definitionPoint2: " << getData().chordPoint
                  << ")";
}
