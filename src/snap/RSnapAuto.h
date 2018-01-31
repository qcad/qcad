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

#ifndef RSNAPAUTO_H
#define RSNAPAUTO_H

#include "snap_global.h"

#include "RSnap.h"

class RMouseEvent;
class RGraphicsView;

/**
 * \brief Auto snapper implementation.
 *
 * \scriptable
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RSnapAuto : public RSnap {
public:
    RSnapAuto() : RSnap(RSnap::Unknown) {}
    virtual ~RSnapAuto() {}

    virtual RVector snap(
            const RVector& position,
            RGraphicsView& view,
            double range=RNANDOUBLE
    );

    static void init(bool force = false);

private:
    static bool initialized;

    static bool intersections;
    static bool endPoints;
    static bool middlePoints;
    static bool centerPoints;
    static bool perpendicular;
    static bool tangential;
    static bool referencePoints;
    static bool gridPoints;
    static bool pointsOnEntity;
    static bool freePositioning;
};

Q_DECLARE_METATYPE(RSnapAuto*)

#endif
