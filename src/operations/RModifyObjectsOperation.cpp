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
#include "RModifyObjectsOperation.h"
#include "RSettings.h"
#include "RTranslation.h"

void RModifyObjectsOperation::transformSelection(RTransformation* transformation, RDocumentInterface* di, int copies, bool preview, bool selectResult, bool useCurrentAttributes) {
    RDocument& document = di->getDocument();
    RStorage& storage = document.getStorage();
    QSet<REntity::Id> ids = document.querySelectedEntities();
    bool move = false;
    if (copies==0) {
        copies=1;
        move = true;
    }

    bool translate = false;
    RVector translationOffset;

    RTranslation* translation = dynamic_cast<RTranslation*>(transformation);
    if (translation!=NULL) {
        translate = true;
        translationOffset = translation->offset;
    }

    for (int k=1; k<=copies; k++) {
        QSet<REntity::Id>::iterator it;
        for (it=ids.begin(); it!=ids.end(); it++) {
            if (preview && getPreviewCounter() > RSettings::getPreviewEntities()) {
                break;
            }

            REntity::Id id = *it;
            QSharedPointer<REntity> entity = document.queryEntity(id);
            if (entity.isNull()) {
                continue;
            }

            QSharedPointer<REntity> newEntity;

            // copy: assign new IDs
            if (!move) {
                newEntity = QSharedPointer<REntity>(entity->clone());
                if (!preview && !selectResult) {
                    newEntity->setSelected(false);
                }
                storage.setObjectId(*newEntity, RObject::INVALID_ID);
            }

            // move: keep IDs:
            else {
                newEntity = entity;
            }

            if (translate) {
                newEntity->move(translationOffset * k);
            }

            addObject(newEntity, useCurrentAttributes);
        }
    }

    // deselect original entities, all copies are selected:
    if (!preview && selectResult) {
        di->deselectEntities(ids);
    }
}
