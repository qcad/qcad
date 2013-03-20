/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RSplineEntity.h"
#include "RMetaTypes.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RSplineEntity::PropertyCustom;
RPropertyTypeId RSplineEntity::PropertyHandle;
RPropertyTypeId RSplineEntity::PropertyType;
RPropertyTypeId RSplineEntity::PropertyBlock;
RPropertyTypeId RSplineEntity::PropertyLayer;
RPropertyTypeId RSplineEntity::PropertyLinetype;
RPropertyTypeId RSplineEntity::PropertyLineweight;
RPropertyTypeId RSplineEntity::PropertyColor;
RPropertyTypeId RSplineEntity::PropertyDrawOrder;
RPropertyTypeId RSplineEntity::PropertyControlPointNX;
RPropertyTypeId RSplineEntity::PropertyControlPointNY;
RPropertyTypeId RSplineEntity::PropertyControlPointNZ;
RPropertyTypeId RSplineEntity::PropertyFitPointNX;
RPropertyTypeId RSplineEntity::PropertyFitPointNY;
RPropertyTypeId RSplineEntity::PropertyFitPointNZ;
RPropertyTypeId RSplineEntity::PropertyKnotN;
RPropertyTypeId RSplineEntity::PropertyPeriodic;
RPropertyTypeId RSplineEntity::PropertyDegree;

RSplineEntity::RSplineEntity(RDocument* document, const RSplineData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
}

RSplineEntity::~RSplineEntity() {
}

