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
#include <QSet>
#include <QSharedPointer>

#include "RDocument.h"
#include "RMoveReferencePointOperation.h"
#include "RExporter.h"


RMoveReferencePointOperation::RMoveReferencePointOperation(
    const RVector& referencePoint, 
    const RVector& targetPoint,
    Qt::KeyboardModifiers modifiers)
    : referencePoint(referencePoint),
      targetPoint(targetPoint),
      modifiers(modifiers),
      scene(NULL) {
}



RTransaction RMoveReferencePointOperation::apply(RDocument& document, bool preview) {
    Q_UNUSED(preview)

    RTransaction transaction(document.getStorage(), text);
    transaction.setGroup(transactionGroup);
    transaction.setTypes(transactionTypes);

    RVector delta = targetPoint-referencePoint;
    bool moveSelected = false;
    QMap<REntity::Id, QList<RRefPoint> > referencePoints;

    // if multilpe reference points are selected, move all of those:
    if (scene!=NULL && scene->hasSelectedReferencePoints()) {
        moveSelected = true;
        referencePoints = scene->getReferencePoints();
    }

    QSet<REntity::Id> selectedEntities = document.querySelectedEntities();
    QSet<REntity::Id>::iterator it;
    for (it=selectedEntities.begin(); it!=selectedEntities.end(); it++) {
        QSharedPointer<REntity> entity = document.queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }
        
        // move all selected reference points:
        if (moveSelected) {
            QList<RRefPoint> entityReferencePoints = referencePoints[*it];
            for (int i=0; i<entityReferencePoints.length(); i++) {
                if (entityReferencePoints[i].isSelected()) {
                    entity->moveReferencePoint(entityReferencePoints[i], entityReferencePoints[i]+delta, modifiers);
                }
            }
            QSet<RPropertyTypeId> props = entity->getPropertyTypeIds(RPropertyAttributes::RefPoint);
            transaction.addObject(entity, false, false, props);
        }

        // move single reference point:
        else {
            if (entity->moveReferencePoint(referencePoint, targetPoint, modifiers)) {
                QSet<RPropertyTypeId> props = entity->getPropertyTypeIds(RPropertyAttributes::RefPoint);
                transaction.addObject(entity, false, false, props);
            }
        }
    }
        
    transaction.end();

    return transaction;
}
