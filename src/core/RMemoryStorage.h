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

#ifndef RMEMORYSTORAGE_H_
#define RMEMORYSTORAGE_H_

#include "core_global.h"

#include <QSharedPointer>

#include "RStorage.h"
#include "RBlockReferenceEntity.h"
#include "RDocumentVariables.h"

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

    virtual QSet<RObject::Id> queryAllObjects() const;
    virtual QSet<RObject::Id> querySelectedLayers() const;
    virtual QSet<REntity::Id> queryAllVisibleEntities();
    virtual QSet<REntity::Id> queryAllEntities(bool undone = false, bool allBlocks = false, RS::EntityType type = RS::EntityAll);
    virtual QSet<REntity::Id> queryAllEntities(bool undone, bool allBlocks, QList<RS::EntityType> types);
    virtual QSet<REntity::Id> queryWorkingSetEntities();
    virtual QSet<RUcs::Id> queryAllUcs();
    virtual QSet<RLayer::Id> queryAllLayers(bool undone = false);
    virtual QSet<RLayerState::Id> queryAllLayerStates(bool undone = false) const;
    virtual QSet<RBlock::Id> queryAllBlocks(bool undone = false);
    virtual QSet<RBlock::Id> queryAllLayoutBlocks(bool includeModelSpace = false, bool undone = false) const;
    virtual QSet<RBlock::Id> queryAllLayouts(bool undone);
    virtual QSet<RView::Id> queryAllViews(bool undone = false);
    virtual QSet<RLinetype::Id> queryAllLinetypes();
    virtual QSet<REntity::Id> queryInfiniteEntities() const;
    virtual QSet<REntity::Id> querySelectedEntities() const;

    virtual QSet<REntity::Id> queryLayerEntities(RLayer::Id layerId, bool allBlocks = false);
    virtual bool hasBlockEntities(RBlock::Id blockId) const;
    virtual QSet<REntity::Id> queryBlockEntities(RBlock::Id blockId);
    virtual QSet<REntity::Id> queryLayerBlockEntities(RLayer::Id layerId, RBlock::Id blockId);
    virtual QSet<REntity::Id> queryChildEntities(REntity::Id parentId, RS::EntityType type = RS::EntityAll);
    virtual bool hasChildEntities(REntity::Id parentId) const;
    virtual QSet<REntity::Id> queryBlockReferences(RBlock::Id blockId) const;
    virtual QSet<REntity::Id> queryAllBlockReferences() const;
    //virtual QSet<REntity::Id> queryViewEntities(RView::Id viewId);

    virtual QSharedPointer<RDocumentVariables> queryDocumentVariables() const;
    virtual QSharedPointer<RDocumentVariables> queryDocumentVariablesDirect() const;
    virtual QSharedPointer<RObject> queryObject(RObject::Id objectId) const;
    virtual QSharedPointer<RObject> queryObjectByHandle(RObject::Handle objectHandle) const;
    virtual QSharedPointer<RObject> queryObjectByHandleDirect(RObject::Handle objectHandle) const;
    virtual QSharedPointer<REntity> queryEntity(REntity::Id objectId) const;
    virtual QSharedPointer<RLayer> queryLayer(RLayer::Id layerId) const;
    virtual QSharedPointer<RLayer> queryLayer(const QString& layerName) const;
    virtual QSharedPointer<RLayerState> queryLayerState(RLayerState::Id layerStateId) const;
    virtual QSharedPointer<RLayerState> queryLayerState(const QString& layerStateName) const;
    virtual QSharedPointer<RLayout> queryLayout(RLayout::Id layoutId) const;
    virtual QSharedPointer<RLayout> queryLayout(const QString& layoutName) const;
    virtual QSharedPointer<RBlock> queryBlock(RBlock::Id blockId) const;
    virtual QSharedPointer<RBlock> queryBlock(const QString& blockName) const;
    virtual QSharedPointer<RBlock> queryBlockDirect(const QString& blockName) const;
    virtual QSharedPointer<RView> queryView(RView::Id viewId) const;
    virtual QSharedPointer<RView> queryView(const QString& viewName) const;
    virtual QSharedPointer<RUcs> queryUcs(RUcs::Id ucsId) const;
    virtual QSharedPointer<RUcs> queryUcs(const QString& ucsName) const;
    virtual QSharedPointer<RLinetype> queryLinetypeDirect(RLinetype::Id linetypeId) const;
    virtual QSharedPointer<RLinetype> queryLinetype(RLinetype::Id linetypeId) const;
    virtual QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const;

    void clearVisibleCache();
    void updateVisibleCache() const;

    void clearSelectionCache();
    void updateSelectedEntityMap() const;
    void updateSelectedLayerMap() const;

    virtual int countSelectedEntities() const;
    virtual void clearEntitySelection(QSet<REntity::Id>* affectedEntities = NULL);
    virtual void selectAllEntities(QSet<REntity::Id>* affectedEntities = NULL);
    virtual void selectEntity(REntity::Id entityId, bool add = false,
        QSet<REntity::Id>* affectedEntities = NULL);
    virtual void deselectEntity(REntity::Id entityId,
        QSet<REntity::Id>* affectedEntities=NULL);
    virtual int selectEntities(const QSet<REntity::Id>& entityIds,
            bool add = false,
            QSet<REntity::Id>* affectedEntities = NULL);
    virtual int deselectEntities(const QSet<REntity::Id>& entityIds,
            QSet<REntity::Id>* affectedEntities = NULL);
    void setEntitySelected(QSharedPointer<REntity> entity, bool on,
        QSet<REntity::Id>* affectedEntities = NULL, bool onlyDescend = false);
    virtual bool isSelected(REntity::Id entityId);
    virtual bool isSelectedWorkingSet(REntity::Id entityId);

    virtual bool isEntityVisible(const REntity& entity) const;

    virtual bool hasSelection() const;

    virtual RBox getBoundingBox(bool ignoreHiddenLayers = true, bool ignoreEmpty=false) const;
    virtual RBox getSelectionBox() const;
    virtual RBox getEntitiesBox(QSet<REntity::Id>& ids) const;

    virtual bool removeObject(QSharedPointer<RObject> object);
    virtual bool saveObject(QSharedPointer<RObject> object, bool checkBlockRecursion = true, bool keepHandles = false);
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
    virtual void setUndoStatus(RObject& object, bool status);
    //virtual bool getUndoStatus(RObject::Id objectId) const;
    virtual int getMaxTransactionId();

    virtual QStringList getVariables() const;
    virtual void setVariable(const QString& key, const QVariant& value, bool overwrite = true);
    virtual QVariant getVariable(const QString& key) const;
    virtual void removeVariable(const QString& key);

    virtual void setKnownVariable(RS::KnownVariable key, const QVariant& value, RTransaction* transaction = NULL);
    virtual QVariant getKnownVariable(RS::KnownVariable key) const;

    virtual QString getLayerName(RLayer::Id layerId) const;
    virtual QSet<QString> getLayerNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RLayer::Id getLayerId(const QString& layerName) const;

    virtual QString getLayerStateName(RLayerState::Id layerStateId) const;
    virtual QSet<QString> getLayerStateNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RLayerState::Id getLayerStateId(const QString& layerStateName) const;

    virtual QString getLayoutName(RLayout::Id layoutId) const;
    virtual QSet<QString> getLayoutNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RLayout::Id getLayoutId(const QString& layoutName) const;

    virtual QString getBlockName(RBlock::Id blockId) const;
    virtual QString getBlockNameFromLayout(const QString& layoutName) const;
    virtual QString getBlockNameFromLayout(RLayout::Id layoutId) const;
    virtual QSet<QString> getBlockNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RBlock::Id getBlockId(const QString& blockName) const;
    virtual RBlock::Id getBlockIdAuto(const QString& blockLayoutName) const;

    virtual QString getViewName(RView::Id viewId) const;
    virtual QSet<QString> getViewNames() const;
    virtual RView::Id getViewId(const QString& viewName) const;

    virtual QString getLinetypeName(RLinetype::Id linetypeId) const;
    virtual QString getLinetypeDescription(RLinetype::Id linetypeId) const;
    virtual QString getLinetypeLabel(RLinetype::Id linetypeId) const;
    virtual QSet<QString> getLinetypeNames() const;
    virtual QList<RLinetypePattern> getLinetypePatterns() const;
    virtual RLinetype::Id getLinetypeId(const QString& linetypeName) const;

    virtual QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const;
    virtual QSharedPointer<REntity> queryEntityDirect(REntity::Id objectId) const;
    virtual QSharedPointer<REntity> queryVisibleEntityDirect(REntity::Id objectId) const;
    virtual QSharedPointer<RUcs> queryUcsDirect(RUcs::Id ucsId) const;
    virtual QSharedPointer<RLayer> queryLayerDirect(RLayer::Id layerId) const;
    virtual QSharedPointer<RLayerState> queryLayerStateDirect(RLayerState::Id layerStateId) const;
    virtual QSharedPointer<RLayout> queryLayoutDirect(RLayout::Id layoutId) const;
    virtual QSharedPointer<RBlock> queryBlockDirect(RBlock::Id blockId) const;

    virtual void setObjectHandle(RObject& object, RObject::Handle objectHandle);
    virtual RObject::Handle getNewObjectHandle();

    virtual void setLastTransactionId(int transactionId);

    virtual RLineweight::Lineweight getMaxLineweight() const;

    virtual void update();

    virtual void setEntityParentId(REntity& entity, REntity::Id parentId);

    //virtual void setUnit(RS::Unit unit, RTransaction* transaction = NULL);
    //virtual RS::Unit getUnit() const;

