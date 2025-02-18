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

#ifndef RSTORAGE_H
#define RSTORAGE_H

#include "core_global.h"

#include <QString>
#include <QSharedPointer>
#include <QDateTime>

#include "RColor.h"
#include "RLinetype.h"
#include "RLinetypePattern.h"
#include "RLineweight.h"
#include "RNonCopyable.h"
#include "RRequireHeap.h"
#include "RUcs.h"

class RBlock;
class RBox;
class RDimStyle;
class RDocument;
class RDocumentVariables;
class REntity;
class RLayer;
class RLayerState;
class RLayout;
class RModifiedListener;
class RTransaction;
class RView;

#ifndef RDEFAULT_QSTRING
#define RDEFAULT_QSTRING QString()
#endif



/**
 * This is the abstract base class for all storage implementations.
 * A storage is used to store documents (entities, layers, blocks,
 * transactions) in memory or on disk. Every \ref RDocument "document"
 * is backed by a storage object.
 *
 * A storage implementation is available in the \ref qcaddbstorage.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RStorage : RNonCopyable, public RRequireHeap {
public:
    RStorage();
    virtual ~RStorage() { }

    void setDocument(RDocument* doc) {
        document = doc;
    }

    RDocument* getDocument() const {
        return document;
    }

    /**
     * Resets this storage to its initial, empty state.
     */
    virtual void clear();

    /**
     * Starts a new transaction.
     * This function is called before something is stored in the
     * storage.
     */
    virtual void beginTransaction() = 0;

    /**
     * Commits the current transaction.
     * This function is called after something has been stored in the
     * storage.
     */
    virtual void commitTransaction() = 0;

    /**
     * Rolls the current transaction back in order to cancel it.
     * This function should never be called under normal circumstances.
     */
    virtual void rollbackTransaction() = 0;

    /**
     * \return Ordered list of given IDs for display purposes.
     */
    virtual QList<RObject::Id> orderBackToFront(const QSet<RObject::Id>& entityIds) const;

    QList<RObject::Id> sortBlocks(const QList<RObject::Id>& blockIds) const;

    QList<RObject::Id> sortLayers(const QList<RObject::Id>& layerIds) const;

    /**
     * \nonscriptable
     */
    static bool lessThan(const QPair<RObject::Id, int>& p1, const QPair<RObject::Id, int>& p2);

    /**
     * \return A set of all object IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllObjects() const = 0;

    virtual QSet<RObject::Id> queryAllVisibleEntities() = 0;

    /**
     * \return A set of all entity IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllEntities(bool undone = false,
            bool allBlocks = false, RS::EntityType type = RS::EntityAll) = 0;

    virtual QSet<RObject::Id> queryAllEntities(bool undone,
            bool allBlocks, QList<RS::EntityType> types) = 0;

    /**
     * \return A set of all entity IDs in the current working set.
     */
    virtual QSet<RObject::Id> queryWorkingSetEntities() = 0;

    /**
     * \return A set of all UCS IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllUcs() = 0;

    /**
     * \return A set of all layer IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllLayers(bool undone = false) = 0;

    /**
     * \return A set of all layer state IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllLayerStates(bool undone = false) const = 0;

    /**
     * \return A set of all block IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllBlocks(bool undone = false) = 0;

    /**
     * \return A set of all block IDs of layout blocks of the document.
     */
    virtual QSet<RObject::Id> queryAllLayoutBlocks(bool includeModelSpace = false, bool undone = false) const = 0;

    /**
     * \return A set of all layout IDs of layouts of the document.
     */
    virtual QSet<RObject::Id> queryAllLayouts(bool undone = false) = 0;

    /**
     * \return A set of all view IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllViews(bool undone = false) = 0;

    /**
     * \return A set of all linetype IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllLinetypes() = 0;

    /**
     * \return A set of all entity IDs on the given layer.
     */
    virtual QSet<RObject::Id> queryLayerEntities(RObject::Id layerId, bool allBlocks = false) = 0;

    /**
     * \return A set of all entity IDs of selected entities on the given layer.
     */
    virtual QSet<RObject::Id> querySelectedLayerEntities(RObject::Id layerId, bool allBlocks = false) = 0;

    /**
     * \return True if the given block contains any entities.
     */
    virtual bool hasBlockEntities(RObject::Id blockId) const = 0;

    /**
     * \return A set of all entity IDs that are part of the given block.
     */
    virtual QSet<RObject::Id> queryBlockEntities(RObject::Id blockId) = 0;

    virtual QSet<RObject::Id> queryLayerBlockEntities(RObject::Id layerId, RObject::Id blockId) = 0;

    /**
     * \return A set of all block attributes which are not stored in the
     * block definition but as separate entities on the same level as
     * the block reference.
     */
    virtual QSet<RObject::Id> queryChildEntities(RObject::Id parentId, RS::EntityType type = RS::EntityAll) = 0;

    virtual bool hasChildEntities(RObject::Id parentId) const = 0;

    /**
     * \return A set of all block reference entity IDs that reference
     * the given block.
     */
    virtual QSet<RObject::Id> queryBlockReferences(RObject::Id blockId) const = 0;

    /**
     * \return A set of all block reference entity IDs.
     */
    virtual QSet<RObject::Id> queryAllBlockReferences() const = 0;

    /**
     * \return A set of all viewport entity IDs.
     */
    virtual QSet<RObject::Id> queryAllViewports() const = 0;

    /**
     * \return A set of entity IDs of all selected entities.
     */
    virtual QSet<RObject::Id> querySelectedEntities() const = 0;

    /**
     * \return A set of object IDs of all selected objects (layers, ...).
     */
    virtual QSet<RObject::Id> querySelectedLayers() const = 0;

    /**
     * \return A set of entity IDs of all infinite entities (xlines).
     */
    virtual QSet<RObject::Id> queryInfiniteEntities() const = 0;

    virtual QSharedPointer<RDocumentVariables> queryDocumentVariables() const = 0;
    virtual QSharedPointer<RDocumentVariables> queryDocumentVariablesDirect() const = 0;

    virtual QSharedPointer<RDimStyle> queryDimStyle() const = 0;
    virtual QSharedPointer<RDimStyle> queryDimStyleDirect() const = 0;

    /**
     * \return A shared pointer to the object with the given \c objectId
     *      or null pointer if the object is no available in this storage.
     */
    virtual QSharedPointer<RObject> queryObject(RObject::Id objectId) const = 0;

    virtual QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const {
        return queryObject(objectId);
    }
    virtual RObject* queryObjectCC(RObject::Id objectId) const = 0;
    virtual QSharedPointer<RObject> queryObjectByHandle(RObject::Handle objectHandle) const = 0;

    /**
     * \return A pointer to the entity with the given \c entityId
     *      or NULL if no such entity exists.
     */
    virtual QSharedPointer<REntity> queryEntity(RObject::Id entityId) const = 0;

    virtual QSharedPointer<REntity> queryEntityDirect(RObject::Id entityId) const;

    virtual QSharedPointer<REntity> queryVisibleEntityDirect(RObject::Id entityId) const;

    /**
     * \return A pointer to the UCS with the given \c ucsId
     *      or NULL if no such UCS exists.
     */
    virtual QSharedPointer<RUcs> queryUcs(RObject::Id ucsId) const = 0;

    virtual QSharedPointer<RUcs> queryUcsDirect(RObject::Id ucsId) const {
        return queryUcs(ucsId);
    }

    /**
     * \return A pointer to the UCS with the given \c ucsName
     *      or NULL if no such UCS exists.
     */
    virtual QSharedPointer<RUcs> queryUcs(const QString& ucsName) const = 0;

    /**
     * \return A pointer to the layer with the given \c layerId
     *      or NULL if no such layer exists.
     */
    virtual QSharedPointer<RLayer> queryLayer(RObject::Id layerId) const = 0;

    virtual QSharedPointer<RLayer> queryLayerDirect(RObject::Id layerId) const {
        return queryLayer(layerId);
    }
    virtual QSharedPointer<RLayer> queryLayerDirect(const QString& layerName) const {
        return queryLayerDirect(getLayerId(layerName));
    }

    /**
     * \return A pointer to the layer with the given \c layerName
     *      or NULL if no such layer exists.
     */
    virtual QSharedPointer<RLayer> queryLayer(const QString& layerName) const = 0;

    virtual QSharedPointer<RLayer> queryCurrentLayer() {
        return queryLayer(getCurrentLayerId());
    }

    /**
     * \return A pointer to the layer state with the given \c layerStateId
     *      or NULL if no such layer state exists.
     */
    virtual QSharedPointer<RLayerState> queryLayerState(RObject::Id layerStateId) const = 0;

    virtual QSharedPointer<RLayerState> queryLayerStateDirect(RObject::Id layerStateId) const {
        return queryLayerState(layerStateId);
    }
    virtual QSharedPointer<RLayerState> queryLayerStateDirect(const QString& layerStateName) const {
        return queryLayerStateDirect(getLayerStateId(layerStateName));
    }

    /**
     * \return A pointer to the layer with the given \c layerName
     *      or NULL if no such layer exists.
     */
    virtual QSharedPointer<RLayerState> queryLayerState(const QString& layerStateName) const = 0;


    /**
     * \return A pointer to the layout with the given \c layoutId
     *      or NULL if no such layout exists.
     */
    virtual QSharedPointer<RLayout> queryLayout(RObject::Id layoutId) const = 0;

    virtual QSharedPointer<RLayout> queryLayoutDirect(RObject::Id layoutId) const {
        return queryLayout(layoutId);
    }

    /**
     * \return A pointer to the layout with the given \c layoutName
     *      or NULL if no such layout exists.
     */
    virtual QSharedPointer<RLayout> queryLayout(const QString& layoutName) const = 0;

    virtual QSharedPointer<RView> queryCurrentView() {
        return queryView(getCurrentViewId());
    }

    virtual QSharedPointer<RLinetype> queryLinetypeDirect(RObject::Id linetypeId) const = 0;
    virtual QSharedPointer<RLinetype> queryLinetype(RObject::Id linetypeId) const = 0;
    virtual QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const = 0;

    virtual QSharedPointer<RBlock> queryBlockDirect(RObject::Id blockId) const = 0;
    virtual QSharedPointer<RBlock> queryBlockDirect(const QString& blockName) const {
        return queryBlockDirect(getBlockId(blockName));
    }
    virtual QSharedPointer<RBlock> queryBlock(RObject::Id blockId) const = 0;
    virtual QSharedPointer<RBlock> queryBlock(const QString& blockName) const = 0;

    virtual QSharedPointer<RView> queryView(RObject::Id viewId) const = 0;
    virtual QSharedPointer<RView> queryView(const QString& viewName) const = 0;

    void setCurrentLayer(RObject::Id layerId, RTransaction* transaction=NULL);
    void setCurrentLayer(const QString& layerName, RTransaction* transaction=NULL);

    virtual RObject::Id getCurrentLayerId() const;
    virtual RObject::Id getCurrentViewId() const {
        return currentViewId;
    }

    virtual void setCurrentColor(const RColor& color);
    virtual RColor getCurrentColor() const;

    void setCurrentLineweight(RLineweight::Lineweight lw);
    virtual RLineweight::Lineweight getCurrentLineweight() const;

    void setCurrentLinetype(RObject::Id ltId);
    void setCurrentLinetype(const QString& name);
    void setCurrentLinetypePattern(const RLinetypePattern& p);
    virtual RObject::Id getCurrentLinetypeId() const;
    virtual RLinetypePattern getCurrentLinetypePattern() const;
    virtual QSharedPointer<RLinetype> queryCurrentLinetype() const {
        return queryLinetype(getCurrentLinetypeId());
    }

    virtual QSharedPointer<RBlock> queryCurrentBlock();

    virtual void setCurrentBlock(RObject::Id blockId);

    void setCurrentBlock(const QString& blockName) {
        RObject::Id id = getBlockId(blockName);
        if (id == RObject::INVALID_ID) {
            return;
        }
        setCurrentBlock(id);
    }

    virtual RObject::Id getCurrentBlockId() const {
        return currentBlockId;
    }

    virtual void setCurrentViewport(RObject::Id viewportId) {
        currentViewportId = viewportId;
    }

    virtual void unsetCurrentViewport() {
        currentViewportId = RObject::INVALID_ID;
    }

    virtual RObject::Id getCurrentViewportId() const {
        return currentViewportId;
    }

    virtual void setModelSpaceBlockId(RObject::Id id) {
        modelSpaceBlockId = id;
    }
    virtual RObject::Id getModelSpaceBlockId() const {
        return modelSpaceBlockId;
    }

    void setCurrentView(RObject::Id viewId) {
        currentViewId = viewId;
    }

    void setCurrentView(const QString& viewName) {
        RObject::Id id = getViewId(viewName);
        // unlike blocks and layers, the current view can be invalid:
        setCurrentView(id);
    }

    QSharedPointer<RDocumentVariables> startDocumentVariablesTransaction(RTransaction*& transaction, bool& useLocalTransaction);
    void endDocumentVariablesTransaction(RTransaction* transaction, bool useLocalTransaction, QSharedPointer<RDocumentVariables> docVars);

    void setUnit(RS::Unit unit, RTransaction* transaction=NULL);
    RS::Unit getUnit() const;

    void setMeasurement(RS::Measurement m, RTransaction* transaction=NULL);
    RS::Measurement getMeasurement() const;

    virtual void setDimensionFont(const QString& f, RTransaction* transaction=NULL);
    virtual QString getDimensionFont() const;

    virtual void setLinetypeScale(double v, RTransaction* transaction=NULL);
    virtual double getLinetypeScale() const;

    virtual QString getBlockName(RObject::Id blockId) const = 0;
    virtual QString getBlockNameFromHandle(RObject::Handle blockHandle) const = 0;
    virtual QString getBlockNameFromLayout(const QString& layoutName) const = 0;
    virtual QString getBlockNameFromLayout(RObject::Id layoutId) const = 0;
    virtual QSet<QString> getBlockNames(const QString& rxStr = RDEFAULT_QSTRING, bool undone = false) const = 0;
    virtual RObject::Id getBlockId(const QString& blockName) const = 0;
    virtual RObject::Id getBlockIdAuto(const QString& blockLayoutName) const = 0;
    virtual bool hasBlock(const QString& blockName) const;

    virtual QString getViewName(RObject::Id viewId) const = 0;
    virtual QSet<QString> getViewNames() const = 0;
    virtual RObject::Id getViewId(const QString& viewName) const = 0;
    virtual bool hasView(const QString& viewName) const;

    virtual QString getLayerName(RObject::Id layerId) const = 0;
    virtual QSet<QString> getLayerNames(const QString& rxStr = RDEFAULT_QSTRING) const = 0;
    virtual RObject::Id getLayerId(const QString& layerName) const = 0;
    virtual void setLayer0Id(RObject::Id id) {
        layer0Id = id;
    }
    virtual RObject::Id getLayer0Id() const {
        return layer0Id;
    }
    virtual bool hasLayer(const QString& layerName) const;

    virtual QString getLayerStateName(RObject::Id layerStateId) const = 0;
    virtual QSet<QString> getLayerStateNames(const QString& rxStr = RDEFAULT_QSTRING) const = 0;
    virtual RObject::Id getLayerStateId(const QString& layerStateName) const = 0;
    virtual bool hasLayerStates() const;
    virtual bool hasLayerState(const QString& layerStateName) const;

    virtual QString getLayoutName(RObject::Id layoutId) const = 0;
    virtual QSet<QString> getLayoutNames(const QString& rxStr = RDEFAULT_QSTRING) const = 0;
    virtual RObject::Id getLayoutId(const QString& layoutName) const = 0;
    virtual bool hasLayout(const QString& layoutName) const;

    /**
     * \return Linetype name of the given linetype.
     */
    virtual QString getLinetypeName(RObject::Id linetypeId) const = 0;
    /**
     * \return User readable description for the given linetype.
     */
    virtual QString getLinetypeDescription(RObject::Id linetypeId) const = 0;
    /**
     * \return User readable label for the given linetype.
     */
    virtual QString getLinetypeLabel(RObject::Id linetypeId) const = 0;
    /**
     * \return List of all available linetype pattern names in this document.
     */
    virtual QSet<QString> getLinetypeNames() const = 0;
    /**
     * \return List of all available linetype patterns in this document.
     */
    virtual QList<RLinetypePattern> getLinetypePatterns() const = 0;
    /**
     * \return Linetype ID of the given linetype name or RObject::INVALID_ID.
     */
    virtual RObject::Id getLinetypeId(const QString& linetypeName) const = 0;
    virtual bool hasLinetype(const QString& linetypeName) const;

    /**
     * \return List of custom variable names stored in this document.
     */
    virtual QStringList getVariables() const = 0;
    /**
     * Sets a custom variable in the context of this document.
     *
     * \param key Variable key (name)
     * \param value Variable value
     * \param overwrite True to overwrite an existing variable with the same key (default)
     */
    virtual void setVariable(const QString& key, const QVariant& value, bool overwrite=true) = 0;
    /**
     * Removes the custom variable with the given key.
     */
    virtual void removeVariable(const QString& key) = 0;
    /**
     * \return The value of the given variable or an invalid variant if the
     *      variable does not exist.
     */
    virtual QVariant getVariable(const QString& key) const = 0;

    /**
     * \return True if the given variable exists in this storage.
     */
    virtual bool hasVariable(const QString& key) const {
        QVariant value = getVariable(key);
        return value.isValid();
    }

    /**
     * Sets a known DXF/DWG variable for this document.
     *
     * \param key Variable key (see DXF reference)
     * \param value New value of the variable.
     * \param transaction RTransaction to use for the change or NULL (default) to create a transaction on the fly.
     */
    virtual void setKnownVariable(RS::KnownVariable key, const QVariant& value, RTransaction* transaction = NULL) = 0;

    /**
     * \return Value for the given DXF/DWG variable.
     */
    virtual QVariant getKnownVariable(RS::KnownVariable key) const = 0;

    /**
     * \return Number of selected entities.
     */
    virtual int countSelectedEntities() const {
        return querySelectedEntities().size();
    }

    /**
     * Clears the selection status of all entities.
     */
    virtual void clearEntitySelection(
        QSet<RObject::Id>* affectedEntities=NULL
    ) = 0;

    /**
     * Sets the selection status of all entities.
     */
    virtual void selectAllEntities(QSet<RObject::Id>* affectedEntities = NULL) = 0;

    /**
     * Selects the entity with the given ID.
     *
     * \param add True to add the entity to the current selection.
     *      False to replace the current selection with the given entity.
     * \param affected Optional pointer to an empty set of entity IDs.
     *      After the call, this set will contain all entity IDs of
     *      entities that were affected by the call.
     */
    virtual void selectEntity(
        RObject::Id entityId,
        bool add=false,
        QSet<RObject::Id>* affectedEntities=NULL
    ) = 0;

    /**
     * Selects all entities with the given IDs.
     *
     * \param add True to add the entities to the current selection.
     *      False to replace the current selection with the new entities.
     * \param affected Optional pointer to an empty set of entity IDs.
     *      After the call, this set will contain all entity IDs of
     *      entities that were affected by the call.
     */
    virtual int selectEntities(
        const QSet<RObject::Id>& entityIds,
        bool add=false,
        QSet<RObject::Id>* affectedEntities=NULL
    ) = 0;

    /**
     * Deselects the entity with the given ID.
     *
     * \param affected Optional pointer to an empty set of entity IDs.
     *      After the call, this set will contain all entity IDs of
     *      entities that were affected by the call.
     */
    virtual void deselectEntity(
        RObject::Id entityId,
        QSet<RObject::Id>* affectedEntities=NULL
    ) = 0;

    /**
     * Deselects all entities with the given IDs.
     *
     * \param affected Optional pointer to an empty set of entity IDs.
     *      After the call, this set will contain all entity IDs of
     *      entities that were affected by the call.
     */
    virtual int deselectEntities(
        const QSet<RObject::Id>& entityIds,
        QSet<RObject::Id>* affectedEntities=NULL
    ) = 0;

    virtual bool isSelected(RObject::Id entityId);

    virtual bool isSelectedWorkingSet(RObject::Id entityId);

    virtual bool isEntity(RObject::Id objectId);

    virtual bool isLayerLocked(RObject::Id layerId) const;
    virtual bool isLayerLocked(const RLayer& layer) const;
    virtual bool isParentLayerLocked(RObject::Id layerId) const;
    virtual bool isParentLayerLocked(const RLayer& layer) const;

    virtual bool isLayerOff(RObject::Id layerId) const;
    virtual bool isLayerOff(const RLayer& layer) const;

    virtual bool isLayerOffOrFrozen(RObject::Id layerId) const;
    virtual bool isLayerOffOrFrozen(const RLayer& layer) const;

    virtual bool isLayerFrozen(RObject::Id layerId) const;
    virtual bool isLayerFrozen(const RLayer& layer) const;
    virtual bool isParentLayerFrozen(RObject::Id layerId) const;
    virtual bool isParentLayerFrozen(const RLayer& layer) const;

    virtual bool isLayerSnappable(RObject::Id layerId) const;
    virtual bool isLayerSnappable(const RLayer& layer) const;
    virtual bool isParentLayerSnappable(RObject::Id layerId) const;
    virtual bool isParentLayerSnappable(const RLayer& layer) const;

    virtual bool isLayerPlottable(RObject::Id layerId) const;
    virtual bool isLayerPlottable(const RLayer& layer) const;
    virtual bool isParentLayerPlottable(RObject::Id layerId) const;
    virtual bool isParentLayerPlottable(const RLayer& layer) const;

    virtual bool isEntityVisible(const REntity& entity, RObject::Id blockId) const;

    /**
     * \return True if the given block is frozen.
     */
    virtual bool isBlockFrozen(RObject::Id blockId) const;

    /**
     * \return True if the given block is a layout block (i.e. paper space block).
     */
    virtual bool isLayoutBlock(RObject::Id blockId) const;

    virtual void setObjectId(RObject& object, RObject::Id objectId) const;
    virtual void setObjectHandle(RObject& object, RObject::Handle objectHandle);

    virtual void setEntityParentId(REntity& entity, RObject::Id parentId);

    virtual void setUndoStatus(RObject& object, bool status);

    /**
     * \return True if at least one entity is selected in this storage.
     */
    virtual bool hasSelection() const = 0;

    /**
     * \return The bounding box around all visible entities.
     */
    virtual RBox getBoundingBox(bool ignoreHiddenLayers = true, bool ignoreEmpty = false) const = 0;

    virtual RBox getSelectionBox() const = 0;
    virtual RBox getEntitiesBox(QSet<RObject::Id>& ids) const = 0;

    virtual bool removeObject(QSharedPointer<RObject> object) = 0;

    /**
     * Saves the given object to the storage.
     */
    virtual bool saveObject(QSharedPointer<RObject> object, bool checkBlockRecursion = true, bool keepHandles = false, bool* overwrite = NULL) = 0;

    /**
     * Deletes the object with the given ID.
     */
    virtual bool deleteObject(RObject::Id objectId) = 0;

    /**
     * \return The ID of the last completed transaction.
     * The default implementation reads variable "LastTransaction".
     */
    virtual int getLastTransactionId() {
        return lastTransactionId;
    }

    /**
     * Sets the ID of the last created transaction. This is called
     * when a transaction is undone or redone (the last transaction
     * id indicates where we are in the transaction stack).
     * The default implementation sets the variable "LastTransaction".
     */
    virtual void setLastTransactionId(int transactionId) {
        lastTransactionId = transactionId;

        setModified(true);
    }

    virtual void startTransactionGroup() {
        lastTransactionGroup++;
    }

    virtual int getTransactionGroup() const {
        return lastTransactionGroup;
    }

    /**
     * Saves the given transaction. Transactions need to be stored
     * for undo / redo functionality.
     */
    virtual void saveTransaction(RTransaction& transaction) = 0;

    /**
     * Deletes all transactions with IDs from transactionId (inclusive)
     * to the maximum transaction ID. This is called if some transactions
     * have been undone and then a redo is triggered. All undone
     * transactions have to be deleted at this point.
     */
    virtual void deleteTransactionsFrom(int transactionId) = 0;

    virtual void resetTransactionStack() = 0;

    /**
     * \return Transaction with the given id.
     */
    virtual RTransaction getTransaction(int transactionId) = 0;

    /**
     * Toggles the current undo status of all given objects.
     * The undo status can for example be a boolean value that is true
     * if the object is undone or false otherwise.
     */
    virtual void toggleUndoStatus(QSet<RObject::Id>& objects) = 0;

    /**
     * Toggles the current undo status of the given object.
     */
    virtual void toggleUndoStatus(RObject::Id object) = 0;

    virtual bool setUndoStatus(RObject::Id object, bool status) = 0;

    //virtual bool getUndoStatus(RObject::Id object) const = 0;

    /**
     * \return The highest transaction ID that is in use. This should be
     * used by \ref deleteTransactionsFrom internally.
     */
    virtual int getMaxTransactionId() = 0;

    virtual RLineweight::Lineweight getMaxLineweight() const = 0;

    virtual RObject::Id getNewObjectId();
    virtual RObject::Id getMaxObjectId();
    virtual RObject::Handle getNewObjectHandle();
    virtual RObject::Handle getMaxObjectHandle();

    virtual void setMaxDrawOrder(int m) {
        maxDrawOrder = m;
    }

    virtual int getMaxDrawOrder() {
        return maxDrawOrder;
    }

    virtual int getMinDrawOrder();

    /**
     * Linked storages should return true if the given object is stored
     * in the storage the linked storage links to.
     */
    virtual bool isInBackStorage(RObject::Id /*object*/) {
        return false;
    }

    static QString getKnownVariableName(RS::KnownVariable n);

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, RStorage& s);

    /**
     * Resets the modified flag. Modification time is stored.
     */
    void setModified(bool m);

    /**
     * \return True if the document has unsaved changes.
     */
    bool isModified() const {
        return modified;
    }

    /**
     * \nonscriptable
     */
    QDateTime getLastModifiedDateTime() const {
        return lastModified;
    }

    QString getLastModified() const {
        return lastModified.toString("yyyyMMddHHmmsszzz");
    }

    void addModifiedListener(RModifiedListener* l);

    /**
     * Clear caches:
     */
    virtual void update() {}

    void setNotifyListeners(bool on) {
        notifyGlobalListeners = on;
    }
    bool getNotifyListeners() const {
        return notifyGlobalListeners;
    }

    static void registerCustomEntityType(RS::EntityType type);
    static void unregisterCustomEntityType(RS::EntityType type);

//    RObject::Id getWorkingSetBlockReferenceId() const;
//    void setWorkingSetBlockReferenceId(RObject::Id id, int group = -1, RTransaction* transaction = NULL);

protected:
    QDateTime lastModified;
    bool modified;
    RObject::Handle handleCounter;

    static QList<RS::EntityType> customEntityTypes;

private:
    RDocument* document;
    int maxDrawOrder;
    RObject::Id idCounter;
    RColor currentColor;
    RLineweight::Lineweight currentLineweight;
    RObject::Id currentLinetypeId;
    RObject::Id currentViewId;
    RObject::Id currentBlockId;
    RObject::Id currentViewportId;
    RObject::Id modelSpaceBlockId;
    RObject::Id layer0Id;

    int lastTransactionId;
    int lastTransactionGroup;

    QList<RModifiedListener*> modifiedListeners;
    bool notifyGlobalListeners;

};

Q_DECLARE_METATYPE(RStorage*)
Q_DECLARE_METATYPE(const RStorage*)

#endif
