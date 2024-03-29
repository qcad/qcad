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

#ifndef RMESSAGEHANDLER_H
#define RMESSAGEHANDLER_H

#include "core_global.h"

#include <QMetaType>

/**
 * \brief Interface for classes that can handle user messages, warnings and errors.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RMessageHandler {
public:
    virtual ~RMessageHandler() {}

    virtual void handleUserMessage(const QString& message, bool escape=true) = 0;
    virtual void handleUserInfo(const QString& message, bool escape=true) = 0;
    virtual void handleUserWarning(const QString& message,
            bool messageBox = false, bool escape=true) = 0;
    virtual void handleUserCommand(const QString& message, bool escape=true) = 0;
};

Q_DECLARE_METATYPE(RMessageHandler*)

#endif
