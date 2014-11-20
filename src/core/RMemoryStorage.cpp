/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
    boundingBoxChanged(true),
    //boundingBoxIgnoreHiddenLayers(false),
    //boundingBoxIgnoreEmpty(false),
    inTransaction(false) {

    setLastTransactionId(-1);
}

RMemoryStorage::~RMemoryStorage() {
}

void RMemoryStorage::clear() {
    RStorage::clear();

    maxLineweight = RLineweight::Weight000;
    inTransaction = false;
    boundingBoxChanged = true;
    boundingBox[0][0] = RBox();
    boundingBox[0][1] = RBox();
    boundingBox[1][0] = RBox();
    boundingBox[1][1] = RBox();
    objectMap.clear();
    objectHandleMap.clear();
    entityMap.clear();
    blockEntityMap.clear();
    blockMap.clear();
    layerMap.clear();
    linetypeMap.clear();
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
    boundingBoxChanged = true;
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
    boundingBoxChanged = true;

    setModified(true);
}

void RMemoryStorage::rollbackTransaction() {
    // drop transaction objects:
    //transactionObjectMap.clear();
    //Q_ASSERT(false);
}

QSet<RObject::Id> RMemoryStorage::queryAllObjects() {
    //result = QSet<RObject::Id>::fromList(objectMap.keys());
    QSet<RObject::Id> result;
    QHash<RObject::Id, QSharedPointer<RObject> >::iterator it;
    for (it = objectMap.begin(); it != objectMap.end(); ++it) {
        if (!(*it).isNull() && !(*it)->isUndone()) {
            result.insert((*it)->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryAllEntities(bool undone, bool allBlocks, RS::EntityType type) {
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
        if (type!=RS::EntityAll && e->getType()!=type) {
            continue;
        }
//        if (!includeFrozenLayers) {
//            RLayer::Id layerId = e->getLayerId();
//            QSharedPointer<RLayer> layer = queryLayer(layerId);
//            if (!layer.isNull()) {
//                if (layer->isFrozen()) {
//                    continue;
//                }
//            }
//        }
//        if (!e.isNull() && (undone || !e->isUndone()) && (allBlocks
//                || e->getBlockId() == currentBlock)) {
//            result.insert(e->getId());
//        }
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

QSet<REntity::Id> RMemoryStorage::queryInfiniteEntities() {
    RBlock::Id currentBlock = getCurrentBlockId();
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone() &&
            (e->getType()==RS::EntityXLine || e->getType()==RS::EntityRay) &&
            e->getBlockId() == currentBlock) {

            result.insert(e->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::querySelectedEntities() {
    RBlock::Id currentBlock = getCurrentBlockId();
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone() && e->isSelected() &&
            e->getBlockId() == currentBlock) {
            result.insert(e->getId());
        }
    }
    return result;
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

QSet<REntity::Id> RMemoryStorage::queryBlockEntities(RBlock::Id blockId) {
    if (!blockEntityMap.contains(blockId)) {
        return QSet<REntity::Id>();
    }

    QSet<REntity::Id> result;
    QList<QSharedPointer<REntity> > candidates = blockEntityMap.values(blockId);
    QList<QSharedPointer<REntity> >::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); it++) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone()) {
            result.insert(e->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryChildEntities(REntity::Id parentId, RS::EntityType type) {
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
}

bool RMemoryStorage::hasChildEntities(REntity::Id parentId) {
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull() || e->isUndone() || e->getParentId()!=parentId) {
            continue;
        }

        return true;
    }

    return false;
}

QSet<REntity::Id> RMemoryStorage::queryBlockReferences(RBlock::Id blockId) {
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<RBlockReferenceEntity> e = it->dynamicCast<RBlockReferenceEntity>();
        if (!e.isNull() && e->getReferencedBlockId() == blockId && !e->isUndone()) {
            result.insert(e->getId());
        }
    }
    return result;
}

QSet<REntity::Id> RMemoryStorage::queryAllBlockReferences() {
    QSet<REntity::Id> result;
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
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
    if (layerMap[layerId].isNull()) {
        return QSharedPointer<RLayer> ();
    }
    if (!layerMap[layerId].dynamicCast<RLayer>().isNull()) {
        return QSharedPointer<RLayer>((RLayer*)layerMap[layerId]->clone());
    }

    qWarning() << "RMemoryStorage::queryLayer: should never be reached: " << layerId;
    qWarning() << "RMemoryStorage::queryLayer: found object but not layer: " << *layerMap[layerId];
    return QSharedPointer<RLayer>();
}

QSharedPointer<RLayer> RMemoryStorage::queryLayer(const QString& layerName) const {
    QHash<RObject::Id, QSharedPointer<RLayer> >::const_iterator it;
    for (it = layerMap.constBegin(); it != layerMap.constEnd(); ++it) {
        QSharedPointer<RLayer> l = *it;
        if (!l.isNull() && l->getName().compare(layerName, Qt::CaseInsensitive)==0 && !l->isUndone()) {
            return QSharedPointer<RLayer> (l->clone());
        }
    }
    return QSharedPointer<RLayer>();
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

QString RMemoryStorage::getBlockName(RBlock::Id blockId) const {
    QSharedPointer<RBlock> l = queryBlock(blockId);
    if (l.isNull()) {
        return QString();
    }
    return l->getName();
}

QSet<QString> RMemoryStorage::getBlockNames() const {
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RBlock> >::const_iterator it;
    for (it = blockMap.constBegin(); it != blockMap.constEnd(); ++it) {
        QSharedPointer<RBlock> b = *it;
        if (!b.isNull() && !b->isUndone()) {
            ret.insert(b->getName());
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
            return u;
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
            return l;
        }
    }

    return QSharedPointer<RLinetype>();
}

void RMemoryStorage::selectAllEntites(QSet<REntity::Id>* affectedEntities) {
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    RBlock::Id currentBlock = getCurrentBlockId();
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isSelected() &&
            e->getBlockId()==currentBlock && e->isEditable()) {

            setEntitySelected(e, true, affectedEntities);
        }
    }
}

void RMemoryStorage::clearEntitySelection(QSet<REntity::Id>* affectedEntities) {
    QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && e->isSelected()) {
//            if (affectedEntities!=NULL) {
//                affectedEntities->insert(e->getId());
//            }
//            e->setSelected(false);
            setEntitySelected(e, false, affectedEntities);
        }
    }
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

void RMemoryStorage::selectEntities(const QSet<REntity::Id>& entityIds,
        bool add, QSet<REntity::Id>* affectedEntities) {

    if (!add) {
        // deselect all first:
        QHash<RObject::Id, QSharedPointer<REntity> >::iterator it;
        for (it = entityMap.begin(); it != entityMap.end(); ++it) {
            QSharedPointer<REntity> e = *it;
            if (!e.isNull() && e->isSelected() &&
                !entityIds.contains(e->getId())) {

                setEntitySelected(e, false, affectedEntities);
            }
        }
    }
    
    QSet<REntity::Id>::const_iterator it;
    for (it = entityIds.constBegin(); it != entityIds.constEnd(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (!e.isNull() && !e->isSelected() &&
            !isLayerLocked(e->getLayerId()) && !isLayerFrozen(e->getLayerId())) {

            setEntitySelected(e, true, affectedEntities);
        }
    }
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

    Q_UNUSED(onlyDescend)

//    disabled:
//    attributes can be selected individually to edit their attributes
//    if (!onlyDescend) {
//        // entity has a parent: select parent instead
//        // (select block ref for attribute):
//        REntity::Id parentId = entity->getParentId();
//        QSharedPointer<REntity> parent = queryEntityDirect(parentId);
//        if (!parent.isNull()) {
//            setEntitySelected(parent, on, affectedEntities);
//            return;
//        }
//    }

    entity->setSelected(on);
    if (affectedEntities!=NULL) {
        affectedEntities->insert(entity->getId());
    }

    // if this is a parent, select all child entities (attributes for block ref):
    // only block references can have child entities (attributes):
    if (entity->getType()!=RS::EntityBlockRef) {
        return;
    }

    // TODO: improve performance for selecting block references (cache child ids):
    if (hasChildEntities(entity->getId())) {
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

void RMemoryStorage::deselectEntities(const QSet<REntity::Id>& entityIds,
        QSet<REntity::Id>* affectedEntities) {

    QSet<REntity::Id>::const_iterator it;
    for (it = entityIds.constBegin(); it != entityIds.constEnd(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (!e.isNull() && e->isSelected()) {
            setEntitySelected(e, false, affectedEntities);
        }
    }
}

bool RMemoryStorage::hasSelection() const {
    RBlock::Id currentBlock = getCurrentBlockId();
    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone() && e->isSelected() &&
            e->getBlockId() == currentBlock) {
            return true;
        }
    }

    return false;
}

RBox RMemoryStorage::getBoundingBox(bool ignoreHiddenLayers, bool ignoreEmpty) const {
    if (!boundingBoxChanged) {
        return boundingBox[ignoreHiddenLayers][ignoreEmpty];
    }

    RBlock::Id currentBlockId = getCurrentBlockId();
    boundingBox[0][0] = RBox();
    boundingBox[0][1] = RBox();
    boundingBox[1][0] = RBox();
    boundingBox[1][1] = RBox();
    maxLineweight = RLineweight::Weight000;

    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = entityMap.constBegin(); it != entityMap.constEnd(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (e.isNull() || e->isUndone()) {
            continue;
        }

        //if (ignoreHiddenLayers) {
        bool layerHidden = false;
            QSharedPointer<RLayer> layer = queryLayerDirect(e->getLayerId());
            if (layer.isNull() || layer->isFrozen()) {
                layerHidden = true;
            }
        //}

        if (e->getBlockId() == currentBlockId) {
            //bb.growToInclude(e->getBoundingBox(ignoreEmpty));

            RBox bb = e->getBoundingBox(false);
            RBox bbIgnoreEmpty = e->getBoundingBox(true);

            boundingBox[0][0].growToInclude(bb);
            boundingBox[0][1].growToInclude(bbIgnoreEmpty);
            if (!layerHidden) {
                boundingBox[1][0].growToInclude(bb);
                boundingBox[1][1].growToInclude(bbIgnoreEmpty);
            }
        }

        // don't resolve block references, if line weight is ByBlock,
        // the maxLinewidth will be adjusted when the block reference
        // is encountered:
        QStack<REntity*> blockRefStack;

        RLineweight::Lineweight lw = e->getLineweight(true, blockRefStack);
        maxLineweight = qMax(lw, maxLineweight);
    }

    boundingBoxChanged = false;

//    qDebug() << "\n\nbb: " << boundingBox[0][0];
//    qDebug() << "bb ignoreEmpty: " << boundingBox[0][1];
//    qDebug() << "bb ignoreHiddenLayers: " << boundingBox[1][0];
//    qDebug() << "bb ignoreHiddenLayers, ignoreEmpty: " << boundingBox[1][1];

    return boundingBox[ignoreHiddenLayers][ignoreEmpty];
}

RBox RMemoryStorage::getSelectionBox() const {
    RBlock::Id currentBlock = getCurrentBlockId();
    RBox ret;
    QHash<RObject::Id, QSharedPointer<REntity> >::const_iterator it;
    for (it = entityMap.constBegin(); it != entityMap.constEnd(); ++it) {
        QSharedPointer<REntity> e = *it;
        if (!e.isNull() && !e->isUndone() && e->isSelected() &&
                e->getBlockId() == currentBlock) {

            ret.growToInclude(e->getBoundingBox());
        }
    }

    return ret;
}

bool RMemoryStorage::removeObject(QSharedPointer<RObject> object) {
    if (object.isNull()) {
        return false;
    }

    QSharedPointer<REntity> entity = object.dynamicCast<REntity> ();
    if (!entity.isNull()) {
        blockEntityMap.remove(entity->getBlockId(), entity);
        return true;
    }

    return false;
}

bool RMemoryStorage::saveObject(QSharedPointer<RObject> object, bool checkBlockRecursion, bool keepHandles) {
    if (object.isNull()) {
        qWarning() << "RMemoryStorage::saveObject: object is NULL";
        return false;
    }

    //qDebug() << "saveObject: " << *object;

    // never allow two layers with identical names, update layer instead:
    QSharedPointer<RLayer> layer = object.dynamicCast<RLayer>();
    if (!layer.isNull()) {
        RLayer::Id id = getLayerId(layer->getName());
        if (id != RLayer::INVALID_ID) {
            setObjectId(*layer, id);
        }
    }

    // never allow two blocks with identical names, update block instead:
    QSharedPointer<RBlock> block = object.dynamicCast<RBlock> ();
    if (!block.isNull()) {
        RBlock::Id id = getBlockId(block->getName());
        if (id != RBlock::INVALID_ID) {
            setObjectId(*block, id);
        }
    }

    // never allow two linetypes with identical names, update linetype instead:
    QSharedPointer<RLinetype> linetype = object.dynamicCast<RLinetype> ();
    if (!linetype.isNull()) {
        RLinetype::Id id = getLinetypeId(linetype->getName());
        if (id != RLinetype::INVALID_ID) {
            setObjectId(*linetype, id);
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

        // assign draw order to new entities:
        if (!entity.isNull()) {
            entity->setDrawOrder(getMaxDrawOrder());
            setMaxDrawOrder(getMaxDrawOrder()+1);
        }
    }

    // TODO: save original object for rollback:
    //if (inTransaction) {
        //transactionObjectMap[object->getId()] = object;
    //}

    objectMap[object->getId()] = object;
    objectHandleMap[object->getHandle()] = object;

    if (!entity.isNull()) {
        entityMap[entity->getId()] = entity;
        blockEntityMap.insert(entity->getBlockId(), entity);
        setMaxDrawOrder(qMax(entity->getDrawOrder()+1, getMaxDrawOrder()));
    }

    if (!layer.isNull()) {
        layerMap[object->getId()] = layer;
    }

    if (!block.isNull()) {
        blockMap[object->getId()] = block;
    }

    if (!linetype.isNull()) {
        linetypeMap[object->getId()] = linetype;
    }

    QSharedPointer<RDocumentVariables> docVars = object.dynamicCast<RDocumentVariables> ();
    if (!docVars.isNull()) {
        documentVariables = docVars;
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
            blockEntityMap.remove(entity->getBlockId(), entity);
            //qDebug() << "deleteObject: removed " << entity->getId() << " from block " << entity->getBlockId();
        }
    }

    objectMap.remove(objectId);
    if (entityMap.contains(objectId)) {
        entityMap.remove(objectId);
    }
    if (blockMap.contains(objectId)) {
        blockMap.remove(objectId);
    }
    if (layerMap.contains(objectId)) {
        layerMap.remove(objectId);
    }

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

                // delete transaction:
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
    QSharedPointer<RObject> obj = queryObjectDirect(objectId);
    if (!obj.isNull()) {
        obj->setUndone(!obj->isUndone());
    }
}

bool RMemoryStorage::setUndoStatus(RObject::Id objectId, bool status) {
    QSharedPointer<RObject> obj = queryObjectDirect(objectId);
    if (obj.isNull()) {
        qWarning() << QString("RMemoryStorage::setUndoStatus: object is NULL");
        return false;
    }
    obj->setUndone(status);
    return true;
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
    boundingBoxChanged = true;
    setModified(true);
}

QVariant RMemoryStorage::getKnownVariable(RS::KnownVariable key) const {
    if (documentVariables.isNull()) {
        return QVariant();
    }

    return documentVariables->getKnownVariable(key);
}

QString RMemoryStorage::getLayerName(RLayer::Id layerId) const {
    QSharedPointer<RLayer> l = queryLayer(layerId);
    if (l.isNull()) {
        return QString();
    }
    return l->getName();
}

QSet<QString> RMemoryStorage::getLayerNames() const {
    QSet<QString> ret;
    QHash<RObject::Id, QSharedPointer<RLayer> >::const_iterator it;
    for (it = layerMap.constBegin(); it != layerMap.constEnd(); ++it) {
        QSharedPointer<RLayer> l = *it;
        if (!l.isNull() && !l->isUndone()) {
            ret.insert(l->getName());
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

RBlock::Id RMemoryStorage::getBlockId(const QString& blockName) const {
    QSharedPointer<RBlock> b = queryBlock(blockName);
    if (b.isNull()) {
        return RBlock::INVALID_ID;
    }
    return b->getId();
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
    boundingBoxChanged = true;
}

RLineweight::Lineweight RMemoryStorage::getMaxLineweight() const {
    return maxLineweight;
}

void RMemoryStorage::update() {
    boundingBoxChanged = true;
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

