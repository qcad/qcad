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

#ifndef RSNAPSELECTION_H
#define RSNAPSELECTION_H

#include "snap_global.h"

#include "RRefPoint.h"
#include "RSnap.h"

class RDocument;
class RGraphicsView;
class RMouseEvent;

/**
 * \brief Selection snapper implementation.
 *
 * Snaps to the corners, edge midpoints and center of the bounding
 * box of the current selection.
 *
 * \scriptable
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RSnapSelection : public RSnap {
public:
    RSnapSelection() : RSnap(RSnap::Unknown), document(NULL) {}
    virtual ~RSnapSelection() {}

    virtual RVector snap(
            const RVector& position,
            RGraphicsView& view,
            double range=RNANDOUBLE
    );

    virtual QList<RRefPoint> getSnapReferencePoints() const;

    virtual void reset() {
        RSnap::reset();
        referencePoints.clear();
    }

private:
    static QList<RRefPoint> calculateReferencePoints(RDocument* document);

    /** Document of the last performed snap. */
    RDocument* document;
    /** Cached reference points, lazily recomputed by getSnapReferencePoints. */
    mutable QList<RRefPoint> referencePoints;
};

Q_DECLARE_METATYPE(RSnapSelection*)

#endif
