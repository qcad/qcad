/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
#include "RTransactionStack.h"

#include "RDebug.h"
#include "RTransaction.h"
#include "RStorage.h"



RTransactionStack::RTransactionStack(RStorage& storage)
    : storage(storage) {
}

RTransactionStack::~RTransactionStack() {
}

void RTransactionStack::reset() {
    storage.resetTransactionStack();
}

bool RTransactionStack::isUndoAvailable() const {
    int lastTransactionId = storage.getLastTransactionId();

    if (lastTransactionId < 0) {
        return false;
    }
    return true;
}

bool RTransactionStack::isRedoAvailable() const {
    int lastTransactionId = storage.getLastTransactionId();
    int maxTransactionId = storage.getMaxTransactionId();
    if (lastTransactionId >= maxTransactionId) {
        return false;
    }
    return true;
}



/**
 * Undoes the last transaction.
 *
 * \return Transaction that was undone. The transaction contains a set of 
 *   affected entity IDs. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
RTransaction RTransactionStack::undo() {
    int lastTransactionId = storage.getLastTransactionId();

    if (lastTransactionId<0) {
        qWarning("RTransactionStack::undo: "
            "already at top of transaction stack");
        return RTransaction(storage);
    }

    RTransaction lastTransaction = storage.getTransaction(lastTransactionId);

    // move up in transaction log:
    storage.setLastTransactionId(lastTransactionId-1);

    lastTransaction.undo();

    return lastTransaction;
}



/**
 * Redoes the last transaction.
 *
 * \return Set of affected entity IDs. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
RTransaction RTransactionStack::redo() {
    int lastTransactionId = storage.getLastTransactionId();

    if (lastTransactionId >= storage.getMaxTransactionId()) {
        qWarning("RTransactionStack::redo: "
            "already at bottom of transaction stack");
        return RTransaction(storage);
    }

    // move down in transaction log:
    storage.setLastTransactionId(lastTransactionId+1);
    
    RTransaction lastTransaction = storage.getTransaction(lastTransactionId+1);

    // update entity undo status:
    //std::set<REntity::Id> affectedEntities = lastTransaction.getAffectedEntities();
    //storage.toggleUndoStatus(affectedEntities);
    lastTransaction.redo();

    return lastTransaction;
}
