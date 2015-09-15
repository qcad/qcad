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
#include "RPolylineEntity.h"
#include "RMetaTypes.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RPolylineEntity::PropertyCustom;
RPropertyTypeId RPolylineEntity::PropertyHandle;
RPropertyTypeId RPolylineEntity::PropertyProtected;
RPropertyTypeId RPolylineEntity::PropertyType;
RPropertyTypeId RPolylineEntity::PropertyBlock;
RPropertyTypeId RPolylineEntity::PropertyLayer;
RPropertyTypeId RPolylineEntity::PropertyLinetype;
RPropertyTypeId RPolylineEntity::PropertyLinetypeScale;
RPropertyTypeId RPolylineEntity::PropertyLineweight;
RPropertyTypeId RPolylineEntity::PropertyColor;
RPropertyTypeId RPolylineEntity::PropertyDisplayedColor;
RPropertyTypeId RPolylineEntity::PropertyDrawOrder;

RPropertyTypeId RPolylineEntity::PropertyPolylineGen;
RPropertyTypeId RPolylineEntity::PropertyClosed;
RPropertyTypeId RPolylineEntity::PropertyVertexNX;
RPropertyTypeId RPolylineEntity::PropertyVertexNY;
RPropertyTypeId RPolylineEntity::PropertyVertexNZ;
RPropertyTypeId RPolylineEntity::PropertyBulgeN;
RPropertyTypeId RPolylineEntity::PropertyStartWidthN;
RPropertyTypeId RPolylineEntity::PropertyEndWidthN;
RPropertyTypeId RPolylineEntity::PropertyGlobalWidth;

RPropertyTypeId RPolylineEntity::PropertyLength;

RPolylineEntity::RPolylineEntity(RDocument* document, const RPolylineData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
    RDebug::incCounter("RPolylineEntity");
}

RPolylineEntity::RPolylineEntity(const RPolylineEntity& other) : REntity(other) {
    RDebug::incCounter("RPolylineEntity");
    data = other.data;
}

RPolylineEntity::~RPolylineEntity() {
    RDebug::decCounter("RPolylineEntity");
}

void RPolylineEntity::setShape(const RPolyline& l) {
    data.setVertices(l.getVertices());
    data.setBulges(l.getBulges());
    data.setClosed(l.isClosed());
}

void RPolylineEntity::init() {
    RPolylineEntity::PropertyCustom.generateId(typeid(RPolylineEntity), RObject::PropertyCustom);
    RPolylineEntity::PropertyHandle.generateId(typeid(RPolylineEntity), RObject::PropertyHandle);
    RPolylineEntity::PropertyProtected.generateId(typeid(RPolylineEntity), RObject::PropertyProtected);
    RPolylineEntity::PropertyType.generateId(typeid(RPolylineEntity), REntity::PropertyType);
    RPolylineEntity::PropertyBlock.generateId(typeid(RPolylineEntity), REntity::PropertyBlock);
    RPolylineEntity::PropertyLayer.generateId(typeid(RPolylineEntity), REntity::PropertyLayer);
    RPolylineEntity::PropertyLinetype.generateId(typeid(RPolylineEntity), REntity::PropertyLinetype);
    RPolylineEntity::PropertyLinetypeScale.generateId(typeid(RPolylineEntity), REntity::PropertyLinetypeScale);
    RPolylineEntity::PropertyLineweight.generateId(typeid(RPolylineEntity), REntity::PropertyLineweight);
    RPolylineEntity::PropertyColor.generateId(typeid(RPolylineEntity), REntity::PropertyColor);
    RPolylineEntity::PropertyDisplayedColor.generateId(typeid(RPolylineEntity), REntity::PropertyDisplayedColor);
    RPolylineEntity::PropertyDrawOrder.generateId(typeid(RPolylineEntity), REntity::PropertyDrawOrder);

    RPolylineEntity::PropertyPolylineGen.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Polyline Pattern"));
    RPolylineEntity::PropertyClosed.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Closed"));
    RPolylineEntity::PropertyVertexNX.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "X"));
    RPolylineEntity::PropertyVertexNY.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RPolylineEntity::PropertyVertexNZ.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RPolylineEntity::PropertyBulgeN.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Bulge"));
    RPolylineEntity::PropertyStartWidthN.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Start Width"));
    RPolylineEntity::PropertyEndWidthN.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "End Width"));

    RPolylineEntity::PropertyGlobalWidth.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Global Width"));
    RPolylineEntity::PropertyLength.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
}

bool RPolylineEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value, transaction);
    ret = ret || RObject::setMember(data.polylineGen, value, PropertyPolylineGen == propertyTypeId);
    ret = ret || RObject::setMember(data.closed, value, PropertyClosed == propertyTypeId);
    ret = ret || RObject::setMemberX(data.vertices, value, PropertyVertexNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.vertices, value, PropertyVertexNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.vertices, value, PropertyVertexNZ == propertyTypeId);
    ret = ret || RObject::setMember(data.bulges, value, PropertyBulgeN == propertyTypeId);
    ret = ret || RObject::setMember(data.startWidths, value, PropertyStartWidthN == propertyTypeId);
    ret = ret || RObject::setMember(data.endWidths, value, PropertyEndWidthN == propertyTypeId);

    if (PropertyGlobalWidth==propertyTypeId) {
        for (int i=0; i<data.startWidths.length(); i++) {
            data.startWidths[i] = value.toDouble();
        }
        for (int i=0; i<data.endWidths.length(); i++) {
            data.endWidths[i] = value.toDouble();
        }
        ret = true;
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RPolylineEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes) {
    if (propertyTypeId == PropertyClosed) {
        QVariant v;
        v.setValue(data.closed);
        return qMakePair(v, RPropertyAttributes());
    } else if (propertyTypeId == PropertyPolylineGen) {
            QVariant v;
            v.setValue(data.polylineGen);
            return qMakePair(v, RPropertyAttributes());
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
    } else if (propertyTypeId == PropertyBulgeN) {
        QVariant v;
        v.setValue(data.bulges);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyStartWidthN) {
        QVariant v;
        v.setValue(data.startWidths);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyEndWidthN) {
        QVariant v;
        v.setValue(data.endWidths);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyGlobalWidth) {
        QVariant v;
        double val = -1.0;
        for (int i=0; i<data.startWidths.length() && i<data.endWidths.length(); i++) {
            if (val<0.0) {
                val = data.startWidths[i];
                v.setValue(val);
            }

            if (!RMath::fuzzyCompare(data.startWidths[i], val) || !RMath::fuzzyCompare(data.endWidths[i], val)) {
                v.setValue(QString());
                break;
            }
        }
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertyLength) {
        QVariant v;
        v.setValue(data.getLength());
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RPolylineEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.setBrush(Qt::NoBrush);

    // temp for painter path testing:
//    RPainterPath pp(data.toPainterPath());
//    pp.setPen(QPen(Qt::white));
//    e.exportPainterPaths(QList<RPainterPath>() << pp);

    e.exportPolyline(data, data.getPolylineGen());
}

void RPolylineEntity::print(QDebug dbg) const {
    dbg.nospace() << "RPolylineEntity(";
    REntity::print(dbg);
    data.print(dbg);
    dbg.nospace()  << ")";
}
