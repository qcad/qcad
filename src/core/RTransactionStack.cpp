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

QString RTransactionStack::getUndoableTransactionText() const {
    int lastTransactionId = storage.getLastTransactionId();

    if (lastTransactionId < 0) {
        return "";
    }
    return storage.getTransaction(lastTransactionId).getText();
}

QString RTransactionStack::getRedoableTransactionText() const {
    int lastTransactionId = storage.getLastTransactionId();
    int maxTransactionId = storage.getMaxTransactionId();

    if (lastTransactionId >= maxTransactionId) {
        return "";
    }
    return storage.getTransaction(lastTransactionId+1).getText();
}

/**
 * Undoes the last transaction.
 *
 * \return Transaction that was undone. The transaction contains a set of 
 *   affected entity IDs. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
QList<RTransaction> RTransactionStack::undo() {
    QList<RTransaction> ret;
    int lastGroup = -2;
    bool done = true;

    do {
        int transactionId = storage.getLastTransactionId();

        if (transactionId<0) {
//            qWarning("RTransactionStack::undo: "
//                "already at top of transaction stack");
            return ret;
        }

        RTransaction transaction = storage.getTransaction(transactionId);

        done = lastGroup==-1 || (lastGroup!=-2 && transaction.getGroup()!=lastGroup);

        if (!done) {
            // move up in transaction log:
            storage.setLastTransactionId(transactionId-1);

            transaction.undo();

            ret.append(transaction);

            lastGroup = transaction.getGroup();
        }
    } while(!done);

    return ret;
}



/**
 * Redoes the last transaction.
 *
 * \return Set of affected entity IDs. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
QList<RTransaction> RTransactionStack::redo() {
    QList<RTransaction> ret;
    int lastGroup = -2;
    bool done = true;

    do {
        int transactionId = storage.getLastTransactionId();

        if (transactionId >= storage.getMaxTransactionId()) {
//            qWarning("RTransactionStack::redo: "
//                "already at bottom of transaction stack");
            qDebug() << "nothing to redo anymore";
            return ret;
        }

        RTransaction transaction = storage.getTransaction(transactionId+1);

        done = lastGroup==-1 || (lastGroup!=-2 && transaction.getGroup()!=lastGroup);

        if (!done) {
            // move down in transaction log:
            storage.setLastTransactionId(transactionId+1);

            // update entity undo status:
            transaction.redo();

            ret.append(transaction);


            lastGroup = transaction.getGroup();
        }
    } while(!done);

    return ret;
}
