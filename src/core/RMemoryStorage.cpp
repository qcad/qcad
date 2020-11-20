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
#include <QRegExp>

#include "RMemoryStorage.h"
#include "RSettings.h"
#include "RS.h"

RMemoryStorage::RMemoryStorage() :
    maxLineweight(RLineweight::Weight000), 
    boundingBoxDirty(true),
    //boundingBoxIgnoreHiddenLayers(false),
    //boundingBoxIgnoreEmpty(false),
    inTransaction(false),
    selectedEntityMapDirty(true),
    visibleEntityMapDirty(true),
    selectedLayerMapDirty(true) {

    setLastTransactionId(-1);
}

RMemoryStorage::~RMemoryStorage() {
}

void RMemoryStorage::clear() {
    RStorage::clear();

    maxLineweight = RLineweight::Weight000;
    inTransaction = false;
    boundingBoxDirty = true;
    boundingBox[0][0] = RBox();
    boundingBox[0][1] = RBox();
    boundingBox[1][0] = RBox();
    boundingBox[1][1] = RBox();
    objectMap.clear();
    objectHandleMap.clear();
    entityMap.clear();
    selectedEntityMap.clear();
    selectedEntityMapDirty = true;
    visibleEntityMap.clear();
    visibleEntityMapDirty = true;
    selectedLayerMap.clear();
    selectedLayerMapDirty = true;
    blockEntityMap.clear();
    blockMap.clear();
    typeObjectMap.clear();
    layerMap.clear();
    layerNameMap.clear();
    layerStateMap.clear();
    layoutMap.clear();
    linetypeMap.clear();
    childMap.clear();
    transactionMap.clear();
    documentVariables.clear();
    variables.clear();
    variableCaseMap.clear();
    if (!documentVariables.isNull()) {
        documentVariables->clear();
    }
    //linetypeScale = 1.0;
    setLastTransactionId(-1);
}

void RMemoryStorage::setCurrentBlock(RBlock::Id blockId) {
    RStorage::setCurrentBlock(blockId);
    boundingBoxDirty = true;
    clearSelectionCache();
    clearVisibleCache();
}

/*
QList<REntity::Id> RMemoryStorage::orderBackToFront(const QSet<REntity::Id>& entityIds) {
    QMap<int, REntity::Id> res;
    QSet<REntity::Id>::const_iterator it;
    maxDrawOrder = 0;
    for (it = entityIds.begin(); it != entityIds.end(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (!e.isNull()) {
            res.insertMulti(e->getDrawOrder(), *it);
            maxDrawOrder = qMax(e->getDrawOrder(), maxDrawOrder);
        }
    }
    return res.values();
}
*/

bool RMemoryStorage::isSelected(REntity::Id entityId) {
    QSharedPointer<REntity> e = queryEntityDirect(entityId);
    return (!e.isNull() && e->isSelected());
}

bool RMemoryStorage::isSelectedWorkingSet(REntity::Id entityId) {
    QSharedPointer<REntity> e = queryEntityDirect(entityId);
    return (!e.isNull() && e->isSelectedWorkingSet());
}

bool RMemoryStorage::isEntityVisible(const REntity& entity) const {
    updateVisibleCache();
    REntity::Id id = entity.getId();
    // query visibility cache:
    if (visibleEntityMap.contains(id)) {
        return true;
    }
    return false;

    //qDebug() << "RMemoryStorage::isEntityVisible: not cached";

    // not in cache, update cache (slow):
//    bool vis = RStorage::isEntityVisible(entity);
//    if (vis) {
//        visibleEntityMap.insert(id, queryEntityDirect(id));
//    }
//    return vis;
}

void RMemoryStorage::beginTransaction() {
    inTransaction = true;

    // delete transactions that are lost for good due to this transaction:
    deleteTransactionsFrom(getLastTransactionId() + 1);
}

void RMemoryStorage::commitTransaction() {
    // copy transaction objects to memory storage:
    /*
    QHash<RObject::Id, QSharedPointer<RObject> >::iterator it;
    for (it = transactionObjectMap.begin(); it!=transactionObjectMap.end(); ++it) {
        if (it.value().isNull()) {
            objectMap.remove(it.key());
        }
        else {
            objectMap[it.key()] = it.value();
        }
    }

    transactionObjectMap.clear();
    */
    inTransaction = false;
    boundingBoxDirty = true;

    setModified(true);
}

void RMemoryStorage::rollbackTransaction() {
    // drop transaction objects:
    //transactionObjectMap.clear();
    //Q_ASSERT(false);
}

QSet<RObject::Id> RMemoryStorage::queryAllObjects() const {
    //result = QSet<RObject::Id>::fromList(objectMap.keys());
    QSet<RObject::Id> result;
    QHash<RObject::Id, QSharedPointer<RObject> >::const_iterator it;
    for (it = objectMap.constBegin(); it != objectMap.constEnd(); ++it) {
        if (!(*it).isNull() && !(*it)->isUndone()) {
            result.insert((*it)->getId());
        }
    }
    return result;
}

/**
 * \return IDs of all visible entities
 * (current block only, no frozen or off layers, no frozen blocks, no undone entities).
 */
QSet<REntity::Id> RMemoryStorage::queryAllVisibleEntities() {
    updateVisibleCache();
    return visibleEntityMap.keys().toSet();

    /*
    QSet<REntity::Id> result;
    result.reserve(entityMap.count());
    RBlock::Id currentBlock = getCurrentBlockId();
    QHash<REntity::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull()) {
            continue;
        }
        if (e->isUndone()) {
            continue;
        }

        {
            // check if entity is part of a frozen block:
            RBlock::Id blockId = e->getBlockId();
            if (blockId != currentBlock) {
                continue;
            }
            QSharedPointer<RBlock> block = queryBlockDirect(blockId);
            if (!block.isNull()) {
                if (block->isFrozen()) {
                    continue;
                }
            }
        }

        // check if entity is a reference to a frozen block:
        QSharedPointer<RBlockReferenceEntity> blockRef = e.dynamicCast<RBlockReferenceEntity>();
        if (!blockRef.isNull()) {
            RBlock::Id blockId = blockRef->getReferencedBlockId();
            QSharedPointer<RBlock> block = queryBlockDirect(blockId);
            if (!block.isNull()) {
                if (block->isFrozen()) {
                    continue;
                }
            }
        }

        RLayer::Id layerId = e->getLayerId();
        if (isLayerOffOrFrozen(layerId)) {
            continue;
        }

        result.insert(e->getId());
    }
    return result;
    */
}

QSet<REntity::Id> RMemoryStorage::queryAllEntities(bool undone, bool allBlocks, RS::EntityType type) {
    QSet<REntity::Id> result;

    QHash<REntity::Id, QSharedPointer<REntity> >* map;
    if (allBlocks) {
        map = &entityMap;
    }
    else {
        RBlock::Id currentBlockId = getCurrentBlockId();
        if (blockEntityMap.contains(currentBlockId)) {
            map = &blockEntityMap[currentBlockId];
        }
        else {
            return result;
        }
    }

    result.reserve(map->count());
    QHash<REntity::Id, QSharedPointer<REntity> >::iterator it;
    for (it = map->begin(); it != map->end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull()) {
            continue;
        }
        if (!undone && e->isUndone()) {
            continue;
        }
//        if (!allBlocks && e->getBlockId() != currentBlock) {
//            continue;
//        }
        if (type!=RS::EntityAll && e->getType()!=type) {
            continue;
        }
        result.insert(e->getId());
    }

    return result;
}

QSet<REntity::Id> RMemoryStorage::queryAllEntities(bool undone, bool allBlocks, QList<RS::EntityType> types) {
    QSet<REntity::Id> result;
    result.reserve(entityMap.count());
    RBlock::Id currentBlock = getCurrentBlockId();
    QHash<REntity::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull()) {
            continue;
        }
        if (!undone && e->isUndone()) {
            continue;
        }
        if (!allBlocks && e->getBlockId() != currentBlock) {
            continue;
        }
        if (!types.isEmpty() && !types.contains(e->getType())) {
            continue;
        }
        result.insert(e->getId());
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryWorkingSetEntities() {
    QSet<REntity::Id> result;
    RBlock::Id currentBlock = getCurrentBlockId();
    QHash<REntity::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull()) {
            continue;
        }
        if (e->isUndone()) {
            continue;
        }
        if (e->getBlockId() != currentBlock) {
            continue;
        }
        if (!e->isWorkingSet()) {
            continue;
        }

        result.insert(e->getId());
    }
    return result;
}

QSet<RUcs::Id> RMemoryStorage::queryAllUcs() {
    QSet<RUcs::Id> result;
    QHash<RObject::Id, QSharedPointer<RObject> >::iterator it;
    for (it = objectMap.begin(); it != objectMap.end(); ++it) {
        QSharedPointer<RUcs> u = it->dynamicCast<RUcs>();
        if (!u.isNull() && !u->isUndone()) {
            result.insert(u->getId());
        }
    }
    return result;
}

