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
#include "RLinkedStorage.h"

RLinkedStorage::RLinkedStorage(RStorage& backStorage) :
    RMemoryStorage(),
    backStorage(&backStorage),
    objectIdOffset(1) {

    // copy document settings from original:
    //QSharedPointer<RDocumentVariables> docVars = QSharedPointer<RDocumentVariables>(new RDocumentVariables(this));
    //saveObject();
}

RLinkedStorage::~RLinkedStorage() {
}

QSet<RObject::Id> RLinkedStorage::queryAllObjects() const {
    return RMemoryStorage::queryAllObjects()
            .unite(backStorage->queryAllObjects());
}

QSet<RObject::Id> RLinkedStorage::querySelectedLayers() const {
    return RMemoryStorage::querySelectedLayers()
            .unite(backStorage->querySelectedLayers());
}

QSet<REntity::Id> RLinkedStorage::queryAllVisibleEntities() {
    return RMemoryStorage::queryAllVisibleEntities()
            .unite(backStorage->queryAllVisibleEntities());
}

QSet<REntity::Id> RLinkedStorage::queryAllEntities(bool undone, bool allBlocks, RS::EntityType type) {
    return RMemoryStorage::queryAllEntities(undone, allBlocks, type)
            .unite(backStorage->queryAllEntities(undone, allBlocks, type));
}

QSet<REntity::Id> RLinkedStorage::queryAllEntities(bool undone, bool allBlocks, QList<RS::EntityType> types) {
    return RMemoryStorage::queryAllEntities(undone, allBlocks, types)
            .unite(backStorage->queryAllEntities(undone, allBlocks, types));
}

QSet<RUcs::Id> RLinkedStorage::queryAllUcs() {
    return RMemoryStorage::queryAllUcs()
            .unite(backStorage->queryAllUcs());
}

QSet<RLayer::Id> RLinkedStorage::queryAllLayers(bool undone) {
    return RMemoryStorage::queryAllLayers(undone)
            .unite(backStorage->queryAllLayers(undone));
}

QSet<RLayerState::Id> RLinkedStorage::queryAllLayerStates(bool undone) {
    return RMemoryStorage::queryAllLayerStates(undone)
            .unite(backStorage->queryAllLayerStates(undone));
}

QSet<RBlock::Id> RLinkedStorage::queryAllBlocks(bool undone) {
    return RMemoryStorage::queryAllBlocks(undone)
            .unite(backStorage->queryAllBlocks(undone));
}

QSet<RBlock::Id> RLinkedStorage::queryAllLayoutBlocks(bool includeModelSpace, bool undone) const {
    return RMemoryStorage::queryAllLayoutBlocks(includeModelSpace, undone)
            .unite(backStorage->queryAllLayoutBlocks(includeModelSpace, undone));
}

QSet<RLayout::Id> RLinkedStorage::queryAllLayouts(bool undone) {
    return RMemoryStorage::queryAllLayouts(undone)
            .unite(backStorage->queryAllLayouts(undone));
}

QSet<RView::Id> RLinkedStorage::queryAllViews(bool undone) {
    return RMemoryStorage::queryAllViews(undone)
            .unite(backStorage->queryAllViews(undone));
}

QSet<RLinetype::Id> RLinkedStorage::queryAllLinetypes() {
    return RMemoryStorage::queryAllLinetypes()
            .unite(backStorage->queryAllLinetypes());
}

QSet<REntity::Id> RLinkedStorage::queryInfiniteEntities() const{
    return RMemoryStorage::queryInfiniteEntities()
            .unite(backStorage->queryInfiniteEntities());
}

QSet<REntity::Id> RLinkedStorage::querySelectedEntities() const {
    return RMemoryStorage::querySelectedEntities()
            .unite(backStorage->querySelectedEntities());
}

QSet<REntity::Id> RLinkedStorage::queryLayerEntities(RLayer::Id layerId, bool allBlocks) {
    return RMemoryStorage::queryLayerEntities(layerId, allBlocks)
            .unite(backStorage->queryLayerEntities(layerId, allBlocks));
}

bool RLinkedStorage::hasBlockEntities(RBlock::Id blockId) const {
    if (blockMap.contains(blockId)) {
        // got block, return only true for block entities from this block:
        return RMemoryStorage::hasBlockEntities(blockId);
    }
    else {
        // block is in back storage, return only true for entities from that block:
        return backStorage->hasBlockEntities(blockId);
    }
}

