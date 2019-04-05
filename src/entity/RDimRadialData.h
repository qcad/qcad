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

#ifndef RDIMRADIALDATA_H
#define RDIMRADIALDATA_H

#include "entity_global.h"

#include "RDocument.h"
#include "RDimensionData.h"
#include "RVector.h"

/**
 * Radial dimension entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimRadialData: public RDimensionData {
    friend class RDimRadialEntity;

protected:
    RDimRadialData(RDocument* document, const RDimRadialData& data);

public:
    RDimRadialData();
    RDimRadialData(const RDimensionData& dimData,
                    const RVector& chordPoint);

    virtual RS::EntityType getType() const {
        return RS::EntityDimRadial;
    }
    virtual bool isValid() const;
    virtual bool isSane() const;

    void setCenter(const RVector& p) {
        setDefinitionPoint(p);
    }

    RVector getCenter() const {
        return getDefinitionPoint();
    }

    void setChordPoint(const RVector& p) {
        chordPoint = p;
    }

    RVector getChordPoint() const {
        return chordPoint;
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;
    virtual double getMeasuredValue() const;
    virtual QString getAutoLabel() const;

private:
    /** Chord point. Definition point from RDimensionData is center. */
    RVector chordPoint;
};

Q_DECLARE_METATYPE(RDimRadialData)
Q_DECLARE_METATYPE(RDimRadialData*)
Q_DECLARE_METATYPE(const RDimRadialData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimRadialData>)

#endif
