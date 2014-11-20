/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
#include "RDocumentInterface.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RMouseEvent.h"
#include "RUcs.h"

RMouseEvent::RMouseEvent(Type type, const RVector& position,
        Qt::MouseButton button, Qt::MouseButtons buttons,
        Qt::KeyboardModifiers modifiers, RGraphicsScene& s, RGraphicsView& v)

:
    QMouseEvent(type, QPoint(position.x, position.y), button, buttons, modifiers),
    RInputEvent(position, s, v) {
}

RMouseEvent::RMouseEvent(const QMouseEvent& mouseEvent, RGraphicsScene& s,
        RGraphicsView& v) :
    QMouseEvent(mouseEvent),
    RInputEvent(RVector(mouseEvent.posF().x(), mouseEvent.posF().y()), s, v) {
}

RMouseEvent::~RMouseEvent() {
}

