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

#ifndef RPOINTDATA_H
#define RPOINTDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "RLine.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a point entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPointData: public REntityData, protected RPoint {

    friend class RPointEntity;

protected:
    RPointData(RDocument* document, const RPointData& data);

public:
    RPointData();
    RPointData(const RVector& point);

    virtual RS::EntityType getType() const {
        return RS::EntityPoint;
    }

    virtual bool isPointType() const {
        return true;
    }

    RVector getPosition() const {
       return RPoint::getPosition();
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(queryBox)
        Q_UNUSED(segment)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RPoint(*this));
    }

};

Q_DECLARE_METATYPE(RPointData)
Q_DECLARE_METATYPE(RPointData*)
Q_DECLARE_METATYPE(const RPointData*)
Q_DECLARE_METATYPE(QSharedPointer<RPointData>)

#endif