QSet<RLayer::Id> RMemoryStorage::queryAllLayers(bool undone) {
    QSet<RLayer::Id> result;
    QHash<RObject::Id, QSharedPointer<RLayer> >::iterator it;
    for (it = layerMap.begin(); it != layerMap.end(); ++it) {
        QSharedPointer<RLayer> l = *it;
        if (!l.isNull() && (undone || !l->isUndone())) {
            result.insert(l->getId());
        }
    }
    return result;
}

QSet<RLayerState::Id> RMemoryStorage::queryAllLayerStates(bool undone) const {
    QSet<RLayerState::Id> result;
    QHash<RObject::Id, QSharedPointer<RLayerState> >::const_iterator it;
    for (it = layerStateMap.constBegin(); it != layerStateMap.constEnd(); ++it) {
        QSharedPointer<RLayerState> l = *it;
        if (!l.isNull() && (undone || !l->isUndone())) {
            result.insert(l->getId());
        }
    }
    return result;
}

QSet<RBlock::Id> RMemoryStorage::queryAllBlocks(bool undone) {
    QSet<RBlock::Id> result;
    QHash<RObject::Id, QSharedPointer<RBlock> >::iterator it;
    for (it = blockMap.begin(); it != blockMap.end(); ++it) {
        QSharedPointer<RBlock> b = *it;
        if (!b.isNull() && (undone || !b->isUndone())) {
            result.insert(b->getId());
        }
    }
    return result;
}

QSet<RBlock::Id> RMemoryStorage::queryAllLayoutBlocks(bool includeModelSpace, bool undone) const {
    QSet<RBlock::Id> result;
    QHash<RObject::Id, QSharedPointer<RBlock> >::const_iterator it;
    for (it = blockMap.constBegin(); it != blockMap.constEnd(); ++it) {
        QSharedPointer<RBlock> b = *it;
        if (!b.isNull() && (undone || !b->isUndone()) && b->hasLayout()) {
            if (includeModelSpace || !b->isModelSpace()) {
                result.insert(b->getId());
            }
        }
    }
    return result;
}

QSet<RBlock::Id> RMemoryStorage::queryAllLayouts(bool undone) {
    QSet<RLayout::Id> result;
    QHash<RObject::Id, QSharedPointer<RLayout> >::iterator it;
    for (it = layoutMap.begin(); it != layoutMap.end(); ++it) {
        QSharedPointer<RLayout> l = *it;
        if (!l.isNull() && (undone || !l->isUndone())) {
            result.insert(l->getId());
        }
    }
    return result;
}

QSet<RView::Id> RMemoryStorage::queryAllViews(bool undone) {
    QSet<RView::Id> result;
    QHash<RObject::Id, QSharedPointer<RObject> >::iterator it;
    for (it = objectMap.begin(); it != objectMap.end(); ++it) {
        QSharedPointer<RView> v = it->dynamicCast<RView>();
        if (!v.isNull() && (undone || !v->isUndone())) {
            result.insert(v->getId());
        }
    }
    return result;
}

QSet<RLinetype::Id> RMemoryStorage::queryAllLinetypes() {
    QSet<RLinetype::Id> result;
    QHash<RObject::Id, QSharedPointer<RLinetype> >::iterator it;
    for (it = linetypeMap.begin(); it != linetypeMap.end(); ++it) {
        QSharedPointer<RLinetype> l = *it;
        if (!l.isNull() && !l->isUndone()) {
            result.insert(l->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryInfiniteEntities() const {
    QSet<REntity::Id> result;

    if (!typeObjectMap.contains(RS::EntityXLine) && !typeObjectMap.contains(RS::EntityRay)) {
        return result;
    }

    RBlock::Id currentBlockId = getCurrentBlockId();
    const QHash<REntity::Id, QSharedPointer<REntity> >* map;
    if (blockEntityMap.contains(currentBlockId)) {
        map = &blockEntityMap[currentBlockId];
    }
    else {
        return result;
    }

    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = map->constBegin(); it != map->constEnd(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull()) {
            continue;
        }

        if (e->isUndone()) {
            continue;
        }

        if (e->getType()!=RS::EntityXLine && e->getType()!=RS::EntityRay) {
            continue;
        }

//        if (e->getBlockId() != currentBlockId) {
//            continue;
//        }

        result.insert(e->getId());
    }

    return result;
}

void RMemoryStorage::clearVisibleCache() {
    visibleEntityMap.clear();
    visibleEntityMapDirty = true;
}

void RMemoryStorage::updateVisibleCache() const {
    if (!visibleEntityMapDirty) {
        return;
    }

    visibleEntityMap.clear();

    RBlock::Id currentBlockId = getCurrentBlockId();
    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = entityMap.constBegin(); it != entityMap.constEnd(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone() /*&& isEntityVisible(*e)*/ &&
            e->getBlockId() == currentBlockId) {

            // this updates the cache:
            //isEntityVisible(*e);
            //selectedEntityMap.insert(e->getId(), e);

            if (RStorage::isEntityVisible(*e, currentBlockId)) {
                visibleEntityMap.insert(e->getId(), queryEntityDirect(e->getId()));
            }
        }
    }

    visibleEntityMapDirty = false;
}

void RMemoryStorage::clearSelectionCache() {
    selectedEntityMap.clear();
    selectedEntityMapDirty = true;

    selectedLayerMap.clear();
    selectedLayerMapDirty = true;
}

// TODO: rename map to cache
void RMemoryStorage::updateSelectedEntityMap() const {
    if (!selectedEntityMapDirty) {
        return;
    }

    selectedEntityMap.clear();

    RBlock::Id currentBlock = getCurrentBlockId();
    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = entityMap.constBegin(); it != entityMap.constEnd(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone() && e->isSelected() &&
            e->getBlockId() == currentBlock) {
            selectedEntityMap.insert(e->getId(), e);
        }
    }

    selectedEntityMapDirty = false;
}

QSet<REntity::Id> RMemoryStorage::querySelectedEntities() const {
    updateSelectedEntityMap();

    return selectedEntityMap.keys().toSet();
}

void RMemoryStorage::updateSelectedLayerMap() const {
    // TODO:
//    if (!selectedObjectMapDirty) {
//        return;
//    }

    selectedLayerMap.clear();

    // TODO: implement for other objects than layers:
    QHash<RLayer::Id, QSharedPointer<RLayer> >::const_iterator it;
    for (it = layerMap.constBegin(); it != layerMap.constEnd(); ++it) {
        QSharedPointer<RLayer> obj = *it;
        if (!obj.isNull() && !obj->isUndone() && obj->isSelected()) {
            selectedLayerMap.insert(obj->getId(), obj);
        }
    }

    selectedLayerMapDirty = false;
}

QSet<RObject::Id> RMemoryStorage::querySelectedLayers() const {
    updateSelectedLayerMap();

    return selectedLayerMap.keys().toSet();
}

QSet<REntity::Id> RMemoryStorage::queryLayerEntities(RLayer::Id layerId, bool allBlocks) {
    RBlock::Id currentBlock = getCurrentBlockId();
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && e->getLayerId() == layerId && !e->isUndone()
                && (allBlocks || e->getBlockId() == currentBlock)) {
            result.insert(e->getId());
        }
    }
    return result;
}

bool RMemoryStorage::hasBlockEntities(RBlock::Id blockId) const {
    if (!blockEntityMap.contains(blockId)) {
        return false;
    }

    QHash<REntity::Id, QSharedPointer<REntity> > candidates = blockEntityMap.value(blockId);
    QHash<REntity::Id, QSharedPointer<REntity> >::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); it++) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone()) {
            return true;
        }
    }
    return false;
}

