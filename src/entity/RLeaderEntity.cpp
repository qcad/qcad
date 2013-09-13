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
#include "RMetaTypes.h"
#include "RExporter.h"
#include "RLeaderEntity.h"

RPropertyTypeId RLeaderEntity::PropertyCustom;
RPropertyTypeId RLeaderEntity::PropertyHandle;
RPropertyTypeId RLeaderEntity::PropertyType;
RPropertyTypeId RLeaderEntity::PropertyBlock;
RPropertyTypeId RLeaderEntity::PropertyLayer;
RPropertyTypeId RLeaderEntity::PropertyLinetype;
RPropertyTypeId RLeaderEntity::PropertyLineweight;
RPropertyTypeId RLeaderEntity::PropertyColor;
RPropertyTypeId RLeaderEntity::PropertyDrawOrder;

RPropertyTypeId RLeaderEntity::PropertyArrowHead;
RPropertyTypeId RLeaderEntity::PropertyVertexNX;
RPropertyTypeId RLeaderEntity::PropertyVertexNY;
RPropertyTypeId RLeaderEntity::PropertyVertexNZ;


RLeaderEntity::RLeaderEntity(RDocument* document, const RLeaderData& data, RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
}

RLeaderEntity::~RLeaderEntity() {
}

void RLeaderEntity::init() {
    RLeaderEntity::PropertyCustom.generateId(typeid(RLeaderEntity), RObject::PropertyCustom);
    RLeaderEntity::PropertyHandle.generateId(typeid(RLeaderEntity), RObject::PropertyHandle);
    RLeaderEntity::PropertyType.generateId(typeid(RLeaderEntity), REntity::PropertyType);
    RLeaderEntity::PropertyBlock.generateId(typeid(RLeaderEntity), REntity::PropertyBlock);
    RLeaderEntity::PropertyLayer.generateId(typeid(RLeaderEntity), REntity::PropertyLayer);
    RLeaderEntity::PropertyLinetype.generateId(typeid(RLeaderEntity), REntity::PropertyLinetype);
    RLeaderEntity::PropertyLineweight.generateId(typeid(RLeaderEntity), REntity::PropertyLineweight);
    RLeaderEntity::PropertyColor.generateId(typeid(RLeaderEntity), REntity::PropertyColor);
    RLeaderEntity::PropertyDrawOrder.generateId(typeid(RLeaderEntity), REntity::PropertyDrawOrder);

    RLeaderEntity::PropertyArrowHead.generateId(typeid(RLeaderEntity), "", QT_TRANSLATE_NOOP("REntity", "Arrow"));
    RLeaderEntity::PropertyVertexNX.generateId(typeid(RLeaderEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "X"));
    RLeaderEntity::PropertyVertexNY.generateId(typeid(RLeaderEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RLeaderEntity::PropertyVertexNZ.generateId(typeid(RLeaderEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Z"));
}

bool RLeaderEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.arrowHead, value, PropertyArrowHead == propertyTypeId);
    ret = ret || RObject::setMemberX(data.vertices, value, PropertyVertexNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.vertices, value, PropertyVertexNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.vertices, value, PropertyVertexNZ == propertyTypeId);

    return ret;
}

QPair<QVariant, RPropertyAttributes> RLeaderEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyArrowHead) {
        return qMakePair(QVariant(data.arrowHead), RPropertyAttributes());
    } else if (propertyTypeId == PropertyVertexNX) {
        QVariant v;
        v.setValue(RVector::getXList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyVertexNY) {
        QVariant v;
        v.setValue(RVector::getYList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyVertexNZ) {
        QVariant v;
        v.setValue(RVector::getZList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RLeaderEntity::exportEntity(RExporter& e, bool preview) const {
    Q_UNUSED(preview)

    // a leader needs at least two vertices to display something:
    if (countVertices()<=1) {
        return;
    }

    RTriangle arrow = data.getArrowShape();

//    RVector p = data.getStartPoint();
//    double direction = data.getDirection1() + M_PI;
//    double dimasz = data.getDimasz();

//    RTriangle arrow = RTriangle::createArrow(p, direction, dimasz);
    QList<QSharedPointer<RShape> > arrowShapes;
    arrowShapes.append(QSharedPointer<RShape>(new RTriangle(arrow)));
    e.exportShapes(arrowShapes);

    e.setBrush(Qt::NoBrush);
    e.exportPolyline(data);
}

void RLeaderEntity::print(QDebug dbg) const {
    dbg.nospace() << "RLeaderEntity(";
    REntity::print(dbg);
    data.print(dbg);
    dbg.nospace()  << ")";
}
