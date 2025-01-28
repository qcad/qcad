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
#include "RSplineEntity.h"
#include "RDebug.h"
#include "RExporter.h"
#include "RS.h"

RPropertyTypeId RSplineEntity::PropertyCustom;
RPropertyTypeId RSplineEntity::PropertyHandle;
RPropertyTypeId RSplineEntity::PropertyProtected;
RPropertyTypeId RSplineEntity::PropertyWorkingSet;
RPropertyTypeId RSplineEntity::PropertyType;
RPropertyTypeId RSplineEntity::PropertyBlock;
RPropertyTypeId RSplineEntity::PropertyLayer;
RPropertyTypeId RSplineEntity::PropertyLinetype;
RPropertyTypeId RSplineEntity::PropertyLinetypeScale;
RPropertyTypeId RSplineEntity::PropertyLineweight;
RPropertyTypeId RSplineEntity::PropertyColor;
RPropertyTypeId RSplineEntity::PropertyDisplayedColor;
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
RPropertyTypeId RSplineEntity::PropertyLength;
RPropertyTypeId RSplineEntity::PropertyTotalLength;
// TODO: tangent support:
RPropertyTypeId RSplineEntity::PropertyUseStartTangent;
RPropertyTypeId RSplineEntity::PropertyStartTangentX;
RPropertyTypeId RSplineEntity::PropertyStartTangentY;
RPropertyTypeId RSplineEntity::PropertyStartTangentZ;
RPropertyTypeId RSplineEntity::PropertyUseEndTangent;
RPropertyTypeId RSplineEntity::PropertyEndTangentX;
RPropertyTypeId RSplineEntity::PropertyEndTangentY;
RPropertyTypeId RSplineEntity::PropertyEndTangentZ;

RSplineEntity::RSplineEntity(RDocument* document, const RSplineData& data) :
    REntity(document), data(document, data) {
    RDebug::incCounter("RSplineEntity");
}

RSplineEntity::RSplineEntity(const RSplineEntity& other) : REntity(other) {
    RDebug::incCounter("RSplineEntity");
    data = other.data;
}

RSplineEntity::~RSplineEntity() {
    RDebug::decCounter("RSplineEntity");
}

