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
#include "RCircleEntity.h"
#include "REllipseEntity.h"
#include "RExporter.h"
#include "RPoint.h"

RPropertyTypeId RArcEntity::PropertyCustom;
RPropertyTypeId RArcEntity::PropertyHandle;
RPropertyTypeId RArcEntity::PropertyProtected;
RPropertyTypeId RArcEntity::PropertyWorkingSet;
RPropertyTypeId RArcEntity::PropertyType;
RPropertyTypeId RArcEntity::PropertyBlock;
RPropertyTypeId RArcEntity::PropertyLayer;
RPropertyTypeId RArcEntity::PropertyLinetype;
RPropertyTypeId RArcEntity::PropertyLinetypeScale;
RPropertyTypeId RArcEntity::PropertyLineweight;
RPropertyTypeId RArcEntity::PropertyColor;
RPropertyTypeId RArcEntity::PropertyDisplayedColor;
RPropertyTypeId RArcEntity::PropertyDrawOrder;

RPropertyTypeId RArcEntity::PropertyCenterX;
RPropertyTypeId RArcEntity::PropertyCenterY;
RPropertyTypeId RArcEntity::PropertyCenterZ;
RPropertyTypeId RArcEntity::PropertyRadius;
RPropertyTypeId RArcEntity::PropertyStartAngle;
RPropertyTypeId RArcEntity::PropertyEndAngle;
RPropertyTypeId RArcEntity::PropertyReversed;

RPropertyTypeId RArcEntity::PropertyDiameter;
RPropertyTypeId RArcEntity::PropertyLength;
RPropertyTypeId RArcEntity::PropertyTotalLength;
RPropertyTypeId RArcEntity::PropertySweepAngle;
RPropertyTypeId RArcEntity::PropertyArea;
RPropertyTypeId RArcEntity::PropertyTotalArea;

RArcEntity::RArcEntity(RDocument* document, const RArcData& data) :
    REntity(document), data(document, data) {
    RDebug::incCounter("RArcEntity");
}

RArcEntity::RArcEntity(const RArcEntity& other) : REntity(other) {
    RDebug::incCounter("RArcEntity");
    REntity::operator=(other);
    data = other.data;
}

RArcEntity::~RArcEntity() {
    RDebug::decCounter("RArcEntity");
}

void RArcEntity::setShape(const RArc& a) {
    data.setCenter(a.getCenter());
    data.setRadius(a.getRadius());
    data.setStartAngle(a.getStartAngle());
    data.setEndAngle(a.getEndAngle());
    data.setReversed(a.isReversed());
}