QSet<REntity::Id> RLinkedStorage::queryBlockEntities(RBlock::Id blockId) {
    if (blockMap.contains(blockId)) {
        // got block, return only block entities from this block:
        return RMemoryStorage::queryBlockEntities(blockId);
    }
    else {
        // block is in back storage, return only entities from that block:
        return backStorage->queryBlockEntities(blockId);
    }
}

QSet<REntity::Id> RLinkedStorage::queryLayerBlockEntities(RLayer::Id layerId, RBlock::Id blockId) {
    // TODO: implement
    return RMemoryStorage::queryLayerBlockEntities(layerId, blockId);
}

QSet<REntity::Id> RLinkedStorage::queryChildEntities(REntity::Id parentId, RS::EntityType type) {
    if (entityMap.contains(parentId)) {
        // got parent, return only child entities from this parent:
        return RMemoryStorage::queryChildEntities(parentId, type);
    }
    else {
        // parent is in back storage, return only child entities from that parent:
        return backStorage->queryChildEntities(parentId, type);
    }
}

bool RLinkedStorage::hasChildEntities(REntity::Id parentId) const {
    if (entityMap.contains(parentId)) {
        return RMemoryStorage::hasChildEntities(parentId);
    }
    else {
        return backStorage->hasChildEntities(parentId);
    }
}

QSet<REntity::Id> RLinkedStorage::queryBlockReferences(RBlock::Id blockId) const {
    return RMemoryStorage::queryBlockReferences(blockId)
            .unite(backStorage->queryBlockReferences(blockId));
}

QSet<REntity::Id> RLinkedStorage::queryAllBlockReferences() const {
    return RMemoryStorage::queryAllBlockReferences()
            .unite(backStorage->queryAllBlockReferences());
}

QSharedPointer<RDocumentVariables> RLinkedStorage::queryDocumentVariablesDirect() const {
    return RMemoryStorage::queryDocumentVariablesDirect();
}

