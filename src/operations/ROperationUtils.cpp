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
#include "RDocumentInterface.h"
#include "ROperationUtils.h"
#include "RAddObjectsOperation.h"

/**
 * Normalizes the draw order of all entities,
 * avoiding duplicate orders or gaps, starting with 0.
 */
void ROperationUtils::normalizeDrawOrder(RDocumentInterface* di, bool useTransactionGroup) {
    if (di==NULL) {
        return;
    }

    RDocument& doc = di->getDocument();

    RAddObjectsOperation* op = new RAddObjectsOperation();
    op->setAllowInvisible(true);
    op->setAllowAll(true);
    if (useTransactionGroup) {
        op->setTransactionGroup(doc.getTransactionGroup());
    }

    QSet<REntity::Id> idsSet = doc.queryAllEntities();
    QList<REntity::Id> ids = doc.getStorage().orderBackToFront(idsSet);
    for (int i=0; i<ids.length(); i++) {
        RObject::Id id = ids[i];
        QSharedPointer<REntity> e = doc.queryEntity(id);
        if (!e.isNull()) {
            e->setDrawOrder(i);
            op->addObject(e, false);
        }
    }

    di->applyOperation(op);
}
