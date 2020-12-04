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

#ifndef RTRANSACTION_H
#define RTRANSACTION_H

#include "core_global.h"

#include <QList>
#include <QMap>
#include <QSet>
#include <QSharedPointer>

#include "RObject.h"
#include "REntity.h"
#include "RPropertyTypeId.h"
#include "RPropertyChange.h"

class RStorage;
class RExporter;

#define RDEFAULT_QSET_RPROPERTYTYPEID QSet<RPropertyTypeId> ()

/**
 * Transaction implementation.
 * 
 * A transaction encapsulates a change of state of a document.
 * Every change of a drawing document is wrapped in a transaction
 * and handled by the QCAD Application Framework as
 * one change. A transaction might add one or multiple objects,
 * modify existing objects or delete objects. Combinations in the
 * same transaction are also possible.
 * 
 * Each transactions should contain a locical change to a drawing.
 * For example if a selection is moved from one place to another,
 * all entities that are part of the selection are moved in the
 * same transaction. This is important for the undo / redo mechanism
 * of QCAD. If each entity would be moved in a separate transaction, 
 * the user would have to issue an undo command for each entity to
 * get back to the state before the entities were moved.
 *
 * Transactions can be applied to a document and are
 * handled by an \ref RTransactionStack for undo / redo functionality. 
 * Transactions are stored in a storage.
 * 
 * Transactions in the QCAD Application Framework are a low level
 * concept. They are unaware of graphics views or widgets that need 
 * to be updated.
 *
 * Transaction listeners may be used to intercept, complete or inspect
 * transactions:
 * RTransactionListener, RInterTransactionListener.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RTransaction {
public:
    /**
     * Transaction type for optimizations.
     */
    enum Type {
        Generic = 0x0000,
        CurrentLayerChange = 0x0001,
        CurrentLayerSelectionChange = 0x0002,
        LayerLockStatusChange = 0x0004,
        LayerVisibilityStatusChange = 0x0008,
        SaveWorkingSet = 0x0010,
        ChangeDocumentSetting = 0x0020,
        Undo = 0x0040,
        Redo = 0x0080
    };
    Q_DECLARE_FLAGS(Types, Type)

public:
    RTransaction();

    RTransaction(RStorage& storage);

    RTransaction(RStorage& storage, int transactionId, const QString& text,
            const QList<RObject::Id>& affectedObjectIds,
            //const QSet<RObject::Id>& affectedEntities,
            const QMap<RObject::Id, QList<RPropertyChange> >& propertyChanges);
            //RTransaction* parent = NULL);

    RTransaction(RStorage& storage, const QString& text, bool undoable = true);
            //RTransaction* parent = NULL);

    virtual ~RTransaction();

    void setRecordAffectedObjects(bool on) {
        recordAffectedObjects = on;
    }

    void setAllowAll(bool on) {
        allowAll = on;
    }

    void setAllowInvisible(bool on) {
        allowInvisible = on;
    }

    void setSpatialIndexDisabled(bool on) {
        spatialIndexDisabled = on;
    }

    void setExistingBlockDetectionDisabled(bool on) {
        existingBlockDetectionDisabled = on;
    }

    void setExistingLayerDetectionDisabled(bool on) {
        existingLayerDetectionDisabled = on;
    }

    void setExistingLinetypeDetectionDisabled(bool on) {
        existingLinetypeDetectionDisabled = on;
    }

    void setBlockRecursionDetectionDisabled(bool on) {
        blockRecursionDetectionDisabled = on;
    }

    void setKeepHandles(bool on) {
        keepHandles = on;
    }

//    void setUndoing(bool on) {
//        undoing = on;
//    }

    bool isUndoing() {
        return undoing;
    }

