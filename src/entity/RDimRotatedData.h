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

#ifndef RDIMROTATEDDATA_H
#define RDIMROTATEDDATA_H

#include "RDocument.h"
#include "RDimLinearData.h"
#include "RVector.h"

/**
 * Rotated dimension entity data class.
 *
 * \scriptable
 * \ingroup entity
 */
class RDimRotatedData: public RDimLinearData {
    friend class RDimRotatedEntity;

protected:
    RDimRotatedData(RDocument* document, const RDimRotatedData& data);

public:
    RDimRotatedData();
    RDimRotatedData(const RDimensionData& dimData,
                    const RVector& extensionPoint1,
                    const RVector& extensionPoint2,
                    double rotation);

    virtual bool isValid() const;

    void setRotation(double r) {
        rotation = r;
    }

    double getRotation() const {
        return rotation;
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

//    virtual bool moveReferencePoint(const RVector& referencePoint,
//        const RVector& targetPoint);

    virtual bool rotate(double rotation, const RVector& center);
    virtual bool mirror(const RLine& axis);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QString getAutoMeasurement() const;

private:
    /** Fixed angle of dimension line in rad. */
    double rotation;
};

Q_DECLARE_METATYPE(RDimRotatedData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimRotatedData>)

#endif
