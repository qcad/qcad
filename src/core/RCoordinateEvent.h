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

#ifndef RCOORDINATEEVENT_H
#define RCOORDINATEEVENT_H

#include "core_global.h"

#include "RInputEvent.h"
#include "RVector.h"

class RGraphicsView;
class RGraphicsScene;

/**
 * Coordinate Event.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RCoordinateEvent : public QEvent, public RInputEvent {
public:
    /**
     * \param position Absolute model coordinate.
     */
    RCoordinateEvent(const RVector& position,
       RGraphicsScene& s, RGraphicsView& v);

    void setModifiers(Qt::KeyboardModifiers m) {
        mods = m;
    }
    Qt::KeyboardModifiers getModifiers() const {
        return mods;
    }

private:
    Qt::KeyboardModifiers mods;
};

Q_DECLARE_METATYPE(RCoordinateEvent*)
Q_DECLARE_METATYPE(const RCoordinateEvent*)

#endif
