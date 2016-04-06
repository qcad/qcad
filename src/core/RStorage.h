/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

#include "RBlock.h"
#include "RBlockReferenceEntity.h"
#include "RBox.h"
#include "RDocumentVariables.h"
#include "REntity.h"
#include "RLayer.h"
#include "RLinetype.h"
#include "RLinetypePattern.h"
#include "RModifiedListener.h"
#include "RNonCopyable.h"
#include "RRequireHeap.h"
#include "RTransaction.h"
#include "RUcs.h"
#include "RView.h"

class RDocument;

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
    virtual QList<REntity::Id> orderBackToFront(const QSet<REntity::Id>& entityIds) const;

    /**
     * \return A set of all object IDs of the document.
     */
    virtual QSet<RObject::Id> queryAllObjects() = 0;

    virtual QSet<REntity::Id> queryAllVisibleEntities() = 0;

    /**
     * \return A set of all entity IDs of the document.
     */
    virtual QSet<REntity::Id> queryAllEntities(bool undone = false,
            bool allBlocks = false, RS::EntityType type = RS::EntityAll) = 0;

    /**
     * \return A set of all UCS IDs of the document.
     */
    virtual QSet<RUcs::Id> queryAllUcs() = 0;

    /**
     * \return A set of all layer IDs of the document.
     */
    virtual QSet<RLayer::Id> queryAllLayers(bool undone = false) = 0;

    /**
     * \return A set of all block IDs of the document.
     */
    virtual QSet<RBlock::Id> queryAllBlocks(bool undone = false) = 0;

    /**
     * \return A set of all view IDs of the document.
     */
    virtual QSet<RView::Id> queryAllViews(bool undone = false) = 0;

    /**
     * \return A set of all linetype IDs of the document.
     */
    virtual QSet<RLinetype::Id> queryAllLinetypes() = 0;

    /**
     * \return A set of all entity IDs on the given layer.
     */
    virtual QSet<REntity::Id> queryLayerEntities(RLayer::Id layerId, bool allBlocks = false) = 0;

    /**
     * \return A set of all entity IDs that are part of the given block.
     */
    virtual QSet<REntity::Id> queryBlockEntities(RBlock::Id blockId) = 0;

    virtual QSet<REntity::Id> queryLayerBlockEntities(RLayer::Id layerId, RBlock::Id blockId) = 0;

    /**
     * \return A set of all block attributes which are not stored in the
     * block definition but as separate entities on the same level as
     * the block reference.
     */
    virtual QSet<REntity::Id> queryChildEntities(REntity::Id parentId, RS::EntityType type = RS::EntityAll) = 0;

    virtual bool hasChildEntities(REntity::Id parentId) = 0;

    /**
     * \return A set of all block reference entity IDs that reference
     * the given block.
     */
    virtual QSet<REntity::Id> queryBlockReferences(RBlock::Id blockId) = 0;

    /**
     * \return A set of all block reference entity IDs.
     */
    virtual QSet<REntity::Id> queryAllBlockReferences() = 0;

    /**
     * \return A set of entity IDs of all selected entities.
     */
    virtual QSet<REntity::Id> querySelectedEntities() const = 0;

    /**
     * \return A set of entity IDs of all infinite entities (xlines).
     */
    virtual QSet<REntity::Id> queryInfiniteEntities() = 0;

    virtual QSharedPointer<RDocumentVariables> queryDocumentVariables() const = 0;
    virtual QSharedPointer<RDocumentVariables> queryDocumentVariablesDirect() const = 0;

    /**
     * \return A shared pointer to the object with the given \c objectId
     *      or null pointer if the object is no available in this storage.
     */
    virtual QSharedPointer<RObject> queryObject(RObject::Id objectId) const = 0;

    virtual QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const {
        return queryObject(objectId);
    }
    virtual QSharedPointer<RObject> queryObjectByHandle(RObject::Handle objectHandle) const = 0;

    /**
     * \return A pointer to the enitity with the given \c entityId
     *      or NULL if no such entity exists.
     */
    virtual QSharedPointer<REntity> queryEntity(REntity::Id entityId) const = 0;

    virtual QSharedPointer<REntity> queryEntityDirect(REntity::Id entityId) const {
        return queryEntity(entityId);
    }

    /**
     * \return A pointer to the UCS with the given \c ucsId
     *      or NULL if no such UCS exists.
     */
    virtual QSharedPointer<RUcs> queryUcs(RUcs::Id ucsId) const = 0;

    virtual QSharedPointer<RUcs> queryUcsDirect(RUcs::Id ucsId) const {
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
    virtual QSharedPointer<RLayer> queryLayer(RLayer::Id layerId) const = 0;

    virtual QSharedPointer<RLayer> queryLayerDirect(RLayer::Id layerId) const {
        return queryLayer(layerId);
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
     * \return A pointer to the layout with the given \c layoutId
     *      or NULL if no such layout exists.
     */
    virtual QSharedPointer<RLayout> queryLayout(RLayout::Id layoutId) const = 0;

    virtual QSharedPointer<RLayout> queryLayoutDirect(RLayout::Id layoutId) const {
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

    virtual QSharedPointer<RLinetype> queryLinetypeDirect(RLinetype::Id linetypeId) const = 0;
    virtual QSharedPointer<RLinetype> queryLinetype(RLinetype::Id linetypeId) const = 0;
    virtual QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const = 0;

    virtual QSharedPointer<RBlock> queryBlockDirect(RBlock::Id blockId) const = 0;
    virtual QSharedPointer<RBlock> queryBlock(RBlock::Id blockId) const = 0;
    virtual QSharedPointer<RBlock> queryBlock(const QString& blockName) const = 0;

    virtual QSharedPointer<RView> queryView(RView::Id viewId) const = 0;
    virtual QSharedPointer<RView> queryView(const QString& viewName) const = 0;

    void setCurrentLayer(RLayer::Id layerId, RTransaction* transaction=NULL);
    void setCurrentLayer(const QString& layerName, RTransaction* transaction=NULL);

    virtual RLayer::Id getCurrentLayerId() const;
    virtual RView::Id getCurrentViewId() const {
        return currentViewId;
    }

    virtual void setCurrentColor(const RColor& color);
    virtual RColor getCurrentColor() const;

    void setCurrentLineweight(RLineweight::Lineweight lw);
    virtual RLineweight::Lineweight getCurrentLineweight() const;

    void setCurrentLinetype(RLinetype::Id ltId);
    void setCurrentLinetype(const QString& name);
    void setCurrentLinetypePattern(const RLinetypePattern& p);
    virtual RLinetype::Id getCurrentLinetypeId() const;
    virtual RLinetypePattern getCurrentLinetypePattern() const;
    virtual QSharedPointer<RLinetype> queryCurrentLinetype() const {
        return queryLinetype(getCurrentLinetypeId());
    }

    virtual QSharedPointer<RBlock> queryCurrentBlock() {
        return queryBlock(getCurrentBlockId());
    }

    virtual void setCurrentBlock(RBlock::Id blockId) {
        currentBlockId = blockId;
    }

    void setCurrentBlock(const QString& blockName) {
        RBlock::Id id = getBlockId(blockName);
        if (id == RBlock::INVALID_ID) {
            return;
        }
        setCurrentBlock(id);
    }

    virtual RBlock::Id getCurrentBlockId() const {
        return currentBlockId;
    }

    virtual void setModelSpaceBlockId(RBlock::Id id) {
        modelSpaceBlockId = id;
    }
    virtual RBlock::Id getModelSpaceBlockId() const {
        return modelSpaceBlockId;
    }

    void setCurrentView(RView::Id viewId) {
        currentViewId = viewId;
    }

    void setCurrentView(const QString& viewName) {
        RView::Id id = getViewId(viewName);
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

    virtual QString getBlockName(RBlock::Id blockId) const = 0;
    virtual QSet<QString> getBlockNames(const QString& rxStr = RDEFAULT_QSTRING) const = 0;
    virtual RBlock::Id getBlockId(const QString& blockName) const = 0;
    virtual bool hasBlock(const QString& blockName) const;

    virtual QString getViewName(RView::Id viewId) const = 0;
    virtual QSet<QString> getViewNames() const = 0;
    virtual RView::Id getViewId(const QString& viewName) const = 0;
    virtual bool hasView(const QString& viewName) const;

    virtual QString getLayerName(RLayer::Id layerId) const = 0;
    virtual QSet<QString> getLayerNames(const QString& rxStr = RDEFAULT_QSTRING) const = 0;
    virtual RLayer::Id getLayerId(const QString& layerName) const = 0;
    virtual bool hasLayer(const QString& layerName) const;

    virtual QString getLayoutName(RLayout::Id layoutId) const = 0;
    virtual QSet<QString> getLayoutNames(const QString& rxStr = RDEFAULT_QSTRING) const = 0;
    virtual RLayout::Id getLayoutId(const QString& layoutName) const = 0;
    virtual bool hasLayout(const QString& layoutName) const;

    virtual QString getLinetypeName(RLinetype::Id linetypeId) const = 0;
    virtual QString getLinetypeDescription(RLinetype::Id linetypeId) const = 0;
    virtual QString getLinetypeLabel(RLinetype::Id linetypeId) const = 0;
    virtual QSet<QString> getLinetypeNames() const = 0;
    virtual QList<RLinetypePattern> getLinetypePatterns() const = 0;
    virtual RLinetype::Id getLinetypeId(const QString& linetypeName) const = 0;
    virtual bool hasLinetype(const QString& linetypeName) const;

    virtual QStringList getVariables() const = 0;
    virtual void setVariable(const QString& key, const QVariant& value, bool overwrite=true) = 0;
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

    virtual void setKnownVariable(RS::KnownVariable key, const QVariant& value, RTransaction* transaction = NULL) = 0;
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
        QSet<REntity::Id>* affectedEntities=NULL
    ) = 0;

    /**
     * Sets the selection status of all entities.
     */
    virtual void selectAllEntites(QSet<REntity::Id>* affectedEntities = NULL) = 0;

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
        REntity::Id entityId,
        bool add=false,
        QSet<REntity::Id>* affectedEntities=NULL
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
    virtual void selectEntities(
        const QSet<REntity::Id>& entityIds,
        bool add=false,
        QSet<REntity::Id>* affectedEntities=NULL
    ) = 0;

    /**
     * Deselects the entity with the given ID.
     *
     * \param affected Optional pointer to an empty set of entity IDs.
     *      After the call, this set will contain all entity IDs of
     *      entities that were affected by the call.
     */
    virtual void deselectEntity(
        REntity::Id entityId,
        QSet<REntity::Id>* affectedEntities=NULL
    ) = 0;

    /**
     * Deselects all entities with the given IDs.
     *
     * \param affected Optional pointer to an empty set of entity IDs.
     *      After the call, this set will contain all entity IDs of
     *      entities that were affected by the call.
     */
    virtual bool deselectEntities(
        const QSet<REntity::Id>& entityIds,
        QSet<REntity::Id>* affectedEntities=NULL
    ) = 0;

    virtual bool isSelected(REntity::Id entityId) {
        QSharedPointer<REntity> e = queryEntityDirect(entityId);
        return (!e.isNull() && e->isSelected());
    }

    virtual bool isEntity(RObject::Id objectId) {
        QSharedPointer<REntity> e = queryEntityDirect(objectId);
        return !e.isNull();
    }

    virtual bool isLayerLocked(RLayer::Id layerId) const {
        QSharedPointer<RLayer> l = queryLayerDirect(layerId);
        if (l.isNull()) {
            return false;
        }
        return l->isLocked();
    }

    virtual bool isLayerFrozen(RLayer::Id layerId) const {
        QSharedPointer<RLayer> l = queryLayerDirect(layerId);
        if (l.isNull()) {
            return false;
        }
        return l->isFrozen();
    }

    virtual bool isBlockFrozen(RBlock::Id blockId) const {
        QSharedPointer<RBlock> b = queryBlockDirect(blockId);
        if (b.isNull()) {
            return false;
        }
        return b->isFrozen();
    }

    virtual void setObjectId(RObject& object, RObject::Id objectId);
    virtual void setObjectHandle(RObject& object, RObject::Handle objectHandle);

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

    virtual bool removeObject(QSharedPointer<RObject> object) = 0;

    /**
     * Saves the given object to the storage.
     */
    virtual bool saveObject(QSharedPointer<RObject> object, bool checkBlockRecursion = true, bool keepHandles = false) = 0;

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
     * have been undone and then a redo is triggerd. All undone
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

    void setModified(bool m);

    bool isModified() const {
        return modified;
    }

    void addModifiedListener(RModifiedListener* l);

    /**
     * Clear caches:
     */
    virtual void update() {}

protected:
    bool modified;

private:
    RDocument* document;
    int maxDrawOrder;
    RObject::Id idCounter;
    RObject::Handle handleCounter;
    RColor currentColor;
    RLineweight::Lineweight currentLineweight;
    RLinetype::Id currentLinetypeId;
    RView::Id currentViewId;
    RBlock::Id currentBlockId;
    RBlock::Id modelSpaceBlockId;

    int lastTransactionId;
    int lastTransactionGroup;

    QList<RModifiedListener*> modifiedListeners;
};

Q_DECLARE_METATYPE(RStorage*)
Q_DECLARE_METATYPE(const RStorage*)

#endif
