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
#include "RWheelEvent.h"

#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RUcs.h"
#include "RDocumentInterface.h"

RWheelEvent::RWheelEvent(const RVector& position, int delta,
        Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers,
        Qt::Orientation orient, RGraphicsScene& s, RGraphicsView& v) :
    QWheelEvent(QPoint(position.x, position.y), delta, buttons, modifiers,
            orient),
    RInputEvent(position, s, v) {

}

RWheelEvent::RWheelEvent(const QWheelEvent& wheelEvent, RGraphicsScene& s,
        RGraphicsView& v, qreal devicePixelRatio) :
    QWheelEvent(wheelEvent),
    RInputEvent(RVector(wheelEvent.pos().x(), wheelEvent.pos().y()), s, v, devicePixelRatio) {
}

RWheelEvent::~RWheelEvent() {
}
