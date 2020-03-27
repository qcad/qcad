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
#include "RModifyObjectsOperation.h"
#include "RSettings.h"
#include "RTranslation.h"

void RModifyObjectsOperation::transformSelection(RTransformation* transformation, RDocumentInterface* di, int copies, bool preview, bool selectResult, bool useCurrentAttributes) {
    RDocument& document = di->getDocument();
    RStorage& storage = document.getStorage();
    QSet<REntity::Id> ids = document.querySelectedEntities();
    QList<REntity::Id> list = storage.orderBackToFront(ids);
    bool move = false;
    if (copies==0) {
        copies=1;
        move = true;
    }

    bool translate = false;
    RVector translationOffset;
    double rotationAngle = 0.0;
    double scaleFactor = 1.0;
    RVector center = RVector::nullVector;

    RTranslation* translation = dynamic_cast<RTranslation*>(transformation);
    if (translation!=NULL) {
        translate = true;
        translationOffset = translation->offset;
        rotationAngle = translation->rotationAngle;
        scaleFactor = translation->scaleFactor;
        center = translation->center;
    }

    for (int k=1; k<=copies; k++) {
        QList<REntity::Id>::iterator it;
        for (it=list.begin(); it!=list.end(); it++) {
            if (preview && getPreviewCounter() > RSettings::getPreviewEntities()) {
                break;
            }

            REntity::Id id = *it;
            QSharedPointer<REntity> entity = document.queryEntity(id);
            if (entity.isNull()) {
                continue;
            }

            // copy: assign new IDs
            if (!move) {
                if (!preview && !selectResult) {
                    entity->setSelected(false);
                }
            }

            if (translate) {
                // TODO: entity->applyTransformation(transformation, k);
                if (!RMath::fuzzyCompare(scaleFactor, 0.0)) {
                    entity->rotate(rotationAngle, center);
                }
                if (!RMath::fuzzyCompare(scaleFactor, 1.0)) {
                    entity->scale(scaleFactor, center);
                }
                entity->move(translationOffset * k);
            }

            //QSet<RPropertyTypeId> props = entity->getPropertyTypeIds(RPropertyAttributes::Location);

            RAddObjectsOperation::Flags flags = RAddObjectsOperation::NoFlags;
            if (!useCurrentAttributes) {
                flags = flags | RAddObjectsOperation::UseAttributes | RAddObjectsOperation::GeometryOnly;
            }

            if (!move) {
                flags = flags | RAddObjectsOperation::ForceNew;
            }

            addObject(entity, flags);
        }
        endCycle();
    }

    // deselect original entities, all copies are selected:
    if (!preview && selectResult) {
        di->deselectEntities(ids);
    }
}