void RSplineEntity::init() {
    RSplineEntity::PropertyCustom.generateId(typeid(RSplineEntity), RObject::PropertyCustom);
    RSplineEntity::PropertyHandle.generateId(typeid(RSplineEntity), RObject::PropertyHandle);
    RSplineEntity::PropertyType.generateId(typeid(RSplineEntity), REntity::PropertyType);
    RSplineEntity::PropertyBlock.generateId(typeid(RSplineEntity), REntity::PropertyBlock);
    RSplineEntity::PropertyLayer.generateId(typeid(RSplineEntity), REntity::PropertyLayer);
    RSplineEntity::PropertyLinetype.generateId(typeid(RSplineEntity), REntity::PropertyLinetype);
    RSplineEntity::PropertyLineweight.generateId(typeid(RSplineEntity), REntity::PropertyLineweight);
    RSplineEntity::PropertyColor.generateId(typeid(RSplineEntity), REntity::PropertyColor);
    RSplineEntity::PropertyDrawOrder.generateId(typeid(RSplineEntity), REntity::PropertyDrawOrder);
    RSplineEntity::PropertyPeriodic.generateId(typeid(RSplineEntity), "", QT_TRANSLATE_NOOP("REntity", "Closed Periodic"));
    RSplineEntity::PropertyDegree.generateId(typeid(RSplineEntity), "", QT_TRANSLATE_NOOP("REntity", "Degree"));
    RSplineEntity::PropertyControlPointNX.generateId(typeid(RSplineEntity), QT_TRANSLATE_NOOP("REntity", "Control Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RSplineEntity::PropertyControlPointNY.generateId(typeid(RSplineEntity), QT_TRANSLATE_NOOP("REntity", "Control Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RSplineEntity::PropertyControlPointNZ.generateId(typeid(RSplineEntity), QT_TRANSLATE_NOOP("REntity", "Control Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RSplineEntity::PropertyFitPointNX.generateId(typeid(RSplineEntity), QT_TRANSLATE_NOOP("REntity", "Fit Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RSplineEntity::PropertyFitPointNY.generateId(typeid(RSplineEntity), QT_TRANSLATE_NOOP("REntity", "Fit Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RSplineEntity::PropertyFitPointNZ.generateId(typeid(RSplineEntity), QT_TRANSLATE_NOOP("REntity", "Fit Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
    //RSplineEntity::PropertyKnotN.generateId(typeid(RSplineEntity), QT_TRANSLATE_NOOP("REntity", "Knot Vector"), QT_TRANSLATE_NOOP("REntity", "Knot"));
}

bool RSplineEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value) {
    bool ret = REntity::setProperty(propertyTypeId, value);
    ret = ret || RObject::setMemberX(data.controlPoints, value, PropertyControlPointNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.controlPoints, value, PropertyControlPointNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.controlPoints, value, PropertyControlPointNZ == propertyTypeId);
    ret = ret || RObject::setMemberX(data.fitPoints, value, PropertyFitPointNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.fitPoints, value, PropertyFitPointNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.fitPoints, value, PropertyFitPointNZ == propertyTypeId);
    //ret = ret || RObject::setMember(data.knotVector, value, PropertyKnotN == propertyTypeId);
    ret = ret || RObject::setMember(data.periodic, value, PropertyPeriodic == propertyTypeId);

    if (PropertyDegree == propertyTypeId) {
        if (value.type()==QVariant::Int) {
            ret = ret || RObject::setMember(data.degree, value);
        }
        else if (value.type()==QVariant::String) {
            ret = ret || RObject::setMember(data.degree, value.toString().toInt());
        }
    }


    if (ret) {
//        data.RSpline::update();
        data.updateInternal();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RSplineEntity::getProperty(
        RPropertyTypeId propertyTypeId, bool humanReadable,
        bool noAttributes) {

    if (propertyTypeId == PropertyType) {
        return qMakePair(QVariant(RS::EntitySpline),
            RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }

    if (!data.controlPoints.isEmpty() && data.fitPoints.isEmpty()) {
        if (propertyTypeId == PropertyControlPointNX) {
            QVariant v;
            v.setValue(RVector::getXList(data.controlPoints));
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
        } else if (propertyTypeId == PropertyControlPointNY) {
            QVariant v;
            v.setValue(RVector::getYList(data.controlPoints));
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
        } else if (propertyTypeId == PropertyControlPointNZ) {
            QVariant v;
            v.setValue(RVector::getZList(data.controlPoints));
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
        }
    }

    if (!data.fitPoints.isEmpty()) {
        if (propertyTypeId == PropertyFitPointNX) {
            QVariant v;
            v.setValue(RVector::getXList(data.fitPoints));
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
        } else if (propertyTypeId == PropertyFitPointNY) {
            QVariant v;
            v.setValue(RVector::getYList(data.fitPoints));
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
        } else if (propertyTypeId == PropertyFitPointNZ) {
            QVariant v;
            v.setValue(RVector::getZList(data.fitPoints));
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
        }
    }

//    if (!data.knotVector.isEmpty()) {
//        if (propertyTypeId == PropertyKnotN) {
//            QVariant v;
//            v.setValue(data.knotVector);
//            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
//        }
//    }

    if (propertyTypeId == PropertyPeriodic) {
//        return qMakePair(QVariant(data.periodic), RPropertyAttributes());
        return qMakePair(QVariant(data.isPeriodic()), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyDegree) {
        RPropertyAttributes attr;
        QSet<QString> choices;
        if (!data.hasFitPoints()) {
            choices.insert("2");
        }
        choices.insert("3");
        attr.setChoices(choices);
        return qMakePair(QVariant(QString("%1").arg(data.degree)), attr);
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RSplineEntity::exportEntity(RExporter& e, bool preview) const {
    Q_UNUSED(preview);

    e.setBrush(Qt::NoBrush);
    e.exportSpline(data);
}

void RSplineEntity::print(QDebug dbg) const {
    dbg.nospace() << "RSplineEntity(";
    REntity::print(dbg);

    dbg.nospace() << getData();

    /*
    dbg.nospace() << "\nclosed: " << isClosed();
    dbg.nospace() << "\nperiodic: " << isPeriodic();

    QList<RVector> controlPoints = getControlPointsWrapped();
    dbg.nospace() << "\ncontrolPoints (" << controlPoints.count() << "): ";
    for (int i=0; i<controlPoints.count(); ++i) {
        dbg.nospace() << i << ": " << controlPoints.at(i);
    }

    QList<RVector> controlPoints = getControlPointsWrapped();
    dbg.nospace() << "\ncontrolPoints (" << controlPoints.count() << "): ";
    for (int i=0; i<controlPoints.count(); ++i) {
        dbg.nospace() << i << ": " << controlPoints.at(i);
    }

    QList<RVector> fitPoints = getFitPoints();
    dbg.nospace() << "\nfitPoints (" << fitPoints.count() << "): ";
    for (int i=0; i<fitPoints.count(); ++i) {
        dbg.nospace() << i << ": " << fitPoints.at(i) << ", ";
    }

    QList<double> knotVector = getKnotVector();
    dbg.nospace() << "\nknots (" << knotVector.count() << "): ";
    for (int i=0; i<knotVector.count(); ++i) {
        dbg.nospace() << i << ": " << knotVector.at(i) << ", ";
    }
    */

    dbg.nospace() << ")";
}

int RSplineEntity::getComplexity() const {
    //##return getData().getExploded().count();
    return qMax(data.countControlPoints()*64, data.countFitPoints()*64);
}
