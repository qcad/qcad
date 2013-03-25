/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RPROPERTYCHANGE_H
#define RPROPERTYCHANGE_H

#include "core_global.h"

#include <QVariant>

#include "RObject.h"
#include "RPropertyTypeId.h"

class RStorage;
class RExporter;

/**
 * Stores the change that was made to a property of an object.
 */
class QCADCORE_EXPORT RPropertyChange {
public:
    RPropertyChange(RPropertyTypeId propertyTypeId, QVariant oldValue,
            QVariant newValue);
    RPropertyTypeId propertyTypeId;
    QVariant oldValue;
    QVariant newValue;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, RPropertyChange& p);

typedef QMap<int, QList<RPropertyChange> > _RMapIntPropertyChange;
Q_DECLARE_METATYPE(_RMapIntPropertyChange*)
Q_DECLARE_METATYPE(_RMapIntPropertyChange)
Q_DECLARE_METATYPE(RPropertyChange*)

#endif
