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

#ifndef RPOLYLINEENTITY_H
#define RPOLYLINEENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RPolylineData.h"

class RDocument;
class RExporter;
class RArc;
class RLine;

/**
 * Polyline entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPolylineEntity: public REntity {

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

    static RPropertyTypeId PropertyClosed;
    static RPropertyTypeId PropertyVertexNX;
    static RPropertyTypeId PropertyVertexNY;
    static RPropertyTypeId PropertyVertexNZ;
    static RPropertyTypeId PropertyBulgeN;

public:
    RPolylineEntity(RDocument* document, const RPolylineData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RPolylineEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RPolylineEntity));
    }

    virtual RPolylineEntity* clone() const {
        return new RPolylineEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityPolyline;
    }

    void setShape(const RPolyline& l);

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false) const;

    virtual RPolylineData& getData() {
        return data;
    }

    virtual const RPolylineData& getData() const {
        return data;
    }

    RPolyline getPolylineShape() const {
        return data.getPolylineShape();
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

    void appendVertex(const RVector& vertex, double bulge = 0.0) {
        data.appendVertex(vertex, bulge);
    }

    void prependVertex(const RVector& vertex, double bulge = 0.0) {
        data.prependVertex(vertex, bulge);
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

    bool reverse() {
        return data.reverse();
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

    bool isLogicallyClosed() const {
        return data.isLogicallyClosed();
    }

    QList<QSharedPointer<RShape> > getExploded() const {
        return data.getExploded();
    }

    virtual int getComplexity() const {
        return countSegments();
    }

    void simplify(double angleTolerance) {
        data.simplify(angleTolerance);
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RPolylineData data;
};

Q_DECLARE_METATYPE(RPolylineEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RPolylineEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RPolylineEntity>*)

#endif
