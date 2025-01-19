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

#ifndef RSNAP_H
#define RSNAP_H

#include "core_global.h"

#include "RMath.h"
#include "RMouseEvent.h"
#include "RObject.h"
#include "RVector.h"

class RGraphicsView;
class RMouseEvent;

/**
 * \brief Abstract base class for all grid and object snap 
 * implementations.
 * A snap class implements an object or grid snap tool. For
 * example to snap to end points of objects.
 *
 * \scriptable
 * \generateScriptShell
 *
 * \ingroup core
 */
class QCADCORE_EXPORT RSnap {
public:
    /**
     * Snap status, returned by snap tools (most importantly auto snap tool)
     * to indicate what snap was used.
     */
    enum Status {
        Unknown = 0,
        Free = 1,
        Grid = 2,
        Endpoint = 3,
        OnEntity = 4,
        Center = 5,
        Middle = 6,
        Distance = 7,
        Intersection = 8,
        IntersectionManual = 9,
        Reference = 10,
        Perpendicular = 11,
        Tangential = 12,
        Coordinate = 13,
        CoordinatePolar = 14
    };

public:
    RSnap(RSnap::Status s = RSnap::Unknown) : status(s), lastSnap(RVector::invalid) {}
    virtual ~RSnap() {}

    /**
     * \return The snapped position (closest relevant position)
     * for the given mouse position.
     */
    virtual RVector snap(
            const RVector& position,
            RGraphicsView& view,
            double range=RNANDOUBLE) {

        return RVector::invalid;
    }

    /**
     * \overload
     * \nonscriptable
     */
    virtual RVector snap(RMouseEvent& event) {
        return snap(event.getModelPosition(), event.getGraphicsView());
    }

    virtual void showUiOptions() {}
    virtual void hideUiOptions() {}

    virtual void suspendEvent() {
        hideUiOptions();
    }
    virtual void finishEvent() {
        hideUiOptions();
    }

    /**
     * \return Set of entity IDs that are relevant for the last performed
     * snap, usually used for highlighting.
     */
    QList<RObject::Id> getEntityIds() {
        return entityIds;
    }

    RSnap::Status getStatus() const {
        return status;
    }

    void setStatus(RSnap::Status s) {
        status = s;
    }

    RVector getLastSnap() const {
        return lastSnap;
    }

    void setLastSnap(const RVector& v) {
        lastSnap = v;
    }

    virtual void reset() {
        entityIds.clear();
        lastSnap = RVector::invalid;
    }

protected:
    QList<RObject::Id> entityIds;
    RSnap::Status status;
    RVector lastSnap;
};

Q_DECLARE_METATYPE(RSnap*)
Q_DECLARE_METATYPE(RSnap::Status)

#endif
