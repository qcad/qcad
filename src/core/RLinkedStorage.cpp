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
#include "RLinkedStorage.h"

RLinkedStorage::RLinkedStorage(RStorage& backStorage) :
    RMemoryStorage(),
    backStorage(&backStorage),
    objectIdOffset(1) {
}

RLinkedStorage::~RLinkedStorage() {
}

QSet<RObject::Id> RLinkedStorage::queryAllObjects() {
    return RMemoryStorage::queryAllObjects()
            .unite(backStorage->queryAllObjects());
}

QSet<REntity::Id> RLinkedStorage::queryAllEntities(bool undone, bool allBlocks) {
    return RMemoryStorage::queryAllEntities(undone, allBlocks)
            .unite(backStorage->queryAllEntities(undone, allBlocks));
}

QSet<RUcs::Id> RLinkedStorage::queryAllUcs() {
    return RMemoryStorage::queryAllUcs()
            .unite(backStorage->queryAllUcs());
}

QSet<RLayer::Id> RLinkedStorage::queryAllLayers(bool undone) {
    return RMemoryStorage::queryAllLayers(undone)
            .unite(backStorage->queryAllLayers(undone));
}

QSet<RBlock::Id> RLinkedStorage::queryAllBlocks(bool undone) {
    return RMemoryStorage::queryAllBlocks(undone)
            .unite(backStorage->queryAllBlocks(undone));
}

QSet<RView::Id> RLinkedStorage::queryAllViews(bool undone) {
    return RMemoryStorage::queryAllViews(undone)
            .unite(backStorage->queryAllViews(undone));
}

QSet<RLinetype::Id> RLinkedStorage::queryAllLinetypes() {
    return RMemoryStorage::queryAllLinetypes()
            .unite(backStorage->queryAllLinetypes());
}

QSet<REntity::Id> RLinkedStorage::querySelectedEntities() {
    return RMemoryStorage::querySelectedEntities()
            .unite(backStorage->querySelectedEntities());
}

QSet<REntity::Id> RLinkedStorage::queryLayerEntities(RLayer::Id layerId, bool allBlocks) {
    return RMemoryStorage::queryLayerEntities(layerId, allBlocks)
            .unite(backStorage->queryLayerEntities(layerId, allBlocks));
}

QSet<REntity::Id> RLinkedStorage::queryBlockEntities(RBlock::Id blockId) {
    if (objectMap.contains(blockId)) {
        // got block, return only block entities from this block:
        return RMemoryStorage::queryBlockEntities(blockId);
    }
    else {
        // block is in back storage, return only entities from that block:
        return backStorage->queryBlockEntities(blockId);
    }
}

QSet<REntity::Id> RLinkedStorage::queryBlockReferences(RBlock::Id blockId) {
    return RMemoryStorage::queryBlockReferences(blockId)
            .unite(backStorage->queryBlockReferences(blockId));
}

QSet<REntity::Id> RLinkedStorage::queryAllBlockReferences() {
    return RMemoryStorage::queryAllBlockReferences()
            .unite(backStorage->queryAllBlockReferences());
}

QSharedPointer<RObject> RLinkedStorage::queryObject(RObject::Id objectId) const {
    if (!objectMap.contains(objectId)) {
        return backStorage->queryObject(objectId);
    }
    return RMemoryStorage::queryObject(objectId);
}

QSharedPointer<RObject> RLinkedStorage::queryObjectDirect(RObject::Id objectId) const {
    if (!objectMap.contains(objectId)) {
        return backStorage->queryObjectDirect(objectId);
    }
    return RMemoryStorage::queryObjectDirect(objectId);
}

QSharedPointer<REntity> RLinkedStorage::queryEntity(REntity::Id objectId) const {
    if (!entityMap.contains(objectId)) {
        return backStorage->queryEntity(objectId);
    }
    return RMemoryStorage::queryEntity(objectId);
}

QSharedPointer<REntity> RLinkedStorage::queryEntityDirect(REntity::Id objectId) const {
    if (!entityMap.contains(objectId)) {
        return backStorage->queryEntityDirect(objectId);
    }
    return RMemoryStorage::queryEntityDirect(objectId);
}

