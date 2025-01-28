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

#include "RBox.h"
#include "RStorage.h"
#include "RTransaction.h"

class RDocumentVariables;

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

    virtual void setCurrentBlock(RObject::Id blockId);

    virtual void beginTransaction();
    virtual void commitTransaction();
    virtual void rollbackTransaction();

    //virtual QList<RObject::Id> orderBackToFront(const QSet<RObject::Id>& entityIds);

    virtual QSet<RObject::Id> queryAllObjects() const;
    virtual QSet<RObject::Id> querySelectedLayers() const;
    virtual QSet<RObject::Id> queryAllVisibleEntities();
    virtual QSet<RObject::Id> queryAllEntities(bool undone = false, bool allBlocks = false, RS::EntityType type = RS::EntityAll);
    virtual QSet<RObject::Id> queryAllEntities(bool undone, bool allBlocks, QList<RS::EntityType> types);
    virtual QSet<RObject::Id> queryWorkingSetEntities();
    virtual QSet<RObject::Id> queryAllUcs();
    virtual QSet<RObject::Id> queryAllLayers(bool undone = false);
    virtual QSet<RObject::Id> queryAllLayerStates(bool undone = false) const;
    virtual QSet<RObject::Id> queryAllBlocks(bool undone = false);
    virtual QSet<RObject::Id> queryAllLayoutBlocks(bool includeModelSpace = false, bool undone = false) const;
    virtual QSet<RObject::Id> queryAllLayouts(bool undone);
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
    //virtual QSet<RObject::Id> queryViewEntities(RObject::Id viewId);

    virtual QSharedPointer<RDocumentVariables> queryDocumentVariables() const;
    virtual QSharedPointer<RDocumentVariables> queryDocumentVariablesDirect() const;
    virtual QSharedPointer<RDimStyle> queryDimStyle() const;
    virtual QSharedPointer<RDimStyle> queryDimStyleDirect() const;
    virtual QSharedPointer<RObject> queryObject(RObject::Id objectId) const;
    virtual QSharedPointer<RObject> queryObjectByHandle(RObject::Handle objectHandle) const;
    virtual QSharedPointer<RObject> queryObjectByHandleDirect(RObject::Handle objectHandle) const;
    virtual QSharedPointer<REntity> queryEntity(RObject::Id objectId) const;
    virtual QSharedPointer<RLayer> queryLayer(RObject::Id layerId) const;
    virtual QSharedPointer<RLayer> queryLayer(const QString& layerName) const;
    virtual QSharedPointer<RLayerState> queryLayerState(RObject::Id layerStateId) const;
    virtual QSharedPointer<RLayerState> queryLayerState(const QString& layerStateName) const;
    virtual QSharedPointer<RLayout> queryLayout(RObject::Id layoutId) const;
    virtual QSharedPointer<RLayout> queryLayout(const QString& layoutName) const;
    virtual QSharedPointer<RBlock> queryBlock(RObject::Id blockId) const;
    virtual QSharedPointer<RBlock> queryBlock(const QString& blockName) const;
    virtual QSharedPointer<RBlock> queryBlockDirect(const QString& blockName) const;
    virtual QSharedPointer<RView> queryView(RObject::Id viewId) const;
    virtual QSharedPointer<RView> queryView(const QString& viewName) const;
    virtual QSharedPointer<RUcs> queryUcs(RObject::Id ucsId) const;
    virtual QSharedPointer<RUcs> queryUcs(const QString& ucsName) const;
    virtual QSharedPointer<RLinetype> queryLinetypeDirect(RObject::Id linetypeId) const;
    virtual QSharedPointer<RLinetype> queryLinetype(RObject::Id linetypeId) const;
    virtual QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const;

    void clearVisibleCache();
    void updateVisibleCache() const;

    void clearSelectionCache();
    void updateSelectedEntityMap() const;
    void updateSelectedLayerMap() const;

    virtual int countSelectedEntities() const;
    virtual void clearEntitySelection(QSet<RObject::Id>* affectedEntities = NULL);
    virtual void selectAllEntities(QSet<RObject::Id>* affectedEntities = NULL);
    virtual void selectEntity(RObject::Id entityId, bool add = false,
        QSet<RObject::Id>* affectedEntities = NULL);
    virtual void deselectEntity(RObject::Id entityId,
        QSet<RObject::Id>* affectedEntities=NULL);
    virtual int selectEntities(const QSet<RObject::Id>& entityIds,
            bool add = false,
            QSet<RObject::Id>* affectedEntities = NULL);
    virtual int deselectEntities(const QSet<RObject::Id>& entityIds,
            QSet<RObject::Id>* affectedEntities = NULL);
    void setEntitySelected(QSharedPointer<REntity> entity, bool on,
        QSet<RObject::Id>* affectedEntities = NULL, bool onlyDescend = false);
    virtual bool isSelected(RObject::Id entityId);
    virtual bool isSelectedWorkingSet(RObject::Id entityId);

    virtual bool isEntityVisible(const REntity& entity) const;

    virtual bool hasSelection() const;

    virtual RBox getBoundingBox(bool ignoreHiddenLayers = true, bool ignoreEmpty=false) const;
    virtual RBox getSelectionBox() const;
    virtual RBox getEntitiesBox(QSet<RObject::Id>& ids) const;

    virtual bool removeObject(QSharedPointer<RObject> object);
    virtual bool saveObject(QSharedPointer<RObject> object, bool checkBlockRecursion = true, bool keepHandles = false, bool *overwrite = NULL);
    bool checkRecursion(
        RObject::Id blockId, RObject::Id potentialChildBlockId
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

    virtual QString getLayerName(RObject::Id layerId) const;
    virtual QSet<QString> getLayerNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RObject::Id getLayerId(const QString& layerName) const;

    virtual QString getLayerStateName(RObject::Id layerStateId) const;
    virtual QSet<QString> getLayerStateNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RObject::Id getLayerStateId(const QString& layerStateName) const;

    virtual QString getLayoutName(RObject::Id layoutId) const;
    virtual QSet<QString> getLayoutNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    virtual RObject::Id getLayoutId(const QString& layoutName) const;

    virtual QString getBlockName(RObject::Id blockId) const;
    virtual QString getBlockNameFromHandle(RObject::Handle blockHandle) const;
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

    virtual QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const;
    virtual RObject* queryObjectCC(RObject::Id objectId) const;
    virtual QSharedPointer<REntity> queryEntityDirect(RObject::Id objectId) const;
    virtual QSharedPointer<REntity> queryVisibleEntityDirect(RObject::Id objectId) const;
    virtual QSharedPointer<RUcs> queryUcsDirect(RObject::Id ucsId) const;
    virtual QSharedPointer<RLayer> queryLayerDirect(RObject::Id layerId) const;
    virtual QSharedPointer<RLayerState> queryLayerStateDirect(RObject::Id layerStateId) const;
    virtual QSharedPointer<RLayout> queryLayoutDirect(RObject::Id layoutId) const;
    virtual QSharedPointer<RBlock> queryBlockDirect(RObject::Id blockId) const;

    virtual void setObjectHandle(RObject& object, RObject::Handle objectHandle);
    virtual RObject::Handle getNewObjectHandle();

    virtual void setLastTransactionId(int transactionId);

    virtual RLineweight::Lineweight getMaxLineweight() const;

    virtual void update();

    virtual void setEntityParentId(REntity& entity, RObject::Id parentId);

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
    QHash<RObject::Id, QSharedPointer<REntity> > entityMap;
    mutable QHash<RObject::Id, QSharedPointer<REntity> > selectedEntityMap;
    mutable bool selectedEntityMapDirty;
    mutable QHash<RObject::Id, QSharedPointer<REntity> > visibleEntityMap;
    mutable bool visibleEntityMapDirty;
    mutable QHash<RObject::Id, QSharedPointer<RLayer> > selectedLayerMap;
    mutable bool selectedLayerMapDirty;
    mutable QHash<RObject::Id, QHash<RObject::Id, QSharedPointer<REntity> > > blockEntityMap;
    QHash<RObject::Id, QSharedPointer<RBlock> > blockMap;
    QHash<RS::EntityType, QHash<RObject::Id, QSharedPointer<RObject> > > typeObjectMap;
    QHash<RObject::Id, QSharedPointer<RLayer> > layerMap;
    QHash<QString, QSharedPointer<RLayer> > layerNameMap;
    QHash<RObject::Id, QSharedPointer<RLayerState> > layerStateMap;
    QHash<RObject::Id, QSharedPointer<RLayout> > layoutMap;
    QHash<RObject::Id, QSharedPointer<RLinetype> > linetypeMap;
    /** maps parent entity IDs to child entity IDs */
    QMultiHash<RObject::Id, RObject::Id> childMap;
    QHash<int, RTransaction> transactionMap;

    // document wide variables are stored as custom properties in this object:
    QSharedPointer<RDocumentVariables> documentVariables;
    QSharedPointer<RDimStyle> dimStyle;

    QHash<QString, QVariant> variables;
    QMap<QString, QString> variableCaseMap;
    //QHash<RS::KnownVariable, QVariant> knownVariables;
    //RS::Unit unit;
    //QString dimensionFont;
    //double linetypeScale;
};

Q_DECLARE_METATYPE(RMemoryStorage*)

#endif /* RMEMORYSTOARGE_H_ */
