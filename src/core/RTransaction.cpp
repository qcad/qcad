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
#include "RDocument.h"
#include "RExporter.h"
#include "RLinetype.h"
#include "RLinkedStorage.h"
#include "RMainWindow.h"
#include "RMemoryStorage.h"
#include "RStorage.h"
#include "RSpline.h"
#include "RTransaction.h"

RTransaction::RTransaction()
    : types(Generic),
      storage(NULL),
      transactionId(-1),
      transactionGroup(-1),
      undoable(true),
      failed(false),
      onlyChanges(true),
      recordAffectedObjects(true),
      allowAll(false),
      allowInvisible(false),
      spatialIndexDisabled(false),
      existingBlockDetectionDisabled(false),
      existingLayerDetectionDisabled(false),
      blockRecursionDetectionDisabled(false),
      keepHandles(false),
      undoing(false),
      redoing(false) {
}


/**
 * Constructs an empty, invalid transaction.
 */
RTransaction::RTransaction(RStorage& storage)
    : types(Generic),
      storage(&storage),
      transactionId(-1),
      transactionGroup(-1),
      undoable(true),
      failed(false),
      onlyChanges(true),
      recordAffectedObjects(true),
      allowAll(false),
      allowInvisible(false),
      spatialIndexDisabled(false),
      existingBlockDetectionDisabled(false),
      existingLayerDetectionDisabled(false),
      blockRecursionDetectionDisabled(false),
      keepHandles(false),
      undoing(false),
      redoing(false) {
}



/**
 * Constructor for existing transactions. This is used by storage
 * implementations to instantiate transactions from a storage (e.g. DB).
 */
RTransaction::RTransaction(
    RStorage& storage,
    int transactionId,
    const QString& text,
    const QList<RObject::Id>& affectedObjectIds,
    const QMap<RObject::Id, QList<RPropertyChange> >& propertyChanges)
    //RTransaction* parent)
    : types(Generic),
      storage(&storage),
      transactionId(transactionId),
      transactionGroup(-1),
      text(text),
      affectedObjectIds(affectedObjectIds),
      propertyChanges(propertyChanges),
      undoable(true),
      failed(false),
      onlyChanges(true),
      recordAffectedObjects(true),
      allowAll(false),
      allowInvisible(false),
      spatialIndexDisabled(false),
      existingBlockDetectionDisabled(false),
      existingLayerDetectionDisabled(false),
      blockRecursionDetectionDisabled(false),
      keepHandles(false),
      undoing(false),
      redoing(false) {

//    if (parent!=NULL) {
//        parent->appendChild(*this);
//    }

    affectedObjectIdsSet = affectedObjectIds.toSet();
}



/**
 * Constructor for new transactions.
 */
RTransaction::RTransaction(
    RStorage& storage,
    const QString& text,
    bool undoable)
    //RTransaction* parent)
    : types(Generic),
      storage(&storage),
      transactionId(-1),
      transactionGroup(-1),
      text(text),
      undoable(undoable),
      failed(false),
      onlyChanges(true),
      recordAffectedObjects(true),
      allowAll(false),
      allowInvisible(false),
      spatialIndexDisabled(false),
      existingBlockDetectionDisabled(false),
      existingLayerDetectionDisabled(false),
      blockRecursionDetectionDisabled(false),
      keepHandles(false),
      undoing(false),
      redoing(false) {

//    if (parent!=NULL) {
//        parent->appendChild(*this);
//    }

    this->storage->beginTransaction();
}



RTransaction::~RTransaction() {
}


void RTransaction::setType(RTransaction::Type type, bool on) {
    if (on) {
        types |= type;
    } else {
        types &= ~type;
    }
}

bool RTransaction::getType(RTransaction::Type type) const {
    return (types & type) == type;
}



/**
 * (Re-)applies this transaction to the document.
 */
