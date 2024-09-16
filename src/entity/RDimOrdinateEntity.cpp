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
#include "RDimOrdinateEntity.h"
#include "RExporter.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimOrdinateEntity::PropertyCustom;
RPropertyTypeId RDimOrdinateEntity::PropertyHandle;
RPropertyTypeId RDimOrdinateEntity::PropertyProtected;
RPropertyTypeId RDimOrdinateEntity::PropertyWorkingSet;
RPropertyTypeId RDimOrdinateEntity::PropertyType;
RPropertyTypeId RDimOrdinateEntity::PropertyBlock;
RPropertyTypeId RDimOrdinateEntity::PropertyLayer;
RPropertyTypeId RDimOrdinateEntity::PropertyLinetype;
RPropertyTypeId RDimOrdinateEntity::PropertyLinetypeScale;
RPropertyTypeId RDimOrdinateEntity::PropertyLineweight;
RPropertyTypeId RDimOrdinateEntity::PropertyColor;
RPropertyTypeId RDimOrdinateEntity::PropertyDisplayedColor;
RPropertyTypeId RDimOrdinateEntity::PropertyDrawOrder;

RPropertyTypeId RDimOrdinateEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimOrdinateEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimOrdinateEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimOrdinateEntity::PropertyText;
RPropertyTypeId RDimOrdinateEntity::PropertyUpperTolerance;
RPropertyTypeId RDimOrdinateEntity::PropertyLowerTolerance;
RPropertyTypeId RDimOrdinateEntity::PropertyMeasuredValue;
RPropertyTypeId RDimOrdinateEntity::PropertyFontName;
RPropertyTypeId RDimOrdinateEntity::PropertyTextRotation;
//RPropertyTypeId RDimOrdinateEntity::PropertyArrow1Flipped;
//RPropertyTypeId RDimOrdinateEntity::PropertyArrow2Flipped;

//RPropertyTypeId RDimOrdinateEntity::PropertyExtLineFix;
//RPropertyTypeId RDimOrdinateEntity::PropertyExtLineFixLength;

RPropertyTypeId RDimOrdinateEntity::PropertyDimscale;
RPropertyTypeId RDimOrdinateEntity::PropertyDimlfac;

RPropertyTypeId RDimOrdinateEntity::PropertyDimBlockName;

RPropertyTypeId RDimOrdinateEntity::PropertyOriginX;
RPropertyTypeId RDimOrdinateEntity::PropertyOriginY;
RPropertyTypeId RDimOrdinateEntity::PropertyOriginZ;

RPropertyTypeId RDimOrdinateEntity::PropertyOrdinate;

RPropertyTypeId RDimOrdinateEntity::PropertyLeaderEndPointX;
RPropertyTypeId RDimOrdinateEntity::PropertyLeaderEndPointY;
RPropertyTypeId RDimOrdinateEntity::PropertyLeaderEndPointZ;

RPropertyTypeId RDimOrdinateEntity::PropertyDefiningPointX;
RPropertyTypeId RDimOrdinateEntity::PropertyDefiningPointY;
RPropertyTypeId RDimOrdinateEntity::PropertyDefiningPointZ;


RDimOrdinateEntity::RDimOrdinateEntity(RDocument* document, const RDimOrdinateData& data) :
    RDimensionEntity(document), data(document, data) {
}

RDimOrdinateEntity::~RDimOrdinateEntity() {
}

