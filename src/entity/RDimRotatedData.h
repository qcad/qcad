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

#ifndef RDIMROTATEDDATA_H
#define RDIMROTATEDDATA_H

#include "entity_global.h"

#include "RDocument.h"
#include "RDimLinearData.h"
#include "RVector.h"

/**
 * Rotated dimension entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimRotatedData: public RDimLinearData {
    friend class RDimRotatedEntity;

protected:
    RDimRotatedData(RDocument* document, const RDimRotatedData& data);

public:
    RDimRotatedData();
    RDimRotatedData(const RDimensionData& dimData,
                    const RVector& extensionPoint1,
                    const RVector& extensionPoint2,
                    double rotation);

    virtual RS::EntityType getType() const {
        return RS::EntityDimRotated;
    }
    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    virtual bool isValid() const;
    virtual bool isSane() const;

    void setRotation(double r) {
        rotation = r;
    }

    double getRotation() const {
        return rotation;
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual QList<RVector> getDimPoints() const;

    virtual void recomputeDefinitionPoint(
        const RVector& oldExtPoint1, const RVector& oldExtPoint2,
        const RVector& newExtPoint1, const RVector& newExtPoint2);

    //virtual void recomputeDefinitionPoint(const RVector& oldDimLineGrip, const RVector& newDimLineGrip);

    virtual bool rotate(double rotation, const RVector& center);
    virtual bool mirror(const RLine& axis);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;
    virtual double getMeasuredValue() const;
    virtual QString getAutoLabel() const;

private:
    /** Fixed angle of dimension line in rad. */
    double rotation;
};

Q_DECLARE_METATYPE(RDimRotatedData)
Q_DECLARE_METATYPE(RDimRotatedData*)
Q_DECLARE_METATYPE(const RDimRotatedData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimRotatedData>)

#endif
