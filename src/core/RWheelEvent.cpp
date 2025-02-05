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


RWheelEvent::RWheelEvent(const RVector& position, int delta,
        Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers,
        Qt::Orientation orient, RGraphicsScene& s, RGraphicsView& v) :
#if QT_VERSION >= 0x060000
    QWheelEvent(QPointF(position.x, position.y), QPointF(position.x, position.y), QPoint(delta, delta), QPoint(0,0), buttons, modifiers, Qt::NoScrollPhase, false),
#else
    QWheelEvent(QPoint(position.x, position.y), delta, buttons, modifiers, orient),
#endif
    RInputEvent(position, s, v) {

}

RWheelEvent::RWheelEvent(const QWheelEvent& wheelEvent, RGraphicsScene& s,
        RGraphicsView& v, qreal devicePixelRatio) :
    QWheelEvent(wheelEvent),
#if QT_VERSION >= 0x060000
    RInputEvent(RVector(wheelEvent.position().x(), wheelEvent.position().y()), s, v, devicePixelRatio) {
#else
    RInputEvent(RVector(wheelEvent.pos().x(), wheelEvent.pos().y()), s, v, devicePixelRatio) {
#endif
}

RWheelEvent::~RWheelEvent() {
}
