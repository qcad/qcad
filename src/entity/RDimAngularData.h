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

#ifndef RDimAngularData_H
#define RDimAngularData_H

#include "entity_global.h"

#include "RArc.h"
#include "RDocument.h"
#include "RDimensionData.h"
#include "RLine.h"
#include "RVector.h"

/**
 * Angular dimension entity data base class.
 *
 * \scriptable
 * \abstract
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAngularData: public RDimensionData {
    friend class RDimAngularEntity;

protected:
    RDimAngularData(RDocument* document, const RDimAngularData& data);

public:
    RDimAngularData();
    RDimAngularData(const RDimensionData& dimData);

    virtual RS::EntityType getType() const {
        return RS::EntityDimAngular;
    }
    virtual bool isValid() const;
    virtual bool isSane() const;

    virtual void setExtensionLine1End(const RVector& p) = 0;
    virtual RVector getExtensionLine1End() const = 0;
    virtual void setExtensionLine2End(const RVector& p) = 0;
    virtual RVector getExtensionLine2End() const = 0;
    virtual void setDimArcPosition(const RVector& p) = 0;
    virtual RVector getDimArcPosition() const = 0;

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    /*
    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);
    */

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;
    double getAngle() const;
    virtual bool getAngles(double& ang1, double& ang2,
                   bool& reversed,
                   RVector& p1, RVector& p2) const = 0;
    virtual RVector getCenter() const = 0;
    virtual double getMeasuredValue() const;
    virtual QString getAutoLabel() const;

    virtual RArc getDimensionArc() const;
};

Q_DECLARE_METATYPE(RDimAngularData*)
Q_DECLARE_METATYPE(const RDimAngularData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngularData>)

#endif
