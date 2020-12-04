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

//#if QT_VERSION >= 0x050000
//#include <QtConcurrent>
//#else
//#include <qtconcurrentmap.h>
//#endif

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



RTransaction RMoveSelectionOperation::apply(RDocument& document, bool preview) {
    RTransaction transaction(document.getStorage(), text);
    transaction.setGroup(transactionGroup);
    transaction.setTypes(transactionTypes);

    QSet<REntity::Id> selectedEntities = document.querySelectedEntities();

//    if (preview) {
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
//            RDebug::startTimer(7);
            if (entity->move(targetPoint - referencePoint)) {
//                RDebug::stopTimer(7, "move");
//                RDebug::startTimer(8);
                QSet<RPropertyTypeId> props = entity->getPropertyTypeIds(RPropertyAttributes::Location);
//                RDebug::stopTimer(8, "props");
//                RDebug::startTimer(9);
                transaction.addObject(entity, false, false, props);
//                RDebug::stopTimer(9, "add");
            }
        }
//    }
//    else {
//        QFutureWatcher<void> futureWatcher;
//        std::function<void(REntity::Id)> mv = [&](REntity::Id entityId) {
//            move(document, transaction, entityId);
//        };
//        futureWatcher.setFuture(QtConcurrent::map(selectedEntities, mv));
//        futureWatcher.waitForFinished();

//    }

    transaction.end();
    return transaction;
}

//void RMoveSelectionOperation::move(RDocument& document, RTransaction& transaction, REntity::Id entityId) {
//    static QMutex m;

//    //qDebug() << "move" << entityId;

//    QSharedPointer<REntity> entity = document.queryEntity(entityId);
//    if (entity.isNull()) {
//        return;
//    }

//    // apply operation to entity:
//    if (entity->move(targetPoint - referencePoint)) {
//        QSet<RPropertyTypeId> props = entity->getPropertyTypeIds(RPropertyAttributes::Location);

//        QMutexLocker ml(&m);
//        transaction.addObject(entity, false, false, props);
//    }
//}
