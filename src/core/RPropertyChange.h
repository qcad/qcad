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
 *
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RPropertyChange {
public:
    RPropertyChange() {}
    RPropertyChange(RPropertyTypeId propertyTypeId, QVariant oldValue, QVariant newValue);

    void setOldValue(const QVariant& v) {
        oldValue = v;
    }
    QVariant getOldValue() const {
        return oldValue;
    }

    void setNewValue(const QVariant& v) {
        newValue = v;
    }
    QVariant getNewValue() const {
        return newValue;
    }

    void setPropertyTypeId(const RPropertyTypeId& id) {
        propertyTypeId = id;
    }
    RPropertyTypeId getPropertyTypeId() const {
        return propertyTypeId;
    }

public:
    RPropertyTypeId propertyTypeId;
    QVariant oldValue;
    QVariant newValue;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RPropertyChange& p);

typedef QMap<int, QList<RPropertyChange> > _RMapIntPropertyChange;
Q_DECLARE_METATYPE(_RMapIntPropertyChange*)
Q_DECLARE_METATYPE(_RMapIntPropertyChange)
Q_DECLARE_METATYPE(RPropertyChange*)
Q_DECLARE_METATYPE(RPropertyChange)

#endif
