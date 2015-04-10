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

#ifndef RPOLYLINEDATA_H
#define RPOLYLINEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPolyline.h"
#include "RVector.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a polyline entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPolylineData: public REntityData, protected RPolyline {

    friend class RPolylineEntity;

protected:
    RPolylineData(RDocument* document, const RPolylineData& data);

public:
    RPolylineData();
    RPolylineData(const RPolyline& polyline);

    virtual QList<RBox> getBoundingBoxes(bool ignoreEmpty=false) const;

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual RShape* castToShape() {
        return this;
    }

    RPolyline getPolylineShape() const {
        return *this;
    }

    void clear() {
        RPolyline::clear();
    }

    void normalize() {
        RPolyline::normalize();
    }

    QList<RVector> getVertices() const {
        return RPolyline::getVertices();
    }

    RVector getVertexAt(int i) const {
        return RPolyline::getVertexAt(i);
    }

    void appendVertex(const RVector& vertex, double bulge = 0.0) {
        RPolyline::appendVertex(vertex, bulge);
    }

    void prependVertex(const RVector& vertex, double bulge = 0.0) {
        RPolyline::prependVertex(vertex, bulge);
    }

    void insertVertex(int index, const RVector& vertex) {
        RPolyline::insertVertex(index, vertex);
    }

    void removeLastVertex() {
        RPolyline::removeLastVertex();
    }

    void removeVertex(int index) {
        RPolyline::removeVertex(index);
    }

    int countSegments() const {
        return RPolyline::countSegments();
    }

    QSharedPointer<RShape> getSegmentAt(int i) const {
        return RPolyline::getSegmentAt(i);
    }

    double getBulgeAt(int i) const {
        return RPolyline::getBulgeAt(i);
    }

    void setBulgeAt(int i, double b) {
        RPolyline::setBulgeAt(i, b);
    }

    double getDirection1() const {
        return RPolyline::getDirection1();
    }

    double getDirection2() const {
        return RPolyline::getDirection2();
    }

    bool reverse() {
        return RPolyline::reverse();
    }

    RVector getEndPoint() const {
        return RPolyline::getEndPoint();
    }

    RVector getStartPoint() const {
        return RPolyline::getStartPoint();
    }

    void setClosed(bool on) {
        RPolyline::setClosed(on);
    }

    bool isClosed() const {
        return RPolyline::isClosed();
    }

    bool isLogicallyClosed() const {
        return RPolyline::isLogicallyClosed();
    }

    QList<QSharedPointer<RShape> > getExploded() const {
        return RPolyline::getExploded();
    }

    void simplify(double angleTolerance) {
        RPolyline::simplify(angleTolerance);
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false) const;

    virtual QList<RVector> getIntersectionPoints(
            const REntityData& other, bool limited = true, bool same = false,
            const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = true) const;

    void setPolylineGen(bool on) {
        polylineGen = on;
    }
    bool getPolylineGen() const {
        return polylineGen;
    }

protected:
    bool polylineGen;
};

Q_DECLARE_METATYPE(RPolylineData)
Q_DECLARE_METATYPE(RPolylineData*)
Q_DECLARE_METATYPE(const RPolylineData*)
Q_DECLARE_METATYPE(QSharedPointer<RPolylineData>)

#endif
