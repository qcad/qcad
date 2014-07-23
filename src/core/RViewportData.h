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

#ifndef RVIEWPORTDATA_H
#define RVIEWPORTDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "RLine.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a viewport entity.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RViewportData: public REntityData {

    friend class RViewportEntity;

protected:
    RViewportData(RDocument* document, const RViewportData& data);

public:
    RViewportData();
    RViewportData(const RVector& center, double width, double height, double scale,
        const RVector& viewCenterPoint,
        const RVector& viewTargetPoint);

    RVector getCenter() const {
       return center;
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const;

private:
    RVector center;
    double width;
    double height;
    double scale;

    RVector viewCenterPoint;
    RVector viewTargetPoint;
};

Q_DECLARE_METATYPE(RViewportData*)
Q_DECLARE_METATYPE(const RViewportData*)
Q_DECLARE_METATYPE(QSharedPointer<RViewportData>)

#endif
