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

#ifndef RDIMANGULAR3PDATA_H
#define RDIMANGULAR3PDATA_H

#include "entity_global.h"

#include "RArc.h"
#include "RDocument.h"
#include "RDimAngularData.h"
#include "RLine.h"
#include "RVector.h"

/**
 * Angular dimension entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAngular3PData: public RDimAngularData {
    friend class RDimAngular3PEntity;

protected:
    RDimAngular3PData(RDocument* document, const RDimAngular3PData& data);

public:
    RDimAngular3PData();
    RDimAngular3PData(const RDimensionData& dimData,
                    const RVector& center,
                    const RVector& extensionLine1End,
                    const RVector& extensionLine2End);

    virtual RS::EntityType getType() const {
        return RS::EntityDimAngular3P;
    }
    virtual bool isValid() const;
    virtual bool isSane() const;

    RVector getCenter() const {
        return center;
    }

    void setCenter(const RVector& p) {
        center = p;
    }

    void setExtensionLine1End(const RVector& p) {
        extensionLine1End = p;
    }

    RVector getExtensionLine1End() const {
        return extensionLine1End;
    }

    void setExtensionLine2End(const RVector& p) {
        extensionLine2End = p;
    }

    RVector getExtensionLine2End() const {
        return extensionLine2End;
    }

    void setDimArcPosition(const RVector& p) {
        setDefinitionPoint(p);
    }

    RVector getDimArcPosition() const {
        return getDefinitionPoint();
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);

    bool getAngles(double& ang1, double& ang2,
                   bool& reversed,
                   RVector& p1, RVector& p2) const;

private:
    /** Start point of first extension line. */
    RVector center;
    /** End point of first extension line. */
    RVector extensionLine1End;
    /** End point of second extension line. */
    RVector extensionLine2End;
    /** Arc position is definitionPoint */
    //RVector dimArcPosition;
};

Q_DECLARE_METATYPE(RDimAngular3PData)
Q_DECLARE_METATYPE(RDimAngular3PData*)
Q_DECLARE_METATYPE(const RDimAngular3PData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngular3PData>)

#endif