QSharedPointer<RLayer> RLinkedStorage::queryLayerDirect(RLayer::Id layerId) const {
    if (!objectMap.contains(layerId)) {
        return backStorage->queryLayerDirect(layerId);
    }
    return RMemoryStorage::queryLayerDirect(layerId);
}

QSharedPointer<RLayer> RLinkedStorage::queryLayer(RLayer::Id layerId) const {
    if (!objectMap.contains(layerId)) {
        return backStorage->queryLayer(layerId);
    }
    return RMemoryStorage::queryLayer(layerId);
}

QSharedPointer<RLayer> RLinkedStorage::queryLayer(const QString& layerName) const {
    QSharedPointer<RLayer> ret = RMemoryStorage::queryLayer(layerName);
    if (ret.isNull()) {
        ret = backStorage->queryLayer(layerName);
    }
    return ret;
}

QSharedPointer<RBlock> RLinkedStorage::queryBlockDirect(RBlock::Id blockId) const {
    if (!objectMap.contains(blockId)) {
        return backStorage->queryBlockDirect(blockId);
    }
    return RMemoryStorage::queryBlockDirect(blockId);
}

QSharedPointer<RBlock> RLinkedStorage::queryBlock(RBlock::Id blockId) const {
    if (!objectMap.contains(blockId)) {
        return backStorage->queryBlock(blockId);
    }
    return RMemoryStorage::queryBlock(blockId);
}

QSharedPointer<RBlock> RLinkedStorage::queryBlock(const QString& blockName) const {
    QSharedPointer<RBlock> ret = RMemoryStorage::queryBlock(blockName);
    if (ret.isNull()) {
        ret = backStorage->queryBlock(blockName);
    }
    return ret;
}

QString RLinkedStorage::getBlockName(RBlock::Id blockId) const {
    QString ret = RMemoryStorage::getBlockName(blockId);
    if (ret.isNull()) {
        ret = backStorage->getBlockName(blockId);
    }
    return ret;
}

QString RLinkedStorage::getViewName(RView::Id viewId) {
    QString ret = RMemoryStorage::getViewName(viewId);
    if (ret.isNull()) {
        ret = backStorage->getViewName(viewId);
    }
    return ret;
}

QSharedPointer<RView> RLinkedStorage::queryView(RView::Id viewId) const {
    if (!objectMap.contains(viewId)) {
        return backStorage->queryView(viewId);
    }
    return RMemoryStorage::queryView(viewId);
}

QSharedPointer<RView> RLinkedStorage::queryView(const QString& viewName) const {
    QSharedPointer<RView> ret = RMemoryStorage::queryView(viewName);
    if (ret.isNull()) {
        ret = backStorage->queryView(viewName);
    }
    return ret;
}

QSharedPointer<RUcs> RLinkedStorage::queryUcsDirect(RUcs::Id ucsId) const {
    if (!objectMap.contains(ucsId)) {
        return backStorage->queryUcsDirect(ucsId);
    }
    return RMemoryStorage::queryUcsDirect(ucsId);
}

QSharedPointer<RUcs> RLinkedStorage::queryUcs(RUcs::Id ucsId) const {
    if (!objectMap.contains(ucsId)) {
        return backStorage->queryUcs(ucsId);
    }
    return RMemoryStorage::queryUcs(ucsId);
}

QSharedPointer<RUcs> RLinkedStorage::queryUcs(const QString& ucsName) const {
    QSharedPointer<RUcs> ret = RMemoryStorage::queryUcs(ucsName);
    if (ret.isNull()) {
        ret = backStorage->queryUcs(ucsName);
    }
    return ret;
}

QSharedPointer<RLinetype> RLinkedStorage::queryLinetype(RLinetype::Id linetypeId) const {
    if (!objectMap.contains(linetypeId)) {
        return backStorage->queryLinetype(linetypeId);
    }
    return RMemoryStorage::queryLinetype(linetypeId);
}

QSharedPointer<RLinetype> RLinkedStorage::queryLinetype(const QString& linetypeName) const {
    QSharedPointer<RLinetype> ret = RMemoryStorage::queryLinetype(linetypeName);
    if (ret.isNull()) {
        ret = backStorage->queryLinetype(linetypeName);
    }
    return ret;
}

