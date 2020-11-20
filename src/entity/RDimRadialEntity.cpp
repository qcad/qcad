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
#include "RDimRadialEntity.h"
#include "RExporter.h"

RPropertyTypeId RDimRadialEntity::PropertyCustom;
RPropertyTypeId RDimRadialEntity::PropertyHandle;
RPropertyTypeId RDimRadialEntity::PropertyProtected;
RPropertyTypeId RDimRadialEntity::PropertyWorkingSet;
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
RPropertyTypeId RDimRadialEntity::PropertyDimBlockName;
RPropertyTypeId RDimRadialEntity::PropertyAutoTextPos;
RPropertyTypeId RDimRadialEntity::PropertyFontName;
RPropertyTypeId RDimRadialEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimRadialEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimRadialEntity::PropertyExtLineFix;
RPropertyTypeId RDimRadialEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimRadialEntity::PropertyCenterPointX;
RPropertyTypeId RDimRadialEntity::PropertyCenterPointY;
RPropertyTypeId RDimRadialEntity::PropertyCenterPointZ;
RPropertyTypeId RDimRadialEntity::PropertyChordPointX;
RPropertyTypeId RDimRadialEntity::PropertyChordPointY;
RPropertyTypeId RDimRadialEntity::PropertyChordPointZ;


RDimRadialEntity::RDimRadialEntity(RDocument* document, const RDimRadialData& data) :
    RDimensionEntity(document), data(document, data) {
}

RDimRadialEntity::~RDimRadialEntity() {
}

void RDimRadialEntity::init() {
    RDimRadialEntity::PropertyCustom.generateId(typeid(RDimRadialEntity), RObject::PropertyCustom);
    RDimRadialEntity::PropertyHandle.generateId(typeid(RDimRadialEntity), RObject::PropertyHandle);
    RDimRadialEntity::PropertyProtected.generateId(typeid(RDimRadialEntity), RObject::PropertyProtected);
    RDimRadialEntity::PropertyWorkingSet.generateId(typeid(RDimRadialEntity), RObject::PropertyWorkingSet);
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
    RDimRadialEntity::PropertyDimBlockName.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyDimBlockName);
    RDimRadialEntity::PropertyAutoTextPos.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimRadialEntity::PropertyFontName.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyFontName);
    RDimRadialEntity::PropertyArrow1Flipped.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimRadialEntity::PropertyArrow2Flipped.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimRadialEntity::PropertyExtLineFix.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyExtLineFix);
    RDimRadialEntity::PropertyExtLineFixLength.generateId(typeid(RDimRadialEntity), RDimensionEntity::PropertyExtLineFixLength);

    RDimRadialEntity::PropertyCenterPointX.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyCenterPointY.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyCenterPointZ.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimRadialEntity::PropertyChordPointX.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyChordPointY.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimRadialEntity::PropertyChordPointZ.generateId(typeid(RDimRadialEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
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
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
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

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimRadialEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimRadialEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", definitionPoint: " << getData().definitionPoint
                  << ", definitionPoint2: " << getData().chordPoint
                  << ")";
}
