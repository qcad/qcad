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

#ifndef RLEADERENTITY_H
#define RLEADERENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RLeaderData.h"

class RDocument;
class RExporter;

/**
 * Leader entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RLeaderEntity: public REntity {
    Q_DECLARE_TR_FUNCTIONS(RLeaderEntity)

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertyArrowHead;
    static RPropertyTypeId PropertyVertexNX;
    static RPropertyTypeId PropertyVertexNY;
    static RPropertyTypeId PropertyVertexNZ;

public:
    RLeaderEntity(RDocument* document, const RLeaderData& data,
                      RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RLeaderEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RLeaderEntity));
    }

    virtual RLeaderEntity* clone() const {
        return new RLeaderEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityLeader;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual RLeaderData& getData() {
        return data;
    }

    void setData(RLeaderData& d) {
        data = d;
    }

    virtual const RLeaderData& getData() const {
        return data;
    }

    void setArrowHead(bool on) {
        data.setArrowHead(on);
    }

    bool hasArrowHead() const {
        return data.hasArrowHead();
    }

    void clear() {
        data.clear();
    }

    void normalize() {
        data.normalize();
    }

    int countVertices() const {
        return data.countVertices();
    }

    void appendVertex(const RVector& vertex) {
        data.appendVertex(vertex);
    }

    void prependVertex(const RVector& vertex) {
        data.prependVertex(vertex);
    }

    void insertVertex(int index, const RVector& vertex) {
        data.insertVertex(index, vertex);
    }

    RVector getVertexAt(int i) const {
        return data.getVertexAt(i);
    }

    void removeLastVertex() {
        data.removeLastVertex();
    }

    void removeVertex(int index) {
        data.removeVertex(index);
    }

    int countSegments() const {
        return data.countSegments();
    }

    QSharedPointer<RShape> getSegmentAt(int i) const {
        return data.getSegmentAt(i);
    }

    double getBulgeAt(int i) const {
        return data.getBulgeAt(i);
    }

    void setBulgeAt(int i, double b) {
        data.setBulgeAt(i, b);
    }

    double getDirection1() const {
        return data.getDirection1();
    }

    double getDirection2() const {
        return data.getDirection2();
    }

    RVector getEndPoint() const {
        return data.getEndPoint();
    }

    RVector getStartPoint() const {
        return data.getStartPoint();
    }

    void setClosed(bool on) {
        data.setClosed(on);
    }

    bool isClosed() const {
        return data.isClosed();
    }

    QList<QSharedPointer<RShape> > getExploded() const {
        return data.getExploded();
    }

    virtual void exportEntity(RExporter& e, bool preview=false) const;

protected:
    virtual void print(QDebug dbg) const;

protected:
    RLeaderData data;
};

Q_DECLARE_METATYPE(RLeaderEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RLeaderEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RLeaderEntity>*)

#endif