void RTransaction::redo() {
    RDocument* document = storage->getDocument();
    if (document==NULL) {
        return;
    }

    // iterate through all objects that were affected by this transaction:
    for (int k=0; k<affectedObjectIds.size(); ++k) {
        RObject::Id objId = affectedObjectIds[k];

        // no properties have changed for this object,
        // i.e. object was created or deleted:
        if (statusChanges.contains(objId)) {
            QSharedPointer<RObject> object = storage->queryObjectDirect(objId);

            // toggle undo status of affected object:
            if (object->isUndone()) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();

                storage->setUndoStatus(*object, false);

                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->addToSpatialIndex(entity);
                }
            }
            else {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->removeFromSpatialIndex(entity);
                }
                storage->setUndoStatus(*object, true);
            }
        }

        // redo property changes:
        else {
            QSharedPointer<RObject> object = storage->queryObject(objId);
            if (object.isNull()) {
                qWarning("RTransaction::redo: object '%d' not found in storage", objId);
                continue;
            }
            if (document!=NULL) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    //qDebug() << "si: remove: " << *entity;
                    document->removeFromSpatialIndex(entity);
                }
            }

            storage->removeObject(storage->queryObjectDirect(objId));

            QList<RPropertyChange> objectChanges = propertyChanges.value(objId);
            for (int i=0; i<objectChanges.size(); ++i) {
                RPropertyTypeId propertyTypeId = objectChanges.at(i).propertyTypeId;
                object->setProperty(propertyTypeId, objectChanges.at(i).newValue);
            }

            storage->saveObject(object, false);

            if (document!=NULL) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    // entity of the block might have changed (in block drag and drop):
                    if (entity->getType()==RS::EntityBlockRef) {
                        //entity->update();
                        affectedBlockReferenceIds.insert(objId);
                    }
                    //qDebug() << "si: add: " << *entity;
                    document->addToSpatialIndex(entity);
                }
            }
        }
    }

    RMainWindow* mainWindow = RMainWindow::getMainWindow();
    if (mainWindow!=NULL && storage->getDocument()!=NULL) {
        mainWindow->notifyInterTransactionListeners(storage->getDocument(), this);
    }

    updateAffectedBlockReferences();
    undoing = true;
}



/**
 * Undoes this transaction.
 */
void RTransaction::undo() {
    RDocument* document = storage->getDocument();
    if (document==NULL) {
        return;
    }

    // iterate through all objects that were affected by this transaction:
    for (int k=affectedObjectIds.size()-1; k>=0; --k) {
        RObject::Id objId = affectedObjectIds[k];

        // no properties have changed for this object,
        // i.e. object was created or deleted:
        if (statusChanges.contains(objId)) {
            QSharedPointer<RObject> object = storage->queryObjectDirect(objId);

            // toggle undo status of affected object:
            if (object->isUndone()) {
                // object was deleted and is now restored:
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                storage->setUndoStatus(*object, false);
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->addToSpatialIndex(entity);
                }
            }
            else {
                // object was created and is now undone:
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->removeFromSpatialIndex(entity);
                }
                storage->setUndoStatus(*object, true);
            }
        }

        // undo property changes:
        else {
            QSharedPointer<RObject> object = storage->queryObject(objId);
            if (object.isNull()) {
                qWarning("RTransaction::undo: "
                    "object '%d' not found in storage", objId);
                continue;
            }

            if (document!=NULL) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->removeFromSpatialIndex(entity);
                }
            }

            storage->removeObject(storage->queryObjectDirect(objId));

            object->setAutoUpdatesBlocked(true);

            QList<RPropertyChange> objectChanges = propertyChanges.value(objId);
            for (int i=objectChanges.size()-1; i>=0; --i) {
                RPropertyTypeId propertyTypeId = objectChanges.at(i).propertyTypeId;
                object->setProperty(propertyTypeId, objectChanges.at(i).oldValue);
            }

            storage->saveObject(object, false);

            if (document!=NULL) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    // entity of the block might have changed (in block drag and drop):
                    if (entity->getType()==RS::EntityBlockRef) {
                        //entity->update();
                        affectedBlockReferenceIds.insert(objId);
                    }
                    document->addToSpatialIndex(entity);
                }
            }

            object->setAutoUpdatesBlocked(false);
        }
    }

    RMainWindow* mainWindow = RMainWindow::getMainWindow();
    if (mainWindow!=NULL && storage->getDocument()!=NULL) {
        mainWindow->notifyInterTransactionListeners(storage->getDocument(), this);
    }

    updateAffectedBlockReferences();
    undoing = true;
}

/**
 * Ends the current transaction cycle. A cycle typcially creates
 * one copy of a selection. This function is necessary to fix IDs in
 * parent / child related entities (block references / attributes).
 */
void RTransaction::endCycle() {
    // reparent cloned child objects:
    for (int i=0; i<affectedObjectIds.size(); i++) {
        RObject::Id id = affectedObjectIds[i];
        QSharedPointer<RObject> object = storage->queryObjectDirect(id);
        QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
        if (entity.isNull()) {
            continue;
        }

        REntity::Id parentId = entity->getParentId();
        if (cloneIds.contains(parentId)) {
            storage->setEntityParentId(*entity, cloneIds.value(parentId, REntity::INVALID_ID));
        }
    }
    cloneIds.clear();
}

