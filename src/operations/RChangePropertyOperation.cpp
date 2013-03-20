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
#include <QSet>

#include "RChangePropertyOperation.h"
#include "RDocument.h"

RChangePropertyOperation::RChangePropertyOperation(
    const RPropertyTypeId& propertyTypeId,
    const QVariant& value,
    RS::EntityType entityTypeFilter,
    bool undoable) :

    ROperation(undoable, entityTypeFilter),
    propertyTypeId(propertyTypeId),
    value(value) {
}

RChangePropertyOperation::RChangePropertyOperation(
    const RPropertyEvent& event,
    bool undoable) :
    ROperation(undoable, event.getEntityTypeFilter()),
    propertyTypeId(event.getPropertyTypeId()),
    value(event.getValue()) {
}

RTransaction RChangePropertyOperation::apply(RDocument& document, bool preview) const {
    RTransaction transaction(document.getStorage(), "Changing property");

    // 20111110: always allow property changes (e.g. move entity to hidden layer)
    transaction.setAllowInvisible(true);

    QVariant val = value;

    // optimization: change layer ID instead of changing layer name:
    if (propertyTypeId==REntity::PropertyLayer && value.type() == QVariant::String) {
        val = QVariant(document.getLayerId(value.toString()));
    }

    //RDebug::startTimer();

    QSet<REntity::Id> selectedEntities = document.querySelectedEntities();
    QSet<REntity::Id>::iterator it;
    for (it = selectedEntities.begin(); it != selectedEntities.end(); it++) {

        QSharedPointer<REntity> entity = document.queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        if (entityTypeFilter!=RS::EntityAll && entityTypeFilter!=entity->getType()) {
            continue;
        }

        // apply operation to entity:
        bool modified = entity->setProperty(propertyTypeId, val);

        if (modified) {
            transaction.addObject(entity, false,
                QSet<RPropertyTypeId>() << propertyTypeId);
        }
    }

    transaction.end();

    //RDebug::stopTimer("RChangePropertyOperation::apply");

    return transaction;
}

void RChangePropertyOperation::preview(RDocument& /*document*/, RExporter& /*exporter*/) const {
    // No preview for property editing
}
