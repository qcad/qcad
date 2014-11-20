/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

RPropertyTypeId RDimOrdinateEntity::PropertyCustom;
RPropertyTypeId RDimOrdinateEntity::PropertyHandle;
RPropertyTypeId RDimOrdinateEntity::PropertyType;
RPropertyTypeId RDimOrdinateEntity::PropertyBlock;
RPropertyTypeId RDimOrdinateEntity::PropertyLayer;
RPropertyTypeId RDimOrdinateEntity::PropertyLinetype;
RPropertyTypeId RDimOrdinateEntity::PropertyLinetypeScale;
RPropertyTypeId RDimOrdinateEntity::PropertyLineweight;
RPropertyTypeId RDimOrdinateEntity::PropertyColor;
RPropertyTypeId RDimOrdinateEntity::PropertyDrawOrder;

RPropertyTypeId RDimOrdinateEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimOrdinateEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimOrdinateEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimOrdinateEntity::PropertyText;
RPropertyTypeId RDimOrdinateEntity::PropertyUpperTolerance;
RPropertyTypeId RDimOrdinateEntity::PropertyLowerTolerance;
RPropertyTypeId RDimOrdinateEntity::PropertyMeasuredValue;
RPropertyTypeId RDimOrdinateEntity::PropertyFontName;

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


RDimOrdinateEntity::RDimOrdinateEntity(RDocument* document, const RDimOrdinateData& data, RObject::Id objectId) :
    RDimensionEntity(document, objectId), data(document, data) {
}

RDimOrdinateEntity::~RDimOrdinateEntity() {
}

void RDimOrdinateEntity::init() {
    RDimOrdinateEntity::PropertyCustom.generateId(typeid(RDimOrdinateEntity), RObject::PropertyCustom);
    RDimOrdinateEntity::PropertyHandle.generateId(typeid(RDimOrdinateEntity), RObject::PropertyHandle);
    RDimOrdinateEntity::PropertyType.generateId(typeid(RDimOrdinateEntity), REntity::PropertyType);
    RDimOrdinateEntity::PropertyBlock.generateId(typeid(RDimOrdinateEntity), REntity::PropertyBlock);
    RDimOrdinateEntity::PropertyLayer.generateId(typeid(RDimOrdinateEntity), REntity::PropertyLayer);
    RDimOrdinateEntity::PropertyLinetype.generateId(typeid(RDimOrdinateEntity), REntity::PropertyLinetype);
    RDimOrdinateEntity::PropertyLinetypeScale.generateId(typeid(RDimOrdinateEntity), REntity::PropertyLinetypeScale);
    RDimOrdinateEntity::PropertyLineweight.generateId(typeid(RDimOrdinateEntity), REntity::PropertyLineweight);
    RDimOrdinateEntity::PropertyColor.generateId(typeid(RDimOrdinateEntity), REntity::PropertyColor);
    RDimOrdinateEntity::PropertyDrawOrder.generateId(typeid(RDimOrdinateEntity), REntity::PropertyDrawOrder);

    RDimOrdinateEntity::PropertyMiddleOfTextX.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyMiddleOfTextX);
    RDimOrdinateEntity::PropertyMiddleOfTextY.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyMiddleOfTextY);
    RDimOrdinateEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyMiddleOfTextZ);
    RDimOrdinateEntity::PropertyText.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyText);
    RDimOrdinateEntity::PropertyUpperTolerance.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyUpperTolerance);
    RDimOrdinateEntity::PropertyLowerTolerance.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyLowerTolerance);
    RDimOrdinateEntity::PropertyMeasuredValue.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyMeasuredValue);
    RDimOrdinateEntity::PropertyFontName.generateId(typeid(RDimOrdinateEntity), RDimensionEntity::PropertyFontName);

    RDimOrdinateEntity::PropertyOriginX.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimOrdinateEntity::PropertyOriginY.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimOrdinateEntity::PropertyOriginZ.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RDimOrdinateEntity::PropertyOrdinate.generateId(typeid(RDimOrdinateEntity), "", QT_TRANSLATE_NOOP("REntity", "Ordinate"));
    RDimOrdinateEntity::PropertyDefiningPointX.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Defining Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimOrdinateEntity::PropertyDefiningPointY.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Defining Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimOrdinateEntity::PropertyDefiningPointZ.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Defining Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RDimOrdinateEntity::PropertyLeaderEndPointX.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Leader End Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimOrdinateEntity::PropertyLeaderEndPointY.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Leader End Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimOrdinateEntity::PropertyLeaderEndPointZ.generateId(typeid(RDimOrdinateEntity), QT_TRANSLATE_NOOP("REntity", "Leader End Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
}

bool RDimOrdinateEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = RDimensionEntity::setProperty(propertyTypeId, value, transaction);

    if (PropertyOrdinate == propertyTypeId) {
        if (value.type() == QVariant::Bool) {
            ret = ret || RObject::setMember(getData().xType, value.toBool(), true);
            data.autoTextPos = true;
        } else if (value.type() == QVariant::String) {
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
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
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

    return RDimensionEntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}

void RDimOrdinateEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimOrdinateEntity(";
    RDimensionEntity::print(dbg);
    dbg.nospace() << ", leaderEndPoint: " << getData().leaderEndPoint
                  << ", definingPoint: " << getData().definingPoint
                  << ", xType: " << getData().xType
                  << ")";
}