//    void setRedoing(bool on) {
//        redoing = on;
//    }

    bool isRedoing() {
        return redoing;
    }

    /**
     * \return True if this transaction should store undo / redo information
     *      for later undo / redo functionality.
     */
    bool isUndoable() const {
        return undoable;
    }

    bool isFailed() const {
        return failed;
    }

    /**
     * Redo undone changes.
     */
    virtual void redo();

    /**
     * Reverts a change to the document. After undo() is called, the state of
     * the document should be the same as before redo() was called.
     */
    virtual void undo();

    void end();

    void updateAffectedBlockReferences();

    /**
     * Sets the ID of this transaction. Typically called by a storage which manages
     * transaction IDs.
     */
    void setId(int id) {
        transactionId = id;
    }

    /**
     * \return Unique ID of this transaction.
     */
    int getId() const {
        return transactionId;
    }

    /**
     * Set group.
     */
    void setGroup(int group) {
        transactionGroup = group;
    }

    /**
     * \return Group of this transaction.
     */
    int getGroup() const {
        return transactionGroup;
    }

    /**
     * \return Logged text for this transaction.
     */
    QString getText() const {
        return text;
    }

    bool overwriteBlock(QSharedPointer<RBlock> block);

    bool addObject(QSharedPointer<RObject> obj,
                   bool useCurrentAttributes = true,
                   bool forceNew = false,
                   const QSet<RPropertyTypeId>& modifiedPropertyTypeIds = RDEFAULT_QSET_RPROPERTYTYPEID);

    void addAffectedObject(RObject::Id objectId);
    void addAffectedObjects(const QSet<RObject::Id>& objectIds);
    void addAffectedObject(QSharedPointer<RObject> object);

    void deleteObject(RObject::Id objectId, bool force = false);
    void deleteObject(QSharedPointer<RObject> object, bool force = false);

    /**
     * \return List of object IDs of objects that are affected by
     *      this transaction.
     */
    QList<RObject::Id> getAffectedObjects() const {
        return affectedObjectIds;
    }

    /**
     * \return Set of object IDs of objects that have been created or
     *      deleted by this transaction.
     */
    QSet<RObject::Id> getStatusChanges() const {
        return statusChanges;
    }

    bool hasStatusChange(RObject::Id id) const {
        return statusChanges.contains(id);
    }

    /**
     * \return Map of properties that are changed by this transaction.
     */
    QMap<RObject::Id, QList<RPropertyChange> > getPropertyChanges() const {
        return propertyChanges;
    }

    QList<RPropertyChange> getPropertyChanges(RObject::Id id) const;

    bool hasOnlyChanges() const {
        return onlyChanges;
    }

    void fail();

    void endCycle();

    bool isPreview() const;

    void setTypes(RTransaction::Types t) {
        types = t;
    }
    RTransaction::Types getTypes() const {
        return types;
    }
    void setType(RTransaction::Type type, bool on = true);
    bool getType(RTransaction::Type type) const;

protected:
    bool addPropertyChange(RObject::Id objectId, const RPropertyChange& propertyChange);
    //void appendChild(RTransaction& t);

    void commit();
    void rollback();

protected:
    RTransaction::Types types;

    /**
     * A transaction always belongs to the storage of a document.
     */
    RStorage* storage;

    /**
     * Unique ID of this transaction.
     */
    int transactionId;

    /**
     * Transaction group or -1. Transaction groups are undone / redone together.
     */
    int transactionGroup;

    /**
     * Log entry for this transaction
     */
    QString text;

    /**
     * List of IDs of all objects that are affected by this transaction.
     * Needs to be in order (not a set):
     */
    QList<RObject::Id> affectedObjectIds;
    QSet<RObject::Id> affectedObjectIdsSet;

    /**
     * List of IDs of all block references that need to be updated.
     */
    QSet<RObject::Id> affectedBlockReferenceIds;

    /**
     * Map of properties that are changed by this transaction. For every
     * undoable, a whole list of properties might have changed in a fixed
     * order.
     */
    QMap<RObject::Id, QList<RPropertyChange> > propertyChanges;

    /**
     * Contains affected objects that have been created or deleted
     * in this transaction.
     */
    QSet<RObject::Id> statusChanges;

    /**
     * Child transactions of this transaction.
     */
    //QList<RTransaction> childTransactions;

    /**
     * True if this transaction can be undone.
     */
    bool undoable;

    /**
     * True if this transaction failed.
     */
    bool failed;

    /**
     * True if this transaction only changed objects, no additions, no deletes.
     */
    bool onlyChanges;

    /**
     * True if caller is intereseted in list of objects that are affected
     * by this transaction.
     */
    bool recordAffectedObjects;

    /**
     * True if all transactions are allowed, even transactions on locked or
     * invisible layers. Typically the case for importers.
     */
    bool allowAll;

    /**
     * True if all transactions on invisible entities are allowed,
     * typically transactions on invisible layers. Used to move entities
     * to an invisible layer.
     */
    bool allowInvisible;

    /**
     * True to ignore spatial index. Used for importers which regenerate
     * the spatial index in the end.
     */
    bool spatialIndexDisabled;

    /**
     * True to disable detection of existing blocks (performance gain).
     */
    bool existingBlockDetectionDisabled;

    /**
     * True to disable detection of existing layers (performance gain).
     */
    bool existingLayerDetectionDisabled;

    /**
     * True to disable detection of existing linetypes (performance gain).
     */
    bool existingLinetypeDetectionDisabled;

    /**
     * True to disable block recursion detection (performance gain for loading).
     */
    bool blockRecursionDetectionDisabled;

    /**
     * True to keep existing object handles (importers).
     */
    bool keepHandles;

    QMap<RObject::Id, RObject::Id> cloneIds;

    bool undoing;
    bool redoing;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, RTransaction& t);

Q_DECLARE_OPERATORS_FOR_FLAGS(RTransaction::Types)
Q_DECLARE_METATYPE(RTransaction)
Q_DECLARE_METATYPE(RTransaction*)
Q_DECLARE_METATYPE(RTransaction::Type)
Q_DECLARE_METATYPE(RTransaction::Type*)
Q_DECLARE_METATYPE(QFlags<RTransaction::Type>)
Q_DECLARE_METATYPE(QFlags<RTransaction::Type>*)

#endif
