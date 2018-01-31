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

#ifndef RPAINTERPATHSOURCE_H
#define RPAINTERPATHSOURCE_H

#include "core_global.h"

#include <QList>

#include "RPainterPath.h"

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Interface for entity data classes that can deliver painter paths.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RPainterPathSource {
public:
    virtual ~RPainterPathSource();
    virtual QList<RPainterPath> getPainterPaths(bool draft = false, double pixelSizeHint = RDEFAULT_MIN1) const = 0;
};

Q_DECLARE_METATYPE(RPainterPathSource*)
Q_DECLARE_METATYPE(const RPainterPathSource*)
Q_DECLARE_METATYPE(QSharedPointer<RPainterPathSource>)
Q_DECLARE_METATYPE(QSharedPointer<RPainterPathSource>*)

#endif
