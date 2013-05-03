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
#include "RAddObjectsOperation.h"
#include "RDocument.h"
#include "RSettings.h"

RAddObjectsOperation::RAddObjectsOperation(bool undoable) :
    ROperation(undoable), list(), previewCounter(0), limitPreview(true) {
}

RAddObjectsOperation::RAddObjectsOperation(
        QList<QSharedPointer<RObject> >& list,
        bool useCurrentAttributes, bool undoable) :
    ROperation(undoable), previewCounter(0), limitPreview(true) {

    for (int i=0; i<list.count(); ++i) {
        addObject(list[i], useCurrentAttributes);
    }
}

void RAddObjectsOperation::replaceObject(const QSharedPointer<RObject>& object,
        bool useCurrentAttributes) {

    if (object.isNull()) {
        return;
    }

    RObject::Id id = object->getId();

    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first.isNull()) {
            continue;
        }

        if (list[i].first->getId()==id) {
            list[i].first = object;
            list[i].second = useCurrentAttributes;
            return;
        }
    }

    addObject(object, useCurrentAttributes);
}

QSharedPointer<RObject> RAddObjectsOperation::getObject(RObject::Id id) {
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first.isNull()) {
            continue;
        }

        if (list[i].first->getId()==id) {
            return list[i].first;
        }
    }

    return QSharedPointer<RObject>();
}

void RAddObjectsOperation::addObject(const QSharedPointer<RObject>& object,
    bool useCurrentAttributes) {

    if (object.isNull()) {
        return;
    }

    if (limitPreview) {
        previewCounter += object->getComplexity();
    }

    list.append(QPair<QSharedPointer<RObject>, bool>(object, useCurrentAttributes));
}

RTransaction RAddObjectsOperation::apply(RDocument& document, bool preview) const {
    RTransaction transaction(document.getStorage(), "Adding object(s)", undoable);
    transaction.setRecordAffectedObjects(recordAffectedObjects);
    transaction.setSpatialIndexDisabled(spatialIndexDisabled);

    for (int i = 0; i < list.size(); ++i) {
        if (limitPreview && preview && i>RSettings::getPreviewEntities()) {
            break;
        }

        if (list[i].first.isNull()) {
            qWarning() << "RAddObjectsOperation::apply: "
                    "list contains NULL object";
            continue;
        }

        transaction.addObject(list[i].first, list[i].second);
    }

    transaction.end();
    return transaction;
}
