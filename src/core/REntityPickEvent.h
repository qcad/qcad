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

#ifndef RENTITYPICKEVENT_H
#define RENTITYPICKEVENT_H

#include "core_global.h"

#include "RInputEvent.h"
#include "REntity.h"
#include "RVector.h"

class RGraphicsView;
class RGraphicsScene;

/**
 * Entity pick event.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT REntityPickEvent : public RInputEvent {
public:
    /**
     * \param entityId ID of picked entity.
     * \param pos Absolute coordinate.
     */
    REntityPickEvent(REntity::Id entityId, const RVector& position,
       RGraphicsScene& s, RGraphicsView& v);

    /**
     * \return The ID of the picked entity or REntity::INVALID_ID.
     */
    REntity::Id getEntityId() const {
        return entityId;
    }

    void setModifiers(Qt::KeyboardModifiers m) {
        mods = m;
    }
    Qt::KeyboardModifiers getModifiers() const {
        return mods;
    }

    /**
     * \return true If the entity ID of the event is valid.
     */
    bool isValid() const {
        return entityId!=REntity::INVALID_ID;
    }

private:
    REntity::Id entityId;
    Qt::KeyboardModifiers mods;
};

Q_DECLARE_METATYPE(REntityPickEvent*)
Q_DECLARE_METATYPE(const REntityPickEvent*)

#endif
