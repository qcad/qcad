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

#ifndef RLINETYPELIST_H
#define RLINETYPELIST_H

#include "core_global.h"

#include <QMap>
#include <QPair>
#include <QSet>
#include <QString>

#include "RLinetypePattern.h"
#include "RResourceList.h"

/**
 * Base class for global lists of linetypes.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RLinetypeList {
public:
    static void init(bool metric, RResourceList<RLinetypePattern>& res);
};

Q_DECLARE_METATYPE(RLinetypeList)
Q_DECLARE_METATYPE(RLinetypeList*)
Q_DECLARE_METATYPE(RResourceList<RLinetypePattern>*)

#endif
