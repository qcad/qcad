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
#include "RPluginLoader.h"

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

//RPropertyTypeId RDimAngular2LEntity::PropertyDimScale;
RPropertyTypeId RDimAngular2LEntity::PropertyDimBlockName;
RPropertyTypeId RDimAngular2LEntity::PropertyAutoTextPos;
RPropertyTypeId RDimAngular2LEntity::PropertyMeasuredValue;
RPropertyTypeId RDimAngular2LEntity::PropertyFontName;
RPropertyTypeId RDimAngular2LEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimAngular2LEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimAngular2LEntity::PropertyDimscale;
//RPropertyTypeId RDimAngular2LEntity::PropertyDimlfac;
RPropertyTypeId RDimAngular2LEntity::PropertyDimtxt;
RPropertyTypeId RDimAngular2LEntity::PropertyDimgap;
RPropertyTypeId RDimAngular2LEntity::PropertyDimasz;
//RPropertyTypeId RDimAngular2LEntity::PropertyDimdli;
RPropertyTypeId RDimAngular2LEntity::PropertyDimexe;
RPropertyTypeId RDimAngular2LEntity::PropertyDimexo;
RPropertyTypeId RDimAngular2LEntity::PropertyDimtad;
RPropertyTypeId RDimAngular2LEntity::PropertyDimtih;
RPropertyTypeId RDimAngular2LEntity::PropertyDimtsz;
//RPropertyTypeId RDimAngular2LEntity::PropertyDimlunit;
//RPropertyTypeId RDimAngular2LEntity::PropertyDimdec;
RPropertyTypeId RDimAngular2LEntity::PropertyDimdsep;
//RPropertyTypeId RDimAngular2LEntity::PropertyDimzin;
RPropertyTypeId RDimAngular2LEntity::PropertyDimaunit;
RPropertyTypeId RDimAngular2LEntity::PropertyDimadec;
RPropertyTypeId RDimAngular2LEntity::PropertyDimazin;
RPropertyTypeId RDimAngular2LEntity::PropertyArchTick;
RPropertyTypeId RDimAngular2LEntity::PropertyDimclrt;

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
    RDimAngular2LEntity::PropertyCustom.generateId(RDimAngular2LEntity::getRtti(), RObject::PropertyCustom);
    RDimAngular2LEntity::PropertyHandle.generateId(RDimAngular2LEntity::getRtti(), RObject::PropertyHandle);
    RDimAngular2LEntity::PropertyProtected.generateId(RDimAngular2LEntity::getRtti(), RObject::PropertyProtected);
    RDimAngular2LEntity::PropertyWorkingSet.generateId(RDimAngular2LEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimAngular2LEntity::PropertyType.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyType);
    RDimAngular2LEntity::PropertyBlock.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyBlock);
    RDimAngular2LEntity::PropertyLayer.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyLayer);
    RDimAngular2LEntity::PropertyLinetype.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyLinetype);
    RDimAngular2LEntity::PropertyLinetypeScale.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimAngular2LEntity::PropertyLineweight.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyLineweight);
    RDimAngular2LEntity::PropertyColor.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyColor);
    RDimAngular2LEntity::PropertyDisplayedColor.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimAngular2LEntity::PropertyDrawOrder.generateId(RDimAngular2LEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimAngular2LEntity::PropertyMiddleOfTextX.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimAngular2LEntity::PropertyMiddleOfTextY.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimAngular2LEntity::PropertyMiddleOfTextZ.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);

    RDimAngular2LEntity::PropertyText.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimAngular2LEntity::PropertyUpperTolerance.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimAngular2LEntity::PropertyLowerTolerance.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimAngular2LEntity::PropertyMeasuredValue.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimAngular2LEntity::PropertyDimscale.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        //RDimAngular2LEntity::PropertyDimlfac.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
        RDimAngular2LEntity::PropertyDimtxt.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimtxt);
        RDimAngular2LEntity::PropertyDimgap.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimgap);
        RDimAngular2LEntity::PropertyDimasz.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimasz);
        //RDimAngular2LEntity::PropertyDimdli.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimdli);
        RDimAngular2LEntity::PropertyDimexe.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimexe);
        RDimAngular2LEntity::PropertyDimexo.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimexo);
        RDimAngular2LEntity::PropertyDimtad.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimtad);
        RDimAngular2LEntity::PropertyDimtih.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimtih);
        RDimAngular2LEntity::PropertyDimtsz.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimtsz);
    //    RDimAngular2LEntity::PropertyDimlunit.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimlunit);
    //    RDimAngular2LEntity::PropertyDimdec.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimdec);
        RDimAngular2LEntity::PropertyDimdsep.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimdsep);
    //    RDimAngular2LEntity::PropertyDimzin.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimzin);
        RDimAngular2LEntity::PropertyDimaunit.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimaunit);
        RDimAngular2LEntity::PropertyDimadec.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimadec);
        RDimAngular2LEntity::PropertyDimazin.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimazin);
        RDimAngular2LEntity::PropertyArchTick.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyArchTick);
        RDimAngular2LEntity::PropertyDimclrt.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimclrt);
    }

    //RDimAngular2LEntity::PropertyDimScale.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimScale);
    RDimAngular2LEntity::PropertyDimBlockName.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);
    RDimAngular2LEntity::PropertyAutoTextPos.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyAutoTextPos);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimAngular2LEntity::PropertyFontName.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimAngular2LEntity::PropertyArrow1Flipped.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        RDimAngular2LEntity::PropertyArrow2Flipped.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        RDimAngular2LEntity::PropertyExtLineFix.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        RDimAngular2LEntity::PropertyExtLineFixLength.generateId(RDimAngular2LEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);
    }

    RDimAngular2LEntity::PropertyExtensionLine1StartX.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine1StartY.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine1StartZ.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 Start"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular2LEntity::PropertyExtensionLine1EndX.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine1EndX);
    RDimAngular2LEntity::PropertyExtensionLine1EndY.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine1EndY);
    RDimAngular2LEntity::PropertyExtensionLine1EndZ.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine1EndZ);

//    RDimAngular2LEntity::PropertyExtensionLine1EndX.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine1EndY.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine1EndZ.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 1 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular2LEntity::PropertyExtensionLine2StartX.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine2StartY.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
    RDimAngular2LEntity::PropertyExtensionLine2StartZ.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 Start"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

//    RDimAngular2LEntity::PropertyExtensionLine2EndX.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "X"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine2EndY.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Y"), true, RPropertyAttributes::Geometry);
//    RDimAngular2LEntity::PropertyExtensionLine2EndZ.generateId(RDimAngular2LEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Line 2 End"), QT_TRANSLATE_NOOP("REntity", "Z"), true, RPropertyAttributes::Geometry);

    RDimAngular2LEntity::PropertyExtensionLine2EndX.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine2EndX);
    RDimAngular2LEntity::PropertyExtensionLine2EndY.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine2EndY);
    RDimAngular2LEntity::PropertyExtensionLine2EndZ.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyExtensionLine2EndZ);

    RDimAngular2LEntity::PropertyDimArcPositionX.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyDimArcPositionX);
    RDimAngular2LEntity::PropertyDimArcPositionY.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyDimArcPositionY);
    RDimAngular2LEntity::PropertyDimArcPositionZ.generateId(RDimAngular2LEntity::getRtti(), RDimAngularEntity::PropertyDimArcPositionZ);
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
