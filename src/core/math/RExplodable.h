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

#ifndef REXPLODABLE_H
#define REXPLODABLE_H

#include "../core_global.h"

#include <QSharedPointer>

#include "RShape.h"

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Interface for explodable shape classes.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RExplodable {
public:
    virtual ~RExplodable() {}
    virtual QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const = 0;
};

Q_DECLARE_METATYPE(RExplodable*)
Q_DECLARE_METATYPE(const RExplodable*)
Q_DECLARE_METATYPE(QSharedPointer<RExplodable>)
Q_DECLARE_METATYPE(QSharedPointer<RExplodable>*)

#endif
