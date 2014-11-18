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

#ifndef RXLINEDATA_H
#define RXLINEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RVector.h"
#include "RXLine.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of an infinit line (xline) entity.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RXLineData: public REntityData, protected RXLine {

    friend class RXLineEntity;

protected:
    RXLineData(RDocument* document, const RXLineData& data);

public:
    RXLineData();
    RXLineData(const RXLine& line);
    RXLineData(const RVector& basePoint, const RVector& dir);

    RXLine getXLine() {
        return *this;
    }

    RVector getBasePoint() const {
        return RXLine::getBasePoint();
    }
    RVector getDirectionVector() const {
        return RXLine::getDirectionVector();
    }
    double getAngle() const {
        return RXLine::getAngle();
    }
    bool reverse() {
        return RXLine::reverse();
    }

    RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint) {
        return RXLine::getTrimEnd(coord, trimPoint);
    }
    void trimStartPoint(const RVector& p) {
        return RXLine::trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return RXLine::trimEndPoint(p);
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return RXLine::getSideOfPoint(point);
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
                QSharedPointer<RShape>(new RXLine(*this));
    }
};

Q_DECLARE_METATYPE(RXLineData*)
Q_DECLARE_METATYPE(const RXLineData*)
Q_DECLARE_METATYPE(QSharedPointer<RXLineData>)

#endif