/**
 * Saves this command to the storage of the document.
 */
void RTransaction::commit() {
    if (failed) {
        //qWarning() << "RTransaction::commit: transaction is in state 'failed'";
        //return;
    }

    //if (!isPreview()) {
        // no inter translation listener notification in preview:
        RMainWindow* mainWindow = RMainWindow::getMainWindow();
        if (mainWindow!=NULL && storage->getDocument()!=NULL) {
            mainWindow->notifyInterTransactionListeners(storage->getDocument(), this);
        }
    //}

    if (affectedObjectIds.size()>0) {
        storage->saveTransaction(*this);
    }
    storage->commitTransaction();

//    if (!cloneIds.isEmpty()) {
//        qWarning() << "RTransaction::commit: last cycle not closed";
//    }

    updateAffectedBlockReferences();
}

void RTransaction::fail() {
    //Q_ASSERT(false);
    failed = true;
}


void RTransaction::rollback() {
    storage->rollbackTransaction();
}

void RTransaction::end() {
    // 20111028: always commit for now
    // (paste partly to locked layer: at least paste what can be pasted)
    //if (failed) {
    //    rollback();
    //} else {
        commit();
    //}
}

void RTransaction::updateAffectedBlockReferences() {
    QSet<RObject::Id>::iterator it;
    for (it=affectedBlockReferenceIds.begin(); it!=affectedBlockReferenceIds.end(); ++it) {
        QSharedPointer<REntity> entity = storage->queryEntityDirect(*it);
        if (entity.isNull()) {
            continue;
        }

        entity->getDocument()->removeFromSpatialIndex(entity);
        entity->update();
        entity->getDocument()->addToSpatialIndex(entity);
    }
}

/**
 * Overwrites a potentially existing block with the given block.
 */
bool RTransaction::overwriteBlock(QSharedPointer<RBlock> block) {
    QString blockName = block->getName();
    if (blockName==RBlock::modelSpaceName) {
        //qWarning() << "RTransaction::overwriteBlock: "
        //              "trying to overwrite the model space block";
        return false;
    }

    bool hasBlock = storage->hasBlock(blockName);

    QSet<REntity::Id> refs;

    // block exists and must be overwritten:
    if (hasBlock) {
        // temporarily 'ground' all existing references to the existing block:
        refs = storage->queryBlockReferences(storage->getBlockId(blockName));
        QSet<REntity::Id>::iterator it;
        for (it = refs.begin(); it != refs.end(); ++it) {
            QSharedPointer<RBlockReferenceEntity> e =
                    storage->queryEntity(*it).dynamicCast<RBlockReferenceEntity> ();
            if (!e.isNull() && !e->isUndone()) {
                e->setReferencedBlockId(REntity::INVALID_ID);
                addObject(e, false);
            }
        }

        // delete existing block in dest:
        // block references are not deleted,
        // because they no longer reference this block
        // block contents is deleted
        deleteObject(storage->getBlockId(blockName), true);
    }

    // add new block to dest or overwrite block:
    addObject(block);

    // block exists and must be overwritten:
    if (hasBlock) {
        // point previously grounded block references to new block:
        QSet<REntity::Id>::iterator it;
        for (it = refs.begin(); it != refs.end(); ++it) {
            QSharedPointer<RBlockReferenceEntity> e =
                    storage->queryEntity(*it).dynamicCast<RBlockReferenceEntity> ();
            if (!e.isNull() && !e->isUndone()) {
                e->setReferencedBlockId(block->getId());
                addObject(e, false);
                affectedBlockReferenceIds.insert(*it);
            }
        }
    }
    return true;
}

/**
 * Adds the given object to the transaction. Adding an object to a
 * transaction means that this transaction modifies or adds the object.
 * Entities that are added with an invalid layer or block ID are placed
 * on the current layer / block.
 *
 * @param modifiedPropertyTypeId: Property IDs that have changed if known
 *      by caller, empty set otherwise.
 */
