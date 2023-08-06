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

#include <QFlags>

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
    enum Mode {
        None = 0x0000,
        Intersections = 0x0001,
        EndPoints = 0x0002,
        MiddlePoints = 0x0004,
        CenterPoints = 0x0008,
        PerpendicularPoints = 0x0010,
        TangentialPoints = 0x0020,
        ReferencePoints = 0x0040,
        GridPoints = 0x0080,
        PointsOnEntity = 0x0100,
        FreePositioning = 0x0200
    };
    Q_DECLARE_FLAGS(Modes, Mode)

public:
    RSnapAuto() : RSnap(RSnap::Unknown) {}
    virtual ~RSnapAuto() {}

    virtual RVector snap(
            const RVector& position,
            RGraphicsView& view,
            double range=RNANDOUBLE
    );

    static void init(bool force = false);

    static RSnapAuto::Modes getModes() {
        return modes;
    }
    static void setModes(RSnapAuto::Modes m) {
        modes = m;
    }

    static void setMode(RSnapAuto::Mode mode, bool on) {
        if (on) {
            modes |= mode;
        } else {
            modes &= ~mode;
        }
    }

    static bool getMode(RSnapAuto::Mode mode) {
        return (modes & mode) == mode;
    }

    static void setIntersections(bool on) {
        setMode(Intersections, on);
    }
    static bool getIntersections() {
        return getMode(Intersections);
    }

    static void setEndPoints(bool on) {
        setMode(EndPoints, on);
    }
    static bool getEndPoints() {
        return getMode(EndPoints);
    }

    static void setMiddlePoints(bool on) {
        setMode(MiddlePoints, on);
    }
    static bool getMiddlePoints() {
        return getMode(MiddlePoints);
    }

    static void setCenterPoints(bool on) {
        setMode(CenterPoints, on);
    }
    static bool getCenterPoints() {
        return getMode(CenterPoints);
    }

    static void setPerpendicular(bool on) {
        setMode(PerpendicularPoints, on);
    }
    static bool getPerpendicular() {
        return getMode(PerpendicularPoints);
    }

    static void setTangential(bool on) {
        setMode(TangentialPoints, on);
    }
    static bool getTangential() {
        return getMode(TangentialPoints);
    }

    static void setReferencePoints(bool on) {
        setMode(ReferencePoints, on);
    }
    static bool getReferencePoints() {
        return getMode(ReferencePoints);
    }

    static void setGridPoints(bool on) {
        setMode(GridPoints, on);
    }
    static bool getGridPoints() {
        return getMode(GridPoints);
    }

    static void setPointsOnEntity(bool on) {
        setMode(PointsOnEntity, on);
    }
    static bool getPointsOnEntity() {
        return getMode(PointsOnEntity);
    }

    static void setFreePositioning(bool on) {
        setMode(FreePositioning, on);
    }
    static bool getFreePositioning() {
        return getMode(FreePositioning);
    }

//    static bool getGridPoints() {
//        return gridPoints;
//    }

//    static void setGridPoints(bool on) {
//        gridPoints = on;
//    }

//    static bool getFreePositioning() {
//        return freePositioning;
//    }

//    static void setFreePositioning(bool on) {
//        freePositioning = on;
//    }

    virtual void reset() {
        status = RSnap::Unknown;
    }

private:
    static bool initialized;

    static Modes modes;

//    static bool intersections;
//    static bool endPoints;
//    static bool middlePoints;
//    static bool centerPoints;
//    static bool perpendicular;
//    static bool tangential;
//    static bool referencePoints;
//    static bool gridPoints;
//    static bool pointsOnEntity;
//    static bool freePositioning;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(RSnapAuto::Modes)
Q_DECLARE_METATYPE(RSnapAuto*)
Q_DECLARE_METATYPE(RSnapAuto::Mode)
Q_DECLARE_METATYPE(RSnapAuto::Mode*)

#endif
