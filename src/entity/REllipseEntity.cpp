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
#include "RArcEntity.h"
#include "REllipseEntity.h"
#include "RExporter.h"
#include "RPoint.h"

RPropertyTypeId REllipseEntity::PropertyCustom;
RPropertyTypeId REllipseEntity::PropertyHandle;
RPropertyTypeId REllipseEntity::PropertyProtected;
RPropertyTypeId REllipseEntity::PropertyWorkingSet;
RPropertyTypeId REllipseEntity::PropertyType;
RPropertyTypeId REllipseEntity::PropertyBlock;
RPropertyTypeId REllipseEntity::PropertyLayer;
RPropertyTypeId REllipseEntity::PropertyLinetype;
RPropertyTypeId REllipseEntity::PropertyLinetypeScale;
RPropertyTypeId REllipseEntity::PropertyLineweight;
RPropertyTypeId REllipseEntity::PropertyColor;
RPropertyTypeId REllipseEntity::PropertyDisplayedColor;
RPropertyTypeId REllipseEntity::PropertyDrawOrder;

RPropertyTypeId REllipseEntity::PropertyCenterX;
RPropertyTypeId REllipseEntity::PropertyCenterY;
RPropertyTypeId REllipseEntity::PropertyCenterZ;
RPropertyTypeId REllipseEntity::PropertyMajorPointX;
RPropertyTypeId REllipseEntity::PropertyMajorPointY;
RPropertyTypeId REllipseEntity::PropertyMajorPointZ;
RPropertyTypeId REllipseEntity::PropertyRatio;
RPropertyTypeId REllipseEntity::PropertyStartParam;
RPropertyTypeId REllipseEntity::PropertyEndParam;
RPropertyTypeId REllipseEntity::PropertyStartAngle;
RPropertyTypeId REllipseEntity::PropertyEndAngle;
RPropertyTypeId REllipseEntity::PropertyReversed;

RPropertyTypeId REllipseEntity::PropertyStartPointX;
RPropertyTypeId REllipseEntity::PropertyStartPointY;
RPropertyTypeId REllipseEntity::PropertyStartPointZ;
RPropertyTypeId REllipseEntity::PropertyEndPointX;
RPropertyTypeId REllipseEntity::PropertyEndPointY;
RPropertyTypeId REllipseEntity::PropertyEndPointZ;

RPropertyTypeId REllipseEntity::PropertyCircumference;

REllipseEntity::REllipseEntity(RDocument* document, const REllipseData& data) :
    REntity(document), data(document, data) {
}

REllipseEntity::~REllipseEntity() {
}