bool RTransaction::addObject(QSharedPointer<RObject> object,
    bool useCurrentAttributes,
    bool forceNew,
    const QSet<RPropertyTypeId>& modifiedPropertyTypeIds) {

    if (object.isNull()) {
        qWarning() << "RTransaction::addObject: object is NULL";
        fail();
        return false;
    }
    if (storage == NULL) {
        qWarning() << "RTransaction::addObject: storage is NULL";
        fail();
        return false;
    }
    if (transactionId != -1) {
        qWarning() << "RTransaction::addObject: "
            "Trying to add object to an existing transaction. "
            "Transactions are immutable once committed.";
        fail();
        Q_ASSERT(false);
        return false;
    }
    RDocument* doc = object->getDocument();
    if (doc==NULL) {
        qWarning() << "RTransaction::addObject: "
            "Object is not linked to a document.";
        fail();
        Q_ASSERT(false);
        return false;
    }

    RObject::Id oldId = RObject::INVALID_ID;
    if (forceNew) {
        oldId=object->getId();
        if (object->getId()!=RObject::INVALID_ID) {
            storage->setObjectId(*object, RObject::INVALID_ID);
        }
        if (object->getHandle()!=RObject::INVALID_ID) {
            storage->setObjectHandle(*object, RObject::INVALID_HANDLE);
        }
    }

    RLinkedStorage* ls = dynamic_cast<RLinkedStorage*>(storage);
    bool storageIsLinked = (ls!=NULL);
    RStorage* objectStorage = &doc->getStorage();

    if (objectStorage==NULL) {
        qWarning() << "RTransaction::addObject: "
                      "Object storage is NULL.";
        fail();
        Q_ASSERT(false);
        return false;
    }

    if (storageIsLinked && objectStorage!=ls && objectStorage!=ls->getBackStorage()) {
        qWarning() << "RTransaction::addObject: "
            "Object is not in linked storage or back storage of transaction.";
        fail();
        Q_ASSERT(false);
        return false;
    }

    if (!storageIsLinked && objectStorage!=storage) {
        qWarning() << "RTransaction::addObject: "
                      "Object is not in storage of transaction.";
        fail();
        Q_ASSERT(false);
        return false;
    }

    QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
    bool mustClone = false;
    if (!entity.isNull() && entity->getId()!=REntity::INVALID_ID) {
        // always clone:
        //mustClone = true;
        QSharedPointer<REntity> oldEntity = storage->queryEntityDirect(entity->getId());
        if (!oldEntity.isNull()) {
            // object is entity and not new:
            if (oldEntity->cloneOnChange()) {
                mustClone = true;
            }
        }
        if (!mustClone) {
            if (entity->getType()==RS::EntityHatch && modifiedPropertyTypeIds.isEmpty()) {
                // entity is hatch and not only one property has changed:
                mustClone = true;
            }
        }

        if (!mustClone) {
            if (entity->getType()==RS::EntitySpline) {
                RSpline* oldSpline = dynamic_cast<RSpline*>(oldEntity->castToShape());
                RSpline* spline = dynamic_cast<RSpline*>(entity->castToShape());
                if (spline!=NULL && oldSpline!=NULL) {
                    // entity is spline and has changed from fit points to control points or vice versa:
                    if (spline->hasFitPoints()!=oldSpline->hasFitPoints()) {
                        mustClone = true;
                    }
                }
            }
        }
    }

    if (!mustClone && object->getId()!=RObject::INVALID_ID) {
        if (object->mustAlwaysClone()) {
            mustClone = true;
        }
    }

    // if object is an existing hatch and we are not just changing a property:
    // delete original and add new since hatch geometry cannot be completely
    // defined through properties which is a requirement for changing objects
    // through transactions:
    // TODO: check if entity is editable:
    if (mustClone) {
        QSharedPointer<RObject> clone = QSharedPointer<RObject>(object->clone());

        objectStorage->setObjectId(*clone, RObject::INVALID_ID);
        // note that we delete the OLD entity here
        // (old entity is queried from storage since we pass the ID here):
        deleteObject(object->getId(), true);
        addObject(clone, useCurrentAttributes, false, modifiedPropertyTypeIds);

        // draw order was set to top value automatically by
        // saveObject of RMemoryStorage:
        QSharedPointer<REntity> entityClone = object.dynamicCast<REntity>();
        if (!entityClone.isNull()) {
            entityClone->setDrawOrder(entity->getDrawOrder());
        }
        return true;
    }

    // if object is an entity,
    // place entity on current layer / block, set current pen attributes:
    if (!entity.isNull()) {
        if (useCurrentAttributes || entity->getLayerId()==RLayer::INVALID_ID) {
            entity->setLayerId(doc->getCurrentLayerId());
        }
        if (useCurrentAttributes || entity->getBlockId()==RBlock::INVALID_ID) {
//            if (doc->hasCurrentViewport()) {
//                // got an active viewport: always add to model space:
//                entity->setBlockId(doc->getModelSpaceBlockId());
//            }
//            else {
                entity->setBlockId(doc->getCurrentBlockId());
//            }
        }
        if (useCurrentAttributes || !entity->getColor().isValid()) {
            entity->setColor(doc->getCurrentColor());
        }
        if (useCurrentAttributes || entity->getLineweight()==RLineweight::WeightInvalid) {
            entity->setLineweight(doc->getCurrentLineweight());
        }
        if (useCurrentAttributes || entity->getLinetypeId()==RLinetype::INVALID_ID) {
            entity->setLinetypeId(doc->getCurrentLinetypeId());
        }

        // move entity to current working set:
        // if we are editing a working set, add object to working set:
        if (doc->isEditingWorkingSet()) {
            entity->setWorkingSet(true);
            if (entity->isSelectedWorkingSet()) {
                entity->setSelectedWorkingSet(false);
                entity->setSelected(true);
            }
        }

        // allowAll to make sure entities on hidden / locked layers can be imported:
        if (!allowAll && !entity->isEditable(allowInvisible)) {
            qWarning() << "RTransaction::addObject: entity not editable (locked or hidden layer)";
            fail();
            return false;
        }

        Q_ASSERT_X(!doc->queryLayerDirect(entity->getLayerId()).isNull(),
            "RTransaction::addObject",
            "layer of entity is NULL");
    }


    // if object is a block definition,
    // look up existing block based on case insensitive name comparison:
    bool objectIsBlock = false;
    if (object->getType()==RS::ObjectBlock) {
        QSharedPointer<RBlock> block = object.dynamicCast<RBlock>();
        if (!block.isNull()) {
            objectIsBlock = true;

            if (!existingBlockDetectionDisabled) {
                QSharedPointer<RBlock> existingBlock = block->getDocument()->queryBlock(block->getName());
                if (!existingBlock.isNull()) {
                    storage->setObjectId(*block, existingBlock->getId());
                }
            }
        }
    }

    // if object is a layer,
    // look up existing layer based on case insensitive name comparison:
    if (object->getType()==RS::ObjectLayer) {
        if (!existingLayerDetectionDisabled && object->getId()==RObject::INVALID_ID) {
            QSharedPointer<RLayer> layer = object.dynamicCast<RLayer>();
            if (!layer.isNull()) {
                QSharedPointer<RLayer> existingLayer = layer->getDocument()->queryLayer(layer->getName());
                if (!existingLayer.isNull()) {
                    storage->setObjectId(*layer, existingLayer->getId());
                }
            }
        }
    }

    // if object is a linetype,
    // look up existing linetype based on case insensitive name comparison:
    if (object->getType()==RS::ObjectLinetype) {
        if (!existingLinetypeDetectionDisabled && object->getId()==RObject::INVALID_ID) {
            QSharedPointer<RLinetype> linetype = object.dynamicCast<RLinetype>();
            if (!linetype.isNull()) {
                QSharedPointer<RLinetype> existingLinetype = linetype->getDocument()->queryLinetype(linetype->getName());
                if (!existingLinetype.isNull()) {
                    storage->setObjectId(*linetype, existingLinetype->getId());
                }
            }
        }
    }

    bool objectHasChanged = false;
    QSharedPointer<RObject> oldObject;

    // object is an existing object that might have changed:
    if (object->getId() != RObject::INVALID_ID) {
        // store diff between previous object and this object
        // as part of this transaction:
        oldObject = storage->queryObjectDirect(object->getId());
        if (oldObject.isNull()) {
            qWarning() << "RTransaction::addObject: original object not found in storage for " << *object;
            fail();
            return false;
        }

        if (typeid(*oldObject) != typeid(*object)) {
            qWarning("RTransaction::addObject: "
                "type of original object and "
                "type of modified object don't match");
            fail();
            return false;
        }

        if (oldObject->getId() != object->getId()) {
            qWarning("RTransaction::addObject: "
                "id of original object and "
                "id of modified object don't match");
            fail();
            return false;
        }

        //qDebug() << "old obj: " << *oldObject;
        //qDebug() << "new obj: " << *object;

        // iterate through all properties of the original object
        // and store the property changes (if any) in this transaction:
        QSet<RPropertyTypeId> propertyTypeIds;
        if (modifiedPropertyTypeIds.isEmpty()) {
//            qWarning() << "doing full diff of all properties";
//            qWarning() << "old obj: " << *oldObject;
//            qWarning() << "new obj: " << *object;
            propertyTypeIds = object->getPropertyTypeIds();
        }
        else {
            propertyTypeIds = modifiedPropertyTypeIds;

            //qDebug() << "only diff props: " << propertyTypeIds;

            // if at least one property is a redundant property, we need to
            // check all properties for changes:
            bool all = false;
            QSet<RPropertyTypeId>::iterator it;
            for (it=propertyTypeIds.begin(); it!=propertyTypeIds.end(); ++it) {
                RPropertyTypeId pid = *it;
                QPair<QVariant, RPropertyAttributes> newProperty =
                    object->getProperty(pid);
                // redundant properties affect other properties:
                if (newProperty.second.isRedundant()) {
                    all = true;
                    break;
                }
            }

            if (all) {
                propertyTypeIds = object->getPropertyTypeIds();
//                qWarning() << "doing full diff of all properties";
//                qWarning() << "old obj: " << *oldObject;
//                qWarning() << "new obj: " << *object;
            }
        }

        propertyTypeIds.unite(object->getCustomPropertyTypeIds());
        propertyTypeIds.unite(oldObject->getCustomPropertyTypeIds());

        //qDebug() << "num props:" << propertyTypeIds.size();

        QSet<RPropertyTypeId>::iterator it;
        for (it=propertyTypeIds.begin(); it!=propertyTypeIds.end(); ++it) {
            RPropertyTypeId pid = *it;
            QPair<QVariant, RPropertyAttributes> newProperty =
                object->getProperty(pid);
            QPair<QVariant, RPropertyAttributes> oldProperty =
                oldObject->getProperty(pid);

//            if (pid==RObject::PropertyProtected) {
//                qDebug() << "pid: " << pid;
//                qDebug() << "old property: " << oldProperty.first;
//                qDebug() << "new property: " << newProperty.first;
//            }

            // don't record changes in redundant properties (e.g. angle for lines):
            if (newProperty.second.isRedundant()) {
                continue;
            }

            // property that has changed affects the visibility of
            // other attributes:
            if (newProperty.second.affectsOtherProperties()) {
                onlyChanges = false;
            }

            objectHasChanged |= addPropertyChange(
                object->getId(),
                RPropertyChange(
                    *it, 
                    oldProperty.first,
                    newProperty.first
                )
            );
        }

        if (objectHasChanged) {
            // remove old entity from storage (only if it has actually changed):
            storage->removeObject(oldObject);

            // only remove from si, if not linked storage / preview
            if (!storage->isInBackStorage(oldObject->getId())) {
                QSharedPointer<REntity> oldEntity = oldObject.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !oldEntity.isNull()) {
                    QSharedPointer<RBlockReferenceEntity> blockRef = oldEntity.dynamicCast<RBlockReferenceEntity>();
                    if (blockRef.isNull() || blockRef->getReferencedBlockId()!=RObject::INVALID_ID) {
                        doc->removeFromSpatialIndex(oldEntity);
                    }
                }
            }
        }
    }

    bool ret = true;

    // object is a new object or an existing object that has changed:
    if (object->getId()==RObject::INVALID_ID || objectHasChanged ||
        // always add block to linked storage to make sure that
        // block entities are found in linked storage:
        (objectIsBlock && storageIsLinked)) {

        // new object:
        if (object->getId()==RObject::INVALID_ID) {
            onlyChanges = false;
        }

        ret = storage->saveObject(object, !blockRecursionDetectionDisabled, keepHandles);

        if (!ret) {
            qCritical() << "RTransaction::addObject: saveObject() failed for object: ";
            qCritical() << *object;
        }

        else {

            if (oldId!=RObject::INVALID_ID) {
                cloneIds.insert(oldId, object->getId());
            }

            addAffectedObject(object);

            // only add to si, if not linked storage / preview
            if (!storageIsLinked) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
                    if (blockRef.isNull() || blockRef->getReferencedBlockId()!=RObject::INVALID_ID) {
                        doc->addToSpatialIndex(entity);
                    }

                    // update block references if entity has been changed inside a block
                    // that is not the current block (in block editing):
                    if (entity->getBlockId()!=storage->getCurrentBlockId()) {
                        affectedBlockReferenceIds.unite(storage->queryBlockReferences(entity->getBlockId()));
                    }
                }
            }

            if (!objectHasChanged) {
                statusChanges.insert(object->getId());
            }
        }
    }
    if (!ret) {
        fail();
    }

    return ret;
}



