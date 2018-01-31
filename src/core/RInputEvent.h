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

#ifndef RINPUTEVENT_H
#define RINPUTEVENT_H

#include "core_global.h"

#include <QMouseEvent>

#include "RVector.h"

class RGraphicsScene;
class RGraphicsView;

/**
 * \brief An input event for a \ref RGraphicsScene "graphics scene".
 *
 * The coordinates in a mouse event are available as scene coordinates
 * or screen coordinates from the view the event originated.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RInputEvent {
public:
    RInputEvent(const RVector& position, RGraphicsScene& s, RGraphicsView& v, qreal devicePixelRatio=1.0);
    virtual ~RInputEvent();

    RVector getModelPosition() const;
    void setModelPosition(const RVector& v);

    RVector getCursorPosition() const;
    void setCursorPosition(const RVector& v);

    RVector getScreenPosition() const;
    void setScreenPosition(const RVector& v);

//  RVector getUcsPosition() const;

    RGraphicsView& getGraphicsView() const;
    RGraphicsScene& getGraphicsScene() const;

    /**
     * \return true If the position of the event is valid.
     */
    bool isValid() const {
        return modelPosition.valid;
    }

protected:
    RVector modelPosition;
    RVector cursorPosition;
//  RVector ucsPosition;
    RVector screenPosition;

    RGraphicsScene& scene;
    RGraphicsView& view;
};

Q_DECLARE_METATYPE(RInputEvent*)

#endif
