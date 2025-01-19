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

#ifndef RLINKEDSTORAGE_H_
#define RLINKEDSTORAGE_H_

#include "core_global.h"

#include <QSharedPointer>

#include "RMemoryStorage.h"

/**
 * Memory based storage that is linked to another storage.
 * The other storage is read only and only used to read objects
 * that are not available in this storage. All added objects are
 * stored in this storage directly.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RLinkedStorage: public RMemoryStorage {
public:
    RLinkedStorage(RStorage& backStorage);
    virtual ~RLinkedStorage();

    virtual void clear();
    virtual void clearLinked();

    virtual QSet<RObject::Id> queryAllObjects() const;
    virtual QSet<RObject::Id> querySelectedLayers() const;
    virtual QSet<RObject::Id> queryAllVisibleEntities();
    virtual QSet<RObject::Id> queryAllEntities(bool undone = false, bool allBlocks = false, RS::EntityType type = RS::EntityAll);
    virtual QSet<RObject::Id> queryAllEntities(bool undone, bool allBlocks, QList<RS::EntityType> types);
    virtual QSet<RObject::Id> queryAllUcs();
    virtual QSet<RObject::Id> queryAllLayers(bool undone = false);
    virtual QSet<RObject::Id> queryAllLayerStates(bool undone = false);
    virtual QSet<RObject::Id> queryAllBlocks(bool undone = false);
    virtual QSet<RObject::Id> queryAllLayoutBlocks(bool includeModelSpace = false, bool undone = false) const;
    virtual QSet<RObject::Id> queryAllLayouts(bool undone = false);
    virtual QSet<RObject::Id> queryAllViews(bool undone = false);
    virtual QSet<RObject::Id> queryAllLinetypes();
    virtual QSet<RObject::Id> queryInfiniteEntities() const;
    virtual QSet<RObject::Id> querySelectedEntities() const;

    virtual QSet<RObject::Id> queryLayerEntities(RObject::Id layerId, bool allBlocks = false);
    virtual QSet<RObject::Id> querySelectedLayerEntities(RObject::Id layerId, bool allBlocks = false);
    virtual bool hasBlockEntities(RObject::Id blockId) const;
    virtual QSet<RObject::Id> queryBlockEntities(RObject::Id blockId);
    virtual QSet<RObject::Id> queryLayerBlockEntities(RObject::Id layerId, RObject::Id blockId);
    virtual QSet<RObject::Id> queryChildEntities(RObject::Id parentId, RS::EntityType type = RS::EntityAll);
    virtual bool hasChildEntities(RObject::Id parentId) const;
    virtual QSet<RObject::Id> queryBlockReferences(RObject::Id blockId) const;
    virtual QSet<RObject::Id> queryAllBlockReferences() const;
    virtual QSet<RObject::Id> queryAllViewports() const;

    virtual QSharedPointer<RDocumentVariables> queryDocumentVariablesDirect() const;
    virtual QSharedPointer<RDocumentVariables> queryDocumentVariables() const;

    virtual QSharedPointer<RDimStyle> queryDimStyle() const;
    virtual QSharedPointer<RDimStyle> queryDimStyleDirect() const;

    //virtual QSharedPointer<RDocumentVariables> queryDocumentVariables() const;
    virtual QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const;
    virtual RObject* queryObjectCC(RObject::Id objectId) const;
    virtual QSharedPointer<RObject> queryObject(RObject::Id objectId) const;
    virtual QSharedPointer<RObject> queryObjectByHandle(RObject::Handle objectHandle) const;

    virtual QSharedPointer<REntity> queryEntityDirect(RObject::Id objectId) const;
    virtual QSharedPointer<REntity> queryEntity(RObject::Id objectId) const;

    virtual QSharedPointer<RLayer> queryLayerDirect(RObject::Id layerId) const;
    virtual QSharedPointer<RLayer> queryLayer(RObject::Id layerId) const;
    virtual QSharedPointer<RLayer> queryLayer(const QString& layerName) const;

    virtual QSharedPointer<RLayerState> queryLayerStateDirect(RObject::Id layerStateId) const;
    virtual QSharedPointer<RLayerState> queryLayerState(RObject::Id layerStateId) const;
    virtual QSharedPointer<RLayerState> queryLayerState(const QString& layerStateName) const;

    virtual QSharedPointer<RLayout> queryLayoutDirect(RObject::Id layoutId) const;
    virtual QSharedPointer<RLayout> queryLayout(RObject::Id layoutId) const;
    virtual QSharedPointer<RLayout> queryLayout(const QString& layoutName) const;

    virtual QSharedPointer<RBlock> queryBlockDirect(RObject::Id blockId) const;
    virtual QSharedPointer<RBlock> queryBlock(RObject::Id blockId) const;
    virtual QSharedPointer<RBlock> queryBlock(const QString& blockName) const;

    virtual QSharedPointer<RView> queryView(RObject::Id viewId) const;
    virtual QSharedPointer<RView> queryView(const QString& viewName) const;

    virtual QSharedPointer<RUcs> queryUcsDirect(RObject::Id ucsId) const;
    virtual QSharedPointer<RUcs> queryUcs(RObject::Id ucsId) const;
    virtual QSharedPointer<RUcs> queryUcs(const QString& ucsName) const;

    virtual QSharedPointer<RLinetype> queryLinetypeDirect(RObject::Id linetypeId) const;
    virtual QSharedPointer<RLinetype> queryLinetype(RObject::Id linetypeId) const;
    virtual QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const;

    virtual QString getLayerName(RObject::Id layerId) const;
    virtual QSet<QString> getLayerNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RObject::Id getLayerId(const QString& layerName) const;

    virtual QString getLayoutName(RObject::Id layoutId) const;
    virtual QSet<QString> getLayoutNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RObject::Id getLayoutId(const QString& layoutName) const;

    virtual QString getBlockName(RObject::Id blockId) const;
    virtual QString getBlockNameFromHandle(RBlock::Handle blockHandle) const;
    virtual QString getBlockNameFromLayout(const QString& layoutName) const;
    virtual QString getBlockNameFromLayout(RObject::Id layoutId) const;
    virtual QSet<QString> getBlockNames(const QString& rxStr = RDEFAULT_QSTRING, bool undone = false) const;
    virtual RObject::Id getBlockId(const QString& blockName) const;
    virtual RObject::Id getBlockIdAuto(const QString& blockLayoutName) const;

    virtual QString getViewName(RObject::Id viewId) const;
    virtual QSet<QString> getViewNames() const;
    virtual RObject::Id getViewId(const QString& viewName) const;

    virtual QString getLinetypeName(RObject::Id linetypeId) const;
    virtual QString getLinetypeDescription(RObject::Id linetypeId) const;
    virtual QString getLinetypeLabel(RObject::Id linetypeId) const;
    virtual QSet<QString> getLinetypeNames() const;
    virtual QList<RLinetypePattern> getLinetypePatterns() const;
    virtual RObject::Id getLinetypeId(const QString& linetypeName) const;


    virtual RObject::Id getNewObjectId();
    virtual RObject::Handle getNewObjectHandle();

    virtual RObject::Id getCurrentLayerId() const;
    virtual RObject::Id getCurrentBlockId() const;
    virtual RObject::Id getCurrentViewId() const;
    virtual RColor getCurrentColor() const;
    virtual RLineweight::Lineweight getCurrentLineweight() const;
    virtual RObject::Id getCurrentLinetypeId() const;

    virtual bool deleteObject(RObject::Id objectId);
    virtual bool setUndoStatus(RObject::Id objectId, bool status);
    virtual QString getDimensionFont() const;

    virtual QVariant getKnownVariable(RS::KnownVariable key) const;

    virtual bool isInBackStorage(RObject::Id object);

    RStorage* getBackStorage() const {
        return backStorage;
    }

private:
    RStorage* backStorage;
    int objectIdOffset;
};

Q_DECLARE_METATYPE(RLinkedStorage*)

#endif /* RMEMORYSTOARGE_H_ */