/**
 * Adds the given property change for the given object to this transaction.
 */
bool RTransaction::addPropertyChange(RObject::Id objectId, const RPropertyChange& propertyChange) {
    if (!RS::compare(propertyChange.oldValue, propertyChange.newValue, true)) {
        //propertyChanges.insert(objectId, propertyChange);
        QList<RPropertyChange> pc = propertyChanges.value(objectId);
        pc.append(propertyChange);
        propertyChanges.insert(objectId, pc);
        return true;
    }
    return false;
}


/**
 * Adds the given object to the list of objects that are
 * affected by this transaction.
 */
void RTransaction::addAffectedObject(RObject::Id objectId) {
    if (storage == NULL) {
        return;
    }

    //if (!affectedObjectIds.contains(objectId)) {
    if (!affectedObjectIdsSet.contains(objectId)) {
        addAffectedObject(storage->queryObjectDirect(objectId));
    }
}


/**
 * Adds the given objects to the list of objects that are
 * affected by this transaction.
 */
void RTransaction::addAffectedObjects(const QSet<RObject::Id>& objectIds) {
    if (storage == NULL) {
        return;
    }

    QSet<RObject::Id>::const_iterator it;
    for (it=objectIds.begin(); it!=objectIds.end(); it++) {
        addAffectedObject(*it);
    }
}