void REllipseEntity::init() {
    REllipseEntity::PropertyCustom.generateId(typeid(REllipseEntity), RObject::PropertyCustom);
    REllipseEntity::PropertyHandle.generateId(typeid(REllipseEntity), RObject::PropertyHandle);
    REllipseEntity::PropertyProtected.generateId(typeid(REllipseEntity), RObject::PropertyProtected);
    REllipseEntity::PropertyWorkingSet.generateId(typeid(REllipseEntity), RObject::PropertyWorkingSet);
    REllipseEntity::PropertyType.generateId(typeid(REllipseEntity), REntity::PropertyType);
    REllipseEntity::PropertyBlock.generateId(typeid(REllipseEntity), REntity::PropertyBlock);
    REllipseEntity::PropertyLayer.generateId(typeid(REllipseEntity), REntity::PropertyLayer);
    REllipseEntity::PropertyLinetype.generateId(typeid(REllipseEntity), REntity::PropertyLinetype);
    REllipseEntity::PropertyLinetypeScale.generateId(typeid(REllipseEntity), REntity::PropertyLinetypeScale);
    REllipseEntity::PropertyLineweight.generateId(typeid(REllipseEntity), REntity::PropertyLineweight);
    REllipseEntity::PropertyColor.generateId(typeid(REllipseEntity), REntity::PropertyColor);
    REllipseEntity::PropertyDisplayedColor.generateId(typeid(REllipseEntity), REntity::PropertyDisplayedColor);
    REllipseEntity::PropertyDrawOrder.generateId(typeid(REllipseEntity), REntity::PropertyDrawOrder);

    REllipseEntity::PropertyCenterX.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyCenterY.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyCenterZ.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyMajorPointX.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Major Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyMajorPointY.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Major Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyMajorPointZ.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Major Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyRatio.generateId(typeid(REllipseEntity), "",QT_TRANSLATE_NOOP("REntity",  "Ratio"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyStartParam.generateId(typeid(REllipseEntity), "", QT_TRANSLATE_NOOP("REntity", "Start Parameter"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyEndParam.generateId(typeid(REllipseEntity), "", QT_TRANSLATE_NOOP("REntity", "End Parameter"), false, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyStartAngle.generateId(typeid(REllipseEntity), "", QT_TRANSLATE_NOOP("REntity", "Start Angle"), true, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyEndAngle.generateId(typeid(REllipseEntity), "", QT_TRANSLATE_NOOP("REntity", "End Angle"), true, RPropertyAttributes::Geometry);
    REllipseEntity::PropertyReversed.generateId(typeid(REllipseEntity), "", QT_TRANSLATE_NOOP("REntity", "Reversed"), false, RPropertyAttributes::Geometry);

    REllipseEntity::PropertyStartPointX.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Start Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    REllipseEntity::PropertyStartPointY.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Start Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    REllipseEntity::PropertyStartPointZ.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "Start Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
    REllipseEntity::PropertyEndPointX.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "End Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    REllipseEntity::PropertyEndPointY.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "End Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    REllipseEntity::PropertyEndPointZ.generateId(typeid(REllipseEntity), QT_TRANSLATE_NOOP("REntity", "End Point"), QT_TRANSLATE_NOOP("REntity", "Z"));

    REllipseEntity::PropertyCircumference.generateId(typeid(REllipseEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
}

bool REllipseEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);
    ret = ret || RObject::setMember(data.center.x, value, PropertyCenterX == propertyTypeId);
    ret = ret || RObject::setMember(data.center.y, value, PropertyCenterY == propertyTypeId);
    ret = ret || RObject::setMember(data.center.z, value, PropertyCenterZ == propertyTypeId);
    ret = ret || RObject::setMember(data.majorPoint.x, value, PropertyMajorPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.majorPoint.y, value, PropertyMajorPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.majorPoint.z, value, PropertyMajorPointZ == propertyTypeId);
    ret = ret || RObject::setMember(data.ratio, value, PropertyRatio == propertyTypeId);
    ret = ret || RObject::setMember(data.startParam, value, PropertyStartParam == propertyTypeId);
    ret = ret || RObject::setMember(data.endParam, value, PropertyEndParam == propertyTypeId);
    if (PropertyStartAngle==propertyTypeId) {
        data.setStartAngle(value.toDouble());
        ret = true;
    }
    else if (PropertyEndAngle==propertyTypeId) {
        data.setEndAngle(value.toDouble());
        ret = true;
    }
    ret = ret || RObject::setMember(data.reversed, value, PropertyReversed == propertyTypeId);

    if (ret) {
        data.correctMajorMinor();
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> REllipseEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
    if (propertyTypeId == PropertyCenterX) {
        return qMakePair(QVariant(data.center.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterY) {
        return qMakePair(QVariant(data.center.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterZ) {
        return qMakePair(QVariant(data.center.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyMajorPointX) {
        return qMakePair(QVariant(data.majorPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyMajorPointY) {
        return qMakePair(QVariant(data.majorPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyMajorPointZ) {
        return qMakePair(QVariant(data.majorPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRatio) {
        return qMakePair(QVariant(data.ratio), RPropertyAttributes());
    } else if (propertyTypeId == PropertyStartParam) {
        return qMakePair(QVariant(data.startParam), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyEndParam) {
        return qMakePair(QVariant(data.endParam), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyStartAngle) {
        return qMakePair(QVariant(data.getStartAngle()), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyEndAngle) {
        return qMakePair(QVariant(data.getEndAngle()), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyReversed) {
        return qMakePair(QVariant(data.reversed), RPropertyAttributes());
    }

    // human readable properties (not relevant for transactions):
    if (humanReadable) {
        if (propertyTypeId == PropertyStartPointX) {
            return qMakePair(QVariant(data.getStartPoint().x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyStartPointY) {
            return qMakePair(QVariant(data.getStartPoint().y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyStartPointZ) {
            return qMakePair(QVariant(data.getStartPoint().z), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyEndPointX) {
            return qMakePair(QVariant(data.getEndPoint().x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyEndPointY) {
            return qMakePair(QVariant(data.getEndPoint().y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyEndPointZ) {
            return qMakePair(QVariant(data.getEndPoint().z), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyCircumference) {
            return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void REllipseEntity::setShape(const REllipse& e) {
    data.setCenter(e.getCenter());
    data.setMajorPoint(e.getMajorPoint());
    data.setRatio(e.getRatio());
    data.setStartParam(e.getStartParam());
    data.setEndParam(e.getEndParam());
    data.setReversed(e.isReversed());
}

void REllipseEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)
    Q_UNUSED(forceSelected)

    e.setBrush(Qt::NoBrush);
    e.exportEllipse(data);
}

QSharedPointer<REntity> REllipseEntity::scaleNonUniform(const RVector& scaleFactors, const RVector& center) {
    return RArcEntity::scaleNonUniform(*this, scaleFactors, center);
}

void REllipseEntity::print(QDebug dbg) const {
    dbg.nospace() << "REllipseEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", center: " << getCenter();
    dbg.nospace() << ", majorPoint: " << getMajorPoint();
    dbg.nospace() << ", ratio: " << getRatio();
    dbg.nospace() << ", startAngle: " << getStartAngle();
    dbg.nospace() << ", endAngle: " << getEndAngle();
    dbg.nospace() << ", reversed: " << isReversed() << ")";
}
