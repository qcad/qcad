/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#ifndef RLINEDATA_H
#define RLINEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RLine.h"
#include "RVector.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a line entity.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RLineData: public REntityData, protected RLine {

    friend class RLineEntity;

protected:
    RLineData(RDocument* document, const RLineData& data);

public:
    RLineData();
    RLineData(const RLine& line);
    RLineData(const RVector& startPoint, const RVector& endPoint);

    RLine getLine() {
        return *this;
    }

    RVector getStartPoint() const {
        return RLine::getStartPoint();
    }
    RVector getEndPoint() const {
        return RLine::getEndPoint();
    }
    double getAngle() const {
        return RLine::getAngle();
    }
    double getDirection1() const {
        return RLine::getDirection1();
    }
    double getDirection2() const {
        return RLine::getDirection2();
    }
    bool reverse() {
        return RLine::reverse();
    }

    RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint) {
        return RLine::getTrimEnd(coord, trimPoint);
    }
    void trimStartPoint(const RVector& p) {
        return RLine::trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return RLine::trimEndPoint(p);
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return RLine::getSideOfPoint(point);
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false) const {
        Q_UNUSED(queryBox)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RLine(*this));
    }
};

Q_DECLARE_METATYPE(RLineData*)
Q_DECLARE_METATYPE(const RLineData*)
Q_DECLARE_METATYPE(QSharedPointer<RLineData>)

#endif
