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
#include "RDimDiametricEntity.h"
#include "RExporter.h"

RPropertyTypeId RDimDiametricEntity::PropertyCustom;
RPropertyTypeId RDimDiametricEntity::PropertyHandle;
RPropertyTypeId RDimDiametricEntity::PropertyProtected;
RPropertyTypeId RDimDiametricEntity::PropertyWorkingSet;
RPropertyTypeId RDimDiametricEntity::PropertyType;
RPropertyTypeId RDimDiametricEntity::PropertyBlock;
RPropertyTypeId RDimDiametricEntity::PropertyLayer;
RPropertyTypeId RDimDiametricEntity::PropertyLinetype;
RPropertyTypeId RDimDiametricEntity::PropertyLinetypeScale;
RPropertyTypeId RDimDiametricEntity::PropertyLineweight;
RPropertyTypeId RDimDiametricEntity::PropertyColor;
RPropertyTypeId RDimDiametricEntity::PropertyDisplayedColor;
RPropertyTypeId RDimDiametricEntity::PropertyDrawOrder;

RPropertyTypeId RDimDiametricEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimDiametricEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimDiametricEntity::PropertyMiddleOfTextZ;

RPropertyTypeId RDimDiametricEntity::PropertyText;
RPropertyTypeId RDimDiametricEntity::PropertyUpperTolerance;
RPropertyTypeId RDimDiametricEntity::PropertyLowerTolerance;
RPropertyTypeId RDimDiametricEntity::PropertyMeasuredValue;

RPropertyTypeId RDimDiametricEntity::PropertyLinearFactor;
RPropertyTypeId RDimDiametricEntity::PropertyDimScale;
RPropertyTypeId RDimDiametricEntity::PropertyDimBlockName;
RPropertyTypeId RDimDiametricEntity::PropertyAutoTextPos;
RPropertyTypeId RDimDiametricEntity::PropertyFontName;
RPropertyTypeId RDimDiametricEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimDiametricEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimDiametricEntity::PropertyExtLineFix;
RPropertyTypeId RDimDiametricEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimDiametricEntity::PropertyChordPointX;
RPropertyTypeId RDimDiametricEntity::PropertyChordPointY;
RPropertyTypeId RDimDiametricEntity::PropertyChordPointZ;

RPropertyTypeId RDimDiametricEntity::PropertyFarChordPointX;
RPropertyTypeId RDimDiametricEntity::PropertyFarChordPointY;
RPropertyTypeId RDimDiametricEntity::PropertyFarChordPointZ;


RDimDiametricEntity::RDimDiametricEntity(RDocument* document, const RDimDiametricData& data) :
    RDimensionEntity(document), data(document, data) {
}

RDimDiametricEntity::~RDimDiametricEntity() {
}

void RDimDiametricEntity::init() {
    RDimDiametricEntity::PropertyCustom.generateId(typeid(RDimDiametricEntity), RObject::PropertyCustom);
    RDimDiametricEntity::PropertyHandle.generateId(typeid(RDimDiametricEntity), RObject::PropertyHandle);
    RDimDiametricEntity::PropertyProtected.generateId(typeid(RDimDiametricEntity), RObject::PropertyProtected);
    RDimDiametricEntity::PropertyWorkingSet.generateId(typeid(RDimDiametricEntity), RObject::PropertyWorkingSet);
    RDimDiametricEntity::PropertyType.generateId(typeid(RDimDiametricEntity), REntity::PropertyType);
    RDimDiametricEntity::PropertyBlock.generateId(typeid(RDimDiametricEntity), REntity::PropertyBlock);
    RDimDiametricEntity::PropertyLayer.generateId(typeid(RDimDiametricEntity), REntity::PropertyLayer);
    RDimDiametricEntity::PropertyLinetype.generateId(typeid(RDimDiametricEntity), REntity::PropertyLinetype);
    RDimDiametricEntity::PropertyLinetypeScale.generateId(typeid(RDimDiametricEntity), REntity::PropertyLinetypeScale);
    RDimDiametricEntity::PropertyLineweight.generateId(typeid(RDimDiametricEntity), REntity::PropertyLineweight);
    RDimDiametricEntity::PropertyColor.generateId(typeid(RDimDiametricEntity), REntity::PropertyColor);
    RDimDiametricEntity::PropertyDisplayedColor.generateId(typeid(RDimDiametricEntity), REntity::PropertyDisplayedColor);
    RDimDiametricEntity::PropertyDrawOrder.generateId(typeid(RDimDiametricEntity), REntity::PropertyDrawOrder);

    RDimDiametricEntity::PropertyMiddleOfTextX.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimDiametricEntity::PropertyMiddleOfTextY.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimDiametricEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimDiametricEntity::PropertyText.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyText);
    RDimDiametricEntity::PropertyUpperTolerance.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimDiametricEntity::PropertyLowerTolerance.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimDiametricEntity::PropertyMeasuredValue.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyMeasuredValue);

    RDimDiametricEntity::PropertyLinearFactor.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyLinearFactor);
    RDimDiametricEntity::PropertyDimScale.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyDimScale);
    RDimDiametricEntity::PropertyDimBlockName.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyDimBlockName);
    RDimDiametricEntity::PropertyAutoTextPos.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyAutoTextPos);
    RDimDiametricEntity::PropertyFontName.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyFontName);
    RDimDiametricEntity::PropertyArrow1Flipped.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimDiametricEntity::PropertyArrow2Flipped.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimDiametricEntity::PropertyExtLineFix.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyExtLineFix);
    RDimDiametricEntity::PropertyExtLineFixLength.generateId(typeid(RDimDiametricEntity), RDimensionEntity::PropertyExtLineFixLength);

    RDimDiametricEntity::PropertyChordPointX.generateId(typeid(RDimDiametricEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyChordPointY.generateId(typeid(RDimDiametricEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyChordPointZ.generateId(typeid(RDimDiametricEntity), QT_TRANSLATE_NOOP("REntity", "Chord Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RDimDiametricEntity::PropertyFarChordPointX.generateId(typeid(RDimDiametricEntity), QT_TRANSLATE_NOOP("REntity", "Far Chord Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyFarChordPointY.generateId(typeid(RDimDiametricEntity), QT_TRANSLATE_NOOP("REntity", "Far Chord Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimDiametricEntity::PropertyFarChordPointZ.generateId(typeid(RDimDiametricEntity), QT_TRANSLATE_NOOP("REntity", "Far Chord Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RDimDiametricEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyChordPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyChordPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyChordPointZ == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.x, value, PropertyFarChordPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.y, value, PropertyFarChordPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.chordPoint.z, value, PropertyFarChordPointZ == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimDiametricEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyChordPointX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyChordPointZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyFarChordPointX) {
        return qMakePair(QVariant(data.chordPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyFarChordPointY) {
        return qMakePair(QVariant(data.chordPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyFarChordPointZ) {
        return qMakePair(QVariant(data.chordPoint.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimDiametricEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimDiametricEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", definitionPoint: " << getData().definitionPoint
                  << ", definitionPoint2: " << getData().chordPoint
                  << ")";
}
