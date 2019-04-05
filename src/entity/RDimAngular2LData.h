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

#ifndef RDIMANGULAR2LDATA_H
#define RDIMANGULAR2LDATA_H

#include "entity_global.h"

#include "RArc.h"
#include "RDocument.h"
#include "RDimAngularData.h"
#include "RLine.h"
#include "RVector.h"

/**
 * Angular dimension entity from 2 lines data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAngular2LData: public RDimAngularData {
    friend class RDimAngular2LEntity;

protected:
    RDimAngular2LData(RDocument* document, const RDimAngular2LData& data);

public:
    RDimAngular2LData();
    RDimAngular2LData(const RDimensionData& dimData,
                    const RVector& extensionLine1Start,
                    const RVector& extensionLine1End,
                    const RVector& extensionLine2Start,
                    const RVector& dimArcPosition);

    virtual RS::EntityType getType() const {
        return RS::EntityDimAngular2L;
    }
    virtual bool isValid() const;
    virtual bool isSane() const;

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

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);

    bool getAngles(double& ang1, double& ang2,
                   bool& reversed,
                   RVector& p1, RVector& p2) const;
    RVector getCenter() const;

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

Q_DECLARE_METATYPE(RDimAngular2LData)
Q_DECLARE_METATYPE(RDimAngular2LData*)
Q_DECLARE_METATYPE(const RDimAngular2LData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngular2LData>)

#endif