void RTransaction::addAffectedObject(QSharedPointer<RObject> object) {
    if (!recordAffectedObjects) {
        return;
    }

    if (object.isNull()) {
        return;
    }

    //if (affectedObjectIds.contains(object->getId())) {
    if (affectedObjectIdsSet.contains(object->getId())) {
        return;
    }

    // first add block as affected object (needs to be handled before entities in it):
    QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
    if (!entity.isNull()) {
        //if (!affectedObjectIds.contains(entity->getBlockId())) {
        if (!affectedObjectIdsSet.contains(entity->getBlockId())) {
            // if an entity has changed, the block definition it was in is affected:
            addAffectedObject(entity->getBlockId());

            // all block references of the block this entity is in are affected:
            // model space has no references:
            if (entity->getBlockId()!=storage->getModelSpaceBlockId()) {
                QSet<REntity::Id> affectedBlockRefIds = storage->queryBlockReferences(entity->getBlockId());
                addAffectedObjects(affectedBlockRefIds);
            }
        }
    }

    // add object after block:
    affectedObjectIds.append(object->getId());
    affectedObjectIdsSet.insert(object->getId());
}

void RTransaction::deleteObject(RObject::Id objectId, bool force) {
    QSharedPointer<RObject> obj = storage->queryObject(objectId);
    deleteObject(obj, force);
}

