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

#ifndef RTERMINATEEVENT_H
#define RTERMINATEEVENT_H

#include "core_global.h"

#include <QEvent>

/**
 * \brief Event that is posted whenever an action has terminated itself.
 * As a reaction to this event, all terminated actions are cleaned up.
 * 
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RTerminateEvent : public QEvent {
public:
    RTerminateEvent() : QEvent((QEvent::Type)(QEvent::User+200)) {}
    virtual ~RTerminateEvent() {}
};

Q_DECLARE_METATYPE(RTerminateEvent*)

#endif
