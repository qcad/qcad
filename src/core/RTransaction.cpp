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
#include "RDocument.h"
#include "RExporter.h"
#include "RLinkedStorage.h"
#include "RMemoryStorage.h"
#include "RStorage.h"
#include "RTransaction.h"

RTransaction::RTransaction()
    : storage(NULL),
      transactionId(-1),
      undoable(true),
      failed(false),
      onlyChanges(true),
      recordAffectedObjects(true),
      allowAll(false),
      allowInvisible(false),
      spatialIndexDisabled(false),
      existingBlockDetectionDisabled(false),
      existingLayerDetectionDisabled(false),
      blockRecursionDetectionDisabled(false) {
}


/**
 * Constructs an empty, invalid transaction.
 */
RTransaction::RTransaction(RStorage& storage)
    : storage(&storage),
      transactionId(-1),
      undoable(true),
      failed(false),
      onlyChanges(true),
      recordAffectedObjects(true),
      allowAll(false),
      allowInvisible(false),
      spatialIndexDisabled(false),
      existingBlockDetectionDisabled(false),
      existingLayerDetectionDisabled(false),
      blockRecursionDetectionDisabled(false) {
}



/**
 * Constructor for existing transactions. This is used by storage
 * implementations to instantiate transactions from a storage (e.g. DB).
 */
RTransaction::RTransaction(
    RStorage& storage,
    int transactionId,
    const QString& text,
    const QList<RObject::Id>& affectedObjects,
    const QMap<RObject::Id, QList<RPropertyChange> >& propertyChanges)
    //RTransaction* parent)
    : storage(&storage),
      transactionId(transactionId),
      text(text),
      affectedObjects(affectedObjects),
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
      blockRecursionDetectionDisabled(false) {

//    if (parent!=NULL) {
//        parent->appendChild(*this);
//    }

}



/**
 * Constructor for new transactions.
 */
RTransaction::RTransaction(
    RStorage& storage,
    const QString& text,
    bool undoable)
    //RTransaction* parent)
    : storage(&storage),
      transactionId(-1),
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
      blockRecursionDetectionDisabled(false) {

//    if (parent!=NULL) {
//        parent->appendChild(*this);
//    }

    this->storage->beginTransaction();
}



RTransaction::~RTransaction() {
}


/**
 * (Re-)applies this transaction to the document.
 */
void RTransaction::redo(RDocument* document) {
    // iterate through all objects that were affected by this transaction:
    for (int k=0; k<affectedObjects.size(); ++k) {
        RObject::Id objId = affectedObjects[k];

        // no properties have changed for this object,
        // i.e. object was created or deleted:
        if (statusChanges.contains(objId)) {
            QSharedPointer<RObject> object = storage->queryObjectDirect(objId);

            // toggle undo status of affected object:
            if (object->isUndone()) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();

                object->setUndone(false);

                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->addToSpatialIndex(entity);
                }
            }
            else {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->removeFromSpatialIndex(entity);
                }
                object->setUndone(true);
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
                    document->removeFromSpatialIndex(entity);
                }
            }

            QList<RPropertyChange> objectChanges = propertyChanges.value(objId);
            for (int i=0; i<objectChanges.size(); ++i) {
                RPropertyTypeId propertyTypeId = objectChanges.at(i).propertyTypeId;
                object->setProperty(propertyTypeId, objectChanges.at(i).newValue);
            }

            storage->saveObject(object, false);

            if (document!=NULL) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->addToSpatialIndex(entity);
                }
            }
        }
    }

    updateOverwrittenBlockReferences();
}



/**
 * Undoes this transaction.
 */
void RTransaction::undo(RDocument* document) {
    // iterate through all objects that were affected by this transaction:
    for (int k=affectedObjects.size()-1; k>=0; --k) {
        RObject::Id objId = affectedObjects[k];

        // no properties have changed for this object,
        // i.e. object was created or deleted:
        if (statusChanges.contains(objId)) {
            QSharedPointer<RObject> object = storage->queryObjectDirect(objId);

            // toggle undo status of affected object:
            if (object->isUndone()) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                object->setUndone(false);
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->addToSpatialIndex(entity);
                }
            }
            else {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->removeFromSpatialIndex(entity);
                }
                object->setUndone(true);
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

            QList<RPropertyChange> objectChanges = propertyChanges.value(objId);
            for (int i=objectChanges.size()-1; i>=0; --i) {
                RPropertyTypeId propertyTypeId = objectChanges.at(i).propertyTypeId;
                object->setProperty(propertyTypeId, objectChanges.at(i).oldValue);
            }

            storage->saveObject(object, false);

            if (document!=NULL) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    document->addToSpatialIndex(entity);
                }
            }
        }
    }

    updateOverwrittenBlockReferences();
}



