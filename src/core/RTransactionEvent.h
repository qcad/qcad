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

#ifndef RTRANSACTIONEVENT_H
#define RTRANSACTIONEVENT_H

#include <QEvent>

#include "RS.h"

/**
 * \brief Event that is posted whenever a transaction happened.
 * 
 * \ingroup core
 * \scriptable
 */
class RTransactionEvent : public QEvent {
public:
    RTransactionEvent(bool onlyChanges=false, RS::EntityType entityTypeFilter = RS::EntityAll) :
        QEvent(QEvent::User), onlyChanges(onlyChanges), entityTypeFilter(entityTypeFilter) {}
    virtual ~RTransactionEvent() {}

    bool hasOnlyChanges() {
        return onlyChanges;
    }

    RS::EntityType getEntityTypeFilter() const {
        return entityTypeFilter;
    }

private:
    bool onlyChanges;
    RS::EntityType entityTypeFilter;
};

Q_DECLARE_METATYPE(RTransactionEvent*)

#endif
