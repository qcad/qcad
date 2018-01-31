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

#ifndef RCOMMANDEVENT_H
#define RCOMMANDEVENT_H

#include "core_global.h"

/**
 * Command Event.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RCommandEvent {
public:
    /**
     * Creates a new command event that is not yet accepted.
     *
     * \param cmd the command that was triggered.
     */
    RCommandEvent(const QString& cmd) {
        this->cmd = cmd;
        accepted = false;
    }

    /**
     * \return the command that was triggered, usually by
     * the user.
     */
    QString getCommand() {
        return cmd;
    }

    /**
     * Sets the event state to accepted.
     */
    void accept() {
        accepted = true;
    }

    /**
     * \return Whether the event was already accepted or not.
     */
    bool isAccepted() {
        return accepted;
    }

private:
    QString cmd;
    bool accepted;
};

Q_DECLARE_METATYPE(RCommandEvent*)

#endif
