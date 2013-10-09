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

#ifndef RDIMORDINATEDATA_H
#define RDIMORDINATEDATA_H

#include "entity_global.h"

#include "RDocument.h"
#include "RDimLinearData.h"
#include "RVector.h"

/**
 * Ordinate dimension entity data class.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimOrdinateData: public RDimensionData {
    friend class RDimOrdinateEntity;

protected:
    RDimOrdinateData(RDocument* document, const RDimOrdinateData& data);

public:
    RDimOrdinateData();
    RDimOrdinateData(const RDimensionData& dimData,
                    const RVector& leaderEndPoint,
                    const RVector& definingPoint);

    virtual bool isValid() const;

    void setLeaderEndPoint(const RVector& p) {
        leaderEndPoint = p;
    }

    RVector getLeaderEndPoint() const {
        return leaderEndPoint;
    }

    void setOrigin(const RVector& p) {
        setDefinitionPoint(p);
    }

    RVector getOrigin() const {
        return getDefinitionPoint();
    }

    void setDefiningPoint(const RVector& p) {
        definingPoint = p;
    }

    RVector getDefiningPoint() const {
        return definingPoint;
    }

    void setMeasuringXAxis() {
        xType = true;
    }

    void setMeasuringYAxis() {
        xType = false;
    }

    bool isMeasuringXAxis() const {
        return xType;
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QString getAutoMeasurement() const;

private:
    /** Defining point (feature location) */
    RVector definingPoint;

    /** End point of leader */
    RVector leaderEndPoint;

    /** True: measures x-value, false: y-value */
    bool xType;
};

Q_DECLARE_METATYPE(RDimOrdinateData*)
Q_DECLARE_METATYPE(const RDimOrdinateData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimOrdinateData>)

#endif