QSet<REntity::Id> RMemoryStorage::queryBlockEntities(RBlock::Id blockId) {
    if (!blockEntityMap.contains(blockId)) {
        return QSet<REntity::Id>();
    }

    QSet<REntity::Id> result;
    QHash<REntity::Id, QSharedPointer<REntity> > candidates = blockEntityMap.value(blockId);
    QHash<REntity::Id, QSharedPointer<REntity> >::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); it++) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone()) {
            result.insert(e->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryLayerBlockEntities(RLayer::Id layerId, RBlock::Id blockId) {
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && e->getLayerId() == layerId && !e->isUndone() && e->getBlockId() == blockId) {
            result.insert(e->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryChildEntities(REntity::Id parentId, RS::EntityType type) {
    Q_UNUSED(type)

    if (!childMap.contains(parentId)) {
        return QSet<REntity::Id>();
    }

    QList<REntity::Id> childIds = childMap.values(parentId);
    return childIds.toSet();

    /*
    QSet<REntity::Id> result; // = queryBlockEntities(blockRef->getReferencedBlockId());
    if (parentId==REntity::INVALID_ID) {
        return result;
    }

    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull() || e->isUndone() || e->getParentId()!=parentId) {
            continue;
        }

        if (type==RS::EntityAll || type==e->getType()) {
            result.insert(e->getId());
        }
    }

    return result;
    */
}

bool RMemoryStorage::hasChildEntities(REntity::Id parentId) const {
    return childMap.contains(parentId);

    /*
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull() || e->isUndone() || e->getParentId()!=parentId) {
            continue;
        }

        return true;
    }

    return false;
    */
}

QSet<REntity::Id> RMemoryStorage::queryBlockReferences(RBlock::Id blockId) const {
    QSet<REntity::Id> result;

    if (!typeObjectMap.contains(RS::EntityBlockRef)) {
        return result;
    }

    const QHash<RObject::Id, QSharedPointer<RObject> >& map = typeObjectMap[RS::EntityBlockRef];
    QHash<RObject::Id, QSharedPointer<RObject> >::const_iterator it;
    for (it = map.constBegin(); it != map.constEnd(); ++it) {
        QSharedPointer<RBlockReferenceEntity> e = it->dynamicCast<RBlockReferenceEntity>();
        if (!e.isNull() && e->getReferencedBlockId() == blockId && !e->isUndone()) {
            result.insert(e->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryAllBlockReferences() const {
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = entityMap.constBegin(); it != entityMap.constEnd(); ++it) {
        QSharedPointer<RBlockReferenceEntity> e = it->dynamicCast<RBlockReferenceEntity>();
        if (!e.isNull() && !e->isUndone()) {
            result.insert(e->getId());
        }
    }
    return result;
}

/*
QSet<REntity::Id> RMemoryStorage::queryViewEntities(RView::Id viewId) {
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && e->getViewId() == viewId && !e->isUndone()) {
            result.insert(e->getId());
        }
    }
    return result;
}
*/

QSharedPointer<RDocumentVariables> RMemoryStorage::queryDocumentVariables() const {
    if (documentVariables.isNull()) {
        //qWarning() << "RMemoryStorage::queryDocumentVariables: document variables is NULL";
        return QSharedPointer<RDocumentVariables>();
    }
    return QSharedPointer<RDocumentVariables>(documentVariables->clone());
}

QSharedPointer<RDocumentVariables> RMemoryStorage::queryDocumentVariablesDirect() const {
    if (documentVariables.isNull()) {
        //qWarning() << "RMemoryStorage::queryDocumentVariablesDirect: document variables is NULL";
    }
    return documentVariables;
}

QSharedPointer<RObject> RMemoryStorage::queryObject(RObject::Id objectId) const {
    if (!objectMap.contains(objectId)) {
        return QSharedPointer<RObject> ();
    }
    if (!objectMap[objectId].isNull()) {
        return QSharedPointer<RObject>(objectMap[objectId]->clone());
    }
    return QSharedPointer<RObject>();
}

QSharedPointer<RObject> RMemoryStorage::queryObjectDirect(RObject::Id objectId) const {
    if (!objectMap.contains(objectId)) {
        return QSharedPointer<RObject>();
    }
    return objectMap[objectId];
}

QSharedPointer<RObject> RMemoryStorage::queryObjectByHandle(RObject::Handle objectHandle) const {
    if (!objectHandleMap.contains(objectHandle)) {
        return QSharedPointer<RObject> ();
    }
    if (!objectHandleMap[objectHandle].isNull()) {
        return QSharedPointer<RObject>(objectHandleMap[objectHandle]->clone());
    }
    return QSharedPointer<RObject>();

    /*
    QSharedPointer<RObject> ret;

    QHash<RObject::Id, QSharedPointer<RObject> >::const_iterator it;
    for (it=objectMap.constBegin(); it!=objectMap.constEnd(); it++) {
        QSharedPointer<RObject> obj = it.value();
        if (obj.isNull()) {
            continue;
        }
        if (obj->getHandle()==objectHandle) {
            ret = QSharedPointer<RObject>(obj->clone());
            break;
        }
    }

    return ret;
    */
}

QSharedPointer<RObject> RMemoryStorage::queryObjectByHandleDirect(RObject::Handle objectHandle) const {
    if (!objectHandleMap.contains(objectHandle)) {
        return QSharedPointer<RObject>();
    }
    return objectHandleMap[objectHandle];
}

QSharedPointer<REntity> RMemoryStorage::queryEntity(REntity::Id objectId) const {
    if (!entityMap.contains(objectId)) {
        return QSharedPointer<REntity> ();
    }
    if (!entityMap[objectId].isNull()) {
        return QSharedPointer<RObject>(entityMap[objectId]->clone()).dynamicCast<REntity>();
    }
    return QSharedPointer<REntity>();
}

QSharedPointer<REntity> RMemoryStorage::queryEntityDirect(REntity::Id objectId) const {
    if (!entityMap.contains(objectId)) {
        return QSharedPointer<REntity>();
    }
    return entityMap[objectId];
}

QSharedPointer<REntity> RMemoryStorage::queryVisibleEntityDirect(REntity::Id objectId) const {
    updateVisibleCache();
    if (!visibleEntityMap.contains(objectId)) {
        return QSharedPointer<REntity>();
    }
    return visibleEntityMap[objectId];
}

QSharedPointer<RLayer> RMemoryStorage::queryLayerDirect(RLayer::Id layerId) const {
    if (!layerMap.contains(layerId)) {
        return QSharedPointer<RLayer>();
    }
    return layerMap[layerId].dynamicCast<RLayer>();
}

QSharedPointer<RLayer> RMemoryStorage::queryLayer(RLayer::Id layerId) const {
    if (!layerMap.contains(layerId)) {
        return QSharedPointer<RLayer> ();
    }
    QSharedPointer<RLayer> layer = layerMap[layerId];
    if (layer.isNull()) {
        return QSharedPointer<RLayer> ();
    }
    //if (!layer.dynamicCast<RLayer>().isNull()) {
        return QSharedPointer<RLayer>(layer->clone());
    //}

//    qWarning() << "RMemoryStorage::queryLayer: should never be reached: " << layerId;
//    qWarning() << "RMemoryStorage::queryLayer: found object but not layer: " << *layerMap[layerId];
//    return QSharedPointer<RLayer>();
}

QSharedPointer<RLayer> RMemoryStorage::queryLayer(const QString& layerName) const {
    if (!layerNameMap.contains(layerName.toLower())) {
        return QSharedPointer<RLayer>();
    }
    QSharedPointer<RLayer> layer = layerNameMap[layerName.toLower()];
    if (layer.isNull()) {
        return QSharedPointer<RLayer> ();
    }
    if (layer->isUndone()) {
        return QSharedPointer<RLayer> ();
    }
    return QSharedPointer<RLayer>(layer->clone());
    //return layerNameMap[layerName.toLower()].dynamicCast<RLayer>();


//    QHash<RObject::Id, QSharedPointer<RLayer> >::const_iterator it;
//    for (it = layerMap.constBegin(); it != layerMap.constEnd(); ++it) {
//        QSharedPointer<RLayer> l = *it;
//        if (!l.isNull() && l->getName().compare(layerName, Qt::CaseInsensitive)==0 && !l->isUndone()) {
//            return QSharedPointer<RLayer> (l->clone());
//        }
//    }
//    return QSharedPointer<RLayer>();
}

QSharedPointer<RLayerState> RMemoryStorage::queryLayerStateDirect(RLayerState::Id layerStateId) const {
    if (!layerStateMap.contains(layerStateId)) {
        return QSharedPointer<RLayerState>();
    }
    return layerStateMap[layerStateId].dynamicCast<RLayerState>();
}

QSharedPointer<RLayerState> RMemoryStorage::queryLayerState(RLayerState::Id layerStateId) const {
    if (!layerStateMap.contains(layerStateId)) {
        return QSharedPointer<RLayerState> ();
    }
    if (layerStateMap[layerStateId].isNull()) {
        return QSharedPointer<RLayerState> ();
    }
    if (!layerStateMap[layerStateId].dynamicCast<RLayerState>().isNull()) {
        return QSharedPointer<RLayerState>((RLayerState*)layerStateMap[layerStateId]->clone());
    }

    qWarning() << "RMemoryStorage::queryLayerState: should never be reached: " << layerStateId;
    qWarning() << "RMemoryStorage::queryLayerState: found object but not layerState: " << *layerStateMap[layerStateId];
    return QSharedPointer<RLayerState>();
}

QSharedPointer<RLayerState> RMemoryStorage::queryLayerState(const QString& layerStateName) const {
    QHash<RObject::Id, QSharedPointer<RLayerState> >::const_iterator it;
    for (it = layerStateMap.constBegin(); it != layerStateMap.constEnd(); ++it) {
        QSharedPointer<RLayerState> l = *it;
        if (!l.isNull() && l->getName().compare(layerStateName, Qt::CaseInsensitive)==0 && !l->isUndone()) {
            return QSharedPointer<RLayerState> (l->clone());
        }
    }
    return QSharedPointer<RLayerState>();
}

QSharedPointer<RLayout> RMemoryStorage::queryLayoutDirect(RLayout::Id layoutId) const {
    if (!layoutMap.contains(layoutId)) {
        return QSharedPointer<RLayout>();
    }
    return layoutMap[layoutId].dynamicCast<RLayout>();
}

QSharedPointer<RLayout> RMemoryStorage::queryLayout(RLayout::Id layoutId) const {
    if (!layoutMap.contains(layoutId)) {
        return QSharedPointer<RLayout> ();
    }
    if (layoutMap[layoutId].isNull()) {
        return QSharedPointer<RLayout> ();
    }
    if (!layoutMap[layoutId].dynamicCast<RLayout>().isNull()) {
        return QSharedPointer<RLayout>((RLayout*)layoutMap[layoutId]->clone());
    }

    qWarning() << "RMemoryStorage::queryLayout: should never be reached: " << layoutId;
    qWarning() << "RMemoryStorage::queryLayout: found object but not layout: " << *layoutMap[layoutId];
    return QSharedPointer<RLayout>();
}

QSharedPointer<RLayout> RMemoryStorage::queryLayout(const QString& layoutName) const {
    QHash<RObject::Id, QSharedPointer<RLayout> >::const_iterator it;
    for (it = layoutMap.constBegin(); it != layoutMap.constEnd(); ++it) {
        QSharedPointer<RLayout> l = *it;
        if (!l.isNull() && l->getName().compare(layoutName, Qt::CaseInsensitive)==0 && !l->isUndone()) {
            return QSharedPointer<RLayout> (l->clone());
        }
    }
    return QSharedPointer<RLayout>();
}

QSharedPointer<RBlock> RMemoryStorage::queryBlock(RBlock::Id blockId) const {
    if (!blockMap.contains(blockId)) {
        return QSharedPointer<RBlock> ();
    }
    if (blockMap[blockId].isNull()) {
        return QSharedPointer<RBlock> ();
    }
    if (!blockMap[blockId].dynamicCast<RBlock>().isNull()) {
        return QSharedPointer<RBlock>((RBlock*)blockMap[blockId]->clone());
    }
    return QSharedPointer<RBlock>();
}

QSharedPointer<RBlock> RMemoryStorage::queryBlockDirect(RBlock::Id blockId) const {
    if (!blockMap.contains(blockId)) {
        return QSharedPointer<RBlock>();
    }
    return blockMap[blockId].dynamicCast<RBlock>();
}

void RMemoryStorage::setObjectHandle(RObject& object, RObject::Handle objectHandle) {
    if (objectHandleMap.contains(objectHandle)) {
        objectHandle = getNewObjectHandle();
    }
    Q_ASSERT(!objectHandleMap.contains(objectHandle));
    RStorage::setObjectHandle(object, objectHandle);
}

RObject::Handle RMemoryStorage::getNewObjectHandle() {
    RObject::Handle candidate = RStorage::getNewObjectHandle();
    while (objectHandleMap.contains(candidate)) {
        candidate++;
    }
    handleCounter = candidate;
    Q_ASSERT(!objectHandleMap.contains(candidate));
    return candidate;
}

QSharedPointer<RBlock> RMemoryStorage::queryBlock(const QString& blockName) const {
    QHash<RObject::Id, QSharedPointer<RBlock> >::const_iterator it;
    for (it = blockMap.constBegin(); it != blockMap.constEnd(); ++it) {
        QSharedPointer<RBlock> b = *it;
        if (!b.isNull() && b->getName().compare(blockName, Qt::CaseInsensitive)==0 && !b->isUndone()) {
            return QSharedPointer<RBlock> (b->clone());
        }
    }
    return QSharedPointer<RBlock>();
}

QSharedPointer<RBlock> RMemoryStorage::queryBlockDirect(const QString& blockName) const {
    QHash<RObject::Id, QSharedPointer<RBlock> >::const_iterator it;
    for (it = blockMap.constBegin(); it != blockMap.constEnd(); ++it) {
        QSharedPointer<RBlock> b = *it;
        if (!b.isNull() && b->getName().compare(blockName, Qt::CaseInsensitive)==0 && !b->isUndone()) {
            return b;
        }
    }
    return QSharedPointer<RBlock>();
}

QString RMemoryStorage::getBlockName(RBlock::Id blockId) const {
    QSharedPointer<RBlock> l = queryBlock(blockId);
    if (l.isNull()) {
        return QString();
    }
    return l->getName();
}

QString RMemoryStorage::getBlockNameFromLayout(const QString& layoutName) const {
    // look up layout:
    QSet<RBlock::Id> ids = queryAllLayoutBlocks();
    QSet<RBlock::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<RBlock> layoutBlock = queryBlockDirect(*it);
        if (QString::compare(layoutBlock->getLayoutName(), layoutName, Qt::CaseInsensitive)==0) {
            return layoutBlock->getName();
        }
    }
    return QString();
}

QString RMemoryStorage::getBlockNameFromLayout(RLayout::Id layoutId) const {
    // look up layout:
    QSet<RBlock::Id> ids = queryAllLayoutBlocks();
    QSet<RBlock::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<RBlock> layoutBlock = queryBlockDirect(*it);
        if (layoutBlock->getLayoutId()==layoutId) {
            return layoutBlock->getName();
        }
    }
    return QString();
}

QSet<QString> RMemoryStorage::getBlockNames(const QString& rxStr) const {
    QRegExp rx(rxStr);
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RBlock> >::const_iterator it;
    for (it = blockMap.constBegin(); it != blockMap.constEnd(); ++it) {
        QSharedPointer<RBlock> b = *it;
        if (!b.isNull() && !b->isUndone()) {
            if (rx.isEmpty() || rx.exactMatch(b->getName())) {
                ret.insert(b->getName());
            }
        }
    }
    return ret;
}

QString RMemoryStorage::getViewName(RView::Id viewId) const {
    QSharedPointer<RView> v = queryView(viewId);
    if (v.isNull()) {
        return QString();
    }
    return v->getName();
}

QSet<QString> RMemoryStorage::getViewNames() const {
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RObject> >::const_iterator it;
    for (it = objectMap.constBegin(); it != objectMap.constEnd(); ++it) {
        QSharedPointer<RView> v = it->dynamicCast<RView> ();
        if (!v.isNull() && !v->isUndone()) {
            ret.insert(v->getName());
        }
    }
    return ret;
}

QSharedPointer<RView> RMemoryStorage::queryView(RView::Id viewId) const {
    if (!objectMap.contains(viewId)) {
        return QSharedPointer<RView> ();
    }
    if (objectMap[viewId].isNull()) {
        return QSharedPointer<RView> ();
    }
    if (!objectMap[viewId].dynamicCast<RView>().isNull()) {
        return QSharedPointer<RView>((RView*)objectMap[viewId]->clone());
    }
    return QSharedPointer<RView>();
}

QSharedPointer<RView> RMemoryStorage::queryView(const QString& viewName) const {
    QHash<RObject::Id, QSharedPointer<RObject> >::const_iterator it;
    for (it = objectMap.constBegin(); it != objectMap.constEnd(); ++it) {
        QSharedPointer<RView> l = it->dynamicCast<RView>();
        if (!l.isNull() && l->getName() == viewName && !l->isUndone()) {
            return QSharedPointer<RView> (l->clone());
        }
    }
    return QSharedPointer<RView>();
}

QSharedPointer<RUcs> RMemoryStorage::queryUcsDirect(RUcs::Id ucsId) const {
    if (!objectMap.contains(ucsId)) {
        return QSharedPointer<RUcs>();
    }
    return objectMap[ucsId].dynamicCast<RUcs>();
}

QSharedPointer<RUcs> RMemoryStorage::queryUcs(RUcs::Id ucsId) const {
    if (!objectMap.contains(ucsId)) {
        return QSharedPointer<RUcs> ();
    }
    if (!objectMap[ucsId].dynamicCast<RUcs>().isNull()) {
        return QSharedPointer<RObject>(objectMap[ucsId]->clone()).dynamicCast<RUcs>();
    }
    return QSharedPointer<RUcs>();
}

QSharedPointer<RUcs> RMemoryStorage::queryUcs(const QString& ucsName) const {
    QHash<RObject::Id, QSharedPointer<RObject> >::const_iterator it;
    for (it = objectMap.constBegin(); it != objectMap.constEnd(); ++it) {
        QSharedPointer<RUcs> u = it->dynamicCast<RUcs>();
        if (!u.isNull() && u->name==ucsName) {
            return QSharedPointer<RUcs> (u->clone());
        }
    }

    return QSharedPointer<RUcs>();
}

QSharedPointer<RLinetype> RMemoryStorage::queryLinetypeDirect(RLinetype::Id linetypeId) const {
    if (!linetypeMap.contains(linetypeId)) {
        return QSharedPointer<RLinetype>();
    }
    return linetypeMap[linetypeId].dynamicCast<RLinetype>();
}

QSharedPointer<RLinetype> RMemoryStorage::queryLinetype(RLinetype::Id linetypeId) const {
    if (!linetypeMap.contains(linetypeId)) {
        return QSharedPointer<RLinetype> ();
    }
    if (linetypeMap[linetypeId].isNull()) {
        return QSharedPointer<RLinetype> ();
    }
    if (!linetypeMap[linetypeId].dynamicCast<RLinetype>().isNull()) {
        return QSharedPointer<RLinetype>(linetypeMap[linetypeId]->clone());
    }
    return QSharedPointer<RLinetype>();
}

QSharedPointer<RLinetype> RMemoryStorage::queryLinetype(const QString& linetypeName) const {
    QHash<RObject::Id, QSharedPointer<RLinetype> >::const_iterator it;
    for (it = linetypeMap.constBegin(); it != linetypeMap.constEnd(); ++it) {
        QSharedPointer<RLinetype> l = it->dynamicCast<RLinetype>();
        if (!l.isNull() && l->getName().compare(linetypeName, Qt::CaseInsensitive)==0) {
            return QSharedPointer<RLinetype> (l->clone());
        }
    }

    return QSharedPointer<RLinetype>();
}

void RMemoryStorage::selectAllEntities(QSet<REntity::Id>* affectedEntities) {
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    RBlock::Id currentBlock = getCurrentBlockId();
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isSelected() &&
            e->getBlockId()==currentBlock && e->isEditable()) {

            setEntitySelected(e, true, affectedEntities);
        }
    }
    clearSelectionCache();
}

int RMemoryStorage::countSelectedEntities() const {
    updateSelectedEntityMap();
    return selectedEntityMap.size();
}

void RMemoryStorage::clearEntitySelection(QSet<REntity::Id>* affectedEntities) {
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && (e->isSelected() || e->isSelectedWorkingSet())) {
            setEntitySelected(e, false, affectedEntities);
        }
    }
    clearSelectionCache();
}

void RMemoryStorage::selectEntity(REntity::Id entityId, bool add, 
    QSet<REntity::Id>* affectedEntities) {

    QSet<REntity::Id> set;
    set.insert(entityId);
    selectEntities(set, add, affectedEntities);
}

void RMemoryStorage::deselectEntity(REntity::Id entityId,
    QSet<REntity::Id>* affectedEntities) {

    QSet<REntity::Id> set;
    set.insert(entityId);
    deselectEntities(set, affectedEntities);
}

int RMemoryStorage::selectEntities(const QSet<REntity::Id>& entityIds,
        bool add, QSet<REntity::Id>* affectedEntities) {

    if (!add) {
        // deselect all first:
        QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
        for (it = entityMap.begin(); it != entityMap.end(); ++it) {
            QSharedPointer<REntity> e = *it;
            if (!e.isNull() && (e->isSelected() || e->isSelectedWorkingSet()) &&
                !entityIds.contains(e->getId())) {

                setEntitySelected(e, false, affectedEntities);
            }
        }
    }
    
    int ret = 0;

    QSet<REntity::Id>::const_iterator it;
    for (it = entityIds.constBegin(); it != entityIds.constEnd(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (!e.isNull() && !e->isSelected() && !e->isSelectedWorkingSet() &&
            !isLayerLocked(e->getLayerId()) && !isLayerOffOrFrozen(e->getLayerId())) {

            setEntitySelected(e, true, affectedEntities);
            ret++;
        }
    }

    return ret;
}

/**
 * Selects first the top most parent in the entity hierarchy and then
 * all children of it. This is necessary for attributes which are
 * children of block references.
 *
 * @todo Improve performance for selecting many block references
 */
void RMemoryStorage::setEntitySelected(QSharedPointer<REntity> entity, bool on,
    QSet<REntity::Id>* affectedEntities, bool onlyDescend) {

    // if user clicks block attribute, select block reference and attributes instead (acad compat)
    // otherwise attributes can be selected individually to edit their attributes
    if (RSettings::getSelectBlockWithAttribute()) {
        if (!onlyDescend && entity->getType()==RS::EntityAttribute) {
            REntity::Id parentId = entity->getParentId();
            if (parentId!=REntity::INVALID_ID) {
                // entity has a parent: select parent instead
                // (select block ref for attribute):
                QSharedPointer<REntity> parent = queryEntityDirect(parentId);
                if (!parent.isNull()) {
                    setEntitySelected(parent, on, affectedEntities);
                    return;
                }
            }
        }
    }

    entity->setSelected(on);
    if (affectedEntities!=NULL) {
        affectedEntities->insert(entity->getId());
    }
    clearSelectionCache();

    // if this is a parent, select all child entities (attributes for block ref):
    // only block references can have child entities (attributes):
    // TODO: improve performance for selecting block references (cache child ids):
    if (entity->getType()==RS::EntityBlockRef && hasChildEntities(entity->getId())) {
        QSet<REntity::Id> childIds = queryChildEntities(entity->getId());
        QSet<REntity::Id>::iterator it;
        for (it=childIds.begin(); it!=childIds.end(); it++) {
            REntity::Id childId = *it;
            QSharedPointer<REntity> child = queryEntityDirect(childId);
            if (child.isNull()) {
                continue;
            }
            setEntitySelected(child, on, affectedEntities, true);
        }
    }
}

int RMemoryStorage::deselectEntities(const QSet<REntity::Id>& entityIds, QSet<REntity::Id>* affectedEntities) {
    int ret = 0;
    QSet<REntity::Id>::const_iterator it;
    for (it = entityIds.constBegin(); it != entityIds.constEnd(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (!e.isNull() && e->isSelected()) {
            setEntitySelected(e, false, affectedEntities);
            ret++;
        }
    }
    return ret;
}

bool RMemoryStorage::hasSelection() const {
    updateSelectedEntityMap();

    return !selectedEntityMap.isEmpty();

//    RBlock::Id currentBlockId = getCurrentBlockId();
//    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
//    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
//        QSharedPointer<REntity> e = *it;
//        if (!e.isNull() && !e->isUndone() && e->isSelected() &&
//            e->getBlockId() == currentBlockId) {
//            return true;
//        }
//    }

//    return false;
}

RBox RMemoryStorage::getBoundingBox(bool ignoreHiddenLayers, bool ignoreEmpty) const {
    if (!boundingBoxDirty) {
        return boundingBox[ignoreHiddenLayers][ignoreEmpty];
    }

    RBlock::Id currentBlockId = getCurrentBlockId();
    //const QHash<REntity::Id, QSharedPointer<REntity> >* map;
    if (!blockEntityMap.contains(currentBlockId)) {
        return RBox();
        //QHash<REntity::Id, QSharedPointer<REntity> > m = blockEntityMap[currentBlockId];
        //map = &blockEntityMap.value(currentBlockId);
    }
    //else {
    //}

    boundingBox[0][0] = RBox();
    boundingBox[0][1] = RBox();
    boundingBox[1][0] = RBox();
    boundingBox[1][1] = RBox();
    maxLineweight = RLineweight::Weight000;

    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = blockEntityMap[currentBlockId].constBegin(); it != blockEntityMap[currentBlockId].constEnd(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull() || e->isUndone()) {
            continue;
        }

        bool visible = e->isVisible();
        //if (ignoreHiddenLayers) {
//        bool layerHidden = false;
//            QSharedPointer<RLayer> layer = queryLayerDirect(e->getLayerId());
//            if (layer.isNull() || layer->isOffOrFrozen()) {
//                layerHidden = true;
//            }
        //}

        //if (e->getBlockId() == currentBlockId) {
            //bb.growToInclude(e->getBoundingBox(ignoreEmpty));

            RBox bb = e->getBoundingBox(false);
            RBox bbIgnoreEmpty = e->getBoundingBox(true);

            if (!bb.isSane()) {
                continue;
            }

            boundingBox[0][0].growToInclude(bb);
            boundingBox[0][1].growToInclude(bbIgnoreEmpty);
            if (visible) {
                boundingBox[1][0].growToInclude(bb);
                boundingBox[1][1].growToInclude(bbIgnoreEmpty);
            }
        //}

        // don't resolve block references, if line weight is ByBlock,
        // the maxLinewidth will be adjusted when the block reference
        // is encountered:
        QStack<REntity*> blockRefStack;

        RLineweight::Lineweight lw = e->getLineweight(true, blockRefStack);
        maxLineweight = qMax(lw, maxLineweight);
    }

    boundingBoxDirty = false;

//    qDebug() << "\n\nbb: " << boundingBox[0][0];
//    qDebug() << "bb ignoreEmpty: " << boundingBox[0][1];
//    qDebug() << "bb ignoreHiddenLayers: " << boundingBox[1][0];
//    qDebug() << "bb ignoreHiddenLayers, ignoreEmpty: " << boundingBox[1][1];

    return boundingBox[(int)ignoreHiddenLayers][(int)ignoreEmpty];
}

RBox RMemoryStorage::getSelectionBox() const {
    updateSelectedEntityMap();

    RBox ret;
    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = selectedEntityMap.constBegin(); it != selectedEntityMap.constEnd(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull()) {
            ret.growToInclude(e->getBoundingBox());
        }
    }

    return ret;
}

RBox RMemoryStorage::getEntitiesBox(QSet<REntity::Id>& ids) const {
    RBox ret;
    QSet<REntity::Id>::const_iterator it;
    for (it = ids.constBegin(); it != ids.constEnd(); ++it) {
        REntity::Id id = *it;
        QSharedPointer<REntity> e = queryEntityDirect(id);
        if (!e.isNull()) {
            ret.growToInclude(e->getBoundingBox());
        }
    }
    return ret;
}

bool RMemoryStorage::removeObject(QSharedPointer<RObject> object) {
    if (object.isNull()) {
        return false;
    }

    bool ret = false;

    QSharedPointer<REntity> entity = object.dynamicCast<REntity> ();
    if (!entity.isNull()) {
        //blockEntityMap.remove(entity->getBlockId(), entity);
        blockEntityMap[entity->getBlockId()].remove(entity->getId());
        if (blockEntityMap[entity->getBlockId()].isEmpty()) {
            // no entities left for this block:
            blockEntityMap.remove(entity->getBlockId());
            //qDebug() << "blockEntityMap empty";
        }
        //qDebug() << "entities left for block:" << blockEntityMap[entity->getBlockId()].count();
        ret = true;
    }

    if (object->getType()==RS::ObjectLayer) {
        QSharedPointer<RLayer> layer = object.dynamicCast<RLayer>();
        if (!layer.isNull()) {
            layerNameMap.remove(layer->getName().toLower());
        }
        ret = true;
    }

    // update object type -> object ID -> object map:
    if (typeObjectMap.contains(object->getType())) {
        typeObjectMap[object->getType()].remove(object->getId());
        ret = true;
    }

//    qDebug() << "objectTypeMap ============================";
//    QHash<RS::EntityType, QHash<RObject::Id, QSharedPointer<RObject> > >::iterator it;
//    for (it=typeObjectMap.begin(); it!=typeObjectMap.end(); it++) {
//        qDebug() << "object type: " << it.key() << ":";
//        QHash<RObject::Id, QSharedPointer<RObject> >::iterator it2;
//        for (it2=it->begin(); it2!=it->end(); it2++) {
//            qDebug() << "\t" << it2.key() << " : " << it2.value();
//        }
//    }

//    if (object->getType()==RS::EntityBlockRef) {
//        QSharedPointer<RBlockReferenceEntity> blockRef = object.dynamicCast<RBlockReferenceEntity>();
//        if (!blockRef.isNull()) {
//            blockRefMap.remove(blockRef->getId());
//        }
//        return true;
//    }

    return ret;
}

bool RMemoryStorage::saveObject(QSharedPointer<RObject> object, bool checkBlockRecursion, bool keepHandles) {
    if (object.isNull()) {
        qWarning() << "RMemoryStorage::saveObject: object is NULL";
        return false;
    }

    QSharedPointer<RLayer> layer;
    QSharedPointer<RLayerState> layerState;
    QSharedPointer<RLayout> layout;
    QSharedPointer<RBlock> block;
    QSharedPointer<RLinetype> linetype;

    //qDebug() << "saveObject: " << *object;

    // never allow two layers with identical names, update layer instead:
    if (object->getType()==RS::ObjectLayer) {
        layer = object.dynamicCast<RLayer>();
        if (!layer.isNull()) {
            RLayer::Id id = getLayerId(layer->getName());
            if (id != RLayer::INVALID_ID && id != layer->getId()) {
                setObjectId(*layer, id);

                // never unprotect an existing protected layer:
                QSharedPointer<RLayer> existingLayer = queryLayerDirect(id);
                if (!existingLayer.isNull()) {
                    if (existingLayer->isProtected()) {
                        layer->setProtected(true);
                    }
                }
            }
        }
    }

    // never allow two layer states with identical names, update layer state instead:
    if (object->getType()==RS::ObjectLayerState) {
        layerState = object.dynamicCast<RLayerState>();
        if (!layerState.isNull()) {
            RLayerState::Id id = getLayerStateId(layerState->getName());
            if (id != RLayerState::INVALID_ID && id != layerState->getId()) {
                setObjectId(*layerState, id);

                // never unprotect an existing protected layerState:
                QSharedPointer<RLayerState> existingLayerState = queryLayerStateDirect(id);
                if (!existingLayerState.isNull()) {
                    if (existingLayerState->isProtected()) {
                        layerState->setProtected(true);
                    }
                }
            }
        }
    }

    // never allow two layouts with identical names, update layout instead:
    if (object->getType()==RS::ObjectLayout) {
        layout = object.dynamicCast<RLayout> ();
        if (!layout.isNull()) {
            RLayout::Id id = getLayoutId(layout->getName());
            if (id != RLayout::INVALID_ID && id != layout->getId()) {
                setObjectId(*layout, id);
            }
        }
    }

    // never allow two blocks with identical names, update block instead:
    if (object->getType()==RS::ObjectBlock) {
        block = object.dynamicCast<RBlock> ();
        if (!block.isNull()) {
            RBlock::Id id = getBlockId(block->getName());
            if (id != RBlock::INVALID_ID && id != block->getId()) {
                setObjectId(*block, id);
            }
        }
    }

    // never allow two linetypes with identical names, update linetype instead:
    if (object->getType()==RS::ObjectLinetype) {
        linetype = object.dynamicCast<RLinetype> ();
        if (!linetype.isNull()) {
            RLinetype::Id id = getLinetypeId(linetype->getName());
            if (id != RLinetype::INVALID_ID && id != linetype->getId()) {
                setObjectId(*linetype, id);
            }
        }
    }

    // avoid block recursions:
    if (checkBlockRecursion) {
        /*
        QSharedPointer<RBlockReferenceEntity> blockRef = object.dynamicCast<RBlockReferenceEntity> ();
        if (!blockRef.isNull()) {
            RBlock::Id id = blockRef->getBlockId();
            RBlock::Id refId = blockRef->getReferencedBlockId();
            // check if block with 'id' may contain a block reference which refers to
            // block with 'refid':
            // 201308: too slow for large, complex drawings:
            if (checkRecursion(id, refId)) {
                qCritical("RMemoryStorage::saveObject: recursion found");
                return false;
            }
        }
        */
    }

    QSharedPointer<REntity> entity = object.dynamicCast<REntity> ();
    if (!entity.isNull()) {
        Q_ASSERT_X(!queryLayerDirect(entity->getLayerId()).isNull(),
            "RMemoryStrorage::saveObject", "Layer of entity is NULL");
    }

    // assign new object ID to new objects:
    if (object->getId() == RObject::INVALID_ID) {
        setObjectId(*object, getNewObjectId());

        // only set new handle if handle is not set already:
        if (!keepHandles || object->getHandle()==RObject::INVALID_HANDLE) {
            setObjectHandle(*object, getNewObjectHandle());
        }

    }

    // assign draw order to new entities and
    // entities for which we want a new drawing order:
    if (!entity.isNull() && entity->getDrawOrder()==REntityData::getDefaultDrawOrder()) {
        entity->setDrawOrder(getMaxDrawOrder());
        setMaxDrawOrder(getMaxDrawOrder()+1);
    }

    // TODO: save original object for rollback:
    //if (inTransaction) {
        //transactionObjectMap[object->getId()] = object;
    //}

    if (object->getId()!=RObject::INVALID_ID) {
        objectMap[object->getId()] = object;
    }
    if (object->getHandle()!=RObject::INVALID_HANDLE) {
        objectHandleMap[object->getHandle()] = object;
    }

    if (!entity.isNull()) {
        entityMap[entity->getId()] = entity;

        //QHash<REntity::Id, QSharedPointer<REntity> > candidates = blockEntityMap.value(blockId);

        if (!blockEntityMap.contains(entity->getBlockId())) {
            blockEntityMap.insert(entity->getBlockId(), QHash<REntity::Id, QSharedPointer<REntity> >());
        }
        blockEntityMap[entity->getBlockId()].insert(entity->getId(), entity);
        //qDebug() << "blockEntityMap:" << blockEntityMap.count();
        //qDebug() << "blockEntityMap block:" << blockEntityMap[entity->getBlockId()].count();

        //blockEntityMap.insert(entity->getBlockId(), entity);

        setMaxDrawOrder(qMax(entity->getDrawOrder()+1, getMaxDrawOrder()));

        if (entity->getParentId()!=REntity::INVALID_ID) {
            childMap.insert(entity->getParentId(), entity->getId());
        }
    }

    if (!layer.isNull()) {
        layerMap[object->getId()] = layer;
        layerNameMap[layer->getName().toLower() ] = layer;
    }

    if (!layerState.isNull()) {
        layerStateMap[object->getId()] = layerState;
    }

    if (!layout.isNull()) {
        layoutMap[object->getId()] = layout;
    }

    if (!block.isNull()) {
        blockMap[object->getId()] = block;
    }

    if (!linetype.isNull()) {
        linetypeMap[object->getId()] = linetype;
    }

    // update object type -> object ID -> object map:
    if (!typeObjectMap.contains(object->getType())) {
        typeObjectMap.insert(object->getType(), QHash<RObject::Id, QSharedPointer<RObject> >());
    }
    typeObjectMap[object->getType()].insert(object->getId(), object);

//    qDebug() << "objectTypeMap ============================";
//    QHash<RS::EntityType, QHash<RObject::Id, QSharedPointer<RObject> > >::iterator it;
//    for (it=typeObjectMap.begin(); it!=typeObjectMap.end(); it++) {
//        qDebug() << "object type: " << it.key() << ":";
//        QHash<RObject::Id, QSharedPointer<RObject> >::iterator it2;
//        for (it2=it->begin(); it2!=it->end(); it2++) {
//            qDebug() << "\t" << it2.key() << " : " << it2.value();
//        }
//    }

    QSharedPointer<RDocumentVariables> docVars = object.dynamicCast<RDocumentVariables> ();
    if (!docVars.isNull()) {
        documentVariables = docVars;
    }

    // entity changed:
    // selection map might need an update:
    // TODO: check if selection status has changed
    if (!entity.isNull()) {
        clearSelectionCache();
    }

    // entity changed or added or deleted:
    // visible map might need an update:
    // TODO: check if layer visibility has changed:
    if (!entity.isNull()) {
        clearVisibleCache();
    }

    // layer changed:
    // visible map might need an update:
    // TODO: check if layer visibility has changed:
    if (!layer.isNull()) {
        clearVisibleCache();
    }

    // block changed:
    // visible map might need an update:
    // TODO: check if block visibility has changed:
    if (!block.isNull()) {
        clearVisibleCache();
    }

    return true;
}

/**
 * Checks recursively, if the given block is allowed to contain
 * references to the potential child block.
 *
 * \return true if a recusrion has been found.
 */
bool RMemoryStorage::checkRecursion(
    RBlock::Id blockId, RBlock::Id potentialChildBlockId) {

    if (blockId==potentialChildBlockId) {
        return true;
    }

    // iterate through all entities inside potential child block and check
    // if anything refers back to the given block:
    QSet<REntity::Id> ids = queryBlockEntities(potentialChildBlockId);
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        QSharedPointer<RBlockReferenceEntity> blockRef = e.dynamicCast<
                RBlockReferenceEntity> ();
        if (blockRef.isNull()) {
            continue;
        }

        if (blockRef->getReferencedBlockId() == blockId) {
            return true;
        }
        if (checkRecursion(blockId, blockRef->getReferencedBlockId())) {
            return true;
        }
    }
    return false;
}

