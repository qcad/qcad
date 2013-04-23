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

#ifndef RLINKEDSTORAGE_H_
#define RLINKEDSTORAGE_H_

#include "core_global.h"

#include <QSharedPointer>

#include "RMemoryStorage.h"
#include "RBlockReferenceEntity.h"

/**
 * Memory based storage that is linked to another storage.
 * The other storage is read only and only used to read objects
 * that are not avilable in this storage. All added objects are
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

    virtual QSet<RObject::Id> queryAllObjects();
    virtual QSet<REntity::Id> queryAllEntities(bool undone = false, bool allBlocks = false);
    virtual QSet<RUcs::Id> queryAllUcs();
    virtual QSet<RLayer::Id> queryAllLayers(bool undone = false);
    virtual QSet<RBlock::Id> queryAllBlocks(bool undone = false);
    virtual QSet<RView::Id> queryAllViews(bool undone = false);
    virtual QSet<RLinetype::Id> queryAllLinetypes();
    virtual QSet<REntity::Id> querySelectedEntities();

    virtual QSet<REntity::Id> queryLayerEntities(RLayer::Id layerId, bool allBlocks = false);
    virtual QSet<REntity::Id> queryBlockEntities(RBlock::Id blockId);
    virtual QSet<REntity::Id> queryBlockReferences(RBlock::Id blockId);
    virtual QSet<REntity::Id> queryAllBlockReferences();

    virtual QSharedPointer<RObject> queryObject(RObject::Id objectId) const;
    virtual QSharedPointer<REntity> queryEntity(REntity::Id objectId) const;
    virtual QSharedPointer<RLayer> queryLayer(RLayer::Id layerId) const;
    virtual QSharedPointer<RLayer> queryLayer(const QString& layerName) const;
    virtual QSharedPointer<RBlock> queryBlock(RBlock::Id blockId) const;
    virtual QSharedPointer<RBlock> queryBlock(const QString& blockName) const;
    virtual QSharedPointer<RView> queryView(RView::Id viewId) const;
    virtual QSharedPointer<RView> queryView(const QString& viewName) const;
    virtual QSharedPointer<RUcs> queryUcs(RUcs::Id ucsId) const;
    virtual QSharedPointer<RUcs> queryUcs(const QString& ucsName) const;
    virtual QSharedPointer<RLinetype> queryLinetype(RLinetype::Id linetypeId) const;
    virtual QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const;

    virtual QString getLayerName(RLayer::Id layerId) const;
    virtual QSet<QString> getLayerNames() const;
    virtual RLayer::Id getLayerId(const QString& layerName) const;

    virtual QString getBlockName(RBlock::Id blockId) const;
    virtual QSet<QString> getBlockNames() const;
    virtual RBlock::Id getBlockId(const QString& blockName) const;

    virtual QString getViewName(RView::Id viewId) const;
    virtual QSet<QString> getViewNames() const;
    virtual RView::Id getViewId(const QString& viewName) const;

    virtual QString getLinetypeName(RLinetype::Id linetypeId) const;
    virtual QSet<QString> getLinetypeNames() const;
    virtual RLinetype::Id getLinetypeId(const QString& linetypeName) const;

    virtual QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const;
    virtual QSharedPointer<REntity> queryEntityDirect(REntity::Id objectId) const;
    virtual QSharedPointer<RUcs> queryUcsDirect(RUcs::Id ucsId) const;
    virtual QSharedPointer<RLayer> queryLayerDirect(RLayer::Id layerId) const;
    virtual QSharedPointer<RBlock> queryBlockDirect(RBlock::Id blockId) const;

    virtual RObject::Id getNewObjectId();
    virtual RObject::Handle getNewObjectHandle();

    virtual RLayer::Id getCurrentLayerId();
    virtual RBlock::Id getCurrentBlockId() const;
    virtual RView::Id getCurrentViewId();
    virtual RColor getCurrentColor();
    virtual RLineweight::Lineweight getCurrentLineweight() const;
    virtual RLinetype getCurrentLinetype() const;

    virtual bool deleteObject(RObject::Id objectId);
    virtual bool setUndoStatus(RObject::Id objectId, bool status);

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