/**
 * Saves this command to the storage of the document.
 */
void RTransaction::commit() {
    if (failed) {
        //qWarning() << "RTransaction::commit: transaction is in state 'failed'";
        //return;
    }
    if (affectedObjects.size()>0) {
        storage->saveTransaction(*this);
    }
    storage->commitTransaction();

    updateOverwrittenBlockReferences();
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

void RTransaction::updateOverwrittenBlockReferences() {
    // update spatial index entries of block references which reference
    // overwritten blocks:
    QList<RObject::Id>::iterator it;
    for (it=overwrittenBlockReferences.begin(); it!=overwrittenBlockReferences.end(); ++it) {
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
 * Overwrites an existing block with the given block.
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
        deleteObject(storage->getBlockId(blockName), block->getDocument());
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
                overwrittenBlockReferences.append(*it);
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
 * @param modifiedPropertyTypeId: Property ID that has changed if known 
 *      by caller, NULL otherwise.
 */
bool RTransaction::addObject(QSharedPointer<RObject> object,
    bool useCurrentAttributes,
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
    if (object->getDocument()==NULL) {
        qWarning() << "RTransaction::addObject: "
            "Object is not linked to a document.";
        fail();
        Q_ASSERT(false);
        return false;
    }

    RLinkedStorage* ls = dynamic_cast<RLinkedStorage*>(storage);
    bool storageIsLinked = (ls!=NULL);
    RStorage* objectStorage = &object->getDocument()->getStorage();

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

    // if object is an existing hatch and we are not just changing a property:
    // delete original and add new since hatch geometry cannot be completely
    // defined through properties which is a requirement for changing objects
    // through transactions:
    QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
    if (!entity.isNull() && entity->getType()==RS::EntityHatch &&
        entity->getId()!=REntity::INVALID_ID && modifiedPropertyTypeIds.isEmpty()) {

        QSharedPointer<REntity> clone = QSharedPointer<REntity>(entity->clone());
        objectStorage->setObjectId(*clone, REntity::INVALID_ID);
        deleteObject(entity, entity->getDocument());
        addObject(clone, useCurrentAttributes, modifiedPropertyTypeIds);
        return true;
    }

    // if object is an entity,
    // place entity on current layer / block, set current pen attributes:
    if (!entity.isNull()) {
        if (useCurrentAttributes || entity->getLayerId()==RLayer::INVALID_ID) {
            entity->setLayerId(object->getDocument()->getCurrentLayerId());
        }
        if (useCurrentAttributes || entity->getBlockId()==RBlock::INVALID_ID) {
            entity->setBlockId(object->getDocument()->getCurrentBlockId());
        }
        if (useCurrentAttributes || !entity->getColor().isValid()) {
            entity->setColor(object->getDocument()->getCurrentColor());
        }
        if (useCurrentAttributes || entity->getLineweight()==RLineweight::WeightInvalid) {
            entity->setLineweight(object->getDocument()->getCurrentLineweight());
        }
        if (useCurrentAttributes || entity->getLinetypeId()==RLinetype::INVALID_ID) {
            entity->setLinetype(object->getDocument()->getCurrentLinetype());
        }

        // 20110922: prevents entities on hidden / locked layers to be imported:
        if (!allowAll && !entity->isEditable(allowInvisible)) {
            //qWarning() << "RTransaction::addObject: entity is not editable";
            fail();
            return false;
        }
    }

    // if object is a block definition,
    // look up existing block based on case insensitive name comparison:
    bool objectIsBlock = false;
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

    // if object is a layer,
    // look up existing layer based on case insensitive name comparison:
    if (!existingLayerDetectionDisabled) {
        QSharedPointer<RLayer> layer = object.dynamicCast<RLayer>();
        if (!layer.isNull()) {
            QSharedPointer<RLayer> existingLayer = layer->getDocument()->queryLayer(layer->getName());
            if (!existingLayer.isNull()) {
                storage->setObjectId(*layer, existingLayer->getId());
            }
        }
    }

    bool objectHasChanged = false;

    // object is an existing object that might have changed:
    if (object->getId() != RObject::INVALID_ID) {
        // store diff between previous object and this object
        // as part of this transaction:
        QSharedPointer<RObject> oldObject =
            storage->queryObjectDirect(object->getId());
        if (oldObject.isNull()) {
            qWarning("RTransaction::addObject: "
                "original object not found in storage");
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

        // iterate through all properties of the original object
        // and store the property changes (if any) in this transaction:
        QSet<RPropertyTypeId> propertyTypeIds;
        if (modifiedPropertyTypeIds.isEmpty()) {
            propertyTypeIds = object->getPropertyTypeIds();
        }
        else {
            propertyTypeIds = modifiedPropertyTypeIds;

            // if at least one property is a redundant property, we need to
            // check all properties for changes:
            bool all = false;
            QSet<RPropertyTypeId>::iterator it;
            for (it=propertyTypeIds.begin(); it!=propertyTypeIds.end(); ++it) {
                QPair<QVariant, RPropertyAttributes> newProperty =
                    object->getProperty(*it);
                // redundant properties affect other properties:
                if (newProperty.second.isRedundant()) {
                    all = true;
                    break;
                }
            }

            if (all) {
                propertyTypeIds = object->getPropertyTypeIds();
            }
        }

        QSet<RPropertyTypeId>::iterator it;
        for (it=propertyTypeIds.begin(); it!=propertyTypeIds.end(); ++it) {
            QPair<QVariant, RPropertyAttributes> newProperty =
                object->getProperty(*it);
            QPair<QVariant, RPropertyAttributes> oldProperty =
                oldObject->getProperty(*it);

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
            if (object->getDocument()!=NULL) {
                // only remove from si, if not linked storage / preview
                if (!storage->isInBackStorage(oldObject->getId())) {
                    QSharedPointer<REntity> oldEntity = oldObject.dynamicCast<REntity>();
                    if (!spatialIndexDisabled && !oldEntity.isNull()) {
                        QSharedPointer<RBlockReferenceEntity> blockRef = oldEntity.dynamicCast<RBlockReferenceEntity>();
                        if (blockRef.isNull() || blockRef->getReferencedBlockId()!=RObject::INVALID_ID) {
                            object->getDocument()->removeFromSpatialIndex(oldEntity);
                        }
                    }
                }
            }
        }
    }

    bool ret = true;
    // this is a new object or an existing object that has changed:
    if (object->getId()==RObject::INVALID_ID || objectHasChanged ||
        // 20120608: always add block to linked storage to make sure that
        // block entities are found in linked storage:
        (objectIsBlock && storageIsLinked)) {
        // new object:
        if (object->getId()==RObject::INVALID_ID) {
            onlyChanges = false;
        }

        //if (object->getDocument()!=NULL) {
            // only add to si, if not linked storage / preview
            //if (!storage->isInBackStorage(object->getId())) {
//            if (ls==NULL) {
//                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
//                if (!spatialIndexDisabled && !entity.isNull()) {
//                    object->getDocument()->addToSpatialIndex(entity);
//                }
//            }
        //}

        ret = storage->saveObject(object, !blockRecursionDetectionDisabled);

        if (!ret) {
            qCritical() << "RTransaction::addObject: saveObject() failed for object: ";
            qCritical() << *object;
        }

        addAffectedObject(object);

        if (object->getDocument()!=NULL) {
            // only add to si, if not linked storage / preview
            if (!storageIsLinked) {
                QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
                if (!spatialIndexDisabled && !entity.isNull()) {
                    QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
                    if (blockRef.isNull() || blockRef->getReferencedBlockId()!=RObject::INVALID_ID) {
                        object->getDocument()->addToSpatialIndex(entity);
                    }
                }
            }
        }

        if (!objectHasChanged) {
            statusChanges.insert(object->getId());
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
    if (!RS::compare(propertyChange.oldValue, propertyChange.newValue)) {
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

    if (!affectedObjects.contains(objectId)) {
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

    if (affectedObjects.contains(object->getId())) {
        return;
    }

    affectedObjects.append(object->getId());

    QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
    if (!entity.isNull()) {
        if (!affectedObjects.contains(entity->getBlockId())) {
            // if an entity has changed, the block definition it was in is affected:
            addAffectedObject(entity->getBlockId());

            // all block references of the block this entity is in are affected:
            QSet<REntity::Id> affectedBlockRefs = storage->queryBlockReferences(entity->getBlockId());
            addAffectedObjects(affectedBlockRefs);
        }
    }
}

void RTransaction::deleteObject(RObject::Id objectId, RDocument* document) {
    QSharedPointer<RObject> obj = storage->queryObject(objectId);
    deleteObject(obj, document);
}

void RTransaction::deleteObject(QSharedPointer<RObject> object, RDocument* document) {
    if (storage == NULL || document == NULL) {
        return;
    }

    //QSharedPointer<RObject> obj = storage->queryObject(objectId);
    if (object.isNull()) {
        qWarning("RTransaction::deleteObject: "
            "original object not found in storage");
        failed = true;
        return;
    }

    onlyChanges = false;

    RObject::Id objectId = object->getId();

    // if a layer is deleted, delete all entities on the layer:
    QSharedPointer<RLayer> layer = object.dynamicCast<RLayer>();
    if (!layer.isNull()) {
        if (layer->getName() == "0") {
            qWarning() << "RTransaction::deleteObject: "
                    "trying to delete the default layer \"0\"";
            return;
        }
        QSet<REntity::Id> ids = storage->queryLayerEntities(objectId, true);
        QSetIterator<REntity::Id> it(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), document);
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

        // delete all block references to this block:
        QSet<REntity::Id> ids = storage->queryBlockReferences(objectId);
        QSetIterator<REntity::Id> it(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), document);
        }

        // delete all entities of this block definition:
        ids = storage->queryBlockEntities(objectId);
        it = QSetIterator<REntity::Id>(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), document);
        }

        // current block deleted, reset current block to model space:
        if (objectId == storage->getCurrentBlockId()) {
            storage->setCurrentBlock(RBlock::modelSpaceName);
        }
    }

    QSharedPointer<REntity> entity = object.dynamicCast<REntity>();

    // if the entity has child entities, delete all child entities (e.g. attributes):
    if (!entity.isNull() && document->hasChildEntities(entity->getId())) {
        QSet<REntity::Id> ids = document->queryChildEntities(entity->getId());
        QSetIterator<REntity::Id> it(ids);
        while (it.hasNext()) {
            deleteObject(it.next(), document);
        }
    }

    // if the current view is deleted, reset current view:
    QSharedPointer<RView> view = object.dynamicCast<RView>();
    if (!view.isNull()) {
        if (objectId == storage->getCurrentViewId()) {
            storage->setCurrentView(QString());
        }
    }

    // if an entity is deleted, the block definition it was in is affected:
    if (!entity.isNull()) {
        addAffectedObject(entity->getBlockId());
    }

    addAffectedObject(objectId);
    statusChanges.insert(objectId);

    if (!undoable) {
        //QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
        if (!spatialIndexDisabled && !entity.isNull()) {
            document->removeFromSpatialIndex(entity);
        }
        storage->deleteObject(objectId);
//        if (!spatialIndexDisabled && !entity.isNull()) {
//            document->removeFromSpatialIndex2(entity);
//        }
    } else {
        //QSharedPointer<REntity> entity = object.dynamicCast<REntity>();
        if (!spatialIndexDisabled && !entity.isNull()) {
            document->removeFromSpatialIndex(entity);
        }
        storage->setUndoStatus(objectId, true);
//        if (!spatialIndexDisabled && !entity.isNull()) {
//            document->removeFromSpatialIndex2(entity);
//        }
    }
}

/**
 * Appends the given child to the list of child transactions of
 * this transaction. This transaction takes o
 */
//void RTransaction::appendChild(RTransaction& t) {
//    childTransactions.push_back(t);
//}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RTransaction& t) {
    dbg.nospace() << "RTransaction(";

    dbg.nospace() << "id: " << t.getId();
    dbg.nospace() << ", text: " << t.getText();

    {
        dbg.nospace() << "\n, affectedObjects: ";
        QList<RObject::Id> objs = t.getAffectedObjects();
        QList<RObject::Id>::iterator it;
        for (it = objs.begin(); it != objs.end(); ++it) {
            dbg.nospace() << *it << ", ";
        }
    }

    {
        dbg.nospace() << "\n, statusChanges: ";
        QSet<RObject::Id> objs = t.getStatusChanges();
        QSet<RObject::Id>::iterator it;
        for (it = objs.begin(); it != objs.end(); ++it) {
            dbg.nospace() << *it << ", ";
        }
    }

    {
        dbg.nospace() << "\n, propertyChanges: ";
        QMap<RObject::Id, QList<RPropertyChange> > propertyChanges =
            t.getPropertyChanges();
        QMap<RObject::Id, QList<RPropertyChange> >::iterator it;
        for (it = propertyChanges.begin(); it != propertyChanges.end(); ++it) {
            dbg.nospace() << "\n\tobjectId: " << it.key() << ", \n\tchanges:\n\t";
            QList<RPropertyChange>::iterator it2;
            for (it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
                dbg.nospace() << *it2 << ", \n\t";
            }
        }
        dbg.nospace() << "\n)\n";
    }

    dbg.nospace() << ")";
    return dbg.space();
}

