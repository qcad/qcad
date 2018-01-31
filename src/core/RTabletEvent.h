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

#ifndef RTABLETEVENT_H
#define RTABLETEVENT_H

#include "core_global.h"

#include <QTabletEvent>

#include "RVector.h"

class RGraphicsScene;
class RGraphicsView;



/**
 * \brief A tablet event for a \ref RGraphicsScene "graphics scene".
 *
 * The coordinates in a mouse event are available as scene coordinates
 * of screen coordinates from the view the event originated.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RTabletEvent: public QTabletEvent {
public:
    /*
    RTabletEvent(
            QEvent::Type type,
            const RVector& position,
            int device,
            int pointerType,
            qreal pressure,
            int xTilt,
            int yTilt,
            qreal tangentialPressure,
            qreal rotation,
            int z,
            Qt::KeyboardModifiers keyState,
            qint64 uniqueID,
            RGraphicsScene& s,
            RGraphicsView& v);
            */

    RTabletEvent(
            const QTabletEvent& tabletEvent,
            RGraphicsScene& s,
            RGraphicsView& v
            );

    virtual ~RTabletEvent();

    RVector getModelPosition() const;
    RVector getUcsPosition() const;
    RVector getScreenPosition() const;

    RGraphicsView& getGraphicsView() const;
    RGraphicsScene& getGraphicsScene() const;

protected:
    RVector modelPosition;
    RVector ucsPosition;
    RVector screenPosition;
    
    RGraphicsScene& scene;
    RGraphicsView& view;
};

Q_DECLARE_METATYPE(RTabletEvent*)

#endif
