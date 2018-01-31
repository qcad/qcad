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

#ifndef RPROGRESSHANDLER_H
#define RPROGRESSHANDLER_H

#include "core_global.h"

#include <QMetaType>

/**
 * \brief Interface for classes that can handle progress status.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RProgressHandler {
public:
    RProgressHandler() : progressEnabled(true) {}

    virtual void setProgress(int value) = 0;
    virtual void setProgressEnd() = 0;
    virtual void setProgressText(const QString& text = "") = 0;
    virtual void setProgressEnabled(bool on) {
        progressEnabled = on;
    }

protected:
    bool progressEnabled;
};

Q_DECLARE_METATYPE(RProgressHandler*)

#endif