void RSplineEntity::init() {
    RSplineEntity::PropertyCustom.generateId(RSplineEntity::getRtti(), RObject::PropertyCustom);
    RSplineEntity::PropertyHandle.generateId(RSplineEntity::getRtti(), RObject::PropertyHandle);
    RSplineEntity::PropertyProtected.generateId(RSplineEntity::getRtti(), RObject::PropertyProtected);
    RSplineEntity::PropertyWorkingSet.generateId(RSplineEntity::getRtti(), RObject::PropertyWorkingSet);
    RSplineEntity::PropertyType.generateId(RSplineEntity::getRtti(), REntity::PropertyType);
    RSplineEntity::PropertyBlock.generateId(RSplineEntity::getRtti(), REntity::PropertyBlock);
    RSplineEntity::PropertyLayer.generateId(RSplineEntity::getRtti(), REntity::PropertyLayer);
    RSplineEntity::PropertyLinetype.generateId(RSplineEntity::getRtti(), REntity::PropertyLinetype);
    RSplineEntity::PropertyLinetypeScale.generateId(RSplineEntity::getRtti(), REntity::PropertyLinetypeScale);
    RSplineEntity::PropertyLineweight.generateId(RSplineEntity::getRtti(), REntity::PropertyLineweight);
    RSplineEntity::PropertyColor.generateId(RSplineEntity::getRtti(), REntity::PropertyColor);
    RSplineEntity::PropertyDisplayedColor.generateId(RSplineEntity::getRtti(), REntity::PropertyDisplayedColor);
    RSplineEntity::PropertyDrawOrder.generateId(RSplineEntity::getRtti(), REntity::PropertyDrawOrder);

    RSplineEntity::PropertyPeriodic.generateId(RSplineEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Closed Periodic"));
    RSplineEntity::PropertyDegree.generateId(RSplineEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Degree"));

    RSplineEntity::PropertyControlPointNX.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Control Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyControlPointNY.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Control Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyControlPointNZ.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Control Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyFitPointNX.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Fit Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyFitPointNY.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Fit Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyFitPointNZ.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Fit Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyKnotN.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Knot Vector"), QT_TRANSLATE_NOOP("REntity", "Knot"));

    RSplineEntity::PropertyLength.generateId(RSplineEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RSplineEntity::PropertyTotalLength.generateId(RSplineEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));

    // TODO: tangent support:
    RSplineEntity::PropertyUseStartTangent.generateId(RSplineEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Use Start Tangent"));
    RSplineEntity::PropertyStartTangentX.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Start Tangent"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyStartTangentY.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Start Tangent"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyStartTangentZ.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Start Tangent"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyUseEndTangent.generateId(RSplineEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Use End Tangent"));
    RSplineEntity::PropertyEndTangentX.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "End Tangent"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyEndTangentY.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "End Tangent"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RSplineEntity::PropertyEndTangentZ.generateId(RSplineEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "End Tangent"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RSplineEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);
    ret = ret || RObject::setMemberX(data.controlPoints, value, PropertyControlPointNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.controlPoints, value, PropertyControlPointNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.controlPoints, value, PropertyControlPointNZ == propertyTypeId);
    ret = ret || RObject::setMemberX(data.fitPoints, value, PropertyFitPointNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.fitPoints, value, PropertyFitPointNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.fitPoints, value, PropertyFitPointNZ == propertyTypeId);
    ret = ret || RObject::setMember(data.knotVector, value, PropertyKnotN == propertyTypeId);

    if (PropertyPeriodic == propertyTypeId) {
        data.setPeriodic(value.toBool());
        ret = true;
    }

    // TODO: tangent support:
    ret = ret || RObject::setMember(data.tangentStart.valid, value, PropertyUseStartTangent == propertyTypeId);
    ret = ret || RObject::setMember(data.tangentStart.x, value, PropertyStartTangentX == propertyTypeId);
    ret = ret || RObject::setMember(data.tangentStart.y, value, PropertyStartTangentY == propertyTypeId);
    ret = ret || RObject::setMember(data.tangentStart.z, value, PropertyStartTangentZ == propertyTypeId);

    ret = ret || RObject::setMember(data.tangentEnd.valid, value, PropertyUseEndTangent == propertyTypeId);
    ret = ret || RObject::setMember(data.tangentEnd.x, value, PropertyEndTangentX == propertyTypeId);
    ret = ret || RObject::setMember(data.tangentEnd.y, value, PropertyEndTangentY == propertyTypeId);
    ret = ret || RObject::setMember(data.tangentEnd.z, value, PropertyEndTangentZ == propertyTypeId);

    // TODO:
//    if  (propertyTypeId==PropertyFitPointNX || propertyTypeId==PropertyFitPointNY || propertyTypeId==PropertyFitPointNZ) {
//        data.controlPoints.clear();
//    }

    if (PropertyDegree == propertyTypeId) {
        if (RS::getMetaType(value)==RS::Int) {
            ret = ret || RObject::setMember(data.degree, value);
        }
        else if (RS::getMetaType(value)==RS::String) {
            ret = ret || RObject::setMember(data.degree, value.toString().toInt());
        }
    }

    if (ret) {
        data.RSpline::update();
//        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RSplineEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes, bool showOnRequest) {

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

        // TODO: tangent support:
        if (propertyTypeId == PropertyUseStartTangent) {
            return qMakePair(QVariant(data.tangentStart.valid), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyStartTangentX) {
            return qMakePair(QVariant(data.tangentStart.x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyStartTangentY) {
            return qMakePair(QVariant(data.tangentStart.y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyStartTangentZ) {
            return qMakePair(QVariant(data.tangentStart.z), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyUseEndTangent) {
            return qMakePair(QVariant(data.tangentEnd.valid), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyEndTangentX) {
            return qMakePair(QVariant(data.tangentEnd.x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyEndTangentY) {
            return qMakePair(QVariant(data.tangentEnd.y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyEndTangentZ) {
            return qMakePair(QVariant(data.tangentEnd.z), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
    }

    if (!data.knotVector.isEmpty()) {
        if (propertyTypeId == PropertyKnotN) {
            QVariant v;
            v.setValue(data.knotVector);
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List | RPropertyAttributes::ReadOnly));
        }
    }

    if (propertyTypeId == PropertyPeriodic) {
        return qMakePair(QVariant(data.isPeriodic()), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyDegree) {
        RPropertyAttributes attr;
        QSet<QString> choices;
        for (int d=1; d<=data.controlPoints.count()-1; d++) {
            if (d==3 || !data.hasFitPoints()) {
                choices.insert(QString("%1").arg(d));
            }
        }
        attr.setChoices(choices);
        attr.setNumericallySorted(true);
        return qMakePair(QVariant(QString("%1").arg(data.degree)), attr);
    }

    // human readable properties (not relevant for transactions):
    if (humanReadable) {
        if (propertyTypeId==PropertyLength) {
            return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Redundant|RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId==PropertyTotalLength) {
            return qMakePair(QVariant(data.getLength()), RPropertyAttributes(RPropertyAttributes::Sum));
        }
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RSplineEntity::setShape(const RSpline& s) {
    data.setShape(s);
}

void RSplineEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)
    Q_UNUSED(forceSelected)

    e.setBrush(Qt::NoBrush);
    e.exportSpline(data);
}

void RSplineEntity::print(QDebug dbg) const {
    dbg.nospace() << "RSplineEntity(";
    REntity::print(dbg);
    dbg.nospace() << getData();
    dbg.nospace() << ")";
}

int RSplineEntity::getComplexity() const {
    return qMax(data.countControlPoints()*64, data.countFitPoints()*64);
}
