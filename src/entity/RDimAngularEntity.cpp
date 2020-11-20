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
#include "RDimAngularEntity.h"
#include "RExporter.h"

RPropertyTypeId RDimAngularEntity::PropertyCustom;
RPropertyTypeId RDimAngularEntity::PropertyHandle;
RPropertyTypeId RDimAngularEntity::PropertyProtected;
RPropertyTypeId RDimAngularEntity::PropertyWorkingSet;
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

RPropertyTypeId RDimAngularEntity::PropertyDimScale;
RPropertyTypeId RDimAngularEntity::PropertyDimBlockName;
RPropertyTypeId RDimAngularEntity::PropertyAutoTextPos;
RPropertyTypeId RDimAngularEntity::PropertyFontName;
RPropertyTypeId RDimAngularEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimAngularEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimAngularEntity::PropertyExtLineFix;
RPropertyTypeId RDimAngularEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimAngularEntity::PropertyCenterX;
RPropertyTypeId RDimAngularEntity::PropertyCenterY;
RPropertyTypeId RDimAngularEntity::PropertyCenterZ;

RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1EndX;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1EndY;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine1EndZ;

RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2EndX;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2EndY;
RPropertyTypeId RDimAngularEntity::PropertyExtensionLine2EndZ;

RPropertyTypeId RDimAngularEntity::PropertyDimArcPositionX;
RPropertyTypeId RDimAngularEntity::PropertyDimArcPositionY;
RPropertyTypeId RDimAngularEntity::PropertyDimArcPositionZ;



RDimAngularEntity::RDimAngularEntity(RDocument* document) :
    RDimensionEntity(document) {
}

RDimAngularEntity::~RDimAngularEntity() {
}

void RDimAngularEntity::init() {
    RDimAngularEntity::PropertyCustom.generateId(typeid(RDimAngularEntity), RObject::PropertyCustom);
    RDimAngularEntity::PropertyHandle.generateId(typeid(RDimAngularEntity), RObject::PropertyHandle);
    RDimAngularEntity::PropertyProtected.generateId(typeid(RDimAngularEntity), RObject::PropertyProtected);
    RDimAngularEntity::PropertyWorkingSet.generateId(typeid(RDimAngularEntity), RObject::PropertyWorkingSet);
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
    RDimAngularEntity::PropertyArrow1Flipped.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyArrow1Flipped);
    RDimAngularEntity::PropertyArrow2Flipped.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyArrow2Flipped);

    RDimAngularEntity::PropertyExtLineFix.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyExtLineFix);
    RDimAngularEntity::PropertyExtLineFixLength.generateId(typeid(RDimAngularEntity), RDimensionEntity::PropertyExtLineFixLength);

    RDimAngularEntity::PropertyCenterX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyCenterY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyCenterZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngularEntity::PropertyExtensionLine1EndX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine1EndY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine1EndZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngularEntity::PropertyExtensionLine2EndX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine2EndY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine2EndZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngularEntity::PropertyDimArcPositionX.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyDimArcPositionY.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyDimArcPositionZ.generateId(typeid(RDimAngularEntity), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);
}

void RDimAngularEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimAngularEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", extensionLine1End: " << getData().getExtensionLine1End()
                  << ", extensionLine2End: " << getData().getExtensionLine2End()
                  << ", dimArcPosition: " << getData().getDimArcPosition()
                  << ", text: " << getData().textData.getText()
                  << ")";
}
