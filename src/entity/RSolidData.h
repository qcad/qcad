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

#ifndef RSOLIDDATA_H
#define RSOLIDDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPolyline.h"
#include "RVector.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a solid entity.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RSolidData: public REntityData, protected RPolyline {

    friend class RSolidEntity;

protected:
    RSolidData(RDocument* document, const RSolidData& data);

public:
    RSolidData(RDocument* document = NULL);
    RSolidData(const RTriangle& triangle);
    RSolidData(const RVector& p1, const RVector& p2, const RVector& p3);
    RSolidData(const RVector& p1, const RVector& p2, const RVector& p3, const RVector& p4);

    RVector getStartPoint() const {
        return RPolyline::getStartPoint();
    }
    RVector getEndPoint() const {
        return RPolyline::getEndPoint();
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
    RVector getVertexAt(int i) const {
        return RPolyline::getVertexAt(i);
    }
    int countVertices() const {
        return RPolyline::countVertices();
    }

    RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint) {
        return RPolyline::getTrimEnd(coord, trimPoint);
    }
    void trimStartPoint(const RVector& p) {
        return RPolyline::trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return RPolyline::trimEndPoint(p);
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RPolyline(*this));
    }

    RPolyline getGeometry() {
        return *this;
    }
};

Q_DECLARE_METATYPE(RSolidData*)
Q_DECLARE_METATYPE(const RSolidData*)
Q_DECLARE_METATYPE(QSharedPointer<RSolidData>)

#endif