void RDimOrdinateEntity::init() {
    RDimOrdinateEntity::PropertyCustom.generateId(RDimOrdinateEntity::getRtti(), RObject::PropertyCustom);
    RDimOrdinateEntity::PropertyHandle.generateId(RDimOrdinateEntity::getRtti(), RObject::PropertyHandle);
    RDimOrdinateEntity::PropertyProtected.generateId(RDimOrdinateEntity::getRtti(), RObject::PropertyProtected);
    RDimOrdinateEntity::PropertyWorkingSet.generateId(RDimOrdinateEntity::getRtti(), RObject::PropertyWorkingSet);
    RDimOrdinateEntity::PropertyType.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyType);
    RDimOrdinateEntity::PropertyBlock.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyBlock);
    RDimOrdinateEntity::PropertyLayer.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyLayer);
    RDimOrdinateEntity::PropertyLinetype.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyLinetype);
    RDimOrdinateEntity::PropertyLinetypeScale.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyLinetypeScale);
    RDimOrdinateEntity::PropertyLineweight.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyLineweight);
    RDimOrdinateEntity::PropertyColor.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyColor);
    RDimOrdinateEntity::PropertyDisplayedColor.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyDisplayedColor);
    RDimOrdinateEntity::PropertyDrawOrder.generateId(RDimOrdinateEntity::getRtti(), REntity::PropertyDrawOrder);

    RDimOrdinateEntity::PropertyMiddleOfTextX.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextX);
    RDimOrdinateEntity::PropertyMiddleOfTextY.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextY);
    RDimOrdinateEntity::PropertyMiddleOfTextZ.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimOrdinateEntity::PropertyText.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyText);
    RDimOrdinateEntity::PropertyUpperTolerance.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyUpperTolerance);
    RDimOrdinateEntity::PropertyLowerTolerance.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyLowerTolerance);
    RDimOrdinateEntity::PropertyMeasuredValue.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyMeasuredValue);

    if (RPluginLoader::hasPlugin("DWG")) {
        RDimOrdinateEntity::PropertyFontName.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyFontName);
        RDimOrdinateEntity::PropertyTextRotation.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyTextRotation);
        //RDimOrdinateEntity::PropertyArrow1Flipped.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyArrow1Flipped);
        //RDimOrdinateEntity::PropertyArrow2Flipped.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyArrow2Flipped);

        //RDimOrdinateEntity::PropertyExtLineFix.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyExtLineFix);
        //RDimOrdinateEntity::PropertyExtLineFixLength.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyExtLineFixLength);

        RDimOrdinateEntity::PropertyDimscale.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyDimscale);
        RDimOrdinateEntity::PropertyDimlfac.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyDimlfac);
    }

    RDimOrdinateEntity::PropertyDimBlockName.generateId(RDimOrdinateEntity::getRtti(), RDimensionEntity::PropertyDimBlockName);

    RDimOrdinateEntity::PropertyOriginX.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyOriginY.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyOriginZ.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);

    RDimOrdinateEntity::PropertyOrdinate.generateId(RDimOrdinateEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Ordinate"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyDefiningPointX.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Defining Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyDefiningPointY.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Defining Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyDefiningPointZ.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Defining Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyLeaderEndPointX.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Leader End Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyLeaderEndPointY.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Leader End Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimOrdinateEntity::PropertyLeaderEndPointZ.generateId(RDimOrdinateEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Leader End Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RDimOrdinateEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    if (PropertyOrdinate == propertyTypeId) {
        if (RS::getMetaType(value) == RS::Bool) {
            ret = ret || RObject::setMember(getData().xType, value.toBool(), true);
            data.autoTextPos = true;
        } else if (RS::getMetaType(value) == RS::String) {
            ret = ret || RObject::setMember(getData().xType, value.toString()=="X", true);
            data.autoTextPos = true;
        }
    }
    ret = ret || RObject::setMember(data.definitionPoint.x, value, PropertyOriginX == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.y, value, PropertyOriginY == propertyTypeId);
    ret = ret || RObject::setMember(data.definitionPoint.z, value, PropertyOriginZ == propertyTypeId);
    ret = ret || RObject::setMember(data.definingPoint.x, value, PropertyDefiningPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.definingPoint.y, value, PropertyDefiningPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.definingPoint.z, value, PropertyDefiningPointZ == propertyTypeId);
    ret = ret || RObject::setMember(data.leaderEndPoint.x, value, PropertyLeaderEndPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.leaderEndPoint.y, value, PropertyLeaderEndPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.leaderEndPoint.z, value, PropertyLeaderEndPointZ == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimOrdinateEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyOrdinate) {
        if (humanReadable) {
            RPropertyAttributes attr;
            if (!noAttributes) {
                attr.setChoices(QSet<QString>() << "X" << "Y");
            }
            return qMakePair(QVariant(data.xType ? "X" : "Y"), attr);
        }
        else {
            return qMakePair(QVariant(data.xType), RPropertyAttributes());
        }
    } else if (propertyTypeId == PropertyOriginX) {
        return qMakePair(QVariant(data.definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyOriginY) {
        return qMakePair(QVariant(data.definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyOriginZ) {
        return qMakePair(QVariant(data.definitionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDefiningPointX) {
        return qMakePair(QVariant(data.definingPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDefiningPointY) {
        return qMakePair(QVariant(data.definingPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDefiningPointZ) {
        return qMakePair(QVariant(data.definingPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLeaderEndPointX) {
        return qMakePair(QVariant(data.leaderEndPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLeaderEndPointY) {
        return qMakePair(QVariant(data.leaderEndPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLeaderEndPointZ) {
        return qMakePair(QVariant(data.leaderEndPoint.z), RPropertyAttributes());
    }

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimOrdinateEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimOrdinateEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", leaderEndPoint: " << getData().leaderEndPoint
                  << ", definingPoint: " << getData().definingPoint
                  << ", xType: " << getData().xType
                  << ")";
}
