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
#include "RArc.h"
#include "RCircle.h"
#include "RMetaTypes.h"
#include "REllipse.h"
#include "RExporter.h"
#include "RImageEntity.h"
#include "RLine.h"
#include "RPoint.h"
#include "RSpline.h"

RPropertyTypeId RImageEntity::PropertyCustom;
RPropertyTypeId RImageEntity::PropertyHandle;
RPropertyTypeId RImageEntity::PropertyProtected;
RPropertyTypeId RImageEntity::PropertyType;
RPropertyTypeId RImageEntity::PropertyBlock;
RPropertyTypeId RImageEntity::PropertyLayer;
RPropertyTypeId RImageEntity::PropertyLinetype;
RPropertyTypeId RImageEntity::PropertyLinetypeScale;
RPropertyTypeId RImageEntity::PropertyLineweight;
RPropertyTypeId RImageEntity::PropertyColor;
RPropertyTypeId RImageEntity::PropertyDrawOrder;

RPropertyTypeId RImageEntity::PropertyFileName;
RPropertyTypeId RImageEntity::PropertyInsertionPointX;
RPropertyTypeId RImageEntity::PropertyInsertionPointY;
RPropertyTypeId RImageEntity::PropertyInsertionPointZ;
RPropertyTypeId RImageEntity::PropertyScaleFactorX;
RPropertyTypeId RImageEntity::PropertyScaleFactorY;
RPropertyTypeId RImageEntity::PropertyWidth;
RPropertyTypeId RImageEntity::PropertyHeight;
RPropertyTypeId RImageEntity::PropertyAngle;
RPropertyTypeId RImageEntity::PropertyFade;

