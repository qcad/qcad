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

#ifndef RTOOLOPTIONEVENTFILTER_H
#define RTOOLOPTIONEVENTFILTER_H

#include "gui_global.h"

#include <QEvent>
#include <QMetaType>
#include <QObject>

/**
 * Tab key navigation filter, installed so we can take over tab handling from Qt (broken).
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RToolOptionEventFilter : public QObject {
    Q_OBJECT

public:
    RToolOptionEventFilter(QObject *parent = NULL);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

Q_DECLARE_METATYPE(RToolOptionEventFilter*)

#endif