bool RMemoryStorage::deleteObject(RObject::Id objectId) {
    // TODO: save original object for rollback:
    if (inTransaction) {
        //transactionObjectMap.insert(objectId, QSharedPointer<RObject>());
    }

    QSharedPointer<RObject> obj = queryObjectDirect(objectId);
    if (!obj.isNull()) {
        objectHandleMap.remove(obj->getHandle());

        QSharedPointer<REntity> entity = obj.dynamicCast<REntity>();
        if (!entity.isNull()) {
            //blockEntityMap.remove(entity->getBlockId(), entity);

            blockEntityMap[entity->getBlockId()].remove(entity->getId());
            if (blockEntityMap[entity->getBlockId()].isEmpty()) {
                // no entities left for this block:
                blockEntityMap.remove(entity->getBlockId());
                //qDebug() << "blockEntityMap empty";
            }
            //qDebug() << "entities left for block:" << blockEntityMap[entity->getBlockId()].count();

            //qDebug() << "deleteObject: removed " << entity->getId() << " from block " << entity->getBlockId();

            // remove entity from childMap values:
            if (entity->getParentId()!=REntity::INVALID_ID) {
                childMap.remove(entity->getParentId(), entity->getId());
            }
        }

        // remove layer from layer name map:
        QSharedPointer<RLayer> layer = obj.dynamicCast<RLayer>();
        if (!layer.isNull()) {
            QString layerKey = layer->getName().toLower();
            if (layerNameMap.contains(layerKey)) {
                layerNameMap.remove(layerKey);
            }
        }
    }

    objectMap.remove(objectId);
    if (entityMap.contains(objectId)) {
        entityMap.remove(objectId);
    }
    if (visibleEntityMap.contains(objectId)) {
        visibleEntityMap.remove(objectId);
    }
    if (blockMap.contains(objectId)) {
        blockMap.remove(objectId);
    }
    if (layoutMap.contains(objectId)) {
        layoutMap.remove(objectId);
    }
    if (layerMap.contains(objectId)) {
        layerMap.remove(objectId);
    }
    if (layerStateMap.contains(objectId)) {
        layerStateMap.remove(objectId);
    }
    if (linetypeMap.contains(objectId)) {
        linetypeMap.remove(objectId);
    }
    if (childMap.contains(objectId)) {
        childMap.remove(objectId);
    }

    clearSelectionCache();

    return true;
}