//    virtual void setDimensionFont(const QString& f);
//    virtual QString getDimensionFont() const;

//    virtual void setLinetypeScale(double v, RTransaction* transaction);
//    virtual double getLinetypeScale() const;

protected:
    mutable RLineweight::Lineweight maxLineweight;

    /**
     * Bounding boxes for ignoreHiddenLayers on/off and ignoreEmpty on/off
     */
    mutable RBox boundingBox[2][2];
    mutable bool boundingBoxDirty;
    //mutable bool boundingBoxIgnoreHiddenLayers;
    //mutable bool boundingBoxIgnoreEmpty;

    bool inTransaction;
    QHash<RObject::Id, QSharedPointer<RObject> > objectMap;
    QHash<RObject::Handle, QSharedPointer<RObject> > objectHandleMap;
    QHash<REntity::Id, QSharedPointer<REntity> > entityMap;
    mutable QHash<REntity::Id, QSharedPointer<REntity> > selectedEntityMap;
    mutable bool selectedEntityMapDirty;
    mutable QHash<REntity::Id, QSharedPointer<REntity> > visibleEntityMap;
    mutable bool visibleEntityMapDirty;
    mutable QHash<RLayer::Id, QSharedPointer<RLayer> > selectedLayerMap;
    mutable bool selectedLayerMapDirty;
    mutable QHash<RBlock::Id, QHash<REntity::Id, QSharedPointer<REntity> > > blockEntityMap;
    QHash<RBlock::Id, QSharedPointer<RBlock> > blockMap;
    QHash<RS::EntityType, QHash<RObject::Id, QSharedPointer<RObject> > > typeObjectMap;
    QHash<RLayer::Id, QSharedPointer<RLayer> > layerMap;
    QHash<QString, QSharedPointer<RLayer> > layerNameMap;
    QHash<RLayerState::Id, QSharedPointer<RLayerState> > layerStateMap;
    QHash<RLayout::Id, QSharedPointer<RLayout> > layoutMap;
    QHash<RLinetype::Id, QSharedPointer<RLinetype> > linetypeMap;
    /** maps parent entity IDs to child entity IDs */
    QMultiHash<REntity::Id, REntity::Id> childMap;
    QHash<int, RTransaction> transactionMap;

    // document wide variables are stored as custom properties in this object:
    QSharedPointer<RDocumentVariables> documentVariables;

    QHash<QString, QVariant> variables;
    QMap<QString, QString> variableCaseMap;
    //QHash<RS::KnownVariable, QVariant> knownVariables;
    //RS::Unit unit;
    //QString dimensionFont;
    //double linetypeScale;
};

Q_DECLARE_METATYPE(RMemoryStorage*)

#endif /* RMEMORYSTOARGE_H_ */
