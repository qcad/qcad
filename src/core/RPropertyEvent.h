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

#ifndef RPROPERTYEVENT_H
#define RPROPERTYEVENT_H

#include "core_global.h"

#include <QEvent>

#include "RPropertyTypeId.h"
#include "RPropertyAttributes.h"



/**
 * \brief A property change event is fired whenever a user interface
 * component was used to change the value of a property.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RPropertyEvent : public QEvent {
public:
    RPropertyEvent() :
        QEvent((QEvent::Type)(QEvent::User+500)),
        propertyTypeId(-1) {
    }

    /**
     * \param propertyTypeId ID of the property that was changed.
     * \param value New value of the property.
     */
    RPropertyEvent(RPropertyTypeId propertyTypeId, const QVariant& value,
                   RS::EntityType entityTypeFilter = RS::EntityAll)
        : QEvent((QEvent::Type)(QEvent::User+500)),
          propertyTypeId(propertyTypeId),
          value(value),
          entityTypeFilter(entityTypeFilter) {
    }

    /**
     * \return The position of the event in real graphic measures.
     */
    RPropertyTypeId getPropertyTypeId() const {
        return propertyTypeId;
    }

    /**
     * \return true If the position of the coordinate event is valid.
     */
    QVariant getValue() const {
        return value;
    }

    /**
     * \return Entity type filter to use for this event.
     */
    RS::EntityType getEntityTypeFilter() const {
        return entityTypeFilter;
    }

private:
    RPropertyTypeId propertyTypeId;
    QVariant value;
    RS::EntityType entityTypeFilter;
};

Q_DECLARE_METATYPE(RPropertyEvent)
Q_DECLARE_METATYPE(RPropertyEvent*)
Q_DECLARE_METATYPE(const RPropertyEvent*)

#endif
