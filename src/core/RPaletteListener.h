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

#ifndef RPALETTELISTENER_H
#define RPALETTELISTENER_H

#include "core_global.h"


/**
 * \brief Abstract base class for classes that are interested 
 * in being notified whenever the current palette (style, theme) changes.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RPaletteListener {
public:
    virtual ~RPaletteListener() {}

    /**
     * This method is called whenever the current palette has changed.
     */
    virtual void updatePalette() = 0;
};

Q_DECLARE_METATYPE(RPaletteListener*)

#endif
