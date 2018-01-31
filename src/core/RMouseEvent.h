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

#ifndef RMOUSEEVENT_H
#define RMOUSEEVENT_H

#include "core_global.h"

#include <QMouseEvent>

#include "RVector.h"
#include "RInputEvent.h"

class RGraphicsScene;
class RGraphicsView;

/**
 * \brief A mouse event for a \ref RGraphicsScene "graphics scene".
 *
 * The coordinates in a mouse event are available as scene coordinates
 * of screen coordinates from the view the event originated.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RMouseEvent: public QMouseEvent, public RInputEvent {
public:
    RMouseEvent(QEvent::Type type, const RVector& position,
            Qt::MouseButton button, Qt::MouseButtons buttons,
            Qt::KeyboardModifiers modifiers, RGraphicsScene& s,
            RGraphicsView& v);

    RMouseEvent(const QMouseEvent& mouseEvent, RGraphicsScene& s,
            RGraphicsView& v, qreal devicePixelRatio = 1.0);

    virtual ~RMouseEvent();

    static bool hasMouseMoved();
    static void resetOriginalMousePos();
    static void setOriginalMousePos(const QPoint& p);

private:
    static QPoint oriCursor;
};

Q_DECLARE_METATYPE(RMouseEvent*)

#endif
