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

#ifndef RDIMALIGNEDDATA_H
#define RDIMALIGNEDDATA_H

#include "entity_global.h"

#include "RDocument.h"
#include "RDimLinearData.h"
#include "RVector.h"

/**
 * Aligned dimension entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAlignedData: public RDimLinearData {
    friend class RDimAlignedEntity;

protected:
    RDimAlignedData(RDocument* document, const RDimAlignedData& data);

public:
    RDimAlignedData();
    RDimAlignedData(const RDimensionData& dimData,
                    const RVector& extensionPoint1,
                    const RVector& extensionPoint2);

    virtual RS::EntityType getType() const {
        return RS::EntityDimAligned;
    }
    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    virtual bool isValid() const;

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual void recomputeDefinitionPoint(
        const RVector& oldExtPoint1, const RVector& oldExtPoint2,
        const RVector& newExtPoint1, const RVector& newExtPoint2);

    virtual double getMeasuredValue() const;
    virtual QString getAutoLabel() const;
    double getAngle() const;

    void updateRefDefinitionPoint1(const RVector& v) const {
        refDefinitionPoint1 = v;
    }
    void updateRefDefinitionPoint2(const RVector& v) const {
        refDefinitionPoint2 = v;
    }
    virtual void to2D() {
        RDimLinearData::to2D();
        refDefinitionPoint1.z = 0.0;
        refDefinitionPoint2.z = 0.0;
    }

private:
    // for caching only:
    mutable RVector refDefinitionPoint1;
    mutable RVector refDefinitionPoint2;
};

Q_DECLARE_METATYPE(RDimAlignedData)
Q_DECLARE_METATYPE(RDimAlignedData*)
Q_DECLARE_METATYPE(const RDimAlignedData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAlignedData>)

#endif
