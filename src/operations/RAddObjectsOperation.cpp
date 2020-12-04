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
#include "RAddObjectsOperation.h"
#include "RDocument.h"
#include "RSettings.h"

RAddObjectsOperation::RAddObjectsOperation(bool undoable) :
    ROperation(undoable), previewCounter(0), limitPreview(true) {

    RDebug::incCounter("RAddObjectsOperation");
}

RAddObjectsOperation::RAddObjectsOperation(
        QList<QSharedPointer<RObject> >& list,
        bool useCurrentAttributes, bool undoable) :
    ROperation(undoable), previewCounter(0), limitPreview(true) {

    RDebug::incCounter("RAddObjectsOperation");
    for (int i=0; i<list.count(); ++i) {
        addObject(list[i], useCurrentAttributes);
    }
}

RAddObjectsOperation::~RAddObjectsOperation() {
    RDebug::decCounter("RAddObjectsOperation");
}

void RAddObjectsOperation::replaceObject(const QSharedPointer<RObject>& object,
        bool useCurrentAttributes) {

    if (object.isNull()) {
        return;
    }

    RObject::Id id = object->getId();

    for (int i = 0; i < addedObjects.size(); ++i) {
        if (addedObjects[i].object.isNull()) {
            continue;
        }

        if (addedObjects[i].object->getId()==id) {
            addedObjects[i].object = object;
            addedObjects[i].setUseAttributes(!useCurrentAttributes);
            return;
        }
    }

    addObject(object, useCurrentAttributes);
}

QSharedPointer<RObject> RAddObjectsOperation::getObject(RObject::Id id) {
    for (int i = 0; i < addedObjects.size(); ++i) {
        if (addedObjects[i].object.isNull()) {
            continue;
        }

        if (addedObjects[i].object->getId()==id) {
            return addedObjects[i].object;
        }
    }

    return QSharedPointer<RObject>();
}

void RAddObjectsOperation::endCycle() {
    addedObjects.append(RModifiedObjects());
}

void RAddObjectsOperation::addObject(const QSharedPointer<RObject>& object,
    bool useCurrentAttributes, bool forceNew) {

    if (object.isNull()) {
        return;
    }

    if (limitPreview) {
        previewCounter += object->getComplexity();
    }

    addedObjects.append(RModifiedObjects(object, useCurrentAttributes, forceNew));
}

void RAddObjectsOperation::addObject(const QSharedPointer<RObject>& object, RAddObjectsOperation::Flags flags) {
    if (object.isNull()) {
        return;
    }

    if (limitPreview) {
        previewCounter += object->getComplexity();
    }

    //qDebug() << "addObject: flags:" << flags;

    addedObjects.append(RModifiedObjects(object, flags));

    //qDebug() << "flags:" << addedObjects.last().flags;
}

void RAddObjectsOperation::deleteObject(const QSharedPointer<RObject>& object) {
    if (object.isNull()) {
        return;
    }

    addedObjects.append(RModifiedObjects(object));
}

RTransaction RAddObjectsOperation::apply(RDocument& document, bool preview) {
    RTransaction transaction(document.getStorage(), text, undoable);
    transaction.setRecordAffectedObjects(recordAffectedObjects);
    transaction.setSpatialIndexDisabled(spatialIndexDisabled);
    transaction.setAllowAll(allowAll);
    transaction.setAllowInvisible(allowInvisible);
    transaction.setGroup(transactionGroup);
    transaction.setTypes(transactionTypes);

    for (int i=0; i<addedObjects.size(); ++i) {
        if (limitPreview && preview && i>RSettings::getPreviewEntities()) {
            break;
        }

        RModifiedObjects modObj = addedObjects[i];

        if (modObj.object.isNull()) {
            transaction.endCycle();
            //qWarning() << "RAddObjectsOperation::apply: "
            //        "list contains NULL object";
            continue;
        }

        if (modObj.getDelete()) {
            transaction.deleteObject(modObj.object);
            continue;
        }

        QSet<RPropertyTypeId> props;
        if (modObj.getGeometryOnly()) {
            // we know that only geometry was modified for this object:
            props = modObj.object->getPropertyTypeIds(RPropertyAttributes::Geometry);
        }

        transaction.addObject(
            modObj.object,
            !modObj.getUseAttributes(),
            modObj.getForceNew(),
            props
        );
    }

    transaction.end();
    return transaction;
}