QSharedPointer<RDocumentVariables> RLinkedStorage::queryDocumentVariables() const {
    return RMemoryStorage::queryDocumentVariables();
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

QSharedPointer<RObject> RLinkedStorage::queryObjectByHandle(RObject::Handle objectHandle) const {
    QSharedPointer<RObject> ret = RMemoryStorage::queryObjectByHandle(objectHandle);
    if (ret.isNull()) {
        ret = backStorage->queryObjectByHandle(objectHandle);
    }
    return ret;
}

QSharedPointer<REntity> RLinkedStorage::queryEntityDirect(REntity::Id objectId) const {
    if (!entityMap.contains(objectId)) {
        return backStorage->queryEntityDirect(objectId);
    }
    return RMemoryStorage::queryEntityDirect(objectId);
}

QSharedPointer<RLayer> RLinkedStorage::queryLayerDirect(RLayer::Id layerId) const {
    if (!layerMap.contains(layerId)) {
        return backStorage->queryLayerDirect(layerId);
    }
    return RMemoryStorage::queryLayerDirect(layerId);
}

QSharedPointer<RLayer> RLinkedStorage::queryLayer(RLayer::Id layerId) const {
    if (!layerMap.contains(layerId)) {
        return backStorage->queryLayer(layerId);
    }
    return RMemoryStorage::queryLayer(layerId);
}

QSharedPointer<RLayer> RLinkedStorage::queryLayer(const QString& layerName) const {
    if (!layerNameMap.contains(layerName)) {
        return backStorage->queryLayer(layerName);
    }
    return RMemoryStorage::queryLayer(layerName);
    //QSharedPointer<RLayer> ret = RMemoryStorage::queryLayer(layerName);
    //if (ret.isNull()) {
    //    ret = backStorage->queryLayer(layerName);
    //}
    //return ret;
}

QSharedPointer<RLayerState> RLinkedStorage::queryLayerStateDirect(RLayerState::Id layerStateId) const {
    if (!layerStateMap.contains(layerStateId)) {
        return backStorage->queryLayerStateDirect(layerStateId);
    }
    return RMemoryStorage::queryLayerStateDirect(layerStateId);
}

QSharedPointer<RLayerState> RLinkedStorage::queryLayerState(RLayerState::Id layerStateId) const {
    if (!layerStateMap.contains(layerStateId)) {
        return backStorage->queryLayerState(layerStateId);
    }
    return RMemoryStorage::queryLayerState(layerStateId);
}

QSharedPointer<RLayerState> RLinkedStorage::queryLayerState(const QString& layerStateName) const {
    QSharedPointer<RLayerState> ret = RMemoryStorage::queryLayerState(layerStateName);
    if (ret.isNull()) {
        ret = backStorage->queryLayerState(layerStateName);
    }
    return ret;
}

QSharedPointer<RLayout> RLinkedStorage::queryLayoutDirect(RLayout::Id layoutId) const {
    if (!layoutMap.contains(layoutId)) {
        return backStorage->queryLayoutDirect(layoutId);
    }
    return RMemoryStorage::queryLayoutDirect(layoutId);
}

QSharedPointer<RLayout> RLinkedStorage::queryLayout(RLayout::Id layoutId) const {
    if (!layoutMap.contains(layoutId)) {
        return backStorage->queryLayout(layoutId);
    }
    return RMemoryStorage::queryLayout(layoutId);
}

QSharedPointer<RLayout> RLinkedStorage::queryLayout(const QString& layoutName) const {
    QSharedPointer<RLayout> ret = RMemoryStorage::queryLayout(layoutName);
    if (ret.isNull()) {
        ret = backStorage->queryLayout(layoutName);
    }
    return ret;
}

QSharedPointer<RBlock> RLinkedStorage::queryBlockDirect(RBlock::Id blockId) const {
    if (!blockMap.contains(blockId)) {
        return backStorage->queryBlockDirect(blockId);
    }
    return RMemoryStorage::queryBlockDirect(blockId);
}

QSharedPointer<RBlock> RLinkedStorage::queryBlock(RBlock::Id blockId) const {
    if (!blockMap.contains(blockId)) {
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

QString RLinkedStorage::getBlockNameFromLayout(const QString& layoutName) const {
    QString ret = RMemoryStorage::getBlockNameFromLayout(layoutName);
    if (ret.isNull()) {
        ret = backStorage->getBlockNameFromLayout(layoutName);
    }
    return ret;
}

QString RLinkedStorage::getBlockNameFromLayout(RLayout::Id layoutId) const {
    QString ret = RMemoryStorage::getBlockNameFromLayout(layoutId);
    if (ret.isNull()) {
        ret = backStorage->getBlockNameFromLayout(layoutId);
    }
    return ret;
}

QString RLinkedStorage::getViewName(RView::Id viewId) const {
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

QSharedPointer<RLinetype> RLinkedStorage::queryLinetypeDirect(RLinetype::Id linetypeId) const {
    if (!linetypeMap.contains(linetypeId)) {
        return backStorage->queryLinetypeDirect(linetypeId);
    }
    return RMemoryStorage::queryLinetypeDirect(linetypeId);
}

QSharedPointer<RLinetype> RLinkedStorage::queryLinetype(RLinetype::Id linetypeId) const {
    if (!linetypeMap.contains(linetypeId)) {
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

QString RLinkedStorage::getLayerName(RLayer::Id layerId) const {
    QString ret = RMemoryStorage::getLayerName(layerId);
    if (ret.isNull()) {
        ret = backStorage->getLayerName(layerId);
    }
    return ret;
}

RLayer::Id RLinkedStorage::getLayerId(const QString& layerName) const {
    RLayer::Id ret = RMemoryStorage::getLayerId(layerName);
    if (ret==RLayer::INVALID_ID) {
        ret = backStorage->getLayerId(layerName);
    }
    return ret;
}

QString RLinkedStorage::getLayoutName(RLayout::Id layoutId) const {
    QString ret = RMemoryStorage::getLayoutName(layoutId);
    if (ret.isNull()) {
        ret = backStorage->getLayoutName(layoutId);
    }
    return ret;
}

RLayout::Id RLinkedStorage::getLayoutId(const QString& layoutName) const {
    RLayout::Id ret = RMemoryStorage::getLayoutId(layoutName);
    if (ret==RLayout::INVALID_ID) {
        ret = backStorage->getLayoutId(layoutName);
    }
    return ret;
}

RBlock::Id RLinkedStorage::getBlockId(const QString& blockName) const {
    RBlock::Id ret = RMemoryStorage::getBlockId(blockName);
    if (ret==RBlock::INVALID_ID) {
        ret = backStorage->getBlockId(blockName);
    }
    return ret;
}

RBlock::Id RLinkedStorage::getBlockIdAuto(const QString& blockLayoutName) const {
    RBlock::Id ret = RMemoryStorage::getBlockIdAuto(blockLayoutName);
    if (ret==RBlock::INVALID_ID) {
        ret = backStorage->getBlockIdAuto(blockLayoutName);
    }
    return ret;
}

RView::Id RLinkedStorage::getViewId(const QString& viewName) const {
    RView::Id ret = RMemoryStorage::getViewId(viewName);
    if (ret==RView::INVALID_ID) {
        ret = backStorage->getViewId(viewName);
    }
    return ret;
}

QString RLinkedStorage::getLinetypeName(RLinetype::Id linetypeId) const {
    QString ret = RMemoryStorage::getLinetypeName(linetypeId);
    if (ret.isNull()) {
        ret = backStorage->getLinetypeName(linetypeId);
    }
    return ret;
}

QString RLinkedStorage::getLinetypeDescription(RLinetype::Id linetypeId) const {
    QString ret = RMemoryStorage::getLinetypeDescription(linetypeId);
    if (ret.isNull()) {
        ret = backStorage->getLinetypeDescription(linetypeId);
    }
    return ret;
}

QString RLinkedStorage::getLinetypeLabel(RLinetype::Id linetypeId) const {
    QString ret = RMemoryStorage::getLinetypeLabel(linetypeId);
    if (ret.isNull()) {
        ret = backStorage->getLinetypeLabel(linetypeId);
    }
    return ret;
}

RLinetype::Id RLinkedStorage::getLinetypeId(const QString& linetypeName) const {
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

RLayer::Id RLinkedStorage::getCurrentLayerId() const {
    return backStorage->getCurrentLayerId();
}

RBlock::Id RLinkedStorage::getCurrentBlockId() const {
    return backStorage->getCurrentBlockId();
}

RView::Id RLinkedStorage::getCurrentViewId() const {
    return backStorage->getCurrentViewId();
}

RColor RLinkedStorage::getCurrentColor() const {
    return backStorage->getCurrentColor();
}

RLineweight::Lineweight RLinkedStorage::getCurrentLineweight() const {
    return backStorage->getCurrentLineweight();
}

RLinetype::Id RLinkedStorage::getCurrentLinetypeId() const {
    return backStorage->getCurrentLinetypeId();
}

QSet<QString> RLinkedStorage::getBlockNames(const QString& rxStr) const {
    return RMemoryStorage::getBlockNames(rxStr).unite(backStorage->getBlockNames(rxStr));
}

QSet<QString> RLinkedStorage::getViewNames() const {
    return RMemoryStorage::getViewNames().unite(backStorage->getViewNames());
}

QSet<QString> RLinkedStorage::getLayerNames(const QString& rxStr) const {
    return RMemoryStorage::getLayerNames(rxStr).unite(backStorage->getLayerNames(rxStr));
}

QSet<QString> RLinkedStorage::getLayoutNames(const QString& rxStr) const {
    return RMemoryStorage::getLayoutNames(rxStr).unite(backStorage->getLayoutNames(rxStr));
}

QSet<QString> RLinkedStorage::getLinetypeNames() const {
    return RMemoryStorage::getLinetypeNames().unite(backStorage->getLinetypeNames());
}

QList<RLinetypePattern> RLinkedStorage::getLinetypePatterns() const {
    QList<RLinetypePattern> ret;
    QSet<QString> names = getLinetypeNames();
    QSet<QString>::iterator it;
    for (it = names.begin(); it != names.end(); ++it) {
        QSharedPointer<RLinetype> lt = queryLinetype(*it);
        if (lt.isNull()) {
            continue;
        }
        ret.append(lt->getPattern());
    }
    return ret;
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

QVariant RLinkedStorage::getKnownVariable(RS::KnownVariable key) const {
    if (documentVariables->hasKnownVariable(key)) {
        return RMemoryStorage::getKnownVariable(key);
    }
    return backStorage->getKnownVariable(key);
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

QString RLinkedStorage::getDimensionFont() const {
    if (documentVariables->getDimensionFont().isEmpty()) {
        return backStorage->getDimensionFont();
    }
    return documentVariables->getDimensionFont();
}