void RMemoryStorage::saveTransaction(RTransaction& transaction) {
    // if the given transaction is not undoable, we don't need to
    // store anything here:
    if (!transaction.isUndoable()) {
        return;
    }

    // assign new unique ID for this transaction:
    transaction.setId(getLastTransactionId() + 1);

    // delete transactions that are lost for good due to this transaction:
    //deleteTransactionsFrom(transaction.getId());

    transactionMap[transaction.getId()] = transaction;

    setLastTransactionId(transaction.getId());
}

void RMemoryStorage::deleteTransactionsFrom(int transactionId) {
    QSet<int> keysToRemove;

    {
        QHash<int, RTransaction>::iterator it;
        for (it = transactionMap.begin(); it!=transactionMap.end(); ++it) {
            if (it.key()>=transactionId) {
                // delete orphaned objects:
                QList<RObject::Id> affectedObjects =
                    it.value().getAffectedObjects();

                QList<RObject::Id>::iterator it2;
                for (it2=affectedObjects.begin(); it2!=affectedObjects.end(); ++it2) {
                    QSharedPointer<RObject> obj = queryObjectDirect(*it2);
                    if (!obj.isNull() && obj->isUndone()) {
                        deleteObject(*it2);
                    }
                }

                // mark transaction for removal:
                keysToRemove.insert(it.key());
            }
        }
    }

    {
        QSet<int>::iterator it;
        for (it=keysToRemove.begin(); it!=keysToRemove.end(); ++it) {
            transactionMap.remove(*it);
        }
    }

    if (!transactionMap.contains(getLastTransactionId())) {
        setLastTransactionId(getMaxTransactionId());
    }
}

