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
class RDocument;

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
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RTransaction {
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

    void setBlockRecursionDetectionDisabled(bool on) {
        blockRecursionDetectionDisabled = on;
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
     * Applies this command to the document.
     */
    virtual void redo(RDocument* objectContainer = NULL);

    /**
     * Reverts a change to the document. After undo() is called, the state of
     * the document should be the same as before redo() was called.
     */
    virtual void undo(RDocument* objectContainer = NULL);

    /**
     * Previews this transaction (as it would be applied) by exporting the result to
     * the given exporter. The exporter typically exports into the preview of a
     * graphics scene.
     */
    //virtual void preview(RExporter& /*exporter*/) const {}

    void end();

    void updateOverwrittenBlockReferences();

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

    void deleteObject(RObject::Id objectId, RDocument* document);
    void deleteObject(QSharedPointer<RObject> object, RDocument* document);

    /**
     * \return Set of object IDs of objects that are affected by
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

    /**
     * \return Map of properties that are changed by this transaction.
     */
    QMap<RObject::Id, QList<RPropertyChange> > getPropertyChanges() const {
        return propertyChanges;
    }

    bool hasOnlyChanges() const {
        return onlyChanges;
    }

    void fail();

    void endCycle();

protected:
    bool addPropertyChange(RObject::Id objectId, const RPropertyChange& propertyChange);
    //void appendChild(RTransaction& t);

    void commit();
    void rollback();

protected:
    /**
     * A transaction always belongs to the storage of a document.
     */
    RStorage* storage;

    /**
     * Unique ID of this transaction.
     */
    int transactionId;

    /**
     * Log entry for this transaction
     */
    QString text;

    /**
     * List of IDs of all objects that are affected by this transaction.
     */
    QList<RObject::Id> affectedObjectIds;

    /**
     * List of IDs of all block references that need to be .
     */
    QList<RObject::Id> overwrittenBlockReferences;

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
     * True to disable block recursion detection (performance gain for loading).
     */
    bool blockRecursionDetectionDisabled;

    QMap<RObject::Id, RObject::Id> cloneIds;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, RTransaction& t);

Q_DECLARE_METATYPE(RTransaction)
Q_DECLARE_METATYPE(RTransaction*)

#endif
