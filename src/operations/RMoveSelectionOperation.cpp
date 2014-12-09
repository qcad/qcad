/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#include "RDocument.h"
#include "RExporter.h"
#include "RMoveSelectionOperation.h"
#include "RSettings.h"


RMoveSelectionOperation::RMoveSelectionOperation(
    const RVector& referencePoint, 
    const RVector& targetPoint)
    : referencePoint(referencePoint),
      targetPoint(targetPoint) {
}



RTransaction RMoveSelectionOperation::apply(RDocument& document, bool preview) const {
    RTransaction transaction(document.getStorage(), text);
    transaction.setGroup(transactionGroup);

    QSet<REntity::Id> selectedEntities = document.querySelectedEntities();
    int counter = 0;
    QSet<REntity::Id>::iterator it;
    for (it=selectedEntities.begin(); it!=selectedEntities.end(); it++) {
        if (preview && ++counter>RSettings::getPreviewEntities()) {
            break;
        }

        QSharedPointer<REntity> entity = document.queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }

        // apply operation to entity:
        if (entity->move(targetPoint - referencePoint)) {
            transaction.addObject(entity, false);
        }
    }

    transaction.end();

    return transaction;
}
