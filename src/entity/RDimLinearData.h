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

#ifndef RDIMLINEARDATA_H
#define RDIMLINEARDATA_H

#include "entity_global.h"

#include "RDocument.h"
#include "RDimensionData.h"
#include "RVector.h"

/**
 * Linear dimension entity data base class.
 *
 * \scriptable
 * \abstract
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimLinearData: public RDimensionData {
    friend class RDimLinearEntity;

protected:
    RDimLinearData(RDocument* document, const RDimLinearData& data);

public:
    RDimLinearData(RDocument* document = NULL);
    RDimLinearData(const RDimensionData& dimData,
                   const RVector& extensionPoint1,
                   const RVector& extensionPoint2);

    virtual RS::EntityType getType() const {
        return RS::EntityDimLinear;
    }
    virtual bool isValid() const;
    virtual bool isSane() const;

    virtual void setDefinitionPoint(const RVector& p) {
        definitionPoint = p;
        recomputeDefinitionPoint(extensionPoint1, extensionPoint2, extensionPoint1, extensionPoint2);
        update();
    }

    void setExtensionPoint1(const RVector& p) {
        extensionPoint1 = p;
    }

    RVector getExtensionPoint1() const {
        return extensionPoint1;
    }

    void setExtensionPoint2(const RVector& p) {
        extensionPoint2 = p;
    }

    RVector getExtensionPoint2() const {
        return extensionPoint2;
    }

    virtual void recomputeDefinitionPoint(
        const RVector& oldExtPoint1, const RVector& oldExtPoint2,
        const RVector& newExtPoint1, const RVector& newExtPoint2) {
        Q_UNUSED(oldExtPoint1)
        Q_UNUSED(oldExtPoint2)
        Q_UNUSED(newExtPoint1)
        Q_UNUSED(newExtPoint2)
    }

//    virtual void recomputeDefinitionPoint(const RVector& oldDimLineGrip, const RVector& newDimLineGrip) {
//        Q_UNUSED(oldDimLineGrip)
//        Q_UNUSED(newDimLineGrip)
//    }

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual void updateTextData() const;

protected:
    /** Definition point. Startpoint of the first extension line. */
    RVector extensionPoint1;
    /** Definition point. Startpoint of the second extension line. */
    RVector extensionPoint2;
};

Q_DECLARE_METATYPE(RDimLinearData*)
Q_DECLARE_METATYPE(const RDimLinearData*)
Q_DECLARE_METATYPE(QSharedPointer<RDimLinearData>)

#endif
