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
 * \copyable
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

    virtual RS::EntityType getType() const {
        return RS::EntityLine;
    }

    RLine getLine() {
        return *this;
    }

    virtual RBox getBoundingBox(bool ignoreEmpty) const;

    virtual RPolyline getHull(double offset) const;

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

    RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
        return RLine::getTrimEnd(trimPoint, clickPoint);
    }
    bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return RLine::trimStartPoint(trimPoint, clickPoint, extend);
    }
    bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return RLine::trimEndPoint(trimPoint, clickPoint, extend);
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return RLine::getSideOfPoint(point);
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(segment)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RLine(*this));
    }
};

Q_DECLARE_METATYPE(RLineData)
Q_DECLARE_METATYPE(RLineData*)
Q_DECLARE_METATYPE(const RLineData*)
Q_DECLARE_METATYPE(QSharedPointer<RLineData>)

#endif