RTransaction RMemoryStorage::getTransaction(int transactionId) {
    if (transactionMap.contains(transactionId)) {
        return transactionMap[transactionId];
    }
    else {
        qWarning("RMemoryStorage::getTransaction: transaction not found: %d", transactionId);
        return RTransaction(*this);
    }
}

void RMemoryStorage::resetTransactionStack() {
    transactionMap.clear();
    setLastTransactionId(-1);
}

void RMemoryStorage::toggleUndoStatus(QSet<RObject::Id>& objects) {
    QSet<RObject::Id>::iterator it;
    for (it=objects.begin(); it!=objects.end(); ++it) {
        toggleUndoStatus(*it);
    }
}

void RMemoryStorage::toggleUndoStatus(RObject::Id objectId) {
    QSharedPointer<RObject> object = queryObjectDirect(objectId);
    if (object.isNull()) {
        return;
    }
    setUndoStatus(*object, !object->isUndone());
}

bool RMemoryStorage::setUndoStatus(RObject::Id objectId, bool status) {
    QSharedPointer<RObject> object = queryObjectDirect(objectId);
    if (object.isNull()) {
        return false;
    }
    setUndoStatus(*object, status);
    return true;
}

void RMemoryStorage::setUndoStatus(RObject& object, bool status) {
    RStorage::setUndoStatus(object, status);

    // TODO: only add / remove object to / from cache:
    clearSelectionCache();
    clearVisibleCache();
}

