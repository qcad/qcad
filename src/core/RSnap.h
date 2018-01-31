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

#include <QSet>

#include "REntity.h"
#include "RMouseEvent.h"
#include "RVector.h"

class RGraphicsView;

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
        Unknown,
        Free,
        Grid,
        Endpoint,
        OnEntity,
        Center,
        Middle,
        Distance,
        Intersection,
        IntersectionManual,
        Reference,
        Perpendicular,
        Tangential,
        Coordinate,
        CoordinatePolar
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
            double range=RNANDOUBLE) = 0;

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
    QSet<REntity::Id> getEntityIds() {
        return entityIds;
    }

    RSnap::Status getStatus() const {
        return status;
    }

    RVector getLastSnap() const {
        return lastSnap;
    }

    void reset() {
        entityIds.clear();
        status = RSnap::Unknown;
        lastSnap = RVector::invalid;
    }

protected:
    QSet<REntity::Id> entityIds;
    RSnap::Status status;
    RVector lastSnap;
};

Q_DECLARE_METATYPE(RSnap*)
Q_DECLARE_METATYPE(RSnap::Status)

#endif