RImageEntity::RImageEntity(RDocument* document, const RImageData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {

    RDebug::incCounter("RImageEntity");
}

RImageEntity::RImageEntity(const RImageEntity& other) : REntity(other) {
    RDebug::incCounter("RImageEntity");
    data = other.data;
}

RImageEntity::~RImageEntity() {
    RDebug::decCounter("RImageEntity");
}

RImageEntity* RImageEntity::clone() const {
    return new RImageEntity(*this);
}

void RImageEntity::init() {
    RImageEntity::PropertyCustom.generateId(typeid(RImageEntity), RObject::PropertyCustom);
    RImageEntity::PropertyHandle.generateId(typeid(RImageEntity), RObject::PropertyHandle);
    RImageEntity::PropertyProtected.generateId(typeid(RImageEntity), RObject::PropertyProtected);
    RImageEntity::PropertyType.generateId(typeid(RImageEntity), REntity::PropertyType);
    RImageEntity::PropertyBlock.generateId(typeid(RImageEntity), REntity::PropertyBlock);
    RImageEntity::PropertyLayer.generateId(typeid(RImageEntity), REntity::PropertyLayer);
    RImageEntity::PropertyLinetype.generateId(typeid(RImageEntity), REntity::PropertyLinetype);
    RImageEntity::PropertyLinetypeScale.generateId(typeid(RImageEntity), REntity::PropertyLinetypeScale);
    RImageEntity::PropertyLineweight.generateId(typeid(RImageEntity), REntity::PropertyLineweight);
    RImageEntity::PropertyColor.generateId(typeid(RImageEntity), REntity::PropertyColor);
    RImageEntity::PropertyDrawOrder.generateId(typeid(RImageEntity), REntity::PropertyDrawOrder);

    RImageEntity::PropertyFileName.generateId(typeid(RImageEntity), "", QT_TRANSLATE_NOOP("REntity", "File"));

    RImageEntity::PropertyInsertionPointX.generateId(typeid(RImageEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RImageEntity::PropertyInsertionPointY.generateId(typeid(RImageEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RImageEntity::PropertyInsertionPointZ.generateId(typeid(RImageEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RImageEntity::PropertyScaleFactorX.generateId(typeid(RImageEntity), "", QT_TRANSLATE_NOOP("REntity", "Width Factor"));
    RImageEntity::PropertyScaleFactorY.generateId(typeid(RImageEntity), "", QT_TRANSLATE_NOOP("REntity", "Height Factor"));

    RImageEntity::PropertyWidth.generateId(typeid(RImageEntity), "", QT_TRANSLATE_NOOP("REntity", "Width"));
    RImageEntity::PropertyHeight.generateId(typeid(RImageEntity), "", QT_TRANSLATE_NOOP("REntity", "Height"));

    RImageEntity::PropertyAngle.generateId(typeid(RImageEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));

    RImageEntity::PropertyFade.generateId(typeid(RImageEntity), "", QT_TRANSLATE_NOOP("REntity", "Fade"));
}

bool RImageEntity::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    if (PropertyFileName == propertyTypeId) {
        data.fileName = value.toString();
        data.reload();
        ret = true;
    }

    ret = ret || RObject::setMember(data.insertionPoint.x, value, PropertyInsertionPointX == propertyTypeId);
    ret = ret || RObject::setMember(data.insertionPoint.y, value, PropertyInsertionPointY == propertyTypeId);
    ret = ret || RObject::setMember(data.insertionPoint.z, value, PropertyInsertionPointZ == propertyTypeId);

    if (PropertyScaleFactorX == propertyTypeId) {
        double s = fabs(value.toDouble());
        if (s<RS::PointTolerance) {
            return false;
        }
        data.uVector.setMagnitude2d(s);
        return true;
    }
    if (PropertyScaleFactorY == propertyTypeId) {
        double s = fabs(value.toDouble());
        if (s<RS::PointTolerance) {
            return false;
        }
        data.vVector.setMagnitude2d(s);
        return true;
    }
    if (PropertyWidth == propertyTypeId) {
        double w = fabs(value.toDouble());
        data.setWidth(w, true);
        return true;
    }
    if (PropertyHeight == propertyTypeId) {
        double h = fabs(value.toDouble());
        data.setHeight(h, true);
        return true;
    }
    if (PropertyAngle == propertyTypeId) {
        data.uVector.setAngle(value.toDouble());
        data.vVector.setAngle(value.toDouble() + M_PI/2);
        return true;
    }
    ret = ret || RObject::setMember(data.fade, value, PropertyFade == propertyTypeId);

    return ret;
}


QPair<QVariant, RPropertyAttributes> RImageEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyFileName) {
        return qMakePair(QVariant(data.fileName), RPropertyAttributes());
    } else if (propertyTypeId == PropertyInsertionPointX) {
        return qMakePair(QVariant(data.insertionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyInsertionPointY) {
        return qMakePair(QVariant(data.insertionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyInsertionPointZ) {
        return qMakePair(QVariant(data.insertionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleFactorX) {
        return qMakePair(QVariant(data.uVector.getMagnitude()), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleFactorY) {
        return qMakePair(QVariant(data.vVector.getMagnitude()), RPropertyAttributes());
    } else if (propertyTypeId == PropertyWidth) {
        return qMakePair(QVariant(data.uVector.getMagnitude() * data.getImage().width()), RPropertyAttributes());
    } else if (propertyTypeId == PropertyHeight) {
        return qMakePair(QVariant(data.vVector.getMagnitude() * data.getImage().height()), RPropertyAttributes());
    } else if (propertyTypeId == PropertyAngle) {
        return qMakePair(QVariant(data.uVector.getAngle()), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyFade) {
        return qMakePair(QVariant(data.fade), RPropertyAttributes(RPropertyAttributes::Percentage));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RImageEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.exportImage(data);
}

void RImageEntity::print(QDebug dbg) const {
    dbg.nospace() << "RImageEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", fileName: " << data.fileName
                  << ", uVector: " << data.uVector
                  << ", vVector: " << data.vVector
                  << ", insertionPoint: " << data.insertionPoint;
    dbg.nospace() << ")";
}