//bool RMemoryStorage::getUndoStatus(RObject::Id objectId) const {
//    QSharedPointer<RObject> obj = queryObjectDirect(objectId);
//    if (obj.isNull()) {
//        qWarning() << QString("RMemoryStorage::getUndoStatus: object is NULL");
//        return false;
//    }
//    return obj->isUndone();
//}

int RMemoryStorage::getMaxTransactionId() {
    int ret = -1;

    QHash<int, RTransaction>::iterator it;
    for (it = transactionMap.begin(); it!=transactionMap.end(); ++it) {
        if (it.key()>ret) {
            ret = it.key();
        }
    }

    return ret;
}

QStringList RMemoryStorage::getVariables() const {
    return variables.keys();
}

void RMemoryStorage::setVariable(const QString& key, const QVariant& value, bool overwrite) {
    if (!overwrite && hasVariable(key)) {
        return;
    }

    if (variables.contains(key) && variables[key]==value) {
        // no change:
        return;
    }

    // remove existing variable with same name (case insensitive comparison):
    if (variableCaseMap.contains(key.toLower()) && variableCaseMap[key.toLower()]!=key) {
        variables.remove(variableCaseMap[key.toLower()]);
    }

    variableCaseMap[key.toLower()] = key;
    variables[key] = value;

    setModified(true);
}

