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

#ifndef RWHEELEVENT_H
#define RWHEELEVENT_H

#include "core_global.h"

#include <QWheelEvent>

#include "RInputEvent.h"

class RGraphicsView;
class RGraphicsScene;

/**
 * \brief A mouse wheel event for a \ref RGraphicsScene "graphics scene".
 *
 * The coordinates in a mouse wheel event are available as scene 
 * coordinates or screen coordinates from the view the event originated.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RWheelEvent: public QWheelEvent, public RInputEvent {
public:
    RWheelEvent(const RVector& position, int delta, Qt::MouseButtons buttons,
            Qt::KeyboardModifiers modifiers, Qt::Orientation orient,
            RGraphicsScene& s, RGraphicsView& v);

    RWheelEvent(const QWheelEvent& wheelEvent, RGraphicsScene& s,
            RGraphicsView& v, qreal devicePixelRatio = 1.0);

    virtual ~RWheelEvent();

};

Q_DECLARE_METATYPE(RWheelEvent*)

#endif
