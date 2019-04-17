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

#ifndef RUCS_H
#define RUCS_H

#include "core_global.h"

#include "RObject.h"
#include "RVector.h"
#include "RPropertyTypeId.h"

class RDocument;


/**
 * Represents a user coordinate system (UCS) in a drawing.
 * The current UCS of a drawing defines the current workplane
 * and coordinate system that is being used for all input.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RUcs : public RObject {
public:
    static RPropertyTypeId PropertyName;
    static RPropertyTypeId PropertyOriginX;
    static RPropertyTypeId PropertyOriginY;
    static RPropertyTypeId PropertyOriginZ;
    static RPropertyTypeId PropertyXAxisDirectionX;
    static RPropertyTypeId PropertyXAxisDirectionY;
    static RPropertyTypeId PropertyXAxisDirectionZ;
    static RPropertyTypeId PropertyYAxisDirectionX;
    static RPropertyTypeId PropertyYAxisDirectionY;
    static RPropertyTypeId PropertyYAxisDirectionZ;

public:
    RUcs() : RObject(), origin(0,0,0), xAxisDirection(1,0,0), yAxisDirection(0,1,0) {
    }

    RUcs(
        RDocument* document,
        const QString& name,
        const RVector& origin,
        const RVector& xAxisDirection,
        const RVector& yAxisDirection
    ) : RObject(document),
        name(name),
        origin(origin),
        xAxisDirection(xAxisDirection),
        yAxisDirection(yAxisDirection) {
   }

    virtual ~RUcs() {
    }

    static void init();

    virtual RS::EntityType getType() const {
        return RS::ObjectUcs;
    }

    virtual RUcs* clone() const {
        return new RUcs(*this);
    }

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

    void setOrigin(const RVector& o) {
        origin = o;
    }

    void setXAxisDirection(const RVector& x) {
        xAxisDirection = x;
    }

    void setYAxisDirection(const RVector& y) {
        yAxisDirection = y;
    }

    RVector getZAxisDirection();

    RVector mapFromUcs(const RVector& positionUcs);
    RVector mapToUcs(const RVector& positionWcs);

public:
    QString name;
    RVector origin;
    RVector xAxisDirection;
    RVector yAxisDirection;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RUcs& u);

Q_DECLARE_METATYPE(RUcs)
Q_DECLARE_METATYPE(RUcs*)
Q_DECLARE_METATYPE(QSharedPointer<RUcs>)
Q_DECLARE_METATYPE(QSharedPointer<RUcs>*)

#endif