void RMemoryStorage::removeVariable(const QString& key) {
    if (!variableCaseMap.contains(key.toLower())) {
        return;
    }

    variables.remove(variableCaseMap[key.toLower()]);
}

QVariant RMemoryStorage::getVariable(const QString& key) const {
    if (!variableCaseMap.contains(key.toLower())) {
        return QVariant();
    }

    return variables[variableCaseMap[key.toLower()]];
}

void RMemoryStorage::setKnownVariable(RS::KnownVariable key, const QVariant& value, RTransaction* transaction) {
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = startDocumentVariablesTransaction(transaction, useLocalTransaction);
    docVars->setKnownVariable(key, value);
    endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);

    // dimension settings might affect bounding box:
    boundingBoxDirty = true;
    setModified(true);
}

QVariant RMemoryStorage::getKnownVariable(RS::KnownVariable key) const {
    if (documentVariables.isNull()) {
        return QVariant();
    }

    return documentVariables->getKnownVariable(key);
}

QString RMemoryStorage::getLayerName(RLayer::Id layerId) const {
    QSharedPointer<RLayer> l = queryLayerDirect(layerId);
    if (l.isNull()) {
        return QString();
    }
    return l->getName();
}

QSet<QString> RMemoryStorage::getLayerNames(const QString& rxStr) const {
    QRegExp rx(rxStr);
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RLayer> >::const_iterator it;
    for (it = layerMap.constBegin(); it != layerMap.constEnd(); ++it) {
        QSharedPointer<RLayer> l = *it;
        if (!l.isNull() && !l->isUndone()) {
            if (rx.isEmpty() || rx.exactMatch(l->getName())) {
                ret.insert(l->getName());
            }
        }
    }
    return ret;
}

RLayer::Id RMemoryStorage::getLayerId(const QString& layerName) const {
    QSharedPointer<RLayer> l = queryLayer(layerName);
    if (l.isNull()) {
        return RLayer::INVALID_ID;
    }
    return l->getId();
}

QString RMemoryStorage::getLayerStateName(RLayerState::Id layerStateId) const {
    QSharedPointer<RLayerState> l = queryLayerStateDirect(layerStateId);
    if (l.isNull()) {
        return QString();
    }
    return l->getName();
}

QSet<QString> RMemoryStorage::getLayerStateNames(const QString& rxStr) const {
    QRegExp rx(rxStr);
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RLayerState> >::const_iterator it;
    for (it = layerStateMap.constBegin(); it != layerStateMap.constEnd(); ++it) {
        QSharedPointer<RLayerState> l = *it;
        if (!l.isNull() && !l->isUndone()) {
            if (rx.isEmpty() || rx.exactMatch(l->getName())) {
                ret.insert(l->getName());
            }
        }
    }
    return ret;
}

RLayerState::Id RMemoryStorage::getLayerStateId(const QString& layerStateName) const {
    QSharedPointer<RLayerState> l = queryLayerState(layerStateName);
    if (l.isNull()) {
        return RLayerState::INVALID_ID;
    }
    return l->getId();
}

QString RMemoryStorage::getLayoutName(RLayout::Id layoutId) const {
    QSharedPointer<RLayout> l = queryLayout(layoutId);
    if (l.isNull()) {
        return QString();
    }
    return l->getName();
}

QSet<QString> RMemoryStorage::getLayoutNames(const QString& rxStr) const {
    QRegExp rx(rxStr);
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RLayout> >::const_iterator it;
    for (it = layoutMap.constBegin(); it != layoutMap.constEnd(); ++it) {
        QSharedPointer<RLayout> l = *it;
        if (!l.isNull() && !l->isUndone()) {
            if (rx.isEmpty() || rx.exactMatch(l->getName())) {
                ret.insert(l->getName());
            }
        }
    }
    return ret;
}

RLayout::Id RMemoryStorage::getLayoutId(const QString& layoutName) const {
    QSharedPointer<RLayout> l = queryLayout(layoutName);
    if (l.isNull()) {
        return RLayout::INVALID_ID;
    }
    return l->getId();
}

RBlock::Id RMemoryStorage::getBlockId(const QString& blockName) const {
    QSharedPointer<RBlock> b = queryBlock(blockName);
    if (b.isNull()) {
        return RBlock::INVALID_ID;
    }
    return b->getId();
}

RBlock::Id RMemoryStorage::getBlockIdAuto(const QString& blockLayoutName) const {
    if (hasBlock(blockLayoutName)) {
        return getBlockId(blockLayoutName);
    }
    else {
        // look up layout instead:
        QSet<RBlock::Id> ids = queryAllLayoutBlocks();
        QSet<RBlock::Id>::iterator it;
        for (it = ids.begin(); it != ids.end(); it++) {
            QSharedPointer<RBlock> layoutBlock = queryBlockDirect(*it);
            if (QString::compare(layoutBlock->getName(), blockLayoutName, Qt::CaseInsensitive)==0) {
                return *it;
            }
        }
    }

    return RBlock::INVALID_ID;
}

RView::Id RMemoryStorage::getViewId(const QString& viewName) const {
    QSharedPointer<RView> v = queryView(viewName);
    if (v.isNull()) {
        return RView::INVALID_ID;
    }
    return v->getId();
}

QString RMemoryStorage::getLinetypeName(RLinetype::Id linetypeId) const {
    QSharedPointer<RLinetype> l = queryLinetypeDirect(linetypeId);
    if (l.isNull()) {
        return QString();
    }
    return l->getName();
}

QString RMemoryStorage::getLinetypeDescription(RLinetype::Id linetypeId) const {
    QSharedPointer<RLinetype> l = queryLinetypeDirect(linetypeId);
    if (l.isNull()) {
        return QString();
    }
    return l->getDescription();
}

QString RMemoryStorage::getLinetypeLabel(RLinetype::Id linetypeId) const {
    QSharedPointer<RLinetype> l = queryLinetypeDirect(linetypeId);
    if (l.isNull()) {
        return QString();
    }
    return l->getLabel();
}

QSet<QString> RMemoryStorage::getLinetypeNames() const {
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RLinetype> >::const_iterator it;
    for (it = linetypeMap.constBegin(); it != linetypeMap.constEnd(); ++it) {
        QSharedPointer<RLinetype> l = *it;
        if (!l.isNull() && !l->isUndone()) {
            ret.insert(l->getName());
        }
    }
    return ret;
}

QList<RLinetypePattern> RMemoryStorage::getLinetypePatterns() const {
    QList<RLinetypePattern> ret;
    QHash<RObject::Id, QSharedPointer<RLinetype> >::const_iterator it;
    for (it = linetypeMap.constBegin(); it != linetypeMap.constEnd(); ++it) {
        QSharedPointer<RLinetype> l = *it;
        if (!l.isNull() && !l->isUndone()) {
            ret.append(l->getPattern());
        }
    }
    return ret;
}

RLinetype::Id RMemoryStorage::getLinetypeId(const QString& linetypeName) const {
    QSharedPointer<RLinetype> l = queryLinetype(linetypeName);
    if (l.isNull()) {
        return RLinetype::INVALID_ID;
    }
    return l->getId();
}

void RMemoryStorage::setLastTransactionId(int transactionId) {
    RStorage::setLastTransactionId(transactionId);
    boundingBoxDirty = true;
}

RLineweight::Lineweight RMemoryStorage::getMaxLineweight() const {
    return maxLineweight;
}

void RMemoryStorage::update() {
    boundingBoxDirty = true;
}

void RMemoryStorage::setEntityParentId(REntity& entity, REntity::Id parentId) {
    RStorage::setEntityParentId(entity, parentId);

    if (entity.getId()==REntity::INVALID_ID || parentId==REntity::INVALID_ID) {
        return;
    }

    // remove links of old parents to this entity:
    QList<REntity::Id> pIds = childMap.keys();
    for (int i=0; i<pIds.length(); i++) {
        REntity::Id pId = pIds[i];
        if (childMap.contains(pId, entity.getId())) {
            childMap.remove(pId, entity.getId());
        }
    }

    // new parent / child link:
    childMap.insert(parentId, entity.getId());
}

//void RMemoryStorage::setUnit(RS::Unit unit, RTransaction* transaction) {
//    this->unit = unit;
//    setModified(true);
//}

//RS::Unit RMemoryStorage::getUnit() const {
//    return unit;
//}

//void RMemoryStorage::setDimensionFont(const QString& f) {
//    this->dimensionFont = f;
//    setModified(true);
//}

//QString RMemoryStorage::getDimensionFont() const {
//    return dimensionFont;
//}

//void RMemoryStorage::setLinetypeScale(double v) {
//    linetypeScale = v;
//    setModified(true);
//}

//double RMemoryStorage::getLinetypeScale() const {
//    return linetypeScale;
//}