void RArcEntity::init() {
    RArcEntity::PropertyCustom.generateId(typeid(RArcEntity), RObject::PropertyCustom);
    RArcEntity::PropertyHandle.generateId(typeid(RArcEntity), RObject::PropertyHandle);
    RArcEntity::PropertyProtected.generateId(typeid(RArcEntity), RObject::PropertyProtected);
    RArcEntity::PropertyWorkingSet.generateId(typeid(RArcEntity), RObject::PropertyWorkingSet);
    RArcEntity::PropertyType.generateId(typeid(RArcEntity), REntity::PropertyType);
    RArcEntity::PropertyBlock.generateId(typeid(RArcEntity), REntity::PropertyBlock);
    RArcEntity::PropertyLayer.generateId(typeid(RArcEntity), REntity::PropertyLayer);
    RArcEntity::PropertyLinetype.generateId(typeid(RArcEntity), REntity::PropertyLinetype);
    RArcEntity::PropertyLinetypeScale.generateId(typeid(RArcEntity), REntity::PropertyLinetypeScale);
    RArcEntity::PropertyLineweight.generateId(typeid(RArcEntity), REntity::PropertyLineweight);
    RArcEntity::PropertyColor.generateId(typeid(RArcEntity), REntity::PropertyColor);
    RArcEntity::PropertyDisplayedColor.generateId(typeid(RArcEntity), REntity::PropertyDisplayedColor);
    RArcEntity::PropertyDrawOrder.generateId(typeid(RArcEntity), REntity::PropertyDrawOrder);

    RArcEntity::PropertyCenterX.generateId(typeid(RArcEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RArcEntity::PropertyCenterY.generateId(typeid(RArcEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RArcEntity::PropertyCenterZ.generateId(typeid(RArcEntity), QT_TRANSLATE_NOOP("REntity", "Center"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RArcEntity::PropertyRadius.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Radius"), false, RPropertyAttributes::Geometry);
    RArcEntity::PropertyStartAngle.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Start Angle"), false, RPropertyAttributes::Geometry);
    RArcEntity::PropertyEndAngle.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "End Angle"), false, RPropertyAttributes::Geometry);
    RArcEntity::PropertyReversed.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Reversed"), false, RPropertyAttributes::Geometry);

    RArcEntity::PropertyDiameter.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Diameter"));
    RArcEntity::PropertyLength.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RArcEntity::PropertyTotalLength.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));
    RArcEntity::PropertySweepAngle.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Sweep Angle"));
    RArcEntity::PropertyArea.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Area"));
    RArcEntity::PropertyTotalArea.generateId(typeid(RArcEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Area"));
}

bool RArcEntity::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.center.x, value, PropertyCenterX
            == propertyTypeId);
    ret = ret || RObject::setMember(data.center.y, value, PropertyCenterY
            == propertyTypeId);
    ret = ret || RObject::setMember(data.center.z, value, PropertyCenterZ
            == propertyTypeId);
    ret = ret || RObject::setMember(data.radius, value, PropertyRadius
            == propertyTypeId);
    ret = ret || RObject::setMember(data.startAngle,
            RMath::getNormalizedAngle(value.toDouble()), PropertyStartAngle == propertyTypeId);
    ret = ret || RObject::setMember(data.endAngle,
            RMath::getNormalizedAngle(value.toDouble()), PropertyEndAngle == propertyTypeId);
    ret = ret || RObject::setMember(data.reversed, value, PropertyReversed
            == propertyTypeId);

    if (propertyTypeId==PropertyDiameter) {
        data.setDiameter(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyLength) {
        data.setLength(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertySweepAngle) {
        data.setSweep(value.toDouble());
        ret = true;
    }
    else if (propertyTypeId==PropertyArea) {
        data.setArea(value.toDouble());
        ret = true;
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RArcEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyCenterX) {
        return qMakePair(QVariant(data.center.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterY) {
        return qMakePair(QVariant(data.center.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterZ) {
        return qMakePair(QVariant(data.center.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRadius) {
        return qMakePair(QVariant(data.radius), RPropertyAttributes());
    } else if (propertyTypeId == PropertyStartAngle) {
        return qMakePair(QVariant(data.startAngle), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyEndAngle) {
        return qMakePair(QVariant(data.endAngle), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyReversed) {
        return qMakePair(QVariant(data.reversed), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDiameter) {
        return qMakePair(QVariant(data.getDiameter()), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertyLength) {
        return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertyTotalLength) {
        return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Sum));
    } else if (propertyTypeId == PropertySweepAngle) {
        return qMakePair(QVariant(data.getSweep()), RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyArea) {
        return qMakePair(QVariant(data.getArea()), RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::Area));
    } else if (propertyTypeId == PropertyTotalArea) {
        if (showOnRequest) {
            QVariant v;
            v.setValue(data.getArea());
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Sum|RPropertyAttributes::Area));
        }
        else {
            QVariant v;
            v.setValue(0.0);
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::OnRequest|RPropertyAttributes::Area));
        }
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RArcEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.setBrush(Qt::NoBrush);
    e.exportArc(data);
}

QSharedPointer<REntity> RArcEntity::scaleNonUniform(const RVector& scaleFactors, const RVector& center) {
    return scaleNonUniform(*this, scaleFactors, center);
}

QSharedPointer<REntity> RArcEntity::scaleNonUniform(REntity& entity, const RVector& scaleFactors, const RVector& center) {
    RShape* s = entity.castToShape();
    if (s==NULL) {
        return QSharedPointer<REntity>();
    }

    RShapeTransformationScale scale(scaleFactors, center);
    QSharedPointer<RShape> shapeT = RShape::transformArc(*s, scale);
    if (shapeT.isNull()) {
        return QSharedPointer<REntity>();
    }

    if (RShape::isEllipseShape(*shapeT)) {
        QSharedPointer<REllipse> ellipseT = shapeT.dynamicCast<REllipse>();
        if (ellipseT.isNull()) {
            return QSharedPointer<REntity>();
        }
        REllipseEntity* e = new REllipseEntity(entity.getDocument(), REllipseData(*ellipseT));
        return QSharedPointer<REntity>(e);
    }
    else if (RShape::isArcShape(*shapeT)) {
        QSharedPointer<RArc> arcT = shapeT.dynamicCast<RArc>();
        if (arcT.isNull()) {
            return QSharedPointer<REntity>();
        }
        RArcEntity* arcEntity = dynamic_cast<RArcEntity*>(&entity);
        if (arcEntity==NULL) {
            return QSharedPointer<REntity>();
        }
        RArcEntity* cl = arcEntity->clone();
        cl->setShape(*arcT);
        return QSharedPointer<REntity>(cl);
    }
    else if (RShape::isCircleShape(*shapeT)) {
        QSharedPointer<RCircle> circleT = shapeT.dynamicCast<RCircle>();
        if (circleT.isNull()) {
            return QSharedPointer<REntity>();
        }
        RCircleEntity* e = new RCircleEntity(entity.getDocument(), RCircleData(*circleT));
        return QSharedPointer<REntity>(e);
    }

    qWarning() << "Unexpected shape returned from RShape::transformArc";
    return QSharedPointer<REntity>();

}

void RArcEntity::print(QDebug dbg) const {
    dbg.nospace() << "RArcEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", center: " << getCenter();
    dbg.nospace() << ", radius: " << getRadius();
    dbg.nospace() << ", startAngle: " << RMath::rad2deg(getStartAngle());
    dbg.nospace() << ", endAngle: " << RMath::rad2deg(getEndAngle());
    dbg.nospace() << ", reversed: " << isReversed() << ")";
}
