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

#ifndef RMEMORYSTORAGE_H_
#define RMEMORYSTORAGE_H_

#include "core_global.h"

#include <QSharedPointer>

#include "RStorage.h"
#include "RBlockReferenceEntity.h"

/**
 * Basic memory based storage.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RMemoryStorage: public RStorage {
public:
    RMemoryStorage();
    virtual ~RMemoryStorage();

    virtual void clear();

    virtual void setCurrentBlock(RBlock::Id blockId);

    virtual void beginTransaction();
    virtual void commitTransaction();
    virtual void rollbackTransaction();

    //virtual QList<REntity::Id> orderBackToFront(const QSet<REntity::Id>& entityIds);

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
    //virtual QSet<REntity::Id> queryViewEntities(RView::Id viewId);

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

    virtual void clearEntitySelection(QSet<REntity::Id>* affectedEntities = NULL);
    virtual void selectAllEntites(QSet<REntity::Id>* affectedEntities = NULL);
    virtual void selectEntity(REntity::Id entityId, bool add = false,
        QSet<REntity::Id>* affectedEntities = NULL);
    virtual void deselectEntity(REntity::Id entityId,
        QSet<REntity::Id>* affectedEntities=NULL);
    virtual void selectEntities(const QSet<REntity::Id>& entityIds,
            bool add = false,
            QSet<REntity::Id>* affectedEntities = NULL);
    virtual void deselectEntities(const QSet<REntity::Id>& entityIds,
            QSet<REntity::Id>* affectedEntities = NULL);
    virtual bool isSelected(REntity::Id entityId);

    virtual bool hasSelection() const;

    virtual RBox getBoundingBox(bool includeHiddenLayer = true);
    virtual RBox getSelectionBox();

    virtual bool saveObject(QSharedPointer<RObject> object);
    bool checkRecursion(
        RBlock::Id blockId, RBlock::Id potentialChildBlockId
    );
    virtual bool deleteObject(RObject::Id objectId);
    virtual void saveTransaction(RTransaction& transaction);
    virtual void deleteTransactionsFrom(int transactionId);
    virtual RTransaction getTransaction(int transactionId);

    virtual void resetTransactionStack();

    virtual void toggleUndoStatus(QSet<RObject::Id>& objects);
    virtual void toggleUndoStatus(RObject::Id object);
    virtual bool setUndoStatus(RObject::Id objectId, bool status);
    //virtual bool getUndoStatus(RObject::Id objectId) const;
    virtual int getMaxTransactionId();

    virtual QStringList getVariables() const;
    virtual void setVariable(const QString& key, const QVariant & value);
    virtual QVariant getVariable(const QString& key) const;

    virtual void setKnownVariable(RS::KnownVariable key, const QVariant& value);
    virtual QVariant getKnownVariable(RS::KnownVariable key) const;

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

    virtual void setLastTransactionId(int transactionId);

    virtual RLineweight::Lineweight getMaxLineweight() const;

    virtual void setUnit(RS::Unit unit);
    virtual RS::Unit getUnit() const;

    virtual void setLinetypeScale(double v);
    virtual double getLinetypeScale() const;

protected:
    RLineweight::Lineweight maxLineweight;
    bool inTransaction;
    bool boundingBoxChanged;
    RBox boundingBox;
    QHash<RObject::Id, QSharedPointer<RObject> > objectMap;
    QHash<REntity::Id, QSharedPointer<REntity> > entityMap;
    QHash<int, RTransaction> transactionMap;
    QHash<QString, QVariant> variables;
    QMap<QString, QString> variableCaseMap;
    QHash<RS::KnownVariable, QVariant> knownVariables;
    RS::Unit unit;
    double linetypeScale;
};

Q_DECLARE_METATYPE(RMemoryStorage*)

#endif /* RMEMORYSTOARGE_H_ */