void RTransaction::deleteObject(QSharedPointer<RObject> object, bool force) {
    if (storage == NULL) {
        return;
    }

    //QSharedPointer<RObject> obj = storage->queryObject(objectId);
    if (object.isNull()) {
        qWarning("RTransaction::deleteObject: object is null");
        failed = true;
        return;
    }

    RLinkedStorage* ls = dynamic_cast<RLinkedStorage*>(storage);
    bool storageIsLinked = (ls!=NULL);

    onlyChanges = false;

    RObject::Id objectId = object->getId();

    if (object->isProtected()) {
        failed = true;
        qWarning() << "RTransaction::deleteObject: trying to delete protected object";
        return;
    }

    // if a layer is deleted, delete all entities on the layer:
    QSharedPointer<RLayer> layer = object.dynamicCast<RLayer>();
    if (!layer.isNull()) {
        if (layer->getName() == "0") {
            failed = true;
            qWarning() << "RTransaction::deleteObject: "
                    "trying to delete the default layer \"0\"";
            return;
        }
        if (layer->isLocked()) {
            failed = true;
            qWarning() << "RTransaction::deleteObject: "
                    "trying to delete locked layer: " << layer->getName();
            return;
        }

        // TODO: undeletable layers

        QSet<REntity::Id> ids = storage->queryLayerEntities(objectId, true);
        QSetIterator<REntity::Id> it(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), true);
        }

        // current layer deleted, reset current layer to layer "0":
        if (objectId == storage->getCurrentLayerId()) {
            storage->setCurrentLayer("0");
        }
    }

    // if a block is deleted, delete all entities in the block:
    QSharedPointer<RBlock> block = object.dynamicCast<RBlock> ();
    if (!block.isNull()) {
        if (block->getName() == RBlock::modelSpaceName) {
            qWarning() << "RTransaction::deleteObject: "
                     "trying to delete the model space block";
            return;
        }

        // make sure entities / block references on locked layers are deleted:
        bool allowAllOri = allowAll;
        allowAll = true;

        // delete all block references to this block:
        QSet<REntity::Id> ids = storage->queryBlockReferences(objectId);
        QSetIterator<REntity::Id> it(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), true);
        }

        // delete all entities of this block definition:
        ids = storage->queryBlockEntities(objectId);
        it = QSetIterator<REntity::Id>(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), true);
        }

        // current block deleted, reset current block to model space:
        if (objectId == storage->getCurrentBlockId()) {
            storage->setCurrentBlock(RBlock::modelSpaceName);
        }

        allowAll = allowAllOri;
    }

    QSharedPointer<REntity> entity = object.dynamicCast<REntity>();

    if (!entity.isNull()) {
        if (!allowAll && !force && !entity->isEditable(allowInvisible)) {
            qWarning() << "RTransaction::deleteObject: entity not editable (locked or hidden layer)";
            fail();
            return;
        }
    }

    // if the entity has child entities, delete all child entities (e.g. attributes):
    if (!entity.isNull() && storage->hasChildEntities(entity->getId())) {
        // make sure child entities on locked layers are deleted:
        bool allowAllOri = allowAll;
        allowAll = true;

        QSet<REntity::Id> ids = storage->queryChildEntities(entity->getId());
        QSetIterator<REntity::Id> it(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), true);
        }

        allowAll = allowAllOri;
    }

    // if the current view is deleted, reset current view:
    QSharedPointer<RView> view = object.dynamicCast<RView>();
    if (!view.isNull()) {
        if (objectId == storage->getCurrentViewId()) {
            storage->setCurrentView(QString());
        }
    }

    // add affected object to list (also adds block the object is in):
    addAffectedObject(objectId);
    statusChanges.insert(objectId);

    RDocument* document = storage->getDocument();
    if (document!=NULL) {
        if (!undoable) {
            // only remove from si, if not linked storage / preview
            if (!storageIsLinked && !spatialIndexDisabled && !entity.isNull()) {
                document->removeFromSpatialIndex(entity);
            }
            storage->deleteObject(objectId);
        } else {
            // only remove from si, if not linked storage / preview
            if (!storageIsLinked && !spatialIndexDisabled && !entity.isNull()) {
                document->removeFromSpatialIndex(entity);
            }
            storage->setUndoStatus(objectId, true);
        }
    }
}

