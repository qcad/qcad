/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

#ifndef RDimAngularDataDATA_H
#define RDimAngularDataDATA_H

#include "entity_global.h"

#include "RArc.h"
#include "RDocument.h"
#include "RDimensionData.h"
#include "RLine.h"
#include "RVector.h"

/**
 * Angular dimension entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAngularData: public RDimensionData {
    friend class RDimAngularEntity;

protected:
    RDimAngularData(RDocument* document, const RDimAngularData& data);

public:
    RDimAngularData();
    RDimAngularData(const RDimensionData& dimData,
                    const RVector& extensionLine1Start,
                    const RVector& extensionLine1End,
                    const RVector& extensionLine2Start,
                    const RVector& dimArcPosition);

    virtual RS::EntityType getType() const {
        return RS::EntityDimAngular;
    }
    virtual bool isValid() const;

    void setExtensionLine1Start(const RVector& p) {
        extensionLine1Start = p;
    }

    RVector getExtensionLine1Start() const {
        return extensionLine1Start;
    }

    void setExtensionLine1End(const RVector& p) {
        extensionLine1End = p;
    }

    RVector getExtensionLine1End() const {
        return extensionLine1End;
    }

    void setExtensionLine2Start(const RVector& p) {
        extensionLine2Start = p;
    }

    RVector getExtensionLine2Start() const {
        return extensionLine2Start;
    }

    void setExtensionLine2End(const RVector& p) {
        setDefinitionPoint(p);
    }

    RVector getExtensionLine2End() const {
        return getDefinitionPoint();
    }

    void setDimArcPosition(const RVector& p) {
        dimArcPosition = p;
    }

    RVector getDimArcPosition() const {
        return dimArcPosition;
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;
    double getAngle() const;
    bool getAngles(double& ang1, double& ang2,
                   bool& reversed,
                   RVector& p1, RVector& p2) const;
    RVector getCenter() const;
    virtual double getMeasuredValue() const;
    virtual QString getAutoLabel() const;

private:
    /** Start point of first extension line. */
    RVector extensionLine1Start;
    /** End point of first extension line. */
    RVector extensionLine1End;
    /** Start point of second extension line. End is definition point. */
    RVector extensionLine2Start;
    /** Arc position */
    RVector dimArcPosition;
};

Q_DECLARE_METATYPE(RDimAngularData)
Q_DECLARE_METATYPE(RDimAngularData*)
Q_DECLARE_METATYPE(const RDimAngularData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngularData>)

#endif
