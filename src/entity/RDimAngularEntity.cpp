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
#include "RPluginLoader.h"

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

RPropertyTypeId RDimAngularEntity::PropertyDimscale;
//RPropertyTypeId RDimAngularEntity::PropertyDimlfac;
RPropertyTypeId RDimAngularEntity::PropertyDimtxt;
RPropertyTypeId RDimAngularEntity::PropertyDimgap;
RPropertyTypeId RDimAngularEntity::PropertyDimasz;
//RPropertyTypeId RDimAngularEntity::PropertyDimdli;
RPropertyTypeId RDimAngularEntity::PropertyDimexe;
RPropertyTypeId RDimAngularEntity::PropertyDimexo;
RPropertyTypeId RDimAngularEntity::PropertyDimtad;
RPropertyTypeId RDimAngularEntity::PropertyDimtih;
RPropertyTypeId RDimAngularEntity::PropertyDimtsz;
//RPropertyTypeId RDimAngularEntity::PropertyDimlunit;
//RPropertyTypeId RDimAngularEntity::PropertyDimdec;
RPropertyTypeId RDimAngularEntity::PropertyDimdsep;
//RPropertyTypeId RDimAngularEntity::PropertyDimzin;
RPropertyTypeId RDimAngularEntity::PropertyDimaunit;
RPropertyTypeId RDimAngularEntity::PropertyDimadec;
RPropertyTypeId RDimAngularEntity::PropertyDimazin;
RPropertyTypeId RDimAngularEntity::PropertyArchTick;
RPropertyTypeId RDimAngularEntity::PropertyDimclrt;

//RPropertyTypeId RDimAngularEntity::PropertyDimScale;
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
    RDimAngularEntity::PropertyCustom.generateId(RDimAngularEntity::getRtti(), RObject::PropertyCustom);
    RDimAngularEntity::PropertyHandle.generateId(RDimAngularEntity::getRtti(), RObject::PropertyHandle);
    RDimAngularEntity::PropertyProtected.generateId(RDimAngularEntity::getRtti(), RObject::PropertyProtected);
    RDimAngularEntity::PropertyWorkingSet.generateId(RDimAngularEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimAngularEntity::PropertyType.generateId(RDimAngularEntity::getRtti(), REntity::PropertyType);
    RDimAngularEntity::PropertyBlock.generateId(RDimAngularEntity::getRtti(), REntity::PropertyBlock);
    RDimAngularEntity::PropertyLayer.generateId(RDimAngularEntity::getRtti(), REntity::PropertyLayer);
    RDimAngularEntity::PropertyLinetype.generateId(RDimAngularEntity::getRtti(), REntity::PropertyLinetype);
    RDimAngularEntity::PropertyLinetypeScale.generateId(RDimAngularEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimAngularEntity::PropertyLineweight.generateId(RDimAngularEntity::getRtti(), REntity::PropertyLineweight);
    RDimAngularEntity::PropertyColor.generateId(RDimAngularEntity::getRtti(), REntity::PropertyColor);
    RDimAngularEntity::PropertyDisplayedColor.generateId(RDimAngularEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimAngularEntity::PropertyDrawOrder.generateId(RDimAngularEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimAngularEntity::PropertyMiddleOfTextX.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAngularEntity::PropertyMiddleOfTextY.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAngularEntity::PropertyMiddleOfTextZ.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimAngularEntity::PropertyText.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimAngularEntity::PropertyUpperTolerance.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimAngularEntity::PropertyLowerTolerance.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimAngularEntity::PropertyMeasuredValue.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimAngularEntity::PropertyDimscale.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        //RDimAngularEntity::PropertyDimlfac.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimAngularEntity::PropertyDimtxt.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimAngularEntity::PropertyDimgap.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimAngularEntity::PropertyDimasz.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimAngularEntity::PropertyDimdli.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimAngularEntity::PropertyDimexe.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimAngularEntity::PropertyDimexo.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimAngularEntity::PropertyDimtad.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimAngularEntity::PropertyDimtih.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimAngularEntity::PropertyDimtsz.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
    //    RDimAngularEntity::PropertyDimlunit.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
    //    RDimAngularEntity::PropertyDimdec.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimAngularEntity::PropertyDimdsep.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
    //    RDimAngularEntity::PropertyDimzin.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimzin);
        RDimAngularEntity::PropertyDimaunit.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
        RDimAngularEntity::PropertyDimadec.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimadec);
        RDimAngularEntity::PropertyDimazin.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimAngularEntity::PropertyArchTick.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimAngularEntity::PropertyDimclrt.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimAngularEntity::PropertyFontName.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimAngularEntity::PropertyArrow1Flipped.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        RDimAngularEntity::PropertyArrow2Flipped.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        RDimAngularEntity::PropertyExtLineFix.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        RDimAngularEntity::PropertyExtLineFixLength.generateId(RDimAngularEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

    RDimAngularEntity::PropertyCenterX.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyCenterY.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyCenterZ.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngularEntity::PropertyExtensionLine1EndX.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine1EndY.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine1EndZ.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngularEntity::PropertyExtensionLine2EndX.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine2EndY.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyExtensionLine2EndZ.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngularEntity::PropertyDimArcPositionX.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyDimArcPositionY.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngularEntity::PropertyDimArcPositionZ.generateId(RDimAngularEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Dimension Arc"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);
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