bool RTransaction::isPreview() const {
    RLinkedStorage* ls = dynamic_cast<RLinkedStorage*>(storage);
    return (ls!=NULL);
}


/**
 * \return List of property changes by this transaction for the given object.
 */
QList<RPropertyChange> RTransaction::getPropertyChanges(RObject::Id id) const {
    if (!propertyChanges.contains(id)) {
        return QList<RPropertyChange>();
    }
    return propertyChanges[id];
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RTransaction& t) {
    dbg.nospace() << "RTransaction(" << QString("%1").arg((long)&t, 0, 16);

    dbg.nospace() << ", id: " << t.getId();
    dbg.nospace() << ", types: " << t.getTypes();
    dbg.nospace() << ", group: " << t.getGroup();
    dbg.nospace() << ", text: " << t.getText();

    {
        dbg.nospace() << "\n, affectedObjectIds: ";
        QList<RObject::Id> objs = t.getAffectedObjects();
        QList<RObject::Id>::iterator it;
        for (it = objs.begin(); it != objs.end(); ++it) {
            dbg.nospace() << *it << ", ";
        }
    }

//    {
//        dbg.nospace() << "\n, statusChanges: ";
//        QSet<RObject::Id> objs = t.getStatusChanges();
//        QSet<RObject::Id>::iterator it;
//        for (it = objs.begin(); it != objs.end(); ++it) {
//            dbg.nospace() << *it << ", ";
//        }
//    }

    {
        QMap<RObject::Id, QList<RPropertyChange> > propertyChanges = t.getPropertyChanges();
        if (!propertyChanges.isEmpty()) {
            dbg.nospace() << "\n, propertyChanges: ";
        }
        QMap<RObject::Id, QList<RPropertyChange> >::iterator it;
        for (it = propertyChanges.begin(); it != propertyChanges.end(); ++it) {
            dbg.nospace() << "\n\tobjectId: " << it.key() << ", \n\tchanges:\n\t";
            QList<RPropertyChange>::iterator it2;
            for (it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
                dbg.nospace() << *it2 << ", \n\t";
            }
        }
    }

    dbg.nospace() << ")";
    return dbg.space();
}