QString RLinkedStorage::getLayerName(RLayer::Id layerId) {
    QString ret = RMemoryStorage::getLayerName(layerId);
    if (ret.isNull()) {
        ret = backStorage->getLayerName(layerId);
    }
    return ret;
}

RLayer::Id RLinkedStorage::getLayerId(const QString& layerName) {
    RLayer::Id ret = RMemoryStorage::getLayerId(layerName);
    if (ret==RLayer::INVALID_ID) {
        ret = backStorage->getLayerId(layerName);
    }
    return ret;
}

RBlock::Id RLinkedStorage::getBlockId(const QString& blockName) {
    RBlock::Id ret = RMemoryStorage::getBlockId(blockName);
    if (ret==RBlock::INVALID_ID) {
        ret = backStorage->getBlockId(blockName);
    }
    return ret;
}

RView::Id RLinkedStorage::getViewId(const QString& viewName) {
    RView::Id ret = RMemoryStorage::getViewId(viewName);
    if (ret==RView::INVALID_ID) {
        ret = backStorage->getViewId(viewName);
    }
    return ret;
}

QString RLinkedStorage::getLinetypeName(RLinetype::Id linetypeId) {
    QString ret = RMemoryStorage::getLinetypeName(linetypeId);
    if (ret.isNull()) {
        ret = backStorage->getLinetypeName(linetypeId);
    }
    return ret;
}

RLinetype::Id RLinkedStorage::getLinetypeId(const QString& linetypeName) {
    RLinetype::Id ret = RMemoryStorage::getLinetypeId(linetypeName);
    if (ret==RLinetype::INVALID_ID) {
        ret = backStorage->getLinetypeId(linetypeName);
    }
    return ret;
}

void RLinkedStorage::clear() {
    backStorage->clear();
}

/**
 * IDs are handled by the back storage exclusively.
 */
RObject::Id RLinkedStorage::getNewObjectId() {
    //return RObject::INVALID_ID;
    return backStorage->getMaxObjectId() + objectIdOffset++;
    //return backStorage->getNewObjectId();
}

RObject::Handle RLinkedStorage::getNewObjectHandle() {
    return RObject::INVALID_HANDLE;
    // don't count up handle counter of back storage:
    //return backStorage->getNewObjectHandle();
}

RLayer::Id RLinkedStorage::getCurrentLayerId() {
    return backStorage->getCurrentLayerId();
}

RBlock::Id RLinkedStorage::getCurrentBlockId() const {
    return backStorage->getCurrentBlockId();
}

RView::Id RLinkedStorage::getCurrentViewId() {
    return backStorage->getCurrentViewId();
}

RColor RLinkedStorage::getCurrentColor() {
    return backStorage->getCurrentColor();
}

RLineweight::Lineweight RLinkedStorage::getCurrentLineweight() {
    return backStorage->getCurrentLineweight();
}

RLinetype RLinkedStorage::getCurrentLinetype() {
    return backStorage->getCurrentLinetype();
}

QSet<QString> RLinkedStorage::getBlockNames() {
    return RMemoryStorage::getBlockNames().unite(backStorage->getBlockNames());
}

QSet<QString> RLinkedStorage::getViewNames() {
    return RMemoryStorage::getViewNames().unite(backStorage->getViewNames());
}

QSet<QString> RLinkedStorage::getLayerNames() {
    return RMemoryStorage::getLayerNames().unite(backStorage->getLayerNames());
}

QSet<QString> RLinkedStorage::getLinetypeNames() {
    return RMemoryStorage::getLinetypeNames().unite(backStorage->getLinetypeNames());
}

bool RLinkedStorage::deleteObject(RObject::Id objectId) {
    if (objectMap.contains(objectId)) {
        return RMemoryStorage::deleteObject(objectId);
    }
    return false;
}

bool RLinkedStorage::setUndoStatus(RObject::Id objectId, bool status) {
    if (objectMap.contains(objectId)) {
        RMemoryStorage::setUndoStatus(objectId, status);
    }
    return false;
}

bool RLinkedStorage::isInBackStorage(RObject::Id objectId) {
    if (objectMap.contains(objectId)) {
        return false;
    }
    if (!backStorage->queryObjectDirect(objectId).isNull()) {
        return true;
    }
    return false;
}
