/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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
#include <QCoreApplication>
#include <QWheelEvent>

#include "RTabEventFilter.h"

/**
 * Event filter. If type is QEvent::None, all events are filtered.
 */
RTabEventFilter::RTabEventFilter(QObject* parent) {
}

bool RTabEventFilter::eventFilter(QObject* obj, QEvent* e) {
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Backtab) {

            // ignore the Tab and Shift+Tab keys
            return true;
        }
    }

    // pass the event on to the parent class
    return QObject::eventFilter(obj, event);
}
