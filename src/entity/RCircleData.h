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

#ifndef RCIRCLEDATA_H
#define RCIRCLEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "RCircle.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a circle entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RCircleData: public REntityData, protected RCircle {

    friend class RCircleEntity;

protected:
    RCircleData(RDocument* document, const RCircleData& data);

public:
    RCircleData();
    RCircleData(const RCircle& circle);
    RCircleData(const RVector& center, double radius);

    virtual RS::EntityType getType() const {
        return RS::EntityCircle;
    }
    RCircle getCircle() {
        return *this;
    }

    RVector getCenter() const {
        return RCircle::getCenter();
    }
    double getRadius() const {
        return RCircle::getRadius();
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
                QSharedPointer<RShape>(new RCircle(*this));
    }

};

Q_DECLARE_METATYPE(RCircleData)
Q_DECLARE_METATYPE(RCircleData*)
Q_DECLARE_METATYPE(const RCircleData*)
Q_DECLARE_METATYPE(QSharedPointer<RCircleData>)

#endif
