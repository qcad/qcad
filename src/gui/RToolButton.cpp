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
#include <QEvent>

#include "RToolButton.h"

RToolButton::RToolButton(QWidget* parent) :
    QToolButton(parent) {
}

bool RToolButton::event(QEvent* event) {
    bool ret = QToolButton::event(event);

    // don't accept these events, so we can request a context
    // menu or start panning on top of an RToolButton:
    if (event->type()==QEvent::MouseButtonPress ||
        event->type()==QEvent::MouseButtonRelease ||
        event->type()==QEvent::MouseMove ||
        event->type()==QEvent::ContextMenu ||
        event->type()==QEvent::Wheel) {
        return false;
    }
    return ret;
}
